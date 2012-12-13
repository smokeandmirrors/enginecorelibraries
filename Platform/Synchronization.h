#pragma once
#ifndef SYNCHRONIZATION_H
#define SYNCHRONIZATION_H
/**
<DEVELOPMENT STATUS>
Current Draft		:	0.0
Current Phase		:   DEVELOPMENT
Purpose				:	DEPLOYMENT
Unit Tested			:	NO
Used in development	:	NO
Used in experiments :	YES
Tested in the field	:	NO
*/

#include <assert.h>
#include "Platform.h"

#if WIN32
#include <process.h>
#include <Windows.h>
#endif//WIN32

#define UNIQUE_SYNCHRONIZATION_CONCAT(SYNCHRONIZED, NUMBER) \
	SYNCHRONIZED##NUMBER

#define UNIQUE_SYNCHRONIZATION_PREFIX(SYNCHRONIZED, NUMBER) \
	UNIQUE_SYNCHRONIZATION_CONCAT(SYNCHRONIZED, NUMBER) 

#define UNIQUE_SYNCHRONIZATION(SYNCHRONIZED) \
	UNIQUE_SYNCHRONIZATION_PREFIX(SYNCHRONIZED, __COUNTER__)

#define GLOBAL_THREAD_SAFETY

#ifdef GLOBAL_THREAD_SAFETY
// globally multithreaded
#define DECLARE_MUTEX(INDENTIFIER) \
	concurrency::Mutex<true> INDENTIFIER;

#define DECLARE_MUTABLE_MUTEX(INDENTIFIER) \
	mutable concurrency::Mutex<true> INDENTIFIER;

#define DECLARE_STATIC_MUTEX(INDENTIFIER) \
	static concurrency::Mutex<true> INDENTIFIER;

#define DEFINE_STATIC_MUTEX(SCOPE, INDENTIFIER) \
	concurrency::Mutex<true> SCOPE##::##INDENTIFIER;

#define SET_THREAD_SPIN_COUNT(MUTEX, SPIN_COUNT) \
	MUTEX.setSpinCount(SPIN_COUNT);

#define SYNC(MUTEX) \
	concurrency::Synchronizer UNIQUE_SYNCHRONIZATION(SYNCHRONIZED)(MUTEX);

#else
// globally single threaded
#define DECLARE_MUTEX(INDENTIFIER) 
#define DECLARE_MUTABLE_MUTEX(INDENTIFIER) 
#define DECLARE_STATIC_MUTEX(INDENTIFIER) 
#define DEFINE_STATIC_MUTEX(SCOPE, INDENTIFIER) 
#define SET_THREAD_SPIN_COUNT(MUTEX, SPIN_COUNT)
#define SYNC(MUTEX) 

#endif//GLOBAL_THREAD_SAFETY

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
	inline PlatformMutex(uint spinCount=0)
	{	// InitializeCriticalSection(&m_criticalSection);
		// for a more recent compiler version 
		InitializeCriticalSectionAndSpinCount(&m_criticalSection, spinCount);
	}

	inline ~PlatformMutex(void)
	{
		DeleteCriticalSection(&m_criticalSection);
	}

	inline void acquire(void)
	{
		EnterCriticalSection(&m_criticalSection);
	}

	inline void setSpinCount(uint spinCount)
	{	// for a more recent compiler version
		SetCriticalSectionSpinCount(&m_criticalSection, spinCount);
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

template<bool IS_THREAD_SAFE=true>
class Mutex 
{
public:
	inline Mutex(void) { /* empty */ }
	inline ~Mutex(void) { /* empty */ }
	inline void acquire(void) { mutex.acquire(); }
	inline void release(void) { mutex.release(); }
	inline void setSpinCount(uint spinCount) { mutex.setSpinCount(spinCount); }

protected:
	Mutex(const Mutex&);
	Mutex& operator=(const Mutex&);

	PlatformMutex mutex;
}; // class Mutex

template<>
class Mutex<false>
{
public:
	inline Mutex(void) { /* empty */ }
	inline ~Mutex(void) { /* empty */ }
	inline void acquire(void) { /* empty */  }
	inline void release(void) { /* empty */  }
	inline void setSpinCount(uint) { /* empty */ }

protected:
	Mutex(const Mutex&);
	Mutex& operator=(const Mutex&);
}; // class Mutex<false>

// typedef Mutex<true> Mutex;

class Semaphore
{
public:
	inline Semaphore(uint count=2) : semaphore(count) { /* empty */ }
	inline ~Semaphore(void) { /* empty */ }
	inline void acquire(void) { semaphore.acquire(); }
	inline void release(void) { semaphore.release(); }

protected:
	Semaphore(const Semaphore&);
	Semaphore& operator=(const Semaphore&);

	PlatformSemaphore semaphore;
}; // class Semaphore


class Synchronizer
{
	enum SynchronizationObjectType
	{
		NoSynchronization,
		MutexType,
		SemaphoreType
	};

public:
	explicit Synchronizer(Mutex<false>&);
	explicit Synchronizer(const Mutex<false>&);
	explicit Synchronizer(Mutex<true>&);
	explicit Synchronizer(const Mutex<true>&);
	explicit Synchronizer(Semaphore&);
	explicit Synchronizer(const Semaphore&);
	
	~Synchronizer(void);
	
private:
	Synchronizer(void);
	Synchronizer(const Synchronizer&);
	Synchronizer& operator=(const Synchronizer&);

	SynchronizationObjectType type;
	void* syncronizationObject;
}; // Synchronizer

} // namespace concurrency

#endif//SYNCHRONIZATION_H