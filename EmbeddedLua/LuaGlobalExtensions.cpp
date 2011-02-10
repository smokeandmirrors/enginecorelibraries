#include "Lua.h"
#include "LuaExtensibility.h"
#include "LuaInclusions.h"
#include "LuaStateInteraction.h"

#include "Vector.h"
/**
add native function that you wish to be in the global %Lua namespace
here
*/

namespace luaExtension
{

static const luaL_reg lua_library_Global[] = {
	lua_named_entry("nativeVectorPerformance", (staticReturn0Param1<uint, &math::nativeVectorPerformance>))
	lua_final_entry
};

void registerGlobalLibrary(lua_State* L)
{
	luaL_register(L, NULL, lua_library_Global);
}

} // namespace luaExtension
