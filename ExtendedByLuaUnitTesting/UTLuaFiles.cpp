#include "Build.h"
#if WITH_UNIT_TESTING
#include <cfixcc.h>

#include "UTTools.h"

class UTLuaFiles : public cfixcc::TestFixture
{
private:

public:
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
