#pragma once
#ifndef LUA_EXPOSE_SCRIPT_TO_NATIVE_H
#define LUA_EXPOSE_NATIVE_TO_SCRIPT_H
/**
\file LuaScriptToNative.h

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
\date 9/20/2011

\warning THIS FUNCTIONALITY IS NOT THREAD SAFE.

<DEVELOPMENT STATUS>
Current Draft		:	0.0
Current Phase		:   DEVELOPMENT
Purpose				:	DEPLOYMENT
Unit Tested			:	NO
Used in development	:	NO
Used in experiments :	YES
Tested in the field	:	NO
*/

#include "Build.h"
#include "Lua.h"
#include "LuaExtensibility.h"
#include "LuaInclusions.h"
#include "LuaStateInteraction.h"
#include "TemplateArguments.h"

// assign the return values from the script call
#define ES2N_ASSIGN_RETURN_VALUES_0 
#define ES2N_ASSIGN_RETURN_VALUES_1 ret1 = to<RET_1>(L, -1);
#define ES2N_ASSIGN_RETURN_VALUES_2 ret1 = to<RET_1>(L, -2); ret2 = to<RET_2>(L, -1);
#define ES2N_ASSIGN_RETURN_VALUES_3 ret1 = to<RET_1>(L, -3); ret2 = to<RET_2>(L, -2); ret3 = to<RET_3>(L, -1);
#define ES2N_ASSIGN_RETURN_VALUES_4 ret1 = to<RET_1>(L, -4); ret2 = to<RET_2>(L, -3); ret3 = to<RET_3>(L, -2); ret4 = to<RET_4>(L, -1);
#define ES2N_ASSIGN_RETURN_VALUES_5 ret1 = to<RET_1>(L, -5); ret2 = to<RET_2>(L, -4); ret3 = to<RET_3>(L, -3); ret4 = to<RET_4>(L, -2); ret5 = to<RET_5>(L, -1);

// begin the class function template signature
#define ES2N_BEGIN_CLASS_TEMPLATE_ARGS \
	template<typename CLASS

// begin the static function template signature
#define ES2N_BEGIN_STATIC_TEMPLATE_ARGS \
	template< 

// supply the correct number of arguments for the lua_call/lua_pcall function
#define ES2N_CLASS_CALL_ARGS_0 1
#define ES2N_CLASS_CALL_ARGS_1 2
#define ES2N_CLASS_CALL_ARGS_2 3
#define ES2N_CLASS_CALL_ARGS_3 4
#define ES2N_CLASS_CALL_ARGS_4 5
#define ES2N_CLASS_CALL_ARGS_5 6

// end the const class member function template signature
#define ES2N_END_CLASS_CONST_TEMPLATE_ARGS(NUM_RETS, NUM_ARGS) \
	CW_TEMPLATE_RETURN_SIGNATURE_RETS_##NUM_RETS(CLASS::* nativeFunction)(CW_TEMPLATE_ARGS_SIGNATURE_RETS_##NUM_RETS##_ARGS_##NUM_ARGS) const>

// end the class member function template signature
#define ES2N_END_CLASS_MEMBER_TEMPLATE_ARGS(NUM_RETS, NUM_ARGS) \
	CW_TEMPLATE_RETURN_SIGNATURE_RETS_##NUM_RETS(CLASS::* nativeFunction)(CW_TEMPLATE_ARGS_SIGNATURE_RETS_##NUM_RETS##_ARGS_##NUM_ARGS) >

// end the hybrid member function template signature
#define ES2N_END_HYBRID_STATIC_TEMPLATE_ARGS(NUM_RETS, NUM_ARGS) \
	, CW_TEMPLATE_RETURN_SIGNATURE_RETS_##NUM_RETS (* nativeFunction)(CW_TEMPLATE_ARGS_SIGNATURE_RETS_##NUM_RETS##_ARGS_##NUM_ARGS) >

// end the simple member function template signature
#define ES2N_END_SIMPLE_STATIC_TEMPLATE_ARGS(NUM_RETS, NUM_ARGS) \
	>

// generate the template function to override static native calls with lua_(p)calls of lua functions
#define ES2N_GENERATE_CLASS_HYBRID_CALL(NUM_RETS, NUM_ARGS, TYPE) \
	ES2N_BEGIN_CLASS_TEMPLATE_ARGS, \
	CW_TEMPLATE_ARGS_RETS_##NUM_RETS##_ARGS_##NUM_ARGS, \
	ES2N_END_CLASS_##TYPE##_TEMPLATE_ARGS(NUM_RETS, NUM_ARGS) \
	inline ScriptToNativeCallResult \
	ES2N_HYBRID_##TYPE##(NUM_RETS, NUM_ARGS) \
	{ \
		push(L, object);					/*s: object */ \
		lua_getfield(L, -1, scriptFunction);/*s: object ? */ \
		if (lua_isfunction(L, -1)) \
		{									/*s: object scriptFunction */ \
			lua_pushvalue(L, -2);			/*s: object scriptFunction object */ \
			ES2N_PUSH_ARGS_##NUM_ARGS		/*s: object scriptFunction object (arguments) */ \
			lua_call(L, ES2N_CLASS_CALL_ARGS_##NUM_ARGS, NUM_RETS ); \
			/*s: object (return values) */ \
			ES2N_ASSIGN_RETURN_VALUES_##NUM_RETS \
			ES2N_POP_RETURN_VALUES_##NUM_RETS \
			/*s: */ \
			return lua_extension::functionSuccess; \
		} \
		else \
		{									/*s: module nil */ \
			lua_pop(L, 2);					/*s: */ \
			CW_ASSIGN_RETS_##NUM_RETS (object.*nativeFunction)(CW_CALL_RETS_##NUM_RETS##_ARGS_##NUM_ARGS); \
			return lua_extension::functionNotFound; \
		} \
	}

// generate the template function to override class native calls with lua_(p)calls of lua functions
#define ES2N_GENERATE_CLASS_HYBRID_PCALL(NUM_RETS, NUM_ARGS, TYPE) \
	ES2N_BEGIN_CLASS_TEMPLATE_ARGS, \
	CW_TEMPLATE_ARGS_RETS_##NUM_RETS##_ARGS_##NUM_ARGS, \
	ES2N_END_CLASS_##TYPE##_TEMPLATE_ARGS(NUM_RETS, NUM_ARGS) \
	inline ScriptToNativeCallResult \
	ES2N_PHYBRID_##TYPE##(NUM_RETS, NUM_ARGS) \
	{ \
		push(L, object);					/*s: object */ \
		lua_getfield(L, -1, scriptFunction);/*s: object ? */ \
		if (lua_isfunction(L, -1)) \
		{									/*s: object scriptFunction */ \
			lua_pushvalue(L, -2);			/*s: object scriptFunction object */ \
			ES2N_PUSH_ARGS_##NUM_ARGS		/*s: object scriptFunction object (arguments) */ \
			if (!Lua::callProtected(L, ES2N_CLASS_CALL_ARGS_##NUM_ARGS, NUM_RETS )) \
			{ 								/*s: object (return values) */ \
				ES2N_ASSIGN_RETURN_VALUES_##NUM_RETS \
				ES2N_POP_RETURN_VALUES_##NUM_RETS \
				/*s: */ \
				return lua_extension::functionSuccess; \
			} \
			else \
			{								/*s: object */ \
				lua_pop(L, 1);				/*s: */ \
				return lua_extension::functionError; \
			} \
		} \
		else \
		{									/*s: module nil */ \
			lua_pop(L, 2);					/*s: */ \
			CW_ASSIGN_RETS_##NUM_RETS (object.*nativeFunction)(CW_CALL_RETS_##NUM_RETS##_ARGS_##NUM_ARGS); \
			return lua_extension::functionNotFound; \
		} \
	}

// generate all the member functions for the supplied number of return values and arguments
#define ES2N_GENERATE_HYBRID_MEMBER_CALLS(NUM_RETS, NUM_ARGS) \
	ES2N_GENERATE_CLASS_HYBRID_CALL(NUM_RETS, NUM_ARGS, CONST) \
	ES2N_GENERATE_CLASS_HYBRID_PCALL(NUM_RETS, NUM_ARGS, CONST) \
	ES2N_GENERATE_CLASS_HYBRID_CALL(NUM_RETS, NUM_ARGS, MEMBER) \
	ES2N_GENERATE_CLASS_HYBRID_PCALL(NUM_RETS, NUM_ARGS, MEMBER)

// generate the template function to call script functions from native
#define ES2N_GENERATE_STATIC_CALL(NUM_RETS, NUM_ARGS, TYPE) \
	ES2N_BEGIN_STATIC_TEMPLATE_ARGS \
	CW_TEMPLATE_ARGS_RETS_##NUM_RETS##_ARGS_##NUM_ARGS \
	ES2N_END_##TYPE##_STATIC_TEMPLATE_ARGS(NUM_RETS, NUM_ARGS) \
	inline ScriptToNativeCallResult \
	ES2N_##TYPE##_CALL(NUM_RETS, NUM_ARGS) \
	{ \
		lua_getglobal(L, module);				/*s: ? */ \
		if (lua_istable(L, -1)) \
		{ \
			lua_getfield(L, -1, scriptFunction);/*s: module ? */ \
			if (lua_isfunction(L, -1)) \
			{									/*s: module scriptFunction */ \
				ES2N_PUSH_ARGS_##NUM_ARGS		/*s: module scriptFunction (arguments) */ \
				lua_call(L, ES2N_STATIC_CALL_ARGS_##NUM_ARGS, NUM_RETS); \
				/*s: module (return values) */ \
				ES2N_ASSIGN_RETURN_VALUES_##NUM_RETS \
				ES2N_POP_RETURN_VALUES_##NUM_RETS \
				/*s: */ \
				return lua_extension::functionSuccess; \
			} \
			else \
			{									/*s: module nil */ \
				lua_pop(L, 2);					/*s: */ \
				ES2N_##TYPE##_CALL_NOT_FOUND(NUM_RETS, NUM_ARGS) \
				return lua_extension::functionNotFound; \
			} \
		} \
		else \
		{										/*s: !table */ \
			lua_pop(L, 1); \
			ES2N_##TYPE##_CALL_NOT_FOUND(NUM_RETS, NUM_ARGS) \
			return lua_extension::moduleNotFound; \
		} \
	}

// generate the template function to protected call script functions from native
#define ES2N_GENERATE_STATIC_PCALL(NUM_RETS, NUM_ARGS, TYPE) \
	ES2N_BEGIN_STATIC_TEMPLATE_ARGS \
	CW_TEMPLATE_ARGS_RETS_##NUM_RETS##_ARGS_##NUM_ARGS \
	ES2N_END_##TYPE##_STATIC_TEMPLATE_ARGS(NUM_RETS, NUM_ARGS) \
	inline ScriptToNativeCallResult \
	ES2N_##TYPE##_PCALL(NUM_RETS, NUM_ARGS) \
	{ \
		lua_getglobal(L, module);				/*s: ? */ \
		if (lua_istable(L, -1)) \
		{ \
			lua_getfield(L, -1, scriptFunction);/*s: module ? */ \
			if (lua_isfunction(L, -1)) \
			{									/*s: module scriptFunction */ \
				ES2N_PUSH_ARGS_##NUM_ARGS		/*s: module scriptFunction (arguments) */ \
				if (!Lua::callProtected(L, ES2N_STATIC_CALL_ARGS_##NUM_ARGS, NUM_RETS)) \
				{								/*s: module (return values) */ \
					ES2N_ASSIGN_RETURN_VALUES_##NUM_RETS \
					ES2N_POP_RETURN_VALUES_##NUM_RETS \
					/*s: */ \
					return lua_extension::functionSuccess; \
				} \
				else \
				{								/*s: module */ \
					lua_pop(L, 1);				/*s: */ \
					return lua_extension::functionError; \
				} \
			} \
			else \
			{									/*s: module nil */ \
				lua_pop(L, 2);					/*s: */ \
				ES2N_##TYPE##_CALL_NOT_FOUND(NUM_RETS, NUM_ARGS) \
				return lua_extension::functionNotFound; \
			} \
		} \
		else \
		{										/*s: !table */ \
			lua_pop(L, 1); \
			ES2N_##TYPE##_CALL_NOT_FOUND(NUM_RETS, NUM_ARGS) \
			return lua_extension::moduleNotFound; \
		} \
	}

// generate all the static functions for the supplied number of return values and arguments
#define ES2N_GENERATE_STATIC_CALLS(NUM_RETS, NUM_ARGS) \
	ES2N_GENERATE_STATIC_CALL(NUM_RETS, NUM_ARGS, HYBRID) \
	ES2N_GENERATE_STATIC_CALL(NUM_RETS, NUM_ARGS, SIMPLE) \
	ES2N_GENERATE_STATIC_PCALL(NUM_RETS, NUM_ARGS, HYBRID) \
	ES2N_GENERATE_STATIC_PCALL(NUM_RETS, NUM_ARGS, SIMPLE) 

// call the native function with the number of return values and arguments
#define ES2N_HYBRID_CALL_NOT_FOUND(NUM_RETS, NUM_ARGS) \
	CW_ASSIGN_RETS_##NUM_RETS (*nativeFunction)(CW_CALL_RETS_##NUM_RETS##_ARGS_##NUM_ARGS);

// declare and implement the hybrid const class function
#define ES2N_HYBRID_CONST(NUM_RETS, NUM_ARGS) \
	hybridConstReturn##NUM_RETS##Param##NUM_ARGS(lua_State* L, const char* scriptFunction, const CLASS& object, CW_DECLARE_FUNCTION_REF_RETS_##NUM_RETS##_ARGS_##NUM_ARGS) 

// declare and implement the hybrid const class function
#define ES2N_HYBRID_MEMBER(NUM_RETS, NUM_ARGS) \
	hybridMemberReturn##NUM_RETS##Param##NUM_ARGS(lua_State* L, const char* scriptFunction, CLASS& object, CW_DECLARE_FUNCTION_REF_RETS_##NUM_RETS##_ARGS_##NUM_ARGS) 

// declare and implement the * * function
#define ES2N_HYBRID_CALL(NUM_RETS, NUM_ARGS) \
	hybridStaticReturn##NUM_RETS##Param##NUM_ARGS(lua_State* L, const char* scriptFunction, CW_DECLARE_FUNCTION_REF_RETS_##NUM_RETS##_ARGS_##NUM_ARGS, const char* module="_G")

// declare and implement the * * function
#define ES2N_HYBRID_PCALL(NUM_RETS, NUM_ARGS) \
	phybridStaticReturn##NUM_RETS##Param##NUM_ARGS(lua_State* L, const char* scriptFunction, CW_DECLARE_FUNCTION_REF_RETS_##NUM_RETS##_ARGS_##NUM_ARGS, const char* module="_G")

// declare and implement the hybrid const class function with a protected call
#define ES2N_PHYBRID_CONST(NUM_RETS, NUM_ARGS) \
	phybridConstReturn##NUM_RETS##Param##NUM_ARGS(lua_State* L, const char* scriptFunction, const CLASS& object, CW_DECLARE_FUNCTION_REF_RETS_##NUM_RETS##_ARGS_##NUM_ARGS) 

// declare and implement the hybrid const class function with a protected call
#define ES2N_PHYBRID_MEMBER(NUM_RETS, NUM_ARGS) \
	phybridMemberReturn##NUM_RETS##Param##NUM_ARGS(lua_State* L, const char* scriptFunction, CLASS& object, CW_DECLARE_FUNCTION_REF_RETS_##NUM_RETS##_ARGS_##NUM_ARGS) 

// pop the appropriate number of values from the stack
#define ES2N_POP_RETURN_VALUES_0 lua_pop(L, 1);
#define ES2N_POP_RETURN_VALUES_1 lua_pop(L, 2);
#define ES2N_POP_RETURN_VALUES_2 lua_pop(L, 3);
#define ES2N_POP_RETURN_VALUES_3 lua_pop(L, 4);
#define ES2N_POP_RETURN_VALUES_4 lua_pop(L, 5);
#define ES2N_POP_RETURN_VALUES_5 lua_pop(L, 6);

// push the appropriate number of values on to the stack
#define ES2N_PUSH_ARGS_0 
#define ES2N_PUSH_ARGS_1 push(L, arg1); 
#define ES2N_PUSH_ARGS_2 push(L, arg1);	push(L, arg2);
#define ES2N_PUSH_ARGS_3 push(L, arg1);	push(L, arg2); push(L, arg3);
#define ES2N_PUSH_ARGS_4 push(L, arg1);	push(L, arg2); push(L, arg3); push(L, arg4);
#define ES2N_PUSH_ARGS_5 push(L, arg1);	push(L, arg2); push(L, arg3); push(L, arg4); push(L, arg5);

// declare and implement the * * function
#define ES2N_SIMPLE_CALL(NUM_RETS, NUM_ARGS) \
	callStaticReturn##NUM_RETS##Param##NUM_ARGS(lua_State* L, const char* scriptFunction, CW_DECLARE_FUNCTION_REF_RETS_##NUM_RETS##_ARGS_##NUM_ARGS, const char* module="_G")

// call the functions (left empty for the simple calls, but it makes the macro easier to write
#define ES2N_SIMPLE_CALL_NOT_FOUND(NUM_RETS, NUM_ARGS) 

// declare and implement the * * function
#define ES2N_SIMPLE_PCALL(NUM_RETS, NUM_ARGS) \
	pcallStaticReturn##NUM_RETS##Param##NUM_ARGS(lua_State* L, const char* scriptFunction, CW_DECLARE_FUNCTION_REF_RETS_##NUM_RETS##_ARGS_##NUM_ARGS, const char* module="_G")

// supply the correct number of arguments for the lua_call/lua_pcall function
#define ES2N_STATIC_CALL_ARGS_0 0
#define ES2N_STATIC_CALL_ARGS_1 1
#define ES2N_STATIC_CALL_ARGS_2 2
#define ES2N_STATIC_CALL_ARGS_3 3
#define ES2N_STATIC_CALL_ARGS_4 4
#define ES2N_STATIC_CALL_ARGS_5 6

namespace lua_extension
{
	typedef enum ScriptToNativeCallResult
	{
		functionSuccess=0,
		functionNotFound,
		functionError,
		moduleNotFound
	}; // ScriptToNativeCallResult
	
	template<typename CLASS, void(CLASS::* nativeFunction)(void) const>
	inline ScriptToNativeCallResult 
		hybridConstReturn0Param0(lua_State* L, const char* scriptFunction, const CLASS& object)
	{
		push(L, object);					/*s: object */
		lua_getfield(L, -1, scriptFunction);/*s: object ? */
		if (lua_isfunction(L, -1))
		{									/*s: object scriptFunction */
			lua_pushvalue(L, -2);			/*s: object scriptFunction object */
			lua_call(L, 1, 0);				/*s: object */
			lua_pop(L, 1);					/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{									/*s: module nil */
			lua_pop(L, 2);					/*s: */
			(object.*nativeFunction)();
			return lua_extension::functionNotFound;
		}
	}
	template<typename CLASS, void(CLASS::* nativeFunction)(void) const>
	inline ScriptToNativeCallResult 
		phybridConstReturn0Param0(lua_State* L, const char* scriptFunction, const CLASS& object)
	{
		push(L, object);					/*s: object */
		lua_getfield(L, -1, scriptFunction);/*s: object ? */
		if (lua_isfunction(L, -1))
		{									/*s: object scriptFunction */
			lua_pushvalue(L, -2);			/*s: object scriptFunction object */
			if (!Lua::callProtected(L, 1, 0))
			{								/*s: object */
				lua_pop(L, 1);				/*s: */
				return lua_extension::functionSuccess;
			}
			else
			{								/*s: object */
				lua_pop(L, 1);				/*s: */
				return lua_extension::functionError;
			}				
		}
		else
		{									/*s: object nil */
			lua_pop(L, 2);					/*s: */
			(object.*nativeFunction)();
			return lua_extension::functionNotFound;
		}
	}

	template<typename CLASS, void(CLASS::* nativeFunction)(void)>
	inline ScriptToNativeCallResult 
		hybridMemberReturn0Param0(lua_State* L, const char* scriptFunction, CLASS& object)
	{
		push(L, object);					/*s: object */
		lua_getfield(L, -1, scriptFunction);/*s: object ? */
		if (lua_isfunction(L, -1))
		{									/*s: object scriptFunction */
			lua_pushvalue(L, -2);			/*s: object scriptFunction object */
			lua_call(L, 1, 0);				/*s: object */
			lua_pop(L, 1);					/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{									/*s: module nil */
			lua_pop(L, 2);					/*s: */
			(object.*nativeFunction)();
			return lua_extension::functionNotFound;
		}
	}
	template<typename CLASS, void(CLASS::* nativeFunction)(void)>
	inline ScriptToNativeCallResult 
		phybridMemberReturn0Param0(lua_State* L, const char* scriptFunction, CLASS& object)
	{
		push(L, object);					/*s: object */
		lua_getfield(L, -1, scriptFunction);/*s: object ? */
		if (lua_isfunction(L, -1))
		{									/*s: object scriptFunction */
			lua_pushvalue(L, -2);			/*s: object scriptFunction object */
			if (!Lua::callProtected(L, 1, 0))
			{								/*s: object */
				lua_pop(L, 1);				/*s: */
				return lua_extension::functionSuccess;
			}
			else
			{								/*s: object */
				lua_pop(L, 1);				/*s: */
				return lua_extension::functionError;
			}				
		}
		else
		{									/*s: object nil */
			lua_pop(L, 2);					/*s: */
			(object.*nativeFunction)();
			return lua_extension::functionNotFound;
		}
	}

	inline ScriptToNativeCallResult 
		callStaticReturn0Param0(lua_State* L, const char* scriptFunction, const char* module="_G")
	{
		lua_getglobal(L, module);				/*s: ? */
		if (lua_istable(L, -1))					
		{
			lua_getfield(L, -1, scriptFunction);/*s: module ? */
			if (lua_isfunction(L, -1))
			{									/*s: module scriptFunction */
				lua_call(L, 0, 0);				/*s: module */
				lua_pop(L, 1);					/*s: */
				return lua_extension::functionSuccess;
			}
			else
			{									/*s: module nil */
				lua_pop(L, 2);					/*s: */
				return lua_extension::functionNotFound;
			}
		}
		else
		{										/*s: !table */
			lua_pop(L, 1);
			return lua_extension::moduleNotFound;
		}
	}
	
	template<void(* nativeFunction)(void)>
	inline ScriptToNativeCallResult 
		hybridStaticReturn0Param0(lua_State* L, const char* scriptFunction, const char* module="_G")
	{	
		lua_getglobal(L, module);				/*s: ? */
		if (lua_istable(L, -1))					
		{
			lua_getfield(L, -1, scriptFunction);/*s: module ? */
			if (lua_isfunction(L, -1))
			{									/*s: module scriptFunction */
				lua_call(L, 0, 0);				/*s: module */
				lua_pop(L, 1);					/*s: */
				return lua_extension::functionSuccess;
			}
			else
			{									/*s: module nil */
				lua_pop(L, 2);					/*s: */
				(*nativeFunction)();
				return lua_extension::functionNotFound;
			}
		}
		else
		{										/*s: !table */
			lua_pop(L, 1);
			(*nativeFunction)();
			return lua_extension::moduleNotFound;
		}
	}
	inline ScriptToNativeCallResult 
		pcallStaticReturn0Param0(lua_State* L, const char* scriptFunction, const char* module="_G")
	{
		lua_getglobal(L, module);				/*s: ? */
		if (lua_istable(L, -1))					
		{
			lua_getfield(L, -1, scriptFunction);/*s: module ? */
			if (lua_isfunction(L, -1))
			{									/*s: module scriptFunction */
				if (!Lua::callProtected(L, 0, 0))
				{								/*s: module */
					lua_pop(L, 1);				/*s: */
					return lua_extension::functionSuccess;
				}
				else
				{								/*s: module */
					lua_pop(L, 1);				/*s: */
					return lua_extension::functionError;
				}
			}
			else
			{									/*s: module nil */
				lua_pop(L, 2);					/*s: */
				return lua_extension::functionNotFound;
			}
		}
		else
		{										/*s: !table */
			lua_pop(L, 1);						/*s: */
			return lua_extension::moduleNotFound;
		}						
	}

	template<void(* nativeFunction)(void)>
	inline ScriptToNativeCallResult 
		phybridStaticReturn0Param0(lua_State* L, const char* scriptFunction, const char* module="_G")
	{	
		lua_getglobal(L, module);				/*s: ? */
		if (lua_istable(L, -1))					
		{
			lua_getfield(L, -1, scriptFunction);/*s: module ? */
			if (lua_isfunction(L, -1))
			{									/*s: module scriptFunction */
				if (!Lua::callProtected(L, 0, 0))
				{								/*s: module */
					lua_pop(L, 1);				/*s: */
					return lua_extension::functionSuccess;
				}
				else
				{								/*s: module */
					lua_pop(L, 1);				/*s: */
					return lua_extension::functionError;
				}
			}
			else
			{									/*s: module nil */
				lua_pop(L, 2);					/*s: */
				(*nativeFunction)();
				return lua_extension::functionNotFound;
			}
		}
		else
		{										/*s: !table */
			lua_pop(L, 1);
			(*nativeFunction)();
			return lua_extension::moduleNotFound;
		}
	}

	// phybridConst, hybridConst, hybridMember, phybridMember
	CW_GENERATE_ALL(ES2N_GENERATE_HYBRID_MEMBER_CALLS)
	
	// callStatic, hybridStatic, pcallStatic, phybridStatic
	CW_GENERATE_ALL(ES2N_GENERATE_STATIC_CALLS)

} // namespace lua_extension



#endif//LUA_EXPOSE_NATIVE_TO_SCRIPT_H