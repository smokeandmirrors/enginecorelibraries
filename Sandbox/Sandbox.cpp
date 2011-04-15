#include <list>
#include <map>
#include <stdio.h>
#include <tchar.h>
#include <vector>

#if WIN32
#include <process.h>
#include <windows.h>
#endif//WIN32

#include "Build.h"
#include "CompilerChecks.h"
#include "Sandbox.h"
#include "Scheduling.h"
#include "Synchronization.h"
#include "Signals.h"
#include "Threads.h"
#include "Time.h"
#include "Vector.h"

sint4 sintCompareAscending(const void* a, const void* b)	{ return (*(sint4*)(a)) - (*(sint4*)(b)); }
sint4 sintCompareDescending(const void* a, const void* b)	{ return (*(sint4*)(b)) - (*(sint4*)(a)); }

inline void doWork(millisecond milliseconds)
{
	sint4 number_size = 1000;
	sint4 numbers[1000];// = new sint4[number_size];
	sint4* i = numbers;
	
	for (sint4 number = 0; number < number_size; number++)
	{
		*i++ = number;
	}

	millisecond start = real_time::milliseconds();
		
	do 
	{
		qsort(numbers, number_size, sizeof(uint4), &sintCompareAscending);	
		qsort(numbers, number_size, sizeof(uint4), &sintCompareDescending);	
	}
	while (real_time::milliseconds() - start < milliseconds);

	// delete[] numbers;
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
		m_onQueuedWork.ceaseTransmission();
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

	template<class RECEIVER>
	void onQueuedWorkConnect(RECEIVER* receiver, void (RECEIVER::* function)(FrameRequirement*))
	{
		m_onQueuedWork.connect(receiver, function);
	}

	template<class RECEIVER>
	void onQueuedWorkConnect(RECEIVER* receiver, void (RECEIVER::* function)(FrameRequirement*) const)
	{
		m_onQueuedWork.connect(receiver, function);
	}

	void onQueuedWorkDisconnect(signals::Receiver* receiver)
	{
		m_onQueuedWork.disconnect(receiver);
	}

	void queueWork(void)
	{
		onQueueWork();
		m_onQueuedWork(this);
	}

protected:	
	void notifyComplete(void) 
	{
		m_onComplete(this);
	}

	virtual void onQueueWork(void)=0;
	
private:
	bool	
		m_isCompleted;
	
	signals::ReceiverMember	
		m_receiver;
	
	signals::Transmitter1<FrameRequirement*> 
		m_onComplete;

	signals::Transmitter1<FrameRequirement*> 
		m_onQueuedWork;
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
		requirement->onQueuedWorkConnect(this, &EngineLoop::noticeWorkQueued);
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

	uint8 getFrameNumber(void) const 
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
	
	void noticeWorkQueued(FrameRequirement* requirement)
	{
		SYNC(m_mutex);
		bool queue_next(false);
		requirements_iter iter = m_incomplete.begin(); 
		requirements_iter sentinel = m_incomplete.end();
		
		while (iter != sentinel)
		{
			if (queue_next)
			{
				(*iter)->queueWork();
				break;
			}

			if (*iter == requirement)
			{
				queue_next = true;
			}

			++iter;
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
		SYNC(m_incompleteMutex)
		
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
	void addToList(FrameRequirement* req, requirements& reqs_list, multithreading::Mutex& mutex)
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
		if (isRunning())
		{
			m_frameNumber++;
			markRequirementsIncomplete();
			startFrame();
		}
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

	void removeFromList(FrameRequirement* req, requirements& reqs_list, multithreading::Mutex& mutex)
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
		if (!m_incomplete.empty())
		{
			(*m_incomplete.front()).queueWork();
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
	signals::Transmitter1<EngineLoop*>			
									m_onComplete;
	signals::ReceiverMember	
									m_receiver;
}; // class EngineLoop

class TestRequirement;

class TestJob
: public multithreading::Executable
{
public:
	TestJob(TestRequirement* requirement)
	: m_requirement(requirement)
	{ /* empty */ }
	
	virtual ~TestJob(void) 
	{ /* empty */ }
	
	void TestJob::execute(void);
	
protected:
	TestJob();

private:
	TestRequirement*	
		m_requirement;
};

class TestRequirement 
: public FrameRequirement
{
public:
	TestRequirement(millisecond work_time, eFrameRequirementID ID_one, sint4 child_jobs)
	: m_reqID(ID_one)
	, m_workTime(work_time)
	, m_childJobs(child_jobs)
	{
		// weird testing
		m_workTime *= 100;
		// end weird testing
		m_original = new TestJob(this);
	}

	virtual 
	~TestRequirement(void)
	{
		delete m_original;
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
	noticeTestJobComplete(TestJob* job, bool& spawn_new, bool& delete_self)
	{
		SYNC(m_mutex);
		++m_completedJobs;
		delete_self = job != m_original;

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

	void onQueueWork(void)
	{
		m_completedJobs = 0;
		std::string name = frameReqName(m_reqID);
		name += "(o)";
		multithreading::Scheduler::single().enqueue(m_original, multithreading::noThreadPreference, name.c_str());
	}

private:
	multithreading::Mutex 
		m_mutex;
	
	sint4					
		m_completedJobs;

	TestJob* 
		m_original;
	
	eFrameRequirementID 
		m_reqID;
	
	millisecond
		m_workTime;

	sint4
		m_childJobs;
}; 

void TestJob::execute(void)
{
	doWork(m_requirement->getWorkTime());
	bool spawn_new;
	bool delete_self;
	m_requirement->noticeTestJobComplete(this, spawn_new, delete_self);
	
	if (spawn_new)
	{
		std::string name = frameReqName(m_requirement->getID());
		name += "(c)";
		TestJob* job = new TestJob(m_requirement);
		multithreading::Scheduler::single().enqueue(job, multithreading::noThreadPreference, name.c_str());
	}

	if (delete_self)
	{
		delete this;
	}
}

class Agent;

class Ability
{
public:
	Ability(void)
	: m_agent(NULL)
	{

	}

	virtual 
	~Ability(void)
	{
		/* empty */
	}

	virtual 
	uint4 
	getAbilityID(void) const=0;

	void 
	attachTo(Agent* agent)
	{
		assert(agent);
		m_agent = agent;
		onAttachTo();
	}

	void 
	detach(void)
	{
		onDetach();
		m_agent = NULL;
	}

	const Agent* 
	getAgent(void) const
	{
		return m_agent;
	}

protected:
	virtual 
	void 
	onAttachTo(void)
	{
		/* empty */
	}

	virtual 
	void 
	onDetach(void)
	{
		/* empty */
	}

private:
	const Agent* m_agent;
};

class Agent
{
	typedef std::map< uint4, Ability* > 
		abilities;

	typedef abilities::iterator 
		abilities_iter;

	typedef std::pair<const uint4, Ability* > 
		abilities_pair;
public:
	void
	add(Ability* ability)
	{
		uint4 id = ability->getAbilityID();

		if (!m_abilities[id])
		{
			m_abilities[id] = ability;
			ability->attachTo(this);
		}
	}
	
	template<typename ABILITY>
	ABILITY* 
	get(bool construct_missing=false)
	{
		uint4 id = ABILITY::staticGetAbilityID();
		Ability* ability = m_abilities[id];

		if (!ability && construct_missing)
		{
			ability = new ABILITY();
			ability->attachTo(this);
		}

		return static_cast<ABILITY*>(ability);	
	}

	template<typename ABILITY>
	bool
	has(void) const
	{
		return m_abilities.find(ABILITY::staticGetAbilityID()) != m_abilities.end();
	}

	void
	remove(Ability* ability)
	{
		abilities_iter iter = m_abilities.find(ability->getAbilityID());

		if (iter != m_abilities.end())
		{
			m_abilities.erase(iter);
		}
	}

private:
	abilities	
		m_abilities;	
};

class Attack : public Ability
{
public:
	static 
	uint4 
	staticGetAbilityID(void)
	{
		return __COUNTER__;
	}

	uint4
	getAbilityID(void) const
	{
		return Attack::staticGetAbilityID();
	}

protected:

private:

};

class Navigation : public Ability
{
public:
	static 
	uint4 
	staticGetAbilityID(void)
	{
		return __COUNTER__;
	}

	uint4
	getAbilityID(void) const
	{
		return Navigation::staticGetAbilityID();
	}

protected:

private:

};

template<typename OWNER>
class Component
{
public:
	static 
	uint4 
	staticGetComponentID(void)
	{ 
		return __COUNTER__;
	}

	virtual
	~Component(void)
	{
		/* empty */
	}

	void 
	attachTo(OWNER& owner)
	{
		m_owner = &owner;
		onAttachTo();
	}
	
	void 
	detach(void)
	{
		onDetach();
		m_owner = NULL;
	}
	
	uint4 
	getComponentID(void) const
	{
		return staticGetComponentID();
	}

	const OWNER* 
	getOwner(void) const
	{
		return m_owner;
	}

protected:
	virtual 
	void 
	onAttachTo(void)
	{
		/* empty */
	}

	virtual 
	void 
	onDetach(void)
	{
		/* empty */
	}

private:
	OWNER*	m_owner;
}; // Component
 
class TAttack : public Component<Agent>
{

};

/*
template<typename OWNER>
class Composite // interface/base/member
{
	typedef std::map< uint4, Component<OWNER>* > 
		components;
	
	typedef components::iterator 
		components_iter;

	typedef std::pair<const uint4, Component<OWNER>* > 
		components_pair;
	
public:
	void
	add(Component<OWNER>* component) 
	{
		uint4 id = component->getComponentID();

		if (!m_components[id])
		{
			m_components[id] = component;
		}
	}
	
	template<typename COMPONENT> 
	COMPONENT* 
	get(bool construct_missing=false)
	{
		uint4 id = COMPONENT::getComponentID();
		COMPONENT* component = m_components[id];
		
		if (!component && construct_missing)
		{
			component = new COMPONENT<OWNER>();
			component->attachTo(this);
		}

		return component;
	}

	template<typename COMPONENT>
	bool 
	hasA(void)
	{
		uint4 id = COMPONENT::getComponentID();
		return false;
	}
	
	void 
	remove(Component<OWNER>* component)
	{
		components_iter iter = m_components.find(component->getComponentID());
		
		if (iter != m_components.end())
		{
			m_components.erase(iter);
		}
	}
	
private:
	components	
		m_components;
}; // Composite
*/

void sandbox::play()
{
	printf("Playing in the sandbox!\n");	
	
	Agent agent;
	agent.add(new Navigation());
	Navigation* nav = agent.get<Navigation>();
	assert(nav->getAgent() == &agent);
	assert(!agent.has<Attack>());
	assert(agent.get<Attack>(true));

	EngineLoop loop;	
	TestRequirement physics_sych(8, eFR_PhysicsSync, 0);
	loop.addFrameRequirement(&physics_sych);
	TestRequirement physics_asych(4, eFR_PhysicsAsync, 1);
	loop.addFrameRequirement(&physics_asych);
	TestRequirement rendering(6, eFR_Rendering, 4);
	loop.addFrameRequirement(&rendering);
	TestRequirement lighting(4, eFR_Lighting, 3);
	loop.addFrameRequirement(&lighting);
	TestRequirement animation(3, eFR_Animation, 2);
	loop.addFrameRequirement(&animation);
	TestRequirement audio(2, eFR_Audio, 4);
	loop.addFrameRequirement(&audio);
	TestRequirement events(1, eFR_Events, 0);
	loop.addFrameRequirement(&events);
	TestRequirement gameplay(1, eFR_Gameplay, 0);
	loop.addFrameRequirement(&gameplay);
	TestRequirement ai(1, eFR_AI, 30);
	loop.addFrameRequirement(&ai);
	TestRequirement garbage_collection(2, eFR_GarbageCollection, 0);
	loop.addFrameRequirement(&garbage_collection);
	TestRequirement networking(2, eFR_Networking, 4);
	loop.addFrameRequirement(&networking);
	loop.start();

	while (loop.getFrameNumber() < 2)
	{
		multithreading::sleep(3000);
	};

	loop.stop();

	while (multithreading::Scheduler::single().hasAnyWork())
	{
		multithreading::sleep(3000);
	}	

	printf("Stopped playing in the sandbox!\n");
	multithreading::Scheduler::single().destroy();
	return;
}

