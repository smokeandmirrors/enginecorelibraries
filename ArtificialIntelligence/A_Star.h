#pragma once
#ifndef A_STAR_H
#define A_STAR_H

#include "Platform.h"

#include <algorithm>
#include "RedBlackMap.h"
#include <vector>

template<typename A_STAR_NODE>
class OpenSet;

template
<
	typename COST, // <, +, getInitialA_StarPathCost<COST>;
	typename ESTIMATE_COST_TO_GOAL, // COST operator(const NODE&, const NODE&) const
	typename GET_COST_TO_NEIGHBOR, // COST operator(const NODE&, const NODE&) const
	typename IS_GOAL, // bool operator(const NODE&, const NODE&) const
	typename IS_INCLUDED, // bool operator(const NODE&, const NODE&) const
	typename NODE // const NODE& getNeighbor(uint index) const, uint getNumNeigbhors(void) const
>
class A_Star
{
public:
	A_Star(const NODE& start, const NODE& goal);
	~A_Star(void);
	void getPath(std::vector<const NODE*>& path) const;
	bool isPathFound(void) const;
	
private:
	class Node;

	typedef containers::RedBlackMap< const NODE*, Node* > RecordMap;

	struct Node
	{	
		COST f;
		COST g;
		COST h;
		const NODE& node;
		Node* parent;
		mutable uint openSetIndex;
		bool isIncluded;
		bool isInOpenSet;// 
		bool isNotInClosedSet; /// \todo I had a version with no closed set.  find this again.
		
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
			, isInOpenSet(false)
			, isNotInClosedSet(true)
		{ /* empty */ }

	private:
		Node& operator=(const Node&);
	};// class A_Star::Node

	inline void addToOpenSet(Node& node)
	{
		node.isInOpenSet = true;
		openSet.push(&node);
	}
	
	inline void initializeSearch(const NODE& start, const NODE& goal)
	{
		if (Node* startNode = isNodeIncluded(start, goal))
		{
			updatePathRecord(*startNode, NULL, getInitialA_StarPathCost<COST>());
			addToOpenSet(*startNode);
		}
	}

	inline Node* isNodeIncluded(const NODE& node, const NODE& goal) 
	{
		Node* record;

		if (!recordsByNodes.has(&node, record))
		{
			if (isIncluded(node))
			{
				record = new Node(node, estimateCostToGoal(node, goal));
			}
			else
			{
				record = new Node(node);
			}

			recordsByNodes.set(&node, record);
		}
		
		return record->isIncluded && record->isNotInClosedSet ? record : NULL;
	}

	A_Star& operator=(const A_Star&);

	inline Node& removeFromOpenSet(void) 
	{
		Node& current(*openSet.top());
		openSet.pop();
		current.isInOpenSet = false;
		current.isNotInClosedSet = false;
		return current;
	}

	Node* search(const NODE& goal)
	{
		while (!openSet.isEmpty())
		{
			Node& current(removeFromOpenSet());

			if (isGoal(current.node, goal))
			{
				return &current;
			}

			if (uint index = current.node.getNumNeighbors())
			{
				do
				{
					--index;

					if (Node* n = isNodeIncluded(current.node.getNeighbor(index), goal))
					{
						Node& neighbor(*n);
						const COST startToNeighbor(current.g + getCostToNeighbor(current.node, neighbor.node));

						if (!neighbor.isInOpenSet)
						{	
							neighbor.h = estimateCostToGoal(neighbor.node, goal);
							updatePathRecord(neighbor, &current, startToNeighbor);
							addToOpenSet(neighbor);
							neighbor.isInOpenSet = true;
						}
						else if (startToNeighbor < neighbor.g)
						{	
							updatePathRecord(neighbor, &current, startToNeighbor);
							openSet.update(neighbor.openSetIndex);
						}
					}
				}
				while (index);
			}
		}

		return NULL;
	}

	inline void updatePathRecord(Node& current, Node* parent, const COST& throughParent)
	{	// update g & f, update position in path from start
		current.g = throughParent;
		current.parent = parent;
		current.f = throughParent + current.h;
	}

	const ESTIMATE_COST_TO_GOAL estimateCostToGoal;
	const GET_COST_TO_NEIGHBOR getCostToNeighbor;
	const IS_GOAL isGoal;
	const IS_INCLUDED isIncluded;
	OpenSet<Node*> openSet;
	RecordMap recordsByNodes;
	Node* endOfPath;
}; // class A_Star

template<typename A_STAR_NODE>
class OpenSet
{
public:
	OpenSet();

	void dump(void) const { for (uint i = 0; i < getSize(); ++i) printf("%d ", get(i).f); }
	A_STAR_NODE& get(uint index);
	uint getSize(void) const;
	bool isEmpty(void) const;
	void pop(void);
	void push(const A_STAR_NODE& element);
	const A_STAR_NODE& top(void) const;
	void update(uint index);

private:
	std::vector<A_STAR_NODE> nodes; 

	inline void down(const uint elementIndex);
	inline void downSwap(uint parentIndex, uint childIndex);
	inline uint getLeftChildIndex(uint elementIndex) const;
	inline uint getParentIndex(uint elementIndex) const;
	inline uint getRightChildIndex(uint elementIndex) const;
	inline bool isValidIndex(const uint index) const { return index < getSize(); }
	inline void up(const A_STAR_NODE& element, uint index);
	inline void upSwap(const A_STAR_NODE& element, uint& elementIndex, const A_STAR_NODE& parent, uint parentIndex);
}; // class OpenSet

template<typename COST, typename ESTIMATE_COST_TO_GOAL, typename GET_COST_TO_NEIGHBOR, typename IS_GOAL, typename IS_INCLUDED, typename NODE>
A_Star<COST, ESTIMATE_COST_TO_GOAL, GET_COST_TO_NEIGHBOR, IS_GOAL, IS_INCLUDED, NODE>::A_Star(const NODE& start, const NODE& goal)
{
	initializeSearch(start, goal);
	endOfPath = search(goal);
}

template<typename COST, typename ESTIMATE_COST_TO_GOAL, typename GET_COST_TO_NEIGHBOR, typename IS_GOAL, typename IS_INCLUDED, typename NODE>
A_Star<COST, ESTIMATE_COST_TO_GOAL, GET_COST_TO_NEIGHBOR, IS_GOAL, IS_INCLUDED, NODE>::~A_Star(void)
{
	recordsByNodes.deleteElements();
}

template<typename COST, typename ESTIMATE_COST_TO_GOAL, typename GET_COST_TO_NEIGHBOR, typename IS_GOAL, typename IS_INCLUDED, typename NODE>
bool A_Star<COST, ESTIMATE_COST_TO_GOAL, GET_COST_TO_NEIGHBOR, IS_GOAL, IS_INCLUDED, NODE>::isPathFound(void) const
{
	return endOfPath != NULL;
}

template<typename COST, typename ESTIMATE_COST_TO_GOAL, typename GET_COST_TO_NEIGHBOR, typename IS_GOAL, typename IS_INCLUDED, typename NODE>
void A_Star<COST, ESTIMATE_COST_TO_GOAL, GET_COST_TO_NEIGHBOR, IS_GOAL, IS_INCLUDED, NODE>::getPath(std::vector<const NODE*>& path) const
{
	if (endOfPath)
	{	
		Node* pathNode(endOfPath);

		do 
		{
			path.push_back(&pathNode->node);
			pathNode = pathNode->parent;
		} 
		while (pathNode);
	
		std::reverse(path.begin(), path.end());
	}
}

template <typename NUMBER>
NUMBER getInitialA_StarPathCost(void)
{
	return static_cast<NUMBER>(0);
}

template<typename A_STAR_NODE>
OpenSet<A_STAR_NODE>::OpenSet()
: nodes()
{
	/* empty */
}

template<typename A_STAR_NODE>
A_STAR_NODE& OpenSet<A_STAR_NODE>::get(uint index) 
{
	return nodes[index];
}

template<typename A_STAR_NODE>
uint OpenSet<A_STAR_NODE>::getLeftChildIndex(uint elementIndex) const
{
	return elementIndex * 2 + 1;
}

template<typename A_STAR_NODE>
uint OpenSet<A_STAR_NODE>::getParentIndex(uint elementIndex) const
{
	return (elementIndex - 1) / 2;
}

template<typename A_STAR_NODE>
uint OpenSet<A_STAR_NODE>::getRightChildIndex(uint elementIndex) const
{
	return elementIndex * 2 + 2;
}

template<typename A_STAR_NODE>
uint OpenSet<A_STAR_NODE>::getSize(void) const
{
	return static_cast<uint>(nodes.size());
}

template<typename A_STAR_NODE>
void OpenSet<A_STAR_NODE>::down(uint index)
{
	for (;;)
	{
		const uint leftChildIndex = getLeftChildIndex(index);
		const uint rightChildIndex = getRightChildIndex(index);
		uint outOfOrderIndex = index;

		if (isValidIndex(leftChildIndex)
		&& get(leftChildIndex)->f < get(outOfOrderIndex)->f)
		{
			outOfOrderIndex = leftChildIndex;
		}

		if (isValidIndex(rightChildIndex)
		&& get(rightChildIndex)->f < get(outOfOrderIndex)->f)
		{
			outOfOrderIndex = rightChildIndex;
		}	

		if (outOfOrderIndex == index)
		{
			break;
		}
		else
		{
			downSwap(index, outOfOrderIndex);
			index = outOfOrderIndex;
		}	
	}
}

template<typename A_STAR_NODE>
void OpenSet<A_STAR_NODE>::downSwap(uint parentIndex, uint childIndex)
{
	A_STAR_NODE parentCopy(get(parentIndex));
	nodes[parentIndex] = get(childIndex);
	nodes[parentIndex]->openSetIndex = parentIndex;
	nodes[childIndex] = parentCopy;
	nodes[childIndex]->openSetIndex = childIndex;
}

template<typename A_STAR_NODE>
bool OpenSet<A_STAR_NODE>::isEmpty(void) const
{
	return nodes.empty();	
}

template<typename A_STAR_NODE>
void OpenSet<A_STAR_NODE>::pop(void) 
{
	assert(getSize());
	nodes[0] = nodes[getSize() - 1];
	nodes.pop_back();

	if (!isEmpty())
	{
		down(0);
	}
}

template<typename A_STAR_NODE>
void OpenSet<A_STAR_NODE>::push(const A_STAR_NODE& element)
{
	const uint elementIndex = getSize();
	nodes.push_back(element);
	element->openSetIndex = elementIndex;
	up(element, elementIndex);
}

template<typename A_STAR_NODE>
const A_STAR_NODE& OpenSet<A_STAR_NODE>::top(void) const
{
	return nodes.front();
}

template<typename A_STAR_NODE>
void OpenSet<A_STAR_NODE>::up(const A_STAR_NODE& element, uint elementIndex)
{
	while (elementIndex)
	{
		const uint parentIndex = getParentIndex(elementIndex);
		const A_STAR_NODE& parent = nodes[parentIndex];

		if (element->f < parent->f)
		{
			upSwap(element, elementIndex, parent, parentIndex);
		}
		else
		{
			break;
		}
	}
}

template<typename A_STAR_NODE>
void OpenSet<A_STAR_NODE>::update(uint index)
{
	assert(isValidIndex(index));
	A_STAR_NODE& element(nodes[index]);
	uint parentIndex(getParentIndex(index));

	if (isValidIndex(parentIndex)
	&& element->f < nodes[getParentIndex(index)]->f)
	{
		upSwap(element, index, nodes[getParentIndex(index)], parentIndex);
		up(element, parentIndex);	
	}
	else
	{
		down(index);
	}	
}

template<typename A_STAR_NODE>
void OpenSet<A_STAR_NODE>::upSwap(const A_STAR_NODE& element, uint& elementIndex, const A_STAR_NODE& parent, uint parentIndex)
{
	A_STAR_NODE parentCopy(parent);
	nodes[parentIndex] = element;
	element->openSetIndex = parentIndex;
	nodes[elementIndex] = parentCopy;
	parentCopy->openSetIndex = elementIndex;
	elementIndex = parentIndex;
}

#endif//A_STAR_H