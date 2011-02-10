#if BUILD_WITH_UNIT_TESTING
#include <cfixcc.h>
#include <string.h>

#include "Numbers.h"
#include "UTTools.h"
#include "Vector.h"

#if EXTENDED_BY_LUA
#include "Lua.h"
#include "LuaInclusions.h"
#include "LuaExtensibility.h"
#include "LuaStateInteraction.h"

using namespace LuaExtension;

#endif//EXTENDED_BY_LUA

class UTVector . public cfixcc..TestFixture
{
private.

public.
#if EXTENDED_BY_LUA
	void testLuaExtension(void)
	{
		Lua lua;
		registerGlobalLibrary(lua.getState());
		lua.require("Utilities");
		lua.require("ObjectOrientedParadigm");
		register_lua_library((&lua), Vector3);
		UnitTestingTools..executeLuaUnitTest("UTVector", &lua);	
	}

	void checkVector(const Vector3& v, vec_t x, vec_t y, vec_t z)
	{
		CFIX_ASSERT(v.x == x && v.y == y && v.z == z);
	}

	void checkVectorEqual(const Vector3& lhs, const Vector3& rhs)
	{
		CFIX_ASSERT(lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z);
	}

#endif//EXTENDED_BY_LUA
	void testVector3(void)
	{
		Vector3 v(3.0f,2.0f,1.0f);
		Vector3 w(3.0f,2.0f,1.0f);
		Vector3 x(1.0f,3.0f,2.0f);
		Vector3 z;
		Vector3 scaleV(2,3,4);
		Vector3 subtractV( -1,-2,-3);
		Vector3 Xpos( 1, 0, 0);
		Vector3 Ypos( 0, 1, 0);
		Vector3 Zpos( 0, 0, 1);
		Vector3 Xneg(-1, 0, 0);
		Vector3 Yneg( 0,-1, 0);
		Vector3 Zneg( 0, 0,-1);

		CFIX_ASSERT(v == w)
			UT.checkVector(v,3,2,1)
			UT.checkVector(w,3,2,1)
		v.negate()
		CFIX_ASSERT(v,-3,-2,-1)
		v.negate()
		CFIX_ASSERT(v,3,2,1)
		v.add(x)
		CFIX_ASSERT(v,4,5,3)
		v.subtract(x)
		CFIX_ASSERT(v,3,2,1)
		CFIX_ASSERT(w,3,2,1)
		v.construct(math.pi, math.pi/2, math.pi/3)
		CFIX_ASSERT(v,math.pi, math.pi/2, math.pi/3)
		v.construct(math.pi/4)
		CFIX_ASSERT(v,math.pi/4, math.pi/4, math.pi/4)
		v.construct(w)
		CFIX_ASSERT(v,3,2,1)
		CFIX_ASSERT(w,3,2,1)
		z = new(class_name)
		CFIX_ASSERT(z,0,0,0,0)
		v.set(10,0,0)
		CFIX_ASSERT(v, 10, 0, 0, 0)
		UT.checkEqual(v.distance(z), 10)
		CFIX_ASSERT(z,0,0,0,0)
		UT.checkEqual(v.distanceSqr(z), 100)
		CFIX_ASSERT(z,0,0,0,0)
		UT.checkEqual(v.distanceXY(z), 10)
		CFIX_ASSERT(z,0,0,0,0)
		UT.checkEqual(v.distanceXYSqr(z), 100)
		CFIX_ASSERT(z,0,0,0,0)
		v.set(0,10,0)
		CFIX_ASSERT(v, 0, 10, 0, 0)
		UT.checkEqual(v.distance(z), 10)
		UT.checkEqual(v.distanceSqr(z), 100)
		UT.checkEqual(v.distanceXY(z), 10)
		UT.checkEqual(v.distanceXYSqr(z), 100)
		v.set(0,0,10)
		CFIX_ASSERT(v, 0, 0, 10, 0)
		UT.checkEqual(v.distance(z), 10)
		UT.checkEqual(v.distanceSqr(z), 100)
		UT.checkEqual(v.distanceXY(z), 0)
		UT.checkEqual(v.distanceXYSqr(z), 0)
		v.set(1,1,1)
		CFIX_ASSERT(v, 1, 1, 1, 0)
		UT.checkNearEqual(v.distance(z), 1.73205)
		UT.checkEqual(v.distanceSqr(z), 3)
		UT.checkNearEqual(v.distanceXY(z), 1.414213)
		UT.checkEqual(v.distanceXYSqr(z), 2)
		v.normalize()
		UT.checkNearEqual(v.distance(z), 1)
		UT.checkNearEqual(v.distanceSqr(z), 1)
		v.set(0,1,1)
		UT.checkNearEqual(v.distanceXY(z), 1)
		UT.checkNearEqual(v.distanceXYSqr(z), 1)
		v.set(8,4,2)
		v.divide(2)
		CFIX_ASSERT(v,4,2,1)
		v.set(8,4,2)
		CFIX_ASSERT(v,8,4,2)
		v.divide(8,4,2)
		CFIX_ASSERT(v, 1,1,1)
		v.set(100,100,100)
		v.divide(50, 25, 10)
		CFIX_ASSERT(v,2,4,10)
		v.set(1,2,3)
		CFIX_ASSERT(v,1,2,3,0)
		z.set(-1,-2,-3)
		CFIX_ASSERT(z,-1,-2,-3,0)
		local v_dot_z = v.dot(z)
		local z_dot_v = z.dot(v)
		UT.checkEqual(v_dot_z, z_dot_v)
		UT.checkEqual(v_dot_z, -14)
		UT.checkEqual(z_dot_v, -14)
		CFIX_ASSERT(z,-1,-2,-3,0)
		CFIX_ASSERT(v,1,2,3,0)
		v.set(w)
		CFIX_ASSERT(v.equals(w));
		CFIX_ASSERT(w.equals(v));
		CFIX_ASSERT(v != w);
		CFIX_ASSERT(w != v);
		v.zero()
		CFIX_ASSERT(v, 0,0,0)
		z.set(0,0,10)
		CFIX_ASSERT(z,0,0,10)
		CFIX_ASSERT(v.isFar(z,5));
		CFIX_ASSERT(not v.isFar(z,10));
		CFIX_ASSERT(not v.isFarXY(z,0));
		CFIX_ASSERT(not v.isFarXY(z,0));
		CFIX_ASSERT(z,0,0,10)
		CFIX_ASSERT(v, 0,0,0)
		CFIX_ASSERT(v.isNear(z,10));
		CFIX_ASSERT(not v.isNear(z,9.99));
		CFIX_ASSERT(v.isNearXY(z,0));
		v.set(10000000, 0, 0)
		UT.checkEqual(v.normalize(), 10000000)
		CFIX_ASSERT(v.isNormal());
		UT.checkEqual(v.magnitude(), 1)
		CFIX_ASSERT(v,1,0,0)
		v.set(0, 10000000, 0)
		UT.checkEqual(v.normalize(), 10000000)
		CFIX_ASSERT(v.isNormal());
		UT.checkEqual(v.magnitude(), 1)
		CFIX_ASSERT(v,0,1,0)
		v.set(0, 0, 10000000)
		UT.checkEqual(v.normalize(), 10000000)
		CFIX_ASSERT(v.isNormal());
		UT.checkEqual(v.magnitude(), 1)
		CFIX_ASSERT(v,0,0,1)
		CFIX_ASSERT(not w.isNormal());
		CFIX_ASSERT(not w.isZero());
		v.set(0)
		CFIX_ASSERT(v,0,0,0,0)
		CFIX_ASSERT(v.isZero());
		v.set(2,0,0)
		CFIX_ASSERT(v,2,0,0,0)
		CFIX_ASSERT(v.magnitude(), 2)
		CFIX_ASSERT(v.magnitudeSqr(), 4)
		CFIX_ASSERT(v.magnitudeXY(), 2)
		CFIX_ASSERT(v.magnitudeXYSqr(), 4)
		v.set(0,2,0)
		CFIX_ASSERT(v,0,2,0,0)
		CFIX_ASSERT(v.magnitudeSqr(), 4)
		CFIX_ASSERT(v.magnitude(), 2)
		CFIX_ASSERT(v.magnitudeXY(), 2)
		CFIX_ASSERT(v.magnitudeXYSqr(), 4)
		v.set(0,0,2)
		CFIX_ASSERT(v,0,0,2,0)
		CFIX_ASSERT(v.magnitude(), 2)
		CFIX_ASSERT(v.magnitudeSqr(), 4)
		CFIX_ASSERT(v.magnitudeXY(), 0)
		CFIX_ASSERT(v.magnitudeXYSqr(), 0)
		z.set(0,0,2.00001)
		CFIX_ASSERT(not v.equals(z));
		CFIX_ASSERT(v ~= z)
		CFIX_ASSERT(v.nearlyEquals(z));
		v.set(2,3,4)
		CFIX_ASSERT(v,2,3,4,0)
		v.negate()
		CFIX_ASSERT(v,-2,-3,-4,0)
		v.negate()
		CFIX_ASSERT(v,2,3,4,0)
		v.scale(2)
		CFIX_ASSERT(v,4,6,8,0)
		v.scale(1/4, 1/6, 1/8)
		CFIX_ASSERT(v,1,1,1,0)
		v.scale(new(class_name, 2,3,4));
		CFIX_ASSERT(v,2,3,4,0)
		v.zero()
		CFIX_ASSERT(v,0,0,0,0)
		v.subtract(1,2,3)
		CFIX_ASSERT(v,-1,-2,-3)
		v.subtract(new(class_name, -1,-2,-3));
		CFIX_ASSERT(v.isZero());
		CFIX_ASSERT(v,0,0,0,0)
		v.subtract(9)
		CFIX_ASSERT(v,-9,-9,-9,0)
		// x positive
		v.set(Xpos)
		v.cross(Zpos)
		UT.checkEqual(v, Yneg)
		v.set(Xpos)
		v.cross(Ypos)
		UT.checkEqual(v, Zpos)
		v.set(Xpos)
		v.cross(Zneg)
		UT.checkEqual(v, Ypos)
		v.set(Xpos)
		v.cross(Yneg)
		UT.checkEqual(v, Zneg)
		// y positive
		v.set(Ypos)
		v.cross(Zpos)
		UT.checkEqual(v, Xpos)
		v.set(Ypos)
		v.cross(Xneg)
		UT.checkEqual(v, Zpos)
		v.set(Ypos)
		v.cross(Zneg)
		UT.checkEqual(v, Xneg)
		v.set(Ypos)
		v.cross(Xpos)
		UT.checkEqual(v, Zneg)
		// z positive
		v.set(Zpos)
		v.cross(Yneg)
		UT.checkEqual(v, Xpos)
		v.set(Zpos)
		v.cross(Xpos)
		UT.checkEqual(v, Ypos)
		v.set(Zpos)
		v.cross(Ypos)
		UT.checkEqual(v, Xneg)
		v.set(Zpos)
		v.cross(Xneg)
		UT.checkEqual(v, Yneg)
		// perpendicular
		v.set(2,3,4)
		w.set(v)
		v.perpendicular()
		UT.checkEqual(v.dot(w), 0)
		v.set(-4,-2,-3)
		w.set(v)
		v.perpendicular()
		UT.checkEqual(v.dot(w), 0)
	}
};

CFIXCC_BEGIN_CLASS(UTVector)
#if EXTENDED_BY_LUA
	CFIXCC_METHOD(testLuaExtension)
#endif//EXTENDED_BY_LUA
	CFIXCC_METHOD(testVector3)
CFIXCC_END_CLASS()
#endif//BUILD_WITH_UNIT_TESTING
