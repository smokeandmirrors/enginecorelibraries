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

#include "Platform.h"

#define UNIQUE_SYNCHRONIZATION_CONCAT(SYNCHRONIZED, NUMBER) \
	SYNCHRONIZED##NUMBER

#define UNIQUE_SYNCHRONIZATION_PREFIX(SYNCHRONIZED, NUMBER) \
	UNIQUE_SYNCHRONIZATION_CONCAT(SYNCHRONIZED, NUMBER) 

#define UNIQUE_SYNCHRONIZATION(SYNCHRONIZED) \
	UNIQUE_SYNCHRONIZATION_PREFIX(SYNCHRONIZED, __COUNTER__)

/** \todo thread policies: at least at the pre-processor level, if single threaded, all of these macros should be defined to an empty statement */
#define DECLARE_MUTEX(INDENTIFIER) \
	concurrency::Mutex INDENTIFIER;

#define DECLARE_MUTABLE_MUTEX(INDENTIFIER) \
	mutable concurrency::Mutex INDENTIFIER;

#define DECLARE_STATIC_MUTEX(INDENTIFIER) \
	static concurrency::Mutex INDENTIFIER;

#define DEFINE_STATIC_MUTEX(SCOPE, INDENTIFIER) \
	concurrency::Mutex SCOPE##::##INDENTIFIER;

#define SET_THREAD_SPIN_COUNT(MUTEX, SPIN_COUNT) \
	MUTEX.setSpinCount(SPIN_COUNT);


#define SYNC(MUTEX) \
	concurrency::SynchronizerMutex	UNIQUE_SYNCHRONIZATION(SYNCHRONIZED)(MUTEX);

namespace concurrency
{

class Mutex 
{
public:
	Mutex(void);
	~Mutex(void);
	void acquire(void);
	void release(void);
	void setSpinCount(uint spinCount);

protected:
	class PlatformMutex* mutex;
}; // class Mutex

class Semaphore
{
public:
	Semaphore(uint count=2);
	~Semaphore(void);
	void acquire(void);
	void release(void);

protected:
	class PlatformSemaphore* semaphore;
}; // class Semaphore

class SynchronizerMutex
{
public:
	SynchronizerMutex(Mutex& m) 
	: mutex(m)
	{
		mutex.acquire();
	}

	SynchronizerMutex(const Mutex& m)
	: mutex(const_cast<Mutex&>(m))
	{
		mutex.acquire();
	}
	
	~SynchronizerMutex(void)
	{
		mutex.release();
	}

private:
	SynchronizerMutex(void);
	SynchronizerMutex(const SynchronizerMutex&);
	SynchronizerMutex& operator=(const SynchronizerMutex&);

	Mutex& mutex;
}; // class SynchronizerMutex

class SynchronizerSemaphore
{
public:
	SynchronizerSemaphore(Semaphore& s) 
	: semaphore(s)
	{
		semaphore.acquire();
	}

	SynchronizerSemaphore(const Semaphore& s)
	: semaphore(const_cast<Semaphore&>(s))
	{
		semaphore.acquire();
	}

	~SynchronizerSemaphore(void)
	{
		semaphore.release();
	}

private:
	SynchronizerSemaphore(void);
	SynchronizerSemaphore(const SynchronizerSemaphore&);
	SynchronizerSemaphore& operator=(const SynchronizerSemaphore&);

	Semaphore& semaphore;
}; // class SynchronizerSemaphore

} // namespace concurrency

#endif//SYNCHRONIZATION_H