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
#include "Singleton.h"
#include "Synchronization.h"
#include "Threads.h"


class TheOne : public design_patterns::Singleton<TheOne>
{
public:
	~TheOne(void)
	{
		printf("The One Destroyed!");
	}

	void decrement(void)
	{
		--one;
	}

	sint get(void) const
	{
		return one;
	}

	void increment(void)
	{
		++one;
	}

private:
	sint one;
}; // class TheOne : public design_patterns::Singleton<TheOne>

// TheOne::getter(TheOne::getUninitialized);

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

	void notify(void)
	{
		m_observable->notify();
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
	Tester(uint value)
		: m_value(value)
	{
		m_observer = new ObserverHelper<Testee>(*this);
	}

	uint m_value;

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
	void notice(Testee*)
	{
		printf("I observed the Testee!\n");
	}

private:
	ObserverHelper<Testee>*	m_observer;	
};
void testObservation(void)
{
	Tester* tester1 = new Tester(1);
	Tester* tester2 = new Tester(2);
	Tester* tester3 = new Tester(3);
	Tester* tester4 = new Tester(4);
	Testee* testee = new Testee();
	
	testee->add(tester1);
	tester1->observe(testee); // bad!
	testee->add(tester2);
	testee->add(tester4);
	testee->add(tester2);
	testee->add(tester3);
	testee->remove(tester4);
	testee->notify();
	tester3->ignore(testee);
	
	delete tester2;
	delete testee;
	delete tester1;
	delete tester3;
	delete tester4;
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
	testObservation();
#endif//TEST_OBSERVATION
}


