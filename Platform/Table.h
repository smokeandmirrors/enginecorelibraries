#pragma once
#ifndef TABLE_H
#define TABLE_H

#define DEVELOP_TABLE 1
#if DEVELOP_TABLE

#include "Hashing.h"
#include "Strings.h"

/**
An implementation of an associative array, explicitly based on the
Lua table as much as possible.

<DEVELOPMENT STATUS>
Current Draft		:	0.0
Current Phase		:   DEVELOPMENT
Purpose				:	RESEARCH
Unit Tested			:	NO
Used in development	:	YES
Used in experiments :	YES
Tested in the field	:	NO
*/

namespace containers
{

const uchar logBaseTwoArray[256] = {
	0,1,2,2,3,3,3,3,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
	6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
	7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
	7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
	8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
	8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
	8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
	8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8
};

const sint maxBits(30);
const sint maxArraySize(1 << maxBits);
const sint valid(1);
const sint invalid(0);

/**
A class that represents the keys of the table
*/
class Key
{
public:
	Key(bool source)
		: original(source)
		, type(boolean)
		, code(algorithms::computeHash(source))  
		, originalKeyString("")
	{ /* empty */ }

	Key(const char* source)
		: originalKeyString(source)
		, type(string)
		, code(originalKeyString.getHash())
	{ }

	Key(const String::Immutable& source)
		: originalKeyString(source)
		, type(string)
		, code(originalKeyString.getHash())
	{ /* empty */ }

	Key(const void* source)
		: original(source) 
		, type(source ? pointer : invalid)
		, code(source ? algorithms::computeHash(source) : 0)
		, originalKeyString("")
	{/* empty */}

	Key(sint source)
		: original(source)
		, type(integer) 
		, code(algorithms::computeHash(source))
		, originalKeyString("")
	{/* empty */}

	Key(sreal source) 
		: original(source) 
		, type(real)
		, code(algorithms::computeHash(source))
		, originalKeyString("")
	{/* empty */}

private:
	template<typename ELEMENT> friend class Table;
	template<typename ELEMENT> friend class Set;

	enum Type
	{
		boolean = 1 << 0,
		integer = 1 << 1,
		invalid = 1 << 2,
		pointer = 1 << 3,
		real	= 1 << 4,
		string	= 1 << 5,		
	}; // enum Type

	union originalType
	{
		bool				keyBool;
		const void*			keyPointer;
		sint				keyInteger;
		sreal				keyReal;

		originalType(void) {}
		originalType(bool source) : keyBool(source) {}
		originalType(const void* source) : keyPointer(source) {}
		originalType(sint source) : keyInteger(source) {}		
		originalType(sreal source) : keyReal(source) {}
	} original; // union originalType
	
	Key(void)
		: type(invalid)
		, code(0)
		, originalKeyString("")
	{ /* empty */ }

	inline void beginIteration(void) 
	{ 
		type = integer; 
	}

	inline bool isValid(void) const
	{
		return (type & invalid) == 0;
	}

	inline bool operator!(void) const
	{
		return (type & invalid) != 0;
	}

	inline bool operator==(const Key& other) const
	{	/// \todo performance comparison
		/// switching on the type vs removing (superfluous in the case of non-string types) orginalKeyString compare
		return (type & other.type) 
			&& code == other.code
			&& ((!(type & string)) || originalKeyString == other.originalKeyString);
	}

	inline Key& operator=(const Key& source)
	{
		code = source.code;
		type = source.type;
		original = source.original;
		originalKeyString = source.originalKeyString;
		return *this;
	}
public:
	String::Immutable originalKeyString;
private:
	Type type;
	algorithms::hash code;
}; // Key

template<typename ELEMENT>
class Table 
{
	// friend class Iterator;
	class Value;
	struct IterationData;

public:
	Table(sint reserveArraySize=0, sint reserveHashSize=0)
		: log2HashPartSize(0)
		, arrayPartSize(0)
		, lastFree(NULL)
		, arrayPart(NULL)
	{
		dummyNode.next = NULL;
		dummyNode.value.invalidate();
		hashPart = &dummyNode;

		if (reserveArraySize || reserveHashSize)
			resize(reserveArraySize, reserveHashSize);
	}

	~Table(void)
	{
		if (hashPart != &dummyNode)
		{
			delete[] hashPart;
		}

		delete[] arrayPart;
	}
	
	ELEMENT& get(const Key& key)
	{	
		Value* position = getInternal(key);

		if (!position)
		{
			position = newKey(key);
		}

		return position->element;
	}

	const ELEMENT& get(const Key& key) const
	{	
		return get(key);
	}

	bool has(const Key& key) const
	{
		Value* v = getInternal(key);
		return v && *v;
	}

	bool has(const Key& key, ELEMENT& value) const
	{
		Value* v = getInternal(key);
		
		if (v && *v)
		{
			value = v->element;
			return true;
		}
		else
		{
			return false;
		}
	}

	void insertAtIndex(const ELEMENT& value, uint insertIndex)
	{
		sint position = static_cast<sint>(insertIndex);
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
			setWithInteger(key, v->element);
		}

		Value* v = setWithInteger(position, value);
		v->validate();
	}
	//
	void popBack(void)
	{
		sint index = findLowestValidNumericalIndexFollowedByInvalidValue();

		if (index >= 0)
		{
			Value* v = findValueWithSignedInteger(index);
			v->invalidate();
		}
	}
	// Table::
	void printHashPart(void) const
	{
		printf("HashPart:\n");

		for (uint i = 0; i < getSizeOfHashPart(); i++)
		{
			printf("%3d: ", i);
			hashPart[i].print();
			printf("\n");
		}

		printf("\n\n");
	}

	void pushBack(const ELEMENT& value)
	{
		sint index = findLowestValidNumericalIndexFollowedByInvalidValue() + 1;
		Value* v = setWithInteger(index, value);
		v->validate();
	}

	void remove(const Key& key)
	{
		if (Value* value = getInternal(key))
		{
			value->invalidate();
		}
	}

	void removeAtIndex(sint index)
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

	void reserve(sint reserveArraySize, sint reserveHashSize=0)
	{
		if (reserveArraySize > arrayPartSize 
		|| reserveHashSize > twoTo(log2HashPartSize))
		{
			resize(reserveArraySize, reserveHashSize);
		}
	}

	void set(const Key& key, const ELEMENT& value)
	{
		Value& v = *setInternal(key);
		v.element = value;
		v.validate();
	}
	
	template<typename COMPARATOR> 
	inline void sort(void)
 	{
		COMPARATOR predicate;
 		sint hi = findLowestValidNumericalIndexFollowedByInvalidValue();
 		quickSort(0, hi, predicate);		
 	}
	
	class Iterator
	{
	public:
		Iterator(Table& table, const Key& key) : data(table, key) { data.v = &table.hashPart[data.iterationIndex].value; }
		Iterator(Table& table) : data(table) { data.shouldContinue = table.next(data); }
		
		inline const Key& key(void) const {return data.k; }
		inline operator bool(void) const { return data.shouldContinue; }
		inline bool operator!(void) const { return !data.shouldContinue; }
		inline Iterator& operator ++(void) { data.shouldContinue = data.t.next(data); return *this; }
		inline Iterator operator ++(int) { Iterator temp(*this); ++*this; return temp; }
		inline ELEMENT& value(void) { return data.v->element; }
		
	private:
		friend class Table;
		
		Iterator(void);

		IterationData data;		
	}; // class Iterator

	class IteratorConst
	{
	public:
		IteratorConst(const Table& table, const Key& key) : data(const_cast<Table&>(table), key) { data.v = &table.hashPart[data.iterationIndex].value; }
		IteratorConst(const Table& table) : data(const_cast<Table&>(table)) { data.shouldContinue = table.next(data); }

		inline const Key& key(void) const {return data.k; }
		inline operator bool(void) const { return data.shouldContinue; }
		inline bool operator!(void) const { return !data.shouldContinue; }
		inline IteratorConst& operator ++(void) { data.shouldContinue = data.t.next(data); return *this; }
		inline IteratorConst operator ++(int) { IteratorConst temp(*this); ++*this; return temp; }
		inline const ELEMENT& value(void) const { return data.v->element; }

	private:
		friend class Table;

		IteratorConst(void);

		IterationData data;		
	}; // class IteratorConst	

private:
	struct IterationData
	{
		IterationData(Table& table) : k(table.getIterator()), t(table), v(NULL), iterationIndex(-1) { k.beginIteration(); }
		IterationData(Table& table, const Key& key) : k(key), t(table) { iterationIndex = table.findIndex(k); k.beginIteration(); }

		Key k;
		Table& t;
		Value* v;
		sint iterationIndex;
		bool shouldContinue;
	}; // struct IterationData

	struct Node
	{
		Node(void) : next(NULL) 
		{
			/* empty, should be completely invalid */
		}

		Node(ELEMENT v, const Key& k) : key(k), next(NULL), value(v)
		{
			/* empty */
		}
		// Table::Node::
		void print(void) const
		{
			printf("K: ");

			if (key.isValid())
			{
				printf("%10s", key.originalKeyString.c_str());
			}
			else
			{
				printf("%10s", "nil");
			}

			printf(" V: ");

			if (value)
			{
				printf("%4d", value);
			}
			else
			{
				printf(" nil");
			}

			printf(" ->");

			if (next)
			{
				next->print();
			}
			else
			{
				printf("NULL");
			}
		}
		Key key;
		Node* next;
		Value value;
	}; // Node

	class Value
	{
	public:
		Value(void) : isValid(invalid)
		{
			/* empty */
		}

		Value(ELEMENT v) : isValid(valid), value(v)
		{
			/* empty */
		}
		
		inline void invalidate(void)
		{
			isValid = invalid;
		}
		
		inline Value& operator=(const Value& original)
		{
			isValid = original.isValid;
			element = original.element;
			return *this;
		}
		
		inline bool operator!(void) const
		{
			return isValid != valid;
		}
		
		inline operator sint(void) const
		{
			return isValid;
		}
		
		inline void validate(void)
		{
			isValid = valid;
		}
		
		ELEMENT element;
	
	private:
		sint isValid;
	}; // Value

	// static int computesizes (int nums[], int *narray)
	static inline bool calculateArrayIndex(const Key& key, sint& arrayIndex)
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
	
	static inline sint calculateNewArraySize(sint nums[], sint& numArrays)
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

	// static int countint (const TValue *key, int *nums)
	static inline sint countInt(const Key& key, sint* outputNumbers)
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

	static inline Node createDummyNode(void)
	{
		Node node;
		node.next = NULL;
		node.value.invalidate();
		return node;
	}

	static inline sint logTwoCeil(uint x)
	{
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

	static inline sint twoTo(sint x)
	{
		return 1 << x;
	}

	// auxiliary search function (which is duplicate code in ltable.c)
	inline sint binarySearch(uint high, uint low) const
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
	// static int numusearray (const Table *t, int *nums)
	inline sint countKeysInArray(sint* perSlotOutput) const
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
	// static int numusehash (const Table *t, int *nums, int *pnasize)
	inline sint countKeysInHash(sint* perSlotOutput, sint& keysInArray) const
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
	// const TValue *luaH_get (Table *t, const TValue *key);
	inline Value* getInternal(const Key& key) const
	{
		switch (key.type)
		{
		case Key::invalid:
			return NULL;

		case Key::integer:
			return findValueWithSignedInteger(key);

		case Key::string:
			return findValueWithString(key);

		default:
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
		} // default
		} // switch (key.type)

		return NULL;
	} 
	// static int findindex (lua_State *L, Table *t, StkId key)
	inline sint findIndex(Key& iter) const
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
		}
		assert(false);/*else invalid key, assert*/
		return -2;
	}
	// LUAI_FUNC int luaH_getn (Table *t);
	inline sint findLowestValidNumericalIndexFollowedByInvalidValue(void) const
	{
		sint high = arrayPartSize;

		if (arrayPartSize > 0 && !arrayPart[high - 1])
		{	// there is a boundary in the array part, binary search for it
			return binarySearch(high, 0) - 1;
		}
		else if (hashPart == &dummyNode)
		{
			return static_cast<sint>(high) - 1;
		}
		else
		{	// unbound search
			sint low = high;
			high++;

			while (findValueWithSignedInteger(high))
			{	// find high and low such that high is present and low is not
				low = high;
				high *= 2;

				if (high > (INT_MAX - 2))
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
	// const TValue *luaH_getint (Table *t, int key);
	inline Value* findValueWithSignedInteger(const Key& key) const
	{	
		sint index = key.original.keyInteger;

		if (index >= 0 
		&& index < static_cast<sint>(arrayPartSize))
		{
			return &arrayPart[index];
		}
		
		Node* n = &hashPart[hashMod(key.code)];

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
	// const TValue *luaH_getstr (Table *t, TString *key);	
	inline Value* findValueWithString(const Key& key) const
	{	
		uint index = hashModPowerOf2(key.code);
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
	// static Node *getfreepos (Table *t)
	inline Node* getFreePosition(void)
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

	inline Key getIterator(void) const
	{
		return Key();
	}
	// #define hashboolean(t,p)        hashpow2(t, p)
	inline Node* getPositionHashMod(const Key& key) const
	{
		uint index = hashMod(key.code);
		return &hashPart[index];
	}
	// #define hashpointer(t,p)	hashmod(t, IntPoint(p))
	inline Node* getPositionHashModPowerOf2(const Key& key) const
	{
		uint index = hashModPowerOf2(key.code);
		return &hashPart[index];
	}
	// static Node *mainposition (const Table *t, const TValue *key)
	inline Node* getMainPosition(const Key& key) const
	{
		assert(key.isValid()); 
		
		switch (key.type)
		{
		case Key::boolean:
		case Key::string:
			return getPositionHashModPowerOf2(key);

		default:
			return getPositionHashMod(key); 
		} // switch (key.type)
	}
	// #define sizenode(t)	(twoto((t)->lsizenode))
	inline uint getSizeOfHashPart(void) const
	{
		return twoTo(log2HashPartSize);
	}
	// #define hashmod(t,n)	(gnode(t, ((n) % ((sizenode(t)-1)|1))))
	inline uint hashMod(const algorithms::hash key) const
	{	// hashmod
		return key % ((getSizeOfHashPart() - 1) | 1);
	}
	// #define hashpow2(t,n)      (gnode(t, lmod((n), sizenode(t))))
	inline uint hashModPowerOf2(const algorithms::hash key) const
	{	
		return key & (getSizeOfHashPart() - 1);
	}

	inline bool isMainPositionIsTaken(Node* mainPosition) const
	{
		return mainPosition->value || (mainPosition == &dummyNode);
	}
	
	inline bool next(IterationData& iter) const
	{
		++iter.iterationIndex;
		assert(iter.iterationIndex >= 0);
		sint index = iter.iterationIndex;

		for (; index < static_cast<sint>(arrayPartSize); index++)
		{
			if (arrayPart[index])
			{
				iter.v = &arrayPart[index];
				iter.k.original.keyInteger = index;
				return true;
			}
		}

		sint sizeHashPart = static_cast<sint>(getSizeOfHashPart());

		for (index -= arrayPartSize; index < sizeHashPart; index++)
		{
			if (hashPart[index].value)
			{
				iter.v = &hashPart[index].value;
				iter.k = hashPart[index].key;
				iter.iterationIndex = index + arrayPartSize;
				return true;
			}
		}

		return false;
	}

	// LUAI_FUNC int luaH_next (lua_State *L, Table *t, StkId key);
// 	inline bool next(Key& iter, Value*& value) const
// 	{
// 		sint index = findIndex(iter) + 1;
// 
// 		for (; index < static_cast<sint>(arrayPartSize); index++)
// 		{
// 			if (arrayPart[index])
// 			{
// 				value = &arrayPart[index];
// 				iter.original.keyInteger = index;
// 				return true;
// 			}
// 		}
// 
// 		sint sizeHashPart = static_cast<sint>(getSizeOfHashPart());
// 
// 		for (index -= arrayPartSize; index < sizeHashPart; index++)
// 		{
// 			if (hashPart[index].value)
// 			{
// 				value = &hashPart[index].value;
// 				iter = hashPart[index].key;
// 				return true;
// 			}
// 		}
// 
// 		return false;
// 	}

	// TValue *luaH_newkey (lua_State *L, Table *t, const TValue *key)
	inline Value* newKey(const Key& key)
	{	/*
		** inserts a new key into a hash table; first, check whether key's main 
		** position is free. If not, check whether colliding node is in its main 
		** position or not: if it is not, move colliding node to an empty place and 
		** put new key in its main position; otherwise (colliding node is in its main 
		** position), new key goes to an empty position. 
		*/
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
				other->next = freePosition;
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
	// static void rehash (lua_State *L, Table *t, const TValue *ek)
	inline void rehash(const Key& key)
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
	// void luaH_resize (lua_State *L, Table *t, int newArraySize, int nhsize);
	inline void resize(sint newArraySize, sint newHashSize)
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
					setWithInteger(Key(index), arrayPart[index].element); 
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
					*oldValueInNewPosition = oldPosition->value;
				}
			} 
			while (index);
		}

		if (oldHashPart != &dummyNode)
		{
			delete[] oldHashPart;
		}
	}
	// void luaH_resizearray (lua_State *L, Table *t, int newArraySize);
	inline void resizeArray(uint newArraySize)
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
	// static void setnodevector (lua_State *L, Table *t, int size)
	inline void resizeHash(uint newHashSize)
	{	// old hash part is deleted in resize()
		sint log2ofSize;

		if (newHashSize)
		{
			log2ofSize = logTwoCeil(newHashSize);
			assert(log2ofSize <= maxBits); // table overflow
			newHashSize = twoTo(log2ofSize);
			hashPart = new Node[newHashSize];// old hash part is deleted in resize()
#if DEBUG
			uint index(newHashSize);
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
#endif//DEBUG
		}
		else
		{
			hashPart = &dummyNode;// old hash part is deleted in resize()
			log2ofSize = 0;
		}

		log2HashPartSize = static_cast<uchar>(log2ofSize);
		lastFree = &hashPart[newHashSize];
	}
	// TValue *luaH_set (lua_State *L, Table *t, const TValue *key);
	inline Value* setInternal(const Key& key)
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
	// void luaH_setint (lua_State *L, Table *t, int key, TValue *value);
	inline Value* setWithInteger(const Key& key, const ELEMENT& value)
	{	// very good optimization candidate? 
		Value* position = findValueWithSignedInteger(key);

		if (!position)
		{
			position = newKey(key);
		}

		position->element = value;
		return position;
	}
	// auxsort
	template<typename COMPARATOR> inline void quickSort(const sint left, const sint right, const COMPARATOR& predicate)
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
			
			FOREVER
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
				
				std::swap(get(i), get(j));
				
				if (get(i) == v)
				{
					++p;
					std::swap(get(p), get(i));
				}

				if (v == get(j))
				{
					--q;
					std::swap(get(j), get(q));
				}
			}

			std::swap(get(i), get(right));
			j = i - 1;
			i = i + 1;
			
			for (sint k = left; k < p; k++, j--)
			{
				std::swap(get(k), get(j));
			}

			for (sint k = right - 1; k > q; k--, i++)
			{
				std::swap(get(i), get(k));
			}

			quickSort(left, j, predicate);
			quickSort(i, right, predicate);
		} // if (left < right)
	}
	
	uchar log2HashPartSize;	// lu_byte lsizenode;
	uint arrayPartSize; 	// int sizearray;
	Node* lastFree;			// Node *lastfree;
	Node* hashPart;			// Node *node;
	Value* arrayPart;		// TValue *array;
	Node dummyNode;
}; // Table

template<typename ELEMENT>
class Set 
{
	// friend class Iterator;
	class Value;
	struct IterationData;

public:
	Set(sint reserveHashSize=0)
		: log2HashPartSize(0)
		, lastFree(NULL)
	{
		dummyNode.next = NULL;
		dummyNode.value.invalidate();
		hashPart = &dummyNode;

		if (reserveHashSize)
			resize(reserveHashSize);

		numKeysUsed = 0;
	}

	~Set(void)
	{
		if (hashPart != &dummyNode)
		{
			delete[] hashPart;
		}
	}
	
	ELEMENT& get(const Key& key)
	{	
		Value* position = getInternal(key);

		if (!position)
		{
			position = newKey(key);
		}

		return position->element;
	}

	const ELEMENT& get(const Key& key) const
	{	
		return const_cast<Set<ELEMENT>*>(this)->get(key);
	}

	uint getSize(void) const
	{
		return numKeysUsed;
	}

	bool has(const Key& key) const
	{
		Value* v = getInternal(key);
		return v && *v;
	}

	bool isEmpty(void) const
	{
		return numKeysUsed == 0;
	}

	// Table::
	void printHashPart(void) const
	{
		printf("HashPart:\n");

		for (uint i = 0; i < getSizeOfHashPart(); i++)
		{
			printf("%3d: ", i);
			hashPart[i].print();
			printf("\n");
		}

		printf("\n\n");
	}

	void pushBack(const ELEMENT& value)
	{
		sint index = findLowestValidNumericalIndexFollowedByInvalidValue() + 1;
		Value* v = setWithInteger(index, value);
		v->validate();
	}

	void remove(const Key& key)
	{
		if (Value* value = getInternal(key))
		{	
			value->invalidate();
			--numKeysUsed;
			
			if ((numKeysUsed * 2) < getSizeOfHashPart())
			{
				resize(numKeysUsed);
			}
		}
	}

	void reserve(sint reserveHashSize=0)
	{
		if (reserveHashSize > twoTo(log2HashPartSize))
		{
			resize(reserveHashSize);
		}
	}

	void set(const Key& key, const ELEMENT& value)
	{
		Value& v = *setInternal(key);
		v.element = value;
		v.validate();
		++numKeysUsed;
	}

	void shrink(void)
	{
		resize(numKeysUsed);
	}
		
	class Iterator
	{
	public:
		Iterator(Set& table, const Key& key) : data(table, key) { data.v = &table.hashPart[data.iterationIndex].value; }
		Iterator(Set& table) : data(table) { data.shouldContinue = table.next(data); }
		
		inline const Key& key(void) const {return data.k; }
		inline operator bool(void) const { return data.shouldContinue; }
		inline bool operator!(void) const { return !data.shouldContinue; }
		inline Iterator& operator ++(void) { data.shouldContinue = data.t.next(data); return *this; }
		inline Iterator operator ++(int) { Iterator temp(*this); ++*this; return temp; }
		inline ELEMENT& value(void) { return data.v->element; }
		
	private:
		friend class Set;
		
		Iterator(void);

		IterationData data;		
	}; // class Iterator

	class IteratorConst
	{
	public:
		IteratorConst(const Set& table, const Key& key) : data(const_cast<Set&>(table), key) { data.v = &table.hashPart[data.iterationIndex].value; }
		IteratorConst(const Set& table) : data(const_cast<Set&>(table)) { data.shouldContinue = table.next(data); }

		inline const Key& key(void) const {return data.k; }
		inline operator bool(void) const { return data.shouldContinue; }
		inline bool operator!(void) const { return !data.shouldContinue; }
		inline IteratorConst& operator ++(void) { data.shouldContinue = data.t.next(data); return *this; }
		inline IteratorConst operator ++(int) { IteratorConst temp(*this); ++*this; return temp; }
		inline const ELEMENT& value(void) const { return data.v->element; }

	private:
		friend class Set;

		IteratorConst(void);

		IterationData data;		
	}; // class IteratorConst	

private:
	struct IterationData
	{
		IterationData(Set& table) : k(table.getIterator()), t(table), v(NULL), iterationIndex(-1) { k.beginIteration(); }
		IterationData(Set& table, const Key& key) : k(key), t(table) { iterationIndex = table.findIndex(k); k.beginIteration(); }

		Key k;
		Set& t;
		Value* v;
		sint iterationIndex;
		bool shouldContinue;
	}; // struct IterationData

	struct Node
	{
		Node(void) : next(NULL) 
		{
			/* empty, should be completely invalid */
		}

		Node(ELEMENT v, const Key& k) : key(k), next(NULL), value(v)
		{
			/* empty */
		}
		// Table::Node::
		void print(void) const
		{
			printf("K: ");

			if (key.isValid())
			{
				printf("%10s", key.originalKeyString.c_str());
			}
			else
			{
				printf("%10s", "nil");
			}

			printf(" V: ");

			if (value)
			{
				printf("%4d", value);
			}
			else
			{
				printf(" nil");
			}

			printf(" ->");

			if (next)
			{
				next->print();
			}
			else
			{
				printf("NULL");
			}
		}
		Key key;
		Node* next;
		Value value;
	}; // Node

	class Value
	{
	public:
		Value(void) : isValid(invalid)
		{
			/* empty */
		}

		Value(ELEMENT v) : isValid(valid), value(v)
		{
			/* empty */
		}
		
		inline void invalidate(void)
		{
			isValid = invalid;
		}
		
		inline Value& operator=(const Value& original)
		{
			isValid = original.isValid;
			element = original.element;
			return *this;
		}
		
		inline bool operator!(void) const
		{
			return isValid != valid;
		}
		
		inline operator sint(void) const
		{
			return isValid;
		}
		
		inline void validate(void)
		{
			isValid = valid;
		}
		
		ELEMENT element;
	
	private:
		sint isValid;
	}; // Value

	
	static inline Node createDummyNode(void)
	{
		Node node;
		node.next = NULL;
		node.value.invalidate();
		return node;
	}

	static inline sint logTwoCeil(uint x)
	{
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

	static inline sint twoTo(sint x)
	{
		return 1 << x;
	}

	// static int numusehash (const Table *t, int *nums, int *pnasize)
	inline sint countKeysInHash(void) const
	{
		sint totaluse = 0;  /* total number of elements */
		sint i = getSizeOfHashPart();

		while (i--) 
		{
			Node *n = &(hashPart[i]);
			totaluse += n->value;
		}

		return totaluse;
	}
	// const TValue *luaH_get (Table *t, const TValue *key);
	inline Value* getInternal(const Key& key) const
	{
		switch (key.type)
		{
		case Key::invalid:
			return NULL;

		case Key::integer:
			return findValueWithSignedInteger(key);

		case Key::string:
			return findValueWithString(key);

		default:
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
		} // default
		} // switch (key.type)

		return NULL;
	} 
	// static int findindex (lua_State *L, Table *t, StkId key)
	inline sint findIndex(Key& iter) const
	{
		Node* n = getMainPosition(iter);

		do 
		{
			if (n->key == iter)
			{
				return static_cast<sint>(n - hashPart);
			}
			else
			{
				n = n->next;
			}
		} 
		while (n);

		assert(false);/*else invalid key, assert*/
		return -2;		
	}
	// const TValue *luaH_getint (Table *t, int key);
	inline Value* findValueWithSignedInteger(const Key& key) const
	{	
		Node* n = &hashPart[hashMod(key.code)];

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
	// const TValue *luaH_getstr (Table *t, TString *key);	
	inline Value* findValueWithString(const Key& key) const
	{	
		uint index = hashModPowerOf2(key.code);
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
	// static Node *getfreepos (Table *t)
	inline Node* getFreePosition(void)
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

	inline Key getIterator(void) const
	{
		return Key();
	}
	// #define hashboolean(t,p)        hashpow2(t, p)
	inline Node* getPositionHashMod(const Key& key) const
	{
		uint index = hashMod(key.code);
		return &hashPart[index];
	}
	// #define hashpointer(t,p)	hashmod(t, IntPoint(p))
	inline Node* getPositionHashModPowerOf2(const Key& key) const
	{
		uint index = hashModPowerOf2(key.code);
		return &hashPart[index];
	}
	// static Node *mainposition (const Table *t, const TValue *key)
	inline Node* getMainPosition(const Key& key) const
	{
		assert(key.isValid()); 
		
		switch (key.type)
		{
		case Key::boolean:
		case Key::string:
			return getPositionHashModPowerOf2(key);

		default:
			return getPositionHashMod(key); 
		} // switch (key.type)
	}
	// #define sizenode(t)	(twoto((t)->lsizenode))
	inline uint getSizeOfHashPart(void) const
	{
		return twoTo(log2HashPartSize);
	}
	// #define hashmod(t,n)	(gnode(t, ((n) % ((sizenode(t)-1)|1))))
	inline uint hashMod(const algorithms::hash key) const
	{	// hashmod
		return key % ((getSizeOfHashPart() - 1) | 1);
	}
	// #define hashpow2(t,n)      (gnode(t, lmod((n), sizenode(t))))
	inline uint hashModPowerOf2(const algorithms::hash key) const
	{	
		return key & (getSizeOfHashPart() - 1);
	}

	inline bool isMainPositionIsTaken(Node* mainPosition) const
	{
		return mainPosition->value || (mainPosition == &dummyNode);
	}
	
	inline bool next(IterationData& iter) const
	{
		++iter.iterationIndex;
		assert(iter.iterationIndex >= 0);
		sint sizeHashPart = static_cast<sint>(getSizeOfHashPart());

		for (sint index = iter.iterationIndex; index < sizeHashPart; index++)
		{
			if (hashPart[index].value)
			{
				iter.v = &hashPart[index].value;
				iter.k = hashPart[index].key;
				iter.iterationIndex = index;
				return true;
			}
		}

		return false;
	}

	// TValue *luaH_newkey (lua_State *L, Table *t, const TValue *key)
	inline Value* newKey(const Key& key)
	{	/*
		** inserts a new key into a hash table; first, check whether key's main 
		** position is free. If not, check whether colliding node is in its main 
		** position or not: if it is not, move colliding node to an empty place and 
		** put new key in its main position; otherwise (colliding node is in its main 
		** position), new key goes to an empty position. 
		*/
		assert(key.isValid()); 
		Node* mainPosition = getMainPosition(key);

		if (isMainPositionIsTaken(mainPosition))
		{
			Node* freePosition = getFreePosition();

			if (!freePosition)
			{
				rehash();
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
				other->next = freePosition;
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
	// static void rehash (lua_State *L, Table *t, const TValue *ek)
	inline void rehash(void)
	{
		sint totaluse = countKeysInHash() + 1; 
		/* resize the table to new computed sizes */
		resize(totaluse);	
	}
	// void luaH_resize (lua_State *L, Table *t, int newArraySize, int nhsize);
	inline void resize(sint newHashSize)
	{
		sint oldHashSize = log2HashPartSize;
		// save the old hash part
		Node* oldHashPart = hashPart;

		// create a new hash part with appropriate size
		resizeHash(newHashSize);  

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
					*oldValueInNewPosition = oldPosition->value;
				}
			} 
			while (index);
		}

		if (oldHashPart != &dummyNode)
		{
			delete[] oldHashPart;
		}
	}
	
	// static void setnodevector (lua_State *L, Table *t, int size)
	inline void resizeHash(uint newHashSize)
	{	// old hash part is deleted in resize()
		sint log2ofSize;

		if (newHashSize)
		{
			log2ofSize = logTwoCeil(newHashSize);
			assert(log2ofSize <= maxBits); // table overflow
			newHashSize = twoTo(log2ofSize);
			hashPart = new Node[newHashSize];// old hash part is deleted in resize()
#if DEBUG
			uint index(newHashSize);
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
#endif//DEBUG
		}
		else
		{
			hashPart = &dummyNode;// old hash part is deleted in resize()
			log2ofSize = 0;
		}

		log2HashPartSize = static_cast<uchar>(log2ofSize);
		lastFree = &hashPart[newHashSize];
	}
	// TValue *luaH_set (lua_State *L, Table *t, const TValue *key);
	inline Value* setInternal(const Key& key)
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
	// void luaH_setint (lua_State *L, Table *t, int key, TValue *value);
	inline Value* setWithInteger(const Key& key, const ELEMENT& value)
	{	// very good optimization candidate? 
		Value* position = findValueWithSignedInteger(key);

		if (!position)
		{
			position = newKey(key);
		}

		position->element = value;
		return position;
	}
	
	uint numKeysUsed;
	uchar log2HashPartSize;	// lu_byte lsizenode;
	Node* lastFree;			// Node *lastfree;
	Node* hashPart;			// Node *node;
	Node dummyNode;
}; // Table

} // namespace containers

#endif//DEVELOP_TABLE

#endif//TABLE_H