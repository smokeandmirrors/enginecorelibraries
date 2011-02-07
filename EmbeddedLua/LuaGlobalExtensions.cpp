#include "Lua.h"
#include "LuaExtensibility.h"
#include "LuaInclusions.h"
#include "LuaStateInteraction.h"

/**
add native function that you wish to be in the global %Lua namespace
here
*/

namespace LuaExtension
{

lua_func(wtf)
{
	sint stack_size = lua_gettop(L);
	return push(L, stack_size);
}

static const luaL_reg lua_library_Global[] = {
	lua_entry(wtf)
	lua_final_entry
};

void registerGlobalLibrary(lua_State* L)
{
	luaL_register(L, NULL, lua_library_Global);
}

} // namespace LuaExtension
