#pragma once
#ifndef RED_BLACK_MAP_H
#define RED_BLACK_MAP_H

/**
An implementation of a Left Leaning variant of a Red Black Tree, described here:
www.cs.princeton.edu/~rs/talks/LLRB/RedBlack.pdf

<DEVELOPMENT STATUS>
Current Draft		:	0.0
Current Phase		:   DEVELOPMENT
Purpose				:	DEPLOYMENT, RESEARCH
Unit Tested			:	NO
Used in development	:	NO
Used in experiments :	YES
Tested in the field	:	NO
*/

#include <map>
#include <stack>
#include <vector>

#include "Platform.h"

namespace containers
{

template<
	typename KEY, 
	typename VALUE, 
	typename IS_EQUAL=std::equal_to<KEY>, 
	typename IS_GREATER=std::greater<KEY>, 
	typename IS_LESS=std::less<KEY>
>
class RedBlackMap
{
	class Node;

public:
	RedBlackMap(void);
	~RedBlackMap(void);
	
	class Iterator;	

	Iterator begin(void)
	{
		return Iterator(*this);
	}

	void deleteElements(void);
	Iterator end(void);
	VALUE get(const KEY& key) const;
	VALUE getMax(void) const;
	VALUE getMin(void) const;
	uint getSize(void) const;
	bool has(const KEY& key) const;
	bool has(const KEY& key, VALUE&) const;
	bool isEmpty(void) const;
	void remove(const KEY& key);
	void removeMax(void);
	void removeMin(void);
	void set(const KEY& key, VALUE value);

	class Iterator 
	{
	public:
		inline operator bool(void) const { return current || (!nodes.empty()); }
		inline bool operator!(void) const { return !(current || (!nodes.empty())); }
		
		inline Iterator& operator ++(void) 
		{ 
			FOREVER
			{
				if (iteration)
				{
					nodes.push(iteration);
					iteration = iteration->m_left;
					continue;
				}
				else if (!nodes.empty())
				{
					iteration = nodes.top();
					nodes.pop();
					current = iteration;
					iteration = iteration->m_right;
				}
				else
				{
					current = NULL;
					break;
				}
			}

			return *this;
		}
		
		/*inline Iterator operator ++(int) 
		{ 
			Iterator temp(*this); ++*this; return temp; 
		}
		*/
		inline VALUE& operator*(void) { return current->m_value; }
	
	public: // private:
		friend class RedBlackMap;		

		Iterator(void);
		
		Iterator(RedBlackMap& m) : current(NULL), iteration(m.m_root), map(&m)
		{
			++(*this);
		}

		Iterator& operator=(const Iterator& other)
		{
			current = other.current;
			iteration = other.iteration;
			map = other.map;
			nodes = other.nodes;
		}
		
		Node* current;
		Node* iteration;
		RedBlackMap* map;
		std::stack<Node*> nodes;
	}; // class Iterator

private:
	static const bool red;
	static const bool black;
	IS_LESS isLess;
	IS_EQUAL isEqual;
	IS_GREATER isGreater;

	class Node
	{	
	public:
		Node(void) {}
		~Node(void)
		{ /* empty */}

		static void deleteAndRecycle(Node* used)
		{
			if (used)
			{
				Node::deleteAndRecycle(used->m_left);
				Node::deleteAndRecycle(used->m_right);
				used->m_value.~VALUE();
				delete used;
			}
		}

		static Node* get(bool color, Node* left, Node* right, const KEY& key, VALUE& value)
		{
			return new Node(color, left, right, key, value);
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

		KEY
			m_key;
		
		VALUE	
			m_value;
	
	private:
		

		Node(bool color, Node* left, Node* right, const KEY& key, VALUE& value) //;
		: m_color(color)
		, m_left(left)
		, m_right(right)
		, m_key(key)
		, m_value(value)
		{ /* empty */}

	

	}; // class Node

	Node
		theEnd;

	inline Node* find(Node* node, const KEY& key) const
	{
		while (node)
		{	
			if (isEqual(key, node->m_key))
			{
				return node;
			}
			else if (isLess(key, node->m_key))
			{
				node = node->m_left;
			}
			else 
			{	
				assert(isGreater(key, node->m_key));				
				node = node->m_right;
			}
		}

		return NULL;
	}

	inline Node* find(const KEY& key) const
	{
		return find(m_root, key);
	}

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
		insert(Node* node, const KEY& key, VALUE& value)
	{
		if (!node)
		{
			m_size++;
			return Node::get(red, NULL, NULL, key, value);
		}
			
		const KEY& currentKey = node->m_key;
		
		if (isLess(key, currentKey))
		{
			node->m_left = insert(node->m_left, key, value);
		}
		else if (isGreater(key, currentKey))
		{		
			node->m_right = insert(node->m_right, key, value);
		}
		else
		{
			assert(isEqual(key, node->m_key)); 
		}

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
	{	// Assuming that node is red and both node.right and node.right.left
		// are black, make node.right or one of its children red.
		switchColor(*node);
		
		if (isRed(node->m_left->m_left))
		{ 
			node = rotateRight(*node);
			switchColor(*node);
		}

		return node;
	}

	inline Node*
		remove(Node* node, const KEY& key)
	{
		if (isLess(key, node->m_key))
		{
			if (!isRed(node->m_left) && !isRed(node->m_left->m_left))
				node = moveRedLeft(node);

			node->m_left = remove(node->m_left, key);
		}
		else
		{
			if (isRed(node->m_left))
				node = rotateRight(*node);
			
			if (isEqual(key, node->m_key) && !node->m_right)
			{
				Node::recycle(node);			
				return NULL;
			}

			if (!isRed(node->m_right) && !isRed(node->m_right->m_left))
				node = moveRedRight(node);

			if (isEqual(key, node->m_key))
			{
				Node* minRight = getMin(node->m_right);
				node->m_key = minRight->m_key;
				node->m_value = minRight->m_value;
				node->m_right = removeMin(node->m_right);
			}
			else
			{
				node->m_right = remove(node->m_right, key);
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

	mutable bool m_isBeingChecked;

// sanity testing
	inline void 
		checkUnitTest(void) const
	{
		if (!m_isBeingChecked)
		{
			m_isBeingChecked = true;
			
			if (m_size == 0)
			{
				assert(m_root == NULL);
			}
			else
			{
				assert(m_root);
				bool is_bst = isBST();
				bool is_234 = is234();
				bool is_balanced = isBalanced();
				assert(is_bst);
				assert(is_234);
				assert(is_balanced);
			}
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
		return isBST(m_root, getMax(m_root)->m_key, getMin(m_root)->m_key);
	}

	inline bool 
		isBST(Node* root, const KEY& max, const KEY& min) const
	{
		if (!root)
			return true;

		if (isLess(max, root->m_key) 
		|| isGreater(min,  root->m_key))
			return false;

		return isBST(root->m_left, root->m_key, min)
			&& isBST(root->m_right, max, root->m_key);
	}

public:
	bool
		isSpreadLessThan(uint spread)
	{	// needs to be 1 lg n
		std::vector<VALUE> depths;

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
		fillDepths(Node* node, uint depth, std::vector<VALUE>& depths)
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

}; // class RedBlackMap

template<typename KEY, typename VALUE, typename IS_EQUAL, typename IS_GREATER, typename IS_LESS> const bool RedBlackMap<KEY, VALUE, IS_EQUAL, IS_GREATER, IS_LESS>::red(true);
template<typename KEY, typename VALUE, typename IS_EQUAL, typename IS_GREATER, typename IS_LESS> const bool RedBlackMap<KEY, VALUE, IS_EQUAL, IS_GREATER, IS_LESS>::black(false);

template<typename KEY, typename VALUE, typename IS_EQUAL, typename IS_GREATER, typename IS_LESS>
RedBlackMap<KEY, VALUE, IS_EQUAL, IS_GREATER, IS_LESS>::RedBlackMap()
: m_root(NULL)
, m_size(0)
, m_isBeingChecked(false)
{ 
	/* empty */ 
}

template<typename KEY, typename VALUE, typename IS_EQUAL, typename IS_GREATER, typename IS_LESS>
RedBlackMap<KEY, VALUE, IS_EQUAL, IS_GREATER, IS_LESS>::~RedBlackMap()
{ 
	Node::recycle(m_root);
}

template<typename KEY, typename VALUE, typename IS_EQUAL, typename IS_GREATER, typename IS_LESS>
void RedBlackMap<KEY, VALUE, IS_EQUAL, IS_GREATER, IS_LESS>::deleteElements(void)
{	
	Node::deleteAndRecycle(m_root);
	m_root = NULL;
	m_size = 0;
}

template<typename KEY, typename VALUE, typename IS_EQUAL, typename IS_GREATER, typename IS_LESS>
VALUE RedBlackMap<KEY, VALUE, IS_EQUAL, IS_GREATER, IS_LESS>::get(const KEY& key) const
{
	if (Node* value = find(key))
	{
		return value->m_value;
	}
	else
	{
		return VALUE();
	}
}

template<typename KEY, typename VALUE, typename IS_EQUAL, typename IS_GREATER, typename IS_LESS> 
VALUE RedBlackMap<KEY, VALUE, IS_EQUAL, IS_GREATER, IS_LESS>::getMax(void) const
{	// checkUnitTest();();
	if (m_root)
		getMax(m_root);
	// checkUnitTest();();
	return m_root ? getMax(m_root)->m_value : NULL;
}

template<typename KEY, typename VALUE, typename IS_EQUAL, typename IS_GREATER, typename IS_LESS>
VALUE RedBlackMap<KEY, VALUE, IS_EQUAL, IS_GREATER, IS_LESS>::getMin(void) const
{	// checkUnitTest();();
	if (m_root)
		getMin(m_root);
	// checkUnitTest();();
	return m_root ? getMin(m_root)->m_value : NULL;
}

template<typename KEY, typename VALUE, typename IS_EQUAL, typename IS_GREATER, typename IS_LESS>
uint RedBlackMap<KEY, VALUE, IS_EQUAL, IS_GREATER, IS_LESS>::getSize(void) const
{	// checkUnitTest();();
	return m_size;
}

template<typename KEY, typename VALUE, typename IS_EQUAL, typename IS_GREATER, typename IS_LESS>
bool RedBlackMap<KEY, VALUE, IS_EQUAL, IS_GREATER, IS_LESS>::has(const KEY& key) const
{	// checkUnitTest();();
	return find(key) != NULL;
}

template<typename KEY, typename VALUE, typename IS_EQUAL, typename IS_GREATER, typename IS_LESS>
bool RedBlackMap<KEY, VALUE, IS_EQUAL, IS_GREATER, IS_LESS>::has(const KEY& key, VALUE& ifFound) const
{	// checkUnitTest();();
	if (Node* value = find(key))
	{
		ifFound = value->m_value;
		return true;
	}
	else
	{
		return false;
	}
}

template<typename KEY, typename VALUE, typename IS_EQUAL, typename IS_GREATER, typename IS_LESS>
bool RedBlackMap<KEY, VALUE, IS_EQUAL, IS_GREATER, IS_LESS>::isEmpty(void) const
{	// checkUnitTest();();
	return m_root == NULL;
}

template<typename KEY, typename VALUE, typename IS_EQUAL, typename IS_GREATER, typename IS_LESS>
void RedBlackMap<KEY, VALUE, IS_EQUAL, IS_GREATER, IS_LESS>::remove(const KEY& key)
{	// checkUnitTest();();
	if (has(key))
		m_size--;

	if (m_root)
		m_root = remove(m_root, key);
	
	if (m_root)
		m_root->m_color = black;
	// checkUnitTest();();
}

template<typename KEY, typename VALUE, typename IS_EQUAL, typename IS_GREATER, typename IS_LESS>
void RedBlackMap<KEY, VALUE, IS_EQUAL, IS_GREATER, IS_LESS>::removeMax(void)
{	// checkUnitTest();();
	if (m_root)
		m_root = removeMax(m_root);

	if (m_root)
		m_root->m_color = black;
	// checkUnitTest();();
}

template<typename KEY, typename VALUE, typename IS_EQUAL, typename IS_GREATER, typename IS_LESS>
void RedBlackMap<KEY, VALUE, IS_EQUAL, IS_GREATER, IS_LESS>::removeMin(void)
{	// checkUnitTest();();
	if (m_root)
		m_root = removeMin(m_root);

	if (m_root)
		m_root->m_color = black;
	// checkUnitTest();();
}

template<typename KEY, typename VALUE, typename IS_EQUAL, typename IS_GREATER, typename IS_LESS>
void RedBlackMap<KEY, VALUE, IS_EQUAL, IS_GREATER, IS_LESS>::set(const KEY& key, VALUE value) 
{
	m_root = insert(m_root, key, value);
	m_root->m_color = black;
}

} // namespace containers

#endif//RED_BLACK_MAP_H