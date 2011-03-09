#pragma once
#ifndef SCHEDULING_H
#define SCHEDULING_H

#include "Build.h"
#include "Observation.h"
#include "Threads.h"

namespace multithreading
{

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
		// Scheduler::single().notifyFinished(this);
	}

	Executor*				m_executor;
	threadID				m_id;
	threadHandle			m_thread;
}; // class Thread



class Scheduler 
{
public:
	static Scheduler& single(void);
	
	void enqueue(Executable* job, sint ideal_thread=-1);
	void enqueue(executableFunction job, sint ideal_thread=-1);
	void getNumberActiveJobs(void);
	void getNumberPendingJobs(void);
	uint getMaxThreads(void) const	{ return m_maxThreads; }
	uint getMinThreads(void) const	{ return m_minThreads; }
	void setMaxThreads(uint max)	{ m_maxThreads = max; }
	void setMinThreads(uint min)	{ m_minThreads = min; }
	
protected:
	uint getNumberSystemThreads(void) const;

private:
	typedef Scheduler& (*schedulerGetter)(void);
	static Scheduler& getInitializedScheduler(void);
	static Scheduler& getUninitializedScheduler(void);
	static Scheduler* singleton;
	static schedulerGetter getScheduler;

	Scheduler(void);
	Scheduler(const Scheduler&);
	Scheduler operator=(const Scheduler&);
	
	uint					m_maxThreads;
	uint					m_minThreads;
}; // class Scheduler

} // multithreading

#endif//SCHEDULING_H