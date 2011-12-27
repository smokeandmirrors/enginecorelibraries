#pragma once
#ifndef BUILD_H
#define BUILD_H
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
\todo a pass on forward declarations rather than includes, since I've just
forgotten about it, after working in UE3 for so long.
\todo find/create a decent set of containers
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

class String
{
	/// \todo get move this to the Strings.h file
public:
	static sint 
		compare(const schar* a, const schar* b)
	{
		int difference(*(unsigned char *)a - *(unsigned char *)b);
		
		while (!difference && *b)
		{
			++a, ++b;
			difference = *(unsigned char *)a - *(unsigned char *)b;
		}

		return difference;
	}

	static bool 
		isEqual(const schar* a, const schar* b)
	{
		return !compare(a, b);
	}
}; // String

#endif//BUILD_H
