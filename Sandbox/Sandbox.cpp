#include <stdio.h>
#include <tchar.h>
#include <vector>

#if WIN32
#include <process.h>
#include <windows.h>
#endif//WIN32

#include "Build.h"
#include "CompilerChecks.h"
#include "Observation.h"
#include "Sandbox.h"
#include "Scheduling.h"
#include "Synchronization.h"
#include "Time.h"
#include "Threads.h"

template<typename T>
class TVector3
{
public:
	T x;
	T y;
	T z;

	TVector3()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	void add(const TVector3& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
	}
};


sint4 sintCompareAscending(const void* a, const void* b)		{ return (*(sint4*)(a)) - (*(sint4*)(b)); }
sint4 sintCompareDescending(const void* a, const void* b)	{ return (*(sint4*)(b)) - (*(sint4*)(a)); }

class QuickSortTester : public multithreading::Executable
{
public:
	virtual void execute(void)
	{
		printf("I STARTED a sort in a CLASS!\n");
		sint4 number_size = 10000;
		sint4 number_sort = 1000;
		sint4 number;
		sint4* numbers = new sint4[number_size];
		sint4* i = numbers;

		for (number = 0; number < number_size; number++)
		{
			*i++ = number;
		}

		for (number = 0; number < number_sort; number++)
		{
			qsort(numbers, number_size, sizeof(uint4), &sintCompareAscending);	
			qsort(numbers, number_size, sizeof(uint4), &sintCompareDescending);	
		}

		printf("I FINISHED a sort in a CLASS!\n");
		delete[] numbers;
	}
}; // QuickSortTester


HANDLE mutex;

multithreading::Mutex* pMutex;// = multithreading::getMutex();
sint4 numberOfThreads = 0;

DEFINE_NOARGS_EXECUTABLE_FUNCTION(useMutexClass,
	synchronize(pMutex);
	numberOfThreads++;
	sint4 myNumThreads = numberOfThreads;
	Sleep(numberOfThreads * 1000);
	assert(numberOfThreads == myNumThreads);
)

DEFINE_NOARGS_EXECUTABLE_FUNCTION(doubleQuickSort,
	sint4 number_size = 10000;
	sint4 number_sort = 1000;
	sint4 number;
	sint4* numbers = new sint4[number_size];
	sint4* i = numbers;
	
	for (number = 0; number < number_size; number++)
	{
		*i++ = number;
	}

	for (number = 0; number < number_sort; number++)
	{
		qsort(numbers, number_size, sizeof(uint4), &sintCompareAscending);	
		qsort(numbers, number_size, sizeof(uint4), &sintCompareDescending);	
	}
 
	printf("I finished a sort!\n");
	delete[] numbers;
)
//
//NOARGS_EXECUTABLE_FUNCTION(doubleQuickSort)
//{
//	sint4 number_size = 10000;
//	sint4 number_sort = 1000;
//	sint4 number;
//	sint4* numbers = new sint4[number_size];
//	sint4* i = numbers;
//	
//	for (number = 0; number < number_size; number++)
//	{
//		*i++ = number;
//	}
//
//	for (number = 0; number < number_sort; number++)
//	{
//		qsort(numbers, number_size, sizeof(uint4), &sintCompareAscending);	
//		qsort(numbers, number_size, sizeof(uint4), &sintCompareDescending);	
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
	const uint4 num_threads = 8;
	
	for (uint4 i = 0; i < num_threads; i++)
	{
		uint4 thread_id1;
		HANDLE thread = (HANDLE)(_beginthreadex(NULL, 0, useMutexClass, NULL, CREATE_SUSPENDED, &thread_id1));
		// HANDLE thread = (HANDLE)(_beginthreadex(NULL, 0, doubleQuickSort, NULL, CREATE_SUSPENDED, &thread_id1));
		threads.push_back(thread);
	}

	for (uint4 i = 0; i < num_threads; i++)
	{
		ResumeThread(threads[i]);
	}
	
	Sleep(3000);

	for (uint4 i = 0; i < num_threads; i++)
	{
		CloseHandle(threads[i]);
	}

	multithreading::returnMutex(pMutex);
}

void firstJob(void)
{
	sint4 number_size = 10000;
	sint4 number_sort = 1000;
	sint4 number;
	sint4* numbers = new sint4[number_size];
	sint4* i = numbers;

	for (number = 0; number < number_size; number++)
	{
		*i++ = number;
	}

	for (number = 0; number < number_sort; number++)
	{
		qsort(numbers, number_size, sizeof(uint4), &sintCompareAscending);	
		qsort(numbers, number_size, sizeof(uint4), &sintCompareDescending);	
	}

	printf("I finished a sort in a JOB!\n");
	delete[] numbers;
}

void sandbox::play()
{
	printf("Playing in the sandbox!\n");
	
	//compiler_checks::sizeOfChecks();
	//// threadsChecking();
	//multithreading::Scheduler& scheduler = multithreading::Scheduler::single();
	//// scheduler.enqueue(firstJob);
	//for (uint4 i = 0; i < 8; i++)
	//{
	//	scheduler.enqueue(new QuickSortTester());
	//}

	real_time::Clock man_clock;
	real_time::Clock backwards;
	backwards.setRate(-2.0);
	real_time::StopWatch timer(backwards);
	cycle before = real_time::cycles();
	Sleep(3000);
	cycle after = real_time::cycles();
	cycle delta = after - before;
	millicycle mhz = real_time::millihertz();
	millicycle delta_mcylc = delta/mhz;
	man_clock.tick();
	millisecond man_ms = man_clock.milliseconds();
	second man_seconds = man_clock.seconds();
	backwards.tick();
	millisecond back_ms = backwards.milliseconds();
	second back_s = backwards.seconds();
	timer.stop();
	millisecond timed_ms = timer.milliseconds();
	second timed_s = timer.seconds(); 

	printf("Stopped playing in the sandbox!\n");
}


