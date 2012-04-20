#include "Platform.h"
#if WITH_UNIT_TESTING
#include <cfixcc.h>

#include "UTTools.h"
#include "Singleton.h"
class UTLuaFiles : public cfixcc::TestFixture
{
public:
	static void SetUp()
	{
		designPatterns::createSingletons();
	}

	static void TearDown()
	{    
		designPatterns::destroySingletons();
	}

	void LuaUnitTesting()
	{
		unit_testing_tools::executeLuaUnitTest("UTLibraryFunctions");
	}
	void LuaOOPUnitTesting()
	{
		unit_testing_tools::executeLuaUnitTest("UTOOP");
	}
};

CFIXCC_BEGIN_CLASS(UTLuaFiles)
	CFIXCC_METHOD(LuaUnitTesting)
	CFIXCC_METHOD(LuaOOPUnitTesting)
CFIXCC_END_CLASS()
#endif//WITH_UNIT_TESTING
