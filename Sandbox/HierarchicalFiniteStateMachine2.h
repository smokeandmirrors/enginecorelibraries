#pragma once
#ifndef HierarchicalFiniteStateMachine2
#define HierarchicalFiniteStateMachine2

/**

*/

#include "Platform.h"
#include "AuthorTimeRunTimeFactory.h"

#include <algorithm>
#include <vector>

#define HAS_AUTHOR_TIME_STATE_false(CLASS_NAME) \
	bool isEqualToAtAuthorTime(const CLASS_NAME##&) const { return true; } \
	static const bool hasAuthorTimeState = false;

#define HAS_AUTHOR_TIME_STATE_true(CLASS_NAME) \
	bool isEqualToAtAuthorTime(const CLASS_NAME##& other) const; \
	static const bool hasAuthorTimeState = true;

#define HAS_RUN_TIME_STATE(VALUE) \
	virtual bool hasRunTimeState(void) const { return VALUE; } 

#define IMPLEMENTATION(CLASS_NAME, FSM_TYPE, TYPE_NAME, AUTHOR_TIME, RUN_TIME) \
	public:\
	HAS_AUTHOR_TIME_STATE_##AUTHOR_TIME##( CLASS_NAME ) \
	HAS_RUN_TIME_STATE(RUN_TIME) \
	private:\
	friend class Factory< AUTHOR_TIME >::Internal< CLASS_NAME >; \
	static CLASS_NAME * duplicate(const CLASS_NAME & source) { return new CLASS_NAME (source);  } \
	virtual FSM_TYPE < TYPE_NAME > * getRunTimeCopy(void) const { return NewRunTimeCopy< CLASS_NAME >(*this); } \
	virtual void recycle(void) { RecycleRunTimeCopy< CLASS_NAME >(*this); } \
	CLASS_NAME& operator=(const CLASS_NAME&); 
	
#define AUTHOR_AND_RUN_TIME_IMPLEMENTATION(CLASS_NAME, FSM_TYPE, TYPE_NAME) \
	IMPLEMENTATION(CLASS_NAME, FSM_TYPE, TYPE_NAME, true, true)

#define AUTHOR_TIME_IMPLEMENTATION(CLASS_NAME, FSM_TYPE, TYPE_NAME) \
	IMPLEMENTATION(CLASS_NAME, FSM_TYPE, TYPE_NAME, true, false)

#define PURE_IMPLEMENTATION(CLASS_NAME, FSM_TYPE, TYPE_NAME) \
	IMPLEMENTATION(CLASS_NAME, FSM_TYPE, TYPE_NAME, false, false)

#define RUN_TIME_IMPLEMENTATION(CLASS_NAME, FSM_TYPE, TYPE_NAME) \
	IMPLEMENTATION(CLASS_NAME, FSM_TYPE, TYPE_NAME, false, true)

// author and run time state
#define CONDITION_WITH_AUTHOR_AND_RUN_TIME_STATE(CLASS_NAME, TYPE_NAME) \
	AUTHOR_AND_RUN_TIME_IMPLEMENTATION(CLASS_NAME, Condition, TYPE_NAME) 

#define STATE_WITH_AUTHOR_AND_RUN_TIME_STATE(CLASS_NAME, TYPE_NAME) \
	AUTHOR_AND_RUN_TIME_IMPLEMENTATION(CLASS_NAME, ActionState, TYPE_NAME) 

#define TRANSITION_FX_WITH_AUTHOR_AND_RUN_TIME_STATE(CLASS_NAME, TYPE_NAME) \
	AUTHOR_AND_RUN_TIME_IMPLEMENTATION(CLASS_NAME, TransitionFX, TYPE_NAME) 

// author time state
#define CONDITION_WITH_AUTHOR_STATE(CLASS_NAME, TYPE_NAME) \
	AUTHOR_TIME_IMPLEMENTATION(CLASS_NAME, Condition, TYPE_NAME) 

#define STATE_WITH_AUTHOR_STATE(CLASS_NAME, TYPE_NAME) \
	AUTHOR_TIME_IMPLEMENTATION(CLASS_NAME, ActionState, TYPE_NAME) 

#define TRANSITION_FX_WITH_AUTHOR_STATE(CLASS_NAME, TYPE_NAME) \
	AUTHOR_TIME_IMPLEMENTATION(CLASS_NAME, TransitionFX, TYPE_NAME) 

// run time state
#define CONDITION_WITH_RUN_TIME_STATE(CLASS_NAME, TYPE_NAME) \
	RUN_TIME_IMPLEMENTATION(CLASS_NAME, Condition, TYPE_NAME) 

#define STATE_WITH_RUN_TIME_STATE(CLASS_NAME, TYPE_NAME) \
	RUN_TIME_IMPLEMENTATION(CLASS_NAME, ActionState, TYPE_NAME) 

#define TRANSITION_FX_WITH_RUN_TIME_STATE(CLASS_NAME, TYPE_NAME) \
	RUN_TIME_IMPLEMENTATION(CLASS_NAME, TransitionFX, TYPE_NAME) 

// pure classes
#define PURE_CONDITION(CLASS_NAME, TYPE_NAME) \
	PURE_IMPLEMENTATION(CLASS_NAME, Condition, TYPE_NAME) 

#define PURE_STATE(CLASS_NAME, TYPE_NAME) \
	PURE_IMPLEMENTATION(CLASS_NAME, ActionState, TYPE_NAME) 

#define PURE_TRANSITION_FX(CLASS_NAME, TYPE_NAME) \
	PURE_IMPLEMENTATION(CLASS_NAME, TransitionFX, TYPE_NAME) 


namespace HFSM2
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
class TraversalEntry;

void test(void);

template<typename AGENT>
class ActionState
{	
	friend class Factory<false>::Internal< ActionState<AGENT> >;
	friend class StateMachine<AGENT>;

public:
	static const bool hasAuthorTimeState = false;

	virtual void act(Traversal<AGENT>& agent) 
	{
		printf("act! "); agent.printState();
	}

	virtual Depth calculateDepth(void) const
	{
		return 0;
	}

	void enter(Traversal<AGENT>& agent) 
	{	
		printf("enter! "); agent.printState();
		onEnter(agent); 
	}

	void exit(Traversal<AGENT>& agent)
	{	
		printf("exit! "); agent.printState();
		onExit(agent);
	}

	virtual ActionState<AGENT>* getRunTimeCopy(void) const=0;

	virtual bool isCompletable(Traversal<AGENT>& /*agent*/) const
	{
		return false;
	}

	virtual bool isComplete(Traversal<AGENT>& agent) const
	{
		return isCompletable(agent) && false;
	}

	virtual void recycle(void)=0;

protected:
	ActionState(void)
	{
		/* empty */
	}

	virtual ~ActionState(void)
	{
		/* empty */
	}
	
	virtual void onEnter(Traversal<AGENT>& /*agent*/) 
	{ 
		/* empty */ 
	}

	virtual void onExit(Traversal<AGENT>& /*agent*/) 
	{ 
		/* empty */ 
	}

	virtual bool hasRunTimeState(void) const=0;
}; // class ActionState

template<typename AGENT>
class Condition
{
	// friend class Factory< Condition<AGENT>>;
	friend class Factory<false>::Internal< Condition<AGENT> >;

public:
	virtual Condition<AGENT>* getRunTimeCopy(void) const=0;

	bool operator()(AGENT* agent)
	{
		// printf("isSatisfied() %s\n", name);
		return isSatisfied(agent);
	}

	virtual void recycle(void)=0;

protected:
	static bool hasAuthoringTimeState(void)
	{
		return true;
	}

	Condition(void)
	{
		/* empty */
	}

	virtual ~Condition(void) 
	{
		/* empty */
	}

	virtual bool hasRunTimeState(void) const=0;

	virtual bool isSatisfied(AGENT* /*agent*/)=0;
}; // Condition

template<typename AGENT>
class ConditionFalse
	: public Condition<AGENT>
{
	PURE_CONDITION(ConditionFalse, AGENT)
	
	ConditionFalse(void)
	{
		/* empty */
	}

protected:
	bool isSatisfied(AGENT*) { return false; };
}; // ConditionFalse

template<typename AGENT>
class ConditionTrue
	: public Condition<AGENT>
{
	PURE_CONDITION(ConditionTrue, AGENT)
	
	ConditionTrue(void)
	{
		/* empty */
	}

protected:
	bool isSatisfied(AGENT*) { return true; };
}; // ConditionTrue

/**
never derive from me
*/
template<typename AGENT>
class StateMachine 
	: public ActionState<AGENT>
{
	template<typename AGENT> class State;
	// friend class Factory< StateMachine<AGENT>>;
	friend class Factory<true>::Internal< StateMachine<AGENT> >;
	
public:
	static const bool hasAuthorTimeState = true;

	virtual void act(Traversal<AGENT>& traversal)
	{
		traversal.incrementDepth();
		// printf("acting on %s\n", name);
		State<AGENT>* current(getCurrentStateAtThisDepth(traversal));
		assert(current);
		ConnectionKey causeKey(evaluateConditions(traversal, current));
		
		if (causeKey == NoSatisfiedCondition)
		{	// no reason to transfer to another state, so act on the current state
			current->state.act(traversal);
		}
		else
		{	// a condition is satisfied
			Connection<AGENT>& connection(current->connections[causeKey]);
			exitPreviousState(traversal, *current);
			causeTransitionFX(connection, *current, &traversal.agent);
			enterNextState(traversal, causeKey, connection);
		}	
	}

	StateKey add(ActionState<AGENT>& actionState) 
	{
		State<AGENT>* state(new State<AGENT>(actionState));
		StateKey actionKey(states.size());
		states.push_back(state);
		return actionKey;
	}
	
	virtual Depth calculateDepth(void) const
	{
		Depth maxChildDepth(0);

		for (std::vector< State<AGENT>* >::const_iterator iter(states.begin()), sentinel(states.end()); 
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

	void connect(StateKey from, Condition<AGENT>& cause, StateKey to, TransitionFX<AGENT>* fx=NULL)
	{
		State<AGENT>* fromState = states[from];
		assert(fromState != NULL);
		assert(states[to] != NULL);
		fromState->connections.push_back(Connection<AGENT>(cause, fx, to));
	}
	
	virtual void recycle(void)
	{
		std::for_each(states.begin(), states.end(), RecycleState<AGENT>());		
	}

protected:
	template<typename AGENT>
	class Connection
	{
	public:
		Connection(Condition<AGENT>& cause, TransitionFX<AGENT>* transFX, StateKey nextState)
			: condition(cause)
			, fx(transFX)
			, next(nextState)
		{
			/* empty */
		}
		
		Condition<AGENT>& condition;
		StateKey next;
		TransitionFX<AGENT>* fx;
		
	private:
		Connection<AGENT>& operator=(const Connection<AGENT>&);
	}; // struct Connection

	template<typename AGENT>
	class State
	{
	public:
		State(ActionState<AGENT>& newState) 
			: state(newState)
		{
			/* empty */
		}

		void recycle(void)
		{
			std::for_each(connections.begin(), connections.end(), RecycleConnection<AGENT>());		
			state.recycle();
		}
		
		std::vector<Connection<AGENT>> connections;
		ActionState<AGENT>& state;
	
	private:
		State<AGENT>& operator=(const State<AGENT>&);
	}; // class ActionTuple
	
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
		
	inline void causeTransitionFX(Connection<AGENT>& connection, State<AGENT>& current, AGENT* agent)
	{
		if (connection.fx)
		{	
			assert(getState(connection.next));
			ActionState<AGENT>& nextAction(getState(connection.next)->state);
			connection.fx->effect(agent, *this, current.state, nextAction);
		}
	}

	static StateMachine<AGENT>* duplicate(const StateMachine<AGENT>& source)
	{	// todo reword this with the code below
		return source.duplicate();
	}

	virtual StateMachine<AGENT>* duplicate(void) const
	{
		StateMachine<AGENT>& master(*(new StateMachine<AGENT>));
		
		for (std::vector< State<AGENT>* >::const_iterator i(states.begin()), i_sentinel(states.end())
			; i != i_sentinel
			; ++i)
		{
			ActionState<AGENT>* actionState((*i)->state.getRunTimeCopy());
			assert(actionState);
			master.add(*actionState);
		}

		for (StateKey from(0), sentinel(states.size())
			; from < sentinel
			; ++from)
		{
			const State<AGENT>& state(*states[from]);
			
			for (std::vector< Connection<AGENT> >::const_iterator j(state.connections.begin()), j_sentinel(state.connections.end())
				; j != j_sentinel
				; ++j)
			{
				const Connection<AGENT>& connection(*j);
				Condition<AGENT>* duplicateCause(connection.condition.getRunTimeCopy());
				assert(duplicateCause);
				Condition<AGENT>& cause(*duplicateCause); 
				TransitionFX<AGENT>* fx(connection.fx ? connection.fx->getRunTimeCopy() : NULL);
				const StateKey to(connection.next);
				master.connect(from, cause, to, fx);
			}
		}

		return &master;
	}

	void enterCurrent(Traversal<AGENT>& traversal)
	{	
		State<AGENT>* current(getCurrentStateAtThisDepth(traversal));
		assert(current);
		current->state.enter(traversal);
	}

	inline void enterNextState(Traversal<AGENT>& traversal, ConnectionKey causeKey, Connection<AGENT>& connection)
	{
		traversal.enter(causeKey, connection.next);
		enterCurrent(traversal);
	}

	inline void exitPreviousState(Traversal<AGENT>& traversal, State<AGENT>& current)
	{
		current.state.exit(traversal);
		traversal.exit();
	}
	
	ConnectionKey evaluateConditions(Traversal<AGENT>& traversal, State<AGENT>* current)
	{
		std::vector< Connection<AGENT> >& connections(current->connections);
		
		for (ConnectionKey connectionKey(0), sentinel(connections.size()); connectionKey < sentinel; ++connectionKey)
		{
			Connection<AGENT>& connection(connections[connectionKey]);

			if (connection.condition(&traversal.agent))
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

	virtual StateMachine<AGENT>* getRunTimeCopy(void) const
	{
		return NewRunTimeCopy<StateMachine<Agent>>(*this);
	}

	inline State<AGENT>* getState(StateKey key) const
	{
		assert(key < static_cast<StateKey>(states.size()));
		assert(key >= 0);
		return states[key];
	}
	
	virtual bool hasRunTimeState(void) const
	{
		for (std::vector< State<AGENT>* >::const_iterator i(states.begin()), sentinel(states.end())
			; i != sentinel
			; ++i)
		{
			const State<AGENT>& state(*(*i));

			if (state.state.hasRunTimeState())
			{
				return true;
			}
		}

		return false;
	}

	bool isEqualToAtAuthorTime(const StateMachine<AGENT>& other) const
	{	// \todo make sure this is correct
		return this == &other;
	}

	virtual void onEnter(Traversal<AGENT>& traversal)
	{	
		traversal.enter(InitialCauseKey, 0);
		enterCurrent(traversal);
	}

	virtual void onExit(Traversal<AGENT>& traversal)
	{	
		State<AGENT>* current(getCurrentState(traversal));
		current->state.exit(traversal);
	}
	
private:
	StateMachine()
		: ActionState()
	{
		/* empty */
	}

	~StateMachine(void)
	{
		std::for_each(states.begin(), states.end(), &deleteObject< State<AGENT> >);
	}

	std::vector< State<AGENT>* > states;
}; // class StateMachine

template<typename AGENT>
class TransitionFX
{
	// friend class Factory< TransitionFX<AGENT>>;
	friend class Factory<false>::Internal< TransitionFX<AGENT> >;
	friend class StateMachine<AGENT>;

public:
	virtual void effect(AGENT* /*agent*/, ActionState<AGENT>& /*master*/, ActionState<AGENT>& /*from*/, ActionState<AGENT>& /*to*/)=0;

	virtual void recycle(void)=0;

protected:
	static const bool hasAuthorTimeState = false;
	
	TransitionFX()
	{
		/* empty */
	}

	virtual ~TransitionFX(void)
	{
		/* empty */
	}

	virtual TransitionFX<AGENT>* getRunTimeCopy(void) const=0;

	virtual bool hasRunTimeState(void) const=0;

private:
	int id;
}; // TransistionFX

template<typename AGENT>
class Traversal
{	
	friend class ActionState<AGENT>;
	friend class StateMachine<AGENT>;
	// keeps the agent, current path through the tree (and the required state?)
public:
	AGENT& agent;

	Traversal(AGENT& traveller)
		: agent(traveller)
		, currentDepth(-1)
		, stateMachine(NULL)
	{
		/* empty */
	}

	void act(void)
	{
		currentDepth = -1; 
		stateMachine->act(*this);
	}
	
	ConnectionKey getCause(void) const
	{
		assert(isValid());
		return traversal[currentDepth].cause;
	}

	Depth getDepth(void) const
	{
		return currentDepth;
	}

	StateKey getState(void) const
	{
		assert(isValid());
		return traversal[currentDepth].state;
	}

	StateKey getState(Depth depth) const
	{
		assert(isValidDepth(depth));
		return traversal[depth].state;
	}

	void start(StateMachine<AGENT>& machine)
	{
		if (stateMachine && (&machine) != stateMachine)
		{
			stop();
		}
	
		stateMachine = &machine;
		startTraversal();
	}

	void stop(void)
	{
		if (stateMachine)
		{
			stateMachine->exit(*this);
		}
	}

	void printState(void) const
	{
		if (currentDepth >= 0)
		{
			printf("Depth: %2d, State: %2d, Value: %2d\n", currentDepth, traversal[currentDepth].state, (currentDepth * 3) + traversal[currentDepth].state + 1);
		}
		else
		{
			printf("Not Traversing anywhere!\n");
		}
	}

public: // protected:	
	void enter(ConnectionKey cause, StateKey state)
	{
		++currentDepth;
		assert(isValidDepth(currentDepth));
		traversal[currentDepth].set(cause, state);
	}

	void exit(void)
	{
		assert(isValid());
		traversal[currentDepth].state = InvalidStateKey;
		--currentDepth;
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
				
	void setMaxDepth(Depth depth)
	{
		traversal.resize(depth);
	}

	void startTraversal(void)
	{	// initialize capacity
		setMaxDepth(stateMachine->calculateDepth());
		// initialize traversal information
		currentDepth = -1;
		// enter the machine for the first time
		stateMachine->enter(*this);
	}
		
private:
	Traversal<AGENT>& operator=(const Traversal<AGENT>&);

	std::vector<TraversalEntry> traversal;
	Depth currentDepth;
	StateMachine<AGENT>* stateMachine;
}; // Traversal

class TraversalEntry 
{
public:
	StateKey state;
	ConnectionKey cause; 

	TraversalEntry(void) 
		: state(InvalidStateKey)
		, cause(InitialCauseKey)
	{
		/* empty */
	}

	void set(ConnectionKey c, StateKey s) 
	{
		cause = c;
		state = s;
	}
}; // TraversalEntry

} // namespace HFSM

#endif//HierarchicalFiniteStateMachine2
