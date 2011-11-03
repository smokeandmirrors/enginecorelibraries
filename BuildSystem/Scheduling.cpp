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

namespace multithreading
{
#if WIN32
inline uint getNumHardwareThreads(void)
{
	_SYSTEM_INFO system_info;
	GetSystemInfo(&system_info);
}
#else
	PREVENT_COMPILE
#endif//WIN32

/** a wrapper for a Thread that can be added to the scheduler */
// \todo make this a transmitter or it might be enough to have the member with the scheduler
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

	void
		reset(Thread* thread)
	{
		if (m_thread)
		{
			m_thread->disconnect(this);
			delete m_thread;
		}
		
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
		start(cpuID& requiredCPU) // start(cpuID&, threadHandle& out) for the WaitCalls
	{
		m_thread->execute(requiredCPU);
	}

	const std::string& 
		toString(void) const
	{
		return m_thread 
			? m_thread->toString() 
			: "invalid";
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
		add(Executor& executable, cpuID preferredCPU)
	{
		Job* job = getFreeJob();
		Thread* thread = new Thread(executable, true, preferredCPU);
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

void Scheduler::enqueue(Executor& executable, cpuID preferredCPU)
{
	SYNC(m_mutex);
	m_pendingJobs->add(executable, preferredCPU);
	startJobs();
	printState();
}

uint Scheduler::getMaxThreads(void) const 
{ 
	return m_maxThreads; 
}

uint Scheduler::getNumberActiveJobs(void) const
{
	return m_numActiveJobs;
}

uint Scheduler::getNumberPendingJobs(void) const
{
	SYNC(m_mutex);
	return m_pendingJobs->getNumber();
}

uint Scheduler::getNumberSystemThreads(void) const	
{ 
	return m_numSystemThreads; 
}

bool Scheduler::hasAnyWork(void) const
{
	SYNC(m_mutex);
	return getNumberActiveJobs() || getNumberPendingJobs();
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

void Scheduler::printState(void) const
{
	std::string output = this->toString();
	printf(output.c_str());
}

void Scheduler::setMaxThreads(uint max)			
{ 
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
		accountForStartedJob(job, required);
		job->start(required);
	}
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
	m_pendingJobs->recycleJob(finished);
	printState();
}

void Scheduler::accountForStartedJob(Job* started, cpuID index)
{
	SYNC(m_mutex);
	m_activeJobs[index] = started;
	m_numActiveJobs++;
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

bool Scheduler::isAnyIndexFree(void) const
{
	SYNC(m_mutex);
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

void Scheduler::onComplete(Job* completed)
{
	SYNC(m_mutex);
	accountForFinish(completed);
	startJobs();
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
} // namespace multithreading
