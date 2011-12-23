#include <map>

#include "Platform.h"
#include "RedBlackTree.h"
#include "Sandbox.h"
#include "Table.h"

using namespace containers;

void sandbox::tableRnD(void)
{
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
}