#include "Composition.h"
#include "HierarchicalFiniteStateMachine2.h"

using namespace HFSM2;
using namespace designPatterns;

class Agent
	: public Composite<Agent>
{
};

class RunTimeAuthorTimeCondition
	: public HFSM2::Condition<Agent>
{

	CONDITION_WITH_AUTHOR_AND_RUN_TIME_STATE(RunTimeAuthorTimeCondition, Agent)

public:
	RunTimeAuthorTimeCondition(int authorTime)
		: Condition<Agent>()
		, m_authorVariable(authorTime)
		, m_runTimeVariable(0)
	{
		/* empty */
	}

protected:
	bool isSatisfied(Agent*)
	{
		return (++m_runTimeVariable) > m_authorVariable;
	}

private:
	const int m_authorVariable;
	int m_runTimeVariable;
};

bool RunTimeAuthorTimeCondition::isEqualToAtAuthorTime(const RunTimeAuthorTimeCondition& other) const
{
	return m_authorVariable == other.m_authorVariable;
}

class RunTimeAuthorTimeState
	: public HFSM2::ActionState<Agent>
{
	STATE_WITH_AUTHOR_AND_RUN_TIME_STATE(RunTimeAuthorTimeState, Agent)

public:
	RunTimeAuthorTimeState(int authorTime)
		: ActionState<Agent>()
		, m_authorVariable(authorTime)
		, m_runTimeVariable(0)
	{
		/* empty */
	}

	virtual void act(Traversal<Agent>& /*agent*/) {}

	virtual void onEnter(Traversal<Agent>& /*agent*/)
	{
		printf("RunTimeAuthorState: %2d %2d\n", ++m_runTimeVariable, m_authorVariable);
	}

private:
	const int m_authorVariable;
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
	AuthorTimeState(int authorTime)
		: ActionState<Agent>()
		, m_authorVariable(authorTime)
	{
		/* empty */
	}

	virtual void act(Traversal<Agent>& /*agent*/) {}

	virtual void onEnter(Traversal<Agent>& /*agent*/)
	{
		printf("AuthorTimeState: %2d\n", m_authorVariable);
	}

private:
	const int m_authorVariable;
}; // class AuthorTimeState

DERIVED_RUN_TIME_TYPE_DEFINITION(AuthorTimeState, ActionState<Agent>, NULL)

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
		, m_runTimeVariable(0)
	{
		/* empty */
	}

	virtual void act(Traversal<Agent>& /*agent*/) {}

	virtual void onEnter(Traversal<Agent>& /*agent*/)
	{
		printf("RunTimeState: %2d\n", ++m_runTimeVariable);
	};

private:
	int m_runTimeVariable;
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
		/* empty */
	}

	virtual void act(Traversal<Agent>& /*agent*/) {}

	virtual void onEnter(Traversal<Agent>& /*agent*/)
	{
		printf("PureState\n");
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
		TransitionFX<Agent>* transitionFX1 = Factory<PureTransitionFX>::getAuthorCopy(); 
		RunTimeAuthorTimeCondition* condition1 = Factory<RunTimeAuthorTimeCondition>::getAuthorCopy<int>(1); 
		RunTimeAuthorTimeCondition* condition2 = Factory<RunTimeAuthorTimeCondition>::getAuthorCopy<int>(1); 

		ActionState<Agent>* state7 = Factory<AuthorTimeState>::getAuthorCopy<int>(7);
		ActionState<Agent>* state8 = Factory<AuthorTimeState>::getAuthorCopy<int>(8);
		ActionState<Agent>* state9 = Factory<AuthorTimeState>::getAuthorCopy<int>(9);
	
		StateKey key7 = add(*state7);
		StateKey key8 = add(*state8);
		StateKey key9 = add(*state9);

		connect(key7, *condition1, key8, transitionFX1);
		connect(key8, *condition2, key9, transitionFX1);
	}

	virtual void onMachineEnter(Agent&)
	{
		printf("StateMachine: 3\n");
	}

	// int memoryTest[20480];
};
DERIVED_RUN_TIME_TYPE_DEFINITION(StateMachineThree, StateMachine<Agent>, NULL)

class StateMachineTwo
	: public StateMachine<Agent>
{
	STATE_WITH_RUN_TIME_STATE(StateMachineTwo, Agent)

protected:
	StateMachineTwo()
	{
		TransitionFX<Agent>* transitionFX1 = Factory<PureTransitionFX>::getAuthorCopy(); 
		RunTimeAuthorTimeCondition* condition1 = Factory<RunTimeAuthorTimeCondition>::getAuthorCopy<int>(1); 
		RunTimeAuthorTimeCondition* condition2 = Factory<RunTimeAuthorTimeCondition>::getAuthorCopy<int>(1); 

		ActionState<Agent>* state4 = Factory<AuthorTimeState>::getAuthorCopy<int>(4);
		ActionState<Agent>* state5 = Factory<AuthorTimeState>::getAuthorCopy<int>(5);
		ActionState<Agent>* state6 = Factory<StateMachineThree>::getAuthorCopy();

		StateKey key7 = add(*state4);
		StateKey key8 = add(*state5);
		StateKey key9 = add(*state6);

		connect(key7, *condition1, key8, transitionFX1);
		connect(key8, *condition2, key9, transitionFX1);
	}

	virtual void onMachineEnter(Agent&)
	{
		printf("StateMachine: 2\n");
	}

	// int memoryTest[20480];

};
DERIVED_RUN_TIME_TYPE_DEFINITION(StateMachineTwo, StateMachine<Agent>, NULL)
	
class StateMachineOne
	: public StateMachine<Agent>
{
	STATE_WITH_RUN_TIME_STATE(StateMachineOne, Agent)

protected:
	StateMachineOne()
	{
		TransitionFX<Agent>* transitionFX1 = Factory<PureTransitionFX>::getAuthorCopy(); 
		RunTimeAuthorTimeCondition* condition1 = Factory<RunTimeAuthorTimeCondition>::getAuthorCopy<int>(1); 
		RunTimeAuthorTimeCondition* condition2 = Factory<RunTimeAuthorTimeCondition>::getAuthorCopy<int>(1); 

		ActionState<Agent>* state1 = Factory<AuthorTimeState>::getAuthorCopy<int>(1);
		ActionState<Agent>* state2 = Factory<AuthorTimeState>::getAuthorCopy<int>(2);
		ActionState<Agent>* state3 = Factory<StateMachineTwo>::getAuthorCopy();

		StateKey key7 = add(*state1);
		StateKey key8 = add(*state2);
		StateKey key9 = add(*state3);

		connect(key7, *condition1, key8, transitionFX1);
		connect(key8, *condition2, key9, transitionFX1);
	}

	virtual void onMachineEnter(Agent&)
	{
		printf("StateMachine: 1\n");
	}
};
DERIVED_RUN_TIME_TYPE_DEFINITION(StateMachineOne, StateMachine<Agent>, NULL)

FactoryDestroyer* factoryDestroyers(NULL);

void HFSM2::test(void)
{
	for(;;)
	{
		Agent gamma;
		Traversal<Agent> alpha(gamma);
		StateMachineOne* stateMachineOne(Factory<StateMachineOne>::getAuthorCopy());
		StateMachineOne* stateMachineOneRun(Factory<StateMachineOne>::getRunTimeCopy(*stateMachineOne));
		// StateMachineThree* stateMachineOne(Factory<StateMachineThree>::getAuthorCopy());
		// StateMachineThree* stateMachineOneRun(Factory<StateMachineThree>::getRunTimeCopy(*stateMachineOne));
		alpha.start(*stateMachineOneRun);
		// just test for memory leaks
		for (int i(0), sentinel(13); i < sentinel; ++i)
		{
			alpha.act();
		}

		assert(alpha.isInState(AuthorTimeState::runTimeType));
		alpha.stop();		

		stateMachineOneRun->recycle();

		destroyAllAuthorTimeFactoryObjects();
	}
	

	BREAKPOINT(0x0);
}


