#include "Sandbox.h"

#include <functional>

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
using namespace xronos;

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
	RUN_TIME_TYPE_DECLARATION
};
BASE_RUN_TIME_TYPE_DEFINITION(Movement, NULL);


typedef enum AttackInhibition
{

}; // AttackInhibition

class AttackImplementation
{
public:
	virtual ~AttackImplementation(void) { /*empty*/ }
	
	virtual bool isAttackAllowed(Agent& agent, AttackInhibition& reason)=0;
	virtual void reset(AttackInhibition) { /*empty*/ }
	virtual void updateAttack(Agent&, bool) { /*empty*/ }
}; // AttackImplementation

class Attack
	: public Component<Agent>
{
	RUN_TIME_TYPE_DECLARATION
public:
	void update(void)
	{
		// for each m_inhibitor...
		//	isAttackAllowed()
		// else reset

		// for each m_inhibitor
			// update
	}

private:
	std::vector<AttackImplementation*> m_inhibitors;
};
BASE_RUN_TIME_TYPE_DEFINITION(Attack, NULL);

class Defense
	: public Component<Agent>
{
	RUN_TIME_TYPE_DECLARATION
public:
};
BASE_RUN_TIME_TYPE_DEFINITION(Defense, NULL);

class Damageable
{
	RUN_TIME_TYPE_DECLARATION
public:
	virtual ~Damageable(void)=0 {}
};
BASE_RUN_TIME_TYPE_DEFINITION(Damageable, NULL);

class Healable
{
	RUN_TIME_TYPE_DECLARATION
public:
	virtual ~Healable(void)=0 {}
};
BASE_RUN_TIME_TYPE_DEFINITION(Healable, NULL);

class Patchable
{
	RUN_TIME_TYPE_DECLARATION
public:
	virtual ~Patchable(void)=0 {}
};
BASE_RUN_TIME_TYPE_DEFINITION(Patchable, NULL);

class ActiveCover
	: public Defense
	, public Damageable
	, public Healable
{
	RUN_TIME_TYPE_DECLARATION;
};

DERIVED_RUN_TIME_TYPE_DEFINITION(ActiveCover, Defense, &Healable::runTimeType, &Damageable::runTimeType, NULL);

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

	std::set<int> mySet;
}

/*

template<typename COMPARATOR>
float CalculateComparedDiameterSquared(const bfx::AreaHandle& area, COMPARATOR comparator, float initial) 
{
const int numEdges(area.GetNumEdges());
float current(initial);

if (numEdges == 3)
{	// for any triangle the radius is just the length of the longest side
for (int i(0); i < 3; ++i)
{
const float candidate(LenSq(area.GetEdgeStartPos(i) - area.GetEdgeStartPos((i+1) % 3)));
if (comparator(candidate, current))
{
current = candidate;
}
}
}
else
{	// handle the zero index case separately, since the inner loop sentinel is different
for (int j(2), j_sentinel(numEdges - 1); j < j_sentinel; ++j)
{
const float candidate(LenSq(area.GetEdgeStartPos(0) - area.GetEdgeStartPos(j)));
if (comparator(candidate, current))
{
current = candidate;
}
} 
// handle the other indices with the normal inner loop sentinel
for (int i(1), i_sentinel(numEdges - 2), j_sentinel(numEdges); i < i_sentinel; ++i)
{
for (int j(i + 2); j < j_sentinel; ++j)
{
const float candidate(LenSq(area.GetEdgeStartPos(i) - area.GetEdgeStartPos(j)));
if (comparator(candidate, current))
{
current = candidate;
}
} 
} 
}	

return current;
}

float PlannerUtils::CalculateMaxDiameterSquared(const bfx::AreaHandle& area) 
{
return CalculateComparedDiameterSquared(area, Greater<float>(), -1.0);
}

float PlannerUtils::CalculateMinDiameterSquared(const bfx::AreaHandle& area) 
{
return CalculateComparedDiameterSquared(area, Less<float>(), FLT_MAX);
}

*/

void testHFSM2(void)
{
	HFSM::test();
}


class MyClass
{
public:
	void MyMethod(void) const
	{
		printf("Hello, world!\n");
	}
};

signals::Transmitter0* transmitterZero;

void connectMe(void);
void connectMeToo(void);
void connectMeFour(void);
void connectMeThree(void);

void connectMe(void)
{
	printf("I'm connected!\n");
	// transmitterZero->disconnect(connectMe);
	// transmitterZero->disconnect(connectMeToo);
	transmitterZero->disconnect(connectMeThree);
	transmitterZero->disconnect(connectMeToo);
	transmitterZero->disconnect(connectMe);
}

void connectMeToo(void)
{
	printf("I'm connected, too!\n");
}

void connectMeThree(void)
{
	printf("I'm connected, three!\n");
	// transmitterZero->disconnect(connectMeFour);
	// transmitterZero->disconnect(connectMeThree);
	// transmitterZero->disconnect(connectMeToo);
	// transmitterZero->disconnect(connectMe);
	// transmitterZero->transmit();
}

class ConnectMe
	: public signals::ReceiverBase
{
public:
	void connectMeConst(void) const
	{
		printf("Connect me const!\n");
	}

	void connectMe(void) 
	{
		printf("Connect me!\n");
	}
};


void connectMeFour(void)
{
	printf("I'm connected, four!\n");
}

void onPlay(void)
{
	// if (true)
	{
		transmitterZero = new signals::Transmitter0();

		ConnectMe object;
		ConnectMe objectConst;

		signals::Transmitter0& transmitter(*transmitterZero);
		transmitter.connect<ConnectMe>(&object, &ConnectMe::connectMe);
		transmitter.connect<ConnectMe>(&objectConst, &ConnectMe::connectMeConst);

		transmitter.disconnect(connectMeToo);
		assert(!transmitter.isConnected(connectMeToo));

		transmitter();
		transmitter.disconnect(connectMe);
		transmitter.transmit();

		{
			signals::Transmitter0 transmitter1(transmitter);
			transmitter1.transmit();
		}
		
		signals::Transmitter0 transmitter2(transmitter);
		transmitter2.transmit();
		
		delete transmitterZero;
	}
	
	// sandbox::schedulingRnD();

	{
		{
			Millisecond two(2.0);
			Millisecond four(4.0);

			Millisecond six = four + two;
			six++;
			++six;
			six += two + four + two + four;
		}

		{
			Second two(2.0);
			Second four(4.0);

			Second six = four + two;
			six++;
			++six;
			six += two + four + two + four;
		}
 
		{
			Millisecond two(2000.0);
			Second four(4.0);

			Second six = four + two;
			six += 4.0;
		}

		float pi(3.14f);
		--pi;
		++pi;
		pi--;
		pi++;

		pi = pi += 3.0f;
		pi = ++pi;

		double dpi(3.14);
		++dpi;
		--dpi;
		dpi++;
		dpi--;
	}
	

	testHFSM2();

	bool shouldQuit(true);
	if (shouldQuit)
		return;

	/*
	for (int i = 4; i < 10; ++i)
	{
		printIndices(i);
	}
	BREAKPOINT(0x0);
	*/

	// time sand boxing
	{
		Clock clock;
		
		RelativeClock<Clock> clockReletive(clock);
		clockReletive.setRate(2.0);

		Stopwatch<Clock> stopwatch(clock);
		Stopwatch<RelativeClock<Clock>> stopwatchReletive(clockReletive);

		Timer<Clock> timer(clock);
		Timer<RelativeClock<Clock>> timerRelative(clockReletive);
		
		timer.set(10000, 10000);
		timerRelative.set(20000, 20000);

		stopwatch.start();
		stopwatchReletive.start();

		timer.start();
		timerRelative.start();


		for (int i = 0; i < 10; ++i)
		{
			concurrency::sleep(1000);
			clock.tick();
			clockReletive.tick();
			/*
			printf("clockAbsolute seconds: %f\n", clock.seconds());
			printf("clockReletive seconds: %f\n", clockReletive.seconds());
			printf("timerAbsolute seconds: %f\n", timer.seconds());
			printf("timerReletive seconds: %f\n", timerRelative.seconds());
			printf("stopwatchAbsolute seconds: %f\n", stopwatch.seconds());
			printf("stopwatchRelative seconds: %f\n", stopwatchReletive.seconds());
			*/
		}

		printf("clockAbsolute seconds: %f\n", clock.seconds());
		printf("clockReletive seconds: %f\n", clockReletive.seconds());
		printf("timerAbsolute seconds: %f\n", timer.seconds());
		printf("timerReletive seconds: %f\n", timerRelative.seconds());
		printf("stopwatchAbsolute seconds: %f\n", stopwatch.seconds());
		printf("stopwatchRelative seconds: %f\n", stopwatchReletive.seconds());
	}


	Agent alpha;
	
	Movement* movement = new Movement();
	Attack* attack = new Attack();
	Defense* defense = new ActiveCover;
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
