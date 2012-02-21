#include <map>

#include "Platform.h"

#include "Numbers.h"
#include "RedBlackTree.h"
#include "RedBlackMap.h"
#include "Sandbox.h"
#include "Strings.h"
#include "Table.h"
#include "Time.h"

using namespace containers;

struct TestUnion
{
	TestUnion(bool source)
	: UnionT(source)
	{
	}

	TestUnion(sint source)
	: UnionT(source)
	{

	}

	union MyUnion
	{
		bool keyBool;
		sint keyInteger;

		MyUnion(bool source) : keyBool(source) {}
		MyUnion(sint source) : keyInteger(source) {}
	} UnionT;
};

void sandbox::tableRnD(void)
{
	RedBlackMap<const schar*, int> stringToNumber;
	stringToNumber.set("awesome", 10);
	stringToNumber.set("bitchin", 20);
	sint bitchin = stringToNumber.get("bitchin");
	if (bitchin) printf("");	
	std::map<int, int> numberToNumber;
	numberToNumber[10] = 100;
	int index100 = numberToNumber[100];
	
	if (index100 < 0)
		printf("referenced");

	RedBlackTree<sint>* outstanding = new RedBlackTree<sint>;
	RedBlackTree<sint>* awesome;

	std::map<const char*, RedBlackTree<sint>*> numberToTree;
	awesome = NULL;
	numberToTree["awesome"] = outstanding;
	awesome = numberToTree["awesome"];
	awesome->insert(5); 
	
	srand(static_cast<uint>(realTime::cycles()));
	
	for (int i = 0; i < 10; i++)
		printf("%f\n", getRand<sreal>(-1.0f, 1.0f));

	for (int i = 0; i < 10; i++)
		printf("%d\n", getRand<sint>(-10, 10));

	// RedBlackTree<sint> rbt;
	RedBlackTree<sint>* pRbt = new RedBlackTree<sint>();
	RedBlackTree<sint>& rbt = *pRbt;
	assert(rbt.isEmpty());
	rbt.insert(-1);
	rbt.remove(-1);
	rbt.getMax();
	rbt.getMin();
	rbt.getSize();
	assert(!rbt.has(2));
	rbt.removeMax();
	rbt.removeMin();

	uint sum = 0;
	
	std::vector<sint> numbers;
	sint randomNumber;
	
	for (sint i = 0; i < 10000; i++)
	{
		// randomNumber = getRand<sint>(-100, 100);
		randomNumber = i;
		numbers.push_back(randomNumber);
		
		assert(!rbt.has(randomNumber));
		assert(rbt.getSize() == sum);
		sum++;
		rbt.insert(randomNumber);
		assert(rbt.getSize() == sum);
		assert(rbt.has(randomNumber));
		
		/*
		assert(!rbt.has(-101));
		assert(!rbt.has(101));
		assert(rbt.getMax() <= 100);
		assert(rbt.getMin() >= -100);		
		*/
	}
	
	delete pRbt;


	TestUnion intVersion(3);
	TestUnion boolVersion(false);

	boolVersion = intVersion;

#if DEVELOP_TABLE
	RedBlackTree<sint>* outstanding = new RedBlackTree<sint>;
	RedBlackTree<sint>* awesome;

		


	Table< RedBlackTree<sint>* > myarray;
	myarray.set(0, outstanding);
	myarray.set(1, outstanding);
	myarray.set(30, outstanding);
	myarray.pushBack(outstanding);
	myarray.insertAtIndex(outstanding, 10);

	Table<int> mynumbs;
	mynumbs.pushBack(30);
	mynumbs.pushBack(2);
	mynumbs.set(6, 6);
	
	for (Table<int>::Iterator i(mynumbs); i; i++)
	{
		printf("MyNumbs: %d\n", *i);
	}


	mynumbs.sort(isGreater<sint>());

	for (Table<int>::Iterator i(mynumbs); i; i++)
	{
		printf("MyNumbs: %d\n", *i);
	}

	std::map<const char*, RedBlackTree<sint>*> numberToTree;
	awesome = NULL;
	awesome = numberToTree["awesome"];
	numberToTree["awesome"] = outstanding;
	awesome = numberToTree["awesome"];
	awesome->insert(5); 

	String::Argument arg("awesome");
	String::Immutable imm("awesome");
	Table< RedBlackTree<sint>* >::Key karg("awesome");
	
	if (karg.isValid())
		printf("Karg is valid");
	else
		printf("awesome");
	
	Table< RedBlackTree<sint>* >::Key kkarg(arg);
	Table< RedBlackTree<sint>* >::Key kimm(imm);

	if (kimm.isValid() && kkarg.isValid())
		printf("awesome");

	Table< RedBlackTree<sint>* > mytable;
	assert(!mytable.has("awesome"));
	awesome = NULL;
	awesome = mytable.get("awesome");
	mytable.set("awesome", outstanding);
	assert(mytable.has("awesome"));
	awesome = mytable.get("awesome");
	mytable.remove("awesome");
	assert(!mytable.has("awesome"));

	if (awesome == outstanding)
		printf("awesome\n");
	else
		printf("not awesome\n");


#endif DEVELOP_TABLE
	{
		std::string really("rel", 3);
		printf("%s\n", really.c_str());
		size_t sum = really.size() + really.length();
		printf("%d\n", sum);
		
		{
			String::Immutable stackVersion("stackVersion");
			String::Immutable* heapVersion = new String::Immutable("stackVersion");
			String::Immutable stackVersion2("stackVersion2");
			String::Immutable* heapVersion2 = new String::Immutable("stackVersion2");
			delete heapVersion2;
			delete heapVersion;
		}
		
		printf("woot\n");
	}
}