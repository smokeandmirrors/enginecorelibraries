#include "Threads.h"

#if WIN32
#include <process.h>
#include <windows.h>
#endif

namespace threading
{
// #if WIN32
// #include <process.h>
// #include <windows.h>
// 
// static const DWORD resumeThreadFailure = -1;
// 
// thread_resource createThread(thread_function function, threadID& id)
// {	/*
// 	calls _beginthreadex with NULL security attributes,
// 	0 stack size, 
// 	thread_function,
// 	no arguments to thread_function,
// 	CREATE_SUSPENDED initflag,
// 	threadID for the thrdaddr
// 	*/
// 	return (HANDLE)(_beginthreadex(NULL, 0, function, NULL, CREATE_SUSPENDED, &id));
// }
// 
// 
// 
// bool startThread(thread_resource, slong& previous_suspension_count)
// {
// 	previous_suspension_count = ResumeThread(thread_resource);
// 	return previous_suspension_count != resumeThreadFailure;
// }
// /*
// bool stopThread(thread_resource, slong& previous_suspension_count)
// {
// 	previous_suspension_count = SuspendThread(thread_resource);
// 	return previous_suspension_count != resumeThreadFailure;
// }
// */
// #endif//WIN32
// 
// Thread::Thread(Runnable* runnable);
// : m_object(runnable)
// , m_thread(NULL) /** todo, initialize state object */
// , m_id(0)
// { 
// 	assert(m_object); 
// }
// 
// Thread::Thread(void(*runnable)(void)) 
// : m_function(runnable)
// , m_thread(NULL) /** todo, initialize state object */
// , m_id(0)
// { 
// 	assert(m_function); 
// }
// 
// Thread::~Thread(void)
// {
// 	// inner class->stop()
// 	if (m_thread)
// 	{
// 		_endthreadex(m_thread)
// 		CloseHandle(m_thread())
// 		// notify observers of destruction
// 	}
// }
// 
// bool Thread::start()
// {
// 	return startThread(thread_resource, m_suspensionCount);
// }

} // namespace threading
