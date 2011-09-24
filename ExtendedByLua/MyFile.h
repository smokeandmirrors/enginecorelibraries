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
} /** callStaticReturn0Param1 */
template<typename ARG_1, void (* nativeFunction)(ARG_1) >
inline ScriptToNativeCallResult
callStatic0Param1(lua_State* L, const char* scriptFunction, ARG_1 arg1, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 1);
			/*s: module (return values) */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn0Param1

/** hybridStaticReturn0Param1 */
template<typename ARG_1, void (* nativeFunction)(ARG_1) >
inline ScriptToNativeCallResult
hybridStatic0Param1(lua_State* L, const char* scriptFunction, ARG_1 arg1, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 1);
			/*s: module (return values) */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			(*nativeFunction)(arg1);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		(*nativeFunction)(arg1);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn0Param1

/** pcallStaticReturn0Param1 */
template<typename ARG_1, void (* nativeFunction)(ARG_1) >
inline ScriptToNativeCallResult
pcallStatic0Param1(lua_State* L, const char* scriptFunction, ARG_1 arg1, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 1))
			{	/*s: module (return values) */ 
				lua_pop(L, 1); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn0Param1

/** phybridStaticReturn0Param1 */
template<typename ARG_1, void (* nativeFunction)(ARG_1) >
inline ScriptToNativeCallResult
phybridStatic0Param1(lua_State* L, const char* scriptFunction, ARG_1 arg1, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 1))
			{	/*s: module (return values) */ 
				lua_pop(L, 1); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			(*nativeFunction)(arg1);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		(*nativeFunction)(arg1);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn0Param1

/** callStaticReturn0Param2 */
template<typename ARG_1, typename ARG_2, void (* nativeFunction)(ARG_1, ARG_2) >
inline ScriptToNativeCallResult
callStatic0Param2(lua_State* L, const char* scriptFunction, ARG_1 arg1, ARG_2 arg2, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 2);
			/*s: module (return values) */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn0Param2

/** hybridStaticReturn0Param2 */
template<typename ARG_1, typename ARG_2, void (* nativeFunction)(ARG_1, ARG_2) >
inline ScriptToNativeCallResult
hybridStatic0Param2(lua_State* L, const char* scriptFunction, ARG_1 arg1, ARG_2 arg2, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 2);
			/*s: module (return values) */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			(*nativeFunction)(arg1, arg2);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		(*nativeFunction)(arg1, arg2);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn0Param2

/** pcallStaticReturn0Param2 */
template<typename ARG_1, typename ARG_2, void (* nativeFunction)(ARG_1, ARG_2) >
inline ScriptToNativeCallResult
pcallStatic0Param2(lua_State* L, const char* scriptFunction, ARG_1 arg1, ARG_2 arg2, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 2))
			{	/*s: module (return values) */ 
				lua_pop(L, 1); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn0Param2

/** phybridStaticReturn0Param2 */
template<typename ARG_1, typename ARG_2, void (* nativeFunction)(ARG_1, ARG_2) >
inline ScriptToNativeCallResult
phybridStatic0Param2(lua_State* L, const char* scriptFunction, ARG_1 arg1, ARG_2 arg2, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 2))
			{	/*s: module (return values) */ 
				lua_pop(L, 1); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			(*nativeFunction)(arg1, arg2);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		(*nativeFunction)(arg1, arg2);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn0Param2

/** callStaticReturn0Param3 */
template<typename ARG_1, typename ARG_2, typename ARG_3, void (* nativeFunction)(ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
callStatic0Param3(lua_State* L, const char* scriptFunction, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 3);
			/*s: module (return values) */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn0Param3

/** hybridStaticReturn0Param3 */
template<typename ARG_1, typename ARG_2, typename ARG_3, void (* nativeFunction)(ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
hybridStatic0Param3(lua_State* L, const char* scriptFunction, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 3);
			/*s: module (return values) */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			(*nativeFunction)(arg1, arg2, arg3);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		(*nativeFunction)(arg1, arg2, arg3);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn0Param3

/** pcallStaticReturn0Param3 */
template<typename ARG_1, typename ARG_2, typename ARG_3, void (* nativeFunction)(ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
pcallStatic0Param3(lua_State* L, const char* scriptFunction, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 3))
			{	/*s: module (return values) */ 
				lua_pop(L, 1); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn0Param3

/** phybridStaticReturn0Param3 */
template<typename ARG_1, typename ARG_2, typename ARG_3, void (* nativeFunction)(ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
phybridStatic0Param3(lua_State* L, const char* scriptFunction, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 3))
			{	/*s: module (return values) */ 
				lua_pop(L, 1); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			(*nativeFunction)(arg1, arg2, arg3);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		(*nativeFunction)(arg1, arg2, arg3);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn0Param3

/** callStaticReturn0Param4 */
template<typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, void (* nativeFunction)(ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
callStatic0Param4(lua_State* L, const char* scriptFunction, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 4);
			/*s: module (return values) */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn0Param4

/** hybridStaticReturn0Param4 */
template<typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, void (* nativeFunction)(ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
hybridStatic0Param4(lua_State* L, const char* scriptFunction, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 4);
			/*s: module (return values) */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			(*nativeFunction)(arg1, arg2, arg3, arg4);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		(*nativeFunction)(arg1, arg2, arg3, arg4);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn0Param4

/** pcallStaticReturn0Param4 */
template<typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, void (* nativeFunction)(ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
pcallStatic0Param4(lua_State* L, const char* scriptFunction, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 4))
			{	/*s: module (return values) */ 
				lua_pop(L, 1); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn0Param4

/** phybridStaticReturn0Param4 */
template<typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, void (* nativeFunction)(ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
phybridStatic0Param4(lua_State* L, const char* scriptFunction, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 4))
			{	/*s: module (return values) */ 
				lua_pop(L, 1); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			(*nativeFunction)(arg1, arg2, arg3, arg4);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		(*nativeFunction)(arg1, arg2, arg3, arg4);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn0Param4

/** callStaticReturn0Param5 */
template<typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, void (* nativeFunction)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
callStatic0Param5(lua_State* L, const char* scriptFunction, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 5);
			/*s: module (return values) */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn0Param5

/** hybridStaticReturn0Param5 */
template<typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, void (* nativeFunction)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
hybridStatic0Param5(lua_State* L, const char* scriptFunction, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 5);
			/*s: module (return values) */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			(*nativeFunction)(arg1, arg2, arg3, arg4, arg5);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		(*nativeFunction)(arg1, arg2, arg3, arg4, arg5);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn0Param5

/** pcallStaticReturn0Param5 */
template<typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, void (* nativeFunction)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
pcallStatic0Param5(lua_State* L, const char* scriptFunction, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 5))
			{	/*s: module (return values) */ 
				lua_pop(L, 1); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn0Param5

/** phybridStaticReturn0Param5 */
template<typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, void (* nativeFunction)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
phybridStatic0Param5(lua_State* L, const char* scriptFunction, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 5))
			{	/*s: module (return values) */ 
				lua_pop(L, 1); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			(*nativeFunction)(arg1, arg2, arg3, arg4, arg5);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		(*nativeFunction)(arg1, arg2, arg3, arg4, arg5);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn0Param5

/** callStaticReturn0Param6 */
template<typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, void (* nativeFunction)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
callStatic0Param6(lua_State* L, const char* scriptFunction, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 6);
			/*s: module (return values) */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn0Param6

/** hybridStaticReturn0Param6 */
template<typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, void (* nativeFunction)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
hybridStatic0Param6(lua_State* L, const char* scriptFunction, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 6);
			/*s: module (return values) */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			(*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		(*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn0Param6

/** pcallStaticReturn0Param6 */
template<typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, void (* nativeFunction)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
pcallStatic0Param6(lua_State* L, const char* scriptFunction, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 6))
			{	/*s: module (return values) */ 
				lua_pop(L, 1); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn0Param6

/** phybridStaticReturn0Param6 */
template<typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, void (* nativeFunction)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
phybridStatic0Param6(lua_State* L, const char* scriptFunction, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 6))
			{	/*s: module (return values) */ 
				lua_pop(L, 1); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			(*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		(*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn0Param6

/** callStaticReturn0Param7 */
template<typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, void (* nativeFunction)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
callStatic0Param7(lua_State* L, const char* scriptFunction, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 7);
			/*s: module (return values) */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn0Param7

/** hybridStaticReturn0Param7 */
template<typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, void (* nativeFunction)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
hybridStatic0Param7(lua_State* L, const char* scriptFunction, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 7);
			/*s: module (return values) */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			(*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		(*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn0Param7

/** pcallStaticReturn0Param7 */
template<typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, void (* nativeFunction)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
pcallStatic0Param7(lua_State* L, const char* scriptFunction, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 7))
			{	/*s: module (return values) */ 
				lua_pop(L, 1); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn0Param7

/** phybridStaticReturn0Param7 */
template<typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, void (* nativeFunction)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
phybridStatic0Param7(lua_State* L, const char* scriptFunction, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 7))
			{	/*s: module (return values) */ 
				lua_pop(L, 1); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			(*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		(*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn0Param7

/** callStaticReturn0Param8 */
template<typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, void (* nativeFunction)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
callStatic0Param8(lua_State* L, const char* scriptFunction, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 8);
			/*s: module (return values) */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn0Param8

/** hybridStaticReturn0Param8 */
template<typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, void (* nativeFunction)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
hybridStatic0Param8(lua_State* L, const char* scriptFunction, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 8);
			/*s: module (return values) */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			(*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		(*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn0Param8

/** pcallStaticReturn0Param8 */
template<typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, void (* nativeFunction)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
pcallStatic0Param8(lua_State* L, const char* scriptFunction, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 8))
			{	/*s: module (return values) */ 
				lua_pop(L, 1); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn0Param8

/** phybridStaticReturn0Param8 */
template<typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, void (* nativeFunction)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
phybridStatic0Param8(lua_State* L, const char* scriptFunction, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 8))
			{	/*s: module (return values) */ 
				lua_pop(L, 1); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			(*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		(*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn0Param8

/** callStaticReturn0Param9 */
template<typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, void (* nativeFunction)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
callStatic0Param9(lua_State* L, const char* scriptFunction, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 9);
			/*s: module (return values) */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn0Param9

/** hybridStaticReturn0Param9 */
template<typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, void (* nativeFunction)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
hybridStatic0Param9(lua_State* L, const char* scriptFunction, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 9);
			/*s: module (return values) */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			(*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		(*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn0Param9

/** pcallStaticReturn0Param9 */
template<typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, void (* nativeFunction)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
pcallStatic0Param9(lua_State* L, const char* scriptFunction, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 9))
			{	/*s: module (return values) */ 
				lua_pop(L, 1); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn0Param9

/** phybridStaticReturn0Param9 */
template<typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, void (* nativeFunction)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
phybridStatic0Param9(lua_State* L, const char* scriptFunction, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 9))
			{	/*s: module (return values) */ 
				lua_pop(L, 1); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			(*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		(*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn0Param9

/** callStaticReturn0Param10 */
template<typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, void (* nativeFunction)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
callStatic0Param10(lua_State* L, const char* scriptFunction, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, ARG_10 arg10, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			push(L, arg10);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 10);
			/*s: module (return values) */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn0Param10

/** hybridStaticReturn0Param10 */
template<typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, void (* nativeFunction)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
hybridStatic0Param10(lua_State* L, const char* scriptFunction, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, ARG_10 arg10, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			push(L, arg10);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 10);
			/*s: module (return values) */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			(*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		(*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn0Param10

/** pcallStaticReturn0Param10 */
template<typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, void (* nativeFunction)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
pcallStatic0Param10(lua_State* L, const char* scriptFunction, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, ARG_10 arg10, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			push(L, arg10);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 10))
			{	/*s: module (return values) */ 
				lua_pop(L, 1); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn0Param10

/** phybridStaticReturn0Param10 */
template<typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, void (* nativeFunction)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
phybridStatic0Param10(lua_State* L, const char* scriptFunction, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, ARG_10 arg10, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			push(L, arg10);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 10))
			{	/*s: module (return values) */ 
				lua_pop(L, 1); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			(*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		(*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn0Param10

/** callStaticReturn1Param0 */
template<typename RET_1, RET_1 (* nativeFunction)(void) >
inline ScriptToNativeCallResult
callStatic1Param0(lua_State* L, const char* scriptFunction, RET_1& ret1, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			/*s: module scriptFunction (arguments) */
			lua_call(L, 0);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -1);
			lua_pop(L, 2);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn1Param0

/** hybridStaticReturn1Param0 */
template<typename RET_1, RET_1 (* nativeFunction)(void) >
inline ScriptToNativeCallResult
hybridStatic1Param0(lua_State* L, const char* scriptFunction, RET_1& ret1, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			/*s: module scriptFunction (arguments) */
			lua_call(L, 0);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -1);
			lua_pop(L, 2);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)();
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)();
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn1Param0

/** pcallStaticReturn1Param0 */
template<typename RET_1, RET_1 (* nativeFunction)(void) >
inline ScriptToNativeCallResult
pcallStatic1Param0(lua_State* L, const char* scriptFunction, RET_1& ret1, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 0))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -1);
				lua_pop(L, 2); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn1Param0

/** phybridStaticReturn1Param0 */
template<typename RET_1, RET_1 (* nativeFunction)(void) >
inline ScriptToNativeCallResult
phybridStatic1Param0(lua_State* L, const char* scriptFunction, RET_1& ret1, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 0))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -1);
				lua_pop(L, 2); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)();
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)();
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn1Param0

/** callStaticReturn1Param1 */
template<typename RET_1, typename ARG_1, RET_1 (* nativeFunction)(ARG_1) >
inline ScriptToNativeCallResult
callStatic1Param1(lua_State* L, const char* scriptFunction, RET_1& ret1, ARG_1 arg1, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 1);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -1);
			lua_pop(L, 2);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn1Param1

/** hybridStaticReturn1Param1 */
template<typename RET_1, typename ARG_1, RET_1 (* nativeFunction)(ARG_1) >
inline ScriptToNativeCallResult
hybridStatic1Param1(lua_State* L, const char* scriptFunction, RET_1& ret1, ARG_1 arg1, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 1);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -1);
			lua_pop(L, 2);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(arg1);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(arg1);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn1Param1

/** pcallStaticReturn1Param1 */
template<typename RET_1, typename ARG_1, RET_1 (* nativeFunction)(ARG_1) >
inline ScriptToNativeCallResult
pcallStatic1Param1(lua_State* L, const char* scriptFunction, RET_1& ret1, ARG_1 arg1, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 1))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -1);
				lua_pop(L, 2); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn1Param1

/** phybridStaticReturn1Param1 */
template<typename RET_1, typename ARG_1, RET_1 (* nativeFunction)(ARG_1) >
inline ScriptToNativeCallResult
phybridStatic1Param1(lua_State* L, const char* scriptFunction, RET_1& ret1, ARG_1 arg1, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 1))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -1);
				lua_pop(L, 2); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(arg1);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(arg1);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn1Param1

/** callStaticReturn1Param2 */
template<typename RET_1, typename ARG_1, typename ARG_2, RET_1 (* nativeFunction)(ARG_1, ARG_2) >
inline ScriptToNativeCallResult
callStatic1Param2(lua_State* L, const char* scriptFunction, RET_1& ret1, ARG_1 arg1, ARG_2 arg2, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 2);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -1);
			lua_pop(L, 2);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn1Param2

/** hybridStaticReturn1Param2 */
template<typename RET_1, typename ARG_1, typename ARG_2, RET_1 (* nativeFunction)(ARG_1, ARG_2) >
inline ScriptToNativeCallResult
hybridStatic1Param2(lua_State* L, const char* scriptFunction, RET_1& ret1, ARG_1 arg1, ARG_2 arg2, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 2);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -1);
			lua_pop(L, 2);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(arg1, arg2);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(arg1, arg2);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn1Param2

/** pcallStaticReturn1Param2 */
template<typename RET_1, typename ARG_1, typename ARG_2, RET_1 (* nativeFunction)(ARG_1, ARG_2) >
inline ScriptToNativeCallResult
pcallStatic1Param2(lua_State* L, const char* scriptFunction, RET_1& ret1, ARG_1 arg1, ARG_2 arg2, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 2))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -1);
				lua_pop(L, 2); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn1Param2

/** phybridStaticReturn1Param2 */
template<typename RET_1, typename ARG_1, typename ARG_2, RET_1 (* nativeFunction)(ARG_1, ARG_2) >
inline ScriptToNativeCallResult
phybridStatic1Param2(lua_State* L, const char* scriptFunction, RET_1& ret1, ARG_1 arg1, ARG_2 arg2, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 2))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -1);
				lua_pop(L, 2); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(arg1, arg2);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(arg1, arg2);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn1Param2

/** callStaticReturn1Param3 */
template<typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (* nativeFunction)(ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
callStatic1Param3(lua_State* L, const char* scriptFunction, RET_1& ret1, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 3);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -1);
			lua_pop(L, 2);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn1Param3

/** hybridStaticReturn1Param3 */
template<typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (* nativeFunction)(ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
hybridStatic1Param3(lua_State* L, const char* scriptFunction, RET_1& ret1, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 3);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -1);
			lua_pop(L, 2);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(arg1, arg2, arg3);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(arg1, arg2, arg3);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn1Param3

/** pcallStaticReturn1Param3 */
template<typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (* nativeFunction)(ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
pcallStatic1Param3(lua_State* L, const char* scriptFunction, RET_1& ret1, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 3))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -1);
				lua_pop(L, 2); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn1Param3

/** phybridStaticReturn1Param3 */
template<typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (* nativeFunction)(ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
phybridStatic1Param3(lua_State* L, const char* scriptFunction, RET_1& ret1, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 3))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -1);
				lua_pop(L, 2); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(arg1, arg2, arg3);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(arg1, arg2, arg3);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn1Param3

/** callStaticReturn1Param4 */
template<typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (* nativeFunction)(ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
callStatic1Param4(lua_State* L, const char* scriptFunction, RET_1& ret1, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 4);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -1);
			lua_pop(L, 2);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn1Param4

/** hybridStaticReturn1Param4 */
template<typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (* nativeFunction)(ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
hybridStatic1Param4(lua_State* L, const char* scriptFunction, RET_1& ret1, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 4);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -1);
			lua_pop(L, 2);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(arg1, arg2, arg3, arg4);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(arg1, arg2, arg3, arg4);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn1Param4

/** pcallStaticReturn1Param4 */
template<typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (* nativeFunction)(ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
pcallStatic1Param4(lua_State* L, const char* scriptFunction, RET_1& ret1, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 4))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -1);
				lua_pop(L, 2); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn1Param4

/** phybridStaticReturn1Param4 */
template<typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (* nativeFunction)(ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
phybridStatic1Param4(lua_State* L, const char* scriptFunction, RET_1& ret1, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 4))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -1);
				lua_pop(L, 2); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(arg1, arg2, arg3, arg4);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(arg1, arg2, arg3, arg4);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn1Param4

/** callStaticReturn1Param5 */
template<typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (* nativeFunction)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
callStatic1Param5(lua_State* L, const char* scriptFunction, RET_1& ret1, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 5);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -1);
			lua_pop(L, 2);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn1Param5

/** hybridStaticReturn1Param5 */
template<typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (* nativeFunction)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
hybridStatic1Param5(lua_State* L, const char* scriptFunction, RET_1& ret1, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 5);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -1);
			lua_pop(L, 2);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(arg1, arg2, arg3, arg4, arg5);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(arg1, arg2, arg3, arg4, arg5);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn1Param5

/** pcallStaticReturn1Param5 */
template<typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (* nativeFunction)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
pcallStatic1Param5(lua_State* L, const char* scriptFunction, RET_1& ret1, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 5))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -1);
				lua_pop(L, 2); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn1Param5

/** phybridStaticReturn1Param5 */
template<typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (* nativeFunction)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
phybridStatic1Param5(lua_State* L, const char* scriptFunction, RET_1& ret1, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 5))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -1);
				lua_pop(L, 2); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(arg1, arg2, arg3, arg4, arg5);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(arg1, arg2, arg3, arg4, arg5);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn1Param5

/** callStaticReturn1Param6 */
template<typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (* nativeFunction)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
callStatic1Param6(lua_State* L, const char* scriptFunction, RET_1& ret1, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 6);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -1);
			lua_pop(L, 2);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn1Param6

/** hybridStaticReturn1Param6 */
template<typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (* nativeFunction)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
hybridStatic1Param6(lua_State* L, const char* scriptFunction, RET_1& ret1, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 6);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -1);
			lua_pop(L, 2);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn1Param6

/** pcallStaticReturn1Param6 */
template<typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (* nativeFunction)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
pcallStatic1Param6(lua_State* L, const char* scriptFunction, RET_1& ret1, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 6))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -1);
				lua_pop(L, 2); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn1Param6

/** phybridStaticReturn1Param6 */
template<typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (* nativeFunction)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
phybridStatic1Param6(lua_State* L, const char* scriptFunction, RET_1& ret1, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 6))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -1);
				lua_pop(L, 2); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn1Param6

/** callStaticReturn1Param7 */
template<typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (* nativeFunction)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
callStatic1Param7(lua_State* L, const char* scriptFunction, RET_1& ret1, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 7);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -1);
			lua_pop(L, 2);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn1Param7

/** hybridStaticReturn1Param7 */
template<typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (* nativeFunction)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
hybridStatic1Param7(lua_State* L, const char* scriptFunction, RET_1& ret1, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 7);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -1);
			lua_pop(L, 2);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn1Param7

/** pcallStaticReturn1Param7 */
template<typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (* nativeFunction)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
pcallStatic1Param7(lua_State* L, const char* scriptFunction, RET_1& ret1, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 7))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -1);
				lua_pop(L, 2); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn1Param7

/** phybridStaticReturn1Param7 */
template<typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (* nativeFunction)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
phybridStatic1Param7(lua_State* L, const char* scriptFunction, RET_1& ret1, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 7))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -1);
				lua_pop(L, 2); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn1Param7

/** callStaticReturn1Param8 */
template<typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (* nativeFunction)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
callStatic1Param8(lua_State* L, const char* scriptFunction, RET_1& ret1, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 8);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -1);
			lua_pop(L, 2);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn1Param8

/** hybridStaticReturn1Param8 */
template<typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (* nativeFunction)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
hybridStatic1Param8(lua_State* L, const char* scriptFunction, RET_1& ret1, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 8);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -1);
			lua_pop(L, 2);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn1Param8

/** pcallStaticReturn1Param8 */
template<typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (* nativeFunction)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
pcallStatic1Param8(lua_State* L, const char* scriptFunction, RET_1& ret1, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 8))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -1);
				lua_pop(L, 2); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn1Param8

/** phybridStaticReturn1Param8 */
template<typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (* nativeFunction)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
phybridStatic1Param8(lua_State* L, const char* scriptFunction, RET_1& ret1, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 8))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -1);
				lua_pop(L, 2); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn1Param8

/** callStaticReturn1Param9 */
template<typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (* nativeFunction)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
callStatic1Param9(lua_State* L, const char* scriptFunction, RET_1& ret1, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 9);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -1);
			lua_pop(L, 2);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn1Param9

/** hybridStaticReturn1Param9 */
template<typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (* nativeFunction)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
hybridStatic1Param9(lua_State* L, const char* scriptFunction, RET_1& ret1, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 9);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -1);
			lua_pop(L, 2);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn1Param9

/** pcallStaticReturn1Param9 */
template<typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (* nativeFunction)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
pcallStatic1Param9(lua_State* L, const char* scriptFunction, RET_1& ret1, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 9))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -1);
				lua_pop(L, 2); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn1Param9

/** phybridStaticReturn1Param9 */
template<typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (* nativeFunction)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
phybridStatic1Param9(lua_State* L, const char* scriptFunction, RET_1& ret1, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 9))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -1);
				lua_pop(L, 2); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn1Param9

/** callStaticReturn1Param10 */
template<typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (* nativeFunction)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
callStatic1Param10(lua_State* L, const char* scriptFunction, RET_1& ret1, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, ARG_10 arg10, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			push(L, arg10);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 10);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -1);
			lua_pop(L, 2);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn1Param10

/** hybridStaticReturn1Param10 */
template<typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (* nativeFunction)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
hybridStatic1Param10(lua_State* L, const char* scriptFunction, RET_1& ret1, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, ARG_10 arg10, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			push(L, arg10);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 10);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -1);
			lua_pop(L, 2);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn1Param10

/** pcallStaticReturn1Param10 */
template<typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (* nativeFunction)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
pcallStatic1Param10(lua_State* L, const char* scriptFunction, RET_1& ret1, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, ARG_10 arg10, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			push(L, arg10);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 10))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -1);
				lua_pop(L, 2); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn1Param10

/** phybridStaticReturn1Param10 */
template<typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (* nativeFunction)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
phybridStatic1Param10(lua_State* L, const char* scriptFunction, RET_1& ret1, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, ARG_10 arg10, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			push(L, arg10);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 10))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -1);
				lua_pop(L, 2); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn1Param10

/** callStaticReturn2Param0 */
template<typename RET_1, typename RET_2, RET_1 (* nativeFunction)(RET_2&) >
inline ScriptToNativeCallResult
callStatic2Param0(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			/*s: module scriptFunction (arguments) */
			lua_call(L, 0);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -2);
			ret2 = to<RET_2>(L, -1);
			lua_pop(L, 3);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn2Param0

/** hybridStaticReturn2Param0 */
template<typename RET_1, typename RET_2, RET_1 (* nativeFunction)(RET_2&) >
inline ScriptToNativeCallResult
hybridStatic2Param0(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			/*s: module scriptFunction (arguments) */
			lua_call(L, 0);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -2);
			ret2 = to<RET_2>(L, -1);
			lua_pop(L, 3);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn2Param0

/** pcallStaticReturn2Param0 */
template<typename RET_1, typename RET_2, RET_1 (* nativeFunction)(RET_2&) >
inline ScriptToNativeCallResult
pcallStatic2Param0(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 0))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -2);
				ret2 = to<RET_2>(L, -1);
				lua_pop(L, 3); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn2Param0

/** phybridStaticReturn2Param0 */
template<typename RET_1, typename RET_2, RET_1 (* nativeFunction)(RET_2&) >
inline ScriptToNativeCallResult
phybridStatic2Param0(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 0))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -2);
				ret2 = to<RET_2>(L, -1);
				lua_pop(L, 3); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn2Param0

/** callStaticReturn2Param1 */
template<typename RET_1, typename RET_2, typename ARG_1, RET_1 (* nativeFunction)(RET_2&, ARG_1) >
inline ScriptToNativeCallResult
callStatic2Param1(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, ARG_1 arg1, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 1);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -2);
			ret2 = to<RET_2>(L, -1);
			lua_pop(L, 3);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn2Param1

/** hybridStaticReturn2Param1 */
template<typename RET_1, typename RET_2, typename ARG_1, RET_1 (* nativeFunction)(RET_2&, ARG_1) >
inline ScriptToNativeCallResult
hybridStatic2Param1(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, ARG_1 arg1, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 1);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -2);
			ret2 = to<RET_2>(L, -1);
			lua_pop(L, 3);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, arg1);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, arg1);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn2Param1

/** pcallStaticReturn2Param1 */
template<typename RET_1, typename RET_2, typename ARG_1, RET_1 (* nativeFunction)(RET_2&, ARG_1) >
inline ScriptToNativeCallResult
pcallStatic2Param1(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, ARG_1 arg1, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 1))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -2);
				ret2 = to<RET_2>(L, -1);
				lua_pop(L, 3); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn2Param1

/** phybridStaticReturn2Param1 */
template<typename RET_1, typename RET_2, typename ARG_1, RET_1 (* nativeFunction)(RET_2&, ARG_1) >
inline ScriptToNativeCallResult
phybridStatic2Param1(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, ARG_1 arg1, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 1))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -2);
				ret2 = to<RET_2>(L, -1);
				lua_pop(L, 3); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, arg1);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, arg1);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn2Param1

/** callStaticReturn2Param2 */
template<typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, RET_1 (* nativeFunction)(RET_2&, ARG_1, ARG_2) >
inline ScriptToNativeCallResult
callStatic2Param2(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, ARG_1 arg1, ARG_2 arg2, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 2);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -2);
			ret2 = to<RET_2>(L, -1);
			lua_pop(L, 3);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn2Param2

/** hybridStaticReturn2Param2 */
template<typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, RET_1 (* nativeFunction)(RET_2&, ARG_1, ARG_2) >
inline ScriptToNativeCallResult
hybridStatic2Param2(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, ARG_1 arg1, ARG_2 arg2, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 2);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -2);
			ret2 = to<RET_2>(L, -1);
			lua_pop(L, 3);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, arg1, arg2);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, arg1, arg2);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn2Param2

/** pcallStaticReturn2Param2 */
template<typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, RET_1 (* nativeFunction)(RET_2&, ARG_1, ARG_2) >
inline ScriptToNativeCallResult
pcallStatic2Param2(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, ARG_1 arg1, ARG_2 arg2, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 2))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -2);
				ret2 = to<RET_2>(L, -1);
				lua_pop(L, 3); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn2Param2

/** phybridStaticReturn2Param2 */
template<typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, RET_1 (* nativeFunction)(RET_2&, ARG_1, ARG_2) >
inline ScriptToNativeCallResult
phybridStatic2Param2(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, ARG_1 arg1, ARG_2 arg2, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 2))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -2);
				ret2 = to<RET_2>(L, -1);
				lua_pop(L, 3); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, arg1, arg2);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, arg1, arg2);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn2Param2

/** callStaticReturn2Param3 */
template<typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (* nativeFunction)(RET_2&, ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
callStatic2Param3(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 3);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -2);
			ret2 = to<RET_2>(L, -1);
			lua_pop(L, 3);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn2Param3

/** hybridStaticReturn2Param3 */
template<typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (* nativeFunction)(RET_2&, ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
hybridStatic2Param3(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 3);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -2);
			ret2 = to<RET_2>(L, -1);
			lua_pop(L, 3);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, arg1, arg2, arg3);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, arg1, arg2, arg3);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn2Param3

/** pcallStaticReturn2Param3 */
template<typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (* nativeFunction)(RET_2&, ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
pcallStatic2Param3(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 3))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -2);
				ret2 = to<RET_2>(L, -1);
				lua_pop(L, 3); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn2Param3

/** phybridStaticReturn2Param3 */
template<typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (* nativeFunction)(RET_2&, ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
phybridStatic2Param3(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 3))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -2);
				ret2 = to<RET_2>(L, -1);
				lua_pop(L, 3); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, arg1, arg2, arg3);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, arg1, arg2, arg3);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn2Param3

/** callStaticReturn2Param4 */
template<typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (* nativeFunction)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
callStatic2Param4(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 4);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -2);
			ret2 = to<RET_2>(L, -1);
			lua_pop(L, 3);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn2Param4

/** hybridStaticReturn2Param4 */
template<typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (* nativeFunction)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
hybridStatic2Param4(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 4);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -2);
			ret2 = to<RET_2>(L, -1);
			lua_pop(L, 3);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, arg1, arg2, arg3, arg4);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, arg1, arg2, arg3, arg4);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn2Param4

/** pcallStaticReturn2Param4 */
template<typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (* nativeFunction)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
pcallStatic2Param4(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 4))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -2);
				ret2 = to<RET_2>(L, -1);
				lua_pop(L, 3); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn2Param4

/** phybridStaticReturn2Param4 */
template<typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (* nativeFunction)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
phybridStatic2Param4(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 4))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -2);
				ret2 = to<RET_2>(L, -1);
				lua_pop(L, 3); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, arg1, arg2, arg3, arg4);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, arg1, arg2, arg3, arg4);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn2Param4

/** callStaticReturn2Param5 */
template<typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (* nativeFunction)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
callStatic2Param5(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 5);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -2);
			ret2 = to<RET_2>(L, -1);
			lua_pop(L, 3);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn2Param5

/** hybridStaticReturn2Param5 */
template<typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (* nativeFunction)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
hybridStatic2Param5(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 5);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -2);
			ret2 = to<RET_2>(L, -1);
			lua_pop(L, 3);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, arg1, arg2, arg3, arg4, arg5);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, arg1, arg2, arg3, arg4, arg5);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn2Param5

/** pcallStaticReturn2Param5 */
template<typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (* nativeFunction)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
pcallStatic2Param5(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 5))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -2);
				ret2 = to<RET_2>(L, -1);
				lua_pop(L, 3); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn2Param5

/** phybridStaticReturn2Param5 */
template<typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (* nativeFunction)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
phybridStatic2Param5(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 5))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -2);
				ret2 = to<RET_2>(L, -1);
				lua_pop(L, 3); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, arg1, arg2, arg3, arg4, arg5);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, arg1, arg2, arg3, arg4, arg5);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn2Param5

/** callStaticReturn2Param6 */
template<typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (* nativeFunction)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
callStatic2Param6(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 6);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -2);
			ret2 = to<RET_2>(L, -1);
			lua_pop(L, 3);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn2Param6

/** hybridStaticReturn2Param6 */
template<typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (* nativeFunction)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
hybridStatic2Param6(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 6);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -2);
			ret2 = to<RET_2>(L, -1);
			lua_pop(L, 3);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, arg1, arg2, arg3, arg4, arg5, arg6);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn2Param6

/** pcallStaticReturn2Param6 */
template<typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (* nativeFunction)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
pcallStatic2Param6(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 6))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -2);
				ret2 = to<RET_2>(L, -1);
				lua_pop(L, 3); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn2Param6

/** phybridStaticReturn2Param6 */
template<typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (* nativeFunction)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
phybridStatic2Param6(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 6))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -2);
				ret2 = to<RET_2>(L, -1);
				lua_pop(L, 3); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, arg1, arg2, arg3, arg4, arg5, arg6);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn2Param6

/** callStaticReturn2Param7 */
template<typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (* nativeFunction)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
callStatic2Param7(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 7);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -2);
			ret2 = to<RET_2>(L, -1);
			lua_pop(L, 3);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn2Param7

/** hybridStaticReturn2Param7 */
template<typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (* nativeFunction)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
hybridStatic2Param7(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 7);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -2);
			ret2 = to<RET_2>(L, -1);
			lua_pop(L, 3);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn2Param7

/** pcallStaticReturn2Param7 */
template<typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (* nativeFunction)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
pcallStatic2Param7(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 7))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -2);
				ret2 = to<RET_2>(L, -1);
				lua_pop(L, 3); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn2Param7

/** phybridStaticReturn2Param7 */
template<typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (* nativeFunction)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
phybridStatic2Param7(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 7))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -2);
				ret2 = to<RET_2>(L, -1);
				lua_pop(L, 3); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn2Param7

/** callStaticReturn2Param8 */
template<typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (* nativeFunction)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
callStatic2Param8(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 8);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -2);
			ret2 = to<RET_2>(L, -1);
			lua_pop(L, 3);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn2Param8

/** hybridStaticReturn2Param8 */
template<typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (* nativeFunction)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
hybridStatic2Param8(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 8);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -2);
			ret2 = to<RET_2>(L, -1);
			lua_pop(L, 3);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn2Param8

/** pcallStaticReturn2Param8 */
template<typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (* nativeFunction)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
pcallStatic2Param8(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 8))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -2);
				ret2 = to<RET_2>(L, -1);
				lua_pop(L, 3); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn2Param8

/** phybridStaticReturn2Param8 */
template<typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (* nativeFunction)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
phybridStatic2Param8(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 8))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -2);
				ret2 = to<RET_2>(L, -1);
				lua_pop(L, 3); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn2Param8

/** callStaticReturn2Param9 */
template<typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (* nativeFunction)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
callStatic2Param9(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 9);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -2);
			ret2 = to<RET_2>(L, -1);
			lua_pop(L, 3);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn2Param9

/** hybridStaticReturn2Param9 */
template<typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (* nativeFunction)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
hybridStatic2Param9(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 9);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -2);
			ret2 = to<RET_2>(L, -1);
			lua_pop(L, 3);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn2Param9

/** pcallStaticReturn2Param9 */
template<typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (* nativeFunction)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
pcallStatic2Param9(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 9))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -2);
				ret2 = to<RET_2>(L, -1);
				lua_pop(L, 3); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn2Param9

/** phybridStaticReturn2Param9 */
template<typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (* nativeFunction)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
phybridStatic2Param9(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 9))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -2);
				ret2 = to<RET_2>(L, -1);
				lua_pop(L, 3); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn2Param9

/** callStaticReturn2Param10 */
template<typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (* nativeFunction)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
callStatic2Param10(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, ARG_10 arg10, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			push(L, arg10);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 10);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -2);
			ret2 = to<RET_2>(L, -1);
			lua_pop(L, 3);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn2Param10

/** hybridStaticReturn2Param10 */
template<typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (* nativeFunction)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
hybridStatic2Param10(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, ARG_10 arg10, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			push(L, arg10);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 10);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -2);
			ret2 = to<RET_2>(L, -1);
			lua_pop(L, 3);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn2Param10

/** pcallStaticReturn2Param10 */
template<typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (* nativeFunction)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
pcallStatic2Param10(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, ARG_10 arg10, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			push(L, arg10);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 10))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -2);
				ret2 = to<RET_2>(L, -1);
				lua_pop(L, 3); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn2Param10

/** phybridStaticReturn2Param10 */
template<typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (* nativeFunction)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
phybridStatic2Param10(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, ARG_10 arg10, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			push(L, arg10);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 10))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -2);
				ret2 = to<RET_2>(L, -1);
				lua_pop(L, 3); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn2Param10

/** callStaticReturn3Param0 */
template<typename RET_1, typename RET_2, typename RET_3, RET_1 (* nativeFunction)(RET_2&, RET_3&) >
inline ScriptToNativeCallResult
callStatic3Param0(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			/*s: module scriptFunction (arguments) */
			lua_call(L, 0);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -3);
			ret2 = to<RET_2>(L, -2);
			ret3 = to<RET_3>(L, -1);
			lua_pop(L, 4);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn3Param0

/** hybridStaticReturn3Param0 */
template<typename RET_1, typename RET_2, typename RET_3, RET_1 (* nativeFunction)(RET_2&, RET_3&) >
inline ScriptToNativeCallResult
hybridStatic3Param0(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			/*s: module scriptFunction (arguments) */
			lua_call(L, 0);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -3);
			ret2 = to<RET_2>(L, -2);
			ret3 = to<RET_3>(L, -1);
			lua_pop(L, 4);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn3Param0

/** pcallStaticReturn3Param0 */
template<typename RET_1, typename RET_2, typename RET_3, RET_1 (* nativeFunction)(RET_2&, RET_3&) >
inline ScriptToNativeCallResult
pcallStatic3Param0(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 0))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -3);
				ret2 = to<RET_2>(L, -2);
				ret3 = to<RET_3>(L, -1);
				lua_pop(L, 4); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn3Param0

/** phybridStaticReturn3Param0 */
template<typename RET_1, typename RET_2, typename RET_3, RET_1 (* nativeFunction)(RET_2&, RET_3&) >
inline ScriptToNativeCallResult
phybridStatic3Param0(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 0))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -3);
				ret2 = to<RET_2>(L, -2);
				ret3 = to<RET_3>(L, -1);
				lua_pop(L, 4); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn3Param0

/** callStaticReturn3Param1 */
template<typename RET_1, typename RET_2, typename RET_3, typename ARG_1, RET_1 (* nativeFunction)(RET_2&, RET_3&, ARG_1) >
inline ScriptToNativeCallResult
callStatic3Param1(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, ARG_1 arg1, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 1);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -3);
			ret2 = to<RET_2>(L, -2);
			ret3 = to<RET_3>(L, -1);
			lua_pop(L, 4);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn3Param1

/** hybridStaticReturn3Param1 */
template<typename RET_1, typename RET_2, typename RET_3, typename ARG_1, RET_1 (* nativeFunction)(RET_2&, RET_3&, ARG_1) >
inline ScriptToNativeCallResult
hybridStatic3Param1(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, ARG_1 arg1, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 1);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -3);
			ret2 = to<RET_2>(L, -2);
			ret3 = to<RET_3>(L, -1);
			lua_pop(L, 4);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, arg1);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, arg1);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn3Param1

/** pcallStaticReturn3Param1 */
template<typename RET_1, typename RET_2, typename RET_3, typename ARG_1, RET_1 (* nativeFunction)(RET_2&, RET_3&, ARG_1) >
inline ScriptToNativeCallResult
pcallStatic3Param1(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, ARG_1 arg1, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 1))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -3);
				ret2 = to<RET_2>(L, -2);
				ret3 = to<RET_3>(L, -1);
				lua_pop(L, 4); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn3Param1

/** phybridStaticReturn3Param1 */
template<typename RET_1, typename RET_2, typename RET_3, typename ARG_1, RET_1 (* nativeFunction)(RET_2&, RET_3&, ARG_1) >
inline ScriptToNativeCallResult
phybridStatic3Param1(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, ARG_1 arg1, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 1))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -3);
				ret2 = to<RET_2>(L, -2);
				ret3 = to<RET_3>(L, -1);
				lua_pop(L, 4); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, arg1);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, arg1);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn3Param1

/** callStaticReturn3Param2 */
template<typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, RET_1 (* nativeFunction)(RET_2&, RET_3&, ARG_1, ARG_2) >
inline ScriptToNativeCallResult
callStatic3Param2(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, ARG_1 arg1, ARG_2 arg2, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 2);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -3);
			ret2 = to<RET_2>(L, -2);
			ret3 = to<RET_3>(L, -1);
			lua_pop(L, 4);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn3Param2

/** hybridStaticReturn3Param2 */
template<typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, RET_1 (* nativeFunction)(RET_2&, RET_3&, ARG_1, ARG_2) >
inline ScriptToNativeCallResult
hybridStatic3Param2(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, ARG_1 arg1, ARG_2 arg2, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 2);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -3);
			ret2 = to<RET_2>(L, -2);
			ret3 = to<RET_3>(L, -1);
			lua_pop(L, 4);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, arg1, arg2);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, arg1, arg2);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn3Param2

/** pcallStaticReturn3Param2 */
template<typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, RET_1 (* nativeFunction)(RET_2&, RET_3&, ARG_1, ARG_2) >
inline ScriptToNativeCallResult
pcallStatic3Param2(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, ARG_1 arg1, ARG_2 arg2, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 2))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -3);
				ret2 = to<RET_2>(L, -2);
				ret3 = to<RET_3>(L, -1);
				lua_pop(L, 4); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn3Param2

/** phybridStaticReturn3Param2 */
template<typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, RET_1 (* nativeFunction)(RET_2&, RET_3&, ARG_1, ARG_2) >
inline ScriptToNativeCallResult
phybridStatic3Param2(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, ARG_1 arg1, ARG_2 arg2, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 2))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -3);
				ret2 = to<RET_2>(L, -2);
				ret3 = to<RET_3>(L, -1);
				lua_pop(L, 4); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, arg1, arg2);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, arg1, arg2);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn3Param2

/** callStaticReturn3Param3 */
template<typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (* nativeFunction)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
callStatic3Param3(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 3);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -3);
			ret2 = to<RET_2>(L, -2);
			ret3 = to<RET_3>(L, -1);
			lua_pop(L, 4);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn3Param3

/** hybridStaticReturn3Param3 */
template<typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (* nativeFunction)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
hybridStatic3Param3(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 3);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -3);
			ret2 = to<RET_2>(L, -2);
			ret3 = to<RET_3>(L, -1);
			lua_pop(L, 4);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, arg1, arg2, arg3);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, arg1, arg2, arg3);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn3Param3

/** pcallStaticReturn3Param3 */
template<typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (* nativeFunction)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
pcallStatic3Param3(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 3))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -3);
				ret2 = to<RET_2>(L, -2);
				ret3 = to<RET_3>(L, -1);
				lua_pop(L, 4); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn3Param3

/** phybridStaticReturn3Param3 */
template<typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (* nativeFunction)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
phybridStatic3Param3(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 3))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -3);
				ret2 = to<RET_2>(L, -2);
				ret3 = to<RET_3>(L, -1);
				lua_pop(L, 4); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, arg1, arg2, arg3);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, arg1, arg2, arg3);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn3Param3

/** callStaticReturn3Param4 */
template<typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (* nativeFunction)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
callStatic3Param4(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 4);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -3);
			ret2 = to<RET_2>(L, -2);
			ret3 = to<RET_3>(L, -1);
			lua_pop(L, 4);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn3Param4

/** hybridStaticReturn3Param4 */
template<typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (* nativeFunction)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
hybridStatic3Param4(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 4);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -3);
			ret2 = to<RET_2>(L, -2);
			ret3 = to<RET_3>(L, -1);
			lua_pop(L, 4);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, arg1, arg2, arg3, arg4);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, arg1, arg2, arg3, arg4);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn3Param4

/** pcallStaticReturn3Param4 */
template<typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (* nativeFunction)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
pcallStatic3Param4(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 4))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -3);
				ret2 = to<RET_2>(L, -2);
				ret3 = to<RET_3>(L, -1);
				lua_pop(L, 4); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn3Param4

/** phybridStaticReturn3Param4 */
template<typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (* nativeFunction)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
phybridStatic3Param4(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 4))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -3);
				ret2 = to<RET_2>(L, -2);
				ret3 = to<RET_3>(L, -1);
				lua_pop(L, 4); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, arg1, arg2, arg3, arg4);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, arg1, arg2, arg3, arg4);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn3Param4

/** callStaticReturn3Param5 */
template<typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (* nativeFunction)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
callStatic3Param5(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 5);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -3);
			ret2 = to<RET_2>(L, -2);
			ret3 = to<RET_3>(L, -1);
			lua_pop(L, 4);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn3Param5

/** hybridStaticReturn3Param5 */
template<typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (* nativeFunction)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
hybridStatic3Param5(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 5);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -3);
			ret2 = to<RET_2>(L, -2);
			ret3 = to<RET_3>(L, -1);
			lua_pop(L, 4);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, arg1, arg2, arg3, arg4, arg5);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, arg1, arg2, arg3, arg4, arg5);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn3Param5

/** pcallStaticReturn3Param5 */
template<typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (* nativeFunction)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
pcallStatic3Param5(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 5))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -3);
				ret2 = to<RET_2>(L, -2);
				ret3 = to<RET_3>(L, -1);
				lua_pop(L, 4); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn3Param5

/** phybridStaticReturn3Param5 */
template<typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (* nativeFunction)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
phybridStatic3Param5(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 5))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -3);
				ret2 = to<RET_2>(L, -2);
				ret3 = to<RET_3>(L, -1);
				lua_pop(L, 4); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, arg1, arg2, arg3, arg4, arg5);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, arg1, arg2, arg3, arg4, arg5);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn3Param5

/** callStaticReturn3Param6 */
template<typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (* nativeFunction)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
callStatic3Param6(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 6);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -3);
			ret2 = to<RET_2>(L, -2);
			ret3 = to<RET_3>(L, -1);
			lua_pop(L, 4);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn3Param6

/** hybridStaticReturn3Param6 */
template<typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (* nativeFunction)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
hybridStatic3Param6(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 6);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -3);
			ret2 = to<RET_2>(L, -2);
			ret3 = to<RET_3>(L, -1);
			lua_pop(L, 4);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, arg1, arg2, arg3, arg4, arg5, arg6);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn3Param6

/** pcallStaticReturn3Param6 */
template<typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (* nativeFunction)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
pcallStatic3Param6(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 6))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -3);
				ret2 = to<RET_2>(L, -2);
				ret3 = to<RET_3>(L, -1);
				lua_pop(L, 4); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn3Param6

/** phybridStaticReturn3Param6 */
template<typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (* nativeFunction)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
phybridStatic3Param6(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 6))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -3);
				ret2 = to<RET_2>(L, -2);
				ret3 = to<RET_3>(L, -1);
				lua_pop(L, 4); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, arg1, arg2, arg3, arg4, arg5, arg6);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn3Param6

/** callStaticReturn3Param7 */
template<typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (* nativeFunction)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
callStatic3Param7(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 7);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -3);
			ret2 = to<RET_2>(L, -2);
			ret3 = to<RET_3>(L, -1);
			lua_pop(L, 4);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn3Param7

/** hybridStaticReturn3Param7 */
template<typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (* nativeFunction)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
hybridStatic3Param7(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 7);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -3);
			ret2 = to<RET_2>(L, -2);
			ret3 = to<RET_3>(L, -1);
			lua_pop(L, 4);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn3Param7

/** pcallStaticReturn3Param7 */
template<typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (* nativeFunction)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
pcallStatic3Param7(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 7))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -3);
				ret2 = to<RET_2>(L, -2);
				ret3 = to<RET_3>(L, -1);
				lua_pop(L, 4); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn3Param7

/** phybridStaticReturn3Param7 */
template<typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (* nativeFunction)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
phybridStatic3Param7(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 7))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -3);
				ret2 = to<RET_2>(L, -2);
				ret3 = to<RET_3>(L, -1);
				lua_pop(L, 4); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn3Param7

/** callStaticReturn3Param8 */
template<typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (* nativeFunction)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
callStatic3Param8(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 8);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -3);
			ret2 = to<RET_2>(L, -2);
			ret3 = to<RET_3>(L, -1);
			lua_pop(L, 4);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn3Param8

/** hybridStaticReturn3Param8 */
template<typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (* nativeFunction)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
hybridStatic3Param8(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 8);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -3);
			ret2 = to<RET_2>(L, -2);
			ret3 = to<RET_3>(L, -1);
			lua_pop(L, 4);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn3Param8

/** pcallStaticReturn3Param8 */
template<typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (* nativeFunction)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
pcallStatic3Param8(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 8))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -3);
				ret2 = to<RET_2>(L, -2);
				ret3 = to<RET_3>(L, -1);
				lua_pop(L, 4); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn3Param8

/** phybridStaticReturn3Param8 */
template<typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (* nativeFunction)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
phybridStatic3Param8(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 8))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -3);
				ret2 = to<RET_2>(L, -2);
				ret3 = to<RET_3>(L, -1);
				lua_pop(L, 4); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn3Param8

/** callStaticReturn3Param9 */
template<typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (* nativeFunction)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
callStatic3Param9(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 9);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -3);
			ret2 = to<RET_2>(L, -2);
			ret3 = to<RET_3>(L, -1);
			lua_pop(L, 4);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn3Param9

/** hybridStaticReturn3Param9 */
template<typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (* nativeFunction)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
hybridStatic3Param9(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 9);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -3);
			ret2 = to<RET_2>(L, -2);
			ret3 = to<RET_3>(L, -1);
			lua_pop(L, 4);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn3Param9

/** pcallStaticReturn3Param9 */
template<typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (* nativeFunction)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
pcallStatic3Param9(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 9))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -3);
				ret2 = to<RET_2>(L, -2);
				ret3 = to<RET_3>(L, -1);
				lua_pop(L, 4); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn3Param9

/** phybridStaticReturn3Param9 */
template<typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (* nativeFunction)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
phybridStatic3Param9(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 9))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -3);
				ret2 = to<RET_2>(L, -2);
				ret3 = to<RET_3>(L, -1);
				lua_pop(L, 4); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn3Param9

/** callStaticReturn3Param10 */
template<typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (* nativeFunction)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
callStatic3Param10(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, ARG_10 arg10, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			push(L, arg10);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 10);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -3);
			ret2 = to<RET_2>(L, -2);
			ret3 = to<RET_3>(L, -1);
			lua_pop(L, 4);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn3Param10

/** hybridStaticReturn3Param10 */
template<typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (* nativeFunction)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
hybridStatic3Param10(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, ARG_10 arg10, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			push(L, arg10);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 10);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -3);
			ret2 = to<RET_2>(L, -2);
			ret3 = to<RET_3>(L, -1);
			lua_pop(L, 4);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn3Param10

/** pcallStaticReturn3Param10 */
template<typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (* nativeFunction)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
pcallStatic3Param10(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, ARG_10 arg10, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			push(L, arg10);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 10))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -3);
				ret2 = to<RET_2>(L, -2);
				ret3 = to<RET_3>(L, -1);
				lua_pop(L, 4); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn3Param10

/** phybridStaticReturn3Param10 */
template<typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (* nativeFunction)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
phybridStatic3Param10(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, ARG_10 arg10, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			push(L, arg10);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 10))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -3);
				ret2 = to<RET_2>(L, -2);
				ret3 = to<RET_3>(L, -1);
				lua_pop(L, 4); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn3Param10

/** callStaticReturn4Param0 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&) >
inline ScriptToNativeCallResult
callStatic4Param0(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			/*s: module scriptFunction (arguments) */
			lua_call(L, 0);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -4);
			ret2 = to<RET_2>(L, -3);
			ret3 = to<RET_3>(L, -2);
			ret4 = to<RET_4>(L, -1);
			lua_pop(L, 5);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn4Param0

/** hybridStaticReturn4Param0 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&) >
inline ScriptToNativeCallResult
hybridStatic4Param0(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			/*s: module scriptFunction (arguments) */
			lua_call(L, 0);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -4);
			ret2 = to<RET_2>(L, -3);
			ret3 = to<RET_3>(L, -2);
			ret4 = to<RET_4>(L, -1);
			lua_pop(L, 5);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn4Param0

/** pcallStaticReturn4Param0 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&) >
inline ScriptToNativeCallResult
pcallStatic4Param0(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 0))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -4);
				ret2 = to<RET_2>(L, -3);
				ret3 = to<RET_3>(L, -2);
				ret4 = to<RET_4>(L, -1);
				lua_pop(L, 5); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn4Param0

/** phybridStaticReturn4Param0 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&) >
inline ScriptToNativeCallResult
phybridStatic4Param0(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 0))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -4);
				ret2 = to<RET_2>(L, -3);
				ret3 = to<RET_3>(L, -2);
				ret4 = to<RET_4>(L, -1);
				lua_pop(L, 5); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn4Param0

/** callStaticReturn4Param1 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, ARG_1) >
inline ScriptToNativeCallResult
callStatic4Param1(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, ARG_1 arg1, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 1);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -4);
			ret2 = to<RET_2>(L, -3);
			ret3 = to<RET_3>(L, -2);
			ret4 = to<RET_4>(L, -1);
			lua_pop(L, 5);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn4Param1

/** hybridStaticReturn4Param1 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, ARG_1) >
inline ScriptToNativeCallResult
hybridStatic4Param1(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, ARG_1 arg1, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 1);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -4);
			ret2 = to<RET_2>(L, -3);
			ret3 = to<RET_3>(L, -2);
			ret4 = to<RET_4>(L, -1);
			lua_pop(L, 5);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, arg1);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, arg1);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn4Param1

/** pcallStaticReturn4Param1 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, ARG_1) >
inline ScriptToNativeCallResult
pcallStatic4Param1(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, ARG_1 arg1, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 1))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -4);
				ret2 = to<RET_2>(L, -3);
				ret3 = to<RET_3>(L, -2);
				ret4 = to<RET_4>(L, -1);
				lua_pop(L, 5); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn4Param1

/** phybridStaticReturn4Param1 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, ARG_1) >
inline ScriptToNativeCallResult
phybridStatic4Param1(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, ARG_1 arg1, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 1))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -4);
				ret2 = to<RET_2>(L, -3);
				ret3 = to<RET_3>(L, -2);
				ret4 = to<RET_4>(L, -1);
				lua_pop(L, 5); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, arg1);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, arg1);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn4Param1

/** callStaticReturn4Param2 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2) >
inline ScriptToNativeCallResult
callStatic4Param2(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, ARG_1 arg1, ARG_2 arg2, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 2);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -4);
			ret2 = to<RET_2>(L, -3);
			ret3 = to<RET_3>(L, -2);
			ret4 = to<RET_4>(L, -1);
			lua_pop(L, 5);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn4Param2

/** hybridStaticReturn4Param2 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2) >
inline ScriptToNativeCallResult
hybridStatic4Param2(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, ARG_1 arg1, ARG_2 arg2, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 2);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -4);
			ret2 = to<RET_2>(L, -3);
			ret3 = to<RET_3>(L, -2);
			ret4 = to<RET_4>(L, -1);
			lua_pop(L, 5);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, arg1, arg2);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, arg1, arg2);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn4Param2

/** pcallStaticReturn4Param2 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2) >
inline ScriptToNativeCallResult
pcallStatic4Param2(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, ARG_1 arg1, ARG_2 arg2, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 2))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -4);
				ret2 = to<RET_2>(L, -3);
				ret3 = to<RET_3>(L, -2);
				ret4 = to<RET_4>(L, -1);
				lua_pop(L, 5); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn4Param2

/** phybridStaticReturn4Param2 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2) >
inline ScriptToNativeCallResult
phybridStatic4Param2(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, ARG_1 arg1, ARG_2 arg2, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 2))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -4);
				ret2 = to<RET_2>(L, -3);
				ret3 = to<RET_3>(L, -2);
				ret4 = to<RET_4>(L, -1);
				lua_pop(L, 5); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, arg1, arg2);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, arg1, arg2);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn4Param2

/** callStaticReturn4Param3 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
callStatic4Param3(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 3);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -4);
			ret2 = to<RET_2>(L, -3);
			ret3 = to<RET_3>(L, -2);
			ret4 = to<RET_4>(L, -1);
			lua_pop(L, 5);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn4Param3

/** hybridStaticReturn4Param3 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
hybridStatic4Param3(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 3);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -4);
			ret2 = to<RET_2>(L, -3);
			ret3 = to<RET_3>(L, -2);
			ret4 = to<RET_4>(L, -1);
			lua_pop(L, 5);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn4Param3

/** pcallStaticReturn4Param3 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
pcallStatic4Param3(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 3))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -4);
				ret2 = to<RET_2>(L, -3);
				ret3 = to<RET_3>(L, -2);
				ret4 = to<RET_4>(L, -1);
				lua_pop(L, 5); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn4Param3

/** phybridStaticReturn4Param3 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
phybridStatic4Param3(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 3))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -4);
				ret2 = to<RET_2>(L, -3);
				ret3 = to<RET_3>(L, -2);
				ret4 = to<RET_4>(L, -1);
				lua_pop(L, 5); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn4Param3

/** callStaticReturn4Param4 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
callStatic4Param4(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 4);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -4);
			ret2 = to<RET_2>(L, -3);
			ret3 = to<RET_3>(L, -2);
			ret4 = to<RET_4>(L, -1);
			lua_pop(L, 5);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn4Param4

/** hybridStaticReturn4Param4 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
hybridStatic4Param4(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 4);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -4);
			ret2 = to<RET_2>(L, -3);
			ret3 = to<RET_3>(L, -2);
			ret4 = to<RET_4>(L, -1);
			lua_pop(L, 5);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3, arg4);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3, arg4);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn4Param4

/** pcallStaticReturn4Param4 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
pcallStatic4Param4(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 4))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -4);
				ret2 = to<RET_2>(L, -3);
				ret3 = to<RET_3>(L, -2);
				ret4 = to<RET_4>(L, -1);
				lua_pop(L, 5); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn4Param4

/** phybridStaticReturn4Param4 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
phybridStatic4Param4(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 4))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -4);
				ret2 = to<RET_2>(L, -3);
				ret3 = to<RET_3>(L, -2);
				ret4 = to<RET_4>(L, -1);
				lua_pop(L, 5); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3, arg4);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3, arg4);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn4Param4

/** callStaticReturn4Param5 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
callStatic4Param5(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 5);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -4);
			ret2 = to<RET_2>(L, -3);
			ret3 = to<RET_3>(L, -2);
			ret4 = to<RET_4>(L, -1);
			lua_pop(L, 5);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn4Param5

/** hybridStaticReturn4Param5 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
hybridStatic4Param5(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 5);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -4);
			ret2 = to<RET_2>(L, -3);
			ret3 = to<RET_3>(L, -2);
			ret4 = to<RET_4>(L, -1);
			lua_pop(L, 5);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3, arg4, arg5);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3, arg4, arg5);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn4Param5

/** pcallStaticReturn4Param5 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
pcallStatic4Param5(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 5))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -4);
				ret2 = to<RET_2>(L, -3);
				ret3 = to<RET_3>(L, -2);
				ret4 = to<RET_4>(L, -1);
				lua_pop(L, 5); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn4Param5

/** phybridStaticReturn4Param5 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
phybridStatic4Param5(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 5))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -4);
				ret2 = to<RET_2>(L, -3);
				ret3 = to<RET_3>(L, -2);
				ret4 = to<RET_4>(L, -1);
				lua_pop(L, 5); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3, arg4, arg5);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3, arg4, arg5);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn4Param5

/** callStaticReturn4Param6 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
callStatic4Param6(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 6);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -4);
			ret2 = to<RET_2>(L, -3);
			ret3 = to<RET_3>(L, -2);
			ret4 = to<RET_4>(L, -1);
			lua_pop(L, 5);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn4Param6

/** hybridStaticReturn4Param6 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
hybridStatic4Param6(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 6);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -4);
			ret2 = to<RET_2>(L, -3);
			ret3 = to<RET_3>(L, -2);
			ret4 = to<RET_4>(L, -1);
			lua_pop(L, 5);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3, arg4, arg5, arg6);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn4Param6

/** pcallStaticReturn4Param6 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
pcallStatic4Param6(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 6))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -4);
				ret2 = to<RET_2>(L, -3);
				ret3 = to<RET_3>(L, -2);
				ret4 = to<RET_4>(L, -1);
				lua_pop(L, 5); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn4Param6

/** phybridStaticReturn4Param6 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
phybridStatic4Param6(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 6))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -4);
				ret2 = to<RET_2>(L, -3);
				ret3 = to<RET_3>(L, -2);
				ret4 = to<RET_4>(L, -1);
				lua_pop(L, 5); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3, arg4, arg5, arg6);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn4Param6

/** callStaticReturn4Param7 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
callStatic4Param7(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 7);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -4);
			ret2 = to<RET_2>(L, -3);
			ret3 = to<RET_3>(L, -2);
			ret4 = to<RET_4>(L, -1);
			lua_pop(L, 5);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn4Param7

/** hybridStaticReturn4Param7 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
hybridStatic4Param7(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 7);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -4);
			ret2 = to<RET_2>(L, -3);
			ret3 = to<RET_3>(L, -2);
			ret4 = to<RET_4>(L, -1);
			lua_pop(L, 5);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn4Param7

/** pcallStaticReturn4Param7 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
pcallStatic4Param7(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 7))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -4);
				ret2 = to<RET_2>(L, -3);
				ret3 = to<RET_3>(L, -2);
				ret4 = to<RET_4>(L, -1);
				lua_pop(L, 5); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn4Param7

/** phybridStaticReturn4Param7 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
phybridStatic4Param7(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 7))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -4);
				ret2 = to<RET_2>(L, -3);
				ret3 = to<RET_3>(L, -2);
				ret4 = to<RET_4>(L, -1);
				lua_pop(L, 5); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn4Param7

/** callStaticReturn4Param8 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
callStatic4Param8(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 8);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -4);
			ret2 = to<RET_2>(L, -3);
			ret3 = to<RET_3>(L, -2);
			ret4 = to<RET_4>(L, -1);
			lua_pop(L, 5);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn4Param8

/** hybridStaticReturn4Param8 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
hybridStatic4Param8(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 8);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -4);
			ret2 = to<RET_2>(L, -3);
			ret3 = to<RET_3>(L, -2);
			ret4 = to<RET_4>(L, -1);
			lua_pop(L, 5);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn4Param8

/** pcallStaticReturn4Param8 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
pcallStatic4Param8(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 8))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -4);
				ret2 = to<RET_2>(L, -3);
				ret3 = to<RET_3>(L, -2);
				ret4 = to<RET_4>(L, -1);
				lua_pop(L, 5); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn4Param8

/** phybridStaticReturn4Param8 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
phybridStatic4Param8(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 8))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -4);
				ret2 = to<RET_2>(L, -3);
				ret3 = to<RET_3>(L, -2);
				ret4 = to<RET_4>(L, -1);
				lua_pop(L, 5); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn4Param8

/** callStaticReturn4Param9 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
callStatic4Param9(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 9);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -4);
			ret2 = to<RET_2>(L, -3);
			ret3 = to<RET_3>(L, -2);
			ret4 = to<RET_4>(L, -1);
			lua_pop(L, 5);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn4Param9

/** hybridStaticReturn4Param9 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
hybridStatic4Param9(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 9);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -4);
			ret2 = to<RET_2>(L, -3);
			ret3 = to<RET_3>(L, -2);
			ret4 = to<RET_4>(L, -1);
			lua_pop(L, 5);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn4Param9

/** pcallStaticReturn4Param9 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
pcallStatic4Param9(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 9))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -4);
				ret2 = to<RET_2>(L, -3);
				ret3 = to<RET_3>(L, -2);
				ret4 = to<RET_4>(L, -1);
				lua_pop(L, 5); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn4Param9

/** phybridStaticReturn4Param9 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
phybridStatic4Param9(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 9))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -4);
				ret2 = to<RET_2>(L, -3);
				ret3 = to<RET_3>(L, -2);
				ret4 = to<RET_4>(L, -1);
				lua_pop(L, 5); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn4Param9

/** callStaticReturn4Param10 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
callStatic4Param10(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, ARG_10 arg10, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			push(L, arg10);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 10);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -4);
			ret2 = to<RET_2>(L, -3);
			ret3 = to<RET_3>(L, -2);
			ret4 = to<RET_4>(L, -1);
			lua_pop(L, 5);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn4Param10

/** hybridStaticReturn4Param10 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
hybridStatic4Param10(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, ARG_10 arg10, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			push(L, arg10);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 10);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -4);
			ret2 = to<RET_2>(L, -3);
			ret3 = to<RET_3>(L, -2);
			ret4 = to<RET_4>(L, -1);
			lua_pop(L, 5);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn4Param10

/** pcallStaticReturn4Param10 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
pcallStatic4Param10(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, ARG_10 arg10, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			push(L, arg10);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 10))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -4);
				ret2 = to<RET_2>(L, -3);
				ret3 = to<RET_3>(L, -2);
				ret4 = to<RET_4>(L, -1);
				lua_pop(L, 5); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn4Param10

/** phybridStaticReturn4Param10 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
phybridStatic4Param10(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, ARG_10 arg10, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			push(L, arg10);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 10))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -4);
				ret2 = to<RET_2>(L, -3);
				ret3 = to<RET_3>(L, -2);
				ret4 = to<RET_4>(L, -1);
				lua_pop(L, 5); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn4Param10

/** callStaticReturn5Param0 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&) >
inline ScriptToNativeCallResult
callStatic5Param0(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			/*s: module scriptFunction (arguments) */
			lua_call(L, 0);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -5);
			ret2 = to<RET_2>(L, -4);
			ret3 = to<RET_3>(L, -3);
			ret4 = to<RET_4>(L, -2);
			ret5 = to<RET_5>(L, -1);
			lua_pop(L, 6);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn5Param0

/** hybridStaticReturn5Param0 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&) >
inline ScriptToNativeCallResult
hybridStatic5Param0(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			/*s: module scriptFunction (arguments) */
			lua_call(L, 0);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -5);
			ret2 = to<RET_2>(L, -4);
			ret3 = to<RET_3>(L, -3);
			ret4 = to<RET_4>(L, -2);
			ret5 = to<RET_5>(L, -1);
			lua_pop(L, 6);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn5Param0

/** pcallStaticReturn5Param0 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&) >
inline ScriptToNativeCallResult
pcallStatic5Param0(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 0))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -5);
				ret2 = to<RET_2>(L, -4);
				ret3 = to<RET_3>(L, -3);
				ret4 = to<RET_4>(L, -2);
				ret5 = to<RET_5>(L, -1);
				lua_pop(L, 6); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn5Param0

/** phybridStaticReturn5Param0 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&) >
inline ScriptToNativeCallResult
phybridStatic5Param0(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 0))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -5);
				ret2 = to<RET_2>(L, -4);
				ret3 = to<RET_3>(L, -3);
				ret4 = to<RET_4>(L, -2);
				ret5 = to<RET_5>(L, -1);
				lua_pop(L, 6); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn5Param0

/** callStaticReturn5Param1 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1) >
inline ScriptToNativeCallResult
callStatic5Param1(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, ARG_1 arg1, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 1);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -5);
			ret2 = to<RET_2>(L, -4);
			ret3 = to<RET_3>(L, -3);
			ret4 = to<RET_4>(L, -2);
			ret5 = to<RET_5>(L, -1);
			lua_pop(L, 6);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn5Param1

/** hybridStaticReturn5Param1 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1) >
inline ScriptToNativeCallResult
hybridStatic5Param1(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, ARG_1 arg1, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 1);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -5);
			ret2 = to<RET_2>(L, -4);
			ret3 = to<RET_3>(L, -3);
			ret4 = to<RET_4>(L, -2);
			ret5 = to<RET_5>(L, -1);
			lua_pop(L, 6);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, arg1);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, arg1);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn5Param1

/** pcallStaticReturn5Param1 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1) >
inline ScriptToNativeCallResult
pcallStatic5Param1(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, ARG_1 arg1, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 1))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -5);
				ret2 = to<RET_2>(L, -4);
				ret3 = to<RET_3>(L, -3);
				ret4 = to<RET_4>(L, -2);
				ret5 = to<RET_5>(L, -1);
				lua_pop(L, 6); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn5Param1

/** phybridStaticReturn5Param1 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1) >
inline ScriptToNativeCallResult
phybridStatic5Param1(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, ARG_1 arg1, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 1))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -5);
				ret2 = to<RET_2>(L, -4);
				ret3 = to<RET_3>(L, -3);
				ret4 = to<RET_4>(L, -2);
				ret5 = to<RET_5>(L, -1);
				lua_pop(L, 6); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, arg1);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, arg1);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn5Param1

/** callStaticReturn5Param2 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2) >
inline ScriptToNativeCallResult
callStatic5Param2(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, ARG_1 arg1, ARG_2 arg2, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 2);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -5);
			ret2 = to<RET_2>(L, -4);
			ret3 = to<RET_3>(L, -3);
			ret4 = to<RET_4>(L, -2);
			ret5 = to<RET_5>(L, -1);
			lua_pop(L, 6);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn5Param2

/** hybridStaticReturn5Param2 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2) >
inline ScriptToNativeCallResult
hybridStatic5Param2(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, ARG_1 arg1, ARG_2 arg2, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 2);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -5);
			ret2 = to<RET_2>(L, -4);
			ret3 = to<RET_3>(L, -3);
			ret4 = to<RET_4>(L, -2);
			ret5 = to<RET_5>(L, -1);
			lua_pop(L, 6);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn5Param2

/** pcallStaticReturn5Param2 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2) >
inline ScriptToNativeCallResult
pcallStatic5Param2(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, ARG_1 arg1, ARG_2 arg2, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 2))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -5);
				ret2 = to<RET_2>(L, -4);
				ret3 = to<RET_3>(L, -3);
				ret4 = to<RET_4>(L, -2);
				ret5 = to<RET_5>(L, -1);
				lua_pop(L, 6); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn5Param2

/** phybridStaticReturn5Param2 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2) >
inline ScriptToNativeCallResult
phybridStatic5Param2(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, ARG_1 arg1, ARG_2 arg2, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 2))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -5);
				ret2 = to<RET_2>(L, -4);
				ret3 = to<RET_3>(L, -3);
				ret4 = to<RET_4>(L, -2);
				ret5 = to<RET_5>(L, -1);
				lua_pop(L, 6); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn5Param2

/** callStaticReturn5Param3 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
callStatic5Param3(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 3);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -5);
			ret2 = to<RET_2>(L, -4);
			ret3 = to<RET_3>(L, -3);
			ret4 = to<RET_4>(L, -2);
			ret5 = to<RET_5>(L, -1);
			lua_pop(L, 6);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn5Param3

/** hybridStaticReturn5Param3 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
hybridStatic5Param3(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 3);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -5);
			ret2 = to<RET_2>(L, -4);
			ret3 = to<RET_3>(L, -3);
			ret4 = to<RET_4>(L, -2);
			ret5 = to<RET_5>(L, -1);
			lua_pop(L, 6);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn5Param3

/** pcallStaticReturn5Param3 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
pcallStatic5Param3(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 3))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -5);
				ret2 = to<RET_2>(L, -4);
				ret3 = to<RET_3>(L, -3);
				ret4 = to<RET_4>(L, -2);
				ret5 = to<RET_5>(L, -1);
				lua_pop(L, 6); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn5Param3

/** phybridStaticReturn5Param3 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
phybridStatic5Param3(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 3))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -5);
				ret2 = to<RET_2>(L, -4);
				ret3 = to<RET_3>(L, -3);
				ret4 = to<RET_4>(L, -2);
				ret5 = to<RET_5>(L, -1);
				lua_pop(L, 6); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn5Param3

/** callStaticReturn5Param4 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
callStatic5Param4(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 4);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -5);
			ret2 = to<RET_2>(L, -4);
			ret3 = to<RET_3>(L, -3);
			ret4 = to<RET_4>(L, -2);
			ret5 = to<RET_5>(L, -1);
			lua_pop(L, 6);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn5Param4

/** hybridStaticReturn5Param4 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
hybridStatic5Param4(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 4);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -5);
			ret2 = to<RET_2>(L, -4);
			ret3 = to<RET_3>(L, -3);
			ret4 = to<RET_4>(L, -2);
			ret5 = to<RET_5>(L, -1);
			lua_pop(L, 6);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn5Param4

/** pcallStaticReturn5Param4 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
pcallStatic5Param4(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 4))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -5);
				ret2 = to<RET_2>(L, -4);
				ret3 = to<RET_3>(L, -3);
				ret4 = to<RET_4>(L, -2);
				ret5 = to<RET_5>(L, -1);
				lua_pop(L, 6); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn5Param4

/** phybridStaticReturn5Param4 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
phybridStatic5Param4(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 4))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -5);
				ret2 = to<RET_2>(L, -4);
				ret3 = to<RET_3>(L, -3);
				ret4 = to<RET_4>(L, -2);
				ret5 = to<RET_5>(L, -1);
				lua_pop(L, 6); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn5Param4

/** callStaticReturn5Param5 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
callStatic5Param5(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 5);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -5);
			ret2 = to<RET_2>(L, -4);
			ret3 = to<RET_3>(L, -3);
			ret4 = to<RET_4>(L, -2);
			ret5 = to<RET_5>(L, -1);
			lua_pop(L, 6);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn5Param5

/** hybridStaticReturn5Param5 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
hybridStatic5Param5(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 5);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -5);
			ret2 = to<RET_2>(L, -4);
			ret3 = to<RET_3>(L, -3);
			ret4 = to<RET_4>(L, -2);
			ret5 = to<RET_5>(L, -1);
			lua_pop(L, 6);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4, arg5);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4, arg5);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn5Param5

/** pcallStaticReturn5Param5 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
pcallStatic5Param5(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 5))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -5);
				ret2 = to<RET_2>(L, -4);
				ret3 = to<RET_3>(L, -3);
				ret4 = to<RET_4>(L, -2);
				ret5 = to<RET_5>(L, -1);
				lua_pop(L, 6); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn5Param5

/** phybridStaticReturn5Param5 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
phybridStatic5Param5(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 5))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -5);
				ret2 = to<RET_2>(L, -4);
				ret3 = to<RET_3>(L, -3);
				ret4 = to<RET_4>(L, -2);
				ret5 = to<RET_5>(L, -1);
				lua_pop(L, 6); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4, arg5);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4, arg5);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn5Param5

/** callStaticReturn5Param6 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
callStatic5Param6(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 6);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -5);
			ret2 = to<RET_2>(L, -4);
			ret3 = to<RET_3>(L, -3);
			ret4 = to<RET_4>(L, -2);
			ret5 = to<RET_5>(L, -1);
			lua_pop(L, 6);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn5Param6

/** hybridStaticReturn5Param6 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
hybridStatic5Param6(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 6);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -5);
			ret2 = to<RET_2>(L, -4);
			ret3 = to<RET_3>(L, -3);
			ret4 = to<RET_4>(L, -2);
			ret5 = to<RET_5>(L, -1);
			lua_pop(L, 6);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4, arg5, arg6);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn5Param6

/** pcallStaticReturn5Param6 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
pcallStatic5Param6(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 6))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -5);
				ret2 = to<RET_2>(L, -4);
				ret3 = to<RET_3>(L, -3);
				ret4 = to<RET_4>(L, -2);
				ret5 = to<RET_5>(L, -1);
				lua_pop(L, 6); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn5Param6

/** phybridStaticReturn5Param6 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
phybridStatic5Param6(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 6))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -5);
				ret2 = to<RET_2>(L, -4);
				ret3 = to<RET_3>(L, -3);
				ret4 = to<RET_4>(L, -2);
				ret5 = to<RET_5>(L, -1);
				lua_pop(L, 6); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4, arg5, arg6);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn5Param6

/** callStaticReturn5Param7 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
callStatic5Param7(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 7);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -5);
			ret2 = to<RET_2>(L, -4);
			ret3 = to<RET_3>(L, -3);
			ret4 = to<RET_4>(L, -2);
			ret5 = to<RET_5>(L, -1);
			lua_pop(L, 6);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn5Param7

/** hybridStaticReturn5Param7 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
hybridStatic5Param7(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 7);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -5);
			ret2 = to<RET_2>(L, -4);
			ret3 = to<RET_3>(L, -3);
			ret4 = to<RET_4>(L, -2);
			ret5 = to<RET_5>(L, -1);
			lua_pop(L, 6);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn5Param7

/** pcallStaticReturn5Param7 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
pcallStatic5Param7(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 7))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -5);
				ret2 = to<RET_2>(L, -4);
				ret3 = to<RET_3>(L, -3);
				ret4 = to<RET_4>(L, -2);
				ret5 = to<RET_5>(L, -1);
				lua_pop(L, 6); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn5Param7

/** phybridStaticReturn5Param7 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
phybridStatic5Param7(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 7))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -5);
				ret2 = to<RET_2>(L, -4);
				ret3 = to<RET_3>(L, -3);
				ret4 = to<RET_4>(L, -2);
				ret5 = to<RET_5>(L, -1);
				lua_pop(L, 6); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn5Param7

/** callStaticReturn5Param8 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
callStatic5Param8(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 8);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -5);
			ret2 = to<RET_2>(L, -4);
			ret3 = to<RET_3>(L, -3);
			ret4 = to<RET_4>(L, -2);
			ret5 = to<RET_5>(L, -1);
			lua_pop(L, 6);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn5Param8

/** hybridStaticReturn5Param8 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
hybridStatic5Param8(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 8);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -5);
			ret2 = to<RET_2>(L, -4);
			ret3 = to<RET_3>(L, -3);
			ret4 = to<RET_4>(L, -2);
			ret5 = to<RET_5>(L, -1);
			lua_pop(L, 6);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn5Param8

/** pcallStaticReturn5Param8 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
pcallStatic5Param8(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 8))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -5);
				ret2 = to<RET_2>(L, -4);
				ret3 = to<RET_3>(L, -3);
				ret4 = to<RET_4>(L, -2);
				ret5 = to<RET_5>(L, -1);
				lua_pop(L, 6); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn5Param8

/** phybridStaticReturn5Param8 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
phybridStatic5Param8(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 8))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -5);
				ret2 = to<RET_2>(L, -4);
				ret3 = to<RET_3>(L, -3);
				ret4 = to<RET_4>(L, -2);
				ret5 = to<RET_5>(L, -1);
				lua_pop(L, 6); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn5Param8

/** callStaticReturn5Param9 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
callStatic5Param9(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 9);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -5);
			ret2 = to<RET_2>(L, -4);
			ret3 = to<RET_3>(L, -3);
			ret4 = to<RET_4>(L, -2);
			ret5 = to<RET_5>(L, -1);
			lua_pop(L, 6);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn5Param9

/** hybridStaticReturn5Param9 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
hybridStatic5Param9(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 9);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -5);
			ret2 = to<RET_2>(L, -4);
			ret3 = to<RET_3>(L, -3);
			ret4 = to<RET_4>(L, -2);
			ret5 = to<RET_5>(L, -1);
			lua_pop(L, 6);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn5Param9

/** pcallStaticReturn5Param9 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
pcallStatic5Param9(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 9))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -5);
				ret2 = to<RET_2>(L, -4);
				ret3 = to<RET_3>(L, -3);
				ret4 = to<RET_4>(L, -2);
				ret5 = to<RET_5>(L, -1);
				lua_pop(L, 6); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn5Param9

/** phybridStaticReturn5Param9 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
phybridStatic5Param9(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 9))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -5);
				ret2 = to<RET_2>(L, -4);
				ret3 = to<RET_3>(L, -3);
				ret4 = to<RET_4>(L, -2);
				ret5 = to<RET_5>(L, -1);
				lua_pop(L, 6); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn5Param9

/** callStaticReturn5Param10 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
callStatic5Param10(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, ARG_10 arg10, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			push(L, arg10);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 10);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -5);
			ret2 = to<RET_2>(L, -4);
			ret3 = to<RET_3>(L, -3);
			ret4 = to<RET_4>(L, -2);
			ret5 = to<RET_5>(L, -1);
			lua_pop(L, 6);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn5Param10

/** hybridStaticReturn5Param10 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
hybridStatic5Param10(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, ARG_10 arg10, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			push(L, arg10);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 10);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -5);
			ret2 = to<RET_2>(L, -4);
			ret3 = to<RET_3>(L, -3);
			ret4 = to<RET_4>(L, -2);
			ret5 = to<RET_5>(L, -1);
			lua_pop(L, 6);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn5Param10

/** pcallStaticReturn5Param10 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
pcallStatic5Param10(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, ARG_10 arg10, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			push(L, arg10);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 10))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -5);
				ret2 = to<RET_2>(L, -4);
				ret3 = to<RET_3>(L, -3);
				ret4 = to<RET_4>(L, -2);
				ret5 = to<RET_5>(L, -1);
				lua_pop(L, 6); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn5Param10

/** phybridStaticReturn5Param10 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
phybridStatic5Param10(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, ARG_10 arg10, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			push(L, arg10);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 10))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -5);
				ret2 = to<RET_2>(L, -4);
				ret3 = to<RET_3>(L, -3);
				ret4 = to<RET_4>(L, -2);
				ret5 = to<RET_5>(L, -1);
				lua_pop(L, 6); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn5Param10

/** callStaticReturn6Param0 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&) >
inline ScriptToNativeCallResult
callStatic6Param0(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			/*s: module scriptFunction (arguments) */
			lua_call(L, 0);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -6);
			ret2 = to<RET_2>(L, -5);
			ret3 = to<RET_3>(L, -4);
			ret4 = to<RET_4>(L, -3);
			ret5 = to<RET_5>(L, -2);
			ret6 = to<RET_6>(L, -1);
			lua_pop(L, 7);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn6Param0

/** hybridStaticReturn6Param0 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&) >
inline ScriptToNativeCallResult
hybridStatic6Param0(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			/*s: module scriptFunction (arguments) */
			lua_call(L, 0);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -6);
			ret2 = to<RET_2>(L, -5);
			ret3 = to<RET_3>(L, -4);
			ret4 = to<RET_4>(L, -3);
			ret5 = to<RET_5>(L, -2);
			ret6 = to<RET_6>(L, -1);
			lua_pop(L, 7);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn6Param0

/** pcallStaticReturn6Param0 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&) >
inline ScriptToNativeCallResult
pcallStatic6Param0(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 0))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -6);
				ret2 = to<RET_2>(L, -5);
				ret3 = to<RET_3>(L, -4);
				ret4 = to<RET_4>(L, -3);
				ret5 = to<RET_5>(L, -2);
				ret6 = to<RET_6>(L, -1);
				lua_pop(L, 7); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn6Param0

/** phybridStaticReturn6Param0 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&) >
inline ScriptToNativeCallResult
phybridStatic6Param0(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 0))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -6);
				ret2 = to<RET_2>(L, -5);
				ret3 = to<RET_3>(L, -4);
				ret4 = to<RET_4>(L, -3);
				ret5 = to<RET_5>(L, -2);
				ret6 = to<RET_6>(L, -1);
				lua_pop(L, 7); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn6Param0

/** callStaticReturn6Param1 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1) >
inline ScriptToNativeCallResult
callStatic6Param1(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, ARG_1 arg1, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 1);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -6);
			ret2 = to<RET_2>(L, -5);
			ret3 = to<RET_3>(L, -4);
			ret4 = to<RET_4>(L, -3);
			ret5 = to<RET_5>(L, -2);
			ret6 = to<RET_6>(L, -1);
			lua_pop(L, 7);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn6Param1

/** hybridStaticReturn6Param1 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1) >
inline ScriptToNativeCallResult
hybridStatic6Param1(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, ARG_1 arg1, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 1);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -6);
			ret2 = to<RET_2>(L, -5);
			ret3 = to<RET_3>(L, -4);
			ret4 = to<RET_4>(L, -3);
			ret5 = to<RET_5>(L, -2);
			ret6 = to<RET_6>(L, -1);
			lua_pop(L, 7);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn6Param1

/** pcallStaticReturn6Param1 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1) >
inline ScriptToNativeCallResult
pcallStatic6Param1(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, ARG_1 arg1, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 1))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -6);
				ret2 = to<RET_2>(L, -5);
				ret3 = to<RET_3>(L, -4);
				ret4 = to<RET_4>(L, -3);
				ret5 = to<RET_5>(L, -2);
				ret6 = to<RET_6>(L, -1);
				lua_pop(L, 7); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn6Param1

/** phybridStaticReturn6Param1 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1) >
inline ScriptToNativeCallResult
phybridStatic6Param1(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, ARG_1 arg1, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 1))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -6);
				ret2 = to<RET_2>(L, -5);
				ret3 = to<RET_3>(L, -4);
				ret4 = to<RET_4>(L, -3);
				ret5 = to<RET_5>(L, -2);
				ret6 = to<RET_6>(L, -1);
				lua_pop(L, 7); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn6Param1

/** callStaticReturn6Param2 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2) >
inline ScriptToNativeCallResult
callStatic6Param2(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, ARG_1 arg1, ARG_2 arg2, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 2);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -6);
			ret2 = to<RET_2>(L, -5);
			ret3 = to<RET_3>(L, -4);
			ret4 = to<RET_4>(L, -3);
			ret5 = to<RET_5>(L, -2);
			ret6 = to<RET_6>(L, -1);
			lua_pop(L, 7);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn6Param2

/** hybridStaticReturn6Param2 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2) >
inline ScriptToNativeCallResult
hybridStatic6Param2(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, ARG_1 arg1, ARG_2 arg2, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 2);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -6);
			ret2 = to<RET_2>(L, -5);
			ret3 = to<RET_3>(L, -4);
			ret4 = to<RET_4>(L, -3);
			ret5 = to<RET_5>(L, -2);
			ret6 = to<RET_6>(L, -1);
			lua_pop(L, 7);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn6Param2

/** pcallStaticReturn6Param2 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2) >
inline ScriptToNativeCallResult
pcallStatic6Param2(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, ARG_1 arg1, ARG_2 arg2, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 2))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -6);
				ret2 = to<RET_2>(L, -5);
				ret3 = to<RET_3>(L, -4);
				ret4 = to<RET_4>(L, -3);
				ret5 = to<RET_5>(L, -2);
				ret6 = to<RET_6>(L, -1);
				lua_pop(L, 7); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn6Param2

/** phybridStaticReturn6Param2 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2) >
inline ScriptToNativeCallResult
phybridStatic6Param2(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, ARG_1 arg1, ARG_2 arg2, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 2))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -6);
				ret2 = to<RET_2>(L, -5);
				ret3 = to<RET_3>(L, -4);
				ret4 = to<RET_4>(L, -3);
				ret5 = to<RET_5>(L, -2);
				ret6 = to<RET_6>(L, -1);
				lua_pop(L, 7); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn6Param2

/** callStaticReturn6Param3 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
callStatic6Param3(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 3);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -6);
			ret2 = to<RET_2>(L, -5);
			ret3 = to<RET_3>(L, -4);
			ret4 = to<RET_4>(L, -3);
			ret5 = to<RET_5>(L, -2);
			ret6 = to<RET_6>(L, -1);
			lua_pop(L, 7);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn6Param3

/** hybridStaticReturn6Param3 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
hybridStatic6Param3(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 3);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -6);
			ret2 = to<RET_2>(L, -5);
			ret3 = to<RET_3>(L, -4);
			ret4 = to<RET_4>(L, -3);
			ret5 = to<RET_5>(L, -2);
			ret6 = to<RET_6>(L, -1);
			lua_pop(L, 7);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn6Param3

/** pcallStaticReturn6Param3 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
pcallStatic6Param3(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 3))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -6);
				ret2 = to<RET_2>(L, -5);
				ret3 = to<RET_3>(L, -4);
				ret4 = to<RET_4>(L, -3);
				ret5 = to<RET_5>(L, -2);
				ret6 = to<RET_6>(L, -1);
				lua_pop(L, 7); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn6Param3

/** phybridStaticReturn6Param3 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
phybridStatic6Param3(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 3))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -6);
				ret2 = to<RET_2>(L, -5);
				ret3 = to<RET_3>(L, -4);
				ret4 = to<RET_4>(L, -3);
				ret5 = to<RET_5>(L, -2);
				ret6 = to<RET_6>(L, -1);
				lua_pop(L, 7); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn6Param3

/** callStaticReturn6Param4 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
callStatic6Param4(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 4);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -6);
			ret2 = to<RET_2>(L, -5);
			ret3 = to<RET_3>(L, -4);
			ret4 = to<RET_4>(L, -3);
			ret5 = to<RET_5>(L, -2);
			ret6 = to<RET_6>(L, -1);
			lua_pop(L, 7);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn6Param4

/** hybridStaticReturn6Param4 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
hybridStatic6Param4(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 4);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -6);
			ret2 = to<RET_2>(L, -5);
			ret3 = to<RET_3>(L, -4);
			ret4 = to<RET_4>(L, -3);
			ret5 = to<RET_5>(L, -2);
			ret6 = to<RET_6>(L, -1);
			lua_pop(L, 7);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn6Param4

/** pcallStaticReturn6Param4 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
pcallStatic6Param4(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 4))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -6);
				ret2 = to<RET_2>(L, -5);
				ret3 = to<RET_3>(L, -4);
				ret4 = to<RET_4>(L, -3);
				ret5 = to<RET_5>(L, -2);
				ret6 = to<RET_6>(L, -1);
				lua_pop(L, 7); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn6Param4

/** phybridStaticReturn6Param4 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
phybridStatic6Param4(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 4))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -6);
				ret2 = to<RET_2>(L, -5);
				ret3 = to<RET_3>(L, -4);
				ret4 = to<RET_4>(L, -3);
				ret5 = to<RET_5>(L, -2);
				ret6 = to<RET_6>(L, -1);
				lua_pop(L, 7); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn6Param4

/** callStaticReturn6Param5 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
callStatic6Param5(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 5);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -6);
			ret2 = to<RET_2>(L, -5);
			ret3 = to<RET_3>(L, -4);
			ret4 = to<RET_4>(L, -3);
			ret5 = to<RET_5>(L, -2);
			ret6 = to<RET_6>(L, -1);
			lua_pop(L, 7);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn6Param5

/** hybridStaticReturn6Param5 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
hybridStatic6Param5(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 5);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -6);
			ret2 = to<RET_2>(L, -5);
			ret3 = to<RET_3>(L, -4);
			ret4 = to<RET_4>(L, -3);
			ret5 = to<RET_5>(L, -2);
			ret6 = to<RET_6>(L, -1);
			lua_pop(L, 7);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4, arg5);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4, arg5);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn6Param5

/** pcallStaticReturn6Param5 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
pcallStatic6Param5(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 5))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -6);
				ret2 = to<RET_2>(L, -5);
				ret3 = to<RET_3>(L, -4);
				ret4 = to<RET_4>(L, -3);
				ret5 = to<RET_5>(L, -2);
				ret6 = to<RET_6>(L, -1);
				lua_pop(L, 7); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn6Param5

/** phybridStaticReturn6Param5 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
phybridStatic6Param5(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 5))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -6);
				ret2 = to<RET_2>(L, -5);
				ret3 = to<RET_3>(L, -4);
				ret4 = to<RET_4>(L, -3);
				ret5 = to<RET_5>(L, -2);
				ret6 = to<RET_6>(L, -1);
				lua_pop(L, 7); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4, arg5);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4, arg5);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn6Param5

/** callStaticReturn6Param6 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
callStatic6Param6(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 6);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -6);
			ret2 = to<RET_2>(L, -5);
			ret3 = to<RET_3>(L, -4);
			ret4 = to<RET_4>(L, -3);
			ret5 = to<RET_5>(L, -2);
			ret6 = to<RET_6>(L, -1);
			lua_pop(L, 7);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn6Param6

/** hybridStaticReturn6Param6 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
hybridStatic6Param6(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 6);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -6);
			ret2 = to<RET_2>(L, -5);
			ret3 = to<RET_3>(L, -4);
			ret4 = to<RET_4>(L, -3);
			ret5 = to<RET_5>(L, -2);
			ret6 = to<RET_6>(L, -1);
			lua_pop(L, 7);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4, arg5, arg6);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn6Param6

/** pcallStaticReturn6Param6 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
pcallStatic6Param6(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 6))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -6);
				ret2 = to<RET_2>(L, -5);
				ret3 = to<RET_3>(L, -4);
				ret4 = to<RET_4>(L, -3);
				ret5 = to<RET_5>(L, -2);
				ret6 = to<RET_6>(L, -1);
				lua_pop(L, 7); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn6Param6

/** phybridStaticReturn6Param6 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
phybridStatic6Param6(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 6))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -6);
				ret2 = to<RET_2>(L, -5);
				ret3 = to<RET_3>(L, -4);
				ret4 = to<RET_4>(L, -3);
				ret5 = to<RET_5>(L, -2);
				ret6 = to<RET_6>(L, -1);
				lua_pop(L, 7); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4, arg5, arg6);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn6Param6

/** callStaticReturn6Param7 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
callStatic6Param7(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 7);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -6);
			ret2 = to<RET_2>(L, -5);
			ret3 = to<RET_3>(L, -4);
			ret4 = to<RET_4>(L, -3);
			ret5 = to<RET_5>(L, -2);
			ret6 = to<RET_6>(L, -1);
			lua_pop(L, 7);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn6Param7

/** hybridStaticReturn6Param7 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
hybridStatic6Param7(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 7);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -6);
			ret2 = to<RET_2>(L, -5);
			ret3 = to<RET_3>(L, -4);
			ret4 = to<RET_4>(L, -3);
			ret5 = to<RET_5>(L, -2);
			ret6 = to<RET_6>(L, -1);
			lua_pop(L, 7);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn6Param7

/** pcallStaticReturn6Param7 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
pcallStatic6Param7(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 7))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -6);
				ret2 = to<RET_2>(L, -5);
				ret3 = to<RET_3>(L, -4);
				ret4 = to<RET_4>(L, -3);
				ret5 = to<RET_5>(L, -2);
				ret6 = to<RET_6>(L, -1);
				lua_pop(L, 7); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn6Param7

/** phybridStaticReturn6Param7 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
phybridStatic6Param7(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 7))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -6);
				ret2 = to<RET_2>(L, -5);
				ret3 = to<RET_3>(L, -4);
				ret4 = to<RET_4>(L, -3);
				ret5 = to<RET_5>(L, -2);
				ret6 = to<RET_6>(L, -1);
				lua_pop(L, 7); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn6Param7

/** callStaticReturn6Param8 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
callStatic6Param8(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 8);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -6);
			ret2 = to<RET_2>(L, -5);
			ret3 = to<RET_3>(L, -4);
			ret4 = to<RET_4>(L, -3);
			ret5 = to<RET_5>(L, -2);
			ret6 = to<RET_6>(L, -1);
			lua_pop(L, 7);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn6Param8

/** hybridStaticReturn6Param8 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
hybridStatic6Param8(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 8);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -6);
			ret2 = to<RET_2>(L, -5);
			ret3 = to<RET_3>(L, -4);
			ret4 = to<RET_4>(L, -3);
			ret5 = to<RET_5>(L, -2);
			ret6 = to<RET_6>(L, -1);
			lua_pop(L, 7);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn6Param8

/** pcallStaticReturn6Param8 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
pcallStatic6Param8(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 8))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -6);
				ret2 = to<RET_2>(L, -5);
				ret3 = to<RET_3>(L, -4);
				ret4 = to<RET_4>(L, -3);
				ret5 = to<RET_5>(L, -2);
				ret6 = to<RET_6>(L, -1);
				lua_pop(L, 7); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn6Param8

/** phybridStaticReturn6Param8 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
phybridStatic6Param8(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 8))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -6);
				ret2 = to<RET_2>(L, -5);
				ret3 = to<RET_3>(L, -4);
				ret4 = to<RET_4>(L, -3);
				ret5 = to<RET_5>(L, -2);
				ret6 = to<RET_6>(L, -1);
				lua_pop(L, 7); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn6Param8

/** callStaticReturn6Param9 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
callStatic6Param9(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 9);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -6);
			ret2 = to<RET_2>(L, -5);
			ret3 = to<RET_3>(L, -4);
			ret4 = to<RET_4>(L, -3);
			ret5 = to<RET_5>(L, -2);
			ret6 = to<RET_6>(L, -1);
			lua_pop(L, 7);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn6Param9

/** hybridStaticReturn6Param9 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
hybridStatic6Param9(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 9);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -6);
			ret2 = to<RET_2>(L, -5);
			ret3 = to<RET_3>(L, -4);
			ret4 = to<RET_4>(L, -3);
			ret5 = to<RET_5>(L, -2);
			ret6 = to<RET_6>(L, -1);
			lua_pop(L, 7);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn6Param9

/** pcallStaticReturn6Param9 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
pcallStatic6Param9(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 9))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -6);
				ret2 = to<RET_2>(L, -5);
				ret3 = to<RET_3>(L, -4);
				ret4 = to<RET_4>(L, -3);
				ret5 = to<RET_5>(L, -2);
				ret6 = to<RET_6>(L, -1);
				lua_pop(L, 7); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn6Param9

/** phybridStaticReturn6Param9 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
phybridStatic6Param9(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 9))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -6);
				ret2 = to<RET_2>(L, -5);
				ret3 = to<RET_3>(L, -4);
				ret4 = to<RET_4>(L, -3);
				ret5 = to<RET_5>(L, -2);
				ret6 = to<RET_6>(L, -1);
				lua_pop(L, 7); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn6Param9

/** callStaticReturn6Param10 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
callStatic6Param10(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, ARG_10 arg10, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			push(L, arg10);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 10);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -6);
			ret2 = to<RET_2>(L, -5);
			ret3 = to<RET_3>(L, -4);
			ret4 = to<RET_4>(L, -3);
			ret5 = to<RET_5>(L, -2);
			ret6 = to<RET_6>(L, -1);
			lua_pop(L, 7);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn6Param10

/** hybridStaticReturn6Param10 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
hybridStatic6Param10(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, ARG_10 arg10, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			push(L, arg10);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 10);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -6);
			ret2 = to<RET_2>(L, -5);
			ret3 = to<RET_3>(L, -4);
			ret4 = to<RET_4>(L, -3);
			ret5 = to<RET_5>(L, -2);
			ret6 = to<RET_6>(L, -1);
			lua_pop(L, 7);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn6Param10

/** pcallStaticReturn6Param10 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
pcallStatic6Param10(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, ARG_10 arg10, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			push(L, arg10);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 10))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -6);
				ret2 = to<RET_2>(L, -5);
				ret3 = to<RET_3>(L, -4);
				ret4 = to<RET_4>(L, -3);
				ret5 = to<RET_5>(L, -2);
				ret6 = to<RET_6>(L, -1);
				lua_pop(L, 7); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn6Param10

/** phybridStaticReturn6Param10 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
phybridStatic6Param10(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, ARG_10 arg10, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			push(L, arg10);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 10))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -6);
				ret2 = to<RET_2>(L, -5);
				ret3 = to<RET_3>(L, -4);
				ret4 = to<RET_4>(L, -3);
				ret5 = to<RET_5>(L, -2);
				ret6 = to<RET_6>(L, -1);
				lua_pop(L, 7); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn6Param10

/** callStaticReturn7Param0 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&) >
inline ScriptToNativeCallResult
callStatic7Param0(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			/*s: module scriptFunction (arguments) */
			lua_call(L, 0);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -7);
			ret2 = to<RET_2>(L, -6);
			ret3 = to<RET_3>(L, -5);
			ret4 = to<RET_4>(L, -4);
			ret5 = to<RET_5>(L, -3);
			ret6 = to<RET_6>(L, -2);
			ret7 = to<RET_7>(L, -1);
			lua_pop(L, 8);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn7Param0

/** hybridStaticReturn7Param0 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&) >
inline ScriptToNativeCallResult
hybridStatic7Param0(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			/*s: module scriptFunction (arguments) */
			lua_call(L, 0);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -7);
			ret2 = to<RET_2>(L, -6);
			ret3 = to<RET_3>(L, -5);
			ret4 = to<RET_4>(L, -4);
			ret5 = to<RET_5>(L, -3);
			ret6 = to<RET_6>(L, -2);
			ret7 = to<RET_7>(L, -1);
			lua_pop(L, 8);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn7Param0

/** pcallStaticReturn7Param0 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&) >
inline ScriptToNativeCallResult
pcallStatic7Param0(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 0))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -7);
				ret2 = to<RET_2>(L, -6);
				ret3 = to<RET_3>(L, -5);
				ret4 = to<RET_4>(L, -4);
				ret5 = to<RET_5>(L, -3);
				ret6 = to<RET_6>(L, -2);
				ret7 = to<RET_7>(L, -1);
				lua_pop(L, 8); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn7Param0

/** phybridStaticReturn7Param0 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&) >
inline ScriptToNativeCallResult
phybridStatic7Param0(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 0))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -7);
				ret2 = to<RET_2>(L, -6);
				ret3 = to<RET_3>(L, -5);
				ret4 = to<RET_4>(L, -4);
				ret5 = to<RET_5>(L, -3);
				ret6 = to<RET_6>(L, -2);
				ret7 = to<RET_7>(L, -1);
				lua_pop(L, 8); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn7Param0

/** callStaticReturn7Param1 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1) >
inline ScriptToNativeCallResult
callStatic7Param1(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, ARG_1 arg1, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 1);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -7);
			ret2 = to<RET_2>(L, -6);
			ret3 = to<RET_3>(L, -5);
			ret4 = to<RET_4>(L, -4);
			ret5 = to<RET_5>(L, -3);
			ret6 = to<RET_6>(L, -2);
			ret7 = to<RET_7>(L, -1);
			lua_pop(L, 8);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn7Param1

/** hybridStaticReturn7Param1 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1) >
inline ScriptToNativeCallResult
hybridStatic7Param1(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, ARG_1 arg1, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 1);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -7);
			ret2 = to<RET_2>(L, -6);
			ret3 = to<RET_3>(L, -5);
			ret4 = to<RET_4>(L, -4);
			ret5 = to<RET_5>(L, -3);
			ret6 = to<RET_6>(L, -2);
			ret7 = to<RET_7>(L, -1);
			lua_pop(L, 8);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn7Param1

/** pcallStaticReturn7Param1 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1) >
inline ScriptToNativeCallResult
pcallStatic7Param1(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, ARG_1 arg1, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 1))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -7);
				ret2 = to<RET_2>(L, -6);
				ret3 = to<RET_3>(L, -5);
				ret4 = to<RET_4>(L, -4);
				ret5 = to<RET_5>(L, -3);
				ret6 = to<RET_6>(L, -2);
				ret7 = to<RET_7>(L, -1);
				lua_pop(L, 8); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn7Param1

/** phybridStaticReturn7Param1 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1) >
inline ScriptToNativeCallResult
phybridStatic7Param1(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, ARG_1 arg1, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 1))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -7);
				ret2 = to<RET_2>(L, -6);
				ret3 = to<RET_3>(L, -5);
				ret4 = to<RET_4>(L, -4);
				ret5 = to<RET_5>(L, -3);
				ret6 = to<RET_6>(L, -2);
				ret7 = to<RET_7>(L, -1);
				lua_pop(L, 8); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn7Param1

/** callStaticReturn7Param2 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2) >
inline ScriptToNativeCallResult
callStatic7Param2(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, ARG_1 arg1, ARG_2 arg2, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 2);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -7);
			ret2 = to<RET_2>(L, -6);
			ret3 = to<RET_3>(L, -5);
			ret4 = to<RET_4>(L, -4);
			ret5 = to<RET_5>(L, -3);
			ret6 = to<RET_6>(L, -2);
			ret7 = to<RET_7>(L, -1);
			lua_pop(L, 8);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn7Param2

/** hybridStaticReturn7Param2 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2) >
inline ScriptToNativeCallResult
hybridStatic7Param2(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, ARG_1 arg1, ARG_2 arg2, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 2);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -7);
			ret2 = to<RET_2>(L, -6);
			ret3 = to<RET_3>(L, -5);
			ret4 = to<RET_4>(L, -4);
			ret5 = to<RET_5>(L, -3);
			ret6 = to<RET_6>(L, -2);
			ret7 = to<RET_7>(L, -1);
			lua_pop(L, 8);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn7Param2

/** pcallStaticReturn7Param2 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2) >
inline ScriptToNativeCallResult
pcallStatic7Param2(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, ARG_1 arg1, ARG_2 arg2, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 2))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -7);
				ret2 = to<RET_2>(L, -6);
				ret3 = to<RET_3>(L, -5);
				ret4 = to<RET_4>(L, -4);
				ret5 = to<RET_5>(L, -3);
				ret6 = to<RET_6>(L, -2);
				ret7 = to<RET_7>(L, -1);
				lua_pop(L, 8); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn7Param2

/** phybridStaticReturn7Param2 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2) >
inline ScriptToNativeCallResult
phybridStatic7Param2(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, ARG_1 arg1, ARG_2 arg2, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 2))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -7);
				ret2 = to<RET_2>(L, -6);
				ret3 = to<RET_3>(L, -5);
				ret4 = to<RET_4>(L, -4);
				ret5 = to<RET_5>(L, -3);
				ret6 = to<RET_6>(L, -2);
				ret7 = to<RET_7>(L, -1);
				lua_pop(L, 8); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn7Param2

/** callStaticReturn7Param3 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
callStatic7Param3(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 3);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -7);
			ret2 = to<RET_2>(L, -6);
			ret3 = to<RET_3>(L, -5);
			ret4 = to<RET_4>(L, -4);
			ret5 = to<RET_5>(L, -3);
			ret6 = to<RET_6>(L, -2);
			ret7 = to<RET_7>(L, -1);
			lua_pop(L, 8);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn7Param3

/** hybridStaticReturn7Param3 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
hybridStatic7Param3(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 3);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -7);
			ret2 = to<RET_2>(L, -6);
			ret3 = to<RET_3>(L, -5);
			ret4 = to<RET_4>(L, -4);
			ret5 = to<RET_5>(L, -3);
			ret6 = to<RET_6>(L, -2);
			ret7 = to<RET_7>(L, -1);
			lua_pop(L, 8);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn7Param3

/** pcallStaticReturn7Param3 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
pcallStatic7Param3(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 3))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -7);
				ret2 = to<RET_2>(L, -6);
				ret3 = to<RET_3>(L, -5);
				ret4 = to<RET_4>(L, -4);
				ret5 = to<RET_5>(L, -3);
				ret6 = to<RET_6>(L, -2);
				ret7 = to<RET_7>(L, -1);
				lua_pop(L, 8); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn7Param3

/** phybridStaticReturn7Param3 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
phybridStatic7Param3(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 3))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -7);
				ret2 = to<RET_2>(L, -6);
				ret3 = to<RET_3>(L, -5);
				ret4 = to<RET_4>(L, -4);
				ret5 = to<RET_5>(L, -3);
				ret6 = to<RET_6>(L, -2);
				ret7 = to<RET_7>(L, -1);
				lua_pop(L, 8); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn7Param3

/** callStaticReturn7Param4 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
callStatic7Param4(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 4);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -7);
			ret2 = to<RET_2>(L, -6);
			ret3 = to<RET_3>(L, -5);
			ret4 = to<RET_4>(L, -4);
			ret5 = to<RET_5>(L, -3);
			ret6 = to<RET_6>(L, -2);
			ret7 = to<RET_7>(L, -1);
			lua_pop(L, 8);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn7Param4

/** hybridStaticReturn7Param4 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
hybridStatic7Param4(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 4);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -7);
			ret2 = to<RET_2>(L, -6);
			ret3 = to<RET_3>(L, -5);
			ret4 = to<RET_4>(L, -4);
			ret5 = to<RET_5>(L, -3);
			ret6 = to<RET_6>(L, -2);
			ret7 = to<RET_7>(L, -1);
			lua_pop(L, 8);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn7Param4

/** pcallStaticReturn7Param4 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
pcallStatic7Param4(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 4))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -7);
				ret2 = to<RET_2>(L, -6);
				ret3 = to<RET_3>(L, -5);
				ret4 = to<RET_4>(L, -4);
				ret5 = to<RET_5>(L, -3);
				ret6 = to<RET_6>(L, -2);
				ret7 = to<RET_7>(L, -1);
				lua_pop(L, 8); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn7Param4

/** phybridStaticReturn7Param4 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
phybridStatic7Param4(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 4))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -7);
				ret2 = to<RET_2>(L, -6);
				ret3 = to<RET_3>(L, -5);
				ret4 = to<RET_4>(L, -4);
				ret5 = to<RET_5>(L, -3);
				ret6 = to<RET_6>(L, -2);
				ret7 = to<RET_7>(L, -1);
				lua_pop(L, 8); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn7Param4

/** callStaticReturn7Param5 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
callStatic7Param5(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 5);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -7);
			ret2 = to<RET_2>(L, -6);
			ret3 = to<RET_3>(L, -5);
			ret4 = to<RET_4>(L, -4);
			ret5 = to<RET_5>(L, -3);
			ret6 = to<RET_6>(L, -2);
			ret7 = to<RET_7>(L, -1);
			lua_pop(L, 8);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn7Param5

/** hybridStaticReturn7Param5 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
hybridStatic7Param5(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 5);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -7);
			ret2 = to<RET_2>(L, -6);
			ret3 = to<RET_3>(L, -5);
			ret4 = to<RET_4>(L, -4);
			ret5 = to<RET_5>(L, -3);
			ret6 = to<RET_6>(L, -2);
			ret7 = to<RET_7>(L, -1);
			lua_pop(L, 8);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4, arg5);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4, arg5);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn7Param5

/** pcallStaticReturn7Param5 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
pcallStatic7Param5(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 5))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -7);
				ret2 = to<RET_2>(L, -6);
				ret3 = to<RET_3>(L, -5);
				ret4 = to<RET_4>(L, -4);
				ret5 = to<RET_5>(L, -3);
				ret6 = to<RET_6>(L, -2);
				ret7 = to<RET_7>(L, -1);
				lua_pop(L, 8); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn7Param5

/** phybridStaticReturn7Param5 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
phybridStatic7Param5(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 5))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -7);
				ret2 = to<RET_2>(L, -6);
				ret3 = to<RET_3>(L, -5);
				ret4 = to<RET_4>(L, -4);
				ret5 = to<RET_5>(L, -3);
				ret6 = to<RET_6>(L, -2);
				ret7 = to<RET_7>(L, -1);
				lua_pop(L, 8); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4, arg5);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4, arg5);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn7Param5

/** callStaticReturn7Param6 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
callStatic7Param6(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 6);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -7);
			ret2 = to<RET_2>(L, -6);
			ret3 = to<RET_3>(L, -5);
			ret4 = to<RET_4>(L, -4);
			ret5 = to<RET_5>(L, -3);
			ret6 = to<RET_6>(L, -2);
			ret7 = to<RET_7>(L, -1);
			lua_pop(L, 8);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn7Param6

/** hybridStaticReturn7Param6 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
hybridStatic7Param6(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 6);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -7);
			ret2 = to<RET_2>(L, -6);
			ret3 = to<RET_3>(L, -5);
			ret4 = to<RET_4>(L, -4);
			ret5 = to<RET_5>(L, -3);
			ret6 = to<RET_6>(L, -2);
			ret7 = to<RET_7>(L, -1);
			lua_pop(L, 8);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4, arg5, arg6);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn7Param6

/** pcallStaticReturn7Param6 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
pcallStatic7Param6(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 6))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -7);
				ret2 = to<RET_2>(L, -6);
				ret3 = to<RET_3>(L, -5);
				ret4 = to<RET_4>(L, -4);
				ret5 = to<RET_5>(L, -3);
				ret6 = to<RET_6>(L, -2);
				ret7 = to<RET_7>(L, -1);
				lua_pop(L, 8); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn7Param6

/** phybridStaticReturn7Param6 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
phybridStatic7Param6(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 6))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -7);
				ret2 = to<RET_2>(L, -6);
				ret3 = to<RET_3>(L, -5);
				ret4 = to<RET_4>(L, -4);
				ret5 = to<RET_5>(L, -3);
				ret6 = to<RET_6>(L, -2);
				ret7 = to<RET_7>(L, -1);
				lua_pop(L, 8); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4, arg5, arg6);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn7Param6

/** callStaticReturn7Param7 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
callStatic7Param7(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 7);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -7);
			ret2 = to<RET_2>(L, -6);
			ret3 = to<RET_3>(L, -5);
			ret4 = to<RET_4>(L, -4);
			ret5 = to<RET_5>(L, -3);
			ret6 = to<RET_6>(L, -2);
			ret7 = to<RET_7>(L, -1);
			lua_pop(L, 8);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn7Param7

/** hybridStaticReturn7Param7 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
hybridStatic7Param7(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 7);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -7);
			ret2 = to<RET_2>(L, -6);
			ret3 = to<RET_3>(L, -5);
			ret4 = to<RET_4>(L, -4);
			ret5 = to<RET_5>(L, -3);
			ret6 = to<RET_6>(L, -2);
			ret7 = to<RET_7>(L, -1);
			lua_pop(L, 8);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn7Param7

/** pcallStaticReturn7Param7 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
pcallStatic7Param7(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 7))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -7);
				ret2 = to<RET_2>(L, -6);
				ret3 = to<RET_3>(L, -5);
				ret4 = to<RET_4>(L, -4);
				ret5 = to<RET_5>(L, -3);
				ret6 = to<RET_6>(L, -2);
				ret7 = to<RET_7>(L, -1);
				lua_pop(L, 8); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn7Param7

/** phybridStaticReturn7Param7 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
phybridStatic7Param7(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 7))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -7);
				ret2 = to<RET_2>(L, -6);
				ret3 = to<RET_3>(L, -5);
				ret4 = to<RET_4>(L, -4);
				ret5 = to<RET_5>(L, -3);
				ret6 = to<RET_6>(L, -2);
				ret7 = to<RET_7>(L, -1);
				lua_pop(L, 8); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn7Param7

/** callStaticReturn7Param8 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
callStatic7Param8(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 8);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -7);
			ret2 = to<RET_2>(L, -6);
			ret3 = to<RET_3>(L, -5);
			ret4 = to<RET_4>(L, -4);
			ret5 = to<RET_5>(L, -3);
			ret6 = to<RET_6>(L, -2);
			ret7 = to<RET_7>(L, -1);
			lua_pop(L, 8);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn7Param8

/** hybridStaticReturn7Param8 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
hybridStatic7Param8(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 8);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -7);
			ret2 = to<RET_2>(L, -6);
			ret3 = to<RET_3>(L, -5);
			ret4 = to<RET_4>(L, -4);
			ret5 = to<RET_5>(L, -3);
			ret6 = to<RET_6>(L, -2);
			ret7 = to<RET_7>(L, -1);
			lua_pop(L, 8);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn7Param8

/** pcallStaticReturn7Param8 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
pcallStatic7Param8(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 8))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -7);
				ret2 = to<RET_2>(L, -6);
				ret3 = to<RET_3>(L, -5);
				ret4 = to<RET_4>(L, -4);
				ret5 = to<RET_5>(L, -3);
				ret6 = to<RET_6>(L, -2);
				ret7 = to<RET_7>(L, -1);
				lua_pop(L, 8); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn7Param8

/** phybridStaticReturn7Param8 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
phybridStatic7Param8(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 8))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -7);
				ret2 = to<RET_2>(L, -6);
				ret3 = to<RET_3>(L, -5);
				ret4 = to<RET_4>(L, -4);
				ret5 = to<RET_5>(L, -3);
				ret6 = to<RET_6>(L, -2);
				ret7 = to<RET_7>(L, -1);
				lua_pop(L, 8); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn7Param8

/** callStaticReturn7Param9 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
callStatic7Param9(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 9);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -7);
			ret2 = to<RET_2>(L, -6);
			ret3 = to<RET_3>(L, -5);
			ret4 = to<RET_4>(L, -4);
			ret5 = to<RET_5>(L, -3);
			ret6 = to<RET_6>(L, -2);
			ret7 = to<RET_7>(L, -1);
			lua_pop(L, 8);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn7Param9

/** hybridStaticReturn7Param9 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
hybridStatic7Param9(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 9);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -7);
			ret2 = to<RET_2>(L, -6);
			ret3 = to<RET_3>(L, -5);
			ret4 = to<RET_4>(L, -4);
			ret5 = to<RET_5>(L, -3);
			ret6 = to<RET_6>(L, -2);
			ret7 = to<RET_7>(L, -1);
			lua_pop(L, 8);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn7Param9

/** pcallStaticReturn7Param9 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
pcallStatic7Param9(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 9))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -7);
				ret2 = to<RET_2>(L, -6);
				ret3 = to<RET_3>(L, -5);
				ret4 = to<RET_4>(L, -4);
				ret5 = to<RET_5>(L, -3);
				ret6 = to<RET_6>(L, -2);
				ret7 = to<RET_7>(L, -1);
				lua_pop(L, 8); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn7Param9

/** phybridStaticReturn7Param9 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
phybridStatic7Param9(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 9))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -7);
				ret2 = to<RET_2>(L, -6);
				ret3 = to<RET_3>(L, -5);
				ret4 = to<RET_4>(L, -4);
				ret5 = to<RET_5>(L, -3);
				ret6 = to<RET_6>(L, -2);
				ret7 = to<RET_7>(L, -1);
				lua_pop(L, 8); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn7Param9

/** callStaticReturn7Param10 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
callStatic7Param10(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, ARG_10 arg10, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			push(L, arg10);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 10);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -7);
			ret2 = to<RET_2>(L, -6);
			ret3 = to<RET_3>(L, -5);
			ret4 = to<RET_4>(L, -4);
			ret5 = to<RET_5>(L, -3);
			ret6 = to<RET_6>(L, -2);
			ret7 = to<RET_7>(L, -1);
			lua_pop(L, 8);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn7Param10

/** hybridStaticReturn7Param10 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
hybridStatic7Param10(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, ARG_10 arg10, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			push(L, arg10);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 10);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -7);
			ret2 = to<RET_2>(L, -6);
			ret3 = to<RET_3>(L, -5);
			ret4 = to<RET_4>(L, -4);
			ret5 = to<RET_5>(L, -3);
			ret6 = to<RET_6>(L, -2);
			ret7 = to<RET_7>(L, -1);
			lua_pop(L, 8);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn7Param10

/** pcallStaticReturn7Param10 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
pcallStatic7Param10(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, ARG_10 arg10, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			push(L, arg10);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 10))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -7);
				ret2 = to<RET_2>(L, -6);
				ret3 = to<RET_3>(L, -5);
				ret4 = to<RET_4>(L, -4);
				ret5 = to<RET_5>(L, -3);
				ret6 = to<RET_6>(L, -2);
				ret7 = to<RET_7>(L, -1);
				lua_pop(L, 8); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn7Param10

/** phybridStaticReturn7Param10 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
phybridStatic7Param10(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, ARG_10 arg10, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			push(L, arg10);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 10))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -7);
				ret2 = to<RET_2>(L, -6);
				ret3 = to<RET_3>(L, -5);
				ret4 = to<RET_4>(L, -4);
				ret5 = to<RET_5>(L, -3);
				ret6 = to<RET_6>(L, -2);
				ret7 = to<RET_7>(L, -1);
				lua_pop(L, 8); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn7Param10

/** callStaticReturn8Param0 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&) >
inline ScriptToNativeCallResult
callStatic8Param0(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			/*s: module scriptFunction (arguments) */
			lua_call(L, 0);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -8);
			ret2 = to<RET_2>(L, -7);
			ret3 = to<RET_3>(L, -6);
			ret4 = to<RET_4>(L, -5);
			ret5 = to<RET_5>(L, -4);
			ret6 = to<RET_6>(L, -3);
			ret7 = to<RET_7>(L, -2);
			ret8 = to<RET_8>(L, -1);
			lua_pop(L, 9);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn8Param0

/** hybridStaticReturn8Param0 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&) >
inline ScriptToNativeCallResult
hybridStatic8Param0(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			/*s: module scriptFunction (arguments) */
			lua_call(L, 0);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -8);
			ret2 = to<RET_2>(L, -7);
			ret3 = to<RET_3>(L, -6);
			ret4 = to<RET_4>(L, -5);
			ret5 = to<RET_5>(L, -4);
			ret6 = to<RET_6>(L, -3);
			ret7 = to<RET_7>(L, -2);
			ret8 = to<RET_8>(L, -1);
			lua_pop(L, 9);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn8Param0

/** pcallStaticReturn8Param0 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&) >
inline ScriptToNativeCallResult
pcallStatic8Param0(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 0))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -8);
				ret2 = to<RET_2>(L, -7);
				ret3 = to<RET_3>(L, -6);
				ret4 = to<RET_4>(L, -5);
				ret5 = to<RET_5>(L, -4);
				ret6 = to<RET_6>(L, -3);
				ret7 = to<RET_7>(L, -2);
				ret8 = to<RET_8>(L, -1);
				lua_pop(L, 9); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn8Param0

/** phybridStaticReturn8Param0 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&) >
inline ScriptToNativeCallResult
phybridStatic8Param0(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 0))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -8);
				ret2 = to<RET_2>(L, -7);
				ret3 = to<RET_3>(L, -6);
				ret4 = to<RET_4>(L, -5);
				ret5 = to<RET_5>(L, -4);
				ret6 = to<RET_6>(L, -3);
				ret7 = to<RET_7>(L, -2);
				ret8 = to<RET_8>(L, -1);
				lua_pop(L, 9); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn8Param0

/** callStaticReturn8Param1 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1) >
inline ScriptToNativeCallResult
callStatic8Param1(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, ARG_1 arg1, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 1);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -8);
			ret2 = to<RET_2>(L, -7);
			ret3 = to<RET_3>(L, -6);
			ret4 = to<RET_4>(L, -5);
			ret5 = to<RET_5>(L, -4);
			ret6 = to<RET_6>(L, -3);
			ret7 = to<RET_7>(L, -2);
			ret8 = to<RET_8>(L, -1);
			lua_pop(L, 9);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn8Param1

/** hybridStaticReturn8Param1 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1) >
inline ScriptToNativeCallResult
hybridStatic8Param1(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, ARG_1 arg1, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 1);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -8);
			ret2 = to<RET_2>(L, -7);
			ret3 = to<RET_3>(L, -6);
			ret4 = to<RET_4>(L, -5);
			ret5 = to<RET_5>(L, -4);
			ret6 = to<RET_6>(L, -3);
			ret7 = to<RET_7>(L, -2);
			ret8 = to<RET_8>(L, -1);
			lua_pop(L, 9);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn8Param1

/** pcallStaticReturn8Param1 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1) >
inline ScriptToNativeCallResult
pcallStatic8Param1(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, ARG_1 arg1, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 1))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -8);
				ret2 = to<RET_2>(L, -7);
				ret3 = to<RET_3>(L, -6);
				ret4 = to<RET_4>(L, -5);
				ret5 = to<RET_5>(L, -4);
				ret6 = to<RET_6>(L, -3);
				ret7 = to<RET_7>(L, -2);
				ret8 = to<RET_8>(L, -1);
				lua_pop(L, 9); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn8Param1

/** phybridStaticReturn8Param1 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1) >
inline ScriptToNativeCallResult
phybridStatic8Param1(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, ARG_1 arg1, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 1))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -8);
				ret2 = to<RET_2>(L, -7);
				ret3 = to<RET_3>(L, -6);
				ret4 = to<RET_4>(L, -5);
				ret5 = to<RET_5>(L, -4);
				ret6 = to<RET_6>(L, -3);
				ret7 = to<RET_7>(L, -2);
				ret8 = to<RET_8>(L, -1);
				lua_pop(L, 9); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn8Param1

/** callStaticReturn8Param2 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2) >
inline ScriptToNativeCallResult
callStatic8Param2(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, ARG_1 arg1, ARG_2 arg2, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 2);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -8);
			ret2 = to<RET_2>(L, -7);
			ret3 = to<RET_3>(L, -6);
			ret4 = to<RET_4>(L, -5);
			ret5 = to<RET_5>(L, -4);
			ret6 = to<RET_6>(L, -3);
			ret7 = to<RET_7>(L, -2);
			ret8 = to<RET_8>(L, -1);
			lua_pop(L, 9);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn8Param2

/** hybridStaticReturn8Param2 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2) >
inline ScriptToNativeCallResult
hybridStatic8Param2(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, ARG_1 arg1, ARG_2 arg2, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 2);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -8);
			ret2 = to<RET_2>(L, -7);
			ret3 = to<RET_3>(L, -6);
			ret4 = to<RET_4>(L, -5);
			ret5 = to<RET_5>(L, -4);
			ret6 = to<RET_6>(L, -3);
			ret7 = to<RET_7>(L, -2);
			ret8 = to<RET_8>(L, -1);
			lua_pop(L, 9);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn8Param2

/** pcallStaticReturn8Param2 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2) >
inline ScriptToNativeCallResult
pcallStatic8Param2(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, ARG_1 arg1, ARG_2 arg2, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 2))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -8);
				ret2 = to<RET_2>(L, -7);
				ret3 = to<RET_3>(L, -6);
				ret4 = to<RET_4>(L, -5);
				ret5 = to<RET_5>(L, -4);
				ret6 = to<RET_6>(L, -3);
				ret7 = to<RET_7>(L, -2);
				ret8 = to<RET_8>(L, -1);
				lua_pop(L, 9); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn8Param2

/** phybridStaticReturn8Param2 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2) >
inline ScriptToNativeCallResult
phybridStatic8Param2(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, ARG_1 arg1, ARG_2 arg2, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 2))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -8);
				ret2 = to<RET_2>(L, -7);
				ret3 = to<RET_3>(L, -6);
				ret4 = to<RET_4>(L, -5);
				ret5 = to<RET_5>(L, -4);
				ret6 = to<RET_6>(L, -3);
				ret7 = to<RET_7>(L, -2);
				ret8 = to<RET_8>(L, -1);
				lua_pop(L, 9); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn8Param2

/** callStaticReturn8Param3 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
callStatic8Param3(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 3);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -8);
			ret2 = to<RET_2>(L, -7);
			ret3 = to<RET_3>(L, -6);
			ret4 = to<RET_4>(L, -5);
			ret5 = to<RET_5>(L, -4);
			ret6 = to<RET_6>(L, -3);
			ret7 = to<RET_7>(L, -2);
			ret8 = to<RET_8>(L, -1);
			lua_pop(L, 9);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn8Param3

/** hybridStaticReturn8Param3 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
hybridStatic8Param3(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 3);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -8);
			ret2 = to<RET_2>(L, -7);
			ret3 = to<RET_3>(L, -6);
			ret4 = to<RET_4>(L, -5);
			ret5 = to<RET_5>(L, -4);
			ret6 = to<RET_6>(L, -3);
			ret7 = to<RET_7>(L, -2);
			ret8 = to<RET_8>(L, -1);
			lua_pop(L, 9);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn8Param3

/** pcallStaticReturn8Param3 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
pcallStatic8Param3(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 3))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -8);
				ret2 = to<RET_2>(L, -7);
				ret3 = to<RET_3>(L, -6);
				ret4 = to<RET_4>(L, -5);
				ret5 = to<RET_5>(L, -4);
				ret6 = to<RET_6>(L, -3);
				ret7 = to<RET_7>(L, -2);
				ret8 = to<RET_8>(L, -1);
				lua_pop(L, 9); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn8Param3

/** phybridStaticReturn8Param3 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
phybridStatic8Param3(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 3))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -8);
				ret2 = to<RET_2>(L, -7);
				ret3 = to<RET_3>(L, -6);
				ret4 = to<RET_4>(L, -5);
				ret5 = to<RET_5>(L, -4);
				ret6 = to<RET_6>(L, -3);
				ret7 = to<RET_7>(L, -2);
				ret8 = to<RET_8>(L, -1);
				lua_pop(L, 9); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn8Param3

/** callStaticReturn8Param4 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
callStatic8Param4(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 4);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -8);
			ret2 = to<RET_2>(L, -7);
			ret3 = to<RET_3>(L, -6);
			ret4 = to<RET_4>(L, -5);
			ret5 = to<RET_5>(L, -4);
			ret6 = to<RET_6>(L, -3);
			ret7 = to<RET_7>(L, -2);
			ret8 = to<RET_8>(L, -1);
			lua_pop(L, 9);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn8Param4

/** hybridStaticReturn8Param4 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
hybridStatic8Param4(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 4);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -8);
			ret2 = to<RET_2>(L, -7);
			ret3 = to<RET_3>(L, -6);
			ret4 = to<RET_4>(L, -5);
			ret5 = to<RET_5>(L, -4);
			ret6 = to<RET_6>(L, -3);
			ret7 = to<RET_7>(L, -2);
			ret8 = to<RET_8>(L, -1);
			lua_pop(L, 9);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn8Param4

/** pcallStaticReturn8Param4 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
pcallStatic8Param4(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 4))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -8);
				ret2 = to<RET_2>(L, -7);
				ret3 = to<RET_3>(L, -6);
				ret4 = to<RET_4>(L, -5);
				ret5 = to<RET_5>(L, -4);
				ret6 = to<RET_6>(L, -3);
				ret7 = to<RET_7>(L, -2);
				ret8 = to<RET_8>(L, -1);
				lua_pop(L, 9); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn8Param4

/** phybridStaticReturn8Param4 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
phybridStatic8Param4(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 4))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -8);
				ret2 = to<RET_2>(L, -7);
				ret3 = to<RET_3>(L, -6);
				ret4 = to<RET_4>(L, -5);
				ret5 = to<RET_5>(L, -4);
				ret6 = to<RET_6>(L, -3);
				ret7 = to<RET_7>(L, -2);
				ret8 = to<RET_8>(L, -1);
				lua_pop(L, 9); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn8Param4

/** callStaticReturn8Param5 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
callStatic8Param5(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 5);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -8);
			ret2 = to<RET_2>(L, -7);
			ret3 = to<RET_3>(L, -6);
			ret4 = to<RET_4>(L, -5);
			ret5 = to<RET_5>(L, -4);
			ret6 = to<RET_6>(L, -3);
			ret7 = to<RET_7>(L, -2);
			ret8 = to<RET_8>(L, -1);
			lua_pop(L, 9);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn8Param5

/** hybridStaticReturn8Param5 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
hybridStatic8Param5(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 5);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -8);
			ret2 = to<RET_2>(L, -7);
			ret3 = to<RET_3>(L, -6);
			ret4 = to<RET_4>(L, -5);
			ret5 = to<RET_5>(L, -4);
			ret6 = to<RET_6>(L, -3);
			ret7 = to<RET_7>(L, -2);
			ret8 = to<RET_8>(L, -1);
			lua_pop(L, 9);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4, arg5);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4, arg5);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn8Param5

/** pcallStaticReturn8Param5 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
pcallStatic8Param5(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 5))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -8);
				ret2 = to<RET_2>(L, -7);
				ret3 = to<RET_3>(L, -6);
				ret4 = to<RET_4>(L, -5);
				ret5 = to<RET_5>(L, -4);
				ret6 = to<RET_6>(L, -3);
				ret7 = to<RET_7>(L, -2);
				ret8 = to<RET_8>(L, -1);
				lua_pop(L, 9); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn8Param5

/** phybridStaticReturn8Param5 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
phybridStatic8Param5(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 5))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -8);
				ret2 = to<RET_2>(L, -7);
				ret3 = to<RET_3>(L, -6);
				ret4 = to<RET_4>(L, -5);
				ret5 = to<RET_5>(L, -4);
				ret6 = to<RET_6>(L, -3);
				ret7 = to<RET_7>(L, -2);
				ret8 = to<RET_8>(L, -1);
				lua_pop(L, 9); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4, arg5);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4, arg5);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn8Param5

/** callStaticReturn8Param6 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
callStatic8Param6(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 6);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -8);
			ret2 = to<RET_2>(L, -7);
			ret3 = to<RET_3>(L, -6);
			ret4 = to<RET_4>(L, -5);
			ret5 = to<RET_5>(L, -4);
			ret6 = to<RET_6>(L, -3);
			ret7 = to<RET_7>(L, -2);
			ret8 = to<RET_8>(L, -1);
			lua_pop(L, 9);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn8Param6

/** hybridStaticReturn8Param6 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
hybridStatic8Param6(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 6);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -8);
			ret2 = to<RET_2>(L, -7);
			ret3 = to<RET_3>(L, -6);
			ret4 = to<RET_4>(L, -5);
			ret5 = to<RET_5>(L, -4);
			ret6 = to<RET_6>(L, -3);
			ret7 = to<RET_7>(L, -2);
			ret8 = to<RET_8>(L, -1);
			lua_pop(L, 9);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4, arg5, arg6);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn8Param6

/** pcallStaticReturn8Param6 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
pcallStatic8Param6(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 6))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -8);
				ret2 = to<RET_2>(L, -7);
				ret3 = to<RET_3>(L, -6);
				ret4 = to<RET_4>(L, -5);
				ret5 = to<RET_5>(L, -4);
				ret6 = to<RET_6>(L, -3);
				ret7 = to<RET_7>(L, -2);
				ret8 = to<RET_8>(L, -1);
				lua_pop(L, 9); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn8Param6

/** phybridStaticReturn8Param6 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
phybridStatic8Param6(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 6))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -8);
				ret2 = to<RET_2>(L, -7);
				ret3 = to<RET_3>(L, -6);
				ret4 = to<RET_4>(L, -5);
				ret5 = to<RET_5>(L, -4);
				ret6 = to<RET_6>(L, -3);
				ret7 = to<RET_7>(L, -2);
				ret8 = to<RET_8>(L, -1);
				lua_pop(L, 9); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4, arg5, arg6);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn8Param6

/** callStaticReturn8Param7 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
callStatic8Param7(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 7);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -8);
			ret2 = to<RET_2>(L, -7);
			ret3 = to<RET_3>(L, -6);
			ret4 = to<RET_4>(L, -5);
			ret5 = to<RET_5>(L, -4);
			ret6 = to<RET_6>(L, -3);
			ret7 = to<RET_7>(L, -2);
			ret8 = to<RET_8>(L, -1);
			lua_pop(L, 9);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn8Param7

/** hybridStaticReturn8Param7 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
hybridStatic8Param7(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 7);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -8);
			ret2 = to<RET_2>(L, -7);
			ret3 = to<RET_3>(L, -6);
			ret4 = to<RET_4>(L, -5);
			ret5 = to<RET_5>(L, -4);
			ret6 = to<RET_6>(L, -3);
			ret7 = to<RET_7>(L, -2);
			ret8 = to<RET_8>(L, -1);
			lua_pop(L, 9);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn8Param7

/** pcallStaticReturn8Param7 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
pcallStatic8Param7(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 7))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -8);
				ret2 = to<RET_2>(L, -7);
				ret3 = to<RET_3>(L, -6);
				ret4 = to<RET_4>(L, -5);
				ret5 = to<RET_5>(L, -4);
				ret6 = to<RET_6>(L, -3);
				ret7 = to<RET_7>(L, -2);
				ret8 = to<RET_8>(L, -1);
				lua_pop(L, 9); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn8Param7

/** phybridStaticReturn8Param7 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
phybridStatic8Param7(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 7))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -8);
				ret2 = to<RET_2>(L, -7);
				ret3 = to<RET_3>(L, -6);
				ret4 = to<RET_4>(L, -5);
				ret5 = to<RET_5>(L, -4);
				ret6 = to<RET_6>(L, -3);
				ret7 = to<RET_7>(L, -2);
				ret8 = to<RET_8>(L, -1);
				lua_pop(L, 9); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn8Param7

/** callStaticReturn8Param8 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
callStatic8Param8(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 8);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -8);
			ret2 = to<RET_2>(L, -7);
			ret3 = to<RET_3>(L, -6);
			ret4 = to<RET_4>(L, -5);
			ret5 = to<RET_5>(L, -4);
			ret6 = to<RET_6>(L, -3);
			ret7 = to<RET_7>(L, -2);
			ret8 = to<RET_8>(L, -1);
			lua_pop(L, 9);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn8Param8

/** hybridStaticReturn8Param8 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
hybridStatic8Param8(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 8);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -8);
			ret2 = to<RET_2>(L, -7);
			ret3 = to<RET_3>(L, -6);
			ret4 = to<RET_4>(L, -5);
			ret5 = to<RET_5>(L, -4);
			ret6 = to<RET_6>(L, -3);
			ret7 = to<RET_7>(L, -2);
			ret8 = to<RET_8>(L, -1);
			lua_pop(L, 9);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn8Param8

/** pcallStaticReturn8Param8 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
pcallStatic8Param8(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 8))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -8);
				ret2 = to<RET_2>(L, -7);
				ret3 = to<RET_3>(L, -6);
				ret4 = to<RET_4>(L, -5);
				ret5 = to<RET_5>(L, -4);
				ret6 = to<RET_6>(L, -3);
				ret7 = to<RET_7>(L, -2);
				ret8 = to<RET_8>(L, -1);
				lua_pop(L, 9); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn8Param8

/** phybridStaticReturn8Param8 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
phybridStatic8Param8(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 8))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -8);
				ret2 = to<RET_2>(L, -7);
				ret3 = to<RET_3>(L, -6);
				ret4 = to<RET_4>(L, -5);
				ret5 = to<RET_5>(L, -4);
				ret6 = to<RET_6>(L, -3);
				ret7 = to<RET_7>(L, -2);
				ret8 = to<RET_8>(L, -1);
				lua_pop(L, 9); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn8Param8

/** callStaticReturn8Param9 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
callStatic8Param9(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 9);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -8);
			ret2 = to<RET_2>(L, -7);
			ret3 = to<RET_3>(L, -6);
			ret4 = to<RET_4>(L, -5);
			ret5 = to<RET_5>(L, -4);
			ret6 = to<RET_6>(L, -3);
			ret7 = to<RET_7>(L, -2);
			ret8 = to<RET_8>(L, -1);
			lua_pop(L, 9);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn8Param9

/** hybridStaticReturn8Param9 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
hybridStatic8Param9(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 9);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -8);
			ret2 = to<RET_2>(L, -7);
			ret3 = to<RET_3>(L, -6);
			ret4 = to<RET_4>(L, -5);
			ret5 = to<RET_5>(L, -4);
			ret6 = to<RET_6>(L, -3);
			ret7 = to<RET_7>(L, -2);
			ret8 = to<RET_8>(L, -1);
			lua_pop(L, 9);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn8Param9

/** pcallStaticReturn8Param9 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
pcallStatic8Param9(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 9))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -8);
				ret2 = to<RET_2>(L, -7);
				ret3 = to<RET_3>(L, -6);
				ret4 = to<RET_4>(L, -5);
				ret5 = to<RET_5>(L, -4);
				ret6 = to<RET_6>(L, -3);
				ret7 = to<RET_7>(L, -2);
				ret8 = to<RET_8>(L, -1);
				lua_pop(L, 9); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn8Param9

/** phybridStaticReturn8Param9 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
phybridStatic8Param9(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 9))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -8);
				ret2 = to<RET_2>(L, -7);
				ret3 = to<RET_3>(L, -6);
				ret4 = to<RET_4>(L, -5);
				ret5 = to<RET_5>(L, -4);
				ret6 = to<RET_6>(L, -3);
				ret7 = to<RET_7>(L, -2);
				ret8 = to<RET_8>(L, -1);
				lua_pop(L, 9); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn8Param9

/** callStaticReturn8Param10 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
callStatic8Param10(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, ARG_10 arg10, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			push(L, arg10);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 10);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -8);
			ret2 = to<RET_2>(L, -7);
			ret3 = to<RET_3>(L, -6);
			ret4 = to<RET_4>(L, -5);
			ret5 = to<RET_5>(L, -4);
			ret6 = to<RET_6>(L, -3);
			ret7 = to<RET_7>(L, -2);
			ret8 = to<RET_8>(L, -1);
			lua_pop(L, 9);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn8Param10

/** hybridStaticReturn8Param10 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
hybridStatic8Param10(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, ARG_10 arg10, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			push(L, arg10);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 10);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -8);
			ret2 = to<RET_2>(L, -7);
			ret3 = to<RET_3>(L, -6);
			ret4 = to<RET_4>(L, -5);
			ret5 = to<RET_5>(L, -4);
			ret6 = to<RET_6>(L, -3);
			ret7 = to<RET_7>(L, -2);
			ret8 = to<RET_8>(L, -1);
			lua_pop(L, 9);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn8Param10

/** pcallStaticReturn8Param10 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
pcallStatic8Param10(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, ARG_10 arg10, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			push(L, arg10);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 10))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -8);
				ret2 = to<RET_2>(L, -7);
				ret3 = to<RET_3>(L, -6);
				ret4 = to<RET_4>(L, -5);
				ret5 = to<RET_5>(L, -4);
				ret6 = to<RET_6>(L, -3);
				ret7 = to<RET_7>(L, -2);
				ret8 = to<RET_8>(L, -1);
				lua_pop(L, 9); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn8Param10

/** phybridStaticReturn8Param10 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
phybridStatic8Param10(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, ARG_10 arg10, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			push(L, arg10);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 10))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -8);
				ret2 = to<RET_2>(L, -7);
				ret3 = to<RET_3>(L, -6);
				ret4 = to<RET_4>(L, -5);
				ret5 = to<RET_5>(L, -4);
				ret6 = to<RET_6>(L, -3);
				ret7 = to<RET_7>(L, -2);
				ret8 = to<RET_8>(L, -1);
				lua_pop(L, 9); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn8Param10

/** callStaticReturn9Param0 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&) >
inline ScriptToNativeCallResult
callStatic9Param0(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			/*s: module scriptFunction (arguments) */
			lua_call(L, 0);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -9);
			ret2 = to<RET_2>(L, -8);
			ret3 = to<RET_3>(L, -7);
			ret4 = to<RET_4>(L, -6);
			ret5 = to<RET_5>(L, -5);
			ret6 = to<RET_6>(L, -4);
			ret7 = to<RET_7>(L, -3);
			ret8 = to<RET_8>(L, -2);
			ret9 = to<RET_9>(L, -1);
			lua_pop(L, 10);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn9Param0

/** hybridStaticReturn9Param0 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&) >
inline ScriptToNativeCallResult
hybridStatic9Param0(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			/*s: module scriptFunction (arguments) */
			lua_call(L, 0);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -9);
			ret2 = to<RET_2>(L, -8);
			ret3 = to<RET_3>(L, -7);
			ret4 = to<RET_4>(L, -6);
			ret5 = to<RET_5>(L, -5);
			ret6 = to<RET_6>(L, -4);
			ret7 = to<RET_7>(L, -3);
			ret8 = to<RET_8>(L, -2);
			ret9 = to<RET_9>(L, -1);
			lua_pop(L, 10);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn9Param0

/** pcallStaticReturn9Param0 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&) >
inline ScriptToNativeCallResult
pcallStatic9Param0(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 0))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -9);
				ret2 = to<RET_2>(L, -8);
				ret3 = to<RET_3>(L, -7);
				ret4 = to<RET_4>(L, -6);
				ret5 = to<RET_5>(L, -5);
				ret6 = to<RET_6>(L, -4);
				ret7 = to<RET_7>(L, -3);
				ret8 = to<RET_8>(L, -2);
				ret9 = to<RET_9>(L, -1);
				lua_pop(L, 10); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn9Param0

/** phybridStaticReturn9Param0 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&) >
inline ScriptToNativeCallResult
phybridStatic9Param0(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 0))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -9);
				ret2 = to<RET_2>(L, -8);
				ret3 = to<RET_3>(L, -7);
				ret4 = to<RET_4>(L, -6);
				ret5 = to<RET_5>(L, -5);
				ret6 = to<RET_6>(L, -4);
				ret7 = to<RET_7>(L, -3);
				ret8 = to<RET_8>(L, -2);
				ret9 = to<RET_9>(L, -1);
				lua_pop(L, 10); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn9Param0

/** callStaticReturn9Param1 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1) >
inline ScriptToNativeCallResult
callStatic9Param1(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, ARG_1 arg1, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 1);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -9);
			ret2 = to<RET_2>(L, -8);
			ret3 = to<RET_3>(L, -7);
			ret4 = to<RET_4>(L, -6);
			ret5 = to<RET_5>(L, -5);
			ret6 = to<RET_6>(L, -4);
			ret7 = to<RET_7>(L, -3);
			ret8 = to<RET_8>(L, -2);
			ret9 = to<RET_9>(L, -1);
			lua_pop(L, 10);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn9Param1

/** hybridStaticReturn9Param1 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1) >
inline ScriptToNativeCallResult
hybridStatic9Param1(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, ARG_1 arg1, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 1);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -9);
			ret2 = to<RET_2>(L, -8);
			ret3 = to<RET_3>(L, -7);
			ret4 = to<RET_4>(L, -6);
			ret5 = to<RET_5>(L, -5);
			ret6 = to<RET_6>(L, -4);
			ret7 = to<RET_7>(L, -3);
			ret8 = to<RET_8>(L, -2);
			ret9 = to<RET_9>(L, -1);
			lua_pop(L, 10);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn9Param1

/** pcallStaticReturn9Param1 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1) >
inline ScriptToNativeCallResult
pcallStatic9Param1(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, ARG_1 arg1, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 1))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -9);
				ret2 = to<RET_2>(L, -8);
				ret3 = to<RET_3>(L, -7);
				ret4 = to<RET_4>(L, -6);
				ret5 = to<RET_5>(L, -5);
				ret6 = to<RET_6>(L, -4);
				ret7 = to<RET_7>(L, -3);
				ret8 = to<RET_8>(L, -2);
				ret9 = to<RET_9>(L, -1);
				lua_pop(L, 10); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn9Param1

/** phybridStaticReturn9Param1 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1) >
inline ScriptToNativeCallResult
phybridStatic9Param1(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, ARG_1 arg1, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 1))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -9);
				ret2 = to<RET_2>(L, -8);
				ret3 = to<RET_3>(L, -7);
				ret4 = to<RET_4>(L, -6);
				ret5 = to<RET_5>(L, -5);
				ret6 = to<RET_6>(L, -4);
				ret7 = to<RET_7>(L, -3);
				ret8 = to<RET_8>(L, -2);
				ret9 = to<RET_9>(L, -1);
				lua_pop(L, 10); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn9Param1

/** callStaticReturn9Param2 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2) >
inline ScriptToNativeCallResult
callStatic9Param2(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, ARG_1 arg1, ARG_2 arg2, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 2);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -9);
			ret2 = to<RET_2>(L, -8);
			ret3 = to<RET_3>(L, -7);
			ret4 = to<RET_4>(L, -6);
			ret5 = to<RET_5>(L, -5);
			ret6 = to<RET_6>(L, -4);
			ret7 = to<RET_7>(L, -3);
			ret8 = to<RET_8>(L, -2);
			ret9 = to<RET_9>(L, -1);
			lua_pop(L, 10);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn9Param2

/** hybridStaticReturn9Param2 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2) >
inline ScriptToNativeCallResult
hybridStatic9Param2(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, ARG_1 arg1, ARG_2 arg2, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 2);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -9);
			ret2 = to<RET_2>(L, -8);
			ret3 = to<RET_3>(L, -7);
			ret4 = to<RET_4>(L, -6);
			ret5 = to<RET_5>(L, -5);
			ret6 = to<RET_6>(L, -4);
			ret7 = to<RET_7>(L, -3);
			ret8 = to<RET_8>(L, -2);
			ret9 = to<RET_9>(L, -1);
			lua_pop(L, 10);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn9Param2

/** pcallStaticReturn9Param2 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2) >
inline ScriptToNativeCallResult
pcallStatic9Param2(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, ARG_1 arg1, ARG_2 arg2, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 2))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -9);
				ret2 = to<RET_2>(L, -8);
				ret3 = to<RET_3>(L, -7);
				ret4 = to<RET_4>(L, -6);
				ret5 = to<RET_5>(L, -5);
				ret6 = to<RET_6>(L, -4);
				ret7 = to<RET_7>(L, -3);
				ret8 = to<RET_8>(L, -2);
				ret9 = to<RET_9>(L, -1);
				lua_pop(L, 10); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn9Param2

/** phybridStaticReturn9Param2 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2) >
inline ScriptToNativeCallResult
phybridStatic9Param2(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, ARG_1 arg1, ARG_2 arg2, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 2))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -9);
				ret2 = to<RET_2>(L, -8);
				ret3 = to<RET_3>(L, -7);
				ret4 = to<RET_4>(L, -6);
				ret5 = to<RET_5>(L, -5);
				ret6 = to<RET_6>(L, -4);
				ret7 = to<RET_7>(L, -3);
				ret8 = to<RET_8>(L, -2);
				ret9 = to<RET_9>(L, -1);
				lua_pop(L, 10); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn9Param2

/** callStaticReturn9Param3 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
callStatic9Param3(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 3);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -9);
			ret2 = to<RET_2>(L, -8);
			ret3 = to<RET_3>(L, -7);
			ret4 = to<RET_4>(L, -6);
			ret5 = to<RET_5>(L, -5);
			ret6 = to<RET_6>(L, -4);
			ret7 = to<RET_7>(L, -3);
			ret8 = to<RET_8>(L, -2);
			ret9 = to<RET_9>(L, -1);
			lua_pop(L, 10);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn9Param3

/** hybridStaticReturn9Param3 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
hybridStatic9Param3(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 3);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -9);
			ret2 = to<RET_2>(L, -8);
			ret3 = to<RET_3>(L, -7);
			ret4 = to<RET_4>(L, -6);
			ret5 = to<RET_5>(L, -5);
			ret6 = to<RET_6>(L, -4);
			ret7 = to<RET_7>(L, -3);
			ret8 = to<RET_8>(L, -2);
			ret9 = to<RET_9>(L, -1);
			lua_pop(L, 10);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn9Param3

/** pcallStaticReturn9Param3 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
pcallStatic9Param3(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 3))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -9);
				ret2 = to<RET_2>(L, -8);
				ret3 = to<RET_3>(L, -7);
				ret4 = to<RET_4>(L, -6);
				ret5 = to<RET_5>(L, -5);
				ret6 = to<RET_6>(L, -4);
				ret7 = to<RET_7>(L, -3);
				ret8 = to<RET_8>(L, -2);
				ret9 = to<RET_9>(L, -1);
				lua_pop(L, 10); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn9Param3

/** phybridStaticReturn9Param3 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
phybridStatic9Param3(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 3))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -9);
				ret2 = to<RET_2>(L, -8);
				ret3 = to<RET_3>(L, -7);
				ret4 = to<RET_4>(L, -6);
				ret5 = to<RET_5>(L, -5);
				ret6 = to<RET_6>(L, -4);
				ret7 = to<RET_7>(L, -3);
				ret8 = to<RET_8>(L, -2);
				ret9 = to<RET_9>(L, -1);
				lua_pop(L, 10); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn9Param3

/** callStaticReturn9Param4 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
callStatic9Param4(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 4);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -9);
			ret2 = to<RET_2>(L, -8);
			ret3 = to<RET_3>(L, -7);
			ret4 = to<RET_4>(L, -6);
			ret5 = to<RET_5>(L, -5);
			ret6 = to<RET_6>(L, -4);
			ret7 = to<RET_7>(L, -3);
			ret8 = to<RET_8>(L, -2);
			ret9 = to<RET_9>(L, -1);
			lua_pop(L, 10);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn9Param4

/** hybridStaticReturn9Param4 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
hybridStatic9Param4(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 4);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -9);
			ret2 = to<RET_2>(L, -8);
			ret3 = to<RET_3>(L, -7);
			ret4 = to<RET_4>(L, -6);
			ret5 = to<RET_5>(L, -5);
			ret6 = to<RET_6>(L, -4);
			ret7 = to<RET_7>(L, -3);
			ret8 = to<RET_8>(L, -2);
			ret9 = to<RET_9>(L, -1);
			lua_pop(L, 10);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn9Param4

/** pcallStaticReturn9Param4 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
pcallStatic9Param4(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 4))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -9);
				ret2 = to<RET_2>(L, -8);
				ret3 = to<RET_3>(L, -7);
				ret4 = to<RET_4>(L, -6);
				ret5 = to<RET_5>(L, -5);
				ret6 = to<RET_6>(L, -4);
				ret7 = to<RET_7>(L, -3);
				ret8 = to<RET_8>(L, -2);
				ret9 = to<RET_9>(L, -1);
				lua_pop(L, 10); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn9Param4

/** phybridStaticReturn9Param4 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
phybridStatic9Param4(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 4))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -9);
				ret2 = to<RET_2>(L, -8);
				ret3 = to<RET_3>(L, -7);
				ret4 = to<RET_4>(L, -6);
				ret5 = to<RET_5>(L, -5);
				ret6 = to<RET_6>(L, -4);
				ret7 = to<RET_7>(L, -3);
				ret8 = to<RET_8>(L, -2);
				ret9 = to<RET_9>(L, -1);
				lua_pop(L, 10); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn9Param4

/** callStaticReturn9Param5 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
callStatic9Param5(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 5);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -9);
			ret2 = to<RET_2>(L, -8);
			ret3 = to<RET_3>(L, -7);
			ret4 = to<RET_4>(L, -6);
			ret5 = to<RET_5>(L, -5);
			ret6 = to<RET_6>(L, -4);
			ret7 = to<RET_7>(L, -3);
			ret8 = to<RET_8>(L, -2);
			ret9 = to<RET_9>(L, -1);
			lua_pop(L, 10);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn9Param5

/** hybridStaticReturn9Param5 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
hybridStatic9Param5(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 5);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -9);
			ret2 = to<RET_2>(L, -8);
			ret3 = to<RET_3>(L, -7);
			ret4 = to<RET_4>(L, -6);
			ret5 = to<RET_5>(L, -5);
			ret6 = to<RET_6>(L, -4);
			ret7 = to<RET_7>(L, -3);
			ret8 = to<RET_8>(L, -2);
			ret9 = to<RET_9>(L, -1);
			lua_pop(L, 10);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4, arg5);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4, arg5);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn9Param5

/** pcallStaticReturn9Param5 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
pcallStatic9Param5(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 5))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -9);
				ret2 = to<RET_2>(L, -8);
				ret3 = to<RET_3>(L, -7);
				ret4 = to<RET_4>(L, -6);
				ret5 = to<RET_5>(L, -5);
				ret6 = to<RET_6>(L, -4);
				ret7 = to<RET_7>(L, -3);
				ret8 = to<RET_8>(L, -2);
				ret9 = to<RET_9>(L, -1);
				lua_pop(L, 10); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn9Param5

/** phybridStaticReturn9Param5 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
phybridStatic9Param5(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 5))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -9);
				ret2 = to<RET_2>(L, -8);
				ret3 = to<RET_3>(L, -7);
				ret4 = to<RET_4>(L, -6);
				ret5 = to<RET_5>(L, -5);
				ret6 = to<RET_6>(L, -4);
				ret7 = to<RET_7>(L, -3);
				ret8 = to<RET_8>(L, -2);
				ret9 = to<RET_9>(L, -1);
				lua_pop(L, 10); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4, arg5);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4, arg5);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn9Param5

/** callStaticReturn9Param6 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
callStatic9Param6(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 6);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -9);
			ret2 = to<RET_2>(L, -8);
			ret3 = to<RET_3>(L, -7);
			ret4 = to<RET_4>(L, -6);
			ret5 = to<RET_5>(L, -5);
			ret6 = to<RET_6>(L, -4);
			ret7 = to<RET_7>(L, -3);
			ret8 = to<RET_8>(L, -2);
			ret9 = to<RET_9>(L, -1);
			lua_pop(L, 10);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn9Param6

/** hybridStaticReturn9Param6 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
hybridStatic9Param6(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 6);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -9);
			ret2 = to<RET_2>(L, -8);
			ret3 = to<RET_3>(L, -7);
			ret4 = to<RET_4>(L, -6);
			ret5 = to<RET_5>(L, -5);
			ret6 = to<RET_6>(L, -4);
			ret7 = to<RET_7>(L, -3);
			ret8 = to<RET_8>(L, -2);
			ret9 = to<RET_9>(L, -1);
			lua_pop(L, 10);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4, arg5, arg6);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn9Param6

/** pcallStaticReturn9Param6 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
pcallStatic9Param6(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 6))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -9);
				ret2 = to<RET_2>(L, -8);
				ret3 = to<RET_3>(L, -7);
				ret4 = to<RET_4>(L, -6);
				ret5 = to<RET_5>(L, -5);
				ret6 = to<RET_6>(L, -4);
				ret7 = to<RET_7>(L, -3);
				ret8 = to<RET_8>(L, -2);
				ret9 = to<RET_9>(L, -1);
				lua_pop(L, 10); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn9Param6

/** phybridStaticReturn9Param6 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
phybridStatic9Param6(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 6))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -9);
				ret2 = to<RET_2>(L, -8);
				ret3 = to<RET_3>(L, -7);
				ret4 = to<RET_4>(L, -6);
				ret5 = to<RET_5>(L, -5);
				ret6 = to<RET_6>(L, -4);
				ret7 = to<RET_7>(L, -3);
				ret8 = to<RET_8>(L, -2);
				ret9 = to<RET_9>(L, -1);
				lua_pop(L, 10); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4, arg5, arg6);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn9Param6

/** callStaticReturn9Param7 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
callStatic9Param7(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 7);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -9);
			ret2 = to<RET_2>(L, -8);
			ret3 = to<RET_3>(L, -7);
			ret4 = to<RET_4>(L, -6);
			ret5 = to<RET_5>(L, -5);
			ret6 = to<RET_6>(L, -4);
			ret7 = to<RET_7>(L, -3);
			ret8 = to<RET_8>(L, -2);
			ret9 = to<RET_9>(L, -1);
			lua_pop(L, 10);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn9Param7

/** hybridStaticReturn9Param7 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
hybridStatic9Param7(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 7);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -9);
			ret2 = to<RET_2>(L, -8);
			ret3 = to<RET_3>(L, -7);
			ret4 = to<RET_4>(L, -6);
			ret5 = to<RET_5>(L, -5);
			ret6 = to<RET_6>(L, -4);
			ret7 = to<RET_7>(L, -3);
			ret8 = to<RET_8>(L, -2);
			ret9 = to<RET_9>(L, -1);
			lua_pop(L, 10);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn9Param7

/** pcallStaticReturn9Param7 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
pcallStatic9Param7(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 7))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -9);
				ret2 = to<RET_2>(L, -8);
				ret3 = to<RET_3>(L, -7);
				ret4 = to<RET_4>(L, -6);
				ret5 = to<RET_5>(L, -5);
				ret6 = to<RET_6>(L, -4);
				ret7 = to<RET_7>(L, -3);
				ret8 = to<RET_8>(L, -2);
				ret9 = to<RET_9>(L, -1);
				lua_pop(L, 10); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn9Param7

/** phybridStaticReturn9Param7 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
phybridStatic9Param7(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 7))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -9);
				ret2 = to<RET_2>(L, -8);
				ret3 = to<RET_3>(L, -7);
				ret4 = to<RET_4>(L, -6);
				ret5 = to<RET_5>(L, -5);
				ret6 = to<RET_6>(L, -4);
				ret7 = to<RET_7>(L, -3);
				ret8 = to<RET_8>(L, -2);
				ret9 = to<RET_9>(L, -1);
				lua_pop(L, 10); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn9Param7

/** callStaticReturn9Param8 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
callStatic9Param8(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 8);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -9);
			ret2 = to<RET_2>(L, -8);
			ret3 = to<RET_3>(L, -7);
			ret4 = to<RET_4>(L, -6);
			ret5 = to<RET_5>(L, -5);
			ret6 = to<RET_6>(L, -4);
			ret7 = to<RET_7>(L, -3);
			ret8 = to<RET_8>(L, -2);
			ret9 = to<RET_9>(L, -1);
			lua_pop(L, 10);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn9Param8

/** hybridStaticReturn9Param8 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
hybridStatic9Param8(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 8);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -9);
			ret2 = to<RET_2>(L, -8);
			ret3 = to<RET_3>(L, -7);
			ret4 = to<RET_4>(L, -6);
			ret5 = to<RET_5>(L, -5);
			ret6 = to<RET_6>(L, -4);
			ret7 = to<RET_7>(L, -3);
			ret8 = to<RET_8>(L, -2);
			ret9 = to<RET_9>(L, -1);
			lua_pop(L, 10);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn9Param8

/** pcallStaticReturn9Param8 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
pcallStatic9Param8(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 8))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -9);
				ret2 = to<RET_2>(L, -8);
				ret3 = to<RET_3>(L, -7);
				ret4 = to<RET_4>(L, -6);
				ret5 = to<RET_5>(L, -5);
				ret6 = to<RET_6>(L, -4);
				ret7 = to<RET_7>(L, -3);
				ret8 = to<RET_8>(L, -2);
				ret9 = to<RET_9>(L, -1);
				lua_pop(L, 10); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn9Param8

/** phybridStaticReturn9Param8 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
phybridStatic9Param8(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 8))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -9);
				ret2 = to<RET_2>(L, -8);
				ret3 = to<RET_3>(L, -7);
				ret4 = to<RET_4>(L, -6);
				ret5 = to<RET_5>(L, -5);
				ret6 = to<RET_6>(L, -4);
				ret7 = to<RET_7>(L, -3);
				ret8 = to<RET_8>(L, -2);
				ret9 = to<RET_9>(L, -1);
				lua_pop(L, 10); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn9Param8

/** callStaticReturn9Param9 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
callStatic9Param9(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 9);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -9);
			ret2 = to<RET_2>(L, -8);
			ret3 = to<RET_3>(L, -7);
			ret4 = to<RET_4>(L, -6);
			ret5 = to<RET_5>(L, -5);
			ret6 = to<RET_6>(L, -4);
			ret7 = to<RET_7>(L, -3);
			ret8 = to<RET_8>(L, -2);
			ret9 = to<RET_9>(L, -1);
			lua_pop(L, 10);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn9Param9

/** hybridStaticReturn9Param9 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
hybridStatic9Param9(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 9);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -9);
			ret2 = to<RET_2>(L, -8);
			ret3 = to<RET_3>(L, -7);
			ret4 = to<RET_4>(L, -6);
			ret5 = to<RET_5>(L, -5);
			ret6 = to<RET_6>(L, -4);
			ret7 = to<RET_7>(L, -3);
			ret8 = to<RET_8>(L, -2);
			ret9 = to<RET_9>(L, -1);
			lua_pop(L, 10);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn9Param9

/** pcallStaticReturn9Param9 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
pcallStatic9Param9(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 9))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -9);
				ret2 = to<RET_2>(L, -8);
				ret3 = to<RET_3>(L, -7);
				ret4 = to<RET_4>(L, -6);
				ret5 = to<RET_5>(L, -5);
				ret6 = to<RET_6>(L, -4);
				ret7 = to<RET_7>(L, -3);
				ret8 = to<RET_8>(L, -2);
				ret9 = to<RET_9>(L, -1);
				lua_pop(L, 10); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn9Param9

/** phybridStaticReturn9Param9 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
phybridStatic9Param9(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 9))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -9);
				ret2 = to<RET_2>(L, -8);
				ret3 = to<RET_3>(L, -7);
				ret4 = to<RET_4>(L, -6);
				ret5 = to<RET_5>(L, -5);
				ret6 = to<RET_6>(L, -4);
				ret7 = to<RET_7>(L, -3);
				ret8 = to<RET_8>(L, -2);
				ret9 = to<RET_9>(L, -1);
				lua_pop(L, 10); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn9Param9

/** callStaticReturn9Param10 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
callStatic9Param10(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, ARG_10 arg10, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			push(L, arg10);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 10);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -9);
			ret2 = to<RET_2>(L, -8);
			ret3 = to<RET_3>(L, -7);
			ret4 = to<RET_4>(L, -6);
			ret5 = to<RET_5>(L, -5);
			ret6 = to<RET_6>(L, -4);
			ret7 = to<RET_7>(L, -3);
			ret8 = to<RET_8>(L, -2);
			ret9 = to<RET_9>(L, -1);
			lua_pop(L, 10);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn9Param10

/** hybridStaticReturn9Param10 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
hybridStatic9Param10(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, ARG_10 arg10, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			push(L, arg10);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 10);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -9);
			ret2 = to<RET_2>(L, -8);
			ret3 = to<RET_3>(L, -7);
			ret4 = to<RET_4>(L, -6);
			ret5 = to<RET_5>(L, -5);
			ret6 = to<RET_6>(L, -4);
			ret7 = to<RET_7>(L, -3);
			ret8 = to<RET_8>(L, -2);
			ret9 = to<RET_9>(L, -1);
			lua_pop(L, 10);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn9Param10

/** pcallStaticReturn9Param10 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
pcallStatic9Param10(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, ARG_10 arg10, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			push(L, arg10);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 10))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -9);
				ret2 = to<RET_2>(L, -8);
				ret3 = to<RET_3>(L, -7);
				ret4 = to<RET_4>(L, -6);
				ret5 = to<RET_5>(L, -5);
				ret6 = to<RET_6>(L, -4);
				ret7 = to<RET_7>(L, -3);
				ret8 = to<RET_8>(L, -2);
				ret9 = to<RET_9>(L, -1);
				lua_pop(L, 10); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn9Param10

/** phybridStaticReturn9Param10 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
phybridStatic9Param10(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, ARG_10 arg10, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			push(L, arg10);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 10))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -9);
				ret2 = to<RET_2>(L, -8);
				ret3 = to<RET_3>(L, -7);
				ret4 = to<RET_4>(L, -6);
				ret5 = to<RET_5>(L, -5);
				ret6 = to<RET_6>(L, -4);
				ret7 = to<RET_7>(L, -3);
				ret8 = to<RET_8>(L, -2);
				ret9 = to<RET_9>(L, -1);
				lua_pop(L, 10); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn9Param10

/** callStaticReturn10Param0 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&) >
inline ScriptToNativeCallResult
callStatic10Param0(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, RET_10& ret10, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			/*s: module scriptFunction (arguments) */
			lua_call(L, 0);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -10);
			ret2 = to<RET_2>(L, -9);
			ret3 = to<RET_3>(L, -8);
			ret4 = to<RET_4>(L, -7);
			ret5 = to<RET_5>(L, -6);
			ret6 = to<RET_6>(L, -5);
			ret7 = to<RET_7>(L, -4);
			ret8 = to<RET_8>(L, -3);
			ret9 = to<RET_9>(L, -2);
			ret10 = to<RET_10>(L, -1);
			lua_pop(L, 11);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn10Param0

/** hybridStaticReturn10Param0 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&) >
inline ScriptToNativeCallResult
hybridStatic10Param0(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, RET_10& ret10, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			/*s: module scriptFunction (arguments) */
			lua_call(L, 0);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -10);
			ret2 = to<RET_2>(L, -9);
			ret3 = to<RET_3>(L, -8);
			ret4 = to<RET_4>(L, -7);
			ret5 = to<RET_5>(L, -6);
			ret6 = to<RET_6>(L, -5);
			ret7 = to<RET_7>(L, -4);
			ret8 = to<RET_8>(L, -3);
			ret9 = to<RET_9>(L, -2);
			ret10 = to<RET_10>(L, -1);
			lua_pop(L, 11);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn10Param0

/** pcallStaticReturn10Param0 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&) >
inline ScriptToNativeCallResult
pcallStatic10Param0(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, RET_10& ret10, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 0))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -10);
				ret2 = to<RET_2>(L, -9);
				ret3 = to<RET_3>(L, -8);
				ret4 = to<RET_4>(L, -7);
				ret5 = to<RET_5>(L, -6);
				ret6 = to<RET_6>(L, -5);
				ret7 = to<RET_7>(L, -4);
				ret8 = to<RET_8>(L, -3);
				ret9 = to<RET_9>(L, -2);
				ret10 = to<RET_10>(L, -1);
				lua_pop(L, 11); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn10Param0

/** phybridStaticReturn10Param0 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&) >
inline ScriptToNativeCallResult
phybridStatic10Param0(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, RET_10& ret10, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 0))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -10);
				ret2 = to<RET_2>(L, -9);
				ret3 = to<RET_3>(L, -8);
				ret4 = to<RET_4>(L, -7);
				ret5 = to<RET_5>(L, -6);
				ret6 = to<RET_6>(L, -5);
				ret7 = to<RET_7>(L, -4);
				ret8 = to<RET_8>(L, -3);
				ret9 = to<RET_9>(L, -2);
				ret10 = to<RET_10>(L, -1);
				lua_pop(L, 11); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn10Param0

/** callStaticReturn10Param1 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1) >
inline ScriptToNativeCallResult
callStatic10Param1(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, RET_10& ret10, ARG_1 arg1, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 1);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -10);
			ret2 = to<RET_2>(L, -9);
			ret3 = to<RET_3>(L, -8);
			ret4 = to<RET_4>(L, -7);
			ret5 = to<RET_5>(L, -6);
			ret6 = to<RET_6>(L, -5);
			ret7 = to<RET_7>(L, -4);
			ret8 = to<RET_8>(L, -3);
			ret9 = to<RET_9>(L, -2);
			ret10 = to<RET_10>(L, -1);
			lua_pop(L, 11);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn10Param1

/** hybridStaticReturn10Param1 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1) >
inline ScriptToNativeCallResult
hybridStatic10Param1(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, RET_10& ret10, ARG_1 arg1, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 1);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -10);
			ret2 = to<RET_2>(L, -9);
			ret3 = to<RET_3>(L, -8);
			ret4 = to<RET_4>(L, -7);
			ret5 = to<RET_5>(L, -6);
			ret6 = to<RET_6>(L, -5);
			ret7 = to<RET_7>(L, -4);
			ret8 = to<RET_8>(L, -3);
			ret9 = to<RET_9>(L, -2);
			ret10 = to<RET_10>(L, -1);
			lua_pop(L, 11);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn10Param1

/** pcallStaticReturn10Param1 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1) >
inline ScriptToNativeCallResult
pcallStatic10Param1(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, RET_10& ret10, ARG_1 arg1, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 1))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -10);
				ret2 = to<RET_2>(L, -9);
				ret3 = to<RET_3>(L, -8);
				ret4 = to<RET_4>(L, -7);
				ret5 = to<RET_5>(L, -6);
				ret6 = to<RET_6>(L, -5);
				ret7 = to<RET_7>(L, -4);
				ret8 = to<RET_8>(L, -3);
				ret9 = to<RET_9>(L, -2);
				ret10 = to<RET_10>(L, -1);
				lua_pop(L, 11); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn10Param1

/** phybridStaticReturn10Param1 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1) >
inline ScriptToNativeCallResult
phybridStatic10Param1(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, RET_10& ret10, ARG_1 arg1, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 1))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -10);
				ret2 = to<RET_2>(L, -9);
				ret3 = to<RET_3>(L, -8);
				ret4 = to<RET_4>(L, -7);
				ret5 = to<RET_5>(L, -6);
				ret6 = to<RET_6>(L, -5);
				ret7 = to<RET_7>(L, -4);
				ret8 = to<RET_8>(L, -3);
				ret9 = to<RET_9>(L, -2);
				ret10 = to<RET_10>(L, -1);
				lua_pop(L, 11); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn10Param1

/** callStaticReturn10Param2 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2) >
inline ScriptToNativeCallResult
callStatic10Param2(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, RET_10& ret10, ARG_1 arg1, ARG_2 arg2, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 2);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -10);
			ret2 = to<RET_2>(L, -9);
			ret3 = to<RET_3>(L, -8);
			ret4 = to<RET_4>(L, -7);
			ret5 = to<RET_5>(L, -6);
			ret6 = to<RET_6>(L, -5);
			ret7 = to<RET_7>(L, -4);
			ret8 = to<RET_8>(L, -3);
			ret9 = to<RET_9>(L, -2);
			ret10 = to<RET_10>(L, -1);
			lua_pop(L, 11);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn10Param2

/** hybridStaticReturn10Param2 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2) >
inline ScriptToNativeCallResult
hybridStatic10Param2(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, RET_10& ret10, ARG_1 arg1, ARG_2 arg2, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 2);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -10);
			ret2 = to<RET_2>(L, -9);
			ret3 = to<RET_3>(L, -8);
			ret4 = to<RET_4>(L, -7);
			ret5 = to<RET_5>(L, -6);
			ret6 = to<RET_6>(L, -5);
			ret7 = to<RET_7>(L, -4);
			ret8 = to<RET_8>(L, -3);
			ret9 = to<RET_9>(L, -2);
			ret10 = to<RET_10>(L, -1);
			lua_pop(L, 11);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn10Param2

/** pcallStaticReturn10Param2 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2) >
inline ScriptToNativeCallResult
pcallStatic10Param2(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, RET_10& ret10, ARG_1 arg1, ARG_2 arg2, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 2))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -10);
				ret2 = to<RET_2>(L, -9);
				ret3 = to<RET_3>(L, -8);
				ret4 = to<RET_4>(L, -7);
				ret5 = to<RET_5>(L, -6);
				ret6 = to<RET_6>(L, -5);
				ret7 = to<RET_7>(L, -4);
				ret8 = to<RET_8>(L, -3);
				ret9 = to<RET_9>(L, -2);
				ret10 = to<RET_10>(L, -1);
				lua_pop(L, 11); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn10Param2

/** phybridStaticReturn10Param2 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2) >
inline ScriptToNativeCallResult
phybridStatic10Param2(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, RET_10& ret10, ARG_1 arg1, ARG_2 arg2, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 2))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -10);
				ret2 = to<RET_2>(L, -9);
				ret3 = to<RET_3>(L, -8);
				ret4 = to<RET_4>(L, -7);
				ret5 = to<RET_5>(L, -6);
				ret6 = to<RET_6>(L, -5);
				ret7 = to<RET_7>(L, -4);
				ret8 = to<RET_8>(L, -3);
				ret9 = to<RET_9>(L, -2);
				ret10 = to<RET_10>(L, -1);
				lua_pop(L, 11); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn10Param2

/** callStaticReturn10Param3 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
callStatic10Param3(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, RET_10& ret10, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 3);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -10);
			ret2 = to<RET_2>(L, -9);
			ret3 = to<RET_3>(L, -8);
			ret4 = to<RET_4>(L, -7);
			ret5 = to<RET_5>(L, -6);
			ret6 = to<RET_6>(L, -5);
			ret7 = to<RET_7>(L, -4);
			ret8 = to<RET_8>(L, -3);
			ret9 = to<RET_9>(L, -2);
			ret10 = to<RET_10>(L, -1);
			lua_pop(L, 11);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn10Param3

/** hybridStaticReturn10Param3 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
hybridStatic10Param3(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, RET_10& ret10, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 3);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -10);
			ret2 = to<RET_2>(L, -9);
			ret3 = to<RET_3>(L, -8);
			ret4 = to<RET_4>(L, -7);
			ret5 = to<RET_5>(L, -6);
			ret6 = to<RET_6>(L, -5);
			ret7 = to<RET_7>(L, -4);
			ret8 = to<RET_8>(L, -3);
			ret9 = to<RET_9>(L, -2);
			ret10 = to<RET_10>(L, -1);
			lua_pop(L, 11);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn10Param3

/** pcallStaticReturn10Param3 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
pcallStatic10Param3(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, RET_10& ret10, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 3))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -10);
				ret2 = to<RET_2>(L, -9);
				ret3 = to<RET_3>(L, -8);
				ret4 = to<RET_4>(L, -7);
				ret5 = to<RET_5>(L, -6);
				ret6 = to<RET_6>(L, -5);
				ret7 = to<RET_7>(L, -4);
				ret8 = to<RET_8>(L, -3);
				ret9 = to<RET_9>(L, -2);
				ret10 = to<RET_10>(L, -1);
				lua_pop(L, 11); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn10Param3

/** phybridStaticReturn10Param3 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
phybridStatic10Param3(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, RET_10& ret10, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 3))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -10);
				ret2 = to<RET_2>(L, -9);
				ret3 = to<RET_3>(L, -8);
				ret4 = to<RET_4>(L, -7);
				ret5 = to<RET_5>(L, -6);
				ret6 = to<RET_6>(L, -5);
				ret7 = to<RET_7>(L, -4);
				ret8 = to<RET_8>(L, -3);
				ret9 = to<RET_9>(L, -2);
				ret10 = to<RET_10>(L, -1);
				lua_pop(L, 11); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn10Param3

/** callStaticReturn10Param4 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
callStatic10Param4(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, RET_10& ret10, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 4);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -10);
			ret2 = to<RET_2>(L, -9);
			ret3 = to<RET_3>(L, -8);
			ret4 = to<RET_4>(L, -7);
			ret5 = to<RET_5>(L, -6);
			ret6 = to<RET_6>(L, -5);
			ret7 = to<RET_7>(L, -4);
			ret8 = to<RET_8>(L, -3);
			ret9 = to<RET_9>(L, -2);
			ret10 = to<RET_10>(L, -1);
			lua_pop(L, 11);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn10Param4

/** hybridStaticReturn10Param4 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
hybridStatic10Param4(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, RET_10& ret10, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 4);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -10);
			ret2 = to<RET_2>(L, -9);
			ret3 = to<RET_3>(L, -8);
			ret4 = to<RET_4>(L, -7);
			ret5 = to<RET_5>(L, -6);
			ret6 = to<RET_6>(L, -5);
			ret7 = to<RET_7>(L, -4);
			ret8 = to<RET_8>(L, -3);
			ret9 = to<RET_9>(L, -2);
			ret10 = to<RET_10>(L, -1);
			lua_pop(L, 11);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn10Param4

/** pcallStaticReturn10Param4 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
pcallStatic10Param4(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, RET_10& ret10, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 4))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -10);
				ret2 = to<RET_2>(L, -9);
				ret3 = to<RET_3>(L, -8);
				ret4 = to<RET_4>(L, -7);
				ret5 = to<RET_5>(L, -6);
				ret6 = to<RET_6>(L, -5);
				ret7 = to<RET_7>(L, -4);
				ret8 = to<RET_8>(L, -3);
				ret9 = to<RET_9>(L, -2);
				ret10 = to<RET_10>(L, -1);
				lua_pop(L, 11); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn10Param4

/** phybridStaticReturn10Param4 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
phybridStatic10Param4(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, RET_10& ret10, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 4))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -10);
				ret2 = to<RET_2>(L, -9);
				ret3 = to<RET_3>(L, -8);
				ret4 = to<RET_4>(L, -7);
				ret5 = to<RET_5>(L, -6);
				ret6 = to<RET_6>(L, -5);
				ret7 = to<RET_7>(L, -4);
				ret8 = to<RET_8>(L, -3);
				ret9 = to<RET_9>(L, -2);
				ret10 = to<RET_10>(L, -1);
				lua_pop(L, 11); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn10Param4

/** callStaticReturn10Param5 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
callStatic10Param5(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, RET_10& ret10, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 5);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -10);
			ret2 = to<RET_2>(L, -9);
			ret3 = to<RET_3>(L, -8);
			ret4 = to<RET_4>(L, -7);
			ret5 = to<RET_5>(L, -6);
			ret6 = to<RET_6>(L, -5);
			ret7 = to<RET_7>(L, -4);
			ret8 = to<RET_8>(L, -3);
			ret9 = to<RET_9>(L, -2);
			ret10 = to<RET_10>(L, -1);
			lua_pop(L, 11);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn10Param5

/** hybridStaticReturn10Param5 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
hybridStatic10Param5(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, RET_10& ret10, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 5);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -10);
			ret2 = to<RET_2>(L, -9);
			ret3 = to<RET_3>(L, -8);
			ret4 = to<RET_4>(L, -7);
			ret5 = to<RET_5>(L, -6);
			ret6 = to<RET_6>(L, -5);
			ret7 = to<RET_7>(L, -4);
			ret8 = to<RET_8>(L, -3);
			ret9 = to<RET_9>(L, -2);
			ret10 = to<RET_10>(L, -1);
			lua_pop(L, 11);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4, arg5);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4, arg5);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn10Param5

/** pcallStaticReturn10Param5 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
pcallStatic10Param5(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, RET_10& ret10, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 5))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -10);
				ret2 = to<RET_2>(L, -9);
				ret3 = to<RET_3>(L, -8);
				ret4 = to<RET_4>(L, -7);
				ret5 = to<RET_5>(L, -6);
				ret6 = to<RET_6>(L, -5);
				ret7 = to<RET_7>(L, -4);
				ret8 = to<RET_8>(L, -3);
				ret9 = to<RET_9>(L, -2);
				ret10 = to<RET_10>(L, -1);
				lua_pop(L, 11); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn10Param5

/** phybridStaticReturn10Param5 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
phybridStatic10Param5(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, RET_10& ret10, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 5))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -10);
				ret2 = to<RET_2>(L, -9);
				ret3 = to<RET_3>(L, -8);
				ret4 = to<RET_4>(L, -7);
				ret5 = to<RET_5>(L, -6);
				ret6 = to<RET_6>(L, -5);
				ret7 = to<RET_7>(L, -4);
				ret8 = to<RET_8>(L, -3);
				ret9 = to<RET_9>(L, -2);
				ret10 = to<RET_10>(L, -1);
				lua_pop(L, 11); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4, arg5);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4, arg5);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn10Param5

/** callStaticReturn10Param6 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
callStatic10Param6(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, RET_10& ret10, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 6);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -10);
			ret2 = to<RET_2>(L, -9);
			ret3 = to<RET_3>(L, -8);
			ret4 = to<RET_4>(L, -7);
			ret5 = to<RET_5>(L, -6);
			ret6 = to<RET_6>(L, -5);
			ret7 = to<RET_7>(L, -4);
			ret8 = to<RET_8>(L, -3);
			ret9 = to<RET_9>(L, -2);
			ret10 = to<RET_10>(L, -1);
			lua_pop(L, 11);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn10Param6

/** hybridStaticReturn10Param6 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
hybridStatic10Param6(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, RET_10& ret10, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 6);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -10);
			ret2 = to<RET_2>(L, -9);
			ret3 = to<RET_3>(L, -8);
			ret4 = to<RET_4>(L, -7);
			ret5 = to<RET_5>(L, -6);
			ret6 = to<RET_6>(L, -5);
			ret7 = to<RET_7>(L, -4);
			ret8 = to<RET_8>(L, -3);
			ret9 = to<RET_9>(L, -2);
			ret10 = to<RET_10>(L, -1);
			lua_pop(L, 11);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4, arg5, arg6);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn10Param6

/** pcallStaticReturn10Param6 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
pcallStatic10Param6(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, RET_10& ret10, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 6))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -10);
				ret2 = to<RET_2>(L, -9);
				ret3 = to<RET_3>(L, -8);
				ret4 = to<RET_4>(L, -7);
				ret5 = to<RET_5>(L, -6);
				ret6 = to<RET_6>(L, -5);
				ret7 = to<RET_7>(L, -4);
				ret8 = to<RET_8>(L, -3);
				ret9 = to<RET_9>(L, -2);
				ret10 = to<RET_10>(L, -1);
				lua_pop(L, 11); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn10Param6

/** phybridStaticReturn10Param6 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
phybridStatic10Param6(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, RET_10& ret10, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 6))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -10);
				ret2 = to<RET_2>(L, -9);
				ret3 = to<RET_3>(L, -8);
				ret4 = to<RET_4>(L, -7);
				ret5 = to<RET_5>(L, -6);
				ret6 = to<RET_6>(L, -5);
				ret7 = to<RET_7>(L, -4);
				ret8 = to<RET_8>(L, -3);
				ret9 = to<RET_9>(L, -2);
				ret10 = to<RET_10>(L, -1);
				lua_pop(L, 11); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4, arg5, arg6);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn10Param6

/** callStaticReturn10Param7 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
callStatic10Param7(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, RET_10& ret10, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 7);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -10);
			ret2 = to<RET_2>(L, -9);
			ret3 = to<RET_3>(L, -8);
			ret4 = to<RET_4>(L, -7);
			ret5 = to<RET_5>(L, -6);
			ret6 = to<RET_6>(L, -5);
			ret7 = to<RET_7>(L, -4);
			ret8 = to<RET_8>(L, -3);
			ret9 = to<RET_9>(L, -2);
			ret10 = to<RET_10>(L, -1);
			lua_pop(L, 11);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn10Param7

/** hybridStaticReturn10Param7 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
hybridStatic10Param7(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, RET_10& ret10, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 7);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -10);
			ret2 = to<RET_2>(L, -9);
			ret3 = to<RET_3>(L, -8);
			ret4 = to<RET_4>(L, -7);
			ret5 = to<RET_5>(L, -6);
			ret6 = to<RET_6>(L, -5);
			ret7 = to<RET_7>(L, -4);
			ret8 = to<RET_8>(L, -3);
			ret9 = to<RET_9>(L, -2);
			ret10 = to<RET_10>(L, -1);
			lua_pop(L, 11);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn10Param7

/** pcallStaticReturn10Param7 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
pcallStatic10Param7(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, RET_10& ret10, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 7))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -10);
				ret2 = to<RET_2>(L, -9);
				ret3 = to<RET_3>(L, -8);
				ret4 = to<RET_4>(L, -7);
				ret5 = to<RET_5>(L, -6);
				ret6 = to<RET_6>(L, -5);
				ret7 = to<RET_7>(L, -4);
				ret8 = to<RET_8>(L, -3);
				ret9 = to<RET_9>(L, -2);
				ret10 = to<RET_10>(L, -1);
				lua_pop(L, 11); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn10Param7

/** phybridStaticReturn10Param7 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
phybridStatic10Param7(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, RET_10& ret10, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 7))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -10);
				ret2 = to<RET_2>(L, -9);
				ret3 = to<RET_3>(L, -8);
				ret4 = to<RET_4>(L, -7);
				ret5 = to<RET_5>(L, -6);
				ret6 = to<RET_6>(L, -5);
				ret7 = to<RET_7>(L, -4);
				ret8 = to<RET_8>(L, -3);
				ret9 = to<RET_9>(L, -2);
				ret10 = to<RET_10>(L, -1);
				lua_pop(L, 11); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn10Param7

/** callStaticReturn10Param8 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
callStatic10Param8(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, RET_10& ret10, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 8);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -10);
			ret2 = to<RET_2>(L, -9);
			ret3 = to<RET_3>(L, -8);
			ret4 = to<RET_4>(L, -7);
			ret5 = to<RET_5>(L, -6);
			ret6 = to<RET_6>(L, -5);
			ret7 = to<RET_7>(L, -4);
			ret8 = to<RET_8>(L, -3);
			ret9 = to<RET_9>(L, -2);
			ret10 = to<RET_10>(L, -1);
			lua_pop(L, 11);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn10Param8

/** hybridStaticReturn10Param8 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
hybridStatic10Param8(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, RET_10& ret10, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 8);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -10);
			ret2 = to<RET_2>(L, -9);
			ret3 = to<RET_3>(L, -8);
			ret4 = to<RET_4>(L, -7);
			ret5 = to<RET_5>(L, -6);
			ret6 = to<RET_6>(L, -5);
			ret7 = to<RET_7>(L, -4);
			ret8 = to<RET_8>(L, -3);
			ret9 = to<RET_9>(L, -2);
			ret10 = to<RET_10>(L, -1);
			lua_pop(L, 11);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn10Param8

/** pcallStaticReturn10Param8 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
pcallStatic10Param8(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, RET_10& ret10, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 8))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -10);
				ret2 = to<RET_2>(L, -9);
				ret3 = to<RET_3>(L, -8);
				ret4 = to<RET_4>(L, -7);
				ret5 = to<RET_5>(L, -6);
				ret6 = to<RET_6>(L, -5);
				ret7 = to<RET_7>(L, -4);
				ret8 = to<RET_8>(L, -3);
				ret9 = to<RET_9>(L, -2);
				ret10 = to<RET_10>(L, -1);
				lua_pop(L, 11); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn10Param8

/** phybridStaticReturn10Param8 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
phybridStatic10Param8(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, RET_10& ret10, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 8))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -10);
				ret2 = to<RET_2>(L, -9);
				ret3 = to<RET_3>(L, -8);
				ret4 = to<RET_4>(L, -7);
				ret5 = to<RET_5>(L, -6);
				ret6 = to<RET_6>(L, -5);
				ret7 = to<RET_7>(L, -4);
				ret8 = to<RET_8>(L, -3);
				ret9 = to<RET_9>(L, -2);
				ret10 = to<RET_10>(L, -1);
				lua_pop(L, 11); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn10Param8

/** callStaticReturn10Param9 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
callStatic10Param9(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, RET_10& ret10, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 9);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -10);
			ret2 = to<RET_2>(L, -9);
			ret3 = to<RET_3>(L, -8);
			ret4 = to<RET_4>(L, -7);
			ret5 = to<RET_5>(L, -6);
			ret6 = to<RET_6>(L, -5);
			ret7 = to<RET_7>(L, -4);
			ret8 = to<RET_8>(L, -3);
			ret9 = to<RET_9>(L, -2);
			ret10 = to<RET_10>(L, -1);
			lua_pop(L, 11);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn10Param9

/** hybridStaticReturn10Param9 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
hybridStatic10Param9(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, RET_10& ret10, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 9);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -10);
			ret2 = to<RET_2>(L, -9);
			ret3 = to<RET_3>(L, -8);
			ret4 = to<RET_4>(L, -7);
			ret5 = to<RET_5>(L, -6);
			ret6 = to<RET_6>(L, -5);
			ret7 = to<RET_7>(L, -4);
			ret8 = to<RET_8>(L, -3);
			ret9 = to<RET_9>(L, -2);
			ret10 = to<RET_10>(L, -1);
			lua_pop(L, 11);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn10Param9

/** pcallStaticReturn10Param9 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
pcallStatic10Param9(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, RET_10& ret10, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 9))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -10);
				ret2 = to<RET_2>(L, -9);
				ret3 = to<RET_3>(L, -8);
				ret4 = to<RET_4>(L, -7);
				ret5 = to<RET_5>(L, -6);
				ret6 = to<RET_6>(L, -5);
				ret7 = to<RET_7>(L, -4);
				ret8 = to<RET_8>(L, -3);
				ret9 = to<RET_9>(L, -2);
				ret10 = to<RET_10>(L, -1);
				lua_pop(L, 11); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn10Param9

/** phybridStaticReturn10Param9 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
phybridStatic10Param9(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, RET_10& ret10, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 9))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -10);
				ret2 = to<RET_2>(L, -9);
				ret3 = to<RET_3>(L, -8);
				ret4 = to<RET_4>(L, -7);
				ret5 = to<RET_5>(L, -6);
				ret6 = to<RET_6>(L, -5);
				ret7 = to<RET_7>(L, -4);
				ret8 = to<RET_8>(L, -3);
				ret9 = to<RET_9>(L, -2);
				ret10 = to<RET_10>(L, -1);
				lua_pop(L, 11); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn10Param9

/** callStaticReturn10Param10 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
callStatic10Param10(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, RET_10& ret10, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, ARG_10 arg10, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			push(L, arg10);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 10);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -10);
			ret2 = to<RET_2>(L, -9);
			ret3 = to<RET_3>(L, -8);
			ret4 = to<RET_4>(L, -7);
			ret5 = to<RET_5>(L, -6);
			ret6 = to<RET_6>(L, -5);
			ret7 = to<RET_7>(L, -4);
			ret8 = to<RET_8>(L, -3);
			ret9 = to<RET_9>(L, -2);
			ret10 = to<RET_10>(L, -1);
			lua_pop(L, 11);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // callStaticReturn10Param10

/** hybridStaticReturn10Param10 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
hybridStatic10Param10(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, RET_10& ret10, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, ARG_10 arg10, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			push(L, arg10);
			/*s: module scriptFunction (arguments) */
			lua_call(L, 10);
			/*s: module (return values) */
			ret1 = to<RET_1>(L, -10);
			ret2 = to<RET_2>(L, -9);
			ret3 = to<RET_3>(L, -8);
			ret4 = to<RET_4>(L, -7);
			ret5 = to<RET_5>(L, -6);
			ret6 = to<RET_6>(L, -5);
			ret7 = to<RET_7>(L, -4);
			ret8 = to<RET_8>(L, -3);
			ret9 = to<RET_9>(L, -2);
			ret10 = to<RET_10>(L, -1);
			lua_pop(L, 11);
			/*s: */
			return lua_extension::functionSuccess;
		}
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::moduleNotFound; 
	} 
} // hybridStaticReturn10Param10

/** pcallStaticReturn10Param10 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
pcallStatic10Param10(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, RET_10& ret10, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, ARG_10 arg10, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			push(L, arg10);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 10))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -10);
				ret2 = to<RET_2>(L, -9);
				ret3 = to<RET_3>(L, -8);
				ret4 = to<RET_4>(L, -7);
				ret5 = to<RET_5>(L, -6);
				ret6 = to<RET_6>(L, -5);
				ret7 = to<RET_7>(L, -4);
				ret8 = to<RET_8>(L, -3);
				ret9 = to<RET_9>(L, -2);
				ret10 = to<RET_10>(L, -1);
				lua_pop(L, 11); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		return lua_extension::moduleNotFound; 
	} 
} // pcallStaticReturn10Param10

/** phybridStaticReturn10Param10 */
template<typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (* nativeFunction)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
phybridStatic10Param10(lua_State* L, const char* scriptFunction, RET_1& ret1, RET_2& ret2, RET_3& ret3, RET_4& ret4, RET_5& ret5, RET_6& ret6, RET_7& ret7, RET_8& ret8, RET_9& ret9, RET_10& ret10, ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, ARG_10 arg10, const char* module="_G")
{	/*s: */
	lua_getglobal(L, module);
	/*s: ? */
	if (lua_istable(L, -1))
	{	/*s: module */
		lua_getfield(L, -1, scriptFunction);
		/*s: module ? */
		if (lua_isfunction(L, -1))
		{	/*s: module scriptFunction */
			push(L, arg1);
			push(L, arg2);
			push(L, arg3);
			push(L, arg4);
			push(L, arg5);
			push(L, arg6);
			push(L, arg7);
			push(L, arg8);
			push(L, arg9);
			push(L, arg10);
			/*s: module scriptFunction (arguments) */
			if (!Lua::callProtected((L, 10))
			{	/*s: module (return values) */ 
				ret1 = to<RET_1>(L, -10);
				ret2 = to<RET_2>(L, -9);
				ret3 = to<RET_3>(L, -8);
				ret4 = to<RET_4>(L, -7);
				ret5 = to<RET_5>(L, -6);
				ret6 = to<RET_6>(L, -5);
				ret7 = to<RET_7>(L, -4);
				ret8 = to<RET_8>(L, -3);
				ret9 = to<RET_9>(L, -2);
				ret10 = to<RET_10>(L, -1);
				lua_pop(L, 11); 
				/*s: */ 
				return lua_extension::functionSuccess;
			} 
			else
			{	/*s: module */
				lua_pop(L, 1);
				/*s: */
				return lua_extension::functionError;
			} 
		else
		{	/*s: module nil */
			lua_pop(L, 2)
			/*s: */
			ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
			return lua_extension::functionNotFound;
		}
	}
	else
	{	/*s: !table */ 
		lua_pop(L, 1);
		/*s: */ 
		ret1 = (*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::moduleNotFound; 
	} 
} // phybridStaticReturn10Param10

} // namespace lua_extension