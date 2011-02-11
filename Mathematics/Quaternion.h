#pragma once
#ifndef QUATERNION_H
#define QUATERNION_H
/**
\file Quaternion.h

Axis - Angle pairs, which are exposed to %Lua.

\author Smoke and Mirrors Development
\copyright 2010 Smoke and Mirrors Development
\email smokeandmirrorsdevelopment@gmail.com
\date 2/18/2011
*/

/** 
\defgroup Mathematics Mathematics 
math classes, constants, functions and formulas
*/

#include <math.h>
#include <assert.h>

#include "Build.h"
#include "Numbers.h"

#if EXTENDED_BY_LUA
#include "LuaExtensibility.h"
#include "LuaStateInteraction.h"
#endif//EXTENDED_BY_LUA

namespace math
{

/**
\class Quaternion
\ingroup Mathematics

a Quaternion class
*/
class Quaternion
#if EXTENDED_BY_LUA
	: public luaExtension::LuaExtendable
#endif
{
public:
	/** if this is rotation, theta degrees around axis n, w = cos(theta/2) */
	vec_t w; 
	/** if this is rotation, theta degrees around axis n, x = n.x * sin(theta/2) */
	vec_t x;
	/** if this is rotation, theta degrees around axis n, y = n.y * sin(theta/2) */
	vec_t y;
	/** if this is rotation, theta degrees around axis n, z = n.z * sin(theta/2) */
	vec_t z;

	Quaternion(void)
	{/* empty */}
	Quaternion(const Quaternion& q) : w(q.w), x(q.x), y(q.y), z(q.z)
	{/* empty */}
	Quaternion(vec_t W, vec_t X, vec_t Y, vec_t Z) : w(W), x(X), y(Y), z(Z)
	{/* empty */}
	Quaternion(vec_t scalar) : w(scalar), x(scalar), y(scalar), z(scalar)
	{/* empty */}
#if EXTENDED_BY_LUA
	virtual ~Quaternion(void)
	{/* empty */}
	createLuaExtendableUserdataDefaultFunctions(Quaternion)
#endif//EXTENDED_BY_LUA 

}; // Quaternion

} // namespace math

#endif//QUATERNION_H