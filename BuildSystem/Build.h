#pragma once
#ifndef BUILD_H
#define BUILD_H
/**
@brief Defines typdefs, macros for the foundation for programming in
and building this project.

This file should contain one of the few properties that reside in the 
global namespace.

It should really only contain fundamental typdefs and macros.

@file 
copyright 2011 Smoke and Mirrors Development
@author Smoke and Mirrors Development
smokeandmirrorsdevelopment@gmail.com
@date 1/20/2011
*/

/**
C/C++ types
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

// \todo number types, and NULL

#endif//BUILD_H
