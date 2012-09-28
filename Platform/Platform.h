#pragma once
#ifndef BUILD_H
#define BUILD_H 1
/**
\file Platform.h 
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
\todo split off base types, macros, all that stuff, and just include them all in a strict order

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

#define FOREVER for (;;) 

#define BREAKPOINT(ID) __debugbreak();

#define OFFSET_OF(CLASS,MEMBER) int( reinterpret_cast<unsigned long long>( &(reinterpret_cast<CLASS*>(16)->MEMBER) ) - 16 )


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

template<typename FLAGS, typename STORAGE>
class Flags
{
public:
	
	inline Flags(const Flags& f) : flags(f.flags) { /* empty */ }
	
	inline Flags(const STORAGE mask=0) : flags(mask) { /* empty */ }
	
	inline STORAGE isLowered(const STORAGE mask) const { return !(flags & mask); }
	
	inline STORAGE isRaised(const STORAGE mask) const { return flags & mask; }
	
	inline void	lower(const STORAGE mask) { flags &= (~mask); }
	
	inline void	lowerAll(void) { flags = 0; }
	
	inline Flags& operator=(const Flags& f) { flags = f.flags; return *this; }
	
	inline STORAGE operator==(const Flags& f) const { return flags == f.flags; }
	
	inline STORAGE operator!=(const Flags& f) const { return flags ^ f.flags; }

	inline STORAGE operator|(const Flags& f) const { return flags | f.flags; }
	
	inline STORAGE operator()(void) const { return flags; }
	
	inline void raiseAll(void) { flags = 0; flags = ~flags; }
	
	inline void raise(const STORAGE mask) { flags |= mask; }
	
	inline void	set(const STORAGE mask) { flags = mask; }
	
private:
	STORAGE flags;
};

template<typename T>
static void deleteObject(T* object)
{
	delete object;
}

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
