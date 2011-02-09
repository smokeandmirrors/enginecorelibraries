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

\todo Math namespaces
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

#if EXTENDED_BY_LUA
#include "LuaExtensibility.h"
#include "LuaStateInteraction.h"
#endif

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
#if EXTENDED_BY_LUA
	: public LuaExtension::LuaExtendable
#endif//EXTENDED_BY_LUA
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
	// \see normalized constructor below
	// Vector2(const Vector2& v, bool /* IGNORED */);
	// 	: x(v.x), y(v.y) 		{/* empty */}
#if EXTENDED_BY_LUA
	virtual ~Vector2(void)		{ /* empty */ };
	createLuaExtendableUserdataDefaultFunctions(Vector2)
#endif//EXTENDED_BY_LUA
	// access
	const vec_t& 	operator[](uint i) const;	
	vec_t 			operator[](uint i);
	// addition 
	void 			add(vec_t scalar);
	void 			add(vec_t X, vec_t Y);
	void 			add(const Vector2& v);
	Vector2& 		operator+=(const Vector2& v);
	// distance to another
	vec_t			distance(const Vector2& v) const;
	vec_t 			distanceSqr(const Vector2& v) const;
	bool			isFar(const Vector2& v, vec_t closest_range) const;
	bool			isNear(const Vector2& v, vec_t farthest_range) const;
	// division
	void 			divide(vec_t scalar);
	void 			divide(vec_t X, vec_t Y);
	void 			divide(const Vector2& v);
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
	vec_t 			magnitudeSqr(void) const;
	// normalization 
	bool			isNormal(void) const;
	vec_t 			normalize(void);
	// construction (normalized)
	Vector2(const Vector2& v, bool /* IGNORED */)
		: x(v.x), y(v.y) { normalize(); }
	// multiplication & scaling 
	void			negate(void);
	void 			scale(vec_t scalar);
	void 			scale(vec_t X, vec_t Y);
	void 			scale(const Vector2& v);
	Vector2& 		operator*=(const Vector2& v);
	// mutation 
	void 			set(vec_t scalar);
	void 			set(vec_t X, vec_t Y);
	void 			set(const Vector2& v);
	void			set(sint index, vec_t scalar);
	Vector2& 		operator=(const Vector2& v);
	// substraction 
	void 			subtract(vec_t scalar);
	void 			subtract(vec_t X, vec_t Y);
	void 			subtract(const Vector2& v);
	Vector2& 		operator-=(const Vector2& v);
	// zero
	bool			isZero(void) const;
	void			zero(void);
}; // class Vector2

#if EXTENDED_BY_LUA
declare_lua_LuaExtendable(Vector2);
#endif//EXTENDED_BY_LUA

class Vector3 
#if EXTENDED_BY_LUA
	: public LuaExtension::LuaExtendable
#endif//EXTENDED_BY_LUA
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
#if EXTENDED_BY_LUA
	virtual ~Vector3(void)		{ /* empty */ };
	createLuaExtendableUserdataDefaultFunctions(Vector3)
#endif//EXTENDED_BY_LUA
	
	// access 
	const vec_t& 	operator[](uint i) const;	
	vec_t 			operator[](uint i);
	// addition 
	void 			add(vec_t scalar);
	void 			add(vec_t X, vec_t Y, vec_t Z);
	void 			add(const Vector3& v);	
	Vector3& 		operator+=(const Vector3& v);
	// cross product 
	void 			cross(const Vector3& v);
	void 			cross(const Vector3& a, const Vector3& b);
	// perpendicular 
	void			perpendicular(void);
	// distance to another 
	vec_t			distance(const Vector3& v) const;
	vec_t 			distanceSqr(const Vector3& v) const;
	vec_t 			distanceXY(const Vector3& v) const;
	vec_t 			distanceXYSqr(const Vector3& v) const;
	bool			isFar(const Vector3& v, vec_t closest_range) const;
	bool			isFarXY(const Vector3& v, vec_t closest_range) const;
	bool			isNear(const Vector3& v, vec_t farthest_range) const;
	bool			isNearXY(const Vector3& v, vec_t farthest_range) const;
	// division 
	void 			divide(vec_t scalar);
	void 			divide(vec_t X, vec_t Y, vec_t Z);
	void 			divide(const Vector3& v);
	Vector3& 		operator/=(const Vector3& v);
	// dot product 
	vec_t 			dot(const Vector3& v) const;
	// equality 
	bool 			equals(const Vector3& v) const;
	bool 			equals(vec_t X, vec_t Y, vec_t Z) const;
	bool			nearlyEquals(const Vector3& v, vec_t epsilon=vectorTolerance) const;
	bool 			operator==(const Vector3& v) const;
	// magnitude 
	vec_t 			magnitude(void) const;
	vec_t 			magnitudeSqr(void) const;
	vec_t 			magnitudeXY(void) const;
	vec_t 			magnitudeXYSqr(void) const;
	// normalization
	bool			isNormal(void) const;
	vec_t 			normalize(void);
	// construction (normalized)
	Vector3(const Vector3& v, bool /* IGNORED */)
		: x(v.x), y(v.y), z(v.z) { normalize(); }
	// multiplication & scaling 
	Vector3&		operator-(void);
	void 			negate(void);
	void 			scale(vec_t scalar);
	void 			scale(vec_t X, vec_t Y, vec_t Z);
	void 			scale(const Vector3& v);
	Vector3& 		operator*=(const Vector3& v);
	// mutation 
	void 			set(vec_t scalar);
	void 			set(vec_t X, vec_t Y, vec_t Z);
	void 			set(const Vector3& v);
	void			set(sint index, vec_t scalar);
	Vector3& 		operator=(const Vector3& v);
	// substraction 
	void 			subtract(vec_t scalar);
	void 			subtract(vec_t X, vec_t Y, vec_t Z);
	void 			subtract(const Vector3& v);
	Vector3& 		operator-=(const Vector3& v);
	// zero
	bool			isZero(void) const;
	void			zero(void);
}; // class Vector3

#if EXTENDED_BY_LUA
declare_lua_LuaExtendable(Vector3);
#endif//EXTENDED_BY_LUA

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
inline void Vector3::perpendicular(void)
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
@defgroup Vector_Distance Distance
@ingroup Vector_Operations
distance to another vector
@{
*/
inline vec_t Vector2::distance(const Vector2& v) const
{
	vec_t x_dist = v.x - x;
	vec_t y_dist = v.y - y;
	return sqrtvec_t(x_dist * x_dist + y_dist * y_dist);
}
inline vec_t Vector2::distanceSqr(const Vector2& v) const
{
	vec_t x_dist = v.x - x;
	vec_t y_dist = v.y - y;
	return x_dist * x_dist + y_dist * y_dist;
}
inline bool Vector2::isFar(const Vector2& v, vec_t closest_range) const
{
	vec_t x_dist = v.x - x;
	vec_t y_dist = v.y - y;
	return (x_dist * x_dist + y_dist * y_dist) > (closest_range * closest_range);
}
inline bool Vector2::isNear(const Vector2& v, vec_t farthest_range) const
{
	vec_t x_dist = v.x - x;
	vec_t y_dist = v.y - y;
	return (x_dist * x_dist + y_dist * y_dist) <= (farthest_range * farthest_range);
}
inline vec_t Vector3::distance(const Vector3& v) const
{
	vec_t x_dist = v.x - x;
	vec_t y_dist = v.y - y;
	vec_t z_dist = v.z - z;
	return sqrtvec_t(x_dist * x_dist + y_dist * y_dist + z_dist * z_dist);
}
inline vec_t Vector3::distanceSqr(const Vector3& v) const
{
	vec_t x_dist = v.x - x;
	vec_t y_dist = v.y - y;
	vec_t z_dist = v.z - z;
	return x_dist * x_dist + y_dist * y_dist + z_dist * z_dist;
}
inline vec_t Vector3::distanceXY(const Vector3& v) const
{
	vec_t x_dist = v.x - x;
	vec_t y_dist = v.y - y;
	return sqrtvec_t(x_dist * x_dist + y_dist * y_dist);
}
inline vec_t Vector3::distanceXYSqr(const Vector3& v) const
{
	vec_t x_dist = v.x - x;
	vec_t y_dist = v.y - y;
	return x_dist * x_dist + y_dist * y_dist;
}
inline bool Vector3::isFar(const Vector3& v, vec_t closest_range) const
{
	vec_t x_dist = v.x - x;
	vec_t y_dist = v.y - y;
	vec_t z_dist = v.z - z;
	return (x_dist * x_dist + y_dist * y_dist + z_dist * z_dist) > (closest_range * closest_range);
}
inline bool Vector3::isFarXY(const Vector3& v, vec_t closest_range) const
{
	vec_t x_dist = v.x - x;
	vec_t y_dist = v.y - y;
	return (x_dist * x_dist + y_dist * y_dist) > (closest_range * closest_range);
}
inline bool Vector3::isNear(const Vector3& v, vec_t farthest_range) const
{
	vec_t x_dist = v.x - x;
	vec_t y_dist = v.y - y;
	vec_t z_dist = v.z - z;
	return (x_dist * x_dist + y_dist * y_dist + z_dist * z_dist) <= (farthest_range * farthest_range);
}
inline bool Vector3::isNearXY(const Vector3& v, vec_t farthest_range) const
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
	scalar = 1.0f / scalar; 
	x *= scalar;
	y *= scalar;
}
inline void Vector2::divide(vec_t X, vec_t Y)
{
	x /= X;
	y /= Y;
}
inline void Vector2::divide(const Vector2& v)
{
	x /= v.x;
	y /= v.y;
}
inline Vector2& Vector2::operator/=(const Vector2& v)
{
	x /= v.x;
	y /= v.y;
	return *this;
}
inline void Vector3::divide(vec_t scalar)
{
	scalar = 1.0f / scalar; 
	x *= scalar;
	y *= scalar;
	z *= scalar;
}
inline void Vector3::divide(vec_t X, vec_t Y, vec_t Z)
{
	x /= X;
	y /= Y;
	z /= Z;
}
inline void Vector3::divide(const Vector3& v)
{
	x /= v.x;
	y /= v.y;
	z /= v.z;
}
inline Vector3& Vector3::operator/=(const Vector3& v)
{
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
inline vec_t Vector2::magnitudeSqr(void) const
{
	return x * x + y * y;
}
inline vec_t Vector3::magnitude(void) const
{
	return sqrtvec_t(x * x + y * y + z * z);
}
inline vec_t Vector3::magnitudeSqr(void) const
{
	return x * x + y * y + z * z;
}
inline vec_t Vector3::magnitudeXY(void) const
{
	return sqrtvec_t(x * x + y * y);
}
inline vec_t Vector3::magnitudeXYSqr(void) const
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
	const vec_t scalar = 1.0f / magnitude;
	x *= scalar;
	y *= scalar;
	return magnitude;
}
/** set unit length to one */
inline vec_t Vector3::normalize(void)
{
	vec_t magnitude = sqrtvec_t(x * x + y * y + z * z);
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
inline Vector2& Vector2::operator*=(const Vector2& v)
{
	x *= v.x;
	y *= v.y;
	return *this;
}
/** scale by -1 */
inline void Vector2::negate(void)
{
	x *= -1.0f;
	y *= -1.0f;
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
inline Vector3& Vector3::operator*=(const Vector3& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
	return *this;
}
/** scale by -1 */
inline void Vector3::negate(void)
{
	x *= -1.0f;
	y *= -1.0f;
	z *= -1.0f;
}
inline Vector3& Vector3::operator-(void)
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
inline void Vector2::subtract(vec_t scalar)
{
	x -= scalar;
	y -= scalar;
}
inline void Vector2::subtract(vec_t X, vec_t Y)
{
	x -= X;
	y -= Y;
}
inline void Vector2::subtract(const Vector2& v)
{
	x -= v.x;
	y -= v.y;
}
inline Vector2& Vector2::operator-=(const Vector2& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}
inline void Vector3::subtract(vec_t scalar)
{
	x -= scalar;
	y -= scalar;
	z -= scalar;
}
inline void Vector3::subtract(vec_t X, vec_t Y, vec_t Z)
{
	x -= X;
	y -= Y;
	z -= Z;
}
inline void Vector3::subtract(const Vector3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
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
