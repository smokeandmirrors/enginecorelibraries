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

<DEVELOPMENT STATUS>
Current Draft		:	0.0
Current Phase		:   DEVELOPMENT
Purpose				:	DEPLOYMENT
Unit Tested			:	NO
Used in development	:	NO
Used in experiments :	YES
Tested in the field	:	NO
*/

namespace designPatterns
{

extern class SingletonController* singletonInitializers;

class SingletonController
{
public:
	virtual ~SingletonController(void) {};
	virtual bool create(void) const=0;
	virtual void destroy(void) const=0;
	virtual bool isInitialized(void) const=0;
	SingletonController* next;
}; // class SingletonController

template<typename SINGLETON>
class CustomSingletonController : public SingletonController
{
public:
	CustomSingletonController()
	{
		next = singletonInitializers;
		singletonInitializers = this;
	}

	virtual bool create(void) const
	{
		return SINGLETON::create();	
	}

	virtual void destroy(void) const
	{
		SINGLETON::destroy();
	}

	virtual bool isInitialized(void) const
	{
		return SINGLETON::isInitialized();
	}
}; // class CustomSingletonController

void createSingletons();
void destroySingletons();

template<typename T>
class Singleton
{
	friend class CustomSingletonController<T>;

public:
	static inline T& single(void) 
	{ 
		return *singleton; 
	}

	static inline bool isInitialized(void) 
	{
		return singleton != NULL;
	}	

protected:
	/** empty no args ctor */
	Singleton(void)
	{
		/* empty */
	} // Singleton(void)

	static bool create(void)
	{
		singleton = T::createSingleton();
		return singleton != NULL;
	}

	static void destroy(void)
	{
		delete singleton;
		singleton = NULL;
	}

private:
	// not allowed
	Singleton(const Singleton&);
	Singleton operator=(const Singleton&);
	template<typename ANY> 
	Singleton operator=(const ANY&);

	/** 
	the single, static instance of T 
	*/
	static T* singleton;
}; // class Singleton

} // namespace designPatterns

// for template singletons, typedef the name first

#define DEFINE_SINGLETON_NS(BASE_CLASS, NAMESPACE) \
namespace designPatterns \
{ \
	template<> NAMESPACE::BASE_CLASS* Singleton<NAMESPACE::BASE_CLASS>::singleton(NULL); \
	static CustomSingletonController<NAMESPACE::BASE_CLASS> BASE_CLASS##Initializer; \
} // namespace designPatterns

#define DEFINE_SINGLETON(BASE_CLASS) \
namespace designPatterns \
{ \
	template<> BASE_CLASS* Singleton<BASE_CLASS>::singleton(NULL); \
	static CustomSingletonController<BASE_CLASS> BASE_CLASS##Initializer; \
} // namespace designPatterns


#endif//SINGLETON_H