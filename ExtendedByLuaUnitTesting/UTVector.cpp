#if BUILD_WITH_UNIT_TESTING
#include <cfixcc.h>
#include <string.h>

#include "UTTools.h"
#include "Vector.h"

#if EXTENDED_BY_LUA
#include "Lua.h"
#include "LuaInclusions.h"
#include "LuaExtensibility.h"
#include "LuaStateInteraction.h"

using namespace LuaExtension;

#endif//EXTENDED_BY_LUA

class UTVector : public cfixcc::TestFixture
{
private:

public:
#if EXTENDED_BY_LUA
	void testLuaExtension()
	{
		Lua lua;
		registerGlobalLibrary(lua.getState());
		lua.require("Utilities");
		lua.require("ObjectOrientedParadigm");
		register_lua_library((&lua), Vector3);
		UnitTestingTools::executeLuaUnitTest("UTVector", &lua);
	
	}
#endif//EXTENDED_BY_LUA
};

CFIXCC_BEGIN_CLASS(UTVector)
	CFIXCC_METHOD(testLuaExtension)
CFIXCC_END_CLASS()
#endif//BUILD_WITH_UNIT_TESTING
