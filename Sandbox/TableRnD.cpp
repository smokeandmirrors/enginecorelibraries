#include <map>

#include "Platform.h"
#include "RedBlackTree.h"
#include "Sandbox.h"
#include "Strings.h"
#include "Table.h"

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