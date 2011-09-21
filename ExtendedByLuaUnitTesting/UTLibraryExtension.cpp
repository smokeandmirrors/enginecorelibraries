#include "Build.h"

#if WITH_UNIT_TESTING
#include <cfixcc.h>
#include <string.h>
#include "UTTools.h"

#if EXTENDED_BY_LUA
#include "LuaExtensionInclusions.h"
using namespace lua_extension;

static sint getOne(void)
{
	return 1;
}

static sint getTwo(sint& two)
{
	two = 2;
	return 1;
}

static sreal incrementByOne(sreal number)
{
	return number + 1.0f;
}

static sreal addAndSubtract(sreal& subtracted, sreal operand)
{
	subtracted = operand - 1.0f;
	return operand + 1.0f;
}

DECLARE_LUA_LIBRARY(UnitTestLibrary)

DEFINE_LUA_LIBRARY(UnitTestLibrary)
	LUA_ENTRY_NAMED("getOne",			(nativeStaticReturn1Param0<sint, getOne>))
	LUA_ENTRY_NAMED("getTwo",			(nativeStaticReturn2Param0<sint, sint, getTwo>))
	LUA_ENTRY_NAMED("incrementByOne",	(nativeStaticReturn1Param1<sreal, sreal, incrementByOne>))
	LUA_ENTRY_NAMED("addAndSubtract",	(nativeStaticReturn2Param1<sreal, sreal, sreal, addAndSubtract>))
END_LUA_LIBRARY(UnitTestLibrary)

class LibraryExtensionUT : public cfixcc::TestFixture
{
public:
	void test_staticParam0()
	{
		DECLARE_UNIT_TESTING_LUA_OBJECT
		lua_State* L = lua.getState();
		//s: 
		REGISTER_LUA_LIBRARY((&lua), UnitTestLibrary);
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
		DECLARE_UNIT_TESTING_LUA_OBJECT
		lua_State* L = lua.getState();
		//s: 
		REGISTER_LUA_LIBRARY((&lua), UnitTestLibrary);
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
		sreal two_point_five = to<sreal>(L, -1);
		CFIX_ASSERT(two_point_five == 2.5f);
		lua_pop(L, 1);
		//s: 
	}

	void test_nativeStaticReturn2Param0()
	{
		DECLARE_UNIT_TESTING_LUA_OBJECT
		lua_State* L = lua.getState();
		//s: 
		REGISTER_LUA_LIBRARY((&lua), UnitTestLibrary);
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

	void test_nativeStaticReturn2Param1()
	{
		DECLARE_UNIT_TESTING_LUA_OBJECT
		lua_State* L = lua.getState();
		//s: 
		REGISTER_LUA_LIBRARY((&lua), UnitTestLibrary);
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
	CFIXCC_METHOD(test_nativeStaticReturn2Param0)
	CFIXCC_METHOD(test_nativeStaticReturn2Param1)
CFIXCC_END_CLASS()
#endif//EXTENDED_BY_LUA
#endif//WITH_UNIT_TESTING