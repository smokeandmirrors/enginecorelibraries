#pragma once
#ifndef NUMBERS_H
#define NUMBERS_H

#include "Build.h"
/**
\warning WORK IN-PROGRESS! 
*/
namespace math
{
/** integers */
extern const sint1 sint1_max;
extern const sint1 sint1_min;
extern const uint1 uint1_max;
extern const sint2 sint2_max;
extern const sint2 sint2_min;
extern const uint2 uint2_max;
extern const sint4 sint4_max;
extern const sint4 sint4_min;
extern const uint4 uint4_max;
extern const sint8 sint8_max;
extern const sint8 sint8_min;
extern const uint8 uint8_max;

/** real numbers */
extern const real4 real4_epsilon; 
extern const real4 real4_max;
extern const real4 real4_max_negative;
extern const real4 real4_min;
extern const real4 real4_min_positive;

extern const real8 real8_epsilon; 
extern const real8 real8_max;
extern const real8 real8_max_negative;
extern const real8 real8_min;
extern const real8 real8_min_positive;

/** real pi numbers */
extern const real4 real4_2_inverse_pi;
extern const real4 real4_2_inverse_root_pi;
extern const real4 real4_degree_to_radian;
extern const real4 real4_inverse_pi;
extern const real4 real4_half_pi;
extern const real4 real4_pi;
extern const real4 real4_qrtr_pi;
extern const real4 real4_radians_to_degrees;

extern const real8 real8_2_inverse_pi;
extern const real8 real8_2_inverse_root_pi;
extern const real8 real8_degree_to_radian;
extern const real8 real8_inverse_pi;
extern const real8 real8_half_pi;
extern const real8 real8_pi;
extern const real8 real8_qrtr_pi;
extern const real8 real8_radians_to_degrees;

/** real logarithm numbers */
extern const real4 real4_e;
extern const real4 real4_log2_e;
extern const real4 real4_log10_e;
extern const real4 real4_ln_2;
extern const real4 real4_ln_10;

/** real square root numbers */
extern const real4 real4_root_2;
extern const real4 real4_inverse_root_2;
} // namespace math

#endif//NUMBERS_H