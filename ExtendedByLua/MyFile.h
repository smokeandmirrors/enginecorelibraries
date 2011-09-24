/** phybridMemberReturn0Param1 */
template<typename CLASS, typename ARG_1, void (CLASS::* function)(ARG_1) >
inline ScriptToNativeCallResult
phybridConstReturn0Param1(lua_State* L, const char* scriptFunction, const CLASS& object, ARG_1 arg1)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 2))
		{	/*s: object (return values) */ 
			lua_pop(L, 1); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		(object.*nativeFunction)(arg1);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn0Param1

/** phybridConstReturn0Param1 */
template<typename CLASS, typename ARG_1, void (CLASS::* function)(ARG_1) const>
inline ScriptToNativeCallResult
phybridMember0Param1(lua_State* L, const char* scriptFunction, CLASS& object, ARG_1 arg1)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 2))
		{	/*s: object (return values) */ 
			lua_pop(L, 1); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		(object.*nativeFunction)(arg1);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn0Param1

/** hybridMemberReturn0Param1 */
template<typename CLASS, typename ARG_1, void (CLASS::* function)(ARG_1) >
inline ScriptToNativeCallResult
hybridConstReturn0Param1(lua_State* L, const char* scriptFunction, const CLASS& object, ARG_1 arg1)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 2); 
		/*s: object (return values) */ 
		lua_pop(L, 1); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		(object.*nativeFunction)(arg1);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn0Param1 */
template<typename CLASS, typename ARG_1, void (CLASS::* function)(ARG_1) const>
inline ScriptToNativeCallResult
hybridMember0Param1(lua_State* L, const char* scriptFunction, CLASS& object, ARG_1 arg1)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 2); 
		/*s: object (return values) */ 
		lua_pop(L, 1); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		(object.*nativeFunction)(arg1);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn0Param2 */
template<typename CLASS, typename ARG_1, typename ARG_2, void (CLASS::* function)(ARG_1, ARG_2) >
inline ScriptToNativeCallResult
phybridConstReturn0Param2(lua_State* L, const char* scriptFunction, const CLASS& object, ARG_1 arg1, ARG_2)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 3))
		{	/*s: object (return values) */ 
			lua_pop(L, 1); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		(object.*nativeFunction)(arg1, arg2);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn0Param2

/** phybridConstReturn0Param2 */
template<typename CLASS, typename ARG_1, typename ARG_2, void (CLASS::* function)(ARG_1, ARG_2) const>
inline ScriptToNativeCallResult
phybridMember0Param2(lua_State* L, const char* scriptFunction, CLASS& object, ARG_1 arg1, ARG_2)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 3))
		{	/*s: object (return values) */ 
			lua_pop(L, 1); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		(object.*nativeFunction)(arg1, arg2);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn0Param2

/** hybridMemberReturn0Param2 */
template<typename CLASS, typename ARG_1, typename ARG_2, void (CLASS::* function)(ARG_1, ARG_2) >
inline ScriptToNativeCallResult
hybridConstReturn0Param2(lua_State* L, const char* scriptFunction, const CLASS& object, ARG_1 arg1, ARG_2)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 3); 
		/*s: object (return values) */ 
		lua_pop(L, 1); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		(object.*nativeFunction)(arg1, arg2);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn0Param2 */
template<typename CLASS, typename ARG_1, typename ARG_2, void (CLASS::* function)(ARG_1, ARG_2) const>
inline ScriptToNativeCallResult
hybridMember0Param2(lua_State* L, const char* scriptFunction, CLASS& object, ARG_1 arg1, ARG_2)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 3); 
		/*s: object (return values) */ 
		lua_pop(L, 1); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		(object.*nativeFunction)(arg1, arg2);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn0Param3 */
template<typename CLASS, typename ARG_1, typename ARG_2, typename ARG_3, void (CLASS::* function)(ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
phybridConstReturn0Param3(lua_State* L, const char* scriptFunction, const CLASS& object, ARG_1 arg1, ARG_2, ARG_3)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 4))
		{	/*s: object (return values) */ 
			lua_pop(L, 1); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		(object.*nativeFunction)(arg1, arg2, arg3);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn0Param3

/** phybridConstReturn0Param3 */
template<typename CLASS, typename ARG_1, typename ARG_2, typename ARG_3, void (CLASS::* function)(ARG_1, ARG_2, ARG_3) const>
inline ScriptToNativeCallResult
phybridMember0Param3(lua_State* L, const char* scriptFunction, CLASS& object, ARG_1 arg1, ARG_2, ARG_3)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 4))
		{	/*s: object (return values) */ 
			lua_pop(L, 1); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		(object.*nativeFunction)(arg1, arg2, arg3);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn0Param3

/** hybridMemberReturn0Param3 */
template<typename CLASS, typename ARG_1, typename ARG_2, typename ARG_3, void (CLASS::* function)(ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
hybridConstReturn0Param3(lua_State* L, const char* scriptFunction, const CLASS& object, ARG_1 arg1, ARG_2, ARG_3)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 4); 
		/*s: object (return values) */ 
		lua_pop(L, 1); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		(object.*nativeFunction)(arg1, arg2, arg3);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn0Param3 */
template<typename CLASS, typename ARG_1, typename ARG_2, typename ARG_3, void (CLASS::* function)(ARG_1, ARG_2, ARG_3) const>
inline ScriptToNativeCallResult
hybridMember0Param3(lua_State* L, const char* scriptFunction, CLASS& object, ARG_1 arg1, ARG_2, ARG_3)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 4); 
		/*s: object (return values) */ 
		lua_pop(L, 1); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		(object.*nativeFunction)(arg1, arg2, arg3);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn0Param4 */
template<typename CLASS, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, void (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
phybridConstReturn0Param4(lua_State* L, const char* scriptFunction, const CLASS& object, ARG_1 arg1, ARG_2, ARG_3, ARG_4)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 5))
		{	/*s: object (return values) */ 
			lua_pop(L, 1); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		(object.*nativeFunction)(arg1, arg2, arg3, arg4);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn0Param4

/** phybridConstReturn0Param4 */
template<typename CLASS, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, void (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4) const>
inline ScriptToNativeCallResult
phybridMember0Param4(lua_State* L, const char* scriptFunction, CLASS& object, ARG_1 arg1, ARG_2, ARG_3, ARG_4)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 5))
		{	/*s: object (return values) */ 
			lua_pop(L, 1); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		(object.*nativeFunction)(arg1, arg2, arg3, arg4);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn0Param4

/** hybridMemberReturn0Param4 */
template<typename CLASS, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, void (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
hybridConstReturn0Param4(lua_State* L, const char* scriptFunction, const CLASS& object, ARG_1 arg1, ARG_2, ARG_3, ARG_4)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 5); 
		/*s: object (return values) */ 
		lua_pop(L, 1); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		(object.*nativeFunction)(arg1, arg2, arg3, arg4);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn0Param4 */
template<typename CLASS, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, void (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4) const>
inline ScriptToNativeCallResult
hybridMember0Param4(lua_State* L, const char* scriptFunction, CLASS& object, ARG_1 arg1, ARG_2, ARG_3, ARG_4)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 5); 
		/*s: object (return values) */ 
		lua_pop(L, 1); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		(object.*nativeFunction)(arg1, arg2, arg3, arg4);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn0Param5 */
template<typename CLASS, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, void (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
phybridConstReturn0Param5(lua_State* L, const char* scriptFunction, const CLASS& object, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 6))
		{	/*s: object (return values) */ 
			lua_pop(L, 1); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		(object.*nativeFunction)(arg1, arg2, arg3, arg4, arg5);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn0Param5

/** phybridConstReturn0Param5 */
template<typename CLASS, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, void (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) const>
inline ScriptToNativeCallResult
phybridMember0Param5(lua_State* L, const char* scriptFunction, CLASS& object, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 6))
		{	/*s: object (return values) */ 
			lua_pop(L, 1); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		(object.*nativeFunction)(arg1, arg2, arg3, arg4, arg5);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn0Param5

/** hybridMemberReturn0Param5 */
template<typename CLASS, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, void (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
hybridConstReturn0Param5(lua_State* L, const char* scriptFunction, const CLASS& object, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 6); 
		/*s: object (return values) */ 
		lua_pop(L, 1); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		(object.*nativeFunction)(arg1, arg2, arg3, arg4, arg5);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn0Param5 */
template<typename CLASS, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, void (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) const>
inline ScriptToNativeCallResult
hybridMember0Param5(lua_State* L, const char* scriptFunction, CLASS& object, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 6); 
		/*s: object (return values) */ 
		lua_pop(L, 1); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		(object.*nativeFunction)(arg1, arg2, arg3, arg4, arg5);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn0Param6 */
template<typename CLASS, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, void (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
phybridConstReturn0Param6(lua_State* L, const char* scriptFunction, const CLASS& object, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 7))
		{	/*s: object (return values) */ 
			lua_pop(L, 1); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		(object.*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn0Param6

/** phybridConstReturn0Param6 */
template<typename CLASS, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, void (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) const>
inline ScriptToNativeCallResult
phybridMember0Param6(lua_State* L, const char* scriptFunction, CLASS& object, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 7))
		{	/*s: object (return values) */ 
			lua_pop(L, 1); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		(object.*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn0Param6

/** hybridMemberReturn0Param6 */
template<typename CLASS, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, void (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
hybridConstReturn0Param6(lua_State* L, const char* scriptFunction, const CLASS& object, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 7); 
		/*s: object (return values) */ 
		lua_pop(L, 1); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		(object.*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn0Param6 */
template<typename CLASS, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, void (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) const>
inline ScriptToNativeCallResult
hybridMember0Param6(lua_State* L, const char* scriptFunction, CLASS& object, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 7); 
		/*s: object (return values) */ 
		lua_pop(L, 1); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		(object.*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn0Param7 */
template<typename CLASS, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, void (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
phybridConstReturn0Param7(lua_State* L, const char* scriptFunction, const CLASS& object, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 8))
		{	/*s: object (return values) */ 
			lua_pop(L, 1); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		(object.*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn0Param7

/** phybridConstReturn0Param7 */
template<typename CLASS, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, void (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) const>
inline ScriptToNativeCallResult
phybridMember0Param7(lua_State* L, const char* scriptFunction, CLASS& object, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 8))
		{	/*s: object (return values) */ 
			lua_pop(L, 1); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		(object.*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn0Param7

/** hybridMemberReturn0Param7 */
template<typename CLASS, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, void (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
hybridConstReturn0Param7(lua_State* L, const char* scriptFunction, const CLASS& object, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 8); 
		/*s: object (return values) */ 
		lua_pop(L, 1); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		(object.*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn0Param7 */
template<typename CLASS, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, void (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) const>
inline ScriptToNativeCallResult
hybridMember0Param7(lua_State* L, const char* scriptFunction, CLASS& object, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 8); 
		/*s: object (return values) */ 
		lua_pop(L, 1); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		(object.*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn0Param8 */
template<typename CLASS, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, void (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
phybridConstReturn0Param8(lua_State* L, const char* scriptFunction, const CLASS& object, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 9))
		{	/*s: object (return values) */ 
			lua_pop(L, 1); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		(object.*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn0Param8

/** phybridConstReturn0Param8 */
template<typename CLASS, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, void (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) const>
inline ScriptToNativeCallResult
phybridMember0Param8(lua_State* L, const char* scriptFunction, CLASS& object, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 9))
		{	/*s: object (return values) */ 
			lua_pop(L, 1); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		(object.*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn0Param8

/** hybridMemberReturn0Param8 */
template<typename CLASS, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, void (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
hybridConstReturn0Param8(lua_State* L, const char* scriptFunction, const CLASS& object, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 9); 
		/*s: object (return values) */ 
		lua_pop(L, 1); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		(object.*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn0Param8 */
template<typename CLASS, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, void (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) const>
inline ScriptToNativeCallResult
hybridMember0Param8(lua_State* L, const char* scriptFunction, CLASS& object, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 9); 
		/*s: object (return values) */ 
		lua_pop(L, 1); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		(object.*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn0Param9 */
template<typename CLASS, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, void (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
phybridConstReturn0Param9(lua_State* L, const char* scriptFunction, const CLASS& object, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		push(L, arg9);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 10))
		{	/*s: object (return values) */ 
			lua_pop(L, 1); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		(object.*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn0Param9

/** phybridConstReturn0Param9 */
template<typename CLASS, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, void (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) const>
inline ScriptToNativeCallResult
phybridMember0Param9(lua_State* L, const char* scriptFunction, CLASS& object, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		push(L, arg9);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 10))
		{	/*s: object (return values) */ 
			lua_pop(L, 1); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		(object.*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn0Param9

/** hybridMemberReturn0Param9 */
template<typename CLASS, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, void (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
hybridConstReturn0Param9(lua_State* L, const char* scriptFunction, const CLASS& object, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		push(L, arg9);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 10); 
		/*s: object (return values) */ 
		lua_pop(L, 1); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		(object.*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn0Param9 */
template<typename CLASS, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, void (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) const>
inline ScriptToNativeCallResult
hybridMember0Param9(lua_State* L, const char* scriptFunction, CLASS& object, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		push(L, arg9);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 10); 
		/*s: object (return values) */ 
		lua_pop(L, 1); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		(object.*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn0Param10 */
template<typename CLASS, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, void (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
phybridConstReturn0Param10(lua_State* L, const char* scriptFunction, const CLASS& object, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
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
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 11))
		{	/*s: object (return values) */ 
			lua_pop(L, 1); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		(object.*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn0Param10

/** phybridConstReturn0Param10 */
template<typename CLASS, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, void (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) const>
inline ScriptToNativeCallResult
phybridMember0Param10(lua_State* L, const char* scriptFunction, CLASS& object, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
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
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 11))
		{	/*s: object (return values) */ 
			lua_pop(L, 1); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		(object.*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn0Param10

/** hybridMemberReturn0Param10 */
template<typename CLASS, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, void (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
hybridConstReturn0Param10(lua_State* L, const char* scriptFunction, const CLASS& object, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
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
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 11); 
		/*s: object (return values) */ 
		lua_pop(L, 1); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		(object.*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn0Param10 */
template<typename CLASS, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, void (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) const>
inline ScriptToNativeCallResult
hybridMember0Param10(lua_State* L, const char* scriptFunction, CLASS& object, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
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
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 11); 
		/*s: object (return values) */ 
		lua_pop(L, 1); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		(object.*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn1Param0 */
template<typename CLASS, typename RET_1, RET_1 (CLASS::* function)(void) >
inline ScriptToNativeCallResult
phybridConstReturn1Param0(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 1))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -1);
			lua_pop(L, 2); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)();
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn1Param0

/** phybridConstReturn1Param0 */
template<typename CLASS, typename RET_1, RET_1 (CLASS::* function)(void) const>
inline ScriptToNativeCallResult
phybridMember1Param0(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 1))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -1);
			lua_pop(L, 2); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)();
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn1Param0

/** hybridMemberReturn1Param0 */
template<typename CLASS, typename RET_1, RET_1 (CLASS::* function)(void) >
inline ScriptToNativeCallResult
hybridConstReturn1Param0(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 1); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -1);
		lua_pop(L, 2); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)();
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn1Param0 */
template<typename CLASS, typename RET_1, RET_1 (CLASS::* function)(void) const>
inline ScriptToNativeCallResult
hybridMember1Param0(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 1); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -1);
		lua_pop(L, 2); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)();
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn1Param1 */
template<typename CLASS, typename RET_1, typename ARG_1, RET_1 (CLASS::* function)(ARG_1) >
inline ScriptToNativeCallResult
phybridConstReturn1Param1(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, ARG_1 arg1)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 2))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -1);
			lua_pop(L, 2); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(arg1);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn1Param1

/** phybridConstReturn1Param1 */
template<typename CLASS, typename RET_1, typename ARG_1, RET_1 (CLASS::* function)(ARG_1) const>
inline ScriptToNativeCallResult
phybridMember1Param1(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, ARG_1 arg1)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 2))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -1);
			lua_pop(L, 2); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(arg1);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn1Param1

/** hybridMemberReturn1Param1 */
template<typename CLASS, typename RET_1, typename ARG_1, RET_1 (CLASS::* function)(ARG_1) >
inline ScriptToNativeCallResult
hybridConstReturn1Param1(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, ARG_1 arg1)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 2); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -1);
		lua_pop(L, 2); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(arg1);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn1Param1 */
template<typename CLASS, typename RET_1, typename ARG_1, RET_1 (CLASS::* function)(ARG_1) const>
inline ScriptToNativeCallResult
hybridMember1Param1(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, ARG_1 arg1)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 2); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -1);
		lua_pop(L, 2); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(arg1);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn1Param2 */
template<typename CLASS, typename RET_1, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(ARG_1, ARG_2) >
inline ScriptToNativeCallResult
phybridConstReturn1Param2(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, ARG_1 arg1, ARG_2)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 3))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -1);
			lua_pop(L, 2); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(arg1, arg2);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn1Param2

/** phybridConstReturn1Param2 */
template<typename CLASS, typename RET_1, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(ARG_1, ARG_2) const>
inline ScriptToNativeCallResult
phybridMember1Param2(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, ARG_1 arg1, ARG_2)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 3))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -1);
			lua_pop(L, 2); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(arg1, arg2);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn1Param2

/** hybridMemberReturn1Param2 */
template<typename CLASS, typename RET_1, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(ARG_1, ARG_2) >
inline ScriptToNativeCallResult
hybridConstReturn1Param2(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, ARG_1 arg1, ARG_2)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 3); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -1);
		lua_pop(L, 2); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(arg1, arg2);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn1Param2 */
template<typename CLASS, typename RET_1, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(ARG_1, ARG_2) const>
inline ScriptToNativeCallResult
hybridMember1Param2(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, ARG_1 arg1, ARG_2)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 3); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -1);
		lua_pop(L, 2); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(arg1, arg2);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn1Param3 */
template<typename CLASS, typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
phybridConstReturn1Param3(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, ARG_1 arg1, ARG_2, ARG_3)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 4))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -1);
			lua_pop(L, 2); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(arg1, arg2, arg3);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn1Param3

/** phybridConstReturn1Param3 */
template<typename CLASS, typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(ARG_1, ARG_2, ARG_3) const>
inline ScriptToNativeCallResult
phybridMember1Param3(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, ARG_1 arg1, ARG_2, ARG_3)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 4))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -1);
			lua_pop(L, 2); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(arg1, arg2, arg3);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn1Param3

/** hybridMemberReturn1Param3 */
template<typename CLASS, typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
hybridConstReturn1Param3(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, ARG_1 arg1, ARG_2, ARG_3)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 4); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -1);
		lua_pop(L, 2); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(arg1, arg2, arg3);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn1Param3 */
template<typename CLASS, typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(ARG_1, ARG_2, ARG_3) const>
inline ScriptToNativeCallResult
hybridMember1Param3(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, ARG_1 arg1, ARG_2, ARG_3)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 4); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -1);
		lua_pop(L, 2); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(arg1, arg2, arg3);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn1Param4 */
template<typename CLASS, typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
phybridConstReturn1Param4(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 5))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -1);
			lua_pop(L, 2); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(arg1, arg2, arg3, arg4);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn1Param4

/** phybridConstReturn1Param4 */
template<typename CLASS, typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4) const>
inline ScriptToNativeCallResult
phybridMember1Param4(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 5))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -1);
			lua_pop(L, 2); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(arg1, arg2, arg3, arg4);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn1Param4

/** hybridMemberReturn1Param4 */
template<typename CLASS, typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
hybridConstReturn1Param4(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 5); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -1);
		lua_pop(L, 2); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(arg1, arg2, arg3, arg4);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn1Param4 */
template<typename CLASS, typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4) const>
inline ScriptToNativeCallResult
hybridMember1Param4(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 5); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -1);
		lua_pop(L, 2); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(arg1, arg2, arg3, arg4);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn1Param5 */
template<typename CLASS, typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
phybridConstReturn1Param5(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 6))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -1);
			lua_pop(L, 2); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(arg1, arg2, arg3, arg4, arg5);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn1Param5

/** phybridConstReturn1Param5 */
template<typename CLASS, typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) const>
inline ScriptToNativeCallResult
phybridMember1Param5(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 6))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -1);
			lua_pop(L, 2); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(arg1, arg2, arg3, arg4, arg5);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn1Param5

/** hybridMemberReturn1Param5 */
template<typename CLASS, typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
hybridConstReturn1Param5(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 6); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -1);
		lua_pop(L, 2); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(arg1, arg2, arg3, arg4, arg5);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn1Param5 */
template<typename CLASS, typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) const>
inline ScriptToNativeCallResult
hybridMember1Param5(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 6); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -1);
		lua_pop(L, 2); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(arg1, arg2, arg3, arg4, arg5);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn1Param6 */
template<typename CLASS, typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
phybridConstReturn1Param6(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 7))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -1);
			lua_pop(L, 2); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn1Param6

/** phybridConstReturn1Param6 */
template<typename CLASS, typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) const>
inline ScriptToNativeCallResult
phybridMember1Param6(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 7))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -1);
			lua_pop(L, 2); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn1Param6

/** hybridMemberReturn1Param6 */
template<typename CLASS, typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
hybridConstReturn1Param6(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 7); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -1);
		lua_pop(L, 2); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn1Param6 */
template<typename CLASS, typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) const>
inline ScriptToNativeCallResult
hybridMember1Param6(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 7); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -1);
		lua_pop(L, 2); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn1Param7 */
template<typename CLASS, typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
phybridConstReturn1Param7(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 8))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -1);
			lua_pop(L, 2); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn1Param7

/** phybridConstReturn1Param7 */
template<typename CLASS, typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) const>
inline ScriptToNativeCallResult
phybridMember1Param7(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 8))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -1);
			lua_pop(L, 2); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn1Param7

/** hybridMemberReturn1Param7 */
template<typename CLASS, typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
hybridConstReturn1Param7(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 8); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -1);
		lua_pop(L, 2); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn1Param7 */
template<typename CLASS, typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) const>
inline ScriptToNativeCallResult
hybridMember1Param7(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 8); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -1);
		lua_pop(L, 2); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn1Param8 */
template<typename CLASS, typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
phybridConstReturn1Param8(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 9))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -1);
			lua_pop(L, 2); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn1Param8

/** phybridConstReturn1Param8 */
template<typename CLASS, typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) const>
inline ScriptToNativeCallResult
phybridMember1Param8(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 9))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -1);
			lua_pop(L, 2); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn1Param8

/** hybridMemberReturn1Param8 */
template<typename CLASS, typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
hybridConstReturn1Param8(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 9); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -1);
		lua_pop(L, 2); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn1Param8 */
template<typename CLASS, typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) const>
inline ScriptToNativeCallResult
hybridMember1Param8(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 9); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -1);
		lua_pop(L, 2); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn1Param9 */
template<typename CLASS, typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
phybridConstReturn1Param9(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		push(L, arg9);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 10))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -1);
			lua_pop(L, 2); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn1Param9

/** phybridConstReturn1Param9 */
template<typename CLASS, typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) const>
inline ScriptToNativeCallResult
phybridMember1Param9(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		push(L, arg9);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 10))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -1);
			lua_pop(L, 2); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn1Param9

/** hybridMemberReturn1Param9 */
template<typename CLASS, typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
hybridConstReturn1Param9(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		push(L, arg9);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 10); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -1);
		lua_pop(L, 2); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn1Param9 */
template<typename CLASS, typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) const>
inline ScriptToNativeCallResult
hybridMember1Param9(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		push(L, arg9);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 10); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -1);
		lua_pop(L, 2); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn1Param10 */
template<typename CLASS, typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
phybridConstReturn1Param10(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
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
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 11))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -1);
			lua_pop(L, 2); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn1Param10

/** phybridConstReturn1Param10 */
template<typename CLASS, typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) const>
inline ScriptToNativeCallResult
phybridMember1Param10(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
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
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 11))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -1);
			lua_pop(L, 2); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn1Param10

/** hybridMemberReturn1Param10 */
template<typename CLASS, typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
hybridConstReturn1Param10(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
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
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 11); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -1);
		lua_pop(L, 2); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn1Param10 */
template<typename CLASS, typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) const>
inline ScriptToNativeCallResult
hybridMember1Param10(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
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
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 11); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -1);
		lua_pop(L, 2); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn2Param0 */
template<typename CLASS, typename RET_1, typename RET_2, RET_1 (CLASS::* function)(RET_2&) >
inline ScriptToNativeCallResult
phybridConstReturn2Param0(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 1))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -2);
			ret2 = to<RET_2>(L, -1);
			lua_pop(L, 3); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn2Param0

/** phybridConstReturn2Param0 */
template<typename CLASS, typename RET_1, typename RET_2, RET_1 (CLASS::* function)(RET_2&) const>
inline ScriptToNativeCallResult
phybridMember2Param0(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 1))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -2);
			ret2 = to<RET_2>(L, -1);
			lua_pop(L, 3); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn2Param0

/** hybridMemberReturn2Param0 */
template<typename CLASS, typename RET_1, typename RET_2, RET_1 (CLASS::* function)(RET_2&) >
inline ScriptToNativeCallResult
hybridConstReturn2Param0(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 1); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -2);
		ret2 = to<RET_2>(L, -1);
		lua_pop(L, 3); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn2Param0 */
template<typename CLASS, typename RET_1, typename RET_2, RET_1 (CLASS::* function)(RET_2&) const>
inline ScriptToNativeCallResult
hybridMember2Param0(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 1); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -2);
		ret2 = to<RET_2>(L, -1);
		lua_pop(L, 3); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn2Param1 */
template<typename CLASS, typename RET_1, typename RET_2, typename ARG_1, RET_1 (CLASS::* function)(RET_2&, ARG_1) >
inline ScriptToNativeCallResult
phybridConstReturn2Param1(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, ARG_1 arg1)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 2))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -2);
			ret2 = to<RET_2>(L, -1);
			lua_pop(L, 3); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, arg1);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn2Param1

/** phybridConstReturn2Param1 */
template<typename CLASS, typename RET_1, typename RET_2, typename ARG_1, RET_1 (CLASS::* function)(RET_2&, ARG_1) const>
inline ScriptToNativeCallResult
phybridMember2Param1(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, ARG_1 arg1)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 2))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -2);
			ret2 = to<RET_2>(L, -1);
			lua_pop(L, 3); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, arg1);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn2Param1

/** hybridMemberReturn2Param1 */
template<typename CLASS, typename RET_1, typename RET_2, typename ARG_1, RET_1 (CLASS::* function)(RET_2&, ARG_1) >
inline ScriptToNativeCallResult
hybridConstReturn2Param1(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, ARG_1 arg1)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 2); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -2);
		ret2 = to<RET_2>(L, -1);
		lua_pop(L, 3); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, arg1);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn2Param1 */
template<typename CLASS, typename RET_1, typename RET_2, typename ARG_1, RET_1 (CLASS::* function)(RET_2&, ARG_1) const>
inline ScriptToNativeCallResult
hybridMember2Param1(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, ARG_1 arg1)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 2); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -2);
		ret2 = to<RET_2>(L, -1);
		lua_pop(L, 3); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, arg1);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn2Param2 */
template<typename CLASS, typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(RET_2&, ARG_1, ARG_2) >
inline ScriptToNativeCallResult
phybridConstReturn2Param2(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, ARG_1 arg1, ARG_2)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 3))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -2);
			ret2 = to<RET_2>(L, -1);
			lua_pop(L, 3); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, arg1, arg2);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn2Param2

/** phybridConstReturn2Param2 */
template<typename CLASS, typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(RET_2&, ARG_1, ARG_2) const>
inline ScriptToNativeCallResult
phybridMember2Param2(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, ARG_1 arg1, ARG_2)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 3))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -2);
			ret2 = to<RET_2>(L, -1);
			lua_pop(L, 3); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, arg1, arg2);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn2Param2

/** hybridMemberReturn2Param2 */
template<typename CLASS, typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(RET_2&, ARG_1, ARG_2) >
inline ScriptToNativeCallResult
hybridConstReturn2Param2(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, ARG_1 arg1, ARG_2)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 3); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -2);
		ret2 = to<RET_2>(L, -1);
		lua_pop(L, 3); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, arg1, arg2);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn2Param2 */
template<typename CLASS, typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(RET_2&, ARG_1, ARG_2) const>
inline ScriptToNativeCallResult
hybridMember2Param2(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, ARG_1 arg1, ARG_2)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 3); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -2);
		ret2 = to<RET_2>(L, -1);
		lua_pop(L, 3); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, arg1, arg2);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn2Param3 */
template<typename CLASS, typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(RET_2&, ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
phybridConstReturn2Param3(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, ARG_1 arg1, ARG_2, ARG_3)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 4))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -2);
			ret2 = to<RET_2>(L, -1);
			lua_pop(L, 3); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, arg1, arg2, arg3);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn2Param3

/** phybridConstReturn2Param3 */
template<typename CLASS, typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(RET_2&, ARG_1, ARG_2, ARG_3) const>
inline ScriptToNativeCallResult
phybridMember2Param3(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, ARG_1 arg1, ARG_2, ARG_3)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 4))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -2);
			ret2 = to<RET_2>(L, -1);
			lua_pop(L, 3); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, arg1, arg2, arg3);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn2Param3

/** hybridMemberReturn2Param3 */
template<typename CLASS, typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(RET_2&, ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
hybridConstReturn2Param3(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, ARG_1 arg1, ARG_2, ARG_3)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 4); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -2);
		ret2 = to<RET_2>(L, -1);
		lua_pop(L, 3); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, arg1, arg2, arg3);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn2Param3 */
template<typename CLASS, typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(RET_2&, ARG_1, ARG_2, ARG_3) const>
inline ScriptToNativeCallResult
hybridMember2Param3(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, ARG_1 arg1, ARG_2, ARG_3)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 4); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -2);
		ret2 = to<RET_2>(L, -1);
		lua_pop(L, 3); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, arg1, arg2, arg3);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn2Param4 */
template<typename CLASS, typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
phybridConstReturn2Param4(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 5))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -2);
			ret2 = to<RET_2>(L, -1);
			lua_pop(L, 3); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, arg1, arg2, arg3, arg4);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn2Param4

/** phybridConstReturn2Param4 */
template<typename CLASS, typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4) const>
inline ScriptToNativeCallResult
phybridMember2Param4(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 5))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -2);
			ret2 = to<RET_2>(L, -1);
			lua_pop(L, 3); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, arg1, arg2, arg3, arg4);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn2Param4

/** hybridMemberReturn2Param4 */
template<typename CLASS, typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
hybridConstReturn2Param4(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 5); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -2);
		ret2 = to<RET_2>(L, -1);
		lua_pop(L, 3); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, arg1, arg2, arg3, arg4);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn2Param4 */
template<typename CLASS, typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4) const>
inline ScriptToNativeCallResult
hybridMember2Param4(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 5); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -2);
		ret2 = to<RET_2>(L, -1);
		lua_pop(L, 3); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, arg1, arg2, arg3, arg4);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn2Param5 */
template<typename CLASS, typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
phybridConstReturn2Param5(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 6))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -2);
			ret2 = to<RET_2>(L, -1);
			lua_pop(L, 3); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, arg1, arg2, arg3, arg4, arg5);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn2Param5

/** phybridConstReturn2Param5 */
template<typename CLASS, typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) const>
inline ScriptToNativeCallResult
phybridMember2Param5(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 6))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -2);
			ret2 = to<RET_2>(L, -1);
			lua_pop(L, 3); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, arg1, arg2, arg3, arg4, arg5);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn2Param5

/** hybridMemberReturn2Param5 */
template<typename CLASS, typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
hybridConstReturn2Param5(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 6); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -2);
		ret2 = to<RET_2>(L, -1);
		lua_pop(L, 3); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, arg1, arg2, arg3, arg4, arg5);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn2Param5 */
template<typename CLASS, typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) const>
inline ScriptToNativeCallResult
hybridMember2Param5(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 6); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -2);
		ret2 = to<RET_2>(L, -1);
		lua_pop(L, 3); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, arg1, arg2, arg3, arg4, arg5);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn2Param6 */
template<typename CLASS, typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
phybridConstReturn2Param6(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 7))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -2);
			ret2 = to<RET_2>(L, -1);
			lua_pop(L, 3); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn2Param6

/** phybridConstReturn2Param6 */
template<typename CLASS, typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) const>
inline ScriptToNativeCallResult
phybridMember2Param6(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 7))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -2);
			ret2 = to<RET_2>(L, -1);
			lua_pop(L, 3); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn2Param6

/** hybridMemberReturn2Param6 */
template<typename CLASS, typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
hybridConstReturn2Param6(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 7); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -2);
		ret2 = to<RET_2>(L, -1);
		lua_pop(L, 3); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn2Param6 */
template<typename CLASS, typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) const>
inline ScriptToNativeCallResult
hybridMember2Param6(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 7); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -2);
		ret2 = to<RET_2>(L, -1);
		lua_pop(L, 3); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn2Param7 */
template<typename CLASS, typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
phybridConstReturn2Param7(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 8))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -2);
			ret2 = to<RET_2>(L, -1);
			lua_pop(L, 3); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn2Param7

/** phybridConstReturn2Param7 */
template<typename CLASS, typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) const>
inline ScriptToNativeCallResult
phybridMember2Param7(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 8))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -2);
			ret2 = to<RET_2>(L, -1);
			lua_pop(L, 3); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn2Param7

/** hybridMemberReturn2Param7 */
template<typename CLASS, typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
hybridConstReturn2Param7(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 8); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -2);
		ret2 = to<RET_2>(L, -1);
		lua_pop(L, 3); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn2Param7 */
template<typename CLASS, typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) const>
inline ScriptToNativeCallResult
hybridMember2Param7(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 8); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -2);
		ret2 = to<RET_2>(L, -1);
		lua_pop(L, 3); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn2Param8 */
template<typename CLASS, typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
phybridConstReturn2Param8(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 9))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -2);
			ret2 = to<RET_2>(L, -1);
			lua_pop(L, 3); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn2Param8

/** phybridConstReturn2Param8 */
template<typename CLASS, typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) const>
inline ScriptToNativeCallResult
phybridMember2Param8(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 9))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -2);
			ret2 = to<RET_2>(L, -1);
			lua_pop(L, 3); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn2Param8

/** hybridMemberReturn2Param8 */
template<typename CLASS, typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
hybridConstReturn2Param8(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 9); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -2);
		ret2 = to<RET_2>(L, -1);
		lua_pop(L, 3); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn2Param8 */
template<typename CLASS, typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) const>
inline ScriptToNativeCallResult
hybridMember2Param8(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 9); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -2);
		ret2 = to<RET_2>(L, -1);
		lua_pop(L, 3); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn2Param9 */
template<typename CLASS, typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
phybridConstReturn2Param9(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		push(L, arg9);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 10))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -2);
			ret2 = to<RET_2>(L, -1);
			lua_pop(L, 3); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn2Param9

/** phybridConstReturn2Param9 */
template<typename CLASS, typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) const>
inline ScriptToNativeCallResult
phybridMember2Param9(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		push(L, arg9);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 10))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -2);
			ret2 = to<RET_2>(L, -1);
			lua_pop(L, 3); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn2Param9

/** hybridMemberReturn2Param9 */
template<typename CLASS, typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
hybridConstReturn2Param9(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		push(L, arg9);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 10); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -2);
		ret2 = to<RET_2>(L, -1);
		lua_pop(L, 3); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn2Param9 */
template<typename CLASS, typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) const>
inline ScriptToNativeCallResult
hybridMember2Param9(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		push(L, arg9);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 10); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -2);
		ret2 = to<RET_2>(L, -1);
		lua_pop(L, 3); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn2Param10 */
template<typename CLASS, typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
phybridConstReturn2Param10(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
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
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 11))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -2);
			ret2 = to<RET_2>(L, -1);
			lua_pop(L, 3); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn2Param10

/** phybridConstReturn2Param10 */
template<typename CLASS, typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) const>
inline ScriptToNativeCallResult
phybridMember2Param10(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
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
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 11))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -2);
			ret2 = to<RET_2>(L, -1);
			lua_pop(L, 3); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn2Param10

/** hybridMemberReturn2Param10 */
template<typename CLASS, typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
hybridConstReturn2Param10(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
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
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 11); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -2);
		ret2 = to<RET_2>(L, -1);
		lua_pop(L, 3); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn2Param10 */
template<typename CLASS, typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) const>
inline ScriptToNativeCallResult
hybridMember2Param10(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
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
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 11); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -2);
		ret2 = to<RET_2>(L, -1);
		lua_pop(L, 3); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn3Param0 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, RET_1 (CLASS::* function)(RET_2&, RET_3&) >
inline ScriptToNativeCallResult
phybridConstReturn3Param0(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 1))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -3);
			ret2 = to<RET_2>(L, -2);
			ret3 = to<RET_3>(L, -1);
			lua_pop(L, 4); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn3Param0

/** phybridConstReturn3Param0 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, RET_1 (CLASS::* function)(RET_2&, RET_3&) const>
inline ScriptToNativeCallResult
phybridMember3Param0(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 1))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -3);
			ret2 = to<RET_2>(L, -2);
			ret3 = to<RET_3>(L, -1);
			lua_pop(L, 4); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn3Param0

/** hybridMemberReturn3Param0 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, RET_1 (CLASS::* function)(RET_2&, RET_3&) >
inline ScriptToNativeCallResult
hybridConstReturn3Param0(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 1); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -3);
		ret2 = to<RET_2>(L, -2);
		ret3 = to<RET_3>(L, -1);
		lua_pop(L, 4); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn3Param0 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, RET_1 (CLASS::* function)(RET_2&, RET_3&) const>
inline ScriptToNativeCallResult
hybridMember3Param0(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 1); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -3);
		ret2 = to<RET_2>(L, -2);
		ret3 = to<RET_3>(L, -1);
		lua_pop(L, 4); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn3Param1 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1) >
inline ScriptToNativeCallResult
phybridConstReturn3Param1(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, ARG_1 arg1)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 2))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -3);
			ret2 = to<RET_2>(L, -2);
			ret3 = to<RET_3>(L, -1);
			lua_pop(L, 4); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, arg1);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn3Param1

/** phybridConstReturn3Param1 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1) const>
inline ScriptToNativeCallResult
phybridMember3Param1(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, ARG_1 arg1)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 2))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -3);
			ret2 = to<RET_2>(L, -2);
			ret3 = to<RET_3>(L, -1);
			lua_pop(L, 4); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, arg1);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn3Param1

/** hybridMemberReturn3Param1 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1) >
inline ScriptToNativeCallResult
hybridConstReturn3Param1(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, ARG_1 arg1)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 2); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -3);
		ret2 = to<RET_2>(L, -2);
		ret3 = to<RET_3>(L, -1);
		lua_pop(L, 4); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, arg1);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn3Param1 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1) const>
inline ScriptToNativeCallResult
hybridMember3Param1(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, ARG_1 arg1)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 2); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -3);
		ret2 = to<RET_2>(L, -2);
		ret3 = to<RET_3>(L, -1);
		lua_pop(L, 4); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, arg1);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn3Param2 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1, ARG_2) >
inline ScriptToNativeCallResult
phybridConstReturn3Param2(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, ARG_1 arg1, ARG_2)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 3))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -3);
			ret2 = to<RET_2>(L, -2);
			ret3 = to<RET_3>(L, -1);
			lua_pop(L, 4); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, arg1, arg2);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn3Param2

/** phybridConstReturn3Param2 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1, ARG_2) const>
inline ScriptToNativeCallResult
phybridMember3Param2(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, ARG_1 arg1, ARG_2)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 3))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -3);
			ret2 = to<RET_2>(L, -2);
			ret3 = to<RET_3>(L, -1);
			lua_pop(L, 4); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, arg1, arg2);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn3Param2

/** hybridMemberReturn3Param2 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1, ARG_2) >
inline ScriptToNativeCallResult
hybridConstReturn3Param2(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, ARG_1 arg1, ARG_2)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 3); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -3);
		ret2 = to<RET_2>(L, -2);
		ret3 = to<RET_3>(L, -1);
		lua_pop(L, 4); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, arg1, arg2);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn3Param2 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1, ARG_2) const>
inline ScriptToNativeCallResult
hybridMember3Param2(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, ARG_1 arg1, ARG_2)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 3); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -3);
		ret2 = to<RET_2>(L, -2);
		ret3 = to<RET_3>(L, -1);
		lua_pop(L, 4); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, arg1, arg2);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn3Param3 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
phybridConstReturn3Param3(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, ARG_1 arg1, ARG_2, ARG_3)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 4))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -3);
			ret2 = to<RET_2>(L, -2);
			ret3 = to<RET_3>(L, -1);
			lua_pop(L, 4); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, arg1, arg2, arg3);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn3Param3

/** phybridConstReturn3Param3 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3) const>
inline ScriptToNativeCallResult
phybridMember3Param3(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, ARG_1 arg1, ARG_2, ARG_3)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 4))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -3);
			ret2 = to<RET_2>(L, -2);
			ret3 = to<RET_3>(L, -1);
			lua_pop(L, 4); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, arg1, arg2, arg3);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn3Param3

/** hybridMemberReturn3Param3 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
hybridConstReturn3Param3(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, ARG_1 arg1, ARG_2, ARG_3)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 4); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -3);
		ret2 = to<RET_2>(L, -2);
		ret3 = to<RET_3>(L, -1);
		lua_pop(L, 4); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, arg1, arg2, arg3);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn3Param3 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3) const>
inline ScriptToNativeCallResult
hybridMember3Param3(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, ARG_1 arg1, ARG_2, ARG_3)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 4); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -3);
		ret2 = to<RET_2>(L, -2);
		ret3 = to<RET_3>(L, -1);
		lua_pop(L, 4); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, arg1, arg2, arg3);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn3Param4 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
phybridConstReturn3Param4(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 5))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -3);
			ret2 = to<RET_2>(L, -2);
			ret3 = to<RET_3>(L, -1);
			lua_pop(L, 4); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, arg1, arg2, arg3, arg4);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn3Param4

/** phybridConstReturn3Param4 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4) const>
inline ScriptToNativeCallResult
phybridMember3Param4(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 5))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -3);
			ret2 = to<RET_2>(L, -2);
			ret3 = to<RET_3>(L, -1);
			lua_pop(L, 4); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, arg1, arg2, arg3, arg4);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn3Param4

/** hybridMemberReturn3Param4 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
hybridConstReturn3Param4(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 5); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -3);
		ret2 = to<RET_2>(L, -2);
		ret3 = to<RET_3>(L, -1);
		lua_pop(L, 4); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, arg1, arg2, arg3, arg4);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn3Param4 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4) const>
inline ScriptToNativeCallResult
hybridMember3Param4(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 5); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -3);
		ret2 = to<RET_2>(L, -2);
		ret3 = to<RET_3>(L, -1);
		lua_pop(L, 4); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, arg1, arg2, arg3, arg4);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn3Param5 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
phybridConstReturn3Param5(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 6))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -3);
			ret2 = to<RET_2>(L, -2);
			ret3 = to<RET_3>(L, -1);
			lua_pop(L, 4); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, arg1, arg2, arg3, arg4, arg5);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn3Param5

/** phybridConstReturn3Param5 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) const>
inline ScriptToNativeCallResult
phybridMember3Param5(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 6))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -3);
			ret2 = to<RET_2>(L, -2);
			ret3 = to<RET_3>(L, -1);
			lua_pop(L, 4); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, arg1, arg2, arg3, arg4, arg5);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn3Param5

/** hybridMemberReturn3Param5 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
hybridConstReturn3Param5(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 6); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -3);
		ret2 = to<RET_2>(L, -2);
		ret3 = to<RET_3>(L, -1);
		lua_pop(L, 4); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, arg1, arg2, arg3, arg4, arg5);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn3Param5 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) const>
inline ScriptToNativeCallResult
hybridMember3Param5(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 6); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -3);
		ret2 = to<RET_2>(L, -2);
		ret3 = to<RET_3>(L, -1);
		lua_pop(L, 4); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, arg1, arg2, arg3, arg4, arg5);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn3Param6 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
phybridConstReturn3Param6(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 7))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -3);
			ret2 = to<RET_2>(L, -2);
			ret3 = to<RET_3>(L, -1);
			lua_pop(L, 4); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn3Param6

/** phybridConstReturn3Param6 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) const>
inline ScriptToNativeCallResult
phybridMember3Param6(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 7))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -3);
			ret2 = to<RET_2>(L, -2);
			ret3 = to<RET_3>(L, -1);
			lua_pop(L, 4); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn3Param6

/** hybridMemberReturn3Param6 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
hybridConstReturn3Param6(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 7); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -3);
		ret2 = to<RET_2>(L, -2);
		ret3 = to<RET_3>(L, -1);
		lua_pop(L, 4); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn3Param6 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) const>
inline ScriptToNativeCallResult
hybridMember3Param6(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 7); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -3);
		ret2 = to<RET_2>(L, -2);
		ret3 = to<RET_3>(L, -1);
		lua_pop(L, 4); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn3Param7 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
phybridConstReturn3Param7(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 8))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -3);
			ret2 = to<RET_2>(L, -2);
			ret3 = to<RET_3>(L, -1);
			lua_pop(L, 4); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn3Param7

/** phybridConstReturn3Param7 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) const>
inline ScriptToNativeCallResult
phybridMember3Param7(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 8))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -3);
			ret2 = to<RET_2>(L, -2);
			ret3 = to<RET_3>(L, -1);
			lua_pop(L, 4); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn3Param7

/** hybridMemberReturn3Param7 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
hybridConstReturn3Param7(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 8); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -3);
		ret2 = to<RET_2>(L, -2);
		ret3 = to<RET_3>(L, -1);
		lua_pop(L, 4); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn3Param7 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) const>
inline ScriptToNativeCallResult
hybridMember3Param7(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 8); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -3);
		ret2 = to<RET_2>(L, -2);
		ret3 = to<RET_3>(L, -1);
		lua_pop(L, 4); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn3Param8 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
phybridConstReturn3Param8(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 9))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -3);
			ret2 = to<RET_2>(L, -2);
			ret3 = to<RET_3>(L, -1);
			lua_pop(L, 4); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn3Param8

/** phybridConstReturn3Param8 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) const>
inline ScriptToNativeCallResult
phybridMember3Param8(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 9))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -3);
			ret2 = to<RET_2>(L, -2);
			ret3 = to<RET_3>(L, -1);
			lua_pop(L, 4); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn3Param8

/** hybridMemberReturn3Param8 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
hybridConstReturn3Param8(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 9); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -3);
		ret2 = to<RET_2>(L, -2);
		ret3 = to<RET_3>(L, -1);
		lua_pop(L, 4); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn3Param8 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) const>
inline ScriptToNativeCallResult
hybridMember3Param8(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 9); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -3);
		ret2 = to<RET_2>(L, -2);
		ret3 = to<RET_3>(L, -1);
		lua_pop(L, 4); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn3Param9 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
phybridConstReturn3Param9(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		push(L, arg9);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 10))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -3);
			ret2 = to<RET_2>(L, -2);
			ret3 = to<RET_3>(L, -1);
			lua_pop(L, 4); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn3Param9

/** phybridConstReturn3Param9 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) const>
inline ScriptToNativeCallResult
phybridMember3Param9(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		push(L, arg9);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 10))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -3);
			ret2 = to<RET_2>(L, -2);
			ret3 = to<RET_3>(L, -1);
			lua_pop(L, 4); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn3Param9

/** hybridMemberReturn3Param9 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
hybridConstReturn3Param9(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		push(L, arg9);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 10); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -3);
		ret2 = to<RET_2>(L, -2);
		ret3 = to<RET_3>(L, -1);
		lua_pop(L, 4); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn3Param9 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) const>
inline ScriptToNativeCallResult
hybridMember3Param9(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		push(L, arg9);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 10); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -3);
		ret2 = to<RET_2>(L, -2);
		ret3 = to<RET_3>(L, -1);
		lua_pop(L, 4); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn3Param10 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
phybridConstReturn3Param10(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
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
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 11))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -3);
			ret2 = to<RET_2>(L, -2);
			ret3 = to<RET_3>(L, -1);
			lua_pop(L, 4); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn3Param10

/** phybridConstReturn3Param10 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) const>
inline ScriptToNativeCallResult
phybridMember3Param10(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
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
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 11))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -3);
			ret2 = to<RET_2>(L, -2);
			ret3 = to<RET_3>(L, -1);
			lua_pop(L, 4); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn3Param10

/** hybridMemberReturn3Param10 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
hybridConstReturn3Param10(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
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
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 11); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -3);
		ret2 = to<RET_2>(L, -2);
		ret3 = to<RET_3>(L, -1);
		lua_pop(L, 4); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn3Param10 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) const>
inline ScriptToNativeCallResult
hybridMember3Param10(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
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
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 11); 
		/*s: object (return values) */ 
		ret1 = to<RET_1>(L, -3);
		ret2 = to<RET_2>(L, -2);
		ret3 = to<RET_3>(L, -1);
		lua_pop(L, 4); 
		/*s: */ 
		return lua_extension::functionSuccess; 
	} 
	else 
	{	/*s: module nil */ 
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn4Param0 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&) >
inline ScriptToNativeCallResult
phybridConstReturn4Param0(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 1))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -4);
			ret2 = to<RET_2>(L, -3);
			ret3 = to<RET_3>(L, -2);
			ret4 = to<RET_4>(L, -1);
			lua_pop(L, 5); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn4Param0

/** phybridConstReturn4Param0 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&) const>
inline ScriptToNativeCallResult
phybridMember4Param0(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 1))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -4);
			ret2 = to<RET_2>(L, -3);
			ret3 = to<RET_3>(L, -2);
			ret4 = to<RET_4>(L, -1);
			lua_pop(L, 5); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn4Param0

/** hybridMemberReturn4Param0 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&) >
inline ScriptToNativeCallResult
hybridConstReturn4Param0(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 1); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn4Param0 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&) const>
inline ScriptToNativeCallResult
hybridMember4Param0(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 1); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn4Param1 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1) >
inline ScriptToNativeCallResult
phybridConstReturn4Param1(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, ARG_1 arg1)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 2))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -4);
			ret2 = to<RET_2>(L, -3);
			ret3 = to<RET_3>(L, -2);
			ret4 = to<RET_4>(L, -1);
			lua_pop(L, 5); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, arg1);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn4Param1

/** phybridConstReturn4Param1 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1) const>
inline ScriptToNativeCallResult
phybridMember4Param1(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, ARG_1 arg1)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 2))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -4);
			ret2 = to<RET_2>(L, -3);
			ret3 = to<RET_3>(L, -2);
			ret4 = to<RET_4>(L, -1);
			lua_pop(L, 5); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, arg1);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn4Param1

/** hybridMemberReturn4Param1 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1) >
inline ScriptToNativeCallResult
hybridConstReturn4Param1(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, ARG_1 arg1)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 2); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, arg1);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn4Param1 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1) const>
inline ScriptToNativeCallResult
hybridMember4Param1(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, ARG_1 arg1)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 2); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, arg1);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn4Param2 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2) >
inline ScriptToNativeCallResult
phybridConstReturn4Param2(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, ARG_1 arg1, ARG_2)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 3))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -4);
			ret2 = to<RET_2>(L, -3);
			ret3 = to<RET_3>(L, -2);
			ret4 = to<RET_4>(L, -1);
			lua_pop(L, 5); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, arg1, arg2);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn4Param2

/** phybridConstReturn4Param2 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2) const>
inline ScriptToNativeCallResult
phybridMember4Param2(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, ARG_1 arg1, ARG_2)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 3))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -4);
			ret2 = to<RET_2>(L, -3);
			ret3 = to<RET_3>(L, -2);
			ret4 = to<RET_4>(L, -1);
			lua_pop(L, 5); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, arg1, arg2);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn4Param2

/** hybridMemberReturn4Param2 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2) >
inline ScriptToNativeCallResult
hybridConstReturn4Param2(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, ARG_1 arg1, ARG_2)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 3); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, arg1, arg2);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn4Param2 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2) const>
inline ScriptToNativeCallResult
hybridMember4Param2(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, ARG_1 arg1, ARG_2)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 3); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, arg1, arg2);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn4Param3 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
phybridConstReturn4Param3(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, ARG_1 arg1, ARG_2, ARG_3)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 4))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -4);
			ret2 = to<RET_2>(L, -3);
			ret3 = to<RET_3>(L, -2);
			ret4 = to<RET_4>(L, -1);
			lua_pop(L, 5); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn4Param3

/** phybridConstReturn4Param3 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3) const>
inline ScriptToNativeCallResult
phybridMember4Param3(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, ARG_1 arg1, ARG_2, ARG_3)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 4))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -4);
			ret2 = to<RET_2>(L, -3);
			ret3 = to<RET_3>(L, -2);
			ret4 = to<RET_4>(L, -1);
			lua_pop(L, 5); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn4Param3

/** hybridMemberReturn4Param3 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
hybridConstReturn4Param3(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, ARG_1 arg1, ARG_2, ARG_3)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 4); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn4Param3 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3) const>
inline ScriptToNativeCallResult
hybridMember4Param3(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, ARG_1 arg1, ARG_2, ARG_3)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 4); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn4Param4 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
phybridConstReturn4Param4(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 5))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -4);
			ret2 = to<RET_2>(L, -3);
			ret3 = to<RET_3>(L, -2);
			ret4 = to<RET_4>(L, -1);
			lua_pop(L, 5); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3, arg4);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn4Param4

/** phybridConstReturn4Param4 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4) const>
inline ScriptToNativeCallResult
phybridMember4Param4(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 5))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -4);
			ret2 = to<RET_2>(L, -3);
			ret3 = to<RET_3>(L, -2);
			ret4 = to<RET_4>(L, -1);
			lua_pop(L, 5); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3, arg4);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn4Param4

/** hybridMemberReturn4Param4 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
hybridConstReturn4Param4(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 5); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3, arg4);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn4Param4 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4) const>
inline ScriptToNativeCallResult
hybridMember4Param4(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 5); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3, arg4);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn4Param5 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
phybridConstReturn4Param5(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 6))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -4);
			ret2 = to<RET_2>(L, -3);
			ret3 = to<RET_3>(L, -2);
			ret4 = to<RET_4>(L, -1);
			lua_pop(L, 5); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3, arg4, arg5);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn4Param5

/** phybridConstReturn4Param5 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) const>
inline ScriptToNativeCallResult
phybridMember4Param5(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 6))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -4);
			ret2 = to<RET_2>(L, -3);
			ret3 = to<RET_3>(L, -2);
			ret4 = to<RET_4>(L, -1);
			lua_pop(L, 5); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3, arg4, arg5);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn4Param5

/** hybridMemberReturn4Param5 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
hybridConstReturn4Param5(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 6); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3, arg4, arg5);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn4Param5 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) const>
inline ScriptToNativeCallResult
hybridMember4Param5(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 6); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3, arg4, arg5);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn4Param6 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
phybridConstReturn4Param6(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 7))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -4);
			ret2 = to<RET_2>(L, -3);
			ret3 = to<RET_3>(L, -2);
			ret4 = to<RET_4>(L, -1);
			lua_pop(L, 5); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn4Param6

/** phybridConstReturn4Param6 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) const>
inline ScriptToNativeCallResult
phybridMember4Param6(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 7))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -4);
			ret2 = to<RET_2>(L, -3);
			ret3 = to<RET_3>(L, -2);
			ret4 = to<RET_4>(L, -1);
			lua_pop(L, 5); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn4Param6

/** hybridMemberReturn4Param6 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
hybridConstReturn4Param6(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 7); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn4Param6 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) const>
inline ScriptToNativeCallResult
hybridMember4Param6(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 7); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn4Param7 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
phybridConstReturn4Param7(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 8))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -4);
			ret2 = to<RET_2>(L, -3);
			ret3 = to<RET_3>(L, -2);
			ret4 = to<RET_4>(L, -1);
			lua_pop(L, 5); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn4Param7

/** phybridConstReturn4Param7 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) const>
inline ScriptToNativeCallResult
phybridMember4Param7(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 8))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -4);
			ret2 = to<RET_2>(L, -3);
			ret3 = to<RET_3>(L, -2);
			ret4 = to<RET_4>(L, -1);
			lua_pop(L, 5); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn4Param7

/** hybridMemberReturn4Param7 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
hybridConstReturn4Param7(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 8); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn4Param7 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) const>
inline ScriptToNativeCallResult
hybridMember4Param7(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 8); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn4Param8 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
phybridConstReturn4Param8(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 9))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -4);
			ret2 = to<RET_2>(L, -3);
			ret3 = to<RET_3>(L, -2);
			ret4 = to<RET_4>(L, -1);
			lua_pop(L, 5); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn4Param8

/** phybridConstReturn4Param8 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) const>
inline ScriptToNativeCallResult
phybridMember4Param8(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 9))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -4);
			ret2 = to<RET_2>(L, -3);
			ret3 = to<RET_3>(L, -2);
			ret4 = to<RET_4>(L, -1);
			lua_pop(L, 5); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn4Param8

/** hybridMemberReturn4Param8 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
hybridConstReturn4Param8(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 9); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn4Param8 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) const>
inline ScriptToNativeCallResult
hybridMember4Param8(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 9); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn4Param9 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
phybridConstReturn4Param9(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		push(L, arg9);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 10))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -4);
			ret2 = to<RET_2>(L, -3);
			ret3 = to<RET_3>(L, -2);
			ret4 = to<RET_4>(L, -1);
			lua_pop(L, 5); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn4Param9

/** phybridConstReturn4Param9 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) const>
inline ScriptToNativeCallResult
phybridMember4Param9(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		push(L, arg9);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 10))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -4);
			ret2 = to<RET_2>(L, -3);
			ret3 = to<RET_3>(L, -2);
			ret4 = to<RET_4>(L, -1);
			lua_pop(L, 5); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn4Param9

/** hybridMemberReturn4Param9 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
hybridConstReturn4Param9(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		push(L, arg9);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 10); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn4Param9 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) const>
inline ScriptToNativeCallResult
hybridMember4Param9(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		push(L, arg9);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 10); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn4Param10 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
phybridConstReturn4Param10(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
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
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 11))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -4);
			ret2 = to<RET_2>(L, -3);
			ret3 = to<RET_3>(L, -2);
			ret4 = to<RET_4>(L, -1);
			lua_pop(L, 5); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn4Param10

/** phybridConstReturn4Param10 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) const>
inline ScriptToNativeCallResult
phybridMember4Param10(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
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
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 11))
		{	/*s: object (return values) */ 
			ret1 = to<RET_1>(L, -4);
			ret2 = to<RET_2>(L, -3);
			ret3 = to<RET_3>(L, -2);
			ret4 = to<RET_4>(L, -1);
			lua_pop(L, 5); 
			/*s: */ 
			return lua_extension::functionSuccess; 
		} 
		else
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn4Param10

/** hybridMemberReturn4Param10 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
hybridConstReturn4Param10(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
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
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 11); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn4Param10 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) const>
inline ScriptToNativeCallResult
hybridMember4Param10(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
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
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 11); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn5Param0 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&) >
inline ScriptToNativeCallResult
phybridConstReturn5Param0(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 1))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn5Param0

/** phybridConstReturn5Param0 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&) const>
inline ScriptToNativeCallResult
phybridMember5Param0(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 1))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn5Param0

/** hybridMemberReturn5Param0 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&) >
inline ScriptToNativeCallResult
hybridConstReturn5Param0(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 1); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn5Param0 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&) const>
inline ScriptToNativeCallResult
hybridMember5Param0(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 1); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn5Param1 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1) >
inline ScriptToNativeCallResult
phybridConstReturn5Param1(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, ARG_1 arg1)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 2))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, arg1);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn5Param1

/** phybridConstReturn5Param1 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1) const>
inline ScriptToNativeCallResult
phybridMember5Param1(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, ARG_1 arg1)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 2))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, arg1);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn5Param1

/** hybridMemberReturn5Param1 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1) >
inline ScriptToNativeCallResult
hybridConstReturn5Param1(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, ARG_1 arg1)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 2); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, arg1);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn5Param1 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1) const>
inline ScriptToNativeCallResult
hybridMember5Param1(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, ARG_1 arg1)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 2); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, arg1);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn5Param2 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2) >
inline ScriptToNativeCallResult
phybridConstReturn5Param2(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, ARG_1 arg1, ARG_2)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 3))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn5Param2

/** phybridConstReturn5Param2 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2) const>
inline ScriptToNativeCallResult
phybridMember5Param2(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, ARG_1 arg1, ARG_2)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 3))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn5Param2

/** hybridMemberReturn5Param2 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2) >
inline ScriptToNativeCallResult
hybridConstReturn5Param2(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, ARG_1 arg1, ARG_2)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 3); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn5Param2 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2) const>
inline ScriptToNativeCallResult
hybridMember5Param2(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, ARG_1 arg1, ARG_2)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 3); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn5Param3 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
phybridConstReturn5Param3(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, ARG_1 arg1, ARG_2, ARG_3)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 4))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn5Param3

/** phybridConstReturn5Param3 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3) const>
inline ScriptToNativeCallResult
phybridMember5Param3(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, ARG_1 arg1, ARG_2, ARG_3)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 4))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn5Param3

/** hybridMemberReturn5Param3 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
hybridConstReturn5Param3(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, ARG_1 arg1, ARG_2, ARG_3)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 4); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn5Param3 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3) const>
inline ScriptToNativeCallResult
hybridMember5Param3(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, ARG_1 arg1, ARG_2, ARG_3)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 4); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn5Param4 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
phybridConstReturn5Param4(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 5))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn5Param4

/** phybridConstReturn5Param4 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4) const>
inline ScriptToNativeCallResult
phybridMember5Param4(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 5))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn5Param4

/** hybridMemberReturn5Param4 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
hybridConstReturn5Param4(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 5); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn5Param4 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4) const>
inline ScriptToNativeCallResult
hybridMember5Param4(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 5); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn5Param5 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
phybridConstReturn5Param5(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 6))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4, arg5);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn5Param5

/** phybridConstReturn5Param5 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) const>
inline ScriptToNativeCallResult
phybridMember5Param5(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 6))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4, arg5);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn5Param5

/** hybridMemberReturn5Param5 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
hybridConstReturn5Param5(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 6); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4, arg5);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn5Param5 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) const>
inline ScriptToNativeCallResult
hybridMember5Param5(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 6); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4, arg5);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn5Param6 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
phybridConstReturn5Param6(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 7))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn5Param6

/** phybridConstReturn5Param6 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) const>
inline ScriptToNativeCallResult
phybridMember5Param6(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 7))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn5Param6

/** hybridMemberReturn5Param6 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
hybridConstReturn5Param6(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 7); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn5Param6 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) const>
inline ScriptToNativeCallResult
hybridMember5Param6(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 7); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn5Param7 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
phybridConstReturn5Param7(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 8))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn5Param7

/** phybridConstReturn5Param7 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) const>
inline ScriptToNativeCallResult
phybridMember5Param7(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 8))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn5Param7

/** hybridMemberReturn5Param7 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
hybridConstReturn5Param7(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 8); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn5Param7 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) const>
inline ScriptToNativeCallResult
hybridMember5Param7(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 8); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn5Param8 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
phybridConstReturn5Param8(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 9))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn5Param8

/** phybridConstReturn5Param8 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) const>
inline ScriptToNativeCallResult
phybridMember5Param8(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 9))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn5Param8

/** hybridMemberReturn5Param8 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
hybridConstReturn5Param8(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 9); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn5Param8 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) const>
inline ScriptToNativeCallResult
hybridMember5Param8(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 9); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn5Param9 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
phybridConstReturn5Param9(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		push(L, arg9);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 10))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn5Param9

/** phybridConstReturn5Param9 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) const>
inline ScriptToNativeCallResult
phybridMember5Param9(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		push(L, arg9);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 10))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn5Param9

/** hybridMemberReturn5Param9 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
hybridConstReturn5Param9(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		push(L, arg9);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 10); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn5Param9 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) const>
inline ScriptToNativeCallResult
hybridMember5Param9(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		push(L, arg9);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 10); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn5Param10 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
phybridConstReturn5Param10(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
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
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 11))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn5Param10

/** phybridConstReturn5Param10 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) const>
inline ScriptToNativeCallResult
phybridMember5Param10(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
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
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 11))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn5Param10

/** hybridMemberReturn5Param10 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
hybridConstReturn5Param10(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
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
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 11); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn5Param10 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) const>
inline ScriptToNativeCallResult
hybridMember5Param10(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
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
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 11); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn6Param0 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&) >
inline ScriptToNativeCallResult
phybridConstReturn6Param0(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 1))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn6Param0

/** phybridConstReturn6Param0 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&) const>
inline ScriptToNativeCallResult
phybridMember6Param0(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 1))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn6Param0

/** hybridMemberReturn6Param0 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&) >
inline ScriptToNativeCallResult
hybridConstReturn6Param0(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 1); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn6Param0 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&) const>
inline ScriptToNativeCallResult
hybridMember6Param0(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 1); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn6Param1 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1) >
inline ScriptToNativeCallResult
phybridConstReturn6Param1(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, ARG_1 arg1)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 2))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn6Param1

/** phybridConstReturn6Param1 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1) const>
inline ScriptToNativeCallResult
phybridMember6Param1(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, ARG_1 arg1)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 2))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn6Param1

/** hybridMemberReturn6Param1 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1) >
inline ScriptToNativeCallResult
hybridConstReturn6Param1(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, ARG_1 arg1)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 2); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn6Param1 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1) const>
inline ScriptToNativeCallResult
hybridMember6Param1(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, ARG_1 arg1)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 2); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn6Param2 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2) >
inline ScriptToNativeCallResult
phybridConstReturn6Param2(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, ARG_1 arg1, ARG_2)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 3))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn6Param2

/** phybridConstReturn6Param2 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2) const>
inline ScriptToNativeCallResult
phybridMember6Param2(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, ARG_1 arg1, ARG_2)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 3))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn6Param2

/** hybridMemberReturn6Param2 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2) >
inline ScriptToNativeCallResult
hybridConstReturn6Param2(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, ARG_1 arg1, ARG_2)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 3); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn6Param2 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2) const>
inline ScriptToNativeCallResult
hybridMember6Param2(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, ARG_1 arg1, ARG_2)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 3); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn6Param3 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
phybridConstReturn6Param3(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, ARG_1 arg1, ARG_2, ARG_3)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 4))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn6Param3

/** phybridConstReturn6Param3 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3) const>
inline ScriptToNativeCallResult
phybridMember6Param3(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, ARG_1 arg1, ARG_2, ARG_3)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 4))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn6Param3

/** hybridMemberReturn6Param3 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
hybridConstReturn6Param3(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, ARG_1 arg1, ARG_2, ARG_3)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 4); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn6Param3 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3) const>
inline ScriptToNativeCallResult
hybridMember6Param3(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, ARG_1 arg1, ARG_2, ARG_3)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 4); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn6Param4 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
phybridConstReturn6Param4(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 5))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn6Param4

/** phybridConstReturn6Param4 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4) const>
inline ScriptToNativeCallResult
phybridMember6Param4(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 5))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn6Param4

/** hybridMemberReturn6Param4 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
hybridConstReturn6Param4(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 5); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn6Param4 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4) const>
inline ScriptToNativeCallResult
hybridMember6Param4(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 5); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn6Param5 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
phybridConstReturn6Param5(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 6))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4, arg5);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn6Param5

/** phybridConstReturn6Param5 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) const>
inline ScriptToNativeCallResult
phybridMember6Param5(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 6))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4, arg5);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn6Param5

/** hybridMemberReturn6Param5 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
hybridConstReturn6Param5(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 6); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4, arg5);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn6Param5 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) const>
inline ScriptToNativeCallResult
hybridMember6Param5(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 6); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4, arg5);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn6Param6 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
phybridConstReturn6Param6(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 7))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn6Param6

/** phybridConstReturn6Param6 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) const>
inline ScriptToNativeCallResult
phybridMember6Param6(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 7))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn6Param6

/** hybridMemberReturn6Param6 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
hybridConstReturn6Param6(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 7); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn6Param6 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) const>
inline ScriptToNativeCallResult
hybridMember6Param6(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 7); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn6Param7 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
phybridConstReturn6Param7(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 8))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn6Param7

/** phybridConstReturn6Param7 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) const>
inline ScriptToNativeCallResult
phybridMember6Param7(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 8))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn6Param7

/** hybridMemberReturn6Param7 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
hybridConstReturn6Param7(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 8); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn6Param7 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) const>
inline ScriptToNativeCallResult
hybridMember6Param7(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 8); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn6Param8 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
phybridConstReturn6Param8(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 9))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn6Param8

/** phybridConstReturn6Param8 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) const>
inline ScriptToNativeCallResult
phybridMember6Param8(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 9))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn6Param8

/** hybridMemberReturn6Param8 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
hybridConstReturn6Param8(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 9); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn6Param8 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) const>
inline ScriptToNativeCallResult
hybridMember6Param8(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 9); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn6Param9 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
phybridConstReturn6Param9(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		push(L, arg9);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 10))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn6Param9

/** phybridConstReturn6Param9 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) const>
inline ScriptToNativeCallResult
phybridMember6Param9(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		push(L, arg9);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 10))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn6Param9

/** hybridMemberReturn6Param9 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
hybridConstReturn6Param9(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		push(L, arg9);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 10); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn6Param9 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) const>
inline ScriptToNativeCallResult
hybridMember6Param9(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		push(L, arg9);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 10); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn6Param10 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
phybridConstReturn6Param10(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
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
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 11))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn6Param10

/** phybridConstReturn6Param10 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) const>
inline ScriptToNativeCallResult
phybridMember6Param10(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
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
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 11))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn6Param10

/** hybridMemberReturn6Param10 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
hybridConstReturn6Param10(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
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
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 11); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn6Param10 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) const>
inline ScriptToNativeCallResult
hybridMember6Param10(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
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
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 11); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn7Param0 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&) >
inline ScriptToNativeCallResult
phybridConstReturn7Param0(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 1))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn7Param0

/** phybridConstReturn7Param0 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&) const>
inline ScriptToNativeCallResult
phybridMember7Param0(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 1))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn7Param0

/** hybridMemberReturn7Param0 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&) >
inline ScriptToNativeCallResult
hybridConstReturn7Param0(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 1); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn7Param0 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&) const>
inline ScriptToNativeCallResult
hybridMember7Param0(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 1); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn7Param1 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1) >
inline ScriptToNativeCallResult
phybridConstReturn7Param1(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, ARG_1 arg1)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 2))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn7Param1

/** phybridConstReturn7Param1 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1) const>
inline ScriptToNativeCallResult
phybridMember7Param1(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, ARG_1 arg1)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 2))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn7Param1

/** hybridMemberReturn7Param1 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1) >
inline ScriptToNativeCallResult
hybridConstReturn7Param1(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, ARG_1 arg1)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 2); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn7Param1 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1) const>
inline ScriptToNativeCallResult
hybridMember7Param1(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, ARG_1 arg1)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 2); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn7Param2 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2) >
inline ScriptToNativeCallResult
phybridConstReturn7Param2(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, ARG_1 arg1, ARG_2)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 3))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn7Param2

/** phybridConstReturn7Param2 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2) const>
inline ScriptToNativeCallResult
phybridMember7Param2(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, ARG_1 arg1, ARG_2)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 3))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn7Param2

/** hybridMemberReturn7Param2 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2) >
inline ScriptToNativeCallResult
hybridConstReturn7Param2(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, ARG_1 arg1, ARG_2)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 3); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn7Param2 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2) const>
inline ScriptToNativeCallResult
hybridMember7Param2(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, ARG_1 arg1, ARG_2)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 3); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn7Param3 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
phybridConstReturn7Param3(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, ARG_1 arg1, ARG_2, ARG_3)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 4))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn7Param3

/** phybridConstReturn7Param3 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3) const>
inline ScriptToNativeCallResult
phybridMember7Param3(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, ARG_1 arg1, ARG_2, ARG_3)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 4))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn7Param3

/** hybridMemberReturn7Param3 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
hybridConstReturn7Param3(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, ARG_1 arg1, ARG_2, ARG_3)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 4); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn7Param3 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3) const>
inline ScriptToNativeCallResult
hybridMember7Param3(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, ARG_1 arg1, ARG_2, ARG_3)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 4); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn7Param4 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
phybridConstReturn7Param4(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 5))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn7Param4

/** phybridConstReturn7Param4 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4) const>
inline ScriptToNativeCallResult
phybridMember7Param4(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 5))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn7Param4

/** hybridMemberReturn7Param4 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
hybridConstReturn7Param4(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 5); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn7Param4 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4) const>
inline ScriptToNativeCallResult
hybridMember7Param4(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 5); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn7Param5 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
phybridConstReturn7Param5(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 6))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4, arg5);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn7Param5

/** phybridConstReturn7Param5 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) const>
inline ScriptToNativeCallResult
phybridMember7Param5(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 6))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4, arg5);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn7Param5

/** hybridMemberReturn7Param5 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
hybridConstReturn7Param5(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 6); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4, arg5);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn7Param5 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) const>
inline ScriptToNativeCallResult
hybridMember7Param5(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 6); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4, arg5);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn7Param6 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
phybridConstReturn7Param6(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 7))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn7Param6

/** phybridConstReturn7Param6 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) const>
inline ScriptToNativeCallResult
phybridMember7Param6(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 7))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn7Param6

/** hybridMemberReturn7Param6 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
hybridConstReturn7Param6(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 7); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn7Param6 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) const>
inline ScriptToNativeCallResult
hybridMember7Param6(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 7); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn7Param7 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
phybridConstReturn7Param7(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 8))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn7Param7

/** phybridConstReturn7Param7 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) const>
inline ScriptToNativeCallResult
phybridMember7Param7(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 8))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn7Param7

/** hybridMemberReturn7Param7 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
hybridConstReturn7Param7(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 8); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn7Param7 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) const>
inline ScriptToNativeCallResult
hybridMember7Param7(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 8); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn7Param8 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
phybridConstReturn7Param8(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 9))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn7Param8

/** phybridConstReturn7Param8 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) const>
inline ScriptToNativeCallResult
phybridMember7Param8(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 9))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn7Param8

/** hybridMemberReturn7Param8 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
hybridConstReturn7Param8(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 9); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn7Param8 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) const>
inline ScriptToNativeCallResult
hybridMember7Param8(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 9); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn7Param9 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
phybridConstReturn7Param9(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		push(L, arg9);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 10))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn7Param9

/** phybridConstReturn7Param9 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) const>
inline ScriptToNativeCallResult
phybridMember7Param9(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		push(L, arg9);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 10))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn7Param9

/** hybridMemberReturn7Param9 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
hybridConstReturn7Param9(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		push(L, arg9);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 10); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn7Param9 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) const>
inline ScriptToNativeCallResult
hybridMember7Param9(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		push(L, arg9);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 10); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn7Param10 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
phybridConstReturn7Param10(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
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
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 11))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn7Param10

/** phybridConstReturn7Param10 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) const>
inline ScriptToNativeCallResult
phybridMember7Param10(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
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
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 11))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn7Param10

/** hybridMemberReturn7Param10 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
hybridConstReturn7Param10(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
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
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 11); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn7Param10 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) const>
inline ScriptToNativeCallResult
hybridMember7Param10(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
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
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 11); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn8Param0 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&) >
inline ScriptToNativeCallResult
phybridConstReturn8Param0(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 1))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn8Param0

/** phybridConstReturn8Param0 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&) const>
inline ScriptToNativeCallResult
phybridMember8Param0(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 1))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn8Param0

/** hybridMemberReturn8Param0 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&) >
inline ScriptToNativeCallResult
hybridConstReturn8Param0(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 1); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn8Param0 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&) const>
inline ScriptToNativeCallResult
hybridMember8Param0(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 1); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn8Param1 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1) >
inline ScriptToNativeCallResult
phybridConstReturn8Param1(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, ARG_1 arg1)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 2))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn8Param1

/** phybridConstReturn8Param1 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1) const>
inline ScriptToNativeCallResult
phybridMember8Param1(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, ARG_1 arg1)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 2))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn8Param1

/** hybridMemberReturn8Param1 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1) >
inline ScriptToNativeCallResult
hybridConstReturn8Param1(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, ARG_1 arg1)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 2); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn8Param1 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1) const>
inline ScriptToNativeCallResult
hybridMember8Param1(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, ARG_1 arg1)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 2); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn8Param2 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2) >
inline ScriptToNativeCallResult
phybridConstReturn8Param2(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, ARG_1 arg1, ARG_2)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 3))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn8Param2

/** phybridConstReturn8Param2 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2) const>
inline ScriptToNativeCallResult
phybridMember8Param2(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, ARG_1 arg1, ARG_2)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 3))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn8Param2

/** hybridMemberReturn8Param2 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2) >
inline ScriptToNativeCallResult
hybridConstReturn8Param2(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, ARG_1 arg1, ARG_2)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 3); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn8Param2 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2) const>
inline ScriptToNativeCallResult
hybridMember8Param2(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, ARG_1 arg1, ARG_2)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 3); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn8Param3 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
phybridConstReturn8Param3(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, ARG_1 arg1, ARG_2, ARG_3)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 4))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn8Param3

/** phybridConstReturn8Param3 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3) const>
inline ScriptToNativeCallResult
phybridMember8Param3(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, ARG_1 arg1, ARG_2, ARG_3)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 4))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn8Param3

/** hybridMemberReturn8Param3 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
hybridConstReturn8Param3(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, ARG_1 arg1, ARG_2, ARG_3)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 4); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn8Param3 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3) const>
inline ScriptToNativeCallResult
hybridMember8Param3(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, ARG_1 arg1, ARG_2, ARG_3)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 4); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn8Param4 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
phybridConstReturn8Param4(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 5))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn8Param4

/** phybridConstReturn8Param4 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4) const>
inline ScriptToNativeCallResult
phybridMember8Param4(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 5))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn8Param4

/** hybridMemberReturn8Param4 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
hybridConstReturn8Param4(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 5); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn8Param4 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4) const>
inline ScriptToNativeCallResult
hybridMember8Param4(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 5); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn8Param5 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
phybridConstReturn8Param5(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 6))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4, arg5);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn8Param5

/** phybridConstReturn8Param5 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) const>
inline ScriptToNativeCallResult
phybridMember8Param5(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 6))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4, arg5);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn8Param5

/** hybridMemberReturn8Param5 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
hybridConstReturn8Param5(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 6); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4, arg5);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn8Param5 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) const>
inline ScriptToNativeCallResult
hybridMember8Param5(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 6); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4, arg5);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn8Param6 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
phybridConstReturn8Param6(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 7))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn8Param6

/** phybridConstReturn8Param6 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) const>
inline ScriptToNativeCallResult
phybridMember8Param6(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 7))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn8Param6

/** hybridMemberReturn8Param6 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
hybridConstReturn8Param6(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 7); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn8Param6 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) const>
inline ScriptToNativeCallResult
hybridMember8Param6(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 7); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn8Param7 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
phybridConstReturn8Param7(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 8))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn8Param7

/** phybridConstReturn8Param7 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) const>
inline ScriptToNativeCallResult
phybridMember8Param7(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 8))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn8Param7

/** hybridMemberReturn8Param7 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
hybridConstReturn8Param7(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 8); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn8Param7 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) const>
inline ScriptToNativeCallResult
hybridMember8Param7(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 8); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn8Param8 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
phybridConstReturn8Param8(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 9))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn8Param8

/** phybridConstReturn8Param8 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) const>
inline ScriptToNativeCallResult
phybridMember8Param8(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 9))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn8Param8

/** hybridMemberReturn8Param8 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
hybridConstReturn8Param8(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 9); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn8Param8 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) const>
inline ScriptToNativeCallResult
hybridMember8Param8(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 9); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn8Param9 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
phybridConstReturn8Param9(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		push(L, arg9);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 10))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn8Param9

/** phybridConstReturn8Param9 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) const>
inline ScriptToNativeCallResult
phybridMember8Param9(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		push(L, arg9);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 10))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn8Param9

/** hybridMemberReturn8Param9 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
hybridConstReturn8Param9(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		push(L, arg9);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 10); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn8Param9 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) const>
inline ScriptToNativeCallResult
hybridMember8Param9(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		push(L, arg9);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 10); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn8Param10 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
phybridConstReturn8Param10(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
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
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 11))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn8Param10

/** phybridConstReturn8Param10 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) const>
inline ScriptToNativeCallResult
phybridMember8Param10(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
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
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 11))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn8Param10

/** hybridMemberReturn8Param10 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
hybridConstReturn8Param10(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
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
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 11); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn8Param10 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) const>
inline ScriptToNativeCallResult
hybridMember8Param10(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
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
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 11); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn9Param0 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&) >
inline ScriptToNativeCallResult
phybridConstReturn9Param0(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 1))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn9Param0

/** phybridConstReturn9Param0 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&) const>
inline ScriptToNativeCallResult
phybridMember9Param0(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 1))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn9Param0

/** hybridMemberReturn9Param0 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&) >
inline ScriptToNativeCallResult
hybridConstReturn9Param0(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 1); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn9Param0 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&) const>
inline ScriptToNativeCallResult
hybridMember9Param0(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 1); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn9Param1 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1) >
inline ScriptToNativeCallResult
phybridConstReturn9Param1(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, ARG_1 arg1)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 2))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn9Param1

/** phybridConstReturn9Param1 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1) const>
inline ScriptToNativeCallResult
phybridMember9Param1(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, ARG_1 arg1)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 2))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn9Param1

/** hybridMemberReturn9Param1 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1) >
inline ScriptToNativeCallResult
hybridConstReturn9Param1(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, ARG_1 arg1)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 2); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn9Param1 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1) const>
inline ScriptToNativeCallResult
hybridMember9Param1(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, ARG_1 arg1)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 2); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn9Param2 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2) >
inline ScriptToNativeCallResult
phybridConstReturn9Param2(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, ARG_1 arg1, ARG_2)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 3))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn9Param2

/** phybridConstReturn9Param2 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2) const>
inline ScriptToNativeCallResult
phybridMember9Param2(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, ARG_1 arg1, ARG_2)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 3))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn9Param2

/** hybridMemberReturn9Param2 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2) >
inline ScriptToNativeCallResult
hybridConstReturn9Param2(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, ARG_1 arg1, ARG_2)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 3); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn9Param2 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2) const>
inline ScriptToNativeCallResult
hybridMember9Param2(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, ARG_1 arg1, ARG_2)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 3); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn9Param3 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
phybridConstReturn9Param3(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, ARG_1 arg1, ARG_2, ARG_3)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 4))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn9Param3

/** phybridConstReturn9Param3 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3) const>
inline ScriptToNativeCallResult
phybridMember9Param3(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, ARG_1 arg1, ARG_2, ARG_3)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 4))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn9Param3

/** hybridMemberReturn9Param3 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
hybridConstReturn9Param3(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, ARG_1 arg1, ARG_2, ARG_3)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 4); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn9Param3 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3) const>
inline ScriptToNativeCallResult
hybridMember9Param3(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, ARG_1 arg1, ARG_2, ARG_3)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 4); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn9Param4 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
phybridConstReturn9Param4(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 5))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn9Param4

/** phybridConstReturn9Param4 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4) const>
inline ScriptToNativeCallResult
phybridMember9Param4(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 5))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn9Param4

/** hybridMemberReturn9Param4 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
hybridConstReturn9Param4(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 5); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn9Param4 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4) const>
inline ScriptToNativeCallResult
hybridMember9Param4(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 5); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn9Param5 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
phybridConstReturn9Param5(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 6))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4, arg5);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn9Param5

/** phybridConstReturn9Param5 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) const>
inline ScriptToNativeCallResult
phybridMember9Param5(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 6))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4, arg5);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn9Param5

/** hybridMemberReturn9Param5 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
hybridConstReturn9Param5(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 6); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4, arg5);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn9Param5 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) const>
inline ScriptToNativeCallResult
hybridMember9Param5(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 6); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4, arg5);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn9Param6 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
phybridConstReturn9Param6(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 7))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn9Param6

/** phybridConstReturn9Param6 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) const>
inline ScriptToNativeCallResult
phybridMember9Param6(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 7))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn9Param6

/** hybridMemberReturn9Param6 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
hybridConstReturn9Param6(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 7); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn9Param6 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) const>
inline ScriptToNativeCallResult
hybridMember9Param6(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 7); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn9Param7 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
phybridConstReturn9Param7(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 8))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn9Param7

/** phybridConstReturn9Param7 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) const>
inline ScriptToNativeCallResult
phybridMember9Param7(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 8))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn9Param7

/** hybridMemberReturn9Param7 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
hybridConstReturn9Param7(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 8); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn9Param7 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) const>
inline ScriptToNativeCallResult
hybridMember9Param7(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 8); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn9Param8 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
phybridConstReturn9Param8(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 9))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn9Param8

/** phybridConstReturn9Param8 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) const>
inline ScriptToNativeCallResult
phybridMember9Param8(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 9))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn9Param8

/** hybridMemberReturn9Param8 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
hybridConstReturn9Param8(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 9); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn9Param8 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) const>
inline ScriptToNativeCallResult
hybridMember9Param8(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 9); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn9Param9 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
phybridConstReturn9Param9(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		push(L, arg9);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 10))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn9Param9

/** phybridConstReturn9Param9 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) const>
inline ScriptToNativeCallResult
phybridMember9Param9(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		push(L, arg9);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 10))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn9Param9

/** hybridMemberReturn9Param9 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
hybridConstReturn9Param9(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		push(L, arg9);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 10); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn9Param9 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) const>
inline ScriptToNativeCallResult
hybridMember9Param9(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		push(L, arg9);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 10); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn9Param10 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
phybridConstReturn9Param10(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
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
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 11))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn9Param10

/** phybridConstReturn9Param10 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) const>
inline ScriptToNativeCallResult
phybridMember9Param10(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
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
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 11))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn9Param10

/** hybridMemberReturn9Param10 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
hybridConstReturn9Param10(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
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
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 11); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn9Param10 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) const>
inline ScriptToNativeCallResult
hybridMember9Param10(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
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
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 11); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn10Param0 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&) >
inline ScriptToNativeCallResult
phybridConstReturn10Param0(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, RET_10& ret)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 1))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn10Param0

/** phybridConstReturn10Param0 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&) const>
inline ScriptToNativeCallResult
phybridMember10Param0(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, RET_10& ret)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 1))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn10Param0

/** hybridMemberReturn10Param0 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&) >
inline ScriptToNativeCallResult
hybridConstReturn10Param0(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, RET_10& ret)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 1); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn10Param0 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&) const>
inline ScriptToNativeCallResult
hybridMember10Param0(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, RET_10& ret)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 1); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn10Param1 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1) >
inline ScriptToNativeCallResult
phybridConstReturn10Param1(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, RET_10& ret, ARG_1 arg1)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 2))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn10Param1

/** phybridConstReturn10Param1 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1) const>
inline ScriptToNativeCallResult
phybridMember10Param1(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, RET_10& ret, ARG_1 arg1)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 2))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn10Param1

/** hybridMemberReturn10Param1 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1) >
inline ScriptToNativeCallResult
hybridConstReturn10Param1(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, RET_10& ret, ARG_1 arg1)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 2); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn10Param1 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1) const>
inline ScriptToNativeCallResult
hybridMember10Param1(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, RET_10& ret, ARG_1 arg1)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 2); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn10Param2 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2) >
inline ScriptToNativeCallResult
phybridConstReturn10Param2(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, RET_10& ret, ARG_1 arg1, ARG_2)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 3))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn10Param2

/** phybridConstReturn10Param2 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2) const>
inline ScriptToNativeCallResult
phybridMember10Param2(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, RET_10& ret, ARG_1 arg1, ARG_2)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 3))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn10Param2

/** hybridMemberReturn10Param2 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2) >
inline ScriptToNativeCallResult
hybridConstReturn10Param2(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, RET_10& ret, ARG_1 arg1, ARG_2)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 3); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn10Param2 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2) const>
inline ScriptToNativeCallResult
hybridMember10Param2(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, RET_10& ret, ARG_1 arg1, ARG_2)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 3); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn10Param3 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
phybridConstReturn10Param3(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, RET_10& ret, ARG_1 arg1, ARG_2, ARG_3)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 4))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn10Param3

/** phybridConstReturn10Param3 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3) const>
inline ScriptToNativeCallResult
phybridMember10Param3(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, RET_10& ret, ARG_1 arg1, ARG_2, ARG_3)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 4))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn10Param3

/** hybridMemberReturn10Param3 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3) >
inline ScriptToNativeCallResult
hybridConstReturn10Param3(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, RET_10& ret, ARG_1 arg1, ARG_2, ARG_3)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 4); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn10Param3 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3) const>
inline ScriptToNativeCallResult
hybridMember10Param3(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, RET_10& ret, ARG_1 arg1, ARG_2, ARG_3)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 4); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn10Param4 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
phybridConstReturn10Param4(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, RET_10& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 5))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn10Param4

/** phybridConstReturn10Param4 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4) const>
inline ScriptToNativeCallResult
phybridMember10Param4(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, RET_10& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 5))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn10Param4

/** hybridMemberReturn10Param4 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline ScriptToNativeCallResult
hybridConstReturn10Param4(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, RET_10& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 5); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn10Param4 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4) const>
inline ScriptToNativeCallResult
hybridMember10Param4(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, RET_10& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 5); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn10Param5 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
phybridConstReturn10Param5(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, RET_10& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 6))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4, arg5);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn10Param5

/** phybridConstReturn10Param5 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) const>
inline ScriptToNativeCallResult
phybridMember10Param5(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, RET_10& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 6))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4, arg5);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn10Param5

/** hybridMemberReturn10Param5 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline ScriptToNativeCallResult
hybridConstReturn10Param5(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, RET_10& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 6); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4, arg5);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn10Param5 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) const>
inline ScriptToNativeCallResult
hybridMember10Param5(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, RET_10& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 6); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4, arg5);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn10Param6 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
phybridConstReturn10Param6(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, RET_10& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 7))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn10Param6

/** phybridConstReturn10Param6 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) const>
inline ScriptToNativeCallResult
phybridMember10Param6(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, RET_10& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 7))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn10Param6

/** hybridMemberReturn10Param6 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline ScriptToNativeCallResult
hybridConstReturn10Param6(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, RET_10& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 7); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn10Param6 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) const>
inline ScriptToNativeCallResult
hybridMember10Param6(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, RET_10& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 7); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4, arg5, arg6);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn10Param7 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
phybridConstReturn10Param7(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, RET_10& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 8))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn10Param7

/** phybridConstReturn10Param7 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) const>
inline ScriptToNativeCallResult
phybridMember10Param7(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, RET_10& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 8))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn10Param7

/** hybridMemberReturn10Param7 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline ScriptToNativeCallResult
hybridConstReturn10Param7(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, RET_10& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 8); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn10Param7 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) const>
inline ScriptToNativeCallResult
hybridMember10Param7(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, RET_10& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 8); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn10Param8 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
phybridConstReturn10Param8(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, RET_10& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 9))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn10Param8

/** phybridConstReturn10Param8 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) const>
inline ScriptToNativeCallResult
phybridMember10Param8(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, RET_10& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 9))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn10Param8

/** hybridMemberReturn10Param8 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline ScriptToNativeCallResult
hybridConstReturn10Param8(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, RET_10& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 9); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn10Param8 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) const>
inline ScriptToNativeCallResult
hybridMember10Param8(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, RET_10& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 9); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn10Param9 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
phybridConstReturn10Param9(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, RET_10& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		push(L, arg9);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 10))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn10Param9

/** phybridConstReturn10Param9 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) const>
inline ScriptToNativeCallResult
phybridMember10Param9(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, RET_10& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		push(L, arg9);
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 10))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn10Param9

/** hybridMemberReturn10Param9 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline ScriptToNativeCallResult
hybridConstReturn10Param9(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, RET_10& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		push(L, arg9);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 10); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn10Param9 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) const>
inline ScriptToNativeCallResult
hybridMember10Param9(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, RET_10& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
		push(L, arg1);
		push(L, arg2);
		push(L, arg3);
		push(L, arg4);
		push(L, arg5);
		push(L, arg6);
		push(L, arg7);
		push(L, arg8);
		push(L, arg9);
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 10); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		return lua_extension::functionNotFound; 
	} 
}

/** phybridMemberReturn10Param10 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
phybridConstReturn10Param10(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, RET_10& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
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
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 11))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::functionNotFound; 
	} 
} // phybridMemberReturn10Param10

/** phybridConstReturn10Param10 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) const>
inline ScriptToNativeCallResult
phybridMember10Param10(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, RET_10& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
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
		/*s: object scriptFunction object (arguments) */ 
		if (!Lua::callProtected((L, 11))
		{	/*s: object (return values) */ 
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
		{	/*s: object */
			lua_pop(L, 1);
			/*s: */
			return lua_extension::functionError;
		} 
	else 
	{	/*s: module nil */
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::functionNotFound; 
	} 
} // phybridConstReturn10Param10

/** hybridMemberReturn10Param10 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline ScriptToNativeCallResult
hybridConstReturn10Param10(lua_State* L, const char* scriptFunction, const CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, RET_10& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
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
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 11); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::functionNotFound; 
	} 
}

/** hybridConstReturn10Param10 */
template<typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) const>
inline ScriptToNativeCallResult
hybridMember10Param10(lua_State* L, const char* scriptFunction, CLASS& object, RET_1& ret, RET_2& ret, RET_3& ret, RET_4& ret, RET_5& ret, RET_6& ret, RET_7& ret, RET_8& ret, RET_9& ret, RET_10& ret, ARG_1 arg1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10)
{	/*s: */
	push(L, object);
	/*s: object */
	lua_getfield(L, -1, scriptFunction);
	/*s: object ? */
	if (lua_isfunction(L, -1)) 
	{	/*s: object scriptFunction */ 
		lua_pushvalue(L, -2);
		/*s: object scriptFunction object */ 
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
		/*s: object scriptFunction object (arguments) */ 
		lua_call(L, 11); 
		/*s: object (return values) */ 
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
		lua_pop(L, 2);
		/*s: */ 
		ret1 = (object.*nativeFunction)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		return lua_extension::functionNotFound; 
	} 
}

