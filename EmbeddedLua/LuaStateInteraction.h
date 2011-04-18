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

namespace lua_extension 
{ 
#if ARGUMENT_ERRORS 
#pragma message("Compiling with Lua stack argument type checking.")
/**
This is a define macro and not an inline function due to the 
average lua_istype function being a macro
*/
#define ASSERT_LUA_ARGUMENT(lua_istype, expected, L, index) \
	{ \
		sint4 stack_size = lua_gettop(L); \
		if (index > stack_size || index < -stack_size) \
		{ \
			luaL_error(L, "argument type error! argument at index %d not found, stack size: %d", index, stack_size); \
		} \
		if (!lua_istype(L, index)) \
		{ \
			const sint1* actual = luaL_typename(L, index); \
			luaL_error(L, "argument type error! argument at index %d expected: %s actual: %s ", index, expected, actual); \
		} \
	}
#else
#define ASSERT_LUA_ARGUMENT(lua_istype, type_name, L, index) {}
#endif//ARGUMENT_ERRORS

inline void lua_assertIndexInStack(lua_State* L, sint4 index)
{
	sint4 stack_size = lua_gettop(L); 
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
template<typename T> inline T to(lua_State* L, sint4 index)
{	// never get something out of %Lua without deliberate checking or NOT checking its type
	PREVENT_COMPILE
}

template<> inline bool to<bool>(lua_State* L, sint4 index)
{
#if ARGUMENT_ERRORS 
	lua_assertIndexInStack(L, index);
	if (!lua_isboolean(L, index)) 
	{ 
		const sint1* actual = luaL_typename(L, index); 
		luaL_error(L, "argument type error! argument at index %d expected: %s actual: %s ", index, "boolean", actual); 
	} 
#endif//ARGUMENT_ERRORS 
	return lua_toboolean(L, index) != 0;
}

template<> inline sint4 to<sint4>(lua_State* L, sint4 index)
{
#if ARGUMENT_ERRORS 
	lua_assertIndexInStack(L, index);
	if (!lua_isnumber(L, index)) 
	{ 
		const sint1* actual = luaL_typename(L, index); 
		luaL_error(L, "argument type error! argument at index %d expected: %s actual: %s ", index, "number", actual); 
	} 
#endif//ARGUMENT_ERRORS 
	return static_cast<sint4>(lua_tonumber(L, index));
}

template<> inline uint4 to<uint4>(lua_State* L, sint4 index)
{
#if ARGUMENT_ERRORS 
	lua_assertIndexInStack(L, index);
	if (!lua_isnumber(L, index)) 
	{ 
		const sint1* actual = luaL_typename(L, index); 
		luaL_error(L, "argument type error! argument at index %d expected: %s actual: %s ", index, "number", actual); 
	} 
#endif//ARGUMENT_ERRORS 
	return static_cast<uint4>(lua_tonumber(L, index));
}

template<> inline real4 to<real4>(lua_State* L, sint4 index)
{
#if ARGUMENT_ERRORS 
	lua_assertIndexInStack(L, index);
	if (!lua_isnumber(L, index)) 
	{ 
		const sint1* actual = luaL_typename(L, index); 
		luaL_error(L, "argument type error! argument at index %d expected: %s actual: %s ", index, "number", actual); 
	} 
#endif//ARGUMENT_ERRORS 
	return static_cast<real4>(lua_tonumber(L, index));
}

template<> inline real8 to<real8>(lua_State* L, sint4 index)
{
#if ARGUMENT_ERRORS 
	lua_assertIndexInStack(L, index);
	if (!lua_isnumber(L, index)) 
	{ 
		const sint1* actual = luaL_typename(L, index); 
		luaL_error(L, "argument type error! argument at index %d expected: %s actual: %s ", index, "number", actual); 
	} 
#endif//ARGUMENT_ERRORS 
	return static_cast<real8>(lua_tonumber(L, index));
}

template<> inline LuaExtendable* to<LuaExtendable*>(lua_State* L, sint4 index)
{
#if ARGUMENT_ERRORS 
	lua_assertIndexInStack(L, index);
	if (!lua_isuserdata(L, index)) 
	{ 
		const sint1* actual = luaL_typename(L, index); 
		luaL_error(L, "argument type error! argument at index %d expected: %s actual: %s ", index, "LuaExtendable", actual); 
	} 
#endif//ARGUMENT_ERRORS 
	LuaExtendable* ud = *static_cast<LuaExtendable**>(lua_touserdata(L, index));
	return ud;
}

template<> inline LuaExtendable& to<LuaExtendable&>(lua_State* L, sint4 index)
{
#if ARGUMENT_ERRORS 
	lua_assertIndexInStack(L, index);
	if (!lua_isuserdata(L, index)) 
	{ 
		const sint1* actual = luaL_typename(L, index); 
		luaL_error(L, "argument type error! argument at index %d expected: %s actual: %s ", index, "LuaExtendable", actual); 
	} 
#endif//ARGUMENT_ERRORS 
	return **static_cast<LuaExtendable**>(lua_touserdata(L, index));
}

template<> inline char* to<char*>(lua_State* L, sint4 index)
{
#if ARGUMENT_ERRORS 
	lua_assertIndexInStack(L, index);
	if (!lua_isstring(L, index)) 
	{ 
		const sint1* actual = luaL_typename(L, index); 
		luaL_error(L, "argument type error! argument at index %d expected: %s actual: %s ", index, "string", actual); 
	} 
#endif//ARGUMENT_ERRORS 
	return const_cast<char*>(lua_tostring(L, index));
}

template<> inline const sint1* to<const sint1*>(lua_State* L, sint4 index)
{
#if ARGUMENT_ERRORS 
	lua_assertIndexInStack(L, index);
	if (!lua_isstring(L, index)) 
	{ 
		const sint1* actual = luaL_typename(L, index); 
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
inline sint4 push(lua_State* L, bool value)
{
	lua_pushboolean(L, value);
	return 1;
}

inline sint4 push(lua_State* L, sint4 value)
{
	lua_pushinteger (L, static_cast<lua_Integer>(value));
	return 1;
}

inline sint4 push(lua_State* L, uint4 value)
{
	lua_pushinteger (L, static_cast<lua_Integer>(value));
	return 1;
}

inline sint4 push(lua_State* L, real4 value)
{
	lua_pushnumber(L, static_cast<lua_Number>(value));
	return 1;
}

inline sint4 push(lua_State* L, real8 value)
{
	lua_pushnumber(L, static_cast<lua_Number>(value));
	return 1;
}

inline sint4 push(lua_State* L, const sint1* value)
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
inline sint4 push(lua_State* L, LuaExtendable* value)
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
		lua_pop(L, 1);								//s: ud
		lua_getglobal(L, "ObjectOrientedParadigm"); //s: ud, OOP
		lua_getfield(L, -1, "initializers_PRIVATE");//s: ud, OOP, initializers
		lua_replace(L, -2);							//s: ud, initializers
		lua_getfield(L, -1, value->getClassName());	//s: ud, initializers, "class_name"
		lua_replace(L, -2);							//s: ud, class()
		lua_pushvalue(L, -2);						//s: ud, class(), ud
		lua_call(L, 1, 0);							//s: ud
	}

	return 1;
}

inline sint4 pushFalse(lua_State* L)
{
	return push(L, false);
}

inline sint4 pushTrue(lua_State* L)
{
	return push(L, true);
}

/** @} */

} // namespace lua_extension

#endif//LUASTATEINTERACTION_H
