#include "Platform.h"
#if WITH_UNIT_TESTING	
#include <cfixcc.h>
#include <string>
#include <vector>
#include "Strings.h"

#include "Table.h"

using namespace containers;
using namespace std;

const sint 
	maxStrings(1000);

const sint 
	maxStringSize(20);

static vector<String::Immutable> 
	randomStrings;

namespace
{
	template<typename NUMBER>
	NUMBER getRand(NUMBER min, NUMBER max) 
	{
		PREVENT_COMPILE
	}

	template<>
	schar getRand(schar min, schar max) 
	{
		return static_cast<schar>((rand() % (max - min)) + min);
	}
}

class UTTable : public cfixcc::TestFixture
{
private:
	
public:
	static void SetUp()
	{
		randomStrings.reserve(maxStrings);

		for (int i = 0; i < maxStrings; ++i)
		{
			string random;

			for (int j = 0; j < maxStringSize; ++j)
			{
				random.push_back(getRand('a', 'z'));
			}

			randomStrings.push_back(String::Immutable(random));
		}
	}

	static void TearDown()
	{
	
	}

	void testGet(void)
	{
		CFIX_INCONCLUSIVE(__TEXT("Not implemented"));
	}

	void testGetConst(void)
	{
		CFIX_INCONCLUSIVE(__TEXT("Not implemented"));
	}

	void testInsertAtIndex(void)
	{
		CFIX_INCONCLUSIVE(__TEXT("Not implemented"));
	}

	void testHas(void)
	{
		CFIX_INCONCLUSIVE(__TEXT("Not implemented"));
	}

	void testPopBack(void)
	{
		CFIX_INCONCLUSIVE(__TEXT("Not implemented"));
	}
	
	void testPushBack(void)
	{
		CFIX_INCONCLUSIVE(__TEXT("Not implemented"));
	}
	
	void testRemove(void)
	{
		CFIX_INCONCLUSIVE(__TEXT("Not implemented"));
	}
	
	void testRemoveAtIndex(void)
	{
		CFIX_INCONCLUSIVE(__TEXT("Not implemented"));
	}
	
	void testReserve(void)
	{
		CFIX_INCONCLUSIVE(__TEXT("Not implemented"));
	}
	
	void testSet(void)
	{
		CFIX_INCONCLUSIVE(__TEXT("Not implemented"));
	}
	
	void testSort(void)
	{
		sint i(maxStrings);
		Table<String::Immutable> t(maxStrings);

		do 
		{
			--i;
			t.pushBack(randomStrings[i]);
		}
		while (i);

		t.sort(isLess<String::Immutable>());
		for (i = 0; i < (maxStrings - 1); ++i)
		{
			const char* greater = t.get(i + 1).c_str();
			const char* lesser = t.get(i).c_str();
			CFIX_ASSERT(! (t.get(i + 1) < t.get(i)));
		}

		t.sort(isGreater<String::Immutable>());
		for (i = 0; i < (maxStrings - 1); ++i)
		{
			const char* lesser = t.get(i + 1).c_str();
			const char* greater = t.get(i).c_str();
			CFIX_ASSERT(! (t.get(i + 1) > t.get(i)));
		}

		
		t.sort(isLess<String::Immutable>());
		for (i = 0; i < (maxStrings - 1); ++i)
		{
			const char* greater = t.get(i + 1).c_str();
			const char* lesser = t.get(i).c_str();
			CFIX_ASSERT(! (t.get(i + 1) < t.get(i)));
		}
	}
};

CFIXCC_BEGIN_CLASS(UTTable)
	CFIXCC_METHOD(testGet)
	CFIXCC_METHOD(testGetConst)
	CFIXCC_METHOD(testInsertAtIndex)
	CFIXCC_METHOD(testHas)
	CFIXCC_METHOD(testPopBack)
	CFIXCC_METHOD(testPushBack)
	CFIXCC_METHOD(testRemove)
	CFIXCC_METHOD(testRemoveAtIndex)
	CFIXCC_METHOD(testReserve)
	CFIXCC_METHOD(testSet)
	CFIXCC_METHOD(testSort)
CFIXCC_END_CLASS()

#endif//WITH_UNIT_TESTING