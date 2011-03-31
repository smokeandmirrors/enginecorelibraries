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
#include "Signals.h"
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
	FrameRequirement(void)
	{
		m_observer.setObserver(this);
		m_observable.setObservable(this);
	}
	
	void add(Observer<FrameRequirement>* observer)
	{
		m_observable.add(observer);
	}
	
	bool isCompleted(void) const
	{
		return m_isCompleted;
	}

	virtual bool isFinishedQueueingWork(void) const=0;

	void ignore(EngineLoop* observable)
	{
		m_observer.ignore(observable);
	}

	void notice(EngineLoop* observable)=0;

	void notify(void)
	{
		m_observable.notify();
	}

	void observe(EngineLoop* observable)
	{
		m_observer.observe(observable);
	}

	virtual void queueWork(void)=0;

	void remove(Observer<FrameRequirement>* observer)
	{
		m_observable.remove(observer);
	}

protected:
	void markCompleted(void)
	{
		m_isCompleted = true;
	}

	void markIncomplete(void)
	{
		m_isCompleted = false;
	}	

private:
	bool	
		m_isCompleted;
	design_patterns::ObserverMember<EngineLoop>
		m_observer;
	design_patterns::ObservableMember<FrameRequirement>
		m_observable;
}; // class FrameRequirement

class EngineLoop
: public design_patterns::Observable<EngineLoop>
, public design_patterns::Observer<FrameRequirement>
{
	typedef std::list<FrameRequirement*>	requirements;
	typedef requirements::iterator			requirements_iter;

public:
	EngineLoop(void)
	: m_isRunning(false)
	, m_frameNumber(0)
	{
		m_observer.setObserver(this);
		m_observable.setObservable(this);
	}

	void add(design_patterns::Observer<EngineLoop>* observer)
	{
		m_observable.add(observer);
	}
	
	void addFrameRequirement(FrameRequirement* requirement)
	{
		requirement->add(this);
		add(requirement);
		m_incomplete.push_back(requirement);
	}

	uint8 getFrameNumber(void) const 
	{ 
		return m_frameNumber; 
	}

	void ignore(FrameRequirement* observable)
	{
		m_observer.ignore(observable);
	}

	bool isRunning(void) const
	{
		return m_isRunning;
	}

	void notice(FrameRequirement* observable)
	{	// really this would always be true
		synchronize(m_mutex);

		if (observable->isCompleted())
		{
			markRequirementCompleted(observable);	

			if (isFrameCompleted())
			{
				markFrameCompleted();
			}
		}
		else if (observable->isFinishedQueueingWork())
		{
			bool queue_next(false);

			for (requirements_iter iter = m_incomplete.begin(); iter != m_incomplete.end(); iter++)
			{
				if (queue_next)
				{
					(*iter)->queueWork();
					break;
				}

				if (*iter == observable)
				{
					queue_next = true;
				}
			}
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
	
	void removeFrameRequirement(FrameRequirement* requirement)
	{
		removeFromList(requirement, m_completed, m_completeMutex);
		removeFromList(requirement, m_incomplete, m_incompleteMutex);
		remove(requirement);
		requirement->remove(this);
	}
	
	void remove(design_patterns::Observer<EngineLoop>* observer)
	{
		m_observable.remove(observer);
	}

	void start(void)
	{
		synchronize(m_incompleteMutex)
		if (!m_isRunning)
		{
			m_isRunning = true;
			startFrame();	
		}
	}

	void stop(void)
	{
		if (m_isRunning)
		{
			m_isRunning = false;
			notify();
		}
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
		markRequirementsIncomplete();
		notify();
		startFrame();
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

	void startFrame(void)
	{
		if (!m_incomplete.empty())
		{
			(*m_incomplete.front()).queueWork();
		}
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
	bool							m_isRunning;
	multithreading::Mutex			m_mutex;
	design_patterns::ObservableMember<EngineLoop>		
									m_observable;
	design_patterns::ObserverMember<FrameRequirement>
									m_observer;
}; // class EngineLoop

multithreading::Mutex physicalMutex;

class Physical
: public multithreading::Executable
{
public:
	Physical(millisecond work_time, Physical* next=NULL, void(*callback)(void)=NULL)
	: m_workTime(work_time)
	, m_next(next)
	, m_callBack(callback)
	{
		/* empty */
	}
	
	void execute(void)
	{
		multithreading::sleep(m_workTime);
		
		if (m_callBack)
		{
			(*m_callBack)();
		}				

		if (m_next)
		{
			synchronize(physicalMutex)
			static bool first(true);
		
			if (first)
			{
				multithreading::Scheduler::single().enqueue(m_next, multithreading::noThreadPreference, "Phyics 1");
				first = false;
			}
			else
			{
				multithreading::Scheduler::single().enqueue(m_next, multithreading::noThreadPreference, "Phyics 2");
			}
		}
	}

protected:
	void(*		m_callBack)(void);
	Physical*	m_next;
	millisecond	m_workTime;
};

void physicsComplete(void);

Physical	physOne(1000, NULL, physicsComplete);
Physical	physTwo(2000, NULL, physicsComplete);
Physical	physThree(3000, &physOne, physicsComplete);
Physical	physFour(4000, &physTwo, physicsComplete);

class Physics 
: public FrameRequirement
{
public:
	Physics(void)
	: m_isDoneQueuingWork(false)
	{

	}

	void testMarkFunctionComplete(void)
	{
		markCompleted();
		notify();
	}

	bool isFinishedQueueingWork(void) const
	{
		return m_isDoneQueuingWork;
	}

	void notice(EngineLoop* observable)
	{
		uint8 current_frame = observable->getFrameNumber();

		if (current_frame > m_lastFrame && observable->isRunning())
		{	// queue up some work
			m_lastFrame = current_frame;
			markIncomplete();
		}
	}

	void queueWork(void)
	{
		multithreading::Scheduler::single().enqueue(&physFour, multithreading::noThreadPreference, "Physics 4");
		multithreading::Scheduler::single().enqueue(&physThree, multithreading::noThreadPreference, "Physics 3");
		m_isDoneQueuingWork = true;
		notify();
	}

private:
	bool	m_isDoneQueuingWork;
	uint8	m_lastFrame;
}; // class Physics


Physics		physics;
uint1		physicsCompletions(0);
multithreading::Mutex physicsMutex;

void physicsComplete(void)
{
	synchronize(physicsMutex);

	physicsCompletions++;

	if (physicsCompletions == 4)
	{
		physics.testMarkFunctionComplete();
		physicsCompletions=0;
	}
}


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

		for (number=0; number < number_size; number++)
		{
			*i++ = number;
		}

		for (number=0; number < number_sort; number++)
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
sint4 numberOfThreads=0;

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
	
	for (number=0; number < number_size; number++)
	{
		*i++ = number;
	}

	for (number=0; number < number_sort; number++)
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
//	for (number=0; number < number_size; number++)
//	{
//		*i++ = number;
//	}
//
//	for (number=0; number < number_sort; number++)
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
	
	for (uint4 i=0; i < num_threads; i++)
	{
		uint4 thread_id1;
		HANDLE thread = (HANDLE)(_beginthreadex(NULL, 0, useMutexClass, NULL, CREATE_SUSPENDED, &thread_id1));
		// HANDLE thread = (HANDLE)(_beginthreadex(NULL, 0, doubleQuickSort, NULL, CREATE_SUSPENDED, &thread_id1));
		threads.push_back(thread);
	}

	for (uint4 i=0; i < num_threads; i++)
	{
		ResumeThread(threads[i]);
	}
	
	multithreading::sleep(3000);

	for (uint4 i=0; i < num_threads; i++)
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

	for (number=0; number < number_size; number++)
	{
		*i++ = number;
	}

	for (number=0; number < number_sort; number++)
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
	/*
	real8 f8(0);
	real4 f4(0);
	sint8 si8(0);
	sint4 si4(0);
	
	printf("%f", math::abs<real8>(f8));
	printf("%f", math::ln<real4>(f4));
	printf("%f", abs(f8));
	printf("%f", abs(f4));	
	printf("%d", math::abs<sint4>(si4));
	printf("%d", math::abs<sint8>(si8));
	*/
}

template<typename OWNER>
class Component
{
public:
	static uint4 
		getComponentID(void); // return __COUNTER__; ???

	Component<OWNER>*
		addShared(void);

	void 
		attachTo(OWNER& owner);
	
	void 
		detach(void);
	
	const OWNER* 
		getOwner(void) const;

private:
	OWNER*	m_owner;
}; // Component
 
template<typename OWNER>
class Composite // interface/base/member
{
public:
	void add(Component<OWNER>* component);
	void remove(Component<OWNER>* component);
	
	template<typename COMPONENT>
	COMPONENT* get(bool construct=false)
	{
		uint4 id = COMPONENT::getComponentID();
		// if (container[id]) =
		return NULL;
	}

	template<typename COMPONENT>
	bool hasA(void)
	{
		uint4 id = COMPONENT::getComponentID();
		return false;
	}

}; // Composite



using namespace signals;

class Switch
{
public:
	Transmitter0				delegate0;
	Transmitter1<sint4>			delegate1;
	Transmitter2<sint4, real4>	delegate2;
	
	void run(void)
	{
		delegate0();
	}

	void run(sint4 how_much)
	{
		delegate1(how_much);
	}

	void run(sint4 how_many_ints, real4 how_many_floats)
	{
		delegate2(how_many_ints, how_many_floats);
	}	
};

class Switch2
{
public:
	template<class RECEIVER>
	void connect(RECEIVER* receiver, void (RECEIVER::* function)(void))
	{
		delegate0.connect(receiver, function);
	}

	template<class RECEIVER>
	void connect(RECEIVER* receiver, void (RECEIVER::* function)(void) const)
	{
		delegate0.connect(receiver, function);
	}

	void disconnect(Receiver* receiver)
	{
		delegate0.disconnect(receiver);
	}

	void run(void)
	{
		delegate0();
	}

private:
	Transmitter0 delegate0;
};

class Light : public ReceiverBase
{
public:
	void turnOff(void)			{ printf("Turned Off!\n"); }
	void setWatts(sint4 watts)	{ printf("Set watts to %d\n", watts); }
	void calibrate(sint4 watts, real4 luminosity) 
	{
		printf("Set watts to %d and luminosity to %f\n", watts, luminosity);
	}
};

class Microwave : public Receiver
{
public:
	void turnOff(void) const	{ printf("Microwave turned Off!\n"); }
	void setWatts(sint4 watts)	{ printf("Microwave set watts to %d\n", watts); }
	void calibrate(sint4 watts, real4 luminosity) 
	{
		printf("Microwave Set watts to %d and luminosity to %f\n", watts, luminosity);
	}

	void disconnect(void)
	{
		m_receiver.disconnect();
	}

	void onConnect(Transmitter* sender)
	{
		m_receiver.onConnect(sender);
	}

	void onDisconnect(Transmitter* sender)
	{
		m_receiver.onDisconnect(sender);
	}
protected:

private:
	signals::ReceiverMember m_receiver;
};

class Foo
{
public:
	void bar(void)
	{}
};

void sandbox::play()
{
	printf("Playing in the sandbox!\n");	
	Switch switch1;
	Microwave microwave;
	Light light;
	Switch2 switch2;

	Microwave* delete_microwave = new Microwave();;
	Light* delete_light = new Light();
	
	switch2.connect(&microwave, &Microwave::turnOff);
	switch2.connect(delete_microwave, &Microwave::turnOff);
	
	switch1.delegate0.connect(&light, &Light::turnOff);
	switch1.delegate0.connect(delete_light, &Light::turnOff);
	switch1.delegate1.connect(&light, &Light::setWatts);
	switch1.delegate2.connect(&light, &Light::calibrate);
	switch1.delegate0.connect(&microwave, &Microwave::turnOff);
	switch1.delegate0.connect(delete_microwave, &Microwave::turnOff);
	switch1.delegate1.connect(&microwave, &Microwave::setWatts);
	switch1.delegate2.connect(&microwave, &Microwave::calibrate);
	
	switch2.run();
	
	switch1.run();
	switch1.run(5);
	delete delete_microwave;
	delete delete_light;

	Switch* delete_switch = new Switch();
	delete_switch->delegate0.connect(&light, &Light::turnOff);
	delete_switch->delegate0.connect(&microwave, &Microwave::turnOff);
	delete_switch->run();
	delete_switch->delegate0.disconnect(&light);
	delete delete_switch;
	

	// compiler_checks::sizeOfChecks();
	// compiler_checks::execute();
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

	EngineLoop loop;
	
	loop.addFrameRequirement(&physics);
	loop.start();

	while (loop.getFrameNumber() < 4)
	{

	};

	loop.stop();

	return;
}

