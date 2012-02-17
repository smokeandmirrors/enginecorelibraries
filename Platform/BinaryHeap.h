#pragma once
#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

/* a binary heap stored in an array */

#include "Platform.h"
#include <vector>

template
<
	typename ELEMENT,
	typename PREDICATE=std::less<ELEMENT>,
	typename CONTAINER = std::vector<ELEMENT>
>
class BinaryHeap
{
public:
	BinaryHeap(uint reserveSize=0);
	const ELEMENT& getNode(uint index) const;
	uint getSize(void) const;
	bool isEmpty(void) const;
	void pop(void);
	void push(const ELEMENT& element);
	const ELEMENT& top(void) const;
	void updateNode(uint index);
	// remove arbitrary node?

private:
	std::vector<ELEMENT> nodes; // CONTAINER nodes;
	PREDICATE predicate;

	inline uint getLeftChildIndex(uint elementIndex) const;
	inline uint getParentIndex(uint elementIndex) const;
	inline uint getRightChildIndex(uint elementIndex) const;
	inline bool isValidIndex(const uint index) const { return index < getSize(); }
	void downHeap(const uint index);
	inline void downHeapSwap(uint parentIndex, uint childIndex);
	inline void upHeapSwap(const ELEMENT& element, uint& elementIndex, const ELEMENT& parent, uint parentIndex);
}; // class BinaryHeap

template<typename ELEMENT, typename PREDICATE, typename CONTAINER>
BinaryHeap<ELEMENT, PREDICATE, CONTAINER>::BinaryHeap(uint reserveSize/* =0 */)
: nodes(reserveSize)
{
	 /* empty */
}

template<typename ELEMENT, typename PREDICATE, typename CONTAINER>
uint BinaryHeap<ELEMENT, PREDICATE, CONTAINER>::getLeftChildIndex(uint elementIndex) const
{
	return elementIndex * 2 + 1;
}

template<typename ELEMENT, typename PREDICATE, typename CONTAINER>
const ELEMENT& BinaryHeap<ELEMENT, PREDICATE, CONTAINER>::getNode(uint index) const
{
	return nodes[index];
}

template<typename ELEMENT, typename PREDICATE, typename CONTAINER>
uint BinaryHeap<ELEMENT, PREDICATE, CONTAINER>::getParentIndex(uint elementIndex) const
{
	return (elementIndex - 1) / 2; // floor((elementIndex - 1) / 2);
}

template<typename ELEMENT, typename PREDICATE, typename CONTAINER>
uint BinaryHeap<ELEMENT, PREDICATE, CONTAINER>::getRightChildIndex(uint elementIndex) const
{
	return elementIndex * 2 + 2;
}

template<typename ELEMENT, typename PREDICATE, typename CONTAINER>
uint BinaryHeap<ELEMENT, PREDICATE, CONTAINER>::getSize(void) const
{
	return static_cast<uint>(nodes.size());
}

template<typename ELEMENT, typename PREDICATE, typename CONTAINER>
void BinaryHeap<ELEMENT, PREDICATE, CONTAINER>::downHeap(uint index)
{
	for (;;)
	{
		const uint leftChildIndex = getLeftChildIndex(index);
		const uint rightChildIndex = getRightChildIndex(index);
		uint outOfOrderIndex = index;
		
		if (isValidIndex(leftChildIndex)
		&& predicate(getNode(leftChildIndex), getNode(outOfOrderIndex)))
		{
			outOfOrderIndex = leftChildIndex;
		}

		if (isValidIndex(rightChildIndex)
		&& predicate(getNode(rightChildIndex), getNode(outOfOrderIndex)))
		{
			outOfOrderIndex = rightChildIndex;
		}	

		if (outOfOrderIndex == index)
		{
			break;
		}
		else
		{
			downHeapSwap(index, outOfOrderIndex);
			index = outOfOrderIndex;
		}	
	}
}

template<typename ELEMENT, typename PREDICATE, typename CONTAINER>
void BinaryHeap<ELEMENT, PREDICATE, CONTAINER>::downHeapSwap(uint parentIndex, uint childIndex)
{
	ELEMENT parentCopy(getNode(parentIndex));
	nodes[parentIndex] = getNode(childIndex);
	nodes[childIndex] = parentCopy;
}

template<typename ELEMENT, typename PREDICATE, typename CONTAINER>
bool BinaryHeap<ELEMENT, PREDICATE, CONTAINER>::isEmpty(void) const
{
	return nodes.empty();	
}

template<typename ELEMENT, typename PREDICATE, typename CONTAINER>
void BinaryHeap<ELEMENT, PREDICATE, CONTAINER>::pop(void) 
{
	assert(getSize());
	nodes[0] = nodes[getSize() - 1];
	nodes.pop_back();
	downHeap(0);
}

template<typename ELEMENT, typename PREDICATE, typename CONTAINER>
void BinaryHeap<ELEMENT, PREDICATE, CONTAINER>::push(const ELEMENT& element)
{
	uint elementIndex = getSize();
	nodes.push_back(element);

	while (elementIndex)
	{
		const uint parentIndex = getParentIndex(elementIndex);
		const ELEMENT& parent = nodes[parentIndex];

		if (predicate(element, parent))
		{
			upHeapSwap(element, elementIndex, parent, parentIndex);
		}
		else
		{
			break;
		}
	}
}

template<typename ELEMENT, typename PREDICATE, typename CONTAINER>
const ELEMENT& BinaryHeap<ELEMENT, PREDICATE, CONTAINER>::top(void) const
{
	return nodes.front();
}

template<typename ELEMENT, typename PREDICATE, typename CONTAINER>
void BinaryHeap<ELEMENT, PREDICATE, CONTAINER>::upHeapSwap(const ELEMENT& element, uint& elementIndex, const ELEMENT& parent, uint parentIndex)
{
	ELEMENT parentCopy(parent);
	nodes[parentIndex] = element;
	nodes[elementIndex] = parentCopy;
	elementIndex = parentIndex;
}
#endif//BINARY_HEAP_H