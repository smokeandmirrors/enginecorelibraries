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
		unitTestingTools::executeLuaUnitTest("UTLibraryFunctions");
	}
	void LuaOOPUnitTesting()
	{
		unitTestingTools::executeLuaUnitTest("UTOOP");
	}
};

CFIXCC_BEGIN_CLASS(UTLuaFiles)
	CFIXCC_METHOD(LuaUnitTesting)
	CFIXCC_METHOD(LuaOOPUnitTesting)
CFIXCC_END_CLASS()
#endif//WITH_UNIT_TESTING
