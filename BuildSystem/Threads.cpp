#if WIN32
#include <process.h>
#include <windows.h>
#endif//WIN32

#include "Observation.h"
#include "Threads.h"

namespace multithreading
{

inline threadHandle createThread(threadable function, threadID& id, void* args, sint CPUid=noThreadPreference);
inline void endThread(void);

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

inline void endThread(void)
{
	uint status(0);
	_endthreadex(status);
}
#endif//WIN32

Thread::~Thread(void)
{
	delete m_observable;
	CloseHandle(m_thread);
	delete m_executor;
}

void Thread::Executor::initialize(Thread* thread, threadHandle& handle, threadID& id, sint CPUid)
{
	handle = multithreading::createThread(Thread::executeThread, id, thread, CPUid);
}

} // namespace multithreading