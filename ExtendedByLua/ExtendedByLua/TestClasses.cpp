#include <string.h>
#include "TestClasses.h"
#include "LuaInclusions.h"
#include "LuaLibraryDeclarations.h"
#include "LuaRegistration.h"

/*
Granparent implementation
*/
bool Grandparent::operator==(const Grandparent& other) const
{
	return strcmp(getFamilyName(), other.getFamilyName()) == 0; 
}

const char* Grandparent::toString()
{ 
	return "This is a Grandparent"; 
}
#ifdef EXTENDED_BY_LUA
int Grandparent::setMetatable(lua_State *L)
{												
	return setDefaultMetatableProxy(L);
}

lua_func(__call)
{
	Grandparent* gp = *static_cast<Grandparent**>(lua_touserdata(L, -1));
	printToLua(L, gp->toString());
	return 0;
}

lua_func(getFamilyName)
{
	Grandparent* gp = *static_cast<Grandparent**>(lua_touserdata(L, -1));
	lua_pushstring(L, gp->getFamilyName());
	return 1;
}

lua_func(getTitle)
{
	Grandparent* gp = *static_cast<Grandparent**>(lua_touserdata(L, -1));
	lua_pushstring(L, gp->getTitle());
	return 1;
}

define_lua_class(Grandparent, Grandparent)
	lua_entry(__call) 
	lua_entry(getFamilyName)
	lua_entry(getTitle)
end_lua_class(Grandparent, Grandparent)
#endif//EXTENDED_BY_LUA


/* 
Basic implementation
*/
#ifdef EXTENDED_BY_LUA
int Basic::setMetatable(lua_State* L)
{
	// return setDefaultClassMetatable(L);
	return 0;
}

const char* Basic::toString(void)
{
	return "This is a Basic.";
}

static Basic* b(NULL);

lua_func(newBasic)
{
	pushRegisteredClass(L, new Basic());	//s: ud
	lua_newtable(L);						//s: ud, ud_mt
	lua_getglobal(L, "Basic");				//s: ud, ud_mt, Basic
	lua_setfield(L, -2, "__index");			//s: ud, ud_mt
	lua_setmetatable(L, -2);				//s: ud/mt
	return 1;
}

lua_func(getBasic)
{
	static Basic* b(NULL);
	
	if (!b)
	{
		b = new Basic();
		pushRegisteredClass(L,b);	//s: ud
		lua_newtable(L);						//s: ud, ud_mt
		lua_getglobal(L, "Basic");				//s: ud, ud_mt, Basic
		lua_setfield(L, -2, "__index");			//s: ud, ud_mt
		lua_setmetatable(L, -2);				//s: ud/mt
	}
	else
	{
		pushRegisteredClass(L,b);	//s: ud
	}
	
	return 1;
}

lua_func(basicFromC)
{
	lua_pushstring(L, "This function came from C!");
	return 1;
}

define_lua_class(Basic, Basic)
	lua_named_entry("new", newBasic)
	lua_named_entry("get", getBasic)
	lua_named_entry("fromC", basicFromC)
end_lua_class(Basic, Basic)

/*
Derived implementation
*/
int Derived::setMetatable(lua_State* L)
{	/**
	\leftoff
	*/
	return setDefaultMetatableProxy(L);
	//return 0;
}

const char* Derived::toString()
{
	return "This is a Derived";
}

define_lua_class_by_proxy_defaults(Derived, Basic)
end_lua_class_by_proxy_defaults(Derived, Basic)
#endif//EXTENDED_BY_LUA
