#pragma once
#ifndef NUMERICALFUNCTIONS_H
#define NUMERICALFUNCTIONS_H

#include <float.h>

#include "Build.h"
#include "Numbers.h"

namespace math
{
#define absvec_t		fabs
#define sqrtvec_t		sqrtf
#define logvec_t		logf

bool isFinite(vec_t number); 
bool isNaN(vec_t number);	
bool isValid(vec_t number);	

inline bool isFinite(vec_t number)	{ return _finite(number) != 0; }
inline bool isNaN(vec_t number)		{ return _isnan(number) != 0; }
inline bool isValid(vec_t number)	{ return _finite(number) != 0; }
} // namespace math


#endif//NUMERICALFUNCTIONS_H