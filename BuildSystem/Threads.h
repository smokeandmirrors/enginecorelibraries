#pragma once
#ifndef THREADS_H
#define THREADS_H

#include "Build.h"

namespace multithreading
{
#if WIN32
#define ARGS_EXECUTABLE_FUNCTION(name) uint __stdcall name(void* args)
#define NOARGS_EXECUTABLE_FUNCTION(name) uint __stdcall name(void*)
#endif// WIN32

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

class Executable 
{
public:
	virtual	~Executable(void) {/* empty */}
	virtual void execute(void)=0;
}; // class Executable

} // multithreading

#endif//THREADS_H