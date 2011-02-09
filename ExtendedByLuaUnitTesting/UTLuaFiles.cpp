#include <cfixcc.h>

#include "UTTools.h"

class UTLuaFiles : public cfixcc::TestFixture
{
private:

public:
	void LuaUnitTesting()
	{
		UnitTestingTools::executeLuaUnitTest("UTLibraryFunctions");
	}
	void LuaOOPUnitTesting()
	{
		UnitTestingTools::executeLuaUnitTest("UTOOP");
	}
};

CFIXCC_BEGIN_CLASS(UTLuaFiles)
	CFIXCC_METHOD(LuaUnitTesting)
	CFIXCC_METHOD(LuaOOPUnitTesting)
CFIXCC_END_CLASS()

