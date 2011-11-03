#if WIN32
#include <process.h>
#include <windows.h>
#endif//WIN32

#include "Thread.h"

namespace multithreading
{
const millisecond waitInfinitely = 999999999.9f;
const cpuID noCPUpreference(-1);

inline void 
	closeThread(threadHandle);

inline threadHandle	
	createThread(threadable function, bool startSuspended, threadID& id, void* args, cpuID cpuPreference=noCPUpreference);

inline bool
	resumeThread(threadHandle);

inline bool 
	waitForCompletion(threadHandle* handles, uint numThreads, bool waitForAll, millisecond milliseconds);

Thread::Thread(Executor& executable,
   bool startSuspended,
   cpuID preferredCPU)
: m_executor(&executable)
, m_preferredCPU(preferredCPU)
, m_thread(NULL)
, m_state(Thread::suspended)
{ 
	if (!startSuspended)
	{
		execute(preferredCPU);
	}
}

Thread::~Thread(void)
{
	if (m_state == running)
	{
		waitOnCompletion();
	}
		
	if (m_state != completed)
	{
		closeThread(m_thread);
	}

	delete m_executor;
}

void Thread::disconnect(signals::Receiver* receiver)
{
	m_onComplete.disconnect(receiver);
}

void Thread::execute(cpuID suggestedCPU)
{	
	initialize(suggestedCPU);
}	

void Thread::executeAndWait(cpuID suggestedCPU)
{
	execute(suggestedCPU);

	if (m_state == running)
	{
		multithreading::waitForCompletion(&m_thread, 1, true, waitInfinitely);
	}
}

cpuID Thread::getPreferredCPU(void) const
{
	return m_preferredCPU;
}

void Thread::internalExecute(void)
{
	m_executor->execute();
	m_state = completed;
	m_onComplete.send(this);
	closeThread(m_thread);
}

void Thread::initialize(cpuID preferredCPU)
{
	updateCPUPreference(preferredCPU);
	m_thread = multithreading::createThread(Thread::systemExecute, false, m_id, this, m_preferredCPU);

	if (m_thread)
	{
		m_state = running;
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

void Thread::updateCPUPreference(cpuID suggestedCPU)
{
	if (suggestedCPU != noCPUpreference)
	{
		m_preferredCPU = suggestedCPU;		
	}
}

void Thread::waitOnCompletion(void)
{
	multithreading::waitForCompletion(&m_thread, 1, true, waitInfinitely);
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

inline bool resumeThread(threadHandle handle)
{
	return ResumeThread(handle) != THREAD_RESUME_FAILED;
}

void sleep(millisecond milliseconds)
{
	Sleep(static_cast<uint>(milliseconds));
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
	}
	
	return success;
}

#endif//WIN32

} // namespace multithreading