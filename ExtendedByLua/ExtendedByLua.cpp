/**
ExtendedByLua.cpp 
Defines the entry point for the console application.
*/
#include <assert.h>
#include <stdio.h>
#include <tchar.h>

#include "LuaMathExtensions.h"

#if EXTENDED_BY_LUA
#pragma message("This executable is compiling with embedded lua.")
#include "LuaExtensionInclusions.h"
using namespace lua_extension;
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
#endif//!GOLDMASTER

#if SANDBOX
#include "Sandbox.h" 
#endif//SANDBOX

#include "Time.h"
#include "Vector.h"

#if WIN32
#include <process.h>
#include <windows.h>
#endif//WIN32

#define UNIT_TEST_VERIFICATION 0

#if UNIT_TEST_VERIFICATION

#endif//UNIT_TEST_VERIFICATION

sint _tmain(sint /* argc */, _TCHAR* /* argv[] */)
{
	real_time::initialize();

#if EXTENDED_BY_LUA 
	{
		lua_extension::Lua lua;
		lua.setPackagePath(LUA_PACKAGE_PATH_RUN_FROM_SOLUTION_DIR);
		registerGlobalLibrary(lua.getState());
		lua.require("Utilities");
		lua.require("ObjectOrientedParadigm");
		REGISTER_LUA_LIBRARY((&lua), Vector2);
		REGISTER_LUA_LIBRARY((&lua), Vector3);

#if UNIT_TEST_VERIFICATION
		REGISTER_LUA_LIBRARY((&lua), Grandparent2);
		REGISTER_LUA_LIBRARY((&lua), Parent2);
		REGISTER_LUA_LIBRARY((&lua), Child2);
#endif // UNIT_TEST_VERIFICATION

		// get the user file for easier rapid iteration
		lua.require("User");
		lua.runConsole();
	}
#endif//EXTENDED_BY_LUA
	
#if SANDBOX
	sandbox::play();// just plays with C/C++ compile/runtime functionality
#endif//SANDBOX	
	return 0;
}

