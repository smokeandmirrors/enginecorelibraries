/** nativeConstReturn0Param0 */
template<typename CLASS, void(CLASS::* function)(void) const>
inline sint nativeConstReturn0Param0(lua_State* L)
{	if (CLASS* object = to<CLASS*>(L, -1))
	{
		(object->*function)();
	}
	return 0;
} // nativeConstReturn0Param0

/** nativeMemberReturn0Param0 */
template<typename CLASS, void(CLASS::* function)(void)>
inline sint nativeMemberReturn0Param0(lua_State* L)
{
	if (CLASS* object = to<CLASS*>(L, -1))
	{
		(object->*function)();
	}
	return 0;
} // nativeMemberReturn0Param0

/** nativeStaticReturn0Param0 */
template<void(* function)(void)>
inline sint nativeStaticReturn0Param0(lua_State*)
{
	(*function)();
	return 0;
}// nativeStaticReturn0Param0

/** nativeConstReturn0Param1 */
template< typename CLASS, typename ARG_1, void (CLASS::* function)(ARG_1) const>
inline LUA_FUNC(nativeConstReturn0Param1)
{
	if (CLASS* object = to<CLASS*>(L, -2))
	{
		(object->*function)(to<ARG_1>(L, -1));
	}
	return 0;
} // nativeConstReturn0Param1

/** nativeMemberReturn0Param1 */
template< typename CLASS, typename ARG_1, void (CLASS::* function)(ARG_1) >
inline LUA_FUNC(nativeMemberReturn0Param1)
{
	if (CLASS* object = to<CLASS*>(L, -2))
	{
		(object->*function)(to<ARG_1>(L, -1));
	}
	return 0;
} // nativeMemberReturn0Param1

/** nativeStaticReturn0Param1 */
template< typename ARG_1, void (* function)(ARG_1) >
inline LUA_FUNC(nativeStaticReturn0Param1)
{
	(*function)(to<ARG_1>(L, -1));
	return 0;
} // nativeStaticReturn0Param1

/** nativeConstReturn0Param2 */
template< typename CLASS, typename ARG_1, typename ARG_2, void (CLASS::* function)(ARG_1, ARG_2) const>
inline LUA_FUNC(nativeConstReturn0Param2)
{
	if (CLASS* object = to<CLASS*>(L, -3))
	{
		(object->*function)(to<ARG_1>(L, -2), to<ARG_2>(L, -1));
	}
	return 0;
} // nativeConstReturn0Param2

/** nativeMemberReturn0Param2 */
template< typename CLASS, typename ARG_1, typename ARG_2, void (CLASS::* function)(ARG_1, ARG_2) >
inline LUA_FUNC(nativeMemberReturn0Param2)
{
	if (CLASS* object = to<CLASS*>(L, -3))
	{
		(object->*function)(to<ARG_1>(L, -2), to<ARG_2>(L, -1));
	}
	return 0;
} // nativeMemberReturn0Param2

/** nativeStaticReturn0Param2 */
template< typename ARG_1, typename ARG_2, void (* function)(ARG_1, ARG_2) >
inline LUA_FUNC(nativeStaticReturn0Param2)
{
	(*function)(to<ARG_1>(L, -2), to<ARG_2>(L, -1));
	return 0;
} // nativeStaticReturn0Param2

/** nativeConstReturn0Param3 */
template< typename CLASS, typename ARG_1, typename ARG_2, typename ARG_3, void (CLASS::* function)(ARG_1, ARG_2, ARG_3) const>
inline LUA_FUNC(nativeConstReturn0Param3)
{
	if (CLASS* object = to<CLASS*>(L, -4))
	{
		(object->*function)(to<ARG_1>(L, -3), to<ARG_2>(L, -2), to<ARG_3>(L, -1));
	}
	return 0;
} // nativeConstReturn0Param3

/** nativeMemberReturn0Param3 */
template< typename CLASS, typename ARG_1, typename ARG_2, typename ARG_3, void (CLASS::* function)(ARG_1, ARG_2, ARG_3) >
inline LUA_FUNC(nativeMemberReturn0Param3)
{
	if (CLASS* object = to<CLASS*>(L, -4))
	{
		(object->*function)(to<ARG_1>(L, -3), to<ARG_2>(L, -2), to<ARG_3>(L, -1));
	}
	return 0;
} // nativeMemberReturn0Param3

/** nativeStaticReturn0Param3 */
template< typename ARG_1, typename ARG_2, typename ARG_3, void (* function)(ARG_1, ARG_2, ARG_3) >
inline LUA_FUNC(nativeStaticReturn0Param3)
{
	(*function)(to<ARG_1>(L, -3), to<ARG_2>(L, -2), to<ARG_3>(L, -1));
	return 0;
} // nativeStaticReturn0Param3

/** nativeConstReturn0Param4 */
template< typename CLASS, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, void (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4) const>
inline LUA_FUNC(nativeConstReturn0Param4)
{
	if (CLASS* object = to<CLASS*>(L, -5))
	{
		(object->*function)(to<ARG_1>(L, -4), to<ARG_2>(L, -3), to<ARG_3>(L, -2), to<ARG_4>(L, -1));
	}
	return 0;
} // nativeConstReturn0Param4

/** nativeMemberReturn0Param4 */
template< typename CLASS, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, void (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4) >
inline LUA_FUNC(nativeMemberReturn0Param4)
{
	if (CLASS* object = to<CLASS*>(L, -5))
	{
		(object->*function)(to<ARG_1>(L, -4), to<ARG_2>(L, -3), to<ARG_3>(L, -2), to<ARG_4>(L, -1));
	}
	return 0;
} // nativeMemberReturn0Param4

/** nativeStaticReturn0Param4 */
template< typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, void (* function)(ARG_1, ARG_2, ARG_3, ARG_4) >
inline LUA_FUNC(nativeStaticReturn0Param4)
{
	(*function)(to<ARG_1>(L, -4), to<ARG_2>(L, -3), to<ARG_3>(L, -2), to<ARG_4>(L, -1));
	return 0;
} // nativeStaticReturn0Param4

/** nativeConstReturn0Param5 */
template< typename CLASS, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, void (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) const>
inline LUA_FUNC(nativeConstReturn0Param5)
{
	if (CLASS* object = to<CLASS*>(L, -6))
	{
		(object->*function)(to<ARG_1>(L, -5), to<ARG_2>(L, -4), to<ARG_3>(L, -3), to<ARG_4>(L, -2), to<ARG_5>(L, -1));
	}
	return 0;
} // nativeConstReturn0Param5

/** nativeMemberReturn0Param5 */
template< typename CLASS, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, void (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline LUA_FUNC(nativeMemberReturn0Param5)
{
	if (CLASS* object = to<CLASS*>(L, -6))
	{
		(object->*function)(to<ARG_1>(L, -5), to<ARG_2>(L, -4), to<ARG_3>(L, -3), to<ARG_4>(L, -2), to<ARG_5>(L, -1));
	}
	return 0;
} // nativeMemberReturn0Param5

/** nativeStaticReturn0Param5 */
template< typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, void (* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline LUA_FUNC(nativeStaticReturn0Param5)
{
	(*function)(to<ARG_1>(L, -5), to<ARG_2>(L, -4), to<ARG_3>(L, -3), to<ARG_4>(L, -2), to<ARG_5>(L, -1));
	return 0;
} // nativeStaticReturn0Param5

/** nativeConstReturn0Param6 */
template< typename CLASS, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, void (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) const>
inline LUA_FUNC(nativeConstReturn0Param6)
{
	if (CLASS* object = to<CLASS*>(L, -7))
	{
		(object->*function)(to<ARG_1>(L, -6), to<ARG_2>(L, -5), to<ARG_3>(L, -4), to<ARG_4>(L, -3), to<ARG_5>(L, -2), to<ARG_6>(L, -1));
	}
	return 0;
} // nativeConstReturn0Param6

/** nativeMemberReturn0Param6 */
template< typename CLASS, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, void (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline LUA_FUNC(nativeMemberReturn0Param6)
{
	if (CLASS* object = to<CLASS*>(L, -7))
	{
		(object->*function)(to<ARG_1>(L, -6), to<ARG_2>(L, -5), to<ARG_3>(L, -4), to<ARG_4>(L, -3), to<ARG_5>(L, -2), to<ARG_6>(L, -1));
	}
	return 0;
} // nativeMemberReturn0Param6

/** nativeStaticReturn0Param6 */
template< typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, void (* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline LUA_FUNC(nativeStaticReturn0Param6)
{
	(*function)(to<ARG_1>(L, -6), to<ARG_2>(L, -5), to<ARG_3>(L, -4), to<ARG_4>(L, -3), to<ARG_5>(L, -2), to<ARG_6>(L, -1));
	return 0;
} // nativeStaticReturn0Param6

/** nativeConstReturn0Param7 */
template< typename CLASS, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, void (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) const>
inline LUA_FUNC(nativeConstReturn0Param7)
{
	if (CLASS* object = to<CLASS*>(L, -8))
	{
		(object->*function)(to<ARG_1>(L, -7), to<ARG_2>(L, -6), to<ARG_3>(L, -5), to<ARG_4>(L, -4), to<ARG_5>(L, -3), to<ARG_6>(L, -2), to<ARG_7>(L, -1));
	}
	return 0;
} // nativeConstReturn0Param7

/** nativeMemberReturn0Param7 */
template< typename CLASS, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, void (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline LUA_FUNC(nativeMemberReturn0Param7)
{
	if (CLASS* object = to<CLASS*>(L, -8))
	{
		(object->*function)(to<ARG_1>(L, -7), to<ARG_2>(L, -6), to<ARG_3>(L, -5), to<ARG_4>(L, -4), to<ARG_5>(L, -3), to<ARG_6>(L, -2), to<ARG_7>(L, -1));
	}
	return 0;
} // nativeMemberReturn0Param7

/** nativeStaticReturn0Param7 */
template< typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, void (* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline LUA_FUNC(nativeStaticReturn0Param7)
{
	(*function)(to<ARG_1>(L, -7), to<ARG_2>(L, -6), to<ARG_3>(L, -5), to<ARG_4>(L, -4), to<ARG_5>(L, -3), to<ARG_6>(L, -2), to<ARG_7>(L, -1));
	return 0;
} // nativeStaticReturn0Param7

/** nativeConstReturn0Param8 */
template< typename CLASS, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, void (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) const>
inline LUA_FUNC(nativeConstReturn0Param8)
{
	if (CLASS* object = to<CLASS*>(L, -9))
	{
		(object->*function)(to<ARG_1>(L, -8), to<ARG_2>(L, -7), to<ARG_3>(L, -6), to<ARG_4>(L, -5), to<ARG_5>(L, -4), to<ARG_6>(L, -3), to<ARG_7>(L, -2), to<ARG_8>(L, -1));
	}
	return 0;
} // nativeConstReturn0Param8

/** nativeMemberReturn0Param8 */
template< typename CLASS, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, void (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline LUA_FUNC(nativeMemberReturn0Param8)
{
	if (CLASS* object = to<CLASS*>(L, -9))
	{
		(object->*function)(to<ARG_1>(L, -8), to<ARG_2>(L, -7), to<ARG_3>(L, -6), to<ARG_4>(L, -5), to<ARG_5>(L, -4), to<ARG_6>(L, -3), to<ARG_7>(L, -2), to<ARG_8>(L, -1));
	}
	return 0;
} // nativeMemberReturn0Param8

/** nativeStaticReturn0Param8 */
template< typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, void (* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline LUA_FUNC(nativeStaticReturn0Param8)
{
	(*function)(to<ARG_1>(L, -8), to<ARG_2>(L, -7), to<ARG_3>(L, -6), to<ARG_4>(L, -5), to<ARG_5>(L, -4), to<ARG_6>(L, -3), to<ARG_7>(L, -2), to<ARG_8>(L, -1));
	return 0;
} // nativeStaticReturn0Param8

/** nativeConstReturn0Param9 */
template< typename CLASS, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, void (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) const>
inline LUA_FUNC(nativeConstReturn0Param9)
{
	if (CLASS* object = to<CLASS*>(L, -10))
	{
		(object->*function)(to<ARG_1>(L, -9), to<ARG_2>(L, -8), to<ARG_3>(L, -7), to<ARG_4>(L, -6), to<ARG_5>(L, -5), to<ARG_6>(L, -4), to<ARG_7>(L, -3), to<ARG_8>(L, -2), to<ARG_9>(L, -1));
	}
	return 0;
} // nativeConstReturn0Param9

/** nativeMemberReturn0Param9 */
template< typename CLASS, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, void (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline LUA_FUNC(nativeMemberReturn0Param9)
{
	if (CLASS* object = to<CLASS*>(L, -10))
	{
		(object->*function)(to<ARG_1>(L, -9), to<ARG_2>(L, -8), to<ARG_3>(L, -7), to<ARG_4>(L, -6), to<ARG_5>(L, -5), to<ARG_6>(L, -4), to<ARG_7>(L, -3), to<ARG_8>(L, -2), to<ARG_9>(L, -1));
	}
	return 0;
} // nativeMemberReturn0Param9

/** nativeStaticReturn0Param9 */
template< typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, void (* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline LUA_FUNC(nativeStaticReturn0Param9)
{
	(*function)(to<ARG_1>(L, -9), to<ARG_2>(L, -8), to<ARG_3>(L, -7), to<ARG_4>(L, -6), to<ARG_5>(L, -5), to<ARG_6>(L, -4), to<ARG_7>(L, -3), to<ARG_8>(L, -2), to<ARG_9>(L, -1));
	return 0;
} // nativeStaticReturn0Param9

/** nativeConstReturn0Param10 */
template< typename CLASS, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, void (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) const>
inline LUA_FUNC(nativeConstReturn0Param10)
{
	if (CLASS* object = to<CLASS*>(L, -11))
	{
		(object->*function)(to<ARG_1>(L, -10), to<ARG_2>(L, -9), to<ARG_3>(L, -8), to<ARG_4>(L, -7), to<ARG_5>(L, -6), to<ARG_6>(L, -5), to<ARG_7>(L, -4), to<ARG_8>(L, -3), to<ARG_9>(L, -2), to<ARG_10>(L, -1));
	}
	return 0;
} // nativeConstReturn0Param10

/** nativeMemberReturn0Param10 */
template< typename CLASS, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, void (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline LUA_FUNC(nativeMemberReturn0Param10)
{
	if (CLASS* object = to<CLASS*>(L, -11))
	{
		(object->*function)(to<ARG_1>(L, -10), to<ARG_2>(L, -9), to<ARG_3>(L, -8), to<ARG_4>(L, -7), to<ARG_5>(L, -6), to<ARG_6>(L, -5), to<ARG_7>(L, -4), to<ARG_8>(L, -3), to<ARG_9>(L, -2), to<ARG_10>(L, -1));
	}
	return 0;
} // nativeMemberReturn0Param10

/** nativeStaticReturn0Param10 */
template< typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, void (* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline LUA_FUNC(nativeStaticReturn0Param10)
{
	(*function)(to<ARG_1>(L, -10), to<ARG_2>(L, -9), to<ARG_3>(L, -8), to<ARG_4>(L, -7), to<ARG_5>(L, -6), to<ARG_6>(L, -5), to<ARG_7>(L, -4), to<ARG_8>(L, -3), to<ARG_9>(L, -2), to<ARG_10>(L, -1));
	return 0;
} // nativeStaticReturn0Param10

/** nativeConstReturn1Param0 */
template< typename CLASS, typename RET_1, RET_1 (CLASS::* function)(void) const>
inline LUA_FUNC(nativeConstReturn1Param0)
{
	if (CLASS* object = to<CLASS*>(L, -1))
	{
		RET_1 ret1 = (object->*function)();
		sint pushed(push(L, ret1));
		return pushed;
	}
	return 0;
} // nativeConstReturn1Param0

/** nativeMemberReturn1Param0 */
template< typename CLASS, typename RET_1, RET_1 (CLASS::* function)(void) >
inline LUA_FUNC(nativeMemberReturn1Param0)
{
	if (CLASS* object = to<CLASS*>(L, -1))
	{
		RET_1 ret1 = (object->*function)();
		sint pushed(push(L, ret1));
		return pushed;
	}
	return 0;
} // nativeMemberReturn1Param0

/** nativeStaticReturn1Param0 */
template< typename RET_1, RET_1 (* function)(void) >
inline LUA_FUNC(nativeStaticReturn1Param0)
{
	RET_1 ret1 = (*function)();
	sint pushed(push(L, ret1));
	return pushed;
} // nativeStaticReturn1Param0

/** nativeConstReturn1Param1 */
template< typename CLASS, typename RET_1, typename ARG_1, RET_1 (CLASS::* function)(ARG_1) const>
inline LUA_FUNC(nativeConstReturn1Param1)
{
	if (CLASS* object = to<CLASS*>(L, -2))
	{
		RET_1 ret1 = (object->*function)(to<ARG_1>(L, -1));
		sint pushed(push(L, ret1));
		return pushed;
	}
	return 0;
} // nativeConstReturn1Param1

/** nativeMemberReturn1Param1 */
template< typename CLASS, typename RET_1, typename ARG_1, RET_1 (CLASS::* function)(ARG_1) >
inline LUA_FUNC(nativeMemberReturn1Param1)
{
	if (CLASS* object = to<CLASS*>(L, -2))
	{
		RET_1 ret1 = (object->*function)(to<ARG_1>(L, -1));
		sint pushed(push(L, ret1));
		return pushed;
	}
	return 0;
} // nativeMemberReturn1Param1

/** nativeStaticReturn1Param1 */
template< typename RET_1, typename ARG_1, RET_1 (* function)(ARG_1) >
inline LUA_FUNC(nativeStaticReturn1Param1)
{
	RET_1 ret1 = (*function)(to<ARG_1>(L, -1));
	sint pushed(push(L, ret1));
	return pushed;
} // nativeStaticReturn1Param1

/** nativeConstReturn1Param2 */
template< typename CLASS, typename RET_1, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(ARG_1, ARG_2) const>
inline LUA_FUNC(nativeConstReturn1Param2)
{
	if (CLASS* object = to<CLASS*>(L, -3))
	{
		RET_1 ret1 = (object->*function)(to<ARG_1>(L, -2), to<ARG_2>(L, -1));
		sint pushed(push(L, ret1));
		return pushed;
	}
	return 0;
} // nativeConstReturn1Param2

/** nativeMemberReturn1Param2 */
template< typename CLASS, typename RET_1, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(ARG_1, ARG_2) >
inline LUA_FUNC(nativeMemberReturn1Param2)
{
	if (CLASS* object = to<CLASS*>(L, -3))
	{
		RET_1 ret1 = (object->*function)(to<ARG_1>(L, -2), to<ARG_2>(L, -1));
		sint pushed(push(L, ret1));
		return pushed;
	}
	return 0;
} // nativeMemberReturn1Param2

/** nativeStaticReturn1Param2 */
template< typename RET_1, typename ARG_1, typename ARG_2, RET_1 (* function)(ARG_1, ARG_2) >
inline LUA_FUNC(nativeStaticReturn1Param2)
{
	RET_1 ret1 = (*function)(to<ARG_1>(L, -2), to<ARG_2>(L, -1));
	sint pushed(push(L, ret1));
	return pushed;
} // nativeStaticReturn1Param2

/** nativeConstReturn1Param3 */
template< typename CLASS, typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(ARG_1, ARG_2, ARG_3) const>
inline LUA_FUNC(nativeConstReturn1Param3)
{
	if (CLASS* object = to<CLASS*>(L, -4))
	{
		RET_1 ret1 = (object->*function)(to<ARG_1>(L, -3), to<ARG_2>(L, -2), to<ARG_3>(L, -1));
		sint pushed(push(L, ret1));
		return pushed;
	}
	return 0;
} // nativeConstReturn1Param3

/** nativeMemberReturn1Param3 */
template< typename CLASS, typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(ARG_1, ARG_2, ARG_3) >
inline LUA_FUNC(nativeMemberReturn1Param3)
{
	if (CLASS* object = to<CLASS*>(L, -4))
	{
		RET_1 ret1 = (object->*function)(to<ARG_1>(L, -3), to<ARG_2>(L, -2), to<ARG_3>(L, -1));
		sint pushed(push(L, ret1));
		return pushed;
	}
	return 0;
} // nativeMemberReturn1Param3

/** nativeStaticReturn1Param3 */
template< typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (* function)(ARG_1, ARG_2, ARG_3) >
inline LUA_FUNC(nativeStaticReturn1Param3)
{
	RET_1 ret1 = (*function)(to<ARG_1>(L, -3), to<ARG_2>(L, -2), to<ARG_3>(L, -1));
	sint pushed(push(L, ret1));
	return pushed;
} // nativeStaticReturn1Param3

/** nativeConstReturn1Param4 */
template< typename CLASS, typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4) const>
inline LUA_FUNC(nativeConstReturn1Param4)
{
	if (CLASS* object = to<CLASS*>(L, -5))
	{
		RET_1 ret1 = (object->*function)(to<ARG_1>(L, -4), to<ARG_2>(L, -3), to<ARG_3>(L, -2), to<ARG_4>(L, -1));
		sint pushed(push(L, ret1));
		return pushed;
	}
	return 0;
} // nativeConstReturn1Param4

/** nativeMemberReturn1Param4 */
template< typename CLASS, typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4) >
inline LUA_FUNC(nativeMemberReturn1Param4)
{
	if (CLASS* object = to<CLASS*>(L, -5))
	{
		RET_1 ret1 = (object->*function)(to<ARG_1>(L, -4), to<ARG_2>(L, -3), to<ARG_3>(L, -2), to<ARG_4>(L, -1));
		sint pushed(push(L, ret1));
		return pushed;
	}
	return 0;
} // nativeMemberReturn1Param4

/** nativeStaticReturn1Param4 */
template< typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (* function)(ARG_1, ARG_2, ARG_3, ARG_4) >
inline LUA_FUNC(nativeStaticReturn1Param4)
{
	RET_1 ret1 = (*function)(to<ARG_1>(L, -4), to<ARG_2>(L, -3), to<ARG_3>(L, -2), to<ARG_4>(L, -1));
	sint pushed(push(L, ret1));
	return pushed;
} // nativeStaticReturn1Param4

/** nativeConstReturn1Param5 */
template< typename CLASS, typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) const>
inline LUA_FUNC(nativeConstReturn1Param5)
{
	if (CLASS* object = to<CLASS*>(L, -6))
	{
		RET_1 ret1 = (object->*function)(to<ARG_1>(L, -5), to<ARG_2>(L, -4), to<ARG_3>(L, -3), to<ARG_4>(L, -2), to<ARG_5>(L, -1));
		sint pushed(push(L, ret1));
		return pushed;
	}
	return 0;
} // nativeConstReturn1Param5

/** nativeMemberReturn1Param5 */
template< typename CLASS, typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline LUA_FUNC(nativeMemberReturn1Param5)
{
	if (CLASS* object = to<CLASS*>(L, -6))
	{
		RET_1 ret1 = (object->*function)(to<ARG_1>(L, -5), to<ARG_2>(L, -4), to<ARG_3>(L, -3), to<ARG_4>(L, -2), to<ARG_5>(L, -1));
		sint pushed(push(L, ret1));
		return pushed;
	}
	return 0;
} // nativeMemberReturn1Param5

/** nativeStaticReturn1Param5 */
template< typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline LUA_FUNC(nativeStaticReturn1Param5)
{
	RET_1 ret1 = (*function)(to<ARG_1>(L, -5), to<ARG_2>(L, -4), to<ARG_3>(L, -3), to<ARG_4>(L, -2), to<ARG_5>(L, -1));
	sint pushed(push(L, ret1));
	return pushed;
} // nativeStaticReturn1Param5

/** nativeConstReturn1Param6 */
template< typename CLASS, typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) const>
inline LUA_FUNC(nativeConstReturn1Param6)
{
	if (CLASS* object = to<CLASS*>(L, -7))
	{
		RET_1 ret1 = (object->*function)(to<ARG_1>(L, -6), to<ARG_2>(L, -5), to<ARG_3>(L, -4), to<ARG_4>(L, -3), to<ARG_5>(L, -2), to<ARG_6>(L, -1));
		sint pushed(push(L, ret1));
		return pushed;
	}
	return 0;
} // nativeConstReturn1Param6

/** nativeMemberReturn1Param6 */
template< typename CLASS, typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline LUA_FUNC(nativeMemberReturn1Param6)
{
	if (CLASS* object = to<CLASS*>(L, -7))
	{
		RET_1 ret1 = (object->*function)(to<ARG_1>(L, -6), to<ARG_2>(L, -5), to<ARG_3>(L, -4), to<ARG_4>(L, -3), to<ARG_5>(L, -2), to<ARG_6>(L, -1));
		sint pushed(push(L, ret1));
		return pushed;
	}
	return 0;
} // nativeMemberReturn1Param6

/** nativeStaticReturn1Param6 */
template< typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline LUA_FUNC(nativeStaticReturn1Param6)
{
	RET_1 ret1 = (*function)(to<ARG_1>(L, -6), to<ARG_2>(L, -5), to<ARG_3>(L, -4), to<ARG_4>(L, -3), to<ARG_5>(L, -2), to<ARG_6>(L, -1));
	sint pushed(push(L, ret1));
	return pushed;
} // nativeStaticReturn1Param6

/** nativeConstReturn1Param7 */
template< typename CLASS, typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) const>
inline LUA_FUNC(nativeConstReturn1Param7)
{
	if (CLASS* object = to<CLASS*>(L, -8))
	{
		RET_1 ret1 = (object->*function)(to<ARG_1>(L, -7), to<ARG_2>(L, -6), to<ARG_3>(L, -5), to<ARG_4>(L, -4), to<ARG_5>(L, -3), to<ARG_6>(L, -2), to<ARG_7>(L, -1));
		sint pushed(push(L, ret1));
		return pushed;
	}
	return 0;
} // nativeConstReturn1Param7

/** nativeMemberReturn1Param7 */
template< typename CLASS, typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline LUA_FUNC(nativeMemberReturn1Param7)
{
	if (CLASS* object = to<CLASS*>(L, -8))
	{
		RET_1 ret1 = (object->*function)(to<ARG_1>(L, -7), to<ARG_2>(L, -6), to<ARG_3>(L, -5), to<ARG_4>(L, -4), to<ARG_5>(L, -3), to<ARG_6>(L, -2), to<ARG_7>(L, -1));
		sint pushed(push(L, ret1));
		return pushed;
	}
	return 0;
} // nativeMemberReturn1Param7

/** nativeStaticReturn1Param7 */
template< typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline LUA_FUNC(nativeStaticReturn1Param7)
{
	RET_1 ret1 = (*function)(to<ARG_1>(L, -7), to<ARG_2>(L, -6), to<ARG_3>(L, -5), to<ARG_4>(L, -4), to<ARG_5>(L, -3), to<ARG_6>(L, -2), to<ARG_7>(L, -1));
	sint pushed(push(L, ret1));
	return pushed;
} // nativeStaticReturn1Param7

/** nativeConstReturn1Param8 */
template< typename CLASS, typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) const>
inline LUA_FUNC(nativeConstReturn1Param8)
{
	if (CLASS* object = to<CLASS*>(L, -9))
	{
		RET_1 ret1 = (object->*function)(to<ARG_1>(L, -8), to<ARG_2>(L, -7), to<ARG_3>(L, -6), to<ARG_4>(L, -5), to<ARG_5>(L, -4), to<ARG_6>(L, -3), to<ARG_7>(L, -2), to<ARG_8>(L, -1));
		sint pushed(push(L, ret1));
		return pushed;
	}
	return 0;
} // nativeConstReturn1Param8

/** nativeMemberReturn1Param8 */
template< typename CLASS, typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline LUA_FUNC(nativeMemberReturn1Param8)
{
	if (CLASS* object = to<CLASS*>(L, -9))
	{
		RET_1 ret1 = (object->*function)(to<ARG_1>(L, -8), to<ARG_2>(L, -7), to<ARG_3>(L, -6), to<ARG_4>(L, -5), to<ARG_5>(L, -4), to<ARG_6>(L, -3), to<ARG_7>(L, -2), to<ARG_8>(L, -1));
		sint pushed(push(L, ret1));
		return pushed;
	}
	return 0;
} // nativeMemberReturn1Param8

/** nativeStaticReturn1Param8 */
template< typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline LUA_FUNC(nativeStaticReturn1Param8)
{
	RET_1 ret1 = (*function)(to<ARG_1>(L, -8), to<ARG_2>(L, -7), to<ARG_3>(L, -6), to<ARG_4>(L, -5), to<ARG_5>(L, -4), to<ARG_6>(L, -3), to<ARG_7>(L, -2), to<ARG_8>(L, -1));
	sint pushed(push(L, ret1));
	return pushed;
} // nativeStaticReturn1Param8

/** nativeConstReturn1Param9 */
template< typename CLASS, typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) const>
inline LUA_FUNC(nativeConstReturn1Param9)
{
	if (CLASS* object = to<CLASS*>(L, -10))
	{
		RET_1 ret1 = (object->*function)(to<ARG_1>(L, -9), to<ARG_2>(L, -8), to<ARG_3>(L, -7), to<ARG_4>(L, -6), to<ARG_5>(L, -5), to<ARG_6>(L, -4), to<ARG_7>(L, -3), to<ARG_8>(L, -2), to<ARG_9>(L, -1));
		sint pushed(push(L, ret1));
		return pushed;
	}
	return 0;
} // nativeConstReturn1Param9

/** nativeMemberReturn1Param9 */
template< typename CLASS, typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline LUA_FUNC(nativeMemberReturn1Param9)
{
	if (CLASS* object = to<CLASS*>(L, -10))
	{
		RET_1 ret1 = (object->*function)(to<ARG_1>(L, -9), to<ARG_2>(L, -8), to<ARG_3>(L, -7), to<ARG_4>(L, -6), to<ARG_5>(L, -5), to<ARG_6>(L, -4), to<ARG_7>(L, -3), to<ARG_8>(L, -2), to<ARG_9>(L, -1));
		sint pushed(push(L, ret1));
		return pushed;
	}
	return 0;
} // nativeMemberReturn1Param9

/** nativeStaticReturn1Param9 */
template< typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline LUA_FUNC(nativeStaticReturn1Param9)
{
	RET_1 ret1 = (*function)(to<ARG_1>(L, -9), to<ARG_2>(L, -8), to<ARG_3>(L, -7), to<ARG_4>(L, -6), to<ARG_5>(L, -5), to<ARG_6>(L, -4), to<ARG_7>(L, -3), to<ARG_8>(L, -2), to<ARG_9>(L, -1));
	sint pushed(push(L, ret1));
	return pushed;
} // nativeStaticReturn1Param9

/** nativeConstReturn1Param10 */
template< typename CLASS, typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) const>
inline LUA_FUNC(nativeConstReturn1Param10)
{
	if (CLASS* object = to<CLASS*>(L, -11))
	{
		RET_1 ret1 = (object->*function)(to<ARG_1>(L, -10), to<ARG_2>(L, -9), to<ARG_3>(L, -8), to<ARG_4>(L, -7), to<ARG_5>(L, -6), to<ARG_6>(L, -5), to<ARG_7>(L, -4), to<ARG_8>(L, -3), to<ARG_9>(L, -2), to<ARG_10>(L, -1));
		sint pushed(push(L, ret1));
		return pushed;
	}
	return 0;
} // nativeConstReturn1Param10

/** nativeMemberReturn1Param10 */
template< typename CLASS, typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline LUA_FUNC(nativeMemberReturn1Param10)
{
	if (CLASS* object = to<CLASS*>(L, -11))
	{
		RET_1 ret1 = (object->*function)(to<ARG_1>(L, -10), to<ARG_2>(L, -9), to<ARG_3>(L, -8), to<ARG_4>(L, -7), to<ARG_5>(L, -6), to<ARG_6>(L, -5), to<ARG_7>(L, -4), to<ARG_8>(L, -3), to<ARG_9>(L, -2), to<ARG_10>(L, -1));
		sint pushed(push(L, ret1));
		return pushed;
	}
	return 0;
} // nativeMemberReturn1Param10

/** nativeStaticReturn1Param10 */
template< typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline LUA_FUNC(nativeStaticReturn1Param10)
{
	RET_1 ret1 = (*function)(to<ARG_1>(L, -10), to<ARG_2>(L, -9), to<ARG_3>(L, -8), to<ARG_4>(L, -7), to<ARG_5>(L, -6), to<ARG_6>(L, -5), to<ARG_7>(L, -4), to<ARG_8>(L, -3), to<ARG_9>(L, -2), to<ARG_10>(L, -1));
	sint pushed(push(L, ret1));
	return pushed;
} // nativeStaticReturn1Param10

/** nativeConstReturn2Param0 */
template< typename CLASS, typename RET_1, typename RET_2, RET_1 (CLASS::* function)(RET_2&) const>
inline LUA_FUNC(nativeConstReturn2Param0)
{
	if (CLASS* object = to<CLASS*>(L, -1))
	{
		RET_2 ret2;
		RET_1 ret1 = (object->*function)(ret2);
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		return pushed;
	}
	return 0;
} // nativeConstReturn2Param0

/** nativeMemberReturn2Param0 */
template< typename CLASS, typename RET_1, typename RET_2, RET_1 (CLASS::* function)(RET_2&) >
inline LUA_FUNC(nativeMemberReturn2Param0)
{
	if (CLASS* object = to<CLASS*>(L, -1))
	{
		RET_2 ret2;
		RET_1 ret1 = (object->*function)(ret2);
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		return pushed;
	}
	return 0;
} // nativeMemberReturn2Param0

/** nativeStaticReturn2Param0 */
template< typename RET_1, typename RET_2, RET_1 (* function)(RET_2&) >
inline LUA_FUNC(nativeStaticReturn2Param0)
{
	RET_2 ret2;
	RET_1 ret1 = (*function)(ret2);
	sint pushed(push(L, ret1));
	pushed += push(L, ret2);
	return pushed;
} // nativeStaticReturn2Param0

/** nativeConstReturn2Param1 */
template< typename CLASS, typename RET_1, typename RET_2, typename ARG_1, RET_1 (CLASS::* function)(RET_2&, ARG_1) const>
inline LUA_FUNC(nativeConstReturn2Param1)
{
	if (CLASS* object = to<CLASS*>(L, -2))
	{
		RET_2 ret2;
		RET_1 ret1 = (object->*function)(ret2, to<ARG_1>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		return pushed;
	}
	return 0;
} // nativeConstReturn2Param1

/** nativeMemberReturn2Param1 */
template< typename CLASS, typename RET_1, typename RET_2, typename ARG_1, RET_1 (CLASS::* function)(RET_2&, ARG_1) >
inline LUA_FUNC(nativeMemberReturn2Param1)
{
	if (CLASS* object = to<CLASS*>(L, -2))
	{
		RET_2 ret2;
		RET_1 ret1 = (object->*function)(ret2, to<ARG_1>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		return pushed;
	}
	return 0;
} // nativeMemberReturn2Param1

/** nativeStaticReturn2Param1 */
template< typename RET_1, typename RET_2, typename ARG_1, RET_1 (* function)(RET_2&, ARG_1) >
inline LUA_FUNC(nativeStaticReturn2Param1)
{
	RET_2 ret2;
	RET_1 ret1 = (*function)(ret2, to<ARG_1>(L, -1));
	sint pushed(push(L, ret1));
	pushed += push(L, ret2);
	return pushed;
} // nativeStaticReturn2Param1

/** nativeConstReturn2Param2 */
template< typename CLASS, typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(RET_2&, ARG_1, ARG_2) const>
inline LUA_FUNC(nativeConstReturn2Param2)
{
	if (CLASS* object = to<CLASS*>(L, -3))
	{
		RET_2 ret2;
		RET_1 ret1 = (object->*function)(ret2, to<ARG_1>(L, -2), to<ARG_2>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		return pushed;
	}
	return 0;
} // nativeConstReturn2Param2

/** nativeMemberReturn2Param2 */
template< typename CLASS, typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(RET_2&, ARG_1, ARG_2) >
inline LUA_FUNC(nativeMemberReturn2Param2)
{
	if (CLASS* object = to<CLASS*>(L, -3))
	{
		RET_2 ret2;
		RET_1 ret1 = (object->*function)(ret2, to<ARG_1>(L, -2), to<ARG_2>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		return pushed;
	}
	return 0;
} // nativeMemberReturn2Param2

/** nativeStaticReturn2Param2 */
template< typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, RET_1 (* function)(RET_2&, ARG_1, ARG_2) >
inline LUA_FUNC(nativeStaticReturn2Param2)
{
	RET_2 ret2;
	RET_1 ret1 = (*function)(ret2, to<ARG_1>(L, -2), to<ARG_2>(L, -1));
	sint pushed(push(L, ret1));
	pushed += push(L, ret2);
	return pushed;
} // nativeStaticReturn2Param2

/** nativeConstReturn2Param3 */
template< typename CLASS, typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(RET_2&, ARG_1, ARG_2, ARG_3) const>
inline LUA_FUNC(nativeConstReturn2Param3)
{
	if (CLASS* object = to<CLASS*>(L, -4))
	{
		RET_2 ret2;
		RET_1 ret1 = (object->*function)(ret2, to<ARG_1>(L, -3), to<ARG_2>(L, -2), to<ARG_3>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		return pushed;
	}
	return 0;
} // nativeConstReturn2Param3

/** nativeMemberReturn2Param3 */
template< typename CLASS, typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(RET_2&, ARG_1, ARG_2, ARG_3) >
inline LUA_FUNC(nativeMemberReturn2Param3)
{
	if (CLASS* object = to<CLASS*>(L, -4))
	{
		RET_2 ret2;
		RET_1 ret1 = (object->*function)(ret2, to<ARG_1>(L, -3), to<ARG_2>(L, -2), to<ARG_3>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		return pushed;
	}
	return 0;
} // nativeMemberReturn2Param3

/** nativeStaticReturn2Param3 */
template< typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (* function)(RET_2&, ARG_1, ARG_2, ARG_3) >
inline LUA_FUNC(nativeStaticReturn2Param3)
{
	RET_2 ret2;
	RET_1 ret1 = (*function)(ret2, to<ARG_1>(L, -3), to<ARG_2>(L, -2), to<ARG_3>(L, -1));
	sint pushed(push(L, ret1));
	pushed += push(L, ret2);
	return pushed;
} // nativeStaticReturn2Param3

/** nativeConstReturn2Param4 */
template< typename CLASS, typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4) const>
inline LUA_FUNC(nativeConstReturn2Param4)
{
	if (CLASS* object = to<CLASS*>(L, -5))
	{
		RET_2 ret2;
		RET_1 ret1 = (object->*function)(ret2, to<ARG_1>(L, -4), to<ARG_2>(L, -3), to<ARG_3>(L, -2), to<ARG_4>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		return pushed;
	}
	return 0;
} // nativeConstReturn2Param4

/** nativeMemberReturn2Param4 */
template< typename CLASS, typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline LUA_FUNC(nativeMemberReturn2Param4)
{
	if (CLASS* object = to<CLASS*>(L, -5))
	{
		RET_2 ret2;
		RET_1 ret1 = (object->*function)(ret2, to<ARG_1>(L, -4), to<ARG_2>(L, -3), to<ARG_3>(L, -2), to<ARG_4>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		return pushed;
	}
	return 0;
} // nativeMemberReturn2Param4

/** nativeStaticReturn2Param4 */
template< typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline LUA_FUNC(nativeStaticReturn2Param4)
{
	RET_2 ret2;
	RET_1 ret1 = (*function)(ret2, to<ARG_1>(L, -4), to<ARG_2>(L, -3), to<ARG_3>(L, -2), to<ARG_4>(L, -1));
	sint pushed(push(L, ret1));
	pushed += push(L, ret2);
	return pushed;
} // nativeStaticReturn2Param4

/** nativeConstReturn2Param5 */
template< typename CLASS, typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) const>
inline LUA_FUNC(nativeConstReturn2Param5)
{
	if (CLASS* object = to<CLASS*>(L, -6))
	{
		RET_2 ret2;
		RET_1 ret1 = (object->*function)(ret2, to<ARG_1>(L, -5), to<ARG_2>(L, -4), to<ARG_3>(L, -3), to<ARG_4>(L, -2), to<ARG_5>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		return pushed;
	}
	return 0;
} // nativeConstReturn2Param5

/** nativeMemberReturn2Param5 */
template< typename CLASS, typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline LUA_FUNC(nativeMemberReturn2Param5)
{
	if (CLASS* object = to<CLASS*>(L, -6))
	{
		RET_2 ret2;
		RET_1 ret1 = (object->*function)(ret2, to<ARG_1>(L, -5), to<ARG_2>(L, -4), to<ARG_3>(L, -3), to<ARG_4>(L, -2), to<ARG_5>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		return pushed;
	}
	return 0;
} // nativeMemberReturn2Param5

/** nativeStaticReturn2Param5 */
template< typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline LUA_FUNC(nativeStaticReturn2Param5)
{
	RET_2 ret2;
	RET_1 ret1 = (*function)(ret2, to<ARG_1>(L, -5), to<ARG_2>(L, -4), to<ARG_3>(L, -3), to<ARG_4>(L, -2), to<ARG_5>(L, -1));
	sint pushed(push(L, ret1));
	pushed += push(L, ret2);
	return pushed;
} // nativeStaticReturn2Param5

/** nativeConstReturn2Param6 */
template< typename CLASS, typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) const>
inline LUA_FUNC(nativeConstReturn2Param6)
{
	if (CLASS* object = to<CLASS*>(L, -7))
	{
		RET_2 ret2;
		RET_1 ret1 = (object->*function)(ret2, to<ARG_1>(L, -6), to<ARG_2>(L, -5), to<ARG_3>(L, -4), to<ARG_4>(L, -3), to<ARG_5>(L, -2), to<ARG_6>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		return pushed;
	}
	return 0;
} // nativeConstReturn2Param6

/** nativeMemberReturn2Param6 */
template< typename CLASS, typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline LUA_FUNC(nativeMemberReturn2Param6)
{
	if (CLASS* object = to<CLASS*>(L, -7))
	{
		RET_2 ret2;
		RET_1 ret1 = (object->*function)(ret2, to<ARG_1>(L, -6), to<ARG_2>(L, -5), to<ARG_3>(L, -4), to<ARG_4>(L, -3), to<ARG_5>(L, -2), to<ARG_6>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		return pushed;
	}
	return 0;
} // nativeMemberReturn2Param6

/** nativeStaticReturn2Param6 */
template< typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline LUA_FUNC(nativeStaticReturn2Param6)
{
	RET_2 ret2;
	RET_1 ret1 = (*function)(ret2, to<ARG_1>(L, -6), to<ARG_2>(L, -5), to<ARG_3>(L, -4), to<ARG_4>(L, -3), to<ARG_5>(L, -2), to<ARG_6>(L, -1));
	sint pushed(push(L, ret1));
	pushed += push(L, ret2);
	return pushed;
} // nativeStaticReturn2Param6

/** nativeConstReturn2Param7 */
template< typename CLASS, typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) const>
inline LUA_FUNC(nativeConstReturn2Param7)
{
	if (CLASS* object = to<CLASS*>(L, -8))
	{
		RET_2 ret2;
		RET_1 ret1 = (object->*function)(ret2, to<ARG_1>(L, -7), to<ARG_2>(L, -6), to<ARG_3>(L, -5), to<ARG_4>(L, -4), to<ARG_5>(L, -3), to<ARG_6>(L, -2), to<ARG_7>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		return pushed;
	}
	return 0;
} // nativeConstReturn2Param7

/** nativeMemberReturn2Param7 */
template< typename CLASS, typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline LUA_FUNC(nativeMemberReturn2Param7)
{
	if (CLASS* object = to<CLASS*>(L, -8))
	{
		RET_2 ret2;
		RET_1 ret1 = (object->*function)(ret2, to<ARG_1>(L, -7), to<ARG_2>(L, -6), to<ARG_3>(L, -5), to<ARG_4>(L, -4), to<ARG_5>(L, -3), to<ARG_6>(L, -2), to<ARG_7>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		return pushed;
	}
	return 0;
} // nativeMemberReturn2Param7

/** nativeStaticReturn2Param7 */
template< typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline LUA_FUNC(nativeStaticReturn2Param7)
{
	RET_2 ret2;
	RET_1 ret1 = (*function)(ret2, to<ARG_1>(L, -7), to<ARG_2>(L, -6), to<ARG_3>(L, -5), to<ARG_4>(L, -4), to<ARG_5>(L, -3), to<ARG_6>(L, -2), to<ARG_7>(L, -1));
	sint pushed(push(L, ret1));
	pushed += push(L, ret2);
	return pushed;
} // nativeStaticReturn2Param7

/** nativeConstReturn2Param8 */
template< typename CLASS, typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) const>
inline LUA_FUNC(nativeConstReturn2Param8)
{
	if (CLASS* object = to<CLASS*>(L, -9))
	{
		RET_2 ret2;
		RET_1 ret1 = (object->*function)(ret2, to<ARG_1>(L, -8), to<ARG_2>(L, -7), to<ARG_3>(L, -6), to<ARG_4>(L, -5), to<ARG_5>(L, -4), to<ARG_6>(L, -3), to<ARG_7>(L, -2), to<ARG_8>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		return pushed;
	}
	return 0;
} // nativeConstReturn2Param8

/** nativeMemberReturn2Param8 */
template< typename CLASS, typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline LUA_FUNC(nativeMemberReturn2Param8)
{
	if (CLASS* object = to<CLASS*>(L, -9))
	{
		RET_2 ret2;
		RET_1 ret1 = (object->*function)(ret2, to<ARG_1>(L, -8), to<ARG_2>(L, -7), to<ARG_3>(L, -6), to<ARG_4>(L, -5), to<ARG_5>(L, -4), to<ARG_6>(L, -3), to<ARG_7>(L, -2), to<ARG_8>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		return pushed;
	}
	return 0;
} // nativeMemberReturn2Param8

/** nativeStaticReturn2Param8 */
template< typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline LUA_FUNC(nativeStaticReturn2Param8)
{
	RET_2 ret2;
	RET_1 ret1 = (*function)(ret2, to<ARG_1>(L, -8), to<ARG_2>(L, -7), to<ARG_3>(L, -6), to<ARG_4>(L, -5), to<ARG_5>(L, -4), to<ARG_6>(L, -3), to<ARG_7>(L, -2), to<ARG_8>(L, -1));
	sint pushed(push(L, ret1));
	pushed += push(L, ret2);
	return pushed;
} // nativeStaticReturn2Param8

/** nativeConstReturn2Param9 */
template< typename CLASS, typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) const>
inline LUA_FUNC(nativeConstReturn2Param9)
{
	if (CLASS* object = to<CLASS*>(L, -10))
	{
		RET_2 ret2;
		RET_1 ret1 = (object->*function)(ret2, to<ARG_1>(L, -9), to<ARG_2>(L, -8), to<ARG_3>(L, -7), to<ARG_4>(L, -6), to<ARG_5>(L, -5), to<ARG_6>(L, -4), to<ARG_7>(L, -3), to<ARG_8>(L, -2), to<ARG_9>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		return pushed;
	}
	return 0;
} // nativeConstReturn2Param9

/** nativeMemberReturn2Param9 */
template< typename CLASS, typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline LUA_FUNC(nativeMemberReturn2Param9)
{
	if (CLASS* object = to<CLASS*>(L, -10))
	{
		RET_2 ret2;
		RET_1 ret1 = (object->*function)(ret2, to<ARG_1>(L, -9), to<ARG_2>(L, -8), to<ARG_3>(L, -7), to<ARG_4>(L, -6), to<ARG_5>(L, -5), to<ARG_6>(L, -4), to<ARG_7>(L, -3), to<ARG_8>(L, -2), to<ARG_9>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		return pushed;
	}
	return 0;
} // nativeMemberReturn2Param9

/** nativeStaticReturn2Param9 */
template< typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline LUA_FUNC(nativeStaticReturn2Param9)
{
	RET_2 ret2;
	RET_1 ret1 = (*function)(ret2, to<ARG_1>(L, -9), to<ARG_2>(L, -8), to<ARG_3>(L, -7), to<ARG_4>(L, -6), to<ARG_5>(L, -5), to<ARG_6>(L, -4), to<ARG_7>(L, -3), to<ARG_8>(L, -2), to<ARG_9>(L, -1));
	sint pushed(push(L, ret1));
	pushed += push(L, ret2);
	return pushed;
} // nativeStaticReturn2Param9

/** nativeConstReturn2Param10 */
template< typename CLASS, typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) const>
inline LUA_FUNC(nativeConstReturn2Param10)
{
	if (CLASS* object = to<CLASS*>(L, -11))
	{
		RET_2 ret2;
		RET_1 ret1 = (object->*function)(ret2, to<ARG_1>(L, -10), to<ARG_2>(L, -9), to<ARG_3>(L, -8), to<ARG_4>(L, -7), to<ARG_5>(L, -6), to<ARG_6>(L, -5), to<ARG_7>(L, -4), to<ARG_8>(L, -3), to<ARG_9>(L, -2), to<ARG_10>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		return pushed;
	}
	return 0;
} // nativeConstReturn2Param10

/** nativeMemberReturn2Param10 */
template< typename CLASS, typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline LUA_FUNC(nativeMemberReturn2Param10)
{
	if (CLASS* object = to<CLASS*>(L, -11))
	{
		RET_2 ret2;
		RET_1 ret1 = (object->*function)(ret2, to<ARG_1>(L, -10), to<ARG_2>(L, -9), to<ARG_3>(L, -8), to<ARG_4>(L, -7), to<ARG_5>(L, -6), to<ARG_6>(L, -5), to<ARG_7>(L, -4), to<ARG_8>(L, -3), to<ARG_9>(L, -2), to<ARG_10>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		return pushed;
	}
	return 0;
} // nativeMemberReturn2Param10

/** nativeStaticReturn2Param10 */
template< typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline LUA_FUNC(nativeStaticReturn2Param10)
{
	RET_2 ret2;
	RET_1 ret1 = (*function)(ret2, to<ARG_1>(L, -10), to<ARG_2>(L, -9), to<ARG_3>(L, -8), to<ARG_4>(L, -7), to<ARG_5>(L, -6), to<ARG_6>(L, -5), to<ARG_7>(L, -4), to<ARG_8>(L, -3), to<ARG_9>(L, -2), to<ARG_10>(L, -1));
	sint pushed(push(L, ret1));
	pushed += push(L, ret2);
	return pushed;
} // nativeStaticReturn2Param10

/** nativeConstReturn3Param0 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, RET_1 (CLASS::* function)(RET_2&, RET_3&) const>
inline LUA_FUNC(nativeConstReturn3Param0)
{
	if (CLASS* object = to<CLASS*>(L, -1))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_1 ret1 = (object->*function)(ret2, ret3);
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		return pushed;
	}
	return 0;
} // nativeConstReturn3Param0

/** nativeMemberReturn3Param0 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, RET_1 (CLASS::* function)(RET_2&, RET_3&) >
inline LUA_FUNC(nativeMemberReturn3Param0)
{
	if (CLASS* object = to<CLASS*>(L, -1))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_1 ret1 = (object->*function)(ret2, ret3);
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		return pushed;
	}
	return 0;
} // nativeMemberReturn3Param0

/** nativeStaticReturn3Param0 */
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

/** nativeConstReturn3Param1 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1) const>
inline LUA_FUNC(nativeConstReturn3Param1)
{
	if (CLASS* object = to<CLASS*>(L, -2))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_1 ret1 = (object->*function)(ret2, ret3, to<ARG_1>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		return pushed;
	}
	return 0;
} // nativeConstReturn3Param1

/** nativeMemberReturn3Param1 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1) >
inline LUA_FUNC(nativeMemberReturn3Param1)
{
	if (CLASS* object = to<CLASS*>(L, -2))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_1 ret1 = (object->*function)(ret2, ret3, to<ARG_1>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		return pushed;
	}
	return 0;
} // nativeMemberReturn3Param1

/** nativeStaticReturn3Param1 */
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

/** nativeConstReturn3Param2 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1, ARG_2) const>
inline LUA_FUNC(nativeConstReturn3Param2)
{
	if (CLASS* object = to<CLASS*>(L, -3))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_1 ret1 = (object->*function)(ret2, ret3, to<ARG_1>(L, -2), to<ARG_2>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		return pushed;
	}
	return 0;
} // nativeConstReturn3Param2

/** nativeMemberReturn3Param2 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1, ARG_2) >
inline LUA_FUNC(nativeMemberReturn3Param2)
{
	if (CLASS* object = to<CLASS*>(L, -3))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_1 ret1 = (object->*function)(ret2, ret3, to<ARG_1>(L, -2), to<ARG_2>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		return pushed;
	}
	return 0;
} // nativeMemberReturn3Param2

/** nativeStaticReturn3Param2 */
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

/** nativeConstReturn3Param3 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3) const>
inline LUA_FUNC(nativeConstReturn3Param3)
{
	if (CLASS* object = to<CLASS*>(L, -4))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_1 ret1 = (object->*function)(ret2, ret3, to<ARG_1>(L, -3), to<ARG_2>(L, -2), to<ARG_3>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		return pushed;
	}
	return 0;
} // nativeConstReturn3Param3

/** nativeMemberReturn3Param3 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3) >
inline LUA_FUNC(nativeMemberReturn3Param3)
{
	if (CLASS* object = to<CLASS*>(L, -4))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_1 ret1 = (object->*function)(ret2, ret3, to<ARG_1>(L, -3), to<ARG_2>(L, -2), to<ARG_3>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		return pushed;
	}
	return 0;
} // nativeMemberReturn3Param3

/** nativeStaticReturn3Param3 */
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

/** nativeConstReturn3Param4 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4) const>
inline LUA_FUNC(nativeConstReturn3Param4)
{
	if (CLASS* object = to<CLASS*>(L, -5))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_1 ret1 = (object->*function)(ret2, ret3, to<ARG_1>(L, -4), to<ARG_2>(L, -3), to<ARG_3>(L, -2), to<ARG_4>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		return pushed;
	}
	return 0;
} // nativeConstReturn3Param4

/** nativeMemberReturn3Param4 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline LUA_FUNC(nativeMemberReturn3Param4)
{
	if (CLASS* object = to<CLASS*>(L, -5))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_1 ret1 = (object->*function)(ret2, ret3, to<ARG_1>(L, -4), to<ARG_2>(L, -3), to<ARG_3>(L, -2), to<ARG_4>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		return pushed;
	}
	return 0;
} // nativeMemberReturn3Param4

/** nativeStaticReturn3Param4 */
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

/** nativeConstReturn3Param5 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) const>
inline LUA_FUNC(nativeConstReturn3Param5)
{
	if (CLASS* object = to<CLASS*>(L, -6))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_1 ret1 = (object->*function)(ret2, ret3, to<ARG_1>(L, -5), to<ARG_2>(L, -4), to<ARG_3>(L, -3), to<ARG_4>(L, -2), to<ARG_5>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		return pushed;
	}
	return 0;
} // nativeConstReturn3Param5

/** nativeMemberReturn3Param5 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline LUA_FUNC(nativeMemberReturn3Param5)
{
	if (CLASS* object = to<CLASS*>(L, -6))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_1 ret1 = (object->*function)(ret2, ret3, to<ARG_1>(L, -5), to<ARG_2>(L, -4), to<ARG_3>(L, -3), to<ARG_4>(L, -2), to<ARG_5>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		return pushed;
	}
	return 0;
} // nativeMemberReturn3Param5

/** nativeStaticReturn3Param5 */
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

/** nativeConstReturn3Param6 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) const>
inline LUA_FUNC(nativeConstReturn3Param6)
{
	if (CLASS* object = to<CLASS*>(L, -7))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_1 ret1 = (object->*function)(ret2, ret3, to<ARG_1>(L, -6), to<ARG_2>(L, -5), to<ARG_3>(L, -4), to<ARG_4>(L, -3), to<ARG_5>(L, -2), to<ARG_6>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		return pushed;
	}
	return 0;
} // nativeConstReturn3Param6

/** nativeMemberReturn3Param6 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline LUA_FUNC(nativeMemberReturn3Param6)
{
	if (CLASS* object = to<CLASS*>(L, -7))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_1 ret1 = (object->*function)(ret2, ret3, to<ARG_1>(L, -6), to<ARG_2>(L, -5), to<ARG_3>(L, -4), to<ARG_4>(L, -3), to<ARG_5>(L, -2), to<ARG_6>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		return pushed;
	}
	return 0;
} // nativeMemberReturn3Param6

/** nativeStaticReturn3Param6 */
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

/** nativeConstReturn3Param7 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) const>
inline LUA_FUNC(nativeConstReturn3Param7)
{
	if (CLASS* object = to<CLASS*>(L, -8))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_1 ret1 = (object->*function)(ret2, ret3, to<ARG_1>(L, -7), to<ARG_2>(L, -6), to<ARG_3>(L, -5), to<ARG_4>(L, -4), to<ARG_5>(L, -3), to<ARG_6>(L, -2), to<ARG_7>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		return pushed;
	}
	return 0;
} // nativeConstReturn3Param7

/** nativeMemberReturn3Param7 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline LUA_FUNC(nativeMemberReturn3Param7)
{
	if (CLASS* object = to<CLASS*>(L, -8))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_1 ret1 = (object->*function)(ret2, ret3, to<ARG_1>(L, -7), to<ARG_2>(L, -6), to<ARG_3>(L, -5), to<ARG_4>(L, -4), to<ARG_5>(L, -3), to<ARG_6>(L, -2), to<ARG_7>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		return pushed;
	}
	return 0;
} // nativeMemberReturn3Param7

/** nativeStaticReturn3Param7 */
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

/** nativeConstReturn3Param8 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) const>
inline LUA_FUNC(nativeConstReturn3Param8)
{
	if (CLASS* object = to<CLASS*>(L, -9))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_1 ret1 = (object->*function)(ret2, ret3, to<ARG_1>(L, -8), to<ARG_2>(L, -7), to<ARG_3>(L, -6), to<ARG_4>(L, -5), to<ARG_5>(L, -4), to<ARG_6>(L, -3), to<ARG_7>(L, -2), to<ARG_8>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		return pushed;
	}
	return 0;
} // nativeConstReturn3Param8

/** nativeMemberReturn3Param8 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline LUA_FUNC(nativeMemberReturn3Param8)
{
	if (CLASS* object = to<CLASS*>(L, -9))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_1 ret1 = (object->*function)(ret2, ret3, to<ARG_1>(L, -8), to<ARG_2>(L, -7), to<ARG_3>(L, -6), to<ARG_4>(L, -5), to<ARG_5>(L, -4), to<ARG_6>(L, -3), to<ARG_7>(L, -2), to<ARG_8>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		return pushed;
	}
	return 0;
} // nativeMemberReturn3Param8

/** nativeStaticReturn3Param8 */
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

/** nativeConstReturn3Param9 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) const>
inline LUA_FUNC(nativeConstReturn3Param9)
{
	if (CLASS* object = to<CLASS*>(L, -10))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_1 ret1 = (object->*function)(ret2, ret3, to<ARG_1>(L, -9), to<ARG_2>(L, -8), to<ARG_3>(L, -7), to<ARG_4>(L, -6), to<ARG_5>(L, -5), to<ARG_6>(L, -4), to<ARG_7>(L, -3), to<ARG_8>(L, -2), to<ARG_9>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		return pushed;
	}
	return 0;
} // nativeConstReturn3Param9

/** nativeMemberReturn3Param9 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline LUA_FUNC(nativeMemberReturn3Param9)
{
	if (CLASS* object = to<CLASS*>(L, -10))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_1 ret1 = (object->*function)(ret2, ret3, to<ARG_1>(L, -9), to<ARG_2>(L, -8), to<ARG_3>(L, -7), to<ARG_4>(L, -6), to<ARG_5>(L, -5), to<ARG_6>(L, -4), to<ARG_7>(L, -3), to<ARG_8>(L, -2), to<ARG_9>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		return pushed;
	}
	return 0;
} // nativeMemberReturn3Param9

/** nativeStaticReturn3Param9 */
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

/** nativeConstReturn3Param10 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) const>
inline LUA_FUNC(nativeConstReturn3Param10)
{
	if (CLASS* object = to<CLASS*>(L, -11))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_1 ret1 = (object->*function)(ret2, ret3, to<ARG_1>(L, -10), to<ARG_2>(L, -9), to<ARG_3>(L, -8), to<ARG_4>(L, -7), to<ARG_5>(L, -6), to<ARG_6>(L, -5), to<ARG_7>(L, -4), to<ARG_8>(L, -3), to<ARG_9>(L, -2), to<ARG_10>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		return pushed;
	}
	return 0;
} // nativeConstReturn3Param10

/** nativeMemberReturn3Param10 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline LUA_FUNC(nativeMemberReturn3Param10)
{
	if (CLASS* object = to<CLASS*>(L, -11))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_1 ret1 = (object->*function)(ret2, ret3, to<ARG_1>(L, -10), to<ARG_2>(L, -9), to<ARG_3>(L, -8), to<ARG_4>(L, -7), to<ARG_5>(L, -6), to<ARG_6>(L, -5), to<ARG_7>(L, -4), to<ARG_8>(L, -3), to<ARG_9>(L, -2), to<ARG_10>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		return pushed;
	}
	return 0;
} // nativeMemberReturn3Param10

/** nativeStaticReturn3Param10 */
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

/** nativeConstReturn4Param0 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&) const>
inline LUA_FUNC(nativeConstReturn4Param0)
{
	if (CLASS* object = to<CLASS*>(L, -1))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4);
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		return pushed;
	}
	return 0;
} // nativeConstReturn4Param0

/** nativeMemberReturn4Param0 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&) >
inline LUA_FUNC(nativeMemberReturn4Param0)
{
	if (CLASS* object = to<CLASS*>(L, -1))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4);
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		return pushed;
	}
	return 0;
} // nativeMemberReturn4Param0

/** nativeStaticReturn4Param0 */
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

/** nativeConstReturn4Param1 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1) const>
inline LUA_FUNC(nativeConstReturn4Param1)
{
	if (CLASS* object = to<CLASS*>(L, -2))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, to<ARG_1>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		return pushed;
	}
	return 0;
} // nativeConstReturn4Param1

/** nativeMemberReturn4Param1 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1) >
inline LUA_FUNC(nativeMemberReturn4Param1)
{
	if (CLASS* object = to<CLASS*>(L, -2))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, to<ARG_1>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		return pushed;
	}
	return 0;
} // nativeMemberReturn4Param1

/** nativeStaticReturn4Param1 */
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

/** nativeConstReturn4Param2 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2) const>
inline LUA_FUNC(nativeConstReturn4Param2)
{
	if (CLASS* object = to<CLASS*>(L, -3))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, to<ARG_1>(L, -2), to<ARG_2>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		return pushed;
	}
	return 0;
} // nativeConstReturn4Param2

/** nativeMemberReturn4Param2 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2) >
inline LUA_FUNC(nativeMemberReturn4Param2)
{
	if (CLASS* object = to<CLASS*>(L, -3))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, to<ARG_1>(L, -2), to<ARG_2>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		return pushed;
	}
	return 0;
} // nativeMemberReturn4Param2

/** nativeStaticReturn4Param2 */
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

/** nativeConstReturn4Param3 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3) const>
inline LUA_FUNC(nativeConstReturn4Param3)
{
	if (CLASS* object = to<CLASS*>(L, -4))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, to<ARG_1>(L, -3), to<ARG_2>(L, -2), to<ARG_3>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		return pushed;
	}
	return 0;
} // nativeConstReturn4Param3

/** nativeMemberReturn4Param3 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3) >
inline LUA_FUNC(nativeMemberReturn4Param3)
{
	if (CLASS* object = to<CLASS*>(L, -4))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, to<ARG_1>(L, -3), to<ARG_2>(L, -2), to<ARG_3>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		return pushed;
	}
	return 0;
} // nativeMemberReturn4Param3

/** nativeStaticReturn4Param3 */
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

/** nativeConstReturn4Param4 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4) const>
inline LUA_FUNC(nativeConstReturn4Param4)
{
	if (CLASS* object = to<CLASS*>(L, -5))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, to<ARG_1>(L, -4), to<ARG_2>(L, -3), to<ARG_3>(L, -2), to<ARG_4>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		return pushed;
	}
	return 0;
} // nativeConstReturn4Param4

/** nativeMemberReturn4Param4 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline LUA_FUNC(nativeMemberReturn4Param4)
{
	if (CLASS* object = to<CLASS*>(L, -5))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, to<ARG_1>(L, -4), to<ARG_2>(L, -3), to<ARG_3>(L, -2), to<ARG_4>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		return pushed;
	}
	return 0;
} // nativeMemberReturn4Param4

/** nativeStaticReturn4Param4 */
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

/** nativeConstReturn4Param5 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) const>
inline LUA_FUNC(nativeConstReturn4Param5)
{
	if (CLASS* object = to<CLASS*>(L, -6))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, to<ARG_1>(L, -5), to<ARG_2>(L, -4), to<ARG_3>(L, -3), to<ARG_4>(L, -2), to<ARG_5>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		return pushed;
	}
	return 0;
} // nativeConstReturn4Param5

/** nativeMemberReturn4Param5 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline LUA_FUNC(nativeMemberReturn4Param5)
{
	if (CLASS* object = to<CLASS*>(L, -6))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, to<ARG_1>(L, -5), to<ARG_2>(L, -4), to<ARG_3>(L, -3), to<ARG_4>(L, -2), to<ARG_5>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		return pushed;
	}
	return 0;
} // nativeMemberReturn4Param5

/** nativeStaticReturn4Param5 */
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

/** nativeConstReturn4Param6 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) const>
inline LUA_FUNC(nativeConstReturn4Param6)
{
	if (CLASS* object = to<CLASS*>(L, -7))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, to<ARG_1>(L, -6), to<ARG_2>(L, -5), to<ARG_3>(L, -4), to<ARG_4>(L, -3), to<ARG_5>(L, -2), to<ARG_6>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		return pushed;
	}
	return 0;
} // nativeConstReturn4Param6

/** nativeMemberReturn4Param6 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline LUA_FUNC(nativeMemberReturn4Param6)
{
	if (CLASS* object = to<CLASS*>(L, -7))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, to<ARG_1>(L, -6), to<ARG_2>(L, -5), to<ARG_3>(L, -4), to<ARG_4>(L, -3), to<ARG_5>(L, -2), to<ARG_6>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		return pushed;
	}
	return 0;
} // nativeMemberReturn4Param6

/** nativeStaticReturn4Param6 */
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

/** nativeConstReturn4Param7 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) const>
inline LUA_FUNC(nativeConstReturn4Param7)
{
	if (CLASS* object = to<CLASS*>(L, -8))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, to<ARG_1>(L, -7), to<ARG_2>(L, -6), to<ARG_3>(L, -5), to<ARG_4>(L, -4), to<ARG_5>(L, -3), to<ARG_6>(L, -2), to<ARG_7>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		return pushed;
	}
	return 0;
} // nativeConstReturn4Param7

/** nativeMemberReturn4Param7 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline LUA_FUNC(nativeMemberReturn4Param7)
{
	if (CLASS* object = to<CLASS*>(L, -8))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, to<ARG_1>(L, -7), to<ARG_2>(L, -6), to<ARG_3>(L, -5), to<ARG_4>(L, -4), to<ARG_5>(L, -3), to<ARG_6>(L, -2), to<ARG_7>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		return pushed;
	}
	return 0;
} // nativeMemberReturn4Param7

/** nativeStaticReturn4Param7 */
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

/** nativeConstReturn4Param8 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) const>
inline LUA_FUNC(nativeConstReturn4Param8)
{
	if (CLASS* object = to<CLASS*>(L, -9))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, to<ARG_1>(L, -8), to<ARG_2>(L, -7), to<ARG_3>(L, -6), to<ARG_4>(L, -5), to<ARG_5>(L, -4), to<ARG_6>(L, -3), to<ARG_7>(L, -2), to<ARG_8>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		return pushed;
	}
	return 0;
} // nativeConstReturn4Param8

/** nativeMemberReturn4Param8 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline LUA_FUNC(nativeMemberReturn4Param8)
{
	if (CLASS* object = to<CLASS*>(L, -9))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, to<ARG_1>(L, -8), to<ARG_2>(L, -7), to<ARG_3>(L, -6), to<ARG_4>(L, -5), to<ARG_5>(L, -4), to<ARG_6>(L, -3), to<ARG_7>(L, -2), to<ARG_8>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		return pushed;
	}
	return 0;
} // nativeMemberReturn4Param8

/** nativeStaticReturn4Param8 */
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

/** nativeConstReturn4Param9 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) const>
inline LUA_FUNC(nativeConstReturn4Param9)
{
	if (CLASS* object = to<CLASS*>(L, -10))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, to<ARG_1>(L, -9), to<ARG_2>(L, -8), to<ARG_3>(L, -7), to<ARG_4>(L, -6), to<ARG_5>(L, -5), to<ARG_6>(L, -4), to<ARG_7>(L, -3), to<ARG_8>(L, -2), to<ARG_9>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		return pushed;
	}
	return 0;
} // nativeConstReturn4Param9

/** nativeMemberReturn4Param9 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline LUA_FUNC(nativeMemberReturn4Param9)
{
	if (CLASS* object = to<CLASS*>(L, -10))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, to<ARG_1>(L, -9), to<ARG_2>(L, -8), to<ARG_3>(L, -7), to<ARG_4>(L, -6), to<ARG_5>(L, -5), to<ARG_6>(L, -4), to<ARG_7>(L, -3), to<ARG_8>(L, -2), to<ARG_9>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		return pushed;
	}
	return 0;
} // nativeMemberReturn4Param9

/** nativeStaticReturn4Param9 */
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

/** nativeConstReturn4Param10 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) const>
inline LUA_FUNC(nativeConstReturn4Param10)
{
	if (CLASS* object = to<CLASS*>(L, -11))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, to<ARG_1>(L, -10), to<ARG_2>(L, -9), to<ARG_3>(L, -8), to<ARG_4>(L, -7), to<ARG_5>(L, -6), to<ARG_6>(L, -5), to<ARG_7>(L, -4), to<ARG_8>(L, -3), to<ARG_9>(L, -2), to<ARG_10>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		return pushed;
	}
	return 0;
} // nativeConstReturn4Param10

/** nativeMemberReturn4Param10 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline LUA_FUNC(nativeMemberReturn4Param10)
{
	if (CLASS* object = to<CLASS*>(L, -11))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, to<ARG_1>(L, -10), to<ARG_2>(L, -9), to<ARG_3>(L, -8), to<ARG_4>(L, -7), to<ARG_5>(L, -6), to<ARG_6>(L, -5), to<ARG_7>(L, -4), to<ARG_8>(L, -3), to<ARG_9>(L, -2), to<ARG_10>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		return pushed;
	}
	return 0;
} // nativeMemberReturn4Param10

/** nativeStaticReturn4Param10 */
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

/** nativeConstReturn5Param0 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&) const>
inline LUA_FUNC(nativeConstReturn5Param0)
{
	if (CLASS* object = to<CLASS*>(L, -1))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5);
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		return pushed;
	}
	return 0;
} // nativeConstReturn5Param0

/** nativeMemberReturn5Param0 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&) >
inline LUA_FUNC(nativeMemberReturn5Param0)
{
	if (CLASS* object = to<CLASS*>(L, -1))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5);
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		return pushed;
	}
	return 0;
} // nativeMemberReturn5Param0

/** nativeStaticReturn5Param0 */
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

/** nativeConstReturn5Param1 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1) const>
inline LUA_FUNC(nativeConstReturn5Param1)
{
	if (CLASS* object = to<CLASS*>(L, -2))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, to<ARG_1>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		return pushed;
	}
	return 0;
} // nativeConstReturn5Param1

/** nativeMemberReturn5Param1 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1) >
inline LUA_FUNC(nativeMemberReturn5Param1)
{
	if (CLASS* object = to<CLASS*>(L, -2))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, to<ARG_1>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		return pushed;
	}
	return 0;
} // nativeMemberReturn5Param1

/** nativeStaticReturn5Param1 */
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

/** nativeConstReturn5Param2 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2) const>
inline LUA_FUNC(nativeConstReturn5Param2)
{
	if (CLASS* object = to<CLASS*>(L, -3))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, to<ARG_1>(L, -2), to<ARG_2>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		return pushed;
	}
	return 0;
} // nativeConstReturn5Param2

/** nativeMemberReturn5Param2 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2) >
inline LUA_FUNC(nativeMemberReturn5Param2)
{
	if (CLASS* object = to<CLASS*>(L, -3))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, to<ARG_1>(L, -2), to<ARG_2>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		return pushed;
	}
	return 0;
} // nativeMemberReturn5Param2

/** nativeStaticReturn5Param2 */
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

/** nativeConstReturn5Param3 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3) const>
inline LUA_FUNC(nativeConstReturn5Param3)
{
	if (CLASS* object = to<CLASS*>(L, -4))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, to<ARG_1>(L, -3), to<ARG_2>(L, -2), to<ARG_3>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		return pushed;
	}
	return 0;
} // nativeConstReturn5Param3

/** nativeMemberReturn5Param3 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3) >
inline LUA_FUNC(nativeMemberReturn5Param3)
{
	if (CLASS* object = to<CLASS*>(L, -4))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, to<ARG_1>(L, -3), to<ARG_2>(L, -2), to<ARG_3>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		return pushed;
	}
	return 0;
} // nativeMemberReturn5Param3

/** nativeStaticReturn5Param3 */
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

/** nativeConstReturn5Param4 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4) const>
inline LUA_FUNC(nativeConstReturn5Param4)
{
	if (CLASS* object = to<CLASS*>(L, -5))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, to<ARG_1>(L, -4), to<ARG_2>(L, -3), to<ARG_3>(L, -2), to<ARG_4>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		return pushed;
	}
	return 0;
} // nativeConstReturn5Param4

/** nativeMemberReturn5Param4 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline LUA_FUNC(nativeMemberReturn5Param4)
{
	if (CLASS* object = to<CLASS*>(L, -5))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, to<ARG_1>(L, -4), to<ARG_2>(L, -3), to<ARG_3>(L, -2), to<ARG_4>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		return pushed;
	}
	return 0;
} // nativeMemberReturn5Param4

/** nativeStaticReturn5Param4 */
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

/** nativeConstReturn5Param5 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) const>
inline LUA_FUNC(nativeConstReturn5Param5)
{
	if (CLASS* object = to<CLASS*>(L, -6))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, to<ARG_1>(L, -5), to<ARG_2>(L, -4), to<ARG_3>(L, -3), to<ARG_4>(L, -2), to<ARG_5>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		return pushed;
	}
	return 0;
} // nativeConstReturn5Param5

/** nativeMemberReturn5Param5 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline LUA_FUNC(nativeMemberReturn5Param5)
{
	if (CLASS* object = to<CLASS*>(L, -6))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, to<ARG_1>(L, -5), to<ARG_2>(L, -4), to<ARG_3>(L, -3), to<ARG_4>(L, -2), to<ARG_5>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		return pushed;
	}
	return 0;
} // nativeMemberReturn5Param5

/** nativeStaticReturn5Param5 */
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

/** nativeConstReturn5Param6 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) const>
inline LUA_FUNC(nativeConstReturn5Param6)
{
	if (CLASS* object = to<CLASS*>(L, -7))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, to<ARG_1>(L, -6), to<ARG_2>(L, -5), to<ARG_3>(L, -4), to<ARG_4>(L, -3), to<ARG_5>(L, -2), to<ARG_6>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		return pushed;
	}
	return 0;
} // nativeConstReturn5Param6

/** nativeMemberReturn5Param6 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline LUA_FUNC(nativeMemberReturn5Param6)
{
	if (CLASS* object = to<CLASS*>(L, -7))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, to<ARG_1>(L, -6), to<ARG_2>(L, -5), to<ARG_3>(L, -4), to<ARG_4>(L, -3), to<ARG_5>(L, -2), to<ARG_6>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		return pushed;
	}
	return 0;
} // nativeMemberReturn5Param6

/** nativeStaticReturn5Param6 */
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

/** nativeConstReturn5Param7 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) const>
inline LUA_FUNC(nativeConstReturn5Param7)
{
	if (CLASS* object = to<CLASS*>(L, -8))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, to<ARG_1>(L, -7), to<ARG_2>(L, -6), to<ARG_3>(L, -5), to<ARG_4>(L, -4), to<ARG_5>(L, -3), to<ARG_6>(L, -2), to<ARG_7>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		return pushed;
	}
	return 0;
} // nativeConstReturn5Param7

/** nativeMemberReturn5Param7 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline LUA_FUNC(nativeMemberReturn5Param7)
{
	if (CLASS* object = to<CLASS*>(L, -8))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, to<ARG_1>(L, -7), to<ARG_2>(L, -6), to<ARG_3>(L, -5), to<ARG_4>(L, -4), to<ARG_5>(L, -3), to<ARG_6>(L, -2), to<ARG_7>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		return pushed;
	}
	return 0;
} // nativeMemberReturn5Param7

/** nativeStaticReturn5Param7 */
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

/** nativeConstReturn5Param8 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) const>
inline LUA_FUNC(nativeConstReturn5Param8)
{
	if (CLASS* object = to<CLASS*>(L, -9))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, to<ARG_1>(L, -8), to<ARG_2>(L, -7), to<ARG_3>(L, -6), to<ARG_4>(L, -5), to<ARG_5>(L, -4), to<ARG_6>(L, -3), to<ARG_7>(L, -2), to<ARG_8>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		return pushed;
	}
	return 0;
} // nativeConstReturn5Param8

/** nativeMemberReturn5Param8 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline LUA_FUNC(nativeMemberReturn5Param8)
{
	if (CLASS* object = to<CLASS*>(L, -9))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, to<ARG_1>(L, -8), to<ARG_2>(L, -7), to<ARG_3>(L, -6), to<ARG_4>(L, -5), to<ARG_5>(L, -4), to<ARG_6>(L, -3), to<ARG_7>(L, -2), to<ARG_8>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		return pushed;
	}
	return 0;
} // nativeMemberReturn5Param8

/** nativeStaticReturn5Param8 */
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

/** nativeConstReturn5Param9 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) const>
inline LUA_FUNC(nativeConstReturn5Param9)
{
	if (CLASS* object = to<CLASS*>(L, -10))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, to<ARG_1>(L, -9), to<ARG_2>(L, -8), to<ARG_3>(L, -7), to<ARG_4>(L, -6), to<ARG_5>(L, -5), to<ARG_6>(L, -4), to<ARG_7>(L, -3), to<ARG_8>(L, -2), to<ARG_9>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		return pushed;
	}
	return 0;
} // nativeConstReturn5Param9

/** nativeMemberReturn5Param9 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline LUA_FUNC(nativeMemberReturn5Param9)
{
	if (CLASS* object = to<CLASS*>(L, -10))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, to<ARG_1>(L, -9), to<ARG_2>(L, -8), to<ARG_3>(L, -7), to<ARG_4>(L, -6), to<ARG_5>(L, -5), to<ARG_6>(L, -4), to<ARG_7>(L, -3), to<ARG_8>(L, -2), to<ARG_9>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		return pushed;
	}
	return 0;
} // nativeMemberReturn5Param9

/** nativeStaticReturn5Param9 */
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

/** nativeConstReturn5Param10 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) const>
inline LUA_FUNC(nativeConstReturn5Param10)
{
	if (CLASS* object = to<CLASS*>(L, -11))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, to<ARG_1>(L, -10), to<ARG_2>(L, -9), to<ARG_3>(L, -8), to<ARG_4>(L, -7), to<ARG_5>(L, -6), to<ARG_6>(L, -5), to<ARG_7>(L, -4), to<ARG_8>(L, -3), to<ARG_9>(L, -2), to<ARG_10>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		return pushed;
	}
	return 0;
} // nativeConstReturn5Param10

/** nativeMemberReturn5Param10 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline LUA_FUNC(nativeMemberReturn5Param10)
{
	if (CLASS* object = to<CLASS*>(L, -11))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, to<ARG_1>(L, -10), to<ARG_2>(L, -9), to<ARG_3>(L, -8), to<ARG_4>(L, -7), to<ARG_5>(L, -6), to<ARG_6>(L, -5), to<ARG_7>(L, -4), to<ARG_8>(L, -3), to<ARG_9>(L, -2), to<ARG_10>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		return pushed;
	}
	return 0;
} // nativeMemberReturn5Param10

/** nativeStaticReturn5Param10 */
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

/** nativeConstReturn6Param0 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&) const>
inline LUA_FUNC(nativeConstReturn6Param0)
{
	if (CLASS* object = to<CLASS*>(L, -1))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6);
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		return pushed;
	}
	return 0;
} // nativeConstReturn6Param0

/** nativeMemberReturn6Param0 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&) >
inline LUA_FUNC(nativeMemberReturn6Param0)
{
	if (CLASS* object = to<CLASS*>(L, -1))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6);
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		return pushed;
	}
	return 0;
} // nativeMemberReturn6Param0

/** nativeStaticReturn6Param0 */
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

/** nativeConstReturn6Param1 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1) const>
inline LUA_FUNC(nativeConstReturn6Param1)
{
	if (CLASS* object = to<CLASS*>(L, -2))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, to<ARG_1>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		return pushed;
	}
	return 0;
} // nativeConstReturn6Param1

/** nativeMemberReturn6Param1 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1) >
inline LUA_FUNC(nativeMemberReturn6Param1)
{
	if (CLASS* object = to<CLASS*>(L, -2))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, to<ARG_1>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		return pushed;
	}
	return 0;
} // nativeMemberReturn6Param1

/** nativeStaticReturn6Param1 */
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

/** nativeConstReturn6Param2 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2) const>
inline LUA_FUNC(nativeConstReturn6Param2)
{
	if (CLASS* object = to<CLASS*>(L, -3))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, to<ARG_1>(L, -2), to<ARG_2>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		return pushed;
	}
	return 0;
} // nativeConstReturn6Param2

/** nativeMemberReturn6Param2 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2) >
inline LUA_FUNC(nativeMemberReturn6Param2)
{
	if (CLASS* object = to<CLASS*>(L, -3))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, to<ARG_1>(L, -2), to<ARG_2>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		return pushed;
	}
	return 0;
} // nativeMemberReturn6Param2

/** nativeStaticReturn6Param2 */
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

/** nativeConstReturn6Param3 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3) const>
inline LUA_FUNC(nativeConstReturn6Param3)
{
	if (CLASS* object = to<CLASS*>(L, -4))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, to<ARG_1>(L, -3), to<ARG_2>(L, -2), to<ARG_3>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		return pushed;
	}
	return 0;
} // nativeConstReturn6Param3

/** nativeMemberReturn6Param3 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3) >
inline LUA_FUNC(nativeMemberReturn6Param3)
{
	if (CLASS* object = to<CLASS*>(L, -4))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, to<ARG_1>(L, -3), to<ARG_2>(L, -2), to<ARG_3>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		return pushed;
	}
	return 0;
} // nativeMemberReturn6Param3

/** nativeStaticReturn6Param3 */
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

/** nativeConstReturn6Param4 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4) const>
inline LUA_FUNC(nativeConstReturn6Param4)
{
	if (CLASS* object = to<CLASS*>(L, -5))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, to<ARG_1>(L, -4), to<ARG_2>(L, -3), to<ARG_3>(L, -2), to<ARG_4>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		return pushed;
	}
	return 0;
} // nativeConstReturn6Param4

/** nativeMemberReturn6Param4 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline LUA_FUNC(nativeMemberReturn6Param4)
{
	if (CLASS* object = to<CLASS*>(L, -5))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, to<ARG_1>(L, -4), to<ARG_2>(L, -3), to<ARG_3>(L, -2), to<ARG_4>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		return pushed;
	}
	return 0;
} // nativeMemberReturn6Param4

/** nativeStaticReturn6Param4 */
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

/** nativeConstReturn6Param5 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) const>
inline LUA_FUNC(nativeConstReturn6Param5)
{
	if (CLASS* object = to<CLASS*>(L, -6))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, to<ARG_1>(L, -5), to<ARG_2>(L, -4), to<ARG_3>(L, -3), to<ARG_4>(L, -2), to<ARG_5>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		return pushed;
	}
	return 0;
} // nativeConstReturn6Param5

/** nativeMemberReturn6Param5 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline LUA_FUNC(nativeMemberReturn6Param5)
{
	if (CLASS* object = to<CLASS*>(L, -6))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, to<ARG_1>(L, -5), to<ARG_2>(L, -4), to<ARG_3>(L, -3), to<ARG_4>(L, -2), to<ARG_5>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		return pushed;
	}
	return 0;
} // nativeMemberReturn6Param5

/** nativeStaticReturn6Param5 */
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

/** nativeConstReturn6Param6 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) const>
inline LUA_FUNC(nativeConstReturn6Param6)
{
	if (CLASS* object = to<CLASS*>(L, -7))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, to<ARG_1>(L, -6), to<ARG_2>(L, -5), to<ARG_3>(L, -4), to<ARG_4>(L, -3), to<ARG_5>(L, -2), to<ARG_6>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		return pushed;
	}
	return 0;
} // nativeConstReturn6Param6

/** nativeMemberReturn6Param6 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline LUA_FUNC(nativeMemberReturn6Param6)
{
	if (CLASS* object = to<CLASS*>(L, -7))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, to<ARG_1>(L, -6), to<ARG_2>(L, -5), to<ARG_3>(L, -4), to<ARG_4>(L, -3), to<ARG_5>(L, -2), to<ARG_6>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		return pushed;
	}
	return 0;
} // nativeMemberReturn6Param6

/** nativeStaticReturn6Param6 */
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

/** nativeConstReturn6Param7 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) const>
inline LUA_FUNC(nativeConstReturn6Param7)
{
	if (CLASS* object = to<CLASS*>(L, -8))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, to<ARG_1>(L, -7), to<ARG_2>(L, -6), to<ARG_3>(L, -5), to<ARG_4>(L, -4), to<ARG_5>(L, -3), to<ARG_6>(L, -2), to<ARG_7>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		return pushed;
	}
	return 0;
} // nativeConstReturn6Param7

/** nativeMemberReturn6Param7 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline LUA_FUNC(nativeMemberReturn6Param7)
{
	if (CLASS* object = to<CLASS*>(L, -8))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, to<ARG_1>(L, -7), to<ARG_2>(L, -6), to<ARG_3>(L, -5), to<ARG_4>(L, -4), to<ARG_5>(L, -3), to<ARG_6>(L, -2), to<ARG_7>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		return pushed;
	}
	return 0;
} // nativeMemberReturn6Param7

/** nativeStaticReturn6Param7 */
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

/** nativeConstReturn6Param8 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) const>
inline LUA_FUNC(nativeConstReturn6Param8)
{
	if (CLASS* object = to<CLASS*>(L, -9))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, to<ARG_1>(L, -8), to<ARG_2>(L, -7), to<ARG_3>(L, -6), to<ARG_4>(L, -5), to<ARG_5>(L, -4), to<ARG_6>(L, -3), to<ARG_7>(L, -2), to<ARG_8>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		return pushed;
	}
	return 0;
} // nativeConstReturn6Param8

/** nativeMemberReturn6Param8 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline LUA_FUNC(nativeMemberReturn6Param8)
{
	if (CLASS* object = to<CLASS*>(L, -9))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, to<ARG_1>(L, -8), to<ARG_2>(L, -7), to<ARG_3>(L, -6), to<ARG_4>(L, -5), to<ARG_5>(L, -4), to<ARG_6>(L, -3), to<ARG_7>(L, -2), to<ARG_8>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		return pushed;
	}
	return 0;
} // nativeMemberReturn6Param8

/** nativeStaticReturn6Param8 */
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

/** nativeConstReturn6Param9 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) const>
inline LUA_FUNC(nativeConstReturn6Param9)
{
	if (CLASS* object = to<CLASS*>(L, -10))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, to<ARG_1>(L, -9), to<ARG_2>(L, -8), to<ARG_3>(L, -7), to<ARG_4>(L, -6), to<ARG_5>(L, -5), to<ARG_6>(L, -4), to<ARG_7>(L, -3), to<ARG_8>(L, -2), to<ARG_9>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		return pushed;
	}
	return 0;
} // nativeConstReturn6Param9

/** nativeMemberReturn6Param9 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline LUA_FUNC(nativeMemberReturn6Param9)
{
	if (CLASS* object = to<CLASS*>(L, -10))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, to<ARG_1>(L, -9), to<ARG_2>(L, -8), to<ARG_3>(L, -7), to<ARG_4>(L, -6), to<ARG_5>(L, -5), to<ARG_6>(L, -4), to<ARG_7>(L, -3), to<ARG_8>(L, -2), to<ARG_9>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		return pushed;
	}
	return 0;
} // nativeMemberReturn6Param9

/** nativeStaticReturn6Param9 */
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

/** nativeConstReturn6Param10 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) const>
inline LUA_FUNC(nativeConstReturn6Param10)
{
	if (CLASS* object = to<CLASS*>(L, -11))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, to<ARG_1>(L, -10), to<ARG_2>(L, -9), to<ARG_3>(L, -8), to<ARG_4>(L, -7), to<ARG_5>(L, -6), to<ARG_6>(L, -5), to<ARG_7>(L, -4), to<ARG_8>(L, -3), to<ARG_9>(L, -2), to<ARG_10>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		return pushed;
	}
	return 0;
} // nativeConstReturn6Param10

/** nativeMemberReturn6Param10 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline LUA_FUNC(nativeMemberReturn6Param10)
{
	if (CLASS* object = to<CLASS*>(L, -11))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, to<ARG_1>(L, -10), to<ARG_2>(L, -9), to<ARG_3>(L, -8), to<ARG_4>(L, -7), to<ARG_5>(L, -6), to<ARG_6>(L, -5), to<ARG_7>(L, -4), to<ARG_8>(L, -3), to<ARG_9>(L, -2), to<ARG_10>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		return pushed;
	}
	return 0;
} // nativeMemberReturn6Param10

/** nativeStaticReturn6Param10 */
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

/** nativeConstReturn7Param0 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&) const>
inline LUA_FUNC(nativeConstReturn7Param0)
{
	if (CLASS* object = to<CLASS*>(L, -1))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7);
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		return pushed;
	}
	return 0;
} // nativeConstReturn7Param0

/** nativeMemberReturn7Param0 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&) >
inline LUA_FUNC(nativeMemberReturn7Param0)
{
	if (CLASS* object = to<CLASS*>(L, -1))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7);
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		return pushed;
	}
	return 0;
} // nativeMemberReturn7Param0

/** nativeStaticReturn7Param0 */
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

/** nativeConstReturn7Param1 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1) const>
inline LUA_FUNC(nativeConstReturn7Param1)
{
	if (CLASS* object = to<CLASS*>(L, -2))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, to<ARG_1>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		return pushed;
	}
	return 0;
} // nativeConstReturn7Param1

/** nativeMemberReturn7Param1 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1) >
inline LUA_FUNC(nativeMemberReturn7Param1)
{
	if (CLASS* object = to<CLASS*>(L, -2))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, to<ARG_1>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		return pushed;
	}
	return 0;
} // nativeMemberReturn7Param1

/** nativeStaticReturn7Param1 */
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

/** nativeConstReturn7Param2 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2) const>
inline LUA_FUNC(nativeConstReturn7Param2)
{
	if (CLASS* object = to<CLASS*>(L, -3))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, to<ARG_1>(L, -2), to<ARG_2>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		return pushed;
	}
	return 0;
} // nativeConstReturn7Param2

/** nativeMemberReturn7Param2 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2) >
inline LUA_FUNC(nativeMemberReturn7Param2)
{
	if (CLASS* object = to<CLASS*>(L, -3))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, to<ARG_1>(L, -2), to<ARG_2>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		return pushed;
	}
	return 0;
} // nativeMemberReturn7Param2

/** nativeStaticReturn7Param2 */
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

/** nativeConstReturn7Param3 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3) const>
inline LUA_FUNC(nativeConstReturn7Param3)
{
	if (CLASS* object = to<CLASS*>(L, -4))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, to<ARG_1>(L, -3), to<ARG_2>(L, -2), to<ARG_3>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		return pushed;
	}
	return 0;
} // nativeConstReturn7Param3

/** nativeMemberReturn7Param3 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3) >
inline LUA_FUNC(nativeMemberReturn7Param3)
{
	if (CLASS* object = to<CLASS*>(L, -4))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, to<ARG_1>(L, -3), to<ARG_2>(L, -2), to<ARG_3>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		return pushed;
	}
	return 0;
} // nativeMemberReturn7Param3

/** nativeStaticReturn7Param3 */
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

/** nativeConstReturn7Param4 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4) const>
inline LUA_FUNC(nativeConstReturn7Param4)
{
	if (CLASS* object = to<CLASS*>(L, -5))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, to<ARG_1>(L, -4), to<ARG_2>(L, -3), to<ARG_3>(L, -2), to<ARG_4>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		return pushed;
	}
	return 0;
} // nativeConstReturn7Param4

/** nativeMemberReturn7Param4 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline LUA_FUNC(nativeMemberReturn7Param4)
{
	if (CLASS* object = to<CLASS*>(L, -5))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, to<ARG_1>(L, -4), to<ARG_2>(L, -3), to<ARG_3>(L, -2), to<ARG_4>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		return pushed;
	}
	return 0;
} // nativeMemberReturn7Param4

/** nativeStaticReturn7Param4 */
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

/** nativeConstReturn7Param5 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) const>
inline LUA_FUNC(nativeConstReturn7Param5)
{
	if (CLASS* object = to<CLASS*>(L, -6))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, to<ARG_1>(L, -5), to<ARG_2>(L, -4), to<ARG_3>(L, -3), to<ARG_4>(L, -2), to<ARG_5>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		return pushed;
	}
	return 0;
} // nativeConstReturn7Param5

/** nativeMemberReturn7Param5 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline LUA_FUNC(nativeMemberReturn7Param5)
{
	if (CLASS* object = to<CLASS*>(L, -6))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, to<ARG_1>(L, -5), to<ARG_2>(L, -4), to<ARG_3>(L, -3), to<ARG_4>(L, -2), to<ARG_5>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		return pushed;
	}
	return 0;
} // nativeMemberReturn7Param5

/** nativeStaticReturn7Param5 */
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

/** nativeConstReturn7Param6 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) const>
inline LUA_FUNC(nativeConstReturn7Param6)
{
	if (CLASS* object = to<CLASS*>(L, -7))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, to<ARG_1>(L, -6), to<ARG_2>(L, -5), to<ARG_3>(L, -4), to<ARG_4>(L, -3), to<ARG_5>(L, -2), to<ARG_6>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		return pushed;
	}
	return 0;
} // nativeConstReturn7Param6

/** nativeMemberReturn7Param6 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline LUA_FUNC(nativeMemberReturn7Param6)
{
	if (CLASS* object = to<CLASS*>(L, -7))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, to<ARG_1>(L, -6), to<ARG_2>(L, -5), to<ARG_3>(L, -4), to<ARG_4>(L, -3), to<ARG_5>(L, -2), to<ARG_6>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		return pushed;
	}
	return 0;
} // nativeMemberReturn7Param6

/** nativeStaticReturn7Param6 */
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

/** nativeConstReturn7Param7 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) const>
inline LUA_FUNC(nativeConstReturn7Param7)
{
	if (CLASS* object = to<CLASS*>(L, -8))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, to<ARG_1>(L, -7), to<ARG_2>(L, -6), to<ARG_3>(L, -5), to<ARG_4>(L, -4), to<ARG_5>(L, -3), to<ARG_6>(L, -2), to<ARG_7>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		return pushed;
	}
	return 0;
} // nativeConstReturn7Param7

/** nativeMemberReturn7Param7 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline LUA_FUNC(nativeMemberReturn7Param7)
{
	if (CLASS* object = to<CLASS*>(L, -8))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, to<ARG_1>(L, -7), to<ARG_2>(L, -6), to<ARG_3>(L, -5), to<ARG_4>(L, -4), to<ARG_5>(L, -3), to<ARG_6>(L, -2), to<ARG_7>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		return pushed;
	}
	return 0;
} // nativeMemberReturn7Param7

/** nativeStaticReturn7Param7 */
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

/** nativeConstReturn7Param8 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) const>
inline LUA_FUNC(nativeConstReturn7Param8)
{
	if (CLASS* object = to<CLASS*>(L, -9))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, to<ARG_1>(L, -8), to<ARG_2>(L, -7), to<ARG_3>(L, -6), to<ARG_4>(L, -5), to<ARG_5>(L, -4), to<ARG_6>(L, -3), to<ARG_7>(L, -2), to<ARG_8>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		return pushed;
	}
	return 0;
} // nativeConstReturn7Param8

/** nativeMemberReturn7Param8 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline LUA_FUNC(nativeMemberReturn7Param8)
{
	if (CLASS* object = to<CLASS*>(L, -9))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, to<ARG_1>(L, -8), to<ARG_2>(L, -7), to<ARG_3>(L, -6), to<ARG_4>(L, -5), to<ARG_5>(L, -4), to<ARG_6>(L, -3), to<ARG_7>(L, -2), to<ARG_8>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		return pushed;
	}
	return 0;
} // nativeMemberReturn7Param8

/** nativeStaticReturn7Param8 */
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

/** nativeConstReturn7Param9 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) const>
inline LUA_FUNC(nativeConstReturn7Param9)
{
	if (CLASS* object = to<CLASS*>(L, -10))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, to<ARG_1>(L, -9), to<ARG_2>(L, -8), to<ARG_3>(L, -7), to<ARG_4>(L, -6), to<ARG_5>(L, -5), to<ARG_6>(L, -4), to<ARG_7>(L, -3), to<ARG_8>(L, -2), to<ARG_9>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		return pushed;
	}
	return 0;
} // nativeConstReturn7Param9

/** nativeMemberReturn7Param9 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline LUA_FUNC(nativeMemberReturn7Param9)
{
	if (CLASS* object = to<CLASS*>(L, -10))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, to<ARG_1>(L, -9), to<ARG_2>(L, -8), to<ARG_3>(L, -7), to<ARG_4>(L, -6), to<ARG_5>(L, -5), to<ARG_6>(L, -4), to<ARG_7>(L, -3), to<ARG_8>(L, -2), to<ARG_9>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		return pushed;
	}
	return 0;
} // nativeMemberReturn7Param9

/** nativeStaticReturn7Param9 */
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

/** nativeConstReturn7Param10 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) const>
inline LUA_FUNC(nativeConstReturn7Param10)
{
	if (CLASS* object = to<CLASS*>(L, -11))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, to<ARG_1>(L, -10), to<ARG_2>(L, -9), to<ARG_3>(L, -8), to<ARG_4>(L, -7), to<ARG_5>(L, -6), to<ARG_6>(L, -5), to<ARG_7>(L, -4), to<ARG_8>(L, -3), to<ARG_9>(L, -2), to<ARG_10>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		return pushed;
	}
	return 0;
} // nativeConstReturn7Param10

/** nativeMemberReturn7Param10 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline LUA_FUNC(nativeMemberReturn7Param10)
{
	if (CLASS* object = to<CLASS*>(L, -11))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, to<ARG_1>(L, -10), to<ARG_2>(L, -9), to<ARG_3>(L, -8), to<ARG_4>(L, -7), to<ARG_5>(L, -6), to<ARG_6>(L, -5), to<ARG_7>(L, -4), to<ARG_8>(L, -3), to<ARG_9>(L, -2), to<ARG_10>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		return pushed;
	}
	return 0;
} // nativeMemberReturn7Param10

/** nativeStaticReturn7Param10 */
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

/** nativeConstReturn8Param0 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&) const>
inline LUA_FUNC(nativeConstReturn8Param0)
{
	if (CLASS* object = to<CLASS*>(L, -1))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8);
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		pushed += push(L, ret8);
		return pushed;
	}
	return 0;
} // nativeConstReturn8Param0

/** nativeMemberReturn8Param0 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&) >
inline LUA_FUNC(nativeMemberReturn8Param0)
{
	if (CLASS* object = to<CLASS*>(L, -1))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8);
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		pushed += push(L, ret8);
		return pushed;
	}
	return 0;
} // nativeMemberReturn8Param0

/** nativeStaticReturn8Param0 */
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

/** nativeConstReturn8Param1 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1) const>
inline LUA_FUNC(nativeConstReturn8Param1)
{
	if (CLASS* object = to<CLASS*>(L, -2))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, to<ARG_1>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		pushed += push(L, ret8);
		return pushed;
	}
	return 0;
} // nativeConstReturn8Param1

/** nativeMemberReturn8Param1 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1) >
inline LUA_FUNC(nativeMemberReturn8Param1)
{
	if (CLASS* object = to<CLASS*>(L, -2))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, to<ARG_1>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		pushed += push(L, ret8);
		return pushed;
	}
	return 0;
} // nativeMemberReturn8Param1

/** nativeStaticReturn8Param1 */
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

/** nativeConstReturn8Param2 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2) const>
inline LUA_FUNC(nativeConstReturn8Param2)
{
	if (CLASS* object = to<CLASS*>(L, -3))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, to<ARG_1>(L, -2), to<ARG_2>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		pushed += push(L, ret8);
		return pushed;
	}
	return 0;
} // nativeConstReturn8Param2

/** nativeMemberReturn8Param2 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2) >
inline LUA_FUNC(nativeMemberReturn8Param2)
{
	if (CLASS* object = to<CLASS*>(L, -3))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, to<ARG_1>(L, -2), to<ARG_2>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		pushed += push(L, ret8);
		return pushed;
	}
	return 0;
} // nativeMemberReturn8Param2

/** nativeStaticReturn8Param2 */
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

/** nativeConstReturn8Param3 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3) const>
inline LUA_FUNC(nativeConstReturn8Param3)
{
	if (CLASS* object = to<CLASS*>(L, -4))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, to<ARG_1>(L, -3), to<ARG_2>(L, -2), to<ARG_3>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		pushed += push(L, ret8);
		return pushed;
	}
	return 0;
} // nativeConstReturn8Param3

/** nativeMemberReturn8Param3 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3) >
inline LUA_FUNC(nativeMemberReturn8Param3)
{
	if (CLASS* object = to<CLASS*>(L, -4))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, to<ARG_1>(L, -3), to<ARG_2>(L, -2), to<ARG_3>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		pushed += push(L, ret8);
		return pushed;
	}
	return 0;
} // nativeMemberReturn8Param3

/** nativeStaticReturn8Param3 */
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

/** nativeConstReturn8Param4 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4) const>
inline LUA_FUNC(nativeConstReturn8Param4)
{
	if (CLASS* object = to<CLASS*>(L, -5))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, to<ARG_1>(L, -4), to<ARG_2>(L, -3), to<ARG_3>(L, -2), to<ARG_4>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		pushed += push(L, ret8);
		return pushed;
	}
	return 0;
} // nativeConstReturn8Param4

/** nativeMemberReturn8Param4 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline LUA_FUNC(nativeMemberReturn8Param4)
{
	if (CLASS* object = to<CLASS*>(L, -5))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, to<ARG_1>(L, -4), to<ARG_2>(L, -3), to<ARG_3>(L, -2), to<ARG_4>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		pushed += push(L, ret8);
		return pushed;
	}
	return 0;
} // nativeMemberReturn8Param4

/** nativeStaticReturn8Param4 */
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

/** nativeConstReturn8Param5 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) const>
inline LUA_FUNC(nativeConstReturn8Param5)
{
	if (CLASS* object = to<CLASS*>(L, -6))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, to<ARG_1>(L, -5), to<ARG_2>(L, -4), to<ARG_3>(L, -3), to<ARG_4>(L, -2), to<ARG_5>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		pushed += push(L, ret8);
		return pushed;
	}
	return 0;
} // nativeConstReturn8Param5

/** nativeMemberReturn8Param5 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline LUA_FUNC(nativeMemberReturn8Param5)
{
	if (CLASS* object = to<CLASS*>(L, -6))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, to<ARG_1>(L, -5), to<ARG_2>(L, -4), to<ARG_3>(L, -3), to<ARG_4>(L, -2), to<ARG_5>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		pushed += push(L, ret8);
		return pushed;
	}
	return 0;
} // nativeMemberReturn8Param5

/** nativeStaticReturn8Param5 */
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

/** nativeConstReturn8Param6 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) const>
inline LUA_FUNC(nativeConstReturn8Param6)
{
	if (CLASS* object = to<CLASS*>(L, -7))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, to<ARG_1>(L, -6), to<ARG_2>(L, -5), to<ARG_3>(L, -4), to<ARG_4>(L, -3), to<ARG_5>(L, -2), to<ARG_6>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		pushed += push(L, ret8);
		return pushed;
	}
	return 0;
} // nativeConstReturn8Param6

/** nativeMemberReturn8Param6 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline LUA_FUNC(nativeMemberReturn8Param6)
{
	if (CLASS* object = to<CLASS*>(L, -7))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, to<ARG_1>(L, -6), to<ARG_2>(L, -5), to<ARG_3>(L, -4), to<ARG_4>(L, -3), to<ARG_5>(L, -2), to<ARG_6>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		pushed += push(L, ret8);
		return pushed;
	}
	return 0;
} // nativeMemberReturn8Param6

/** nativeStaticReturn8Param6 */
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

/** nativeConstReturn8Param7 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) const>
inline LUA_FUNC(nativeConstReturn8Param7)
{
	if (CLASS* object = to<CLASS*>(L, -8))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, to<ARG_1>(L, -7), to<ARG_2>(L, -6), to<ARG_3>(L, -5), to<ARG_4>(L, -4), to<ARG_5>(L, -3), to<ARG_6>(L, -2), to<ARG_7>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		pushed += push(L, ret8);
		return pushed;
	}
	return 0;
} // nativeConstReturn8Param7

/** nativeMemberReturn8Param7 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline LUA_FUNC(nativeMemberReturn8Param7)
{
	if (CLASS* object = to<CLASS*>(L, -8))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, to<ARG_1>(L, -7), to<ARG_2>(L, -6), to<ARG_3>(L, -5), to<ARG_4>(L, -4), to<ARG_5>(L, -3), to<ARG_6>(L, -2), to<ARG_7>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		pushed += push(L, ret8);
		return pushed;
	}
	return 0;
} // nativeMemberReturn8Param7

/** nativeStaticReturn8Param7 */
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

/** nativeConstReturn8Param8 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) const>
inline LUA_FUNC(nativeConstReturn8Param8)
{
	if (CLASS* object = to<CLASS*>(L, -9))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, to<ARG_1>(L, -8), to<ARG_2>(L, -7), to<ARG_3>(L, -6), to<ARG_4>(L, -5), to<ARG_5>(L, -4), to<ARG_6>(L, -3), to<ARG_7>(L, -2), to<ARG_8>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		pushed += push(L, ret8);
		return pushed;
	}
	return 0;
} // nativeConstReturn8Param8

/** nativeMemberReturn8Param8 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline LUA_FUNC(nativeMemberReturn8Param8)
{
	if (CLASS* object = to<CLASS*>(L, -9))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, to<ARG_1>(L, -8), to<ARG_2>(L, -7), to<ARG_3>(L, -6), to<ARG_4>(L, -5), to<ARG_5>(L, -4), to<ARG_6>(L, -3), to<ARG_7>(L, -2), to<ARG_8>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		pushed += push(L, ret8);
		return pushed;
	}
	return 0;
} // nativeMemberReturn8Param8

/** nativeStaticReturn8Param8 */
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

/** nativeConstReturn8Param9 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) const>
inline LUA_FUNC(nativeConstReturn8Param9)
{
	if (CLASS* object = to<CLASS*>(L, -10))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, to<ARG_1>(L, -9), to<ARG_2>(L, -8), to<ARG_3>(L, -7), to<ARG_4>(L, -6), to<ARG_5>(L, -5), to<ARG_6>(L, -4), to<ARG_7>(L, -3), to<ARG_8>(L, -2), to<ARG_9>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		pushed += push(L, ret8);
		return pushed;
	}
	return 0;
} // nativeConstReturn8Param9

/** nativeMemberReturn8Param9 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline LUA_FUNC(nativeMemberReturn8Param9)
{
	if (CLASS* object = to<CLASS*>(L, -10))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, to<ARG_1>(L, -9), to<ARG_2>(L, -8), to<ARG_3>(L, -7), to<ARG_4>(L, -6), to<ARG_5>(L, -5), to<ARG_6>(L, -4), to<ARG_7>(L, -3), to<ARG_8>(L, -2), to<ARG_9>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		pushed += push(L, ret8);
		return pushed;
	}
	return 0;
} // nativeMemberReturn8Param9

/** nativeStaticReturn8Param9 */
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

/** nativeConstReturn8Param10 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) const>
inline LUA_FUNC(nativeConstReturn8Param10)
{
	if (CLASS* object = to<CLASS*>(L, -11))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, to<ARG_1>(L, -10), to<ARG_2>(L, -9), to<ARG_3>(L, -8), to<ARG_4>(L, -7), to<ARG_5>(L, -6), to<ARG_6>(L, -5), to<ARG_7>(L, -4), to<ARG_8>(L, -3), to<ARG_9>(L, -2), to<ARG_10>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		pushed += push(L, ret8);
		return pushed;
	}
	return 0;
} // nativeConstReturn8Param10

/** nativeMemberReturn8Param10 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline LUA_FUNC(nativeMemberReturn8Param10)
{
	if (CLASS* object = to<CLASS*>(L, -11))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, to<ARG_1>(L, -10), to<ARG_2>(L, -9), to<ARG_3>(L, -8), to<ARG_4>(L, -7), to<ARG_5>(L, -6), to<ARG_6>(L, -5), to<ARG_7>(L, -4), to<ARG_8>(L, -3), to<ARG_9>(L, -2), to<ARG_10>(L, -1));
		sint pushed(push(L, ret1));
		pushed += push(L, ret2);
		pushed += push(L, ret3);
		pushed += push(L, ret4);
		pushed += push(L, ret5);
		pushed += push(L, ret6);
		pushed += push(L, ret7);
		pushed += push(L, ret8);
		return pushed;
	}
	return 0;
} // nativeMemberReturn8Param10

/** nativeStaticReturn8Param10 */
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

/** nativeConstReturn9Param0 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&) const>
inline LUA_FUNC(nativeConstReturn9Param0)
{
	if (CLASS* object = to<CLASS*>(L, -1))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_9 ret9;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9);
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
	}
	return 0;
} // nativeConstReturn9Param0

/** nativeMemberReturn9Param0 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&) >
inline LUA_FUNC(nativeMemberReturn9Param0)
{
	if (CLASS* object = to<CLASS*>(L, -1))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_9 ret9;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9);
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
	}
	return 0;
} // nativeMemberReturn9Param0

/** nativeStaticReturn9Param0 */
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

/** nativeConstReturn9Param1 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1) const>
inline LUA_FUNC(nativeConstReturn9Param1)
{
	if (CLASS* object = to<CLASS*>(L, -2))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_9 ret9;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, to<ARG_1>(L, -1));
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
	}
	return 0;
} // nativeConstReturn9Param1

/** nativeMemberReturn9Param1 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1) >
inline LUA_FUNC(nativeMemberReturn9Param1)
{
	if (CLASS* object = to<CLASS*>(L, -2))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_9 ret9;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, to<ARG_1>(L, -1));
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
	}
	return 0;
} // nativeMemberReturn9Param1

/** nativeStaticReturn9Param1 */
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

/** nativeConstReturn9Param2 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2) const>
inline LUA_FUNC(nativeConstReturn9Param2)
{
	if (CLASS* object = to<CLASS*>(L, -3))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_9 ret9;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, to<ARG_1>(L, -2), to<ARG_2>(L, -1));
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
	}
	return 0;
} // nativeConstReturn9Param2

/** nativeMemberReturn9Param2 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2) >
inline LUA_FUNC(nativeMemberReturn9Param2)
{
	if (CLASS* object = to<CLASS*>(L, -3))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_9 ret9;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, to<ARG_1>(L, -2), to<ARG_2>(L, -1));
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
	}
	return 0;
} // nativeMemberReturn9Param2

/** nativeStaticReturn9Param2 */
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

/** nativeConstReturn9Param3 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3) const>
inline LUA_FUNC(nativeConstReturn9Param3)
{
	if (CLASS* object = to<CLASS*>(L, -4))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_9 ret9;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, to<ARG_1>(L, -3), to<ARG_2>(L, -2), to<ARG_3>(L, -1));
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
	}
	return 0;
} // nativeConstReturn9Param3

/** nativeMemberReturn9Param3 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3) >
inline LUA_FUNC(nativeMemberReturn9Param3)
{
	if (CLASS* object = to<CLASS*>(L, -4))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_9 ret9;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, to<ARG_1>(L, -3), to<ARG_2>(L, -2), to<ARG_3>(L, -1));
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
	}
	return 0;
} // nativeMemberReturn9Param3

/** nativeStaticReturn9Param3 */
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

/** nativeConstReturn9Param4 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4) const>
inline LUA_FUNC(nativeConstReturn9Param4)
{
	if (CLASS* object = to<CLASS*>(L, -5))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_9 ret9;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, to<ARG_1>(L, -4), to<ARG_2>(L, -3), to<ARG_3>(L, -2), to<ARG_4>(L, -1));
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
	}
	return 0;
} // nativeConstReturn9Param4

/** nativeMemberReturn9Param4 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline LUA_FUNC(nativeMemberReturn9Param4)
{
	if (CLASS* object = to<CLASS*>(L, -5))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_9 ret9;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, to<ARG_1>(L, -4), to<ARG_2>(L, -3), to<ARG_3>(L, -2), to<ARG_4>(L, -1));
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
	}
	return 0;
} // nativeMemberReturn9Param4

/** nativeStaticReturn9Param4 */
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

/** nativeConstReturn9Param5 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) const>
inline LUA_FUNC(nativeConstReturn9Param5)
{
	if (CLASS* object = to<CLASS*>(L, -6))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_9 ret9;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, to<ARG_1>(L, -5), to<ARG_2>(L, -4), to<ARG_3>(L, -3), to<ARG_4>(L, -2), to<ARG_5>(L, -1));
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
	}
	return 0;
} // nativeConstReturn9Param5

/** nativeMemberReturn9Param5 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline LUA_FUNC(nativeMemberReturn9Param5)
{
	if (CLASS* object = to<CLASS*>(L, -6))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_9 ret9;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, to<ARG_1>(L, -5), to<ARG_2>(L, -4), to<ARG_3>(L, -3), to<ARG_4>(L, -2), to<ARG_5>(L, -1));
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
	}
	return 0;
} // nativeMemberReturn9Param5

/** nativeStaticReturn9Param5 */
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

/** nativeConstReturn9Param6 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) const>
inline LUA_FUNC(nativeConstReturn9Param6)
{
	if (CLASS* object = to<CLASS*>(L, -7))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_9 ret9;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, to<ARG_1>(L, -6), to<ARG_2>(L, -5), to<ARG_3>(L, -4), to<ARG_4>(L, -3), to<ARG_5>(L, -2), to<ARG_6>(L, -1));
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
	}
	return 0;
} // nativeConstReturn9Param6

/** nativeMemberReturn9Param6 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline LUA_FUNC(nativeMemberReturn9Param6)
{
	if (CLASS* object = to<CLASS*>(L, -7))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_9 ret9;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, to<ARG_1>(L, -6), to<ARG_2>(L, -5), to<ARG_3>(L, -4), to<ARG_4>(L, -3), to<ARG_5>(L, -2), to<ARG_6>(L, -1));
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
	}
	return 0;
} // nativeMemberReturn9Param6

/** nativeStaticReturn9Param6 */
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

/** nativeConstReturn9Param7 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) const>
inline LUA_FUNC(nativeConstReturn9Param7)
{
	if (CLASS* object = to<CLASS*>(L, -8))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_9 ret9;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, to<ARG_1>(L, -7), to<ARG_2>(L, -6), to<ARG_3>(L, -5), to<ARG_4>(L, -4), to<ARG_5>(L, -3), to<ARG_6>(L, -2), to<ARG_7>(L, -1));
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
	}
	return 0;
} // nativeConstReturn9Param7

/** nativeMemberReturn9Param7 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline LUA_FUNC(nativeMemberReturn9Param7)
{
	if (CLASS* object = to<CLASS*>(L, -8))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_9 ret9;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, to<ARG_1>(L, -7), to<ARG_2>(L, -6), to<ARG_3>(L, -5), to<ARG_4>(L, -4), to<ARG_5>(L, -3), to<ARG_6>(L, -2), to<ARG_7>(L, -1));
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
	}
	return 0;
} // nativeMemberReturn9Param7

/** nativeStaticReturn9Param7 */
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

/** nativeConstReturn9Param8 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) const>
inline LUA_FUNC(nativeConstReturn9Param8)
{
	if (CLASS* object = to<CLASS*>(L, -9))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_9 ret9;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, to<ARG_1>(L, -8), to<ARG_2>(L, -7), to<ARG_3>(L, -6), to<ARG_4>(L, -5), to<ARG_5>(L, -4), to<ARG_6>(L, -3), to<ARG_7>(L, -2), to<ARG_8>(L, -1));
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
	}
	return 0;
} // nativeConstReturn9Param8

/** nativeMemberReturn9Param8 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline LUA_FUNC(nativeMemberReturn9Param8)
{
	if (CLASS* object = to<CLASS*>(L, -9))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_9 ret9;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, to<ARG_1>(L, -8), to<ARG_2>(L, -7), to<ARG_3>(L, -6), to<ARG_4>(L, -5), to<ARG_5>(L, -4), to<ARG_6>(L, -3), to<ARG_7>(L, -2), to<ARG_8>(L, -1));
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
	}
	return 0;
} // nativeMemberReturn9Param8

/** nativeStaticReturn9Param8 */
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

/** nativeConstReturn9Param9 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) const>
inline LUA_FUNC(nativeConstReturn9Param9)
{
	if (CLASS* object = to<CLASS*>(L, -10))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_9 ret9;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, to<ARG_1>(L, -9), to<ARG_2>(L, -8), to<ARG_3>(L, -7), to<ARG_4>(L, -6), to<ARG_5>(L, -5), to<ARG_6>(L, -4), to<ARG_7>(L, -3), to<ARG_8>(L, -2), to<ARG_9>(L, -1));
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
	}
	return 0;
} // nativeConstReturn9Param9

/** nativeMemberReturn9Param9 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline LUA_FUNC(nativeMemberReturn9Param9)
{
	if (CLASS* object = to<CLASS*>(L, -10))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_9 ret9;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, to<ARG_1>(L, -9), to<ARG_2>(L, -8), to<ARG_3>(L, -7), to<ARG_4>(L, -6), to<ARG_5>(L, -5), to<ARG_6>(L, -4), to<ARG_7>(L, -3), to<ARG_8>(L, -2), to<ARG_9>(L, -1));
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
	}
	return 0;
} // nativeMemberReturn9Param9

/** nativeStaticReturn9Param9 */
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

/** nativeConstReturn9Param10 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) const>
inline LUA_FUNC(nativeConstReturn9Param10)
{
	if (CLASS* object = to<CLASS*>(L, -11))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_9 ret9;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, to<ARG_1>(L, -10), to<ARG_2>(L, -9), to<ARG_3>(L, -8), to<ARG_4>(L, -7), to<ARG_5>(L, -6), to<ARG_6>(L, -5), to<ARG_7>(L, -4), to<ARG_8>(L, -3), to<ARG_9>(L, -2), to<ARG_10>(L, -1));
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
	}
	return 0;
} // nativeConstReturn9Param10

/** nativeMemberReturn9Param10 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline LUA_FUNC(nativeMemberReturn9Param10)
{
	if (CLASS* object = to<CLASS*>(L, -11))
	{
		RET_2 ret2;
		RET_3 ret3;
		RET_4 ret4;
		RET_5 ret5;
		RET_6 ret6;
		RET_7 ret7;
		RET_8 ret8;
		RET_9 ret9;
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, to<ARG_1>(L, -10), to<ARG_2>(L, -9), to<ARG_3>(L, -8), to<ARG_4>(L, -7), to<ARG_5>(L, -6), to<ARG_6>(L, -5), to<ARG_7>(L, -4), to<ARG_8>(L, -3), to<ARG_9>(L, -2), to<ARG_10>(L, -1));
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
	}
	return 0;
} // nativeMemberReturn9Param10

/** nativeStaticReturn9Param10 */
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

/** nativeConstReturn10Param0 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&) const>
inline LUA_FUNC(nativeConstReturn10Param0)
{
	if (CLASS* object = to<CLASS*>(L, -1))
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
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10);
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
	}
	return 0;
} // nativeConstReturn10Param0

/** nativeMemberReturn10Param0 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&) >
inline LUA_FUNC(nativeMemberReturn10Param0)
{
	if (CLASS* object = to<CLASS*>(L, -1))
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
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10);
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
	}
	return 0;
} // nativeMemberReturn10Param0

/** nativeStaticReturn10Param0 */
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

/** nativeConstReturn10Param1 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1) const>
inline LUA_FUNC(nativeConstReturn10Param1)
{
	if (CLASS* object = to<CLASS*>(L, -2))
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
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, to<ARG_1>(L, -1));
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
	}
	return 0;
} // nativeConstReturn10Param1

/** nativeMemberReturn10Param1 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1) >
inline LUA_FUNC(nativeMemberReturn10Param1)
{
	if (CLASS* object = to<CLASS*>(L, -2))
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
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, to<ARG_1>(L, -1));
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
	}
	return 0;
} // nativeMemberReturn10Param1

/** nativeStaticReturn10Param1 */
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

/** nativeConstReturn10Param2 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2) const>
inline LUA_FUNC(nativeConstReturn10Param2)
{
	if (CLASS* object = to<CLASS*>(L, -3))
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
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, to<ARG_1>(L, -2), to<ARG_2>(L, -1));
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
	}
	return 0;
} // nativeConstReturn10Param2

/** nativeMemberReturn10Param2 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2) >
inline LUA_FUNC(nativeMemberReturn10Param2)
{
	if (CLASS* object = to<CLASS*>(L, -3))
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
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, to<ARG_1>(L, -2), to<ARG_2>(L, -1));
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
	}
	return 0;
} // nativeMemberReturn10Param2

/** nativeStaticReturn10Param2 */
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

/** nativeConstReturn10Param3 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3) const>
inline LUA_FUNC(nativeConstReturn10Param3)
{
	if (CLASS* object = to<CLASS*>(L, -4))
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
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, to<ARG_1>(L, -3), to<ARG_2>(L, -2), to<ARG_3>(L, -1));
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
	}
	return 0;
} // nativeConstReturn10Param3

/** nativeMemberReturn10Param3 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3) >
inline LUA_FUNC(nativeMemberReturn10Param3)
{
	if (CLASS* object = to<CLASS*>(L, -4))
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
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, to<ARG_1>(L, -3), to<ARG_2>(L, -2), to<ARG_3>(L, -1));
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
	}
	return 0;
} // nativeMemberReturn10Param3

/** nativeStaticReturn10Param3 */
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

/** nativeConstReturn10Param4 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4) const>
inline LUA_FUNC(nativeConstReturn10Param4)
{
	if (CLASS* object = to<CLASS*>(L, -5))
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
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, to<ARG_1>(L, -4), to<ARG_2>(L, -3), to<ARG_3>(L, -2), to<ARG_4>(L, -1));
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
	}
	return 0;
} // nativeConstReturn10Param4

/** nativeMemberReturn10Param4 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline LUA_FUNC(nativeMemberReturn10Param4)
{
	if (CLASS* object = to<CLASS*>(L, -5))
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
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, to<ARG_1>(L, -4), to<ARG_2>(L, -3), to<ARG_3>(L, -2), to<ARG_4>(L, -1));
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
	}
	return 0;
} // nativeMemberReturn10Param4

/** nativeStaticReturn10Param4 */
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

/** nativeConstReturn10Param5 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) const>
inline LUA_FUNC(nativeConstReturn10Param5)
{
	if (CLASS* object = to<CLASS*>(L, -6))
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
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, to<ARG_1>(L, -5), to<ARG_2>(L, -4), to<ARG_3>(L, -3), to<ARG_4>(L, -2), to<ARG_5>(L, -1));
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
	}
	return 0;
} // nativeConstReturn10Param5

/** nativeMemberReturn10Param5 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline LUA_FUNC(nativeMemberReturn10Param5)
{
	if (CLASS* object = to<CLASS*>(L, -6))
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
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, to<ARG_1>(L, -5), to<ARG_2>(L, -4), to<ARG_3>(L, -3), to<ARG_4>(L, -2), to<ARG_5>(L, -1));
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
	}
	return 0;
} // nativeMemberReturn10Param5

/** nativeStaticReturn10Param5 */
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

/** nativeConstReturn10Param6 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) const>
inline LUA_FUNC(nativeConstReturn10Param6)
{
	if (CLASS* object = to<CLASS*>(L, -7))
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
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, to<ARG_1>(L, -6), to<ARG_2>(L, -5), to<ARG_3>(L, -4), to<ARG_4>(L, -3), to<ARG_5>(L, -2), to<ARG_6>(L, -1));
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
	}
	return 0;
} // nativeConstReturn10Param6

/** nativeMemberReturn10Param6 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline LUA_FUNC(nativeMemberReturn10Param6)
{
	if (CLASS* object = to<CLASS*>(L, -7))
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
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, to<ARG_1>(L, -6), to<ARG_2>(L, -5), to<ARG_3>(L, -4), to<ARG_4>(L, -3), to<ARG_5>(L, -2), to<ARG_6>(L, -1));
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
	}
	return 0;
} // nativeMemberReturn10Param6

/** nativeStaticReturn10Param6 */
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

/** nativeConstReturn10Param7 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) const>
inline LUA_FUNC(nativeConstReturn10Param7)
{
	if (CLASS* object = to<CLASS*>(L, -8))
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
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, to<ARG_1>(L, -7), to<ARG_2>(L, -6), to<ARG_3>(L, -5), to<ARG_4>(L, -4), to<ARG_5>(L, -3), to<ARG_6>(L, -2), to<ARG_7>(L, -1));
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
	}
	return 0;
} // nativeConstReturn10Param7

/** nativeMemberReturn10Param7 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline LUA_FUNC(nativeMemberReturn10Param7)
{
	if (CLASS* object = to<CLASS*>(L, -8))
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
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, to<ARG_1>(L, -7), to<ARG_2>(L, -6), to<ARG_3>(L, -5), to<ARG_4>(L, -4), to<ARG_5>(L, -3), to<ARG_6>(L, -2), to<ARG_7>(L, -1));
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
	}
	return 0;
} // nativeMemberReturn10Param7

/** nativeStaticReturn10Param7 */
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

/** nativeConstReturn10Param8 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) const>
inline LUA_FUNC(nativeConstReturn10Param8)
{
	if (CLASS* object = to<CLASS*>(L, -9))
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
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, to<ARG_1>(L, -8), to<ARG_2>(L, -7), to<ARG_3>(L, -6), to<ARG_4>(L, -5), to<ARG_5>(L, -4), to<ARG_6>(L, -3), to<ARG_7>(L, -2), to<ARG_8>(L, -1));
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
	}
	return 0;
} // nativeConstReturn10Param8

/** nativeMemberReturn10Param8 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline LUA_FUNC(nativeMemberReturn10Param8)
{
	if (CLASS* object = to<CLASS*>(L, -9))
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
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, to<ARG_1>(L, -8), to<ARG_2>(L, -7), to<ARG_3>(L, -6), to<ARG_4>(L, -5), to<ARG_5>(L, -4), to<ARG_6>(L, -3), to<ARG_7>(L, -2), to<ARG_8>(L, -1));
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
	}
	return 0;
} // nativeMemberReturn10Param8

/** nativeStaticReturn10Param8 */
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

/** nativeConstReturn10Param9 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) const>
inline LUA_FUNC(nativeConstReturn10Param9)
{
	if (CLASS* object = to<CLASS*>(L, -10))
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
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, to<ARG_1>(L, -9), to<ARG_2>(L, -8), to<ARG_3>(L, -7), to<ARG_4>(L, -6), to<ARG_5>(L, -5), to<ARG_6>(L, -4), to<ARG_7>(L, -3), to<ARG_8>(L, -2), to<ARG_9>(L, -1));
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
	}
	return 0;
} // nativeConstReturn10Param9

/** nativeMemberReturn10Param9 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline LUA_FUNC(nativeMemberReturn10Param9)
{
	if (CLASS* object = to<CLASS*>(L, -10))
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
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, to<ARG_1>(L, -9), to<ARG_2>(L, -8), to<ARG_3>(L, -7), to<ARG_4>(L, -6), to<ARG_5>(L, -5), to<ARG_6>(L, -4), to<ARG_7>(L, -3), to<ARG_8>(L, -2), to<ARG_9>(L, -1));
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
	}
	return 0;
} // nativeMemberReturn10Param9

/** nativeStaticReturn10Param9 */
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

/** nativeConstReturn10Param10 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) const>
inline LUA_FUNC(nativeConstReturn10Param10)
{
	if (CLASS* object = to<CLASS*>(L, -11))
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
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, to<ARG_1>(L, -10), to<ARG_2>(L, -9), to<ARG_3>(L, -8), to<ARG_4>(L, -7), to<ARG_5>(L, -6), to<ARG_6>(L, -5), to<ARG_7>(L, -4), to<ARG_8>(L, -3), to<ARG_9>(L, -2), to<ARG_10>(L, -1));
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
	}
	return 0;
} // nativeConstReturn10Param10

/** nativeMemberReturn10Param10 */
template< typename CLASS, typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, RET_1 (CLASS::* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline LUA_FUNC(nativeMemberReturn10Param10)
{
	if (CLASS* object = to<CLASS*>(L, -11))
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
		RET_1 ret1 = (object->*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, to<ARG_1>(L, -10), to<ARG_2>(L, -9), to<ARG_3>(L, -8), to<ARG_4>(L, -7), to<ARG_5>(L, -6), to<ARG_6>(L, -5), to<ARG_7>(L, -4), to<ARG_8>(L, -3), to<ARG_9>(L, -2), to<ARG_10>(L, -1));
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
	}
	return 0;
} // nativeMemberReturn10Param10

/** nativeStaticReturn10Param10 */
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

