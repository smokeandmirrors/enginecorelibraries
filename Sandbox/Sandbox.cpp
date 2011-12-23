#include <list>
#include <map>
#include <queue>
#if WIN32
#include <process.h>
#endif//WIN32
#include <stdio.h>
#include <sstream>
#include <tchar.h>
#include <typeinfo>
#include <vector>
#if WIN32
#include <windows.h>
#endif//WIN32

#include "Platform.h"
#include "CompilerChecks.h"
#include "Composition.h"
#include "Concurrency.h"
#include "RedBlackTree.h"
#include "Sandbox.h"
#include "Scheduling.h"
#include "Synchronization.h"
#include "Signals.h"

#include "Thread.h"
#include "Time.h"
#include "UnitTestVerification.h"
#include "Vector.h"

// using namespace algorithms;
using namespace containers;
using namespace concurrency;
using namespace designPatterns;
using namespace realTime;

template<typename NUMBER>
NUMBER getRand(NUMBER min, NUMBER max) 
{
	PREVENT_COMPILE
}

template<>
sint getRand(sint min, sint max) 
{
	return (rand() % (max - min)) + min;
}

template<>
sreal getRand(sreal min, sreal max) 
{
	const sreal v = getRand<sint>(0, RAND_MAX)*( 1.0f / RAND_MAX); 
	return v * (max - min) + min;
}

void onPlay(void);

void sandbox::play()
{
	compilerChecks::check();
	printf("Playing in the sandbox!\n");
	onPlay();
	printf("Stopped playing in the sandbox!\n");
}

sint sintCompareAscending(const void* a, const void* b)	{ return (*(sint*)(a)) - (*(sint*)(b)); }
sint sintCompareDescending(const void* a, const void* b)	{ return (*(sint*)(b)) - (*(sint*)(a)); }

inline void doWork(millisecond milliseconds)
{
	sint number_size = 1000;
	sint numbers[1000];// = new sint[number_size];
	sint* i = numbers;
	
	for (sint number = 0; number < number_size; number++)
	{
		*i++ = number;
	}

	millisecond start = realTime::milliseconds();
		
	do 
	{
		qsort(numbers, number_size, sizeof(uint), &sintCompareAscending);	
		qsort(numbers, number_size, sizeof(uint), &sintCompareDescending);	
	}
	while (realTime::milliseconds() - start < milliseconds); // delete[] numbers;
}

void doWork3(void) { doWork(3000); }
void doWork4(void) { doWork(4000); }
void doWork5(void) { doWork(5000); }
void doWork10(void) { doWork(10000); }

void simpleChildrenPre(void)
{
	doWork3();
	Executor* one = new Executor(&doWork3);
	Scheduler::single().enqueue(*one);
}

void simpleChildrenPost(void)
{
	Executor* one = new Executor(&doWork3);
	Scheduler::single().enqueue(*one);
	doWork3();
}

void doWork1Children(void)
{
	Executor* one = new Executor(&doWork3);
	Scheduler::single().enqueue(*one);
	doWork3();
}

void doWork2Children(void)
{
	Executor* one = new Executor(&doWork1Children);
	Executor* two = new Executor(&doWork1Children);
	Scheduler::single().enqueue(*one);
	Scheduler::single().enqueue(*two);
	doWork3();
}

void doWork3Children(void) 
{
	Executor* one = new Executor(&doWork2Children);
	Executor* two = new Executor(&doWork2Children);
	Executor* three = new Executor(&doWork2Children);
	Scheduler::single().enqueue(*one);
	Scheduler::single().enqueue(*two);
	Scheduler::single().enqueue(*three);
	doWork3();
}

typedef enum  
{
	eFR_AI=0,
	eFR_Animation,
	eFR_Audio,
	eFR_Events,
	eFR_Gameplay,
	eFR_GarbageCollection,
	eFR_Lighting,
	eFR_Networking,
	eFR_PhysicsAsync,
	eFR_PhysicsSync,
	eFR_Rendering,
} 
eFrameRequirementID; 

const char* 
frameReqName(eFrameRequirementID frameReqID)
{
	switch (frameReqID)
	{
		case eFR_AI: 
			return "A. I...."; 
		case eFR_Animation: 
			return "Animate."; 
		case eFR_Audio: 
			return "AudioFX."; 
		case eFR_Events: 
			return "Events.."; 
		case eFR_Gameplay: 
			return "Gameplay"; 
		case eFR_GarbageCollection: 
			return "GarbageC"; 
		case eFR_Lighting: 
			return "Lighting"; 
		case eFR_Networking: 
			return "Network."; 
		case eFR_PhysicsAsync: 
			return "PhysicsA"; 
		case eFR_PhysicsSync: 
			return "PhysicsS"; 
		case eFR_Rendering: 
			return "VisualFX";
		default:
			assert(false);
			return NULL;
	};
}

std::string 
getFormattedName(eFrameRequirementID frameReqID, sint completedJobs, sint maxJobs)
{
	std::stringstream namestream;
	namestream << frameReqName(frameReqID);
	namestream << "(";
	if (completedJobs < 10)
		namestream << " ";
	namestream << (completedJobs + 1);
	namestream << " / ";
	if (maxJobs < 10)
		namestream << " ";
	namestream << maxJobs;
	namestream << ")";
	return namestream.str();
}

class EngineLoop;
class FrameRequirement;

// make an interface
class FrameRequirement
: public signals::Transmitter1<FrameRequirement*>
, public signals::Receiver
{
public:
	FrameRequirement(void)
	{
		m_receiver.setReceiver(this);
	}

	virtual ~FrameRequirement(void) 
	{

	}

	void ceaseReception(void)
	{
		m_receiver.ceaseReception();
	}

	void ceaseTransmission(void)
	{
		m_onComplete.ceaseTransmission();
	}
	
	void noticeNextFrame(EngineLoop*)
	{
		
	}

	template<class RECEIVER>
	void onCompleteConnect(RECEIVER* receiver, void (RECEIVER::* function)(FrameRequirement*))
	{
		m_onComplete.connect(receiver, function);
	}

	template<class RECEIVER>
	void onCompleteConnect(RECEIVER* receiver, void (RECEIVER::* function)(FrameRequirement*) const)
	{
		m_onComplete.connect(receiver, function);
	}

	void onCompleteDisconnect(signals::Receiver* receiver)
	{
		m_onComplete.disconnect(receiver);
	}

	void onConnect(signals::Transmitter* sender)
	{
		m_receiver.onConnect(sender);
	}

	void onDisconnect(signals::Transmitter* sender)
	{
		m_receiver.onDisconnect(sender);
	}

	virtual void getInitialRequiredWork(std::queue<Executor*>& work)=0;

protected:	
	void notifyComplete(void) 
	{
		m_onComplete(this);
	}
	
private:
	bool	
		m_isCompleted;
	
	signals::ReceiverMember	
		m_receiver;
	
	signals::Transmitter1<FrameRequirement*> 
		m_onComplete;
}; // class FrameRequirement

class EngineLoop
: public signals::Transmitter1<EngineLoop*>
, public signals::Receiver
{
	typedef std::list<FrameRequirement*>	requirements;
	typedef requirements::iterator			requirements_iter;

public:
	EngineLoop(void)
	: m_isRunning(false)
	, m_frameNumber(0)
	{
		m_receiver.setReceiver(this);
	}

	virtual ~EngineLoop(void) 
	{

	}

	void addFrameRequirement(FrameRequirement* requirement)
	{
		SYNC(m_mutex);
		m_onComplete.connect(requirement, &FrameRequirement::noticeNextFrame);
		requirement->onCompleteConnect(this, &EngineLoop::noticeComplete);
		m_incomplete.push_back(requirement);
	}

	void ceaseReception()
	{
		m_receiver.ceaseReception();
	}

	void ceaseTransmission()
	{
		m_onComplete.ceaseTransmission();
	}

	template<class RECEIVER>
	void connect(RECEIVER* receiver, void (RECEIVER::* function)(FrameRequirement*))
	{
		m_onComplete.connect(receiver, function);
	}

	template<class RECEIVER>
	void connect(RECEIVER* receiver, void (RECEIVER::* function)(FrameRequirement*) const)
	{
		m_onComplete.connect(receiver, function);
	}

	void disconnect(signals::Receiver* receiver)
	{
		m_onComplete.disconnect(receiver);
	}

	ulong getFrameNumber(void) const 
	{ 
		return m_frameNumber; 
	}

	bool isRunning(void) const
	{
		return m_isRunning;
	}
	
	void noticeComplete(FrameRequirement* requirement)
	{
		SYNC(m_mutex);
		markRequirementCompleted(requirement);	

		if (isFrameCompleted())
		{
			markFrameCompleted();
		}
	}
	
	void onConnect(signals::Transmitter* sender)
	{
		m_receiver.onConnect(sender);
	}

	void onDisconnect(signals::Transmitter* sender)
	{
		m_receiver.onDisconnect(sender);
	}

	void removeFrameRequirement(FrameRequirement* requirement)
	{
		SYNC(m_mutex);
		m_onComplete.disconnect(requirement);
		removeFromList(requirement, m_completed, m_completeMutex);
		removeFromList(requirement, m_incomplete, m_incompleteMutex);
	}
	
	void start(void)
	{
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
		}
	}

protected:
	void addToList(FrameRequirement* req, requirements& reqs_list, concurrency::Mutex& mutex)
	{
		SYNC(mutex)
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
	}
	
	void markRequirementCompleted(FrameRequirement* requirement)
	{
		removeFromList(requirement, m_incomplete, m_incompleteMutex);
		addToList(requirement, m_completed, m_completeMutex);
	}
	
	void markRequirementsIncomplete(void)
	{
		SYNC(m_completeMutex)
		SYNC(m_incompleteMutex)
		assert(m_incomplete.empty());
		m_incomplete = m_completed;
		m_completed.resize(0);
		assert(m_completed.empty());
	}

	void removeFromList(FrameRequirement* req, requirements& reqs_list, concurrency::Mutex& mutex)
	{
		SYNC(mutex)
		for (requirements_iter iter = reqs_list.begin(); iter != reqs_list.end(); iter++)
		{
			if (*iter == req)
			{
				reqs_list.erase(iter);
				return;
			}
		}
	}

	void startFrame(void)
	{
		int frame(0);
		realTime::ClockReal realClock;
		realTime::Stopwatch timer(realClock);
		timer.start();
		bool forever = true;

		while (forever) // should continue
		{
			timer.reset();
			std::queue<Executor*> work;
			{
				SYNC(m_incompleteMutex)
				requirements_iter iter = m_incomplete.begin();
				requirements_iter sentinel = m_incomplete.end();

				while (iter != sentinel)
				{
					(*iter)->getInitialRequiredWork(work);
					iter++;
				}
			}
			
			frame++;
			Scheduler::single().enqueueAndWaitOnChildren(work);
			printf("Frame %5d COMPLETE in %f!\n", frame, timer.milliseconds());
		}
	}

private:
	requirements					m_completed;
	DECLARE_MUTEX(m_completeMutex);
	ulong							m_frameNumber;
	requirements					m_incomplete;
	DECLARE_MUTEX(m_incompleteMutex);
	bool							m_isRunning;
	DECLARE_MUTEX(m_mutex);
	signals::Transmitter1<EngineLoop*>			
									m_onComplete;
	signals::ReceiverMember	
									m_receiver;
}; // class EngineLoop

class TestRequirement;

class TestJob
: public concurrency::Executable
{
public:
	TestJob(TestRequirement* requirement);
	
	virtual ~TestJob(void) 
	{ /* empty */ }
	
	void TestJob::execute(void);
	
	const std::string &toString(void) const
	{
		return m_name;
	}

protected:
	TestJob();

private:
	TestRequirement*	
		m_requirement;

	std::string
		m_name;
};

class TestRequirement 
: public FrameRequirement
{
public:
	TestRequirement(millisecond work_time, eFrameRequirementID ID_one, sint child_jobs)
	: m_reqID(ID_one)
	, m_workTime(work_time)
	, m_childJobs(child_jobs)
	{
		// time adjustment testing
		m_workTime *= 0.1f;
		m_childJobs *= static_cast<sint>(0.1f);
		m_originalJob = new TestJob(this);
	}

	virtual 
	~TestRequirement(void)
	{
	}

	inline eFrameRequirementID
	getID(void) const
	{
		return m_reqID;
	}

	inline millisecond
	getWorkTime(void) const
	{ 
		return m_workTime;
	}

	void 
	noticeTestJobComplete(TestJob* job, bool& spawn_new, bool& delete_self, sint& jobNumber, sint& maxNumber)
	{
		SYNC(m_mutex);
		++m_completedJobs;
		delete_self = job != m_originalJob;

		jobNumber = m_completedJobs;
		maxNumber = m_childJobs;

		if (m_completedJobs >= m_childJobs)
		{
			notifyComplete();
			spawn_new = false;
		}
		else
		{
			spawn_new = true;
		}
	}

	void getInitialRequiredWork(std::queue<Executor*>& work)
	{
		m_completedJobs = 0;
		std::string name = getFormattedName(m_reqID, m_completedJobs, m_childJobs);
		Executor* executor = new concurrency::Executor(m_originalJob, name);
		work.push(executor);
	}

private:
	DECLARE_MUTEX(m_mutex);
	
	sint					
		m_completedJobs;

	TestJob*
		m_originalJob;
	
	eFrameRequirementID 
		m_reqID;
	
	millisecond
		m_workTime;

	sint
		m_childJobs;
}; 

void TestJob::execute(void)
{
	doWork(m_requirement->getWorkTime());
	bool spawn_new;
	bool delete_self;
	sint maxJobs;
	sint jobNumber;
	m_requirement->noticeTestJobComplete(this, spawn_new, delete_self, jobNumber, maxJobs);
	
	if (spawn_new)
	{
		std::string name = getFormattedName(m_requirement->getID(), jobNumber, maxJobs);
		TestJob* job = new TestJob(m_requirement);
		concurrency::Executor* executor = new concurrency::Executor(job, name);
		concurrency::Scheduler::single().enqueue(*executor);
	}

	if (delete_self)
	{
		delete this;
	}
}

TestJob::TestJob(TestRequirement* requirement)
: m_requirement(requirement)
, m_name(frameReqName(requirement->getID()))
{ /* empty */ }

class Agent 
: public Composite<Agent>
{
public:

};

class VisualFX
: public Composite<VisualFX>
{

};

class Movement
: public Component<Agent, Movement>
{
};

class Attack
: public Component<Agent, Attack>
{
public:

};

class Defense
: public Component<Agent, Defense>
{

};

class Shadows
: public Component<VisualFX, Shadows>
{

};

void testEngineLoop(void)
{
	EngineLoop loop;	
	
	TestRequirement physics_sych(8, eFR_PhysicsSync, 5);
	loop.addFrameRequirement(&physics_sych);
	TestRequirement physics_asych(4, eFR_PhysicsAsync, 10);
	loop.addFrameRequirement(&physics_asych);
	TestRequirement rendering(6, eFR_Rendering, 40);
	loop.addFrameRequirement(&rendering);
	TestRequirement lighting(4, eFR_Lighting, 30);
	loop.addFrameRequirement(&lighting);
	TestRequirement animation(3, eFR_Animation, 20);
	loop.addFrameRequirement(&animation);
	TestRequirement audio(2, eFR_Audio, 40);
	loop.addFrameRequirement(&audio);
	TestRequirement events(1, eFR_Events, 5);
	loop.addFrameRequirement(&events);
	TestRequirement gameplay(1, eFR_Gameplay, 5);
	loop.addFrameRequirement(&gameplay);
	TestRequirement ai(1, eFR_AI, 30);
	loop.addFrameRequirement(&ai);
	TestRequirement garbage_collection(2, eFR_GarbageCollection, 2);
	loop.addFrameRequirement(&garbage_collection);
	TestRequirement networking(2, eFR_Networking, 4);
	loop.addFrameRequirement(&networking);
	
	loop.start();
	loop.stop();
}

// #include <map>

void onPlay(void)
{
	sandbox::verifyUnitTests();
	sandbox::tableRnD();

	// concurrency::Thread[] runUs = new concurrency::Thread[];
	/*
	concurrency::Executor* executor(NULL);
	executor = new concurrency::Executor(&doWork3);
	concurrency::Thread* runMe = concurrency::Thread::getExecuting(*executor);
	concurrency::Thread::waitOnCompletion(*runMe);
	concurrency::Thread::waitOnCompletion(*runMe);
	delete runMe;
	
	executor = new concurrency::Executor(&doWork3);
	concurrency::Scheduler::single().enqueueAndWait(*executor);
	printf("Waited Scheduler\n");
	
	
	
	executor = new concurrency::Executor(&doWork3);
	concurrency::Thread* runMeAndWait = concurrency::Thread::getExecuting(*executor);
	concurrency::Thread::waitOnCompletion(*runMeAndWait);
	delete runMeAndWait;
	printf("Waited Thread\n");

	
	std::vector<concurrency::Thread*> threads;
	uint numThreads(32);
	for (uint i = 0; i < numThreads; i++)
	{
		executor = new concurrency::Executor(&doWork3);
		concurrency::Thread* waitable = concurrency::Thread::getExecuting(*executor);
		threads.push_back(waitable);
	}

	concurrency::Thread::waitOnCompletion(threads);
	printf("Waiting for 32 threads\n");

	for (uint i = 0; i < numThreads; i++)
	{
		delete threads[i];
	}
	
	Executor* original = new Executor(&doWork3Children);
	Scheduler::single().enqueueAndWaitOnChildren(*original);
	// Executor* original = new Executor(&simpleChildrenPost);
	// Scheduler::single().enqueueAndWaitOnChildren(*original);
	printf("Nice!  That was awesome!");
	*/
	// Thread* runMe = new Thread*[];


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

	// RedBlackTree<sint> rbt;
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

	testEngineLoop();
	
// 	for (int i = 0; i < 10000; i++)
// 	{
// 		randomNumber = numbers[i];
// 		assert(rbt.getSize() == sum);
// 		assert(rbt.has(randomNumber));
// 		rbt.remove(randomNumber);
// 		sum--;
// 		assert(rbt.getSize() == sum);
// 		/*
// 		assert(!rbt.has(-101));
// 		assert(!rbt.has(101));
// 		assert(rbt.getMax() <= 100);
// 		assert(rbt.getMin() >= -100);		
// 		*/
// 	}
// 
// 	assert(rbt.isEmpty());
}

// 	Agent alpha;
// 	Movement movement;
// 	Attack attack;
// 	Defense defense;
// 	alpha.add(movement);
// 	alpha.add(attack);
// 
// 	uint movement_ID = movement.getGUID();
// 	uint static_movement_ID = Movement::componentGUID;
// 	uint attack_ID = attack.getGUID();
// 	uint static_attack_ID = Attack::componentGUID;
// 	uint defense_ID = defense.getGUID();
// 	uint static_defense_ID = Defense::componentGUID;
// 
// 	uint one = __COUNTER__;
// 	uint two = __COUNTER__;
// 	uint three = __COUNTER__;
// 
// 	std::map<type_info, sint> crazytalk;
// 	
// 	
// 	int idone = typeid(Movement).before(typeid(Movement));
// 	int MbeforeA = typeid(Movement).before(typeid(Attack));
// 	int AbeforeM = typeid(Attack).before(typeid(Movement));
// 
// 	if (typeid(Movement) == typeid(Attack))
// 	{
// 		printf("sweet");
// 	}
// 	else
// 	{
// 		printf("awesome");
// 	}
// 
// 	assert(alpha.has<Movement>());
// 	assert(alpha.has<Attack>());
// 	assert(!alpha.has<Defense>());
// 	assert(&movement == alpha.get<Movement>());
// 	assert(&attack == alpha.get<Attack>());
// 	assert(NULL == alpha.get<Defense>());
// 	alpha.remove(movement);
// 	assert(!alpha.has<Movement>());
// 	assert(NULL == alpha.get<Movement>());
// 	alpha.remove(attack);
// 	assert(!alpha.has<Attack>());
// 	assert(NULL == alpha.get<Attack>());
// 
// 	
// 	ClockReal realSingle;
// 	ClockReal realDouble;
// 	ClockRelative relative(realSingle);