#pragma once
#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include "math.h"
#include "float.h"

/**
An implementation of associative arrayPart based on the
Lua table.
*/

namespace algorithms
{

typedef uint hash;

inline hash 
	computeHash(const bool key);

inline hash 
	computeHash(const schar* string);

inline hash 
	computeHash(const schar* string, size_t length);

template<typename T> inline hash
	computeHash(const T* pointer);

inline hash
	computeHash(const void* pointer);

inline hash
	computeHash(sint number);

inline hash
	computeHash(sreal number);

} // namespace algorithms

namespace containers
{

static const sint maxBits(30);
static const sint maxArraySize( 1 << maxBits);
static const sint valid(1);
static const sint invalid(0);

template<typename ELEMENT>
class Table 
{
public:
	struct Key
	{
		enum Type
		{
			boolean = 1 << 0,
			integer = 1 << 1,
			invalid = 1 << 2,
			pointer = 1 << 3,
			real	= 1 << 4,
			string	= 1 << 5,		
		}; // enum Type

		inline static bool 
			isValid(const Key& h)
		{
			return h.type != Key::invalid;
		}

		Key(void)
		: type(Key::invalid)
		, key(0)
		{ /* empty */ }
		
		Key(bool original)
		: originalBool(original)
		, type(Key::boolean)
		, key(algorithms::computeHash(original))  
		{ /* empty */ }

		Key(const schar* original)
		: originalString(original)
		, type(original ? Key::string : Key::invalid)
		, key(original ? algorithms::computeHash(original, strlen(original)) : 0)
		{ /* empty */ }

		Key(const schar* original, size_t length)
		: originalString(original) 
		, type(original ? Key::string : Key::invalid)
		, key(original ? algorithms::computeHash(original, length) : 0)
		{/* empty */}

		Key(const void* original)
		: originalPointer(original) 
		, type(original ? Key::pointer : Key::invalid)
		, key(original ? algorithms::computeHash(original) : 0)
		{/* empty */}

		Key(sint original)
		: originalInteger(original)
		, type(Key::integer) 
		, key(algorithms::computeHash(original))
		{/* empty */}

		Key(sreal original) 
		: originalReal(original) 
		, type(Key::real)
		, key(algorithms::computeHash(original))
		{/* empty */}

		
		bool operator!(void) const
		{
			return type & Key::invalid;
		}

		bool operator==(const Key& other) const
		{
			return (type & other.type) && key == other.key;
		}

		Key& operator=(const Key& original)
		{
			algorithms::hash& mutableKey = const_cast<algorithms::hash&>(key);
			mutableKey = original.key;
			Type& mutableType = const_cast<Type&>(type);
			mutableType = original.type;
			return *this;
		}

		union
		{
			const schar*	originalString;
			bool			originalBool;
			const void*		originalPointer;
			sint			originalInteger;
			sreal			originalReal;
		};

		const Type 
			type;

		const algorithms::hash 
			key;
	}; // Key

private:
	struct Value
	{
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

		Value& operator=(const Value& original)
		{
			isValid = original.isValid;
			value = original.value;
			return *this;
		}	

		sint 
			isValid;

		ELEMENT 
			value;
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
		operator[](const Key& key);
	
	const ELEMENT& 
		operator[](const Key& key) const;
	
	bool 
		has(const Key& key) const;
	// TValue *luaH_set (lua_State *L, Table *t, const TValue *key);
	inline Value*
		set(const Key& key);
	
private:
	/// \todo will template versions of these be unnecessarily generated? 
	// static int arrayindex (const TValue *key)
	static inline sint
		calculateArrayIndex(const Key& key);
	// static int computesizes (int nums[], int *narray)
	static inline sint
		calculateNewArraySize(sint nums[], sint* numArrays);
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
	// static int numusearray (const Table *t, int *nums)
	inline sint 
		countKeysInArray(sint* perSlotOutput) const;
	// static int numusehash (const Table *t, int *nums, int *pnasize)
	inline sint 
		countKeysInHash(sint* perSlotOutput, sint* keysInArray) const;
	// const TValue *luaH_get (Table *t, const TValue *key);
	inline Value*
		get(const Key& key) const;
	// const TValue *luaH_getint (Table *t, int key);
	inline Value*
		findValueWithSignedInteger(const Key& key) const;
	// const TValue *luaH_getstr (Table *t, TString *key);	
	inline Value*
		findValueWithString(const Key& key) const;
	// static Node *getfreepos (Table *t)
	inline Node*
		getFreePosition(void);
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
		hashMod(const uint key) const;
	// #define hashpow2(t,n)      (gnode(t, lmod((n), sizenode(t))))
	inline uint
		hashModPowerOf2(const uint powerOf2) const;
	inline bool
		isMainPositionIsTaken(Node*) const;
	// TValue *luaH_newkey (lua_State *L, Table *t, const TValue *key)
	inline Value*
		newKey(const Key& key);
	// static void rehash (lua_State *L, Table *t, const TValue *ek)
	inline void
		rehash(const Key& key);
	// void luaH_resize (lua_State *L, Table *t, int nasize, int nhsize);
	inline void
		resize(sint arraySize, sint hashSize);
	// void luaH_resizearray (lua_State *L, Table *t, int nasize);
	inline void
		resizeArray(uint newArraySize);
	// static void setnodevector (lua_State *L, Table *t, int size)
	inline void
		resizeHash(uint newHashSize);
	// void luaH_setint (lua_State *L, Table *t, int key, TValue *value);
	inline void /* very good optimization candidate? */
		setWithInteger(const Key& key, ELEMENT& value);
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

} // namespace containers

namespace algorithms
{

inline algorithms::hash algorithms::computeHash(bool key)
{
	return static_cast<algorithms::hash>(key);
}

inline algorithms::hash algorithms::computeHash(const schar* string)
{	
	return computeHash(string, strlen(string));
}

inline algorithms::hash algorithms::computeHash(const schar* string, size_t length)
{	// modified from lstring.c
	algorithms::hash h = static_cast<algorithms::hash>(length);
	algorithms::hash step = static_cast<hash>((length >> 5) + 1);

	for ( ; length >= step; length -= step) 
	{
		h = h ^ ((h << 5) + (h >> 2) + static_cast<algorithms::hash>(string[length - 1]));
	}

	return h;
}

inline algorithms::hash algorithms::computeHash(const void* pointer)
{
	return static_cast<algorithms::hash>(reinterpret_cast<ulong>(pointer));
}

inline hash computeHash(sint number)
{
	return computeHash(static_cast<sreal>(number));
}

inline hash computeHash(sreal number)
{
/** if the compiler can handle it, \see llimits.h
#define luai_hashnum(i,n)  \
	{ volatile union luai_Cast u; u.l_d = (n) + 1.0;   avoid -0  \
	(i) = u.l_p[0]; (i) += u.l_p[1]; }   add double bits for his hash */
	
	/// casting from float to sint is reportedly slow
	/// investigate faster options.  \see lua_number2int
	
	// begin luai_hashnum(i, n)
	sint exponent; 
	sint key = static_cast<sint>(frexp(number, &exponent) * static_cast<sreal>(INT_MAX - DBL_MAX_EXP));
	key += exponent; 
	// end luai_hashnum(i, n)
	
	if (key < 0) 
	{	// use unsigned to avoid overflows 
		if (static_cast<unsigned int>(key) == 0u - key)  
		{	 // handle INT_MIN 
			 key = 0; 
		}
		else
		{	// must be a positive value 
			key = -key;  
		}
	}	

	return static_cast<hash>(key);
}

} // namespace algorithms

namespace containers
{
template<typename ELEMENT> 
typename Table<ELEMENT>::Node Table<ELEMENT>::dummyNode(Table<ELEMENT>::createDummyNode());

// LUAI_FUNC Table *luaH_new (lua_State *L, int narray, int lnhash);
template<typename ELEMENT> 
Table<ELEMENT>::Table(sint /*reserveArraySize*/, sint /*reserveHashSize*/)
: log2HashPartSize(0)
, arrayPartSize(0)
, hashPart(&dummyNode)
, lastFree(NULL)
, arrayPart(NULL)
{
	// resize(reserveArraySize, reserveHashSize);
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
sint Table<ELEMENT>::calculateArrayIndex(const Key& key)
{
	if (key.key == Key::integer
	&& key.key >= 0) 
	{	// check if is integer value, and if the key is the same value as the number
		return key.key;
	}
	else
	{
		return -1;
	}
}

template<typename ELEMENT>
uint Table<ELEMENT>::hashMod(const uint key) const
{	// hashmod
	return key % ((getSizeOfHashPart() - 1) | 1);
}

template<typename ELEMENT>
uint Table<ELEMENT>::hashModPowerOf2(const uint powerOf2) const
{	
	const uint sizeHashPart = getSizeOfHashPart();
	assert((sizeHashPart & (sizeHashPart - 1)) == 0);
	return powerOf2 & (sizeHashPart - 1);
}

template<typename ELEMENT>
sint Table<ELEMENT>::calculateNewArraySize(sint nums[], sint* numArrays)
{
	sint i;
	sint twotoi;  /* 2^i */
	sint a = 0;  /* number of elements smaller than 2^i */
	sint na = 0;  /* number of elements to go to array part */
	sint n = 0;  /* optimal size for array part */
	for (i = 0, twotoi = 1; twotoi/2 < *numArrays; i++, twotoi *= 2) 
	{
		if (nums[i] > 0) 
		{
			a += nums[i];
			
			if (a > twotoi/2) 
			{  /* more than half elements present? */
				n = twotoi;  /* optimal size (till now) */
				na = a;  /* all elements smaller than n will go to array part */
			}
		}

		if (a == *numArrays) 
			break;  /* all elements already counted */
	}
	*numArrays = n;
	assert(*numArrays/2 <= na && na <= *numArrays);
	return na;
}

template<typename ELEMENT>
sint Table<ELEMENT>::countInt(const Key& key, sint* outputNumbers)
{
	sint arrayIndex = calculateArrayIndex(key);
	
	if (arrayIndex > 0 && arrayIndex <= maxArraySize)
	{
		outputNumbers[logTwoCeil(arrayIndex)]++;
		return 1;
	}
	else
	{
		return 0;
	}
}

template<typename ELEMENT> 
sint Table<ELEMENT>::countKeysInArray(sint* perSlotOutput) const
{	
	sint logBase2;
	sint twoToLogBase2;  /* 2 ^logBase2 */
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
		
		{	// count elements in range (2^(logBase2-1), 2^logBase2]
			sint n = index - 1;

			for (; n < upperLimit; n++) 
			{	
				counter += arrayPart[n].isValid;				
			}

			index = n + 1;
		}
		
		perSlotOutput[logBase2] += counter;
		total += counter;
	}

	return total;
}

template<typename ELEMENT>
sint Table<ELEMENT>::countKeysInHash(sint* perSlotOutput, sint* keysInArray) const
{
	sint totaluse = 0;  /* total number of elements */
	sint summationOfNums = 0;  /* summation of `nums' */
	sint i = getSizeOfHashPart();
	
	while (i--) 
	{
		Node *n = &(hashPart[i]);
		
		if (!n->value.isValid) 
		{
			summationOfNums += countInt(n->key, perSlotOutput);
			totaluse++;
		}
	}
	
	*keysInArray += summationOfNums;
	return totaluse;
}

template<typename ELEMENT> 
typename Table<ELEMENT>::Node Table<ELEMENT>::createDummyNode(void)
{
	Node node;
	node.next = NULL;
	node.value.isValid = 0;
	return node;
}

template<typename ELEMENT> 
typename Table<ELEMENT>::Value* Table<ELEMENT>::findValueWithSignedInteger(const Key& key) const
{	
	sint index = key.originalInteger;
	
	if (index > 0 
	&& index < static_cast<sint>(arrayPartSize))
	{
		return &arrayPart[index];
	}
	// how this is never NULL, I don't know
	Node* n = &hashPart[hashMod(key.key)];

	do 
	{
		if (n->key.type & Key::integer
			&& n->key.originalInteger == key.originalInteger)
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
	// how this is never NULL, I don't know
	Node* n = &hashPart[index];

	do 
	{
		if (n->key.type & Key::string
		&& String::isEqual(n->key.originalString, key.originalString))
		{
			return &n->value;
		}

		n = n->next;
	} 
	while (n);

	return NULL;
}

template<typename ELEMENT> 
typename Table<ELEMENT>::Value* Table<ELEMENT>::get(const Key& key) const
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
} // const Table<ELEMENT>::Value* Table<ELEMENT>::get(const Key& key) const

template<typename ELEMENT> 
typename Table<ELEMENT>::Node* Table<ELEMENT>::getFreePosition(void) 
{
	while (lastFree > hashPart)
	{
		lastFree--;

		if (!lastFree->value.isValid)
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
bool Table<ELEMENT>::isMainPositionIsTaken(Node* mainPosition) const
{
	return mainPosition->value.isValid || (mainPosition == &dummyNode);
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
	x--;
	
	while (x >= 256) 
	{ 
		l += 8; 
		x >>= 8; 
	}
	
	return l + logBaseTwoArray[x];
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
	assert(Key::isValid(key));
	Node* mainPosition = getMainPosition(key);
		
	if (isMainPositionIsTaken(mainPosition))
	{
		Node* freePosition = getFreePosition();

		if (!freePosition)
		{
			rehash(key);
			return set(key);
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
			mainPosition->value.isValid = invalid;
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
	assert(!mainPosition->value.isValid);
	return &(mainPosition->value);
}

/* LUAI_FUNC const TValue *luaH_get (Table *t, const TValue *key);
LUAI_FUNC TValue *luaH_set (lua_State *L, Table *t, const TValue *key);	*/
template<typename ELEMENT> 
typename ELEMENT& Table<ELEMENT>::operator[](const Key& key)
{	
	Value* position = get(key);
	
	if (!position)
	{
		position = newKey(key);
	}

	return position->value;
}
/* LUAI_FUNC const TValue *luaH_get (Table *t, const TValue *key);
LUAI_FUNC TValue *luaH_set (lua_State *L, Table *t, const TValue *key);	*/
template<typename ELEMENT> 
const ELEMENT& Table<ELEMENT>::operator[](const Key& key) const
{	
	Value* position = get(key);

	if (!position)
	{
		position = newKey(key);;
	}

	return position->value;
}

template<typename ELEMENT> 
void Table<ELEMENT>::rehash(const Key& key)
{
	sint nasize, na;
	sint nums[maxBits+1];  /* nums[i] = number of keys with, 2^(i-1) keys 2^i */
	sint i;
	sint totaluse;
	for (i=0; i<=maxBits; i++) nums[i] = 0;  /* reset counts */
	nasize = countKeysInArray(nums);  /* count keys in arrayPart part */
	totaluse = nasize;  /* all those keys are integer keys */
	totaluse += countKeysInHash(nums, &nasize);  /* count keys in hash part */
	/* count extra key */
	nasize += countInt(key, nums);
	totaluse++;
	/* compute new size for arrayPart part */
	na = calculateNewArraySize(nums, &nasize);
	/* resize the table to new computed sizes */
	resize(nasize, totaluse - na);	
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
	{ 
		arrayPartSize = newArraySize;
		// re-insert elements from the vanishing slice		
		for (sint index = newArraySize; index < oldArraySize; index++) 
		{
			if (arrayPart[index].isValid)
			{	
				setWithInteger(index + 1, arrayPart[index].value); 
			}
		}
		// shrink the array
		resizeArray(newArraySize);
	}
	
	sint index = twoTo(oldHashSize) - 1;
	// re-insert elements from hash part 
	if (index > 0)
	{
		do 
		{
			index--;
			Node* oldPosition = oldHashPart + index;
			
			if (oldPosition->value.isValid)
			{	
				Value* oldValueInNewPosition = set(oldPosition->key);
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
	
	if (newArraySize)
	{
		do 
		{
			newArraySize--;
			newArrayPart[newArraySize] = arrayPart[newArraySize];
		} 
		while (newArraySize);
	}

	delete[] arrayPart;
	arrayPart = newArrayPart;
}

template<typename ELEMENT> 
void Table<ELEMENT>::resizeHash(uint newHashSize)
{
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
			assert(!Key::isValid(newNode->key));
			assert(!newNode->value.isValid);
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
typename Table<ELEMENT>::Value* Table<ELEMENT>::set(const Key& key)
{
	if (Value* v = get(key))
	{
		return v;
	}
	else
	{
		return newKey(key);
	}
}

template<typename ELEMENT> 
void Table<ELEMENT>::setWithInteger(const Key& key, ELEMENT& value)
{	
	Value* position = findValueWithSignedInteger(key);
	
	if (!position)
	{
		position = newKey(key);
	}
	
	position->value = value;
}

template<typename ELEMENT> 
sint Table<ELEMENT>::twoTo(sint x)
{
	return 1 << x;
}

} // namespace containers

#endif//TABLE_H