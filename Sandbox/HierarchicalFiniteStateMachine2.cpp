#include "Composition.h"
#include "HierarchicalFiniteStateMachine2.h"

using namespace HFSM2;
using namespace designPatterns;

class Agent
	: public Composite<Agent>
{
};

#define RUN_TIME_AUTHOR_TIME_DEFAULTS
#define RUN_TIME_DEFAULTS
#define AUTHOR_TIME_DEFAULTS
#define PURE_CLASS_DEFAULTS

class RunTimeAuthorTimeState
	: public HFSM2::ActionState<Agent>
{
	friend class Factory<RunTimeAuthorTimeState>;

public:
protected:
	static bool hasAuthoringTimeState(void)
	{
		return true;
	}

private:
}; // class RunTimeAuthorTimeState

class AuthorTimeState
	: public HFSM2::ActionState<Agent>
{
	friend class Factory<AuthorTimeState>;

public:
protected:
	static bool hasAuthoringTimeState(void)
	{
		return true;
	}

private:
}; // class AuthorTimeState

class RunTimeState
	: public HFSM2::ActionState<Agent>
{
	friend class Factory<RunTimeState>;

public:
protected:
	static bool hasAuthoringTimeState(void)
	{
		return false;
	}

private:
}; // class RunTimeState

class PureState
	: public HFSM2::ActionState<Agent>
{
	friend class Factory<PureState>;

public:
	PureState(void)
		: ActionState<Agent>()
	{
		static int pureStateCount(0);
		++pureStateCount;
		assert(pureStateCount == 1);
	}

	ActionState<Agent>* getRunTimeCopy(void) const
	{
		return Factory<PureState>::getRunTimeCopy(*this);
	}

	bool hasRunTimeState(void) const
	{
		return false;
	}

	void recycle(void)
	{
		Factory<PureState>::recycle(*this);
	}

protected:
	static PureState* duplicate(const PureState& source)
	{
		return new PureState(source);
	}
	
	static bool hasAuthoringTimeState(void)
	{
		return false;
	}

private:
}; // class PureState

class PureTransitionFX
	: public TransitionFX<Agent>
{
	friend class Factory<PureTransitionFX>;

public:
	virtual void effect(Agent* /*agent*/, ActionState<Agent>& /*master*/, ActionState<Agent>& /*from*/, ActionState<Agent>& /*to*/)
	{
		printf("effecting on transition!\n");
	}

	virtual void recycle(void)
	{
		Factory<PureTransitionFX>::recycle(*this);
	}

protected:
	static PureTransitionFX* duplicate(const PureTransitionFX& source) 
	{
		return new PureTransitionFX(source);
	}

	static bool hasAuthoringTimeState(void)
	{
		return false;
	}

	virtual TransitionFX<Agent>* getRunTimeCopy(void) const
	{
		return Factory<PureTransitionFX>::getRunTimeCopy(*this);
	}

	virtual bool hasRunTimeState(void) const
	{
		return false;
	}
}; // class PureTransitionFX

void HFSM2::test(void)
{
	Agent gamma;
	Traversal<Agent> alpha(gamma);

	TransitionFX<Agent>* transitionFX1 = Factory<PureTransitionFX>::getAuthorCopy(); // ("transition fx");
	TransitionFX<Agent>* transitionFX2 = transitionFX1;
	// TransitionFX<Agent>* transitionFX3 = transitionFX1;

	ConditionTrue<Agent>* condition1 = Factory<ConditionTrue<Agent>>::getAuthorCopy(); // ("condition");
	ConditionTrue<Agent>* condition2 = condition1;
	ConditionTrue<Agent>* condition3 = condition1;
	ConditionTrue<Agent>* condition4 = condition1;
	ConditionTrue<Agent>* condition5 = condition1;
	ConditionTrue<Agent>* condition6 = condition1;
//	ConditionTrue<Agent>* condition7 = condition1;

	StateMachine<Agent>* stateMachine1 = Factory<StateMachine<Agent>>::getAuthorCopy(); // ("state/machine 0/x");

	PureState* state1 = Factory<PureState>::getAuthorCopy(); // ("state");
	ActionState<Agent>* state2 = Factory<PureState>::getAuthorCopy();
	StateMachine<Agent>* stateMachine2 = Factory<StateMachine<Agent>>::getAuthorCopy(); // ("state/machine 3/1");

	ActionState<Agent>* state4 = Factory<PureState>::getAuthorCopy();
	ActionState<Agent>* state5 = Factory<PureState>::getAuthorCopy();
	StateMachine<Agent>* stateMachine3 = Factory<StateMachine<Agent>>::getAuthorCopy(); // ("state/machine 6/2");		

	ActionState<Agent>* state7 = Factory<PureState>::getAuthorCopy();
	ActionState<Agent>* state8 = Factory<PureState>::getAuthorCopy();
	ActionState<Agent>* state9 = Factory<PureState>::getAuthorCopy();

	{
		StateKey key1 = stateMachine1->add(*state1);
		StateKey key2 = stateMachine1->add(*state2);
		StateKey key3 = stateMachine1->add(*stateMachine2);
		stateMachine1->connect(key1, *condition1, key2, transitionFX1);
		stateMachine1->connect(key2, *condition2, key3, transitionFX2);
	}

	{
		StateKey key4 = stateMachine2->add(*state4);
		StateKey key5 = stateMachine2->add(*state5);
		StateKey key6 = stateMachine2->add(*stateMachine3);
		stateMachine2->connect(key4, *condition3, key5, transitionFX1);
		stateMachine2->connect(key5, *condition4, key6, transitionFX2);
	}

	{
		StateKey key7 = stateMachine3->add(*state7);
		StateKey key8 = stateMachine3->add(*state8);
		StateKey key9 = stateMachine3->add(*state9);
		stateMachine3->connect(key7, *condition5, key8, transitionFX1);
		stateMachine3->connect(key8, *condition6, key9, transitionFX2);
		//stateMachine3->connect(key9, *condition7, key7, transitionFX3);
	}

	StateMachine<Agent>* stateMachineRun = Factory<StateMachine<Agent>>::getRunTimeCopy(*stateMachine1);

	alpha.start(*stateMachineRun);

	for (int i = 0; i < 12; ++i)
	{
		alpha.act();
	}

	alpha.stop();	
	
	stateMachine1->recycle();
	
	Factory<PureTransitionFX>::destroyObjects();
	Factory<ConditionTrue<Agent>>::destroyObjects();
	Factory<StateMachine<Agent>>::destroyObjects();
	Factory<ActionState<Agent>>::destroyObjects();

	BREAKPOINT(0x0);
}