#pragma once
#ifndef LUAFUNCTIONEXPOSITION_H
#define LUAFUNCTIONEXPOSITION_H
/**
\file LuaFunctionExposition.h

\brief This file attempts to make even easier the generation C++ functions
that are exposed to Lua.

\author Smoke and Mirrors Development
\htmlonly
<A HREF="smokeandmirrorsdevelopment@gmail.com">
smokeandmirrorsdevelopment@gmail.com</A>
<BR>
&copy;2009-2011 Smoke and Mirrors Development
<BR>
\endhtmlonly
\date 2/18/2010

\warning THIS FUNCTIONALITY IS NOT THREAD SAFE.

<DEVELOPMENT STATUS>
Current Draft		:	1.0
Current Phase		:   FIELD TESTING
Purpose				:	DEPLOYMENT
Unit Tested			:	YES
Used in development	:	YES
Used in experiments :	YES
Tested in the field	:	YES

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
inline sint memberReturn0Param1(lua_State* L);

template<typename CLASS, typename RET_1, RET_1 (CLASS::* function)(void)>
inline sint memberReturn1Param0(lua_State* L);

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
inline sint const_Return1Param0(lua_State* L);

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
sreal Vector3::dot(const Vector3& v) const; // member function, 1 return value, 1 argument
\endcode

wrapper:
\code
const_Return1Param1<Vector3, sreal, const Vector3&, &Vector3::dot>
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

If you need to add another function for a not present number of arguments,
make sure that the template arguments macros are present in 
TemplateArguments.h:
CW_TEMPLATE_ARGS_RETS_
CW_TEMPLATE_RETURN_SIGNATURE_
CW_DECLARE_RETS_
CW_ASSIGN_RETS_
CW_CALL_RETS_

And then make sure the necessary arguments are present below:
EFL_GET_ARGS_
EFL_PUSH_RETS_
EFL_GET_INSTANCE_ARGS_

\todo optional arguments (should be nearly trivial, but annoying to write)

*/

#include "Build.h"
#include "LuaExtensibility.h"
#include "LuaInclusions.h"
#include "LuaStateInteraction.h"
#include "TemplateArguments.h"

namespace lua_extension
{
	template<void(* function)(void)> 
	inline sint staticReturn0Param0(lua_State* L)
	{
		(*function)();
		return 0;
	}

	template<typename CLASS, void(CLASS::* function)(void)>
	inline sint memberReturn0Param0(lua_State* L)
	{
		if (CLASS* object = to<CLASS*>(L, -1))
		{
			(object->*function)();
		}
		return 0;	
	}

	template<typename CLASS, void(CLASS::* function)(void) const>
	inline sint const_Return0Param0(lua_State* L)
	{
		if (CLASS* object = to<CLASS*>(L, -1))
		{
			(object->*function)();
		}
		return 0;	
	}
} // namespace lua_extension


/** function implementation */
// fill in the arguments in the run-time function call
#define EFL_GET_ARGS_0 ;
#define EFL_GET_ARGS_1 ARG_1 arg1 = to<ARG_1>(L, -1);
#define EFL_GET_ARGS_2 ARG_1 arg1 = to<ARG_1>(L, -2); ARG_2 arg2 = to<ARG_2>(L, -1);
#define EFL_GET_ARGS_3 ARG_1 arg1 = to<ARG_1>(L, -3); ARG_2 arg2 = to<ARG_2>(L, -2); ARG_3 arg3 = to<ARG_3>(L, -1);
#define EFL_GET_ARGS_4 ARG_1 arg1 = to<ARG_1>(L, -4); ARG_2 arg2 = to<ARG_2>(L, -3); ARG_3 arg3 = to<ARG_3>(L, -2); ARG_4 arg4 = to<ARG_4>(L, -1);
#define EFL_GET_ARGS_5 ARG_1 arg1 = to<ARG_1>(L, -5); ARG_2 arg2 = to<ARG_2>(L, -4); ARG_3 arg3 = to<ARG_3>(L, -3); ARG_4 arg4 = to<ARG_4>(L, -2); ARG_5 arg5 = to<ARG_5>(L, -1);

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
#define EFL_END_STATIC_TEMPLATE_ARGS(NUM_RETS, NUM_ARGS) \
	CW_TEMPLATE_RETURN_SIGNATURE_RETS_##NUM_RETS (* function)(CW_TEMPLATE_ARGS_SIGNATURE_RETS_##NUM_RETS##_ARGS_##NUM_ARGS) >

// end the class member function template declaration
#define EFL_END_CLASS_TEMPLATE_ARGS(NUM_RETS, NUM_ARGS) \
	CW_TEMPLATE_RETURN_SIGNATURE_RETS_##NUM_RETS (CLASS::* function)(CW_TEMPLATE_ARGS_SIGNATURE_RETS_##NUM_RETS##_ARGS_##NUM_ARGS) >

// end the class const member function template declaration
#define EFL_END_CONST_CLASS_TEMPLATE_ARGS(NUM_RETS, NUM_ARGS) \
	CW_TEMPLATE_RETURN_SIGNATURE_RETS_##NUM_RETS (CLASS::* function)(CW_TEMPLATE_ARGS_SIGNATURE_RETS_##NUM_RETS##_ARGS_##NUM_ARGS) const>

// and implement the class member function
#define EFL_CLASS_IMPLEMENTATION(NUM_RETS, NUM_ARGS) \
	{ \
		if (CLASS* object = EFL_GET_INSTANCE_ARGS_##NUM_ARGS) \
		{ \
			sint pushed(0); \
			CW_DECLARE_RETS_##NUM_RETS \
			EFL_GET_ARGS_##NUM_ARGS \
			CW_ASSIGN_RETS_##NUM_RETS (object->*function)(CW_CALL_RETS_##NUM_RETS##_ARGS_##NUM_ARGS); \
			EFL_PUSH_RETS_##NUM_RETS \
			return pushed; \
		} \
		return 0; \
	}

// declare and implement the template non-member static function
#define EFL_STATIC(NUM_RETS, NUM_ARGS) \
	inline LUA_FUNC(staticReturn##NUM_RETS##Param##NUM_ARGS) \
	{ \
		sint pushed(0); \
		CW_DECLARE_RETS_##NUM_RETS \
		EFL_GET_ARGS_##NUM_ARGS \
		CW_ASSIGN_RETS_##NUM_RETS (*function)(CW_CALL_RETS_##NUM_RETS##_ARGS_##NUM_ARGS); \
		EFL_PUSH_RETS_##NUM_RETS \
		return pushed; \
	}

// declare and implement the class member function
#define EFL_CLASS(NUM_RETS, NUM_ARGS) \
	inline LUA_FUNC(memberReturn##NUM_RETS##Param##NUM_ARGS) \
	EFL_CLASS_IMPLEMENTATION(NUM_RETS, NUM_ARGS)

// declare and implement the class const member function
#define EFL_CONST_CLASS(NUM_RETS, NUM_ARGS) \
	inline LUA_FUNC(const_Return##NUM_RETS##Param##NUM_ARGS) \
	EFL_CLASS_IMPLEMENTATION(NUM_RETS, NUM_ARGS)

// define a static function with the specified number of arguments
#define EFL_GENERATE_STATIC_TEMPLATE(NUM_RETS, NUM_ARGS) \
	EFL_BEGIN_STATIC_TEMPLATE_ARGS \
	CW_TEMPLATE_ARGS_RETS_##NUM_RETS##_ARGS_##NUM_ARGS, \
	EFL_END_STATIC_TEMPLATE_ARGS(NUM_RETS, NUM_ARGS) \
	EFL_STATIC(NUM_RETS, NUM_ARGS)

// define a class member function with the specified number of arguments
#define EFL_GENERATE_CLASS_TEMPLATE(NUM_RETS, NUM_ARGS) \
	EFL_BEGIN_CLASS_TEMPLATE_ARGS, \
	CW_TEMPLATE_ARGS_RETS_##NUM_RETS##_ARGS_##NUM_ARGS, \
	EFL_END_CLASS_TEMPLATE_ARGS(NUM_RETS, NUM_ARGS) \
	EFL_CLASS(NUM_RETS, NUM_ARGS)

// define a class const member function with the specified number of arguments
#define EFL_GENERATE_CLASS_CONST_TEMPLATE(NUM_RETS, NUM_ARGS) \
	EFL_BEGIN_CLASS_TEMPLATE_ARGS, \
	CW_TEMPLATE_ARGS_RETS_##NUM_RETS##_ARGS_##NUM_ARGS, \
	EFL_END_CONST_CLASS_TEMPLATE_ARGS(NUM_RETS, NUM_ARGS) \
	EFL_CONST_CLASS(NUM_RETS, NUM_ARGS)

// define all argument #, parameter # functions of the generation_macro
#define EFL_GENERATE_ALL(generation_macro) \
	generation_macro(0, 1) \
	generation_macro(0, 2) \
	generation_macro(0, 3) \
	generation_macro(0, 4) \
	generation_macro(0, 5) \
	generation_macro(1, 0) \
	generation_macro(1, 1) \
	generation_macro(1, 2) \
	generation_macro(1, 3) \
	generation_macro(1, 4) \
	generation_macro(1, 5) \
	generation_macro(2, 0) \
	generation_macro(2, 1) \
	generation_macro(2, 2) \
	generation_macro(2, 3) \
	generation_macro(2, 4) \
	generation_macro(2, 5) \
	generation_macro(3, 0) \
	generation_macro(3, 1) \
	generation_macro(3, 2) \
	generation_macro(3, 3) \
	generation_macro(3, 4) \
	generation_macro(3, 5) \
	generation_macro(4, 0) \
	generation_macro(4, 1) \
	generation_macro(4, 2) \
	generation_macro(4, 3) \
	generation_macro(4, 4) \
	generation_macro(4, 5) \
	generation_macro(5, 0) \
	generation_macro(5, 1) \
	generation_macro(5, 2) \
	generation_macro(5, 3) \
	generation_macro(5, 4) \
	generation_macro(5, 5) 

namespace lua_extension
{
/** static, non-member functions */
EFL_GENERATE_ALL(EFL_GENERATE_STATIC_TEMPLATE)
/** class member functions */
EFL_GENERATE_ALL(EFL_GENERATE_CLASS_TEMPLATE)
/** const class member functions */
EFL_GENERATE_ALL(EFL_GENERATE_CLASS_CONST_TEMPLATE)
} // namespace lua_extension

#endif//LUAFUNCTIONEXPOSITION_H

