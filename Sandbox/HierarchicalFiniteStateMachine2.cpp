#include "Composition.h"
#include "HierarchicalFiniteStateMachine2.h"

using namespace HFSM2;
using namespace designPatterns;

class Agent
	: public Composite<Agent>
{
};

class ActTracker 
	: public ActionState<Agent>
{
public:
	ActTracker(const char* n)
		: ActionState<Agent>(n)
		, m_numTimesActed(0)
		, m_numTimesOnEnter(0)
		, m_numTimesOnExit(0)
	{

	}

	virtual void act(Traversal<Agent>&)
	{
		printf("Num times act: %d\n", ++m_numTimesActed);
	}
	
protected:
	virtual void onEnter(Traversal<Agent>&) 
	{ 
		printf("Num times onEnter: %d\n", ++m_numTimesOnEnter);
	}

	virtual void onExit(Traversal<Agent>&) 
	{ 
		printf("Num times onExit: %d\n", ++m_numTimesOnExit);
	}

private:
	int m_numTimesActed;
	int m_numTimesOnEnter;
	int m_numTimesOnExit;
};

class TimesEvaluated
	: public Condition<Agent>
{
public:
	TimesEvaluated(int numTimesToEvaluate=0)
		: requiredEvaluations(numTimesToEvaluate)
		, m_numTimesIsSatisfied(0)
	{
		/* empty */
	}

protected:
	virtual bool isSatisfied(Agent*)
	{
		printf("Num times isSatisfied: %d\n", ++m_numTimesIsSatisfied);
		return m_numTimesIsSatisfied >= requiredEvaluations;
	}
	
private:
	int requiredEvaluations;
	int m_numTimesIsSatisfied;
};

void printIndices(const int numEdges)
{
	printf("Num Edges: %d\n", numEdges);
	// handle the zero index case separately, since the inner loop sentinel is different
	for (int j(2), j_sentinel(numEdges - 1); j < j_sentinel; ++j)
	{
		printf("0 : %d\n", j);
	}
	// handle the other indices with the normal inner loop sentinel
	for (int i(1), i_sentinel(numEdges - 2), j_sentinel(numEdges); i < i_sentinel; ++i)
	{
		for (int j(i + 2); j < j_sentinel; ++j)
		{
			printf("%d : %d\n", i, j);
		} // j loop
	} // i loop 

	printf("\n");
}


void HFSM2::test(void)
{
	Agent gamma;
	Traversal<Agent> alpha(&gamma);

	TransitionFX<Agent>* transitionFX1 = new TransitionFX<Agent>;
	TransitionFX<Agent>* transitionFX2 = new TransitionFX<Agent>;
	TransitionFX<Agent>* transitionFX3 = new TransitionFX<Agent>;

	ConditionTrue<Agent>* condition1 = new ConditionTrue<Agent>("condition 1");
	ConditionTrue<Agent>* condition2 = new ConditionTrue<Agent>("condition 2");
	ConditionTrue<Agent>* condition3 = new ConditionTrue<Agent>("condition 3");
	ConditionTrue<Agent>* condition4 = new ConditionTrue<Agent>("condition 4");
	ConditionTrue<Agent>* condition5 = new ConditionTrue<Agent>("condition 5");
	ConditionTrue<Agent>* condition6 = new ConditionTrue<Agent>("condition 6");
	ConditionTrue<Agent>* condition7 = new ConditionTrue<Agent>("condition 7");

	StateMachine<Agent>* stateMachine1 = new StateMachine<Agent>("state/machine 0/x");

	ActionState<Agent>* state1 = new ActionState<Agent>("state 1");
	ActionState<Agent>* state2 = new ActionState<Agent>("state 2");
	StateMachine<Agent>* stateMachine2 = new StateMachine<Agent>("state/machine 3/1");

	ActionState<Agent>* state4 = new ActionState<Agent>("state 4");
	ActionState<Agent>* state5 = new ActionState<Agent>("state 5");
	StateMachine<Agent>* stateMachine3 = new StateMachine<Agent>("state/machine 6/2");		

	ActionState<Agent>* state7 = new ActionState<Agent>("state 7");
	ActionState<Agent>* state8 = new ActionState<Agent>("state 8");
	ActionState<Agent>* state9 = new ActionState<Agent>("state 9");

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
		stateMachine3->connect(key9, *condition7, key7, transitionFX3);
	}

	alpha.start(*stateMachine1);

	for (int i = 0; i < 12; ++i)
	{
		alpha.act();
	}

	alpha.stop();	

	{
		delete transitionFX1;
		delete transitionFX2;
		delete transitionFX3;
		delete condition1;
		delete condition2;
		delete condition3;
		delete condition4;
		delete condition5;
		delete condition6;
		delete condition7;
		delete stateMachine1;
		delete stateMachine2;
		delete stateMachine3;
		delete state1;
		delete state2;
		delete state4;
		delete state5;
		delete state7;
		delete state8;
		delete state9;
	}

	BREAKPOINT(0x0);
}