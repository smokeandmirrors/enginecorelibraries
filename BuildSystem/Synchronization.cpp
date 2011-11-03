#include "Synchronization.h"
#include <assert.h>
#if WIN32
#include <process.h>
#include <windows.h>
#endif//WIN32

namespace multithreading
{
#if WIN32
typedef CRITICAL_SECTION criticalSection;
#else
	PREVENT_COMPILE
#endif//WIN32

class PlatformMutex 
{
public:
#if WIN32
	/** \todo inspect SetCriticalSectionSpinCount */
	inline PlatformMutex(void)
	{
		InitializeCriticalSection(&m_criticalsection);
	}

	inline ~PlatformMutex(void)
	{
		DeleteCriticalSection(&m_criticalsection);
	}

	inline void acquire(void)
	{
		EnterCriticalSection(&m_criticalsection);
	}
	
	inline void release(void)
	{
		LeaveCriticalSection(&m_criticalsection);
	}

protected:
	criticalSection	m_criticalsection;
#else
	PREVENT_COMPILE
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


} // namespace multithreading