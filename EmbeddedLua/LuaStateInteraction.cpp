#include "LuaStateInteraction.h"

LuaExtension::LuaExtendable* LuaExtension::toLuaExtendable(lua_State* L, int index)
{
	assert_lua_argument(lua_isuserdata, "LuaExtendable", L, index);
	return static_cast<LuaExtension::LuaExtendable*>(lua_touserdata(L, index));
}