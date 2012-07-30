#pragma once
#ifndef THREADS_H
#define THREADS_H

#include <algorithm>
#include <string>
#include <vector>

#include "Concurrency.h"
#include "Platform.h"
#include "Signals.h"
#include "Thread.h"

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

typedef uint ExecutionPriority;
extern const ExecutionPriority unspecifiedPriority;

class Thread
{
	friend class Tree;

public:
	class ExecutableInput
	{
	public:
		ExecutableInput(Executor* new_executable, cpuID new_preferredCPU, ExecutionPriority new_priority)
			: executable(new_executable)
			, preferredCPU(new_preferredCPU)
			, priority(new_priority)
		{
			assert(executable != NULL);
		}

		Executor* executable;
		cpuID preferredCPU;
		ExecutionPriority priority;
	};

	class ExecutableQueue
	{
		friend class Thread;
		friend class Dispatcher;

	public:
		typedef std::vector<ExecutableInput>::iterator ExecutableQueueIter; 

	void add(Executor* executable, cpuID preferredCPU=noCPUpreference, ExecutionPriority priority=unspecifiedPriority)
	{
		assert(executable != NULL);
		inputQueue.push_back(ExecutableInput(executable, preferredCPU, priority));
	}
		
	private:
		std::vector<ExecutableInput> inputQueue;
	};
	
	/// \todo these all need to be handled via shared_ptr ? or not

	// these may not be necessary, as the dispatcher clearly needs some attention, too
	/// for the user/scheduler to wait on it
	static Thread* createSuspended(Executor& executable, cpuID preferredCPU=noCPUpreference);
	/// for the daring user, for the scheduler to get the preferred CPU
	static Thread* createUninitialized(Executor& executable, cpuID preferredCPU=noCPUpreference); 
	///
	static Thread* createExecuting(Executor& executable, cpuID preferredCPU=noCPUpreference);
	
	
	// static void execute(ExecutableQueue& executables);
	static void initializeSystem(void);


	static bool isThisWaitedOn(void); // ?? the new dispatcher might need this?
	static bool isWaitedOn(threadID id);
	
	static void shutDownSystem(void);
	static void waitOnCompletion(void);
	static void waitOnCompletion(ExecutableQueue& executables);
	static void waitOnCompletionOfChildren(ExecutableQueue& executables);


	/// for the normal user
	
	
	/// get the ID of the executing thread
	static threadID getThisID(void);
	
	

	template<class RECEIVER> void connect(RECEIVER* receiver, void (RECEIVER::* function)(Thread*));

	template<class RECEIVER> void connect(RECEIVER* receiver, void (RECEIVER::* function)(Thread*) const);

	void addReference(void) const { ++m_referenceCount; }

	void disconnect(signals::Receiver* receiver);

	void execute(cpuID preferredCPU=noCPUpreference); 
	
	void executeAndWait(cpuID preferredCPU=noCPUpreference);

	inline bool getID(threadID& id) const;

	cpuID getPreferredCPU(void) const;
		
	void removeReference(void) const 
	{
		assert(m_referenceCount);
		--m_referenceCount;
		if (!m_referenceCount)
			delete this;
	}

	const std::string& toString(void) const;

public:
	class Tree
	{
	public:
		typedef std::vector<Thread*>::const_iterator ThreadIterConst; 
		typedef std::vector<Thread*>::iterator ThreadIter; 

		Tree(void)
			: rootID(Thread::getThisID())
		{
			SET_THREAD_SPIN_COUNT(mutex, 4);
			threads.reserve(20);
		}

		~Tree()
		{
			Thread::Tree::ThreadIter sentinel(threads.end());
			for (Thread::Tree::ThreadIter iter(threads.begin());
				iter != sentinel;
				iter++)
			{
				(*iter)->removeReference();
			}
		}

		inline ThreadIter begin(void) 
		{
			SYNC(mutex);
			return threads.begin();
		}

		inline ThreadIterConst begin(void) const
		{
			SYNC(mutex);
			return threads.begin();
		}

		inline ThreadIter end(void) 
		{
			SYNC(mutex);
			return threads.end();
		}

		inline ThreadIterConst end(void) const
		{
			SYNC(mutex);
			return threads.end();
		}

		inline size_t getSize(void) const
		{
			SYNC(mutex);
			return threads.size();
		}

		inline threadID getOriginalID(void) const
		{
			return rootID;
		}

		inline Thread* operator[](size_t index) 
		{
			SYNC(mutex);
			return threads[index];
		}

		inline const Thread* operator[](size_t index) const
		{
			SYNC(mutex);
			return threads[index];
		}

		inline void push(Thread* thread)
		{
			SYNC(mutex);
			thread->addReference();
			threads.push_back(thread);
		}

	private:
		Thread& operator=(const Thread&);

		threadID rootID;

		DECLARE_MUTEX(mutex);

		std::vector<Thread*> threads;
	}; // class Thread::Tree
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
	static uint __stdcall systemExecute(threadHandle thread)
	{
		static_cast<Thread*>(thread)->internalExecute();
		// thread->notifyTreeOfCompletion
		return 0;
	}
#else
	#error unsupported concurrency platform
#endif//WIN32

	Thread(Executor& executable, cpuID preferredCPU, RunningState initialState);
	~Thread(void);

	/** not allowed */
	Thread(const Thread&);
	Thread(void);

	void closeHardware(void);

	void internalExecute(void);

	void initializeHardware(cpuID preferredCPU, bool startSuspended);

	void initializeSuspended(cpuID preferredCPU);

	inline bool isExecutable(void) const;

	inline bool isHardwareInitialized(void) const;

	inline bool isWaitable(void) const; 
	void setPreferredCPU(cpuID prefeeredCPU);
	bool updateCPUPreference(cpuID suggestedCPU);
	/// wait on the thread to complete
	static void waitOnCompletion(Thread& thread);
	/// wait on all threads currently in the tree
	static void waitOnCompletion(Tree& threads, size_t startingIndex=0);
	/// wait on the threads in the tree, and any child thread
	static void waitOnCompletionOfChildren(Tree& threads);
	RunningState m_state;

	Executor* m_executor;
	
	mutable uint m_referenceCount;

	threadID m_id;
	
	cpuID m_preferredCPU;

	threadHandle m_thread;

	signals::Transmitter1<Thread*> m_onComplete;

	DECLARE_MUTEX(m_mutex);

#if TEST_THREAD_DESTRUCTION	
	static uint m_created;
	DECLARE_STATIC_MUTEX(m_createdMutex);
	static void incrementCreated(void)
	{
		SYNC(m_createdMutex);
		++m_created;
	}
	static void decrementCreated(void)
	{
		SYNC(m_createdMutex);
		--m_created;
	}

public:
	static void checkDestruction(void)
	{
		SYNC(m_createdMutex);
		assert(m_created == 0);
	}
#endif//TEST_THREAD_DESTRUCTION
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
