#include <map>
#include <stack>
#include "Platform.h"

#include "Numbers.h"
#include "RedBlackTree.h"
#include "RedBlackMap.h"
#include "Sandbox.h"
#include "Strings.h"
#include "Table.h"
#include "Time.h"

using namespace containers;

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

#if DEVELOP_TABLE
// 	Table< RedBlackTree<sint>* > myarray;
// 	myarray.set(0, outstanding);
// 	myarray.set(1, outstanding);
// 	myarray.set(30, outstanding);
// 	myarray.pushBack(outstanding);
// 	myarray.insertAtIndex(outstanding, 10);
// 
 	Table<int> mynumbs;
 	mynumbs.set("one", 15);
	mynumbs.set("two", 30);
	mynumbs.set("three", 2);
	mynumbs.set("four", 2);
	mynumbs.set("five", 2);
	
 	for (Table<int>::Iterator i(mynumbs); i; i++)
 	{
 		printf("MyNumbs: %d\n", *i);
 	}
// 
// 	mynumbs.sort<std::greater<sint>>();
// 	printf("Sorted\n");
// 	for (Table<int>::Iterator i(mynumbs); i; i++)
// 	{
// 		printf("MyNumbs: %d\n", *i);
// 	}
// 
// 	mynumbs.sort<std::less<sint>>();
// 	printf("Sorted\n");
// 	for (Table<int>::Iterator i(mynumbs); i; i++)
// 	{
// 		printf("MyNumbs: %d\n", *i);
// 	}
// 
// 	awesome = NULL;
// 	awesome = numberToTree["awesome"];
// 	numberToTree["awesome"] = outstanding;
// 	awesome = numberToTree["awesome"];
// 	awesome->insert(5); 
// 	
// 	Table< RedBlackTree<sint>* > mytable;
// 	assert(!mytable.has("awesome"));
// 	awesome = NULL;
// 	awesome = mytable.get(String::Immutable("awesome"));
// 	awesome = outstanding;
// 	// Key(&mytable);
// 	mytable.set(Key(&mytable), awesome);
// 	assert(mytable.get(Key(&mytable)) == awesome);
// 	mytable.set("awesome", outstanding);
// 	assert(mytable.has(String::Immutable("awesome")));
// 	awesome = mytable.get(String::Immutable("awesome"));
// 	mytable.remove(String::Immutable("awesome"));
// 	assert(!mytable.has(String::Immutable("awesome")));
// 
// 	if (awesome == outstanding)
// 		printf("awesome\n");
// 	else
// 		printf("not awesome\n");

	// NoArray<sint> hashOnly;
	
	{
		// race!
		realTime::ClockReal realClock;
		realTime::Stopwatch tableTime(realClock);
		realTime::Stopwatch treeTime(realClock);
		realTime::Stopwatch mapTime(realClock);
		std::vector<String::Immutable> strings;
		
		RedBlackMap<String::Immutable, sint> tree;
		Table<sint> table;
		std::map<String::Immutable, sint> map;

		const int numStrings(1000);

		for (int i = 0; i < numStrings; i++)
		{
			std::string myString;
			char integerString[10];
			_itoa_s(i, &integerString[0], 10, 10);
			myString += integerString;
			myString += "_wicked";
			String::Immutable immutable(myString);
			strings.push_back(immutable);
		}

		treeTime.start();
		for (int i = 0; i < numStrings; i++)
		{
			tree.set(strings[i], i);	
		}
		treeTime.stop();

		tableTime.start();
		for (int i = 0; i < numStrings; i++)
		{
			table.set(strings[i], i);
// 			
// 			if (i == 1911)
// 				table.printHashPart();

			//if (i == 1911) //  || i == 1910 || i == 1912)
// 			{	
// 				// table.printHashPart();
// 						
//  				int atBreak(0);
//  				int tableCount(0);
// 				int iterationCount(0);
// 				RedBlackTree<sint> allReady;
// 
//  				for (Table<sint>::Iterator iter(table); iter; ++iter)
//  				{
// 					iterationCount++;
//  					if (i == 1911 && iterationCount == 409)
//  					{
//  						printf("wtf");
//  					}
// 					assert(!allReady.has(*iter));
// 					allReady.insert(*iter);
// 					tableCount += *iter;
//  					//assert(atBreak <= i);
//  					atBreak++;
//  				}
// 			}
		}
		tableTime.stop();
	//	printf("Print pairs\n");
// 		int count(0);
// 		for (Table<sint>::Iterator iter(table); iter; ++iter)
// 		{
// 			count++;
// 			if (count == 409)
// 				BREAKPOINT(0x0)
// 			
// 			printf("%s %d\n", iter.key().originalKeyString.c_str(), *iter);
// 			
// 			if (count > numStrings)
// 			{
// 				break;
// 				BREAKPOINT(0x0)
// 			}
// 		}
// 		BREAKPOINT(0x0)
		mapTime.start();
		for (int i = 0; i < numStrings; i++)
		{
			map[ strings[i] ] =  i;	
		}
		mapTime.stop();

		millisecond treeInsert = treeTime.milliseconds();
		millisecond tableInsert = tableTime.milliseconds();
		millisecond mapInsert = mapTime.milliseconds();

		printf("Insert Table: %10.6f\nTree  : %10.6f\nMap  : %10.6f\n\n", tableInsert, treeInsert, mapInsert); 
		// BREAKPOINT(0x0)

		int mapCount(0);
		mapTime.reset();
		mapTime.start();
		std::map<String::Immutable, sint>::iterator mapSentinel(map.end());
		for (std::map<String::Immutable, sint>::iterator i(map.begin()); i != mapSentinel; ++i)
		{
			mapCount += (*i).second; 
		}
		mapTime.stop();	

		int tableCount(0);
		tableTime.reset();
		tableTime.start();
		for (Table<sint>::Iterator iter(table); iter; ++iter)
		{
			tableCount += *iter;
		}
		tableTime.stop();

		assert(mapCount == tableCount);
		millisecond treeIterate = treeTime.milliseconds();
		millisecond tableIterate = tableTime.milliseconds();
		millisecond mapIterate = mapTime.milliseconds();
		printf("Iterate Table: %10.6f\nTree  : %10.6f\nMap  : %10.6f\n\n", tableIterate, treeIterate, mapIterate); 
		BREAKPOINT(0x0)

}

	/*
	

	
	
	*/
	
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