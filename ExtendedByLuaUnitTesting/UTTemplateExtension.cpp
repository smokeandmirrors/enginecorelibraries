#include "Platform.h"
#if 0 //WITH_UNIT_TESTING
#include <cfixcc.h>
#include "UTTools.h"

#if EXTENDED_BY_LUA
#include "LuaExtensionInclusions.h"

using namespace embeddedLua;

class UTTemplateExtension : public cfixcc::TestFixture
{
private:

public:
	void Test()
	{
		//CFIX_INCONCLUSIVE(__TEXT("Not implemented"));
	}
};

CFIXCC_BEGIN_CLASS(UTTemplateExtension)
	//CFIXCC_METHOD(Test)
CFIXCC_END_CLASS()

#endif//EXTENDED_BY_LUA
#endif//WITH_UNIT_TESTING

