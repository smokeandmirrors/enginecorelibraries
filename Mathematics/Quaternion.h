#pragma once
#ifndef QUATERNION_H
#define QUATERNION_H
/**
\file Quaternion.h
This file defines the Quaternion class, which is exposed to %Lua.

\author Smoke and Mirrors Development
\htmlonly
<A HREF="smokeandmirrorsdevelopment@gmail.com">
smokeandmirrorsdevelopment@gmail.com</A>
<BR>
&copy;2009-2011 Smoke and Mirrors Development
<BR>
\endhtmlonly
\date 2/18/2011

<DEVELOPMENT STATUS>
Current Draft		:	0.0
Current Phase		:   DEVELOPMENT
Purpose				:	DEPLOYMENT
Unit Tested			:	NO
Used in development	:	NO
Used in experiments :	NO
Tested in the field	:	NO
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
#include "LuaExtensionInclusions.h"
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
	: public lua_extension::LuaExtendable
#endif
{
public:
	/** if this is rotation, theta degrees around axis n, w = cos(theta/2) */
	sreal w; 
	/** if this is rotation, theta degrees around axis n, x = n.x * sin(theta/2) */
	sreal x;
	/** if this is rotation, theta degrees around axis n, y = n.y * sin(theta/2) */
	sreal y;
	/** if this is rotation, theta degrees around axis n, z = n.z * sin(theta/2) */
	sreal z;

	Quaternion(void)
	{/* empty */}
	Quaternion(const Quaternion& q) : w(q.w), x(q.x), y(q.y), z(q.z)
	{/* empty */}
	Quaternion(sreal W, sreal X, sreal Y, sreal Z) : w(W), x(X), y(Y), z(Z)
	{/* empty */}
	Quaternion(sreal scalar) : w(scalar), x(scalar), y(scalar), z(scalar)
	{/* empty */}
#if EXTENDED_BY_LUA
	DEFINE_LUAEXTENDABLE_USERDATA_DEFAULT_FUNCTIONS(Quaternion)
#endif//EXTENDED_BY_LUA 

}; // Quaternion

} // namespace math

#endif//QUATERNION_H