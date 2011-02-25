#include "Threads.h"

//#if WIN32
//#include <process.h>
//#include <windows.h>
//
///** 
//todo, these themselves might have to be hidden behind even smaller classes for
//better cross-platform use
//*/
//typedef uint			threadID;
//typedef uint __stdcall (*thread_function)(void*);
//typedef HANDLE			thread_resource;
//#endif//WIN32
//
//namespace threading
//{
//
//static const DWORD resumeThreadFailure = -1;
//
//class Thread;
//
//thread_resource createThread(thread_function function, threadID& id);
//void			endThread(void);
//bool			startThread(thread_resource, slong& previous_suspension_count);
//bool			runThread(Thread* object);
//
//bool runThread(Thread* object)
//{
//	object->runFunction();
//	delete object;
//}
//
///** 
//should be an observer or something, there needs to be a way
//of notifying the thread of the Runnable's destruction 
//*/
//class Thread
//{
//public:
//	Thread(Runnable* runnable);
//	Thread(void(*runnable)(void));
//	~Thread(void);
//	bool			start();
//	// below are deprecated in Java, but remain in C++
//	// void	stop();
//	// void	resume();
//
//protected:
//	void			destroyResource();
//	void			runFunction();
//
//private:
//	/** one inner class for the Runnable*, one for the void(*)(void); */
//	void(*			m_function)(void);
//	threadID		m_id;
//	Runnable*		m_object;
//	slong			m_suspensionCount;
//	thread_resource	m_thread;
//}; // class Thread
//
//Thread::Thread(Runnable* runnable);
//: m_object(runnable)
//, m_thread(NULL) /** todo, initialize state object */
//, m_id(0)
//{ 
//	assert(m_object); 
//}
//
//Thread::Thread(void(*runnable)(void)) 
//: m_function(runnable)
//, m_thread(NULL) /** todo, initialize state object */
//, m_id(0)
//{ 
//	assert(m_function); 
//}
//
//Thread::~Thread(void)
//{
//	// inner class->stop()
//	if (m_thread) // if the thread is still running
//	{
//		CloseHandle(m_thread);
//		// notify observers of destruction
//	}
//}
//
//bool Thread::start()
//{
//	return startThread(thread_resource, m_suspensionCount);
//}
//
//thread_resource createThread(thread_function function, threadID& id)
//{	/*
//	calls _beginthreadex with NULL security attributes,
//	0 stack size, 
//	thread_function,
//	no arguments to thread_function,
//	CREATE_SUSPENDED initflag,
//	threadID for the thrdaddr
//	*/
//	return (HANDLE)(_beginthreadex(NULL, 0, function, NULL, CREATE_SUSPENDED, &id));
//}
//
//bool endThread(void)
//{
//	_endthreadex(m_thread);
//}
//
//bool startThread(thread_resource, slong& previous_suspension_count)
//{
//	previous_suspension_count = ResumeThread(thread_resource);
//	return previous_suspension_count != resumeThreadFailure;
//}
///*
//bool stopThread(thread_resource, slong& previous_suspension_count)
//{
//	previous_suspension_count = SuspendThread(thread_resource);
//	return previous_suspension_count != resumeThreadFailure;
//}
//*/

//} // namespace threading
