/**
ExtendedByLua.cpp 
Defines the entry point for the console application.
*/
#include <assert.h>
#include <stdio.h>
#include <tchar.h>

#if EXTENDED_BY_LUA
#pragma message("This executable is compiling with embedded lua.")
#include "LuaExtensionInclusions.h"
using namespace luaExtension;
#endif//EXTENDED_BY_LUA

#if !GOLDMASTER
#define SANDBOX 1
#endif//!GOLDMASTER

#if SANDBOX
#include "Sandbox.h" 
#endif//SANDBOX

#include "Vector.h"

sint _tmain(sint /* argc */, _TCHAR* /* argv[] */)
{
#if SANDBOX
	// just plays with C/C++ compile/runtime functionality
	Sandbox::play();
#endif//SANDBOX

#if EXTENDED_BY_LUA 
	{
		luaExtension::Lua lua;
		registerGlobalLibrary(lua.getState());
		lua.require("Utilities");
		lua.require("ObjectOrientedParadigm");
		register_lua_library((&lua), Vector2);
		register_lua_library((&lua), Vector3);
		// get the user file for easier rapid iteration
		lua.require("User");
		lua.runConsole();
	}
#endif//EXTENDED_BY_LUA

	return 0;
}

