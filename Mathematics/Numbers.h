#pragma once
#ifndef NUMBERS_H
#define NUMBERS_H

#include "Build.h"
/**
<DEVELOPMENT STATUS>
Current Draft		:	0.0
Current Phase		:   DEVELOPMENT
Purpose				:	DEPLOYMENT
Unit Tested			:	YES
Used in development	:	YES
Used in experiments :	YES
Tested in the field	:	NO
*/
namespace math
{
// integers 
/** max signed 1 byte integer */
extern const sint1 sint1_max;
/** max signed 1 byte integer */
extern const sint1 sint1_min;
/** max unsigned 1 byte integer */
extern const uint1 uint1_max;
/** max signed 2 byte integer */
extern const sint2 sint2_max;
/** max signed 2 byte integer */
extern const sint2 sint2_min;
/** max unsigned 2 byte integer */
extern const uint2 uint2_max;
/** max signed 4 byte integer */
extern const sint4 sint4_max;
/** max signed 4 byte integer */
extern const sint4 sint4_min;
/** max unsigned 4 byte integer */
extern const uint4 uint4_max;
/** max signed 8 byte integer */
extern const sint8 sint8_max;
/** max signed 8 byte integer */
extern const sint8 sint8_min;
/** max unsigned 8 byte integer */
extern const uint8 uint8_max;

// real numbers
/** smallest x such that 1.0 + x != 1.0 */
extern const real4 real4_epsilon; 
/** largest 4 byte real number */
extern const real4 real4_max;
/** largest 4 byte real number < 0 */
extern const real4 real4_max_negative;
/** smallest 4 byte real number */
extern const real4 real4_min;
/** smallest 4 byte real number > 0 */
extern const real4 real4_min_positive;

/** smallest x such that 1.0 + x != 1.0 */
extern const real8 real8_epsilon; 
/** largest 8 byte real number */
extern const real8 real8_max;
/** largest 8 byte real number < 0 */
extern const real8 real8_max_negative;
/** smallest 8 byte real number */
extern const real8 real8_min;
/** smallest 8 byte real number > 0 */
extern const real8 real8_min_positive;

// real pi numbers 
/** 2 / pi */
extern const real4 real4_2_inverse_pi;
/** 2 / sqrt(pi) */
extern const real4 real4_2_inverse_root_pi;
/** pi / 180.0 */
extern const real4 real4_degree_to_radian;
/** 1 / pi */
extern const real4 real4_inverse_pi;
/** pi / 2 */
extern const real4 real4_half_pi;
/** circumference over diameter */
extern const real4 real4_pi;
/** pi / 4 */
extern const real4 real4_qrtr_pi;
/** 180.0 / pi */
extern const real4 real4_radians_to_degrees;

/** 2 / pi */
extern const real8 real8_2_inverse_pi;
/** 2 / sqrt(pi) */
extern const real8 real8_2_inverse_root_pi;
/** pi / 180.0 */
extern const real8 real8_degree_to_radian;
/** 1 / pi */
extern const real8 real8_inverse_pi;
/** pi / 2 */
extern const real8 real8_half_pi;
/** circumference over diameter */
extern const real8 real8_pi;
/** pi / 4 */
extern const real8 real8_qrtr_pi;
/** 180.0 / pi */
extern const real8 real8_radians_to_degrees;

// real logarithm numbers 
/** value e such that the value f(x) = e^x is equal to the derivative of f at x */
extern const real4 real4_e;
/** log base 2 (e) */
extern const real4 real4_log2_e;
/** log base 10 (e) */
extern const real4 real4_log10_e;
/** ln 2 */
extern const real4 real4_ln_2;
/** ln 10 */
extern const real4 real4_ln_10;

/** value e such that the value f(x) = e^x is equal to the derivative of f at x */
extern const real8 real8_e;
/** log base 2 (e) */
extern const real8 real8_log2_e;
/** log base 10 (e) */
extern const real8 real8_log10_e;
/** ln 2 */
extern const real8 real8_ln_2;
/** ln 10 */
extern const real8 real8_ln_10;

// real square root numbers 
/** sqrt(2) */
extern const real4 real4_root_2;
/** 1 / sqrt(2) */
extern const real4 real4_inverse_root_2;

/** sqrt(2) */
extern const real8 real8_root_2;
/** 1 / sqrt(2) */
extern const real8 real8_inverse_root_2;
} // namespace math

#endif//NUMBERS_H