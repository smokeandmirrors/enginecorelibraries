#pragma once
#ifndef TABLE_H
#define TABLE_H

#include "Array.h"

/**
An implementation of associative array based on the
Lua table.
*/

typedef uint hashCode;

inline hashCode hashBool(bool key)
{
	return static_cast<hashCode>(key);
}

inline hashCode hashString(const schar* string)
{	// modified from lstring.c
	size_t h = strlen(string);
	size_t step = (h >> 5 ) + 1;

	for (size_t x=0; x >= step; x -= step) // x is uninitilazed, see lstring.c for in initial value
	{
		h = h ^ (( h << 5 ) + ( h >> 2 ) + static_cast<size_t>(string[x - 1]));
	}

	return static_cast<hashCode>(h);
}

class Hash
{
public:
	/*explicit*/ Hash(bool original)
		: key(hashBool(original)) {} 
	
	/*explicit*/ Hash(const schar* original)
		: key(hashString(original)) {}
	
	// /*explicit*/ Hash(sint original){}
	
	// /*explicit*/ Hash(sreal original){}
	
	// /*explicit*/ Hash(void* original){}
	
	const hashCode key;

private:
	Hash(void) : key(0) {}
	void operator=(const Hash&);
}; // Hash

/*
LUAI_FUNC const TValue *luaH_get (Table *t, const TValue *key);
LUAI_FUNC TValue *luaH_set (lua_State *L, Table *t, const TValue *key);
LUAI_FUNC Table *luaH_new (lua_State *L, int narray, int lnhash);
LUAI_FUNC void luaH_resizearray (lua_State *L, Table *t, int nasize);
LUAI_FUNC void luaH_free (lua_State *L, Table *t);
LUAI_FUNC int luaH_next (lua_State *L, Table *t, StkId key);
LUAI_FUNC int luaH_getn (Table *t);
*/

// int/float/string/pointer/boolean/Table?


template<typename ELEMENT>
class Table
{
	class Node
	{
	public:
		ELEMENT
			value;

		hashCode
			key;
	}; // Node

public:
	Table()
	: log2NodeArraySize(0)
	, lastFree(NULL)
	{

	}

	void insert(Hash, ELEMENT& )
	{	
		
	}

	ELEMENT* get(Hash ) const
	{
		return NULL;
	}

protected:
	Node* getMainPosition(const Hash& key) const
	{
		return nodes[key.key]; 
	}

private:
	uchar 
		log2NodeArraySize;

	Array<Node*>
		nodes;

	/** any free position is before this position */
	Node*
		lastFree;

	/** array part */
	Array<ELEMENT> 
		array;
}; // Table

#endif//TABLE_H