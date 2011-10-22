#pragma once
#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H
/**

An implementation of a Left Leaning variant of a Red Black Tree, described here:
www.cs.princeton.edu/~rs/talks/LLRB/RedBlack.pdf

*/

#include "Build.h"

template<typename ELEMENT>
class RedBlackTree
{
public:
	static const bool red;
	static const bool black;
	
	RedBlackTree(void)
		: m_root(NULL)
		, m_size(0)
	{ /* empty */ }

	ELEMENT
		getMax(void) const;

	ELEMENT
		getMin(void) const;

	uint 
		getSize(void) const;

	bool 
		has(ELEMENT value) const;
	
	void 
		insert(ELEMENT value);

	bool
		isEmpty(void) const;
	
	void
		remove(ELEMENT value);

	void
		removeMax(void);
	
	void
		removeMin(void);

private:
	class Node
	{	
	public:
		Node(bool color, Node* left, Node* right, ELEMENT value)
			: m_color(color)
			, m_left(left)
			, m_right(right)
			, m_value(value)
		{ /* empty */ }

		bool	m_color;
		Node*	m_left;
		Node*	m_right;
		ELEMENT	m_value;
	}; // class Node

	inline Node* 
		fixUp(Node* node)
	{
		if (isRed(node->m_right))
			node = rotateLeft(node);

		if (isRed(node->m_left) && isRed(node->m_left->m_left))
			node = rotateRight(node);

		if (isRed(node->m_left) && isRed(node->m_right))
			switchColor(*node);	
		
		return node;
	}

	inline Node* 
		insert(Node* node, ELEMENT value)
	{
		if (!node)
		{
			return new RedBlackTree<ELEMENT>::Node(red, NULL, NULL, value);
		}

		ELEMENT& currentValue = node->m_value;

		if (currentValue < value)
		{
			node = insert(node->m_left, value);
		}
		else if (currentValue > value)
		{
			node = insert(node->m_right, value);
		}

		return fixUp(node);
	}

	inline bool 
		isRed(Node* node) const
	{
		return node && node->m_color == red;
	}

	inline Node*
		getMax(Node* node) const
	{
		while (node->m_right)
		{
			node = node->m_right;
		}

		return node;
	}

	inline Node*
		getMin(Node* node) const
	{
		while (node->m_left)
		{
			node = node->m_left;
		}

		return node;
	}

	inline Node*
		moveRedLeft(Node* node)
	{	// Assuming that h is red and both h.left and h.left.left
		// are black, make h.left or one of its children red.
		switchColor(*node);
		
		if (isRed(node.m_right->m_left))
		{ 
			node->m_right = rotateRight(*node->m_right);
			node = rotateLeft(*node);
			switchColor(*node);
		}
		
		return node;
	}

	inline Node*
		moveRedRight(Node* node)
	{	// Assuming that h is red and both h.right and h.right.left
		// are black, make h.right or one of its children red.
		switchColor(*node);
		
		if (isRed(node.m_left->m_left))
		{ 
			node = rotateRight(*node);
			switchColor(*node);
		}

		return node;
	}

	inline Node*
		remove(Node* node, ELEMENT value)
	{
		if (value < node->m_value)
		{
			if (!isRed(node->m_left) && !isRed(node->m_left->m_left))
				node = moveRedLeft(node);

			node->m_left = delete(node->m_left, value);
		}
		else
		{
			if (isRed(node->m_left))
				node = rotateRight(*node);
			/* left off */
		}
		
		return fixUp(node);
	}

	inline Node*
		removeMax(Node* node);

	inline Node*
		removeMin(Node* node);

	inline Node*
		rotateLeft(Node& h)
	{	// Make a right-leaning 3-node lean to the left.
		Node& x = *h.m_right;
		h.m_right = x.m_left;
		x.m_left = h;
		x.m_color = x.m_left->m_color;
		x.m_left->m_color = red;
		return &x;
	}

	inline Node*
		rotateRight(Node& h)
	{  // Make a left-leaning 3-node lean to the right.
		Node& x = *h.m_left;
		h.m_left = x.m_right;
		x.m_right = h;
		x.m_color = x.m_right->m_color;                   
		x.m_right->m_color = red;                     
		return &x;
	}

	inline void
		switchColor(Node& node)
	{
		node.m_color = !node.m_color;
	}

	Node*	
		m_root;
	
	uint	
		m_size;
}; // class RedBlackTree

template<typename ELEMENT> const bool RedBlackTree<ELEMENT>::red(true);
template<typename ELEMENT> const bool RedBlackTree<ELEMENT>::black(false);

template<typename ELEMENT> 
ELEMENT RedBlackTree<ELEMENT>::getMax(void) const
{
	return m_root ? getMax(m_root) : NULL;
}

template<typename ELEMENT> 
ELEMENT RedBlackTree<ELEMENT>::getMin(void) const
{
	return m_root ? getMin(m_root) : NULL;
}

template<typename ELEMENT> 
uint RedBlackTree<ELEMENT>::getSize(void) const
{
	return m_size;
}

template<typename ELEMENT> 
bool RedBlackTree<ELEMENT>::has(ELEMENT value) const
{
	return false;
}

template<typename ELEMENT> 
void RedBlackTree<ELEMENT>::insert(ELEMENT value)
{
	m_root = insert(m_root, value);
	m_root->m_color = black;
}

template<typename ELEMENT> 
bool RedBlackTree<ELEMENT>::isEmpty(void) const
{
	return m_root == NULL;
}

template<typename ELEMENT> 
void RedBlackTree<ELEMENT>::remove(ELEMENT value)
{
	m_root = remove(m_root, value);
	m_root->m_color = black;
}

template<typename ELEMENT> 
void RedBlackTree<ELEMENT>::removeMax(void)
{
	m_root = removeMax(m_root);
	m_root->m_color = black;
}

template<typename ELEMENT> 
void RedBlackTree<ELEMENT>::removeMin(void)
{
	m_root = removeMin(m_root);
	m_root->m_color = black;
}

#endif//REDBLACKTREE_H