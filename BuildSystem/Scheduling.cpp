#include "Scheduling.h"
#include "Synchronization.h"
#include "Threads.h"

#if WIN32
#include "Windows.h"
#endif//WIN32

namespace multithreading
{

/** scheduler singleton */
Mutex*						scheduleGetterMutex(getMutex());	// get synchronization
Scheduler::schedulerGetter	Scheduler::getScheduler(getUninitializedScheduler);
Scheduler*					Scheduler::singleton(NULL);

Scheduler::Scheduler(void)
: m_maxThreads(getNumberSystemThreads())
, m_minThreads(1)
{
	/* empty */
}

void Scheduler::enqueue(Executable* job, sint ideal_thread/* =-1 */)
{
	Thread* thread = new Thread(job);
}

void Scheduler::enqueue(executableFunction job, sint ideal_thread/* =-1 */)
{
	Thread* thread = new Thread(job);
}

Scheduler& Scheduler::getInitializedScheduler(void)
{
	return *singleton;
}

uint Scheduler::getNumberSystemThreads(void) const
{
	uint num_system_threads(1);
#if WIN32
	SYSTEM_INFO windows_info;
	GetSystemInfo(&windows_info);
	num_system_threads = windows_info.dwNumberOfProcessors;
#endif//WIN32
	return num_system_threads;
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
		returnMutex(scheduleGetterMutex);
	
	return *singleton;
}
/*
void Scheduler::notifyFinished(Thread* thread)
{
	delete thread;
	// check the job queue for more work (on this thread)
	// create a new thread and send it to work if it exists
}
*/
Scheduler& Scheduler::single(void)
{
	return (*getScheduler)();
}

} // namespace multithreading