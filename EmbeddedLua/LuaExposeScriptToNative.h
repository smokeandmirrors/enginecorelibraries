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

namespace lua_extension
{	
	typedef enum ScriptToNativeCallResult
	{
		functionSuccess=0,
		functionNotFound,
		functionError,
		moduleNotFound
	};

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
		scriptStaticReturn0Param0(lua_State* L, const char* scriptFunction, const char* module="_G")
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
	inline ScriptToNativeCallResult 
		pscriptStaticReturn0Param0(lua_State* L, const char* scriptFunction, const char* module="_G")
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

	








	template<typename ARG_1, typename ARG_2, typename RET_1, typename RET_2>
	RET_1 nativeLuaCall(lua_State* L, const char* function, RET_2& ret_2, ARG_1 arg_1, ARG_2 arg_2, const char* module="_G")
	{
		lua_getglobal(L, module);		//s: module
		lua_getfield(L, -1, function);	//s: module function
		assert(lua_isfunction(L, -1));	
		push(L, arg_1);					//s: module function arg_1
		push(L, arg_2);					//s: module function arg_1 arg_2
		lua_call(L, 2, 2);				//s: module ret_1, ret_2
		ret_2 = to<RET_2>(L, -1);
		RET_1 ret_1 = to<RET_1>(L, -2);
		lua_pop(L, 3);					//s: 
		return ret_1;
	}

	template<typename ARG_1, typename ARG_2, typename RET_1, typename RET_2>
	RET_1 nativeLuaPCall(lua_State* L, const char* function, RET_2& ret_2, ARG_1 arg_1, ARG_2 arg_2, const char* module="_G")
	{
		lua_getglobal(L, module);		//s: module
		lua_getfield(L, -1, function);	//s: module function
		assert(lua_isfunction(L, -1));	
		push(L, arg_1);					//s: module function arg_1
		push(L, arg_2);					//s: module function arg_1 arg_2
		Lua::callProtected(L, 2, 2);	//s: module ret_1, ret_2
		ret_2 = to<RET_2>(L, -1);
		RET_1 ret_1 = to<RET_1>(L, -2);
		lua_pop(L, 3);					//s: 
		return ret_1;
	}

	template<typename RET_1, typename ARG_1, typename ARG_2>
	RET_1 nativeLuaCall(lua_State* L, const char* scriptFunction, ARG_1 arg_1, ARG_2 arg_2, const char* module="_G")
	{
		lua_getglobal(L, module);			//s: module
		lua_getfield(L, -1, scriptFunction);//s: module scriptFunction
		assert(lua_isfunction(L, -1));	
		push(L, arg_1);						//s: module scriptFunction arg_1
		push(L, arg_2);						//s: module scriptFunction arg_1 arg_2
		lua_call(L, 2, 1);					//s: module ret_1
		RET_1 ret_1 = to<RET_1>(L, -1);
		lua_pop(L, 3);						//s: 
		return ret_1;
	}

	template<typename CLASS, typename RET_1, RET_1(CLASS::*function)(void) const>
	RET_1 nativeLuaCall2(lua_State* L, const char* scriptFunction, CLASS* object, const char* module="_G")
	{
		lua_getglobal(L, module);			//s: module
		lua_getfield(L, -1, scriptFunction);//s: module ?

		if (lua_isfunction(L, -1))
		{									//s: module function
			push(L, object);				//s: module function self
			if (!Lua::callProtected(L, 1, 1))
			{								//s: module ret_1
				RET_1 ret_1 = to<RET_1>(L, -1);
				lua_pop(L, 2);				//s: 
				return ret_1;
			}
			else
			{								//s: module
				lua_pop(L, 1);				//s:
			}
		}
		else
		{									//s: module nil
			lua_pop(L, 2);					//s: 
		}

		return (object->*function)();
	}

} // namespace lua_extension
#endif//LUA_EXPOSE_NATIVE_TO_SCRIPT_H