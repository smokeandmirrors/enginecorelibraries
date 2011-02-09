#if EXTENDED_BY_LUA
#include <cfixcc.h>
#include <stdlib.h>
#include <string>

#include "Lua.h"
#include "LuaExtensibility.h"
#include "LuaInclusions.h"
#include "UTTools.h"

using namespace LuaExtension;

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
		CFIX_ASSERT(strcmp("testing", args_lua->getName()) == 0);
		delete args_lua;
		
		Lua stack_lua;
		CFIX_ASSERT(stack_lua.getState());
	}

	void luaRequire()
	{
		Lua* lua = new Lua();
		bool result = lua->require("Utilities"); 
		CFIX_ASSERT(result);
		result = lua->require("ObjectOrientedParadigm");
		CFIX_ASSERT(result);
		delete lua;
	}

	void doString()
	{	
		Lua lua;
		lua.doString("print\'Hello!\'");
	}
		
	void nilLoadedStatus()
	{
		Lua lua;
		lua.require("UnitTestingFramework");
		lua_State* L = lua.getState();
		//s: ?
		lua_getglobal(L, "package");
		lua_getfield(L, -1, "loaded");
		//s: package.loaded
		lua_getfield(L, -1, "UnitTestingFramework");
		//s: UnitTestingFramework
		CFIX_ASSERT(lua_istable(L, -1));
		lua_pop(L, 1);
		//s: ?
		lua.nilLoadedStatus("UnitTestingFramework");
		lua_getglobal(L, "package");
		lua_getfield(L, -1, "loaded");
		//s: package.loaded
		lua_getfield(L, -1, "UnitTestingFramework");
		//s: UnitTestingFramework
		CFIX_ASSERT(lua_isnil(L, -1));
		lua_pop(L, 1);		
	}

	void callProtected()
	{
		Lua lua;
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
	CFIXCC_METHOD(nilLoadedStatus)
	CFIXCC_METHOD(callProtected)
CFIXCC_END_CLASS()
#endif//EXTENDED_BY_LUA
