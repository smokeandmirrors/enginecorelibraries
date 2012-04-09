#include <list>
#include <string>
#include <vector>
#include <queue>
#if WIN32
#include <process.h>
#include <windows.h>
#endif//WIN32

#include "Dispatcher.h"
#include "Signals.h"
#include "Synchronization.h"
#include "Thread.h"

using namespace signals;

// #define SCHEDULE_PRINT printState();
#define SCHEDULE_PRINT 
// 
// namespace designPatterns
// {
// 	template<> concurrency::Dispatcher* Singleton<concurrency::Dispatcher>::single(NULL);
// 	static CustomSingletonInitializer<concurrency::Dispatcher> dispatcherInitializer;
// } // namespace designPatterns

DEFINE_SINGLETON_NS(Dispatcher, concurrency)

namespace concurrency
{
	
inline threadID getInitializedID(const Thread& thread)
{
	threadID id;
	IF_DEBUG(bool success =) thread.getID(id);
	assert(success);
	return id;
}

#if WIN32
inline uint getNumHardwareThreads(void)
{
	_SYSTEM_INFO system_info;
	GetSystemInfo(&system_info);
}
#else
	#error unsupported concurrency platform
#endif//WIN32

/** a wrapper for a Thread that can be added to the scheduler */
class Dispatcher::Job : public Receiver
{	
public:
	class Compare
	{
	public:
		bool operator()(const Job* left, const Job* right) const
		{
			return left->getPriority() < right->getPriority();
		}
	}; // PriorityCompare 

	void ceaseReception(void)
	{
		m_receiver.ceaseReception();
	}

	inline SchedulePriority getPriority(void) const
	{
		return m_priority;
	}

	cpuID getPreferredCPU(void) const
	{
		return m_thread->getPreferredCPU();
	}

	threadID getThreadID(void) const
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

	void reset(Thread* newThread, SchedulePriority newPriority)
	{
		if (m_thread)
		{
			m_thread->disconnect(this);
			m_thread->removeReference();
		}

		m_thread = newThread;

		if (m_thread)
		{
			m_thread->connect(this, &Job::onComplete);
			m_thread->addReference();
			m_priority = newPriority;
		}		
	}

	inline void onComplete(Thread*)
	{
		Dispatcher::single->accountForFinish(this);
	}

	inline void onConnect(Transmitter* transmitter)
	{
		m_receiver.onConnect(transmitter);
	}

	inline void onDisconnect(Transmitter* transmitter)
	{
		m_receiver.onDisconnect(transmitter);
	}

	inline void onRecycle(void)
	{
		if (m_thread)
		{
			m_thread->disconnect(this);
			m_thread->removeReference();
			m_thread = NULL;
		}
	}

	inline void start(cpuID& requiredCPU) 
	{
		m_thread->execute(requiredCPU);
	}

	const std::string& toString(void) const
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
			m_thread->removeReference();
		}
	}

	signals::ReceiverMember	m_receiver;
	Thread* m_thread;
	SchedulePriority m_priority;
}; // Job 


class Dispatcher::PendingJobQueue
{
public:
	inline void
		add(Dispatcher::Input& work, Thread** waitable)
	{
		Job* job = getFreeJob();
		Thread* thread; 
		
		if (waitable)
		{
			thread = Thread::getSuspended(*work.executable, work.preferredCPU);
			*waitable = thread;
		}
		else
		{
			thread = Thread::getUninitialized(*work.executable, work.preferredCPU);
		}
		
		job->reset(thread, work.priority);
		m_pendingJobs.push(job);
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
			return m_pendingJobs.top()->getPreferredCPU();
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
			Job* nextJob = m_pendingJobs.top();
			m_pendingJobs.pop();
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
	std::priority_queue<Job*, std::vector<Job*>, Job::Compare> 
		m_pendingJobs;

	std::vector<Job*>
		m_jobPool;
}; // class PendingJobQueue 

Dispatcher::Dispatcher(void)
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

Dispatcher::~Dispatcher(void)
{
	delete m_pendingJobs;
}

void Dispatcher::accountForFinish(Job* finished)
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
		finished->reset(NULL, 0);
	}
	
	m_pendingJobs->recycleJob(finished);
	
	startJobs();
	SCHEDULE_PRINT
}

void Dispatcher::accountForStartedJob(Job* started, cpuID index)
{
	m_activeJobs[index] = started;
	m_numActiveJobs++;
	SCHEDULE_PRINT
}

void Dispatcher::accountForWaitedOnThreadCompletion(Thread::Tree* children)
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

void Dispatcher::enqueue(Dispatcher::Input& work)
{
	InputQueue shortcut;
	shortcut.push_back(work);
	enqueue(shortcut);
}

void Dispatcher::enqueue(Dispatcher::InputQueue& work)
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
		Thread::Tree* tree = threadsIter->second;
		InputQueueIterator sentinel(work.end());
		
		for (InputQueueIterator iter(work.begin()); iter != sentinel; ++iter)
		{
			initializeAndTrackJob(*iter, tree);
		}
	}
	else
	{
		InputQueueIterator sentinel(work.end());
		
		for (InputQueueIterator iter(work.begin()); iter != sentinel; ++iter)
		{
			m_pendingJobs->add(*iter, NULL);
		}
		
	}

	startJobs();
}

void Dispatcher::enqueueAndWait(Dispatcher::Input& work)
{
	InputQueue shortcut;
	shortcut.push_back(work);
	enqueueAndWait(shortcut);
}

void Dispatcher::enqueueAndWait(Dispatcher::InputQueue& work)
{
	Thread::Tree tree;
	
	{
		SYNC(m_mutex);
		InputQueueIterator sentinel(work.end());
		
		for (InputQueueIterator iter(work.begin()); iter != sentinel; ++iter)
		{
			Thread* output(NULL);
			m_pendingJobs->add(*iter, &output);
			tree.push(output);
		}

		startJobs();
	}
	
	Thread::waitOnCompletion(tree);
}

void Dispatcher::enqueueAndWaitOnChildren(Dispatcher::Input& work)
{
	InputQueue shortcut;
	shortcut.push_back(work);
	enqueueAndWaitOnChildren(shortcut);
}

void Dispatcher::enqueueAndWaitOnChildren(Dispatcher::InputQueue& work)
{	
	Thread::Tree children; // Thread::Tree* children = new Thread::Tree();

	{
		SYNC(m_mutex);
		InputQueueIterator sentinel(work.end());
		
		for (InputQueueIterator iter(work.begin()); iter != sentinel; ++iter)
		{
			initializeAndTrackJob(*iter, &children);
		}

		startJobs();
	}

	Thread::waitOnCompletionOfChildren(children);
	accountForWaitedOnThreadCompletion(&children); // delete children;	
}

bool Dispatcher::getFreeIndex(cpuID& index)
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

bool Dispatcher::getFreeIndex(cpuID& available, cpuID idealCPU)
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

uint Dispatcher::getMaxThreads(void) const 
{ 
	SYNC(m_mutex);
	return m_maxThreads; 
}

uint Dispatcher::getNumberActiveJobs(void) const
{
	SYNC(m_mutex);
	return m_numActiveJobs;
}

uint Dispatcher::getNumberPendingJobs(void) const
{
	SYNC(m_mutex);
	return m_pendingJobs->getNumber();
}

uint Dispatcher::getNumberSystemThreads(void) const	
{ 
	SYNC(m_mutex);
	return m_numSystemThreads; 
}

void Dispatcher::initializeAndTrackJob(Dispatcher::Input& work, Thread::Tree* children)
{
	const threadID originalID = children->getOriginalID();	
	// add the job to the pending queue, to initialize the thread
	Thread* thread(NULL);
	m_pendingJobs->add(work, &thread);
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

void Dispatcher::initializeNumberSystemThreads(void)
{
#if WIN32
	SYSTEM_INFO windows_info;
	GetSystemInfo(&windows_info);
	m_numSystemThreads = windows_info.dwNumberOfProcessors;
#else
	#error unsupported concurrency platform
#endif//WIN32
}

bool Dispatcher::isAnyIndexFree(void) const
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

bool Dispatcher::isAnyJobPending(void) const
{
	return m_pendingJobs->getNumber() != 0;
}

bool Dispatcher::isOriginalWaitingOnThread(threadID childID, threadID* originalID) const
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


void Dispatcher::printState(void) const
{
	SYNC(m_mutex);
	printf(toString().c_str());
}

void Dispatcher::setMaxThreads(uint max)			
{ 
	SYNC(m_mutex);
	m_maxThreads = max; 
}

void Dispatcher::startJobs(void)
{
	SYNC(m_mutex);
	while (isAnyJobPending() && isAnyIndexFree())
	{
		cpuID preferred(m_pendingJobs->getNextPreferredCPU());
		cpuID required;
		IF_DEBUG(bool success =)getFreeIndex(required, preferred);
		assert(success);
		Job* job = m_pendingJobs->getNextJob();
		job->start(required);
		accountForStartedJob(job, required);
	}
}

const std::string Dispatcher::toString(void) const
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

const std::string Dispatcher::toStringActiveJob(Job* job) const
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

const std::string Dispatcher::toStringInactiveJob(void) const
{
	return std::string("    inactive.    ");
}
} // namespace concurrency
