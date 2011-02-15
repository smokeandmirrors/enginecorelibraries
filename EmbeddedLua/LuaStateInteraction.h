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
*/

#include "Build.h"
#include "LuaExtensibility.h"
#include "LuaInclusions.h"

namespace luaExtension 
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
\defgroup luaToFunctions Lua to<T> functions
returns an object of type T from the specified index in the %Lua stack.
@{
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

/**
\note when pushing a LueExtendable into %Lua, it might not be because the 
object was created by a call to ObjectOrientedParadigm.new() in %Lua.  In this
case, if the class has a extra methods defined in %Lua, especially a 'construct'
method, that %Lua only properties of the object must be initialized the first
time the object is pushed into %Lua
*/
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

/** @} */

/**
\defgroup luaFunctionTemplates Lua function templates
Template functions to make it easer to expose static and class
functions to %Lua.  I only use the goofy syntax of splitting up the
template<> arguments on each line to make it easier to discern
which types of functions all ready have a template defined.

There are 2 major types of template function wrappers:
1. static (as in static member, or none class member functions)
2. class member functions (where the first argument is ALWAYS presumed to be
	an userdata pointer of the type of the class)

The naming convention is as follows
1. static:	staticReturn<# of return values>Param<# of parameters>
2. class:	return<# of return values>Param<# of parameters>{const}

example:
C function:
\code
vec_t Vector3::dot(const Vector3& v); // member function, 1 return value, 1 argument
\endcode

wrapper:
\code
return1Param1<Vector3, vec_t, const Vector3&>
\endcode

%Lua call:
\code
local dot_product = v:dot(w)
\endcode

To return more than one value to %Lua, you wrap a function that has the 2nd
through Nth return value passed by reference.  The 1st return value to %Lua,
is the return value of the function.  The 2nd return value is the first 
argument by reference, and the Nth return value is the (N - 1)th argument
by reference, etc.  All arguments after the last argument to be returned to
%Lua will not be returned to %Lua, no matter how they are passed to the 
C function

@{
*/

/**
static function wrappers
*/
/**
void function wrappers
*/
/** to wrap: void anyfunction(void); */
template
<
void(* function)(void)
>
inline sint staticReturn0Param0(lua_State* L)
{
	(*function)();
	return 0;
}

/** to wrap: void anyfunction(T arg); */
template
<
typename ARG_1, 
void(* function)(ARG_1)
>
inline sint staticReturn0Param1(lua_State* L)
{
	(*function)(to<ARG_1>(L, -1));
	return 0;
}

/** to wrap: void anyfunction(T arg, T arg); */
template
<
typename ARG_1,
typename ARG_2,
void(* function)(ARG_1, ARG_2)
>
inline sint staticReturn0Param2(lua_State* L)
{
	(*function)(to<ARG_1>(L, -2), to<ARG_2>(L, -1));
	return 0;
}

/** to wrap: void anyfunction(T arg, T arg, T arg); */
template
<
typename ARG_1,
typename ARG_2,
typename ARG_3,
void(* function)(ARG_1, ARG_2, ARG_3)
>
inline sint staticReturn0Param3(lua_State* L)
{
	(*function)(to<ARG_1>(L, -3), to<ARG_2>(L, -2), to<ARG_3>(L, -1));
	return 0;
}

/** to wrap: void anyfunction(T arg, T arg, T arg, T arg); */
template
<
typename ARG_1,
typename ARG_2,
typename ARG_3,
typename ARG_4,
void(* function)(ARG_1, ARG_2, ARG_3, ARG_4)
>
inline sint staticReturn0Param3(lua_State* L)
{
	(*function)(to<ARG_1>(L, -4), to<ARG_2>(L, -3), 
		to<ARG_3>(L, -2), to<ARG_4>(L, -1));
	return 0;
}

/**
non-void function wrappers 
*/
/** to wrap: T anyfunction(void); */
template
<
typename RET_1, 
RET_1(* function)(void)
>
inline sint staticReturn1Param0(lua_State* L)
{
	return push(L, (*function)());	
}

/** to wrap: T anyfunction(T arg); */
template
<
typename RET_1, 
typename ARG_1, 
RET_1(* function)(ARG_1)
>
inline sint staticReturn1Param1(lua_State* L)
{
	return push(L, (*function)(to<ARG_1>(L, -1)));	
}

/**
multiple return value function wrappers
*/
/** to wrap: T anyfunction(T& arg); */
template
<
typename RET_1, 
typename RET_2, 
RET_1(* function)(RET_2&)
>
inline sint staticReturn2Param0(lua_State* L)
{
	RET_2 retval2;
	sint num_pushed = push(L, (*function)(retval2));
	num_pushed += push(L, retval2);
	return num_pushed;
}

/** to wrap: T anyfunction(T& arg, T arg); */
template
<
typename RET_1, 
typename RET_2, 
typename ARG_1, 
RET_1(* function)(RET_2&, ARG_1)
>
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
/** 
void, volatile function wrappers
*/
template
<
typename CLASS, 
void(CLASS::* function)(void)
>
inline sint return0Param0(lua_State* L)
{
	if (CLASS* object = to<CLASS*>(L, -1))
	{
		(object->*function)();
	}
	return 0;	
}

template
<
typename CLASS, 
typename ARG_1, 
void(CLASS::* function)(ARG_1)
>
inline sint return0Param1(lua_State* L)
{
	if (CLASS* object = to<CLASS*>(L, -2))
	{
		(object->*function)(to<ARG_1>(L, -1));
	}
	return 0;	
}

template
<
typename CLASS, 
typename ARG_1,
typename ARG_2,
void(CLASS::* function)(ARG_1, ARG_2)
>
inline sint return0Param2(lua_State* L)
{
	if (CLASS* object = to<CLASS*>(L, -3))
	{
		(object->*function)(to<ARG_1>(L, -2), to<ARG_2>(L, -1));
	}
	return 0;	
}

template
<
typename CLASS, 
typename ARG_1,
typename ARG_2,
typename ARG_3,
void(CLASS::* function)(ARG_1, ARG_2, ARG_3)
>
inline sint return0Param3(lua_State* L)
{
	if (CLASS* object = to<CLASS*>(L, -4))
	{
		(object->*function)(to<ARG_1>(L, -3), to<ARG_2>(L, -2), to<ARG_3>(L, -1));
	}
	return 0;	
}

/** 
non-void, volatile function wrappers
*/
template
<
typename CLASS, 
typename RET_1, 
RET_1(CLASS::* function)(void)
>
inline sint return1Param0(lua_State* L)
{
	if (CLASS* object = to<CLASS*>(L, -1))
	{
		return push(L, (object->*function)());
	}
	return 0;
}

/** 
non-void, const function wrappers
*/
template
<
typename CLASS, 
typename RET_1, 
RET_1(CLASS::* function)(void) const
>
inline sint return1Param0const(lua_State* L)
{
	if (CLASS* object = to<CLASS*>(L, -1))
	{
		return push(L, (object->*function)());
	}
	return 0;
}

template
<
typename CLASS, 
typename RET_1, 
typename ARG_1,  
RET_1(CLASS::* function)(ARG_1) const
>
inline sint return1Param1const(lua_State* L)
{
	if (CLASS* object = to<CLASS*>(L, -2))
	{
		return push(L, (object->*function)(to<ARG_1>(L, -1)));
	}
	return 0;
}

template
<
typename CLASS, 
typename RET_1, 
typename ARG_1, 
typename ARG_2, 
RET_1(CLASS::* function)(ARG_1, ARG_2) const
>
inline sint return1Param2const(lua_State* L)
{
	if (CLASS* object = to<CLASS*>(L, -3))
	{
		return push(L, (object->*function)(to<ARG_1>(L, -2), to<ARG_2>(L, -1)));
	}
	return 0;
}
/** @} */
} // namespace luaExtension

#endif//LUASTATEINTERACTION_H
