#include "UnitTestingTools.h"

#include <cfixcc.h>
#include <string.h>

#ifdef EXTENDED_BY_LUA 
#include "Lua.h"
#include "LuaStateInteraction.h"
#include "LuaExtensibility.h"
#include "LuaInclusions.h"
#include "LuaLibraryDeclarations.h"
#endif

namespace UnitTestingTools
{
#ifdef EXTENDED_BY_LUA 
using namespace LuaExtension;

void executeLuaUnitTest(char* module, Lua* lua)
{
	bool delete_lua(false);

	if (!lua)
	{
		lua = new Lua();
		delete_lua = true;
	}

	if (strcmp(module, "Grandparent") == 0)
	{
		lua->doString("_G.wtf = ObjectOrientedParadigm.classes_PRIVATE['Grandparent']");
		lua_getglobal(lua->getState(), "wtf");
		CFIX_ASSERT(lua_istable(lua->getState(), -1));
	}

	lua->require("UnitTestingFramework");
	
	if (strcmp(module, "Grandparent") == 0)
	{
		lua->doString("_G.wtf = ObjectOrientedParadigm.classes_PRIVATE['Grandparent']");
		lua_getglobal(lua->getState(), "wtf");
		CFIX_ASSERT(lua_istable(lua->getState(), -1));
	}

	CFIX_ASSERT(lua->require(module));
	
	if (strcmp(module, "Grandparent") == 0)
	{
		lua->doString("_G.wtf = ObjectOrientedParadigm.classes_PRIVATE['Grandparent']");
		lua_getglobal(lua->getState(), "wtf");
		CFIX_ASSERT(lua_istable(lua->getState(), -1));
	}

	lua_State* L = lua->getState();
	//s: ?
	lua_getglobal(L, "UnitTestingFramework");
	
	if (strcmp(module, "Grandparent") == 0)
	{
		lua->doString("_G.wtf = ObjectOrientedParadigm.classes_PRIVATE['Grandparent']");
		lua_getglobal(lua->getState(), "wtf");
		CFIX_ASSERT(lua_istable(lua->getState(), -1));
	}

	//s: UnitTestingFramework
	lua_getfield(L, -1, "testAll");
	//s: testAll
	lua_call(L, 0, 1);
	//s: bool
	lua_pop(L, 1);
	//s:
	lua_getglobal(L, "lastUnitTestNumFailures");
	//s: lastUnitTestNumFailures
	sint result = to<sint>(L, -1);
	lua_pop(L, 1);
	//s:
	lua_getglobal(L,  "lastUnitTestReport");
	//s: lastUnitTestReport
	const char* report = to<const char*>(L, -1);
	lua_pop(L, 1);
	//s:
	// Convert to a wchar_t*
	size_t origsize = strlen(report) + 1;
	size_t convertedChars = 0;
	wchar_t* wcstring = new wchar_t[origsize];
	mbstowcs_s(&convertedChars, wcstring, origsize, report, _TRUNCATE);
	CFIX_LOG(L"Lua Unit Test Report %s", wcstring);
	
	delete[] wcstring;
	if (delete_lua)
		delete lua;

	CFIX_ASSERT(result == 0);

}
#endif

} // namespace UnitTestingTools