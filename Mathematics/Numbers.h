#pragma once
#ifndef NUMBERS_H
#define NUMBERS_H

#include <float.h>
#include "Build.h"

namespace math
{
/** the vector element type */
typedef float vec_t;
/** for tolerance comparisons of vectors */
extern const vec_t	vectorTolerance;
/** circumference / diameter of a any circle */
extern const vec_t pi; 
} // namespace math

#endif//NUMBERS_H