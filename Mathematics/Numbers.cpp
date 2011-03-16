#include <float.h>
#include <limits.h>
#include <math.h>
#include <cmath>
#include <stdlib.h>
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
const real4 real4_max_negative				= 0.0f - FLT_EPSILON; // _nextafterf(0.0f, -1.0f);
const real4 real4_min						= FLT_MIN;
const real4 real4_min_positive				= 0.0f + FLT_EPSILON; // _nextafterf(0.0f, 1.0f);

const real8 real8_epsilon					= DBL_EPSILON; 
const real8 real8_max						= DBL_MAX;
const real8 real8_max_negative				= 0.0 - DBL_EPSILON; // _nextafter(0.0, -1.0);
const real8 real8_min						= DBL_MIN;
const real8 real8_min_positive				= 0.0 + DBL_EPSILON; // _nextafter(0.0, 1.0);

/** real pi numbers */
const real4 real4_2_inverse_pi				= static_cast<real4>(0.636619772367581343076);
const real4 real4_2_inverse_root_pi			= static_cast<real4>(1.12837916709551257390);
const real4 real4_degree_to_radian			= static_cast<real4>(3.14159265358979323846 / 180.0);
const real4 real4_inverse_pi				= static_cast<real4>(0.318309886183790671538);
const real4 real4_half_pi					= static_cast<real4>(1.57079632679489661923);
const real4 real4_pi						= static_cast<real4>(3.14159265358979323846);
const real4 real4_qrtr_pi					= static_cast<real4>(0.785398163397448309616);
const real4 real4_radians_to_degrees		= static_cast<real4>(3.14159265358979323846 / 180.0);

const real8 real8_2_inverse_pi				= 0.636619772367581343076;
const real8 real8_2_inverse_root_pi			= 1.12837916709551257390;
const real8 real8_degree_to_radian			= 3.14159265358979323846 / 180.0;
const real8 real8_inverse_pi				= 0.318309886183790671538;
const real8 real8_half_pi					= 1.57079632679489661923;
const real8 real8_pi						= 3.14159265358979323846;
const real8 real8_qrtr_pi					= 0.785398163397448309616;
const real8 real8_radians_to_degrees		= 3.14159265358979323846 / 180.0;

/** real logarithm numbers */
const real4 real4_e							= static_cast<real4>(2.71828182845904523536);
const real4 real4_log2_e					= static_cast<real4>(1.44269504088896340736);
const real4 real4_log10_e					= static_cast<real4>(0.434294481903251827651);
const real4 real4_ln_2						= static_cast<real4>(0.693147180559945309417);
const real4 real4_ln_10						= static_cast<real4>(2.30258509299404568402);

const real8 real8_e							= 2.71828182845904523536;
const real8 real8_log2_e					= 1.44269504088896340736;
const real8 real8_log10_e					= 0.434294481903251827651;
const real8 real8_ln_2						= 0.693147180559945309417;
const real8 real8_ln_10						= 2.30258509299404568402;

/** real square root numbers */
const real4 real4_root_2					= static_cast<real4>(1.41421356237309504880);
const real4 real4_inverse_root_2			= static_cast<real4>(0.707106781186547524401);

const real8 real8_root_2					= 1.41421356237309504880;
const real8 real8_inverse_root_2			= 0.707106781186547524401;
} // namespace math