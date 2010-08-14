#if EXTENDED_BY_LUA
#include <cfixcc.h>
#include "Lua.h"
#include "LuaExtensibility.h"
#include "LuaInclusions.h"
#include "LuaLibraryDeclarations.h"

#include <stdlib.h>
#include <string>

class LuaClass : public cfixcc::TestFixture
{
private:

public:
	
public:
	void luaObjectCreationAndDestruction()
	{
		Lua* no_args = new Lua();
		CFIX_ASSERT(no_args);
		CFIX_ASSERT(no_args->getState());
		delete no_args;

		Lua* args_lua = new Lua("testing", false, false);
		CFIX_ASSERT(args_lua);
		CFIX_ASSERT(args_lua->getState());
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
		int result = static_cast<int>(lua_tonumber(L, -1));
		lua_pop(L, 1);
		//s:
		lua_getglobal(L,  "lastUnitTestReport");
		//s: lastUnitTestReport
		const char* report = lua_tostring(L, -1);
		lua_pop(L, 1);
		//s:
		CFIX_ASSERT(result == 0);
		// Convert to a wchar_t*
		size_t origsize = strlen(report) + 1;
		size_t convertedChars = 0;
		// wchar_t wcstring[origsize];
		wchar_t* wcstring = new wchar_t[origsize];
		mbstowcs_s(&convertedChars, wcstring, origsize, report, _TRUNCATE);
		CFIX_LOG(L"Lua Unit Test Report %s", wcstring);
		delete[] wcstring;
		// std::string report_string(report);
		// CFIX_LOG(L"Lua Unit Test Report %s", report_string);
	}
};

CFIXCC_BEGIN_CLASS(LuaClass)
	CFIXCC_METHOD(luaObjectCreationAndDestruction)
	CFIXCC_METHOD(luaRequire)
	CFIXCC_METHOD(doString)
	CFIXCC_METHOD(luaUnitTesting)
CFIXCC_END_CLASS()
#endif//EXTENDED_BY_LUA
