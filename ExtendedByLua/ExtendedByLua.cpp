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
/**
@class
demonstrates full inheritance tree and proxy useage
*/
class Grandparent 
	: public LuaExtendable
{
public:
	typedef Grandparent super;

	Grandparent(const char* name=NULL) 
		: m_name(name) 
	{ /* empty */ }

	virtual ~Grandparent(void) 
	{ /* empty */ }

	const char* getFamilyName(void) const 
	{ 
		return "Curran"; 
	}

	virtual const char* getTitle(void) const 
	{ 
		return "Grandparent"; 
	}

	bool operator==(const Grandparent& other) const
	{
		// return strcmp(getFamilyName(), other.getFamilyName()) == 0; 
		return this == &other; 
	}

	sint setMetatable(lua_State* L)
	{
		return setProxyMetatable(L);
	}

	virtual const char*	toString(void)
	{ 
		return "This is a Grandparent"; 
	}

protected:
	const char*				m_name;
}; // Grandparent

declare_lua_LuaExtendable(Grandparent);

lua_func(__call)
{
	Grandparent& gp = to<Grandparent&>(L, -1);
	printToLua(L, gp.toString());
	return 0;
}

define_lua_LuaExtendable_by_proxy(Grandparent, Grandparent)
	lua_entry(__call) 
	lua_named_entry("getFamilyName",	(return1Param0const<Grandparent, const char*, &Grandparent::getFamilyName>))
	lua_named_entry("getTitle",			(return1Param0const<Grandparent, const char*, &Grandparent::getTitle>))
	lua_named_entry("__eq",				(return1Param1const<Grandparent, bool, const Grandparent&, &Grandparent::operator==>))
end_lua_LuaExtendable_by_proxy(Grandparent, Grandparent)

/**
@class

demonstrates full inheritance tree and proxy usesage
*/
class Parent 
	: public Grandparent
{
public:
	typedef Grandparent super;
	Parent(Grandparent* gp=NULL) : m_grandParent(gp)		{ /* empty */ }
	Grandparent*			getGrandparent(void) const		{ return m_grandParent; }
	const char*				getGrandparentName(void) const	{ return "Robert Michael Curran, Sr."; }
	virtual const char*		getTitle(void) const			{ return "Parent"; }

private:
	Grandparent*			m_grandParent;			
}; // Parent

declare_lua_LuaExtendable(Parent);

define_lua_LuaExtendable_by_proxy(Parent, Grandparent)
	lua_named_entry("getGrandparent",		(return1Param0const<Parent, Grandparent*, &Parent::getGrandparent>))
	lua_named_entry("getGrandparentName",	(return1Param0const<Parent, const char*, &Parent::getGrandparentName>))
end_lua_LuaExtendable_by_proxy(Parent, Grandparent) 

/**
@class

demonstrates full inheritance tree and proxy usesage
*/
class Child 
	: public Parent
{
public:
	typedef Parent super;

	Parent*					getParent(void) const		{ return m_parent; }
	const char*				getParentName(void) const	{ return "Robert Michael Curran, Jr."; }
	virtual const char*		getTitle(void) const		{ return "Child"; }

private:
	Child*					m_parent;
}; // Child

declare_lua_LuaExtendable(Child);

define_lua_LuaExtendable_by_proxy(Child, Parent)
	lua_named_entry("getParent",		(return1Param0const<Child, Parent*, &Child::getParent>))
	lua_named_entry("getParentName",	(return1Param0const<Child, const char*, &Child::getParentName>))
end_lua_LuaExtendable_by_proxy(Child, Parent)

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
	register_lua_library((&lua), Grandparent);
	register_lua_library((&lua), Parent);
	register_lua_library((&lua), Child);
	// performance testing
	// lua.require("Vector3PureLua");
	// get the user file for easier rapid iteration
	lua.require("User");
	lua.runConsole();
#endif//EXTENDED_BY_LUA
	return 0;
}

