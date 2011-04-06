#pragma once
#ifndef SYNCHRONIZATION_H
#define SYNCHRONIZATION_H

#define UNIQUE_AUX_2(sychronized,number)	sychronized##number
#define UNIQUE_AUX_1(sychronized,number)	UNIQUE_AUX_2(sychronized,number) 
#define UNIQUE_SYNCHRONIZATION(sychronized) UNIQUE_AUX_1(sychronized, __COUNTER__)

/** \todo thread policies */
#define SYNC(mutex) multithreading::Synchronizer UNIQUE_SYNCHRONIZATION(sychronized)(mutex);
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
namespace multithreading
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

} // namespace multithreading

#endif//SYNCHRONIZATION_H