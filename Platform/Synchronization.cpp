#include "Synchronization.h"
#include <assert.h>

#if WIN32
#include <process.h>
#include <Windows.h>
#endif//WIN32

namespace concurrency
{
Synchronizer::Synchronizer(Mutex<false>&)
	: type(NoSynchronization)
{
	/* empty */
}

Synchronizer::Synchronizer(const Mutex<false>&)
	: type(NoSynchronization)
{
	/* empty */
}

Synchronizer::Synchronizer(Mutex<true>& mutex) 
	: type(MutexType)
	, syncronizationObject(reinterpret_cast<void*>(&mutex))
{
	mutex.acquire();
}

Synchronizer::Synchronizer(const Mutex<true>& mutex)
	: type(MutexType)
	, syncronizationObject(reinterpret_cast<void*>(& const_cast<Mutex<true>&>(mutex)))
{
	const_cast<Mutex<true>&>(mutex).acquire();
}

Synchronizer::Synchronizer(Semaphore& semaphore) 
	: type(SemaphoreType)
	, syncronizationObject(reinterpret_cast<void*>(&semaphore))
{
	semaphore.acquire();
}

Synchronizer::Synchronizer(const Semaphore& semaphore)
	: type(SemaphoreType)
	, syncronizationObject(reinterpret_cast<void*>(& const_cast<Semaphore&>(semaphore)))
{
	const_cast<Semaphore&>(semaphore).acquire();
}

Synchronizer::~Synchronizer(void)
{
	switch (type)
	{
	case MutexType:
		reinterpret_cast<Mutex<true>*>(syncronizationObject)->release();
		break;

	case SemaphoreType:
		reinterpret_cast<Semaphore*>(syncronizationObject)->release();
		break;
	}
}

} // namespace concurrency