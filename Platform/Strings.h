#pragma once
#ifndef STRINGS_H
#define STRINGS_H

#include "Hashing.h"
#include <string>
#include "Platform.h"
#include "Singleton.h"

class Strings 
	: public designPatterns::Singleton<Strings>
{
public:
	class Immutable;
	class Mutable;

	static const Immutable& 
		getImmutable(const schar* value);

	static const Immutable& 
		getImmutable(const schar* value, size_t length);

	static const Immutable& 
		getImmutable(const std::string& value);

	class Immutable
	{
	public:
		const std::string 
			string;

		const algorithms::hash 
			hashCode;

	private:
		Immutable(const schar* value, size_t length)
		: string(value)
		, hashCode(algorithms::computeHash(value, length))
		{ /* empty */ }

		Immutable& operator=(const Immutable&);

		Immutable* next;
	}; // strings::Immutable

	class Mutable
	{
	public:
		std::string 
			string;
	}; // strings::Mutable

private:
	Strings(void);

	~Strings(void);

	Immutable* 
		createNew(const schar* value, size_t length);

	Immutable*
		find(const schar* value, size_t length);

	void
		resizeImmutableTable(uint newSize);

	uint			
		numUsed;

	std::vector<Immutable*> 
		table;

}; // class Strings

Strings::Strings(void)
: numUsed(0)
{

}

Strings::~Strings(void)
{
	/** \todo free all the immutables */
}

Strings::Immutable* Strings::createNew(const schar* value, size_t length)
{
	if (numUsed >= table.capacity() && table.capacity() <= (INT_MAX / 2));
	{
		resizeImmutableTable(table.capacity() * 2);
	}

	Immutable* string = new Immutable(value, length);
	const uint index = algorithms::modHashPowerOf2(string->hashCode, table.capacity());
	table[index] = string;
	numUsed++;
	return string;
}

void Strings::resizeImmutableTable(uint newSize)
{
	sint oldCapacity = table.capacity();
	// grow
	if (newSize > oldCapacity)
	{
		table.resize(newSize);
		
		for (sint i = oldCapacity; i < newSize; i++)
		{
			table[i] = NULL;
		}
	}
	// rehash
	for (sint i = 0; i < oldCapacity; i++)
	{
		Immutable* p = table[i];

		while (p)
		{
			// save next
			Immutable* next = p->next;
			// calc new position
			uint index = algorithms::modHashPowerOf2(next->hashCode, newSize);
			// chain it
			p->next = table[index];
			table[index] = p;
			p = next;
		}
	}
	// shrink
	if (newSize < oldCapacity)
	{
		assert(table[newSize] == NULL && table[oldCapacity - 1] == NULL);
		table.resize(newSize);
	}
}

#endif//STRINGS_H