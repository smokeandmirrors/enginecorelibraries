#pragma once
#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H
/**
An implementation of a Left Leaning variant of a Red Black Tree, described here:
www.cs.princeton.edu/~rs/talks/LLRB/RedBlack.pdf

\todo make key value implementation
\todo make STL-like
*/

#include <vector>
#include "Platform.h"

namespace containers
{

template<typename ELEMENT>
class RedBlackTree
{
public:
	static const bool red;
	static const bool black;
	
	RedBlackTree(void)
		: m_root(NULL)
		, m_size(0)
		, m_isBeingChecked(false)
	{ /* empty */ }

	~RedBlackTree(void)
	{ 
		Node::recycle(m_root);
	}

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
		static Node* get(bool color, Node* left, Node* right, ELEMENT value)
		{
			return new Node(color, left, right, value);
		}

		static void recycle(Node* used)
		{
			if (used)
			{
				Node::recycle(used->m_left);
				Node::recycle(used->m_right);	
				delete used;
			}
		}

		bool	
			m_color;
		
		Node*	
			m_left;
		
		Node*	
			m_right;
		
		ELEMENT	
			m_value;
	
	private:
		Node(bool color, Node* left, Node* right, ELEMENT value) //;
		: m_color(color)
		, m_left(left)
		, m_right(right)
		, m_value(value)
		{ /* empty */}

		~Node(void)
		{ /* empty */}

	}; // class Node

	inline Node* 
		fixUp(Node* node)
	{
		if (isRed(node->m_right))
			node = rotateLeft(*node);

		if (isRed(node->m_left) && isRed(node->m_left->m_left))
			node = rotateRight(*node);

		if (isRed(node->m_left) && isRed(node->m_right))
			switchColor(*node);

		return node;
	}

	inline Node* 
		insert(Node* node, ELEMENT value)
	{
		if (!node)
		{
			m_size++;
			return Node::get(red, NULL, NULL, value);
		}
			
		const ELEMENT& currentValue = node->m_value;
		
		if (value < currentValue)
			node->m_left = insert(node->m_left, value);
		
		else if (value > currentValue)
			node->m_right = insert(node->m_right, value);
		
		if (isRed(node->m_right))
			node = rotateLeft(*node);

		if (isRed(node->m_left) && isRed(node->m_left->m_left))
			node = rotateRight(*node);
				
		if (isRed(node->m_left) && isRed(node->m_right))
			switchColor(*node);
	
		return node;
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
		
		if (isRed(node->m_right->m_left))
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
		
		if (isRed(node->m_left->m_left))
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

			node->m_left = remove(node->m_left, value);
		}
		else
		{
			if (isRed(node->m_left))
				node = rotateRight(*node);
			
			if (value == node->m_value && !node->m_right)
			{
				Node::recycle(node);			
				return NULL;
			}

			if (!isRed(node->m_right) && !isRed(node->m_right->m_left))
				node = moveRedRight(node);

			if (value == node->m_value)
			{
				node = getMin(node->m_right);
				node->m_right = removeMin(node->m_right);
			}
			else
			{
				node->m_right = remove(node->m_right, value);
			}
		}
		
		return fixUp(node);
	}

	inline Node*
		removeMax(Node* node)
	{
		if (isRed(node->m_left))
			node = rotateRight(*node);

		if (!node->m_right)
		{
			Node::recycle(node);
			return NULL;
		}

		if (!isRed(node->m_right) && !isRed(node->m_right->m_left))
			node = moveRedRight(node);

		node->m_right = removeMax(node->m_right);

		return fixUp(node);
	}

	inline Node*
		removeMin(Node* node)
	{
		if (!node->m_left)
		{
			Node::recycle(node);
			return NULL;
		}

		if (!isRed(node->m_left) && !isRed(node->m_left->m_left))
			node = moveRedLeft(node);

		node->m_left = removeMin(node->m_left);

		return fixUp(node);
	}

	inline Node*
		rotateLeft(Node& h)
	{	// Make a right-leaning 3-node lean to the left.
		Node& x = *h.m_right;
		h.m_right = x.m_left;
		x.m_left = &h;
		x.m_color = x.m_left->m_color;
		x.m_left->m_color = red;
		return &x;
	}

	inline Node*
		rotateRight(Node& h)
	{  // Make a left-leaning 3-node lean to the right.
		Node& x = *h.m_left;
		h.m_left = x.m_right;
		x.m_right = &h;
		x.m_color = x.m_right->m_color;                   
		x.m_right->m_color = red;                     
		return &x;
	}

	inline void
		switchColor(Node& node)
	{
		node.m_color = !node.m_color;
		node.m_right->m_color = !node.m_right->m_color;
		node.m_left->m_color = !node.m_left->m_color;
	}

	Node*	
		m_root;
	
	uint	
		m_size;

	mutable bool 
		m_isBeingChecked;

// sanity testing
	inline void 
		check(void) const
	{
		if (!m_isBeingChecked)
		{
			m_isBeingChecked = true;
			bool is_bst = isBST();
			bool is_234 = is234();
			bool is_balanced = isBalanced();
			assert(is_bst);
			assert(is_234);
			assert(is_balanced);
			m_isBeingChecked = false;
		}
	}

	inline bool 
		is234(void) const
	{
		return is234(m_root);
	}

	inline bool 
		is234(Node* root) const
	{
		if (!root)
			return true;

		else if (isRed(root->m_right))
			return false;

		else if (isRed(root)
			&& isRed(root->m_left)
			&& isRed(root->m_left->m_left))
			return false;

		return is234(root->m_left) && is234(root->m_right);
	}

	inline bool 
		isBalanced(void) const
	{	// Do all paths from root to leaf have same number of black edges?
		int numBlack = 0; // number of black links on path from root to min
		Node* x = m_root;
		while (x)
		{
			if (!isRed(x))
				numBlack++;

			x = x->m_left;
		}

		return isBalanced(m_root, numBlack);
	}

	inline bool 
		isBalanced(Node* x, int numBlack) const
	{	// Does every path from the root to a leaf have the given number 
		// of black links?
		if (!x)
			return numBlack == 0;
		
		if (!isRed(x))
			numBlack--;

		return isBalanced(x->m_left, numBlack) 
			&& isBalanced(x->m_right, numBlack);
	}

	inline bool 
		isBST(void) const
	{
		return isBST(m_root, getMax(), getMin());
	}

	inline bool 
		isBST(Node* root, ELEMENT max, ELEMENT min) const
	{
		if (!root)
			return true;

		if ((max < root->m_value) || (min > root->m_value))
			return false;

		return isBST(root->m_left, root->m_value, min)
			&& isBST(root->m_right, max, root->m_value);
	}

public:
	bool
		isSpreadLessThan(uint spread)
	{	// needs to be 1 lg n
		std::vector<ELEMENT> depths;

		if (m_root)
		{
			fillDepths(m_root, 0, depths);
		}
		uint mindepth(100000);
		uint maxdepth(0);
		for (uint i = 0; i < depths.size(); i++)
		{
			if (depths[i] > maxdepth)
				maxdepth = depths[i];
			if (depths[i] < mindepth)
				mindepth = depths[i];
		}
		uint delta = maxdepth - mindepth;
		return delta < spread;

	}

	void 
		fillDepths(Node* node, uint depth, std::vector<ELEMENT>& depths)
	{
		if (!node)
		{
			depths.push_back(depth);
		}
		else
		{
			depth++;
			fillDepths(node->m_left, depth, depths);
			fillDepths(node->m_right, depth, depths);
		}
	}

}; // class RedBlackTree

template<typename ELEMENT> const bool RedBlackTree<ELEMENT>::red(true);
template<typename ELEMENT> const bool RedBlackTree<ELEMENT>::black(false);

template<typename ELEMENT> 
ELEMENT RedBlackTree<ELEMENT>::getMax(void) const
{	// check();
	if (m_root)
		getMax(m_root);
	// check();
	return m_root ? getMax(m_root)->m_value : NULL;
}

template<typename ELEMENT> 
ELEMENT RedBlackTree<ELEMENT>::getMin(void) const
{	// check();
	if (m_root)
		getMin(m_root);
	// check();
	return m_root ? getMin(m_root)->m_value : NULL;
}

template<typename ELEMENT> 
uint RedBlackTree<ELEMENT>::getSize(void) const
{	// check();
	return m_size;
}

template<typename ELEMENT> 
bool RedBlackTree<ELEMENT>::has(ELEMENT value) const
{	// check();
	if (Node* node = m_root)
	{
		do 
		{
			if (value == node->m_value)
				return true;

			else if (value < node->m_value)
				node = node->m_left;

			else 
				node = node->m_right;

		} while (node);
	}

	return false;
}

template<typename ELEMENT> 
void RedBlackTree<ELEMENT>::insert(ELEMENT value)
{	// check();
	m_root = insert(m_root, value);
	m_root->m_color = black;
	// check();
}

template<typename ELEMENT> 
bool RedBlackTree<ELEMENT>::isEmpty(void) const
{	// check();
	return m_root == NULL;
}

template<typename ELEMENT> 
void RedBlackTree<ELEMENT>::remove(ELEMENT value)
{	// check();
	if (has(value))
		m_size--;

	if (m_root)
		m_root = remove(m_root, value);
	
	if (m_root)
		m_root->m_color = black;
	// check();
}

template<typename ELEMENT> 
void RedBlackTree<ELEMENT>::removeMax(void)
{	// check();
	if (m_root)
		m_root = removeMax(m_root);

	if (m_root)
		m_root->m_color = black;
	// check();
}

template<typename ELEMENT> 
void RedBlackTree<ELEMENT>::removeMin(void)
{	// check();
	if (m_root)
		m_root = removeMin(m_root);

	if (m_root)
		m_root->m_color = black;
	// check();
}

} // namespace containers

#endif//REDBLACKTREE_H