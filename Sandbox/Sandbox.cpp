#include "BinaryHeap.h"
#include "Composition.h"
#include "Sandbox.h"
#include "UnitTestVerification.h"

const char* megaString = ""
"abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz123456789012345678901";

typedef std::string TestStringType; // String::Immutable



using namespace designPatterns;

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
/*
/// \todo it might be worth it to have the graph keep search data, rather than searches keeping graph data
template
<
	typename NODE, 
	typename COST, // <, +, getInitialA_StarPathCost<COST>;
	typename IS_GOAL, 
	typename ESTIMATE_COST,
	typename GET_COST,
	typename IS_INCLUDED
>
class A_Star
{
	class Node;
	class OpenSet;
	
	typedef RedBlackMap<const NODE*, Node*> RecordMap;

public:
	
	bool search(const NODE& start, const NODE& goal)
	{
		if (isIncluded(start))
		{
			const COST initial = estimateCostToGoal(start);
			Node* startRecord = new Node(initial, initial, 0, start, NULL, true, true); 
			openSet.add(*startRecord);

			do 
			{
				const Node& current(openSet.remove());

				if (isGoal(current.node))
				{
					return true;
				}

				if (const uint index = current.node.getNumNeighbors())
				{
					do
					{
						--index;

						if (Node* n = isNeighborIncluded(current.node.getNeighbor(index)))
						{
							Node& neighbor(*n);
							const COST startToNeighbor(current.g + getCostToNeighbor(current.node, neighbor.node));

							if (!neighbor.isInOpenSet)
							{	
								neighbor.h = estimateCostToGoal(neighbor.node, goal);
								updatePathRecord(neighbor, current, startToNeighbor);
								openSet.add(neighbor);
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
			while (!openSet.isEmpty())
		}

		return false;
	}

private:
	struct Node
	{	
		COST h;
		COST f;
		COST g;
		const NODE& node;
		const NODE* parent;
		bool isIncluded;
		bool isInOpenSet;
		// bool isInClosedList; // unecessary in this version
		
		inline Node(COST& new_h, COST& new_f, COST& new_g, const NODE& n, const NODE* parent, bool included, bool inOpenSet) 
			: h(new_h)
			, f(new_f)
			, g(new_g)
			, node(n)
			, parent(parent)
			, isIncluded(included)
			, isInOpenSet(inOpenSet)
		{ 
			// empty  
		}		
	}; // class A_Star::Node

	inline const Node* isNeighborIncluded(const NODE& node) const
	{
		Node* record;
		
		if (!recordsByNodes.has(&node, record))
		{
			if (isIncluded(node))
			{

				record = new Node(node, estimateCostToGoal(,,,,,,,);
			}
			else
			{
				record = new Node(node);
			}
		}
		
		return record->isIncluded ? record : NULL;
	}

	inline void updatePathRecord(Node& current, Node& parent, COST& throughParent)
	{	// update g & f, update position in path from start
		current.g = throughParent;
		current.parent = &parent;
		current.f = throughParent + current.h;
	}

	IS_GOAL isGoal;
	IS_INCLUDED isIncluded;
	GET_COST getCostToNeighbor;
	ESTIMATE_COST estimateCostToGoal;
	OpenSet openSet;
	RecordMap recordsByNodes;
}; // class A_Star
*/
void onPlay(void)
{
	// sandbox::tableRnD();
	// sandbox::verifyUnitTests();
	// sandbox::schedulingRnD();
	
 	Agent alpha;
 	Movement* movement = new Movement();
 	Attack* attack = new Attack();
 	Defense* defense = new Defense;
 	alpha.add(*movement);
 	alpha.add(*attack);
	alpha.add(*defense);
	alpha.remove(*attack);

	std::priority_queue<sint> priqueue;
	priqueue.push(20);
	priqueue.push(30);
	priqueue.push(10);
	
	const sint& top = priqueue.top();
	assert(top != 20);


	BinaryHeap<sint> biheap;
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
		assert(nexttop >= mytop);
		mytop = nexttop;
		biheap.pop();
	}

}
