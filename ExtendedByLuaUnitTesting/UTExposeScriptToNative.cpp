#include "Build.h"
#if WITH_UNIT_TESTING
#include <cfixcc.h>
#include "UTTools.h"

#if EXTENDED_BY_LUA 
using namespace lua_extension; 
#endif// lua_extension

class UTExposeScriptToNative : public cfixcc::TestFixture
{
private:

public:
	void Test()
	{
#if EXTENDED_BY_LUA 
		CFIX_INCONCLUSIVE(__TEXT("Not implemented"));
#endif// lua_extension
	}
};

CFIXCC_BEGIN_CLASS(UTExposeScriptToNative)
	CFIXCC_METHOD(Test)
CFIXCC_END_CLASS()
#endif//WITH_UNIT_TESTING
