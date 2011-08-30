#include <float.h>
#include <limits.h>
#include <math.h>
#include <cmath>
#include <stdlib.h>
#include "Numbers.h"

namespace math 
{
/** integers */
const schar sint1_max						= SCHAR_MAX;
const schar sint1_min						= SCHAR_MIN;
const uchar uint1_max						= UCHAR_MAX;
const sshort sint2_max						= SHRT_MAX;
const sshort sint2_min						= SHRT_MIN;
const ushort uint2_max						= USHRT_MAX;
const sint sint4_max						= INT_MAX;
const sint sint4_min						= INT_MIN;
const uint uint4_max						= UINT_MAX;
const slong sint8_max						= LLONG_MAX;
const slong sint8_min						= LLONG_MIN;
const ulong uint8_max						= ULLONG_MAX;

/** real numbers */
const sreal real4_epsilon					= FLT_EPSILON; 
const sreal real4_max						= FLT_MAX;
const sreal real4_max_negative				= 0.0f - FLT_EPSILON; // _nextafterf(0.0f, -1.0f);
const sreal real4_min						= FLT_MIN;
const sreal real4_min_positive				= 0.0f + FLT_EPSILON; // _nextafterf(0.0f, 1.0f);

const dreal dreal_epsilon					= DBL_EPSILON; 
const dreal dreal_max						= DBL_MAX;
const dreal dreal_max_negative				= 0.0 - DBL_EPSILON; // _nextafter(0.0, -1.0);
const dreal dreal_min						= DBL_MIN;
const dreal dreal_min_positive				= 0.0 + DBL_EPSILON; // _nextafter(0.0, 1.0);

/** real pi numbers */
const sreal real4_2_inverse_pi				= static_cast<sreal>(0.636619772367581343076);
const sreal real4_2_inverse_root_pi			= static_cast<sreal>(1.12837916709551257390);
const sreal real4_degree_to_radian			= static_cast<sreal>(3.14159265358979323846 / 180.0);
const sreal real4_inverse_pi				= static_cast<sreal>(0.318309886183790671538);
const sreal real4_half_pi					= static_cast<sreal>(1.57079632679489661923);
const sreal real4_pi						= static_cast<sreal>(3.14159265358979323846);
const sreal real4_qrtr_pi					= static_cast<sreal>(0.785398163397448309616);
const sreal real4_radians_to_degrees		= static_cast<sreal>(3.14159265358979323846 / 180.0);

const dreal dreal_2_inverse_pi				= 0.636619772367581343076;
const dreal dreal_2_inverse_root_pi			= 1.12837916709551257390;
const dreal dreal_degree_to_radian			= 3.14159265358979323846 / 180.0;
const dreal dreal_inverse_pi				= 0.318309886183790671538;
const dreal dreal_half_pi					= 1.57079632679489661923;
const dreal dreal_pi						= 3.14159265358979323846;
const dreal dreal_qrtr_pi					= 0.785398163397448309616;
const dreal dreal_radians_to_degrees		= 3.14159265358979323846 / 180.0;

/** real logarithm numbers */
const sreal real4_e							= static_cast<sreal>(2.71828182845904523536);
const sreal real4_log2_e					= static_cast<sreal>(1.44269504088896340736);
const sreal real4_log10_e					= static_cast<sreal>(0.434294481903251827651);
const sreal real4_ln_2						= static_cast<sreal>(0.693147180559945309417);
const sreal real4_ln_10						= static_cast<sreal>(2.30258509299404568402);

const dreal dreal_e							= 2.71828182845904523536;
const dreal dreal_log2_e					= 1.44269504088896340736;
const dreal dreal_log10_e					= 0.434294481903251827651;
const dreal dreal_ln_2						= 0.693147180559945309417;
const dreal dreal_ln_10						= 2.30258509299404568402;

/** real square root numbers */
const sreal real4_root_2					= static_cast<sreal>(1.41421356237309504880);
const sreal real4_inverse_root_2			= static_cast<sreal>(0.707106781186547524401);

const dreal dreal_root_2					= 1.41421356237309504880;
const dreal dreal_inverse_root_2			= 0.707106781186547524401;
} // namespace math