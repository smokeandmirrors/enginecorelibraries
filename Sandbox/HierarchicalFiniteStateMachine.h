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

	class PersistentDatum
	{
	public:
		virtual ~PersistentDatum(void)=0 { /* empty */ printf("PersistentDatum deleted!\n"); }		
	};

	class TraversalEntry 
	{
	public:
		StateKey state;
		ConnectionKey cause; 
		PersistentDatum* stateDatum;
		std::vector<PersistentDatum*> connectionData;

		TraversalEntry(void) : state(InvalidStateKey), cause(InitialCauseKey), stateDatum(NULL)
		{
			/* empty */
		}

		void set(ConnectionKey c, StateKey s) 
		{
			cause = c;
			state = s;
		}

		void setConditionDatum(ConnectionKey c, PersistentDatum* datum)
		{
			connectionData[c] = datum;
		}

		void setNumConditions(ConnectionKey size)
		{
			connectionData.resize(size);
		}

		void setStateDatum(PersistentDatum* datum)
		{
			stateDatum = datum;
		}

	}; // TraversalEntry
	
template<typename AGENT> class ActionState;
template<typename AGENT> class Condition;
template<typename AGENT> class PersistentData;
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

	virtual void act(Traversal<AGENT>& /*agent*/, PersistentDatum* /*datum*/) 
	{
		printf("acting on %s\n", name);
	}

	virtual Depth calculateDepth(void) const
	{
		return 0;
	}
	
	void enter(Traversal<AGENT>& agent, PersistentDatum* datum) 
	{	
		printf("entering %s\n", name);
		onEnter(agent, datum); 
	}

	void exit(Traversal<AGENT>& agent, PersistentDatum* datum)
	{	
		printf("exiting %s\n", name);
		onExit(agent, datum);
	}

	virtual PersistentDatum* getPersistentDatum(void) const
	{
		return NULL;
	}

	virtual bool isCompletable(Traversal<AGENT>& /*agent*/) const
	{
		return false;
	}

	virtual bool isComplete(Traversal<AGENT>& agent) const
	{
		return isCompletable(agent) && false;
	}

	virtual void recyclePersistentDatum(PersistentDatum* datum) const
	{
		delete datum;
	}
	
protected:
	virtual void onEnter(Traversal<AGENT>& /*agent*/, PersistentDatum* /*datum*/) 
	{ 
		/* empty */ 
	}

	virtual void onExit(Traversal<AGENT>& /*agent*/, PersistentDatum* /*datum*/) 
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
	
	virtual PersistentDatum* getPersistentDatum(void) const
	{
		return NULL;
	}

	void recyclePersistentDatum(PersistentDatum* datum)
	{
		delete datum;
	}

	bool operator()(AGENT* agent, PersistentDatum* datum)
	{
		update(agent, datum);
		return isSatisfied(agent, datum);
	}
	
protected:
	virtual bool isSatisfied(AGENT* /*agent*/, PersistentDatum* /*datum*/)=0;

	virtual void update(AGENT* /*agent*/, PersistentDatum* /*datum*/)
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
	bool isSatisfied(AGENT*, PersistentDatum* /*datum*/) { return false; };
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
	bool isSatisfied(AGENT*, PersistentDatum* /*datum*/) { return true; };
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

	virtual void act(Traversal<AGENT>& traversal, PersistentDatum* /*datum*/)
	{
		traversal.incrementDepth();
		printf("acting on %s\n", name);
		State<AGENT>* current(getCurrentStateAtThisDepth(traversal));
		assert(current);
		ConnectionKey causeKey(evaluateConditions(traversal, current));
		
		if (causeKey == NoSatisfiedCondition)
		{	// no reason to transfer to another state, so act on the current state
			current->state.act(traversal, traversal.getStateDatum());
		}
		else
		{	// a condition is satisfied
			Connection<AGENT>& connection(current->connections[causeKey]);
			exitPreviousState(traversal, *current);
			causeTransitionFX(connection, *current, traversal.agent);
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

		~State(void)
		{
			/* empty release all of the conditions, transitionFX, and states */
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
		PersistentDatum* stateDatum(current->state.getPersistentDatum());
		traversal.setStateDatum(stateDatum);
		
		std::vector< Connection<AGENT> >& connections(current->connections);
		ConnectionKey sentinel(connections.size());
		traversal.setConditionDataSize(sentinel);

		for (ConnectionKey connectionKey(0); connectionKey < sentinel; ++connectionKey)
		{
			Connection<AGENT>& connection(connections[connectionKey]);
			PersistentDatum* datum = connection.condition.getPersistentDatum();
			traversal.setConditionDatum(connectionKey, datum);
		}

		current->state.enter(traversal, stateDatum);
	}

	inline void enterNextState(Traversal<AGENT>& traversal, ConnectionKey causeKey, Connection<AGENT>& connection)
	{
		traversal.enter(causeKey, connection.next);
		enterCurrent(traversal);
	}

	inline void exitPreviousState(Traversal<AGENT>& traversal, State<AGENT>& current)
	{
		PersistentDatum* datum(traversal.getStateDatum());
		current.state.exit(traversal, datum);
		current.state.recyclePersistentDatum(datum);
		
		std::vector< Connection<AGENT> >& connections(current.connections);
		ConnectionKey sentinel(connections.size());
		for (ConnectionKey connectionKey(0); connectionKey < sentinel; ++connectionKey)
		{
			Connection<AGENT>& connection(connections[connectionKey]);
			connection.condition.recyclePersistentDatum(traversal.getConditionDatum(connectionKey));
		}

		traversal.exit();
	}
	
	ConnectionKey evaluateConditions(Traversal<AGENT>& traversal, State<AGENT>* current)
	{
		std::vector< Connection<AGENT> >& connections(current->connections);
		ConnectionKey sentinel(connections.size());
		
		for (ConnectionKey connectionKey(0); connectionKey < sentinel; ++connectionKey)
		{
			Connection<AGENT>& connection(connections[connectionKey]);

			if (connection.condition(traversal.agent, traversal.getConditionDatum(connectionKey)))
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

	inline State<AGENT>* getState(StateKey key) const
	{
		assert(key < static_cast<StateKey>(states.size()));
		assert(key >= 0);
		return states[key];
	}

	virtual void onEnter(Traversal<AGENT>& traversal, PersistentDatum* /*datum*/)
	{	//assert(datum == NULL);
		traversal.enter(InitialCauseKey, 0);
		enterCurrent(traversal);
	}

	virtual void onExit(Traversal<AGENT>& traversal, PersistentDatum* /*datum*/)
	{	//assert(datum == NULL);
		State<AGENT>* current(getCurrentState(traversal));
		current->state.exit(traversal, traversal.getStateDatum());
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
		stateMachine->act(*this, NULL);
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

	PersistentDatum* getConditionDatum(ConnectionKey key) const
	{
		assert(isValid());
		return traversal[currentDepth].connectionData[key];
	}

	PersistentDatum* getStateDatum(void) const
	{
		assert(isValid());
		return traversal[currentDepth].stateDatum;
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

	void setConditionDataSize(ConnectionKey size)
	{
		assert(isValid());
		traversal[currentDepth].connectionData.resize(size);
	}

	void setConditionDatum(ConnectionKey key, PersistentDatum* datum)
	{
		assert(isValid());
		traversal[currentDepth].connectionData[key] = datum;
	}

	void setStateDatum(PersistentDatum* datum)
	{
		assert(isValid());
		traversal[currentDepth].stateDatum = datum;
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
			stateMachine->exit(*this, NULL);
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
		stateMachine->enter(*this, NULL);
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
