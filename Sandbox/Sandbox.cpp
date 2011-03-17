#include <list>
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
#include "Time.h"
#include "Vector.h"

class EngineLoop;
class FrameRequirement;

// make an interface
class FrameRequirement
: public design_patterns::Observable<FrameRequirement>
, public design_patterns::Observer<EngineLoop>
{
public:
	void ignore(EngineLoop* observable);

	void notice(EngineLoop* observable)=0;

	bool isCompleted(void) const;

	void observe(EngineLoop* observable);

private:
	bool	m_isCompleted;
	design_patterns::ObserverHelper<EngineLoop> 
		m_observer;
}; // class FrameRequirement

class EngineLoop
: public design_patterns::Observable<EngineLoop>
, public design_patterns::Observer<FrameRequirement>
{
	typedef std::list<FrameRequirement*>	requirements;
	typedef requirements::iterator			requirements_iter;

public:
	void add(design_patterns::Observer<EngineLoop>* observer)
	{
		m_observable.add(observer);
	}
	
	void addFrameRequirement(FrameRequirement* observable)
	{
		m_incomplete.push_back(observable);
	}

	uint8 getFrameNumber(void) const 
	{ 
		return m_frameNumber; 
	}

	void ignore(FrameRequirement* observable)
	{
		m_observer.ignore(observable);
	}

	void notice(FrameRequirement* observable)
	{	// really this would always be true
		if (observable->isCompleted())
		{
			markRequirementCompleted(observable);	
		}

		synchronize(m_mutex);
		
		if (isFrameCompleted())
		{
			markFrameCompleted();
		}
	}
	
	void notify(void)
	{
		m_observable.notify();
	}
	
	void observe(FrameRequirement* observable)
	{
		m_observer.observe(observable);
	}
	
	void removeFrameRequirement(FrameRequirement* observable)
	{
		removeFromList(observable, m_completed, m_completeMutex);
		removeFromList(observable, m_incomplete, m_incompleteMutex);
	}
	
	void remove(design_patterns::Observer<EngineLoop>* observer)
	{
		m_observable.remove(observer);
	}

protected:
	void addToList(FrameRequirement* req, requirements& reqs_list, multithreading::Mutex& mutex)
	{
		synchronize(mutex)
		reqs_list.push_back(req);
	}

	bool isFrameCompleted(void) const
	{
		return m_incomplete.empty();
	}
	
	void markFrameCompleted(void)
	{
		m_frameNumber++;
		notify();
		markRequirementsIncomplete();
	}
	
	void markRequirementCompleted(FrameRequirement* requirement)
	{
		removeFromList(requirement, m_incomplete, m_incompleteMutex);
		addToList(requirement, m_completed, m_completeMutex);
	}
	
	void markRequirementsIncomplete(void)
	{
		synchronize(m_completeMutex)
		synchronize(m_incompleteMutex)
		assert(m_incomplete.empty());
		m_incomplete = m_completed;
		m_completed.resize(0);
		assert(m_completed.empty());
	}

	void removeFromList(FrameRequirement* req, requirements& reqs_list, multithreading::Mutex& mutex)
	{
		synchronize(mutex)
		for (requirements_iter iter = reqs_list.begin(); iter != reqs_list.end(); iter++)
		{
			if (*iter == req)
			{
				reqs_list.erase(iter);
				return;
			}
		}
	}
	
private:
	requirements					m_completed;
	multithreading::Mutex			m_completeMutex;
	uint8							m_frameNumber;
	requirements					m_incomplete;
	multithreading::Mutex			m_incompleteMutex;
	multithreading::Mutex			m_mutex;
	design_patterns::ObservableHelper<EngineLoop>		
									m_observable;
	design_patterns::ObserverHelper<FrameRequirement>	
									m_observer;
}; // class EngineLoop

void FrameRequirement::ignore(EngineLoop* observable)
{
	m_observer.ignore(observable);
}
 
// void FrameRequirement::notice(EngineLoop* observable)
// {
// 	// if the engine loop is complete..
// 	// then queue up some more work 
// 	// on the scheduler?
// 	// if (lastFrameLoop < currentFrameLoop)
// 	// {}
// }

bool FrameRequirement::isCompleted(void) const
{
	return m_isCompleted;
}

void FrameRequirement::observe(EngineLoop* observable)
{
	m_observer.observe(observable);
}


class Physical
: public multithreading::Executable
{
public:
	Physical(millisecond work_time, Physical* next=NULL)
	: m_workTime(work_time)
	, m_next(next)
	{
		/* empty */
	}
	
	void execute(void)
	{
		multithreading::sleep(m_workTime);
		
		if (m_next)
		{
			multithreading::Scheduler::single().enqueue(m_next);
		}
	}

protected:
	Physical*	m_next;
	millisecond	m_workTime;
};


Physical	physOne(1000);
Physical	physTwo(2000);
Physical	physThree(3000, &physOne);
Physical	physFour(4000, &physTwo);

class Physics 
: public FrameRequirement
, public multithreading::Executable
{
public:
	void execute(void)
	{
		multithreading::Scheduler::single().enqueue(&physFour);
		multithreading::Scheduler::single().enqueue(&physThree);
	}

	void notice(EngineLoop* observable)
	{
		uint8 current_frame = observable->getFrameNumber();

		if (current_frame > m_lastFrame)
		{
			// queue up some work
			m_lastFrame = current_frame;

		}
	}

private:
	uint8 m_lastFrame;
}; // class Physics


sint4 sintCompareAscending(const void* a, const void* b)	{ return (*(sint4*)(a)) - (*(sint4*)(b)); }
sint4 sintCompareDescending(const void* a, const void* b)	{ return (*(sint4*)(b)) - (*(sint4*)(a)); }

class QuickSortTester : public multithreading::Executable
{
public:
	virtual void execute(void)
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

		delete[] numbers;

		multithreading::Scheduler::single().enqueue(
			new QuickSortTester(),  
			multithreading::noThreadPreference, 
			"2nd Gen!");
	}
}; // QuickSortTester

HANDLE mutex;

multithreading::Mutex m_mutex;
sint4 numberOfThreads = 0;

DEFINE_NOARGS_EXECUTABLE_FUNCTION(useMutexClass,
	synchronize(m_mutex);
	numberOfThreads++;
	sint4 myNumThreads = numberOfThreads;
	multithreading::sleep(numberOfThreads * 1000);
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
	
	multithreading::sleep(3000);

	for (uint4 i = 0; i < num_threads; i++)
	{
		CloseHandle(threads[i]);
	}
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

template<typename T> 
void testVectors(T epsilon)
{
	math::V3<T> lhs;
	math::V3<T> rhs; 
	bool nearly_equals = lhs.nearlyEquals(rhs, epsilon);
	T distance = lhs.distanceSqr(rhs);
	if (nearly_equals)
	{
		printf("nearly equal!");
	}

	if (distance < 0)
	{
		printf("impossible!");
	}
}

void playNumericalFunctions(void)
{
	real8 f8;
	real4 f4;
	sint8 si8;
	sint4 si4;

	printf("%f", math::abs<real8>(f8));
	printf("%f", math::ln<real4>(f4));
	printf("%f", abs(f8));
	printf("%f", abs(f4));

}


void sandbox::play()
{
	printf("Playing in the sandbox!\n");	

	compiler_checks::sizeOfChecks();
	// threadsChecking();	
	multithreading::Scheduler& scheduler = multithreading::Scheduler::single();
	// scheduler.enqueue(firstJob);
	
	uint4 i = 32;
	do 
	{
		--i;		
		char buffer[256];
		int index = 256;
		do 
		{
			index--;
			buffer[index] = '\0';
		} 
		while (index);
		sprintf_s(buffer, "Quick:%2d", i);

	// 	scheduler.enqueue(new QuickSortTester(),  multithreading::noThreadPreference, buffer);	
	}
	while (i);

	/*
	real_time::Clock man_clock;
	real_time::Clock backwards;
	backwards.setRate(-2.0);
	real_time::StopWatch timer(backwards);
	cycle before = real_time::cycles();
	multithreading::sleep(3000);
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
	*/
	
	while (scheduler.hasAnyWork())
		/** empty */;


	scheduler.printState();
	printf("Stopped playing in the sandbox!\n");
 
	testVectors<real8>(1.0);
	testVectors<real4>(1.0f);
	testVectors<sint1>(1);
	testVectors<uint2>(1);

	playNumericalFunctions();

	return;
}


