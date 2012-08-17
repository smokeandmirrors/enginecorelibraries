/**
ExtendedByLua.cpp 
Defines the entry point for the console application.
*/
#include <assert.h>
#include <stdio.h>
#include <tchar.h>

#include "Platform.h"
#include "Concurrency.h"

#if EXTENDED_BY_LUA
#pragma message("This executable is compiling with embedded lua.")
#include "LuaExtensionInclusions.h"
using namespace embeddedLua;
/** 
make sure all folders containing desired .lua files
relative to the working directory)
are included in the macro below
*/
#define LUA_PACKAGE_PATH_RUN_FROM_SOLUTION_DIR \
	"..\\LuaFiles\\?.lua;"  \
	"..\\LuaFiles\\UTLuaFiles\\?.lua;"
#endif//EXTENDED_BY_LUA

#if !GOLDMASTER
#define SANDBOX 1
#endif//GOLDMASTER

#if SANDBOX
#include "Sandbox.h" 
#include "Thread.h"
concurrency::Semaphore* allowable;

void theDoFunction(void)
{
	printf("My name is %10d I'm about to acquire!\n", concurrency::Thread::getThisID());
	allowable->acquire();
	printf("My name is %10d I'm doing the function!\n", concurrency::Thread::getThisID());
	concurrency::sleep(500);
	printf("My name is %10d I finished the function!\n", concurrency::Thread::getThisID());
	allowable->release();
}
#endif//SANDBOX

sint _tmain(sint /* argc */, _TCHAR* /* argv[] */)
{
	designPatterns::createSingletons();
	designPatterns::destroySingletons();

 	designPatterns::createSingletons();
#if SANDBOX
	sandbox::play();// just plays with C/C++ compile/runtime functionality
// 
// 
//  	uint numThreads = 15;
//  	uint numResources = 10;
// 	// concurrency::Semaphore onStack(numResources);
//  	// allowable = &onStack; 
// 	allowable = new concurrency::Semaphore(numResources);
//  	
//  	for (uint i = 0; i < numThreads; ++i)
//  	{
//  		concurrency::Executor* job = new concurrency::Executor(&theDoFunction);
//  		concurrency::Thread::getExecuting(*job); // threads delete themselves!
//  	}
//  
//  	concurrency::sleep(10000);
//   
//  	delete allowable;
#endif//SANDBOX	

#if EXTENDED_BY_LUA 
	{
		embeddedLua::Lua lua;
		lua.setPackagePath(LUA_PACKAGE_PATH_RUN_FROM_SOLUTION_DIR);
		registerGlobalLibrary(lua.getState());
		lua.require("Utilities");
		lua.require("ObjectOrientedParadigm");
		lua.require("User");
		lua.runConsole();
	}
#endif//EXTENDED_BY_LUA

	designPatterns::destroySingletons();
	return 0;
}

