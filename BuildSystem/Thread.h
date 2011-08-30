#pragma once
#ifndef THREADS_H
#define THREADS_H

#include "Build.h"
#include "Multithreading.h"
#include "Signals.h"

/**
<DEVELOPMENT STATUS>
Current Draft		:	0.0
Current Phase		:   DEVELOPMENT
Purpose				:	DEPLOYMENT
Unit Tested			:	NO
Used in development	:	NO
Used in experiments :	YES
Tested in the field	:	NO
*/
namespace multithreading
{

#if WIN32
typedef uint(__stdcall*	threadable)(void*);
typedef uint				threadID;
typedef void*				threadHandle;
#else
	PREVENT_COMPILE
#endif//WIN32
		
class Thread
{
public:
	/** \todo make thread pool, static borrow/recycle, private constructors, destructors, etc */
	template<class RECEIVER>
	Thread(executableFunction executable, 
		sint CPUid=noThreadPreference, 
		RECEIVER* receiver=NULL, 
		void (RECEIVER::* function)(Thread*) const=NULL,
		const schar* name="un-named")
	: m_executor(new Thread::FunctionExecutor(executable))
	, m_name(name)
	{ 
		initialize(CPUid, receiver, function);
	}

	template<class RECEIVER>
	Thread(Executable* executable, 
		sint CPUid=noThreadPreference, 
		RECEIVER* receiver=NULL, 
		void (RECEIVER::* function)(Thread*) const=NULL,
		const schar* name="un-named")
	: m_executor(new Thread::ExecutableExecutor(executable))
	, m_name(name)
	{ 
		initialize(CPUid, receiver, function);
	}

	template<class RECEIVER>
	Thread(Executable* executable, 
		sint CPUid=noThreadPreference, 
		RECEIVER* receiver=NULL, 
		void (RECEIVER::* function)(Thread*)=NULL,
		const schar* name="un-named") 
	: m_executor(new Thread::ExecutableExecutor(executable))
	, m_name(name)
	{ 
		initialize(CPUid, receiver, function);
	}

	template<class RECEIVER>
	Thread(executableFunction executable, 
		sint CPUid=noThreadPreference, 
		RECEIVER* receiver=NULL, 
		void (RECEIVER::* function)(Thread*)=NULL,
		const schar* name="un-named") 
	: m_executor(new Thread::FunctionExecutor(executable))
	, m_name(name)
	{ 
		initialize(CPUid, receiver, function);
	}

	virtual ~Thread(void);

	template<class RECEIVER>
	void connect(RECEIVER* receiver, void (RECEIVER::* function)(Thread*))
	{
		m_onComplete.connect(receiver, function);
	}

	template<class RECEIVER>
	void connect(RECEIVER* receiver, void (RECEIVER::* function)(Thread*) const)
	{
		m_onComplete.connect(receiver, function);
	}

	void disconnect(signals::Receiver* receiver)
	{
		m_onComplete.disconnect(receiver);
	}

	const std::string toString(void) const 
	{ 
		return m_name; 
	} 

private:
#if WIN32
	static uint __stdcall executeThread(void* pThread)
	{
		static_cast<Thread*>(pThread)->execute();
		return 0;
	}
#else
	PREVENT_COMPILE
#endif//WIN32

	class Executor
	{
	public:
		virtual void execute(void)=0;
		void initialize(Thread* thread, threadHandle& handle, threadID& id, sint CPUid);
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
		m_onComplete(this);
		delete this;
	}

	template<class RECEIVER>
	void initialize(sint CPUid, RECEIVER* receiver, void (RECEIVER::* function)(Thread*))
	{
		assert(m_executor);
		m_onComplete.connect(receiver, function);
		m_executor->initialize(this, m_thread, m_id, CPUid);
	}
	
	template<class RECEIVER>
	void initialize(sint CPUid, RECEIVER* receiver, void (RECEIVER::* function)(Thread*) const)
	{
		assert(m_executor);
		m_onComplete.connect(receiver, function);
		m_executor->initialize(this, m_thread, m_id, CPUid);
	}

	Executor*			
		m_executor;
	
	threadID
		m_id;
	
	std::string
		m_name;
	
	signals::Transmitter1<Thread*> 
		m_onComplete;
	
	threadHandle		
		m_thread;
};

} // multithreading

#endif//THREADS_H