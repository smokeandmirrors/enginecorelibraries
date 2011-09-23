

//test generateStaticTemplate
template< typename ARG_1, void (* function)(ARG_1) >
inline LUA_FUNC(nativeStaticReturn1Param0)
{
	sint pushed(0);
	ARG_1 arg1 = to<ARG_1>(L, -1);
	(*function)(arg1);

	return pushed;
} // nativeStaticReturn0Param1

//test generateStaticTemplate
template< typename RET_1, RET_1 (* function)(void) >
inline LUA_FUNC(nativeStaticReturn0Param1)
{
	sint pushed(0);
	RET_1 ret1 = (*function)();
	pushed += push(L, ret1);

	return pushed;
} // nativeStaticReturn1Param0

//test generateStaticTemplate
template< typename RET_1, typename ARG_1, void (* function)(ARG_1) >
inline LUA_FUNC(nativeStaticReturn1Param1)
{
	sint pushed(0);
	ARG_1 arg1 = to<ARG_1>(L, -1);
	RET_1 ret1 = (*function)(arg1);
	pushed += push(L, ret1);

	return pushed;
} // nativeStaticReturn1Param1

//test generateStaticTemplate
template< typename RET_1, typename ARG_1, typename ARG_2, void (* function)(ARG_1, ARG_2) >
inline LUA_FUNC(nativeStaticReturn2Param1)
{
	sint pushed(0);
	ARG_1 arg1 = to<ARG_1>(L, -2);
	ARG_2 arg2 = to<ARG_2>(L, -1);
	RET_1 ret1 = (*function)(arg1, arg2);
	pushed += push(L, ret1);

	return pushed;
} // nativeStaticReturn1Param2

//test generateStaticTemplate
template< typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, void (* function)(ARG_1, ARG_2, ARG_3) >
inline LUA_FUNC(nativeStaticReturn3Param1)
{
	sint pushed(0);
	ARG_1 arg1 = to<ARG_1>(L, -3);
	ARG_2 arg2 = to<ARG_2>(L, -2);
	ARG_3 arg3 = to<ARG_3>(L, -1);
	RET_1 ret1 = (*function)(arg1, arg2, arg3);
	pushed += push(L, ret1);

	return pushed;
} // nativeStaticReturn1Param3

//test generateStaticTemplate
template< typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, void (* function)(ARG_1, ARG_2, ARG_3, ARG_4) >
inline LUA_FUNC(nativeStaticReturn4Param1)
{
	sint pushed(0);
	ARG_1 arg1 = to<ARG_1>(L, -4);
	ARG_2 arg2 = to<ARG_2>(L, -3);
	ARG_3 arg3 = to<ARG_3>(L, -2);
	ARG_4 arg4 = to<ARG_4>(L, -1);
	RET_1 ret1 = (*function)(arg1, arg2, arg3, arg4);
	pushed += push(L, ret1);

	return pushed;
} // nativeStaticReturn1Param4

//test generateStaticTemplate
template< typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, void (* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline LUA_FUNC(nativeStaticReturn5Param1)
{
	sint pushed(0);
	ARG_1 arg1 = to<ARG_1>(L, -5);
	ARG_2 arg2 = to<ARG_2>(L, -4);
	ARG_3 arg3 = to<ARG_3>(L, -3);
	ARG_4 arg4 = to<ARG_4>(L, -2);
	ARG_5 arg5 = to<ARG_5>(L, -1);
	RET_1 ret1 = (*function)(arg1, arg2, arg3, arg4, arg5);
	pushed += push(L, ret1);

	return pushed;
} // nativeStaticReturn1Param5

//test generateStaticTemplate
template< typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, void (* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline LUA_FUNC(nativeStaticReturn6Param1)
{
	sint pushed(0);
	ARG_1 arg1 = to<ARG_1>(L, -6);
	ARG_2 arg2 = to<ARG_2>(L, -5);
	ARG_3 arg3 = to<ARG_3>(L, -4);
	ARG_4 arg4 = to<ARG_4>(L, -3);
	ARG_5 arg5 = to<ARG_5>(L, -2);
	ARG_6 arg6 = to<ARG_6>(L, -1);
	RET_1 ret1 = (*function)(arg1, arg2, arg3, arg4, arg5, arg6);
	pushed += push(L, ret1);

	return pushed;
} // nativeStaticReturn1Param6

//test generateStaticTemplate
template< typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, void (* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline LUA_FUNC(nativeStaticReturn7Param1)
{
	sint pushed(0);
	ARG_1 arg1 = to<ARG_1>(L, -7);
	ARG_2 arg2 = to<ARG_2>(L, -6);
	ARG_3 arg3 = to<ARG_3>(L, -5);
	ARG_4 arg4 = to<ARG_4>(L, -4);
	ARG_5 arg5 = to<ARG_5>(L, -3);
	ARG_6 arg6 = to<ARG_6>(L, -2);
	ARG_7 arg7 = to<ARG_7>(L, -1);
	RET_1 ret1 = (*function)(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
	pushed += push(L, ret1);

	return pushed;
} // nativeStaticReturn1Param7

//test generateStaticTemplate
template< typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, void (* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline LUA_FUNC(nativeStaticReturn8Param1)
{
	sint pushed(0);
	ARG_1 arg1 = to<ARG_1>(L, -8);
	ARG_2 arg2 = to<ARG_2>(L, -7);
	ARG_3 arg3 = to<ARG_3>(L, -6);
	ARG_4 arg4 = to<ARG_4>(L, -5);
	ARG_5 arg5 = to<ARG_5>(L, -4);
	ARG_6 arg6 = to<ARG_6>(L, -3);
	ARG_7 arg7 = to<ARG_7>(L, -2);
	ARG_8 arg8 = to<ARG_8>(L, -1);
	RET_1 ret1 = (*function)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
	pushed += push(L, ret1);

	return pushed;
} // nativeStaticReturn1Param8

//test generateStaticTemplate
template< typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, void (* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline LUA_FUNC(nativeStaticReturn9Param1)
{
	sint pushed(0);
	ARG_1 arg1 = to<ARG_1>(L, -9);
	ARG_2 arg2 = to<ARG_2>(L, -8);
	ARG_3 arg3 = to<ARG_3>(L, -7);
	ARG_4 arg4 = to<ARG_4>(L, -6);
	ARG_5 arg5 = to<ARG_5>(L, -5);
	ARG_6 arg6 = to<ARG_6>(L, -4);
	ARG_7 arg7 = to<ARG_7>(L, -3);
	ARG_8 arg8 = to<ARG_8>(L, -2);
	ARG_9 arg9 = to<ARG_9>(L, -1);
	RET_1 ret1 = (*function)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
	pushed += push(L, ret1);

	return pushed;
} // nativeStaticReturn1Param9

//test generateStaticTemplate
template< typename RET_1, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, void (* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline LUA_FUNC(nativeStaticReturn10Param1)
{
	sint pushed(0);
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
	RET_1 ret1 = (*function)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
	pushed += push(L, ret1);

	return pushed;
} // nativeStaticReturn1Param10

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename ARG_1, void (* function)(RET_2&, ARG_1) >
inline LUA_FUNC(nativeStaticReturn1Param2)
{
	sint pushed(0);
	RET_2 ret2;
	ARG_1 arg1 = to<ARG_1>(L, -1);
	RET_1 ret1 = (*function)(ret2, arg1);
	pushed += push(L, ret1);
	pushed += push(L, ret2);

	return pushed;
} // nativeStaticReturn2Param1

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, void (* function)(RET_2&, ARG_1, ARG_2) >
inline LUA_FUNC(nativeStaticReturn2Param2)
{
	sint pushed(0);
	RET_2 ret2;
	ARG_1 arg1 = to<ARG_1>(L, -2);
	ARG_2 arg2 = to<ARG_2>(L, -1);
	RET_1 ret1 = (*function)(ret2, arg1, arg2);
	pushed += push(L, ret1);
	pushed += push(L, ret2);

	return pushed;
} // nativeStaticReturn2Param2

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, void (* function)(RET_2&, ARG_1, ARG_2, ARG_3) >
inline LUA_FUNC(nativeStaticReturn3Param2)
{
	sint pushed(0);
	RET_2 ret2;
	ARG_1 arg1 = to<ARG_1>(L, -3);
	ARG_2 arg2 = to<ARG_2>(L, -2);
	ARG_3 arg3 = to<ARG_3>(L, -1);
	RET_1 ret1 = (*function)(ret2, arg1, arg2, arg3);
	pushed += push(L, ret1);
	pushed += push(L, ret2);

	return pushed;
} // nativeStaticReturn2Param3

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, void (* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline LUA_FUNC(nativeStaticReturn4Param2)
{
	sint pushed(0);
	RET_2 ret2;
	ARG_1 arg1 = to<ARG_1>(L, -4);
	ARG_2 arg2 = to<ARG_2>(L, -3);
	ARG_3 arg3 = to<ARG_3>(L, -2);
	ARG_4 arg4 = to<ARG_4>(L, -1);
	RET_1 ret1 = (*function)(ret2, arg1, arg2, arg3, arg4);
	pushed += push(L, ret1);
	pushed += push(L, ret2);

	return pushed;
} // nativeStaticReturn2Param4

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, void (* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline LUA_FUNC(nativeStaticReturn5Param2)
{
	sint pushed(0);
	RET_2 ret2;
	ARG_1 arg1 = to<ARG_1>(L, -5);
	ARG_2 arg2 = to<ARG_2>(L, -4);
	ARG_3 arg3 = to<ARG_3>(L, -3);
	ARG_4 arg4 = to<ARG_4>(L, -2);
	ARG_5 arg5 = to<ARG_5>(L, -1);
	RET_1 ret1 = (*function)(ret2, arg1, arg2, arg3, arg4, arg5);
	pushed += push(L, ret1);
	pushed += push(L, ret2);

	return pushed;
} // nativeStaticReturn2Param5

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, void (* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline LUA_FUNC(nativeStaticReturn6Param2)
{
	sint pushed(0);
	RET_2 ret2;
	ARG_1 arg1 = to<ARG_1>(L, -6);
	ARG_2 arg2 = to<ARG_2>(L, -5);
	ARG_3 arg3 = to<ARG_3>(L, -4);
	ARG_4 arg4 = to<ARG_4>(L, -3);
	ARG_5 arg5 = to<ARG_5>(L, -2);
	ARG_6 arg6 = to<ARG_6>(L, -1);
	RET_1 ret1 = (*function)(ret2, arg1, arg2, arg3, arg4, arg5, arg6);
	pushed += push(L, ret1);
	pushed += push(L, ret2);

	return pushed;
} // nativeStaticReturn2Param6

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, void (* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline LUA_FUNC(nativeStaticReturn7Param2)
{
	sint pushed(0);
	RET_2 ret2;
	ARG_1 arg1 = to<ARG_1>(L, -7);
	ARG_2 arg2 = to<ARG_2>(L, -6);
	ARG_3 arg3 = to<ARG_3>(L, -5);
	ARG_4 arg4 = to<ARG_4>(L, -4);
	ARG_5 arg5 = to<ARG_5>(L, -3);
	ARG_6 arg6 = to<ARG_6>(L, -2);
	ARG_7 arg7 = to<ARG_7>(L, -1);
	RET_1 ret1 = (*function)(ret2, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
	pushed += push(L, ret1);
	pushed += push(L, ret2);

	return pushed;
} // nativeStaticReturn2Param7

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, void (* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline LUA_FUNC(nativeStaticReturn8Param2)
{
	sint pushed(0);
	RET_2 ret2;
	ARG_1 arg1 = to<ARG_1>(L, -8);
	ARG_2 arg2 = to<ARG_2>(L, -7);
	ARG_3 arg3 = to<ARG_3>(L, -6);
	ARG_4 arg4 = to<ARG_4>(L, -5);
	ARG_5 arg5 = to<ARG_5>(L, -4);
	ARG_6 arg6 = to<ARG_6>(L, -3);
	ARG_7 arg7 = to<ARG_7>(L, -2);
	ARG_8 arg8 = to<ARG_8>(L, -1);
	RET_1 ret1 = (*function)(ret2, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
	pushed += push(L, ret1);
	pushed += push(L, ret2);

	return pushed;
} // nativeStaticReturn2Param8

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, void (* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline LUA_FUNC(nativeStaticReturn9Param2)
{
	sint pushed(0);
	RET_2 ret2;
	ARG_1 arg1 = to<ARG_1>(L, -9);
	ARG_2 arg2 = to<ARG_2>(L, -8);
	ARG_3 arg3 = to<ARG_3>(L, -7);
	ARG_4 arg4 = to<ARG_4>(L, -6);
	ARG_5 arg5 = to<ARG_5>(L, -5);
	ARG_6 arg6 = to<ARG_6>(L, -4);
	ARG_7 arg7 = to<ARG_7>(L, -3);
	ARG_8 arg8 = to<ARG_8>(L, -2);
	ARG_9 arg9 = to<ARG_9>(L, -1);
	RET_1 ret1 = (*function)(ret2, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
	pushed += push(L, ret1);
	pushed += push(L, ret2);

	return pushed;
} // nativeStaticReturn2Param9

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, void (* function)(RET_2&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline LUA_FUNC(nativeStaticReturn10Param2)
{
	sint pushed(0);
	RET_2 ret2;
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
	RET_1 ret1 = (*function)(ret2, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
	pushed += push(L, ret1);
	pushed += push(L, ret2);

	return pushed;
} // nativeStaticReturn2Param10

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename ARG_1, void (* function)(RET_2&, RET_3&, ARG_1) >
inline LUA_FUNC(nativeStaticReturn1Param3)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	ARG_1 arg1 = to<ARG_1>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, arg1);
	pushed += push(L, ret1);
	pushed += push(L, ret2);
	pushed += push(L, ret3);

	return pushed;
} // nativeStaticReturn3Param1

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, void (* function)(RET_2&, RET_3&, ARG_1, ARG_2) >
inline LUA_FUNC(nativeStaticReturn2Param3)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	ARG_1 arg1 = to<ARG_1>(L, -2);
	ARG_2 arg2 = to<ARG_2>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, arg1, arg2);
	pushed += push(L, ret1);
	pushed += push(L, ret2);
	pushed += push(L, ret3);

	return pushed;
} // nativeStaticReturn3Param2

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, void (* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3) >
inline LUA_FUNC(nativeStaticReturn3Param3)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	ARG_1 arg1 = to<ARG_1>(L, -3);
	ARG_2 arg2 = to<ARG_2>(L, -2);
	ARG_3 arg3 = to<ARG_3>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, arg1, arg2, arg3);
	pushed += push(L, ret1);
	pushed += push(L, ret2);
	pushed += push(L, ret3);

	return pushed;
} // nativeStaticReturn3Param3

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, void (* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline LUA_FUNC(nativeStaticReturn4Param3)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	ARG_1 arg1 = to<ARG_1>(L, -4);
	ARG_2 arg2 = to<ARG_2>(L, -3);
	ARG_3 arg3 = to<ARG_3>(L, -2);
	ARG_4 arg4 = to<ARG_4>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, arg1, arg2, arg3, arg4);
	pushed += push(L, ret1);
	pushed += push(L, ret2);
	pushed += push(L, ret3);

	return pushed;
} // nativeStaticReturn3Param4

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, void (* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline LUA_FUNC(nativeStaticReturn5Param3)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	ARG_1 arg1 = to<ARG_1>(L, -5);
	ARG_2 arg2 = to<ARG_2>(L, -4);
	ARG_3 arg3 = to<ARG_3>(L, -3);
	ARG_4 arg4 = to<ARG_4>(L, -2);
	ARG_5 arg5 = to<ARG_5>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, arg1, arg2, arg3, arg4, arg5);
	pushed += push(L, ret1);
	pushed += push(L, ret2);
	pushed += push(L, ret3);

	return pushed;
} // nativeStaticReturn3Param5

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, void (* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline LUA_FUNC(nativeStaticReturn6Param3)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	ARG_1 arg1 = to<ARG_1>(L, -6);
	ARG_2 arg2 = to<ARG_2>(L, -5);
	ARG_3 arg3 = to<ARG_3>(L, -4);
	ARG_4 arg4 = to<ARG_4>(L, -3);
	ARG_5 arg5 = to<ARG_5>(L, -2);
	ARG_6 arg6 = to<ARG_6>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, arg1, arg2, arg3, arg4, arg5, arg6);
	pushed += push(L, ret1);
	pushed += push(L, ret2);
	pushed += push(L, ret3);

	return pushed;
} // nativeStaticReturn3Param6

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, void (* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline LUA_FUNC(nativeStaticReturn7Param3)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	ARG_1 arg1 = to<ARG_1>(L, -7);
	ARG_2 arg2 = to<ARG_2>(L, -6);
	ARG_3 arg3 = to<ARG_3>(L, -5);
	ARG_4 arg4 = to<ARG_4>(L, -4);
	ARG_5 arg5 = to<ARG_5>(L, -3);
	ARG_6 arg6 = to<ARG_6>(L, -2);
	ARG_7 arg7 = to<ARG_7>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
	pushed += push(L, ret1);
	pushed += push(L, ret2);
	pushed += push(L, ret3);

	return pushed;
} // nativeStaticReturn3Param7

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, void (* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline LUA_FUNC(nativeStaticReturn8Param3)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	ARG_1 arg1 = to<ARG_1>(L, -8);
	ARG_2 arg2 = to<ARG_2>(L, -7);
	ARG_3 arg3 = to<ARG_3>(L, -6);
	ARG_4 arg4 = to<ARG_4>(L, -5);
	ARG_5 arg5 = to<ARG_5>(L, -4);
	ARG_6 arg6 = to<ARG_6>(L, -3);
	ARG_7 arg7 = to<ARG_7>(L, -2);
	ARG_8 arg8 = to<ARG_8>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
	pushed += push(L, ret1);
	pushed += push(L, ret2);
	pushed += push(L, ret3);

	return pushed;
} // nativeStaticReturn3Param8

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, void (* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline LUA_FUNC(nativeStaticReturn9Param3)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	ARG_1 arg1 = to<ARG_1>(L, -9);
	ARG_2 arg2 = to<ARG_2>(L, -8);
	ARG_3 arg3 = to<ARG_3>(L, -7);
	ARG_4 arg4 = to<ARG_4>(L, -6);
	ARG_5 arg5 = to<ARG_5>(L, -5);
	ARG_6 arg6 = to<ARG_6>(L, -4);
	ARG_7 arg7 = to<ARG_7>(L, -3);
	ARG_8 arg8 = to<ARG_8>(L, -2);
	ARG_9 arg9 = to<ARG_9>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
	pushed += push(L, ret1);
	pushed += push(L, ret2);
	pushed += push(L, ret3);

	return pushed;
} // nativeStaticReturn3Param9

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, void (* function)(RET_2&, RET_3&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline LUA_FUNC(nativeStaticReturn10Param3)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
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
	RET_1 ret1 = (*function)(ret2, ret3, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
	pushed += push(L, ret1);
	pushed += push(L, ret2);
	pushed += push(L, ret3);

	return pushed;
} // nativeStaticReturn3Param10

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, void (* function)(RET_2&, RET_3&, RET_4&, ARG_1) >
inline LUA_FUNC(nativeStaticReturn1Param4)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	RET_4 ret4;
	ARG_1 arg1 = to<ARG_1>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, arg1);
	pushed += push(L, ret1);
	pushed += push(L, ret2);
	pushed += push(L, ret3);
	pushed += push(L, ret4);

	return pushed;
} // nativeStaticReturn4Param1

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, void (* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2) >
inline LUA_FUNC(nativeStaticReturn2Param4)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	RET_4 ret4;
	ARG_1 arg1 = to<ARG_1>(L, -2);
	ARG_2 arg2 = to<ARG_2>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, arg1, arg2);
	pushed += push(L, ret1);
	pushed += push(L, ret2);
	pushed += push(L, ret3);
	pushed += push(L, ret4);

	return pushed;
} // nativeStaticReturn4Param2

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, void (* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3) >
inline LUA_FUNC(nativeStaticReturn3Param4)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	RET_4 ret4;
	ARG_1 arg1 = to<ARG_1>(L, -3);
	ARG_2 arg2 = to<ARG_2>(L, -2);
	ARG_3 arg3 = to<ARG_3>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, arg1, arg2, arg3);
	pushed += push(L, ret1);
	pushed += push(L, ret2);
	pushed += push(L, ret3);
	pushed += push(L, ret4);

	return pushed;
} // nativeStaticReturn4Param3

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, void (* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline LUA_FUNC(nativeStaticReturn4Param4)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	RET_4 ret4;
	ARG_1 arg1 = to<ARG_1>(L, -4);
	ARG_2 arg2 = to<ARG_2>(L, -3);
	ARG_3 arg3 = to<ARG_3>(L, -2);
	ARG_4 arg4 = to<ARG_4>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, arg1, arg2, arg3, arg4);
	pushed += push(L, ret1);
	pushed += push(L, ret2);
	pushed += push(L, ret3);
	pushed += push(L, ret4);

	return pushed;
} // nativeStaticReturn4Param4

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, void (* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline LUA_FUNC(nativeStaticReturn5Param4)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	RET_4 ret4;
	ARG_1 arg1 = to<ARG_1>(L, -5);
	ARG_2 arg2 = to<ARG_2>(L, -4);
	ARG_3 arg3 = to<ARG_3>(L, -3);
	ARG_4 arg4 = to<ARG_4>(L, -2);
	ARG_5 arg5 = to<ARG_5>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, arg1, arg2, arg3, arg4, arg5);
	pushed += push(L, ret1);
	pushed += push(L, ret2);
	pushed += push(L, ret3);
	pushed += push(L, ret4);

	return pushed;
} // nativeStaticReturn4Param5

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, void (* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline LUA_FUNC(nativeStaticReturn6Param4)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	RET_4 ret4;
	ARG_1 arg1 = to<ARG_1>(L, -6);
	ARG_2 arg2 = to<ARG_2>(L, -5);
	ARG_3 arg3 = to<ARG_3>(L, -4);
	ARG_4 arg4 = to<ARG_4>(L, -3);
	ARG_5 arg5 = to<ARG_5>(L, -2);
	ARG_6 arg6 = to<ARG_6>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, arg1, arg2, arg3, arg4, arg5, arg6);
	pushed += push(L, ret1);
	pushed += push(L, ret2);
	pushed += push(L, ret3);
	pushed += push(L, ret4);

	return pushed;
} // nativeStaticReturn4Param6

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, void (* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline LUA_FUNC(nativeStaticReturn7Param4)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	RET_4 ret4;
	ARG_1 arg1 = to<ARG_1>(L, -7);
	ARG_2 arg2 = to<ARG_2>(L, -6);
	ARG_3 arg3 = to<ARG_3>(L, -5);
	ARG_4 arg4 = to<ARG_4>(L, -4);
	ARG_5 arg5 = to<ARG_5>(L, -3);
	ARG_6 arg6 = to<ARG_6>(L, -2);
	ARG_7 arg7 = to<ARG_7>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
	pushed += push(L, ret1);
	pushed += push(L, ret2);
	pushed += push(L, ret3);
	pushed += push(L, ret4);

	return pushed;
} // nativeStaticReturn4Param7

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, void (* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline LUA_FUNC(nativeStaticReturn8Param4)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	RET_4 ret4;
	ARG_1 arg1 = to<ARG_1>(L, -8);
	ARG_2 arg2 = to<ARG_2>(L, -7);
	ARG_3 arg3 = to<ARG_3>(L, -6);
	ARG_4 arg4 = to<ARG_4>(L, -5);
	ARG_5 arg5 = to<ARG_5>(L, -4);
	ARG_6 arg6 = to<ARG_6>(L, -3);
	ARG_7 arg7 = to<ARG_7>(L, -2);
	ARG_8 arg8 = to<ARG_8>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
	pushed += push(L, ret1);
	pushed += push(L, ret2);
	pushed += push(L, ret3);
	pushed += push(L, ret4);

	return pushed;
} // nativeStaticReturn4Param8

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, void (* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline LUA_FUNC(nativeStaticReturn9Param4)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	RET_4 ret4;
	ARG_1 arg1 = to<ARG_1>(L, -9);
	ARG_2 arg2 = to<ARG_2>(L, -8);
	ARG_3 arg3 = to<ARG_3>(L, -7);
	ARG_4 arg4 = to<ARG_4>(L, -6);
	ARG_5 arg5 = to<ARG_5>(L, -5);
	ARG_6 arg6 = to<ARG_6>(L, -4);
	ARG_7 arg7 = to<ARG_7>(L, -3);
	ARG_8 arg8 = to<ARG_8>(L, -2);
	ARG_9 arg9 = to<ARG_9>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
	pushed += push(L, ret1);
	pushed += push(L, ret2);
	pushed += push(L, ret3);
	pushed += push(L, ret4);

	return pushed;
} // nativeStaticReturn4Param9

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, void (* function)(RET_2&, RET_3&, RET_4&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline LUA_FUNC(nativeStaticReturn10Param4)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	RET_4 ret4;
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
	RET_1 ret1 = (*function)(ret2, ret3, ret4, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
	pushed += push(L, ret1);
	pushed += push(L, ret2);
	pushed += push(L, ret3);
	pushed += push(L, ret4);

	return pushed;
} // nativeStaticReturn4Param10

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1) >
inline LUA_FUNC(nativeStaticReturn1Param5)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	RET_4 ret4;
	RET_5 ret5;
	ARG_1 arg1 = to<ARG_1>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, arg1);
	pushed += push(L, ret1);
	pushed += push(L, ret2);
	pushed += push(L, ret3);
	pushed += push(L, ret4);
	pushed += push(L, ret5);

	return pushed;
} // nativeStaticReturn5Param1

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2) >
inline LUA_FUNC(nativeStaticReturn2Param5)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	RET_4 ret4;
	RET_5 ret5;
	ARG_1 arg1 = to<ARG_1>(L, -2);
	ARG_2 arg2 = to<ARG_2>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, arg1, arg2);
	pushed += push(L, ret1);
	pushed += push(L, ret2);
	pushed += push(L, ret3);
	pushed += push(L, ret4);
	pushed += push(L, ret5);

	return pushed;
} // nativeStaticReturn5Param2

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3) >
inline LUA_FUNC(nativeStaticReturn3Param5)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	RET_4 ret4;
	RET_5 ret5;
	ARG_1 arg1 = to<ARG_1>(L, -3);
	ARG_2 arg2 = to<ARG_2>(L, -2);
	ARG_3 arg3 = to<ARG_3>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, arg1, arg2, arg3);
	pushed += push(L, ret1);
	pushed += push(L, ret2);
	pushed += push(L, ret3);
	pushed += push(L, ret4);
	pushed += push(L, ret5);

	return pushed;
} // nativeStaticReturn5Param3

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline LUA_FUNC(nativeStaticReturn4Param5)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	RET_4 ret4;
	RET_5 ret5;
	ARG_1 arg1 = to<ARG_1>(L, -4);
	ARG_2 arg2 = to<ARG_2>(L, -3);
	ARG_3 arg3 = to<ARG_3>(L, -2);
	ARG_4 arg4 = to<ARG_4>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4);
	pushed += push(L, ret1);
	pushed += push(L, ret2);
	pushed += push(L, ret3);
	pushed += push(L, ret4);
	pushed += push(L, ret5);

	return pushed;
} // nativeStaticReturn5Param4

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline LUA_FUNC(nativeStaticReturn5Param5)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	RET_4 ret4;
	RET_5 ret5;
	ARG_1 arg1 = to<ARG_1>(L, -5);
	ARG_2 arg2 = to<ARG_2>(L, -4);
	ARG_3 arg3 = to<ARG_3>(L, -3);
	ARG_4 arg4 = to<ARG_4>(L, -2);
	ARG_5 arg5 = to<ARG_5>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4, arg5);
	pushed += push(L, ret1);
	pushed += push(L, ret2);
	pushed += push(L, ret3);
	pushed += push(L, ret4);
	pushed += push(L, ret5);

	return pushed;
} // nativeStaticReturn5Param5

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline LUA_FUNC(nativeStaticReturn6Param5)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	RET_4 ret4;
	RET_5 ret5;
	ARG_1 arg1 = to<ARG_1>(L, -6);
	ARG_2 arg2 = to<ARG_2>(L, -5);
	ARG_3 arg3 = to<ARG_3>(L, -4);
	ARG_4 arg4 = to<ARG_4>(L, -3);
	ARG_5 arg5 = to<ARG_5>(L, -2);
	ARG_6 arg6 = to<ARG_6>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4, arg5, arg6);
	pushed += push(L, ret1);
	pushed += push(L, ret2);
	pushed += push(L, ret3);
	pushed += push(L, ret4);
	pushed += push(L, ret5);

	return pushed;
} // nativeStaticReturn5Param6

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline LUA_FUNC(nativeStaticReturn7Param5)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	RET_4 ret4;
	RET_5 ret5;
	ARG_1 arg1 = to<ARG_1>(L, -7);
	ARG_2 arg2 = to<ARG_2>(L, -6);
	ARG_3 arg3 = to<ARG_3>(L, -5);
	ARG_4 arg4 = to<ARG_4>(L, -4);
	ARG_5 arg5 = to<ARG_5>(L, -3);
	ARG_6 arg6 = to<ARG_6>(L, -2);
	ARG_7 arg7 = to<ARG_7>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
	pushed += push(L, ret1);
	pushed += push(L, ret2);
	pushed += push(L, ret3);
	pushed += push(L, ret4);
	pushed += push(L, ret5);

	return pushed;
} // nativeStaticReturn5Param7

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline LUA_FUNC(nativeStaticReturn8Param5)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	RET_4 ret4;
	RET_5 ret5;
	ARG_1 arg1 = to<ARG_1>(L, -8);
	ARG_2 arg2 = to<ARG_2>(L, -7);
	ARG_3 arg3 = to<ARG_3>(L, -6);
	ARG_4 arg4 = to<ARG_4>(L, -5);
	ARG_5 arg5 = to<ARG_5>(L, -4);
	ARG_6 arg6 = to<ARG_6>(L, -3);
	ARG_7 arg7 = to<ARG_7>(L, -2);
	ARG_8 arg8 = to<ARG_8>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
	pushed += push(L, ret1);
	pushed += push(L, ret2);
	pushed += push(L, ret3);
	pushed += push(L, ret4);
	pushed += push(L, ret5);

	return pushed;
} // nativeStaticReturn5Param8

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline LUA_FUNC(nativeStaticReturn9Param5)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	RET_4 ret4;
	RET_5 ret5;
	ARG_1 arg1 = to<ARG_1>(L, -9);
	ARG_2 arg2 = to<ARG_2>(L, -8);
	ARG_3 arg3 = to<ARG_3>(L, -7);
	ARG_4 arg4 = to<ARG_4>(L, -6);
	ARG_5 arg5 = to<ARG_5>(L, -5);
	ARG_6 arg6 = to<ARG_6>(L, -4);
	ARG_7 arg7 = to<ARG_7>(L, -3);
	ARG_8 arg8 = to<ARG_8>(L, -2);
	ARG_9 arg9 = to<ARG_9>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
	pushed += push(L, ret1);
	pushed += push(L, ret2);
	pushed += push(L, ret3);
	pushed += push(L, ret4);
	pushed += push(L, ret5);

	return pushed;
} // nativeStaticReturn5Param9

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline LUA_FUNC(nativeStaticReturn10Param5)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	RET_4 ret4;
	RET_5 ret5;
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
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
	pushed += push(L, ret1);
	pushed += push(L, ret2);
	pushed += push(L, ret3);
	pushed += push(L, ret4);
	pushed += push(L, ret5);

	return pushed;
} // nativeStaticReturn5Param10

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1) >
inline LUA_FUNC(nativeStaticReturn1Param6)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	RET_4 ret4;
	RET_5 ret5;
	RET_6 ret6;
	ARG_1 arg1 = to<ARG_1>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, arg1);
	pushed += push(L, ret1);
	pushed += push(L, ret2);
	pushed += push(L, ret3);
	pushed += push(L, ret4);
	pushed += push(L, ret5);
	pushed += push(L, ret6);

	return pushed;
} // nativeStaticReturn6Param1

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2) >
inline LUA_FUNC(nativeStaticReturn2Param6)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	RET_4 ret4;
	RET_5 ret5;
	RET_6 ret6;
	ARG_1 arg1 = to<ARG_1>(L, -2);
	ARG_2 arg2 = to<ARG_2>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, arg1, arg2);
	pushed += push(L, ret1);
	pushed += push(L, ret2);
	pushed += push(L, ret3);
	pushed += push(L, ret4);
	pushed += push(L, ret5);
	pushed += push(L, ret6);

	return pushed;
} // nativeStaticReturn6Param2

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3) >
inline LUA_FUNC(nativeStaticReturn3Param6)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	RET_4 ret4;
	RET_5 ret5;
	RET_6 ret6;
	ARG_1 arg1 = to<ARG_1>(L, -3);
	ARG_2 arg2 = to<ARG_2>(L, -2);
	ARG_3 arg3 = to<ARG_3>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3);
	pushed += push(L, ret1);
	pushed += push(L, ret2);
	pushed += push(L, ret3);
	pushed += push(L, ret4);
	pushed += push(L, ret5);
	pushed += push(L, ret6);

	return pushed;
} // nativeStaticReturn6Param3

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline LUA_FUNC(nativeStaticReturn4Param6)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	RET_4 ret4;
	RET_5 ret5;
	RET_6 ret6;
	ARG_1 arg1 = to<ARG_1>(L, -4);
	ARG_2 arg2 = to<ARG_2>(L, -3);
	ARG_3 arg3 = to<ARG_3>(L, -2);
	ARG_4 arg4 = to<ARG_4>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4);
	pushed += push(L, ret1);
	pushed += push(L, ret2);
	pushed += push(L, ret3);
	pushed += push(L, ret4);
	pushed += push(L, ret5);
	pushed += push(L, ret6);

	return pushed;
} // nativeStaticReturn6Param4

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline LUA_FUNC(nativeStaticReturn5Param6)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	RET_4 ret4;
	RET_5 ret5;
	RET_6 ret6;
	ARG_1 arg1 = to<ARG_1>(L, -5);
	ARG_2 arg2 = to<ARG_2>(L, -4);
	ARG_3 arg3 = to<ARG_3>(L, -3);
	ARG_4 arg4 = to<ARG_4>(L, -2);
	ARG_5 arg5 = to<ARG_5>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4, arg5);
	pushed += push(L, ret1);
	pushed += push(L, ret2);
	pushed += push(L, ret3);
	pushed += push(L, ret4);
	pushed += push(L, ret5);
	pushed += push(L, ret6);

	return pushed;
} // nativeStaticReturn6Param5

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline LUA_FUNC(nativeStaticReturn6Param6)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	RET_4 ret4;
	RET_5 ret5;
	RET_6 ret6;
	ARG_1 arg1 = to<ARG_1>(L, -6);
	ARG_2 arg2 = to<ARG_2>(L, -5);
	ARG_3 arg3 = to<ARG_3>(L, -4);
	ARG_4 arg4 = to<ARG_4>(L, -3);
	ARG_5 arg5 = to<ARG_5>(L, -2);
	ARG_6 arg6 = to<ARG_6>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4, arg5, arg6);
	pushed += push(L, ret1);
	pushed += push(L, ret2);
	pushed += push(L, ret3);
	pushed += push(L, ret4);
	pushed += push(L, ret5);
	pushed += push(L, ret6);

	return pushed;
} // nativeStaticReturn6Param6

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline LUA_FUNC(nativeStaticReturn7Param6)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	RET_4 ret4;
	RET_5 ret5;
	RET_6 ret6;
	ARG_1 arg1 = to<ARG_1>(L, -7);
	ARG_2 arg2 = to<ARG_2>(L, -6);
	ARG_3 arg3 = to<ARG_3>(L, -5);
	ARG_4 arg4 = to<ARG_4>(L, -4);
	ARG_5 arg5 = to<ARG_5>(L, -3);
	ARG_6 arg6 = to<ARG_6>(L, -2);
	ARG_7 arg7 = to<ARG_7>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
	pushed += push(L, ret1);
	pushed += push(L, ret2);
	pushed += push(L, ret3);
	pushed += push(L, ret4);
	pushed += push(L, ret5);
	pushed += push(L, ret6);

	return pushed;
} // nativeStaticReturn6Param7

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline LUA_FUNC(nativeStaticReturn8Param6)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	RET_4 ret4;
	RET_5 ret5;
	RET_6 ret6;
	ARG_1 arg1 = to<ARG_1>(L, -8);
	ARG_2 arg2 = to<ARG_2>(L, -7);
	ARG_3 arg3 = to<ARG_3>(L, -6);
	ARG_4 arg4 = to<ARG_4>(L, -5);
	ARG_5 arg5 = to<ARG_5>(L, -4);
	ARG_6 arg6 = to<ARG_6>(L, -3);
	ARG_7 arg7 = to<ARG_7>(L, -2);
	ARG_8 arg8 = to<ARG_8>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
	pushed += push(L, ret1);
	pushed += push(L, ret2);
	pushed += push(L, ret3);
	pushed += push(L, ret4);
	pushed += push(L, ret5);
	pushed += push(L, ret6);

	return pushed;
} // nativeStaticReturn6Param8

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline LUA_FUNC(nativeStaticReturn9Param6)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	RET_4 ret4;
	RET_5 ret5;
	RET_6 ret6;
	ARG_1 arg1 = to<ARG_1>(L, -9);
	ARG_2 arg2 = to<ARG_2>(L, -8);
	ARG_3 arg3 = to<ARG_3>(L, -7);
	ARG_4 arg4 = to<ARG_4>(L, -6);
	ARG_5 arg5 = to<ARG_5>(L, -5);
	ARG_6 arg6 = to<ARG_6>(L, -4);
	ARG_7 arg7 = to<ARG_7>(L, -3);
	ARG_8 arg8 = to<ARG_8>(L, -2);
	ARG_9 arg9 = to<ARG_9>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
	pushed += push(L, ret1);
	pushed += push(L, ret2);
	pushed += push(L, ret3);
	pushed += push(L, ret4);
	pushed += push(L, ret5);
	pushed += push(L, ret6);

	return pushed;
} // nativeStaticReturn6Param9

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline LUA_FUNC(nativeStaticReturn10Param6)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	RET_4 ret4;
	RET_5 ret5;
	RET_6 ret6;
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
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
	pushed += push(L, ret1);
	pushed += push(L, ret2);
	pushed += push(L, ret3);
	pushed += push(L, ret4);
	pushed += push(L, ret5);
	pushed += push(L, ret6);

	return pushed;
} // nativeStaticReturn6Param10

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1) >
inline LUA_FUNC(nativeStaticReturn1Param7)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	RET_4 ret4;
	RET_5 ret5;
	RET_6 ret6;
	RET_7 ret7;
	ARG_1 arg1 = to<ARG_1>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, arg1);
	pushed += push(L, ret1);
	pushed += push(L, ret2);
	pushed += push(L, ret3);
	pushed += push(L, ret4);
	pushed += push(L, ret5);
	pushed += push(L, ret6);
	pushed += push(L, ret7);

	return pushed;
} // nativeStaticReturn7Param1

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2) >
inline LUA_FUNC(nativeStaticReturn2Param7)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	RET_4 ret4;
	RET_5 ret5;
	RET_6 ret6;
	RET_7 ret7;
	ARG_1 arg1 = to<ARG_1>(L, -2);
	ARG_2 arg2 = to<ARG_2>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2);
	pushed += push(L, ret1);
	pushed += push(L, ret2);
	pushed += push(L, ret3);
	pushed += push(L, ret4);
	pushed += push(L, ret5);
	pushed += push(L, ret6);
	pushed += push(L, ret7);

	return pushed;
} // nativeStaticReturn7Param2

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3) >
inline LUA_FUNC(nativeStaticReturn3Param7)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	RET_4 ret4;
	RET_5 ret5;
	RET_6 ret6;
	RET_7 ret7;
	ARG_1 arg1 = to<ARG_1>(L, -3);
	ARG_2 arg2 = to<ARG_2>(L, -2);
	ARG_3 arg3 = to<ARG_3>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3);
	pushed += push(L, ret1);
	pushed += push(L, ret2);
	pushed += push(L, ret3);
	pushed += push(L, ret4);
	pushed += push(L, ret5);
	pushed += push(L, ret6);
	pushed += push(L, ret7);

	return pushed;
} // nativeStaticReturn7Param3

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline LUA_FUNC(nativeStaticReturn4Param7)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	RET_4 ret4;
	RET_5 ret5;
	RET_6 ret6;
	RET_7 ret7;
	ARG_1 arg1 = to<ARG_1>(L, -4);
	ARG_2 arg2 = to<ARG_2>(L, -3);
	ARG_3 arg3 = to<ARG_3>(L, -2);
	ARG_4 arg4 = to<ARG_4>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4);
	pushed += push(L, ret1);
	pushed += push(L, ret2);
	pushed += push(L, ret3);
	pushed += push(L, ret4);
	pushed += push(L, ret5);
	pushed += push(L, ret6);
	pushed += push(L, ret7);

	return pushed;
} // nativeStaticReturn7Param4

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline LUA_FUNC(nativeStaticReturn5Param7)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	RET_4 ret4;
	RET_5 ret5;
	RET_6 ret6;
	RET_7 ret7;
	ARG_1 arg1 = to<ARG_1>(L, -5);
	ARG_2 arg2 = to<ARG_2>(L, -4);
	ARG_3 arg3 = to<ARG_3>(L, -3);
	ARG_4 arg4 = to<ARG_4>(L, -2);
	ARG_5 arg5 = to<ARG_5>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4, arg5);
	pushed += push(L, ret1);
	pushed += push(L, ret2);
	pushed += push(L, ret3);
	pushed += push(L, ret4);
	pushed += push(L, ret5);
	pushed += push(L, ret6);
	pushed += push(L, ret7);

	return pushed;
} // nativeStaticReturn7Param5

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline LUA_FUNC(nativeStaticReturn6Param7)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	RET_4 ret4;
	RET_5 ret5;
	RET_6 ret6;
	RET_7 ret7;
	ARG_1 arg1 = to<ARG_1>(L, -6);
	ARG_2 arg2 = to<ARG_2>(L, -5);
	ARG_3 arg3 = to<ARG_3>(L, -4);
	ARG_4 arg4 = to<ARG_4>(L, -3);
	ARG_5 arg5 = to<ARG_5>(L, -2);
	ARG_6 arg6 = to<ARG_6>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4, arg5, arg6);
	pushed += push(L, ret1);
	pushed += push(L, ret2);
	pushed += push(L, ret3);
	pushed += push(L, ret4);
	pushed += push(L, ret5);
	pushed += push(L, ret6);
	pushed += push(L, ret7);

	return pushed;
} // nativeStaticReturn7Param6

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline LUA_FUNC(nativeStaticReturn7Param7)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	RET_4 ret4;
	RET_5 ret5;
	RET_6 ret6;
	RET_7 ret7;
	ARG_1 arg1 = to<ARG_1>(L, -7);
	ARG_2 arg2 = to<ARG_2>(L, -6);
	ARG_3 arg3 = to<ARG_3>(L, -5);
	ARG_4 arg4 = to<ARG_4>(L, -4);
	ARG_5 arg5 = to<ARG_5>(L, -3);
	ARG_6 arg6 = to<ARG_6>(L, -2);
	ARG_7 arg7 = to<ARG_7>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
	pushed += push(L, ret1);
	pushed += push(L, ret2);
	pushed += push(L, ret3);
	pushed += push(L, ret4);
	pushed += push(L, ret5);
	pushed += push(L, ret6);
	pushed += push(L, ret7);

	return pushed;
} // nativeStaticReturn7Param7

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline LUA_FUNC(nativeStaticReturn8Param7)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	RET_4 ret4;
	RET_5 ret5;
	RET_6 ret6;
	RET_7 ret7;
	ARG_1 arg1 = to<ARG_1>(L, -8);
	ARG_2 arg2 = to<ARG_2>(L, -7);
	ARG_3 arg3 = to<ARG_3>(L, -6);
	ARG_4 arg4 = to<ARG_4>(L, -5);
	ARG_5 arg5 = to<ARG_5>(L, -4);
	ARG_6 arg6 = to<ARG_6>(L, -3);
	ARG_7 arg7 = to<ARG_7>(L, -2);
	ARG_8 arg8 = to<ARG_8>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
	pushed += push(L, ret1);
	pushed += push(L, ret2);
	pushed += push(L, ret3);
	pushed += push(L, ret4);
	pushed += push(L, ret5);
	pushed += push(L, ret6);
	pushed += push(L, ret7);

	return pushed;
} // nativeStaticReturn7Param8

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline LUA_FUNC(nativeStaticReturn9Param7)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	RET_4 ret4;
	RET_5 ret5;
	RET_6 ret6;
	RET_7 ret7;
	ARG_1 arg1 = to<ARG_1>(L, -9);
	ARG_2 arg2 = to<ARG_2>(L, -8);
	ARG_3 arg3 = to<ARG_3>(L, -7);
	ARG_4 arg4 = to<ARG_4>(L, -6);
	ARG_5 arg5 = to<ARG_5>(L, -5);
	ARG_6 arg6 = to<ARG_6>(L, -4);
	ARG_7 arg7 = to<ARG_7>(L, -3);
	ARG_8 arg8 = to<ARG_8>(L, -2);
	ARG_9 arg9 = to<ARG_9>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
	pushed += push(L, ret1);
	pushed += push(L, ret2);
	pushed += push(L, ret3);
	pushed += push(L, ret4);
	pushed += push(L, ret5);
	pushed += push(L, ret6);
	pushed += push(L, ret7);

	return pushed;
} // nativeStaticReturn7Param9

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline LUA_FUNC(nativeStaticReturn10Param7)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	RET_4 ret4;
	RET_5 ret5;
	RET_6 ret6;
	RET_7 ret7;
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
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
	pushed += push(L, ret1);
	pushed += push(L, ret2);
	pushed += push(L, ret3);
	pushed += push(L, ret4);
	pushed += push(L, ret5);
	pushed += push(L, ret6);
	pushed += push(L, ret7);

	return pushed;
} // nativeStaticReturn7Param10

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1) >
inline LUA_FUNC(nativeStaticReturn1Param8)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	RET_4 ret4;
	RET_5 ret5;
	RET_6 ret6;
	RET_7 ret7;
	RET_8 ret8;
	ARG_1 arg1 = to<ARG_1>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1);
	pushed += push(L, ret1);
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
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2) >
inline LUA_FUNC(nativeStaticReturn2Param8)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	RET_4 ret4;
	RET_5 ret5;
	RET_6 ret6;
	RET_7 ret7;
	RET_8 ret8;
	ARG_1 arg1 = to<ARG_1>(L, -2);
	ARG_2 arg2 = to<ARG_2>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2);
	pushed += push(L, ret1);
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
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3) >
inline LUA_FUNC(nativeStaticReturn3Param8)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	RET_4 ret4;
	RET_5 ret5;
	RET_6 ret6;
	RET_7 ret7;
	RET_8 ret8;
	ARG_1 arg1 = to<ARG_1>(L, -3);
	ARG_2 arg2 = to<ARG_2>(L, -2);
	ARG_3 arg3 = to<ARG_3>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3);
	pushed += push(L, ret1);
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
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline LUA_FUNC(nativeStaticReturn4Param8)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	RET_4 ret4;
	RET_5 ret5;
	RET_6 ret6;
	RET_7 ret7;
	RET_8 ret8;
	ARG_1 arg1 = to<ARG_1>(L, -4);
	ARG_2 arg2 = to<ARG_2>(L, -3);
	ARG_3 arg3 = to<ARG_3>(L, -2);
	ARG_4 arg4 = to<ARG_4>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4);
	pushed += push(L, ret1);
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
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline LUA_FUNC(nativeStaticReturn5Param8)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	RET_4 ret4;
	RET_5 ret5;
	RET_6 ret6;
	RET_7 ret7;
	RET_8 ret8;
	ARG_1 arg1 = to<ARG_1>(L, -5);
	ARG_2 arg2 = to<ARG_2>(L, -4);
	ARG_3 arg3 = to<ARG_3>(L, -3);
	ARG_4 arg4 = to<ARG_4>(L, -2);
	ARG_5 arg5 = to<ARG_5>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4, arg5);
	pushed += push(L, ret1);
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
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline LUA_FUNC(nativeStaticReturn6Param8)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	RET_4 ret4;
	RET_5 ret5;
	RET_6 ret6;
	RET_7 ret7;
	RET_8 ret8;
	ARG_1 arg1 = to<ARG_1>(L, -6);
	ARG_2 arg2 = to<ARG_2>(L, -5);
	ARG_3 arg3 = to<ARG_3>(L, -4);
	ARG_4 arg4 = to<ARG_4>(L, -3);
	ARG_5 arg5 = to<ARG_5>(L, -2);
	ARG_6 arg6 = to<ARG_6>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4, arg5, arg6);
	pushed += push(L, ret1);
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
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline LUA_FUNC(nativeStaticReturn7Param8)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	RET_4 ret4;
	RET_5 ret5;
	RET_6 ret6;
	RET_7 ret7;
	RET_8 ret8;
	ARG_1 arg1 = to<ARG_1>(L, -7);
	ARG_2 arg2 = to<ARG_2>(L, -6);
	ARG_3 arg3 = to<ARG_3>(L, -5);
	ARG_4 arg4 = to<ARG_4>(L, -4);
	ARG_5 arg5 = to<ARG_5>(L, -3);
	ARG_6 arg6 = to<ARG_6>(L, -2);
	ARG_7 arg7 = to<ARG_7>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
	pushed += push(L, ret1);
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
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline LUA_FUNC(nativeStaticReturn8Param8)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	RET_4 ret4;
	RET_5 ret5;
	RET_6 ret6;
	RET_7 ret7;
	RET_8 ret8;
	ARG_1 arg1 = to<ARG_1>(L, -8);
	ARG_2 arg2 = to<ARG_2>(L, -7);
	ARG_3 arg3 = to<ARG_3>(L, -6);
	ARG_4 arg4 = to<ARG_4>(L, -5);
	ARG_5 arg5 = to<ARG_5>(L, -4);
	ARG_6 arg6 = to<ARG_6>(L, -3);
	ARG_7 arg7 = to<ARG_7>(L, -2);
	ARG_8 arg8 = to<ARG_8>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
	pushed += push(L, ret1);
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
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline LUA_FUNC(nativeStaticReturn9Param8)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	RET_4 ret4;
	RET_5 ret5;
	RET_6 ret6;
	RET_7 ret7;
	RET_8 ret8;
	ARG_1 arg1 = to<ARG_1>(L, -9);
	ARG_2 arg2 = to<ARG_2>(L, -8);
	ARG_3 arg3 = to<ARG_3>(L, -7);
	ARG_4 arg4 = to<ARG_4>(L, -6);
	ARG_5 arg5 = to<ARG_5>(L, -5);
	ARG_6 arg6 = to<ARG_6>(L, -4);
	ARG_7 arg7 = to<ARG_7>(L, -3);
	ARG_8 arg8 = to<ARG_8>(L, -2);
	ARG_9 arg9 = to<ARG_9>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
	pushed += push(L, ret1);
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
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline LUA_FUNC(nativeStaticReturn10Param8)
{
	sint pushed(0);
	RET_2 ret2;
	RET_3 ret3;
	RET_4 ret4;
	RET_5 ret5;
	RET_6 ret6;
	RET_7 ret7;
	RET_8 ret8;
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
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
	pushed += push(L, ret1);
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
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1) >
inline LUA_FUNC(nativeStaticReturn1Param9)
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
	ARG_1 arg1 = to<ARG_1>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1);
	pushed += push(L, ret1);
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
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2) >
inline LUA_FUNC(nativeStaticReturn2Param9)
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
	ARG_1 arg1 = to<ARG_1>(L, -2);
	ARG_2 arg2 = to<ARG_2>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2);
	pushed += push(L, ret1);
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
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3) >
inline LUA_FUNC(nativeStaticReturn3Param9)
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
	ARG_1 arg1 = to<ARG_1>(L, -3);
	ARG_2 arg2 = to<ARG_2>(L, -2);
	ARG_3 arg3 = to<ARG_3>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3);
	pushed += push(L, ret1);
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
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline LUA_FUNC(nativeStaticReturn4Param9)
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
	ARG_1 arg1 = to<ARG_1>(L, -4);
	ARG_2 arg2 = to<ARG_2>(L, -3);
	ARG_3 arg3 = to<ARG_3>(L, -2);
	ARG_4 arg4 = to<ARG_4>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4);
	pushed += push(L, ret1);
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
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline LUA_FUNC(nativeStaticReturn5Param9)
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
	ARG_1 arg1 = to<ARG_1>(L, -5);
	ARG_2 arg2 = to<ARG_2>(L, -4);
	ARG_3 arg3 = to<ARG_3>(L, -3);
	ARG_4 arg4 = to<ARG_4>(L, -2);
	ARG_5 arg5 = to<ARG_5>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4, arg5);
	pushed += push(L, ret1);
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
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline LUA_FUNC(nativeStaticReturn6Param9)
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
	ARG_1 arg1 = to<ARG_1>(L, -6);
	ARG_2 arg2 = to<ARG_2>(L, -5);
	ARG_3 arg3 = to<ARG_3>(L, -4);
	ARG_4 arg4 = to<ARG_4>(L, -3);
	ARG_5 arg5 = to<ARG_5>(L, -2);
	ARG_6 arg6 = to<ARG_6>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4, arg5, arg6);
	pushed += push(L, ret1);
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
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline LUA_FUNC(nativeStaticReturn7Param9)
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
	ARG_1 arg1 = to<ARG_1>(L, -7);
	ARG_2 arg2 = to<ARG_2>(L, -6);
	ARG_3 arg3 = to<ARG_3>(L, -5);
	ARG_4 arg4 = to<ARG_4>(L, -4);
	ARG_5 arg5 = to<ARG_5>(L, -3);
	ARG_6 arg6 = to<ARG_6>(L, -2);
	ARG_7 arg7 = to<ARG_7>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
	pushed += push(L, ret1);
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
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline LUA_FUNC(nativeStaticReturn8Param9)
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
	ARG_1 arg1 = to<ARG_1>(L, -8);
	ARG_2 arg2 = to<ARG_2>(L, -7);
	ARG_3 arg3 = to<ARG_3>(L, -6);
	ARG_4 arg4 = to<ARG_4>(L, -5);
	ARG_5 arg5 = to<ARG_5>(L, -4);
	ARG_6 arg6 = to<ARG_6>(L, -3);
	ARG_7 arg7 = to<ARG_7>(L, -2);
	ARG_8 arg8 = to<ARG_8>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
	pushed += push(L, ret1);
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
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline LUA_FUNC(nativeStaticReturn9Param9)
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
	ARG_1 arg1 = to<ARG_1>(L, -9);
	ARG_2 arg2 = to<ARG_2>(L, -8);
	ARG_3 arg3 = to<ARG_3>(L, -7);
	ARG_4 arg4 = to<ARG_4>(L, -6);
	ARG_5 arg5 = to<ARG_5>(L, -5);
	ARG_6 arg6 = to<ARG_6>(L, -4);
	ARG_7 arg7 = to<ARG_7>(L, -3);
	ARG_8 arg8 = to<ARG_8>(L, -2);
	ARG_9 arg9 = to<ARG_9>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
	pushed += push(L, ret1);
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
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) >
inline LUA_FUNC(nativeStaticReturn10Param9)
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
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
	pushed += push(L, ret1);
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
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1) >
inline LUA_FUNC(nativeStaticReturn1Param10)
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
	ARG_1 arg1 = to<ARG_1>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1);
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
} // nativeStaticReturn10Param1

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2) >
inline LUA_FUNC(nativeStaticReturn2Param10)
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
	ARG_1 arg1 = to<ARG_1>(L, -2);
	ARG_2 arg2 = to<ARG_2>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2);
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
} // nativeStaticReturn10Param2

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3) >
inline LUA_FUNC(nativeStaticReturn3Param10)
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
	ARG_1 arg1 = to<ARG_1>(L, -3);
	ARG_2 arg2 = to<ARG_2>(L, -2);
	ARG_3 arg3 = to<ARG_3>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3);
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
} // nativeStaticReturn10Param3

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4) >
inline LUA_FUNC(nativeStaticReturn4Param10)
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
	ARG_1 arg1 = to<ARG_1>(L, -4);
	ARG_2 arg2 = to<ARG_2>(L, -3);
	ARG_3 arg3 = to<ARG_3>(L, -2);
	ARG_4 arg4 = to<ARG_4>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4);
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
} // nativeStaticReturn10Param4

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) >
inline LUA_FUNC(nativeStaticReturn5Param10)
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
	ARG_1 arg1 = to<ARG_1>(L, -5);
	ARG_2 arg2 = to<ARG_2>(L, -4);
	ARG_3 arg3 = to<ARG_3>(L, -3);
	ARG_4 arg4 = to<ARG_4>(L, -2);
	ARG_5 arg5 = to<ARG_5>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4, arg5);
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
} // nativeStaticReturn10Param5

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) >
inline LUA_FUNC(nativeStaticReturn6Param10)
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
	ARG_1 arg1 = to<ARG_1>(L, -6);
	ARG_2 arg2 = to<ARG_2>(L, -5);
	ARG_3 arg3 = to<ARG_3>(L, -4);
	ARG_4 arg4 = to<ARG_4>(L, -3);
	ARG_5 arg5 = to<ARG_5>(L, -2);
	ARG_6 arg6 = to<ARG_6>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4, arg5, arg6);
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
} // nativeStaticReturn10Param6

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) >
inline LUA_FUNC(nativeStaticReturn7Param10)
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
	ARG_1 arg1 = to<ARG_1>(L, -7);
	ARG_2 arg2 = to<ARG_2>(L, -6);
	ARG_3 arg3 = to<ARG_3>(L, -5);
	ARG_4 arg4 = to<ARG_4>(L, -4);
	ARG_5 arg5 = to<ARG_5>(L, -3);
	ARG_6 arg6 = to<ARG_6>(L, -2);
	ARG_7 arg7 = to<ARG_7>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
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
} // nativeStaticReturn10Param7

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) >
inline LUA_FUNC(nativeStaticReturn8Param10)
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
	ARG_1 arg1 = to<ARG_1>(L, -8);
	ARG_2 arg2 = to<ARG_2>(L, -7);
	ARG_3 arg3 = to<ARG_3>(L, -6);
	ARG_4 arg4 = to<ARG_4>(L, -5);
	ARG_5 arg5 = to<ARG_5>(L, -4);
	ARG_6 arg6 = to<ARG_6>(L, -3);
	ARG_7 arg7 = to<ARG_7>(L, -2);
	ARG_8 arg8 = to<ARG_8>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
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
} // nativeStaticReturn10Param8

//test generateStaticTemplate
template< typename RET_1, typename RET_2, typename RET_3, typename RET_4, typename RET_5, typename RET_6, typename RET_7, typename RET_8, typename RET_9, typename RET_10, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, void (* function)(RET_2&, RET_3&, RET_4&, RET_5&, RET_6&, RET_7&, RET_8&, RET_9&, RET_10&, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) >
inline LUA_FUNC(nativeStaticReturn9Param10)
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
	ARG_1 arg1 = to<ARG_1>(L, -9);
	ARG_2 arg2 = to<ARG_2>(L, -8);
	ARG_3 arg3 = to<ARG_3>(L, -7);
	ARG_4 arg4 = to<ARG_4>(L, -6);
	ARG_5 arg5 = to<ARG_5>(L, -5);
	ARG_6 arg6 = to<ARG_6>(L, -4);
	ARG_7 arg7 = to<ARG_7>(L, -3);
	ARG_8 arg8 = to<ARG_8>(L, -2);
	ARG_9 arg9 = to<ARG_9>(L, -1);
	RET_1 ret1 = (*function)(ret2, ret3, ret4, ret5, ret6, ret7, ret8, ret9, ret10, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
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
} // nativeStaticReturn10Param9

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
