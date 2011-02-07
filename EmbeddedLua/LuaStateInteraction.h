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

namespace LuaExtension 
{ 
#if ARGUMENT_ERRORS 
#pragma message("Compiling with Lua stack argument type checking.")
/**
This is a define macro and not an inline function due to the 
average lua_istype function being a macro
*/
#define assert_lua_argument(lua_istype, expected, L, index) \
	{ \
		sint stack_size = lua_gettop(L); \
		if (index > stack_size || index < -stack_size) \
		{ \
			luaL_error(L, "argument type error! argument at index %d not found, stack size: %d", index, stack_size); \
		} \
		if (!lua_istype(L, index)) \
		{ \
			const char* actual = luaL_typename(L, index); \
			luaL_error(L, "argument type error! argument at index %d expected: %s actual: %s ", index, expected, actual); \
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
template<typename T> inline T to(lua_State* L, sint index)
{	
	prevent_compile
}

template<> inline bool to<bool>(lua_State* L, sint index)
{
	assert_lua_argument(lua_isboolean, "boolean", L, index);
	return lua_toboolean(L, index) != 0;
}

template<> inline sint to<sint>(lua_State* L, sint index)
{
	assert_lua_argument(lua_isnumber, "number", L, index);
	return static_cast<sint>(lua_tonumber(L, index));
}

template<> inline uint to<uint>(lua_State* L, sint index)
{
	assert_lua_argument(lua_isnumber, "number", L, index);
	return static_cast<uint>(lua_tonumber(L, index));
}

template<> inline float to<float>(lua_State* L, sint index)
{
	assert_lua_argument(lua_isnumber, "number", L, index);
	return static_cast<float>(lua_tonumber(L, index));
}

template<> inline double to<double>(lua_State* L, sint index)
{
	assert_lua_argument(lua_isnumber, "number", L, index);
	return static_cast<double>(lua_tonumber(L, index));
}

template<> inline LuaExtendable* to<LuaExtendable*>(lua_State* L, sint index)
{
	assert_lua_argument(lua_isuserdata, "LuaExtendable", L, index);
	return *static_cast<LuaExtendable**>(lua_touserdata(L, index));
}

template<> inline LuaExtendable& to<LuaExtendable&>(lua_State* L, sint index)
{
	assert_lua_argument(lua_isuserdata, "LuaExtendable", L, index);
	return **static_cast<LuaExtendable**>(lua_touserdata(L, index));
}

template<> inline char* to<char*>(lua_State* L, sint index)
{
	assert_lua_argument(lua_isstring, "string", L, index);
	return const_cast<char*>(lua_tostring(L, index));
}

template<> inline const char* to<const char*>(lua_State* L, sint index)
{
	assert_lua_argument(lua_isstring, "string", L, index);
	return lua_tostring(L, index);
}

/**
push<T> functions
pushes the object on top of the stack, and returns the
number of actual %Lua type objects that were placed
on top of the stack
*/
inline sint push(lua_State* L, bool value)
{
	lua_pushboolean(L, value);
	return 1;
}

inline sint push(lua_State* L, sint value)
{
	lua_pushinteger (L, static_cast<lua_Integer>(value));
	return 1;
}

inline sint push(lua_State* L, uint value)
{
	lua_pushinteger (L, static_cast<lua_Integer>(value));
	return 1;
}

inline sint push(lua_State* L, float value)
{
	lua_pushnumber(L, static_cast<lua_Number>(value));
	return 1;
}

inline sint push(lua_State* L, double value)
{
	lua_pushnumber(L, static_cast<lua_Number>(value));
	return 1;
}

inline sint push(lua_State* L, const char* value)
{
	lua_pushstring(L, value);
	return 1;
}

inline sint push(lua_State* L, LuaExtendable* value)
{
	pushRegisteredClass(L, value);					//s: ud
	lua_getglobal(L, "getmetatable");				//s: ud, getmetatable	
	lua_pushvalue(L, -2);							//s: ud, getmetatable, ud
	lua_call(L, 1, 1);								//s: ud, getmetatable, ?

	if (lua_istable(L, -1))
	{												//s: ud, mt
		lua_pop(L, 1);								//s: ud
	}
	else
	{												//s: ud, nil	
		// assert(lua_isnil(L, -1));
		lua_pop(L, 1);								//s: ud
		// assert(lua_isuserdata(L, -1));			
		lua_getglobal(L, "ObjectOrientedParadigm"); //s: ud, OOP
		// assert(lua_istable(L, -1));			
		// assert(lua_isuserdata(L, -2));			
		lua_getfield(L, -1, "initializers_PRIVATE");//s: ud, OOP, initializers
		lua_replace(L, -2);							//s: ud, initializers
		// assert(lua_istable(L, -1));			
		// assert(lua_isuserdata(L, -2));			
		lua_getfield(L, -1, value->getClassName());	//s: ud, initializers, "class_name"
		lua_replace(L, -2);							//s: ud, class()
		// assert(lua_isfunction(L, -1));			
		// assert(lua_isuserdata(L, -2));			
		lua_pushvalue(L, -2);						//s: ud, class(), ud
		// assert(lua_isuserdata(L, -1));			
		// assert(lua_isuserdata(L, -3));			
		lua_call(L, 1, 0);							//s: ud
	}

	return 1;
}

inline sint pushFalse(lua_State* L)
{
	return push(L, false);
}

inline sint pushTrue(lua_State* L)
{
	return push(L, true);
}

/**
static functions
*/
template<typename RET_1, RET_1(* function)(void)>
inline sint staticReturn1Param0(lua_State* L)
{
	return push(L, (*function)());
}

template<typename RET_1, typename ARG_1, RET_1(* function)(ARG_1)>
inline sint staticReturn1Param1(lua_State* L)
{
	ARG_1 arg1 = to<ARG_1>(L, -1);
	return push(L, (*function)(arg1));	
}

template <typename RET_1, typename RET_2, RET_1(* function)(RET_2&)>
inline sint staticReturn2Param0(lua_State* L)
{
	RET_2 retval2;
	sint num_pushed = push(L, (*function)(retval2));
	num_pushed += push(L, retval2);
	return num_pushed;
}

template <typename RET_1, typename RET_2, typename ARG_1, RET_1(* function)(RET_2&, ARG_1)>
inline sint staticReturn2Param1(lua_State* L)
{
	RET_2 retval2;
	ARG_1 argument = to<ARG_1>(L, -1);
	sint num_pushed = push(L, (*function)(retval2, argument));
	num_pushed += push(L, retval2);
	return num_pushed;
}

/**
class functions
*/
template<typename CLASS, typename ARG_1, void(CLASS::* function)(ARG_1)>
inline sint return0Param1(lua_State* L)
{
	if (CLASS* object = to<CLASS*>(L, -2))
	{
		(object->*function)( to<ARG_1>(L, -1));
	}

	return 0;	
}

template<typename CLASS, typename RET_1, RET_1(CLASS::* function)(void) const>
inline sint return1Param0const(lua_State* L)
{
	if (CLASS* object = to<CLASS*>(L, -1))
	{
		RET_1 value = (object->*function)();
		return push(L, value);
	}
	else
	{
		return 0;
	}	
}

template<typename CLASS, typename RET_1, typename ARG_1,  RET_1(CLASS::* function)(ARG_1) const>
inline sint return1Param1const(lua_State* L)
{
	if (CLASS* object = to<CLASS*>(L, -2))
	{
		ARG_1 argument = to<ARG_1>(L, -1);
		RET_1 value = (object->*function)(argument);
		return push(L, value);
	}
	else
	{
		return 0;
	}	
}

} // namespace LuaExtension

#endif//LUASTATEINTERACTION_H
