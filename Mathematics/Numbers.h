#pragma once
#ifndef NUMBERS_H
#define NUMBERS_H

#include "Platform.h"

/**
<DEVELOPMENT STATUS>
Current Draft		:	0.0
Current Phase		:   DEVELOPMENT
Purpose				:	DEPLOYMENT
Unit Tested			:	YES
Used in development	:	YES
Used in experiments :	YES
Tested in the field	:	NO

\todo move this to the platform library
\todo examine the use of global const memory access cost
\todo move these to template math libs or macros

*/
namespace math
{
// integers 
/** max signed 1 byte integer */
extern const schar sint1_max;
/** max signed 1 byte integer */
extern const schar sint1_min;
/** max unsigned 1 byte integer */
extern const uchar uint1_max;
/** max signed 2 byte integer */
extern const sshort sint2_max;
/** max signed 2 byte integer */
extern const sshort sint2_min;
/** max unsigned 2 byte integer */
extern const ushort uint2_max;
/** max signed 4 byte integer */
extern const sint sint4_max;
/** max signed 4 byte integer */
extern const sint sint4_min;
/** max unsigned 4 byte integer */
extern const uint uint4_max;
/** max signed 8 byte integer */
extern const slong sint8_max;
/** max signed 8 byte integer */
extern const slong sint8_min;
/** max unsigned 8 byte integer */
extern const ulong uint8_max;

// real numbers
/** smallest x such that 1.0 + x != 1.0 */
extern const sreal real4_epsilon; 
/** largest 4 byte real number */
extern const sreal real4_max;
/** largest 4 byte real number < 0 */
extern const sreal real4_max_negative;
/** smallest 4 byte real number */
extern const sreal real4_min;
/** smallest 4 byte real number > 0 */
extern const sreal real4_min_positive;

/** smallest x such that 1.0 + x != 1.0 */
extern const dreal dreal_epsilon; 
/** largest 8 byte real number */
extern const dreal dreal_max;
/** largest 8 byte real number < 0 */
extern const dreal dreal_max_negative;
/** smallest 8 byte real number */
extern const dreal dreal_min;
/** smallest 8 byte real number > 0 */
extern const dreal dreal_min_positive;

// real pi numbers 
/** 2 / pi */
extern const sreal real4_2_inverse_pi;
/** 2 / sqrt(pi) */
extern const sreal real4_2_inverse_root_pi;
/** pi / 180.0 */
extern const sreal real4_degree_to_radian;
/** 1 / pi */
extern const sreal real4_inverse_pi;
/** pi / 2 */
extern const sreal real4_half_pi;
/** circumference over diameter */
extern const sreal real4_pi;
/** pi / 4 */
extern const sreal real4_qrtr_pi;
/** 180.0 / pi */
extern const sreal real4_radians_to_degrees;

/** 2 / pi */
extern const dreal dreal_2_inverse_pi;
/** 2 / sqrt(pi) */
extern const dreal dreal_2_inverse_root_pi;
/** pi / 180.0 */
extern const dreal dreal_degree_to_radian;
/** 1 / pi */
extern const dreal dreal_inverse_pi;
/** pi / 2 */
extern const dreal dreal_half_pi;
/** circumference over diameter */
extern const dreal dreal_pi;
/** pi / 4 */
extern const dreal dreal_qrtr_pi;
/** 180.0 / pi */
extern const dreal dreal_radians_to_degrees;

// real logarithm numbers 
/** value e such that the value f(x) = e^x is equal to the derivative of f at x */
extern const sreal real4_e;
/** log base 2 (e) */
extern const sreal real4_log2_e;
/** log base 10 (e) */
extern const sreal real4_log10_e;
/** ln 2 */
extern const sreal real4_ln_2;
/** ln 10 */
extern const sreal real4_ln_10;

/** value e such that the value f(x) = e^x is equal to the derivative of f at x */
extern const dreal dreal_e;
/** log base 2 (e) */
extern const dreal dreal_log2_e;
/** log base 10 (e) */
extern const dreal dreal_log10_e;
/** ln 2 */
extern const dreal dreal_ln_2;
/** ln 10 */
extern const dreal dreal_ln_10;

// real square root numbers 
/** sqrt(2) */
extern const sreal real4_root_2;
/** 1 / sqrt(2) */
extern const sreal real4_inverse_root_2;

/** sqrt(2) */
extern const dreal dreal_root_2;
/** 1 / sqrt(2) */
extern const dreal dreal_inverse_root_2;
} // namespace math

#endif//NUMBERS_H