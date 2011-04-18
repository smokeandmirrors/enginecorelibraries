#pragma once
#ifndef MULTITHREADING_H
#define MULTITHREADING_H

#include "Build.h"
#include "Time.h"

/**
<DEVELOPMENT STATUS>
Current Draft		:	0.0
Current Phase		:   DEVELOPMENT
Purpose				:	DEPLOYMENT
Unit Tested			:	NO
Used in development	:	NO
Used in experiments :	YES
Tested in the field	:	NO
*/
namespace multithreading
{
#if WIN32
#define ARGS_EXECUTABLE_FUNCTION(name) uint4 __stdcall name(void* args)
#define NOARGS_EXECUTABLE_FUNCTION(name) uint4 __stdcall name(void*)
#else
	PREVENT_COMPILE
#endif//WIN32

#define DECLARE_NOARGS_EXECUTABLE_FUNCTION(name) NOARGS_EXECUTABLE_FUNCTION(name);
#define DEFINE_NOARGS_EXECUTABLE_FUNCTION(name, code) NOARGS_EXECUTABLE_FUNCTION(name) \
	{ \
		code \
		return 0; \
	}

#define DECLARE_ARGS_EXECUTABLE_FUNCTION(name) ARGS_EXECUTABLE_FUNCTION(name);
#define DEFINE_ARGS_EXECUTABLE_FUNCTION(name, code) ARGS_EXECUTABLE_FUNCTION(name) \
	{ \
		code \
		return 0; \
	}

typedef void(* executableFunction)(void);

extern const sint4 noThreadPreference; 

void sleep(millisecond milliseconds);

class Executable 
{
public:
	virtual	~Executable(void)=0 {/* empty */}
	virtual void execute(void)=0;
}; // class Executable

}//namespace multithreading

#endif//MULTITHREADING_H