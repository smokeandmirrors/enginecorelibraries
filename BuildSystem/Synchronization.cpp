#include "Synchronization.h"
#include <assert.h>
#if WIN32
#include <process.h>
#include <windows.h>

typedef CRITICAL_SECTION criticalSection;
#endif//WIN32

namespace multithreading
{

class Mutex 
{
public:
#if WIN32
	Mutex(void)
	{
		InitializeCriticalSection(&m_criticalsection);
	}

	~Mutex(void)
	{
		DeleteCriticalSection(&m_criticalsection);
	}

	void enter(void)
	{
		EnterCriticalSection(&m_criticalsection);
	}
	
	void exit(void)
	{
		LeaveCriticalSection(&m_criticalsection);
	}

protected:
	criticalSection	m_criticalsection;
#endif//WIN32
}; // class Mutex

Synchronizer::Synchronizer(Mutex* mutex) 
: m_mutex(mutex)
{
	assert(mutex);
	m_mutex->enter();
}

Synchronizer::Synchronizer(const Mutex* mutex) 
: m_mutex(const_cast<Mutex*>(mutex))
{
	assert(mutex);
	m_mutex->enter();
}

Synchronizer::~Synchronizer(void)
{
	m_mutex->exit();
}

Mutex* getMutex(void) 
{
	return new Mutex();
}

void returnMutex(Mutex* mutex)
{
	delete mutex;
}

} // namespace multithreading