#include <float.h>
#include <limits.h>
#include <math.h>
#include "Numbers.h"

namespace math 
{
/** integers */
const sint1 sint1_max						= SCHAR_MAX;
const sint1 sint1_min						= SCHAR_MIN;
const uint1 uint1_max						= UCHAR_MAX;
const sint2 sint2_max						= SHRT_MAX;
const sint2 sint2_min						= SHRT_MIN;
const uint2 uint2_max						= USHRT_MAX;
const sint4 sint4_max						= INT_MAX;
const sint4 sint4_min						= INT_MIN;
const uint4 uint4_max						= UINT_MAX;
const sint8 sint8_max						= LLONG_MAX;
const sint8 sint8_min						= LLONG_MIN;
const uint8 uint8_max						= ULLONG_MAX;

/** real numbers */
const real4 real4_epsilon					= FLT_EPSILON; 
const real4 real4_max						= FLT_MAX;
const real4 real4_max_negative				= 0.0f - real4_epsilon;
const real4 real4_min						= FLT_MIN;
const real4 real4_min_positive				= -real4_max;

const real8 real8_epsilon					= DBL_EPSILON; 
const real8 real8_max						= DBL_MAX;
const real8 real8_max_negative				= 0.0f - real8_epsilon;
const real8 real8_min						= DBL_MIN;
const real8 real8_min_positive				= -real8_max;

/** real pi numbers */
const real8 real8_2_inverse_pi				= 0.636619772367581343076;
const real8 real8_2_inverse_root_pi			= 1.12837916709551257390;
const real8 real8_degree_to_radian			= 3.14159265358979323846 / 180.0;
const real8 real8_inverse_pi				= 0.318309886183790671538;
const real8 real8_half_pi					= 1.57079632679489661923;
const real8 real8_pi						= 3.14159265358979323846;
const real8 real8_qrtr_pi					= 0.785398163397448309616;
const real8 real8_radians_to_degrees		= 3.14159265358979323846 / 180.0;

const real4 real4_2_inverse_pi				= static_cast<real4>(0.636619772367581343076);
const real4 real4_2_inverse_root_pi			= static_cast<real4>(1.12837916709551257390);
const real4 real4_degree_to_radian			= static_cast<real4>(3.14159265358979323846 / 180.0);
const real4 real4_inverse_pi				= static_cast<real4>(0.318309886183790671538);
const real4 real4_half_pi					= static_cast<real4>(1.57079632679489661923);
const real4 real4_pi						= static_cast<real4>(3.14159265358979323846);
const real4 real4_qrtr_pi					= static_cast<real4>(0.785398163397448309616);
const real4 real4_radians_to_degrees		= static_cast<real4>(3.14159265358979323846 / 180.0);

/** real logarithm numbers */
//const real8 real8_e;
//const real8 real8_log2_e;
//const real8 real8_log10_e;
//const real8 real8_ln_2;
//const real8 real8_ln_10;
//
//const real4 real4_e;
//const real4 real4_log2_e;
//const real4 real4_log10_e;
//const real4 real4_ln_2;
//const real4 real4_ln_10;
//
///** real square root numbers */
//const real8 real8_root_2;
//const real8 real8_inverse_root_2;
//
//const real4 real4_root_2;
//const real4 real4_inverse_root_2;
} // namespace math