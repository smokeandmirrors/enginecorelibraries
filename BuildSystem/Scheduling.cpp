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
inline uint getNumHardwareThreads(void)
{
	_SYSTEM_INFO system_info;
	GetSystemInfo(&system_info);
}
#endif//WIN32

/** scheduler singleton */
Mutex*						scheduleGetterMutex(getMutex());	// get synchronization
Scheduler::schedulerGetter	Scheduler::getScheduler(getUninitializedScheduler);
Scheduler*					Scheduler::singleton(NULL);

class PendingJobQueue
{
	class PendingJob 
	{
	public:
		virtual ~PendingJob(void) {}
		
		virtual sint getIdealThread(void) const
		{
			return m_idealThread;
		}

		virtual Thread* newThread(Scheduler* scheduler, sint CPUid)=0;
		virtual void	recycle(PendingJobQueue& queue)=0;
	
	protected:
		sint		m_idealThread;
	}; // PendingJob 

	class PendingObject : public PendingJob
	{
	public:
		virtual Thread* newThread(Scheduler* scheduler, sint CPUid)
		{
			return new Thread(m_job, CPUid, scheduler);
		}

		virtual void recycle(PendingJobQueue& queue)
		{
			queue.m_objectPool.push_back(this);
		}

		inline void reset(Executable* job=NULL, sint ideal_thread=noThreadPreference)
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
		virtual Thread* newThread(Scheduler* scheduler, sint CPUid)
		{
			return new Thread(m_job, CPUid, scheduler);
		}

		virtual void recycle(PendingJobQueue& queue)
		{
			queue.m_functionPool.push_back(this);
		}

		inline void reset(executableFunction job=NULL, sint ideal_thread=noThreadPreference)
		{
			m_job = job;
			m_idealThread = ideal_thread;
		}

	private:
		executableFunction	m_job;
	}; // PendingFunction

public:
	inline void add(Executable* job, sint ideal_thread=noThreadPreference)
	{
		m_pendingJobs.push_back(getFreeJob(job, ideal_thread));
	}
	
	inline void add(executableFunction job, sint ideal_thread=noThreadPreference)
	{
		m_pendingJobs.push_back(getFreeJob(job, ideal_thread));
	}

	inline bool getNextIdealThread(sint& ideal_thread) const
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

	inline uint getNumberPendingJobs(void) const
	{
		return static_cast<uint>(m_pendingJobs.size());
	}

	inline Thread* startNextJob(Scheduler* scheduler, sint CPUid)
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

	inline PendingJob* getFreeJob(Executable* job, sint ideal_thread)
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

	inline PendingJob* getFreeJob(executableFunction job, sint ideal_thread)
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
	
	for (uint i = 0; i < m_numSystemThreads; i++)
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

void Scheduler::destroy(void)
{
	bool return_mutex(false);

	{
		synchronize(scheduleGetterMutex);

		if (singleton)
		{
			delete singleton;
			singleton = NULL;
			getScheduler = getUninitializedScheduler;
			return_mutex = true;
		}
	}

	if (return_mutex)
	{
		returnMutex(scheduleGetterMutex);
	}
}

void Scheduler::enqueue(Executable* job, sint ideal_thread/* =noThreadPreference */)
{
	sint index;

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

void Scheduler::enqueue(executableFunction job, sint ideal_thread/* =noThreadPreference */)
{
	sint index;

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

Scheduler& Scheduler::getInitializedScheduler(void)
{
	return *singleton;
}

Scheduler& Scheduler::getUninitializedScheduler(void)
{
	bool return_mutex(false);
	
	{
		synchronize(scheduleGetterMutex);
	
		if (!singleton)
		{
			singleton = new Scheduler();
			getScheduler = getInitializedScheduler;
			return_mutex = true;
		}
	}

	if (return_mutex)
	{
		returnMutex(scheduleGetterMutex);
	}

	return *singleton;
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

Scheduler& Scheduler::single(void)
{
	return (*getScheduler)();
}

void Scheduler::startNextJob(void)
{
	if (m_pendingJobs->getNumberPendingJobs())
	{
		sint thread_index;
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