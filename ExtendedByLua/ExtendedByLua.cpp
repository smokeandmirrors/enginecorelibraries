/**
ExtendedByLua.cpp 
Defines the entry point for the console application.
*/
#include <assert.h>
#include <stdio.h>
#include <tchar.h>
#ifdef EXTENDED_BY_LUA
#pragma message("This executable is compiling with embedded lua.")
#include "Lua.h"
#include "LuaExtensibility.h"
#include "LuaInclusions.h"
#include "LuaLibraryDeclarations.h"
#endif//EXTENDED_BY_LUA

int _tmain(int /* argc */, _TCHAR* /* argv[] */)
{
#ifdef EXTENDED_BY_LUA 
	Lua* lua = new Lua();
	lua->require("Utilities");
	lua->require("ObjectOrientedParadigm");
	lua->require("User");
	lua->runConsole();
	delete lua;
#endif//EXTENDED_BY_LUA 

	return 0;
}

