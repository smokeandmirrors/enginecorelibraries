#include "Scheduling.h"
#include "Synchronization.h"
#include "Threads.h"

#if WIN32
#include "Windows.h"
#endif//WIN32

namespace multithreading
{
/** \todo move the thread class to the Threads.h file 
the conditional compilation is fine, and can be moved there 
without moving the win32 stuff */
#if WIN32
#include <process.h>
#include <windows.h>

typedef uint(__stdcall*		threadable)(void*);
typedef uint				threadID;
typedef void*				threadHandle;
#endif//WIN32
/** 
todo, these themselves might have to be hidden behind even smaller classes for
better cross-platform use
*/

inline threadHandle createThread(threadable function, threadID& id, void* args, sint CPUid=-1);
inline void endThread(void);
inline uint GetNumHardwareThreads(void);

#if WIN32
inline threadHandle createThread(threadable function, threadID& id, void* args, sint/* CPUid*/)
{	
	HANDLE newthread = (HANDLE)(_beginthreadex(NULL, 0, function, args, 0, &id));
	/** 
	\todo the last parameter is CPUid, allow for setting the processor affinity on a per
	platform basis
	DWORD result = SetThreadIdealProcessor(newthread, CPUid);
	*/
	return newthread;
}

inline void endThread(void)
{
	uint status(0);
	_endthreadex(status);
}

inline uint GetNumHardwareThreads(void)
{
	_SYSTEM_INFO system_info;
	GetSystemInfo(&system_info);
}
#endif//WIN32

/** 
should be an observer or something, there needs to be a way
of notifying the thread of the Executable's destruction 
*/
class Thread
{
#if WIN32
	static uint __stdcall executeThread(void* pThread)
	{
		static_cast<Thread*>(pThread)->execute();
		return 0;
	}
#endif//WIN32

	class Executor
	{
	public:
		virtual void execute(void)=0;
		void initialize(Thread* thread, threadHandle& handle, threadID& id, sint CPUid)
		{
			handle = multithreading::createThread(Thread::executeThread, id, thread, CPUid);
		}
	}; // class Executor

	class ExecutableExecutor : public Executor
	{
	public:
		ExecutableExecutor(Executable* object) 
		: m_object(object) 
		{ 
			/* empty */ 
		}

		void execute(void)
		{
			m_object->execute();
		}					

	private:	
		Executable*	m_object;
	}; // class ExecutableExecutor : public Executor

	class FunctionExecutor : public Executor
	{
	public:		
		FunctionExecutor(executableFunction function) 
		: m_function(function) 
		{ 
			/* empty */ 
		}

		void execute(void)
		{
			(*m_function)();
		}		

	private:
		executableFunction m_function;
	}; // class FunctionExecutor : public Executor

	friend class FunctionExecutor;
	friend class Executor;
	friend class ExecutableExecutor;

public:
	Thread(Executable* executable, sint CPUid=-1) 
	: m_executor(new Thread::ExecutableExecutor(executable))
	{ 
		initialize(CPUid);
	}
	
	Thread(executableFunction executable, sint CPUid=-1)
	: m_executor(new Thread::FunctionExecutor(executable))
	{ 
		initialize(CPUid);
	}
	
	~Thread(void)
	{	
		CloseHandle(m_thread);
		delete m_executor;
	}

private:
	/** not allowed */
	Thread(const Thread&);
	Thread(void);
	
	void execute(void)
	{
		m_executor->execute();
		notifyTerminated();
	}

	void initialize(sint CPUid)
	{
		assert(m_executor);
		m_executor->initialize(this, m_thread, m_id, CPUid);
	}

	void notifyTerminated(void)
	{
		// tell [the scheduler], observers that the functionality
		// executed by the this thread is complete
	}

	Executor*				m_executor;
	threadID				m_id;
	threadHandle			m_thread;
}; // class Thread

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

Scheduler& Scheduler::single(void)
{
	return (*getScheduler)();
}


} // namespace multithreading