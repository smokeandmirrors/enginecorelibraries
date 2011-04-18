#include <list>
#include <string>
#include <vector>
#if WIN32
#include <process.h>
#include <windows.h>
#endif//WIN32

#include "Scheduling.h"
#include "Synchronization.h"
#include "Thread.h"

namespace multithreading
{
#if WIN32
inline uint4 getNumHardwareThreads(void)
{
	_SYSTEM_INFO system_info;
	GetSystemInfo(&system_info);
}
#else
	PREVENT_COMPILE
#endif//WIN32

class PendingJobQueue
{
	class PendingJob 
	{
	public:
		sint4 getIdealThread(void) const
		{
			return m_idealThread;
		}

		virtual Thread* newThread(Scheduler* scheduler, sint4 CPUid)=0;
		virtual void	recycle(PendingJobQueue& queue)=0;
	
		const std::string toString(void) const
		{
			return m_name;
		}
	
	protected:
		sint4			m_idealThread;
		std::string		m_name;
	}; // PendingJob 

	class PendingObject : public PendingJob
	{
	public:
		virtual Thread* newThread(Scheduler* scheduler, sint4 CPUid)
		{
			return new Thread(m_job, CPUid, scheduler, &Scheduler::onComplete, m_name.c_str());
		}

		virtual void recycle(PendingJobQueue& queue)
		{
			queue.m_objectPool.push_back(this);
		}

		inline void reset(Executable* job=NULL, 
			sint4 ideal_thread=noThreadPreference, 
			const sint1* name="un-named")
		{
			m_idealThread = ideal_thread;
			m_job = job;
			m_name = name;
		}

	private:
		Executable*	m_job;
	}; // PendingObject

	class PendingFunction : public PendingJob
	{
	public:
		virtual Thread* newThread(Scheduler* scheduler, sint4 CPUid)
		{
			return new Thread(m_job, CPUid, scheduler, &Scheduler::onComplete, m_name.c_str());
		}

		virtual void recycle(PendingJobQueue& queue)
		{
			queue.m_functionPool.push_back(this);
		}

		inline void reset(executableFunction job=NULL, 
			sint4 ideal_thread=noThreadPreference, 
			const sint1* name="un-named")
		{
			m_job = job;
			m_idealThread = ideal_thread;
			m_name = name;
		}

	private:
		executableFunction	m_job;
	}; // PendingFunction

public:
	inline void add(Executable* job, 
		sint4 ideal_thread=noThreadPreference, 
		const sint1* name="un-named")
	{
		m_pendingJobs.push_back(getFreeJob(job, ideal_thread, name));
	}
	
	inline void add(executableFunction job, 
		sint4 ideal_thread=noThreadPreference, 
		const sint1* name="un-named")
	{
		m_pendingJobs.push_back(getFreeJob(job, ideal_thread, name));
	}

	inline bool getNextIdealThread(sint4& ideal_thread) const
	{
		if (getNumber())
		{
			PendingJob* next_job = m_pendingJobs.front();
			ideal_thread = next_job->getIdealThread();
			return true;
		}
		else
		{
			return false;
		}	
	}

	inline uint4 getNumber(void) const
	{
		return static_cast<uint4>(m_pendingJobs.size());
	}

	inline Thread* startNextJob(Scheduler* scheduler, sint4 CPUid)
	{
		if (getNumber())
		{
			PendingJob* next_job = m_pendingJobs.front();
			m_pendingJobs.pop_front();
			Thread* thread = next_job->newThread(scheduler, CPUid);
			recycleJob(next_job);
			return thread;
		}
		else
		{
			return NULL;
		}
	}
	
protected:
	inline void recycleJob(PendingJob* pending)
	{
		pending->recycle(*this);
	}

	inline PendingJob* getFreeJob(Executable* job, 
		sint4 ideal_thread, 
		const sint1* name="un-named")
	{
		PendingObject* object;
		
		if (m_objectPool.empty())
		{
			object = new PendingObject();
		}
		else
		{
			object = m_objectPool.back();
			m_objectPool.pop_back();
		}

		object->reset(job, ideal_thread, name);
		return object;
	}

	inline PendingJob* getFreeJob(executableFunction job, 
		sint4 ideal_thread, 
		const sint1* name="un-named")
	{
		PendingFunction* object;

		if (m_functionPool.empty())
		{
			object = new PendingFunction();
		}
		else
		{
			object = m_functionPool.back();
			m_functionPool.pop_back();
		}

		object->reset(job, ideal_thread, name);
		return object;
	}

private:
	friend class PendingJob;
	friend class PendingFunction;
	friend class PendingObject;

	std::list<PendingJob*>			m_pendingJobs;
	std::vector<PendingFunction*>	m_functionPool;
	std::vector<PendingObject*>		m_objectPool;
}; // class PendingJobQueue 

Scheduler::Scheduler(void)
: m_numActiveJobs(0)
{
	m_receiver.setReceiver(this);
	initializeNumberSystemThreads();
	m_maxThreads = getNumberSystemThreads();
	m_activeJobs = new Thread*[m_numSystemThreads];
	
	for (uint4 i = 0; i < m_numSystemThreads; i++)
	{
		m_activeJobs[i] = NULL;
	}

	m_pendingJobs = new PendingJobQueue();
}

Scheduler::~Scheduler(void)
{
	delete m_pendingJobs;
	delete[] m_activeJobs;
}

void Scheduler::enqueue(Executable* job, 
	sint4 ideal_thread/* =noThreadPreference */, 
	const sint1* name/* ="un-named" */)
{
	SYNC(m_mutex);
	sint4 index;

	if (getOpenThread(index, ideal_thread))
	{
		Thread* thread = new Thread(job, index, this, &Scheduler::onComplete, name);
		accountForNewJob(thread, index);
	}
	else
	{
		m_pendingJobs->add(job, ideal_thread, name);
		printState();
	}
}

void Scheduler::enqueue(executableFunction job, 
	sint4 ideal_thread/* =noThreadPreference */, 
	const sint1* name/* ="un-named" */)
{
	SYNC(m_mutex);
	sint4 index;

	if (getOpenThread(index, ideal_thread))
	{
		Thread* thread = new Thread(job, index, this, &Scheduler::onComplete, name);
		accountForNewJob(thread, index);
	}
	else
	{
		m_pendingJobs->add(job, ideal_thread, name);
		printState();
	}
}

uint4 Scheduler::getNumberPendingJobs(void) const
{
	SYNC(m_mutex);
	return m_pendingJobs->getNumber();
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

void Scheduler::startNextJob(void)
{
	SYNC(m_mutex);
		
	if (getNumberPendingJobs())
	{
		sint4 thread_index;
		m_pendingJobs->getNextIdealThread(thread_index);
			
		if (thread_index == -1)
		{
			bool free_thread = getFreeIndex(thread_index);
			assert(free_thread);
		}

		Thread* thread = m_pendingJobs->startNextJob(this, thread_index);
		assert(thread);
		accountForNewJob(thread, thread_index);
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

	for (uint4 hardware_index = 0; hardware_index < getNumberSystemThreads(); hardware_index++)
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

const std::string Scheduler::toStringActiveJob(Thread* job) const
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