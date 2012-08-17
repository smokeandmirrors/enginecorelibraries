#pragma once
#ifndef HierarchicalFiniteStateMachine
#define HierarchicalFiniteStateMachine

/**

*/

#include "Platform.h"

#include <algorithm>
#include <vector>

namespace HFSM
{
	typedef signed int StateKey;
	typedef signed int ConnectionKey;
	typedef signed int Depth;

	static const ConnectionKey InitialCauseKey(-1);
	static const ConnectionKey NoSatisfiedCondition(-1);
	static const StateKey InitialStateKey(0);
	static const StateKey InvalidStateKey(-1);
		
	class TraversalEntry 
	{
	public:
		StateKey state;
		ConnectionKey cause; 

		TraversalEntry(void) : state(InvalidStateKey), cause(InitialCauseKey)
		{
			/* empty */
		}

		void reset(void)
		{
			state = InvalidStateKey;
		}

		void set(ConnectionKey c, StateKey s) 
		{
			cause = c;
			state = s;
		}
	}; // TraversalEntry

template<typename AGENT> class ActionState;
template<typename AGENT> class Condition;
template<typename AGENT> class StateMachine; 
template<typename AGENT> class TransitionFX;
template<typename AGENT> class Traversal;

template<typename AGENT>
class ActionState
{	// \todo debug logging
	// friend class StateMachine<AGENT>;
	friend class StateMachine<AGENT>;

public:
	ActionState(const char* n)
		: name(n)
	{
		/* empty */
	}

	virtual ~ActionState(void)
	{
		/* empty */
	}

	virtual void act(Traversal<AGENT>& /*agent*/) 
	{
		printf("acting on %s\n", name);
	}

	virtual Depth calculateDepth(void) const
	{
		return 0;
	}
	
	void enter(Traversal<AGENT>& agent) 
	{	
		printf("entering %s\n", name);
		onEnter(agent); 
	}

	void exit(Traversal<AGENT>& agent)
	{	
		printf("exiting %s\n", name);
		onExit(agent);
	}

	virtual bool isCompletable(AGENT* /*agent*/) const
	{
		return false;
	}

	virtual bool isComplete(AGENT* agent) const
	{
		return isCompletable(agent) && false;
	}
	
	void reset(Traversal<AGENT>& agent, Depth depth)
	{
		printf("resetting %s\n", name);
		onReset(agent, depth);
		agent.reset(depth);
	}

protected:
	virtual void onEnter(Traversal<AGENT>& /*agent*/) 
	{ 
		/* empty */ 
	}

	virtual void onExit(Traversal<AGENT>& /*agent*/) 
	{ 
		/* empty */ 
	}

	virtual void onReset(Traversal<AGENT>& /*agent*/, Depth /*depth*/)
	{
		/* empty */
	}

	const char* name;
}; // class ActionState

template<typename AGENT>
class Condition
{
	friend class StateMachine<AGENT>;

public:
	Condition(const char* n=NULL)
		: name(n)
	{

	}

	virtual ~Condition(void) 
	{
		/* empty */
	}
	
	bool operator()(AGENT* agent)
	{
		update(agent);
		return isSatisfied(agent);
	}
	
protected:
	virtual bool isSatisfied(AGENT* /*agent*/)=0;

	virtual void reset(AGENT* /*agent*/)
	{
		printf("resetting %s\n", name);
	}

	virtual void update(AGENT* /*agent*/)
	{
		printf("updating/evaluating %s\n", name);
	}

	const char* name;
}; // Condition

template<typename AGENT>
class ConditionFalse
	: public Condition<AGENT>
{
public:
	ConditionFalse(const char* n=NULL)
		: Condition(n)
	{

	}

protected:
	bool isSatisfied(AGENT*) { return false; };
}; // ConditionFalse

template<typename AGENT>
class ConditionTrue
	: public Condition<AGENT>
{
public:
	ConditionTrue(const char* n=NULL)
		: Condition(n)
	{

	}

protected:
	bool isSatisfied(AGENT*) { return true; };
}; // ConditionTrue

template<typename AGENT>
class StateMachine 
	: public ActionState<AGENT>
{
protected:
	template<typename AGENT> class State;

public:
	StateMachine(const char* n=NULL)
		: ActionState<AGENT>(n)
	{
		/* empty */
	}

	~StateMachine(void)
	{
		std::for_each(states.begin(), states.end(), &deleteObject< State<AGENT> >);
	}

	virtual void act(Traversal<AGENT>& traversal)
	{
		traversal.incrementDepth();
		printf("acting on %s\n", name);
		State<AGENT>* current(getCurrentStateAtThisDepth(traversal));
		assert(current);
		ConnectionKey conditionKey(evaluateConditions(traversal.agent, current));
		
		if (conditionKey == NoSatisfiedCondition)
		{	// no reason to transfer to another state, so act on the current state
			current->state.act(traversal);
		}
		else
		{	// a condition is satisfied
			Connection<AGENT>& connection(current->connections[conditionKey]);
			// exit the previous state
			current->state.exit(traversal);
			traversal.exit();
			// cause any transistion effects
			causeTransitionFX(connection, *current, traversal.agent);
			// enter the next state
			traversal.enter(conditionKey, connection.next);
			enterCurrent(traversal);
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

		inline void reset(AGENT* agent)
		{
			condition.reset(agent);
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

		~State(void)
		{
			/* empty release all of the conditions, transitionFX, and states */
		}

		void reset(Traversal<AGENT>& agent, Depth depth)
		{
			// assert(false, "RESET states reset conditions on entry from the state machine level, otherwise the traveller handles resetting of traveller data");
			state.reset(agent, depth);
		}

		std::vector< Connection<AGENT> > connections;
		ActionState<AGENT>& state;
	
	private:
		State<AGENT>& operator=(const State<AGENT>&);
	}; // class ActionTuple
	
	inline void causeTransitionFX(Connection<AGENT>& connection, State<AGENT>& current, AGENT* agent)
	{
		if (connection.fx)
		{	
			assert(getState(connection.next));
			ActionState<AGENT>& nextAction(getState(connection.next)->state);
			connection.fx->effect(agent, *this, current.state, nextAction);
		}
	}

	void enterCurrent(Traversal<AGENT>& traversal)
	{	
		State<AGENT>* current(getCurrentStateAtThisDepth(traversal));
		assert(current);
		
		for (std::vector< Connection<AGENT> >::iterator iter(current->connections.begin()), sentinel(current->connections.end()); 
			iter != sentinel; 
			++iter)
		{	// reset the conditions before entering this state
			Connection<AGENT>& connection(*iter);
			connection.condition.reset(traversal.agent);
		}

		current->state.enter(traversal);
	}
	
	ConnectionKey evaluateConditions(AGENT* agent, State<AGENT>* current)
	{
		std::vector< Connection<AGENT> > connections(current->connections);
		ConnectionKey sentinel(connections.size());
		
		for (ConnectionKey connectionKey(0); connectionKey < sentinel; ++connectionKey)
		{
			Connection<AGENT>& connection(connections[connectionKey]);

			if (connection.condition(agent))
			{
				return connectionKey;
			}
		}

		return NoSatisfiedCondition;
	}
	
	inline State<AGENT>* getCurrentState(Traversal<AGENT>& agent) const
	{
		const StateMachine<AGENT>* machine(this);
		Depth depth(0);

		while (depth < agent.getDepth())
		{
			machine = static_cast<const StateMachine<AGENT>*>(&machine->states[agent.getState(depth)]->state);
			++depth;
		}

		return machine->states[agent.getState()];
	}

	inline State<AGENT>* getCurrentStateAtThisDepth(Traversal<AGENT>& agent) const
	{
		return getState(agent.getState());
	}

	inline State<AGENT>* getState(StateKey key) const
	{
		assert(key < static_cast<StateKey>(states.size()));
		assert(key >= 0);
		return states[key];
	}

	virtual void onEnter(Traversal<AGENT>& agent)
	{
		agent.enter(InitialCauseKey, 0);
		enterCurrent(agent);
	}

	virtual void onExit(Traversal<AGENT>& agent)
	{
		State<AGENT>* current(getCurrentState(agent));
		current->state.exit(agent);
	}

	virtual void onReset(Traversal<AGENT>& agent, Depth depth)
	{	
		for (std::vector< State<AGENT>* >::iterator iter(states.begin()), sentinel(states.end()); 
			iter != sentinel; 
			++iter)
		{	// reset the child states
			printf("reseting all the child states!");
			(*iter)->reset(agent, depth + 1);
		}
	}

private:
	std::vector< State<AGENT>* > states;
}; // class StateMachine

template<typename AGENT>
class Traversal
{	
	friend class ActionState<AGENT>;
	friend class StateMachine<AGENT>;
	// keeps the agent, current path through the tree (and the required state?)
public:
	AGENT* agent;

	Traversal(AGENT* traveller)
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

	void start(StateMachine<AGENT>* hfsm)
	{
		if (stateMachine && hfsm != stateMachine)
		{
			stop();
		}
	
		resetAll();
		stateMachine = hfsm;
		startTraversal();
	}

	void stop(void)
	{
		if (stateMachine)
		{
			stateMachine->exit(*this);
		}
	}

protected:	
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

	void reset(Depth depth)
	{
		assert(isValidDepth(depth));
		traversal[depth].reset();
	}

	void resetAll(void)
	{
		for (unsigned int i = 0; i < traversal.size(); ++i)
		{
			traversal[i].reset();
		}
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
	std::vector<TraversalEntry> traversal;
	Depth currentDepth;
	StateMachine<AGENT>* stateMachine;
}; // Traversal

template<typename AGENT>
class TransitionFX
{
public:
	virtual ~TransitionFX(void)
	{
		/* empty */
	}

	virtual void effect(AGENT* /*agent*/, ActionState<AGENT>& /*master*/, ActionState<AGENT>& /*from*/, ActionState<AGENT>& /*to*/) 
	{
		/* empty */printf("effecting on transition!\n");
	}
}; // TransistionFX

} // namespace HFSM

#endif//HierarchicalFiniteStateMachine
