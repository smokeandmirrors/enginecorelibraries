#pragma once
#ifndef VECTOR_H
#define VECTOR_H
/**
\file Vector.h

2D and 3D vectors, which are exposed to %Lua, primarily for use in 
performance comparison.

\author Smoke and Mirrors Development
\htmlonly
<A HREF="smokeandmirrorsdevelopment@gmail.com">smokeandmirrorsdevelopment@gmail.com</A>
<BR>
&copy;2009-2011 Smoke and Mirrors Development
<BR>
\endhtmlonly
\date 2/18/2010

<DEVELOPMENT STATUS>
Current Draft		:	0.0
Current Phase		:   DEVELOPMENT
Purpose				:	DEPLOYMENT
Unit Tested			:	YES
Used in development	:	YES
Used in experiments :	YES
Tested in the field	:	NO

*/

/** 
\defgroup Mathematics Mathematics 
math classes, constants, functions and formulas
*/

/**
\defgroup Vectors Vectors
\ingroup Mathematics
Vector classes and operations
*/

#include <math.h>
#include <assert.h>

#include "Platform.h"
#include "Numbers.h"
#include "NumericalFunctions.h"

namespace math
{

template<typename T> class V2; 
template<typename T> class V3; 

typedef V2<float> Vector2;
typedef V3<float> Vector3;

typedef V2<sint> Pixel;

/** 
\defgroup Vector_Directions Directions
\ingroup Mathematics
directional shortcuts
@{
*/
extern const Vector2	down2D;
extern const Vector2	left2D;
extern const Vector2	origin2D;
extern const Vector2	right2D;
extern const Vector2	up2D;
extern const Vector3	down3D;
extern const Vector3	backward3D;
extern const Vector3	forward3D;
extern const Vector3	left3D;
extern const Vector3	origin3D;
extern const Vector3	right3D;
extern const Vector3	up3D;
/** @} end Vector_Directions */

/**
\class Vector2
\ingroup Vectors
a 2D Vector class with T elements
\warning The thread safety of this class is not guaranteed!
*/
template<typename T>
class V2 
{
public:
	// data
	T x;
	T y;
	// construction
	V2(void) 					
	{/* empty */}
	explicit V2(const V2<T>& v) : x(v.x), y(v.y)  
	{/* empty */}
	V2(T X, T Y) : x(X), y(Y)
	{/* empty */}
	explicit V2(T scalar) : x(scalar), y(scalar) 	
	{/* empty */}
	// \see normalized constructor below
	// access
	const T& 	operator[](uint i) const;	
	T& 			operator[](uint i);
	// addition 
	void 		add(T scalar);
	void 		add(T X, T Y);
	void 		add(const V2<T>& v);
	V2<T>& 		operator+=(const V2<T>& v);
	// distance to another
	T			distance(const V2<T>& v) const;
	T			distanceManhattan(const V2<T>& v) const;
	T 			distanceSqr(const V2<T>& v) const;
	bool		isFar(const V2<T>& v, T closest_range) const;
	bool		isNear(const V2<T>& v, T farthest_range) const;
	// division
	void 		divide(T scalar);
	void 		divide(T X, T Y);
	void 		divide(const V2<T>& v);
	V2<T>& 		operator/=(const V2<T>& v);
	// dot product 
	T 			dot(const V2<T>& v) const;
	// equality 
	bool 		equals(T X, T Y) const;
	bool		nearlyEquals(const V2<T>& v, T epsilon=vectorTolerance) const;
	bool 		notEquals(T X, T Y) const;
	bool 		operator==(const V2<T>& v) const;
	bool		operator!=(const V2<T>& v) const;
	// magnitude 
	T 			magnitude(void) const;
	T 			magnitudeSqr(void) const;
	// normalization 
	bool		isNormal(void) const;
	T 			normalize(void);
	// construction (normalized)
	V2(const V2<T>& v, bool /* ignored */) : x(v.x), y(v.y) 
	{ normalize(); }
	// multiplication & scaling 
	void		negate(void);
	void 		scale(T scalar);
	void 		scale(T X, T Y);
	void 		scale(const V2<T>& v);
	V2<T>& 		operator*=(const V2<T>& v);
	// mutation 
	void 		set(T scalar);
	void 		set(T X, T Y);
	void 		set(const V2<T>& v);
	void		set(uint index, T scalar);
	V2<T>& 		operator=(const V2<T>& v);
	// substraction 
	void 		subtract(T scalar);
	void 		subtract(T X, T Y);
	void 		subtract(const V2<T>& v);
	V2<T>& 		operator-=(const V2<T>& v);
	// zero, infinity and NaN
	bool		isValid(void) const;
	bool		isZero(void) const;
	void		zero(void);
}; // class Vector2

/**
\warning The thread safety of this class is not guaranteed!
*/
template<typename T>
class V3 
{
public:
	// data 
	T x;
	T y;
	T z;
	// construction 
	V3(void) 								
	{/* empty */}
	explicit V3(const V3<T>& v) : x(v.x), y(v.y), z(v.z) 			
	{/* empty */}
	V3(T X, T Y, T Z) : x(X), y(Y), z(Z) 					
	{/* empty */}
	explicit V3(T scalar) : x(scalar), y(scalar), z(scalar) 	
	{/* empty */}
	// \see normalized constructor below
	// access 
	const T& 	operator[](uint i) const;	
	T& 			operator[](uint i);
	// addition 
	void 		add(T scalar);
	void 		add(T X, T Y, T Z);
	void 		add(const V3<T>& v);	
	V3<T>& 		operator+=(const V3<T>& v);
	// cross product 
	void 		cross(const V3<T>& v);
	void 		cross(const V3<T>& a, const V3<T>& b);
	// perpendicular 
	void		perpendicular(void);
	// distance to another 
	T			distance(const V3<T>& v) const;
	T 			distanceSqr(const V3<T>& v) const;
	T 			distanceXY(const V3<T>& v) const;
	T 			distanceXYSqr(const V3<T>& v) const;
	bool		isFar(const V3<T>& v, T closest_range) const;
	bool		isFarXY(const V3<T>& v, T closest_range) const;
	bool		isNear(const V3<T>& v, T farthest_range) const;
	bool		isNearXY(const V3<T>& v, T farthest_range) const;
	// division 
	void 		divide(T scalar);
	void 		divide(T X, T Y, T Z);
	void 		divide(const V3<T>& v);
	V3<T>& 		operator/=(const V3<T>& v);
	// dot product 
	T 			dot(const V3<T>& v) const;
	// equality 
	bool 		equals(T X, T Y, T Z) const;
	bool		nearlyEquals(const V3<T>& v, T epsilon) const;
	bool		notEquals(T X, T Y, T Z) const;
	bool 		operator==(const V3<T>& v) const;
	bool 		operator!=(const V3<T>& v) const;
	// magnitude 
	T 			magnitude(void) const;
	T 			magnitudeSqr(void) const;
	T 			magnitudeXY(void) const;
	T 			magnitudeXYSqr(void) const;
	// normalization
	bool		isNormal(void) const;
	T 			normalize(void);
	// construction (normalized)
	V3(const V3<T>& v, bool /* ignored */) : x(v.x), y(v.y), z(v.z) 
	{ normalize(); }
	// multiplication & scaling 
	void 		negate(void);
	void 		scale(T scalar);
	void 		scale(T X, T Y, T Z);
	void 		scale(const V3<T>& v);
	V3<T>& 		operator*=(const V3<T>& v);
	// mutation 
	void 		set(T scalar);
	void 		set(T X, T Y, T Z);
	void 		set(const V3<T>& v);
	void		set(uint index, T scalar);
	V3<T>&		operator=(const V2<T>& v);
	V3<T>& 		operator=(const V3<T>& v);
	// substraction 
	void 		subtract(T scalar);
	void 		subtract(T X, T Y, T Z);
	void 		subtract(const V3<T>& v);
	V3<T>& 		operator-=(const V3<T>& v);
	// zero
	bool		isValid(void) const;
	bool		isZero(void) const;
	void		zero(void);
}; // class Vector3

void nativeVectorPerformance(uint iterations);

/** 
\defgroup Vector_Operations Operations
\ingroup Vectors
standard vector operations
@{
*/

/** 
\defgroup Vector_Accessors Acessors
array and function accessors 
@{
*/
template<typename T> inline const T& V2<T>::operator[](uint i) const
{
	assert(i < 2);
	return (&x)[i];
}
template<typename T> inline T& V2<T>::operator[](uint i)
{
	assert(i < 2);
	return (&x)[i];
}
template<typename T> inline const T& V3<T>::operator[](uint i) const
{
	assert(i < 3);
	return (&x)[i];
}
template<typename T> inline T& V3<T>::operator[](uint i)
{
	assert(i < 3);
	return (&x)[i];
}
/** @} end Vector_Access */

/** 
\defgroup Vector_Addition Addition
vector and scalar addition operations 
@{
*/
template<typename T> inline void V2<T>::add(T scalar)
{
	x += scalar;
	y += scalar;
}
template<typename T> inline void V2<T>::add(T X, T Y)
{
	x += X;
	y += Y;
}
template<typename T> inline void V2<T>::add(const V2<T>& v)
{
	x += v.x;
	y += v.y;
}
template<typename T> inline V2<T>& V2<T>::operator+=(const V2<T>& v)
{
	x += v.x;
	y += v.y;
	return *this;
}
template<typename T> inline void V3<T>::add(T scalar)
{
	x += scalar;
	y += scalar;
	z += scalar;
}
template<typename T> inline void V3<T>::add(T X, T Y, T Z)
{
	x += X;
	y += Y;
	z += Z;
}
template<typename T> inline void V3<T>::add(const V3<T>& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
}
template<typename T> inline V3<T>& V3<T>::operator+=(const V3<T>& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}
/** @} end Vector_Addition */

/** 
\defgroup Vector_CrossProduct Cross Product
\ingroup Vector_Operations
Vector Cross Product
@{
*/
template<typename T> inline void V3<T>::cross(const V3<T>& v)
{
	T a = y * v.z - z * v.y;
	T b = z * v.x - x * v.z;
	T c = x * v.y - y * v.x;
	x = a;
	y = b;
	z = c;
}
template<typename T> inline void V3<T>::cross(const V3<T>& a, const V3<T>& b)
{
	x = a.y * b.z - a.z * b.y;
	y = a.z * b.x - a.x * b.z;
	z = a.x * b.y - a.y * b.x;
}
template<typename T> inline void V3<T>::perpendicular(void)
{
	if (x != 0.0f || y != 0.0f)
	{
		cross(up3D);
	}
	else 
	{
		cross(right3D);
	}
}
/** @} end Vector_CrossProduct */

/** 
\defgroup Vector_Distance Distance
\ingroup Vector_Operations
distance to another vector
@{
*/
template<typename T> inline T V2<T>::distance(const V2<T>& v) const
{
	T x_dist = v.x - x;
	T y_dist = v.y - y;
	return sqrt(x_dist * x_dist + y_dist * y_dist);
}
template<typename T> inline T V2<T>::distanceManhattan(const V2<T>& v) const
{
	return abs(v.x - x) + abs(v.y - y);
}
template<typename T> inline T V2<T>::distanceSqr(const V2<T>& v) const
{
	T x_dist = v.x - x;
	T y_dist = v.y - y;
	return x_dist * x_dist + y_dist * y_dist;
}
template<typename T> inline bool V2<T>::isFar(const V2<T>& v, T closest_range) const
{
	T x_dist = v.x - x;
	T y_dist = v.y - y;
	return (x_dist * x_dist + y_dist * y_dist) > (closest_range * closest_range);
}
template<typename T> inline bool V2<T>::isNear(const V2<T>& v, T farthest_range) const
{
	T x_dist = v.x - x;
	T y_dist = v.y - y;
	return (x_dist * x_dist + y_dist * y_dist) <= (farthest_range * farthest_range);
}
template<typename T> inline T V3<T>::distance(const V3<T>& v) const
{
	T x_dist = v.x - x;
	T y_dist = v.y - y;
	T z_dist = v.z - z;
	return sqrt(x_dist * x_dist + y_dist * y_dist + z_dist * z_dist);
}
template<typename T> inline T V3<T>::distanceSqr(const V3<T>& v) const
{
	T x_dist = v.x - x;
	T y_dist = v.y - y;
	T z_dist = v.z - z;
	return x_dist * x_dist + y_dist * y_dist + z_dist * z_dist;
}
template<typename T> inline T V3<T>::distanceXY(const V3<T>& v) const
{
	T x_dist = v.x - x;
	T y_dist = v.y - y;
	return sqrt(x_dist * x_dist + y_dist * y_dist);
}
template<typename T> inline T V3<T>::distanceXYSqr(const V3<T>& v) const
{
	T x_dist = v.x - x;
	T y_dist = v.y - y;
	return x_dist * x_dist + y_dist * y_dist;
}
template<typename T> inline bool V3<T>::isFar(const V3<T>& v, T closest_range) const
{
	T x_dist = v.x - x;
	T y_dist = v.y - y;
	T z_dist = v.z - z;
	return (x_dist * x_dist + y_dist * y_dist + z_dist * z_dist) > (closest_range * closest_range);
}
template<typename T> inline bool V3<T>::isFarXY(const V3<T>& v, T closest_range) const
{
	T x_dist = v.x - x;
	T y_dist = v.y - y;
	return (x_dist * x_dist + y_dist * y_dist) > (closest_range * closest_range);
}
template<typename T> inline bool V3<T>::isNear(const V3<T>& v, T farthest_range) const
{
	T x_dist = v.x - x;
	T y_dist = v.y - y;
	T z_dist = v.z - z;
	return (x_dist * x_dist + y_dist * y_dist + z_dist * z_dist) <= (farthest_range * farthest_range);
}
template<typename T> inline bool V3<T>::isNearXY(const V3<T>& v, T farthest_range) const
{
	T x_dist = v.x - x;
	T y_dist = v.y - y;
	return (x_dist * x_dist + y_dist * y_dist) <= (farthest_range * farthest_range);
}
/** @} end Vector_Distance */


/** 
\defgroup Vector_Dot_Product Dot Product
\ingroup Vector_Operations
Vector dot product
@{
*/
template<typename T> inline T V2<T>::dot(const V2<T>& v) const
{
	return x * v.x + y * v.y;
}
template<typename T> inline T V3<T>::dot(const V3<T>& v) const
{
	return x * v.x + y * v.y + z * v.z;
}
/** @} end Vector_Dot_Product */

/** 
\defgroup Vector_Division Division
\ingroup Vector_Operations
scalar and per element division
@{
*/
template<typename T> inline void V2<T>::divide(T scalar)
{
	scalar = 1.0f / scalar; 
	x *= scalar;
	y *= scalar;
}
template<typename T> inline void V2<T>::divide(T X, T Y)
{
	x /= X;
	y /= Y;
}
template<typename T> inline void V2<T>::divide(const V2<T>& v)
{
	x /= v.x;
	y /= v.y;
}
template<typename T> inline V2<T>& V2<T>::operator/=(const V2<T>& v)
{
	x /= v.x;
	y /= v.y;
	return *this;
}
template<typename T> inline void V3<T>::divide(T scalar)
{
	scalar = 1.0f / scalar; 
	x *= scalar;
	y *= scalar;
	z *= scalar;
}
template<typename T> inline void V3<T>::divide(T X, T Y, T Z)
{
	x /= X;
	y /= Y;
	z /= Z;
}
template<typename T> inline void V3<T>::divide(const V3<T>& v)
{
	x /= v.x;
	y /= v.y;
	z /= v.z;
}
template<typename T> inline V3<T>& V3<T>::operator/=(const V3<T>& v)
{
	x /= v.x;
	y /= v.y;
	z /= v.z;
	return *this;
}
/** @} end Vector_Division */

/** 
\defgroup Vector_Equality Equality
\ingroup Vector_Operations
equality testing
@{
*/
template<typename T> inline bool V2<T>::equals(T X, T Y) const
{
	return x == X && y == Y;
}
template<typename T> inline bool V2<T>::nearlyEquals(const V2<T>& v, T epsilon) const
{
	return abs(x - v.x) <= epsilon && abs(y - v.y) <= epsilon;
}
template<typename T> inline bool V2<T>::notEquals(T X, T Y) const
{
	return x != X || y != Y;
}
template<typename T> inline bool V2<T>::operator==(const V2<T>& v) const
{	
	return x == v.x && y == v.y;
}
template<typename T> inline bool V2<T>::operator!=(const V2<T>& v) const
{	
	return x != v.x || y != v.y;
}
template<typename T> inline bool V3<T>::equals(T X, T Y, T Z) const
{
	return x == X && y == Y && z == Z;
}
template<typename T> inline bool V3<T>::nearlyEquals(const V3<T>& v, T epsilon) const
{
	return abs(x - v.x) <= epsilon && abs(y - v.y) <= epsilon && abs(z - v.z) <= epsilon;
}
template<typename T> inline bool V3<T>::notEquals(T X, T Y, T Z) const
{
	return x != X || y != Y || z != Z;
}
template<typename T> inline bool V3<T>::operator==(const V3<T>& v) const
{	
	return x == v.x && y == v.y && z == v.z;
}
template<typename T> inline bool V3<T>::operator!=(const V3<T>& v) const
{	
	return x != v.x || y != v.y || z != v.z;
}
/** @} end Vector_Equality */

/** 
\defgroup Vector_Magnitude Magnitude
\ingroup Vector_Operations
vector magnitude
@{
*/
template<typename T> inline T V2<T>::magnitude(void) const
{
	return sqrt(x * x + y * y);
}
template<typename T> inline T V2<T>::magnitudeSqr(void) const
{
	return x * x + y * y;
}
template<typename T> inline T V3<T>::magnitude(void) const
{
	return sqrt(x * x + y * y + z * z);
}
template<typename T> inline T V3<T>::magnitudeSqr(void) const
{
	return x * x + y * y + z * z;
}
template<typename T> inline T V3<T>::magnitudeXY(void) const
{
	return sqrt(x * x + y * y);
}
template<typename T> inline T V3<T>::magnitudeXYSqr(void) const
{
	return x * x + y * y;
}
/** @} end Vector_Magnitude */

/** 
\defgroup Vector_Normalization Normalization
\ingroup Vector_Operations
Vector Normalization
@{
*/
/** check for unit length of one */
template<typename T> inline bool V2<T>::isNormal(void) const
{
	return x * x + y * y == 1.0f;
}
/** check for unit length of one */
template<typename T> inline bool V3<T>::isNormal(void) const
{
	return x * x + y * y + z * z == 1.0f;
}
/** set unit length to one */
template<typename T> inline T V2<T>::normalize(void)
{
	T magnitude = sqrt(x * x + y * y);
	const T scalar = 1.0f / magnitude;
	x *= scalar;
	y *= scalar;
	return magnitude;
}
/** set unit length to one */
template<typename T> inline T V3<T>::normalize(void)
{
	T magnitude = sqrt(x * x + y * y + z * z);
	const T scalar = 1.0f / magnitude;
	x *= scalar;
	y *= scalar;
	z *= scalar;
	return magnitude;
}
/** @} Vector_Normalization */

/** 
\defgroup Vector_Scaling Scaling
\ingroup Vector_Operations
multiplication & scaling 
@{
*/
template<typename T> inline void V2<T>::scale(T scalar)
{
	x *= scalar;
	y *= scalar;
}
template<typename T> inline void V2<T>::scale(T X, T Y)
{
	x *= X;
	y *= Y;
}
template<typename T> inline void V2<T>::scale(const V2<T>& v)
{
	x *= v.x;
	y *= v.y;
}
template<typename T> inline V2<T>& V2<T>::operator*=(const V2<T>& v)
{
	x *= v.x;
	y *= v.y;
	return *this;
}
/** scale by -1 */
template<typename T> inline void V2<T>::negate(void)
{
	x *= -1.0f;
	y *= -1.0f;
}
template<typename T> inline void V3<T>::scale(T scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
}
template<typename T> inline void V3<T>::scale(T X, T Y, T Z)
{
	x *= X;
	y *= Y;
	z *= Z;
}
template<typename T> inline void V3<T>::scale(const V3<T>& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
}
template<typename T> inline V3<T>& V3<T>::operator*=(const V3<T>& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
	return *this;
}
/** scale by -1 */
template<typename T> inline void V3<T>::negate(void)
{
	x *= -1.0f;
	y *= -1.0f;
	z *= -1.0f;
}
/** @} end Vector_Scaling */

/** 
\defgroup Vector_Substraction Substraction
\ingroup Vector_Operations
Vector Substraction
@{
*/
template<typename T> inline void V2<T>::subtract(T scalar)
{
	x -= scalar;
	y -= scalar;
}
template<typename T> inline void V2<T>::subtract(T X, T Y)
{
	x -= X;
	y -= Y;
}
template<typename T> inline void V2<T>::subtract(const V2<T>& v)
{
	x -= v.x;
	y -= v.y;
}
template<typename T> inline V2<T>& V2<T>::operator-=(const V2<T>& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}
template<typename T> inline void V3<T>::subtract(T scalar)
{
	x -= scalar;
	y -= scalar;
	z -= scalar;
}
template<typename T> inline void V3<T>::subtract(T X, T Y, T Z)
{
	x -= X;
	y -= Y;
	z -= Z;
}
template<typename T> inline void V3<T>::subtract(const V3<T>& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
}
template<typename T> inline V3<T>& V3<T>::operator-=(const V3<T>& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}
/** @} Vector_Substraction */

/** 
\defgroup Vector_Mutatators Mutatators
\ingroup Vector_Operations
Vector Mutatators
@{
*/
template<typename T> inline void V2<T>::set(T scalar)
{
	x = scalar;
	y = scalar;
}
template<typename T> inline void V2<T>::set(T X, T Y)
{
	x = X;
	y = Y;
}
template<typename T> inline void V2<T>::set(const V2<T>& v)
{
	*this = v;
}
template<typename T> inline V2<T>& V2<T>::operator=(const V2<T>& v) 
{
	x = v.x;
	y = v.y;
	return *this;
}
template<typename T> inline void V2<T>::set(uint index, T scalar)
{
	switch (index)
	{
	case 0: x = scalar;
	case 1: y = scalar;
	default: assert(false);
	}
}
template<typename T> inline void V3<T>::set(T scalar)
{
	x = scalar;
	y = scalar;
	z = scalar;
}
template<typename T> inline void V3<T>::set(T X, T Y, T Z)
{
	x = X;
	y = Y;
	z = Z;
}
template<typename T> inline void V3<T>::set(const V3<T>& v)
{
	*this = v;
}
template<typename T> inline V3<T>& V3<T>::operator=(const V3<T>& v) 
{
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}
template<typename T> inline V3<T>& V3<T>::operator=(const V2<T>& v)
{
	x = v.x;
	y = v.y;
	return *this;
}
template<typename T> inline void V3<T>::set(uint index, T scalar)
{
	switch (index)
	{
	case 0: x = scalar;
	case 1: y = scalar;
	case 2: z = scalar;
	default: assert(false);
	}
}
/** @} end Vector_Mutators */
/** 
\defgroup Vector_Zero Zero
\ingroup Vector_Operations
Vector Mutatators
@{
*/
template<typename T> inline bool V2<T>::isValid() const
{
	return math::isValid(x) 
		&& math::isValid(y);
}
template<typename T> inline bool V3<T>::isValid() const
{
	return math::isValid(x) 
		&& math::isValid(y) 
		&& math::isValid(z);
}
template<typename T> inline bool V2<T>::isZero() const
{
	return x == 0.0f 
		&& y == 0.0f;
}
template<typename T> inline bool V3<T>::isZero() const
{
	return x == 0.0f 
		&& y == 0.0f 
		&& z == 0.0f;
}
template<typename T> inline void V2<T>::zero() 
{
	y = x = 0.0f;
}
template<typename T> inline void V3<T>::zero() 
{
	z = y = x = 0.0f;
}
/** @} end Vector_Zero */
/** @} end Vector_Operations */

} // end namespace math

#endif//VECTOR_H
