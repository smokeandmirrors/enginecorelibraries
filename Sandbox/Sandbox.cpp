#include "BinaryHeap.h"
#include "Composition.h"
#include "Numbers.h"
#include "RedBlackMap.h"
#include "Sandbox.h"
#include "Vector.h"
#include "UnitTestVerification.h"

const char* megaString = ""
"abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz123456789012345678901";

typedef std::string TestStringType; // String::Immutable

using namespace designPatterns;
using namespace containers;

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

template <typename TYPE>
struct IsPointerEqual
{
	inline bool operator()(const TYPE* lhs, const TYPE* rhs) const
	{
		return lhs == rhs;
	}
};

template <typename TYPE>
struct IsPointerLess
{
	inline bool operator()(const TYPE* lhs, const TYPE* rhs) const
	{
		return lhs < rhs;
	}
};

template <typename TYPE>
struct IsPointerGreater
{
	inline bool operator()(const TYPE* lhs, const TYPE* rhs) const
	{
		return lhs > rhs;
	}
};

class Graph
{
public:
	typedef uint ID;
	class Node;

	void connect(Node& a, Node& b) const
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

		Node(const math::Pixel& p, Graph::ID newGraphID)
		: position(p)
		, graphID(newGraphID)
		{ /* empty */ }       
		
		inline void connect(const Node& neighbor) { neighbors.push_back(&neighbor); }
		inline sint getCost(const Node& other) const { return position.distanceManhattan(other.position) + artificialCost; }
		inline sint getID(void) const { return nodeID; }
		inline const Node& getNeighbor(uint index) const { assert(index < getNumNeighbors()); return *neighbors[index]; }
		inline uint getNumNeighbors(void) const { return static_cast<uint>(neighbors.size()); }
		
	private:
		Node& operator=(const Node&);

		Graph::ID graphID;
		ID nodeID;
		std::vector<const Node*> neighbors;
		sint artificialCost;
	}; // Graph::Node

	std::vector<Node*> nodes;
}; // Graph

template <typename NUMBER>
NUMBER getInitialA_StarPathCost(void)
{
	return static_cast<NUMBER>(0);
}

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

/// \todo it might be worth it to have the graph keep search data, rather than searches keeping graph data
template
<
	typename COST, // <, +, getInitialA_StarPathCost<COST>;
	typename ESTIMATE_COST_TO_GOAL, // COST operator(const NODE&, const NODE&) const
	typename GET_COST_TO_NEIGHBOR, // COST operator(const NODE&, const NODE&) const
	typename IS_GOAL, // bool operator(const NODE&, const NODE&) const
	typename IS_INCLUDED, // bool operator(const NODE&, const NODE&) const
	typename NODE
>
class A_Star
{
public:
	A_Star() {}

	bool search(const NODE& start, const NODE& goal)
	{
		if (isIncluded(start))
		{
			const COST initial = estimateCostToGoal(start, goal);
			Node* startRecord = new Node(initial, initial, 0, start, NULL, true, true); 
			openSet.push(startRecord);

			do 
			{
				Node& current(removeFromOpenSet());
				openSet.pop();
				current.isInOpenSet = false;

				if (isGoal(current.node, goal))
				{
					return true;
				}

				if (uint index = current.node.getNumNeighbors())
				{
					do
					{
						--index;

						if (Node* n = isNeighborIncluded(current.node.getNeighbor(index), goal))
						{
							Node& neighbor(*n);
							const COST startToNeighbor(current.g + getCostToNeighbor(current.node, neighbor.node));

							if (!neighbor.isInOpenSet)
							{	
								neighbor.h = estimateCostToGoal(neighbor.node, goal);
								updatePathRecord(neighbor, current, startToNeighbor);
								openSet.push(&neighbor);
							}
							else if (startToNeighbor < neighbor.g)
							{	
								updatePathRecord(neighbor, current, startToNeighbor);
								openSet.update(neighbor);
							}
						}
					}
					while (index);
				}
			}
			while (!openSet.isEmpty());
		}

		return false;
	}

private:
	class Node;
	typedef BinaryHeap<const Node*> OpenSet;
	// , IsPointerEqual<NODE>, IsPointerLess<NODE>, IsPointerGreater<NODE>
	typedef containers::RedBlackMap< const NODE*, Node* > RecordMap;

	struct Node
	{	
		COST h;
		COST f;
		COST g;
		const NODE& node;
		const NODE* parent;
		uint openSetIndex;
		bool isIncluded;
		bool isInOpenSet;
		// bool isInClosedList; // unecessary in this version
		
		/// constructor for the first start node
		inline Node(const COST& new_h, const COST& new_f, const COST& new_g, const NODE& n, const NODE* parent, bool included, bool inOpenSet) 
			: h(new_h)
			, f(new_f)
			, g(new_g)
			, node(n)
			, parent(parent)
			, isIncluded(included)
			, isInOpenSet(inOpenSet)
		{ /* empty */ }
		
		/// constructor for nodes that aren't included in the search
		inline Node(const NODE& n)
			: node(n)
			, isIncluded(false)
		{ /* empty */ }
		
		/// constructor for nodes that are created when a node gets neighbors
		inline Node(const NODE& n, const COST& new_h)
			: h(new_h)
			, node(n)
			, isIncluded(true)
			, isInOpenSet(true)
		{ /* empty */ }

	private:
		Node& operator=(const Node&);
	};// class A_Star::Node

	inline void addToOpenSet(Node& node)
	{
		node.isInOpenSet = true;
		openSet.push(&node);
	}

	inline Node* isNeighborIncluded(const NODE& node, const NODE& goal) 
	{
		Node* record;
		
		if (!recordsByNodes.has(&node, record))
		{
			if (isIncluded(node))
			{
				record = new Node(node, estimateCostToGoal(node, goal));
				addToOpenSet(*record);
			}
			else
			{
				record = new Node(node);
			}

			recordsByNodes.set(&node, record);
		}
		
		return record->isIncluded ? record : NULL;
	}

	A_Star& operator=(const A_Star&);

	inline Node& removeFromOpenSet(void) 
	{
		Node& current(*openSet.top());
		openSet.pop();
		current.isInOpenSet = false;
		return current;
	}

	inline void updatePathRecord(Node& current, Node& parent, const COST& throughParent)
	{	// update g & f, update position in path from start
		current.g = throughParent;
		current.parent = &parent.node;
		current.f = throughParent + current.h;
	}

	const ESTIMATE_COST_TO_GOAL estimateCostToGoal;
	const GET_COST_TO_NEIGHBOR getCostToNeighbor;
	const IS_GOAL isGoal;
	const IS_INCLUDED isIncluded;
	OpenSet openSet;
	RecordMap recordsByNodes;
}; // class A_Star


void onPlay(void)
{
	// sandbox::tableRnD();
	// sandbox::verifyUnitTests();
	// sandbox::schedulingRnD();

	

	math::Pixel s, e;

	Graph::Node start(s, 0);
	Graph::Node end(e, 0);

	std::equal_to<const float*> grrr;
	if (grrr(NULL, NULL))
	{
		printf("wtf?");
	}

	containers::RedBlackMap<const float*, sint> wtf;
	wtf.set(NULL, 2);

	A_Star<sint, GetCost, GetCost, IsGoal, IsIncluded, Graph::Node> aStar;
	aStar.search(start, end);
	
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
		const sint& top = priqueue.top();
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

		const sint& shouldbegreatest = biheap.top();
		const sint& shouldalsobegreatest = priqueue.top();
		assert(shouldbegreatest == shouldalsobegreatest);

		for (sint i = 1; i < 1000; ++i)
		{
			sint randi = getRand<sint>(-i, i);
			biheap.update(0, randi);
			priqueue.pop();
			priqueue.push(randi);

			assert(biheap.top() == priqueue.top());
		}

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
