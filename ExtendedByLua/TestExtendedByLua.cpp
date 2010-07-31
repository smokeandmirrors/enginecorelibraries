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

namespace 
{

TEST(luaObjectCreationAndDestruction)
{
	Lua* lua = new Lua();
	CHECK(lua);
	delete lua;
	
	{
		Lua stack_lua;
		CHECK(stack_lua.getState());
	}
}

TEST(luaRequire)
{
	Lua* lua = new Lua();
	CHECK(lua->require("Utilities"));
	CHECK(lua->require("ObjectOrientedParadigm"));
	delete lua;
}

TEST(playingInTheSandBox)
{
	Sandbox::Play();
}

TEST(testingMain)
{
#ifdef EXTENDED_BY_LUA 
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
#endif//EXTENDED_BY_LUA 
}

} // namespace
#endif//GOLDMASTER