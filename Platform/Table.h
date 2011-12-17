#pragma once
#ifndef TABLE_H
#define TABLE_H

#include <vector>

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
	static Hash getInvalid(void);

	/*explicit*/ Hash(const schar* original)
		: key(algorithms::hashString(original, strlen(original)))
		, type(HashableTypes_string)
		{ }
	
	// same lua get function
	/** \todo if this is ever finished, profile and optimize the float to int conversion */
	// /*explicit*/ Hash(sint original){}
	// /*explicit*/ Hash(sreal original){}
	
	// same lua get function
	///*explicit*/ Hash(bool original)
	//	: key(algorithms::hashBool(original)) {} 
	// /*explicit*/ Hash(void* original){}
	// /*explicit*/ Hash(void* original){}
	
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
	Hash(void);
}; // Hash

/*
LUAI_FUNC void luaH_resizearray (lua_State *L, Table *t, int nasize);
LUAI_FUNC int luaH_next (lua_State *L, Table *t, StkId key);
LUAI_FUNC int luaH_getn (Table *t);
*/

// int/float/string/pointer/boolean/Table?

static const sint maxBits(26);
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
		: key(Hash::getInvalid())
		{
			/* empty */
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
	Table(sint reserveArraySize=0, sint reserveHashSize=0); 
	~Table(void); // LUAI_FUNC void luaH_free (lua_State *L, Table *t);
	
	ELEMENT& 
		operator[](const Hash& key);
	
	const ELEMENT& 
		operator[](const Hash& key) const;

	bool 
		has(const Hash& key) const;
	
private:
	/** will template versions of these be unnecessarily generated? */
	static inline sint
		calculateArrayIndex(const Hash& key);

	static inline sint
		calculateNewArraySize(sint nums[], sint* numArrays);

	static inline sint
		countInt(const Hash& key, sint* outputNumbers);

	static inline sint
		logTwo(uint x);

	static inline sint
		logTwoCeil(sint x);

	static inline sint 
		twoTo(sint x);
	
	inline sint
		calculateHashIndex(const Hash& key) const;

	inline sint 
		countKeysInArray(sint* perSlotOutput) const;
	
	inline sint 
		countKeysInHash(sint* perSlotOutput, sint* keysInArray) const;

	inline Node*
		findNodeWithBool(const Hash& key) const;

	inline Node*
		findNodeWithPointer(const Hash& key) const;
	
	inline Node*
		findNodeWithReal(const Hash& key) const;

	inline Node*
		findNodeWithSignedInteger(const Hash& key) const;
		
	inline Node*
		findNodeWithString(const Hash& key) const;

	inline const Value*
		get(const Hash& key) const;

	inline Node*
		getFreePosition(void);

	inline Node* 
		getMainPosition(const Hash& key) const;
	
	inline sint
		getSizeOfNodeArray(void) const;

	inline Value*
		newKey(const Hash& key);

	inline void
		rehash(const Hash& key);

	inline void
		resize(sint arraySize, sint hashSize);

	inline void
		resizeArray(sint newArraySize);

	inline void
		resizeHash(sint newHashSize);

	inline Value*
		set(const Hash& key);

	uchar 
		log2HashPartArraySize;

	sint
		arrayPartSize;

	Node*
		dummyNode;

	Node*					
		firstFree;
	
	Node*					
		hashPart;
		
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

namespace containers
{
// LUAI_FUNC Table *luaH_new (lua_State *L, int narray, int lnhash);
template<typename ELEMENT> 
Table<ELEMENT>::Table(sint reserveArraySize, sint reserveHashSize)
: log2HashPartArraySize(0)
, arrayPartSize(0)
, hashPart(NULL)
, firstFree(NULL)
, arrayPart(NULL)
{
	dummyNode = new Node();
	dummyNode->key = Hash::getInvalid();
	dummyNode->next	= NULL;
	dummyNode->value.isValid = 0;
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
	{
		return key.key;
	}
	else
	{
		return -1;
	}
}

template<typename ELEMENT>
sint Table<ELEMENT>::calculateHashIndex(const Hash& key) const
{	// 'mod operation'
	return key.key & (twoTo(log2HashPartArraySize) - 1);
}

template<typename ELEMENT>
sint Table<ELEMENT>::calculateNewArraySize(sint nums[], sint* numArrays)
{
	sint i;
	sint twotoi;  /* 2^i */
	sint a = 0;  /* number of elements smaller than 2^i */
	sint na = 0;  /* number of elements to go to array part */
	sint n = 0;  /* optimal size for array part */
	for (i = 0, twotoi = 1; twotoi/2 < *numArrays; i++, twotoi *= 2) {
		if (nums[i] > 0) {
			a += nums[i];
			if (a > twotoi/2) {  /* more than half elements present? */
				n = twotoi;  /* optimal size (till now) */
				na = a;  /* all elements smaller than n will go to array part */
			}
		}
		if (a == *numArrays) break;  /* all elements already counted */
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
	sint i = getSizeOfNodeArray();
	
	while (i--) 
	{
		Node *n = &(hashPart[i]);
		
		if (!n->isValid) 
		{
			summationOfNums += countInt(n->key, perSlotOutput);
			totaluse++;
		}
	}
	
	*keysInArray += summationOfNums;
	return totaluse;
}

template<typename ELEMENT> 
typename Table<ELEMENT>::Node* Table<ELEMENT>::findNodeWithString(const Hash& key) const
{	// HashableTypes_string
	// hashstr(this, key); -> hashpow2(this, (key)->tsv.hash)
	// hashpow2(this, key.key); -> hashpow2(this,key.key)      ( gnode(this, lmod((key.key), sizenode(this))) )
	//		sizenode(this) -> twoto((this)->log2HashPartArraySize)
	//			twoto -> 1<<(log2HashPartArraySize)
	//		lmod(key.key, 1<<log2HashPartArraySize)); -> lmod(key.key,log2HashPartArraySize) = ()
	//			check_exp( (log2HashPartArraySize&(log2HashPartArraySize-1))==0, ( ) ) )
	//				(lua_assert((log2HashPartArraySize&(log2HashPartArraySize-1))==0), (cast(int, (key.key) & ((log2HashPartArraySize)-1)))
	//		gnode(this,i)	-> (&(this)->node[i])

	// Node *n = (gnode(this, lmod((key.key), sizenode(this))))

	
	//	
	sint index = calculateHashIndex(key);
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
typename Table<ELEMENT>::Node* Table<ELEMENT>::getFreePosition(void) 
{
	while (firstFree-- > hashPart)
	{
		if (!firstFree->isValid)
			return firstFree;
	}	
	// no free position
	return NULL;
}

template<typename ELEMENT> 
typename Table<ELEMENT>::Node* Table<ELEMENT>::getMainPosition(const Hash& key) const
{
	switch (key.type)
	{
		/*
	case Hash::HashableTypes_bool:
		return findNodeWithBool(key.key);
	
	case Hash::HashableTypes_pointer:
		return findNodeWithPointer(key.key);
	
	case Hash::HashableTypes_sint:
		return findNodeWithSignedInteger(key.key);
	
	case Hash::HashableTypes_sreal:
		return findNodeWithReal(key.key);
	*/
	case Hash::HashableTypes_string:
		return findNodeWithString(key);
	
	default:
		assert(false);
	}
	
	return dummyNode;
}

template<typename ELEMENT> 
sint Table<ELEMENT>::getSizeOfNodeArray(void) const
{
	return 1 << log2HashPartArraySize;
}

template<typename ELEMENT> 
sint Table<ELEMENT>::logTwo(uint x)
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
	
	sint multipleOfEight = -1;
	
	while (x >= 256) 
	{ 
		multipleOfEight += 8; 
		x >>= 8; 
	}
	
	return multipleOfEight + logBaseTwoArray[x];
}

template<typename ELEMENT> 
sint Table<ELEMENT>::logTwoCeil(sint x)
{
	return logTwo(x - 1) + 1;
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
	Node* mainPosition = getMainPosition(key);
	
	if (!mainPosition->value->isValueValid)
	{
		Node* freePosition = getFreePosition();

		if (!freePosition)
		{
			rehash(key);
			return set(key);
		}
		
		assert(mainPosition->key == key);
		Node* other = getMainPosition(mainPosition->key);

		if (other != mainPosition)
		{
			while (other->next != mainPosition)
			{
				other = other->next;
			}

			other->next	 = freePosition;
			*freePosition = *mainPosition;
			mainPosition->next = NULL;
			mainPosition->value->isValueValid = Value::invalid;
		}
	}
	
	mainPosition->key = key;
	assert(!mainPosition->value->isValueValid);
	return &(mainPosition->value);
}

/* LUAI_FUNC const TValue *luaH_get (Table *t, const TValue *key);
LUAI_FUNC TValue *luaH_set (lua_State *L, Table *t, const TValue *key);	*/
template<typename ELEMENT> 
ELEMENT& Table<ELEMENT>::operator[](const Hash& key )
{	// finish me
	// just make the stuff compile right now
	Node* n = getMainPosition(key);
	
	if (!n)
	{
		// ELEMENT defaultElement;
		// n = insert(key, defaultElement);
	}
	
	return n->value.value;		
	// return arrayPart[0];
}
/* LUAI_FUNC const TValue *luaH_get (Table *t, const TValue *key);
LUAI_FUNC TValue *luaH_set (lua_State *L, Table *t, const TValue *key);	*/
template<typename ELEMENT> 
const ELEMENT& Table<ELEMENT>::operator[](const Hash& /* key */) const
{
	return arrayPart[0];
}

template<typename ELEMENT> 
void Table<ELEMENT>::rehash(const Hash& key)
{
	sint nasize, na;
	sint nums[maxBits+1];  /* nums[i] = number of keys between 2^(i-1) and 2^i */
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
	sint oldHashSize = log2HashPartArraySize;
		
	if (newArraySize > oldArraySize)  
	{
		resizeArray(newArraySize);
	}
	else if (newArraySize < oldArraySize) 
	{ 
		arrayPartSize = newArraySize;
		
		for (sint i=newArraySize; i<oldArraySize; i++) 
		{
			if (arrayPart[i].isValid)
			{	// finish me...
			// 	setobjt2t(L, luaH_setnum(L, t, i+1), &t->array[i]);
			}
		}
		/* shrink array */
		// luaM_reallocvector(L, t->array, oldArraySize, newArraySize, TValue);
	}
	
	Node* oldHashPart = hashPart;  
	resizeHash(newHashSize);  
	
	/* re-insert elements from hash part */
	sint i = twoTo(oldHashSize) - 1;
	if (i > 0)
	{
		do 
		{
			i--;
			Node* old = oldHashPart + i;
			
			if (!old->value.isValid)
			{	//									old->key, old->value
				// setobjt2t(L, luaH_set(L, t, key2tval(old)), gval(old));
				// is a copy (1 , 2) 1 := 2 
				
			}
		} 
		while (i);
	}

	if (oldHashPart != NULL)
	{
		// luaM_freearray(L, nold, twoto(oldHashSize), Node);  
	}
}


template<typename ELEMENT> 
void Table<ELEMENT>::resizeArray(sint /*newArraySize*/)
{

}

template<typename ELEMENT> 
void Table<ELEMENT>::resizeHash(sint /*newHashSize*/)
{

}

template<typename ELEMENT> 
typename Table<ELEMENT>::Value* Table<ELEMENT>::set(const Hash& key)
{
	Value* v = const_cast<Value*>(get(key));
	
	if (!v)
	{
		assert(Hash::isValid(key));
		v = newKey(key);
	}
		
	return v;
}

template<typename ELEMENT> 
sint Table<ELEMENT>::twoTo(sint x)
{
	return 1 << x;
}

} // namespace containers

#endif//TABLE_H