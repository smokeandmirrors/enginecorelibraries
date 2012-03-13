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

#include "Platform.h"

namespace designPatterns
{

template<typename T>
class Singleton
{
public:
	/** 
	the single, static instance of T 
	
	\todo I never see this implementation.  I understand the reasoning behind
	the lazy evaluation methods, buy (at least in C++) they bring up all kinds of 
	problems.  I thought the problems with a single static instance would
	be related to multiple instantiation in different libraries or compilation units,
	but so far, I can't substantiate that either.

	Or was it initialization of start up statics...?

	*/
	static T single;
	
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
	// not allowed
	Singleton(const Singleton&);
	
	Singleton 
		operator=(const Singleton&);
	
	template<typename ANY> 
	Singleton 
		operator=(const ANY&);
}; // class Singleton
// static initialization
template<typename T> T Singleton<T>::single; 
} // namespace designPatterns

#endif//SINGLETON_H