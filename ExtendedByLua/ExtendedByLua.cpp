/**
ExtendedByLua.cpp 
Defines the entry point for the console application.
*/
#include <assert.h>
#include <stdio.h>
#include <tchar.h>

#include "Platform.h"

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
#endif//SANDBOX

sint _tmain(sint /* argc */, _TCHAR* /* argv[] */)
{
#if SANDBOX
	// sandbox::play();// just plays with C/C++ compile/runtime functionality
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
	return 0;
}

