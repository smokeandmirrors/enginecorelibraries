#pragma once
#ifndef TESTCLASSES_H 
#define TESTCLASSES_H

#include "LuaExtensibility.h"

/**
@class

demonstrates full inheritance tree and proxy usesage
*/
class Grandparent 
#ifdef EXTENDED_BY_LUA ////
: public LuaExtendable
#endif//EXTENDED_BY_LUA
{
public:
	virtual ~Grandparent() {}
	const char*				getFamilyName(void) const { return "Curran"; }
	virtual const char*		getTitle(void) const { return "Grandparent"; }
	virtual const char*		toString(void);
	bool					operator==(const Grandparent& other) const;
#ifdef EXTENDED_BY_LUA////
	int						setMetatable(lua_State* L);
#endif//EXTENDED_BY_LUA
}; // Grandparent


/**
@class

demonstrates full inheritance tree and proxy usesage
*/
class Parent 
: public Grandparent
{
public:
	typedef Grandparent super;
	const char*				getGrandparentName(void) const { return "Robert Michael Curran, Sr."; }
	virtual const char*		getTitle(void) const { return "Parent"; }
}; // Parent

/**
@class

demonstrates full inheritance tree and proxy usesage
*/
class Child 
	: public Parent
{
public:
	typedef Parent super;
	const char*				getParentName(void) const { return "Robert Michael Curran, Jr."; }
	virtual const char*		getTitle(void) const { return "Child"; }
}; // Child


#ifdef EXTENDED_BY_LUA////
class Basic
: public LuaExtendable
{
public:
	typedef Basic super;
	virtual int					setMetatable(lua_State* L);
	virtual const char*			toString(void);
}; // Basic

declare_lua_library(Basic)

class Derived
: public Basic
{
public:
	typedef Basic super;
	virtual int					setMetatable(lua_State* L);
	virtual const char*			toString(void);
}; // Derived

declare_lua_library(Derived)
#endif//EXTENDED_BY_LUA

#endif//TESTCLASSES_H