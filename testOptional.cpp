
/** nativeMemberReturn0Param4 */
template< typename CLASS, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, void (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4) >
inline LUA_FUNC(nativeMemberReturn0Param4)
{
	if (CLASS* object = to<CLASS*>(L, -5))
	{
		(object->*function)(to<ARG_1>(L, -4),
			to<ARG_2>(L, -3),
			to<ARG_3>(L, -2),
			to<ARG_4>(L, -1));
	}
	return 0;
} // nativeMemberReturn0Param4


/** nativeMemberReturn0Param4 */
template< typename CLASS, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, void (CLASS::* function)(ARG_1, ARG_2, ARG_3, ARG_4) >
inline LUA_FUNC(nativeMemberReturn0Param4Optional3)
{
	switch (lua_gettop(L))
	{
	case 5:
	{	
		if (CLASS* object = to<CLASS*>(L, -5))
		{		
			(object->*function)(to<ARG_1>(L, -4),
				to<ARG_2>(L, -3),
				to<ARG_3>(L, -2),
				to<ARG_4>(L, -1));
		}
	}
	case 4:
	{	
		if (CLASS* object = to<CLASS*>(L, -4))
		{		
			(object->*function)(to<ARG_1>(L, -3),
				to<ARG_2>(L, -2),
				to<ARG_3>(L, -1));
		}
	}
	case 3:
	{	
		if (CLASS* object = to<CLASS*>(L, -3))
		{		
			(object->*function)(to<ARG_1>(L, -2),
				to<ARG_2>(L, -1));
		}
	}
	case 2:
	{	
		if (CLASS* object = to<CLASS*>(L, -2))
		{		
			(object->*function)(to<ARG_1>(L, -1));
		}
	}	
	}; // switch (lua_gettop(L))
	
	return 0;
} // nativeMemberReturn0Param4
