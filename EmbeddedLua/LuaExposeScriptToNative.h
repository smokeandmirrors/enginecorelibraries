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
#include "LuaExtensibility.h"
#include "LuaInclusions.h"
#include "LuaStateInteraction.h"
#include "TemplateArguments.h"

#define PROTECTED_CALLS 1

#if PROTECTED_CALLS
	inline sint callLua(lua_State* L, sint nargs, sint nrets)
	{
		return !Lua::callProtected(L, nargs, rets);
	}
#else
	inline sint callLua(lua_State* L, sint nargs, sint nrets)
	{
		lua_call(L, nargs, nrets); return 0;
	}
#endif//DEBUG


namespace lua_extension
{	
	inline void scriptStaticReturn0Param0(lua_State* L, const char* function, const char* module="_G")
	{
		lua_getglobal(L, module);		//s: module
		lua_getfield(L, -1, function);	//s: module function
		lua_replace(L, -1);				//s: function
		callLua(L, 0, 0);				//s: 
	}

	template<void(*function)(void)>
	inline void hybridStaticReturn0Param0(lua_State* L, const char* function, const char* module="_G")
	{	
		lua_getglobal(L, module);			//s: module
		lua_getfield(L, -1, function);		//s: module ?
		
		if (lua_isfunction(L, -1))
		{									//s: module function
			if (!callLua(L, 0, 0))
			{								//s: module 
				lua_pop(L, 1);				//s: 
			}
			else
			{								//s: module
				lua_pop(L, 1);				//s:
			}
			
			return;
		}
		else
		{									//s: module nil
			lua_pop(L, 2);					//s: 
		}
		(*function)();
	}


	template<typename CLASS, void(CLASS::* function)(void)>
	inline sint scriptMemberReturn0Param0(lua_State* L)
	{
		if (CLASS* object = to<CLASS*>(L, -1))
		{
			(object->*function)();
		}
		return 0;	
	}

	template<typename CLASS, void(CLASS::* function)(void) const>
	inline sint scriptConstReturn0Param0(lua_State* L)
	{
		if (CLASS* object = to<CLASS*>(L, -1))
		{
			(object->*function)();
		}
		return 0;	
	}
} // namespace lua_extension
#endif//LUA_EXPOSE_NATIVE_TO_SCRIPT_H