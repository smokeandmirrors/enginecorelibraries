#pragma once
#ifndef HASHING_H
#define HASHING_H

#include "math.h"
#include "float.h"

#include "Platform.h"

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

	inline uint
		modHashPowerOf2(hash key, uint powerOf2);

	inline hash computeHash(bool key)
	{
		return static_cast<hash>(key);
	}

	inline hash computeHash(const schar* string)
	{	
		return computeHash(string, strlen(string));
	}

	inline hash computeHash(const schar* string, size_t length)
	{	// taking from Lua: lstring.c
		hash h = static_cast<hash>(length);
		hash step = static_cast<hash>((length >> 5) + 1);

		for ( ; length >= step; length -= step) 
		{
			h = h ^ ((h << 5) + (h >> 2) + static_cast<hash>(string[length - 1]));
		}

		return h;
	}

	inline hash computeHash(const void* pointer)
	{
		return static_cast<hash>(reinterpret_cast<ulong>(pointer));
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

	inline uint modHashPowerOf2(hash key, uint powerOf2)
	{
		assert((powerOf2 & (powerOf2 - 1)) == 0);
		return key & (powerOf2 - 1);
	}

} // namespace algorithms

#endif//HASHING_H