#include "Build.h"
#if WITH_UNIT_TESTING
#include <cfixcc.h>
#include <string.h>

#if EXTENDED_BY_LUA
#include "LuaExtensionInclusions.h"
using namespace lua_extension;

static sint4 getOne(void)
{
	return 1;
}

static sint4 getTwo(sint4& two)
{
	two = 2;
	return 1;
}

static real4 incrementByOne(real4 number)
{
	return number + 1.0f;
}

static real4 addAndSubtract(real4& subtracted, real4 operand)
{
	subtracted = operand - 1.0f;
	return operand + 1.0f;
}

DECLARE_LUA_LIBRARY(UnitTestLibrary)

DEFINE_LUA_LIBRARY(UnitTestLibrary)
	LUA_NAMED_ENTRY("getOne",			(staticReturn1Param0<sint4, getOne>))
	LUA_NAMED_ENTRY("getTwo",			(staticReturn2Param0<sint4, sint4, getTwo>))
	LUA_NAMED_ENTRY("incrementByOne",	(staticReturn1Param1<real4, real4, incrementByOne>))
	LUA_NAMED_ENTRY("addAndSubtract",	(staticReturn2Param1<real4, real4, real4, addAndSubtract>))
END_LUA_LIBRARY(UnitTestLibrary)

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
		sint4 one = to<sint4>(L, -1);
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
		real4 two_point_five = to<real4>(L, -1);
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
		sint4 one = to<sint4>(L, -2);
		CFIX_ASSERT(one == 1);
		sint4 two = to<sint4>(L, -1);
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
		sint4 four = to<sint4>(L, -2);
		CFIX_ASSERT(four == 4);
		sint4 two = to<sint4>(L, -1);
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
#endif//WITH_UNIT_TESTING