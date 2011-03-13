#include <list>
#include <vector>
#if WIN32
#include <process.h>
#include <windows.h>
#endif//WIN32

#include "Observation.h"
#include "Scheduling.h"
#include "Synchronization.h"
#include "Threads.h"

namespace multithreading
{

#if WIN32
inline uint4 getNumHardwareThreads(void)
{
	_SYSTEM_INFO system_info;
	GetSystemInfo(&system_info);
}
#endif//WIN32

class PendingJobQueue
{
	class PendingJob 
	{
	public:
		virtual ~PendingJob(void) {}
		
		virtual sint4 getIdealThread(void) const
		{
			return m_idealThread;
		}

		virtual Thread* newThread(Scheduler* scheduler, sint4 CPUid)=0;
		virtual void	recycle(PendingJobQueue& queue)=0;
	
	protected:
		sint4		m_idealThread;
	}; // PendingJob 

	class PendingObject : public PendingJob
	{
	public:
		virtual Thread* newThread(Scheduler* scheduler, sint4 CPUid)
		{
			return new Thread(m_job, CPUid, scheduler);
		}

		virtual void recycle(PendingJobQueue& queue)
		{
			queue.m_objectPool.push_back(this);
		}

		inline void reset(Executable* job=NULL, sint4 ideal_thread=noThreadPreference)
		{
			m_job = job;
			m_idealThread = ideal_thread;
		}

	private:
		Executable*	m_job;
	}; // PendingObject

	class PendingFunction : public PendingJob
	{
	public:
		virtual Thread* newThread(Scheduler* scheduler, sint4 CPUid)
		{
			return new Thread(m_job, CPUid, scheduler);
		}

		virtual void recycle(PendingJobQueue& queue)
		{
			queue.m_functionPool.push_back(this);
		}

		inline void reset(executableFunction job=NULL, sint4 ideal_thread=noThreadPreference)
		{
			m_job = job;
			m_idealThread = ideal_thread;
		}

	private:
		executableFunction	m_job;
	}; // PendingFunction

public:
	inline void add(Executable* job, sint4 ideal_thread=noThreadPreference)
	{
		m_pendingJobs.push_back(getFreeJob(job, ideal_thread));
	}
	
	inline void add(executableFunction job, sint4 ideal_thread=noThreadPreference)
	{
		m_pendingJobs.push_back(getFreeJob(job, ideal_thread));
	}

	inline bool getNextIdealThread(sint4& ideal_thread) const
	{
		if (getNumberPendingJobs())
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

	inline uint4 getNumberPendingJobs(void) const
	{
		return static_cast<uint4>(m_pendingJobs.size());
	}

	inline Thread* startNextJob(Scheduler* scheduler, sint4 CPUid)
	{
		if (getNumberPendingJobs())
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

	inline PendingJob* getFreeJob(Executable* job, sint4 ideal_thread)
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

		object->reset(job, ideal_thread);
		return object;
	}

	inline PendingJob* getFreeJob(executableFunction job, sint4 ideal_thread)
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

		object->reset(job, ideal_thread);
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
: m_maxThreads(getNumberSystemThreads())
, m_minThreads(1)
, m_numActiveJobs(0)
{
	initializeNumberSystemThreads();
	m_observer = new design_patterns::ObserverHelper<Thread>(*this);
	m_activeJobs = new Thread*[m_numSystemThreads];
	
	for (uint4 i = 0; i < m_numSystemThreads; i++)
	{
		m_activeJobs[i] = NULL;
	}

	m_pendingJobs = new PendingJobQueue();
}

Scheduler::~Scheduler(void)
{
	delete m_observer;
	delete m_pendingJobs;
	delete[] m_activeJobs;
}

void Scheduler::enqueue(Executable* job, sint4 ideal_thread/* =noThreadPreference */)
{
	sint4 index;

	if (getOpenThread(index, ideal_thread))
	{
		Thread* thread = new Thread(job, index, this);
		accountForNewJob(thread, index);
	}
	else
	{
		m_pendingJobs->add(job, ideal_thread);
	}
}

void Scheduler::enqueue(executableFunction job, sint4 ideal_thread/* =noThreadPreference */)
{
	sint4 index;

	if (getOpenThread(index, ideal_thread))
	{
		Thread* thread = new Thread(job, index, this);
		accountForNewJob(thread, index);
	}
	else
	{
		m_pendingJobs->add(job, ideal_thread);
	}
}

void Scheduler::initializeNumberSystemThreads(void)
{
#if WIN32
	SYSTEM_INFO windows_info;
	GetSystemInfo(&windows_info);
	m_numSystemThreads = windows_info.dwNumberOfProcessors;
#elif 
	m_numSystemThreads = 1;
#endif//WIN32
}

void Scheduler::startNextJob(void)
{
	if (m_pendingJobs->getNumberPendingJobs())
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

} // namespace multithreading