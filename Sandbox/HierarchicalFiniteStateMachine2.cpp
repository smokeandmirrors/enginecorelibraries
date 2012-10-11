#include "Composition.h"
#include "HierarchicalFiniteStateMachine2.h"

using namespace HFSM2;
using namespace designPatterns;


template<typename TRAIT>
struct HasAuthorTimeState
{
	static const bool value = true;
};

template<> 
struct HasAuthorTimeState<void>
{
	static const bool value = false;
};


template<bool HAS_AUTHOR_TIME_STATE>
struct AuthorGeneratorSelector
{
	template<typename OBJECT>
	static OBJECT* generate(void)
	{
		printf("has author time version!");
		return new OBJECT;
	}
};

template<>
struct AuthorGeneratorSelector<false>
{
	template<typename OBJECT>
	static OBJECT* generate(void)
	{
		static OBJECT object;
		printf("has NOT author time version!");
		return &object;
	}
};

template<typename OBJECT>
OBJECT* GenerateAuthorCopy(void)
{
	// return AuthorGeneratorSelector< HasAuthorTimeState< OBJECT >::value >::generate<OBJECT>();
	return AuthorGeneratorSelector< OBJECT::hasAuthorTimeState >::generate<OBJECT>();
};


template<bool HAS_AUTHOR_TIME_STATE>
struct AuthorGeneratorSelectorWithArgs
{
	template<typename OBJECT, typename ARGS>
	static OBJECT* generate(const ARGS& args)
	{
		printf("has author time version with args!\n");
		return new OBJECT(args);
	}

	template<typename OBJECT>
	static OBJECT* generate(void)
	{
		printf("has author time version without args!\n");
		return new OBJECT;
	}
};

template<>
struct AuthorGeneratorSelectorWithArgs<false>
{
	template<typename OBJECT, typename ARGS>
	static OBJECT* generate(const ARGS& args)
	{
		static OBJECT object(args);
		printf("has NOT author time version with args!\n");
		return &object;
	}

	template<typename OBJECT>
	static OBJECT* generate(void)
	{
		static OBJECT object;
		printf("has NOT author time version with no args!\n");
		return &object;;
	}
};

template<typename OBJECT, typename ARGS>
OBJECT* GenerateAuthorCopyWithArgs(const ARGS& args)
{
	// return AuthorGeneratorSelector< HasAuthorTimeState< OBJECT >::value >::generate<OBJECT>();
	return AuthorGeneratorSelectorWithArgs< OBJECT::hasAuthorTimeState >::generate<OBJECT, ARGS>(args);
};

template<typename OBJECT>
OBJECT* GenerateAuthorCopyWithArgs(void)
{
	return AuthorGeneratorSelectorWithArgs< OBJECT::hasAuthorTimeState >::generate<OBJECT>();
}


class AuthorCopyA 
{
public:
	static const bool hasAuthorTimeState = true;

	AuthorCopyA() {}
	AuthorCopyA(int i) {}
};

class AuthorCopyB 
{
public:
	static const bool hasAuthorTimeState = false;

	AuthorCopyB() {}
	AuthorCopyB(int i) {}
};

template<>
struct HasAuthorTimeState<AuthorCopyB>
{
	static const bool value = false;
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

class PureTransitionFX
	: public TransitionFX<Agent>
{
	PURE_TRANSITION_FX(PureTransitionFX, Agent)

public:
	virtual void effect(Agent* /*agent*/, ActionState<Agent>& /*master*/, ActionState<Agent>& /*from*/, ActionState<Agent>& /*to*/)
	{
		printf("effecting on transition!\n");
	}
}; // class PureTransitionFX

void HFSM2::test(void)
{

	AuthorCopyB* bcbw = GenerateAuthorCopyWithArgs<AuthorCopyB, int>(2);
	AuthorCopyA* acbw = GenerateAuthorCopyWithArgs<AuthorCopyA, int>(2);
	AuthorCopyB* bcbwo = GenerateAuthorCopyWithArgs<AuthorCopyB>();
	AuthorCopyA* acbwo = GenerateAuthorCopyWithArgs<AuthorCopyA>();

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

	PureState* pureState = Factory<PureState>::getAuthorCopy(); // ("state");
	AuthorTimeState* authorTimeState(Factory<AuthorTimeState>::getAuthorCopy<int>(5));
	RunTimeState* runTimeState(Factory<RunTimeState>::getAuthorCopy());
	RunTimeAuthorTimeState* authorTimeRunTimeState(Factory<RunTimeAuthorTimeState>::getAuthorCopy<int>(3));
	
	ActionState<Agent>* state1 = runTimeState;
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


