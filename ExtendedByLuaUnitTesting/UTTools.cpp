#include "Build.h"
#if WITH_UNIT_TESTING

#include <cfixcc.h>
#include <string.h>
#include <math.h>
#include "UTTools.h"

#if EXTENDED_BY_LUA 
#include "LuaExtensionInclusions.h"
#endif

namespace unitTestingTools
{

void checkNearEqual(float lhs, float rhs, float tolerance)
{
	tolerance = tolerance == 0.0f ? 0.0001f : tolerance;
	float delta = fabs(lhs - rhs);
	CFIXCC_ASSERT_LESS_OR_EQUAL(delta, tolerance);
}

void checkNearEqual(double lhs, double rhs, double tolerance)
{
	tolerance = tolerance == 0.0f ? 0.0001 : tolerance;
	double delta = abs(lhs - rhs);
	CFIXCC_ASSERT_LESS_OR_EQUAL(delta, tolerance);
}

#if EXTENDED_BY_LUA 
using namespace luaExtension;

void executeLuaUnitTest(char* module, Lua* lua)
{
	bool delete_lua(false);

	if (!lua)
	{
		lua = new Lua();
		delete_lua = true;
	}

	lua->require("UnitTestingFramework");
	if (!lua->require(module))
	{
		size_t origsize = strlen(module) + 1;
		size_t convertedChars = 0;
		wchar_t* wmodule = new wchar_t[origsize * 10];
		mbstowcs_s(&convertedChars, wmodule, origsize, module, _TRUNCATE);
		CFIX_LOG(L"\nLua Unit Test Report: %s", wmodule);
		CFIX_LOG(L"Test not found or written incorrectly: %s", wmodule);
		return;
	}
	lua_State* L = lua->getState();
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
	wchar_t* wreport = new wchar_t[origsize * 10];
	mbstowcs_s(&convertedChars, wreport, origsize, report, _TRUNCATE);
	CFIX_LOG(L"\nLua Unit Test Report: %s", wreport);
	
	delete[] wreport;
	if (delete_lua)
		delete lua;

	CFIX_ASSERT(!result);
}
#endif

} // namespace unitTestingTools
#endif//WITH_UNIT_TESTING