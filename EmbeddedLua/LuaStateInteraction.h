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
\email smokeandmirrorsdevelopment@gmail.com
\date 8/21/2010
*/

#include "Build.h"
#include "LuaExtensibility.h"
#include "LuaInclusions.h"
#include "Vector.h"

namespace LuaExtension 
{ 
#if 1 // ARGUMENT_ERRORS
#pragma message("Compiling with Lua stack argument type checking.")
/**
This is a define macro and not an inline function due to the 
average lua_istype function being a macro
*/
#define assert_lua_argument(lua_istype, type_name, L, index) \
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
#define assert_lua_argument(lua_istype, type_name, L, index) {}
#endif//ARGUMENT_ERRORS

#define static_assert(pred) switch(0){case 0:case pred:;}
#define prevent_compile switch(0){case 0:case 0:;}

/**
to<T> functions
returns an object from the specified index in the %Lua stack
*/
template<typename T> inline T to(lua_State* L, int index)
{	
	prevent_compile
}

template<> inline bool to<bool>(lua_State* L, int index)
{
	assert_lua_argument(lua_isboolean, "boolean", L, index);
	return lua_toboolean(L, index) != 0;
}

template<> inline sint to<sint>(lua_State* L, int index)
{
	assert_lua_argument(lua_isnumber, "number", L, index);
	return static_cast<sint>(lua_tonumber(L, index));
}

template<> inline uint to<uint>(lua_State* L, int index)
{
	assert_lua_argument(lua_isnumber, "number", L, index);
	return static_cast<uint>(lua_tonumber(L, index));
}

template<> inline float to<float>(lua_State* L, int index)
{
	assert_lua_argument(lua_isnumber, "number", L, index);
	return static_cast<float>(lua_tonumber(L, index));
}

template<> inline double to<double>(lua_State* L, int index)
{
	assert_lua_argument(lua_isnumber, "number", L, index);
	return static_cast<double>(lua_tonumber(L, index));
}

template<> inline LuaExtendable* to<LuaExtendable*>(lua_State* L, int index)
{
	assert_lua_argument(lua_isuserdata, "LuaExtendable", L, index);
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

inline int push(lua_State* L, sint value)
{
	lua_pushnumber(L, static_cast<lua_Number>(value));
	return 1;
}

inline int push(lua_State* L, float value)
{
	lua_pushnumber(L, static_cast<lua_Number>(value));
	return 1;
}

inline int push(lua_State* L, LuaExtendable* value)
{
	return pushRegisteredClass(L, value);
}

/**
static functions
*/
template<typename RET_1, RET_1(* function)(void)>
inline int staticReturn1Param0(lua_State* L)
{
	return push(L, (*function)());
}

template<typename RET_1, typename ARG_1, RET_1(* function)(ARG_1)>
inline int staticReturn1Param1(lua_State* L)
{
	ARG_1 argument = to<ARG_1>(L, -1);
	lua_pop(L, -1);
	return push(L, (*function)(argument));	
}

template <typename RET_1, typename RET_2, RET_1(* function)(RET_2&)>
inline int staticReturn2Param0(lua_State* L)
{
	RET_2 retval2;
	int num_pushed = push(L, (*function)(retval2));
	num_pushed += push(L, retval2);
	return num_pushed;
}

template <typename RET_1, typename RET_2, typename ARG_1, RET_1(* function)(RET_2&, ARG_1)>
inline int staticReturn2Param1(lua_State* L)
{
	RET_2 retval2;
	ARG_1 argument = to<ARG_1>(L, -1);
	lua_pop(L, -1);
	int num_pushed = push(L, (*function)(retval2, argument));
	num_pushed += push(L, retval2);
	return num_pushed;
}


/**
class functions
*/
template<typename CLASS, typename RETURN, RETURN(CLASS::* function)(void) const>
int return1Param0const(lua_State* L)
{
	RETURN value;

	if (CLASS* object = to<CLASS*>(L, 1))
	{
		value = (object->*function)();
		return push(L, value);
	}
	else
	{
		return 0;
	}	
}

} // namespace LuaExtension

#endif//LUASTATEINTERACTION_H
