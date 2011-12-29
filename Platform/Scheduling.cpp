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

// #define SCHEDULE_PRINT printState();
#define SCHEDULE_PRINT 


namespace concurrency
{

inline threadID 
getInitializedID(const Thread& thread)
{
	threadID id;
	IF_DEBUG(bool success =) thread.getID(id);
	assert(success);
	return id;
}

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
			id = invalidThreadID; 
		}

		return id;
	}

	void
	reset(Thread* thread)
	{
		if (m_thread)
		{
			m_thread->disconnect(this);
		}

		m_thread = thread;

		if (thread)
		{
			m_thread->connect(this, &Job::onComplete);
		}
	}

	inline void
	onComplete(Thread*)
	{
		Scheduler::single.accountForFinish(this);
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
		if (m_thread)
		{
			m_thread->disconnect(this);
			Thread::destroyThread(*m_thread);
			m_thread = NULL;
		}
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
		if (m_thread)
		{
			Thread::destroyThread(*m_thread);
		}
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
	const bool originalWasWaiting = isOriginalWaitingOnThread(finished->getThreadID(), &originalID);

	if (originalWasWaiting)
	{	
		finished->reset(NULL);
	}
	
	m_pendingJobs->recycleJob(finished);
	
	startJobs();
	SCHEDULE_PRINT
}

void Scheduler::accountForStartedJob(Job* started, cpuID index)
{
	m_activeJobs[index] = started;
	m_numActiveJobs++;
	SCHEDULE_PRINT
}

void Scheduler::accountForWaitedOnThreadCompletion(Thread::Tree* children)
{
	SYNC(m_mutex);
	const threadID originalID = children->getOriginalID();

	{
		Thread::Tree::ThreadIterConst sentinel(children->end());
		for (Thread::Tree::ThreadIterConst iter(children->begin());
			iter != sentinel;
			iter++)
		{
			m_originalByChildren.erase(getInitializedID(*(*iter)));
		}
		
		m_childrenByOriginal.erase(originalID);
	}
}

void Scheduler::enqueue(Executor& executable, cpuID preferredCPU)
{
	SYNC(m_mutex);
	 
	threadID parentID = Thread::getCurrentID();
	std::map<threadID, threadID>::iterator originalIDIter = m_originalByChildren.find(parentID);

	if (originalIDIter != m_originalByChildren.end())
	{	// a parent job is waiting on the end of this one
		threadID originalID = originalIDIter->second;
		std::map<threadID, Thread::Tree*>::iterator threadsIter =
			m_childrenByOriginal.find(originalID);
		assert(threadsIter != m_childrenByOriginal.end());
		
		initializeAndTrackJob(executable, preferredCPU, threadsIter->second);		
	}
	else
	{
		m_pendingJobs->add(executable, preferredCPU, NULL);
	}
	
	startJobs();
}

void Scheduler::enqueueAndWait(Executor& executable, cpuID preferredCPU)
{
	Thread* output(NULL);
	{
		SYNC(m_mutex);
		m_pendingJobs->add(executable, preferredCPU, &output);
		startJobs();
	}
	Thread::waitOnCompletion(*output);
}

void Scheduler::enqueueAndWaitOnChildren(Executor& executable, cpuID preferredCPU)
{	// Thread::Tree* children = new Thread::Tree();
	Thread::Tree children;

	{
		SYNC(m_mutex);
		initializeAndTrackJob(executable, preferredCPU, &children);
		startJobs();
	}

	children.waitOnCompletion();
	accountForWaitedOnThreadCompletion(&children);
	// delete children;
}

void Scheduler::enqueueAndWaitOnChildren(std::queue<Executor*>& work)
{	// Thread::Tree* children = new Thread::Tree();
	Thread::Tree children;
		
	{
		SYNC(m_mutex);
		
		while (!work.empty())
		{
			initializeAndTrackJob(*(work.front()), noCPUpreference, &children);
			work.pop();
		}

		startJobs();
	}

	children.waitOnCompletion();
	accountForWaitedOnThreadCompletion(&children);
	// delete children;
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

void Scheduler::initializeAndTrackJob(Executor& executable,
								   cpuID preferredCPU,
								   Thread::Tree* children)
{
	const threadID originalID = children->getOriginalID();	
	// add the job to the pending queue, to initialize the thread
	Thread* thread(NULL);
	m_pendingJobs->add(executable, preferredCPU, &thread);
	// get the child thread ID
	const threadID childID = getInitializedID(*thread);
	// make sure the current thread isn't already waiting on tree of threads
	assert(m_originalByChildren.find(originalID) == m_originalByChildren.end());
	// map the children to the parent ID
	m_childrenByOriginal[originalID] = children;
	// map the parent ID to the children
	m_originalByChildren[childID] = originalID;	
	// store the thread for deletion	
	children->push(thread);
	// make the original is waiting on the child now
	assert(isOriginalWaitingOnThread(childID));
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
	SYNC(m_mutex);
	printf(toString().c_str());
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
		IF_DEBUG(bool success =) getFreeIndex(required, preferred);
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
	
	sprintf_s(buffer, ""
		"SysThreads: %2d "
		"MaxThreads: %2d "
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
	sprintf_s(buffer, "Pending: %3d", getNumberPendingJobs());
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

	output += "|\n";

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
	return std::string("    inactive.    ");
}
} // namespace concurrency
