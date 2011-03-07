#include "Threads.h"

#if WIN32
#include <process.h>
#include <windows.h>

typedef uint(__stdcall*		threadable)(void*);
typedef uint				threadID;
typedef void*				threadHandle;
typedef void(*				executableFunction)(void);

/** 
todo, these themselves might have to be hidden behind even smaller classes for
better cross-platform use
*/

namespace multithreading
{
inline threadHandle createThread(threadable function, threadID& id, void* args, sint CPUid=-1);
inline void endThread(void);
inline uint GetNumHardwareThreads(void);

#if WIN32
inline threadHandle createThread(threadable function, threadID& id, void* args, sint/* CPUid*/)
{	
	HANDLE newthread = (HANDLE)(_beginthreadex(NULL, 0, function, args, 0, &id));
	/** 
	\todo the last parameter is CPUid, allow for setting the processor affinity on a per
	platform basis
	DWORD result = SetThreadIdealProcessor(newthread, CPUid);
	*/
	return newthread;
}

inline void endThread(void)
{
	uint status(0);
	_endthreadex(status);
}

inline uint GetNumHardwareThreads(void)
{
	_SYSTEM_INFO system_info;
	GetSystemInfo(&system_info);
}
#endif//WIN32

/** 
should be an observer or something, there needs to be a way
of notifying the thread of the Executable's destruction 
*/
class Thread
{
public:
	Thread(Executable* runnable, sint CPUid=-1);
	Thread(executableFunction, sint CPUid=-1);
	~Thread(void);

protected:
	void					execute(void);

private:
	
	class Executor
	{
	public:
		void initialize(Thread* thread, threadHandle& handle, threadID& id, sint CPUid)
		{
			handle = multithreading::createThread(Thread::executeThread, id, thread, CPUid);
		}
		virtual void execute(void)=0;
	};

	class ExecutableExecutor : public Executor
	{
	public:
		ExecutableExecutor(Executable* object) 
		: m_object(object) 
		{ /* empty */ }
		
		void execute(void)
		{
			m_object->execute();
		}					
		
		Executable*				m_object;
	};

	class FunctionExecutor : public Executor
	{
	public:		
		FunctionExecutor(executableFunction function) 
		: m_function(function) 
		{ /* empty */ }
		
		void execute(void)
		{
			(*m_function)();
		}		

		executableFunction		m_function;
	};
	
	friend class Thread::FunctionExecutor;
	friend class Thread::Executor;
	friend class Thread::ExecutableExecutor;

#if WIN32
	static uint __stdcall executeThread(void* pThread);
#endif//WIN32

	/** not allowed */
	Thread(const Thread&);
	Thread(void);
	void					initialize(sint CPUid);
	
	Executor*				m_executor;
	threadID				m_id;
	threadHandle			m_thread;
}; // class Thread

Thread::Thread(Executable* executable, sint CPUid) 
: m_executor(new Thread::ExecutableExecutor(executable))
{ 
	initialize(CPUid);
}

Thread::Thread(void(*executable)(void), sint CPUid)
: m_executor(new Thread::FunctionExecutor(executable))
{ 
	initialize(CPUid);
}

Thread::~Thread(void)
{	
	CloseHandle(m_thread);
	delete m_executor;
}

void Thread::execute(void)
{
	m_executor->execute();
}

uint Thread::executeThread(void* pThread)
{
	static_cast<Thread*>(pThread)->execute();
	endThread();
	return 0;
}

void Thread::initialize(sint CPUid)
{
	assert(m_executor);
	m_executor->initialize(this, m_thread, m_id, CPUid);
	m_executor->execute();
}

} // namespace multithreading
#endif//WIN32