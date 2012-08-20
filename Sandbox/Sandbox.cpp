#include "Sandbox.h"

#include "BinaryHeap.h"
#include "A_Star.h"
#include "Composition.h"
#include "HierarchicalFiniteStateMachine.h"
#include "Numbers.h"
#include "RedBlackMap.h"
#include "Strings.h"
#include "Vector.h"
#include "UnitTestVerification.h"
#include "Table.h"
#include "LuaExtensionInclusions.h"
#include "Thread.h"

const char* megaString = ""
"abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz123456789012345678901";

typedef std::string TestStringType; // String::Immutable

using namespace designPatterns;
using namespace containers;
using namespace embeddedLua;
using namespace HFSM;

class Agent 
	: public Composite<Agent>
{
};

class VisualFX
	: public Composite<VisualFX>
{

};

class Movement
	: public Component<Agent>
{
public:
	static const designPatterns::RunTimeType runTimeType;
	const designPatterns::RunTimeType& getRunTimeType(void) const { return runTimeType; }
};
const designPatterns::RunTimeType Movement::runTimeType(NULL, NULL);

class Attack
	: public Component<Agent>
{
public:
	static const designPatterns::RunTimeType runTimeType;
	const designPatterns::RunTimeType& getRunTimeType(void) const { return runTimeType; }
};
const designPatterns::RunTimeType Attack::runTimeType(NULL, NULL);

class Defense
	: public Component<Agent>
{
public:
	static const designPatterns::RunTimeType runTimeType;
	const designPatterns::RunTimeType& getRunTimeType(void) const { return runTimeType; }
};
const designPatterns::RunTimeType Defense::runTimeType(NULL, NULL);

class Damageable
{
public:
	static const designPatterns::RunTimeType runTimeType;
	virtual ~Damageable(void)=0 {}
};
const designPatterns::RunTimeType Damageable::runTimeType(NULL, NULL);

class Healable
{
public:
	static const designPatterns::RunTimeType runTimeType;
	virtual ~Healable(void)=0 {}
};
const designPatterns::RunTimeType Healable::runTimeType(NULL, NULL);

class Patchable
{
public:
	static const designPatterns::RunTimeType runTimeType;
	virtual ~Patchable(void)=0 {}
};
const designPatterns::RunTimeType Patchable::runTimeType(NULL, NULL);

class ActiveCover
	: public Defense
	, public Damageable
	, public Healable
{
public:
	static const designPatterns::RunTimeType runTimeType;
	const designPatterns::RunTimeType& getRunTimeType(void) const { return runTimeType; }
private:
	static const RunTimeType* const interfaces[];
};
const designPatterns::RunTimeType* const ActiveCover::interfaces[] = {&Healable::runTimeType, &Damageable::runTimeType, NULL};
const designPatterns::RunTimeType ActiveCover::runTimeType(&Defense::runTimeType, ActiveCover::interfaces);

class Shadows
	: public Component<VisualFX>
{
public:
	static const designPatterns::RunTimeType runTimeType;
	const designPatterns::RunTimeType& getRunTimeType(void) const { return runTimeType; }
};
const designPatterns::RunTimeType Shadows::runTimeType(NULL, NULL);

#include <queue>

static const sint dimensionsAC = 3;

static uint testID(0);

// mostly just used to test A*
class Graph
{
public:
	typedef uint ID;
	class Node;

	static void connect(Node& a, Node& b)
	{
		a.connect(b);
		b.connect(a);
	}

	Node& addNode(Node& n)
	{
		nodes.push_back(&n);	
	}

public:
	class Node
	{
		friend class Graph;

	public:
		typedef uint ID;

		const math::Pixel position;
		uint data;

		Node(const math::Pixel& p, uint newData, String::Immutable newName)
		: position(p)
		, data(newData)
		, name(newName)
		, nodeID(testID++)
		{ /* empty */ }       
		
		inline void connect(const Node& neighbor) 
		{ 
			for (uint i(0); i < getNumConnections(); ++i) 
				assert(neighbor != getConnection(i));
			
			neighbors.push_back(&neighbor); 
		}
		
		inline sint getCost(const Node& other) const 
		{ 
			sint manhattanDistance = 10 * position.distanceManhattan(other.position); 
			return manhattanDistance + data; 
		}

		inline bool operator!=(const Node& rhs) const
		{
			return nodeID != rhs.nodeID;
		}

		inline sint getID(void) const { return nodeID; }
		inline const Node& getConnection(uint index) const { assert(index < getNumConnections()); return *neighbors[index]; }
		inline uint getNumConnections(void) const { return static_cast<uint>(neighbors.size()); }
		
		inline const schar* toString(void) const
		{
			return name.c_str();
		}

	private:
		Node& operator=(const Node&);

		String::Immutable name;
		ID nodeID;
		std::vector<const Node*> neighbors;
	}; // Graph::Node

	std::vector<Node*> nodes;
}; // Graph

struct GraphEstimate
{
	inline sint operator()(const Graph::Node& node, const Graph::Node& goal) const
	{
		return node.getCost(goal);
	}
};

struct GetCost
{
	inline sint operator()(const Graph::Node& node, const Graph::Node& neighbor) const
	{
		return node.getCost(neighbor);
	}
};

struct IsGoal
{
	inline bool operator()(const Graph::Node& node, const Graph::Node& goal) const
	{
		return node.getID() == goal.getID();
	}
};

struct IsIncluded
{
	inline bool operator()(const Graph::Node&) const
 	{
		return true;
	}
};

#define GRAPH_CONNECT(A, B) Graph::connect(node##A, node##B); 
#define NODE_ENTRY(IDx, x, y, cost) math::Pixel p##IDx##( x , y ); Graph::Node node##IDx( p##IDx , cost, #IDx );

// proof of concept for public members exposed to Lua with a hashtable mapping index names to offsets
struct MyStruct
{
	uint a;
	bool b;
	MyStruct* c;
	void method(void) const { printf("MyStruct::method() was called!\n"); }
};

struct MyChildStruct : public MyStruct
{
	float d;
	bool e;
};

DECLARE_LUA_CLASS(MyStruct)

DEFINE_LUA_PUBLIC_MEMBER_INDEXING(MyStruct, MyStruct)
	LUA_PUBLIC_MEMBER_INDEX_ENTRY(MyStruct, uint, a)
	LUA_PUBLIC_MEMBER_INDEX_ENTRY(MyStruct, bool, b)
	LUA_PUBLIC_MEMBER_INDEX_ENTRY(MyStruct, MyStruct*, c)
END_LUA_PUBLIC_MEMBER_INDEXING(MyStruct, MyStruct)

DEFINE_LUA_CLASS_PUBLIC_MEMBERS(CLASS, MyStruct, MyStruct)
	LUA_ENTRY_NAMED("method", (nativeConstReturn0Param0<MyStruct, &MyStruct::method>))
END_LUA_CLASS(MyStruct, MyStruct)

// expose MyChildStruct to %Lua
DECLARE_LUA_CLASS(MyChildStruct)

DEFINE_LUA_PUBLIC_MEMBER_INDEXING(MyChildStruct, MyStruct)
LUA_PUBLIC_MEMBER_INDEX_ENTRY(MyChildStruct, float, d)
LUA_PUBLIC_MEMBER_INDEX_ENTRY(MyChildStruct, bool, e)
END_LUA_PUBLIC_MEMBER_INDEXING(MyChildStruct, MyStruct)

DEFINE_LUA_CLASS_PUBLIC_MEMBERS(CLASS, MyChildStruct, MyStruct)
END_LUA_CLASS(MyChildStruct, MyStruct)

struct MyStructProxy
{
	uint a;
	bool b;
	MyStructProxy* c;
	void method(void) const { printf("MyStructProxy::method() was called!\n"); }
};

struct MyChildStructProxy : public MyStructProxy
{
	float d;
	bool e;
};

DECLARE_LUA_CLASS(MyStructProxy)

DEFINE_LUA_PUBLIC_MEMBER_INDEXING(MyStructProxy, MyStructProxy)
	LUA_PUBLIC_MEMBER_INDEX_ENTRY(MyStructProxy, uint, a)
	LUA_PUBLIC_MEMBER_INDEX_ENTRY(MyStructProxy, bool, b)
	LUA_PUBLIC_MEMBER_INDEX_ENTRY(MyStructProxy, MyStructProxy*, c)
END_LUA_PUBLIC_MEMBER_INDEXING(MyStructProxy, MyStructProxy)

DEFINE_LUA_CLASS_BY_PROXY_PUBLIC_MEMBERS(CLASS, MyStructProxy, MyStructProxy) 
	LUA_ENTRY_NAMED("method", (nativeConstReturn0Param0<MyStructProxy, &MyStructProxy::method>))
END_LUA_CLASS(MyStructProxy, MyStructProxy)

// expose MyChildStructProxy to %Lua
DECLARE_LUA_CLASS(MyChildStructProxy)

DEFINE_LUA_PUBLIC_MEMBER_INDEXING(MyChildStructProxy, MyStructProxy)
	LUA_PUBLIC_MEMBER_INDEX_ENTRY(MyChildStructProxy, float, d)
	LUA_PUBLIC_MEMBER_INDEX_ENTRY(MyChildStructProxy, bool, e)
END_LUA_PUBLIC_MEMBER_INDEXING(MyChildStructProxy, MyStructProxy)

DEFINE_LUA_CLASS_BY_PROXY_PUBLIC_MEMBERS(CLASS, MyChildStructProxy, MyStructProxy)
END_LUA_CLASS(MyChildStructProxy, MyStructProxy)

// end proof of concept

class A
{
public:
	virtual ~A() {}

	virtual uint m(sreal, const math::Vector3&) 
	{ 
		return 3; 
	}
};

class AChild : public A
{
public:
	virtual uint m(sreal, const math::Vector3&) 
	{
		return 4;
	}
};

class CallAdapter
{
	// Whatever
};

typedef uint (A::* mptype)(sreal, const math::Vector3&);
typedef uint (CallAdapter::* mptype2)(sreal, const math::Vector3&);

typedef UpdateManager<Attack> UpdateManager_Attack;
typedef UpdateManager<Agent> UpdateManager_Agent;
DEFINE_SINGLETON(UpdateManager_Attack);
DEFINE_SINGLETON(UpdateManager_Agent);

template<typename T>
class BaseClass
{
public:
	~BaseClass(void) { printf("base destructor called\n"); }
};

class ChildClass
	: public BaseClass<ChildClass>
{
public:
	~ChildClass(void) { printf("child destructor called\n"); }
};

void proveThePoint(void)
{
	ChildClass* c1 = new ChildClass();
	BaseClass<ChildClass>* c2 = new ChildClass();
	delete c2;
	delete c1;
	printf("done\n");
}

class TrackerOfEntryDatum
	: public HFSM::PersistentDatum
{
public:
	TrackerOfEntryDatum(void)
		: numTimesActed(0)
		, numTimesEntered(0)
		, numTimesExited(0)
		, numTimesIsSatisfied(0)
		, numTimesUpdated(0)
	{ /* empty */ }

	~TrackerOfEntryDatum(void) 
	{ 
		/* empty */ 
		printf("TrackerOfEntryDatum deleted!\n");
	}

	int numTimesActed;
	int numTimesEntered;
	int numTimesExited;
	int numTimesIsSatisfied;
	int numTimesUpdated;
};

class ActTracker 
	: public HFSM::ActionState<Agent>
{
public:
	ActTracker(const char* n)
		: HFSM::ActionState<Agent>(n)
	{

	}

	virtual void act(Traversal<Agent>& , PersistentDatum* datum)
	{
		TrackerOfEntryDatum* tracker(static_cast<TrackerOfEntryDatum*>(datum));
		printf("Num times act: %d\n", ++tracker->numTimesActed);
	}

	virtual PersistentDatum* getPersistentDatum(void) const
	{
		return new TrackerOfEntryDatum();
	}

	virtual void recyclePersistentDatum(PersistentDatum* datum)
	{
		delete datum;
	}

protected:
	virtual void onEnter(Traversal<Agent>& , PersistentDatum* datum) 
	{ 
		TrackerOfEntryDatum* tracker(static_cast<TrackerOfEntryDatum*>(datum));
		printf("Num times onEnter: %d\n", ++tracker->numTimesEntered);
	}

	virtual void onExit(Traversal<Agent>& , PersistentDatum* datum) 
	{ 
		TrackerOfEntryDatum* tracker(static_cast<TrackerOfEntryDatum*>(datum));
		printf("Num times onExit: %d\n", ++tracker->numTimesExited);
	}
};

class TimesEvaluated
	: public HFSM::Condition<Agent>
{
public:
	TimesEvaluated(int numTimesToEvaluate=0)
		: requiredEvaluations(numTimesToEvaluate)
	{
		/* empty */
	}

	virtual PersistentDatum* getPersistentDatum(void) const
	{
		return new TrackerOfEntryDatum();
	}

	void recyclePersistentDatum(PersistentDatum* datum)
	{
		delete datum;
	}

protected:
	virtual bool isSatisfied(Agent* /*agent*/, PersistentDatum* datum)
	{
		TrackerOfEntryDatum* tracker(static_cast<TrackerOfEntryDatum*>(datum));
		printf("Num times isSatisfied: %d\n", ++tracker->numTimesIsSatisfied);
		return tracker->numTimesIsSatisfied >= requiredEvaluations;
	}

	virtual void update(Agent* /*agent*/, PersistentDatum* datum)
	{
		TrackerOfEntryDatum* tracker(static_cast<TrackerOfEntryDatum*>(datum));
		printf("Num times update: %d\n", ++tracker->numTimesUpdated);
	}

private:
	int requiredEvaluations;
};

void onPlay(void)
{
	Agent alpha;
	
	{
		Agent deltaAgent;
		HFSM::Traversal<Agent> delta(&deltaAgent);

		TimesEvaluated evaluateTwice(2);
		TimesEvaluated evaluateThrice(3);

		ActTracker actTrackerOne("one");
		ActTracker actTrackerTwo("two");

		StateMachine<Agent> machine;
		StateKey key1(machine.add(actTrackerOne));
		StateKey key2(machine.add(actTrackerOne));
		machine.connect(key1, evaluateTwice, key2);
		machine.connect(key2, evaluateThrice, key1);

		delta.start(machine);

		for (int i = 0; i < 10; ++i)
		{
			delta.act();
		}
	}



	{
		Agent gamma;

		HFSM::Traversal<Agent> alpha(&gamma);

		HFSM::TransitionFX<Agent>* transitionFX1 = new TransitionFX<Agent>;
		HFSM::TransitionFX<Agent>* transitionFX2 = new TransitionFX<Agent>;
		HFSM::TransitionFX<Agent>* transitionFX3 = new TransitionFX<Agent>;

		HFSM::ConditionTrue<Agent>* condition1 = new ConditionTrue<Agent>("condition 1");
		HFSM::ConditionTrue<Agent>* condition2 = new ConditionTrue<Agent>("condition 2");
		HFSM::ConditionTrue<Agent>* condition3 = new ConditionTrue<Agent>("condition 3");
		HFSM::ConditionTrue<Agent>* condition4 = new ConditionTrue<Agent>("condition 4");
		HFSM::ConditionTrue<Agent>* condition5 = new ConditionTrue<Agent>("condition 5");
		HFSM::ConditionTrue<Agent>* condition6 = new ConditionTrue<Agent>("condition 6");
		HFSM::ConditionTrue<Agent>* condition7 = new ConditionTrue<Agent>("condition 7");

		HFSM::StateMachine<Agent>* stateMachine1 = new StateMachine<Agent>("state/machine 0/x");
		
		HFSM::ActionState<Agent>* state1 = new ActionState<Agent>("state 1");
		HFSM::ActionState<Agent>* state2 = new ActionState<Agent>("state 2");
		HFSM::StateMachine<Agent>* stateMachine2 = new StateMachine<Agent>("state/machine 3/1");
		
		HFSM::ActionState<Agent>* state4 = new ActionState<Agent>("state 4");
		HFSM::ActionState<Agent>* state5 = new ActionState<Agent>("state 5");
		HFSM::StateMachine<Agent>* stateMachine3 = new StateMachine<Agent>("state/machine 6/2");		
		
		HFSM::ActionState<Agent>* state7 = new ActionState<Agent>("state 7");
		HFSM::ActionState<Agent>* state8 = new ActionState<Agent>("state 8");
		HFSM::ActionState<Agent>* state9 = new ActionState<Agent>("state 9");
		
		{
			HFSM::StateKey key1 = stateMachine1->add(*state1);
			HFSM::StateKey key2 = stateMachine1->add(*state2);
			HFSM::StateKey key3 = stateMachine1->add(*stateMachine2);
			stateMachine1->connect(key1, *condition1, key2, transitionFX1);
			stateMachine1->connect(key2, *condition2, key3, transitionFX2);
		}
		
		{
			HFSM::StateKey key4 = stateMachine2->add(*state4);
			HFSM::StateKey key5 = stateMachine2->add(*state5);
			HFSM::StateKey key6 = stateMachine2->add(*stateMachine3);
			stateMachine2->connect(key4, *condition3, key5, transitionFX1);
			stateMachine2->connect(key5, *condition4, key6, transitionFX2);
		}

		{
			HFSM::StateKey key7 = stateMachine3->add(*state7);
			HFSM::StateKey key8 = stateMachine3->add(*state8);
			HFSM::StateKey key9 = stateMachine3->add(*state9);
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
	
	Movement* movement = new Movement();
	Attack* attack = new Attack();
	Defense* defense = new ActiveCover;
	
	{
		Agent beta;
		Defense* defense = new ActiveCover;
		beta.add(*defense);
		assert(!beta.has<Attack>());
		assert(beta.get<Defense>() != NULL);
		assert(beta.get<ActiveCover>() != NULL);
		assert(beta.getOrCreate<Attack>() != NULL);
		assert(beta.has<Attack>());
		assert(beta.get<Attack>()->isActive());
		assert(beta.isActive<Attack>());
		beta.get<Attack>()->deactivate();
		assert(!beta.get<Attack>()->isActive());

	}
	
	alpha.add(*movement);
	alpha.add(*attack);
	alpha.add(*defense);
	alpha.remove<Attack>();
	assert(!alpha.has<Attack>());
	assert(alpha.has<Movement>());
	assert(alpha.has<Damageable>());
	assert(alpha.has<ActiveCover>());
	assert(alpha.has<Healable>());
	assert(!alpha.has<Patchable>());
	
	{
		UpdateManager<Attack>::single().add(attack);
		UpdateManager<Attack>::single().update();
	}

	{
		UpdateManager<Agent>::single().add(&alpha);
		UpdateManager<Agent>::single().update();
	}

	math::Vector3 z;
	z.zero();

	A* a = new AChild(); // A();
	CallAdapter* callAdapter = (CallAdapter*) a;

	mptype mp = &A::m;
	mptype2 mp2 = (mptype2) mp;

	int r = (callAdapter->*mp2)(1, z);
	assert(r == 4);

	delete a;


//  #if EXTENDED_BY_LUA 
//  	{
//  		embeddedLua::Lua lua;
//  		lua.setPackagePath(
//  			"..\\LuaFiles\\?.lua;"  
//  			"..\\LuaFiles\\UTLuaFiles\\?.lua;");
//  		registerGlobalLibrary(lua.getState());
//  		lua.require("Utilities");
//  		lua.require("ObjectOrientedParadigm");
// 		REGISTER_LUA_LIBRARY((&lua), MyStruct);
// 		REGISTER_LUA_LIBRARY((&lua), MyChildStruct);
// 		REGISTER_LUA_LIBRARY((&lua), MyStructProxy);
// 		REGISTER_LUA_LIBRARY((&lua), MyChildStructProxy);
// 		lua.require("User");
//  		lua.runConsole();
//  	}
//  #endif//EXTENDED_BY_LUA	

	// sandbox::verifyUnitTests();
	sandbox::schedulingRnD();
	sandbox::tableRnD();
	
	//	6,	0, e0
	//	5,	10,	2
	// s0,	1,	1

 	std::vector<const Graph::Node*> path;
 
 	/*O*/NODE_ENTRY(a, -1, 1,12); /*O*/NODE_ENTRY(b,  0, 1, 0); /*X*/NODE_ENTRY(c,  1, 1, 0); 
 	/*O*/NODE_ENTRY(d, -1, 0,50); /*O*/NODE_ENTRY(e,  0, 0,50); /*X*/NODE_ENTRY(f,  1, 0, 4); 
 	/*X*/NODE_ENTRY(g, -1,-1, 0); /*X*/NODE_ENTRY(h,  0,-1, 2); /*X*/NODE_ENTRY(i,  1,-1, 2); 
 
 	GRAPH_CONNECT(a, d); GRAPH_CONNECT(a, b);
 	GRAPH_CONNECT(b, e); GRAPH_CONNECT(b, c);
 	GRAPH_CONNECT(c, f);
 	GRAPH_CONNECT(d, g); GRAPH_CONNECT(d, e);
 	GRAPH_CONNECT(e, h); GRAPH_CONNECT(e, f);
 	GRAPH_CONNECT(f, i);
 	GRAPH_CONNECT(g, h);
 	GRAPH_CONNECT(h, i);
 		
 	A_Star::Search<sint, GetCost, GetCost, IsGoal, Graph::Node, A_Star::FindFirstPath> aStar(nodeg, nodec);
 	A_Star::Search<sint, GetCost, GetCost, IsGoal, Graph::Node, A_Star::FindFirstPath, IsIncluded> aStar2(nodeg, nodec);
 	A_Star::Search<sint, GetCost, GetCost, IsGoal, Graph::Node, A_Star::FindShortestPath> aStar3(nodeg, nodec);
 	A_Star::Search<sint, GetCost, GetCost, IsGoal, Graph::Node, A_Star::FindShortestPath, IsIncluded> aStar4(nodeg, nodec);
 	assert(aStar.isPathFound());
 	aStar.getPath(path);
 	
 	// 
 	assert(path[0] == &nodeg);
 	assert(path[1] == &nodeh);
 	assert(path[2] == &nodei);
 	assert(path[3] == &nodef);
 	assert(path[4] == &nodec);
 
 	nodeh.data = 100;
 	path.clear();
 	A_Star::Search<sint, GetCost, GetCost, IsGoal, Graph::Node, A_Star::FindShortestPath> aStar5(nodeg, nodec);
 	assert(aStar5.isPathFound());
 	aStar2.getPath(path);
 	printf("finished A*!\n");


	{
		std::priority_queue<sint > priqueue;
		priqueue.push(20);
		priqueue.push(30);
		priqueue.push(10);
		IF_DEBUG(const sint& top =)priqueue.top();
		assert(top != 20);
		BinaryHeap<sint, std::greater<sint>> biheap;
		biheap.push(20);
		biheap.push(30);
		biheap.push(10);
		sint mytop = biheap.top();
		biheap.push(50);
		for (sint i = 0; i < 10; ++i)
		{
			biheap.push(i * 10);
		}
		mytop = biheap.top();
		while (!biheap.isEmpty())
		{
			sint nexttop = biheap.top();
			assert(nexttop <= mytop);
			mytop = nexttop;
			biheap.pop();
		}
	}

	{
		std::priority_queue<sint> priqueue;
		BinaryHeap<sint, std::greater<sint>> biheap;

		for (sint i = 1; i < 1000; ++i)
		{
			sint randi = generateRandom(-i, i);
			biheap.push(randi);
			priqueue.push(randi);

			assert(biheap.top() == priqueue.top());
		}

		IF_DEBUG(const sint& shouldbegreatest =) biheap.top();
		IF_DEBUG(const sint& shouldalsobegreatest =) priqueue.top();
		assert(shouldbegreatest == shouldalsobegreatest);

		while (!biheap.isEmpty())
		{
			assert(!priqueue.empty());
			assert(biheap.top() == priqueue.top());
			biheap.pop();
			priqueue.pop();
		}

		assert(priqueue.empty());
	}
}

void sandbox::play()
{
	compilerChecks::check();
	printf("Playing in the sandbox!\n");
	onPlay();
	printf("Stopped playing in the sandbox!\n");
}