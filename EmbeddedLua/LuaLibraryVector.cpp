#ifdef EXTENDED_BY_LUA
#include <assert.h>
#include <string.h>

#include "LuaInclusions.h"
#include "LuaLibraryDeclarations.h"
#include "LuaStateInteraction.h"
#include "LuaExtensibility.h"
#include "Vector.h"

using namespace LuaExtension;

static bool TRUE() { return true; }
static bool FALSE() { return false; }

static sint newVector2(lua_State* L)
{
	lua_newtable(L);
	return 1;
}

define_lua_library(Vector2)
lua_named_entry("new", newVector2)
lua_named_entry("TRUE", (staticReturn1Param0<bool, TRUE>))
lua_named_entry("FALSE", (staticReturn1Param0<bool, FALSE>))
end_lua_library(Vector2)

static sint lua_newVector3(lua_State* L);
static sint luamt__gcVector3(lua_State* L);
static sint luamt__indexVector3(lua_State* L); 
static sint luamt__newindexVector3(lua_State* L);

static sint lua_newVector3(lua_State* L)
{
	Vector3* vector = new Vector3();
	pushRegisteredClass(L, vector);
	return 1;
}

static sint luamt__gcVector3(lua_State* L)
{
	Vector3* udata = *static_cast<Vector3**>(lua_touserdata(L, -1));
	delete udata;
	return 0;
}

//@ todo, if this vector ever goes live, get rid of
// this class' proxy table
// @however, if I do that, this class would have to track
// wether it set a member to NIL or not...
static sint luamt__indexVector3(lua_State* L)
{
	const char* key = lua_tostring(L, -1);
	Vector3* udata = *static_cast<Vector3**>(lua_touserdata(L, -2));
	Vector3& vector = *udata;
	lua_pushnumber(L, static_cast<lua_Number>(vector[*key - 'x']));
	
	return 1;
	/*
	fastest?:
	lua_pushnumber(L, static_cast<lua_Number>((**static_cast<Vector3**>(lua_touserdata(L, -2)))[*lua_tostring(L, -1) - 'x']));
	return 1;

	faster?:
	Vector3* udata = *static_cast<Vector3**>(lua_touserdata(L, -2));
	Vector3& vector = *udata;
	lua_pushnumber(L, static_cast<lua_Number>(vector[*key - 'x']));
	return 1;
	
	slow?:
	
	if (strcmp(key, "x") == 0)
	{
		lua_pushnumber(L, static_cast<lua_Number>(vector.x));
		return 1;
	}
	else if (strcmp(key, "y") == 0)
	{
		lua_pushnumber(L, static_cast<lua_Number>(vector.y));
		return 1;
	}
	else if (strcmp(key, "z") == 0)
	{
		lua_pushnumber(L, static_cast<lua_Number>(vector.z));
		return 1;
	}
	*/
}

// do the same thing with index
static sint luamt__newindexVector3(lua_State* L) 
{	/** @todo find out how much to pop */	//s: table,	k, v 	
	float value = static_cast<float>(lua_tonumber(L, -1));
	const char* key = lua_tostring(L, -2);
	Vector3* udata = *static_cast<Vector3**>(lua_touserdata(L, -3));
	Vector3& vector = *udata;
	(&vector.x)[*key - 'x'] = value;
	lua_pop(L, 3); 
	return 0;
	/*
	if (strcmp(key, "x") == 0)
	{
		udata->x = value;
	}
	else if (strcmp(key, "y") == 0)
	{
		float value = static_cast<float>(lua_tonumber(L, -1));
		Vector3* udata = *static_cast<Vector3**>(lua_touserdata(L, -3));
		udata->y = value;
	}
	else if (strcmp(key, "z") == 0)
	{
		float value = static_cast<float>(lua_tonumber(L, -1));
		Vector3* udata = *static_cast<Vector3**>(lua_touserdata(L, -3));
		udata->z = value;
	}

	lua_pushvalue(L, lua_upvalueindex(1));	//s: table, k, v, proxy
	lua_replace(L, -4);						//s: proxy, k, v
	lua_rawset(L, -3);						//s: proxy
	lua_pop(L, 1);							//s: 
	return 0;
	*/
}

sint lua_setmetatableVector3(lua_State* L)
{										//s: userdata, lua_class_mt
	lua_newtable(L);					//s: userdata, lua_class_mt, proxy
	lua_insert(L, -2);					//s: userdata, proxy, lua_class_mt
	lua_setmetatable(L, -2);			//s: userdata, proxy/mt
	lua_newtable(L);					//s: userdata, proxy/mt, userdata_mt
	lua_pushvalue(L, -2);				//s: userdata, proxy/mt, userdata_mt, proxy/mt
	lua_setfield(L, -2, "__index");		//s: userdata, proxy/mt, userdata_mt
	lua_pushvalue(L, -2);				//s: userdata, proxy/mt, userdata_mt, proxy/mt
	lua_pushcclosure(L, luamt__newindexVector3, 1);	
										//s: userdata, proxy/mt, userdata_mt, __newindexProxy
	lua_setfield(L, -2, "__newindex");	//s: userdata, proxy/mt, userdata_mt
	lua_pushcfunction(L, luamt__gcVector3);
	lua_setfield(L, -2, "__gc");		//s: userdata, proxy/mt
	lua_pushcfunction(L, luamt__indexVector3);	
										//s: userdata, proxy/mt, __gcLuaExtendable
	lua_setfield(L, -2, "__index");	
	lua_setmetatable(L, -3);			//s: userdata/mt, proxy/mt
	lua_pop(L, 1);						//s: userdata/mt
	return 1;
}


define_lua_library(Vector3)
lua_named_entry("new", lua_newVector3)
lua_named_entry("setmetatable", lua_setmetatableVector3)
end_lua_library(Vector3)
#endif//EXTENDED_BY_LUA
