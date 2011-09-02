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


struct AllPublic
{
	sint 
		one;
	bool 
		two;
	sreal 
		three;

	sint method(void) const { return 17; }
};

DECLARE_LUA_CLASS(AllPublic);

LUA_FUNC(AllPublic__index)
{
	const schar* k = to<const schar*>(L, -1);
	const AllPublic& t = to<const AllPublic&>(L, -2);

	if (!strcmp(k,"one")) return push(L, t.one);
	if (!strcmp(k,"two")) return push(L, t.two);
	if (!strcmp(k,"three")) return push(L, t.three);

	lua_getglobal(L, "getClass");	//s: getClass
	push(L, "AllPublic");			//s: getClass, "AllPublic"
	lua_call(L, 1, 1);				//s: AllPublic
	lua_getfield(L, -1, k);		//s: AllPublic[k]
	return 1;
}

LUA_FUNC(AllPublic__newindex)
{
	const schar* k = to<const schar*>(L, -2);
	AllPublic& t = to<AllPublic&>(L, -3);

	if (!strcmp(k,"one")) { t.one = to<sint>(L, -1); return 0; }
	if (!strcmp(k,"two")) { t.two = to<bool>(L, -1); return 0; }
	if (!strcmp(k,"three")) { t.three = to<sreal>(L, -1); return 0; }

	return luaL_error(L, "ERROR! nonassignable index %s for AllPublic", k);
}

// DEFINE_LUA_NO_INDEX_METHODS(CLASS, TYPE, SUPER_CLASS)
DEFINE_LUA_CLASS_PUSH_FUNCTION(AllPublic) 
	OPEN_LUA_NS(AllPublic) 
		DEFINE_LUA_CLASS_AUTO_METAMETHODS(AllPublic) 
		OPEN_LUA_LIB(AllPublic)
			// LUA_NAMED_ENTRY("construct", doNothing)
			LUA_ENTRY_CLASS__gc_DESTRUCTOR(AllPublic) 
			LUA_ENTRY_CLASS__isnewindexable_FALSE
			LUA_ENTRY_CLASS__new_AUTO(AllPublic) 
			LUA_ENTRY_CLASS__setmetatable_USERDATA 
			LUA_ENTRY_CLASS__tostring_AUTO(AllPublic)
			LUA_NAMED_ENTRY("__index", AllPublic__index)
			LUA_NAMED_ENTRY("__newindex", AllPublic__newindex)
			LUA_NAMED_ENTRY("method", (const_Return1Param0<AllPublic, sint, &AllPublic::method>))
END_LUA_CLASS(AllPublic, AllPublic)


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
		REGISTER_LUA_LIBRARY((&lua), AllPublic);

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

