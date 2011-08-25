#pragma once
#ifndef UNITTESTINGTOOLS_H
#define UNITTESTINGTOOLS_H

#include "Build.h"
#if WITH_UNIT_TESTING
#include "Lua.h"

/** 
\note until I figure out from where the Unit testing files run, 
this path will have to be set on a per machine basis
*/
#define UNIT_TESTING_LUA_PACKAGE_PATH \
	"C:\\Users\\carlos.curran\\Documents\\Smoke and Mirrors\\LuaFiles\\?.lua;" \
	"C:\\Users\\carlos.curran\\Documents\\Smoke and Mirrors\\LuaFiles\\UTLuaFiles\\?.lua;"

#define DECLARE_UNIT_TESTING_LUA_OBJECT \
	lua_extension::Lua lua; \
	lua.setPackagePath(UNIT_TESTING_LUA_PACKAGE_PATH);

namespace unit_testing_tools
{
	void checkNearEqual(real4 lhs, real4 rhs, real4 tolerance=0.0f);
	void checkNearEqual(real8 lhs, real8 rhs, real8 tolerance=0.0f);
#if EXTENDED_BY_LUA 
	void executeLuaUnitTest(char* module, lua_extension::Lua* lua=NULL);
#endif
} // namespace unit_testing_tools

#endif//WITH_UNIT_TESTING
#endif//UNITTESTINGTOOLS_H