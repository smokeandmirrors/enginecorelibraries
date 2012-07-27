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
const ExecutionPriority unspecifiedPriority = 0;

Thread* mainThread(NULL);

DECLARE_MUTEX(treesByIDsMutex); 
// containers::Table<Thread::Tree*> treesByIDs; // todo, fix this, we can't have static tables
containers::RedBlackMap<concurrency::threadID, Thread::Tree*> treesByIDs;

const millisecond waitInfinitely(10000000000);
const cpuID noCPUpreference(-1);
const threadID invalidThreadID(0xFFFFFFFF);

inline void closeThread(threadHandle);
inline threadHandle	createThread(threadable function, bool startSuspended, threadID& id, void* args, cpuID cpuPreference=noCPUpreference);
inline threadHandle	getCurrentThread(void);
inline threadID getCurrentThreadID(void);

inline bool resumeThread(threadHandle);
inline bool setThreadCPUpreference(threadHandle& handle, cpuID cpuPreference);
inline bool waitForCompletion(threadHandle& handle, millisecond milliseconds);
inline bool waitForCompletion(threadHandle* handles, uint numThreads, bool waitForAll, millisecond milliseconds);

#if TEST_THREAD_DESTRUCTION	
uint Thread::m_created(0);
DEFINE_STATIC_MUTEX(Thread, m_createdMutex)
#endif//TEST_THREAD_DESTRUCTION	

void Thread::initializeSystem()
{
	if (mainThread == NULL)
	{
		mainThread = new Thread();
		registerThread(Thread::getThisID(), mainThread);
	}
}

void Thread::registerThread(cpuID id, Thread* thread)
{
	Thread::Tree* tree(NULL);
	{
		SYNC(treesByIDsMutex);
		cpuID thisID(Thread::getThisID());

		if (treesByIDs.has(thisID, tree))
		{	// this thread is waited on			
			treesByIDs.set(id, tree);
		}
	}

	if (tree)
	{
		tree->push(thread);
	}
}

void Thread::shutDownSystem()
{	// check to make sure no threads are waiting?
	delete mainThread;
	mainThread = NULL;
}

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
	, m_state(Thread::uninitialized)
	, m_referenceCount(1)
{	
	switch (initialState)
	{
	case Thread::uninitialized:
		break;
	
	case Thread::suspended:
		initializeSuspended(m_preferredCPU);
		break;
	
	case Thread::running:
		execute();
		break;
	
	default:
			assert(false);
	}
	/// \todo a start running really must be created
}

Thread::~Thread(void)
{
	if (this != mainThread)
	{
		if (m_state == running)
		{
			waitOnCompletion(*this);
		}

		closeHardware();
		delete m_executor;
	}
}

void Thread::closeHardware()
{
	SYNC(m_mutex);
	if (m_state == completed
	|| m_state == suspended
	|| m_state == resumed)
	{
		closeThread(m_thread);
		m_state	= closed;
	}
}

void Thread::disconnect(signals::Receiver* receiver)
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
	else if (m_state == suspended)
	{
		if (updateCPUPreference(preferredCPU))
		{
			setThreadCPUpreference(m_thread, m_preferredCPU);
		}

		m_state = resumed;
		resumeThread(m_thread);
	}
	else
	{
		assert(false);
	}
}	

void Thread::executeAndWait(cpuID suggestedCPU)
{
	execute(suggestedCPU);
	waitOnCompletion(*this);
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

Thread* Thread::createSuspended(Executor& executable, cpuID preferredCPU)
{
	Thread* thread = new Thread(executable, preferredCPU, Thread::suspended);
	thread->initializeSuspended(preferredCPU);
	return thread;
}

Thread* Thread::createUninitialized(Executor& executable, cpuID preferredCPU)
{
	return new Thread(executable, preferredCPU, Thread::uninitialized);
}

void Thread::internalExecute(void)
{
	assert(getCurrentThreadID() == m_id);
	assert(isExecutable());	
	m_state = running;
	m_executor->execute();
	m_state = completed;
	m_onComplete.transmit(this);
	removeReference();
}

void Thread::initializeHardware(cpuID preferredCPU, bool startSuspended)
{
	// SYNC(m_mutex);
	updateCPUPreference(preferredCPU);
	
	if (!startSuspended)
		m_state = suspended;

	m_thread = concurrency::createThread(Thread::systemExecute, startSuspended, m_id, this, m_preferredCPU);
	
	registerThread(m_id, this);

	if (m_thread)
	{
		if (startSuspended)
		{
			m_state = suspended;
		} // else m_state will be handled in the attempt to call execute() 
	}
	else
	{
		m_state = error;
	}
}

void Thread::initializeSuspended(cpuID preferredCPU)
{
	initializeHardware(preferredCPU, true);
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

void Thread::waitOnCompletion(ExecutableQueue& executables)
{
	Thread::Tree tree;
	size_t previousSize = executables.inputQueue.size();
	for (size_t i = 0; i < previousSize; ++i)
	{
		ExecutableQueue::ExecutableInput& input = executables.inputQueue[i];
		tree.push(createExecuting(*input.executable, input.preferredCPU));
	}	
	
	waitOnCompletion(tree, 0);
}

void Thread::waitOnCompletionOfChildren(ExecutableQueue& executables)
{
	Thread::Tree tree;
	threadID id(Thread::getThisID());
	assert(!treesByIDs.has(id));
	treesByIDs.set(id, &tree);
	
	size_t previousSize = executables.inputQueue.size();

	for (size_t i = 0; i < previousSize; ++i)
	{
		ExecutableQueue::ExecutableInput& input = executables.inputQueue[i];
		tree.push(createExecuting(*input.executable, input.preferredCPU));
	}	
	
	size_t startingIndex = 0;

	do
	{
		waitOnCompletion(tree, startingIndex);
		startingIndex = previousSize;
		previousSize = tree.getSize();
	}
	while (previousSize != startingIndex);

	// delete all the thread and executables
	// remove all the thread id entries from the treesByIDs
	treesByIDs.remove(id);

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
	
// #define WAIT_ON_MULTIPLE 
#ifdef WAIT_ON_MULTIPLE 
	size_t numHandles = size - startingIndex;
	threadHandle* handles = new threadHandle[numHandles];
	uint numValid(0);

	for (size_t index = startingIndex; index < size; index++)
	{
		Thread* thread = threads[index];

		if (thread->isWaitable())
		{
			handles[numValid] = thread->m_thread;
			numValid++;
		}
		else
		{
			assert(false);
		}
	}

	for (size_t index = numValid; index < numHandles; index++)
	{
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
		Thread* thread = threads[index];
		
		if (thread->isWaitable())
		{
			waitForCompletion(thread->m_thread, waitInfinitely);
		}
	}
#endif // WAIT_ON_MULTIPLE
}

#if WIN32

#define THREAD_RESUME_FAILED (0xFFFFFFFF)

inline threadHandle createThread(threadable function, bool startSuspended, threadID& id, void* args, sint CPUid)
{	
	// see windows docs, _beginthreadex calls CreateThread
	// see safety issues http://msdn.microsoft.com/en-us/library/kdzttdcb.aspx
	unsigned initflag = startSuspended ? CREATE_SUSPENDED : 0;
	HANDLE newthread = (HANDLE)(_beginthreadex(NULL, 0, function, args, initflag, &id));
	/** 
	\todo the last parameter is CPUid, allow for setting the processor affinity on a per
	platform basis
	*/
	if (CPUid != noCPUpreference)
	{
		DWORD result = SetThreadIdealProcessor(newthread, static_cast<uint>(CPUid));
		if (result == -1)
		{
			printf("SetIdeal Failed!\n");
		}
		else
		{
			printf("SetIdeal worked!  %d to %d\n", result, CPUid);
		}
	}
	
	return newthread;
}

inline void	closeThread(threadHandle handle)
{
	CloseHandle(handle);
}

inline threadID getCurrentThreadID(void)
{
	return static_cast<threadID>(GetCurrentThreadId());
}

inline bool resumeThread(threadHandle handle)
{
	return ResumeThread(handle) != THREAD_RESUME_FAILED;
}

inline bool setThreadCPUpreference(threadHandle& handle, cpuID CPUid)
{
	if (CPUid != noCPUpreference)
	{
		if (CPUid > 10)
		{
			printf("SetIdeal on ELEVEN!  %d\n", CPUid);
		}

		DWORD result = SetThreadIdealProcessor(handle, static_cast<uint>(CPUid));
		if (result == -1)
		{
			printf("SetIdeal Failed!  %d\n", CPUid);
			return false;
		}
		else
		{
			printf("SetIdeal worked!  %d to %d\n", result, CPUid);
			return true;
		}
	}

	return false;
}

void sleep(millisecond milliseconds)
{
	Sleep(static_cast<uint>(milliseconds));
}

inline bool waitForCompletion(threadHandle& handle, millisecond milliseconds)
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

inline bool waitForCompletion(threadHandle* handles, uint numThreads, bool waitForAll, millisecond milliseconds)
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
			DWORD lastError = GetLastError();
			LPTSTR buffer(NULL);
			
			if (!FormatMessage(
				FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS,
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

	}
	
	return success;
}

#endif//WIN32

} // namespace concurrency