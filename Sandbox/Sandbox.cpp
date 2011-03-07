#include <stdio.h>
#include <tchar.h>
#include <vector>

#include "Build.h"
#include "CompilerChecks.h"
#include "Sandbox.h"
#include "Scheduling.h"
#include "Synchronization.h"
#include "Threads.h"

#if WIN32
#include <process.h>
#include <windows.h>
#endif

HANDLE mutex;

multithreading::Mutex* pMutex;// = multithreading::getMutex();
int numberOfThreads = 0;

DEFINE_NOARGS_EXECUTABLE_FUNCTION(useMutexClass,
	synchronize(pMutex);
	numberOfThreads++;
	int myNumThreads = numberOfThreads;
	Sleep(numberOfThreads * 1000);
	assert(numberOfThreads == myNumThreads);
)

sint sintCompareAscending(const void* a, const void* b)		{ return (*(sint*)(a)) - (*(sint*)(b)); }
sint sintCompareDescending(const void* a, const void* b)	{ return (*(sint*)(b)) - (*(sint*)(a)); }

DEFINE_NOARGS_EXECUTABLE_FUNCTION(doubleQuickSort,
	sint number_size = 10000;
	sint number_sort = 1000;
	sint number;
	sint* numbers = new sint[number_size];
	sint* i = numbers;
	
	for (number = 0; number < number_size; number++)
	{
		*i++ = number;
	}

	for (number = 0; number < number_sort; number++)
	{
		qsort(numbers, number_size, sizeof(uint), &sintCompareAscending);	
		qsort(numbers, number_size, sizeof(uint), &sintCompareDescending);	
	}
 
	printf("I finished a sort!\n");
	delete[] numbers;
)
//
//NOARGS_EXECUTABLE_FUNCTION(doubleQuickSort)
//{
//	sint number_size = 10000;
//	sint number_sort = 1000;
//	sint number;
//	sint* numbers = new sint[number_size];
//	sint* i = numbers;
//	
//	for (number = 0; number < number_size; number++)
//	{
//		*i++ = number;
//	}
//
//	for (number = 0; number < number_sort; number++)
//	{
//		qsort(numbers, number_size, sizeof(uint), &sintCompareAscending);	
//		qsort(numbers, number_size, sizeof(uint), &sintCompareDescending);	
//	}
// 
//	printf("I finished a sort!\n");
//	delete[] numbers;
//	return 0;
//}

void threadsChecking()
{
	pMutex = multithreading::getMutex();
	mutex = CreateMutex(NULL, false, NULL);
	
	std::vector<HANDLE> threads;
	const uint num_threads = 8;
	
	for (uint i = 0; i < num_threads; i++)
	{
		uint thread_id1;
		HANDLE thread = (HANDLE)(_beginthreadex(NULL, 0, useMutexClass, NULL, CREATE_SUSPENDED, &thread_id1));
		// HANDLE thread = (HANDLE)(_beginthreadex(NULL, 0, doubleQuickSort, NULL, CREATE_SUSPENDED, &thread_id1));
		threads.push_back(thread);
	}

	for (uint i = 0; i < num_threads; i++)
	{
		ResumeThread(threads[i]);
	}
	
	Sleep(3000);

	for (uint i = 0; i < num_threads; i++)
	{
		CloseHandle(threads[i]);
	}

	multithreading::returnMutex(pMutex);
}

void Sandbox::play()
{
	printf("Playing in the sandbox!\n");
	CompilerChecks::sizeOfChecks();
	threadsChecking();

	multithreading::Scheduler& scheduler = multithreading::Scheduler::single();
	uint max_threads = scheduler.getMaxThreads();
	max_threads++;

	multithreading::returnMutex(multithreading::getMutex());
}