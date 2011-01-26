#pragma once
#ifndef UNITTESTINGTOOLS_H
#define UNITTESTINGTOOLS_H

#include "Lua.h"

namespace UnitTestingTools
{
	/**
	the wchar_t* returned must be deleted[].
	*/
#ifdef EXTENDED_BY_LUA 
	void executeLuaUnitTest(char* module, LuaExtension::Lua* lua=NULL);
#endif
} // namespace UnitTestingTools

#endif//UNITTESTINGTOOLS_H