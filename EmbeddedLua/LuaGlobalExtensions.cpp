#include "Lua.h"
#include "LuaExtensibility.h"
#include "LuaInclusions.h"
#include "LuaStateInteraction.h"

namespace luaExtension
{

/**
\brief
add native functions that you wish to be in the global %Lua namespace here
(in alphabetical order please)
*/
static const luaL_reg lua_library_Global[] = {
	lua_final_entry
};

void registerGlobalLibrary(lua_State* L)
{
	luaL_register(L, NULL, lua_library_Global);
}

} // namespace luaExtension
