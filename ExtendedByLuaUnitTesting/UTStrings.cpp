#include <cfixcc.h>
#include "Singleton.h"
class UTStrings : public cfixcc::TestFixture
{
private:

public:
	static void SetUp()
	{
		designPatterns::createSingletons();
	}

	static void TearDown()
	{    
		designPatterns::destroySingletons();
	}


	void Before()
	{
	}

	void After()
	{
	}

	void Test()
	{
		CFIX_INCONCLUSIVE(__TEXT("Not implemented"));
	}
};

CFIXCC_BEGIN_CLASS(UTStrings)
	CFIXCC_METHOD(Test)
CFIXCC_END_CLASS()

