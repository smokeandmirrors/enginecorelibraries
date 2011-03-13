#pragma once
#ifndef THREADS_H
#define THREADS_H

#include "Build.h"
#include "Observation.h"

namespace multithreading
{
#if WIN32
#define ARGS_EXECUTABLE_FUNCTION(name) uint4 __stdcall name(void* args)
#define NOARGS_EXECUTABLE_FUNCTION(name) uint4 __stdcall name(void*)
#endif// WIN32

#define DECLARE_NOARGS_EXECUTABLE_FUNCTION(name) NOARGS_EXECUTABLE_FUNCTION(name);
#define DEFINE_NOARGS_EXECUTABLE_FUNCTION(name, code) NOARGS_EXECUTABLE_FUNCTION(name) \
	{ \
		code \
		return 0; \
	}

#define DECLARE_ARGS_EXECUTABLE_FUNCTION(name) ARGS_EXECUTABLE_FUNCTION(name);
#define DEFINE_ARGS_EXECUTABLE_FUNCTION(name, code) ARGS_EXECUTABLE_FUNCTION(name) \
	{ \
		code \
		return 0; \
	}

typedef void(* executableFunction)(void);

class Executable 
{
public:
	virtual	~Executable(void) {/* empty */}
	virtual void execute(void)=0;
}; // class Executable

#if WIN32
typedef uint4(__stdcall*		threadable)(void*);
typedef uint4				threadID;
typedef void*				threadHandle;
#endif//WIN32

static sint4 noThreadPreference(-1);

class Thread
: public design_patterns::Observable<Thread>
{
public:
	/** \todo make thread pool, static borrow/recycle, private constructors, destructors, etc */
	Thread(Executable* executable, 
		sint4 CPUid=noThreadPreference, 
		design_patterns::Observer<Thread>* observer=NULL) 
	: m_executor(new Thread::ExecutableExecutor(executable))
	{ 
		initialize(CPUid, observer);
	}

	Thread(executableFunction executable, 
		sint4 CPUid=noThreadPreference, 
		design_patterns::Observer<Thread>* observer=NULL)
	: m_executor(new Thread::FunctionExecutor(executable))
	{ 
		initialize(CPUid, observer);
	}

	~Thread(void);

	void add(design_patterns::Observer<Thread>* observer)
	{
		m_observable->add(observer);
	}
	
	void remove(design_patterns::Observer<Thread>* observer)
	{
		m_observable->remove(observer);
	}
	
	void notify(void)
	{
		m_observable->notify();
	}

private:
#if WIN32
	static uint4 __stdcall executeThread(void* pThread)
	{
		static_cast<Thread*>(pThread)->execute();
		return 0;
	}
#endif//WIN32

	class Executor
	{
	public:
		virtual void execute(void)=0;
		void initialize(Thread* thread, threadHandle& handle, threadID& id, sint4 CPUid);
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

	/** not allowed */
	Thread(const Thread&);
	Thread(void);

	void execute(void)
	{
		m_executor->execute();
		m_observable->notify();
		delete this;
	}

	void initialize(sint4 CPUid, design_patterns::Observer<Thread>* observer)
	{
		assert(m_executor);
		m_observable = new design_patterns::ObservableHelper<Thread>(*this);

		if (observer)
		{
			add(observer);
		}

		m_executor->initialize(this, m_thread, m_id, CPUid);
	}

	Executor*			m_executor;
	threadID			m_id;
	design_patterns::ObservableHelper<Thread>*	
						m_observable;
	threadHandle		m_thread;
};

} // multithreading

#endif//THREADS_H