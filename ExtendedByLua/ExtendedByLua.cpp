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

using namespace LuaExtension;

class Basic
	: public LuaExtension::LuaExtendable
{
public:
	typedef Basic super;

	int getValue(void) const 
	{ 
		return value; 
	}

	virtual int setMetatable(lua_State* L)
	{
		return LuaExtension::setDefaultMetatableProxy(L);
	}

	virtual const char* toString(void)
	{
		return "This is a Basic.";
	}

	int setValue(int new_value) 
	{ 
		value = new_value; 
	}

private:
	int value;
}; // Basic

declare_lua_extendable(Basic)

lua_func(newBasic)
{
	pushRegisteredClass(L, new Basic());	//s: ud
	lua_newtable(L);						//s: ud, ud_mt
	lua_getglobal(L, "Basic");				//s: ud, ud_mt, Basic
	lua_setfield(L, -2, "__index");			//s: ud, ud_mt
	lua_setmetatable(L, -2);				//s: ud/mt
	return 1;
}

lua_func(getBasic)
{
	static Basic* b(NULL);

	if (!b)
	{
		b = new Basic();
		pushRegisteredClass(L,b);				//s: ud
		lua_newtable(L);						//s: ud, ud_mt
		lua_getglobal(L, "Basic");				//s: ud, ud_mt, Basic
		lua_setfield(L, -2, "__index");			//s: ud, ud_mt
		lua_setmetatable(L, -2);				//s: ud/mt
	}
	else
	{
		pushRegisteredClass(L,b);	//s: ud
	}

	return 1;
}

lua_func(basicFromC)
{
	lua_pushstring(L, "This function came from C!");
	return 1;
}

define_lua_class(Basic, Basic)
lua_named_entry("new", newBasic)
lua_named_entry("get", getBasic)
lua_named_entry("fromC", basicFromC)
lua_named_entry("getValue", (return1Param0const<Basic, int, &Basic::getValue>))
end_lua_class(Basic, Basic)


#endif//EXTENDED_BY_LUA

#if !GOLDMASTER
#define SANDBOX 1
#endif//!GOLDMASTER

#if SANDBOX
#include "Sandbox.h" 
#endif//SANDBOX

int _tmain(int /* argc */, _TCHAR* /* argv[] */)
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
	register_lua_library((&lua), Basic);
	// performance testing
	lua.require("Vector3PureLua");
	// get the user file for easier rapid iteration
	lua.require("User");
	lua.runConsole();
#endif//EXTENDED_BY_LUA
	return 0;
}

