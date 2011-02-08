#include "Vector.h"

// using namespace Math;

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

#ifdef EXTENDED_BY_LUA
#include <assert.h>
#include <string.h>

#include "LuaExtensionInclusions.h"

using namespace LuaExtension;

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
		Vector3& a = to<Vector3&>(L, -2); \
		Vector3& b = to<Vector3&>(L, -1); \
		return push(L, new Vector3(a opfunc b)); \
	}
// #define defineVector3Operator(opfunc)  

defineVoidVector3Func(add)
defineVector3Operator(__add, +)

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
		luaL_error(L, "bad parameters to Vector3.Set()");
	}
	return 0;
}

lua_func(getCross)
{
	Vector3* b = to<Vector3*>(L, -1);
	Vector3* a = to<Vector3*>(L, -2);
	return push(L, new Vector3(a->getCross(*b)));
}

defineVoidVector3Func(divide)
defineVector3Operator(__div, /)

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
defineVector3Operator(__mul, *)

defineVoidVector3Func(subtract)
defineVector3Operator(__sub, -)


} // end namespace lua_library_Vector3

define_lua_LuaExtendable(Vector3, Vector3)
		lua_named_entry("__index", __indexVector3)
		lua_named_entry("__newindex", __newindexVector3) 
		lua_named_entry("__newindexable", LuaExtension::pushFalse)
		lua_entry(__add)
		lua_entry(add)
		lua_named_entry("construct", initialize)
		lua_entry(cross)
		lua_entry(getCross)
		lua_named_entry("distanceTo", (return1Param1const<Vector3, vec_t, const Vector3&, &Vector3::distanceTo>))
		lua_named_entry("distanceToSqrd", (return1Param1const<Vector3, vec_t, const Vector3&, &Vector3::distanceToSqrd>))
		lua_named_entry("distanceToXY", (return1Param1const<Vector3, vec_t, const Vector3&, &Vector3::distanceToXY>))
		lua_named_entry("distanceToXYSqrd", (return1Param1const<Vector3, vec_t, const Vector3&, &Vector3::distanceToXYSqrd>))
		lua_named_entry("isFarFrom", (return1Param2const<Vector3, bool, const Vector3&, vec_t, &Vector3::isFarFrom>))
		lua_named_entry("isFarFromXY", (return1Param2const<Vector3, bool, const Vector3&, vec_t, &Vector3::isFarFromXY>))
		lua_named_entry("isNearTo", (return1Param2const<Vector3, bool, const Vector3&, vec_t, &Vector3::isNearTo>))
		lua_named_entry("isNearToXY", (return1Param2const<Vector3, bool, const Vector3&, vec_t, &Vector3::isNearToXY>))
		lua_entry(divide)
		lua_entry(__div)
		lua_named_entry("dot", (return1Param1const<Vector3, vec_t, const Vector3&, &Vector3::dot>))
		lua_entry(equals)
		lua_entry(nearlyEquals)
		lua_named_entry("__eq", (return1Param1const<Vector3, bool, const Vector3&, &Vector3::operator==>))
		// lua_entry(getPerpendicular)
		lua_named_entry("magnitude", (return1Param0const<Vector3, vec_t, &Vector3::magnitude>))
		lua_named_entry("magnitudeSqrd", (return1Param0const<Vector3, vec_t, &Vector3::magnitudeSqrd>))
		lua_named_entry("magnitudeXY", (return1Param0const<Vector3, vec_t, &Vector3::magnitudeXY>))
		lua_named_entry("magnitudeXYSqrd", (return1Param0const<Vector3, vec_t, &Vector3::magnitudeXYSqrd>))
		lua_named_entry("isNormal", (return1Param0const<Vector3, bool, &Vector3::isNormal>))
		lua_named_entry("normalize", (return1Param0<Vector3, vec_t, &Vector3::normalize>))
		// lua_entry(__unm)
		// lua_entry(negate)
		lua_entry(scale)
		lua_entry(__mul)
		lua_named_entry("set", initialize)
		lua_entry(subtract)
		lua_entry(__sub)
		lua_named_entry("isZero", (return1Param0const<Vector3, bool, &Vector3::isZero>))
		lua_named_entry("zero", (return0Param0<Vector3, &Vector3::zero>))
		// lua_entry(set)
		lua_final_entry 
	};	// end function list 
	sint key(lua_State* L) 
	{ 
		luaL_register(L, "Vector3", Vector3_library); 
		LuaExtendable::declareLuaClass(L, "Vector3", "Vector3"); 
		return 1; 
	} 
}; // end namespace lua_library_Vector3

#endif//EXTENDED_BY_LUA
