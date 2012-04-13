#pragma once
#ifndef LUASTATEINTERACTION_H
#define LUASTATEINTERACTION_H
/**
\file LuaStateInteraction.h
This file defines function helpers akin to lua_to<type> and
lua_push<type> to assist in easily extending interaction with
the %Lua state to include custom types.

\author Smoke and Mirrors Development
\htmlonly
<A HREF="smokeandmirrorsdevelopment@gmail.com">
smokeandmirrorsdevelopment@gmail.com</A>
<BR>
&copy;2009-2011 Smoke and Mirrors Development
<BR>
\endhtmlonly

\warning THIS FUNCTIONALITY IS NOT THREAD SAFE.

<DEVELOPMENT STATUS>
Current Draft		:	1.0
Current Phase		:   FIELD TESTING
Purpose				:	DEPLOYMENT
Unit Tested			:	YES
Used in development	:	YES
Used in experiments :	YES
Tested in the field	:	YES
*/
#include "LuaBuild.h"
#include "LuaExtensibility.h"
#include "LuaInclusions.h"

#include "Time.h"

namespace embeddedLua 
{ 
#if ARGUMENT_ERRORS 
#pragma message("Compiling with Lua stack argument type checking.")
/**
This is a define macro and not an inline function due to the 
average lua_istype function being a macro
*/
#define ASSERT_LUA_ARGUMENT(lua_istype, expected, L, index) \
	{ \
		sint stack_size = lua_gettop(L); \
		if (index > stack_size || index < -stack_size) \
		{ \
			luaL_error(L, "argument type error! argument at index %d not found, stack size: %d", index, stack_size); \
		} \
		if (!lua_istype(L, index)) \
		{ \
			const schar* actual = luaL_typename(L, index); \
			luaL_error(L, "argument type error! argument at index %d expected: %s actual: %s ", index, expected, actual); \
		} \
	}
#else
#define ASSERT_LUA_ARGUMENT(lua_istype, type_name, L, index) {}
#endif//ARGUMENT_ERRORS

inline void lua_assertIndexInStack(lua_State* L, sint index)
{
	sint stack_size = lua_gettop(L); 
	if (index > stack_size || index < -stack_size) 
	{ 
		luaL_error(L, "argument type error! argument at index %d not found, stack size: %d", index, stack_size); 
	} 
}

/**
\defgroup luaToFunctions Lua to<T> functions
returns an object of type T from the specified index in the %Lua stack.
@{
*/
template<typename T> inline T to(lua_State* L, sint index)
{	// never get something out of %Lua without deliberate checking or NOT checking its type
	PREVENT_COMPILE
}

template<> inline bool to<bool>(lua_State* L, sint index)
{
#if ARGUMENT_ERRORS 
	lua_assertIndexInStack(L, index);
	if (!lua_isboolean(L, index)) 
	{ 
		const schar* actual = luaL_typename(L, index); 
		luaL_error(L, "argument type error! argument at index %d expected: %s actual: %s ", index, "boolean", actual); 
	} 
#endif//ARGUMENT_ERRORS 
	return lua_toboolean(L, index) != 0;
}

template<> inline sint to<sint>(lua_State* L, sint index)
{
#if ARGUMENT_ERRORS 
	lua_assertIndexInStack(L, index);
	if (!lua_isnumber(L, index)) 
	{ 
		const schar* actual = luaL_typename(L, index); 
		luaL_error(L, "argument type error! argument at index %d expected: %s actual: %s ", index, "number", actual); 
	} 
#endif//ARGUMENT_ERRORS 
	return static_cast<sint>(lua_tointeger(L, index));
}

template<> inline uint to<uint>(lua_State* L, sint index)
{
#if ARGUMENT_ERRORS 
	lua_assertIndexInStack(L, index);
	if (!lua_isnumber(L, index)) 
	{ 
		const schar* actual = luaL_typename(L, index); 
		luaL_error(L, "argument type error! argument at index %d expected: %s actual: %s ", index, "number", actual); 
	} 
#endif//ARGUMENT_ERRORS 
	return static_cast<uint>(lua_tointeger(L, index));
}

template<> inline sreal to<sreal>(lua_State* L, sint index)
{
#if ARGUMENT_ERRORS 
	lua_assertIndexInStack(L, index);
	if (!lua_isnumber(L, index)) 
	{ 
		const schar* actual = luaL_typename(L, index); 
		luaL_error(L, "argument type error! argument at index %d expected: %s actual: %s ", index, "number", actual); 
	} 
#endif//ARGUMENT_ERRORS 
	return static_cast<sreal>(lua_tonumber(L, index));
}

template<> inline dreal to<dreal>(lua_State* L, sint index)
{
#if ARGUMENT_ERRORS 
	lua_assertIndexInStack(L, index);
	if (!lua_isnumber(L, index)) 
	{ 
		const schar* actual = luaL_typename(L, index); 
		luaL_error(L, "argument type error! argument at index %d expected: %s actual: %s ", index, "number", actual); 
	} 
#endif//ARGUMENT_ERRORS 
	return static_cast<dreal>(lua_tonumber(L, index));
}

template<> inline LuaExtendable* to<LuaExtendable*>(lua_State* L, sint index)
{
#if ARGUMENT_ERRORS 
	lua_assertIndexInStack(L, index);
	if (lua_isnil(L, index))
	{
		return NULL;
	}
	else if (!lua_isuserdata(L, index)) 
	{ 
		const schar* actual = luaL_typename(L, index); 
		luaL_error(L, "argument type error! argument at index %d expected: %s actual: %s ", index, "LuaExtendable", actual); 
	} 
#endif//ARGUMENT_ERRORS 
	LuaExtendable* ud = *static_cast<LuaExtendable**>(lua_touserdata(L, index));
	return ud;
}

template<> inline LuaExtendable& to<LuaExtendable&>(lua_State* L, sint index)
{
#if ARGUMENT_ERRORS 
	lua_assertIndexInStack(L, index);
	if (!lua_isuserdata(L, index)) 
	{ 
		const schar* actual = luaL_typename(L, index); 
		luaL_error(L, "argument type error! argument at index %d expected: %s actual: %s ", index, "LuaExtendable", actual); 
	} 
#endif//ARGUMENT_ERRORS 
	return **static_cast<LuaExtendable**>(lua_touserdata(L, index));
}

template<> inline char* to<char*>(lua_State* L, sint index)
{
#if ARGUMENT_ERRORS 
	lua_assertIndexInStack(L, index);
	if (!lua_isstring(L, index)) 
	{ 
		const schar* actual = luaL_typename(L, index); 
		luaL_error(L, "argument type error! argument at index %d expected: %s actual: %s ", index, "string", actual); 
	} 
#endif//ARGUMENT_ERRORS 
	return const_cast<char*>(lua_tostring(L, index));
}

template<> inline const schar* to<const schar*>(lua_State* L, sint index)
{
#if ARGUMENT_ERRORS 
	lua_assertIndexInStack(L, index);
	if (!lua_isstring(L, index)) 
	{ 
		const schar* actual = luaL_typename(L, index); 
		luaL_error(L, "argument type error! argument at index %d expected: %s actual: %s ", index, "string", actual); 
	} 
#endif//ARGUMENT_ERRORS 
	return lua_tostring(L, index);
}
/** @} */

/**
\defgroup luaPushFuntions Lua push(lua_State* L, T t) functions
pushes the object of type T top of the stack, and returns the
number of actual %Lua type objects that were placed
on top of the stack (1).
@{
*/
inline sint push(lua_State* L, bool value)
{
	lua_pushboolean(L, value);
	return 1;
}

inline sint push(lua_State* L, schar value)
{
	lua_pushinteger(L, static_cast<lua_Integer>(value));
	return 1;
}

inline sint push(lua_State* L, uchar value)
{
	lua_pushinteger(L, static_cast<lua_Integer>(value));
	return 1;
}

inline sint push(lua_State* L, sshort value)
{
	lua_pushinteger(L, static_cast<lua_Integer>(value));
	return 1;
}

inline sint push(lua_State* L, ushort value)
{
	lua_pushinteger(L, static_cast<lua_Integer>(value));
	return 1;
}

inline sint push(lua_State* L, sint value)
{
	lua_pushinteger(L, static_cast<lua_Integer>(value));
	return 1;
}

inline sint push(lua_State* L, uint value)
{
	lua_pushinteger(L, static_cast<lua_Integer>(value));
	return 1;
}

inline sint push(lua_State* L, ulong value)
{
	lua_pushinteger(L, static_cast<lua_Integer>(value));
	return 1;
}

inline sint push(lua_State* L, slong value)
{
	lua_pushinteger(L, static_cast<lua_Integer>(value));
	return 1;
}

inline sint push(lua_State* L, sreal value)
{
	lua_pushnumber(L, static_cast<lua_Number>(value));
	return 1;
}

inline sint push(lua_State* L, dreal value)
{
	lua_pushnumber(L, static_cast<lua_Number>(value));
	return 1;
}

inline sint push(lua_State* L, const schar* value)
{
	lua_pushstring(L, value);
	return 1;
}

/**
\note when pushing a LueExtendable into %Lua, it might not be because the 
object was created by a call to ObjectOrientedParadigm.new() in %Lua.  In this
case, if the class has a extra methods defined in %Lua, especially a 'construct'
method, that %Lua only properties of the object must be initialized the first
time the object is pushed into %Lua
*/
sint push(lua_State* L, LuaExtendable* value);

inline sint pushFalse(lua_State* L)
{
	return push(L, false);
}

inline sint pushNil(lua_State* L)
{
	lua_pushnil(L);
	return 1;
}

inline sint pushTrue(lua_State* L)
{
	return push(L, true);
}

/** @} */

} // namespace embeddedLua

#endif//LUASTATEINTERACTION_H
