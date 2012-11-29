#if WIN32
#include <process.h>
#include <windows.h>
#endif//WIN32

#include "Table.h"
#include "RedBlackMap.h"
#include "Dispatcher.h"
#include "Thread.h"

namespace concurrency
{
class WaitingTree
{	
public:
	WaitingTree(bool onChildren)
		: waitOnChildren(onChildren)
	{
		/* empty */
	}

	bool isWaitedOn(threadID id)
	{
		SYNC(mutex);
		{
			return waitsByThreadIDs.has(id);
		}
	}
	
	void registerHandle(concurrency::Handle handle)
	{
		threadID thisID = Thread::getThisID();
		Thread::Tree* tree(NULL);
		{
			SYNC(mutex);
			if (waitsByThreadIDs.has(thisID, tree))
			{	// this thread is waited on
				tree->push(handle);
			}
		}
	}

	void registerThread(threadID id, Thread& thread)
	{
		threadID thisID = Thread::getThisID();
		Thread::Tree* tree(NULL);
		{
			SYNC(mutex);
			if (waitsByThreadIDs.has(thisID, tree))
			{	// this thread is waited on
				tree->push(thread);

				if (waitOnChildren)
				{	// so are the children
					waitsByThreadIDs.set(id, tree); 
				}
			}
		}
	}

	void registerTree(threadID id, Thread::Tree& tree)
	{
		SYNC(mutex);
		Thread::Tree* parent;
		if (waitsByThreadIDs.has(id, parent))
		{	// we are in a wait by a wait call
			waitsByThreadIDs.set(id, &tree);
			tree.setParent(parent);
		}
		else
		{
			waitsByThreadIDs.set(id, &tree);
		}
	}

	void unregisterThread(threadID threadID)
	{
		SYNC(mutex);
		waitsByThreadIDs.remove(threadID);
	}

	void unregisterTree(threadID id)
	{
		SYNC(mutex);
		Thread::Tree* tree;
		if (waitsByThreadIDs.has(id, tree))
		{
			if (tree->getParent() == NULL)
			{
				waitsByThreadIDs.remove(id);
			}
			else
			{
				waitsByThreadIDs.set(id, tree->getParent());
			}
		}
	}

private:
	bool waitOnChildren;
	DECLARE_MUTEX(mutex); 
	containers::RedBlackMap<concurrency::threadID, Thread::Tree*> waitsByThreadIDs;
};

WaitingTree singleWait(false);
WaitingTree childWait(true);

void registerHandle(concurrency::Handle handle)
{
	singleWait.registerHandle(handle);
	childWait.registerHandle(handle);
}

void registerTree(threadID id, Thread::Tree& tree, bool waitOnChildren)
{
	WaitingTree& waitingTree = waitOnChildren ? childWait : singleWait;
	waitingTree.registerTree(id, tree);
}

void registerThread(threadID threadID, Thread& thread)
{
	singleWait.registerThread(threadID, thread);
	childWait.registerThread(threadID, thread);
}

void unregisterTree(threadID id, bool waitOnChildren)
{
	WaitingTree& waitingTree = waitOnChildren ? childWait : singleWait;
	waitingTree.unregisterTree(id);
}
	
void unregisterThread(threadID threadID)
{
	singleWait.unregisterThread(threadID);
	childWait.unregisterThread(threadID);
}


const ExecutionPriority unspecifiedPriority = 0;


Thread::Sleeper::Sleeper(bool sleepOnFamily)
	: sleepsOnFamily(sleepOnFamily)
	, id(Thread::getThisID())
{
	registerTree(id, tree, sleepsOnFamily);
}

Thread::Sleeper::~Sleeper(void)
{
	if (sleepsOnFamily)
	{
		size_t previousSize = tree.getSize();
		size_t startingIndex = 0;

		do
		{
			Thread::waitOnCompletion(tree, startingIndex);
			startingIndex = previousSize;
			previousSize = tree.getSize();
		}
		while (previousSize != startingIndex);
	}
	else
	{	
		Thread::waitOnCompletion(tree, 0);
	}

	unregisterTree(id, sleepsOnFamily);
}


const millisecond waitInfinitely(10000000000);
const cpuID noCPUpreference(-1);
const threadID invalidThreadID(0xFFFFFFFF);

inline void closeThread(concurrency::Handle);
inline void closeIdleThreadWaitObject(concurrency::Handle);
inline Handle createIdleThreadWaitObject(void);
inline concurrency::Handle	createThread(threadable function, bool startSuspended, threadID& id, void* args, cpuID cpuPreference=noCPUpreference);
inline concurrency::Handle	getCurrentThread(void);
inline threadID getCurrentThreadID(void);

inline bool resumeThread(concurrency::Handle);
inline void signalWaitObject(concurrency::Handle);
inline bool setThreadCPUpreference(concurrency::Handle& handle, cpuID cpuPreference);
inline bool waitForCompletion(concurrency::Handle handle, millisecond milliseconds);
inline bool waitForCompletion(concurrency::Handle* handles, uint numThreads, bool waitForAll, millisecond milliseconds);

#if TEST_THREAD_DESTRUCTION	
uint Thread::m_created(0);
DEFINE_STATIC_MUTEX(Thread, m_createdMutex)
#endif//TEST_THREAD_DESTRUCTION	

Thread::Thread(void)
: m_id(Thread::getThisID())
{
	/* empty */
}

Thread::Thread
	( Executor& executable
	, cpuID preferredCPU
	, RunningState initialState)
	: m_executor(&executable)
	, m_preferredCPU(preferredCPU)
	, m_thread(NULL)
	, m_event(NULL)
	, m_state(Thread::uninitialized)
	, m_referenceCount(1)
{	
	switch (initialState)
	{
	case Thread::running:
		initializeHardwareForExecution();
		break;
	
	case Thread::uninitialized:
		break;
	
	case Thread::waiting:
		initializeHardwareForWaiting();
		break;
			
	default:
		assert(false);
	}
	/// \todo a start running really must be created
}

Thread::~Thread(void)
{
	if (m_state == running)
	{
		waitOnCompletion(*this);
	}

	if (m_state != uninitialized)
	{
		unregisterThread(m_id);
	}

	closeHardware();
	delete m_executor;
}

void Thread::closeHardware()
{
	SYNC(m_mutex);
	if (m_state == completed)
	{
		closeThread(m_thread);
		m_state	= closed;
	}

	if (m_event)
	{
		closeIdleThreadWaitObject(m_event);
	}	
}

void Thread::disconnect(signals::Receiver& receiver)
{
	m_onComplete.disconnect(receiver);
}

void Thread::execute(cpuID preferredCPU)
{	
	SYNC(m_mutex);
	
	if (m_state == uninitialized)
	{
		initializeHardware(preferredCPU, false);
	}
	else
	{
		BREAKPOINT(0x0);
		assert(false);
	}
}	

void Thread::execute(ExecutableQueue& executables)
{
	for (ExecutableQueue::ExecutableQueueIter iter(executables.inputQueue.begin()), sentinel(executables.inputQueue.end()); 
		iter != sentinel; 
		++iter)
	{
		createExecuting(*iter->executable, iter->preferredCPU);
	}	
}

void Thread::executeAndWait(ExecutableQueue& work)
{
	Sleeper sleeper(false);
	execute(work);
}

void Thread::executeAndWaitOnChildren(ExecutableQueue& work)
{
	Sleeper sleeper(true);
	execute(work);
}

threadID Thread::getThisID(void)
{
	return getCurrentThreadID();
}

Thread* Thread::createExecuting(Executor& executable, cpuID preferredCPU)
{
	Thread* thread = new Thread(executable, preferredCPU, Thread::running);
	return thread;
}

cpuID Thread::getPreferredCPU(void) const
{
	return m_preferredCPU;
}

Thread* Thread::create(Executor& executable, cpuID preferredCPU)
{
	return new Thread(executable, preferredCPU, isThisWaitedOn() ? Thread::waiting : Thread::uninitialized);
}

void Thread::internalExecute(void)
{
	m_state = running;
	m_executor->execute();
	m_state = completed;
	m_onComplete.transmit(this);
	removeReference();
}

bool Thread::isThisWaitedOn(void)
{
	return isWaitedOn(getThisID());	
}

bool Thread::isWaitedOn(threadID id)
{
	return childWait.isWaitedOn(id) || singleWait.isWaitedOn(id);
}

void Thread::initializeHardware(cpuID preferredCPU, bool startSuspended)
{
	updateCPUPreference(preferredCPU);
	
	if (startSuspended)
	{
		initializeHardwareForWaiting();
	}
	else
	{
		initializeHardwareForExecution();
	}
}

void Thread::initializeHardwareForExecution(void)
{
	m_thread = concurrency::createThread(Thread::systemExecute, false, m_id, this, m_preferredCPU);
	
	if (m_event)
	{
		signalWaitObject(m_event);
	}

	if (m_thread)
	{
		m_state = running;
		registerThread(m_id, *this);
	}
	else
	{
		m_state = error;
	}
}

void Thread::initializeHardwareForWaiting(void)
{
	m_event = concurrency::createIdleThreadWaitObject();
	
	if (m_event)
	{
		registerHandle(m_event);
	}	
	else
	{
		m_state = error;
	}
}

const std::string& Thread::toString(void) const 
{ 
	return m_executor->toString(); 
} 

bool Thread::updateCPUPreference(cpuID suggestedCPU)
{
	if (suggestedCPU != noCPUpreference
	&& suggestedCPU != m_preferredCPU)
	{
		m_preferredCPU = suggestedCPU;
		return true;
	}
	else
	{
		return false;
	}
}

void Thread::waitOnCompletion(Thread& thread)
{
	if (thread.isWaitable())
	{
		waitForCompletion(thread.m_thread, waitInfinitely);
	}
}

void Thread::waitOnCompletion(Tree& threads, size_t startingIndex)
{
	size_t size = threads.getSize();
	assert(size > 0);
	assert(startingIndex >= 0);
	assert(startingIndex < static_cast<sint>(size));
	
#define WAIT_ON_MULTIPLE 
#ifdef WAIT_ON_MULTIPLE 
	size_t numHandles = size - startingIndex;
	concurrency::Handle* handles = new concurrency::Handle[numHandles];
	uint numValid(0);

	for (size_t index = startingIndex; index < size; index++)
	{
		handles[numValid] = threads[index];
		numValid++;
	}

	for (size_t index = numValid; index < numHandles; index++)
	{
		assert(handles[index] == NULL);
		handles[index] = NULL; // should be unnecessary
	}

	for (size_t index = 0; index < numValid; index++)
	{
		assert(handles[index] != NULL);
	}

	// change this to single wait version
	waitForCompletion(handles, numValid, true, waitInfinitely);
	
	for (size_t i = 0; i < numHandles; i++)
		handles[i] = NULL; // should be unnecessary

	delete[] handles;
#else // ndef WAIT_ON_MULTIPLE
	for (size_t index = startingIndex; index < size; index++)
	{
		waitForCompletion(threads[index], waitInfinitely);
	}
#endif // WAIT_ON_MULTIPLE
}

#if WIN32

#define THREAD_RESUME_FAILED (0xFFFFFFFF)

inline void reportLastError(void);

inline void closeIdleThreadWaitObject(concurrency::Handle handle)
{
	if (!CloseHandle(handle))
	{
		reportLastError();
	}
}

inline Handle createIdleThreadWaitObject(void)
{
	Handle handle = CreateEvent(NULL, true, false, NULL);
	if (!handle)
	{
		reportLastError();
	}
	return handle;
}

inline concurrency::Handle createThread(threadable function, bool startSuspended, threadID& id, void* args, sint CPUid)
{	
	// see windows docs, _beginthreadex calls CreateThread
	// see safety issues http://msdn.microsoft.com/en-us/library/kdzttdcb.aspx
	unsigned initflag = startSuspended ? CREATE_SUSPENDED : 0;
	HANDLE newthread = (HANDLE)(_beginthreadex(NULL, 0, function, args, initflag, &id));

	if (newthread)
	{
	/** 
	\todo the last parameter is CPUid, allow for setting the processor affinity on a per
	platform basis
	*/
		if (CPUid != noCPUpreference)
		{
			setThreadCPUpreference(newthread, CPUid);
		}

		return newthread;
	}
	else
	{
		int errorValue;
		errno_t errorCallStatus = _get_errno(&errorValue);
		
		if (!errorCallStatus)
		{
			printf("error discovery failed!\n");
		}
		
		BREAKPOINT(0x0);
		return NULL;
	}
	
}

inline void	closeThread(concurrency::Handle handle)
{
	CloseHandle(handle);
}

inline threadID getCurrentThreadID(void)
{
	return static_cast<threadID>(GetCurrentThreadId());
}

inline void reportLastError(void)
{
	DWORD lastError = GetLastError();
	LPTSTR buffer(NULL);

	if (!FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, 
		0,
		0,
		buffer, 
		0,
		NULL))
	{
		wprintf(L"Format message failed with 0x%x\n", lastError);
	}
	else
	{
		wprintf(buffer);
		LocalFree(buffer);
	}
}

inline bool resumeThread(concurrency::Handle handle)
{
	return ResumeThread(handle) != THREAD_RESUME_FAILED;
}

inline void signalWaitObject(concurrency::Handle handle)
{
	if (!SetEvent(handle))
	{
		reportLastError();
	}
}

inline bool setThreadCPUpreference(concurrency::Handle& handle, cpuID CPUid)
{
	if (CPUid != noCPUpreference)
	{
// 		if (CPUid > 10)
// 		{
// 			printf("SetIdeal on ELEVEN!  %d\n", CPUid);
// 		}
//		SetThreadIdealProcessor(handle, static_cast<uint>(CPUid));
//		DWORD result = SetThreadIdealProcessor(handle, static_cast<uint>(CPUid));
// 		if (result == -1)
// 		{
// 			printf("SetIdeal Failed!  %d\n", CPUid);
// 			return false;
// 		}
// 		else
// 		{
// 			printf("SetIdeal worked!  %d to %d\n", result, CPUid);
// 			return true;
// 		}
	}

	return false;
}

void sleep(millisecond milliseconds)
{
	Sleep(static_cast<uint>(milliseconds));
}

inline bool waitForCompletion(concurrency::Handle handle, millisecond milliseconds)
{
	bool success(false);

	DWORD result = WaitForSingleObject(handle, 
		milliseconds == waitInfinitely 
		? INFINITE 
		: static_cast<DWORD>(milliseconds));

	success = result != WAIT_FAILED;

	if (!success)
	{
		DWORD lastError = GetLastError();
		printf("waitForCompletion single ERROR: %d\n", lastError);
		LPWSTR pMessage = L"%1!*.*s! %4 %5!*s!";
		DWORD_PTR pArgs[] = { (DWORD_PTR)4, (DWORD_PTR)2, (DWORD_PTR)L"Bill",  // %1!*.*s! refers back to the first insertion string in pMessage
			(DWORD_PTR)L"Bob",                                                // %4 refers back to the second insertion string in pMessage
			(DWORD_PTR)6, (DWORD_PTR)L"Bill" };                               // %5!*s! refers back to the third insertion string in pMessage
		const DWORD size = 100+1;
		WCHAR buffer[size];


		if (!FormatMessage(FORMAT_MESSAGE_FROM_STRING | FORMAT_MESSAGE_ARGUMENT_ARRAY,
			pMessage, 
			0,
			0,
			buffer, 
			size, 
			(va_list*)pArgs))
		{
			wprintf(L"Format message failed with 0x%x\n", GetLastError());
		}
		else
		{
			wprintf(buffer);
		}
	}

	return success;
}

inline bool waitForCompletion(concurrency::Handle* handles, uint numThreads, bool waitForAll, millisecond milliseconds)
{
	bool success(false);

	if (handles && numThreads)
	{
		DWORD result = WaitForMultipleObjects(
			numThreads, 
			handles, 
			waitForAll, 
			milliseconds == waitInfinitely 
				? INFINITE 
				: static_cast<DWORD>(milliseconds));
		
		success = result != WAIT_FAILED;

		if (!success)
		{
			reportLastError();
		}
	}
	
	return success;
}

#endif//WIN32

} // namespace concurrency