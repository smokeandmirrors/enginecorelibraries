#if 0
// #if EXTENDED_BY_LUA
#include <cfixcc.h>
#include "Lua.h"
#include "LuaExtensibility.h"
#include "LuaInclusions.h"
#include "LuaLibraryDeclarations.h"
class LuaClass : public cfixcc::TestFixture
{
private:

public:
	
public:
	void luaObjectCreationAndDestruction()
	{
		Lua* no_args = new Lua();
		CFIX_ASSERT(no_args);
		CFIX_ASSERT(no_args->getState());
		delete no_args;

		Lua* args_lua = new Lua("testing", false, false);
		CFIX_ASSERT(args_lua);
		CFIX_ASSERT(args_lua->getState());
		delete args_lua;
		
		Lua stack_lua;
		CFIX_ASSERT(stack_lua.getState());
	}

	void luaRequire()
	{
		Lua* lua = new Lua();
		CFIX_ASSERT(lua->require("Utilities"));
		CFIX_ASSERT(lua->require("ObjectOrientedParadigm"));
		delete lua;
	}

	void doString()
	{	
		Lua lua;
		lua.doString("print\'Hello!\'");
	}
		
	void luaUnitTesting()
	{
		Lua* lua = new Lua();
		lua->require("Utilities");
		lua->require("ObjectOrientedParadigm");
		// registration must be done in dependency order
		register_lua_library(lua, Vector2) 
		register_lua_library(lua, Vector3)
		lua->require("Vector3PureLua");
		lua->require("User");
		lua->require("UnitTesting");
		// \todo run all the lua unit tests
	}
};

CFIXCC_BEGIN_CLASS(LuaClass)
	CFIXCC_METHOD(luaObjectCreationAndDestruction)
	CFIXCC_METHOD(luaRequire)
	CFIXCC_METHOD(doString)
	CFIXCC_METHOD(luaUnitTesting)
CFIXCC_END_CLASS()
#endif//EXTENDED_BY_LUA
