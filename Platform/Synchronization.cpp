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

Mutex::Mutex(void)
: m_mutex(new PlatformMutex())
{
	/* empty */
}

Mutex::~Mutex(void)
{
	delete m_mutex;
}

void Mutex::acquire(void)
{
	m_mutex->acquire();
}

void Mutex::release(void)
{ 
	m_mutex->release();
}


} // namespace concurrency