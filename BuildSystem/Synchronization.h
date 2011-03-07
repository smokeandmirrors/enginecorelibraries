#pragma once
#ifndef SYNCHRONIZATION_H
#define SYNCHRONIZATION_H

#define UNIQUE_AUX_2(sychronized,number)	sychronized##number
#define UNIQUE_AUX_1(sychronized,number)	UNIQUE_AUX_2(sychronized,number) 
#define UNIQUE_SYNCHRONIZATION(sychronized) UNIQUE_AUX_1(sychronized, __COUNTER__)

#define synchronize(mutex) multithreading::Synchronizer UNIQUE_SYNCHRONIZATION(sychronized)(mutex);

namespace multithreading
{

class Mutex;

class Synchronizer
{
public:
	Synchronizer(Mutex* mutex);
	Synchronizer(const Mutex* mutex);
	~Synchronizer(void);

private:
	Synchronizer(void);
	Synchronizer(const Synchronizer&);
	Synchronizer& operator=(const Synchronizer&);

	Mutex* m_mutex;
}; // class Synchronizer

Mutex*	getMutex(void);
void	returnMutex(Mutex* mutex);

} // namespace multithreading

#endif//SYNCHRONIZATION_H