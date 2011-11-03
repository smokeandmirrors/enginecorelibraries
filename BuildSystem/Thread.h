#pragma once
#ifndef THREADS_H
#define THREADS_H

#include <string>

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
	
class Thread
{
public:
	/** 
	\todo unify job/thread make Executor public
	\todo make thread pool, static borrow/recycle, private constructors, destructors, answer questions about state?
	\todo make all public functionality static? 
	*/
	Thread(Executor& executable,
		bool startSuspended=false,
		cpuID preferredCPU=noCPUpreference);

	virtual 
		~Thread(void);

	template<class RECEIVER> void
		connect(RECEIVER* receiver, void (RECEIVER::* function)(Thread*));

	template<class RECEIVER> void 
		connect(RECEIVER* receiver, void (RECEIVER::* function)(Thread*) const);

	void 
		disconnect(signals::Receiver* receiver);

	void 
		execute(cpuID suggestedCPU=noCPUpreference); 
	
	void 
		executeAndWait(cpuID suggestedCPU=noCPUpreference);

	cpuID 
		getPreferredCPU(void) const;

	const std::string& 
		toString(void) const;

	void
		waitOnCompletion(void);

private:
	
	enum RunningState
	{
		completed,
		error,
		running,
		suspended
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
		
	/** not allowed */
	Thread(const Thread&);
	Thread(void);

	void
		updateCPUPreference(cpuID suggestedCPU);
	
	void 
		internalExecute(void);

	void 
		initialize(cpuID preferredCPU);
	
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
