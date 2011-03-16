#pragma once
#ifndef NUMERICALFUNCTIONS_H
#define NUMERICALFUNCTIONS_H

#include <float.h>

#include "Build.h"
#include "Numbers.h"
/**
\todo C99 functions:
http://en.wikipedia.org/wiki/Math.h
*/

namespace math
{

// template<typename T> sqrt(T square);

bool isFinite(real4 number); 
bool isNaN(real4 number);	
bool isValid(real4 number);	

inline bool isFinite(real4 number)	{ return _finite(number) != 0; }
inline bool isNaN(real4 number)		{ return _isnan(number) != 0; }
inline bool isValid(real4 number)	{ return _finite(number) != 0; }
} // namespace math


#endif//NUMERICALFUNCTIONS_H