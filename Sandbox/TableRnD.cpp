#include <map>

#include "Platform.h"
#include "RedBlackTree.h"
#include "Sandbox.h"
#include "Strings.h"
#include "Table.h"

using namespace containers;


void sandbox::tableRnD(void)
{
#if DEVELOP_TABLE

	RedBlackTree<sint>* outstanding = new RedBlackTree<sint>;
	RedBlackTree<sint>* awesome;
	
	std::map<const char*, RedBlackTree<sint>*> numberToTree;
	awesome = NULL;
	awesome = numberToTree["awesome"];
	numberToTree["awesome"] = outstanding;
	awesome = numberToTree["awesome"];
	awesome->insert(5); 

	Table< RedBlackTree<sint>* > mytable;
	awesome = NULL;
	awesome = mytable["awesome"];
	mytable["awesome"] = outstanding;
	awesome = mytable["awesome"];
	
	if (awesome == outstanding)
		printf("awesome\n");
	else
		printf("not awesome\n");

	const Strings::Immutable& immutable = Strings::getImmutable("can't change!");
	printf(immutable.string.c_str());
#endif DEVELOP_TABLE

#if DEVELOP_INTERNAL_STRING
#endif//DEVELOP_INTERNAL_STRING

	std::string really("rel", 3);
	printf("%s\n", really.c_str());
	size_t sum = really.size() + really.length();
	printf("%d\n", sum);
	
	{
		Strings::Immutable stackVersion("stackVersion");
		Strings::Immutable* heapVersion = new Strings::Immutable("stackVersion");
		Strings::Immutable stackVersion2("stackVersion2");
		Strings::Immutable* heapVersion2 = new Strings::Immutable("stackVersion2");
		delete heapVersion2;
		delete heapVersion;
	}
	
	printf("woot\n");
}