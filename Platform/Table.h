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

inline hashCode hashBool(bool key);
inline hashCode hashString(const schar* string);
inline hashCode hashString(const schar* string, size_t x);

} // namespace algorithms

namespace containers
{

class Hash
{
public:
	/*explicit*/ Hash(bool original)
		: key(algorithms::hashBool(original)) {} 
	
	/*explicit*/ Hash(const schar* original)
		: key(algorithms::hashString(original, strlen(original))) {}
	
	// /*explicit*/ Hash(sint original){}
	
	/** \todo if this is ever finished, profile and optimize the float to int conversion */
	// /*explicit*/ Hash(sreal original){}
	
	// /*explicit*/ Hash(void* original){}
	
	const algorithms::hashCode key;

private:
	Hash(void) : key(0) {}
	void operator=(const Hash&);
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
	
protected:
	inline Node* 
		getMainPosition(const Hash& key) const
	{
		return nodes[key.key]; 
	}
	
private:
	uchar 
		log2NodeArraySize;

	std::vector<Node*>
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

/* LUAI_FUNC const TValue *luaH_get (Table *t, const TValue *key);
LUAI_FUNC TValue *luaH_set (lua_State *L, Table *t, const TValue *key);	*/
template<typename ELEMENT> 
ELEMENT& Table<ELEMENT>::operator[](const Hash& /* key */)
{	// finish me
	return array[0];
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