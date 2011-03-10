#pragma once
#ifndef SINGLETON_H
#define SINGLETON_H

#include "Build.h"
#include "Synchronization.h"

namespace design_patterns
{

template<typename T>
class Singleton
{
public:
	/** get the only reference to the singleton */
	static T& single(void)
	{
		return (*getter)();
	} // static T& single(void)
	
	/** 
	destroy the only reference to the singleton 
	\warning use once only!
	*/
	static void destroy(void)
	{
		synchronize(mutex);

		if (singleton)
		{
			delete singleton;
			singleton = NULL;
			getter = getUninitialized;
			printf("SINGLETON DESTROYED!");
		}
	} // static void destroy(void)

protected:
	Singleton(void)
	{
		/* empty */
	} // Singleton(void)

	virtual ~Singleton(void) 
	{ 
		/* empty */ 
	} // virtual ~Singleton(void) 

private:
	static T& getInitialized(void)
	{
		return *singleton;
	} // static T& getInitialized(void)

	static T& getUninitialized(void)
	{
		synchronize(mutex);

		if (!singleton)
		{
			singleton = new T();
			getter = getInitialized;
		}

		return *singleton;
	} // static T& getUninitialized(void)

	static T& (*					getter)(void);
	static multithreading::Mutex*	mutex;
	static T*						singleton;
	
	Singleton(const Singleton&);
	Singleton operator=(const Singleton&);
}; // class Singleton

// static initialization
template<typename T> T& (*					Singleton<T>::getter)(void) (Singleton<T>::getUninitialized);
template<typename T> multithreading::Mutex*	Singleton<T>::mutex(multithreading::getMutex());
template<typename T> T*						Singleton<T>::singleton(NULL);

} // namespace design_patterns

#endif//SINGLETON_H