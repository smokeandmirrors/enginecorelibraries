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
	typename IS_INCLUDED,
	typename OPEN_LIST, 
	typename OPEN_LIST_INDEX,
>
class A_Star
{
	class Node;
	
public:
	
	bool search(const NODE& start, const NODE& goal)
	{
		Node n(start);
		openList.add(start);

		while (!openList.isEmpty())
		{
			const Node current(openList.remove());
			
			if (isGoal(current))
			{
				return true;
			}

			if (const uint index = current.getNumNeighbors())
			{
				do
				{
					--index;
					Node& neighbor(current.getNeighbor(index));

					if (isIncluded(neighbor))
					{
						const COST currentPathToNeighbor(current.g + getCostToNeighbor(current.node, neighbor.node));
						
						if (!neighbor.isInOpenList())
						{	
							neighbor.h = estimateCostToGoal(neighbor.node, goal);
							neighbor.updatePathStatus(current, currentPathToNeighbor);
							openList.add(neighbor);
						}
						else if (currentPathToNeighbor < neighbor.g)
						{	
							neighbor.updatePathStatus(current, currentPathToNeighbor);
							openList.update(neighbor);
						}
					}
				}
				while (index);
			}
		}

		return false;
	}

private:
	class Node
	{	
	public:
		const NODE& node;
		COST h;
		COST f;
		COST g;
		OPEN_LIST_INDEX index;
		OPEN_LIST_INDEX parent;

		inline Node(const NODE& n) 
			: node(n)
		{ 
			// empty  
		}

		inline Node& getNeighbor(void) const;
		
		inline uint getNumNeighbors(void) const;
		
		inline bool isInOpenList(void) const;
		
		inline void updatePathStatus(Node& current, COST& currentPathToNeighbor)
		{	// update g & f, update position in path from start
			g = currentPathToNeighbor;
			parent = current.index;
			f = currentPathToNeighbor + h;
		}
	}; // class A_Star::Node

	IS_GOAL isGoal;
	IS_INCLUDED isIncluded;
	OPEN_LIST openList;
	GET_COST getCostToNeighbor;
	ESTIMATE_COST estimateCostToGoal;
}; // class A_Star

*/

void onPlay(void)
{
	// sandbox::tableRnD();
	// sandbox::verifyUnitTests();
	sandbox::schedulingRnD();
	
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
}
