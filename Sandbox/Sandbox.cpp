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
#include "Threads.h"

sint sintCompareAscending(const void* a, const void* b)		{ return (*(sint*)(a)) - (*(sint*)(b)); }
sint sintCompareDescending(const void* a, const void* b)	{ return (*(sint*)(b)) - (*(sint*)(a)); }

class QuickSortTester : public multithreading::Executable
{
public:
	virtual void execute(void)
	{
		printf("I STARTED a sort in a CLASS!\n");
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

		printf("I FINISHED a sort in a CLASS!\n");
		delete[] numbers;
	}
}; // QuickSortTester


#define TEST_OBSERVATION 1
#if TEST_OBSERVATION 

using namespace design_patterns;


class Testee 
: public Observable<Testee>
{
public:
	Testee(void)
	{
		m_observable = new ObservableHelper<Testee>(*this);
	}

	~Testee(void)
	{
		delete m_observable;
	}

	void add(Observer<Testee>* observer)
	{
		m_observable->add(observer);
	}

	void update(void)
	{
		m_observable->update();
	}

	void remove(Observer<Testee>* observer)
	{
		printf("I lost an observer!\n");
		m_observable->remove(observer);
	}

private:
	ObservableHelper<Testee>* m_observable;
};

class Tester 
: public Observer<Testee>
{
public:
	Tester(void)
	{
		m_observer = new ObserverHelper<Testee>(*this);
	}

	~Tester(void)
	{
		delete m_observer;
	}

	void ignore(Testee* observable)
	{
		m_observer->ignore(observable);
	}

	void observe(Testee* observable)
	{
		m_observer->observe(observable);
	}

protected:
	void notify(Testee*)
	{
		printf("I observed the Testee!\n");
	}

	void notifyDestruction(Testee*)
	{
		printf("I observed the Testee's destruction!\n");
	}

private:
	ObserverHelper<Testee>*	m_observer;	
};
void testObservation(void)
{
	Tester* tester1 = new Tester();
	Tester* tester2 = new Tester();
	Tester* tester3 = new Tester();
	Testee* testee = new Testee();
	tester1->observe(testee);
	tester2->observe(testee);
	tester2->observe(testee);
	tester3->observe(testee);
	testee->update();
	tester3->ignore(testee);
	delete tester2;
	delete testee;
	delete tester1;
	delete tester3;
}
#endif// TEST_OBSERVATION


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

void firstJob(void)
{
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

	printf("I finished a sort in a JOB!\n");
	delete[] numbers;
}

void Sandbox::play()
{
	printf("Playing in the sandbox!\n");
	CompilerChecks::sizeOfChecks();
	// threadsChecking();

	multithreading::Scheduler& scheduler = multithreading::Scheduler::single();
	// scheduler.enqueue(firstJob);
	
	for (uint i = 0; i < 36; i++)
	{
		scheduler.enqueue(new QuickSortTester());
	}

#if TEST_OBSERVATION
	// testObservation();
#endif//TEST_OBSERVATION
}


