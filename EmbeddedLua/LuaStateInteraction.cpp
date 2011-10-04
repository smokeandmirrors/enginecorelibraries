#include "LuaStateInteraction.h"

/**
\note when pushing an object into %Lua, it might not be because the 
object was created by a call to ObjectOrientedParadigm.new() in %Lua.  In this
case, if the class has a extra methods defined in %Lua, especially a 'construct'
method, that %Lua only properties of the object must be initialized the first
time the object is pushed into %Lua

\warning when called at this time (somewhere NOT from a new() call) NO ARGUMENTS WILL 
BE PASSED IN TO THE FUNCTION
*/

sint embeddedLua::push(lua_State* L, LuaExtendable* value)
{
	if (value)
	{
		pushRegisteredClass(L, value);					//s: ud
		lua_getglobal(L, "getmetatable");				//s: ud, getmetatable	
		lua_pushvalue(L, -2);							//s: ud, getmetatable, ud
		lua_call(L, 1, 1);								//s: ud, getmetatable, ?

		if (lua_istable(L, -1))
		{												//s: ud, mt
			lua_pop(L, 1);								//s: ud
		}
		else
		{												//s: ud, nil	
			lua_pop(L, 1);								//s: ud
			lua_getglobal(L, "ObjectOrientedParadigm"); //s: ud, OOP
			lua_getfield(L, -1, "initializers_PRIVATE");//s: ud, OOP, initializers
			lua_replace(L, -2);							//s: ud, initializers
			lua_getfield(L, -1, value->getClassName());	//s: ud, initializers, "class_name"
			lua_replace(L, -2);							//s: ud, class()
			lua_pushvalue(L, -2);						//s: ud, class(), ud
			lua_call(L, 1, 0);							//s: ud
		}
	}
	else 
	{
		lua_pushnil(L);
	}
	return 1;
}