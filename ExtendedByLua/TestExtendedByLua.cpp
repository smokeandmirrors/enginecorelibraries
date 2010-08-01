#ifndef GOLDMASTER
#include "CompilerChecks.h"
#ifdef EXTENDED_BY_LUA
#include "Lua.h"
#include "LuaExtensibility.h"
#include "LuaInclusions.h"
#include "LuaLibraryDeclarations.h"
#endif//EXTENDED_BY_LUA
#include "TestClasses.h"
#include "Vector.h"
#include <UnitTest++.h>

SUITE(ExtendedByLuaTesting)
{
	TEST(playingInTheSandBox)
	{
		Sandbox::Play();
	}

#ifdef EXTENDED_BY_LUA 
	TEST(testingMain)
	{
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
		delete lua;
	}
#endif//EXTENDED_BY_LUA 
} // SUITE(ExtendedByLuaTesting)
#endif//GOLDMASTER