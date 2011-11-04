#if WIN32
#include <process.h>
#include <windows.h>
#endif//WIN32

#include "Thread.h"

namespace multithreading
{
const millisecond 
	waitInfinitely = 10000000000.0f;

const cpuID 
	noCPUpreference(-1);

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
	if (m_state == completed
	|| m_state == suspended)
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
	if (m_state == uninitialized)
	{
		initializeHardware(preferredCPU, false);
	}
	else if (m_state == suspended
	&& resumeThread(m_thread))
	{
		m_state = running;
	}
}	

void Thread::executeAndWait(cpuID suggestedCPU)
{
	execute(suggestedCPU);
	waitOnCompletion(*this);
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
	m_executor->execute();
	m_state = completed;
	m_onComplete.send(this);
	closeHardware();
}

void Thread::initializeHardware(cpuID preferredCPU, bool startSuspended)
{
	updateCPUPreference(preferredCPU);
	m_thread = multithreading::createThread(Thread::systemExecute, startSuspended, m_id, this, m_preferredCPU);

	if (m_thread)
	{
		m_state = startSuspended ? suspended : running;
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
		multithreading::waitForCompletion(thread.m_thread, waitInfinitely);
	}
}

void Thread::waitOnCompletion(std::vector<Thread*>& threads)
{
	threadHandle* handles = new threadHandle[threads.size()];

	std::vector<Thread*>::iterator sentinel(threads.end());

	uint numValid(0);

	for (std::vector<Thread*>::iterator iter(threads.begin());
	iter != sentinel;
	iter++)
	{
		if ((*iter)->isWaitable())
		{
			handles[numValid] = (*iter)->m_thread;
			numValid++;
		}
	}

	waitForCompletion(handles, numValid, true, waitInfinitely);
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
		printf("ERROR: %d\n", lastError);
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
			printf("ERROR: %d\n", lastError);
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

} // namespace multithreading