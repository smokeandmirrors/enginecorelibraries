#if EXTENDED_BY_LUA
#include <cfixcc.h>
#include "Lua.h"
#include "LuaExtensibility.h"
#include "LuaInclusions.h"
#include "LuaLibraryDeclarations.h"

#include <stdlib.h>
#include <string>

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
		
	void luaUnitTesting()
	{
		Lua lua;
		lua.require("UnitTesting");
		lua.require("UnitTestingFramework");
		lua_State* L = lua.getState();
		//s: ?
		lua_getglobal(L, "UnitTestingFramework");
		//s: UnitTestingFramework
		lua_getfield(L, -1, "testAll");
		//s: testAll
		lua_call(L, 0, 1);
		//s: bool
		lua_pop(L, 1);
		//s:
		lua_getglobal(L, "lastUnitTestNumFailures");
		//s: lastUnitTestNumFailures
		sint result = static_cast<sint>(lua_tonumber(L, -1));
		lua_pop(L, 1);
		//s:
		lua_getglobal(L,  "lastUnitTestReport");
		//s: lastUnitTestReport
		const char* report = lua_tostring(L, -1);
		lua_pop(L, 1);
		//s:
		// Convert to a wchar_t*
		size_t origsize = strlen(report) + 1;
		size_t convertedChars = 0;
		// wchar_t wcstring[origsize];
		wchar_t* wcstring = new wchar_t[origsize];
		mbstowcs_s(&convertedChars, wcstring, origsize, report, _TRUNCATE);
		CFIX_LOG(L"Lua Unit Test Report %s", wcstring);
		CFIX_ASSERT(result == 0);
		delete[] wcstring;
	}

	void nilLoadedStatus()
	{
		Lua lua;
		lua.require("UnitTesting");
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
	CFIXCC_METHOD(luaUnitTesting)
	CFIXCC_METHOD(nilLoadedStatus)
	CFIXCC_METHOD(callProtected)
CFIXCC_END_CLASS()
#endif//EXTENDED_BY_LUA
