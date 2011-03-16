#pragma once
#ifndef SYNCHRONIZATION_H
#define SYNCHRONIZATION_H

#define UNIQUE_AUX_2(sychronized,number)	sychronized##number
#define UNIQUE_AUX_1(sychronized,number)	UNIQUE_AUX_2(sychronized,number) 
#define UNIQUE_SYNCHRONIZATION(sychronized) UNIQUE_AUX_1(sychronized, __COUNTER__)

#define synchronize(mutex) multithreading::Synchronizer UNIQUE_SYNCHRONIZATION(sychronized)(mutex);
/**
\warning WORK IN-PROGRESS! 
\note EXPERIMENTAL!  NOT INTENDED FOR USE!
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