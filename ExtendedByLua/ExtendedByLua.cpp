/**
ExtendedByLua.cpp 
Defines the entry point for the console application.
*/
#include <stdio.h>
#include <tchar.h>

#ifdef EXTENDED_BY_LUA //
#pragma message("This executable is compiling with embedded lua.")
#include "LuaExtensibility.h"
#include "Lua.h"
#include "LuaInclusions.h"
#include "LuaLibraryDeclarations.h"
#endif // EXTENDED_BY_LUA

// testing includes:
#include "CompilerChecks.h"
#include "Vector.h"
#include "TestClasses.h"

#include <UnitTest++.h>
/*
TEST(FailSpectacularly)
{
	CHECK(true);
}
TEST(SucceedReallyWell)
{
	CHECK(true);
}
*/

int _tmain(int /* argc */, _TCHAR* /* argv[] */)
{
	assert(!UnitTest::RunAllTests());
	Sandbox::Play();
#ifdef EXTENDED_BY_LUA /////
	Lua* lua = new Lua();
	lua->require("Utilities");
	lua->require("ObjectOrientedParadigm");
	// registration must be done in dependency order
	register_lua_library(lua, Vector2) 
	register_lua_library(lua, Vector3)
	register_lua_library(lua, Grandparent)
	register_lua_library(lua, Parent)
	register_lua_library(lua, Child)
	register_lua_library(lua, Basic);
	register_lua_library(lua, Derived);
	
	lua->require("Vector3PureLua");
	lua->require("User");
	
	lua->runConsole();
	delete lua;
#endif // EXTENDED_BY_LUA 

	return 0;
}

