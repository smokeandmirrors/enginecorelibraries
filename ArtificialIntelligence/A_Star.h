#pragma once
#ifndef A_STAR_H
#define A_STAR_H

#include "Platform.h"

#include <algorithm>
#include "RedBlackMap.h"
#include <vector>

/// \todo replace bool with flags
/// \todo make all the classes private

template<typename A_STAR_NODE>
class OpenSet;

template <typename NUMBER>
NUMBER getInitialA_StarPathCost(void)
{
	return static_cast<NUMBER>(0);
}

template <typename NODE>
struct IncludeAll
{
	inline bool operator()(const NODE&) const
	{
		return true;
	}
};

template<typename RECORD, typename COST, typename ESTIMATE_COST_TO_GOAL, typename NODE, typename IS_INCLUDED>
struct A_StarRecordGenerator
{
	inline static RECORD* getActiveRecord(containers::RedBlackMap< const NODE*, RECORD* >& recordsByNodes, const NODE& node, const NODE& goal, const ESTIMATE_COST_TO_GOAL& estimateCostToGoal, const IS_INCLUDED& isIncluded)
	{
		RECORD* record;

		if (!recordsByNodes.has(&node, record))
		{
			if (isIncluded(node))
			{
				record = new RECORD(node, estimateCostToGoal(node, goal));
			}
			else
			{
				record = new RECORD(node);
			}

			recordsByNodes.set(&node, record);
		}

		return record->isIncluded /*&& record->isNotInClosedSet*/ ? record : NULL;	
	}
};

template<typename RECORD, typename COST, typename ESTIMATE_COST_TO_GOAL, typename NODE>
struct A_StarRecordGenerator<RECORD, COST, ESTIMATE_COST_TO_GOAL, NODE, IncludeAll<NODE> >
{
	inline static RECORD* getActiveRecord(containers::RedBlackMap< const NODE*, RECORD* >& recordsByNodes, const NODE& node, const NODE& goal, const ESTIMATE_COST_TO_GOAL& estimateCostToGoal, const IncludeAll<NODE>&)
	{
		RECORD* record;

		if (!recordsByNodes.has(&node, record))
		{
			record = new RECORD(node, estimateCostToGoal(node, goal));
			recordsByNodes.set(&node, record);
		}

		// return record->isNotInClosedSet ? record : NULL;	
		return record;
	}
};

class AStarVariant {};
class FindFirstPath : public AStarVariant {};
class FindShortestPath : public AStarVariant {};

template<typename A_STAR, typename RECORD, typename NODE, typename COST, typename OPEN_SET, typename ESTIMATE_COST_TO_GOAL, typename SEARCH_TYPE>
struct A_StarConnection
{
	inline static void process(A_STAR& search, RECORD& current, RECORD& neighbor, const NODE& goal, const COST& g, OPEN_SET& openSet, const ESTIMATE_COST_TO_GOAL& estimateCostToGoal) 
	{
		PREVENT_COMPILE;
	}
};

template<typename A_STAR, typename RECORD, typename NODE, typename COST, typename OPEN_SET, typename ESTIMATE_COST_TO_GOAL>
struct A_StarConnection<A_STAR, RECORD, NODE, COST, OPEN_SET, ESTIMATE_COST_TO_GOAL, FindFirstPath>
{
	inline static void process(A_STAR& search, RECORD& current, RECORD& connection, const NODE& goal, const COST& g, OPEN_SET& openSet, const ESTIMATE_COST_TO_GOAL& estimateCostToGoal)
	{
		if (!connection.isInOpenSet)
		{	
			connection.h = estimateCostToGoal(connection.node, goal);
			connection.update(&current, g);
			search.addToOpenSet(connection);
		}
		else if (g < connection.g)
		{	
			connection.update(&current, g);
			openSet.update(connection.openSetIndex);
		}
	}
};

template<typename A_STAR, typename RECORD, typename NODE, typename COST, typename OPEN_SET, typename ESTIMATE_COST_TO_GOAL>
struct A_StarConnection<A_STAR, RECORD, NODE, COST, OPEN_SET, ESTIMATE_COST_TO_GOAL, FindShortestPath>
{
	inline static void process(A_STAR& search, RECORD& current, RECORD& connection, const NODE& goal, const COST& g, OPEN_SET& openSet, const ESTIMATE_COST_TO_GOAL& estimateCostToGoal)
	{
		if (!connection.isNotInClosedSet
		&& g < connection.g)
		{
			connection.update(&current, g);
			search.addToOpenSet(connection);
		}
		else if (!connection.isInOpenSet)
		{	
			connection.h = estimateCostToGoal(connection.node, goal);
			connection.update(&current, g);
			search.addToOpenSet(connection);
		}
		else if (g < connection.g)
		{	
			connection.update(&current, g);
			openSet.update(connection.openSetIndex);
		}
	}
};

template
<
	typename COST, // <, +, getInitialA_StarPathCost<COST>;
	typename ESTIMATE_COST_TO_GOAL, // COST operator(const NODE&, const NODE&) const
	typename GET_COST_TO_NEIGHBOR, // COST operator(const NODE&, const NODE&) const
	typename IS_GOAL, // bool operator(const NODE&, const NODE&) const
	typename NODE, // const NODE& getConnection(uint index) const, uint getNumNeigbhors(void) const
	typename SEARCH_TYPE, // must be AStarVariant::eFindFirstPath or AStarVariant::eFindShortestPath
	typename IS_INCLUDED=IncludeAll<NODE> // bool operator(const NODE&, const NODE&) const
>
class A_Star
{
	enum A_StarFlags
	{
		A_StarInClosedSet,
		A_StarIncluded,
		A_StarInOpenSet,
	}; // A_StarFlags

public:
	A_Star(const NODE& start, const NODE& goal)
	{
		initializeSearch(start, goal);
		endOfPath = search(goal);
	}

	~A_Star(void)
	{
		recordsByNodes.deleteElements();
	}

	void getPath(std::vector<const NODE*>& path) const
	{
		if (endOfPath)
		{	
			Record* pathNode(endOfPath);

			do 
			{
				path.push_back(&pathNode->node);
				pathNode = pathNode->parent;
			} 
			while (pathNode != startOfPath);
			
			path.push_back(&pathNode->node);
			std::reverse(path.begin(), path.end());
		}
	}
	
	bool isPathFound(void) const
	{
		return endOfPath != NULL;
	}
	
private:
	struct Record;
	typedef containers::RedBlackMap< const NODE*, Record* > RecordMap;
	typedef A_StarRecordGenerator<Record,COST,ESTIMATE_COST_TO_GOAL,NODE,IS_INCLUDED> RecordGenerator;
	typedef A_StarConnection<A_Star, Record, NODE, COST, OpenSet<Record*>, ESTIMATE_COST_TO_GOAL, SEARCH_TYPE> Connection;

	friend struct Connection;
	
	struct Record
	{	
		COST f;
		COST g;
		COST h;
		const NODE& node;
		Record* parent;
		mutable uint openSetIndex;
		bool isIncluded;
		bool isInOpenSet;
		bool isNotInClosedSet;

		/// constructor for nodes that aren't included in the search
		inline Record(const NODE& n)
			: node(n)
			, isIncluded(false)
		{ /* empty */ }

		/// constructor for nodes that are created when a node gets neighbors
		inline Record(const NODE& n, const COST& new_h)
			: h(new_h)
			, node(n)
			, isIncluded(true)
			, isInOpenSet(false)
			, isNotInClosedSet(true)
		{ /* empty */ }

		inline void update(Record* newParent, const COST& new_g)
		{	// update g & f, update position in path from start
			g = new_g;
			parent = newParent;
			f = new_g + h;
		}

	private:
		Record& operator=(const Record&);
	}; // struct Record

	inline void addToOpenSet(Record& node)
	{
		node.isInOpenSet = true;
		node.isNotInClosedSet = true;
		openSet.push(&node);
	}
	
	inline void initializeSearch(const NODE& start, const NODE& goal)
	{
		startOfPath = RecordGenerator::getActiveRecord(recordsByNodes, start, goal, estimateCostToGoal, isIncluded);
		
		if (startOfPath)
		{
			startOfPath->update(NULL, getInitialA_StarPathCost<COST>());
			addToOpenSet(*startOfPath);			
		}
	}

	A_Star& operator=(const A_Star&);

	inline Record& removeFromOpenSet(void) 
	{
		Record& current(*openSet.top());
		openSet.pop();
		current.isInOpenSet = false;
		current.isNotInClosedSet = false;
		return current;
	}

	Record* search(const NODE& goal)
	{
		static int iterations(0);
		iterations = 0;

		while (!openSet.isEmpty())
		{	
			iterations++;
			printf("\nOpenSet: %5d\n", iterations); openSet.dump();
			Record& current(removeFromOpenSet());

			if (isGoal(current.node, goal))
			{
				return &current;
			}

			if (uint index = current.node.getNumConnections())
			{
				do
				{
					--index;

					if (Record* n = RecordGenerator::getActiveRecord(recordsByNodes, current.node.getConnection(index), goal, estimateCostToGoal, isIncluded))
					{
						Connection::process(*this, current, *n, goal, current.g + getCostToNeighbor(current.node, n->node), openSet, estimateCostToGoal);
					}
				}
				while (index);
			}
		}

		return NULL;
	}

	const ESTIMATE_COST_TO_GOAL estimateCostToGoal;
	const GET_COST_TO_NEIGHBOR getCostToNeighbor;
	const IS_GOAL isGoal;
	const IS_INCLUDED isIncluded;
	OpenSet<Record*> openSet;
	RecordMap recordsByNodes;
	Record* startOfPath;
	Record* endOfPath;
}; // class A_Star

template<typename A_STAR_NODE>
class OpenSet
{
public:
	OpenSet();

	void dump(void) const 
	{
		for (uint i = 0; i < getSize(); i++)
		{
			printf("%s COST: %5d\n", nodes[i]->node.toString(), nodes[i]->f);
		}
	}

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