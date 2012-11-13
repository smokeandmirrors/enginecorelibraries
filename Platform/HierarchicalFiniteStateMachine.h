#pragma once
#ifndef HIERARCHICAL_FSM
#define HIERARCHICAL_FSM

/**
\file HierarchicalFiniteStateMachine.h 
\brief Contains the code for a high performance, low-memory consumption, 
easy to use finite state machine system.  The primary feature is 
that any full state machine can be added to another machine as single state.

\author Smoke and Mirrors Development
\htmlonly
<A HREF="smokeandmirrorsdevelopment@gmail.com">
smokeandmirrorsdevelopment@gmail.com</A>
<BR>
&copy;2009-2012 Smoke and Mirrors Development
<BR>
\endhtmlonly

The intended usage is to create a machine of several states
connected by conditions that are evaluated in order.  An agent
that operates in a state machine does so as a member of the Traversal
object.  The Traversal object keeps track of the current state of agent
in the machine.  This way, thousands of agents can simultaneously operate
on a single instance of any machine.

In order to restrict the memory, the creation of machines are strictly 
controlled by the Factory<T> objects defined in AuthorTimeRunTimeFactory.h.

If the HFSM objects have state at run-time (that is, during traversal time),
a new object gets created for each traversal.  Otherwise, only one 
object gets created per author-time configuration.

Dependencies here are kept at a minimum, RunTimeType.h can be 
removed if it is unnecessary to query whether a traversal is in a certain 
type of state.  Remove the #include "RunTimeType." and all RUN_TIME_TYPE_DECLARATION
and related macros.

\note if leaks are suspected in the AuthorTimeRunTimeFactory.h system
add the lines below to #define IMPLEMENTATION, and create and destroy a ton of 
machine systems.  the leak should reveal itself very quickly
virtual void recycle(void) { memoryTest[0] += 1; printf("%d : memtest\n", memoryTest[0]); Factory< CLASS_NAME >::recycleRunTimeCopy(*this); } \
int memoryTest[20480]; 

The motivation for this implementation is as follows.  I have several
times needed various forms of high performance run time state machines
that are powerful (expressive and easy to change).  I have written
and worked with several version, and most, if not all, have been 
had one or more problems.  Many involved too much casting, or 
ignoring more powerful C++, O-O features.  This led to problems creating
and properly executing the states at run time.  Additionally, most
implementations required that each agent have entirely its own copy
of a state.  This version solves most issues I have ever run into.

\note This functionality is intentionally not thread-safe.  As long
as the author-time states are created from a single thread, run time execution
should be perfectly fine.   If specific optimizations of run-time copies
are desired, changes would have to be made to the recycle() methods here,
and in AuthorTimeRunTimeFactory.h.

\see GenericConditions.h for some helpful template Condition classes

<DEVELOPMENT STATUS>
Current Draft		:	3.0
Current Phase		:   FIELD TESTING
Purpose				:	DEPLOYMENT
Unit Tested			:	NO
Used in development	:	YES
Used in experiments :	YES
Tested in the field	:	NO
*/

#include "Platform.h" 
#include "AuthorTimeRunTimeFactory.h"
#include "RunTimeType.h"

#include <algorithm>
#include <vector>

/** support macro for the declaration of HFSM objects on a author/run time state basis */
#define GET_RUN_TIME_COPY_GENERIC(CLASS_NAME, FSM_TYPE, TYPE_NAME) \
	virtual FSM_TYPE < TYPE_NAME > * getRunTimeCopy(void) const { return Factory< CLASS_NAME >::getRunTimeCopy(*this); } 

/** support macro for the declaration of HFSM objects on a author/run time state basis */
#define GET_RUN_TIME_COPY_ActionState(CLASS_NAME, FSM_TYPE, TYPE_NAME) \
	GET_RUN_TIME_COPY_GENERIC(CLASS_NAME, FSM_TYPE, TYPE_NAME)

/** support macro for the declaration of HFSM objects on a author/run time state basis */
#define GET_RUN_TIME_COPY_Condition(CLASS_NAME, FSM_TYPE, TYPE_NAME) \
	GET_RUN_TIME_COPY_GENERIC(CLASS_NAME, FSM_TYPE, TYPE_NAME)

/** support macro for the declaration of HFSM objects on a author/run time state basis */
#define GET_RUN_TIME_COPY_StateMachine(CLASS_NAME, FSM_TYPE, TYPE_NAME) \
	virtual ActionState< TYPE_NAME > * getRunTimeCopy(void) const { return Factory< CLASS_NAME >::getRunTimeCopy(*this); } 

/** support macro for the declaration of HFSM objects on a author/run time state basis */
#define GET_RUN_TIME_COPY_TransitionFX(CLASS_NAME, FSM_TYPE, TYPE_NAME) \
	GET_RUN_TIME_COPY_GENERIC(CLASS_NAME, FSM_TYPE, TYPE_NAME)

/** support macro for the declaration of HFSM objects on a author/run time state basis */
#define HAS_RUN_TIME_STATE_ActionState(VALUE) \
	HAS_RUN_TIME_STATE_GENERIC(VALUE)

/** support macro for the declaration of HFSM objects on a author/run time state basis */
#define HAS_RUN_TIME_STATE_Condition(VALUE) \
	HAS_RUN_TIME_STATE_GENERIC(VALUE)

/** support macro for the declaration of HFSM objects on a author/run time state basis */
#define HAS_RUN_TIME_STATE_StateMachine(VALUE) 
	// virtual bool hasRunTimeState(void) const { return StateMachine<Agent>::hasRunTimeState(); }

/** support macro for the declaration of HFSM objects on a author/run time state basis */
#define HAS_RUN_TIME_STATE_TransitionFX(VALUE) \
	HAS_RUN_TIME_STATE_GENERIC(VALUE)

/** support macro for the declaration of HFSM objects on a author/run time state basis */
#define IMPLEMENTATION(CLASS_NAME, FSM_TYPE, TYPE_NAME, AUTHOR_TIME, RUN_TIME) \
	public: \
	virtual void recycle(void) { Factory< CLASS_NAME >::recycleRunTimeCopy(*this); } \
	HAS_AUTHOR_TIME_STATE_##AUTHOR_TIME##( CLASS_NAME ) \
	HAS_RUN_TIME_STATE_##FSM_TYPE##(RUN_TIME) \
	private: \
	friend class Factory< CLASS_NAME >; \
	friend class FactorySelector< AUTHOR_TIME >::Internal< CLASS_NAME >; \
	static CLASS_NAME * duplicate(const CLASS_NAME & source) { return new CLASS_NAME (source);  } \
	GET_RUN_TIME_COPY_##FSM_TYPE##(CLASS_NAME, FSM_TYPE, TYPE_NAME) \
	CLASS_NAME& operator=(const CLASS_NAME&); 
	
/** support macro for the declaration of HFSM objects on a author/run time state basis */
#define AUTHOR_AND_RUN_TIME_IMPLEMENTATION(CLASS_NAME, FSM_TYPE, TYPE_NAME) \
	IMPLEMENTATION(CLASS_NAME, FSM_TYPE, TYPE_NAME, true, true)

/** support macro for the declaration of HFSM objects on a author/run time state basis */
#define AUTHOR_TIME_IMPLEMENTATION(CLASS_NAME, FSM_TYPE, TYPE_NAME) \
	IMPLEMENTATION(CLASS_NAME, FSM_TYPE, TYPE_NAME, true, false)

/** support macro for the declaration of HFSM objects on a author/run time state basis */
#define PURE_IMPLEMENTATION(CLASS_NAME, FSM_TYPE, TYPE_NAME) \
	IMPLEMENTATION(CLASS_NAME, FSM_TYPE, TYPE_NAME, false, false)

/** support macro for the declaration of HFSM objects on a author/run time state basis */
#define RUN_TIME_IMPLEMENTATION(CLASS_NAME, FSM_TYPE, TYPE_NAME) \
	IMPLEMENTATION(CLASS_NAME, FSM_TYPE, TYPE_NAME, false, true)

/** Use this macro in the class declaration of a ActionState with no author or run time state */
#define ACTION_STATE_PURE(CLASS_NAME, TYPE_NAME) \
	RUN_TIME_TYPE_DECLARATION \
	PURE_IMPLEMENTATION(CLASS_NAME, ActionState, TYPE_NAME) 

/** Use this macro in the class declaration of a ActionState with author time state */
#define ACTION_STATE_WITH_AUTHOR_TIME_STATE(CLASS_NAME, TYPE_NAME) \
	RUN_TIME_TYPE_DECLARATION \
	AUTHOR_TIME_IMPLEMENTATION(CLASS_NAME, ActionState, TYPE_NAME) 

/** Use this macro in the class declaration of a ActionState with author & run time state */
#define ACTION_STATE_WITH_AUTHOR_AND_RUN_TIME_STATE(CLASS_NAME, TYPE_NAME) \
	RUN_TIME_TYPE_DECLARATION \
	AUTHOR_AND_RUN_TIME_IMPLEMENTATION(CLASS_NAME, ActionState, TYPE_NAME) 

/** Use this macro in the class declaration of a ActionState with run time state */
#define ACTION_STATE_WITH_RUN_TIME_STATE(CLASS_NAME, TYPE_NAME) \
	RUN_TIME_TYPE_DECLARATION \
	RUN_TIME_IMPLEMENTATION(CLASS_NAME, ActionState, TYPE_NAME) 

/** Use this macro in the class declaration of a Condition with no author or run time state */
#define CONDITION_PURE(CLASS_NAME, TYPE_NAME) \
	PURE_IMPLEMENTATION(CLASS_NAME, Condition, TYPE_NAME) 

/** Use this macro in the class declaration of a Condition with author time state */
#define CONDITION_WITH_AUTHOR_TIME_STATE(CLASS_NAME, TYPE_NAME) \
	AUTHOR_TIME_IMPLEMENTATION(CLASS_NAME, Condition, TYPE_NAME) 

/** Use this macro in the class declaration of a Condition with author & run time state */
#define CONDITION_WITH_AUTHOR_TIME_AND_RUN_TIME_STATE(CLASS_NAME, TYPE_NAME) \
	AUTHOR_AND_RUN_TIME_IMPLEMENTATION(CLASS_NAME, Condition, TYPE_NAME) 

/** Use this macro in the class declaration of a Condition with run time state */
#define CONDITION_WITH_RUN_TIME_STATE(CLASS_NAME, TYPE_NAME) \
	RUN_TIME_IMPLEMENTATION(CLASS_NAME, Condition, TYPE_NAME) 

/** Use this macro in the class declaration of a StateMachine with no author or run time state */
#define STATE_MACHINE_WITH_AUTHOR_TIME_STATE(CLASS_NAME, TYPE_NAME) \
	RUN_TIME_TYPE_DECLARATION \
	AUTHOR_AND_RUN_TIME_IMPLEMENTATION(CLASS_NAME, StateMachine, TYPE_NAME) 

/** Use this macro in the class declaration of a StateMachine with no author or run time state */
#define STATE_MACHINE_WITHOUT_AUTHOR_TIME_STATE(CLASS_NAME, TYPE_NAME) \
	RUN_TIME_TYPE_DECLARATION \
	RUN_TIME_IMPLEMENTATION(CLASS_NAME, StateMachine, TYPE_NAME) 

/** Use this macro in the class declaration of a TransitionFX with no author or run time state */
#define TRANSITION_FX_PURE(CLASS_NAME, TYPE_NAME) \
	PURE_IMPLEMENTATION(CLASS_NAME, TransitionFX, TYPE_NAME) 

/** Use this macro in the class declaration of a TransitionFX with author time state */
#define TRANSITION_FX_WITH_AUTHOR_TIME_STATE(CLASS_NAME, TYPE_NAME) \
	AUTHOR_TIME_IMPLEMENTATION(CLASS_NAME, TransitionFX, TYPE_NAME) 

/** Use this macro in the class declaration of a TransitionFX with author & run time state */
#define TRANSITION_FX_WITH_AUTHOR_TIME_AND_RUN_TIME_STATE(CLASS_NAME, TYPE_NAME) \
	AUTHOR_AND_RUN_TIME_IMPLEMENTATION(CLASS_NAME, TransitionFX, TYPE_NAME) 

/** Use this macro in the class declaration of a TransitionFX with run time state */
#define TRANSITION_FX_WITH_RUN_TIME_STATE(CLASS_NAME, TYPE_NAME) \
	RUN_TIME_IMPLEMENTATION(CLASS_NAME, TransitionFX, TYPE_NAME) 

namespace HFSM
{

typedef signed int StateKey;
typedef signed int ConnectionKey;
typedef signed int Depth;

static const ConnectionKey InitialCauseKey(-1);
static const ConnectionKey NoSatisfiedCondition(-1);
static const StateKey InitialStateKey(0);
static const StateKey InvalidStateKey(-1);

template<typename AGENT> class ActionState;
template<typename AGENT> class Condition;
template<typename AGENT> class StateMachine; 
template<typename AGENT> class TransitionFX;
template<typename AGENT> class Traversal;
struct TraversalEntry;

void test(void);

/**
\class ActionState

abstract base class for any single action that can be
executed by the template AGENT.  It can be used
on its own as well as part of a state machine.
*/
template<typename AGENT>
class ActionState
{	
	/** 
	by default ActionStates have custom RTTI, in order to support querying
	whether or not a traversal is in a certain state by type 
	*/
	RUN_TIME_TYPE_DECLARATION

	friend class StateMachine<AGENT>;
		
public:
	/** override this to perform an action with the agent */
	virtual void act(AGENT&)=0; 

	/**
	This is called every time a state is entered by the
	agent during traversal. Afterwards only act() is called.
	Override this for custom functionality.
	*/
	virtual void enter(AGENT&) 
	{ 
		/* empty */ 
	}

	/**
	This is called every time a state is exited by the
	agent during traversal. 
	Override this for custom functionality.
	*/
	virtual void exit(AGENT&) 
	{ 
		/* empty */ 
	}
	
	/** 
	Factory system compatibility.  
	Override this function for traversal time state.
	Override or use the Factory system macros.
	\see AuthorTimeRunTimeFactory.h for more info.
	*/
	virtual bool hasRunTimeState(void) const=0;

	/** override this if the action is completable */
	virtual bool isCompletable(Traversal<AGENT>& /*traversal*/) const
	{
		return false;
	}

	/** 
	override this when the action is completed, and make sure to
	override isCompletable() as well
	*/
	virtual bool isComplete(Traversal<AGENT>& traversal) const
	{
		return isCompletable(traversal) && false;
	}

	/** 
	Factory system compatibility.  
	Override this function for traversal time memory management.
	Override or use the Factory system macros.
	\see AuthorTimeRunTimeFactory.h for more info.
	*/
	virtual void recycle(void)=0;

protected:
	/** 
	Factory system compatibility.  
	Only the Factory can create/destroy these objects.
	\see AuthorTimeRunTimeFactory.h for more info.
	*/
	ActionState(void)
	{
		/* empty */
	}

	/** 
	Factory system compatibility.  
	Only the Factory can create/destroy these objects.
	\see AuthorTimeRunTimeFactory.h for more info.
	*/
	virtual ~ActionState(void)
	{
		/* empty */
	}

	/** a helper function for the traversal */
	virtual Depth calculateDepth(void) const
	{
		return 0;
	}

	/** 
	Factory system compatibility.  
	Override this function for traversal time copies.
	Override or use the Factory system macros.
	\see AuthorTimeRunTimeFactory.h for more info.
	*/
	virtual ActionState<AGENT>* getRunTimeCopy(void) const=0;
		
	/** 
	Traversal accounting function
	\warning Do not override this!
	*/
	virtual void recordAction(Traversal<AGENT>& traversal)
	{
		act(traversal.agent);
	}

	/** 
	Traversal accounting function
	\warning Do not override this!
	*/
	virtual void recordEntry(Traversal<AGENT>& traversal) 
	{	
		enter(traversal.agent);
	}

	/** 
	Traversal accounting function
	\warning Do not override this!
	*/
	virtual void recordExit(Traversal<AGENT>& traversal)
	{	
		exit(traversal.agent);
	}

	/** 
	Factory system compatibility.  
	Override this function for alternative memory management.
	Override or use the Factory system macros.
	\see AuthorTimeRunTimeFactory.h for more info.
	*/
	virtual void recycleRunTimeCopy(void) { delete this; }
}; // class ActionState

/**
\class Condition
\brief predicate objects that create the transitions between states
in a state machine.

Override isSatisfied(). If it returns true, the condition
The machine will transition to the state connected via this
connection.
*/
template<typename AGENT>
class Condition
{
	friend class StateMachine<AGENT>;

public:
	
	/** 
	Factory system compatibility.  
	Override this function for traversal time state.
	Override or use the Factory system macros.
	\see AuthorTimeRunTimeFactory.h for more info.
	*/
	virtual bool hasRunTimeState(void) const=0;

	/** returns true if the Condition is satisfied */
	inline bool operator()(AGENT& agent)
	{
		return isSatisfied(agent);
	}

	/** 
	Factory system compatibility.  
	Override this function for traversal time memory management.
	Override or use the Factory system macros.
	\see AuthorTimeRunTimeFactory.h for more info.
	*/
	virtual void recycle(void)=0;
	
protected:
	/** 
	Factory system compatibility.  
	Only the Factory can create/destroy these objects.
	\see AuthorTimeRunTimeFactory.h for more info.
	*/
	Condition(void)
	{
		/* empty */
	}

	/** 
	Factory system compatibility.  
	Only the Factory can create/destroy these objects.
	\see AuthorTimeRunTimeFactory.h for more info.
	*/
	virtual ~Condition(void) 
	{
		/* empty */
	}

	/** called when an agent enters a state from which this Condition is connected */
	virtual void enter(AGENT& /*agent*/)
	{
		// empty
	}

	/** called when an agent exits a state from which this Condition is connected */
	virtual void exit(AGENT& /*agent*/)
	{
		// empty
	}
	
	/** 
	Factory system compatibility.  
	Override this function for traversal time copies.
	Override or use the Factory system macros.
	\see AuthorTimeRunTimeFactory.h for more info.
	*/
	virtual Condition<AGENT>* getRunTimeCopy(void) const=0;

	/** override this for your custom functionality */
	virtual bool isSatisfied(AGENT& /*agent*/)=0;
	
	/** 
	Factory system compatibility.  
	Override this function for memory management.
	Override or use the Factory system macros.
	\see AuthorTimeRunTimeFactory.h for more info.
	*/
	virtual void recycleRunTimeCopy(void) { delete this; }

public:	
	inline bool and(AGENT& agent, bool rhs) 
	{
		return rhs && isSatisfied(agent);
	}

	inline bool and(AGENT& agent, Condition<AGENT>& rhs)
	{
		return isSatisfied(agent) && rhs.isSatisfied(agent);
	}

	inline bool not(AGENT& agent)
	{
		return !isSatisfied(agent);
	}

	inline bool or(AGENT& agent, bool rhs) 
	{
		return rhs || isSatisfied(agent);
	}

	inline bool or(AGENT& agent, Condition<AGENT>& rhs)
	{
		return isSatisfied(agent) || rhs.isSatisfied(agent);
	}

	inline bool xor(AGENT& agent, bool rhs) 
	{
		return isSatisfied(agent) ^ rhs;
	}

	inline bool xor(AGENT& agent, Condition<AGENT>& rhs)
	{
		return isSatisfied(agent) ^ rhs.isSatisfied(agent);
	}

}; // Condition

/**
The StateMachine handles the connections and transition
effects between states.

\note Custom StateMachines are created solely be deriving from
StateMachine and adding ActionStates, and connecting them with
Conditions and [optional] TransitionFX.

\see a silly example of full authorship and use at the bottom
of this file.

\warning Be very careful to override only the appropriate functions
when deriving from StateMachine.  That is, DO NOT override
act(), onEnter(), or onExit(), instead override
onMachineAct(), onMachineEnter(), and onMachineExit().
*/
template<typename AGENT>
class StateMachine 
	: public ActionState<AGENT>
{
	template<typename AGENT> class Connection;
	template<typename AGENT> class State;
	friend class Traversal<AGENT>;

	typedef std::vector< State<AGENT>* > States;
	typedef std::vector< Connection<AGENT> > Connections;


	RUN_TIME_TYPE_DECLARATION
	/** all state machines have author time state */
	static const bool hasAuthorTimeState = true;

protected:
	
	/** 
	Factory system compatibility.  
	Only the Factory can create/destroy these objects.
	\see AuthorTimeRunTimeFactory.h for more info.
	*/
	StateMachine()
		: ActionState()
	{
		/* empty */
	}
	
	/** 
	Factory system compatibility.  
	Only the Factory can create/destroy these objects.
	\see AuthorTimeRunTimeFactory.h for more info.
	*/
	StateMachine(const StateMachine<AGENT>& source)
	{	
		for (States::const_iterator i(source.states.begin()), i_sentinel(source.states.end())
			; i != i_sentinel
			; ++i)
		{
			ActionState<AGENT>* actionState((*i)->state.getRunTimeCopy());
			assert(actionState);
			add(*actionState);
		}

		for (StateKey from(0), sentinel(source.states.size())
			; from < sentinel
			; ++from)
		{
			const State<AGENT>& state(*source.states[from]);

			for (Connections::const_iterator j(state.connections.begin()), j_sentinel(state.connections.end())
				; j != j_sentinel
				; ++j)
			{
				const Connection<AGENT>& connection(*j);
				Condition<AGENT>* duplicateCause(connection.condition.getRunTimeCopy());
				assert(duplicateCause);
				Condition<AGENT>& cause(*duplicateCause); 
				TransitionFX<AGENT>* fx(connection.fx ? connection.fx->getRunTimeCopy() : NULL);
				const StateKey to(connection.next);
				connect(from, cause, to, fx);
			}
		}
	}

	/** 
	Factory system compatibility.  
	Only the Factory can create/destroy these objects.
	\see AuthorTimeRunTimeFactory.h for more info.
	*/
	~StateMachine(void)
	{	// a distinction has to be made between deleting the runtime copies of StateMachines
		// and deleting the authoring copies of StateMachines
		std::for_each(states.begin(), states.end(), &deleteObject< State<AGENT> >);
	}

	/** override to perform a custom action at the state-machine (non-leaf state) level */
	virtual void act(AGENT&)
	{
		// empty
	}

	/** 
	adds an ActionState to the state machine, and returns a key
	the first state added is the initial state
	to allow connection the state to another (previously added state) via a Condition 
	*/
	StateKey add(ActionState<AGENT>& actionState) 
	{
		State<AGENT>* state(new State<AGENT>(actionState));
		StateKey actionKey(states.size());
		states.push_back(state);
		return actionKey;
	}
	
	/**
	creates a connection between to states.  If the cause condition is satisfied during a traversal
	the agent will exit the from state, cause the TransitionFX, and enter the to state.

	conditions are evaluated in order of calls to connect()
	*/
	void connect(StateKey from, Condition<AGENT>& cause, StateKey to, TransitionFX<AGENT>* fx=NULL)
	{
		State<AGENT>* fromState = states[from];
		assert(fromState != NULL);
		assert(states[to] != NULL);
		fromState->connections.push_back(Connection<AGENT>(cause, fx, to));
	}
			
	/** 
	Factory system compatibility.  
	Override this function for alternative memory management.
	Override or use the Factory system macros.
	\see AuthorTimeRunTimeFactory.h for more info.
	*/
	virtual void recycleRunTimeCopy(void)
	{
		std::for_each(states.begin(), states.end(), RecycleState<AGENT>());
		delete this;
	}

protected:
	template<typename AGENT>
	class Connection
	{
	public:
		inline Connection(Condition<AGENT>& cause, TransitionFX<AGENT>* transFX, StateKey nextState)
			: condition(cause)
			, fx(transFX)
			, next(nextState)
		{
			/* empty */
		}

		inline void enter(AGENT& agent)
		{
			condition.enter(agent);	
			
			if (fx)
			{
				fx->enter(agent);
			}
		}

		inline void exit(AGENT& agent)
		{
			condition.exit(agent);
			
			if (fx)
			{
				fx->exit(agent);
			}
		}

		Condition<AGENT>& condition;
		StateKey next;
		TransitionFX<AGENT>* fx;

	private:
		Connection<AGENT>& operator=(const Connection<AGENT>&);
	}; // struct Connection


	template<typename AGENT>
	struct EnterConnection
	{
		AGENT& agent;

		inline EnterConnection(AGENT& a) : agent(a) {}

		inline void operator()(Connection<AGENT>& connection)
		{
			connection.enter(agent);
		}

	private:
		EnterConnection& operator=(const EnterConnection&);
	}; // struct EnterConnection


	template<typename AGENT>
	struct ExitConnection
	{
		AGENT& agent;

		inline ExitConnection(AGENT& a) : agent(a) {}

		inline void operator()(Connection<AGENT>& connection)
		{
			connection.exit(agent);
		}
	private:
		ExitConnection& operator=(const ExitConnection&);
	}; // struct ExitConnection

	template<typename AGENT>
	struct RecycleConnection
	{
		inline void operator()(Connection<AGENT>& connection)
		{
			if (connection.fx)
			{
				connection.fx->recycle();
			}

			connection.condition.recycle();
		}
	}; // struct RecycleConnection

	template<typename AGENT>
	struct RecycleState
	{
		inline void operator()(State<AGENT>* state)
		{
			state->recycle();
		}
	}; // struct RecycleState

	template<typename AGENT>
	class State
	{
	
	public:
		inline State(ActionState<AGENT>& newState) 
			: state(newState)
		{
			/* empty */
		}

		~State()
		{
			/* empty */
		}

		inline void enter(AGENT& agent)
		{
			std::for_each(connections.begin(), connections.end(), EnterConnection<AGENT>(agent));	
		}

		inline void exit(AGENT& agent)
		{
			std::for_each(connections.begin(), connections.end(), ExitConnection<AGENT>(agent));	
		}
		
		inline void recycle(void)
		{
			std::for_each(connections.begin(), connections.end(), RecycleConnection<AGENT>());		
			state.recycle();
		}

		Connections connections;
		ActionState<AGENT>& state;

	private:
		State<AGENT>& operator=(const State<AGENT>&);
	}; // class State
	
	inline StateKey getNumStates(void) const
	{
		return states.size();
	}

	inline State<AGENT>* getState(StateKey key) const
	{
		assert(key < static_cast<StateKey>(states.size()));
		assert(key >= 0);
		return states[key];
	}

	/** 
	Factory system compatibility.  
	There should be no reason to override this, just derive from the StateMachine,
	and author your desired machine using the factory methods in your constructor.
	Whether a StateMachine has state at run time is entirely determined by the 
	child states that it governs.
	\see AuthorTimeRunTimeFactory.h for more info.
	*/
	virtual bool hasRunTimeState(void) const
	{
		for (States::const_iterator i(states.begin()), sentinel(states.end())
			; i != sentinel
			; ++i)
		{
			const State<AGENT>& state(*(*i));

			if (state.state.hasRunTimeState())
			{
				return true;
			}
			else
			{
				const Connections& connections(state.connections);

				for (int i(0), sentinel(connections.size()); i < sentinel; ++i)
				{
					const Connection<AGENT>& connection(connections[i]);

					if (connection.condition.hasRunTimeState()
					|| (connection.fx && connection.fx->hasRunTimeState()))
					{
						return true;
					}
				}
			}
		}

		return false;
	}
	
private:
	virtual Depth calculateDepth(void) const
	{
		Depth maxChildDepth(0);

		for (States::const_iterator iter(states.begin()), sentinel(states.end()); 
			iter != sentinel; 
			++iter)
		{	
			Depth currentDepth((*iter)->state.calculateDepth());

			if (currentDepth > maxChildDepth)
			{
				maxChildDepth = currentDepth;
			}
		}

		return maxChildDepth + 1;
	}

	inline void causeTransitionFX(Connection<AGENT>& connection, State<AGENT>& current, AGENT& agent)
	{
		if (connection.fx)
		{	
			assert(getState(connection.next));
			ActionState<AGENT>& nextAction(getState(connection.next)->state);
			connection.fx->effect(agent, *this, current.state, nextAction);
		}
	}
		
	inline void enterCurrent(Traversal<AGENT>& traversal)
	{	
		State<AGENT>* current(getCurrentStateAtThisDepth(traversal));
		assert(current);
		current->enter(traversal.agent);
		current->state.recordEntry(traversal);
	}

	inline void enterNextState(Traversal<AGENT>& traversal, ConnectionKey causeKey, Connection<AGENT>& connection)
	{
		traversal.enter(causeKey, connection.next);
		enterCurrent(traversal);
	}

	inline void exitPreviousState(Traversal<AGENT>& traversal, State<AGENT>& current)
	{
		current.state.recordExit(traversal);
		current.exit(traversal.agent);
		traversal.exit(); // this will become unecessary...I think
	}
	
	inline ConnectionKey evaluateConditions(Traversal<AGENT>& traversal, State<AGENT>* current)
	{
		Connections& connections(current->connections);
		
		for (ConnectionKey connectionKey(0), sentinel(connections.size()); connectionKey < sentinel; ++connectionKey)
		{
			Connection<AGENT>& connection(connections[connectionKey]);

			if (connection.condition(traversal.agent))
			{
				return connectionKey;
			}
		}

		return NoSatisfiedCondition;
	}
	
	inline State<AGENT>* getCurrentState(Traversal<AGENT>& traversal) const
	{
		const StateMachine<AGENT>* machine(this);
		Depth depth(0);

		while (depth < traversal.getDepth())
		{
			machine = static_cast<const StateMachine<AGENT>*>(&machine->states[traversal.getState(depth)]->state);
			++depth;
		}

		return machine->states[traversal.getState()];
	}

	inline State<AGENT>* getCurrentStateAtThisDepth(Traversal<AGENT>& traversal) const
	{
		return getState(traversal.getState());
	}
	
	virtual bool isInState(const Traversal<AGENT>& traversal, const designPatterns::RunTimeType& type) const
	{
		const StateMachine<AGENT>* machine(this);
		Depth depth(0);

		while (depth < traversal.getDepth())
		{
			machine = static_cast<const StateMachine<AGENT>*>(&machine->states[traversal.getState(depth)]->state);

			if (machine->getRunTimeType().IS_A(type))
				return true;

			++depth;
		}

		return machine->states[traversal.getState()]->state.getRunTimeType().IS_A(type);
	}

	virtual bool isInState(const Traversal<AGENT>& traversal, const ActionState<AGENT>& state) const
	{
		const StateMachine<AGENT>* machine(this);
		Depth depth(0);

		while (depth < traversal.getDepth())
		{
			machine = static_cast<const StateMachine<AGENT>*>(&machine->states[traversal.getState(depth)]->state);

			if (machine == &state)
				return true;

			++depth;
		}

		return &(machine->states[traversal.getState()]->state) == &state;
	}
	
	/**
	calls derived act() if there is one
	then, evaluates conditions on the current state in order of connection
	if a satisfied condition is found, it plays the transitionfx and moves to the next state
	*/
	virtual void recordAction(Traversal<AGENT>& traversal)
	{
		act(traversal.agent);
		traversal.incrementDepth();
		// printf("acting on %s\n", name);
		State<AGENT>* current(getCurrentStateAtThisDepth(traversal));
		assert(current);
		ConnectionKey causeKey(evaluateConditions(traversal, current));

		if (causeKey == NoSatisfiedCondition)
		{	// no reason to transfer to another state, so act on the current state
			current->state.recordAction(traversal);
		}
		else
		{	// a condition is satisfied
			Connection<AGENT>& connection(current->connections[causeKey]);
			exitPreviousState(traversal, *current);
			causeTransitionFX(connection, *current, traversal.agent);
			enterNextState(traversal, causeKey, connection);
		}	
	}

	/**
	entering a state machine enters all initial states of child
	state machines until a leaf state is entered
	*/
	virtual void recordEntry(Traversal<AGENT>& traversal)
	{	
		enter(traversal.agent);
		traversal.enter(InitialCauseKey, 0);
		enterCurrent(traversal);
	}

	/**
	exiting a state machines exits all current states of 
	on the traversal from the current level
	*/
	virtual void recordExit(Traversal<AGENT>& traversal)
	{	
		traversal.incrementDepth();
		State<AGENT>* current(getCurrentStateAtThisDepth(traversal));
		current->state.recordExit(traversal);
		traversal.exit();
		exit(traversal.agent);
	}
		
private:
	typedef States States;
	States states;
}; // class StateMachine

/**
States connected in a machine can optionally have a TransitionFX hooked 
up to them.  During traversal, if an agent leaves the one state
and enters another, it will call the connected TransitionFX::effect() 
function.  The motivation for this is to reduce the number of 
ActionStates that differ only by onEnter()/onExit() functionality.
*/
template<typename AGENT>
class TransitionFX
{
	friend class StateMachine<AGENT>;

public:
	/** called when an agent travels between one state an another */
	virtual void effect(
		AGENT& /*agent*/, 
		const ActionState<AGENT>& /*master*/, 
		const ActionState<AGENT>& /*from*/, 
		const ActionState<AGENT>& /*to*/)=0;
	
	/** 
	Factory system compatibility.  
	Override this function for traversal time memory management.
	Override or use the Factory system macros.
	\see AuthorTimeRunTimeFactory.h for more info.
	*/
	virtual void recycle(void)=0;

protected:
	/** 
	Factory system compatibility.  
	Only the Factory can create/destroy these objects.
	\see AuthorTimeRunTimeFactory.h for more info.
	*/
	TransitionFX()
	{
		/* empty */
	}

	/** 
	Factory system compatibility.  
	Only the Factory can create/destroy these objects.
	\see AuthorTimeRunTimeFactory.h for more info.
	*/
	virtual ~TransitionFX(void)
	{
		/* empty */
	}

	/** called when an agent enters a state from which this TransitionFX is connected */
	virtual void enter(AGENT& /*agent*/)
	{
		// empty
	}

	/** called when an agent exits a state from which this TransitionFX is connected */
	virtual void exit(AGENT& /*agent*/)
	{
		// empty
	}

	/** 
	Factory system compatibility.  
	Override this function for traversal time copies.
	Override or use the Factory system macros.
	\see AuthorTimeRunTimeFactory.h for more info.
	*/
	virtual TransitionFX<AGENT>* getRunTimeCopy(void) const=0;

	/** 
	Factory system compatibility.  
	Override this function for traversal time state.
	Override or use the Factory system macros.
	\see AuthorTimeRunTimeFactory.h for more info.
	*/
	virtual bool hasRunTimeState(void) const=0;
	
	/** 
	Factory system compatibility.  
	Override this function for alternative memory management.
	Override or use the Factory system macros.
	\see AuthorTimeRunTimeFactory.h for more info.
	*/
	virtual void recycleRunTimeCopy(void)
	{
		delete this;
	}

private:
	TransitionFX& operator=(const TransitionFX&);

	int id;
}; // TransistionFX

/**
This is the class that is used to traverse a state machine
with an AGENT.
*/
template<typename AGENT>
class Traversal
{	
	friend class StateMachine<AGENT>;
	typedef std::vector<TraversalEntry> TraversalEntries;

public:
	AGENT& agent;

	Traversal(AGENT& traveller)
		: agent(traveller)
		, stateMachine(NULL)
		, currentDepth(-1)
		, isInActiveState(false)
	{
		/* empty */
	}

	/** this will cause one action to occur with the current state machine (assuming there is one) */
	void act(void)
	{
		if (isInActiveState)
		{
			currentDepth = -1; 
			stateMachine->recordAction(*this);
		}
	}
	
	/** returns true iff at any point in the current traversal the agent is in the passed in state */
	bool isInState(const ActionState<AGENT>& state)
	{
		return isInActiveState && (stateMachine == &state || stateMachine->isInState(state));
	}

	/** returns true iff at any point in the current traversal the agent is in an instance of the passed in type */
	bool isInState(const designPatterns::RunTimeType& type) const
	{
		return isInActiveState && (stateMachine->getRunTimeType().IS_A(type) || stateMachine->isInState(*this, type));
	}
	
	/** 
	starts the traversal of a machine by entering into the machine and the initial leaf action state,
	no conditions get evaluated at this time
	*/ 
	void start(StateMachine<AGENT>& machine)
	{
		if (stateMachine && (&machine != stateMachine))
		{
			stop();
		}
	
		if (stateMachine != &machine || (!isInActiveState))
		{
			stateMachine = &machine;
			isInActiveState = true;
			startTraversal();
		}
	}

	/**
	exits the machine if it is in one
	*/
	void stop(void)
	{
		if (isInActiveState)
		{
			currentDepth = -1;
			stateMachine->recordExit(*this);
			isInActiveState = false;
		}	
	}
	
	/** prints the indices of the current depth of the traversal */
	void printState(void) const
	{
		if (isInActiveState && currentDepth >= 0)
		{
			printf("Depth: %2d, State: %2d, Value: %2d\n", currentDepth, traversal[currentDepth].state, (currentDepth * 3) + traversal[currentDepth].state + 1);
		}
		else
		{
			printf("Not Traversing anywhere!\n");
		}
	}

protected: 
	inline void enter(ConnectionKey cause, StateKey state)
	{
		++currentDepth;
		assert(isValidDepth(currentDepth));
		traversal[currentDepth].set(cause, state);
	}

	inline void exit(void)
	{
		assert(isValid());
		traversal[currentDepth].state = InvalidStateKey;
		--currentDepth;
	}

	inline ConnectionKey getCause(void) const
	{
		assert(isValid());
		return traversal[currentDepth].cause;
	}

	inline Depth getDepth(void) const
	{
		return currentDepth;
	}

	inline StateKey getState(void) const
	{
		assert(isValid());
		return traversal[currentDepth].state;
	}

	inline StateKey getState(Depth depth) const
	{
		assert(isValidDepth(depth));
		return traversal[depth].state;
	}

	inline void incrementDepth(void)
	{
		++currentDepth;
	}
	
	inline bool isValid(void) const
	{
		return isValidDepth(currentDepth) && traversal[currentDepth].state != InvalidStateKey;
	}

	inline bool isValidDepth(Depth depth) const
	{
		return depth >= 0 
			&& depth < static_cast<Depth>(traversal.size()); 
	}
				
	inline void setMaxDepth(Depth depth)
	{
		traversal.resize(depth);
	}

	inline void startTraversal(void)
	{	// initialize capacity
		setMaxDepth(stateMachine->calculateDepth());
		// initialize traversal information
		currentDepth = -1;
		// enter the machine for the first time
		stateMachine->recordEntry(*this);
	}
		
private:
	Traversal<AGENT>& operator=(const Traversal<AGENT>&);

	TraversalEntries traversal;
	StateMachine<AGENT>* stateMachine;
	Depth currentDepth;
	bool isInActiveState;
}; // Traversal

/** 
this is essentially an internal record-keeping class
for the Traversal, but isn't template dependent 
*/
struct TraversalEntry 
{
	StateKey state;
	ConnectionKey cause; 

	inline TraversalEntry(void) 
		: state(InvalidStateKey)
		, cause(InitialCauseKey)
	{
		/* empty */
	}

	inline void set(ConnectionKey c, StateKey s) 
	{
		cause = c;
		state = s;
	}
}; // TraversalEntry

DEFINE_TEMPLATE_BASE_RUN_TIME_TYPE(AGENT, ActionState, NULL)
DEFINE_TEMPLATE_DERIVED_RUN_TIME_TYPE(AGENT, StateMachine, ActionState<AGENT>, NULL)
} // namespace HFSM

/**
\code
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

// at runtime somewhere:
void runAlarmExample()
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
\endcode
*/

#endif//HIERARCHICAL_FSM
