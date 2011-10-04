#include "LuaMathExtensions.h"

#if EXTENDED_BY_LUA
#include <assert.h>
#include <string.h>
#endif//EXTENDED_BY_LUA

#include "Numbers.h"
#include "Vector.h"

#if EXTENDED_BY_LUA
#include "LuaExtensionInclusions.h"
#include "LuaExposeNativeToScript.h"
#include "LuaMathExtensions.h"
using namespace embeddedLua;
#endif//EXTENDED_BY_LUA
using namespace math;

#if EXTENDED_BY_LUA

DEFINE_LUA_CLASS_PUSH_FUNCTION(Vector2)
DEFINE_LUA_CLASS_PUSH_FUNCTION(Vector3)

namespace lua_library_Vector2 
{
	LUA_FUNC(__indexVector2)
	{
		const schar* key = to<const schar*>(L, -1);
		const Vector2& v = to<const Vector2&>(L, -2);

		if (key[1] == '\0' && (key[0] == 'x' || key[0] == 'y')) 
		{
			return push(L, v[*key - 'x']);
		}
		else
		{									//s:
			lua_getglobal(L, "getClass");	//s: getClass
			push(L, "Vector2");				//s: getClass, "Vector2"
			lua_call(L, 1, 1);				//s: Vector2
			lua_getfield(L, -1, key);		//s: Vector2[key]
			return 1;
		}
	}

	LUA_FUNC(__newindexVector2)
	{
		sreal value = to<sreal>(L, -1);
		const schar* key = to<const schar*>(L, -2);
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

	DEFINE_LUA_CLASS_AUTO_METAMETHODS(Vector2)
	
	static const luaL_reg Vector2_library[] = 
	{
		LUA_ENTRY_NAMED("__gc", embeddedLua::__gcmetamethod<Vector2>)
		LUA_ENTRY_CLASS__isnewindexable_FALSE
		LUA_ENTRY_CLASS__new_AUTO(Vector2)
		LUA_ENTRY_CLASS__setmetatable_USERDATA
		LUA_ENTRY_CLASS__tostring_AUTO(Vector2)
		LUA_ENTRY_NAMED("__index", __indexVector2)
		LUA_ENTRY_NAMED("__newindex", __newindexVector2)
		LUA_ENTRY_NAMED("add", (nativeMemberReturn0Param1<Vector2, const Vector2&, &Vector2::add>))
END_LUA_CLASS(Vector2, Vector2)

namespace lua_library_Vector3
{	
#define DEFINE_VOID_VECTOR3_FUNC(opfunc) \
	LUA_FUNC(opfunc) \
	{ \
	sint stack_size = lua_gettop(L); \
	switch (stack_size) \
	{ \
	case 2: \
	{ \
	Vector3& v = to<Vector3&>(L, -2); \
	if (lua_isnumber(L, -1)) \
	{ \
	v.opfunc(to<sreal>(L, -1)); \
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
	v.opfunc(to<sreal>(L, -3), to<sreal>(L, -2), to<sreal>(L, -1)); \
} \
	break; \
		default: \
		luaL_error(L, "bad parameters to Vector3." #opfunc "()"); \
} \
	return 0; \
} 
	
#define DEFINE_VECTOR3_OPERATOR(name, opfunc) \
	LUA_FUNC(name) \
	{ \
	Vector3& lhs = to<Vector3&>(L, -2); \
	Vector3& rhs = to<Vector3&>(L, -1); \
	return push(L, new Vector3(lhs opfunc rhs)); \
}
	
	DEFINE_VOID_VECTOR3_FUNC(add)

	LUA_FUNC(cross)
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

	DEFINE_VOID_VECTOR3_FUNC(divide)

	LUA_FUNC(equals)
	{
		sint stack_size = lua_gettop(L); 

		switch (stack_size) 
		{ 
		case 2: 
			{ 
				Vector3& lhs = to<Vector3&>(L, -2); 
				Vector3& rhs = to<Vector3&>(L, -1);
				return push(L, lhs == rhs); 
			} 
			break; 
		case 4: 
			{ 
				Vector3& v = to<Vector3&>(L, -4); 
				return push(L, v.equals(to<sreal>(L, -3), to<sreal>(L, -2), to<sreal>(L, -1))); 
			} 
			break; 
		default: 
			luaL_error(L, "bad parameters to Vector3.equals()"); 
		} 
		return 0; 
	}

	LUA_FUNC(nearlyEquals)
	{
		sint stack_size = lua_gettop(L); 

		switch (stack_size) 
		{ 
		case 2: 
			{ 
				Vector3& lhs = to<Vector3&>(L, -2); 
				Vector3& rhs = to<Vector3&>(L, -1);
				return push(L, lhs.nearlyEquals(rhs, 0.001f)); 
			} 
			break; 
		case 3: 
			{ 
				Vector3& lhs = to<Vector3&>(L, -3); 
				Vector3& rhs = to<Vector3&>(L, -4);
				sreal epsilon = to<sreal>(L, -1);
				return push(L, lhs.nearlyEquals(rhs, epsilon)); 
			} 
			break; 
		default: 
			luaL_error(L, "bad parameters to Vector3.nearlyEquals()"); 
		} 
		return 0; 
	}

	LUA_FUNC(initialize)
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
					v.set(to<sreal>(L, -1));
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
				v.set(to<sint>(L, -2), to<sreal>(L, -1));
				lua_pushvalue(L, -3);
				return 1;
			}
		case 4:
			{
				Vector3& v = to<Vector3&>(L, -4);
				v.set(to<sreal>(L, -3), to<sreal>(L, -2), to<sreal>(L, -1));
				lua_pushvalue(L, -4);
				return 1;
			}
			break;
		default:
			luaL_error(L, "bad parameters to Vector3.set()");
			return 0;
		}
	} // sint set(lua_State* L)

	DEFINE_VOID_VECTOR3_FUNC(scale)
	DEFINE_VOID_VECTOR3_FUNC(subtract)

	LUA_FUNC(__indexVector3)
	{
		const schar* key = to<const schar*>(L, -1);
		const Vector3& v = to<const Vector3&>(L, -2);

		if (key[1] == '\0' 
			&& (key[0] == 'x' || key[0] == 'y' || key[0] == 'z')) 
		{
			return push(L, v[*key - 'x']);
		}
		else
		{									//s:
			lua_getglobal(L, "getClass");	//s: getClass
			push(L, "Vector3");				//s: getClass, "Vector3"
			lua_call(L, 1, 1);				//s: Vector3
			lua_getfield(L, -1, key);		//s: Vector3[key]
			return 1;
		}
	}

	LUA_FUNC(__newindexVector3)
	{
		sreal value = to<sreal>(L, -1);
		const schar* key = to<const schar*>(L, -2);
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

	DEFINE_LUA_CLASS_AUTO_METAMETHODS(Vector3)
		
	static const luaL_reg Vector3_library[] = 
	{
		LUA_ENTRY_NAMED("__gc", embeddedLua::__gcmetamethod<Vector3>)
		LUA_ENTRY_CLASS__isnewindexable_FALSE
		LUA_ENTRY_CLASS__new_AUTO(Vector3)
		LUA_ENTRY_CLASS__setmetatable_USERDATA
		LUA_ENTRY_CLASS__tostring_AUTO(Vector3)
		LUA_ENTRY_NAMED("__index", __indexVector3)
		LUA_ENTRY_NAMED("__newindex", __newindexVector3)
		LUA_ENTRY_NAMED("__eq", (nativeConstReturn1Param1<Vector3, bool, const Vector3&, &V3<float>::operator==>))
		LUA_ENTRY_CLASS__isnewindexable_FALSE
		LUA_ENTRY(		 add)
		LUA_ENTRY_NAMED("construct", initialize)
		LUA_ENTRY(		 cross)
		LUA_ENTRY_NAMED("distance", (nativeConstReturn1Param1<Vector3, sreal, const Vector3&, &V3<float>::distance>))
		LUA_ENTRY_NAMED("distanceSqr", (nativeConstReturn1Param1<Vector3, sreal, const Vector3&, &V3<float>::distanceSqr>))
		LUA_ENTRY_NAMED("distanceXY", (nativeConstReturn1Param1<Vector3, sreal, const Vector3&, &V3<float>::distanceXY>))
		LUA_ENTRY_NAMED("distanceXYSqr", (nativeConstReturn1Param1<Vector3, sreal, const Vector3&, &V3<float>::distanceXYSqr>))
		LUA_ENTRY(		 divide)
		LUA_ENTRY_NAMED("dot", (nativeConstReturn1Param1<Vector3, sreal, const Vector3&, &V3<float>::dot>))
		LUA_ENTRY(		 equals)
		LUA_ENTRY_NAMED("isFar", (nativeConstReturn1Param2<Vector3, bool, const Vector3&, sreal, &V3<float>::isFar>))
		LUA_ENTRY_NAMED("isFarXY", (nativeConstReturn1Param2<Vector3, bool, const Vector3&, sreal, &V3<float>::isFarXY>))
		LUA_ENTRY_NAMED("isNear", (nativeConstReturn1Param2<Vector3, bool, const Vector3&, sreal, &V3<float>::isNear>))
		LUA_ENTRY_NAMED("isNearXY", (nativeConstReturn1Param2<Vector3, bool, const Vector3&, sreal, &V3<float>::isNearXY>))
		LUA_ENTRY_NAMED("isNormal", (nativeConstReturn1Param0<Vector3, bool, &V3<float>::isNormal>))
		LUA_ENTRY_NAMED("isZero", (nativeConstReturn1Param0<Vector3, bool, &V3<float>::isZero>))
		LUA_ENTRY_NAMED("magnitude", (nativeConstReturn1Param0<Vector3, sreal, &V3<float>::magnitude>))
		LUA_ENTRY_NAMED("magnitudeSqr", (nativeConstReturn1Param0<Vector3, sreal, &V3<float>::magnitudeSqr>))
		LUA_ENTRY_NAMED("magnitudeXY", (nativeConstReturn1Param0<Vector3, sreal, &V3<float>::magnitudeXY>))
		LUA_ENTRY_NAMED("magnitudeXYSqr", (nativeConstReturn1Param0<Vector3, sreal, &V3<float>::magnitudeXYSqr>))
		LUA_ENTRY(		 nearlyEquals)
		LUA_ENTRY_NAMED("negate", (nativeMemberReturn0Param0<Vector3, &V3<float>::negate>))
		LUA_ENTRY_NAMED("normalize", (nativeMemberReturn1Param0<Vector3, sreal, &V3<float>::normalize>))
		LUA_ENTRY_NAMED("perpendicular", (nativeMemberReturn0Param0<Vector3, &V3<float>::perpendicular>))
		LUA_ENTRY(		 scale)
		LUA_ENTRY_NAMED("set", initialize)
		// slightly higher performance options for Lua
		LUA_ENTRY_NAMED("setAll", (nativeMemberReturn0Param1<Vector3, sreal, &V3<float>::set>))
		LUA_ENTRY_NAMED("setEach", (nativeMemberReturn0Param3<Vector3, sreal, sreal, sreal, &V3<float>::set>))
		LUA_ENTRY_NAMED("setEqual", (nativeMemberReturn0Param1<Vector3, const Vector3&, &V3<float>::set>))
		LUA_ENTRY_NAMED("setIndex", (nativeMemberReturn0Param2<Vector3, uint, sreal, &V3<float>::set>))
		LUA_ENTRY(		 subtract)
		LUA_ENTRY_NAMED("zero", (nativeMemberReturn0Param0<Vector3, &V3<float>::zero>))
END_LUA_CLASS(Vector3, Vector3)

#endif//EXTENDED_BY_LUA