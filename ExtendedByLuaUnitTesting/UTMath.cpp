#include "Build.h"
#if WITH_UNIT_TESTING
#include <cfixcc.h>
#include <string.h>

#if EXTENDED_BY_LUA
#include "LuaExtensionInclusions.h"
#include "LuaMathExtensions.cpp"
#endif//EXTENDED_BY_LUA
#include "Numbers.h"
#include "NumericalFunctions.h"
#include "UTTools.h"
#include "Vector.h"

using namespace embeddedLua;
using namespace math;
using namespace unit_testing_tools;

void checkVector(const Vector3& v, sreal x, sreal y, sreal z)
{
	CFIXCC_ASSERT_EQUALS(v.x, x);
	CFIXCC_ASSERT_EQUALS(v.y, y);
	CFIXCC_ASSERT_EQUALS(v.z, z);
}

void checkVector(const Vector3& v, sreal x, sreal y, sreal z, sreal tolerance)
{
	checkNearEqual(v.x, x, tolerance);
	checkNearEqual(v.y, y, tolerance);
	checkNearEqual(v.z, z, tolerance);
}

void checkVectorEqual(const Vector3& lhs, const Vector3& rhs)
{
	CFIXCC_ASSERT_EQUALS(lhs.x, rhs.x);
	CFIXCC_ASSERT_EQUALS(lhs.y, rhs.y);
	CFIXCC_ASSERT_EQUALS(lhs.z, rhs.z);
}

class UTMath : public cfixcc::TestFixture
{
private:

public:
	void testNumbers(void);
	void testVector3(void);
	void testLuaExtension(void);
};

void UTMath::testLuaExtension(void)
{
	DECLARE_UNIT_TESTING_LUA_OBJECT
	lua.require("Utilities");
	lua.require("ObjectOrientedParadigm");
	REGISTER_LUA_LIBRARY((&lua), Vector3);
	unit_testing_tools::executeLuaUnitTest("UTVector", &lua);	
}

void UTMath::testNumbers(void)
{
	sreal decimal = 0.999999999999999999999f;
	sint limit = 4294967295;

	for (sint i = -limit; i < limit; i++)
	{
		sreal value = static_cast<sreal>(i) + decimal;
		CFIX_ASSERT(isFinite(value));
		CFIX_ASSERT(!isNaN(value));
		CFIX_ASSERT(isValid(value));
	}
#if DEBUG
	sreal one = 1.0f;
	sreal zero = 0.0f;
	sreal positive_infinity = one / zero;
	sreal negative_infinity = log(0.0f);
	sreal not_a_number = zero / zero; 

	CFIX_ASSERT(!isFinite(positive_infinity));
	CFIX_ASSERT(!isNaN(positive_infinity));
	CFIX_ASSERT(!isValid(positive_infinity));

	CFIX_ASSERT(!isFinite(negative_infinity));
	CFIX_ASSERT(!isNaN(negative_infinity));
	CFIX_ASSERT(!isValid(negative_infinity));

	CFIX_ASSERT(isNaN(not_a_number));
	CFIX_ASSERT(!isValid(not_a_number));
	CFIX_ASSERT(!isFinite(not_a_number));
#endif//DEBUG
}

void UTMath::testVector3(void)
{
	Vector3 v(3.0f,2.0f,1.0f);
	Vector3 w(3.0f,2.0f,1.0f);
	Vector3 x(1.0f,3.0f,2.0f);
	Vector3 z(0.0f);
	Vector3 scaleV(2,3,4);
	Vector3 subtractV( -1,-2,-3);
	Vector3 Xpos( 1, 0.0f, 0.0f);
	Vector3 Ypos( 0.0f, 1, 0.0f);
	Vector3 Zpos( 0.0f, 0.0f, 1);
	Vector3 Xneg(-1, 0.0f, 0.0f);
	Vector3 Yneg( 0.0f,-1, 0.0f);
	Vector3 Zneg( 0.0f, 0.0f,-1);

	CFIX_ASSERT(v == w);
	checkVector(v,3,2,1);
	checkVector(w,3,2,1);
	v.negate();
	checkVector(v,-3,-2,-1);
	v.negate();
	checkVector(v,3,2,1);
	v.add(x);
	checkVector(v,4,5,3);
	v.subtract(x);
	checkVector(v,3,2,1);
	checkVector(w,3,2,1);
	v.set(math::real4_pi, math::real4_pi/2, math::real4_pi/3);
	checkVector(v,math::real4_pi, math::real4_pi/2, math::real4_pi/3);
	v.set(math::real4_pi/4);
	checkVector(v,math::real4_pi/4, math::real4_pi/4, math::real4_pi/4);
	v.set(w);
	checkVector(v,3,2,1);
	checkVector(w,3,2,1);
	v.set(10.0f,0.0f,0.0f);
	checkVector(v, 10.0f, 0.0f, 0.0f);
	CFIXCC_ASSERT_EQUALS(v.distance(z), 10.0f);
	checkVector(z,0.0f,0.0f,0.0f);
	CFIXCC_ASSERT_EQUALS(v.distanceSqr(z), 100.0f);
	checkVector(z,0.0f,0.0f,0.0f,0.0f);
	CFIXCC_ASSERT_EQUALS(v.distanceXY(z), 10.0f);
	checkVector(z,0.0f,0.0f,0.0f,0.0f);
	CFIXCC_ASSERT_EQUALS(v.distanceXYSqr(z), 100.0f);
	checkVector(z,0.0f,0.0f,0.0f,0.0f);
	v.set(0.0f,10.0f,0.0f);
	checkVector(v, 0.0f, 10.0f, 0.0f, 0.0f);
	CFIXCC_ASSERT_EQUALS(v.distance(z), 10.0f);
	CFIXCC_ASSERT_EQUALS(v.distanceSqr(z), 100.0f);
	CFIXCC_ASSERT_EQUALS(v.distanceXY(z), 10.0f);
	CFIXCC_ASSERT_EQUALS(v.distanceXYSqr(z), 100.0f);
	v.set(0.0f,0.0f,10.0f);
	checkVector(v, 0.0f, 0.0f, 10.0f, 0.0f);
	CFIXCC_ASSERT_EQUALS(v.distance(z), 10.0f);
	CFIXCC_ASSERT_EQUALS(v.distanceSqr(z), 100.0f);
	CFIXCC_ASSERT_EQUALS(v.distanceXY(z), 0.0f);
	CFIXCC_ASSERT_EQUALS(v.distanceXYSqr(z), 0.0f);
	v.set(1,1,1);
	checkVector(v, 1, 1, 1, 0.0f);
	checkNearEqual(v.distance(z), 1.73205f);
	CFIXCC_ASSERT_EQUALS(v.distanceSqr(z), 3.0f);
	checkNearEqual(v.distanceXY(z), 1.414213f);
	CFIXCC_ASSERT_EQUALS(v.distanceXYSqr(z), 2.0f);
	v.normalize();
	checkNearEqual(v.distance(z), 1);
	checkNearEqual(v.distanceSqr(z), 1);
	v.set(0.0f,1,1);
	checkNearEqual(v.distanceXY(z), 1);
	checkNearEqual(v.distanceXYSqr(z), 1);
	v.set(8,4,2);
	v.divide(2);
	checkVector(v,4,2,1);
	v.set(8,4,2);
	checkVector(v,8,4,2);
	v.divide(8,4,2);
	checkVector(v, 1,1,1);
	v.set(100.0f,100.0f,100.0f);
	v.divide(50, 25, 10.0f);
	checkVector(v,2,4,10.0f);
	v.set(1,2,3);
	checkVector(v,1,2,3,0.0f);
	z.set(-1,-2,-3);
	checkVector(z,-1,-2,-3,0.0f);
	sreal v_dot_z = v.dot(z);
	sreal z_dot_v = z.dot(v);
	CFIXCC_ASSERT_EQUALS(v_dot_z, z_dot_v);
	CFIXCC_ASSERT_EQUALS(v_dot_z, -14.0f);
	CFIXCC_ASSERT_EQUALS(z_dot_v, -14.0f);
	checkVector(z,-1,-2,-3,0.0f);
	checkVector(v,1,2,3,0.0f);
	v.set(w);
	CFIX_ASSERT(! (v != w));
	CFIX_ASSERT(! (w != v));
	CFIX_ASSERT(w == v);
	CFIX_ASSERT(v == w);
	v.zero();
	checkVector(v, 0.0f,0.0f,0.0f);
	z.set(0.0f,0.0f,10.0f);
	checkVector(z,0.0f,0.0f,10.0f);
	CFIX_ASSERT(v.isFar(z,5));
	CFIX_ASSERT(!v.isFar(z,10.0f));
	CFIX_ASSERT(!v.isFarXY(z,0.0f));
	CFIX_ASSERT(!v.isFarXY(z,0.0f));
	checkVector(z,0.0f,0.0f,10.0f);
	checkVector(v, 0.0f,0.0f,0.0f);
	CFIX_ASSERT(v.isNear(z,10.0f));
	CFIX_ASSERT(!v.isNear(z,9.99f));
	CFIX_ASSERT(v.isNearXY(z,0.0f));
	v.set(10000000.0f, 0.0f, 0.0f);
	CFIXCC_ASSERT_EQUALS(v.normalize(), 10000000.0f);
	CFIX_ASSERT(v.isNormal());
	CFIXCC_ASSERT_EQUALS(v.magnitude(), 1.0f);
	checkVector(v,1,0.0f,0.0f);
	v.set(0.0f, 10000000.0f, 0.0f);
	CFIXCC_ASSERT_EQUALS(v.normalize(), 10000000.0f);
	CFIX_ASSERT(v.isNormal());
	CFIXCC_ASSERT_EQUALS(v.magnitude(), 1.0f);
	checkVector(v,0.0f,1.0f,0.0f);
	v.set(0.0f, 0.0f, 10000000.0f);
	CFIXCC_ASSERT_EQUALS(v.normalize(), 10000000.0f);
	CFIX_ASSERT(v.isNormal());
	CFIXCC_ASSERT_EQUALS(v.magnitude(), 1.0f);
	checkVector(v,0.0f,0.0f,1.0f);
	CFIX_ASSERT(!w.isNormal());
	CFIX_ASSERT(!w.isZero());
	v.set(0.0f);
	checkVector(v,0.0f,0.0f,0.0f,0.0f);
	CFIX_ASSERT(v.isZero());
	v.set(2,0.0f,0.0f);
	checkVector(v,2,0.0f,0.0f,0.0f);
	CFIXCC_ASSERT_EQUALS(v.magnitude(), 2.0f);
	CFIXCC_ASSERT_EQUALS(v.magnitudeSqr(), 4.0f);
	CFIXCC_ASSERT_EQUALS(v.magnitudeXY(), 2.0f);
	CFIXCC_ASSERT_EQUALS(v.magnitudeXYSqr(), 4.0f);
	v.set(0.0f,2.0f,0.0f);
	checkVector(v,0.0f,2.0f,0.0f,0.0f);
	CFIXCC_ASSERT_EQUALS(v.magnitudeSqr(), 4.0f);
	CFIXCC_ASSERT_EQUALS(v.magnitude(), 2.0f);
	CFIXCC_ASSERT_EQUALS(v.magnitudeXY(), 2.0f);
	CFIXCC_ASSERT_EQUALS(v.magnitudeXYSqr(), 4.0f);
	v.set(0.0f,0.0f,2.0f);
	checkVector(v,0.0f,0.0f,2.0f,0.0f);
	CFIXCC_ASSERT_EQUALS(v.magnitude(), 2.0f);
	CFIXCC_ASSERT_EQUALS(v.magnitudeSqr(), 4.0f);
	CFIXCC_ASSERT_EQUALS(v.magnitudeXY(), 0.0f);
	CFIXCC_ASSERT_EQUALS(v.magnitudeXYSqr(), 0.0f);
	z.set(0.0f,0.0f,2.00001f);
	CFIX_ASSERT(! (v == z));
	CFIX_ASSERT(v != z);
	CFIX_ASSERT(v.nearlyEquals(z, 0.001f));
	v.set(2,3,4);
	checkVector(v,2,3,4,0.0f);
	v.negate();
	checkVector(v,-2,-3,-4,0.0f);
	v.negate();
	checkVector(v,2,3,4,0.0f);
	v.scale(2);
	checkVector(v,4,6,8,0.0f);
	v.scale(1.0f/4.0f, 1.0f/6.0f, 1.0f/8.0f);
	checkVector(v,1.0f,1.0f,1.0f,0.0f);
	v.scale(scaleV);
	checkVector(v,2.0f,3.0f,4.0f,0.0f);
	v.zero();
	checkVector(v,0.0f,0.0f,0.0f,0.0f);
	v.subtract(1.0f,2.0f,3.0f);
	checkVector(v,-1.0f,-2.0f,-3.0f);
	v.subtract(subtractV);
	CFIX_ASSERT(v.isZero());
	checkVector(v,0.0f,0.0f,0.0f,0.0f);
	v.subtract(9.0f);
	checkVector(v,-9.0f,-9.0f,-9.0f,0.0f);
	// x positive
	v.set(Xpos);
	v.cross(Zpos);
	checkVectorEqual(v, Yneg);
	v.set(Xpos);
	v.cross(Ypos);
	checkVectorEqual(v, Zpos);
	v.set(Xpos);
	v.cross(Zneg);
	checkVectorEqual(v, Ypos);
	v.set(Xpos);
	v.cross(Yneg);
	checkVectorEqual(v, Zneg);
	// y positive
	v.set(Ypos);
	v.cross(Zpos);
	checkVectorEqual(v, Xpos);
	v.set(Ypos);
	v.cross(Xneg);
	checkVectorEqual(v, Zpos);
	v.set(Ypos);
	v.cross(Zneg);
	checkVectorEqual(v, Xneg);
	v.set(Ypos);
	v.cross(Xpos);
	checkVectorEqual(v, Zneg);
	// z positive
	v.set(Zpos);
	v.cross(Yneg);
	checkVectorEqual(v, Xpos);
	v.set(Zpos);
	v.cross(Xpos);
	checkVectorEqual(v, Ypos);
	v.set(Zpos);
	v.cross(Ypos);
	checkVectorEqual(v, Xneg);
	v.set(Zpos);
	v.cross(Xneg);
	checkVectorEqual(v, Yneg);
	// perpendicular
	v.set(2,3,4);
	w.set(v);
	v.perpendicular();
	CFIXCC_ASSERT_EQUALS(v.dot(w), 0.0f);
	v.set(-4,-2,-3);
	w.set(v);
	v.perpendicular();
	CFIXCC_ASSERT_EQUALS(v.dot(w), 0.0f);
}

CFIXCC_BEGIN_CLASS(UTMath)
#if EXTENDED_BY_LUA
CFIXCC_METHOD(testLuaExtension)
#endif//EXTENDED_BY_LUA
CFIXCC_METHOD(testNumbers)
CFIXCC_METHOD(testVector3)
CFIXCC_END_CLASS()
#endif//WITH_UNIT_TESTING