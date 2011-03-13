#if WIN32
#include <process.h>
#include <windows.h>
#endif//WIN32

#include "Observation.h"
#include "Threads.h"

namespace multithreading
{

inline threadHandle	createThread(threadable function, threadID& id, void* args, sint4 CPUid=noThreadPreference);
inline void			closeThread(threadHandle);

#if WIN32
inline threadHandle createThread(threadable function, threadID& id, void* args, sint4/* CPUid*/)
{	
	HANDLE newthread = (HANDLE)(_beginthreadex(NULL, 0, function, args, 0, &id));
	/** 
	\todo the last parameter is CPUid, allow for setting the processor affinity on a per
	platform basis
	if (CPUid != noThreadPreference)
	{
		DWORD result = SetThreadIdealProcessor(newthread, static_cast<uint4>(CPUid));
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
	delete m_observable;
	delete m_executor;
	closeThread(m_thread);
}

void Thread::Executor::initialize(Thread* thread, threadHandle& handle, threadID& id, sint4 CPUid)
{
	handle = multithreading::createThread(Thread::executeThread, id, thread, CPUid);
}

} // namespace multithreading