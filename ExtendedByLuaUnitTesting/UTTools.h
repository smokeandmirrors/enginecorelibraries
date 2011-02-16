#pragma once
#ifndef UNITTESTINGTOOLS_H
#define UNITTESTINGTOOLS_H

#include "Build.h"
#if WITH_UNIT_TESTING

#include "Lua.h"

namespace unitTestingTools
{
	void checkNearEqual(float lhs, float rhs, float tolerance=0.0f);
	void checkNearEqual(double lhs, double rhs, double tolerance=0.0f);
#if EXTENDED_BY_LUA 
	void executeLuaUnitTest(char* module, luaExtension::Lua* lua=NULL);
#endif
} // namespace unitTestingTools

#endif//WITH_UNIT_TESTING
#endif//UNITTESTINGTOOLS_H