#pragma once
#ifndef NUMBERS_H
#define NUMBERS_H

#include <float.h>
#include "Build.h"

namespace math
{
/** the vector element type */
typedef float vec_t;

/**
@ingroup Vectors
\def sqrtvec_t
defines the vector element square root function
*/
#define absvec_t		fabs
#define sqrtvec_t		sqrtf
#define logvec_t		logf

/** 
@ingroup Mathematics
for tolerance comparisons of vectors
*/
extern const vec_t	vectorTolerance;

/** 
@ingroup Mathematics
circumference / diameter of a any circle 
*/
extern const vec_t pi; 

bool isFinite(vec_t number); 
bool isNaN(vec_t number);	
bool isValid(vec_t number);	

// MS compiler
inline bool isFinite(vec_t number)	{ return _finite(number) != 0; }
inline bool isNaN(vec_t number)		{ return _isnan(number) != 0; }
inline bool isValid(vec_t number)	{ return _finite(number) != 0; }

} // namespace math

#endif//NUMBERS_H