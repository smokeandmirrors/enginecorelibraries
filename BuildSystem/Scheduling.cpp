#include <list>
#include <string>
#include <vector>
#if WIN32
#include <process.h>
#include <windows.h>
#endif//WIN32

#include "Scheduling.h"
#include "Signals.h"
#include "Synchronization.h"
#include "Thread.h"

using namespace signals;

namespace concurrency
{
#if WIN32
inline uint 
getNumHardwareThreads(void)
{
	_SYSTEM_INFO system_info;
	GetSystemInfo(&system_info);
}
#else
	PREVENT_COMPILE
#endif//WIN32

/** a wrapper for a Thread that can be added to the scheduler */
class Scheduler::Job : public Receiver
{
public:
	void 
	ceaseReception(void)
	{
		m_receiver.ceaseReception();
	}

	cpuID 
	getPreferredCPU(void) const
	{
		return m_thread->getPreferredCPU();
	}

	threadID
	getThreadID(void) const
	{
		threadID id;

		if (m_thread)
		{
			m_thread->getID(id);
		}
		else
		{
			id = 0xFFFFFFFF;
		}

		return id;
	}

	void
	reset(Thread* thread)
	{
		m_thread = thread;
		m_thread->connect(this, &Job::onComplete);
	}

	inline void
	onComplete(Thread*)
	{
		Scheduler::single().accountForFinish(this);
	}

	inline void
	onConnect(Transmitter* transmitter)
	{
		m_receiver.onConnect(transmitter);
	}

	inline void
	onDisconnect(Transmitter* transmitter)
	{
		m_receiver.onDisconnect(transmitter);
	}

	inline void
	onRecycle(void)
	{
		m_thread->disconnect(this);
		delete m_thread;
		m_thread = NULL;
	}

	inline void
	start(cpuID& requiredCPU) 
	{
		m_thread->execute(requiredCPU);
	}

	const std::string& 
	toString(void) const
	{
		static std::string badThreadMessage("invalid");
		
		return m_thread 
			? m_thread->toString() 
			: badThreadMessage;
	}

private:
	friend class PendingJobQueue;

	Job(void)
		: m_thread(NULL)
	{ /* empty */ }

	~Job(void)
	{
		delete m_thread;
	}

	signals::ReceiverMember	
		m_receiver;

	Thread* 
		m_thread;
}; // Job 

class Scheduler::PendingJobQueue
{
public:
	inline void 
		add(Executor& executable, cpuID preferredCPU, Thread** waitable)
	{
		Job* job = getFreeJob();
		Thread* thread; 
		
		if (waitable)
		{
			thread = Thread::getSuspended(executable, preferredCPU);
			*waitable = thread;
		}
		else
		{
			thread = Thread::getUninitialized(executable, preferredCPU);
		}
		
		job->reset(thread);
		m_pendingJobs.push_back(job);
	}

	inline bool 
		areJobsPending(void) const
	{
		return getNumber() != 0;
	}

	cpuID 
		getNextPreferredCPU(void) const
	{
		if (areJobsPending())
		{
			Job* nextJob = m_pendingJobs.front();
			return nextJob->getPreferredCPU();
		}
		else
		{
			return noCPUpreference;
		}	
	}

	inline Job* 
		getFreeJob(void)
	{
		Job* job;

		if (m_jobPool.empty())
		{
			job = new Job();
		}
		else
		{
			job = m_jobPool.back();
			m_jobPool.pop_back();
		}

		return job;
	}

	inline Job* 
		getNextJob()
	{
		if (areJobsPending())
		{
			Job* nextJob = m_pendingJobs.front();
			m_pendingJobs.pop_front();
			return nextJob;
		}
		else
		{
			return NULL;
		}
	}

	inline uint 
		getNumber(void) const
	{
		return static_cast<uint>(m_pendingJobs.size());
	}

	inline void 
		recycleJob(Job* complete)
	{
		complete->onRecycle();
		m_jobPool.push_back(complete);
	}

private:
	/** \todo make m_pendingJobs a priority queue */
	std::list<Job*> 
		m_pendingJobs;

	std::vector<Job*>
		m_jobPool;
}; // class PendingJobQueue 

Scheduler::Scheduler(void)
: m_numActiveJobs(0)
{
	initializeNumberSystemThreads();
	m_maxThreads = getNumberSystemThreads();
	m_activeJobs.resize(m_maxThreads);

	for (uint i = 0; i < m_numSystemThreads; i++)
	{
		m_activeJobs[i] = NULL;
	}

	m_pendingJobs = new PendingJobQueue();
}

Scheduler::~Scheduler(void)
{
	delete m_pendingJobs;
}

void Scheduler::accountForFinish(Job* finished)
{
	SYNC(m_mutex);
	sint thread_index = -1;

	for (uint i = 0; i < m_numSystemThreads; i++)
	{
		if (m_activeJobs[i] == finished)
		{
			thread_index = static_cast<sint>(i);
			break;
		}
	}

	assert(thread_index != -1);
	m_activeJobs[thread_index] = NULL;
	m_numActiveJobs--;
	

	threadID originalID;

	if (Scheduler::single().isOriginalWaitingOnThread(finished->getThreadID(), &originalID))
	{
		std::map<threadID, std::vector<Job*>*>::iterator iter =
			m_childJobsByOriginalID.find(originalID);

		iter->second->push_back(finished);
	}
	else
	{
		m_pendingJobs->recycleJob(finished);
	}
	
	startJobs();
	printState();
}

void Scheduler::accountForStartedJob(Job* started, cpuID index)
{
	m_activeJobs[index] = started;
	m_numActiveJobs++;
	printState();
}

void Scheduler::enqueue(Executor& executable, cpuID preferredCPU)
{
	SYNC(m_mutex);
	 
	threadID parentID = Thread::getCurrentID();
	std::map<threadID, threadID>::iterator originalIDIter = m_originalByChildren.find(parentID);

	if (originalIDIter != m_originalByChildren.end())
	{	// parent thread is waiting on this tree, so the child thread must at least get started
		threadID originalID = originalIDIter->second;
		
		// initialize the child thread
		Thread* childThread(NULL);
		m_pendingJobs->add(executable, preferredCPU, &childThread);
		assert(childThread);
		
		// add the child thread to the originals list threads to wait on
		std::map<threadID, std::vector<Thread*>* >::iterator threadsIter =
			m_childThreadsByOriginalID.find(originalIDIter->second);
		assert(threadsIter != m_childThreadsByOriginalID.end());
		std::vector<Thread*>& childThreads = *(threadsIter->second);
		childThreads.push_back(childThread);

		// make sure we can find the original by the child ID, in case 
		// the child spawns more threads
		threadID childID;
		bool success = childThread->getID(childID);
		assert(success);
		// make sure the current thread isn't already waiting on tree of threads
		assert(m_originalByChildren.find(childID) == m_originalByChildren.end());
		// map the original ID to the children
		m_originalByChildren[childID] = originalID;
		assert(isOriginalWaitingOnThread(childID));
	}
	else
	{
		m_pendingJobs->add(executable, preferredCPU, NULL);
	}
	// if parent is waiting on this thread
		// add child job to original waiting list (use enqueue and wait?)
	startJobs();
	printState();
}

void Scheduler::enqueueAndWait(Executor& executable, cpuID preferredCPU)
{
	Thread* output(NULL);
	{
		SYNC(m_mutex);
		m_pendingJobs->add(executable, preferredCPU, &output);
		startJobs();
		printState();
	}
	Thread::waitOnCompletion(*output);
	printState();
}

void Scheduler::enqueueAndWaitOnChildren(Executor& executable, cpuID preferredCPU)
{
	std::vector<Thread*>* children(NULL);
	std::vector<Job*>* childJobs(NULL);

	threadID originalID;
	
	{
		SYNC(m_mutex);
		Thread* output(NULL);
		m_pendingJobs->add(executable, preferredCPU, &output);
		// get the current thread ID for the parent
		originalID = Thread::getCurrentID();
		// get the child thread ID
		threadID childID;
		bool success = output->getID(childID);
		assert(success);
		// make sure the current thread isn't already waiting on tree of threads
		assert(m_originalByChildren.find(originalID) == m_originalByChildren.end());
		// create the list of child threads do wait on
		children = new std::vector<Thread*>();
		children->push_back(output);
		childJobs = new std::vector<Job*>();
		// map the children to the parent ID
		m_childThreadsByOriginalID[originalID] = children;
		m_childJobsByOriginalID[originalID] = childJobs;
		// map the parent ID to the children
		m_originalByChildren[childID] = originalID;
		// start the jobs
		startJobs();
		printState();
	}
	
	Thread::waitOnCompletionOfTree(*children);
	
	{
		SYNC(m_mutex);
		{
			std::vector<Thread*>::iterator sentinel(children->end());
			for (std::vector<Thread*>::iterator iter(children->begin());
			iter != sentinel;
			iter++)
			{
				threadID childID;
				bool success = (*iter)->getID(childID);
				assert(success);
				m_originalByChildren.erase(childID);
			}
			m_childThreadsByOriginalID.erase(originalID);
			delete children;
		}
		
		{
			std::vector<Job*>::iterator sentinel(childJobs->end());
			for (std::vector<Job*>::iterator iter(childJobs->begin());
			iter != sentinel;
			iter++)
			{
				m_pendingJobs->recycleJob(*iter);
			}

			m_childJobsByOriginalID.erase(originalID);
			delete childJobs;
		}

	}
	
	printState();
}

bool Scheduler::getFreeIndex(cpuID& index)
{
	SYNC(m_mutex);
	for (uint i = 0; i < m_numSystemThreads; i++)
	{
		if (!m_activeJobs[i])
		{
			index = static_cast<cpuID>(i);
			return true;
		}
	}

	return false;
}

bool Scheduler::getFreeIndex(cpuID& available, cpuID idealCPU)
{
	SYNC(m_mutex);
	if (idealCPU != noCPUpreference && !m_activeJobs[idealCPU])
	{
		available = idealCPU;
		return true;
	}
	else
	{
		return getFreeIndex(available);
	}	
}

uint Scheduler::getMaxThreads(void) const 
{ 
	SYNC(m_mutex);
	return m_maxThreads; 
}

uint Scheduler::getNumberActiveJobs(void) const
{
	SYNC(m_mutex);
	return m_numActiveJobs;
}

uint Scheduler::getNumberPendingJobs(void) const
{
	SYNC(m_mutex);
	return m_pendingJobs->getNumber();
}

uint Scheduler::getNumberSystemThreads(void) const	
{ 
	SYNC(m_mutex);
	return m_numSystemThreads; 
}

void Scheduler::initializeNumberSystemThreads(void)
{
#if WIN32
	SYSTEM_INFO windows_info;
	GetSystemInfo(&windows_info);
	m_numSystemThreads = windows_info.dwNumberOfProcessors;
#else
	PREVENT_COMPILE
#endif//WIN32
}

bool Scheduler::isAnyIndexFree(void) const
{
	for (uint i = 0; i < m_numSystemThreads; i++)
	{
		if (!m_activeJobs[i])
		{
			return true;
		}
	}

	return false;
}

bool Scheduler::isAnyJobPending(void) const
{
	return m_pendingJobs->getNumber() != 0;
}

bool Scheduler::isOriginalWaitingOnThread(threadID childID, threadID* originalID) const
{
	std::map<threadID, threadID>::const_iterator originalIDIter = m_originalByChildren.find(childID);
	
	if (originalIDIter != m_originalByChildren.end())
	{
		if (originalID)
		{
			*originalID = originalIDIter->second;
		}

		return true;
	}
	else
	{
		return false;
	}
}


void Scheduler::printState(void) const
{
	return;
	//SYNC(m_mutex);
	// printf(toString().c_str());
}

void Scheduler::setMaxThreads(uint max)			
{ 
	SYNC(m_mutex);
	m_maxThreads = max; 
}

void Scheduler::startJobs(void)
{
	SYNC(m_mutex);
	while (isAnyJobPending() && isAnyIndexFree())
	{
		cpuID preferred(m_pendingJobs->getNextPreferredCPU());
		cpuID required;
		bool success = getFreeIndex(required, preferred);
		assert(success);
		Job* job = m_pendingJobs->getNextJob();
		job->start(required);
		accountForStartedJob(job, required);
	}
}

const std::string Scheduler::toString(void) const
{
	std::string output;
	
	char buffer[256];
	int index = 256;
	do 
	{
		index--;
		buffer[index] = '\0';
	} 
	while (index);
	
	sprintf_s(buffer, "\n\n*** Scheduler state ***\n"
		"System Threads: %d\n"
		"Max Threads: %d\n"
		, m_numSystemThreads
		, m_maxThreads
		);
	output += buffer;

	index = 256;
	do 
	{
		index--;
		buffer[index] = '\0';
	} 
	while (index);
	sprintf_s(buffer, "Number of pending jobs: %d\n", getNumberPendingJobs());
	output += buffer;

	for (uint hardware_index = 0; hardware_index < getNumberSystemThreads(); hardware_index++)
	{
		index = 256;
		do 
		{
			index--;
			buffer[index] = '\0';
		} 
		while (index);
		sprintf_s(buffer, "|%1d: ", hardware_index);
		output += buffer;
		
		if (m_activeJobs[hardware_index])
		{
			output += toStringActiveJob(m_activeJobs[hardware_index]);
		}
		else
		{
			output += toStringInactiveJob();
		}

		output += " ";
	}	

	output += "|\n\n";

	return output;
}

const std::string Scheduler::toStringActiveJob(Job* job) const
{
	char active_job[256];
	int index = 256;
	do 
	{
		index--;
		active_job[index] = '\0';
	} 
	while (index);
	sprintf_s(active_job, "%11s", job->toString().c_str());
	
	std::string output(active_job);
	return output;
}

const std::string Scheduler::toStringInactiveJob(void) const
{
	return std::string(" inactive. ");
}
} // namespace concurrency
