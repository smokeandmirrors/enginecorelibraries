#pragma once
#ifndef LUASTATEINTERACTION_H
#define LUASTATEINTERACTION_H
/**
LuaStateInteraction.h

This file defines function helpers akin to lua_to<type> and
lua_push<type> to assist in easily extending interaction with
the %Lua state to include custom types.

\copyright 2010 Smoke and Mirrors Development
\author Smoke and Mirrors Development
smokeandmirrorsdevelopment@gmail.com
\date 8/21/2010
*/

#include "LuaExtensibility.h"
#include "LuaInclusions.h"
#include "Vector.h"

#if !GOLDMASTER
#define ARGUMENT_ERRORS 1
#endif//!GOLDMASTER

namespace LuaExtension 
{ 
#if ARGUMENT_ERRORS
#pragma message("Compiling with Lua stack argument type checking.")
/**
This is a define macro and not an inline function due to the 
average lua_istype function being a macro
*/
#define CHECK_ARG(lua_istype, type_name, L, index) \
	{ \
		if (index > lua_gettop(L) || index < -lua_gettop(L)) \
		{ \
			luaL_error(L, "argument type error! argument # %d not found", index); \
		} \
		if (!lua_istype(L, index)) \
		{ \
			luaL_error(L, "argument type error! #: %d expected: %s actual: %s ", index, type_name, luaL_typename(L, index)); \
		} \
	}
#else
#define CHECK_ARG(lua_istype, type_name, L, index) {}
#endif//ARGUMENT_ERRORS

template<typename T> class Differentiator {/* empty */};

/**
to<T> functions
returns an object from the specified index in the %Lua stack
*/
template<typename T> T to(lua_State* L, int index)
{	
	return static_cast<T>(to(Differentiator<T>(), L, index));
}

//inline bool to(lua_State* L, int index, Differentiator<bool>&)
//{
//	CHECK_ARG(lua_isboolean, "boolean", L, index);
//	return lua_toboolean(L, index) != 0;
//}
//
//inline int to(lua_State* L, int index, Differentiator<int>&)
//{
//	CHECK_ARG(lua_isnumber, "number", L, index);
//	return static_cast<int>(lua_tonumber(L, index));
//}
//
//inline float to(lua_State* L, int index, Differentiator<float>&)
//{
//	CHECK_ARG(lua_isnumber, "number", L, index);
//	return static_cast<float>(lua_tonumber(L, index));
//}

LuaExtendable* toLuaExtendable(lua_State* L, int index)
{
	CHECK_ARG(lua_isuserdata, "LuaExtendable", L, index);
	return static_cast<LuaExtendable*>(lua_touserdata(L, index));
}

/**
push<T> functions
pushes the object on top of the stack, and returns the
number of actual %Lua type objects that were placed
on top of the stack
*/
inline int push(lua_State* L, bool value)
{
	lua_pushboolean(L, value);
	return 1;
}

inline int push(lua_State* L, LuaExtendable* value)
{
	return pushRegisteredClass(L, value);
}

/**
static functions
*/
template<typename RETURN, RETURN(*function)(void)>
inline int staticParam0(lua_State* L)
{
	return push(L, (*function)());
}

/**
class functions
*/
template<typename CLASS, typename RETURN, RETURN(CLASS::*function)(void) const>
int param0const(lua_State* L)
{
	RETURN value = RETURN();
	if (CLASS* object = to<CLASS*>(L, 1))
	{
		value = (object->*function)();
	}
	return push(L, value);
}

} // namespace LuaExtension

#endif//LUASTATEINTERACTION_H
