#pragma once
#ifndef HierarchicalFiniteStateMachine2
#define HierarchicalFiniteStateMachine2

/**

*/

#include "Platform.h"

#include <algorithm>
#include <vector>

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

struct EmptyStruct 
{
	bool operator==(const EmptyStruct&) const { return true; }
	bool operator!=(const EmptyStruct&) const { return false; }
}; // struct EmptyStruct 

template<typename OBJECT>
class Factory
{
	typedef std::vector<OBJECT*> Objects;

public:
	static void destroyObjects(void)
	{
		for (Objects::iterator i(objects.begin()), sentinel(objects.end())
			; i != sentinel
			; ++i)
		{
			delete *i;
		}
	}

	static OBJECT* getAuthorCopy(void)
	{
		int objectIndex(0);

		if (!OBJECT::hasAuthoringTimeState())
		{
			if (objects.empty())
			{
				objects.push_back(new OBJECT);
			}
		}
		else
		{
			OBJECT candidate;

			if (!has(candidate, objectIndex))
			{
				objectIndex = objects.size();
				objects.push_back(new OBJECT);
			}
		}			

		return objects[objectIndex];
	}
	
	template<typename CONSTRUCTION_ARGS>
	static OBJECT* getAuthorCopy(const CONSTRUCTION_ARGS& args)
	{
		int objectIndex(0);

		if (!OBJECT::hasAuthoringTimeState())
		{
			if (objects.empty())
			{
				objects.push_back(new OBJECT(args));
			}
		}
		else
		{
			OBJECT candidate(args);
			
			if (!has(candidate, objectIndex))
			{
				objectIndex = objects.size();
				objects.push_back(new OBJECT(args));
			}
		}			
		
		return objects[objectIndex];
	}

	static OBJECT* getRunTimeCopy(const OBJECT& object)
	{
		/**
		Does the state have run-time state?
		Return a new copy, every time.

		Does the state have author-time state?
		Return a single copy on a per author-time basis.

		Return a single copy.

		The get run time copy will make a new GetRunTimeCopy for each state, every time.  (Unless the while tree is stateless. At run time.)
		*/
		if (object.hasRunTimeState())
		{
			return object.duplicate();
		}
		else
		{
			return const_cast<OBJECT*>(&object);
		}
	}

	static void recycle(OBJECT& object)
	{
		if (object.hasRunTimeState())
		{
			delete &object;
		}
	}

protected:
	static int has(const OBJECT& object, int& objectIndex)
	{
		objectIndex = -1;

		for (int i(0), sentinel(objects.size()); i < sentinel; ++i)
		{
			if (*objects[i] == object)
			{
				objectIndex = i;
				return true;
			}
		}

		return false;
	}

private:
	static Objects objects;
};

template<typename OBJECT> 
std::vector<OBJECT*> Factory<OBJECT>::objects;

template<typename AGENT>
class ActionState
{	
	friend class Factory<ActionState<AGENT>>;
	friend class StateMachine<AGENT>;

public:
	
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

	virtual ActionState<AGENT>* getRunTimeCopy(void) const=0
	{
		return Factory<ActionState<Agent>>::getRunTimeCopy(*this);
	}

	virtual bool isCompletable(Traversal<AGENT>& /*agent*/) const
	{
		return false;
	}

	virtual bool isComplete(Traversal<AGENT>& agent) const
	{
		return isCompletable(agent) && false;
	}

	bool operator==(const ActionState<AGENT>& other)
	{
		return this == &other;
	}


protected:
	static bool hasAuthoringTimeState(void)
	{
		return true;
	}
	
	ActionState(void)
	{
		/* empty */
	}

	virtual ~ActionState(void)
	{
		/* empty */
	}

	virtual ActionState<AGENT>* duplicate(void) const=0
	{
		return NULL;
	}

	virtual void onEnter(Traversal<AGENT>& /*agent*/) 
	{ 
		/* empty */ 
	}

	virtual void onExit(Traversal<AGENT>& /*agent*/) 
	{ 
		/* empty */ 
	}

	virtual bool hasRunTimeState(void) const=0
	{
		return false;
	}
}; // class ActionState

template<typename AGENT>
class Condition
{
	friend class Factory< Condition<AGENT>>;

public:
	virtual Condition<AGENT>* getRunTimeCopy(void) const=0
	{
		return Factory<Condition<Agent>>::getRunTimeCopy(*this);
	}

	bool operator()(AGENT* agent)
	{
		// printf("isSatisfied() %s\n", name);
		return isSatisfied(agent);
	}

	bool operator==(const Condition<AGENT>& other)
	{
		return this == &other;
	}

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

	virtual Condition<AGENT>* duplicate(void) const=0;

	virtual bool hasRunTimeState(void) const=0
	{
		return false;
	}

	virtual bool isSatisfied(AGENT* /*agent*/)=0;
}; // Condition

template<typename AGENT>
class ConditionFalse
	: public Condition<AGENT>
{

	friend class Factory< ConditionFalse<AGENT> >;

public:
	virtual ConditionFalse<AGENT>* getRunTimeCopy(void) const
	{
		return Factory<ConditionFalse<Agent>>::getRunTimeCopy(*this);
	}

	bool operator==(const ConditionFalse<AGENT>& other)
	{
		return this == &other;
	}

protected:
	static bool hasAuthoringTimeState(void)
	{
		return true;
	}

	ConditionFalse(void)
	{
		/* empty */
	}

	virtual ConditionFalse<AGENT>* duplicate(void) const
	{
		return new ConditionFalse<AGENT>;
	}

	virtual bool hasRunTimeState(void) const
	{
		return false;
	}

	bool isSatisfied(AGENT*) { return false; };
}; // ConditionFalse

template<typename AGENT>
class ConditionTrue
	: public Condition<AGENT>
{
	friend class Factory< ConditionTrue<AGENT> >;

public:
	virtual ConditionTrue<AGENT>* getRunTimeCopy(void) const
	{
		return Factory<ConditionTrue<Agent>>::getRunTimeCopy(*this);
	}

	bool operator==(const ConditionTrue<AGENT>& other)
	{
		return this == &other;
	}

protected:
	static bool hasAuthoringTimeState(void)
	{
		return true;
	}

	ConditionTrue(void)
	{
		/* empty */
	}

	virtual ConditionTrue<AGENT>* duplicate(void) const
	{
		return new ConditionTrue<AGENT>;
	}

	virtual bool hasRunTimeState(void) const
	{
		return false;
	}

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
	friend class Factory< StateMachine<AGENT>>;

public:
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

	bool operator==(const StateMachine<AGENT>& other)
	{
		return this == &other;
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
	
	static bool hasAuthoringTimeState(void)
	{
		return true;
	}
	
	inline void causeTransitionFX(Connection<AGENT>& connection, State<AGENT>& current, AGENT* agent)
	{
		if (connection.fx)
		{	
			assert(getState(connection.next));
			ActionState<AGENT>& nextAction(getState(connection.next)->state);
			connection.fx->effect(agent, *this, current.state, nextAction);
		}
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
		return Factory<StateMachine<Agent>>::getRunTimeCopy(*this);
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
	friend class Factory< TransitionFX<AGENT>>;
	friend class StateMachine<AGENT>;

public:
	virtual void effect(AGENT* /*agent*/, ActionState<AGENT>& /*master*/, ActionState<AGENT>& /*from*/, ActionState<AGENT>& /*to*/)=0
	{
		/* empty */
		printf("effecting on transition!\n");
	}

	bool operator==(const TransitionFX<AGENT>& other)
	{
		return this == &other;
	}
		
protected:
	static bool hasAuthoringTimeState(void)
	{
		return true;
	}
	
	TransitionFX()
	{
		/* empty */
	}

	virtual ~TransitionFX(void)
	{
		/* empty */
	}

	virtual TransitionFX<AGENT>* duplicate(void) const=0
	{
		return new TransitionFX<AGENT>;
	}

	virtual TransitionFX<AGENT>* getRunTimeCopy(void) const=0
	{
		return Factory<TransitionFX<Agent>>::getRunTimeCopy(*this);
	}

	virtual bool hasRunTimeState(void) const=0
	{
		return false;
	}

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
