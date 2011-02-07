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
sint initialize(lua_State* L)
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
		luaL_error(L, "bad parameters to Vector3.Set()");
		return 0;
	}
} // sint set(lua_State* L)

} // end namespace lua_library_Vector3

define_lua_LuaExtendable(Vector3, Vector3)
		lua_named_entry("__index", __indexVector3)
		lua_named_entry("__newindex", __newindexVector3) 
		lua_named_entry("__newindexable", LuaExtension::pushFalse) 
		lua_named_entry("add", (return0Param1<Vector3, const Vector3&, &Vector3::add>))
		lua_named_entry("construct", initialize)
		lua_named_entry("set", initialize)
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
