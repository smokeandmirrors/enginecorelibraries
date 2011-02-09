#pragma once
#ifndef UNITTESTINGTOOLS_H
#define UNITTESTINGTOOLS_H

#include "Build.h"
#if BUILD_WITH_UNIT_TESTING

#include "Lua.h"

namespace UnitTestingTools
{
#if EXTENDED_BY_LUA 
	void executeLuaUnitTest(char* module, LuaExtension::Lua* lua=NULL);
#endif
} // namespace UnitTestingTools

#endif//BUILD_WITH_UNIT_TESTING
#endif//UNITTESTINGTOOLS_H