#pragma once
#ifndef VECTOR_H
#define VECTOR_H

/**
@file Vector.h
Vector definitions mostly for performance testing on a lua library
extention.  That is, I want to see if it would be faster to have 
any or all vector operations implemented in C.  Previously, testing
has revealed that at least complicated operations benefit, but 
that simple operations may not be worth it.

@author Smoke and Mirrors Development
copyright 2010 Smoke and Mirrors Development
smokeandmirrorsdevelopment@gmail.com

@date 2/18/2010
*/

/** 
@defgroup Mathematics Mathematics 
Math classes, constants, functions and formulas
*/

/**
@defgroup Vectors Vectors
@ingroup Mathematics
Vector classes and operations
*/

#include <math.h>
#include <assert.h>

#include "Build.h"

/**
@ingroup Vectors
\def sqrtvec_t
defines the vector element square root function
*/
#define sqrtvec_t sqrtf

typedef float vec_t;

/** 
@ingroup Mathematics
for tolerance comparisons of vectors
*/
extern const vec_t		vectorTolerance;

class Vector2;
class Vector3;

/** 
@defgroup Vector_Directions Directions
@ingroup Mathematics
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
@class Vector2
@ingroup Vectors
a 2D Vector class with vec_t elements
*/
class Vector2 
{
public:
	// data
	vec_t x;
	vec_t y;
	// construction
	Vector2() 					{/* empty */}
	Vector2(const Vector2& v) 
		: x(v.x), y(v.y) 		{/* empty */}
	Vector2(vec_t X, vec_t Y) 
		: x(X), y(Y)  			{/* empty */}
	Vector2(vec_t scalar) 
		: x(scalar), y(scalar) 	{/* empty */}
	// access
	const vec_t& 	operator[](uint i) const;	
	vec_t 			operator[](uint i);
	// addition 
	void 			add(vec_t scalar);
	void 			add(vec_t X, vec_t Y);
	void 			add(const Vector2& v);
	/** \warning abuse may be slow! */
	const Vector2 	operator+(const Vector2& v) const; 
	Vector2& 		operator+=(const Vector2& v);
	// distance to another
	vec_t			distanceTo(const Vector2& v) const;
	vec_t 			distanceToSqrd(const Vector2& v) const;
	bool			isFarFrom(const Vector2& v, vec_t closest_range) const;
	bool			isNearTo(const Vector2& v, vec_t farthest_range) const;
	// division
	void 			divide(vec_t scalar);
	void 			divide(vec_t X, vec_t Y);
	void 			divide(const Vector2& v);
	/** \warning abuse may be slow! */
	const Vector2 	operator/(const Vector2& v) const; 
	Vector2& 		operator/=(const Vector2& v);
	// dot product 
	vec_t 			dot(const Vector2& v) const;
	// equality 
	bool 			equals(const Vector2& v) const;
	bool 			equals(vec_t X, vec_t Y) const;
	bool			nearlyEquals(const Vector2& v, vec_t epsilon=vectorTolerance) const;
	bool 			operator==(const Vector2& v) const;
	// magnitude 
	vec_t 			magnitude(void) const;
	vec_t 			magnitudeSqrd(void) const;
	// normalization 
	bool			isNormal(void) const;
	vec_t 			normalize(void);
	// multiplication & scaling 
	const Vector2& 	negate(void);
	void 			scale(vec_t scalar);
	void 			scale(vec_t X, vec_t Y);
	void 			scale(const Vector2& v);
	const Vector2 	operator*(const Vector2& v) const; 
	Vector2& 		operator*=(const Vector2& v);
	// mutation 
	void 			set(vec_t scalar);
	void 			set(vec_t X, vec_t Y);
	void 			set(const Vector2& v);
	void			set(sint index, vec_t scalar);
	Vector2& 		operator=(const Vector2& v);
	// substraction 
	void 			substract(vec_t scalar);
	void 			substract(vec_t X, vec_t Y);
	void 			substract(const Vector2& v);
	/** \warning abuse may be slow! */
	const Vector2 	operator-(const Vector2& v) const; 
	Vector2& 		operator-=(const Vector2& v);
	// zero
	bool			isZero(void) const;
	void			zero(void);
}; // class Vector2

class Vector3 
{
public:
	// data 
	vec_t x;
	vec_t y;
	vec_t z;
	// construction 
	Vector3() 								{/* empty */}
	Vector3(const Vector3& v) 
		: x(v.x), y(v.y), z(v.z) 			{/* empty */}
	Vector3(vec_t X, vec_t Y, vec_t Z) 
		: x(X), y(Y), z(Z) 					{/* empty */}
	Vector3(vec_t scalar) 
		: x(scalar), y(scalar), z(scalar) 	{/* empty */}
	// \see normalized constructor below
	// Vector3(const Vector3& v, bool /* IGNORED */);
	// 	: x(v.x), y(v.y), z(v.z) 			{/* empty */}
	// access 
	const vec_t& 	operator[](uint i) const;	
	vec_t 			operator[](uint i);
	// addition 
	void 			add(vec_t scalar);
	void 			add(vec_t X, vec_t Y, vec_t Z);
	void 			add(const Vector3& v);	
	/** \warning abuse may be slow! */
	const Vector3 	operator+(const Vector3& v) const; 
	Vector3& 		operator+=(const Vector3& v);
	// cross product 
	void 			cross(const Vector3& v);
	void 			cross(const Vector3& a, const Vector3& b);
	Vector3 		getCross(const Vector3& v) const;
	// distance to another 
	vec_t			distanceTo(const Vector3& v) const;
	vec_t 			distanceToSqrd(const Vector3& v) const;
	vec_t 			distanceToXY(const Vector3& v) const;
	vec_t 			distanceToXYSqrd(const Vector3& v) const;
	bool			isFarFrom(const Vector3& v, vec_t closest_range) const;
	bool			isFarFromXY(const Vector3& v, vec_t closest_range) const;
	bool			isNearTo(const Vector3& v, vec_t farthest_range) const;
	bool			isNearToXY(const Vector3& v, vec_t farthest_range) const;
	// division 
	void 			divide(vec_t scalar);
	void 			divide(vec_t X, vec_t Y, vec_t Z);
	void 			divide(const Vector3& v);
	/** \warning abuse may be slow! */
	const Vector3 	operator/(const Vector3& v) const; 
	Vector3& 		operator/=(const Vector3& v);
	// dot product 
	vec_t 			dot(const Vector3& v) const;
	// equality 
	bool 			equals(const Vector3& v) const;
	bool 			equals(vec_t X, vec_t Y, vec_t Z) const;
	bool			nearlyEquals(const Vector3& v, vec_t epsilon=vectorTolerance) const;
	bool 			operator==(const Vector3& v) const;
	// perpendicular 
	Vector3			getPerpendicular(void) const;
	// magnitude 
	vec_t 			magnitude(void) const;
	vec_t 			magnitudeSqrd(void) const;
	vec_t 			magnitudeXY(void) const;
	vec_t 			magnitudeXYSqrd(void) const;
	// normalization
	vec_t 			normalize(void);
	bool			isNormal(void) const;
	// construction (normalized)
	Vector3(const Vector3& v, bool /* IGNORED */)
		: x(v.x), y(v.y), z(v.z) { normalize(); }
	// multiplication & scaling 
	const Vector3& 	negate(void);
	void 			scale(vec_t scalar);
	void 			scale(vec_t X, vec_t Y, vec_t Z);
	void 			scale(const Vector3& v);
	/** \warning abuse may be slow! */
	const Vector3 	operator*(const Vector3& v) const;
	Vector3& 		operator*=(const Vector3& v);
	// mutation 
	void 			set(vec_t scalar);
	void 			set(vec_t X, vec_t Y, vec_t Z);
	void 			set(const Vector3& v);
	void			set(sint index, vec_t scalar);
	Vector3& 		operator=(const Vector3& v);
	// substraction 
	void 			substract(vec_t scalar);
	void 			substract(vec_t X, vec_t Y, vec_t Z);
	void 			substract(const Vector3& v);
	/** \warning abuse may be slow! */
	const Vector3 	operator-(const Vector3& v) const; 
	Vector3& 		operator-=(const Vector3& v);
	// zero
	bool			isZero(void) const;
	void			zero(void);
}; // class Vector3

/** 
@defgroup Vector_Operations Operations
@ingroup Vectors
standard vector operations
@{
*/


/** 
@defgroup Vector_Accessors Acessors
array and function accessors 
@{
*/
inline const vec_t& Vector2::operator[](uint i) const
{
	assert(i < 2);
	return (&x)[i];
}
inline vec_t Vector2::operator[](uint i)
{
	assert(i < 2);
	return (&x)[i];
}
inline const vec_t& Vector3::operator[](uint i) const
{
	assert(i < 3);
	return (&x)[i];
}
inline vec_t Vector3::operator[](uint i)
{
	assert(i < 3);
	return (&x)[i];
}
/** @} end Vector_Access */

/** 
@defgroup Vector_Addition Addition
vector and scalar addition operations 
@{
*/
inline void Vector2::add(vec_t scalar)
{
	x += scalar;
	y += scalar;
}
inline void Vector2::add(vec_t X, vec_t Y)
{
	x += X;
	y += Y;
}
inline void Vector2::add(const Vector2& v)
{
	x += v.x;
	y += v.y;
}
inline const Vector2 Vector2::operator+(const Vector2& v) const
{	// warning: abuse can be slow!
	return Vector2(x + v.x, y + v.y);
}
inline Vector2& Vector2::operator+=(const Vector2& v)
{
	x += v.x;
	y += v.y;
	return *this;
}
inline void Vector3::add(vec_t scalar)
{
	x += scalar;
	y += scalar;
	z += scalar;
}
inline void Vector3::add(vec_t X, vec_t Y, vec_t Z)
{
	x += X;
	y += Y;
	z += Z;
}
inline void Vector3::add(const Vector3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
}
inline const Vector3 Vector3::operator+(const Vector3& v) const
{	// warning: abuse can be slow!
	return Vector3(x + v.x, y + v.y, z + v.z);
}
inline Vector3& Vector3::operator+=(const Vector3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}
/** @} end Vector_Addition */

/** 
@defgroup Vector_CrossProduct Cross Product
@ingroup Vector_Operations
Vector Cross Product
@{
*/
inline void Vector3::cross(const Vector3& v)
{
	vec_t a = y * v.z - z * v.y;
	vec_t b = z * v.x - x * v.z;
	vec_t c = x * v.y - y * v.x;
	x = a;
	y = b;
	z = c;
}
inline void Vector3::cross(const Vector3& a, const Vector3& b)
{
	x = a.y * b.z - a.z * b.y;
	y = a.z * b.x - a.x * b.z;
	z = a.x * b.y - a.y * b.x;
}
inline Vector3 Vector3::getCross(const Vector3& v) const
{
	vec_t a = y * v.z - z * v.y;
	vec_t b = z * v.x - x * v.z;
	vec_t c = x * v.y - y * v.x;
	return Vector3(a,b,c);
}

inline Vector3 Vector3::getPerpendicular(void) const
{
	if ((x != 0.0f || y != 0.0f))
	{
		return getCross(up3D);
	}
	else 
	{
		return getCross(right3D);
	}
}
/** @} end Vector_CrossProduct */

/** 
@defgroup Vector_Distance Distance
@ingroup Vector_Operations
distance to another vector
@{
*/
inline vec_t Vector2::distanceTo(const Vector2& v) const
{
	vec_t x_dist = v.x - x;
	vec_t y_dist = v.y - y;
	return sqrtvec_t(x_dist * x_dist + y_dist * y_dist);
}
inline vec_t Vector2::distanceToSqrd(const Vector2& v) const
{
	vec_t x_dist = v.x - x;
	vec_t y_dist = v.y - y;
	return x_dist * x_dist + y_dist * y_dist;
}
inline bool Vector2::isFarFrom(const Vector2& v, vec_t closest_range) const
{
	vec_t x_dist = v.x - x;
	vec_t y_dist = v.y - y;
	return (x_dist * x_dist + y_dist * y_dist) > (closest_range * closest_range);
}
inline bool Vector2::isNearTo(const Vector2& v, vec_t farthest_range) const
{
	vec_t x_dist = v.x - x;
	vec_t y_dist = v.y - y;
	return (x_dist * x_dist + y_dist * y_dist) <= (farthest_range * farthest_range);
}
inline vec_t Vector3::distanceTo(const Vector3& v) const
{
	vec_t x_dist = v.x - x;
	vec_t y_dist = v.y - y;
	vec_t z_dist = v.z - z;
	return sqrtvec_t(x_dist * x_dist + y_dist * y_dist + z_dist * z_dist);
}
inline vec_t Vector3::distanceToSqrd(const Vector3& v) const
{
	vec_t x_dist = v.x - x;
	vec_t y_dist = v.y - y;
	vec_t z_dist = v.z - z;
	return x_dist * x_dist + y_dist * y_dist + z_dist * z_dist;
}
inline vec_t Vector3::distanceToXY(const Vector3& v) const
{
	vec_t x_dist = v.x - x;
	vec_t y_dist = v.y - y;
	return sqrtvec_t(x_dist * x_dist + y_dist * y_dist);
}
inline vec_t Vector3::distanceToXYSqrd(const Vector3& v) const
{
	vec_t x_dist = v.x - x;
	vec_t y_dist = v.y - y;
	return x_dist * x_dist + y_dist * y_dist;
}
inline bool Vector3::isFarFrom(const Vector3& v, vec_t closest_range) const
{
	vec_t x_dist = v.x - x;
	vec_t y_dist = v.y - y;
	vec_t z_dist = v.z - z;
	return (x_dist * x_dist + y_dist * y_dist + z_dist * z_dist) > (closest_range * closest_range);
}
inline bool Vector3::isFarFromXY(const Vector3& v, vec_t closest_range) const
{
	vec_t x_dist = v.x - x;
	vec_t y_dist = v.y - y;
	return (x_dist * x_dist + y_dist * y_dist) > (closest_range * closest_range);
}
inline bool Vector3::isNearTo(const Vector3& v, vec_t farthest_range) const
{
	vec_t x_dist = v.x - x;
	vec_t y_dist = v.y - y;
	vec_t z_dist = v.z - z;
	return (x_dist * x_dist + y_dist * y_dist + z_dist * z_dist) <= (farthest_range * farthest_range);
}
inline bool Vector3::isNearToXY(const Vector3& v, vec_t farthest_range) const
{
	vec_t x_dist = v.x - x;
	vec_t y_dist = v.y - y;
	return (x_dist * x_dist + y_dist * y_dist) <= (farthest_range * farthest_range);
}
/** @} end Vector_Distance */


/** 
@defgroup Vector_Dot_Product Dot Product
@ingroup Vector_Operations
Vector dot product
@{
*/
inline vec_t Vector2::dot(const Vector2& v) const
{
	return x * v.x + y * v.y;
}
inline vec_t Vector3::dot(const Vector3& v) const
{
	return x * v.x + y * v.y + z * v.z;
}
/** @} end Vector_Dot_Product */

/** 
@defgroup Vector_Division Division
@ingroup Vector_Operations
scalar and per element division
@{
*/
inline void Vector2::divide(vec_t scalar)
{
	assert(scalar != 0.0f);
	scalar = 1.0f / scalar; //@ todo performance test
	x *= scalar;
	y *= scalar;
}
inline void Vector2::divide(vec_t X, vec_t Y)
{
	assert(X != 0.0f && Y != 0.0f);
	x /= X;
	y /= Y;
}
inline void Vector2::divide(const Vector2& v)
{
	assert(v.x != 0.0f && v.y != 0.0f);
	x /= v.x;
	y /= v.y;
}
inline const Vector2 Vector2::operator/(const Vector2& v) const
{	// warning: abuse can be slow!
	assert(v.x != 0.0f && v.y != 0.0f);
	return Vector2(x / v.x, y / v.y);
}
inline Vector2& Vector2::operator/=(const Vector2& v)
{
	assert(v.x != 0.0f && v.y != 0.0f);
	x /= v.x;
	y /= v.y;
	return *this;
}
inline void Vector3::divide(vec_t scalar)
{
	assert(scalar != 0.0f);
	scalar = 1.0f / scalar; // @todo performance test
	x *= scalar;
	y *= scalar;
	z *= scalar;
}
inline void Vector3::divide(vec_t X, vec_t Y, vec_t Z)
{
	assert(X != 0.0f && Y != 0.0f && Z != 0.0f);
	x /= X;
	y /= Y;
	z /= Z;
}
inline void Vector3::divide(const Vector3& v)
{
	assert(v.x != 0.0f && v.y != 0.0f && v.z != 0.0f);
	x /= v.x;
	y /= v.y;
	z /= v.z;
}
inline const Vector3 Vector3::operator/(const Vector3& v) const
{	// warning: abuse can be slow!
	assert(v.x != 0.0f && v.y != 0.0f && v.z != 0.0f);
	return Vector3(x / v.x, y / v.y, z / v.z);
}
inline Vector3& Vector3::operator/=(const Vector3& v)
{
	assert(v.x != 0.0f && v.y != 0.0f && v.z != 0.0f);
	x /= v.x;
	y /= v.y;
	z /= v.z;
	return *this;
}
/** @} end Vector_Division */

/** 
@defgroup Vector_Equality Equality
@ingroup Vector_Operations
equality testing
@{
*/
inline bool Vector2::equals(const Vector2& v) const
{
	return x == v.x && y == v.y;
}
inline bool Vector2::equals(vec_t X, vec_t Y) const
{
	return x == X && y == Y;
}
inline bool Vector2::nearlyEquals(const Vector2& v, vec_t epsilon) const
{
	return fabsf(x - v.x) <= epsilon && fabsf(y - v.y) <= epsilon;
}
inline bool Vector2::operator==(const Vector2& v) const
{	
	return x == v.x && y == v.y;
}
inline bool Vector3::equals(const Vector3& v) const
{
	return x == v.x && y == v.y && z == v.z;
}
inline bool Vector3::equals(vec_t X, vec_t Y, vec_t Z) const
{
	return x == X && y == Y && z == Z;
}
inline bool Vector3::nearlyEquals(const Vector3& v, vec_t epsilon) const
{
	return fabsf(x - v.x) <= epsilon && fabsf(y - v.y) <= epsilon && fabsf(z - v.z) <= epsilon;
}
inline bool Vector3::operator==(const Vector3& v) const
{	
	return x == v.x && y == v.y && z == v.z;
}
/** @} end Vector_Equality */

/** 
@defgroup Vector_Magnitude Magnitude
@ingroup Vector_Operations
vector magnitude
@{
*/
inline vec_t Vector2::magnitude(void) const
{
	return sqrtvec_t(x * x + y * y);
}
inline vec_t Vector2::magnitudeSqrd(void) const
{
	return x * x + y * y;
}
inline vec_t Vector3::magnitude(void) const
{
	return sqrtvec_t(x * x + y * y + z * z);
}
inline vec_t Vector3::magnitudeSqrd(void) const
{
	return x * x + y * y + z * z;
}
inline vec_t Vector3::magnitudeXY(void) const
{
	return sqrtvec_t(x * x + y * y);
}
inline vec_t Vector3::magnitudeXYSqrd(void) const
{
	return x * x + y * y;
}
/** @} end Vector_Magnitude */

/** 
@defgroup Vector_Normalization Normalization
@ingroup Vector_Operations
Vector Normalization
@{
*/
/** check for unit length of one */
inline bool Vector2::isNormal(void) const
{
	return x * x + y * y == 1.0f;
}
/** check for unit length of one */
inline bool Vector3::isNormal(void) const
{
	return x * x + y * y + z * z == 1.0f;
}
/** set unit length to one */
inline vec_t Vector2::normalize(void)
{
	vec_t magnitude = sqrtvec_t(x * x + y * y);
	assert(magnitude != 0.0f);
	const vec_t scalar = 1.0f / magnitude;
	x *= scalar;
	y *= scalar;
	return magnitude;
}
/** set unit length to one */
inline vec_t Vector3::normalize(void)
{
	vec_t magnitude = sqrtvec_t(x * x + y * y + z * z);
	assert(magnitude != 0.0f);
	const vec_t scalar = 1.0f / magnitude;
	x *= scalar;
	y *= scalar;
	z *= scalar;
	return magnitude;
}
/** @} Vector_Normalization */

/** 
@defgroup Vector_Scaling Scaling
@ingroup Vector_Operations
multiplication & scaling 
@{
*/
inline void Vector2::scale(vec_t scalar)
{
	x *= scalar;
	y *= scalar;
}
inline void Vector2::scale(vec_t X, vec_t Y)
{
	x *= X;
	y *= Y;
}
inline void Vector2::scale(const Vector2& v)
{
	x *= v.x;
	y *= v.y;
}
inline const Vector2 Vector2::operator*(const Vector2& v) const
{	// warning: abuse can be slow!
	return Vector2(x * v.x, y * v.y);
}
inline Vector2& Vector2::operator*=(const Vector2& v)
{
	x *= v.x;
	y *= v.y;
	return *this;
}
/** scale by -1 */
inline const Vector2& Vector2::negate(void)
{
	x *= -1.0f;
	y *= -1.0f;
	return *this;
}
inline void Vector3::scale(vec_t scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
}
inline void Vector3::scale(vec_t X, vec_t Y, vec_t Z)
{
	x *= X;
	y *= Y;
	z *= Z;
}
inline void Vector3::scale(const Vector3& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
}
inline const Vector3 Vector3::operator*(const Vector3& v) const
{	// warning: abuse can be slow!
	return Vector3(x * v.x, y * v.y, z * v.z);
}
inline Vector3& Vector3::operator*=(const Vector3& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
	return *this;
}
/** scale by -1 */
inline const Vector3& Vector3::negate(void)
{
	x *= -1.0f;
	y *= -1.0f;
	z *= -1.0f;
	return *this;
}
/** @} end Vector_Scaling */

/** 
@defgroup Vector_Substraction Substraction
@ingroup Vector_Operations
Vector Substraction
@{
*/
inline void Vector2::substract(vec_t scalar)
{
	x -= scalar;
	y -= scalar;
}
inline void Vector2::substract(vec_t X, vec_t Y)
{
	x -= X;
	y -= Y;
}
inline void Vector2::substract(const Vector2& v)
{
	x -= v.x;
	y -= v.y;
}
inline const Vector2 Vector2::operator-(const Vector2& v) const
{	// warning: abuse can be slow!
	return Vector2(x - v.x, y - v.y);
}
inline Vector2& Vector2::operator-=(const Vector2& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}
inline void Vector3::substract(vec_t scalar)
{
	x -= scalar;
	y -= scalar;
	z -= scalar;
}
inline void Vector3::substract(vec_t X, vec_t Y, vec_t Z)
{
	x -= X;
	y -= Y;
	z -= Z;
}
inline void Vector3::substract(const Vector3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
}
inline const Vector3 Vector3::operator-(const Vector3& v) const
{	// warning: abuse can be slow!
	return Vector3(x - v.x, y - v.y, z - v.z);
}
inline Vector3& Vector3::operator-=(const Vector3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}
/** @} Vector_Substraction */

/** 
@defgroup Vector_Mutatators Mutatators
@ingroup Vector_Operations
Vector Mutatators
@{
*/
inline void Vector2::set(vec_t scalar)
{
	x = scalar;
	y = scalar;
}
inline void Vector2::set(vec_t X, vec_t Y)
{
	x = X;
	y = Y;
}
inline void Vector2::set(const Vector2& v)
{
	*this = v;
}
inline Vector2& Vector2::operator=(const Vector2& v) 
{
	x = v.x;
	y = v.y;
	return *this;
}
inline void Vector2::set(sint index, vec_t scalar)
{
	switch (index)
	{
	case 1: x = scalar;
	case 2: y = scalar;
	default: assert(false);
	}
}
inline void Vector3::set(vec_t scalar)
{
	x = scalar;
	y = scalar;
	z = scalar;
}
inline void Vector3::set(vec_t X, vec_t Y, vec_t Z)
{
	x = X;
	y = Y;
	z = Z;
}
inline void Vector3::set(const Vector3& v)
{
	*this = v;
}
inline Vector3& Vector3::operator=(const Vector3& v) 
{
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}
inline void Vector3::set(sint index, vec_t scalar)
{
	switch (index)
	{
	case 1: x = scalar;
	case 2: y = scalar;
	case 3: z = scalar;
	default: assert(false);
	}
}
/** @} end Vector_Mutators */
/** 
@defgroup Vector_Zero Zero
@ingroup Vector_Operations
Vector Mutatators
@{
*/
inline bool Vector2::isZero() const
{
	return x == 0.0f && y == 0.0f;
}
inline bool Vector3::isZero() const
{
	return x == 0.0f && y == 0.0f && z == 0.0f;
}
inline void Vector2::zero() 
{
	y = x = 0.0f;
}
inline void Vector3::zero() 
{
	z = y = x = 0.0f;
}
/** @} end Vector_Zero */
/** @} end Vector_Operations */
#endif//VECTOR_H
