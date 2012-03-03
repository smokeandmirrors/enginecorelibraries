#pragma once
#ifndef A_STAR_H
#define A_STAR_H

#include "Platform.h"

#include <algorithm>
#include "RedBlackMap.h"
#include <vector>

namespace A_Star
{

enum NodeStatus
{
	Included		= 1 << 0,
	InClosedSet		= 1 << 1,
	InOpenSet		= 1 << 2,
}; // NodeStatus

const ushort OpenSetMask(Included | InOpenSet);
const ushort ClosedSetMask(Included | InClosedSet);

template<typename A_STAR_NODE>
class OpenSet;

template<typename NUMBER>
NUMBER getInitialCost(void)
{
	return static_cast<NUMBER>(0);
}

template<typename NODE>
struct IncludeAll
{
	inline bool operator()(const NODE&) const
	{
		return true;
	}
};

class FindFirstPath {};

class FindShortestPath {};

template
<
	typename COST, // <, +, getInitialCost<COST>;
	typename ESTIMATE_COST_TO_GOAL, // COST operator(const NODE&, const NODE&) const
	typename GET_COST_TO_NEIGHBOR, // COST operator(const NODE&, const NODE&) const
	typename IS_GOAL, // bool operator(const NODE&, const NODE&) const
	typename NODE, // const NODE& getConnection(uint index) const, uint getNumNeigbhors(void) const
	typename SEARCH_TYPE=FindFirstPath, // must be FindFirstPath or FindShortestPath
	typename IS_INCLUDED=IncludeAll<NODE> // bool operator(const NODE&, const NODE&) const
>
class Search
{
public:
	Search(const NODE& start, const NODE& goal)
	{
		initializeSearch(start, goal);
		endOfPath = search(goal);
	}

	~Search(void)
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
	template<typename RECORD, typename COST, typename ESTIMATE_COST_TO_GOAL, typename NODE, typename IS_INCLUDED>
	struct NodeRecorder
	{
		inline static RECORD* record(containers::RedBlackMap< const NODE*, RECORD* >& recordsByNodes, const NODE& node, const NODE& goal, const ESTIMATE_COST_TO_GOAL& estimateCostToGoal, const IS_INCLUDED& isIncluded)
		{
			RECORD* r;

			if (!recordsByNodes.has(&node, r))
			{
				if (isIncluded(node))
				{
					r = new RECORD(node, estimateCostToGoal(node, goal));
					recordsByNodes.set(&node, r);
				}
				else
				{
					r = new RECORD(node);
					recordsByNodes.set(&node, r);
				}			
			}

			return r;
		}
	};

	template<typename RECORD, typename COST, typename ESTIMATE_COST_TO_GOAL, typename NODE>
	struct NodeRecorder<RECORD, COST, ESTIMATE_COST_TO_GOAL, NODE, IncludeAll<NODE> >
	{
		inline static RECORD* record(containers::RedBlackMap< const NODE*, RECORD* >& recordsByNodes, const NODE& node, const NODE& goal, const ESTIMATE_COST_TO_GOAL& estimateCostToGoal, const IncludeAll<NODE>&)
		{
			RECORD* r;

			if (!recordsByNodes.has(&node, r))
			{
				r = new RECORD(node, estimateCostToGoal(node, goal));
				recordsByNodes.set(&node, r);
			}

			return r;
		}
	};

	template<typename NODE, typename RECORD, typename IS_INCLUDED, typename SEARCH_TYPE>
	struct StatusEvaluator
	{
		inline static RECORD* check(RECORD* record) 
		{
			PREVENT_COMPILE;
			return record;
		}
	};

	template<typename NODE, typename RECORD, typename IS_INCLUDED>
	struct StatusEvaluator<NODE, RECORD, IS_INCLUDED, FindFirstPath>
	{
		inline static RECORD* check(RECORD* record) 
		{
			return record->isIncludedAndNotInClosed() ? record : NULL;
		}
	};

	template<typename NODE, typename RECORD, typename IS_INCLUDED>
	struct StatusEvaluator<NODE, RECORD, IS_INCLUDED, FindShortestPath>
	{
		inline static RECORD* check(RECORD* record) 
		{
			return record->isIncluded() ? record : NULL;
		}
	};

	template<typename NODE, typename RECORD>
	struct StatusEvaluator<NODE, RECORD, IncludeAll<NODE>, FindFirstPath>
	{
		inline static RECORD* check(RECORD* record) 
		{
			return  record->isNotInClosedSet() ? record : NULL;
		}
	};

	template<typename NODE, typename RECORD>
	struct StatusEvaluator<NODE, RECORD, IncludeAll<NODE>, FindShortestPath>
	{
		inline static RECORD* check(RECORD* record) 
		{
			return record;
		}
	};

	template<typename RECORD, typename COST, typename ESTIMATE_COST_TO_GOAL, typename NODE, typename IS_INCLUDED, typename SEARCH_TYPE>
	struct RecordFactoryTemplate
	{
		inline static RECORD* getActiveRecord(containers::RedBlackMap< const NODE*, RECORD* >& recordsByNodes, const NODE& node, const NODE& goal, const ESTIMATE_COST_TO_GOAL& estimateCostToGoal, const IS_INCLUDED& isIncluded)
		{
			return StatusEvaluator<NODE, RECORD, IS_INCLUDED, SEARCH_TYPE>::check(NodeRecorder<RECORD, COST, ESTIMATE_COST_TO_GOAL, NODE, IS_INCLUDED>::record(recordsByNodes, node, goal, estimateCostToGoal, isIncluded));
		}
	};

	template<typename A_STAR, typename RECORD, typename NODE, typename COST, typename OPEN_SET, typename ESTIMATE_COST_TO_GOAL, typename SEARCH_TYPE>
	struct ConnectionTemplate
	{
		inline static void process(A_STAR& search, RECORD& current, RECORD& neighbor, const NODE& goal, const COST& g, OPEN_SET& openSet, const ESTIMATE_COST_TO_GOAL& estimateCostToGoal) 
		{
			PREVENT_COMPILE;
		}
	};

	template<typename A_STAR, typename RECORD, typename NODE, typename COST, typename OPEN_SET, typename ESTIMATE_COST_TO_GOAL>
	struct ConnectionTemplate<A_STAR, RECORD, NODE, COST, OPEN_SET, ESTIMATE_COST_TO_GOAL, FindFirstPath>
	{
		inline static void process(A_STAR& search, RECORD& current, RECORD& connection, const NODE& goal, const COST& g, OPEN_SET& openSet, const ESTIMATE_COST_TO_GOAL& estimateCostToGoal)
		{		
			if (connection.isNotInOpenSet())
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
	struct ConnectionTemplate<A_STAR, RECORD, NODE, COST, OPEN_SET, ESTIMATE_COST_TO_GOAL, FindShortestPath>
	{
		inline static void process(A_STAR& search, RECORD& current, RECORD& connection, const NODE& goal, const COST& g, OPEN_SET& openSet, const ESTIMATE_COST_TO_GOAL& estimateCostToGoal)
		{
			if (connection.isInClosedSet())
			{
				if (g < connection.g)
				{
					connection.update(&current, g);
					search.addToOpenSet(connection);
				}
			}
			else if (connection.isNotInOpenSet())
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
	
	struct Record;
	typedef containers::RedBlackMap< const NODE*, Record* > RecordMap;
	typedef RecordFactoryTemplate<Record, COST, ESTIMATE_COST_TO_GOAL, NODE, IS_INCLUDED, SEARCH_TYPE> RecordFactory;
	typedef ConnectionTemplate<Search, Record, NODE, COST, OpenSet<Record*>, ESTIMATE_COST_TO_GOAL, SEARCH_TYPE> Connection;

	friend struct Connection;
	
	struct Record
	{	
		COST f;
		COST g;
		COST h;
		const NODE& node;
		Record* parent;
		mutable uint openSetIndex;

		/// constructor for nodes that aren't included in the search
		inline Record(const NODE& n)
			: node(n)
			, status(0)
		{ /* empty */ }

		/// constructor for nodes that are created when a node gets neighbors
		inline Record(const NODE& n, const COST& new_h)
			: h(new_h)
			, node(n)
			, status(Included)
		{ /* empty */ }

		inline ushort isInClosedSet(void) const 
		{
			return status.isRaised(InClosedSet);
		}
		
		inline ushort isIncluded(void) const
		{
			return status.isRaised(Included);
		}

		inline ushort isIncludedAndNotInClosed(void) const
		{
			return (status() & ClosedSetMask) == Included;
		}

		inline ushort isInOpenSet(void) const 
		{
			return status.isRaised(InOpenSet);
		}

		inline ushort isNotInClosedSet(void) const 
		{
			return status.isLowered(InClosedSet);
		}

		inline ushort isNotInOpenSet(void) const
		{
			return status.isLowered(InOpenSet);
		}

		inline void onAddToOpenSet(void)
		{
			status.raise(InOpenSet);
		}

		inline void onRemoveFromOpenSet(void)
		{
			status.set(ClosedSetMask);
		}

		inline void update(Record* newParent, const COST& new_g)
		{	// update f, g, and position in path
			f = new_g + h;
			g = new_g;
			parent = newParent;
		}
		
	private:
		Record& operator=(const Record&);
		Flags<NodeStatus, ushort> status;
	}; // struct Record

	inline void addToOpenSet(Record& node)
	{
		node.onAddToOpenSet();
		openSet.push(&node);
	}
	
	inline void initializeSearch(const NODE& start, const NODE& goal)
	{
		startOfPath = RecordFactory::getActiveRecord(recordsByNodes, start, goal, estimateCostToGoal, isIncluded);
		
		if (startOfPath)
		{
			startOfPath->update(NULL, getInitialCost<COST>());
			addToOpenSet(*startOfPath);			
		}
	}

	Search& operator=(const Search&);

	inline Record& removeFromOpenSet(void) 
	{
		Record& current(*openSet.top());
		openSet.pop();
		current.onRemoveFromOpenSet();
		return current;
	}

	Record* search(const NODE& goal)
	{
		static uint iterations;
		iterations = 0;

		while (!openSet.isEmpty())
		{	
			iterations++;
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

					if (Record* n = RecordFactory::getActiveRecord(recordsByNodes, current.node.getConnection(index), goal, estimateCostToGoal, isIncluded))
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
}; // class Search


template<typename A_STAR_NODE>
class OpenSet
{
public:
	OpenSet(): nodes()
	{
		/* empty */
	}

	A_STAR_NODE& get(uint index)
	{
		return nodes[index];
	}

	uint getSize(void) const
	{
		return static_cast<uint>(nodes.size());
	}

	bool isEmpty(void) const
	{
		return nodes.empty();	
	}

	void pop(void)
	{
		assert(getSize());
		nodes[0] = nodes[getSize() - 1];
		nodes.pop_back();

		if (!isEmpty())
		{
			down(0);
		}
	}

	void push(const A_STAR_NODE& element)
	{
		const uint elementIndex = getSize();
		nodes.push_back(element);
		element->openSetIndex = elementIndex;
		up(element, elementIndex);
	}

	const A_STAR_NODE& top(void) const
	{
		return nodes.front();
	}

	void update(uint index)
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

private:
	std::vector<A_STAR_NODE> nodes; 

	inline void down(uint index)
	{
		INFINITE_LOOP_BEGIN
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
		INFINITE_LOOP_END
	}

	inline void downSwap(uint parentIndex, uint childIndex)
	{
		A_STAR_NODE parentCopy(get(parentIndex));
		nodes[parentIndex] = get(childIndex);
		nodes[parentIndex]->openSetIndex = parentIndex;
		nodes[childIndex] = parentCopy;
		nodes[childIndex]->openSetIndex = childIndex;
	}

	inline uint getLeftChildIndex(uint elementIndex) const
	{
		return elementIndex * 2 + 1;
	}

	inline uint getParentIndex(uint elementIndex) const
	{
		return (elementIndex - 1) / 2;
	}

	inline uint getRightChildIndex(uint elementIndex) const
	{
		return elementIndex * 2 + 2;
	}

	inline bool isValidIndex(const uint index) const 
	{ 
		return index < getSize(); 
	}

	inline void up(const A_STAR_NODE& element, uint index)
	{
		while (index)
		{
			const uint parentIndex = getParentIndex(index);
			const A_STAR_NODE& parent = nodes[parentIndex];

			if (element->f < parent->f)
			{
				upSwap(element, index, parent, parentIndex);
			}
			else
			{
				break;
			}
		}
	}

	inline void upSwap(const A_STAR_NODE& element, uint& elementIndex, const A_STAR_NODE& parent, uint parentIndex)
	{
		A_STAR_NODE parentCopy(parent);
		nodes[parentIndex] = element;
		element->openSetIndex = parentIndex;
		nodes[elementIndex] = parentCopy;
		parentCopy->openSetIndex = elementIndex;
		elementIndex = parentIndex;
	}
}; // class OpenSet

} // namespace A_Star

#endif//A_STAR_H