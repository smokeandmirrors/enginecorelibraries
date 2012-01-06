#include "Strings.h"


String::String(void)
: numUsed(0)
{
	table.push_back(NULL);
}

String::~String(void)
{
	std::vector<ImmutableInternal*>::iterator sentinel(table.end());
	std::vector<ImmutableInternal*>::iterator iter(table.begin());

	for (iter; iter != sentinel; iter++)
	{
		delete *(iter);
	}
}

const String::ImmutableInternal& String::find(const Argument& search) 
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

	const uint newindex = algorithms::modHashPowerOf2(key, static_cast<uint>(table.size()));
	ImmutableInternal* previousOccupant = table[newindex];
	ImmutableInternal* string = new ImmutableInternal(search_string, search_size, key, previousOccupant);
	table[newindex] = string;

	numUsed++;
	return *string;
}

void String::notifyDeadString(const ImmutableInternal* dead)
{
	const uint index = algorithms::modHashPowerOf2(dead->hashCode, static_cast<uint>(table.size()));
	ImmutableInternal* previous(NULL);

	if (index == 32)
	{
		printf("break");
	}

	ImmutableInternal* current = table[index];

	IF_DEBUG( bool found(false); )

	while (current)
	{
		if (current == dead)
		{
			assert(current->string == dead->string);

			if (previous)
			{
				previous->next = dead->next;
			}
			else
			{
				table[index] = current->next;
			}
	
			IF_DEBUG( found = true; )
			break;
		}

		assert(current->string != dead->string);
		previous = current;
		current = current->next;
	}

	IF_DEBUG( assert(found); )
	numUsed--;
}

void String::resizeImmutableTable(sint newSize)
{
	sint oldSize = static_cast<sint>(table.size());
	// grow
	if (newSize > oldSize)
	{
		table.resize(newSize);

		for (sint i = oldSize; i < newSize; i++)
		{
			table[i] = NULL;
		}
	}
	// rehash
	for (sint i = 0; i < oldSize; i++)
	{
		ImmutableInternal* p = table[i];
		table[i] = NULL;

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
	if (newSize < oldSize)
	{
		assert(table[newSize] == NULL && table[oldSize - 1] == NULL);
		table.resize(newSize);
	}
}