/**
ExtendedByLua.cpp 
Defines the entry point for the console application.
*/
#include <assert.h>
#include <stdio.h>
#include <tchar.h>

#if EXTENDED_BY_LUA
#pragma message("This executable is compiling with embedded lua.")
#include "Lua.h"
#include "LuaStateInteraction.h"
#include "LuaExtensibility.h"
#include "LuaInclusions.h"
#include "LuaLibraryDeclarations.h"
#endif//EXTENDED_BY_LUA

#if !GOLDMASTER
#define SANDBOX 1
#endif//!GOLDMASTER

#if SANDBOX
#include "Sandbox.h" 
#endif//SANDBOX

sint _tmain(sint /* argc */, _TCHAR* /* argv[] */)
{
#if SANDBOX
	// just plays with C/C++ compile/runtime functionality
	Sandbox::play();
#endif//SANDBOX

#ifdef EXTENDED_BY_LUA 
	LuaExtension::Lua lua;
	assert(lua.require("Utilities"));
	lua.require("ObjectOrientedParadigm");
	// registration must be done in dependency order
	register_lua_library((&lua), Vector2); 
	register_lua_library((&lua), Vector3);
	// performance testing
	// lua.require("Vector3PureLua");
	// get the user file for easier rapid iteration
	lua.require("User");
	lua.runConsole();
#endif//EXTENDED_BY_LUA
	return 0;
}

