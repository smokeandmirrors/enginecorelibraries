#if EXTENDED_BY_LUA
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
		bool result = lua->require("Utilities"); 
		CFIX_ASSERT(result);
		result = lua->require("ObjectOrientedParadigm");
		CFIX_ASSERT(result);
		delete lua;
	}

	void doString()
	{	
		Lua lua;
		lua.doString("print\'Hello!\'");
	}
		
	void luaUnitTesting()
	{
		Lua lua;
		lua.require("UnitTesting");
		lua_State* L = lua.getState();
		lua_getglobal(L, "unitTestSuccessful"); //s: unitTestSuccessful
		int result = lua_toboolean(L, -1);		//s: unitTestSuccessful
		lua_pop(L, 1);
		// \todo get the results of the lua unit testing failure string
		// report it with the message
		CFIX_ASSERT(result);
	}
};

CFIXCC_BEGIN_CLASS(LuaClass)
	CFIXCC_METHOD(luaObjectCreationAndDestruction)
	CFIXCC_METHOD(luaRequire)
	CFIXCC_METHOD(doString)
	CFIXCC_METHOD(luaUnitTesting)
CFIXCC_END_CLASS()
#endif//EXTENDED_BY_LUA
