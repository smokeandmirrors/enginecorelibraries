#pragma once
#ifndef TABLE_H
#define TABLE_H

#define DEVELOP_TABLE 0
#if DEVELOP_TABLE

#include "Hashing.h"
#include "Strings.h"

/**
An implementation of an associative array, explicity based on the
Lua table as much as possible.

WARNING: THIS IS A LEARNING EXERCISE, AND IS NOT
INTENDED FOR DEPLOYMENT
*/

template<typename T> 
class isLess
{
public:
	bool operator()(const T& a, const T& b) const
	{
		return a < b;
	}
};

template<typename T> 
class isGreater
{
public:
	bool operator()(const T& a, const T& b) const
	{
		return a > b;
	}
};

template<> 
class isLess<std::string>
{
public:
	bool operator()(const std::string& a, const std::string& b) const
	{
		return String::compare(a.c_str(), b.c_str()) < 0;
	}
};

template<> 
class isGreater<std::string>
{
public:
	bool operator()(const std::string& a, const std::string& b) const
	{
		return String::compare(a.c_str(), b.c_str()) > 0;
	}
};
namespace containers
{

static const sint maxBits(30);
static const sint maxArraySize( 1 << maxBits);
static const sint valid(1);
static const sint invalid(0);

template<typename ELEMENT>
class Table 
{
	class Value;
public:
	friend class Iterator;

	class Key
	{
	friend class Table;
	public:
		enum Type
		{
			boolean = 1 << 0,
			integer = 1 << 1,
			invalid = 1 << 2,
			pointer = 1 << 3,
			real	= 1 << 4,
			string	= 1 << 5,		
		}; // enum Type

		Key(void)
		: type(Key::invalid)
		, key(0)
		, originalKeyString("")
		{ /* empty */ }
		
		explicit Key(bool source)
		: original(source)
		, type(Key::boolean)
		, key(algorithms::computeHash(source))  
		, originalKeyString("")
		{ /* empty */ }

		Key(const char* source)
		: originalKeyString(source)
		, type(Key::string)
		, key(originalKeyString.getHash())
		{ }
		/** 
		\todo this below should have worked for const char* 
		there are enough conversion operators, 
		but it doesn't 
		*/
		Key(const String::Immutable& source)
		: originalKeyString(source)
		, type(Key::string)
		, key(originalKeyString.getHash())
		{ /* empty */ }

		explicit Key(const void* source)
		: original(source) 
		, type(source ? Key::pointer : Key::invalid)
		, key(source ? algorithms::computeHash(source) : 0)
		, originalKeyString("")
		{/* empty */}

		Key(sint source)
		: original(source)
		, type(Key::integer) 
		, key(algorithms::computeHash(source))
		, originalKeyString("")
		{/* empty */}

		explicit Key(sreal source) 
		: original(source) 
		, type(Key::real)
		, key(algorithms::computeHash(source))
		, originalKeyString("")
		{/* empty */}
		
		inline bool
			isValid(void) const
		{
			return (type & Key::invalid) == 0;
		}

		inline bool 
			operator!(void) const
		{
			return (type & Key::invalid) != 0;
		}

		inline bool 
			operator==(const Key& other) const
		{
			return (type & other.type) && key == other.key;
		}

		inline Key& 
			operator=(const Key& source)
		{
			key = source.key;
			type = source.type;
			original = source.original;
			originalKeyString = source.originalKeyString;
			return *this;
		}

		union originalType
		{
			bool				keyBool;
			const void*			keyPointer;
			sint				keyInteger;
			sreal				keyReal;
			
			originalType() 
				{}
			
			originalType(bool source) 
				: keyBool(source) {}
			
			originalType(const void* source) 
				: keyPointer(source) {}
			
			originalType(sint source) 
				: keyInteger(source) {}
			
			originalType(sreal source) 
				: keyReal(source) {}
			
		} original; // union originalType

	private:
		inline void 
			beginIteration(void)
		{
			type = Key::integer;
		}

		String::Immutable
			originalKeyString;

		Type 
			type;

		algorithms::hash 
			key;
	}; // Key

	class Iterator
	{
	friend class Table;
	public:
		Iterator(Table& table)
			: k(table.getIterator())
			, t(table)
			, v(NULL)
		{
			shouldContinue = t.next(k, v);
		}

		operator bool(void) const
		{
			return shouldContinue;
		}

		bool
			operator!(void) const
		{
			return !shouldContinue;
		}

		Iterator& 
			operator ++(void) 
		{
			shouldContinue = t.next(k, v);
			return *this;
		}

		Iterator
			operator ++(int)
		{
			shouldContinue = t.next(k, v);
			return *this;
		}

		ELEMENT&
			operator->(void)
		{
			return v->value;
		}	

		ELEMENT&
			operator*(void)
		{
			return v->value;
		}

	private:
		Iterator(void);
		
		Iterator
			operator=(const Iterator&);

		bool
			shouldContinue;

		Table& 
			t;

		Value*
			v;
		
		Key 
			k;
	}; // class Iterator

private:
	class Value
	{
	public:
		Value(void)
		: isValid(invalid)
		{
			/* empty */
		}

		Value(ELEMENT v)
		: isValid(valid)
		, value(v)
		{
			/* empty */
		}

		Value& 
			operator=(const Value& original)
		{
			isValid = original.isValid;
			value = original.value;
			return *this;
		}	

		bool 
			operator!(void) const
		{
			return isValid != valid;
		}

		void
			validate(void)
		{
			isValid = valid;
		}
		
		void 
			invalidate(void)
		{
			isValid = invalid;
		}
		
		operator sint(void) const
		{
			return isValid;
		}

		ELEMENT 
			value;
	
	private:
		sint 
			isValid;
	}; // Value

	struct Node
	{
		Node(void)
			: next(NULL) 
		{
			/* empty, should be completely invalid */
		}

		Node(ELEMENT v, const Key& k)
		: key(k)
		, next(NULL) 
		, value(v)
		{
			/* empty */
		}
		
		Node& operator=(const Node& original)
		{
			value = original.value;
			key = original.key;
			return *this;
		}

		Key
			key;
		
		Node*
			next;

		Value
			value;
	}; // Node

public:
	// Table *luaH_new (lua_State *L);
	Table(sint reserveArraySize=0, sint reserveHashSize=0); 
	// void luaH_free (lua_State *L, Table *t);
	~Table(void); 
	
	ELEMENT& 
		get(const Key& key);
	
	const ELEMENT& 
		get(const Key& key) const;
	
	void
		insertAtIndex(const ELEMENT& value, uint index);

	bool 
		has(const Key& key) const;

	void
		popBack(void);

	void
		pushBack(const ELEMENT& value);
	
	void
		remove(const Key& key);
	
	void
		removeAtIndex(sint index);
		
	void 
		reserve(sint reserveArraySize, sint reserveHashSize=0);
	
	void
		set(const Key& key, const ELEMENT& value);

	template<typename COMPARATOR> inline void 
		sort(COMPARATOR predicate=isGreater<ELEMENT>())
	{
		sint hi = findLowestValidNumericalIndexFollowedByInvalidValue();
		sortImplementation(0, hi, predicate);		
	}

private:
	/// \todo will template versions of these be unnecessarily generated? 
	// static int computesizes (int nums[], int *narray)
	static inline bool
		calculateArrayIndex(const Key& key, sint& arrayIndex);
	
	static inline sint
		calculateNewArraySize(sint nums[], sint& numArrays);
	// static int countint (const TValue *key, int *nums)
	static inline sint
		countInt(const Key& key, sint* outputNumbers);

	static inline Node
		createDummyNode(void);

	static inline sint
		logTwoCeil(uint x);

	static inline sint 
		twoTo(sint x);

	static Node
		dummyNode;
	// auxiliary search function (which is duplicate code in ltable.c)
	inline sint 
		binarySearch(uint high, uint low) const;
	// static int numusearray (const Table *t, int *nums)
	inline sint 
		countKeysInArray(sint* perSlotOutput) const;
	// static int numusehash (const Table *t, int *nums, int *pnasize)
	inline sint 
		countKeysInHash(sint* perSlotOutput, sint& keysInArray) const;
	// const TValue *luaH_get (Table *t, const TValue *key);
	inline Value*
		getInternal(const Key& key) const;
	// static int findindex (lua_State *L, Table *t, StkId key)
	inline sint 
		findIndex(Key& key) const;
	// LUAI_FUNC int luaH_getn (Table *t);
	inline sint
		findLowestValidNumericalIndexFollowedByInvalidValue(void) const;
	// const TValue *luaH_getint (Table *t, int key);
	inline Value*
		findValueWithSignedInteger(const Key& key) const;
	// const TValue *luaH_getstr (Table *t, TString *key);	
	inline Value*
		findValueWithString(const Key& key) const;
	// static Node *getfreepos (Table *t)
	inline Node*
		getFreePosition(void);
	inline Key
		getIterator(void) const;
	// #define hashboolean(t,p)        hashpow2(t, p)
	inline Node*
		getPositionHashMod(const Key& key) const;
	// #define hashpointer(t,p)	hashmod(t, IntPoint(p))
	inline Node*
		getPositionHashModPowerOf2(const Key& key) const;
	// static Node *mainposition (const Table *t, const TValue *key)
	inline Node* 
		getMainPosition(const Key& key) const;
	// #define sizenode(t)	(twoto((t)->lsizenode))
	inline uint
		getSizeOfHashPart(void) const;
	// #define hashmod(t,n)	(gnode(t, ((n) % ((sizenode(t)-1)|1))))
	inline uint
		hashMod(const algorithms::hash  key) const;
	// #define hashpow2(t,n)      (gnode(t, lmod((n), sizenode(t))))
	inline uint
		hashModPowerOf2(const algorithms::hash  powerOf2) const;
	inline bool
		isMainPositionIsTaken(Node*) const;
	// LUAI_FUNC int luaH_next (lua_State *L, Table *t, StkId key);
	inline bool 
		next(Key& k, Value*& v) const;
	// TValue *luaH_newkey (lua_State *L, Table *t, const TValue *key)
	inline Value*
		newKey(const Key& key);
	// static void rehash (lua_State *L, Table *t, const TValue *ek)
	inline void
		rehash(const Key& key);
	// void luaH_resize (lua_State *L, Table *t, int newArraySize, int nhsize);
	inline void
		resize(sint arraySize, sint hashSize);
	// void luaH_resizearray (lua_State *L, Table *t, int newArraySize);
	inline void
		resizeArray(uint newArraySize);
	// static void setnodevector (lua_State *L, Table *t, int size)
	inline void
		resizeHash(uint newHashSize);
	// TValue *luaH_set (lua_State *L, Table *t, const TValue *key);
	inline Value*
		setInternal(const Key& key);
	// void luaH_setint (lua_State *L, Table *t, int key, TValue *value);
	inline Value* /* very good optimization candidate? */
		setWithInteger(const Key& key, const ELEMENT& value);
	// auxsort
	template<typename COMPARATOR> inline void 
		sortImplementation(const sint left, const sint right, const COMPARATOR& predicate)
	{
		/*
		Quicksort with 3-way partitioning
		from QUICKSORT IS OPTIMAL
		Robert Sedgewick
		Jon Bentley
		http://www.sorting-algorithms.com/static/QuicksortIsOptimal.pdf
		*/
		

		if (left < right)
		{
			sint i = left - 1;
			sint j = right;
			sint p = left - 1;
			sint q = right;
			
			ELEMENT v = get(right);

			for (;;)
			{
				while (predicate(get(++i), v))
				{ /* empty */ }
				
				while (predicate(v, get(--j)))
				{
					if (j == left)
					{
						break;
					}
				}

				if (i >= j)
				{
					break;
				}
				
				quickSwap(get(i), get(j));
				
				if (get(i) == v)
				{
					++p;
					quickSwap(get(p), get(i));
				}

				if (v == get(j))
				{
					--q;
					quickSwap(get(j), get(q));
				}
			} // for (;;)

			quickSwap(get(i), get(right));
			j = i - 1;
			i = i + 1;
			
			for (sint k = left; k < p; k++, j--)
			{
				quickSwap(get(k), get(j));
			}

			for (sint k = right - 1; k > q; k--, i++)
			{
				quickSwap(get(i), get(k));
			}

			sortImplementation(left, j, predicate);
			sortImplementation(i, right, predicate);
		} // if (left < right)

		/*
		Quicksort
		** (based on `Algorithms in MODULA-3', Robert Sedgewick;
		**  Addison-Wesley, 1993.)
		** based on ltablib.c
		while (lo < hi)
		{	// sort elements t[lo], t[(lo + hi) / 2] and t[hi] 
			sint i, j;
			{
				{
					const ELEMENT& vlo = get(lo);
					const ELEMENT& vhi = get(hi);
					
					if (predicate(vhi, vlo))
					{	// a[vhi] < a[vlo]
						swap(vlo, lo, vhi, hi);
					}
				}
				// there are only two
				if ((hi-lo) == 1)
					break; 

				i = (lo + hi) / 2;

				{
					const ELEMENT& vi = get(i);
					const ELEMENT& vlo = get(lo);
					
					if (predicate(vi, vlo))
					{	// a[i] < a[lo]
						swap(vi, i, vlo, lo);
					}
					else
					{
						const ELEMENT& vhi = get(hi);

						if (predicate(vhi, vi))
						{	// a[hi] < a[i]
							swap(vi, i, vhi, hi);
						}
					}
				}
				// there are only 3
				if ((hi - lo) == 2)
					break;
			}
			// t[lo] <= Pivot == t[hi - 1] <= t[hi]; sort lo + 1 to hi - 2
			{	// pivot
				const ELEMENT& pivot = get(i);
				const ELEMENT& vhiMinusOne = get(hi - 1);
				swap(pivot, i, vhiMinusOne, hi - 1);
				i = lo;
				j = hi - 1;
				
				for (;;) // invariant: t[lo..i] <= Pivot <= t[j..hi]
				{	// repeat ++i until t[i] >= Pivot
					for(;;)
					{
						++i;
						const ELEMENT& vi = get(i);
						
						if (predicate(vi, pivot))
						{
							assert(i < hi); // invalid sort function
						}
						else
						{
							break;
						}
					} // repeat ++i until t[i] >= Pivot
					// repeat --j until t[j] <= Pivot
					for(;;)
					{
						--j;
						const ELEMENT& vj = get(j);
						
						if (predicate(pivot, vj))
						{
							assert(j > lo); // invalid sort function
						}
						else
						{
							break;
						}		
					} // repeat --j until t[j] <= Pivot

					if (j < i)
					{
						break;
					}

					const ELEMENT& vi = get(i);
					const ELEMENT& vj = get(j);
					swap(vi, i, vj, j);
					
				} // invariant: t[lo..i] <= Pivot <= t[j..hi]	
			} 
			// swap pivot (a[u-1]) with a[i]
			const ELEMENT& pivot = get(i);
			const ELEMENT& vhiMinusOne = get(hi - 1);
			swap(pivot, i, vhiMinusOne, hi - 1);			
			// a[l..i-1] <= a[i] == P <= a[i+1..u] 
			// adjust so that smaller half is in [j..i] and larger one in [l..u] 
 			if ((i - lo) < (hi - i))
			{
				j = lo;
				--i;
				lo = i + 2;
			}
			else
			{
				j = i + 1;
				i = hi;
				hi = j - 2;
			}

			sortImplementation(j, i, predicate);
		}
		*/
	}

	inline void
		swap(const ELEMENT& vlo, const Key& lo, const ELEMENT& vhi, const Key& hi) 
	{
		Value& loV = *findValueWithSignedInteger(lo);
		Value& hiV = *findValueWithSignedInteger(hi);
		const ELEMENT c = vlo;
		loV.value = vhi;
		hiV.value = c;
	}

	inline void 
		swap(const Key& lo, const Key& hi) 
	{
		Value& loV = *findValueWithSignedInteger(lo);
		Value& hiV = *findValueWithSignedInteger(hi);
		const ELEMENT c = loV.value;
		loV.value = hiV.value;
		hiV.value = c;
	}

	inline void
		quickSwap(ELEMENT& a, ELEMENT& b) 
	{
		ELEMENT c(a);
		a = b;
		b = c;
	}
	// lu_byte lsizenode;
	uchar 
		log2HashPartSize;
	// int sizearray;
	uint
		arrayPartSize;
	// Node *lastfree;
	Node*					
		lastFree;
	// Node *node;
	Node*					
		hashPart;
	// TValue *array;
	Value*	
		arrayPart;
}; // Table

template<typename ELEMENT> 
typename Table<ELEMENT>::Node Table<ELEMENT>::dummyNode(Table<ELEMENT>::createDummyNode());

// LUAI_FUNC Table *luaH_new (lua_State *L, int narray, int lnhash);
template<typename ELEMENT> 
Table<ELEMENT>::Table(sint reserveArraySize, sint reserveHashSize)
: log2HashPartSize(0)
, arrayPartSize(0)
, hashPart(&dummyNode)
, lastFree(NULL)
, arrayPart(NULL)
{
	if (reserveArraySize || reserveHashSize)
		resize(reserveArraySize, reserveHashSize);
}
// LUAI_FUNC void luaH_free (lua_State *L, Table *t);
template<typename ELEMENT>
Table<ELEMENT>::~Table(void)
{
	if (hashPart != &dummyNode)
	{
		delete[] hashPart;
	}

	delete[] arrayPart;
}

template<typename ELEMENT>
uint Table<ELEMENT>::hashMod(const algorithms::hash key) const
{	// hashmod
	return key % ((getSizeOfHashPart() - 1) | 1);
}

template<typename ELEMENT>
uint Table<ELEMENT>::hashModPowerOf2(const algorithms::hash key) const
{	
	return algorithms::modHashPowerOf2(key, getSizeOfHashPart());
}

template<typename ELEMENT>
bool Table<ELEMENT>::calculateArrayIndex(const Key& key, sint& arrayIndex)
{
	if (key.type & Key::integer
	&& key.original.keyInteger >= 0)
	{
		arrayIndex = key.original.keyInteger;
		return true;
	}
	else
	{
		return false;
	}
}

template<typename ELEMENT>
sint Table<ELEMENT>::calculateNewArraySize(sint nums[], sint& numArrays)
{
	sint i;
	sint twotoi;	/* 2^i */
	sint a = 0;		/* number of elements smaller than 2^i */
	sint na = 0;	/* number of elements to go to array part */
	sint n = 0;		/* optimal size for array part */
	for (i = 0, twotoi = 1; twotoi/2 < numArrays; i++, twotoi *= 2) 
	{
		if (nums[i] >= 0) 
		{
			a += nums[i];
			
			if (a > twotoi/2) 
			{  /* more than half elements present? */
				n = twotoi;  /* optimal size (till now) */
				na = a;  /* all elements smaller than n will go to array part */
			}
		}

		if (a == numArrays) 
			break;  /* all elements already counted */
	}
	numArrays = n;
	assert(numArrays/2 <= na && na <= numArrays);
	return na;
}

template<typename ELEMENT>
sint Table<ELEMENT>::countInt(const Key& key, sint* outputNumbers)
{
	sint arrayIndex;
	
	if (calculateArrayIndex(key, arrayIndex))
	{
		if (arrayIndex < maxArraySize)
		{
			outputNumbers[logTwoCeil(arrayIndex + 1)]++;
			return 1;
		}
	}

	return 0;
}

template<typename ELEMENT> 
sint Table<ELEMENT>::countKeysInArray(sint* perSlotOutput) const
{	
	sint logBase2;
	sint twoToLogBase2;  /* 2 ^ logBase2 */
	sint total = 0;  
	sint index = 1;  
	sint arraySize = arrayPartSize;
	// for each slice
	for (logBase2 = 0, twoToLogBase2 = 1; logBase2 <= maxBits; logBase2++, twoToLogBase2 *= 2) 
	{  
		sint counter = 0;  
		sint upperLimit = twoToLogBase2;

		if (upperLimit > arraySize) 
		{
			upperLimit = arraySize;  
			
			if (index > upperLimit)
			{	// no more elements to count
				break;  
			}
		}
		
		// count elements in range (2^(logBase2-1), 2^logBase2]
		for (; index <= upperLimit; index++) 
		{	
			counter += arrayPart[index - 1];				
		}
		
		perSlotOutput[logBase2] += counter;
		total += counter;
	}

	return total;
}

template<typename ELEMENT>
sint Table<ELEMENT>::countKeysInHash(sint* perSlotOutput, sint& keysInArray) const
{
	sint totaluse = 0;  /* total number of elements */
	sint summationOfNums = 0;  /* summation of `nums' */
	sint i = getSizeOfHashPart();
	
	while (i--) 
	{
		Node *n = &(hashPart[i]);
		
		if (n->value) 
		{
			summationOfNums += countInt(n->key, perSlotOutput);
			totaluse++;
		}
	}
	
	keysInArray += summationOfNums;
	return totaluse;
}

template<typename ELEMENT> 
typename Table<ELEMENT>::Node Table<ELEMENT>::createDummyNode(void)
{
	Node node;
	node.next = NULL;
	node.value.invalidate();
	return node;
}

template<typename ELEMENT>
sint Table<ELEMENT>::findIndex(Key& iter) const
{
	if (!iter)
	{// first iteration
		iter.beginIteration();
		return -1;
	}
	else
	{	
		sint index;

		if (calculateArrayIndex(iter, index)
			&& index < static_cast<sint>(arrayPartSize))
		{	// in the array part
			return index;
		}
		else
		{	// check for hash part
			Node* n = getMainPosition(iter);

			do 
			{
				if (n->key == iter)
				{
					return static_cast<sint>(n - hashPart) + arrayPartSize;
				}
				else
				{
					n = n->next;
				}
			} 
			while (n);
			/*else invalid key, assert?*/
			assert(false);
			return -2;
		}
	}
}

template<typename ELEMENT>
sint Table<ELEMENT>::binarySearch(uint high, uint low) const
{
	while (high - low > 1)
	{
		uint middle = (high + low) / 2;

		if (!arrayPart[middle - 1])
		{
			high = middle;
		}
		else
		{
			low = middle;
		}
	}

	return static_cast<sint>(low);
}

template<typename ELEMENT>
sint Table<ELEMENT>::findLowestValidNumericalIndexFollowedByInvalidValue(void) const
{
	uint high = arrayPartSize;

	if (arrayPartSize > 0 && !arrayPart[high - 1])
	{	// there is a boundary in the array part, binary search for it
		/// \todo why binary search here, are the arry keys sorted somehow?
		return binarySearch(high, 0) - 1;
	}
	else if (hashPart == &dummyNode)
	{
		return static_cast<sint>(high) - 1;
	}
	else
	{	// unbound search
		uint low = high;
		high++;

		while (findValueWithSignedInteger(high))
		{	// find high and low such that high is present and low is not
			low = high;
			high *= 2;
			
			if (static_cast<sint>(high) > (INT_MAX - 2))
			{	// "table was built with bad purposes: resort to linear search" - ltable.c
				low = 0;
				
				while (findValueWithSignedInteger(low))
				{
					low++;
				}

				return low - 1;
			}
		}
		// now binary search between them
		return binarySearch(high, low) - 1;
	}
}

template<typename ELEMENT> 
typename Table<ELEMENT>::Value* Table<ELEMENT>::findValueWithSignedInteger(const Key& key) const
{	
	sint index = key.original.keyInteger;
	
	if (index >= 0 
	&& index < static_cast<sint>(arrayPartSize))
	{
		return &arrayPart[index];
	}
	// how this is never NULL, I don't know
	Node* n = &hashPart[hashMod(key.key)];

	do 
	{
		if (n->key.type & Key::integer
		&& n->key.original.keyInteger == key.original.keyInteger)
		{
			return &n->value;
		}

		n = n->next;			
	} 
	while (n);

	return NULL;
}

template<typename ELEMENT> 
typename Table<ELEMENT>::Value* Table<ELEMENT>::findValueWithString(const Key& key) const
{	
	uint index = hashMod(key.key);
	Node* n = &hashPart[index];

	do 
	{
		if (n->key.type & Key::string
		&& n->key.originalKeyString == key.originalKeyString)
		{
			return &n->value;
		}

		n = n->next;
	} 
	while (n);

	return NULL;
}
/* LUAI_FUNC const TValue *luaH_get (Table *t, const TValue *key);
LUAI_FUNC TValue *luaH_set (lua_State *L, Table *t, const TValue *key);	*/
template<typename ELEMENT> 
typename ELEMENT& Table<ELEMENT>::get(const Key& key)
{	
	Value* position = getInternal(key);

	if (!position)
	{
		position = newKey(key);
	}

	return position->value;
}
/* LUAI_FUNC const TValue *luaH_get (Table *t, const TValue *key);
LUAI_FUNC TValue *luaH_set (lua_State *L, Table *t, const TValue *key);	*/
template<typename ELEMENT> 
const ELEMENT& Table<ELEMENT>::get(const Key& key) const
{	
	return get(key);
}

template<typename ELEMENT>
typename Table<ELEMENT>::Key Table<ELEMENT>::getIterator(void) const
{
	return Key();
}

template<typename ELEMENT> 
typename Table<ELEMENT>::Value* Table<ELEMENT>::getInternal(const Key& key) const
{
	switch (key.type)
	{
		case Key::invalid:
			return NULL;
	
		case Key::integer:
			return findValueWithSignedInteger(key);

		case Key::string:
			return findValueWithString(key);
			
		case Key::pointer:
		case Key::boolean:
		case Key::real:
		{
			Node* node = getMainPosition(key);
			
			do 
			{
				if (node->key == key)
				{
					return &node->value;
				}
				else
				{
					node = node->next;
				}
			} 
			while (node);
			break;
		}
		
		default:
			assert(false);
	} // switch (key.type)

	return NULL;
} // const Table<ELEMENT>::Value* Table<ELEMENT>::getInternal(const Key& key) const

template<typename ELEMENT> 
typename Table<ELEMENT>::Node* Table<ELEMENT>::getFreePosition(void) 
{
	while (lastFree > hashPart)
	{
		lastFree--;

		if (!lastFree->value)
			return lastFree;
	}	
	// no free position
	return NULL;
}

template<typename ELEMENT> 
typename Table<ELEMENT>::Node* Table<ELEMENT>::getPositionHashMod(const Key& key) const
{
	uint index = hashMod(key.key);
	return &hashPart[index];
}

template<typename ELEMENT> 
typename Table<ELEMENT>::Node* Table<ELEMENT>::getPositionHashModPowerOf2(const Key& key) const
{
	uint index = hashModPowerOf2(key.key);
	return &hashPart[index];
}

template<typename ELEMENT> 
typename Table<ELEMENT>::Node* Table<ELEMENT>::getMainPosition(const Key& key) const
{
	switch (key.type)
	{
	case Key::boolean:
	case Key::string:
		return getPositionHashModPowerOf2(key);
	
	case Key::integer:
	case Key::real:
	case Key::pointer:
		return getPositionHashMod(key); 
	
	default:
		assert(false);
	}
	
	return &dummyNode;
}

template<typename ELEMENT> 
uint Table<ELEMENT>::getSizeOfHashPart(void) const
{
	return twoTo(log2HashPartSize);
}

template<typename ELEMENT> 
bool Table<ELEMENT>::has(const Key& key) const
{
	Value* v = getInternal(key);
	return v && *v;
}

template<typename ELEMENT> 
void Table<ELEMENT>::insertAtIndex(const ELEMENT& value, uint p)
{
	sint position = static_cast<sint>(p);
	sint index = findLowestValidNumericalIndexFollowedByInvalidValue();

	if (position > index && index >= 0)
	{
		index = position;
	}

	Key key(1);

	for (sint i = index; i > position; i--)
	{
		key.original.keyInteger = i;
		Value* v = findValueWithSignedInteger(key);
		key.original.keyInteger = i + 1;
		setWithInteger(key, v->value);
	}

	Value* v = setWithInteger(position, value);
	v->validate();
}

template<typename ELEMENT> 
bool Table<ELEMENT>::isMainPositionIsTaken(Node* mainPosition) const
{
	return mainPosition->value || (mainPosition == &dummyNode);
}

template<typename ELEMENT> 
sint Table<ELEMENT>::logTwoCeil(uint x)
{
	static const uchar logBaseTwoArray[256] = {
		0,1,2,2,3,3,3,3,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
		6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
		7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
		7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
		8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
		8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
		8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
		8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8
	};

	sint l = 0;
	assert(x > 0);
	x--;

	while (x >= 256) 
	{ 
		l += 8; 
		x >>= 8; 
	}
	
	return l + logBaseTwoArray[x];
}

template<typename ELEMENT>
bool Table<ELEMENT>::next(Key& iter, Value*& value) const
{
	sint index = findIndex(iter) + 1;
	
	for (; index < static_cast<sint>(arrayPartSize); index++)
	{
		if (arrayPart[index])
		{
			value = &arrayPart[index];
			iter.original.keyInteger = index;
			return true;
		}
	}

	sint sizeHashPart = static_cast<sint>(getSizeOfHashPart());
	
	for (index -= arrayPartSize; index < sizeHashPart; index++)
	{
		if (hashPart[index].value)
		{
			value = &hashPart[index].value;
			iter = hashPart[index].key;
			return true;
		}
	}

	return false;
}

/*
** inserts a new key into a hash table; first, check whether key's main 
** position is free. If not, check whether colliding node is in its main 
** position or not: if it is not, move colliding node to an empty place and 
** put new key in its main position; otherwise (colliding node is in its main 
** position), new key goes to an empty position. 
*/
template<typename ELEMENT>
typename Table<ELEMENT>::Value* Table<ELEMENT>::newKey(const Key& key)
{
	assert(key.isValid()); 
	Node* mainPosition = getMainPosition(key);
		
	if (isMainPositionIsTaken(mainPosition))
	{
		Node* freePosition = getFreePosition();

		if (!freePosition)
		{
			rehash(key);
			return setInternal(key);
		}
		
		assert(mainPosition != &dummyNode);
		Node* other = getMainPosition(mainPosition->key);

		if (other != mainPosition)
		{	// colliding node is out of its main position
			// move the colliding node into the free position
			while (other->next != mainPosition)
			{	// find the previous node
				other = other->next;
			}
			// redo the chain with free position in place of main position
			other->next	 = freePosition;
			// copy colliding node into free position
			*freePosition = *mainPosition;
			// main position is now free
			mainPosition->next = NULL;
			mainPosition->value.invalidate();
		}
		else
		{	// colling node is in its own main position
			// new node will go into free position
			freePosition->next = mainPosition->next;
			// chain the new position
			mainPosition->next = freePosition;
			mainPosition = freePosition;
		}
	}
	
	mainPosition->key = key;
	assert(!mainPosition->value);
	return &(mainPosition->value);
}

template<typename ELEMENT>
void Table<ELEMENT>::popBack(void)
{
	sint index = findLowestValidNumericalIndexFollowedByInvalidValue();
	
	if (index >= 0)
	{
		Value* v = findValueWithSignedInteger(index);
		v->invalidate();
	}
}

template<typename ELEMENT>
void Table<ELEMENT>::pushBack(const ELEMENT& value)
{
	sint index = findLowestValidNumericalIndexFollowedByInvalidValue() + 1;
	Value* v = setWithInteger(index, value);
	v->validate();
}

template<typename ELEMENT> 
void Table<ELEMENT>::rehash(const Key& key)
{
	sint newArraySize, numUsedInArray;
	sint nums[maxBits+1];  /* nums[i] = number of keys with, 2^(i-1) keys 2^i */
	sint i;
	sint totaluse;
	for (i=0; i<=maxBits; i++) nums[i] = 0;  /* reset counts */
	newArraySize = countKeysInArray(nums);  /* count keys in arrayPart part */
	totaluse = newArraySize;  /* all those keys are integer keys */
	totaluse += countKeysInHash(nums, newArraySize);  /* count keys in hash part */
	/* count extra key */
	newArraySize += countInt(key, nums);
	totaluse++;
	/* compute new size for arrayPart part */
	numUsedInArray = calculateNewArraySize(nums, newArraySize);
	/* resize the table to new computed sizes */
	resize(newArraySize, totaluse - numUsedInArray);	
}

template<typename ELEMENT>
void Table<ELEMENT>::remove(const Key& key)
{
	if (Value* value = getInternal(key))
	{
		value->invalidate();
	}
}

template<typename ELEMENT>
void Table<ELEMENT>::removeAtIndex(sint position)
{
	sint index = findLowestValidNumericalIndexFollowedByInvalidValue();
	
	if (position >= 0 
	&& index >= 0 
	&& position <= index)
	{
		Value* atPosition = findValueWithSignedInteger(position);

		for (; position < index; position++)
		{
			Value* atPositionPlusOne = findValueWithSignedInteger(position + 1);
			*atPosition = *atPositionPlusOne;
			atPosition = atPositionPlusOne;
		}
		// 
		atPosition->invalidate();
	}	
}

template<typename ELEMENT>
void Table<ELEMENT>::reserve(sint newArraySize, sint newHashSize)
{
	if (newArraySize > arrayPartSize 
	|| newHashSize > twoTo(log2HashPartSize))
	{
		resize(newArraySize, newHashSize);
	}
}
								
template<typename ELEMENT> 
void Table<ELEMENT>::resize(sint newArraySize, sint newHashSize)
{
	sint oldArraySize = arrayPartSize;
	sint oldHashSize = log2HashPartSize;
	// save the old hash part
	Node* oldHashPart = hashPart;

	if (newArraySize > oldArraySize)  
	{	// grow the array
		resizeArray(newArraySize);
	}
	// create a new hash part with appropriate size
	resizeHash(newHashSize);  
		
	if (newArraySize < oldArraySize) 
	{	// re-insert elements from the vanishing slice into the hash table		
		for (sint index = newArraySize; index < oldArraySize; index++) 
		{
			if (arrayPart[index])
			{	
				setWithInteger(Key(index), arrayPart[index].value); 
			}
		}
		// shrink the array
		resizeArray(newArraySize);
	}
	
	sint index = twoTo(oldHashSize);
	// re-insert elements from hash part 
	if (index > 0)
	{
		do 
		{
			index--;
			Node* oldPosition = oldHashPart + index;
			
			if (oldPosition->value)
			{	
				Value* oldValueInNewPosition = setInternal(oldPosition->key);
				oldValueInNewPosition->value = oldPosition->value.value;				
			}
		} 
		while (index);
	}

	if (oldHashPart != &dummyNode)
	{
		delete[] oldHashPart;
	}
}


template<typename ELEMENT> 
void Table<ELEMENT>::resizeArray(uint newArraySize)
{	
	Value* newArrayPart = new Value[newArraySize];
	sint index = arrayPartSize < newArraySize ? arrayPartSize : newArraySize;

	if (index)
	{
		do 
		{
			index--;
			newArrayPart[index] = arrayPart[index];
		} 
		while (index);
	}

	delete[] arrayPart;
	arrayPart = newArrayPart;
	arrayPartSize = newArraySize;
}

template<typename ELEMENT> 
void Table<ELEMENT>::resizeHash(uint newHashSize)
{	// old hash part is deleted in resize()
	sint log2ofSize;
	
	if (newHashSize)
	{
		log2ofSize = logTwoCeil(newHashSize);
		assert(log2ofSize <= maxBits); // table overflow?
		newHashSize = twoTo(log2ofSize);
		hashPart = new Node[newHashSize];
		uint index(newHashSize);
		// initialize new nodes (may not be necessary)
		Node* newNode = &hashPart[index];
		
		do 
		{
			--index;
			--newNode;
			assert(newNode->next == NULL);
			assert(!newNode->key); 
			assert(!newNode->value);
		} 
		while (index);
	}
	else
	{
		hashPart = &dummyNode;
		log2ofSize = 0;
	}

	log2HashPartSize = static_cast<uchar>(log2ofSize);
	lastFree = &hashPart[newHashSize];
}


template<typename ELEMENT> 
void Table<ELEMENT>::set(const Key& key, const ELEMENT& value)
{
	Value& v = *setInternal(key);
	v.value = value;
	v.validate();
}

template<typename ELEMENT> 
typename Table<ELEMENT>::Value* Table<ELEMENT>::setInternal(const Key& key)
{
	if (Value* v = getInternal(key))
	{
		return v;
	}
	else
	{
		return newKey(key);
	}
}

template<typename ELEMENT> 
typename Table<ELEMENT>::Value* Table<ELEMENT>::setWithInteger(const Key& key, const ELEMENT& value)
{	
	Value* position = findValueWithSignedInteger(key);
	
	if (!position)
	{
		position = newKey(key);
	}
	
	position->value = value;
	return position;
}

template<typename ELEMENT> 
sint Table<ELEMENT>::twoTo(sint x)
{
	return 1 << x;
}

} // namespace containers

#endif//DEVELOP_TABLE

#endif//TABLE_H