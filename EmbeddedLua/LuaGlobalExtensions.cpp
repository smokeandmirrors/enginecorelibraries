#include "LuaExtensionInclusions.h"
#include "Vector.h"

namespace luaExtension
{

/**
\brief
add native functions that you wish to be in the global %Lua namespace here
(in alphabetical order please)
*/
static const luaL_reg lua_library_Global[] = {
	LUA_NAMED_ENTRY("nativeVectorPerformance", (staticReturn0Param1<uint, &math::nativeVectorPerformance>))
	LUA_FINAL_ENTRY
};

void registerGlobalLibrary(lua_State* L)
{
	luaL_register(L, NULL, lua_library_Global);
}

} // namespace luaExtension
