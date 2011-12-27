#pragma once
#ifndef STRINGS_H
#define STRINGS_H

#define DEVELOP_INTERNAL_STRING 1
#if DEVELOP_INTERNAL_STRING

#include "Hashing.h"
#include <string>
#include "Platform.h"
#include "Singleton.h"

class Strings 
	: public designPatterns::Singleton<Strings>
{
	class ImmutableInternal;
	friend class designPatterns::Singleton<Strings>;

public:
	class Argument;
	class Immutable;
	class Mutable;
	
	class Argument
	{
	public:
		Argument(const schar* v)
		: cStyleString(v)
		, size(-1)
		{ assert(cStyleString != NULL); }

		Argument(const schar* v, size_t valueLength)
		: cStyleString(v)
		, size(static_cast<sint>(valueLength))
		{ assert(cStyleString != NULL); }

		Argument(const std::string& v)
		: cStyleString(NULL)
		, cppStyleString(&v) // could I be taking the address of temporaries here?
		{ assert(cppStyleString != NULL); }

		const char* 
			c_str(void) const
		{
			return cStyleString ? cStyleString : cppStyleString->c_str();
		}

		size_t
			length(void) const
		{
			if (cStyleString)
			{
				if (size > 0)
				{
					return size;
				}
				else
				{	
					return strlen(cStyleString);
				}
			}
			else
			{
				return cppStyleString->length();
			} 
		}

	private:
		const schar*
			cStyleString;

		sint 
			size;

		const std::string*
			cppStyleString;
	}; // Argument

	
	class Immutable
	{
	public:
		// inline wrap all the const std::string methods
		Immutable(const Argument& s)
			: internal(Strings::single().find(s))
		{
			internal.acquire();
		}

		~Immutable(void)
		{
			internal.release();
		}

		inline bool
			operator==(const Immutable& other) const
		{
			return &internal == &other.internal;
		}

		inline const char*
			c_str(void) const
		{
			return internal.string.c_str();
		}

	private:
		Immutable&
			operator=(const Immutable&);

		const ImmutableInternal&
			internal;
	}; // class Immutable

	class Mutable
	{
	public:
		std::string 
			string;
	}; // strings::Mutable

protected:	
	Strings(void);
	~Strings(void);


private:
	class ImmutableInternal
	{
	public:
		ImmutableInternal(const schar* cstring, size_t length, const algorithms::hash key)
		: next(NULL)
		, string(cstring, length)
		, hashCode(key)
		, references(0)
		{ /* empty */ }

		void 
			acquire(void) const 
		{ 
			++references; 
		}
		
		void 
			release(void) const 
		{ 
			--references; 

			if (!references)
			{	// tell the Strings singleton
				// about the fact there are no more references
				// to this string
				Strings::single().notifyDeadString(this);
				delete this;
			}
		}
		
		ImmutableInternal* 
			next;
		
		const std::string 
			string;
		
		const algorithms::hash 
			hashCode;

	private:
		ImmutableInternal& 
			operator=(const ImmutableInternal&);

		mutable uint
			references;
	}; // strings::Immutable
	
	const ImmutableInternal&
		find(const Argument& s)	;

	void 
		notifyDeadString(const ImmutableInternal* dead);

	void
		resizeImmutableTable(sint newSize);

	uint			
		numUsed;

	std::vector<ImmutableInternal*> 
		table;

}; // class Strings

Strings::Strings(void)
: numUsed(0)
{
	table.push_back(NULL);
}

Strings::~Strings(void)
{
	/** \todo free all the ImmutableInternal */
}

const Strings::ImmutableInternal& Strings::find(const Argument& search) 
{
	const schar* search_string = search.c_str();
	size_t search_size = search.length();
	const algorithms::hash key = algorithms::computeHash(search_string, search_size);
	const uint index = algorithms::modHashPowerOf2(key, static_cast<uint>(table.size()));
		
	for (ImmutableInternal* s = table[index]; s != NULL; s = s->next)
	{
		if (s->hashCode == key 
		&& s->string.size() == search_size
		&& String::isEqual(s->string.c_str(), search_string))
		{	// found the key
			return *s;
		}
	}
	// not found, create a new name	
	if (numUsed >= table.size() 
	&& table.size() <= (INT_MAX / 2))
	{
		resizeImmutableTable(static_cast<uint>(table.size() * 2));
	}
	
	ImmutableInternal* string = new ImmutableInternal(search_string, search_size, key);
	const uint newindex = algorithms::modHashPowerOf2(key, static_cast<uint>(table.size()));
	
	if (table[newindex])
	{
		string->next = table[newindex];
	}
	else
	{
		table[newindex] = string;
	}
	
	numUsed++;
	return *string;
}
 
void Strings::notifyDeadString(const ImmutableInternal* dead)
{
	const uint index = algorithms::modHashPowerOf2(dead->hashCode, static_cast<uint>(table.size()));
	ImmutableInternal* previous(NULL);

	for (ImmutableInternal* s = table[index]; s != NULL; s = s->next)
	{
		if (s == dead)
		{
			if (previous)
			{
				previous->next = dead->next;
			}
		}

		previous = s;
		s = s->next;
	}
}

void Strings::resizeImmutableTable(sint newSize)
{
	sint oldCapacity = static_cast<sint>(table.size());
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
		ImmutableInternal* p = table[i];

		while (p)
		{
			// save next
			ImmutableInternal* next = p->next;
			// calc new position
			uint index = algorithms::modHashPowerOf2(p->hashCode, newSize);
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

#endif//DEVELOP_INTERNAL_STRING

#endif//STRINGS_H