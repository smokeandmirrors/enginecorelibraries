#include <cfixcc.h>
#include <string.h>

#if EXTENDED_BY_LUA
#include "Lua.h"
#include "LuaInclusions.h"
#include "LuaLibraryDeclarations.h"
#include "LuaExtensibility.h"
#include "LuaStateInteraction.h"

using namespace LuaExtension;

/** 
\todo unit test __gc and garbage collection
*/

class One
{
public:
	typedef One super;
	sint getValue(void) const		{ return 1; }
	sint increment(sint i) const	{ return i + getValue(); }
}; // Basic

declare_lua_library(One)

lua_func(newOne)
{
	pushRegisteredClass(L, new One());		//s: ud
	lua_newtable(L);						//s: ud, ud_mt
	lua_getglobal(L, "One");				//s: ud, ud_mt, Basic
	lua_setfield(L, -2, "__index");			//s: ud, ud_mt
	lua_setmetatable(L, -2);				//s: ud/mt
	return 1;
}

lua_func(getOne)
{
	static One* singleOne(NULL);

	if (!singleOne)
	{
		singleOne = new One();
		pushRegisteredClass(L,singleOne);		//s: ud
		lua_newtable(L);						//s: ud, ud_mt
		lua_getglobal(L, "One");				//s: ud, ud_mt, Basic
		lua_setfield(L, -2, "__index");			//s: ud, ud_mt
		lua_setmetatable(L, -2);				//s: ud/mt
	}
	else
	{
		pushRegisteredClass(L,singleOne);		//s: ud
	}

	return 1;
}

lua_func(getValueOne)
{
	One* one = static_cast<One*>(lua_touserdata(L, -1));	//s: ud
	return push(L, one->getValue());						//s: ud, value
}

lua_func(incrementOne)
{
	sint argument = to<sint>(L, -1);						//s: ud, arg
	lua_pop(L, 1);											//s: ud
	One* one = static_cast<One*>(lua_touserdata(L, -1));	//s: ud
	return push(L, one->increment(argument));				//s: ud, valuereturn 1;
}

define_lua_class(One, One)
	lua_named_entry("new", newOne)
	lua_named_entry("get", getOne)
	lua_named_entry("getValue", getValueOne)
	lua_named_entry("increment", incrementOne)
end_lua_class(One, One)

class Classes : public cfixcc::TestFixture
{
public:
	void Test_declare_lua_library_withClasses()
	{
		Lua lua;
		register_lua_library((&lua), One);
		CFIX_ASSERT(lua.doString("_G.one = One.new()"));
		lua_State* L = lua.getState();
		lua_getglobal(L, "one");
		//s: one
		CFIX_ASSERT(lua_isuserdata(L, -1));
		void* ud = lua_touserdata(L, -1);
		CFIX_ASSERT(ud);
		One* one = static_cast<One*>(lua_touserdata(L, -1));
		CFIX_ASSERT(one);
		lua_getfield(L, -1, "getValue");
		//s: one getValue
		CFIX_ASSERT(lua_iscfunction(L, -1));
		lua_pushvalue(L, -2);
		//s: one getValue one
		CFIX_ASSERT(lua_isuserdata(L, -1));
		lua_call(L, 1, 1);
		//s: one 1
		CFIX_ASSERT(lua_isnumber(L, -1));
		sint one_value = to<sint>(L, -1);
		//s: one 1
		CFIX_ASSERT(one_value == 1);
		lua_pop(L, 1);
		//s: one
		lua_getfield(L, -1, "increment");
		//s: one increment
		CFIX_ASSERT(lua_iscfunction(L, -1));
		lua_pushvalue(L, -2);
		//s: one increment one
		CFIX_ASSERT(lua_isuserdata(L, -1));
		push(L, 2);
		//s: one increment one 2
		lua_call(L, 2, 1);
		//s: one 3
		sint three_value = to<sint>(L, -1);
		//s: one 1
		CFIX_ASSERT(three_value == 3);
		lua_pop(L, 2);
		lua.require("UTOne");
		CFIX_ASSERT(lua.doString("_G.one2 = One.new()"));
		CFIX_ASSERT(lua.doString("_G.there = type(one2.decrement) == 'function'"));
		lua_getglobal(L, "there");
		bool there = to<bool>(L, -1);
		//s: _G.there
		CFIX_ASSERT(there);
		CFIX_ASSERT(lua.doString("_G.zero = one2.decrement(one2:getValue())"));
		lua_getglobal(L, "zero");
		//s: _G.there _G.zero
		CFIX_ASSERT(lua_isnumber(L, -1));
		sint zero = to<sint>(L, -1);
		CFIX_ASSERT(zero == 0);
		lua_pop(L, 2);
	}
};

CFIXCC_BEGIN_CLASS(Classes)
	CFIXCC_METHOD(Test_declare_lua_library_withClasses)
CFIXCC_END_CLASS()


#endif//EXTENDED_BY_LUA

