#include "Synchronization.h"
#include <assert.h>

#if WIN32
#include <process.h>
#include <windows.h>
#endif//WIN32

namespace concurrency
{
#if WIN32
typedef CRITICAL_SECTION criticalSection;
#else
	#error unsupported concurrency platform
#endif//WIN32

class PlatformMutex 
{
public:
#if WIN32
	/** \todo inspect SetCriticalSectionSpinCount */
	inline PlatformMutex(void)
	{
		InitializeCriticalSection(&m_criticalSection);
	}

	inline ~PlatformMutex(void)
	{
		DeleteCriticalSection(&m_criticalSection);
	}

	inline void acquire(void)
	{
		EnterCriticalSection(&m_criticalSection);
	}
	
	inline void release(void)
	{
		LeaveCriticalSection(&m_criticalSection);
	}

private:
	criticalSection	m_criticalSection;
#else
	#error unsupported concurrency platform
#endif//WIN32
}; // class PlatformMutex

#if WIN32
class PlatformSemaphore
{
public:
	inline PlatformSemaphore(uint maxCount=2)
	{
		assert(maxCount >= 2);
		semaphore = CreateSemaphore(NULL, maxCount, maxCount, NULL);
	}

	inline ~PlatformSemaphore(void)
	{
		CloseHandle(semaphore);
	}

	inline void acquire(void)
	{
		WaitForSingleObject(semaphore, INFINITE);
	}

	inline void release(void)
	{
		ReleaseSemaphore(semaphore, 1, NULL);
	}

private:
	HANDLE semaphore;
}; // class PlatformMutex
#else
	#error unsupported concurrency platform
#endif//WIN32

Mutex::Mutex(void)
: mutex(new PlatformMutex())
{
	// empty
}

Mutex::~Mutex(void)
{
	delete mutex;
}

void Mutex::acquire(void)
{
	mutex->acquire();
}

void Mutex::release(void)
{ 
	mutex->release();
}

Semaphore::Semaphore(uint count)
: semaphore(new PlatformSemaphore(count))
{
	// empty
}

Semaphore::~Semaphore(void)
{
	delete semaphore;
}

void Semaphore::acquire(void)
{
	semaphore->acquire();
}

void Semaphore::release(void)
{ 
	semaphore->release();
}

} // namespace concurrency