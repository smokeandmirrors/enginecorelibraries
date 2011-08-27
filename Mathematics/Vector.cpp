#if EXTENDED_BY_LUA
#include <assert.h>
#include <string.h>
#endif//EXTENDED_BY_LUA

#include "Numbers.h"
#include "Vector.h"

#if EXTENDED_BY_LUA
#include "LuaExtensionInclusions.h"
#include "LuaFunctionExposition.h"
#include "LuaMathExtensions.h"
using namespace lua_extension;
#endif//EXTENDED_BY_LUA
using namespace math;

namespace math 
{
// right handed spidey space
const Vector2	down2D		( 0.0f, -1.0f);
const Vector2	left2D		(-1.0f,  0.0f);
const Vector2	origin2D	( 0.0f,  0.0f);
const Vector2	right2D		( 0.0f,	 1.0f);
const Vector2	up2D		( 1.0f,  0.0f);

const Vector3	backward3D	( 0.0f, -1.0f,  0.0f);
const Vector3	down3D		( 0.0f,  0.0f, -1.0f);
const Vector3	forward3D	( 0.0f,  1.0f,  0.0f);
const Vector3	left3D		(-1.0f,  0.0f,  0.0f);
const Vector3	origin3D	( 0.0f,  0.0f,  0.0f);
const Vector3	right3D		( 1.0f,  0.0f,  0.0f);
const Vector3	up3D		( 0.0f,  0.0f,  1.0f);
}

void math::nativeVectorPerformance(uint4 iterations)
{	/** 
	this function simply tries to emulate a %Lua vector performance
	function as closely as possible for fair comparison 
	*/
	Vector3* v = new Vector3(3.0f,2.0f,1.0f);
	Vector3* w = new Vector3(3.0f,2.0f,1.0f);
	Vector3* x = new Vector3(1.0f,3.0f,2.0f);
	Vector3* z = new Vector3();
	Vector3* scaleV = new Vector3(2,3,4);
	Vector3* subtractV = new Vector3( -1,-2,-3);
	Vector3* Xpos = new Vector3( 1, 0, 0);
	Vector3* Ypos = new Vector3( 0, 1, 0);
	Vector3* Zpos = new Vector3( 0, 0, 1);
	Vector3* Xneg = new Vector3(-1, 0, 0);
	Vector3* Yneg = new Vector3( 0,-1, 0);
	Vector3* Zneg = new Vector3( 0, 0,-1);

	for (uint4 i(0); i < iterations; i++)
	{
		bool is_true;
		is_true = w == v;
		is_true = v == w;
		v->add(*x);
		v->subtract(*x);
		v->set(real4_pi, real4_pi/2, real4_pi/3);
		v->set(real4_pi/4);
		v->set(*w);
		v->set(10,0,0);
		v->distance(*z);
		v->distanceSqr(*z);
		v->distanceXY(*z);
		v->distanceXYSqr(*z); 
		v->set(0,10,0);
		v->distance(*z);
		v->distanceSqr(*z);
		v->distanceXY(*z); 
		v->distanceXYSqr(*z);
		v->set(0,0,10);
		v->distance(*z);
		v->distanceSqr(*z); 
		v->distanceXY(*z); 
		v->distanceXYSqr(*z); 
		v->set(1,1,1);
		v->distance(*z); 
		v->distanceSqr(*z); 
		v->distanceXY(*z); 
		v->distanceXYSqr(*z); 
		v->normalize();
		v->distance(*z); 
		v->distanceSqr(*z); 
		v->set(0,1,1);
		v->distanceXY(*z); 
		v->distanceXYSqr(*z); 
		v->set(8,4,2);
		v->divide(2);
		v->set(8,4,2);
		v->divide(8,4,2);
		v->set(100,100,100);
		v->divide(50, 25, 10);
		v->set(1,2,3);
		z->set(-1,-2,-3);
		real4 v_dot_z = v->dot(*z);
		real4 z_dot_v = z->dot(*v);
		v_dot_z = z_dot_v;
		v->set(*w);
		*v == *w;
		*w == *v;
		v->zero();
		z->set(0,0,10);
		v->isFar(*z,5);
		is_true = ! v->isFar(*z,10);
		is_true = ! v->isFarXY(*z,0);
		is_true = ! v->isFarXY(*z,0);
		is_true = v->isNear(*z,10);
		is_true = ! v->isNear(*z,9.99f);
		is_true = v->isNearXY(*z,0);
		v->set(10000000, 0, 0);
		v->normalize();
		v->isNormal();
		v->magnitude();
		v->set(0, 10000000, 0);
		v->normalize();
		v->isNormal();
		v->magnitude();
		v->set(0, 0, 10000000);
		v->normalize();
		is_true = v->isNormal();
		v->magnitude();
		is_true = ! w->isNormal();
		is_true = ! w->isZero();
		v->set(0);
		v->isZero();
		v->set(2,0,0);
		v->magnitude();
		v->magnitudeSqr();
		v->magnitudeXY();
		v->magnitudeXYSqr();
		v->set(0,2,0);
		v->magnitudeSqr();
		v->magnitude();
		v->magnitudeXY();
		v->magnitudeXYSqr();
		v->set(0,0,2);
		v->magnitude();
		v->magnitudeSqr();
		v->magnitudeXY();
		v->magnitudeXYSqr();
		z->set(0,0,2.00001f);
		is_true = *v == *z;
		is_true = *v == *z;
		v->nearlyEquals(*z, 0.001f);
		v->set(2,3,4);
		v->negate();
		v->negate();
		v->scale(2);
		v->scale(1/4, 1/6, 1/8);
		v->scale(*scaleV);
		v->zero();
		v->subtract(1,2,3);
		v->subtract(*subtractV);
		is_true = v->isZero();
		v->subtract(9);
		// x positive
		v->set(*Xpos);
		v->cross(*Zpos);
		v->set(*Xpos);
		v->cross(*Ypos);
		v->set(*Xpos);
		v->cross(*Zneg);
		v->set(*Xpos);
		v->cross(*Yneg);
		// y positive
		v->set(*Ypos);
		v->cross(*Zpos);
		v->set(*Ypos);
		v->cross(*Xneg);
		v->set(*Ypos);
		v->cross(*Zneg);
		v->set(*Ypos);
		v->cross(*Xpos);
		// z positive
		v->set(*Zpos);
		v->cross(*Yneg);
		v->set(*Zpos);
		v->cross(*Xpos);
		v->set(*Zpos);
		v->cross(*Ypos);
		v->set(*Zpos);
		v->cross(*Xneg);
		// perpendicular
		v->set(2,3,4);
		w->set(*v);
		v->perpendicular();
		v->dot(*w);
		v->set(-4,-2,-3);
		w->set(*v);
		v->perpendicular();
	}

	delete v;
	delete w;
	delete x;
	delete z;
	delete  scaleV ; // Vector3(2,3,4);
	delete  subtractV ; // Vector3( -1,-2,-3);
	delete  Xpos ; // Vector3( 1, 0, 0);
	delete  Ypos ; // Vector3( 0, 1, 0);
	delete  Zpos ; // Vector3( 0, 0, 1);
	delete  Xneg ; // Vector3(-1, 0, 0);
	delete  Yneg ; // Vector3( 0,-1, 0);
	delete  Zneg ; // Vector3( 0, 0,-1);
}


