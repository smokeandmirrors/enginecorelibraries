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

/*
#define UNIT_TESTING_LUA_PACKAGE_PATH \
	"D:\\enginecorelibraries\\LuaFiles\\?.lua;" \
	"D:\\enginecorelibraries\\LuaFiles\\UTLuaFiles\\?.lua;"
*/

#define DECLARE_UNIT_TESTING_LUA_OBJECT \
	embeddedLua::Lua lua; \
	lua.setPackagePath(UNIT_TESTING_LUA_PACKAGE_PATH);

namespace unit_testing_tools
{
	void checkNearEqual(sreal lhs, sreal rhs, sreal tolerance=0.0f);
	void checkNearEqual(dreal lhs, dreal rhs, dreal tolerance=0.0f);
#if EXTENDED_BY_LUA 
	void executeLuaUnitTest(char* module, embeddedLua::Lua* lua=NULL);
#endif
} // namespace unit_testing_tools

#endif//WITH_UNIT_TESTING
#endif//UNITTESTINGTOOLS_H