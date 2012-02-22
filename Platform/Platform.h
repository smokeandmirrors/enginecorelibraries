#pragma once
#ifndef BUILD_H
#define BUILD_H 1
/**
\file Build.h 
Defines typdefs, macros for the foundation for programming in
and building this project.

This file should contain one of the few properties that reside in the 
global namespace.
It should really only contain fundamental typdefs and macros.

\author Smoke and Mirrors Development
\htmlonly
<A HREF="smokeandmirrorsdevelopment@gmail.com">
smokeandmirrorsdevelopment@gmail.com</A>
<BR>
&copy;2009-2011 Smoke and Mirrors Development
<BR>
\endhtmlonly
\date 1/20/2011

\todo NULL, assert, warn, error
\todo global bit packing investigation

<DEVELOPMENT STATUS>
Current Draft		:	0.0
Current Phase		:   DEVELOPMENT
Purpose				:	DEPLOYMENT
Unit Tested			:	NO
Used in development	:	YES
Used in experiments :	YES
Tested in the field	:	NO
*/
#include <assert.h>
#include <stdio.h>

#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

/** preprocessor control for conditionally preventing code from compiling */
#define COMPILE_IF(condition) switch(0){case 0: case condition:;}
/** preprocessor control for explicitly preventing code from compiling */
#define PREVENT_COMPILE switch(0){case 0:case 0:;}
/** preprocessor control for unit testing compilation */
#define WITH_UNIT_TESTING 1

#if DEBUG
#define IF_DEBUG(code) code 
#else
#define IF_DEBUG(code) 
#endif//DEBUG

#if RELEASE
#define IF_RELEASE(code) code 
#else
#define IF_RELEASE(code) 
#endif//RELEASE

#if GOLD_MASTER
#define IF_GOLD_MASTER(code) code 
#else
#define IF_GOLD_MASTER(code) 
#endif//GOLD_MASTER

#if !DEBUG
#define IF_NOT_DEBUG(code) code 
#else
#define IF_NOT_DEBUG(code) 
#endif//DEBUG

#if !RELEASE
#define IF_NOT_RELEASE(code) code 
#else
#define IF_NOT_RELEASE(code) 
#endif//RELEASE

#if !GOLD_MASTER
#define IF_NOT_GOLD_MASTER(code) code 
#else
#define IF_NOT_GOLD_MASTER(code) 
#endif//GOLD_MASTER


enum BoolEnum
{
	BoolEnum_False=0,
	BoolEnum_True,
	BoolEnum_Unset
}; // BoolEnum

/**
\defgroup Global typedefs 
Adhere to these to enable easier cross-platform development

\note I just finally heard from another programmer why this is done 
so often, and it is mostly related to serialization/communication
across platforms/networks/compilers/implementations

in ANY other situation, do NOT use the sized types, use the unsized types

@{
*/

/** un-sized types */
typedef char				schar;
typedef unsigned char		uchar;
typedef short				sshort;
typedef unsigned short		ushort;
typedef int					sint;
typedef unsigned int		uint;
typedef long long			slong;
typedef unsigned long long	ulong;
typedef float 				sreal;
typedef double				dreal;

/** sized types 
\todo investigate sized vs unsized types more, fill these in with compiler/OS specific types when a proven reason for it comes up:
probably going to be something over network/serialization/platform requirements

typedef char				schar;
typedef unsigned char		uchar;
typedef short				sshort;
typedef unsigned short		ushort;
typedef int					sint;
typedef unsigned int		uint;
typedef long long			slong;
typedef unsigned long long	ulong;
typedef float 				sreal;
typedef double				dreal;
*/

/**@}*/


template<typename T> 
class isLess
{
public:
	inline static bool evaluate(const T& a, const T& b) 
	{
		return a < b;
	}
	
	inline bool operator()(const T& a, const T& b) const
	{
		return evaluate(a, b);
	}
};

template<typename T> 
class isGreater
{
public:
	inline static bool evaluate(const T& a, const T& b) 
	{
		return a > b;
	}
	
	inline bool operator()(const T& a, const T& b) const
	{
		return evaluate(a, b);
	}
};

template<typename T>
class isEqual
{
public:
	inline static bool evaluate(const T& a, const T& b) 
	{
		return a == b;
	}
	
	inline bool operator()(const T& a, const T& b) const
	{
		return evaluate(a, b);
	}
};

#if DEFINE_CHECKED_CAST
template<class TO, class FROM>
TO* checked_cast(FROM* from)
{
	assert(static_cast<TO*>(from) == dynamic_cast<TO*>(from));
	return static_cast<TO*>(from);
}

template<class TO, class FROM>
TO& checked_cast(FROM& from)
{
	assert(static_cast<TO*>(&from) == dynamic_cast<TO*>(&from));
	return static_cast<TO&>(from);
}

template<class TO, class FROM>
const TO* checked_cast(const FROM* from)
{
	assert(static_cast<const TO*>(from) == dynamic_cast<const TO*>(from));
	return static_cast<const TO*>(from);
}

template<class TO, class FROM>
const TO& checked_cast(const FROM& from)
{
	assert(static_cast<const TO*>(&from) == dynamic_cast<const TO*>(&from));
	return static_cast<const TO&>(from);
}
#endif//DEFINE_CHECKED_CAST

#endif//BUILD_H
