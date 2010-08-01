#ifdef EXTENDED_BY_LUA
#ifndef GOLDMASTER
#include "Lua.h"
#include "LuaExtensibility.h"
#include "LuaInclusions.h"
#include "LuaLibraryDeclarations.h"
#include <UnitTest++.h>

SUITE(LuaClassTesting) 
{
	TEST(luaObjectCreationAndDestruction)
	{
		Lua* no_args = new Lua();
		CHECK(no_args);
		delete no_args;

		Lua* args_lua = new Lua("testing", false, false);
		CHECK(args_lua);
		CHECK(args_lua);
		delete ;
		
		{
			Lua stack_lua;
			CHECK(stack_lua.getState());
		}
	}

	TEST(luaRequire)
	{
		Lua* lua = new Lua();
		CHECK(lua->require("Utilities"));
		CHECK(lua->require("ObjectOrientedParadigm"));
		delete lua;
	}

	TEST(luaUnitTesting)
	{
		// \todo test the lua unit testing framework
		// \todo run all the lua unit tests
	}

} // SUITE(LuaClassTesting)
#endif//GOLDMASTER	
#endif//EXTENDED_BY_LUA 
