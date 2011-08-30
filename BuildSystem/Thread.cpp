#if WIN32
#include <process.h>
#include <windows.h>
#endif//WIN32

#include "Thread.h"

namespace multithreading
{

const sint noThreadPreference(-1);

void sleep(millisecond milliseconds)
{
#if WIN32
	Sleep(static_cast<uint>(milliseconds));
#endif//WIN32
}

inline void			closeThread(threadHandle);
inline threadHandle	createThread(threadable function, threadID& id, void* args, sint CPUid=noThreadPreference);

#if WIN32
inline threadHandle createThread(threadable function, threadID& id, void* args, sint/* CPUid*/)
{	
	HANDLE newthread = (HANDLE)(_beginthreadex(NULL, 0, function, args, 0, &id));
	/** 
	\todo the last parameter is CPUid, allow for setting the processor affinity on a per
	platform basis
	if (CPUid != noThreadPreference)
	{
		DWORD result = SetThreadIdealProcessor(newthread, static_cast<uint>(CPUid));
	}
	*/
	return newthread;
}

inline void	closeThread(threadHandle threadHandle)
{
	CloseHandle(threadHandle);
}
#endif//WIN32

Thread::~Thread(void)
{
	delete m_executor;
	closeThread(m_thread);
}

void Thread::Executor::initialize(Thread* thread, threadHandle& handle, threadID& id, sint CPUid)
{
	handle = multithreading::createThread(Thread::executeThread, id, thread, CPUid);
}

} // namespace multithreading