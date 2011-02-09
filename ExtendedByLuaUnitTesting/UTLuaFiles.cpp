#include <cfixcc.h>

#include "UnitTestingTools.h"

class UTLuaFiles : public cfixcc::TestFixture
{
private:

public:
	void LuaUnitTesting()
	{
		UnitTestingTools::executeLuaUnitTest("UnitTesting");
	}
	void LuaOOPUnitTesting()
	{
		UnitTestingTools::executeLuaUnitTest("OOPUnitTesting");
	}
};

CFIXCC_BEGIN_CLASS(UTLuaFiles)
	CFIXCC_METHOD(LuaUnitTesting)
	CFIXCC_METHOD(LuaOOPUnitTesting)
CFIXCC_END_CLASS()

