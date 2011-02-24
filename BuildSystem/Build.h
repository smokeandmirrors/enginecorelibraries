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
*/
#include <assert.h>

/** preprocessor control for explicitly preventing code from compiling */
#define PREVENT_COMPILE switch(0){case 0:case 0:;}
/** conditional preprocessor control for explicitly preventing code from compiling */
#define PREVENT_COMPILE_IF(condition) switch(0){case 0: case condition:;}
/** preprocessor control for unit testing compilation */
#define WITH_UNIT_TESTING 1

/**
\defgroup Global typedefs 
Adhere to these to enable easier cross-platform development
@{
*/
// typedef bool				bool;
typedef signed char			schar;
typedef unsigned char		uchar;
typedef	wchar_t				wchar;
typedef signed short		sshort;
typedef unsigned short		ushort;
typedef signed int			sint;
typedef unsigned			uint;
typedef signed long			slong;
typedef unsigned long		ulong;
// typedef float				float;
// typedef double				double;
typedef long double			ldouble;
/**@}*/
#endif//BUILD_H
