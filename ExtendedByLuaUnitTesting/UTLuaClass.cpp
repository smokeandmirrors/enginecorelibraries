#include "Platform.h"
#if WITH_UNIT_TESTING
#if EXTENDED_BY_LUA
#include <cfixcc.h>
#include <stdlib.h>
#include <string>

#include "Lua.h"
#include "LuaExtensibility.h"
#include "LuaInclusions.h"
#include "LuaStateInteraction.h"
#include "UTTools.h"

using namespace embeddedLua;

class LuaClass : public cfixcc::TestFixture
{
private:

public:
	
public:
	/**
	tests: constructors(), openLibrary(), openStandardLibraries()
	getState(), getName()
	*/
	void luaObjectCreationAndDestruction()
	{
		Lua* no_args = new Lua();
		CFIX_ASSERT(no_args);
		CFIX_ASSERT(no_args->getState());
		delete no_args;

		Lua* args_lua = new Lua("testing", false, false);
		CFIX_ASSERT(args_lua);
		CFIX_ASSERT(args_lua->getState());
		CFIX_ASSERT(String::compare("testing", args_lua->getName()) == 0);
		delete args_lua;
		
		Lua stack_lua;
		CFIX_ASSERT(stack_lua.getState());
	}

	void luaRequire()
	{
		DECLARE_UNIT_TESTING_LUA_OBJECT
		bool result = lua.require("Utilities"); 
		CFIX_ASSERT(result);
		result = lua.require("ObjectOrientedParadigm");
		CFIX_ASSERT(result);
	}

	void doString()
	{	
		DECLARE_UNIT_TESTING_LUA_OBJECT
		lua.doString("print\'Hello!\'");
	}
	
	void callProtected()
	{
		DECLARE_UNIT_TESTING_LUA_OBJECT
		lua_State* L = lua.getState();
		lua_getglobal(L, "math");
		CFIX_ASSERT(lua_istable(L, -1));
		lua_getfield(L, -1, "sqrt");
		CFIX_ASSERT(lua_isfunction(L, -1));
		lua_pushnumber(L, 4);
		Lua::callProtected(L, 1);
		CFIX_ASSERT(lua_isnumber(L, -1));
		sint i = static_cast<sint>(lua_tonumber(L, -1));
		CFIX_ASSERT(i == 2);
		lua_pop(L, 1);
		lua_getglobal(L, "math");
		CFIX_ASSERT(lua_istable(L, -1));
		lua_getfield(L, -1, "sqrt");
		CFIX_ASSERT(lua_isfunction(L, -1));
		Lua::callProtected(L, 1);
	}
};

CFIXCC_BEGIN_CLASS(LuaClass)
	CFIXCC_METHOD(luaObjectCreationAndDestruction)
	CFIXCC_METHOD(luaRequire)
	CFIXCC_METHOD(doString)
	CFIXCC_METHOD(callProtected)
CFIXCC_END_CLASS()
#endif//EXTENDED_BY_LUA
#endif//WITH_UNIT_TESTING