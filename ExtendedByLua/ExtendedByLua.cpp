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
using namespace lua_extension;
#endif//EXTENDED_BY_LUA

#if !GOLDMASTER
#define SANDBOX 1
#endif//!GOLDMASTER

#if SANDBOX
#include "Sandbox.h" 
#endif//SANDBOX

#include "Time.h"
#include "Vector.h"
/**
\todo, better support for Template class exports to %Lua
*/
template<typename T>
class Value 
#if EXTENDED_BY_LUA 
: public LuaExtendable
#endif//EXTENDED_BY_LUA 
{
public:
#if EXTENDED_BY_LUA
	INLINE_LUAEXTENDABLE_USERDATA_DEFAULT_FUNCTIONS(Value)
#endif//EXTENDED_BY_LUA
	T m_value;
	T getValue(void) const { return m_value; }
	void setValue(T value) { m_value = value; }
};

typedef Value<sint4> Value_sint4 ;

DECLARE_LUA_LIBRARY(Value_sint4);
DEFINE_TO_LUAEXTENDABLES(Value<sint4>);
DEFINE_LUA_LUAEXTENDABLE(Value_sint4, Value_sint4)
	LUA_NAMED_ENTRY("getValue", (return1Param0const<Value_sint4, sint4, &Value<sint4>::getValue>))  
	LUA_NAMED_ENTRY("setValue", (return0Param1<Value_sint4, sint4, &Value<sint4>::setValue>))
END_LUA_LUAEXTENDABLE(Value_sint4, Value_sint4) 

#if WIN32
#include <process.h>
#include <windows.h>
#endif//WIN32

sint4 _tmain(sint4 /* argc */, _TCHAR* /* argv[] */)
{
	real_time::initialize();

#if EXTENDED_BY_LUA 
	{
		lua_extension::Lua lua;
		registerGlobalLibrary(lua.getState());
		lua.require("Utilities");
		lua.require("ObjectOrientedParadigm");
		register_lua_library((&lua), Vector2);
		register_lua_library((&lua), Vector3);
		register_lua_library((&lua), Value_sint4);
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

