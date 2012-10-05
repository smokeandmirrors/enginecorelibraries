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
public:
protected:
	static bool hasAuthoringTimeState(void)
	{
		return false;
	}

private:
}; // class PureState

void HFSM2::test(void)
{
	Agent gamma;
	Traversal<Agent> alpha(gamma);

	TransitionFX<Agent>* transitionFX1 = Factory< TransitionFX<Agent>>::getAuthorCopy(); // ("transition fx");
	TransitionFX<Agent>* transitionFX2 = transitionFX1;
	// TransitionFX<Agent>* transitionFX3 = transitionFX1;

	ConditionTrue<Agent>* condition1 = Factory< ConditionTrue<Agent>>::getAuthorCopy(); // ("condition");
	ConditionTrue<Agent>* condition2 = condition1;
	ConditionTrue<Agent>* condition3 = condition1;
	ConditionTrue<Agent>* condition4 = condition1;
	ConditionTrue<Agent>* condition5 = condition1;
	ConditionTrue<Agent>* condition6 = condition1;
//	ConditionTrue<Agent>* condition7 = condition1;

	StateMachine<Agent>* stateMachine1 = Factory< StateMachine<Agent>>::getAuthorCopy(); // ("state/machine 0/x");

	PureState* state1 = Factory<PureState>::getAuthorCopy(); // ("state");
	ActionState<Agent>* state2 = state1;
	StateMachine<Agent>* stateMachine2 = Factory< StateMachine<Agent>>::getAuthorCopy(); // ("state/machine 3/1");

	ActionState<Agent>* state4 = state1;
	ActionState<Agent>* state5 = state1;
	StateMachine<Agent>* stateMachine3 = Factory< StateMachine<Agent>>::getAuthorCopy(); // ("state/machine 6/2");		

	ActionState<Agent>* state7 = state1;
	ActionState<Agent>* state8 = state1;
	ActionState<Agent>* state9 = state1;

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

	StateMachine<Agent>* stateMachineRun = Factory< StateMachine<Agent>>::getRunTimeCopy(*stateMachine1);

	alpha.start(*stateMachineRun);

	for (int i = 0; i < 12; ++i)
	{
		alpha.act();
	}

	alpha.stop();	

	{
		Factory< TransitionFX<Agent>>::recycle( *transitionFX1);
		Factory< ConditionTrue<Agent>>::recycle( *condition1 );
		Factory< StateMachine<Agent>>::recycle( *stateMachine1 );
		Factory< StateMachine<Agent>>::recycle( *stateMachine2 );
		Factory< StateMachine<Agent>>::recycle( *stateMachine3 );
		Factory< ActionState<Agent>>::recycle( *state1 );
	}

	Factory< TransitionFX<Agent>>::destroyObjects();
	Factory< ConditionTrue<Agent>>::destroyObjects();
	Factory< StateMachine<Agent>>::destroyObjects();
	Factory< ActionState<Agent>>::destroyObjects();

	BREAKPOINT(0x0);
}