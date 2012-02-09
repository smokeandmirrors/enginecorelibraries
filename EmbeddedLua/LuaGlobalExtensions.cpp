#include "LuaExtensionInclusions.h"

#include "Vector.h"

namespace embeddedLua
{

/**
\brief
add native functions that you wish to be in the global %Lua namespace here
(in alphabetical order please)
*/
static const luaL_Reg lua_library_Global[] = {
	LUA_ENTRY_NAMED("nativeVectorPerformance", (nativeStaticReturn0Param1<uint, &math::nativeVectorPerformance>))
	LUA_FINAL_ENTRY
};

void registerGlobalLibrary(lua_State* L)
{
	lua_pushglobaltable(L);
	luaL_setfuncs(L, lua_library_Global, 0);
}

} // namespace embeddedLua
