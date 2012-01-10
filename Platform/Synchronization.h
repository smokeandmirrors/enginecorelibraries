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

#define UNIQUE_SYNCHRONIZATION_CONCAT(sychronized,number) \
	sychronized##number

#define UNIQUE_SYNCHRONIZATION_PREFIX(sychronized,number) \
	UNIQUE_SYNCHRONIZATION_CONCAT(sychronized,number) 

#define UNIQUE_SYNCHRONIZATION(sychronized) \
	UNIQUE_SYNCHRONIZATION_PREFIX(sychronized, __COUNTER__)

/** \todo thread policies */
#define DECLARE_MUTEX(identifier) \
	concurrency::Mutex			identifier;

#define DECLARE_MUTABLE_MUTEX(identifier) \
	mutable concurrency::Mutex	identifier;

#define DECLARE_STATIC_MUTEX(identifier) \
	static concurrency::Mutex	identifier;

#define DEFINE_STATIC_MUTEX(SCOPE, INDENTIFIER) \
	concurrency::Mutex SCOPE##::##INDENTIFIER;

#define SYNC(mutex) \
	concurrency::Synchronizer	UNIQUE_SYNCHRONIZATION(sychronized)(mutex);

namespace concurrency
{

class PlatformMutex;

class Mutex 
{
public:
	Mutex(void);
	~Mutex(void);
	void acquire(void);
	void release(void);

protected:
	PlatformMutex* m_mutex;
}; // class Mutex

class Synchronizer
{
public:
	Synchronizer(Mutex& mutex) 
	: m_mutex(mutex)
	{
		m_mutex.acquire();
	}

	Synchronizer(const Mutex& mutex)
	: m_mutex(const_cast<Mutex&>(mutex))
	{
		m_mutex.acquire();
	}
	
	~Synchronizer(void)
	{
		m_mutex.release();
	}

private:
	Synchronizer(void);
	Synchronizer(const Synchronizer&);
	Synchronizer& operator=(const Synchronizer&);

	Mutex& m_mutex;
}; // class Synchronizer

} // namespace concurrency

#endif//SYNCHRONIZATION_H