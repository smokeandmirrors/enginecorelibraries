#include "Composition.h"
#include "HierarchicalFiniteStateMachine.h"

using namespace HFSM;
using namespace designPatterns;

class Agent
	: public Composite<Agent>
{
};


class AuthorTimeCondition
	: public HFSM::Condition<Agent>
{
	CONDITION_WITH_AUTHOR_TIME_STATE(AuthorTimeCondition, Agent)

public:
	AuthorTimeCondition(int authorTime)
		: Condition<Agent>()
		, m_authorVariable(authorTime)
	{
		/* empty */
	}

protected:
	bool isSatisfied(Agent&)
	{
		return true;
	}

private:
	const int m_authorVariable;
}; // AuthorTimeCondition

bool AuthorTimeCondition::isEqualToAtAuthorTime(const AuthorTimeCondition& other) const
{
	return m_authorVariable == other.m_authorVariable;
}

class RunTimeAuthorTimeCondition
	: public HFSM::Condition<Agent>
{
	CONDITION_WITH_AUTHOR_TIME_AND_RUN_TIME_STATE(RunTimeAuthorTimeCondition, Agent)

public:
	RunTimeAuthorTimeCondition(int authorTime)
		: Condition<Agent>()
		, m_authorVariable(authorTime)
		, m_runTimeVariable(0)
	{
		/* empty */
	}

protected:
	bool isSatisfied(Agent&)
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
	: public HFSM::ActionState<Agent>
{
	ACTION_STATE_WITH_AUTHOR_AND_RUN_TIME_STATE(RunTimeAuthorTimeState, Agent)

public:
	RunTimeAuthorTimeState(int authorTime)
		: ActionState<Agent>()
		, m_authorVariable(authorTime)
		, m_runTimeVariable(0)
	{
		/* empty */
	}

	virtual void act(Agent& /*agent*/) {}

	virtual void enter(Agent& /*agent*/)
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
	: public HFSM::ActionState<Agent>
{
	ACTION_STATE_WITH_AUTHOR_TIME_STATE(AuthorTimeState, Agent)

public:
	AuthorTimeState(int authorTime)
		: ActionState<Agent>()
		, m_authorVariable(authorTime)
	{
		/* empty */
	}

	virtual void act(Agent& /*agent*/) {}

	virtual void enter(Agent& /*agent*/)
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
	: public HFSM::ActionState<Agent>
{
	ACTION_STATE_WITH_RUN_TIME_STATE(RunTimeState, Agent)

public:
	RunTimeState(void)
		: ActionState<Agent>()
		, m_runTimeVariable(0)
	{
		/* empty */
	}

	virtual void act(Agent& /*agent*/) {}

	virtual void enter(Agent& /*agent*/)
	{
		printf("RunTimeState: %2d\n", ++m_runTimeVariable);
	};

private:
	int m_runTimeVariable;
}; // class RunTimeState

DERIVED_RUN_TIME_TYPE_DEFINITION(RunTimeState, ActionState<Agent>, NULL)

class PureState
	: public HFSM::ActionState<Agent>
{
	ACTION_STATE_PURE(PureState, Agent)

public:
	PureState(void)
		: ActionState<Agent>()
	{
		/* empty */
	}

	virtual void act(Agent& /*agent*/) {}

	virtual void enter(Agent& /*agent*/)
	{
		printf("PureState\n");
	}

}; // class PureState

DERIVED_RUN_TIME_TYPE_DEFINITION(PureState, ActionState<Agent>, NULL)

class PureTransitionFX
	: public TransitionFX<Agent>
{
	TRANSITION_FX_PURE(PureTransitionFX, Agent)

public:
	PureTransitionFX(void)
	{
		/* empty */
	}

	virtual void effect(Agent& /*agent*/, const ActionState<Agent>& /*master*/, const ActionState<Agent>& /*from*/, const ActionState<Agent>& /*to*/)
	{
		printf("effecting on transition!\n");
	}
}; // class PureTransitionFX

class StateMachineWithAuthorState
	: public StateMachine<Agent>
{
	STATE_MACHINE_WITH_AUTHOR_TIME_STATE(StateMachineWithAuthorState, Agent)


protected:
	StateMachineWithAuthorState(int seven)
	{
		TransitionFX<Agent>* transitionFX1 = Factory<PureTransitionFX>::getAuthorCopy(); 
		AuthorTimeCondition* condition1 = Factory<AuthorTimeCondition>::getAuthorCopy<int>(1); 
		AuthorTimeCondition* condition2 = Factory<AuthorTimeCondition>::getAuthorCopy<int>(1); 

		ActionState<Agent>* state7 = Factory<AuthorTimeState>::getAuthorCopy<int>(seven);
		ActionState<Agent>* state8 = Factory<AuthorTimeState>::getAuthorCopy<int>(++seven);
		ActionState<Agent>* state9 = Factory<PureState>::getAuthorCopy();

		StateKey key7 = add(*state7);
		StateKey key8 = add(*state8);
		StateKey key9 = add(*state9);

		connect(key7, *condition1, key8, transitionFX1);
		connect(key8, *condition2, key9, transitionFX1);
	}

	virtual void enter(Agent&)
	{
		printf("StateMachineWith author state: 3\n");
	}

};

bool StateMachineWithAuthorState::isEqualToAtAuthorTime(const StateMachineWithAuthorState& other) const
{
	const AuthorTimeState* myATS(static_cast<const AuthorTimeState*>(&getState(0)->state));
	const AuthorTimeState* otherATS(static_cast<const AuthorTimeState*>(&other.getState(0)->state));
	return myATS == otherATS;
}

DERIVED_RUN_TIME_TYPE_DEFINITION(StateMachineWithAuthorState, StateMachine<Agent>, NULL)

class StateMachineThree
	: public StateMachine<Agent>
{
	STATE_MACHINE_WITHOUT_AUTHOR_TIME_STATE(StateMachineThree, Agent)

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
		connect(key9, *condition2, key7, transitionFX1);
	}

	virtual void enter(Agent&)
	{
		printf("StateMachine: 6\n");
	}

	int memoryTest[20480];
};
DERIVED_RUN_TIME_TYPE_DEFINITION(StateMachineThree, StateMachine<Agent>, NULL)

class StateMachineTwo
	: public StateMachine<Agent>
{
	STATE_MACHINE_WITHOUT_AUTHOR_TIME_STATE(StateMachineTwo, Agent)

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

	virtual void enter(Agent&)
	{
		printf("StateMachine: 3\n");
	}

	// int memoryTest[20480];

};
DERIVED_RUN_TIME_TYPE_DEFINITION(StateMachineTwo, StateMachine<Agent>, NULL)
	
class StateMachineOne
	: public StateMachine<Agent>
{
	STATE_MACHINE_WITHOUT_AUTHOR_TIME_STATE(StateMachineOne, Agent)

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

	virtual void enter(Agent&)
	{
		printf("StateMachine: 0\n");
	}
};
DERIVED_RUN_TIME_TYPE_DEFINITION(StateMachineOne, StateMachine<Agent>, NULL)

FactoryDestroyer* factoryDestroyers(NULL);

class Alarm
{
public:
	void detectSmoke(void)
	{
		printf("looking for smoke\n");
	}

	void initialBeep(void)
	{
		printf("initial alarm beep!\n");
	}

	void sound(void) 
	{
		printf("BEEP BEEP BEEP!\n");
	}
}; // Alarm

class InitialAlarmBeep : public TransitionFX<Alarm>
{
	TRANSITION_FX_WITH_RUN_TIME_STATE(InitialAlarmBeep, Alarm);

	InitialAlarmBeep()
	{
		m_timesExecuted = 0;
	}

public:
	void effect(Alarm& alarm, const ActionState<Alarm>& , const ActionState<Alarm>& , const ActionState<Alarm>&)
	{
		if (m_timesExecuted < 2)
		{
			alarm.initialBeep();
		}
		else
		{
			printf("alarm beep FX has reached its limit\n");
		}
	}

protected:
	void enter(Alarm& alarm)
	{
		printf("entering alarm beep FX\n");
		++m_timesExecuted;
	}
	
private:
	int m_timesExecuted;
}; // 


class IsAlarmSilenced: public Condition<Alarm>
{
	CONDITION_WITH_RUN_TIME_STATE(IsAlarmSilenced, Alarm);

protected:
	void enter(Alarm& alarm)
	{
		printf("enter is alarm silenced condition\n");
		m_timesExecuted = 0;
	}

	void exit(Alarm& alarm)
	{
		printf("exiting is alarm silenced condition\n");
	}
	
	bool isSatisfied(Alarm& alarm)
	{
		++m_timesExecuted;
		return m_timesExecuted > 3;	
	}

private:
	int m_timesExecuted;
};

class IsSmokePresent : public Condition<Alarm>
{
	CONDITION_WITH_RUN_TIME_STATE(IsSmokePresent, Alarm);

protected:
	void enter(Alarm& alarm)
	{
		printf("enter is smoke present condition\n");
		m_timesExecuted = 0;
	}

	void exit(Alarm& alarm)
	{
		printf("exiting is smoke present condition\n");
	}

	bool isSatisfied(Alarm& alarm)
	{
		++m_timesExecuted;
		return m_timesExecuted > 2;	
	}

private:
	int m_timesExecuted;
};

class SoundAlarm : public ActionState<Alarm>
{
	ACTION_STATE_PURE(SoundAlarm, Alarm)

public:
	void act(Alarm& agent)
	{
		agent.sound();
	}
}; 
DERIVED_RUN_TIME_TYPE_DEFINITION(SoundAlarm, ActionState<Alarm>, NULL)

class DetectSmoke : public ActionState<Alarm>
{
	ACTION_STATE_PURE(DetectSmoke, Alarm)

public:
	void act(Alarm& alarm)
	{
		alarm.detectSmoke();
	}
};
DERIVED_RUN_TIME_TYPE_DEFINITION(DetectSmoke, ActionState<Alarm>, NULL)

// definition
class AlarmState : public StateMachine<Alarm>
{
	STATE_MACHINE_WITHOUT_AUTHOR_TIME_STATE(AlarmState, Alarm);

protected:
	AlarmState()
	{	// get the author objects
		ActionState<Alarm>* soundAlarm = Factory<SoundAlarm>::getAuthorCopy();
		ActionState<Alarm>* detectSmoke = Factory<DetectSmoke>::getAuthorCopy();
		TransitionFX<Alarm>* initialBeep = Factory<InitialAlarmBeep>::getAuthorCopy();
		Condition<Alarm>* isSilenced = Factory<IsAlarmSilenced>::getAuthorCopy();
		Condition<Alarm>* isSmokePresent = Factory<IsSmokePresent>::getAuthorCopy();
		// add the states to the machine
		StateKey detectSmokeKey(add(*detectSmoke));
		StateKey soundAlarmKey(add(*soundAlarm));
		// define the connections
		connect(detectSmokeKey, *isSmokePresent, soundAlarmKey, initialBeep);
		connect(soundAlarmKey, *isSilenced, detectSmokeKey);
	}
}; // AlarmState
DERIVED_RUN_TIME_TYPE_DEFINITION(AlarmState, StateMachine<Alarm>, NULL)

void HFSM::test(void)
{
	// this the alarm
	{
		Alarm alarm;
		Traversal<Alarm> traversal(alarm);

		AlarmState* alarmAuthor = Factory<AlarmState>::getAuthorCopy();
		AlarmState* alarmRunTime = Factory<AlarmState>::getRunTimeCopy(*alarmAuthor);
		traversal.start(*alarmRunTime);

		for (int i = 0; i < 20; ++i)
		{
			traversal.act();
		}
		
		traversal.stop();
		alarmRunTime->recycle();
		
		// later
		FactoryDestroyer::destroyAllAuthorTimeAndStatelessObjects();
	}

	for(;;) // test for memory leaks
	{
		Agent gamma;
		Traversal<Agent> alpha(gamma);		

		StateMachineOne* smOneAuthor1(Factory<StateMachineOne>::getAuthorCopy());
		StateMachineOne* smOneAuthor2(Factory<StateMachineOne>::getAuthorCopy());
		StateMachineOne* smOneRun1(Factory<StateMachineOne>::getRunTimeCopy(*smOneAuthor1));
		StateMachineOne* smOneRun2(Factory<StateMachineOne>::getRunTimeCopy(*smOneAuthor2));

		StateMachineWithAuthorState* authorAuthor(Factory<StateMachineWithAuthorState>::getAuthorCopy<int>(7));
		StateMachineWithAuthorState* authorAuthor2(Factory<StateMachineWithAuthorState>::getAuthorCopy<int>(7));
		StateMachineWithAuthorState* authorAuthor3(Factory<StateMachineWithAuthorState>::getAuthorCopy<int>(8));
		StateMachineWithAuthorState* authorRun(Factory<StateMachineWithAuthorState>::getRunTimeCopy(*authorAuthor));
		StateMachineWithAuthorState* authorRun2(Factory<StateMachineWithAuthorState>::getRunTimeCopy(*authorAuthor2));

		// StateMachineThree* stateMachineOne(Factory<StateMachineThree>::getAuthorCopy());
		// StateMachineThree* stateMachineOneRun(Factory<StateMachineThree>::getRunTimeCopy(*stateMachineOne));
		
		alpha.start(*smOneRun1);
		// just test for memory leaks
		for (int i(0), sentinel(19); i < sentinel; ++i)
		{
			alpha.act();
		}

		assert(alpha.isInState(AuthorTimeState::runTimeType));
		alpha.stop();		

		smOneRun1->recycle();
		smOneRun2->recycle();
		authorRun2->recycle();
		authorRun->recycle();

		FactoryDestroyer::destroyAllAuthorTimeAndStatelessObjects();
	}
	

	BREAKPOINT(0x0);
}


