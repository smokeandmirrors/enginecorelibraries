#pragma once
#ifndef STRINGS_H
#define STRINGS_H

#include <string>
#include <vector>

#include "Hashing.h"
#include "Platform.h"
#include "Singleton.h"

class String 
	: public designPatterns::Singleton<String>
{
	class ImmutableInternal;
	friend class designPatterns::Singleton<String>;

public:
	class Argument;
	class Immutable;
	class Mutable;
	
	static sint 
		compare(const schar* a, const schar* b)
	{
		int difference(*(unsigned char *)a - *(unsigned char *)b);

		while (!difference && *b)
		{
			++a, ++b;
			difference = *(unsigned char *)a - *(unsigned char *)b;
		}

		return difference;
	}

	inline static sint
		compare(const Immutable& a, const Immutable& b)
	{
		return compare(a.c_str(), b.c_str());
	}

	static bool 
		isEqual(const schar* a, const schar* b)
	{
		return !compare(a, b);
	}

	static bool
		isEqual(const Immutable& a, const Immutable& b)
	{
		return a == b;
	}

	class Argument
	{
	public:
		Argument(const char* v)
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
		inline Immutable()
		: internal(&String::single.find(""))
		{
			internal->acquire();
		}
		
		inline Immutable(const Argument& s)
		: internal(&String::single.find(s))
		{
			internal->acquire();
		}

		inline Immutable(const Immutable& s)
		: internal(s.internal)
		{
			internal->acquire();
		}

		~Immutable(void)
		{
			internal->release();
		}

		inline void
			acquire(void)
		{
			internal->acquire();
		}

		inline void
			release(void)
		{
			internal->release();
		}

		inline const char*
			c_str(void) const
		{
			return internal->string.c_str();
		}

		inline algorithms::hash 
			getHash(void) const
		{
			return internal->hashCode;
		}	

		inline Immutable&
			operator=(const Immutable& source)
		{
			internal->release();
			internal = source.internal;
			internal->acquire();
			return *this;
		}

		inline bool
			operator==(const Immutable& other) const
		{
			return internal == other.internal;
		}

	private:
		const ImmutableInternal*
			internal;
	}; // class Immutable

	class Mutable
	{
	public:
		std::string 
			string;
	}; // strings::Mutable

protected:	
	String(void);
	~String(void);


private:
	class ImmutableInternal
	{
	public:
		ImmutableInternal(const schar* cstring, size_t length, const algorithms::hash key, ImmutableInternal* nextInternal)
		: next(nextInternal)
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
			{	// tell the String singleton
				// about the fact there are no more references
				// to this string
				String::single.notifyDeadString(this);
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
		find(const Argument& s);	

	void 
		notifyDeadString(const ImmutableInternal* dead);

	void
		resizeImmutableTable(sint newSize);

	uint			
		numUsed;

	std::vector<ImmutableInternal*> 
		table;

}; // class String


#endif//STRINGS_H