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

class PureState
	: public HFSM2::ActionState<Agent>
{
	RUN_TIME_TYPE_DECLARATION

	PURE_STATE(PureState, Agent)
		/*
private: 
	friend class Factory< false >::Internal< PureState >; 
	static PureState * duplicate(const PureState & source) { return new PureState (source);  } 
	virtual ActionState < Agent > * getRunTimeCopy(void) const { return NewRunTimeCopy< PureState >(*this); } 
	virtual void recycle(void) { RecycleRunTimeCopy< PureState >(*this); } 
	HAS_AUTHOR_TIME_STATE_false( PureState ) 
	HAS_RUN_TIME_STATE(false) 
	PureState& operator=(const PureState&); 
	PureState(const PureState&);
	*/
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

void HFSM2::test(void)
{
	AuthorCopyB* bcbw = NewAuthorCopy<AuthorCopyB>();
	AuthorCopyA* acbw = NewAuthorCopy<AuthorCopyA, int>(2);
	AuthorCopyA* acbw2 = NewAuthorCopy<AuthorCopyA, int>(2);
	AuthorCopyB* bcbwo = NewAuthorCopy<AuthorCopyB>();
	AuthorCopyA* acbwo = NewAuthorCopy<AuthorCopyA>();
	AuthorCopyA* acbwo2 = NewAuthorCopy<AuthorCopyA>();

	DestroyAuthorCopies<AuthorCopyA>();
	DestroyAuthorCopies<AuthorCopyB>();
	
	Agent gamma;
	Traversal<Agent> alpha(gamma);

	TransitionFX<Agent>* transitionFX1 = NewAuthorCopy<PureTransitionFX>(); // ("transition fx");
	TransitionFX<Agent>* transitionFX2 = transitionFX1;
	// TransitionFX<Agent>* transitionFX3 = transitionFX1;

	ConditionTrue<Agent>* condition1 = NewAuthorCopy<ConditionTrue<Agent>>(); // ("condition");
	ConditionTrue<Agent>* condition2 = condition1;
	ConditionTrue<Agent>* condition3 = condition1;
	ConditionTrue<Agent>* condition4 = condition1;
	ConditionTrue<Agent>* condition5 = condition1;
	ConditionTrue<Agent>* condition6 = condition1;
//	ConditionTrue<Agent>* condition7 = condition1;

	StateMachine<Agent>* stateMachine1 = NewAuthorCopy<StateMachine<Agent>>(); // ("state/machine 0/x");

	PureState* pureState = NewAuthorCopy<PureState>(); // ("state");
	AuthorTimeState* authorTimeState(NewAuthorCopy<AuthorTimeState, int>(5));
	RunTimeState* runTimeState(NewAuthorCopy<RunTimeState>());
	RunTimeAuthorTimeState* authorTimeRunTimeState(NewAuthorCopy<RunTimeAuthorTimeState, int>(3));
	
	ActionState<Agent>* state1 = runTimeState;
	ActionState<Agent>* state2 = NewAuthorCopy<PureState>();
	StateMachine<Agent>* stateMachine2 = NewAuthorCopy< StateMachine<Agent> >(); // ("state/machine 3/1");
	ActionState<Agent>* state4 = NewAuthorCopy<PureState>();
	ActionState<Agent>* state5 = NewAuthorCopy<PureState>();
	StateMachine<Agent>* stateMachine3 = NewAuthorCopy<StateMachine<Agent>>(); // ("state/machine 6/2");		

	ActionState<Agent>* state7 = NewAuthorCopy<PureState>();
	ActionState<Agent>* state8 = NewAuthorCopy<PureState>();
	ActionState<Agent>* state9 = NewAuthorCopy<PureState>();

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

	StateMachine<Agent>* stateMachineRun = NewRunTimeCopy<StateMachine<Agent>>(*stateMachine1);

	alpha.start(*stateMachineRun);

	for (int i = 0; i < 12; ++i)
	{
		alpha.act();
	}
	
	bool is_in_state = alpha.isInState(PureState::runTimeType);
	alpha.stop();		
	stateMachine1->recycle();
	
	DestroyAuthorCopies<PureTransitionFX>();
	DestroyAuthorCopies<ConditionTrue<Agent>>();
	DestroyAuthorCopies<StateMachine<Agent>>();
	DestroyAuthorCopies<ActionState<Agent>>();

	BREAKPOINT(0x0);
}


