#pragma once
#ifndef LUA_EXPOSE_NATIVE_TO_SCRIPT_H
#define LUA_EXPOSE_NATIVE_TO_SCRIPT_H
/**
\file LuaExposeNativeToScript.h

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
1. static:	nativeStaticReturn<# of return values>Param<# of parameters>\n
2. class:	return<# of return values>Param<# of parameters>{const}\n

The following templates are currently defined by way of the macros below:
\code
//////////////////////////////////////////////////////////////////////////
// static non member functions: 
template<typename ARG_1, void (* function)(ARG_1)> 
inline sint nativeStaticReturn0Param1(lua_State* L);

template<typename RET_1, RET_1 (* function)(void)>
inline sint nativeStaticReturn1Param0(lua_State* L);

// ... 

template<typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, RET_1 (*function)(RET_2&, ARG_1, ARG_2)>
inline sint nativeStaticReturn2Param2(lua_State* L);

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
inline sint nativeReturn0Param1(lua_State* L);

template<typename CLASS, typename RET_1, RET_1 (CLASS::* function)(void)>
inline sint nativeReturn1Param0(lua_State* L);

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
inline sint nativeReturn1Param0(lua_State* L);

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
nativeReturn1Param1<Vector3, sreal, const Vector3&, &Vector3::dot>
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
\note EN2S_ here means "Expose Function to Lua.."
\see the simplest examples below

If you need to add another function for a not present number of arguments,
make sure that the template arguments macros are present in 
TemplateArguments.h:
CW_TEMPLATE_ARGS_RETS_
CW_TEMPLATE_RETURN_SIGNATURE_
CW_DECLARE_RETS_
CW_DECLARE_1_ASSIGN_RETS_
CW_CALL_RETS_

And then make sure the necessary arguments are present below:
EN2S_GET_ARGS_
EN2S_PUSH_RETS_
EN2S_GET_INSTANCE_ARGS_

\todo optional arguments (should be nearly trivial, but annoying to write)

*/

#include "Build.h"
#include "LuaExtensibility.h"
#include "LuaInclusions.h"
#include "LuaStateInteraction.h"
#include "TemplateArguments.h"

// begin the class function template declaration
#define EN2S_BEGIN_CLASS_TEMPLATE_ARGS \
	template<typename CLASS

// begin the static function template declaration
#define EN2S_BEGIN_STATIC_TEMPLATE_ARGS \
	template< 

// declare and implement the class member function
#define EN2S_CLASS(NUM_RETS, NUM_ARGS) \
	inline LUA_FUNC(nativeMemberReturn##NUM_RETS##Param##NUM_ARGS) \
	EN2S_CLASS_IMPLEMENTATION(NUM_RETS, NUM_ARGS)

// and implement the class member function
#define EN2S_CLASS_IMPLEMENTATION(NUM_RETS, NUM_ARGS) \
	{ \
		if (CLASS* object = EN2S_GET_INSTANCE_ARGS_##NUM_ARGS) \
		{ \
			sint pushed(0); \
			CW_DECLARE_RETS_##NUM_RETS \
			EN2S_GET_ARGS_##NUM_ARGS \
			CW_DECLARE_1_ASSIGN_RETS_##NUM_RETS (object->*function)(CW_CALL_RETS_##NUM_RETS##_ARGS_##NUM_ARGS); \
			EN2S_PUSH_RETS_##NUM_RETS \
			return pushed; \
		} \
		return 0; \
	}

// declare and implement the class const member function
#define EN2S_CONST_CLASS(NUM_RETS, NUM_ARGS) \
	inline LUA_FUNC(nativeConstReturn##NUM_RETS##Param##NUM_ARGS) \
	EN2S_CLASS_IMPLEMENTATION(NUM_RETS, NUM_ARGS)

// end the class member function template declaration
#define EN2S_END_CLASS_TEMPLATE_ARGS(NUM_RETS, NUM_ARGS) \
	CW_TEMPLATE_RETURN_SIGNATURE_RETS_##NUM_RETS (CLASS::* function)(CW_TEMPLATE_ARGS_SIGNATURE_RETS_##NUM_RETS##_ARGS_##NUM_ARGS) >

// end the class const member function template declaration
#define EN2S_END_CONST_CLASS_TEMPLATE_ARGS(NUM_RETS, NUM_ARGS) \
	CW_TEMPLATE_RETURN_SIGNATURE_RETS_##NUM_RETS (CLASS::* function)(CW_TEMPLATE_ARGS_SIGNATURE_RETS_##NUM_RETS##_ARGS_##NUM_ARGS) const>

// end the static function template declaration
#define EN2S_END_STATIC_TEMPLATE_ARGS(NUM_RETS, NUM_ARGS) \
	CW_TEMPLATE_RETURN_SIGNATURE_RETS_##NUM_RETS (* function)(CW_TEMPLATE_ARGS_SIGNATURE_RETS_##NUM_RETS##_ARGS_##NUM_ARGS) >

// define a class const member function with the specified number of arguments
#define EN2S_GENERATE_CLASS_CONST_TEMPLATE(NUM_RETS, NUM_ARGS) \
	EN2S_BEGIN_CLASS_TEMPLATE_ARGS, \
	CW_TEMPLATE_ARGS_RETS_##NUM_RETS##_ARGS_##NUM_ARGS, \
	EN2S_END_CONST_CLASS_TEMPLATE_ARGS(NUM_RETS, NUM_ARGS) \
	EN2S_CONST_CLASS(NUM_RETS, NUM_ARGS)

// define a class member function with the specified number of arguments
#define EN2S_GENERATE_CLASS_TEMPLATE(NUM_RETS, NUM_ARGS) \
	EN2S_BEGIN_CLASS_TEMPLATE_ARGS, \
	CW_TEMPLATE_ARGS_RETS_##NUM_RETS##_ARGS_##NUM_ARGS, \
	EN2S_END_CLASS_TEMPLATE_ARGS(NUM_RETS, NUM_ARGS) \
	EN2S_CLASS(NUM_RETS, NUM_ARGS)

// define a static function with the specified number of arguments
#define EN2S_GENERATE_STATIC_TEMPLATE(NUM_RETS, NUM_ARGS) \
	EN2S_BEGIN_STATIC_TEMPLATE_ARGS \
	CW_TEMPLATE_ARGS_RETS_##NUM_RETS##_ARGS_##NUM_ARGS, \
	EN2S_END_STATIC_TEMPLATE_ARGS(NUM_RETS, NUM_ARGS) \
	EN2S_STATIC(NUM_RETS, NUM_ARGS)

// fill in the arguments in the run-time function call
#define EN2S_GET_ARGS_0 ;
#define EN2S_GET_ARGS_1 ARG_1 arg1 = to<ARG_1>(L, -1);
#define EN2S_GET_ARGS_2 ARG_1 arg1 = to<ARG_1>(L, -2); ARG_2 arg2 = to<ARG_2>(L, -1);
#define EN2S_GET_ARGS_3 ARG_1 arg1 = to<ARG_1>(L, -3); ARG_2 arg2 = to<ARG_2>(L, -2); ARG_3 arg3 = to<ARG_3>(L, -1);
#define EN2S_GET_ARGS_4 ARG_1 arg1 = to<ARG_1>(L, -4); ARG_2 arg2 = to<ARG_2>(L, -3); ARG_3 arg3 = to<ARG_3>(L, -2); ARG_4 arg4 = to<ARG_4>(L, -1);
#define EN2S_GET_ARGS_5 ARG_1 arg1 = to<ARG_1>(L, -5); ARG_2 arg2 = to<ARG_2>(L, -4); ARG_3 arg3 = to<ARG_3>(L, -3); ARG_4 arg4 = to<ARG_4>(L, -2); ARG_5 arg5 = to<ARG_5>(L, -1);

// get the instance of the object of the 
#define EN2S_GET_INSTANCE_ARGS_0 to<CLASS*>(L, -1)
#define EN2S_GET_INSTANCE_ARGS_1 to<CLASS*>(L, -2)
#define EN2S_GET_INSTANCE_ARGS_2 to<CLASS*>(L, -3)
#define EN2S_GET_INSTANCE_ARGS_3 to<CLASS*>(L, -4)
#define EN2S_GET_INSTANCE_ARGS_4 to<CLASS*>(L, -5)
#define EN2S_GET_INSTANCE_ARGS_5 to<CLASS*>(L, -6)

// push the appropriate number of values back to %Lua
#define EN2S_PUSH_RETS_0 ;
#define EN2S_PUSH_RETS_1 pushed += push(L, ret1); 
#define EN2S_PUSH_RETS_2 pushed += push(L, ret1); pushed += push(L, ret2); 
#define EN2S_PUSH_RETS_3 pushed += push(L, ret1); pushed += push(L, ret2); pushed += push(L, ret3);
#define EN2S_PUSH_RETS_4 pushed += push(L, ret1); pushed += push(L, ret2); pushed += push(L, ret3); pushed += push(L, ret4);
#define EN2S_PUSH_RETS_5 pushed += push(L, ret1); pushed += push(L, ret2); pushed += push(L, ret3); pushed += push(L, ret4); pushed += push(L, ret5);

// declare and implement the template non-member static function
#define EN2S_STATIC(NUM_RETS, NUM_ARGS) \
	inline LUA_FUNC(nativeStaticReturn##NUM_RETS##Param##NUM_ARGS) \
	{ \
		sint pushed(0); \
		CW_DECLARE_RETS_##NUM_RETS \
		EN2S_GET_ARGS_##NUM_ARGS \
		CW_DECLARE_1_ASSIGN_RETS_##NUM_RETS (*function)(CW_CALL_RETS_##NUM_RETS##_ARGS_##NUM_ARGS); \
		EN2S_PUSH_RETS_##NUM_RETS \
		return pushed; \
	}

namespace lua_extension
{
	template<void(* function)(void)> 
	inline sint nativeStaticReturn0Param0(lua_State*)
	{
		(*function)();
		return 0;
	}

	template<typename CLASS, void(CLASS::* function)(void)>
	inline sint nativeMemberReturn0Param0(lua_State* L)
	{
		if (CLASS* object = to<CLASS*>(L, -1))
		{
			(object->*function)();
		}
		return 0;	
	}

	template<typename CLASS, void(CLASS::* function)(void) const>
	inline sint nativeConstReturn0Param0(lua_State* L)
	{
		if (CLASS* object = to<CLASS*>(L, -1))
		{
			(object->*function)();
		}
		return 0;	
	}
	
	

	//test generateStaticTemplate
	template< typename ARG_1, void (* function)(ARG_1) >
	inline LUA_FUNC(nativeStaticReturn0Param1)
	{
		(*function)(to<ARG_1>(L, -1));
		return 0;
	} // nativeStaticReturn0Param1

	//test generateStaticTemplate
	template< typename ARG_1, typename ARG_2, void (* function)(ARG_1, ARG_2) >
	inline LUA_FUNC(nativeStaticReturn0Param2)
	{
		(*function)(to<ARG_1>(L, -2), to<ARG_2>(L, -1));
		return 0;
	} // nativeStaticReturn0Param2

	//test generateStaticTemplate
	template< typename ARG_1, typename ARG_2, typename ARG_3, void (* function)(ARG_1, ARG_2, ARG_3) >
	inline LUA_FUNC(nativeStaticReturn0Param3)
	{
		(*function)(to<ARG_1>(L, -3), to<ARG_2>(L, -2), to<ARG_3>(L, -1));
		return 0;
	} // nativeStaticReturn0Param3

	//test generateStaticTemplate
	template< typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, void (* function)(ARG_1, ARG_2, ARG_3, ARG_4) >
	inline LUA_FUNC(nativeStaticReturn0Param4)
	{
		(*function)(to<ARG_1>(L, -4), to<ARG_2>(L, -3), to<ARG_3>(L, -2), to<ARG_4>(L, -1));
		return 0;
	} // nativeStaticReturn0Param4

	//test generateStaticTemplate
	template< typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, void (* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
	inline LUA_FUNC(nativeStaticReturn0Param5)
	{
		(*function)(to<ARG_1>(L, -5), to<ARG_2>(L, -4), to<ARG_3>(L, -3), to<ARG_4>(L, -2), to<ARG_5>(L, -1));
		return 0;
	} // nativeStaticReturn0Param5

	//test generateStaticTemplate
	template< typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, void (* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
	inline LUA_FUNC(nativeStaticReturn0Param6)
	{
		(*function)(to<ARG_1>(L, -6), to<ARG_2>(L, -5), to<ARG_3>(L, -4), to<ARG_4>(L, -3), to<ARG_5>(L, -2), to<ARG_6>(L, -1));
		return 0;
	} // nativeStaticReturn0Param6

	//test generateStaticTemplate
	template< typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, void (* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
	inline LUA_FUNC(nativeStaticReturn0Param7)
	{
		(*function)(to<ARG_1>(L, -7), to<ARG_2>(L, -6), to<ARG_3>(L, -5), to<ARG_4>(L, -4), to<ARG_5>(L, -3), to<ARG_6>(L, -2), to<ARG_7>(L, -1));
		return 0;
	} // nativeStaticReturn0Param7

	//test generateStaticTemplate
	template< typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, void (* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
	inline LUA_FUNC(nativeStaticReturn0Param8)
	{
		(*function)(to<ARG_1>(L, -8), to<ARG_2>(L, -7), to<ARG_3>(L, -6), to<ARG_4>(L, -5), to<ARG_5>(L, -4), to<ARG_6>(L, -3), to<ARG_7>(L, -2), to<ARG_8>(L, -1));
		return 0;
	} // nativeStaticReturn0Param8

	//test generateStaticTemplate
	template< typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, void (* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
	inline LUA_FUNC(nativeStaticReturn0Param9)
	{
		(*function)(to<ARG_1>(L, -9), to<ARG_2>(L, -8), to<ARG_3>(L, -7), to<ARG_4>(L, -6), to<ARG_5>(L, -5), to<ARG_6>(L, -4), to<ARG_7>(L, -3), to<ARG_8>(L, -2), to<ARG_9>(L, -1));
		return 0;
	} // nativeStaticReturn0Param9

	//test generateStaticTemplate
	template< typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, void (* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
	inline LUA_FUNC(nativeStaticReturn0Param10)
	{
		(*function)(to<ARG_1>(L, -10), to<ARG_2>(L, -9), to<ARG_3>(L, -8), to<ARG_4>(L, -7), to<ARG_5>(L, -6), to<ARG_6>(L, -5), to<ARG_7>(L, -4), to<ARG_8>(L, -3), to<ARG_9>(L, -2), to<ARG_10>(L, -1));
		return 0;
	} // nativeStaticReturn0Param10

	//test generateStaticTemplate
	template< typename RET_1, RET_1 (* function)(void) >
	inline LUA_FUNC(nativeStaticReturn1Param0)
	{
		RET_1 ret1 = (*function)();
		sint pushed(push(L, ret1));
		return pushed;
	} // nativeStaticReturn1Param0

	//test generateStaticTemplate
	template< typename RET_1, typename ARG_1, RET_1 (* function)(ARG_1) >
	inline LUA_FUNC(nativeStaticReturn1Param1)
	{
		RET_1 ret1 = (*function)(to<ARG_1>(L, -1));
		sint pushed(push(L, ret1));
		return pushed;
	} // nativeStaticReturn1Param1

	//test generateStaticTemplate
	template< typename RET_1, typename ARG_1, typename ARG_2, RET_1 (* function)(ARG_1, ARG_2) >
	inline LUA_FUNC(nativeStaticReturn1Param2)
	{
		RET_1 ret1 = (*function)(to<ARG_1>(L, -2), to<ARG_2>(L, -1));
		sint pushed(push(L, ret1));
		return pushed;
	} // nativeStaticReturn1Param2

	//test generateStaticTemplate
	template< typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (* function)(ARG_1, ARG_2, ARG_3) >
	inline LUA_FUNC(nativeStaticReturn1Param3)
	{
		RET_1 ret1 = (*function)(to<ARG_1>(L, -3), to<ARG_2>(L, -2), to<ARG_3>(L, -1));
		sint pushed(push(L, ret1));
		return pushed;
	} // nativeStaticReturn1Param3

	//test generateStaticTemplate
	template< typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (* function)(ARG_1, ARG_2, ARG_3, ARG_4) >
	inline LUA_FUNC(nativeStaticReturn1Param4)
	{
		RET_1 ret1 = (*function)(to<ARG_1>(L, -4), to<ARG_2>(L, -3), to<ARG_3>(L, -2), to<ARG_4>(L, -1));
		sint pushed(push(L, ret1));
		return pushed;
	} // nativeStaticReturn1Param4

	//test generateStaticTemplate
	template< typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
	inline LUA_FUNC(nativeStaticReturn1Param5)
	{
		RET_1 ret1 = (*function)(to<ARG_1>(L, -5), to<ARG_2>(L, -4), to<ARG_3>(L, -3), to<ARG_4>(L, -2), to<ARG_5>(L, -1));
		sint pushed(push(L, ret1));
		return pushed;
	} // nativeStaticReturn1Param5

	//test generateStaticTemplate
	template< typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
	inline LUA_FUNC(nativeStaticReturn1Param6)
	{
		RET_1 ret1 = (*function)(to<ARG_1>(L, -6), to<ARG_2>(L, -5), to<ARG_3>(L, -4), to<ARG_4>(L, -3), to<ARG_5>(L, -2), to<ARG_6>(L, -1));
		sint pushed(push(L, ret1));
		return pushed;
	} // nativeStaticReturn1Param6

	//test generateStaticTemplate
	template< typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
	inline LUA_FUNC(nativeStaticReturn1Param7)
	{
		RET_1 ret1 = (*function)(to<ARG_1>(L, -7), to<ARG_2>(L, -6), to<ARG_3>(L, -5), to<ARG_4>(L, -4), to<ARG_5>(L, -3), to<ARG_6>(L, -2), to<ARG_7>(L, -1));
		sint pushed(push(L, ret1));
		return pushed;
	} // nativeStaticReturn1Param7

	//test generateStaticTemplate
	template< typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
	inline LUA_FUNC(nativeStaticReturn1Param8)
	{
		RET_1 ret1 = (*function)(to<ARG_1>(L, -8), to<ARG_2>(L, -7), to<ARG_3>(L, -6), to<ARG_4>(L, -5), to<ARG_5>(L, -4), to<ARG_6>(L, -3), to<ARG_7>(L, -2), to<ARG_8>(L, -1));
		sint pushed(push(L, ret1));
		return pushed;
	} // nativeStaticReturn1Param8

	//test generateStaticTemplate
	template< typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
	inline LUA_FUNC(nativeStaticReturn1Param9)
	{
		RET_1 ret1 = (*function)(to<ARG_1>(L, -9), to<ARG_2>(L, -8), to<ARG_3>(L, -7), to<ARG_4>(L, -6), to<ARG_5>(L, -5), to<ARG_6>(L, -4), to<ARG_7>(L, -3), to<ARG_8>(L, -2), to<ARG_9>(L, -1));
		sint pushed(push(L, ret1));
		return pushed;
	} // nativeStaticReturn1Param9

	//test generateStaticTemplate
	template< typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
	inline LUA_FUNC(nativeStaticReturn1Param10)
	{
		RET_1 ret1 = (*function)(to<ARG_1>(L, -10), to<ARG_2>(L, -9), to<ARG_3>(L, -8), to<ARG_4>(L, -7), to<ARG_5>(L, -6), to<ARG_6>(L, -5), to<ARG_7>(L, -4), to<ARG_8>(L, -3), to<ARG_9>(L, -2), to<ARG_10>(L, -1));
		sint pushed(push(L, ret1));
		return pushed;
	} // nativeStaticReturn1Param10

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, RET_1 (* function)(RET_2&) >
	inline LUA_FUNC(nativeStaticReturn2Param0)
	{
		RET_2 ret2;
		RET_1 ret1 = (*function)(ret2);
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		return pushed;
	} // nativeStaticReturn2Param0

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename ARG_1, RET_1 (* function)(RET_2&, ARG_1) >
	inline LUA_FUNC(nativeStaticReturn2Param1)
	{
		RET_2 ret2;
		RET_1 ret1 = (*function)(ret2, to<ARG_1>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		return pushed;
	} // nativeStaticReturn2Param1

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, RET_1 (* function)(RET_2&, ARG_1, ARG_2) >
	inline LUA_FUNC(nativeStaticReturn2Param2)
	{
		RET_2 ret2;
		RET_1 ret1 = (*function)(ret2, to<ARG_1>(L, -2), to<ARG_2>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		return pushed;
	} // nativeStaticReturn2Param2

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (* function)(RET_2&, ARG_1, ARG_2, ARG_3) >
	inline LUA_FUNC(nativeStaticReturn2Param3)
	{
		RET_2 ret2;
		RET_1 ret1 = (*function)(ret2, to<ARG_1>(L, -3), to<ARG_2>(L, -2), to<ARG_3>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		return pushed;
	} // nativeStaticReturn2Param3

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4) >
	inline LUA_FUNC(nativeStaticReturn2Param4)
	{
		RET_2 ret2;
		RET_1 ret1 = (*function)(ret2, to<ARG_1>(L, -4), to<ARG_2>(L, -3), to<ARG_3>(L, -2), to<ARG_4>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		return pushed;
	} // nativeStaticReturn2Param4

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
	inline LUA_FUNC(nativeStaticReturn2Param5)
	{
		RET_2 ret2;
		RET_1 ret1 = (*function)(ret2, to<ARG_1>(L, -5), to<ARG_2>(L, -4), to<ARG_3>(L, -3), to<ARG_4>(L, -2), to<ARG_5>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		return pushed;
	} // nativeStaticReturn2Param5

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
	inline LUA_FUNC(nativeStaticReturn2Param6)
	{
		RET_2 ret2;
		RET_1 ret1 = (*function)(ret2, to<ARG_1>(L, -6), to<ARG_2>(L, -5), to<ARG_3>(L, -4), to<ARG_4>(L, -3), to<ARG_5>(L, -2), to<ARG_6>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		return pushed;
	} // nativeStaticReturn2Param6

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
	inline LUA_FUNC(nativeStaticReturn2Param7)
	{
		RET_2 ret2;
		RET_1 ret1 = (*function)(ret2, to<ARG_1>(L, -7), to<ARG_2>(L, -6), to<ARG_3>(L, -5), to<ARG_4>(L, -4), to<ARG_5>(L, -3), to<ARG_6>(L, -2), to<ARG_7>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		return pushed;
	} // nativeStaticReturn2Param7

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
	inline LUA_FUNC(nativeStaticReturn2Param8)
	{
		RET_2 ret2;
		RET_1 ret1 = (*function)(ret2, to<ARG_1>(L, -8), to<ARG_2>(L, -7), to<ARG_3>(L, -6), to<ARG_4>(L, -5), to<ARG_5>(L, -4), to<ARG_6>(L, -3), to<ARG_7>(L, -2), to<ARG_8>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		return pushed;
	} // nativeStaticReturn2Param8

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
	inline LUA_FUNC(nativeStaticReturn2Param9)
	{
		RET_2 ret2;
		RET_1 ret1 = (*function)(ret2, to<ARG_1>(L, -9), to<ARG_2>(L, -8), to<ARG_3>(L, -7), to<ARG_4>(L, -6), to<ARG_5>(L, -5), to<ARG_6>(L, -4), to<ARG_7>(L, -3), to<ARG_8>(L, -2), to<ARG_9>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		return pushed;
	} // nativeStaticReturn2Param9

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
	inline LUA_FUNC(nativeStaticReturn2Param10)
	{
		RET_2 ret2;
		RET_1 ret1 = (*function)(ret2, to<ARG_1>(L, -10), to<ARG_2>(L, -9), to<ARG_3>(L, -8), to<ARG_4>(L, -7), to<ARG_5>(L, -6), to<ARG_6>(L, -5), to<ARG_7>(L, -4), to<ARG_8>(L, -3), to<ARG_9>(L, -2), to<ARG_10>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		return pushed;
	} // nativeStaticReturn2Param10

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, RET_1 (* function)(RET_2&, RET_3&) >
	inline LUA_FUNC(nativeStaticReturn3Param0)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_1 ret1 = (*function)(ret2, ret3);
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		return pushed;
	} // nativeStaticReturn3Param0

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename ARG_1, RET_1 (* function)(RET_2&, RET_3&, ARG_1) >
	inline LUA_FUNC(nativeStaticReturn3Param1)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_1 ret1 = (*function)(ret2, ret3, to<ARG_1>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		return pushed;
	} // nativeStaticReturn3Param1

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, RET_1 (* function)(RET_2&, RET_3&, ARG_1, ARG_2) >
	inline LUA_FUNC(nativeStaticReturn3Param2)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_1 ret1 = (*function)(ret2, ret3, to<ARG_1>(L, -2), to<ARG_2>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		return pushed;
	} // nativeStaticReturn3Param2

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3) >
	inline LUA_FUNC(nativeStaticReturn3Param3)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_1 ret1 = (*function)(ret2, ret3, to<ARG_1>(L, -3), to<ARG_2>(L, -2), to<ARG_3>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		return pushed;
	} // nativeStaticReturn3Param3

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4) >
	inline LUA_FUNC(nativeStaticReturn3Param4)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_1 ret1 = (*function)(ret2, ret3, to<ARG_1>(L, -4), to<ARG_2>(L, -3), to<ARG_3>(L, -2), to<ARG_4>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		return pushed;
	} // nativeStaticReturn3Param4

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
	inline LUA_FUNC(nativeStaticReturn3Param5)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_1 ret1 = (*function)(ret2, ret3, to<ARG_1>(L, -5), to<ARG_2>(L, -4), to<ARG_3>(L, -3), to<ARG_4>(L, -2), to<ARG_5>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		return pushed;
	} // nativeStaticReturn3Param5

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
	inline LUA_FUNC(nativeStaticReturn3Param6)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_1 ret1 = (*function)(ret2, ret3, to<ARG_1>(L, -6), to<ARG_2>(L, -5), to<ARG_3>(L, -4), to<ARG_4>(L, -3), to<ARG_5>(L, -2), to<ARG_6>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		return pushed;
	} // nativeStaticReturn3Param6

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
	inline LUA_FUNC(nativeStaticReturn3Param7)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_1 ret1 = (*function)(ret2, ret3, to<ARG_1>(L, -7), to<ARG_2>(L, -6), to<ARG_3>(L, -5), to<ARG_4>(L, -4), to<ARG_5>(L, -3), to<ARG_6>(L, -2), to<ARG_7>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		return pushed;
	} // nativeStaticReturn3Param7

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
	inline LUA_FUNC(nativeStaticReturn3Param8)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_1 ret1 = (*function)(ret2, ret3, to<ARG_1>(L, -8), to<ARG_2>(L, -7), to<ARG_3>(L, -6), to<ARG_4>(L, -5), to<ARG_5>(L, -4), to<ARG_6>(L, -3), to<ARG_7>(L, -2), to<ARG_8>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		return pushed;
	} // nativeStaticReturn3Param8

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
	inline LUA_FUNC(nativeStaticReturn3Param9)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_1 ret1 = (*function)(ret2, ret3, to<ARG_1>(L, -9), to<ARG_2>(L, -8), to<ARG_3>(L, -7), to<ARG_4>(L, -6), to<ARG_5>(L, -5), to<ARG_6>(L, -4), to<ARG_7>(L, -3), to<ARG_8>(L, -2), to<ARG_9>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		return pushed;
	} // nativeStaticReturn3Param9

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
	inline LUA_FUNC(nativeStaticReturn3Param10)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_1 ret1 = (*function)(ret2, ret3, to<ARG_1>(L, -10), to<ARG_2>(L, -9), to<ARG_3>(L, -8), to<ARG_4>(L, -7), to<ARG_5>(L, -6), to<ARG_6>(L, -5), to<ARG_7>(L, -4), to<ARG_8>(L, -3), to<ARG_9>(L, -2), to<ARG_10>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		return pushed;
	} // nativeStaticReturn3Param10

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, RET_1 (* function)(RET_2&, RET_3&, RET_4&) >
	inline LUA_FUNC(nativeStaticReturn4Param0)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_1 ret1 = (*function)(ret2, ret3, ret4);
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		return pushed;
	} // nativeStaticReturn4Param0

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, RET_1 (* function)(RET_2&, RET_3&, RET_4&, ARG_1) >
	inline LUA_FUNC(nativeStaticReturn4Param1)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, to<ARG_1>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		return pushed;
	} // nativeStaticReturn4Param1

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, RET_1 (* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2) >
	inline LUA_FUNC(nativeStaticReturn4Param2)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, to<ARG_1>(L, -2), to<ARG_2>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		return pushed;
	} // nativeStaticReturn4Param2

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3) >
	inline LUA_FUNC(nativeStaticReturn4Param3)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, to<ARG_1>(L, -3), to<ARG_2>(L, -2), to<ARG_3>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		return pushed;
	} // nativeStaticReturn4Param3

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4) >
	inline LUA_FUNC(nativeStaticReturn4Param4)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, to<ARG_1>(L, -4), to<ARG_2>(L, -3), to<ARG_3>(L, -2), to<ARG_4>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		return pushed;
	} // nativeStaticReturn4Param4

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
	inline LUA_FUNC(nativeStaticReturn4Param5)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, to<ARG_1>(L, -5), to<ARG_2>(L, -4), to<ARG_3>(L, -3), to<ARG_4>(L, -2), to<ARG_5>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		return pushed;
	} // nativeStaticReturn4Param5

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
	inline LUA_FUNC(nativeStaticReturn4Param6)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, to<ARG_1>(L, -6), to<ARG_2>(L, -5), to<ARG_3>(L, -4), to<ARG_4>(L, -3), to<ARG_5>(L, -2), to<ARG_6>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		return pushed;
	} // nativeStaticReturn4Param6

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
	inline LUA_FUNC(nativeStaticReturn4Param7)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, to<ARG_1>(L, -7), to<ARG_2>(L, -6), to<ARG_3>(L, -5), to<ARG_4>(L, -4), to<ARG_5>(L, -3), to<ARG_6>(L, -2), to<ARG_7>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		return pushed;
	} // nativeStaticReturn4Param7

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
	inline LUA_FUNC(nativeStaticReturn4Param8)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, to<ARG_1>(L, -8), to<ARG_2>(L, -7), to<ARG_3>(L, -6), to<ARG_4>(L, -5), to<ARG_5>(L, -4), to<ARG_6>(L, -3), to<ARG_7>(L, -2), to<ARG_8>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		return pushed;
	} // nativeStaticReturn4Param8

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
	inline LUA_FUNC(nativeStaticReturn4Param9)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, to<ARG_1>(L, -9), to<ARG_2>(L, -8), to<ARG_3>(L, -7), to<ARG_4>(L, -6), to<ARG_5>(L, -5), to<ARG_6>(L, -4), to<ARG_7>(L, -3), to<ARG_8>(L, -2), to<ARG_9>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		return pushed;
	} // nativeStaticReturn4Param9

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
	inline LUA_FUNC(nativeStaticReturn4Param10)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, to<ARG_1>(L, -10), to<ARG_2>(L, -9), to<ARG_3>(L, -8), to<ARG_4>(L, -7), to<ARG_5>(L, -6), to<ARG_6>(L, -5), to<ARG_7>(L, -4), to<ARG_8>(L, -3), to<ARG_9>(L, -2), to<ARG_10>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		return pushed;
	} // nativeStaticReturn4Param10

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&) >
	inline LUA_FUNC(nativeStaticReturn5Param0)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5);
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		return pushed;
	} // nativeStaticReturn5Param0

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1) >
	inline LUA_FUNC(nativeStaticReturn5Param1)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, to<ARG_1>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		return pushed;
	} // nativeStaticReturn5Param1

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2) >
	inline LUA_FUNC(nativeStaticReturn5Param2)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, to<ARG_1>(L, -2), to<ARG_2>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		return pushed;
	} // nativeStaticReturn5Param2

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3) >
	inline LUA_FUNC(nativeStaticReturn5Param3)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, to<ARG_1>(L, -3), to<ARG_2>(L, -2), to<ARG_3>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		return pushed;
	} // nativeStaticReturn5Param3

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4) >
	inline LUA_FUNC(nativeStaticReturn5Param4)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, to<ARG_1>(L, -4), to<ARG_2>(L, -3), to<ARG_3>(L, -2), to<ARG_4>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		return pushed;
	} // nativeStaticReturn5Param4

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
	inline LUA_FUNC(nativeStaticReturn5Param5)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, to<ARG_1>(L, -5), to<ARG_2>(L, -4), to<ARG_3>(L, -3), to<ARG_4>(L, -2), to<ARG_5>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		return pushed;
	} // nativeStaticReturn5Param5

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
	inline LUA_FUNC(nativeStaticReturn5Param6)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, to<ARG_1>(L, -6), to<ARG_2>(L, -5), to<ARG_3>(L, -4), to<ARG_4>(L, -3), to<ARG_5>(L, -2), to<ARG_6>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		return pushed;
	} // nativeStaticReturn5Param6

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
	inline LUA_FUNC(nativeStaticReturn5Param7)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, to<ARG_1>(L, -7), to<ARG_2>(L, -6), to<ARG_3>(L, -5), to<ARG_4>(L, -4), to<ARG_5>(L, -3), to<ARG_6>(L, -2), to<ARG_7>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		return pushed;
	} // nativeStaticReturn5Param7

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
	inline LUA_FUNC(nativeStaticReturn5Param8)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, to<ARG_1>(L, -8), to<ARG_2>(L, -7), to<ARG_3>(L, -6), to<ARG_4>(L, -5), to<ARG_5>(L, -4), to<ARG_6>(L, -3), to<ARG_7>(L, -2), to<ARG_8>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		return pushed;
	} // nativeStaticReturn5Param8

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
	inline LUA_FUNC(nativeStaticReturn5Param9)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, to<ARG_1>(L, -9), to<ARG_2>(L, -8), to<ARG_3>(L, -7), to<ARG_4>(L, -6), to<ARG_5>(L, -5), to<ARG_6>(L, -4), to<ARG_7>(L, -3), to<ARG_8>(L, -2), to<ARG_9>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		return pushed;
	} // nativeStaticReturn5Param9

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
	inline LUA_FUNC(nativeStaticReturn5Param10)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, to<ARG_1>(L, -10), to<ARG_2>(L, -9), to<ARG_3>(L, -8), to<ARG_4>(L, -7), to<ARG_5>(L, -6), to<ARG_6>(L, -5), to<ARG_7>(L, -4), to<ARG_8>(L, -3), to<ARG_9>(L, -2), to<ARG_10>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		return pushed;
	} // nativeStaticReturn5Param10

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&) >
	inline LUA_FUNC(nativeStaticReturn6Param0)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6);
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		return pushed;
	} // nativeStaticReturn6Param0

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1) >
	inline LUA_FUNC(nativeStaticReturn6Param1)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, to<ARG_1>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		return pushed;
	} // nativeStaticReturn6Param1

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2) >
	inline LUA_FUNC(nativeStaticReturn6Param2)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, to<ARG_1>(L, -2), to<ARG_2>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		return pushed;
	} // nativeStaticReturn6Param2

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3) >
	inline LUA_FUNC(nativeStaticReturn6Param3)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, to<ARG_1>(L, -3), to<ARG_2>(L, -2), to<ARG_3>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		return pushed;
	} // nativeStaticReturn6Param3

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4) >
	inline LUA_FUNC(nativeStaticReturn6Param4)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, to<ARG_1>(L, -4), to<ARG_2>(L, -3), to<ARG_3>(L, -2), to<ARG_4>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		return pushed;
	} // nativeStaticReturn6Param4

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
	inline LUA_FUNC(nativeStaticReturn6Param5)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, to<ARG_1>(L, -5), to<ARG_2>(L, -4), to<ARG_3>(L, -3), to<ARG_4>(L, -2), to<ARG_5>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		return pushed;
	} // nativeStaticReturn6Param5

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
	inline LUA_FUNC(nativeStaticReturn6Param6)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, to<ARG_1>(L, -6), to<ARG_2>(L, -5), to<ARG_3>(L, -4), to<ARG_4>(L, -3), to<ARG_5>(L, -2), to<ARG_6>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		return pushed;
	} // nativeStaticReturn6Param6

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
	inline LUA_FUNC(nativeStaticReturn6Param7)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, to<ARG_1>(L, -7), to<ARG_2>(L, -6), to<ARG_3>(L, -5), to<ARG_4>(L, -4), to<ARG_5>(L, -3), to<ARG_6>(L, -2), to<ARG_7>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		return pushed;
	} // nativeStaticReturn6Param7

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
	inline LUA_FUNC(nativeStaticReturn6Param8)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, to<ARG_1>(L, -8), to<ARG_2>(L, -7), to<ARG_3>(L, -6), to<ARG_4>(L, -5), to<ARG_5>(L, -4), to<ARG_6>(L, -3), to<ARG_7>(L, -2), to<ARG_8>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		return pushed;
	} // nativeStaticReturn6Param8

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
	inline LUA_FUNC(nativeStaticReturn6Param9)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, to<ARG_1>(L, -9), to<ARG_2>(L, -8), to<ARG_3>(L, -7), to<ARG_4>(L, -6), to<ARG_5>(L, -5), to<ARG_6>(L, -4), to<ARG_7>(L, -3), to<ARG_8>(L, -2), to<ARG_9>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		return pushed;
	} // nativeStaticReturn6Param9

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
	inline LUA_FUNC(nativeStaticReturn6Param10)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, to<ARG_1>(L, -10), to<ARG_2>(L, -9), to<ARG_3>(L, -8), to<ARG_4>(L, -7), to<ARG_5>(L, -6), to<ARG_6>(L, -5), to<ARG_7>(L, -4), to<ARG_8>(L, -3), to<ARG_9>(L, -2), to<ARG_10>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		return pushed;
	} // nativeStaticReturn6Param10

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&) >
	inline LUA_FUNC(nativeStaticReturn7Param0)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7);
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		return pushed;
	} // nativeStaticReturn7Param0

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1) >
	inline LUA_FUNC(nativeStaticReturn7Param1)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, to<ARG_1>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		return pushed;
	} // nativeStaticReturn7Param1

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2) >
	inline LUA_FUNC(nativeStaticReturn7Param2)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, to<ARG_1>(L, -2), to<ARG_2>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		return pushed;
	} // nativeStaticReturn7Param2

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3) >
	inline LUA_FUNC(nativeStaticReturn7Param3)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, to<ARG_1>(L, -3), to<ARG_2>(L, -2), to<ARG_3>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		return pushed;
	} // nativeStaticReturn7Param3

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4) >
	inline LUA_FUNC(nativeStaticReturn7Param4)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, to<ARG_1>(L, -4), to<ARG_2>(L, -3), to<ARG_3>(L, -2), to<ARG_4>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		return pushed;
	} // nativeStaticReturn7Param4

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
	inline LUA_FUNC(nativeStaticReturn7Param5)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, to<ARG_1>(L, -5), to<ARG_2>(L, -4), to<ARG_3>(L, -3), to<ARG_4>(L, -2), to<ARG_5>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		return pushed;
	} // nativeStaticReturn7Param5

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
	inline LUA_FUNC(nativeStaticReturn7Param6)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, to<ARG_1>(L, -6), to<ARG_2>(L, -5), to<ARG_3>(L, -4), to<ARG_4>(L, -3), to<ARG_5>(L, -2), to<ARG_6>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		return pushed;
	} // nativeStaticReturn7Param6

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
	inline LUA_FUNC(nativeStaticReturn7Param7)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, to<ARG_1>(L, -7), to<ARG_2>(L, -6), to<ARG_3>(L, -5), to<ARG_4>(L, -4), to<ARG_5>(L, -3), to<ARG_6>(L, -2), to<ARG_7>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		return pushed;
	} // nativeStaticReturn7Param7

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
	inline LUA_FUNC(nativeStaticReturn7Param8)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, to<ARG_1>(L, -8), to<ARG_2>(L, -7), to<ARG_3>(L, -6), to<ARG_4>(L, -5), to<ARG_5>(L, -4), to<ARG_6>(L, -3), to<ARG_7>(L, -2), to<ARG_8>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		return pushed;
	} // nativeStaticReturn7Param8

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
	inline LUA_FUNC(nativeStaticReturn7Param9)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, to<ARG_1>(L, -9), to<ARG_2>(L, -8), to<ARG_3>(L, -7), to<ARG_4>(L, -6), to<ARG_5>(L, -5), to<ARG_6>(L, -4), to<ARG_7>(L, -3), to<ARG_8>(L, -2), to<ARG_9>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		return pushed;
	} // nativeStaticReturn7Param9

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
	inline LUA_FUNC(nativeStaticReturn7Param10)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, to<ARG_1>(L, -10), to<ARG_2>(L, -9), to<ARG_3>(L, -8), to<ARG_4>(L, -7), to<ARG_5>(L, -6), to<ARG_6>(L, -5), to<ARG_7>(L, -4), to<ARG_8>(L, -3), to<ARG_9>(L, -2), to<ARG_10>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		return pushed;
	} // nativeStaticReturn7Param10

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&) >
	inline LUA_FUNC(nativeStaticReturn8Param0)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8);
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		pushed += push(L, ret8);
		return pushed;
	} // nativeStaticReturn8Param0

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1) >
	inline LUA_FUNC(nativeStaticReturn8Param1)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, to<ARG_1>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		pushed += push(L, ret8);
		return pushed;
	} // nativeStaticReturn8Param1

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2) >
	inline LUA_FUNC(nativeStaticReturn8Param2)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, to<ARG_1>(L, -2), to<ARG_2>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		pushed += push(L, ret8);
		return pushed;
	} // nativeStaticReturn8Param2

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3) >
	inline LUA_FUNC(nativeStaticReturn8Param3)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, to<ARG_1>(L, -3), to<ARG_2>(L, -2), to<ARG_3>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		pushed += push(L, ret8);
		return pushed;
	} // nativeStaticReturn8Param3

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4) >
	inline LUA_FUNC(nativeStaticReturn8Param4)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, to<ARG_1>(L, -4), to<ARG_2>(L, -3), to<ARG_3>(L, -2), to<ARG_4>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		pushed += push(L, ret8);
		return pushed;
	} // nativeStaticReturn8Param4

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
	inline LUA_FUNC(nativeStaticReturn8Param5)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, to<ARG_1>(L, -5), to<ARG_2>(L, -4), to<ARG_3>(L, -3), to<ARG_4>(L, -2), to<ARG_5>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		pushed += push(L, ret8);
		return pushed;
	} // nativeStaticReturn8Param5

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
	inline LUA_FUNC(nativeStaticReturn8Param6)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, to<ARG_1>(L, -6), to<ARG_2>(L, -5), to<ARG_3>(L, -4), to<ARG_4>(L, -3), to<ARG_5>(L, -2), to<ARG_6>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		pushed += push(L, ret8);
		return pushed;
	} // nativeStaticReturn8Param6

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
	inline LUA_FUNC(nativeStaticReturn8Param7)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, to<ARG_1>(L, -7), to<ARG_2>(L, -6), to<ARG_3>(L, -5), to<ARG_4>(L, -4), to<ARG_5>(L, -3), to<ARG_6>(L, -2), to<ARG_7>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		pushed += push(L, ret8);
		return pushed;
	} // nativeStaticReturn8Param7

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
	inline LUA_FUNC(nativeStaticReturn8Param8)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, to<ARG_1>(L, -8), to<ARG_2>(L, -7), to<ARG_3>(L, -6), to<ARG_4>(L, -5), to<ARG_5>(L, -4), to<ARG_6>(L, -3), to<ARG_7>(L, -2), to<ARG_8>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		pushed += push(L, ret8);
		return pushed;
	} // nativeStaticReturn8Param8

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
	inline LUA_FUNC(nativeStaticReturn8Param9)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, to<ARG_1>(L, -9), to<ARG_2>(L, -8), to<ARG_3>(L, -7), to<ARG_4>(L, -6), to<ARG_5>(L, -5), to<ARG_6>(L, -4), to<ARG_7>(L, -3), to<ARG_8>(L, -2), to<ARG_9>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		pushed += push(L, ret8);
		return pushed;
	} // nativeStaticReturn8Param9

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
	inline LUA_FUNC(nativeStaticReturn8Param10)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, to<ARG_1>(L, -10), to<ARG_2>(L, -9), to<ARG_3>(L, -8), to<ARG_4>(L, -7), to<ARG_5>(L, -6), to<ARG_6>(L, -5), to<ARG_7>(L, -4), to<ARG_8>(L, -3), to<ARG_9>(L, -2), to<ARG_10>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		pushed += push(L, ret8);
		return pushed;
	} // nativeStaticReturn8Param10

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&) >
	inline LUA_FUNC(nativeStaticReturn9Param0)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_9 ret9;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9);
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		pushed += push(L, ret8);
		pushed += push(L, ret9);
		return pushed;
	} // nativeStaticReturn9Param0

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1) >
	inline LUA_FUNC(nativeStaticReturn9Param1)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_9 ret9;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, to<ARG_1>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		pushed += push(L, ret8);
		pushed += push(L, ret9);
		return pushed;
	} // nativeStaticReturn9Param1

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2) >
	inline LUA_FUNC(nativeStaticReturn9Param2)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_9 ret9;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, to<ARG_1>(L, -2), to<ARG_2>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		pushed += push(L, ret8);
		pushed += push(L, ret9);
		return pushed;
	} // nativeStaticReturn9Param2

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3) >
	inline LUA_FUNC(nativeStaticReturn9Param3)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_9 ret9;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, to<ARG_1>(L, -3), to<ARG_2>(L, -2), to<ARG_3>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		pushed += push(L, ret8);
		pushed += push(L, ret9);
		return pushed;
	} // nativeStaticReturn9Param3

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4) >
	inline LUA_FUNC(nativeStaticReturn9Param4)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_9 ret9;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, to<ARG_1>(L, -4), to<ARG_2>(L, -3), to<ARG_3>(L, -2), to<ARG_4>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		pushed += push(L, ret8);
		pushed += push(L, ret9);
		return pushed;
	} // nativeStaticReturn9Param4

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
	inline LUA_FUNC(nativeStaticReturn9Param5)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_9 ret9;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, to<ARG_1>(L, -5), to<ARG_2>(L, -4), to<ARG_3>(L, -3), to<ARG_4>(L, -2), to<ARG_5>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		pushed += push(L, ret8);
		pushed += push(L, ret9);
		return pushed;
	} // nativeStaticReturn9Param5

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
	inline LUA_FUNC(nativeStaticReturn9Param6)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_9 ret9;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, to<ARG_1>(L, -6), to<ARG_2>(L, -5), to<ARG_3>(L, -4), to<ARG_4>(L, -3), to<ARG_5>(L, -2), to<ARG_6>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		pushed += push(L, ret8);
		pushed += push(L, ret9);
		return pushed;
	} // nativeStaticReturn9Param6

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
	inline LUA_FUNC(nativeStaticReturn9Param7)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_9 ret9;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, to<ARG_1>(L, -7), to<ARG_2>(L, -6), to<ARG_3>(L, -5), to<ARG_4>(L, -4), to<ARG_5>(L, -3), to<ARG_6>(L, -2), to<ARG_7>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		pushed += push(L, ret8);
		pushed += push(L, ret9);
		return pushed;
	} // nativeStaticReturn9Param7

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
	inline LUA_FUNC(nativeStaticReturn9Param8)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_9 ret9;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, to<ARG_1>(L, -8), to<ARG_2>(L, -7), to<ARG_3>(L, -6), to<ARG_4>(L, -5), to<ARG_5>(L, -4), to<ARG_6>(L, -3), to<ARG_7>(L, -2), to<ARG_8>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		pushed += push(L, ret8);
		pushed += push(L, ret9);
		return pushed;
	} // nativeStaticReturn9Param8

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
	inline LUA_FUNC(nativeStaticReturn9Param9)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_9 ret9;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, to<ARG_1>(L, -9), to<ARG_2>(L, -8), to<ARG_3>(L, -7), to<ARG_4>(L, -6), to<ARG_5>(L, -5), to<ARG_6>(L, -4), to<ARG_7>(L, -3), to<ARG_8>(L, -2), to<ARG_9>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		pushed += push(L, ret8);
		pushed += push(L, ret9);
		return pushed;
	} // nativeStaticReturn9Param9

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
	inline LUA_FUNC(nativeStaticReturn9Param10)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_9 ret9;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, to<ARG_1>(L, -10), to<ARG_2>(L, -9), to<ARG_3>(L, -8), to<ARG_4>(L, -7), to<ARG_5>(L, -6), to<ARG_6>(L, -5), to<ARG_7>(L, -4), to<ARG_8>(L, -3), to<ARG_9>(L, -2), to<ARG_10>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		pushed += push(L, ret8);
		pushed += push(L, ret9);
		return pushed;
	} // nativeStaticReturn9Param10

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&) >
	inline LUA_FUNC(nativeStaticReturn10Param0)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_9 ret9;
		RET_10 ret10;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10);
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		pushed += push(L, ret8);
		pushed += push(L, ret9);
		pushed += push(L, ret10);
		return pushed;
	} // nativeStaticReturn10Param0

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1) >
	inline LUA_FUNC(nativeStaticReturn10Param1)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_9 ret9;
		RET_10 ret10;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, to<ARG_1>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		pushed += push(L, ret8);
		pushed += push(L, ret9);
		pushed += push(L, ret10);
		return pushed;
	} // nativeStaticReturn10Param1

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2) >
	inline LUA_FUNC(nativeStaticReturn10Param2)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_9 ret9;
		RET_10 ret10;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, to<ARG_1>(L, -2), to<ARG_2>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		pushed += push(L, ret8);
		pushed += push(L, ret9);
		pushed += push(L, ret10);
		return pushed;
	} // nativeStaticReturn10Param2

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3) >
	inline LUA_FUNC(nativeStaticReturn10Param3)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_9 ret9;
		RET_10 ret10;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, to<ARG_1>(L, -3), to<ARG_2>(L, -2), to<ARG_3>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		pushed += push(L, ret8);
		pushed += push(L, ret9);
		pushed += push(L, ret10);
		return pushed;
	} // nativeStaticReturn10Param3

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4) >
	inline LUA_FUNC(nativeStaticReturn10Param4)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_9 ret9;
		RET_10 ret10;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, to<ARG_1>(L, -4), to<ARG_2>(L, -3), to<ARG_3>(L, -2), to<ARG_4>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		pushed += push(L, ret8);
		pushed += push(L, ret9);
		pushed += push(L, ret10);
		return pushed;
	} // nativeStaticReturn10Param4

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
	inline LUA_FUNC(nativeStaticReturn10Param5)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_9 ret9;
		RET_10 ret10;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, to<ARG_1>(L, -5), to<ARG_2>(L, -4), to<ARG_3>(L, -3), to<ARG_4>(L, -2), to<ARG_5>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		pushed += push(L, ret8);
		pushed += push(L, ret9);
		pushed += push(L, ret10);
		return pushed;
	} // nativeStaticReturn10Param5

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
	inline LUA_FUNC(nativeStaticReturn10Param6)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_9 ret9;
		RET_10 ret10;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, to<ARG_1>(L, -6), to<ARG_2>(L, -5), to<ARG_3>(L, -4), to<ARG_4>(L, -3), to<ARG_5>(L, -2), to<ARG_6>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		pushed += push(L, ret8);
		pushed += push(L, ret9);
		pushed += push(L, ret10);
		return pushed;
	} // nativeStaticReturn10Param6

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
	inline LUA_FUNC(nativeStaticReturn10Param7)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_9 ret9;
		RET_10 ret10;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, to<ARG_1>(L, -7), to<ARG_2>(L, -6), to<ARG_3>(L, -5), to<ARG_4>(L, -4), to<ARG_5>(L, -3), to<ARG_6>(L, -2), to<ARG_7>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		pushed += push(L, ret8);
		pushed += push(L, ret9);
		pushed += push(L, ret10);
		return pushed;
	} // nativeStaticReturn10Param7

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
	inline LUA_FUNC(nativeStaticReturn10Param8)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_9 ret9;
		RET_10 ret10;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, to<ARG_1>(L, -8), to<ARG_2>(L, -7), to<ARG_3>(L, -6), to<ARG_4>(L, -5), to<ARG_5>(L, -4), to<ARG_6>(L, -3), to<ARG_7>(L, -2), to<ARG_8>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		pushed += push(L, ret8);
		pushed += push(L, ret9);
		pushed += push(L, ret10);
		return pushed;
	} // nativeStaticReturn10Param8

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
	inline LUA_FUNC(nativeStaticReturn10Param9)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_9 ret9;
		RET_10 ret10;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, to<ARG_1>(L, -9), to<ARG_2>(L, -8), to<ARG_3>(L, -7), to<ARG_4>(L, -6), to<ARG_5>(L, -5), to<ARG_6>(L, -4), to<ARG_7>(L, -3), to<ARG_8>(L, -2), to<ARG_9>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		pushed += push(L, ret8);
		pushed += push(L, ret9);
		pushed += push(L, ret10);
		return pushed;
	} // nativeStaticReturn10Param9

	//test generateStaticTemplate
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
	inline LUA_FUNC(nativeStaticReturn10Param10)
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_9 ret9;
		RET_10 ret10;
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, to<ARG_1>(L, -10), to<ARG_2>(L, -9), to<ARG_3>(L, -8), to<ARG_4>(L, -7), to<ARG_5>(L, -6), to<ARG_6>(L, -5), to<ARG_7>(L, -4), to<ARG_8>(L, -3), to<ARG_9>(L, -2), to<ARG_10>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		pushed += push(L, ret8);
		pushed += push(L, ret9);
		pushed += push(L, ret10);
		return pushed;
	} // nativeStaticReturn10Param10

		
		/** class member functions */
	CW_GENERATE_ALL(EN2S_GENERATE_CLASS_TEMPLATE)
	/** const class member functions */
	CW_GENERATE_ALL(EN2S_GENERATE_CLASS_CONST_TEMPLATE)
} // namespace lua_extension

#endif//LUA_EXPOSE_NATIVE_TO_SCRIPT_H

