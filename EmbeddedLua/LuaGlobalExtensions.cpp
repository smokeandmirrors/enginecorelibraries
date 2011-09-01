#include "LuaExtensionInclusions.h"

#include "Vector.h"

namespace lua_extension
{
	sint f_staticReturn1Param0_1(sint opt1 = 1)
	{
		return opt1;
	}

	sint f_staticReturn1Param0_2(sint opt1 = 1, sint opt2 = 2)
	{
		return opt1 + opt2;
	}

	sint f_staticReturn1Param0_3(sint opt1 = 1, sint opt2 = 2, sint opt3 = 3)
	{
		return opt1 + opt2 + opt3;
	}

	LUA_FUNC(lf0o1)
	{
		sint num_args = lua_gettop(L);
		switch (num_args)
		{
		case 1:
			{
				sint pushed(0);
				sint arg1 = to<sint>(L, -1); 
				sint ret1 = f_staticReturn1Param0_1(arg1);
				pushed = push(L, ret1);
				return pushed;
			}
		case 0:
			{
				sint pushed(0);
				sint ret1 = f_staticReturn1Param0_1();
				pushed = push(L, ret1);
				return pushed;
			}
		default:
			{
				return luaL_error(L, "num args error! 0 to 1 required, %d found", num_args);
				break;
			}
		} // switch	
	}

	LUA_FUNC(lf0o2)
	{
		sint num_args = lua_gettop(L);
		switch (num_args)
		{
		case 2:
			{
				sint pushed(0);
				sint arg1 = to<sint>(L, -2); sint arg2 = to<sint>(L, -1);
				sint ret1 = f_staticReturn1Param0_2(arg1, arg2);
				pushed = push(L, ret1);
				return pushed;
			}
		case 1:
			{
				sint pushed(0);
				sint arg1 = to<sint>(L, -1); 
				sint ret1 = f_staticReturn1Param0_2(arg1);
				pushed = push(L, ret1);
				return pushed;
			}
		case 0:
			{
				sint pushed(0);
				sint ret1 = f_staticReturn1Param0_2();
				pushed = push(L, ret1);
				return pushed;
			}
		default:
			{
				return luaL_error(L, "num args error! 0 to 2 required, %d found", num_args);
				break;
			}
		} // switch	
	}

	LUA_FUNC(lf0o3)
	{
		sint num_args = lua_gettop(L);
		switch (num_args)
		{
		case 3:
			{
				sint pushed(0);
				sint arg1 = to<sint>(L, -3); sint arg2 = to<sint>(L, -2); sint arg3 = to<sint>(L, -3);
				sint ret1 = f_staticReturn1Param0_3(arg1, arg2, arg3);
				pushed = push(L, ret1);
				return pushed;
			}
		case 2:
			{
				sint pushed(0);
				sint arg1 = to<sint>(L, -2); sint arg2 = to<sint>(L, -1);
				sint ret1 = f_staticReturn1Param0_3(arg1, arg2);
				pushed = push(L, ret1);
				return pushed;
			}
		case 1:
			{
				sint pushed(0);
				sint arg1 = to<sint>(L, -1); 
				sint ret1 = f_staticReturn1Param0_3(arg1);
				pushed = push(L, ret1);
				return pushed;
			}
		case 0:
			{
				sint pushed(0);
				sint ret1 = f_staticReturn1Param0_3();
				pushed = push(L, ret1);
				return pushed;
			}
		default:
			{
				return luaL_error(L, "num args error! 0 to 3 required, %d found", num_args);
				break;
			}
		} // switch	
	}


/**
\brief
add native functions that you wish to be in the global %Lua namespace here
(in alphabetical order please)
*/
static const luaL_reg lua_library_Global[] = {
	LUA_ENTRY(lf0o1)
	LUA_ENTRY(lf0o2)
	LUA_ENTRY(lf0o3)
	LUA_NAMED_ENTRY("nativeVectorPerformance", (staticReturn0Param1<uint, &math::nativeVectorPerformance>))
	LUA_FINAL_ENTRY
};

void registerGlobalLibrary(lua_State* L)
{
	luaL_register(L, NULL, lua_library_Global);
}

} // namespace lua_extension
