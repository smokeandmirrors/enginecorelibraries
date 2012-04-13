#if WIN32
#include <process.h>
#include <windows.h>
#endif//WIN32

#include "Dispatcher.h"
#include "Thread.h"

namespace concurrency
{
const millisecond waitInfinitely = 10000000000;

const cpuID 
	noCPUpreference(-1);

const threadID
	invalidThreadID(0xFFFFFFFF);

inline void 
	closeThread(threadHandle);

inline threadHandle	
	createThread(threadable function, bool startSuspended, threadID& id, void* args, cpuID cpuPreference=noCPUpreference);

inline threadHandle	
	getCurrentThread(void);

inline threadID
	getCurrentThreadID(void);

inline bool
	resumeThread(threadHandle);

inline bool 
	waitForCompletion(threadHandle& handle, millisecond milliseconds);

inline bool 
	waitForCompletion(threadHandle* handles, uint numThreads, bool waitForAll, millisecond milliseconds);

#if TEST_THREAD_DESTRUCTION	
uint Thread::m_created(0);
DEFINE_STATIC_MUTEX(Thread, m_createdMutex)
#endif//TEST_THREAD_DESTRUCTION	

Thread::~Thread(void)
{
	if (m_state == running)
	{
		waitOnCompletion(*this);
	}
	
	closeHardware();
	delete m_executor;
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
	assert(invalidThreadID == m_launcherID);
	m_launcherID = getCurrentThreadID();

	if (m_state == uninitialized)
	{
		initializeHardware(preferredCPU, false);
	}
	else if (m_state == suspended)
	{
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

threadID Thread::getCurrentID(void)
{
	return getCurrentThreadID();
}

Thread* Thread::getExecuting(Executor& executable, cpuID preferredCPU)
{
	Thread* thread = new Thread(executable, preferredCPU);
	thread->execute(preferredCPU);
	return thread;
}

cpuID Thread::getPreferredCPU(void) const
{
	return m_preferredCPU;
}

Thread* Thread::getSuspended(Executor& executable, cpuID preferredCPU)
{
	Thread* thread = new Thread(executable, preferredCPU);
	thread->initializeSuspended(preferredCPU);
	return thread;
}

Thread* Thread::getUninitialized(Executor& executable, cpuID preferredCPU)
{
	return new Thread(executable, preferredCPU);
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

void Thread::updateCPUPreference(cpuID suggestedCPU)
{
	if (suggestedCPU != noCPUpreference)
	{
		m_preferredCPU = suggestedCPU;		
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
	
#define WAIT_ON_MULTIPLE 0
#if WAIT_ON_MULTIPLE 
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
#else // !WAIT_ON_MULTIPLE
	for (size_t index = startingIndex; index < size; index++)
	{
		Thread* thread = threads[index];
		
		if (thread->isWaitable())
		{
			waitForCompletion(thread->m_thread, waitInfinitely);
		}
	}
#endif//WAIT_ON_MULTIPLE
}

void Thread::waitOnCompletionOfChildren(Thread::Tree& threads)
{
	size_t previousSize = 0; 
	
	do
	{
		size_t startingIndex = previousSize;
		previousSize = threads.getSize();
		waitOnCompletion(threads, startingIndex);		
	}
	while (previousSize != threads.getSize());
}


#if WIN32

#define THREAD_RESUME_FAILED (0xFFFFFFFF)

inline threadHandle createThread(threadable function, bool startSuspended, threadID& id, void* args, sint/* CPUid*/)
{	
	// see windows docs, _beginthreadex calls CreateThread
	// see safety issues http://msdn.microsoft.com/en-us/library/kdzttdcb.aspx
	unsigned initflag = startSuspended ? CREATE_SUSPENDED : 0;
	HANDLE newthread = (HANDLE)(_beginthreadex(NULL, 0, function, args, initflag, &id));
	/** 
	\todo the last parameter is CPUid, allow for setting the processor affinity on a per
	platform basis
	if (CPUid != noCPUpreference)
	{
		DWORD result = SetThreadIdealProcessor(newthread, static_cast<uint>(CPUid));
	}
	*/
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
			printf("waitForCompletion array ERROR: %d\n", lastError);
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

	}
	
	return success;
}

#endif//WIN32

} // namespace concurrency