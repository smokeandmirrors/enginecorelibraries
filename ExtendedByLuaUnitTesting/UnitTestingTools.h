#pragma once
#ifndef UNITTESTINGTOOLS_H
#define UNITTESTINGTOOLS_H

#include "Lua.h"

namespace UnitTestingTools
{
#ifdef EXTENDED_BY_LUA 
	void executeLuaUnitTest(char* module, LuaExtension::Lua* lua=NULL);
#endif
} // namespace UnitTestingTools

#endif//UNITTESTINGTOOLS_H