#ifndef LUABUILD_H
#define LUABUILD_H
#include "Platform.h"

struct lua_Debug;
struct lua_State;
struct luaL_Reg;

typedef sint (*lua_function)(lua_State* L);

namespace embeddedLua 
{
	bool isIndexTable(lua_State* L, sint index);
}

#endif//LUABUILD_H