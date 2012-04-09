#pragma once
#ifndef SINGLETON_H
#define SINGLETON_H
/**
\file Singleton.h

I am running out of love for the singleton pattern

Defines a template Singleton implementation, that simply provides
most of the Singleton requirements: initialization, accessor,
destruction, protected constructor/destructor.

\author Smoke and Mirrors Development
\htmlonly
<A HREF="smokeandmirrorsdevelopment@gmail.com">
smokeandmirrorsdevelopment@gmail.com</A>
<BR>
&copy;2009-2011 Smoke and Mirrors Development
<BR>
\endhtmlonly
\date 3/10/2011


\todo fix the initialization of all of this stuff.
1. create a macro which will create a class for that holds an initialization function
2. create one static instance of that static initializer class
3. its constructor will register itself in a list of singleton initialization functions
4. resource management of the singletons will be through that class only


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

namespace designPatterns
{

extern class SingletonInitializer* singletonInitializers;

class SingletonInitializer
{
public:
	virtual ~SingletonInitializer(void) {};
	virtual bool create(void) const=0;
	virtual void destroy(void) const=0;
	virtual bool isInitialized(void) const=0;
	SingletonInitializer* next;
}; // class SingletonInitializer

template<typename T>
class CustomSingletonInitializer : public SingletonInitializer
{
public:
	CustomSingletonInitializer()
	{
		next = singletonInitializers;
		singletonInitializers = this;
	}

	virtual bool create(void) const
	{
		return T::create();	
	}

	virtual void destroy(void) const
	{
		T::destroy();
	}

	virtual bool isInitialized(void) const
	{
		return T::single != NULL;
	}
}; // class CustomSingletonInitializer

void createSingletons();
void destroySingletons();

template<typename T>
class Singleton
{
	friend class CustomSingletonInitializer<T>;

public:
	/** 
	the single, static instance of T 
	\todo use the run time generation version, with a macro declared registration functions?
	*/
	static T* single;	
	
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

	static bool create(void)
	{
		single = T::createSingleton();
		return single != NULL;
	}

	static void destroy(void)
	{
		delete single;
		single = NULL;
	}

private:
	// not allowed
	Singleton(const Singleton&);
	Singleton operator=(const Singleton&);
	template<typename ANY> 
	Singleton operator=(const ANY&);
}; // class Singleton

// static initialization
// template<typename T> T* Singleton<T>::single(NULL); 
// template<typename T> CustomSingletonInitializer<T> Singleton<T>::initializer;
} // namespace designPatterns

#define DEFINE_SINGLETON_NS(BASE_CLASS, NAMESPACE) \
namespace designPatterns \
{ \
	template<> NAMESPACE::BASE_CLASS* Singleton<NAMESPACE::BASE_CLASS>::single(NULL); \
	static CustomSingletonInitializer<NAMESPACE::BASE_CLASS> BASE_CLASS##Initializer; \
} // namespace designPatterns

#define DEFINE_SINGLETON(BASE_CLASS) \
namespace designPatterns \
{ \
	template<> BASE_CLASS* Singleton<BASE_CLASS>::single(NULL); \
	static CustomSingletonInitializer<BASE_CLASS> BASE_CLASS##Initializer; \
} // namespace designPatterns


#endif//SINGLETON_H