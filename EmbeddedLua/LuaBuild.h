#ifndef LUABUILD_H
#define LUABUILD_H
#include "Build.h"

struct lua_State;
struct lua_Debug;

typedef sint (*lua_function)(lua_State* L);

#endif//LUABUILD_H