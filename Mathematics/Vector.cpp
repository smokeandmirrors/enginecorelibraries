#include "Vector.h"

namespace Math
{

// right handed spidey space
const vec_t		vectorTolerance(0.0001f);

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

#if EXTENDED_BY_LUA
#include <assert.h>
#include <string.h>

#include "LuaExtensionInclusions.h"

using namespace LuaExtension;
using namespace Math;

lua_func(__indexVector2)
{
	const char* key = to<const char*>(L, -1);
	const Vector2& v = to<const Vector2&>(L, -2);
	
	if (key[1] == '\0' && (key[0] == 'x' || key[0] == 'y')) 
	{
		return push(L, v[*key - 'x']);
	}
	else
	{	// s:
		lua_getglobal(L, "getClass");
		//s: getClass
		push(L, "Vector2");
		//s: getClass, "Vector2"
		lua_call(L, 1, 1);
		//s: Vector2
		lua_getfield(L, -1, key);
		//s: Vector2[key]
		return 1;
	}
}

lua_func(__newindexVector2)
{
	float value = to<float>(L, -1);
	const char* key = to<const char*>(L, -2);
	Vector2& v = to<Vector2&>(L, -3);
	
	if (key[1] == '\0' && (key[0] == 'x' || key[0] == 'y')) 
	{
		(&v.x)[*key - 'x'] = value;
		return 0;
	}
	else
	{
		return luaL_error(L, "ERROR! the only valid assignable indices for Vector2"
			" are 'x' and 'y'");
	}
}

define_lua_LuaExtendable(Vector2, Vector2)
		lua_named_entry("__index", __indexVector2)
		lua_named_entry("__newindex", __newindexVector2)
		lua_named_entry("__newindexable", LuaExtension::pushFalse) 
		lua_named_entry("add", (return0Param1<Vector2, const Vector2&, &Vector2::add>))
		lua_final_entry 
	};	// end function list 
	sint key(lua_State* L) 
	{ 
		luaL_register(L, "Vector2", Vector2_library); 
		LuaExtendable::declareLuaClass(L, "Vector2", "Vector2"); 
		return 1; 
	} 
}; // end namespace lua_library_Vector2


lua_func(__indexVector3)
{
	const char* key = to<const char*>(L, -1);
	const Vector3& v = to<const Vector3&>(L, -2);
	
	if (key[1] == '\0' 
	&& (key[0] == 'x' || key[0] == 'y' || key[0] == 'z')) 
	{
		return push(L, v[*key - 'x']);
	}
	else
	{	// s:
		lua_getglobal(L, "getClass");
		//s: getClass
		push(L, "Vector3");
		//s: getClass, "Vector3"
		lua_call(L, 1, 1);
		//s: Vector3
		lua_getfield(L, -1, key);
		//s: Vector3[key]
		return 1;
	}
}

lua_func(__newindexVector3)
{
	float value = to<float>(L, -1);
	const char* key = to<const char*>(L, -2);
	Vector3& v = to<Vector3&>(L, -3);
	
	if (key[1] == '\0' 
	&& (key[0] == 'x' || key[0] == 'y' || key[0] == 'z')) 
	{
		(&v.x)[*key - 'x'] = value;
		return 0;
	}
	else
	{
		return luaL_error(L, "ERROR! the only valid assignable indices for Vector3"
			" are 'x', 'y' and 'z'");
	}
}

namespace lua_library_Vector3
{	
#define defineVoidVector3Func(opfunc) \
	lua_func(opfunc) \
	{ \
		sint stack_size = lua_gettop(L); \
		switch (stack_size) \
		{ \
		case 2: \
			{ \
				Vector3& v = to<Vector3&>(L, -2); \
				if (lua_isnumber(L, -1)) \
				{ \
					v.opfunc(to<vec_t>(L, -1)); \
				} \
				else \
				{ \
					v.opfunc(to<const Vector3&>(L, -1)); \
				} \
			} \
			break; \
		case 4: \
			{ \
				Vector3& v = to<Vector3&>(L, -4); \
				v.opfunc(to<vec_t>(L, -3), to<vec_t>(L, -2), to<vec_t>(L, -1)); \
			} \
			break; \
		default: \
		luaL_error(L, "bad parameters to Vector3." #opfunc "()"); \
		} \
		return 0; \
	} 
// #define defineVoidVector3Func(opfunc)

#define defineVector3Operator(name, opfunc) \
	lua_func(name) \
	{ \
		Vector3& lhs = to<Vector3&>(L, -2); \
		Vector3& rhs = to<Vector3&>(L, -1); \
		return push(L, new Vector3(lhs opfunc rhs)); \
	}
// #define defineVector3Operator(opfunc)  

defineVoidVector3Func(add)

lua_func(cross)
{
	sint stack_size = lua_gettop(L);
	switch (stack_size)
	{
	case 2:
		{
			Vector3& v = to<Vector3&>(L, -2);
			v.cross(to<const Vector3&>(L, -1));
		}
		break;
	case 3:
		{
			Vector3& c = to<Vector3&>(L, -3);
			Vector3& a = to<Vector3&>(L, -2);
			Vector3& b = to<Vector3&>(L, -1);
			c.cross(a, b);
		}
		break;
	default:
		luaL_error(L, "bad parameters to Vector3.cross()");
	}
	return 0;
}

defineVoidVector3Func(divide)

lua_func(equals)
{
	sint stack_size = lua_gettop(L); 
	
	switch (stack_size) 
	{ 
	case 2: 
	{ 
		Vector3& lhs = to<Vector3&>(L, -2); 
		Vector3& rhs = to<Vector3&>(L, -1);
		return push(L, lhs.equals(rhs)); 
	} 
	break; 
	case 4: 
	{ 
		Vector3& v = to<Vector3&>(L, -4); 
		return push(L, v.equals(to<vec_t>(L, -3), to<vec_t>(L, -2), to<vec_t>(L, -1))); 
	} 
	break; 
		default: 
		luaL_error(L, "bad parameters to Vector3.equals()"); 
	} 
	return 0; 
}

lua_func(nearlyEquals)
{
	sint stack_size = lua_gettop(L); 

	switch (stack_size) 
	{ 
	case 2: 
		{ 
			Vector3& lhs = to<Vector3&>(L, -2); 
			Vector3& rhs = to<Vector3&>(L, -1);
			return push(L, lhs.nearlyEquals(rhs)); 
		} 
		break; 
	case 3: 
		{ 
			Vector3& lhs = to<Vector3&>(L, -3); 
			Vector3& rhs = to<Vector3&>(L, -4);
			vec_t epsilon = to<vec_t>(L, -1);
			return push(L, lhs.nearlyEquals(rhs, epsilon)); 
		} 
		break; 
	default: 
		luaL_error(L, "bad parameters to Vector3.nearlyEquals()"); 
	} 
	return 0; 
}

lua_func(initialize)
{
	sint stack_size = lua_gettop(L);
	switch (stack_size)
	{
	case 1:
	{
		Vector3& v = to<Vector3&>(L, -1);
		v.zero();
		lua_pushvalue(L, -1);
		return 1;
	}
	break;
	case 2:
	{
		Vector3& v = to<Vector3&>(L, -2);
		if (lua_isnumber(L, -1))
		{
			v.set(to<vec_t>(L, -1));
		}
		else
		{
			v.set(to<Vector3&>(L, -1));
		}
		lua_pushvalue(L, -2);
		return 1;
	}
	break;
	case 3:
	{
		Vector3& v = to<Vector3&>(L, -3);
		v.set(to<sint>(L, -2), to<vec_t>(L, -1));
		lua_pushvalue(L, -3);
		return 1;
	}
	case 4:
	{
		Vector3& v = to<Vector3&>(L, -4);
		v.set(to<vec_t>(L, -3), to<vec_t>(L, -2), to<vec_t>(L, -1));
		lua_pushvalue(L, -4);
		return 1;
	}
	break;
	default:
		luaL_error(L, "bad parameters to Vector3.set()");
		return 0;
	}
} // sint set(lua_State* L)

defineVoidVector3Func(scale)

defineVoidVector3Func(subtract)

} // end namespace lua_library_Vector3

define_lua_LuaExtendable(Vector3, Vector3)
		lua_named_entry("__eq", (return1Param1const<Vector3, bool, const Vector3&, &Vector3::operator==>))
		lua_named_entry("__index", __indexVector3)
		lua_named_entry("__newindex", __newindexVector3) 
		lua_named_entry("__newindexable", LuaExtension::pushFalse)
		lua_entry(		 add)
		lua_named_entry("construct", initialize)
		lua_entry(		 cross)
		lua_named_entry("distance", (return1Param1const<Vector3, vec_t, const Vector3&, &Vector3::distance>))
		lua_named_entry("distanceSqr", (return1Param1const<Vector3, vec_t, const Vector3&, &Vector3::distanceSqr>))
		lua_named_entry("distanceXY", (return1Param1const<Vector3, vec_t, const Vector3&, &Vector3::distanceXY>))
		lua_named_entry("distanceXYSqr", (return1Param1const<Vector3, vec_t, const Vector3&, &Vector3::distanceXYSqr>))
		lua_entry(		 divide)
		lua_named_entry("dot", (return1Param1const<Vector3, vec_t, const Vector3&, &Vector3::dot>))
		lua_entry(		 equals)
		lua_named_entry("isFar", (return1Param2const<Vector3, bool, const Vector3&, vec_t, &Vector3::isFar>))
		lua_named_entry("isFarXY", (return1Param2const<Vector3, bool, const Vector3&, vec_t, &Vector3::isFarXY>))
		lua_named_entry("isNear", (return1Param2const<Vector3, bool, const Vector3&, vec_t, &Vector3::isNear>))
		lua_named_entry("isNearXY", (return1Param2const<Vector3, bool, const Vector3&, vec_t, &Vector3::isNearXY>))
		lua_named_entry("isNormal", (return1Param0const<Vector3, bool, &Vector3::isNormal>))
		lua_named_entry("isZero", (return1Param0const<Vector3, bool, &Vector3::isZero>))
		lua_named_entry("magnitude", (return1Param0const<Vector3, vec_t, &Vector3::magnitude>))
		lua_named_entry("magnitudeSqr", (return1Param0const<Vector3, vec_t, &Vector3::magnitudeSqr>))
		lua_named_entry("magnitudeXY", (return1Param0const<Vector3, vec_t, &Vector3::magnitudeXY>))
		lua_named_entry("magnitudeXYSqr", (return1Param0const<Vector3, vec_t, &Vector3::magnitudeXYSqr>))
		lua_entry(		 nearlyEquals)
		lua_named_entry("negate", (return0Param0<Vector3, &Vector3::negate>))
		lua_named_entry("normalize", (return1Param0<Vector3, vec_t, &Vector3::normalize>))
		lua_named_entry("perpendicular", (return0Param0<Vector3, &Vector3::perpendicular>))
		lua_entry(		 scale)
		lua_named_entry("set", initialize)
		// slightly higher performance options for Lua
		lua_named_entry("setAll", (return0Param1<Vector3, vec_t, &Vector3::set>))
		lua_named_entry("setEach", (return0Param3<Vector3, vec_t, vec_t, vec_t, &Vector3::set>))
		lua_named_entry("setEqual", (return0Param1<Vector3, const Vector3&, &Vector3::set>))
		lua_named_entry("setIndex", (return0Param2<Vector3, uint, vec_t, &Vector3::set>))
		lua_entry(		 subtract)
		lua_named_entry("zero", (return0Param0<Vector3, &Vector3::zero>))
		lua_final_entry 
	};	// end function list 
	sint key(lua_State* L) 
	{ 
		luaL_register(L, "Vector3", Vector3_library); 
		LuaExtendable::declareLuaClass(L, "Vector3", "Vector3"); 
		return 1; 
	} 
}; // end namespace lua_library_Vector3

static const vec_t pi = 3.141592653589793f;

void Math::nativeVectorPerformance(uint iterations)
{
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

	for (uint i(0); i < iterations; i++)
	{
		bool is_true;
		is_true = w == v;
		is_true = v == w;
		v->add(*x);
		v->subtract(*x);
		v->set(pi, pi/2, pi/3);
		v->set(pi/4);
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
		vec_t v_dot_z = v->dot(*z);
		vec_t z_dot_v = z->dot(*v);
		v_dot_z = z_dot_v;
		v->set(*w);
		v->equals(*w);
		w->equals(*v);
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
		is_true = !v->equals(*z);
		is_true = *v == *z;
		v->nearlyEquals(*z);
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

#endif//EXTENDED_BY_LUA
