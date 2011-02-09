#include "Build.h"
#if BUILD_WITH_UNIT_TESTING
#include <cfixcc.h>
#include <string.h>

#if EXTENDED_BY_LUA
#include "Lua.h"
#include "LuaInclusions.h"
#include "LuaExtensibility.h"
#include "LuaStateInteraction.h"

using namespace LuaExtension;

static sint getOne(void)
{
	return 1;
}

static sint getTwo(sint& two)
{
	two = 2;
	return 1;
}

static float incrementByOne(float number)
{
	return number + 1.0f;
}

static float addAndSubtract(float& subtracted, float operand)
{
	subtracted = operand - 1.0f;
	return operand + 1.0f;
}

declare_lua_library(UnitTestLibrary)

define_lua_library(UnitTestLibrary)
	lua_named_entry("getOne",			(staticReturn1Param0<sint, getOne>))
	lua_named_entry("getTwo",			(staticReturn2Param0<sint, sint, getTwo>))
	lua_named_entry("incrementByOne",	(staticReturn1Param1<float, float, incrementByOne>))
	lua_named_entry("addAndSubtract",	(staticReturn2Param1<float, float, float, addAndSubtract>))
end_lua_library(UnitTestLibrary)

class LibraryExtensionUT : public cfixcc::TestFixture
{
public:
	void test_staticParam0()
	{
		Lua lua;
		lua_State* L = lua.getState();
		//s: 
		register_lua_library((&lua), UnitTestLibrary);
		//s: 
		lua_getglobal(L, "UnitTestLibrary");
		//s: UnitTestLibrary
		CFIX_ASSERT(lua_istable(L, -1));
		lua_getfield(L, -1, "getOne");
		//s: getOne
		CFIX_ASSERT(lua_isfunction(L, -1));
		lua_call(L, 0, 1);
		//s: 1
		CFIX_ASSERT(lua_isnumber(L, -1));
		sint one = to<sint>(L, -1);
		CFIX_ASSERT(one == 1);
		lua_Number one_l = lua_tonumber(L, -1);
		CFIX_ASSERT(one_l == 1);
		lua_pop(L, 1);
		//s: 
	}

	void test_staticParam1()
	{
		Lua lua;
		lua_State* L = lua.getState();
		//s: 
		register_lua_library((&lua), UnitTestLibrary);
		//s: 
		lua_getglobal(L, "UnitTestLibrary");
		//s: UnitTestLibrary
		CFIX_ASSERT(lua_istable(L, -1));
		lua_getfield(L, -1, "incrementByOne");
		//s: incrementByOne
		CFIX_ASSERT(lua_isfunction(L, -1));
		push(L, 1.5f);
		//s: incrementByOne, 1.0f
		lua_call(L, 1, 1);
		//s: 1.5f
		CFIX_ASSERT(lua_isnumber(L, -1));
		float two_point_five = to<float>(L, -1);
		CFIX_ASSERT(two_point_five == 2.5f);
		lua_pop(L, 1);
		//s: 
	}

	void test_staticReturn2Param0()
	{
		Lua lua;
		lua_State* L = lua.getState();
		//s: 
		register_lua_library((&lua), UnitTestLibrary);
		//s: 
		lua_getglobal(L, "UnitTestLibrary");
		//s: UnitTestLibrary
		CFIX_ASSERT(lua_istable(L, -1));
		lua_getfield(L, -1, "getTwo");
		//s: getTwo
		CFIX_ASSERT(lua_isfunction(L, -1));
		lua_call(L, 0, 2);
		//s: 1, 2
		CFIX_ASSERT(lua_isnumber(L, -1));
		CFIX_ASSERT(lua_isnumber(L, -2));
		sint one = to<sint>(L, -2);
		CFIX_ASSERT(one == 1);
		sint two = to<sint>(L, -1);
		CFIX_ASSERT(two == 2);
		lua_pop(L, 2);
		//s: 
	}

	void test_staticReturn2Param1()
	{
		Lua lua;
		lua_State* L = lua.getState();
		//s: 
		register_lua_library((&lua), UnitTestLibrary);
		//s: 
		lua_getglobal(L, "UnitTestLibrary");
		//s: UnitTestLibrary
		CFIX_ASSERT(lua_istable(L, -1));
		lua_getfield(L, -1, "addAndSubtract");
		//s: addAndSubtract
		CFIX_ASSERT(lua_isfunction(L, -1));
		lua_pushnumber(L, 3.0f);
		lua_call(L, 1, 2);
		//s: 4, 2
		CFIX_ASSERT(lua_isnumber(L, -1));
		CFIX_ASSERT(lua_isnumber(L, -2));
		sint four = to<sint>(L, -2);
		CFIX_ASSERT(four == 4);
		sint two = to<sint>(L, -1);
		CFIX_ASSERT(two == 2);
		lua_pop(L, 2);
		//s: 
	}
};

CFIXCC_BEGIN_CLASS(LibraryExtensionUT)
	CFIXCC_METHOD(test_staticParam0)
	CFIXCC_METHOD(test_staticParam1)
	CFIXCC_METHOD(test_staticReturn2Param0)
	CFIXCC_METHOD(test_staticReturn2Param1)
CFIXCC_END_CLASS()
#endif//EXTENDED_BY_LUA
#endif//BUILD_WITH_UNIT_TESTING