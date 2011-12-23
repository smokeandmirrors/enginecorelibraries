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

typedef uint hashCode;

inline hashCode 
	hashBool(const bool key);

template<typename T>
inline hashCode
	hashGeneric(const T* pointer);

inline hashCode
	hashInteger(sint number);

inline hashCode
	hashPointer(const void* pointer);

inline hashCode
	hashReal(sreal number);

inline hashCode 
	hashString(const schar* string);

inline hashCode 
	hashString(const schar* string, size_t x);

} // namespace algorithms

namespace containers
{

/** 
clean up the hash, turn it into class Key, 
and turn every value into its static uin hash (which then
gets hashed again depending on the array size
*/
struct Hash
{
	// todo template this?
	enum HashableType
	{
		HashableTypes_invalid,
		HashableTypes_bool,
		HashableTypes_pointer,
		HashableTypes_sint,
		HashableTypes_sreal,
		HashableTypes_string,		
	};
	
	static bool isValid(const Hash& h);
	
	Hash(void)
		: type(HashableTypes_invalid)
	{/* empty */}

	/*explicit*/ Hash(const schar* original)
		: key(algorithms::hashString(original, strlen(original)))
		, type(HashableTypes_string)
		{ }
	
	/** \todo if this is ever finished, profile and optimize the float to int conversion */
	/*explicit*/ Hash(sint /*original*/){}
	/*explicit*/ Hash(sreal /*original*/){}
	
	// same lua get function
	/*explicit*/ Hash(bool original)
		: key(algorithms::hashBool(original)) {} 
	/*explicit*/ Hash(void* /*original*/){}
	
	Hash& operator=(const Hash& original)
	{
		key = original.key;
		type = original.type;
		return *this;
	}

	algorithms::hashCode 
		key;
	
	HashableType 
		type;

private:
}; // Hash

static const sint maxBits(30);
static const sint maxArraySize( 1 << maxBits);
static const sint valid(1);
static const sint invalid(0);

template<typename ELEMENT>
class Table 
{
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
			/* empty, should be completely invalid*/
		}

		Node(ELEMENT v, const containers::Hash& k)
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

		containers::Hash
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
		operator[](const Hash& key);
	
	const ELEMENT& 
		operator[](const Hash& key) const;
	
	bool 
		has(const Hash& key) const;
	// TValue *luaH_set (lua_State *L, Table *t, const TValue *key);
	inline const Value*
		set(const Hash& key);
	
private:
	/// \todo will template versions of these be unnecessarily generated? 
	// static int arrayindex (const TValue *key)
	static inline sint
		calculateArrayIndex(const Hash& key);
	// static int computesizes (int nums[], int *narray)
	static inline sint
		calculateNewArraySize(sint nums[], sint* numArrays);
	// static int countint (const TValue *key, int *nums)
	static inline sint
		countInt(const Hash& key, sint* outputNumbers);

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
	inline const Value*
		get(const Hash& key) const;
	
	inline Value*
		findValueWithBool(const Hash& key) const;

	inline Value*
		findValueWithPointer(const Hash& key) const;
	
	inline Value*
		findValueWithReal(const Hash& key) const;
	// const TValue *luaH_getint (Table *t, int key);
	inline Value*
		findValueWithSignedInteger(const Hash& key) const;
	// const TValue *luaH_getstr (Table *t, TString *key);	
	inline Value*
		findValueWithString(const Hash& key) const;
	// static Node *getfreepos (Table *t)
	inline Node*
		getFreePosition(void);
	// #define hashboolean(t,p)        hashpow2(t, p)
	inline Node*
		getHashPositionOfBool(const Hash& key) const;
	// #define hashpointer(t,p)	hashmod(t, IntPoint(p))
	inline Node*
		getHashPositionOfPointer(const Hash& key) const;
	// static Node *hashnum (const Table *t, lua_Number n)
	inline Node*
		getHashPositionOfNumber(const sreal number) const;
	// #define hashstr(t,str)  hashpow2(t, (str)->tsv.hash)
	inline Node*
		getHashPositionOfString(const Hash& key) const;
	// static Node *mainposition (const Table *t, const TValue *key)
	inline Node* 
		getMainPosition(const Hash& key) const;
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
		newKey(const Hash& key);
	// static void rehash (lua_State *L, Table *t, const TValue *ek)
	inline void
		rehash(const Hash& key);
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
		setWithInteger(sint key /*const Hash& key*/, ELEMENT& value);
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

inline algorithms::hashCode algorithms::hashBool(bool key)
{
	return static_cast<hashCode>(key);
}

inline algorithms::hashCode algorithms::hashString(const schar* string)
{	
	return hashString(string, strlen(string));
}

inline algorithms::hashCode algorithms::hashString(const schar* string, size_t x)
{	// modified from lstring.c
	uint h = static_cast<uint>(x);
	size_t step = (h >> 5 ) + 1;

	for (; x >= step; x -= step) 
	{
		h = h ^ (( h << 5 ) + ( h >> 2 ) + static_cast<size_t>(string[x - 1]));
	}

	return static_cast<hashCode>(h);
}

inline algorithms::hashCode algorithms::hashPointer(const void* pointer)
{
	return static_cast<uint>(reinterpret_cast<ulong>(pointer));
}

namespace containers
{
template<typename ELEMENT> 
typename Table<ELEMENT>::Node Table<ELEMENT>::dummyNode(Table<ELEMENT>::createDummyNode());

// LUAI_FUNC Table *luaH_new (lua_State *L, int narray, int lnhash);
template<typename ELEMENT> 
Table<ELEMENT>::Table(sint reserveArraySize, sint reserveHashSize)
: log2HashPartSize(0)
, arrayPartSize(0)
, hashPart(NULL)
, lastFree(NULL)
, arrayPart(NULL)
{
	resize(reserveArraySize, reserveHashSize);
}
// LUAI_FUNC void luaH_free (lua_State *L, Table *t);
template<typename ELEMENT>
Table<ELEMENT>::~Table(void)
{
	// free hashPart and stuff
}

template<typename ELEMENT>
sint Table<ELEMENT>::calculateArrayIndex(const Hash& key)
{
	if (key.key == Hash::HashableTypes_sint
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
sint Table<ELEMENT>::countInt(const Hash& key, sint* outputNumbers)
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
	sint twoToLogBase2;  /* 2^logBase2 */
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
typename Table<ELEMENT>::Value* Table<ELEMENT>::findValueWithString(const Hash& key) const
{	// HashableTypes_string
	// hashstr(this, key); -> hashpow2(this, (key)->tsv.hash)
	// hashpow2(this, key.key); -> hashpow2(this,key.key)      ( gnode(this, lmod((key.key), sizenode(this))) )
	//		sizenode(this) -> twoto((this)->log2HashPartSize)
	//			twoto -> 1<<(log2HashPartSize)
	//		lmod(key.key, 1<<log2HashPartSize)); -> lmod(key.key,log2HashPartSize) = ()
	//			check_exp( (log2HashPartSize&(log2HashPartSize-1))==0, ( ) ) )
	//				(lua_assert((log2HashPartSize&(log2HashPartSize-1))==0), (cast(int, (key.key) & ((log2HashPartSize)-1)))
	//		gnode(this,i)	-> (&(this)->node[i])

	// Node *n = (gnode(this, lmod((key.key), sizenode(this))))

	
	//	
	sint index = hashMod(key);
	Node* n = &(hashPart[index]);

	do 
	{
		if (n->key.type == Hash::HashableTypes_string
		&& n->key.key == key.key)
		{
			break;	
		}

		n = n->next;
	} 
	while (n);

	return NULL;

	/*
	luaH_get(t, string key) == luaH_getstr(t, rawtsvalue(key));

	do {  // check whether `key' is somewhere in the chain 
		// if the keytype is a string && the keys are equal
		if (ttisstring(gkey(n)) && rawtsvalue(gkey(n)) == key)
			return gval(n);  // that's it 
		else n = gnext(n);
	} while (n);
	return NULL;;
	*/
}

template<typename ELEMENT> 
typename const Table<ELEMENT>::Value* Table<ELEMENT>::get(const Hash& key) const
{
	switch (key.type)
	{
	// unfinished
	case Hash::HashableTypes_sint:
	{	
		uint index = static_cast<uint>(key.key);
		
		if (index < arrayPartSize)
		{
			return &arrayPart[index];
		}
		else
		{
			return NULL;
		}

		break;
	}
	
	default:
		assert(false);
	} // switch (key.type)

	return NULL;
} // const Table<ELEMENT>::Value* Table<ELEMENT>::get(const Hash& key) const

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
typename Table<ELEMENT>::Node* Table<ELEMENT>::getHashPositionOfBool(const Hash& key) const
{
	uint index = hashModPowerOf2(key.key);
	return &hashPart[index];
}

template<typename ELEMENT> 
typename Table<ELEMENT>::Node* Table<ELEMENT>::getHashPositionOfNumber(sreal number) const
{
	/// MOVE THIS TO THE CONSTRUCTOR FOR THE NEW KEY CLASS (replaces Hash)	
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
	// #define hashmod(gnode(t, ((n) % ((sizenode(t)-1)|1)))) 
	return &hashPart[hashMod(static_cast<uint>(key))];
}

template<typename ELEMENT> 
typename Table<ELEMENT>::Node* Table<ELEMENT>::getHashPositionOfPointer(const Hash& key) const
{
	uint index = hashMod(key.key);
	return &hashPart[index];
}

template<typename ELEMENT> 
typename Table<ELEMENT>::Node* Table<ELEMENT>::getHashPositionOfString(const Hash& key) const
{	
	uint index = hashModPowerOf2(key.key);
	return &hashPart[index];
}

template<typename ELEMENT> 
typename Table<ELEMENT>::Node* Table<ELEMENT>::getMainPosition(const Hash& key) const
{
	switch (key.type)
	{
	case Hash::HashableTypes_bool:
		return getHashPositionOfBool(key);
	
	case Hash::HashableTypes_pointer:
		return getHashPositionOfPointer(key);
	
	case Hash::HashableTypes_sint:
	case Hash::HashableTypes_sreal:
		return getHashPositionOfNumber(static_cast<sreal>(key.key)); // todo fix this part
	
	case Hash::HashableTypes_string:
		return getHashPositionOfString(key);
	
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
typename Table<ELEMENT>::Value* Table<ELEMENT>::newKey(const Hash& key)
{
	assert(Hash::isValid(key));
	Node* mainPosition = getMainPosition(key);
		
	if (isMainPositionIsTaken(mainPosition))
	{
		Node* freePosition = getFreePosition();

		if (!freePosition)
		{
			rehash(key);
			return const_cast<Value*>(set(key));
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
typename ELEMENT& Table<ELEMENT>::operator[](const Hash& /*key*/ )
{	// finish me
	return dummyNode.value.value;
}
/* LUAI_FUNC const TValue *luaH_get (Table *t, const TValue *key);
LUAI_FUNC TValue *luaH_set (lua_State *L, Table *t, const TValue *key);	*/
template<typename ELEMENT> 
const ELEMENT& Table<ELEMENT>::operator[](const Hash& /* key */) const
{	// finish me
	return dummyNode.value.value;
}

template<typename ELEMENT> 
void Table<ELEMENT>::rehash(const Hash& key)
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
				Value* oldValueInNewPosition = const_cast<Value*>(set(oldPosition->key));
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
			assert(!Hash::isValid(newNode->key));
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
typename const Table<ELEMENT>::Value* Table<ELEMENT>::set(const Hash& key)
{
	if (Value* v = const_cast<Value*>(get(key)))
	{
		return v;
	}
	else
	{
		return newKey(key);
	}
}

template<typename ELEMENT> 
void Table<ELEMENT>::setWithInteger(sint key /*const Hash& key*/, ELEMENT& value)
{	
	Value* position = const_cast<Value*>(findValueWithSignedInteger(key));
	
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