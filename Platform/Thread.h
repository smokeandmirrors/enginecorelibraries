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
	friend class Sleeper;

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
	
	static bool isThisWaitedOn(void); // ?? the new dispatcher might need this?
	static bool isWaitedOn(threadID id);
	static Thread* create(Executor& executable, cpuID preferredCPU=noCPUpreference);
	static void execute(ExecutableQueue& executables);
	static void executeAndWait(ExecutableQueue& executables);
	static void executeAndWaitOnChildren(ExecutableQueue& executables);
	/// get the ID of the executing thread
	static threadID getThisID(void);
	
	template<class RECEIVER> void connect(RECEIVER* receiver, void (RECEIVER::* function)(Thread*));
	template<class RECEIVER> void connect(RECEIVER* receiver, void (RECEIVER::* function)(Thread*) const);
	void addReference(void) const { ++m_referenceCount; }
	void disconnect(signals::Receiver* receiver);
	void execute(cpuID preferredCPU);
	inline bool getID(threadID& id) const;
	cpuID getPreferredCPU(void) const;
	inline bool isHardwareInitialized(void) const;
	inline bool isWaitable(void) const; 
	inline void removeReference(void) const;
	const std::string& toString(void) const;

public:
	class Tree
	{
	public:
		typedef std::vector<concurrency::Handle> Handles;
		typedef std::vector<concurrency::Handle>::const_iterator IteratorConst; 
		typedef std::vector<concurrency::Handle>::iterator Iterator; 

		Tree(void)
			: parent(NULL)
		{
			SET_THREAD_SPIN_COUNT(mutex, 4);
			handles.reserve(20);
		}
		
		inline Tree::Iterator begin(void) 
		{
			SYNC(mutex);
			return handles.begin();
		}

		inline Tree::IteratorConst begin(void) const
		{
			SYNC(mutex);
			return handles.begin();
		}

		inline Tree::Iterator end(void) 
		{
			SYNC(mutex);
			return handles.end();
		}

		inline Tree::IteratorConst end(void) const
		{
			SYNC(mutex);
			return handles.end();
		}
		
		inline Thread::Tree* getParent(void) 
		{
			return parent;
		}

		inline size_t getSize(void) const
		{
			SYNC(mutex);
			return handles.size();
		}
		
		inline concurrency::Handle operator[](size_t index) 
		{
			SYNC(mutex);
			return handles[index];
		}

		inline const concurrency::Handle operator[](size_t index) const
		{
			SYNC(mutex);
			return handles[index];
		}

		inline void push(concurrency::Handle handle)
		{
			handles.push_back(handle);
		}

		inline void push(Thread& thread)
		{
			assert(thread.isWaitable());
			SYNC(mutex);
			thread.addReference();
			handles.push_back(thread.m_thread);
		}

		inline void setParent(Thread::Tree* parent)
		{
			this->parent = parent;
		}

	private:
		Thread::Tree& operator=(const Thread::Tree&);
		Thread::Tree* parent;		
		DECLARE_MUTEX(mutex);
		Handles handles;
	}; // class Thread::Tree

	class Sleeper
	{
	public:
		Sleeper(bool sleepOnFamily);
		~Sleeper(void);

	private:
		bool sleepsOnFamily;
		cpuID id;
		Tree tree;
	};

private:
	enum RunningState
	{
		completed,		// execution complete 
		closed,			// hardware thread resource returned
		error,			// hardware initialization failed 
		running,		// hardware thread executing
		uninitialized,	// no hardware initialization
		waiting,		// waited on, but not executing 
	}; // enum Thread::RunningState

	// these may not be necessary, as the dispatcher clearly needs some attention, too
	/// for the user/scheduler to wait on it
	///
	static Thread* createExecuting(Executor& executable, cpuID preferredCPU=noCPUpreference);


#if WIN32
	static uint __stdcall systemExecute(concurrency::Handle thread)
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
	void initializeHardwareForExecution();
	void initializeHardwareForWaiting(void);
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

	concurrency::Handle m_thread;
	concurrency::Handle m_event;

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

inline bool Thread::getID(threadID& id) const
{
	id = m_id;
	return isHardwareInitialized();
}

inline bool Thread::isHardwareInitialized(void) const
{	// todo clean this up in a static flag
	return !(m_state == error || m_state == uninitialized || m_state == closed);
}

inline bool Thread::isWaitable(void) const 
{ 
	return isHardwareInitialized(); 
}

inline void Thread::removeReference(void) const 
{
	assert(m_referenceCount);
	--m_referenceCount;
	if (!m_referenceCount)
		delete this;
}

} // concurrency

#endif//THREADS_H
