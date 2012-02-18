#pragma once
#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

/** a binary heap stored in an array */

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
	
	ELEMENT& get(uint index);
	uint getSize(void) const;
	bool isEmpty(void) const;
	void pop(void);
	void push(const ELEMENT& element);
	const ELEMENT& top(void) const;
	void update(uint index, const ELEMENT& newValue);

private:
	CONTAINER nodes; 
	PREDICATE predicate;

	inline void down(const uint elementIndex);
	inline void downSwap(uint parentIndex, uint childIndex);
	inline uint getLeftChildIndex(uint elementIndex) const;
	inline uint getParentIndex(uint elementIndex) const;
	inline uint getRightChildIndex(uint elementIndex) const;
	inline bool isValidIndex(const uint index) const { return index < getSize(); }
	inline void up(const ELEMENT& element, uint index);
	inline void upSwap(const ELEMENT& element, uint& elementIndex, const ELEMENT& parent, uint parentIndex);
}; // class BinaryHeap

template<typename ELEMENT, typename PREDICATE, typename CONTAINER>
BinaryHeap<ELEMENT, PREDICATE, CONTAINER>::BinaryHeap(uint reserveSize/* =0 */)
: nodes(reserveSize)
{
	 /* empty */
}

template<typename ELEMENT, typename PREDICATE, typename CONTAINER>
ELEMENT& BinaryHeap<ELEMENT, PREDICATE, CONTAINER>::get(uint index) 
{
	return nodes[index];
}

template<typename ELEMENT, typename PREDICATE, typename CONTAINER>
uint BinaryHeap<ELEMENT, PREDICATE, CONTAINER>::getLeftChildIndex(uint elementIndex) const
{
	return elementIndex * 2 + 1;
}

template<typename ELEMENT, typename PREDICATE, typename CONTAINER>
uint BinaryHeap<ELEMENT, PREDICATE, CONTAINER>::getParentIndex(uint elementIndex) const
{
	return (elementIndex - 1) / 2;
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
void BinaryHeap<ELEMENT, PREDICATE, CONTAINER>::down(uint index)
{
	for (;;)
	{
		const uint leftChildIndex = getLeftChildIndex(index);
		const uint rightChildIndex = getRightChildIndex(index);
		uint outOfOrderIndex = index;
		
		if (isValidIndex(leftChildIndex)
		&& predicate(get(leftChildIndex), get(outOfOrderIndex)))
		{
			outOfOrderIndex = leftChildIndex;
		}

		if (isValidIndex(rightChildIndex)
		&& predicate(get(rightChildIndex), get(outOfOrderIndex)))
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

template<typename ELEMENT, typename PREDICATE, typename CONTAINER>
void BinaryHeap<ELEMENT, PREDICATE, CONTAINER>::downSwap(uint parentIndex, uint childIndex)
{
	ELEMENT parentCopy(get(parentIndex));
	nodes[parentIndex] = get(childIndex);
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
	
	if (!isEmpty())
	{
		down(0);
	}
}

template<typename ELEMENT, typename PREDICATE, typename CONTAINER>
void BinaryHeap<ELEMENT, PREDICATE, CONTAINER>::push(const ELEMENT& element)
{
	const uint elementIndex = getSize();
	nodes.push_back(element);
	up(element, elementIndex);
}

template<typename ELEMENT, typename PREDICATE, typename CONTAINER>
const ELEMENT& BinaryHeap<ELEMENT, PREDICATE, CONTAINER>::top(void) const
{
	return nodes.front();
}

template<typename ELEMENT, typename PREDICATE, typename CONTAINER>
void BinaryHeap<ELEMENT, PREDICATE, CONTAINER>::update(uint index, const ELEMENT& newValue)
{
	assert(isValidIndex(index));
	ELEMENT& element(nodes[index]);
	element = newValue;
	
	uint parentIndex(getParentIndex(index));

	if (isValidIndex(parentIndex)
	&& predicate(element, nodes[getParentIndex(index)]))
	{
		upSwap(element, index, nodes[getParentIndex(index)], parentIndex);
		up(element, parentIndex);	
	}
	else
	{
		down(index);
	}	
}

template<typename ELEMENT, typename PREDICATE, typename CONTAINER>
void BinaryHeap<ELEMENT, PREDICATE, CONTAINER>::up(const ELEMENT& element, uint elementIndex)
{
	while (elementIndex)
	{
		const uint parentIndex = getParentIndex(elementIndex);
		const ELEMENT& parent = nodes[parentIndex];

		if (predicate(element, parent))
		{
			upSwap(element, elementIndex, parent, parentIndex);
		}
		else
		{
			break;
		}
	}
}

template<typename ELEMENT, typename PREDICATE, typename CONTAINER>
void BinaryHeap<ELEMENT, PREDICATE, CONTAINER>::upSwap(const ELEMENT& element, uint& elementIndex, const ELEMENT& parent, uint parentIndex)
{
	ELEMENT parentCopy(parent);
	nodes[parentIndex] = element;
	nodes[elementIndex] = parentCopy;
	elementIndex = parentIndex;
}

#endif//BINARY_HEAP_H