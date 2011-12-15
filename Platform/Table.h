#pragma once
#ifndef TABLE_H
#define TABLE_H

#include <vector>

/**
An implementation of associative array based on the
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
		HashableTypes_bool,
		HashableTypes_pointer,
		HashableTypes_sint,
		HashableTypes_sreal,
		HashableTypes_string,
	};
	
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
	
	const algorithms::hashCode 
		key;
	
	const HashableType 
		type;

private:
	Hash(void);
	
	void 
		operator=(const Hash&);
}; // Hash

/*


LUAI_FUNC void luaH_resizearray (lua_State *L, Table *t, int nasize);

LUAI_FUNC int luaH_next (lua_State *L, Table *t, StkId key);
LUAI_FUNC int luaH_getn (Table *t);
*/

// int/float/string/pointer/boolean/Table?


template<typename ELEMENT>
class Table 
{
	struct Node
	{
		ELEMENT
			value;

		algorithms::hashCode
			key;
	}; // Node

public:
	Table(sint arraySize=0); // LUAI_FUNC Table *luaH_new (lua_State *L, int narray, int lnhash);
	~Table(void); // LUAI_FUNC void luaH_free (lua_State *L, Table *t);
	/* LUAI_FUNC const TValue *luaH_get (Table *t, const TValue *key);
	LUAI_FUNC TValue *luaH_set (lua_State *L, Table *t, const TValue *key);	*/
	ELEMENT& 
		operator[](const Hash& key);
	
	const ELEMENT& 
		operator[](const Hash& key) const;

	bool 
		has(const Hash& key) const;
	
private:
	inline Node* 
		getMainPosition(const Hash& key) const;
	
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

	inline Node*
		insert(const Hash& key, ELEMENT& value); 
	
	uchar 
		log2NodeArraySize;

	std::list<Node*>
		nodes;
	 
	Node*					// any free position is before this position
		lastFree;
	
	std::vector<ELEMENT>	// array part 
		array;
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
Table<ELEMENT>::Table(sint arraySize)
: log2NodeArraySize(0)
, lastFree(NULL)
{

}
// LUAI_FUNC void luaH_free (lua_State *L, Table *t);
template<typename ELEMENT>
Table<ELEMENT>::~Table(void)
{
	// free nodes and stuff
}

template<typename ELEMENT> 
typename Table<ELEMENT>::Node* Table<ELEMENT>::findNodeWithString(const Hash& key) const
{	// HashableTypes_string
	// hashstr(this, key); -> hashpow2(this, (key)->tsv.hash)
	// hashpow2(this, key.key); -> hashpow2(this,key.key)      ( gnode(this, lmod((key.key), sizenode(this))) )
	//		sizenode(this) -> twoto((this)->log2NodeArraySize)
	//			twoto -> 1<<(log2NodeArraySize)
	//		lmod(key.key, 1<<log2NodeArraySize)); -> lmod(key.key,log2NodeArraySize) = ()
	//			check_exp( (log2NodeArraySize&(log2NodeArraySize-1))==0, ( ) ) )
	//				(lua_assert((log2NodeArraySize&(log2NodeArraySize-1))==0), (cast(int, (key.key) & ((log2NodeArraySize)-1)))
	//		gnode(this,i)	-> (&(this)->node[i])

	// Node *n = (gnode(this, lmod((key.key), sizenode(this))))
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
	return NULL;
}

/* LUAI_FUNC const TValue *luaH_get (Table *t, const TValue *key);
LUAI_FUNC TValue *luaH_set (lua_State *L, Table *t, const TValue *key);	*/
template<typename ELEMENT> 
typename ELEMENT& Table<ELEMENT>::operator[](const Hash& key )
{	// finish me
	

	// just make the stuff compile right now
	Node* n = getMainPosition(key);
	
	if (!n)
	{
		ELEMENT defaultElement;
		n = insert(key, defaultElement);
	}
	
	return n->value;
	


	
	
	
	// return array[0];
}
/* LUAI_FUNC const TValue *luaH_get (Table *t, const TValue *key);
LUAI_FUNC TValue *luaH_set (lua_State *L, Table *t, const TValue *key);	*/
template<typename ELEMENT> 
const ELEMENT& Table<ELEMENT>::operator[](const Hash& /* key */) const
{
	return array[0];
}

} // namespace containers

#endif//TABLE_H