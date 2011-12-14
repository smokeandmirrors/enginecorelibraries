#pragma once
#ifndef THREADS_H
#define THREADS_H

#include <string>
#include <vector>

#include "Concurrency.h"
#include "Platform.h"
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
namespace concurrency
{

class Thread
{
public:
	class Tree
	{
	public:
		typedef std::vector<Thread*>::const_iterator ThreadIterConst; 
		typedef std::vector<Thread*>::iterator ThreadIter; 

		Tree(void)
		: rootID(Thread::getCurrentID())
		{
			threads.reserve(20);
		}

		~Tree()
		{
			Thread::Tree::ThreadIter sentinel(threads.end());
			for (Thread::Tree::ThreadIter iter(threads.begin());
				iter != sentinel;
				iter++)
			{
				Thread& thread = *(*iter);
				destroyThread(thread);
			}
		}
	
		inline ThreadIter
			begin(void) 
		{
			SYNC(mutex);
			return threads.begin();
		}
		
		inline ThreadIterConst
			begin(void) const
		{
			SYNC(mutex);
			return threads.begin();
		}

		inline ThreadIter
			end(void) 
		{
			SYNC(mutex);
			return threads.end();
		}

		inline ThreadIterConst
			end(void) const
		{
			SYNC(mutex);
			return threads.end();
		}

		inline size_t
			getSize(void) const
		{
			SYNC(mutex);
			return threads.size();
		}

		inline threadID 
			getOriginalID(void) const
		{
			return rootID;
		}

		inline Thread*
			operator[](size_t index) 
		{
			SYNC(mutex);
			return threads[index];
		}

		inline const Thread*
			operator[](size_t index) const
		{
			SYNC(mutex);
			return threads[index];
		}

		inline void
			push(Thread* thread)
		{
			SYNC(mutex);
			threads.push_back(thread);
		}

		inline void
			waitOnCompletion(void)
		{
			waitOnCompletionOfTree(*this);
		}

	private:
		Thread& operator=(const Thread&);

		threadID
			rootID;

		DECLARE_MUTEX(mutex);
		
		std::vector<Thread*>
			threads;
	}; // class Thread::Tree

	static void 
		destroyThread(Thread& thread);
	
	static threadID
		getCurrentID(void);
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
		waitOnCompletion(Tree& threads, size_t startingIndex=0);

	static void
		waitOnCompletionOfTree(Tree& threads);

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

	inline bool 
		getID(threadID& id) const;

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
		resumed,		// hardware resume / start created attempted
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
	, m_launcherID(invalidThreadID)
	{ /* empty */ }


	virtual 
	~Thread(void);

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
		isExecutable(void) const;

	inline bool
		isHardwareInitialized(void) const;

	inline bool 
		isWaitable(void) const; 

	void
		updateCPUPreference(cpuID suggestedCPU);

	RunningState
		m_state;

	Executor*			
		m_executor;
	
	threadID
		m_id;

	threadID
		m_launcherID;

	cpuID 
		m_preferredCPU;

	threadHandle		
		m_thread;

 	signals::Transmitter1<Thread*> 
		m_onComplete;

	DECLARE_MUTEX(m_mutex);
};

template<class RECEIVER> void 
Thread::connect(RECEIVER* receiver, void (RECEIVER::* function)(Thread*))
{
	m_onComplete.connect(receiver, function);
}

template<class RECEIVER> void 
Thread::connect(RECEIVER* receiver, void (RECEIVER::* function)(Thread*) const)
{
	m_onComplete.connect(receiver, function);
}

inline bool 
Thread::getID(threadID& id) const
{
	id = m_id;
	return isHardwareInitialized();
}

inline bool
Thread::isExecutable(void) const
{
	return m_state == resumed || m_state == suspended;
}

inline bool 
Thread::isHardwareInitialized(void) const
{
	return !(m_state == error || m_state == uninitialized);
}

inline bool 
Thread::isWaitable(void) const 
{ 
	return isHardwareInitialized(); 
}
} // concurrency

#endif//THREADS_H
