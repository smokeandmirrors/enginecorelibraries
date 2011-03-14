#pragma once
#ifndef SINGLETON_H
#define SINGLETON_H
/**
\file Singleton.h

\author Smoke and Mirrors Development
\htmlonly
<A HREF="smokeandmirrorsdevelopment@gmail.com">
smokeandmirrorsdevelopment@gmail.com</A>
<BR>
&copy;2009-2011 Smoke and Mirrors Development
<BR>
\endhtmlonly
\date 3/10/2011
*/

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
	/** empty no args ctor */
	Singleton(void)
	{
		/* empty */
	} // Singleton(void)

	/** empty dtor */
	virtual ~Singleton(void) 
	{ 
		/* empty */ 
	} // virtual ~Singleton(void) 

private:
	/** returns the initialized, dereferenced pointer to the only T */
	static T& getInitialized(void)
	{
		return *singleton;
	} // static T& getInitialized(void)

	/** creates the only T and returns the the dereferenced pointer to it */
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

	/** a pointer to the current getter function */
	static T& (*					getter)(void);
	/** a mutex to guard the creation/destruction of the singleton */
	static multithreading::Mutex	mutex;
	/** the static pointer to the only instance of T */
	static T*						singleton;
	// not allowed
	Singleton(const Singleton&);
	Singleton operator=(const Singleton&);
}; // class Singleton

// static initialization
template<typename T> T& (*					Singleton<T>::getter)(void) (Singleton<T>::getUninitialized);
template<typename T> multithreading::Mutex	Singleton<T>::mutex; 
template<typename T> T*						Singleton<T>::singleton(NULL);

} // namespace design_patterns

#endif//SINGLETON_H