#include "Sandbox.h"

#include "BinaryHeap.h"
#include "A_Star.h"
#include "Composition.h"
#include "Numbers.h"
#include "RedBlackMap.h"
#include "Strings.h"
#include "Vector.h"
#include "UnitTestVerification.h"
#include "Table.h"
#include "LuaExtensionInclusions.h"

const char* megaString = ""
"abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz123456789012345678901";

typedef std::string TestStringType; // String::Immutable

using namespace designPatterns;
using namespace containers;
using namespace embeddedLua;

class Agent 
	: public Composite<Agent>
{
public:

};

class VisualFX
	: public Composite<VisualFX>
{

};

class Movement
	: public Component<Agent>
{
};

class Attack
	: public Component<Agent>
{
public:

};

class Defense
	: public Component<Agent>
{

};

class Shadows
	: public Component<VisualFX>
{

};

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

enum E1
{
  val11 = 1,
  val12
};

enum E2
{
	val21 = 2,
	val22
};

int withE(E1 arg) { return arg; }
int withE(E2 arg) { return arg; }

void onPlay(void)
{
	int e1 = withE(val11);
	int e2 = withE(val21);
	
	
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

	sandbox::verifyUnitTests();
	// sandbox::schedulingRnD();
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

 	Agent alpha;
 	Movement* movement = new Movement();
 	Attack* attack = new Attack();
 	Defense* defense = new Defense;
 	alpha.add(*movement);
 	alpha.add(*attack);
	alpha.add(*defense);
	alpha.remove(*attack);

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
			sint randi = getRand<sint>(-i, i);
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
