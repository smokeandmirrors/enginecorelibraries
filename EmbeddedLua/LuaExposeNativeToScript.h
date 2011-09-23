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
	template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
	inline LUA_FUNC(nativeStaticReturn10Param10)
	{
		sint pushed(0);
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_9 ret9;
		RET_10 ret10;
		ARG_1 arg1 = to<ARG_1>(L, -10);
		ARG_2 arg2 = to<ARG_2>(L, -9);
		ARG_3 arg3 = to<ARG_3>(L, -8);
		ARG_4 arg4 = to<ARG_4>(L, -7);
		ARG_5 arg5 = to<ARG_5>(L, -6);
		ARG_6 arg6 = to<ARG_6>(L, -5);
		ARG_7 arg7 = to<ARG_7>(L, -4);
		ARG_8 arg8 = to<ARG_8>(L, -3);
		ARG_9 arg9 = to<ARG_9>(L, -2);
		ARG_10 arg10 = to<ARG_10>(L, -1);
		RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		pushed += push(L, ret1);
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
		
	/** static, non-member functions */
	CW_GENERATE_ALL(EN2S_GENERATE_STATIC_TEMPLATE)
	/** class member functions */
	CW_GENERATE_ALL(EN2S_GENERATE_CLASS_TEMPLATE)
	/** const class member functions */
	CW_GENERATE_ALL(EN2S_GENERATE_CLASS_CONST_TEMPLATE)
} // namespace lua_extension

#endif//LUA_EXPOSE_NATIVE_TO_SCRIPT_H

