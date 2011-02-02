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

using namespace LuaExtension;


class Simple
	: public LuaExtendable
{
private:
	static bool everCreated;
	static uint numAllocated;

public:
	Simple(void)
	{
		everCreated = true;
		numAllocated++;
	}

	virtual ~Simple(void)
	{
		numAllocated--;
	}

	static uint getNumAllocated(void)	{ return numAllocated; }
	static bool wasEverCreated(void)	{ return everCreated; }

public:
	Simple*			getOther(void) const		{ return m_other; }
	virtual uint	getValue(void) const		{ return 7; }
	bool			isSimple(void) const		{ return true; }
	Simple*			reproduce() const			{ return new Simple(); }

	sint setMetatable(lua_State* L)
	{
		return setUserdataMetatable(L);
	}

	void setOther(Simple* other) 
	{ 
		m_other = other; 
	}

	virtual const char* toString(void)
	{ 
		return "Simple"; 
	}

private:
	Simple*			m_other;
};

uint Simple::numAllocated = 0;
bool Simple::everCreated = false;


inline sint push(lua_State* L, Simple* value)
{	
	pushRegisteredClass(L, value);		//s: ud
	lua_getglobal(L, "getmetatable");	//s: ud, getmetatable	
	lua_pushvalue(L, -2);				//s: ud, getmetatable, ud
	lua_call(L, 1, 1);					//s: ud, getmetatable, ?

	if (lua_istable(L, -1))
	{									//s: ud, mt
		lua_pop(L, 1);					//s: ud
	}
	else
	{												//s: ud, nil	
		assert(lua_isnil(L, -1));
		lua_pop(L, 1);								//s: ud
		assert(lua_isuserdata(L, -1));			
		lua_getglobal(L, "ObjectOrientedParadigm"); //s: ud, OOP
		assert(lua_istable(L, -1));			
		assert(lua_isuserdata(L, -2));			
		lua_getfield(L, -1, "initializers_PRIVATE");//s: ud, OOP, initializers
		lua_replace(L, -2);							//s: ud, initializers
		assert(lua_istable(L, -1));			
		assert(lua_isuserdata(L, -2));			
		lua_getfield(L, -1, "Simple");				//s: ud, initializers, simple()
		lua_replace(L, -2);							//s: ud, simple()
		assert(lua_isfunction(L, -1));			
		assert(lua_isuserdata(L, -2));			
		lua_pushvalue(L, -2);						//s: ud, simple(), ud
		assert(lua_isuserdata(L, -1));			
		assert(lua_isuserdata(L, -3));			
		lua_call(L, 1, 0);							//s: ud
	}

	return 1;
}

declare_lua_LuaExtendable(Simple);

define_lua_LuaExtendable(Simple, Simple)
lua_named_entry("__call", (return1Param0const<Simple, uint, &Simple::getValue>))
lua_named_entry("getOther", (return1Param0const<Simple, Simple*, &Simple::getOther>))
lua_named_entry("getValue", (return1Param0const<Simple, uint, &Simple::getValue>))
lua_named_entry("isSimple", (return1Param0const<Simple, bool, &Simple::isSimple>))
lua_named_entry("reproduce", (return1Param0const<Simple, Simple*, &Simple::reproduce>))
lua_named_entry("setOther", (return0Param1<Simple, Simple*, &Simple::setOther>))
end_lua_LuaExtendable(Simple, Simple)


class Derived
	: public Simple
{
private:
	static bool everCreated;
	static uint numAllocated;

public:
	Derived(void)
	{
		everCreated = true;
		numAllocated++;
	}

	virtual ~Derived(void)
	{
		numAllocated--;
	}

	static uint getNumAllocated(void)		{ return numAllocated; }
	static bool wasEverCreated(void)		{ return everCreated; }

public:
	uint				getDerivation(void) const	{ return 21; }
	virtual uint		getValue(void) const		{ return 14; }
	virtual const char* toString(void)
	{ 
		return "Derived"; 
	}
};

uint Derived::numAllocated = 0;
bool Derived::everCreated = false;

declare_lua_LuaExtendable(Derived);

define_lua_LuaExtendable(Derived, Simple)
lua_named_entry("getDerivation", (return1Param0const<Derived, uint, &Derived::getDerivation>))
end_lua_LuaExtendable(Derived, Simple)

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

#ifdef EXTENDED_BY_LUA 
	{
		LuaExtension::Lua lua;
		assert(lua.require("Utilities"));
		lua.require("ObjectOrientedParadigm");
		register_lua_library((&lua), Vector2);
		register_lua_library((&lua), Vector3);
		register_lua_library((&lua), Simple);
		register_lua_library((&lua), Derived);
		// get the user file for easier rapid iteration
		lua.require("User");
		lua.runConsole();
	}
#endif//EXTENDED_BY_LUA
	return 0;
}

