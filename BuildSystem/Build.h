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

\todo 32/64-bit number types, NULL, assert, warn, error

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

/**
\defgroup Global typedefs 
Adhere to these to enable easier cross-platform development
@{
*/

/** integral types */
typedef char				sint1;
typedef unsigned char		uint1;
typedef short				sint2;
typedef unsigned short		uint2;
typedef int					sint4;
typedef unsigned int		uint4;
typedef long long			sint8;
typedef unsigned long long	uint8;

/** floating point types */
typedef float 				real4;
typedef double				real8;

/**@}*/
#endif//BUILD_H
