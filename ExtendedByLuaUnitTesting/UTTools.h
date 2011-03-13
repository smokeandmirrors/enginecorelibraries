#pragma once
#ifndef UNITTESTINGTOOLS_H
#define UNITTESTINGTOOLS_H

#include "Build.h"
#if WITH_UNIT_TESTING

#include "Lua.h"

namespace unitTestingTools
{
	void checkNearEqual(real4 lhs, real4 rhs, real4 tolerance=0.0f);
	void checkNearEqual(real8 lhs, real8 rhs, real8 tolerance=0.0f);
#if EXTENDED_BY_LUA 
	void executeLuaUnitTest(char* module, lua_extension::Lua* lua=NULL);
#endif
} // namespace unitTestingTools

#endif//WITH_UNIT_TESTING
#endif//UNITTESTINGTOOLS_H