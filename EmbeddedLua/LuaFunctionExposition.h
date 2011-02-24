#pragma once
#ifndef LUAFUNCTIONEXPOSITION_H
#define LUAFUNCTIONEXPOSITION_H
/**
\file LuaFunctionExposition.h

This file attempts to make even easier the generation C++ functions
that are exposed to Lua.

luaFunctionTemplates Lua function templates
Template functions to make it easer to expose static and class
functions to %Lua.  I only use the goofy syntax of splitting up the
template<> arguments on each line to make it easier to discern
which types of functions all ready have a template defined.

There are 2 major types of template function wrappers:\n
1. static (as in static member, or none class member functions)\n
2. class member functions (where the first argument is ALWAYS presumed to be\n
an userdata pointer of the type of the class)

The naming convention is as follows:\n
1. static:	staticReturn<# of return values>Param<# of parameters>\n
2. class:	return<# of return values>Param<# of parameters>{const}\n

The following templates are currently defined by way of the macros below:
\code
//////////////////////////////////////////////////////////////////////////
// static non member functions: 
template<typename ARG_1, void (* function)(ARG_1)> 
inline sint staticReturn0Param1(lua_State* L);

template<typename RET_1, RET_1 (* function)(void)>
inline sint staticReturn1Param0(lua_State* L);

// ... 

template<typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, RET_1 (*function)(RET_2&, ARG_1, ARG_2)>
inline sint staticReturn2Param2(lua_State* L);

// ...

template
<
typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, 
typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, 
RET_1 (*function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5)
>
inline sint return5Param5(lua_State* L);

//////////////////////////////////////////////////////////////////////////
// class member functions: 
template<typename CLASS, typename ARG_1, void (CLASS::* function)(ARG_1)> 
inline sint return0Param1(lua_State* L);

template<typename CLASS, typename RET_1, RET_1 (CLASS::* function)(void)>
inline sint return1Param0(lua_State* L);

// ... 

template<typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(RET_2&, ARG_1, ARG_2)>
inline sint return2Param2(lua_State* L);

// ...

template
<
typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, 
typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, 
RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5)
>
inline sint return5Param5(lua_State* L);

//////////////////////////////////////////////////////////////////////////
// class member const functions: 
template<typename CLASS, typename ARG_1, void (CLASS::* function)(ARG_1) const> 
inline sint return0Param1const(lua_State* L);

template<typename CLASS, typename RET_1, RET_1 (CLASS::* function)(void) const>
inline sint return1Param0const(lua_State* L);

// ... 

template<typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(RET_2&, ARG_1, ARG_2) const>
inline sint return2Param2const(lua_State* L);

// ...

template
<
typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, 
typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, 
RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) const
>
inline sint return5Param5const(lua_State* L);
\endcode

example:
C function:
\code
vec_t Vector3::dot(const Vector3& v) const; // member function, 1 return value, 1 argument
\endcode

wrapper:
\code
return1Param1const<Vector3, vec_t, const Vector3&, &Vector3::dot>
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

\note on implementation, return 0, arguments 0 are MANUALLY written 
\note EFL_ here means "Expose Function to Lua.."
\see the simplest examples below
*/

namespace luaExtension
{
	template<void(* function)(void)> 
	inline sint staticReturn0Param0(lua_State* L)
	{
		(*function)();
		return 0;
	}

	template<typename CLASS, void(CLASS::* function)(void)>
	inline sint return0Param0(lua_State* L)
	{
		if (CLASS* object = to<CLASS*>(L, -1))
		{
			(object->*function)();
		}
		return 0;	
	}

	template<typename CLASS, void(CLASS::* function)(void) const>
	inline sint return0Param0const(lua_State* L)
	{
		if (CLASS* object = to<CLASS*>(L, -1))
		{
			(object->*function)();
		}
		return 0;	
	}
} // namespace luaExtension

#include "Build.h"
#include "LuaExtensibility.h"
#include "LuaInclusions.h"
#include "LuaStateInteraction.h"

/** template arguments */
// fill in the template arguments in the declaration
#define EFL_TEMPLATE_ARGS_RETS_0_ARGS_1 typename ARG_1,
#define EFL_TEMPLATE_ARGS_RETS_0_ARGS_2 typename ARG_1, typename ARG_2, 
#define EFL_TEMPLATE_ARGS_RETS_0_ARGS_3 typename ARG_1, typename ARG_2, typename ARG_3,
#define EFL_TEMPLATE_ARGS_RETS_0_ARGS_4 typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4,
#define EFL_TEMPLATE_ARGS_RETS_0_ARGS_5 typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5,

#define EFL_TEMPLATE_ARGS_RETS_1_ARGS_0 typename RET_1, 
#define EFL_TEMPLATE_ARGS_RETS_1_ARGS_1 typename RET_1, typename ARG_1, 
#define EFL_TEMPLATE_ARGS_RETS_1_ARGS_2 typename RET_1, typename ARG_1, typename ARG_2,
#define EFL_TEMPLATE_ARGS_RETS_1_ARGS_3 typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, 
#define EFL_TEMPLATE_ARGS_RETS_1_ARGS_4 typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4,
#define EFL_TEMPLATE_ARGS_RETS_1_ARGS_5 typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5,

#define EFL_TEMPLATE_ARGS_RETS_2_ARGS_0 typename RET_1, typename RET_2, 
#define EFL_TEMPLATE_ARGS_RETS_2_ARGS_1 typename RET_1, typename RET_2, typename ARG_1, 
#define EFL_TEMPLATE_ARGS_RETS_2_ARGS_2 typename RET_1, typename RET_2, typename ARG_1, typename ARG_2,
#define EFL_TEMPLATE_ARGS_RETS_2_ARGS_3 typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, 
#define EFL_TEMPLATE_ARGS_RETS_2_ARGS_4 typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4,
#define EFL_TEMPLATE_ARGS_RETS_2_ARGS_5 typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5,

#define EFL_TEMPLATE_ARGS_RETS_3_ARGS_0 typename RET_1, typename RET_2, typename RET_3, 
#define EFL_TEMPLATE_ARGS_RETS_3_ARGS_1 typename RET_1, typename RET_2, typename RET_3, typename ARG_1, 
#define EFL_TEMPLATE_ARGS_RETS_3_ARGS_2 typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2,
#define EFL_TEMPLATE_ARGS_RETS_3_ARGS_3 typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, 
#define EFL_TEMPLATE_ARGS_RETS_3_ARGS_4 typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4,
#define EFL_TEMPLATE_ARGS_RETS_3_ARGS_5 typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5,

#define EFL_TEMPLATE_ARGS_RETS_4_ARGS_0 typename RET_1, typename RET_2, typename RET_3, typename RET_4,
#define EFL_TEMPLATE_ARGS_RETS_4_ARGS_1 typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, 
#define EFL_TEMPLATE_ARGS_RETS_4_ARGS_2 typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2,
#define EFL_TEMPLATE_ARGS_RETS_4_ARGS_3 typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, 
#define EFL_TEMPLATE_ARGS_RETS_4_ARGS_4 typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4,
#define EFL_TEMPLATE_ARGS_RETS_4_ARGS_5 typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5,

#define EFL_TEMPLATE_ARGS_RETS_5_ARGS_0 typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5,
#define EFL_TEMPLATE_ARGS_RETS_5_ARGS_1 typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, 
#define EFL_TEMPLATE_ARGS_RETS_5_ARGS_2 typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2,
#define EFL_TEMPLATE_ARGS_RETS_5_ARGS_3 typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, 
#define EFL_TEMPLATE_ARGS_RETS_5_ARGS_4 typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4,
#define EFL_TEMPLATE_ARGS_RETS_5_ARGS_5 typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5,

// fill in the template arguments in the template function 
#define EFL_TEMPLATE_RETURN_SIGNATURE_RETS_0 void
#define EFL_TEMPLATE_RETURN_SIGNATURE_RETS_1 RET_1
#define EFL_TEMPLATE_RETURN_SIGNATURE_RETS_2 RET_1
#define EFL_TEMPLATE_RETURN_SIGNATURE_RETS_3 RET_1
#define EFL_TEMPLATE_RETURN_SIGNATURE_RETS_4 RET_1
#define EFL_TEMPLATE_RETURN_SIGNATURE_RETS_5 RET_1

#define EFL_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_1 ARG_1
#define EFL_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_2 ARG_1, ARG_2
#define EFL_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_3 ARG_1, ARG_2, ARG_3
#define EFL_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_4 ARG_1, ARG_2, ARG_3, ARG_4
#define EFL_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_5 ARG_1, ARG_2, ARG_3, ARG_4, ARG_5

#define EFL_TEMPLATE_ARGS_SIGNATURE_RETS_1_ARGS_0 void
#define EFL_TEMPLATE_ARGS_SIGNATURE_RETS_1_ARGS_1 ARG_1
#define EFL_TEMPLATE_ARGS_SIGNATURE_RETS_1_ARGS_2 ARG_1, ARG_2
#define EFL_TEMPLATE_ARGS_SIGNATURE_RETS_1_ARGS_3 ARG_1, ARG_2, ARG_3
#define EFL_TEMPLATE_ARGS_SIGNATURE_RETS_1_ARGS_4 ARG_1, ARG_2, ARG_3, ARG_4
#define EFL_TEMPLATE_ARGS_SIGNATURE_RETS_1_ARGS_5 ARG_1, ARG_2, ARG_3, ARG_4, ARG_5

#define EFL_TEMPLATE_ARGS_SIGNATURE_RETS_2_ARGS_0 RET_2&
#define EFL_TEMPLATE_ARGS_SIGNATURE_RETS_2_ARGS_1 RET_2&, ARG_1
#define EFL_TEMPLATE_ARGS_SIGNATURE_RETS_2_ARGS_2 RET_2&, ARG_1, ARG_2
#define EFL_TEMPLATE_ARGS_SIGNATURE_RETS_2_ARGS_3 RET_2&, ARG_1, ARG_2, ARG_3
#define EFL_TEMPLATE_ARGS_SIGNATURE_RETS_2_ARGS_4 RET_2&, ARG_1, ARG_2, ARG_3, ARG_4
#define EFL_TEMPLATE_ARGS_SIGNATURE_RETS_2_ARGS_5 RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5

#define EFL_TEMPLATE_ARGS_SIGNATURE_RETS_3_ARGS_0 RET_2&, RET_3&
#define EFL_TEMPLATE_ARGS_SIGNATURE_RETS_3_ARGS_1 RET_2&, RET_3&, ARG_1
#define EFL_TEMPLATE_ARGS_SIGNATURE_RETS_3_ARGS_2 RET_2&, RET_3&, ARG_1, ARG_2
#define EFL_TEMPLATE_ARGS_SIGNATURE_RETS_3_ARGS_3 RET_2&, RET_3&, ARG_1, ARG_2, ARG_3
#define EFL_TEMPLATE_ARGS_SIGNATURE_RETS_3_ARGS_4 RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4
#define EFL_TEMPLATE_ARGS_SIGNATURE_RETS_3_ARGS_5 RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5

#define EFL_TEMPLATE_ARGS_SIGNATURE_RETS_4_ARGS_0 RET_2&, RET_3&, RET_4&
#define EFL_TEMPLATE_ARGS_SIGNATURE_RETS_4_ARGS_1 RET_2&, RET_3&, RET_4&, ARG_1
#define EFL_TEMPLATE_ARGS_SIGNATURE_RETS_4_ARGS_2 RET_2&, RET_3&, RET_4&, ARG_1, ARG_2
#define EFL_TEMPLATE_ARGS_SIGNATURE_RETS_4_ARGS_3 RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3
#define EFL_TEMPLATE_ARGS_SIGNATURE_RETS_4_ARGS_4 RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4
#define EFL_TEMPLATE_ARGS_SIGNATURE_RETS_4_ARGS_5 RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5

#define EFL_TEMPLATE_ARGS_SIGNATURE_RETS_5_ARGS_0 RET_2&, RET_3&, RET_4&, RET_5&
#define EFL_TEMPLATE_ARGS_SIGNATURE_RETS_5_ARGS_1 RET_2&, RET_3&, RET_4&, RET_5&, ARG_1
#define EFL_TEMPLATE_ARGS_SIGNATURE_RETS_5_ARGS_2 RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2
#define EFL_TEMPLATE_ARGS_SIGNATURE_RETS_5_ARGS_3 RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3
#define EFL_TEMPLATE_ARGS_SIGNATURE_RETS_5_ARGS_4 RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4
#define EFL_TEMPLATE_ARGS_SIGNATURE_RETS_5_ARGS_5 RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5

/** function implementation */
// declare the return values that get passed by reference into the function
#define EFL_DECLARE_RETS_0 ;
#define EFL_DECLARE_RETS_1 ;	
#define EFL_DECLARE_RETS_2 RET_2 ret2;
#define EFL_DECLARE_RETS_3 RET_2 ret2; RET_3 ret3;
#define EFL_DECLARE_RETS_4 RET_2 ret2; RET_3 ret3; RET_4 ret4;
#define EFL_DECLARE_RETS_5 RET_2 ret2; RET_3 ret3; RET_4 ret4; RET_5 ret5;

// fill in the arguments in the run-time function call
#define EFL_GET_ARGS_0 ;
#define EFL_GET_ARGS_1 ARG_1 arg1 = to<ARG_1>(L, -1);
#define EFL_GET_ARGS_2 ARG_1 arg1 = to<ARG_1>(L, -2); ARG_2 arg2 = to<ARG_2>(L, -1);
#define EFL_GET_ARGS_3 ARG_1 arg1 = to<ARG_1>(L, -3); ARG_2 arg2 = to<ARG_2>(L, -2); ARG_3 arg3 = to<ARG_3>(L, -1);
#define EFL_GET_ARGS_4 ARG_1 arg1 = to<ARG_1>(L, -4); ARG_2 arg2 = to<ARG_2>(L, -3); ARG_3 arg3 = to<ARG_3>(L, -2); ARG_4 arg4 = to<ARG_4>(L, -1);
#define EFL_GET_ARGS_5 ARG_1 arg1 = to<ARG_1>(L, -5); ARG_2 arg2 = to<ARG_2>(L, -4); ARG_3 arg3 = to<ARG_3>(L, -3); ARG_4 arg4 = to<ARG_4>(L, -2); ARG_5 arg5 = to<ARG_5>(L, -1);

// assign the value of the function
#define EFL_ASSIGN_RETS_0
#define EFL_ASSIGN_RETS_1 RET_1 ret1 = 
#define EFL_ASSIGN_RETS_2 RET_1 ret1 = 
#define EFL_ASSIGN_RETS_3 RET_1 ret1 = 
#define EFL_ASSIGN_RETS_4 RET_1 ret1 = 
#define EFL_ASSIGN_RETS_5 RET_1 ret1 = 

// pass in the arguments to the function
#define EFL_CALL_RETS_0_ARGS_0 
#define EFL_CALL_RETS_0_ARGS_1 arg1
#define EFL_CALL_RETS_0_ARGS_2 arg1, arg2
#define EFL_CALL_RETS_0_ARGS_3 arg1, arg2, arg3
#define EFL_CALL_RETS_0_ARGS_4 arg1, arg2, arg3, arg4
#define EFL_CALL_RETS_0_ARGS_5 arg1, arg2, arg3, arg4, arg5

#define EFL_CALL_RETS_1_ARGS_0 
#define EFL_CALL_RETS_1_ARGS_1 arg1
#define EFL_CALL_RETS_1_ARGS_2 arg1, arg2
#define EFL_CALL_RETS_1_ARGS_3 arg1, arg2, arg3
#define EFL_CALL_RETS_1_ARGS_4 arg1, arg2, arg3, arg4
#define EFL_CALL_RETS_1_ARGS_5 arg1, arg2, arg3, arg4, arg5

#define EFL_CALL_RETS_2_ARGS_0 ret2
#define EFL_CALL_RETS_2_ARGS_1 ret2, arg1
#define EFL_CALL_RETS_2_ARGS_2 ret2, arg1, arg2
#define EFL_CALL_RETS_2_ARGS_3 ret2, arg1, arg2, arg3
#define EFL_CALL_RETS_2_ARGS_4 ret2, arg1, arg2, arg3, arg4
#define EFL_CALL_RETS_2_ARGS_5 ret2, arg1, arg2, arg3, arg4, arg5

#define EFL_CALL_RETS_3_ARGS_0 ret2, ret3
#define EFL_CALL_RETS_3_ARGS_1 ret2, ret3, arg1
#define EFL_CALL_RETS_3_ARGS_2 ret2, ret3, arg1, arg2
#define EFL_CALL_RETS_3_ARGS_3 ret2, ret3, arg1, arg2, arg3
#define EFL_CALL_RETS_3_ARGS_4 ret2, ret3, arg1, arg2, arg3, arg4
#define EFL_CALL_RETS_3_ARGS_5 ret2, ret3, arg1, arg2, arg3, arg4, arg5

#define EFL_CALL_RETS_4_ARGS_0 ret2, ret3, ret4 
#define EFL_CALL_RETS_4_ARGS_1 ret2, ret3, ret4, arg1
#define EFL_CALL_RETS_4_ARGS_2 ret2, ret3, ret4, arg1, arg2
#define EFL_CALL_RETS_4_ARGS_3 ret2, ret3, ret4, arg1, arg2, arg3
#define EFL_CALL_RETS_4_ARGS_4 ret2, ret3, ret4, arg1, arg2, arg3, arg4
#define EFL_CALL_RETS_4_ARGS_5 ret2, ret3, ret4, arg1, arg2, arg3, arg4, arg5

#define EFL_CALL_RETS_5_ARGS_0 ret2, ret3, ret4, ret5
#define EFL_CALL_RETS_5_ARGS_1 ret2, ret3, ret4, ret5, arg1
#define EFL_CALL_RETS_5_ARGS_2 ret2, ret3, ret4, ret5, arg1, arg2
#define EFL_CALL_RETS_5_ARGS_3 ret2, ret3, ret4, ret5, arg1, arg2, arg3
#define EFL_CALL_RETS_5_ARGS_4 ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4
#define EFL_CALL_RETS_5_ARGS_5 ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4, arg5

// push the appropriate number of values back to %Lua
#define EFL_PUSH_RETS_0 ;
#define EFL_PUSH_RETS_1 pushed += push(L, ret1); 
#define EFL_PUSH_RETS_2 pushed += push(L, ret1); pushed += push(L, ret2); 
#define EFL_PUSH_RETS_3 pushed += push(L, ret1); pushed += push(L, ret2); pushed += push(L, ret3);
#define EFL_PUSH_RETS_4 pushed += push(L, ret1); pushed += push(L, ret2); pushed += push(L, ret3); pushed += push(L, ret4);
#define EFL_PUSH_RETS_5 pushed += push(L, ret1); pushed += push(L, ret2); pushed += push(L, ret3); pushed += push(L, ret4); pushed += push(L, ret5);

// get the instance of the object of the 
#define EFL_GET_INSTANCE_ARGS_0 to<CLASS*>(L, -1)
#define EFL_GET_INSTANCE_ARGS_1 to<CLASS*>(L, -2)
#define EFL_GET_INSTANCE_ARGS_2 to<CLASS*>(L, -3)
#define EFL_GET_INSTANCE_ARGS_3 to<CLASS*>(L, -4)
#define EFL_GET_INSTANCE_ARGS_4 to<CLASS*>(L, -5)
#define EFL_GET_INSTANCE_ARGS_5 to<CLASS*>(L, -6)

// begin the static function template declaration
#define EFL_BEGIN_STATIC_TEMPLATE_ARGS \
	template< 

// begin the class function template declaration
#define EFL_BEGIN_CLASS_TEMPLATE_ARGS \
	template<typename CLASS

// end the static function template declaration
#define EFL_END_STATIC_TEMPLATE_ARGS(num_rets, num_args) \
	EFL_TEMPLATE_RETURN_SIGNATURE_RETS_##num_rets (* function)(EFL_TEMPLATE_ARGS_SIGNATURE_RETS_##num_rets##_ARGS_##num_args) >

// end the class member function template declaration
#define EFL_END_CLASS_TEMPLATE_ARGS(num_rets, num_args) \
	EFL_TEMPLATE_RETURN_SIGNATURE_RETS_##num_rets (CLASS::* function)(EFL_TEMPLATE_ARGS_SIGNATURE_RETS_##num_rets##_ARGS_##num_args) >

// end the class const member function template declaration
#define EFL_END_CONST_CLASS_TEMPLATE_ARGS(num_rets, num_args) \
	EFL_TEMPLATE_RETURN_SIGNATURE_RETS_##num_rets (CLASS::* function)(EFL_TEMPLATE_ARGS_SIGNATURE_RETS_##num_rets##_ARGS_##num_args) const>

// and implement the class member function
#define EFL_CLASS_IMPLEMENTATION(num_rets, num_args) \
	{ \
		if (CLASS* object = EFL_GET_INSTANCE_ARGS_##num_args) \
		{ \
			sint pushed(0); \
			EFL_DECLARE_RETS_##num_rets \
			EFL_GET_ARGS_##num_args \
			EFL_ASSIGN_RETS_##num_rets (object->*function)(EFL_CALL_RETS_##num_rets##_ARGS_##num_args); \
			EFL_PUSH_RETS_##num_rets \
			return pushed; \
		} \
		return 0; \
	}

// declare and implement the template non-member static function
#define EFL_STATIC(num_rets, num_args) \
	inline sint staticReturn##num_rets##Param##num_args##(lua_State* L) \
	{ \
		sint pushed(0); \
		EFL_DECLARE_RETS_##num_rets \
		EFL_GET_ARGS_##num_args \
		EFL_ASSIGN_RETS_##num_rets (*function)(EFL_CALL_RETS_##num_rets##_ARGS_##num_args); \
		EFL_PUSH_RETS_##num_rets \
		return pushed; \
	}

// declare and implement the class member function
#define EFL_CLASS(num_rets, num_args) \
	inline sint return##num_rets##Param##num_args##(lua_State* L) \
	EFL_CLASS_IMPLEMENTATION(num_rets, num_args)

// declare and implement the class const member function
#define EFL_CONST_CLASS(num_rets, num_args) \
	inline sint return##num_rets##Param##num_args##const(lua_State* L) \
	EFL_CLASS_IMPLEMENTATION(num_rets, num_args)

// define a static function with the specified number of arguments
#define EFL_GENERATE_STATIC_TEMPLATE(num_rets, num_args) \
	EFL_BEGIN_STATIC_TEMPLATE_ARGS \
	EFL_TEMPLATE_ARGS_RETS_##num_rets##_ARGS_##num_args \
	EFL_END_STATIC_TEMPLATE_ARGS(num_rets, num_args) \
	EFL_STATIC(num_rets, num_args)

// define a class member function with the specified number of arguments
#define EFL_GENERATE_CLASS_TEMPLATE(num_rets, num_args) \
	EFL_BEGIN_CLASS_TEMPLATE_ARGS, \
	EFL_TEMPLATE_ARGS_RETS_##num_rets##_ARGS_##num_args \
	EFL_END_CLASS_TEMPLATE_ARGS(num_rets, num_args) \
	EFL_CLASS(num_rets, num_args)

// define a class const member function with the specified number of arguments
#define EFL_GENERATE_CLASS_CONST_TEMPLATE(num_rets, num_args) \
	EFL_BEGIN_CLASS_TEMPLATE_ARGS, \
	EFL_TEMPLATE_ARGS_RETS_##num_rets##_ARGS_##num_args \
	EFL_END_CONST_CLASS_TEMPLATE_ARGS(num_rets, num_args) \
	EFL_CONST_CLASS(num_rets, num_args)


namespace luaExtension
{
/** static, non-member functions */
EFL_GENERATE_STATIC_TEMPLATE(0, 1)
EFL_GENERATE_STATIC_TEMPLATE(0, 2)
EFL_GENERATE_STATIC_TEMPLATE(0, 3)
EFL_GENERATE_STATIC_TEMPLATE(0, 4)
EFL_GENERATE_STATIC_TEMPLATE(0, 5)

EFL_GENERATE_STATIC_TEMPLATE(1, 0)
EFL_GENERATE_STATIC_TEMPLATE(1, 1)
EFL_GENERATE_STATIC_TEMPLATE(1, 2)
EFL_GENERATE_STATIC_TEMPLATE(1, 3)
EFL_GENERATE_STATIC_TEMPLATE(1, 4)
EFL_GENERATE_STATIC_TEMPLATE(1, 5)

EFL_GENERATE_STATIC_TEMPLATE(2, 0)
EFL_GENERATE_STATIC_TEMPLATE(2, 1)
EFL_GENERATE_STATIC_TEMPLATE(2, 2)
EFL_GENERATE_STATIC_TEMPLATE(2, 3)
EFL_GENERATE_STATIC_TEMPLATE(2, 4)
EFL_GENERATE_STATIC_TEMPLATE(2, 5)

EFL_GENERATE_STATIC_TEMPLATE(3, 0)
EFL_GENERATE_STATIC_TEMPLATE(3, 1)
EFL_GENERATE_STATIC_TEMPLATE(3, 2)
EFL_GENERATE_STATIC_TEMPLATE(3, 3)
EFL_GENERATE_STATIC_TEMPLATE(3, 4)
EFL_GENERATE_STATIC_TEMPLATE(3, 5)

EFL_GENERATE_STATIC_TEMPLATE(4, 0)
EFL_GENERATE_STATIC_TEMPLATE(4, 1)
EFL_GENERATE_STATIC_TEMPLATE(4, 2)
EFL_GENERATE_STATIC_TEMPLATE(4, 3)
EFL_GENERATE_STATIC_TEMPLATE(4, 4)
EFL_GENERATE_STATIC_TEMPLATE(4, 5)

EFL_GENERATE_STATIC_TEMPLATE(5, 0)
EFL_GENERATE_STATIC_TEMPLATE(5, 1)
EFL_GENERATE_STATIC_TEMPLATE(5, 2)
EFL_GENERATE_STATIC_TEMPLATE(5, 3)
EFL_GENERATE_STATIC_TEMPLATE(5, 4)
EFL_GENERATE_STATIC_TEMPLATE(5, 5)

/** class member functions */
EFL_GENERATE_CLASS_TEMPLATE(0, 1)
EFL_GENERATE_CLASS_TEMPLATE(0, 2)
EFL_GENERATE_CLASS_TEMPLATE(0, 3)
EFL_GENERATE_CLASS_TEMPLATE(0, 4)
EFL_GENERATE_CLASS_TEMPLATE(0, 5)

EFL_GENERATE_CLASS_TEMPLATE(1, 0)
EFL_GENERATE_CLASS_TEMPLATE(1, 1)
EFL_GENERATE_CLASS_TEMPLATE(1, 2)
EFL_GENERATE_CLASS_TEMPLATE(1, 3)
EFL_GENERATE_CLASS_TEMPLATE(1, 4)
EFL_GENERATE_CLASS_TEMPLATE(1, 5)

EFL_GENERATE_CLASS_TEMPLATE(2, 0)
EFL_GENERATE_CLASS_TEMPLATE(2, 1)
EFL_GENERATE_CLASS_TEMPLATE(2, 2)
EFL_GENERATE_CLASS_TEMPLATE(2, 3)
EFL_GENERATE_CLASS_TEMPLATE(2, 4)
EFL_GENERATE_CLASS_TEMPLATE(2, 5)

EFL_GENERATE_CLASS_TEMPLATE(3, 0)
EFL_GENERATE_CLASS_TEMPLATE(3, 1)
EFL_GENERATE_CLASS_TEMPLATE(3, 2)
EFL_GENERATE_CLASS_TEMPLATE(3, 3)
EFL_GENERATE_CLASS_TEMPLATE(3, 4)
EFL_GENERATE_CLASS_TEMPLATE(3, 5)

EFL_GENERATE_CLASS_TEMPLATE(4, 0)
EFL_GENERATE_CLASS_TEMPLATE(4, 1)
EFL_GENERATE_CLASS_TEMPLATE(4, 2)
EFL_GENERATE_CLASS_TEMPLATE(4, 3)
EFL_GENERATE_CLASS_TEMPLATE(4, 4)
EFL_GENERATE_CLASS_TEMPLATE(4, 5)

EFL_GENERATE_CLASS_TEMPLATE(5, 0)
EFL_GENERATE_CLASS_TEMPLATE(5, 1)
EFL_GENERATE_CLASS_TEMPLATE(5, 2)
EFL_GENERATE_CLASS_TEMPLATE(5, 3)
EFL_GENERATE_CLASS_TEMPLATE(5, 4)
EFL_GENERATE_CLASS_TEMPLATE(5, 5)

/** const class member functions */
EFL_GENERATE_CLASS_CONST_TEMPLATE(0, 1)
EFL_GENERATE_CLASS_CONST_TEMPLATE(0, 2)
EFL_GENERATE_CLASS_CONST_TEMPLATE(0, 3)
EFL_GENERATE_CLASS_CONST_TEMPLATE(0, 4)
EFL_GENERATE_CLASS_CONST_TEMPLATE(0, 5)

EFL_GENERATE_CLASS_CONST_TEMPLATE(1, 0)
EFL_GENERATE_CLASS_CONST_TEMPLATE(1, 1)
EFL_GENERATE_CLASS_CONST_TEMPLATE(1, 2)
EFL_GENERATE_CLASS_CONST_TEMPLATE(1, 3)
EFL_GENERATE_CLASS_CONST_TEMPLATE(1, 4)
EFL_GENERATE_CLASS_CONST_TEMPLATE(1, 5)

EFL_GENERATE_CLASS_CONST_TEMPLATE(2, 0)
EFL_GENERATE_CLASS_CONST_TEMPLATE(2, 1)
EFL_GENERATE_CLASS_CONST_TEMPLATE(2, 2)
EFL_GENERATE_CLASS_CONST_TEMPLATE(2, 3)
EFL_GENERATE_CLASS_CONST_TEMPLATE(2, 4)
EFL_GENERATE_CLASS_CONST_TEMPLATE(2, 5)

EFL_GENERATE_CLASS_CONST_TEMPLATE(3, 0)
EFL_GENERATE_CLASS_CONST_TEMPLATE(3, 1)
EFL_GENERATE_CLASS_CONST_TEMPLATE(3, 2)
EFL_GENERATE_CLASS_CONST_TEMPLATE(3, 3)
EFL_GENERATE_CLASS_CONST_TEMPLATE(3, 4)
EFL_GENERATE_CLASS_CONST_TEMPLATE(3, 5)

EFL_GENERATE_CLASS_CONST_TEMPLATE(4, 0)
EFL_GENERATE_CLASS_CONST_TEMPLATE(4, 1)
EFL_GENERATE_CLASS_CONST_TEMPLATE(4, 2)
EFL_GENERATE_CLASS_CONST_TEMPLATE(4, 3)
EFL_GENERATE_CLASS_CONST_TEMPLATE(4, 4)
EFL_GENERATE_CLASS_CONST_TEMPLATE(4, 5)

EFL_GENERATE_CLASS_CONST_TEMPLATE(5, 0)
EFL_GENERATE_CLASS_CONST_TEMPLATE(5, 1)
EFL_GENERATE_CLASS_CONST_TEMPLATE(5, 2)
EFL_GENERATE_CLASS_CONST_TEMPLATE(5, 3)
EFL_GENERATE_CLASS_CONST_TEMPLATE(5, 4)
EFL_GENERATE_CLASS_CONST_TEMPLATE(5, 5)

} // namespace luaExtension

#endif//LUAFUNCTIONEXPOSITION_H

