#pragma once
#ifndef THREADS_H
#define THREADS_H

#include <string>
#include <vector>

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
typedef uint(__stdcall*		threadable)(void*);
typedef uint				threadID;
typedef void*				threadHandle;
#else
	PREVENT_COMPILE
#endif//WIN32
	
/** 
	\todo make thread pool, static borrow/recycle, private constructors, destructors, answer questions about state?
	\todo make all public functionality static? 
	\todo static borrow/recycle with waitable
*/
class Thread
{
public:
	// for the normal user
	static Thread* 
		getExecuting(Executor& executable, cpuID preferredCPU=noCPUpreference);
	// for the user/scheduler to wait on it
	static Thread* 
		getSuspended(Executor& executable, cpuID preferredCPU=noCPUpreference);
	// for the daring user, for the scheduler to get the preferred CPU
	static Thread* 
		getUninitialized(Executor& executable, cpuID preferredCPU=noCPUpreference); 

	static void
		waitOnCompletion(Thread& thread);

	static void
		waitOnCompletion(std::vector<Thread*>& threads);

	virtual 
		~Thread(void);

	template<class RECEIVER> void
		connect(RECEIVER* receiver, void (RECEIVER::* function)(Thread*));

	template<class RECEIVER> void 
		connect(RECEIVER* receiver, void (RECEIVER::* function)(Thread*) const);

	void 
		disconnect(signals::Receiver* receiver);

	void 
		execute(cpuID preferredCPU=noCPUpreference); 
	
	void 
		executeAndWait(cpuID preferredCPU=noCPUpreference);

	cpuID 
		getPreferredCPU(void) const;

	const std::string& 
		toString(void) const;

private:
	enum RunningState
	{
		completed,		// execution complete 
		closed,			// hardware thread resource returned
		error,			// hardware initialization failed 
		uninitialized,	// no hardware thread
		running,		// hardware thread executing
		suspended		// hardware execution paused
	}; // enum Thread::RunningState

#if WIN32
	static uint __stdcall 
		systemExecute(threadHandle thread)
	{
		static_cast<Thread*>(thread)->internalExecute();
		return 0;
	}
#else
	PREVENT_COMPILE
#endif//WIN32

	Thread(Executor& executable,
	cpuID preferredCPU)
	: m_executor(&executable)
	, m_preferredCPU(preferredCPU)
	, m_thread(NULL)
	, m_state(Thread::uninitialized)
	{ /* empty */ }

	/** not allowed */
	Thread(const Thread&);
	Thread(void);

	void
		closeHardware(void);

	void 
		internalExecute(void);

	void
		initializeHardware(cpuID preferredCPU, bool startSuspended);

	void 
		initializeSuspended(cpuID preferredCPU);

	inline bool 
		isWaitable(void) const { return m_state == running || m_state == suspended; }

	void
		updateCPUPreference(cpuID suggestedCPU);

	RunningState
		m_state;

	Executor*			
		m_executor;
	
	threadID
		m_id;

	cpuID 
		m_preferredCPU;

	threadHandle		
		m_thread;

 	signals::Transmitter1<Thread*> 
		m_onComplete;
};

template<class RECEIVER> 
void Thread::connect(RECEIVER* receiver, void (RECEIVER::* function)(Thread*))
{
	m_onComplete.connect(receiver, function);
}

template<class RECEIVER> 
void Thread::connect(RECEIVER* receiver, void (RECEIVER::* function)(Thread*) const)
{
	m_onComplete.connect(receiver, function);
}

} // multithreading

#endif//THREADS_H
