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
	/*
	RedBlackTree<sint> printMe;
	for (int i= 0; i < 20; i++)
		printMe.insert(i);

	printf("in:\n");
	printMe.printInOrder();
	printf("\npost:\n");
	printMe.printPostOrder();
	printf("\npre\n");
	printMe.printPreOrder();
	printMe.printBFV();
	

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
	
	srand(static_cast<uint>(xronos::Clock::single().cycles()));
	
	for (int i = 0; i < 10; i++)
		printf("%f\n", generateRandom<sreal>(-1.0f, 1.0f));

	for (int i = 0; i < 10; i++)
		printf("%d\n", generateRandom<sint>(-10, 10));

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
		// randomNumber = generateRandom<sint>(-100, 100);
		randomNumber = i;
		numbers.push_back(randomNumber);
		
		assert(!rbt.has(randomNumber));
		assert(rbt.getSize() == sum);
		sum++;
		rbt.insert(randomNumber);
		assert(rbt.getSize() == sum);
		assert(rbt.has(randomNumber));
		
		assert(!rbt.has(-101));
		assert(!rbt.has(101));
		assert(rbt.getMax() <= 100);
		assert(rbt.getMin() >= -100);		
	}
	
	delete pRbt;
	*/
#if DEVELOP_TABLE
// 	Table< RedBlackTree<sint>* > myarray;
// 	myarray.set(0, outstanding);
// 	myarray.set(1, outstanding);
// 	myarray.set(30, outstanding);
// 	myarray.pushBack(outstanding);
// 	myarray.insertAtIndex(outstanding, 10);
// 
//  	Table<int> mynumbs;
//  	mynumbs.set("one", 15);
// 	mynumbs.set("two", 30);
// 	mynumbs.set("three", 2);
// 	mynumbs.set("four", 2);
// 	mynumbs.set("five", 2);
// 	
//  	for (Table<int>::Iterator i(mynumbs); i; i++)
//  	{
//  		printf("MyNumbs: %d\n", i.value());
//  	}
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
		xronos::Clock& realClock(xronos::Clock::single());
		xronos::Stopwatch tableTime(realClock);
		xronos::Stopwatch treeTime(realClock);
		xronos::Stopwatch mapTime(realClock);
		std::vector<String::Immutable> strings;
		
		RedBlackMap<String::Immutable, sint> tree;
		Set<sint> table;
		// Table<sint> table;
		std::map<String::Immutable, sint> map;

		const int numStrings(10000);

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

		// find the delete problem
		{
			for (int i = 0; i < numStrings; i++)
			{
				tree.set(strings[i], i);
			}

			for (int j = 0; j < numStrings; j++)
			{
				tree.remove(strings[j]);
			}
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
		}
		table.shrink();
		tableTime.stop();

		mapTime.start();
		for (int i = 0; i < numStrings; i++)
		{
			map[ strings[i] ] =  i;	
		}
		mapTime.stop();

		millisecond treeInsert = treeTime.milliseconds();
		millisecond tableInsert = tableTime.milliseconds();
		millisecond mapInsert = mapTime.milliseconds();

		printf("Insert:\n%10.6f :Table\n%10.6f :Tree\n%10.6f :Map\n\n", tableInsert, treeInsert, mapInsert); 
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

		int treeCount(0);
		treeTime.reset();
		treeTime.start();
		
		for (RedBlackMap<String::Immutable, sint>::Iterator i(tree.begin()); i; ++i)
		{
			treeCount += (*i); 
		}
		treeTime.stop();	

		int tableCount(0);
		tableTime.reset();
		tableTime.start();
 		for (Set<sint>::Iterator iter(table); iter; ++iter)
 		{
 			tableCount += iter.value();
 		}
		tableTime.stop();

		millisecond treeIterate = treeTime.milliseconds();
		millisecond tableIterate = tableTime.milliseconds();
		millisecond mapIterate = mapTime.milliseconds();
		printf("Iterate:\n%10.6f :Table\n%10.6f :Tree\n%10.6f :Map\n\n", tableIterate, treeIterate, mapIterate); 

		// find performance
		{	
			bool treeHas(true);
			treeTime.start();
			for (int i = 0; i < numStrings; i++)
			{
				treeHas &= tree.has(strings[i]);
			}
			treeTime.stop();
			assert(treeHas);		

			bool tableHas(true);
			tableTime.start();
			for (int i = 0; i < numStrings; i++)
			{
				tableHas &= table.has(strings[i]);
			}
			tableTime.stop();
			assert(tableHas);		
		
			bool mapHas(true);
			mapTime.start();
			for (int i = 0; i < numStrings; i++)
			{
				mapHas &= map.find(strings[i]) != mapSentinel;
			}
			mapTime.stop();
			assert(mapHas);

			millisecond treeInsert = treeTime.milliseconds();
			millisecond tableInsert = tableTime.milliseconds();
			millisecond mapInsert = mapTime.milliseconds();

			printf("Find:\n%10.6f :Table\n%10.6f :Tree\n%10.6f :Map\n\n", tableInsert, treeInsert, mapInsert); 
		}

		Set<int> emptyTable;
		
		for (Set<int>::Iterator emptyIterator(emptyTable); emptyIterator; emptyIterator++)
		{
			Set<int>::Iterator emptyIteratorCopy(emptyTable, emptyIterator.key());
			printf("Did this work?\n");
		}

		Set<sint>::Iterator iter(table);
		Set<sint>::IteratorConst iterConst(table);
		Set<sint>::Iterator pp1(table, iter.key());
		Set<sint>::IteratorConst iterConstpp1(table, iter.key());

		bool switcher(false);

		while (iter)
		{
			Set<sint>::Iterator pp(table, iter.key());
			
			sint iterValue = iter.value();
			sint ppValue = pp.value();
			sint pp1Value = pp1.value();
			sint iterConstValue = iterConst.value();
			const sint iterConstValuepp1 = iterConstpp1.value();
			assert( iterValue == ppValue);
			assert( iterValue == pp1Value);
			assert( iterValue == iterConstValue);
			assert( iterValue == iterConstValuepp1);
			
			if (switcher)
			{
				++iter;
				++pp1;
				++pp;
				++iterConstpp1;
				++iterConst;
			}
			else
			{
				iter++;
				pp1++;
				pp++;
				iterConstpp1++;
				iterConst++;
			}
			switcher = (!switcher);
		}

		assert(!pp1);
		
		assert(mapCount == tableCount);

		// delete performance
		{

			treeTime.start();
			for (int i = 0; i < numStrings; i++)
			{
				tree.remove(strings[i]);	
			}
			treeTime.stop();

			tableTime.start();
			for (int i = 0; i < numStrings; i++)
			{
				table.remove(strings[i]);
			}
			tableTime.stop();

			mapTime.start();
			for (int i = 0; i < numStrings; i++)
			{
				map.erase(strings[i]);
			}
			mapTime.stop();

			millisecond treeInsert = treeTime.milliseconds();
			millisecond tableInsert = tableTime.milliseconds();
			millisecond mapInsert = mapTime.milliseconds();

			printf("Delete:\n%10.6f :Table\n%10.6f :Tree\n%10.6f :Map\n\n", tableInsert, treeInsert, mapInsert); 
		}

		BREAKPOINT(0x0)
}

	/*
	
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