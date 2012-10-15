#include "Composition.h"
#include "HierarchicalFiniteStateMachine2.h"

using namespace HFSM2;
using namespace designPatterns;

// typedef ActionState<Agent> AgentActionState;

// BASE_RUN_TIME_TYPE_DEFINITION(AgentActionState, NULL)
// DERIVED_RUN_TIME_TYPE_DEFINITION(StateMachine<Agent>, ActionState<Agent>, NULL)

class AuthorCopyA 
{
public:
	static const bool hasAuthorTimeState = true;

	AuthorCopyA()
	: m_authorTimeVariable(0)
	{

	}

	AuthorCopyA(int i)
	: m_authorTimeVariable (i)
	{
	
	}

	const int m_authorTimeVariable;

	bool isEqualToAtAuthorTime(const AuthorCopyA& other) { return m_authorTimeVariable == other.m_authorTimeVariable; }

private:
	AuthorCopyA& operator=(const AuthorCopyA&);
};

class AuthorCopyB 
{
public:
	static const bool hasAuthorTimeState = false;

	AuthorCopyB() {}
	AuthorCopyB(int i) {}
};

class Agent
	: public Composite<Agent>
{
};

class RunTimeAuthorTimeState
	: public HFSM2::ActionState<Agent>
{
	STATE_WITH_AUTHOR_AND_RUN_TIME_STATE(RunTimeAuthorTimeState, Agent)

public:
	RunTimeAuthorTimeState(int i)
		: ActionState<Agent>()
	{
		static int runTimeAuthorState(0);
		++runTimeAuthorState;
		// assert(runTimeAuthorState == 1);
		m_authorVariable = i;
	}

private:
	int m_authorVariable;
	int m_runTimeVariable;
}; // class RunTimeAuthorTimeState

DERIVED_RUN_TIME_TYPE_DEFINITION(RunTimeAuthorTimeState, ActionState<Agent>, NULL)

bool RunTimeAuthorTimeState::isEqualToAtAuthorTime(const RunTimeAuthorTimeState& other) const
{
	return m_authorVariable == other.m_authorVariable;
}

class AuthorTimeState
	: public HFSM2::ActionState<Agent>
{
	STATE_WITH_AUTHOR_STATE(AuthorTimeState, Agent)
public:

	static int authorTimeState;

	AuthorTimeState(int i)
		: ActionState<Agent>()
	{
		++authorTimeState;
		m_authorVariable = i;
	}

	~AuthorTimeState(void)
	{
		--authorTimeState;
	}

private:
	int m_authorVariable;
}; // class AuthorTimeState

DERIVED_RUN_TIME_TYPE_DEFINITION(AuthorTimeState, ActionState<Agent>, NULL)

int AuthorTimeState::authorTimeState = 0;

bool AuthorTimeState::isEqualToAtAuthorTime(const AuthorTimeState& other) const
{
	return m_authorVariable == other.m_authorVariable;
}

class RunTimeState
	: public HFSM2::ActionState<Agent>
{
	STATE_WITH_RUN_TIME_STATE(RunTimeState, Agent)
public:
	RunTimeState(void)
		: ActionState<Agent>()
	{
		static int runTimeState(0);
		++runTimeState;
		// assert(runTimeState  1);
	}
}; // class RunTimeState

DERIVED_RUN_TIME_TYPE_DEFINITION(RunTimeState, ActionState<Agent>, NULL)

class PureState
	: public HFSM2::ActionState<Agent>
{
	
	PURE_STATE(PureState, Agent)
public:
	PureState(void)
		: ActionState<Agent>()
	{
		static int pureStateCount(0);
		++pureStateCount;
		assert(pureStateCount == 1);
	}

}; // class PureState

DERIVED_RUN_TIME_TYPE_DEFINITION(PureState, ActionState<Agent>, NULL)

class PureTransitionFX
	: public TransitionFX<Agent>
{
	PURE_TRANSITION_FX(PureTransitionFX, Agent)
public:
	PureTransitionFX(void)
	{
		/* empty */
	}

	virtual void effect(Agent* /*agent*/, ActionState<Agent>& /*master*/, ActionState<Agent>& /*from*/, ActionState<Agent>& /*to*/)
	{
		printf("effecting on transition!\n");
	}
}; // class PureTransitionFX

class StateMachineThree
	: public StateMachine<Agent>
{
	STATE_WITH_RUN_TIME_STATE(StateMachineThree, Agent)

protected:
	StateMachineThree()
	{
		TransitionFX<Agent>* transitionFX1 = Factory<PureTransitionFX>::NewAuthorCopy(); 
		ConditionTrue<Agent>* condition1 = Factory<ConditionTrue<Agent>>::NewAuthorCopy(); 
		
		ActionState<Agent>* state7 = Factory<PureState>::NewAuthorCopy();
		ActionState<Agent>* state8 = Factory<PureState>::NewAuthorCopy();
		ActionState<Agent>* state9 = Factory<PureState>::NewAuthorCopy();

		StateKey key7 = add(*state7);
		StateKey key8 = add(*state8);
		StateKey key9 = add(*state9);

		connect(key7, *condition1, key8, transitionFX1);
		connect(key8, *condition1, key9, transitionFX1);
	}
};
DERIVED_RUN_TIME_TYPE_DEFINITION(StateMachineThree, StateMachine<Agent>, NULL)

class StateMachineTwo
	: public StateMachine<Agent>
{
	STATE_WITH_RUN_TIME_STATE(StateMachineTwo, Agent)

protected:
	StateMachineTwo()
	{
		TransitionFX<Agent>* transitionFX1 = Factory<PureTransitionFX>::NewAuthorCopy(); 
		ConditionTrue<Agent>* condition1 = Factory<ConditionTrue<Agent>>::NewAuthorCopy(); 

		ActionState<Agent>* state4 = Factory<PureState>::NewAuthorCopy();
		ActionState<Agent>* state5 = Factory<PureState>::NewAuthorCopy();
		ActionState<Agent>* state6 = Factory<StateMachineThree>::NewAuthorCopy();

		StateKey key7 = add(*state4);
		StateKey key8 = add(*state5);
		StateKey key9 = add(*state6);

		connect(key7, *condition1, key8, transitionFX1);
		connect(key8, *condition1, key9, transitionFX1);
	}
};
DERIVED_RUN_TIME_TYPE_DEFINITION(StateMachineTwo, StateMachine<Agent>, NULL)
	
class StateMachineOne
	: public StateMachine<Agent>
{
	STATE_WITH_RUN_TIME_STATE(StateMachineOne, Agent)

protected:
	StateMachineOne()
	{
		TransitionFX<Agent>* transitionFX1 = Factory<PureTransitionFX>::NewAuthorCopy(); 
		ConditionTrue<Agent>* condition1 = Factory<ConditionTrue<Agent>>::NewAuthorCopy(); 

		ActionState<Agent>* state1 = Factory<PureState>::NewAuthorCopy();
		ActionState<Agent>* state2 = Factory<PureState>::NewAuthorCopy();
		ActionState<Agent>* state3 = Factory<StateMachineTwo>::NewAuthorCopy();

		StateKey key7 = add(*state1);
		StateKey key8 = add(*state2);
		StateKey key9 = add(*state3);

		connect(key7, *condition1, key8, transitionFX1);
		connect(key8, *condition1, key9, transitionFX1);
	}
};
DERIVED_RUN_TIME_TYPE_DEFINITION(StateMachineOne, StateMachine<Agent>, NULL)

FactoryDestroyer* factoryDestroyers(NULL);

void HFSM2::test(void)
{
	Agent gamma;
	Traversal<Agent> alpha(gamma);
	StateMachineOne* stateMachineOne(Factory<StateMachineOne>::NewAuthorCopy());
	StateMachineOne* stateMachineOneRun(Factory<StateMachineOne>::NewRunTimeCopy(*stateMachineOne));
	alpha.start(*stateMachineOneRun);

	for (int i = 0; i < 12; ++i)
	{
		alpha.act();
	}

	bool is_in_state = alpha.isInState(PureState::runTimeType);
	alpha.stop();		
	
	stateMachineOneRun->recycle();
	
	
	// Factory<StateMachine<Agent>>::destroyObjects();
	/*
	Factory<StateMachineOne>::destroyObjects();
	Factory<StateMachineTwo>::destroyObjects();
	Factory<StateMachineThree>::destroyObjects();
	Factory<PureTransitionFX>::destroyObjects();
	Factory<ConditionTrue<Agent>>::destroyObjects();
	Factory<ActionState<Agent>>::destroyObjects();
	Factory<PureState>::destroyObjects();
	*/
	destroyFactoryObjects();

	BREAKPOINT(0x0);
}


