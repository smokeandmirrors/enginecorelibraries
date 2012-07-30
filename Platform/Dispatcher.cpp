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

	inline ExecutionPriority getPriority(void) const
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

	void reset(Thread* newThread, ExecutionPriority newPriority)
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
		Dispatcher::single().accountForFinish(this);
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
	ExecutionPriority m_priority;
}; // Job 


class Dispatcher::PendingJobQueue
{
public:
	inline void
		add(Thread::ExecutableInput& work)
	{
		Job* job = getFreeJob();
		Thread* thread = Thread::createSuspended(*work.executable, work.preferredCPU);
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
	
	if (Thread::isWaitedOn(finished->getThreadID()))
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

void Dispatcher::addAndStartJobs(Thread::ExecutableQueue& work)
{
	SYNC(m_mutex);

	for (Thread::ExecutableQueue::ExecutableQueueIter iter(work.inputQueue.begin()), sentinel(work.inputQueue.end()); 
		iter != sentinel; 
		++iter)
	{
		m_pendingJobs->add(*iter);
	}

	startJobs();
}

void Dispatcher::enqueue(Thread::ExecutableQueue& work)
{
	addAndStartJobs(work);
}

void Dispatcher::enqueueAndWait(Thread::ExecutableQueue& work)
{
	Thread::Sleeper sleeper(false);
	addAndStartJobs(work);
}

void Dispatcher::enqueueAndWaitOnChildren(Thread::ExecutableQueue& work)
{	
	Thread::Sleeper sleeper(true);
	addAndStartJobs(work);
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