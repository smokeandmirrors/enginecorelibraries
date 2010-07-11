#ifdef EXTENDED_BY_LUA
#include <assert.h>
#include <string.h>

#include "TestClasses.h"

#include "LuaInclusions.h"
#include "LuaLibraryDeclarations.h"
#include "LuaRegistration.h"

static int lua_newParent(lua_State* L)
{
	Parent* p = new Parent();
	pushRegisteredClass(L, p);
	return 1;
}

static int lua_Parent_getGrandparentName(lua_State* L)
{
	Parent* p = *static_cast<Parent**>(lua_touserdata(L, -1));
	lua_pushstring(L, p->getGrandparentName());
	return 1;
}

define_lua_class(Parent, Parent::super)
// should be able to be automagicked...
lua_named_entry("new", lua_newParent)
lua_named_entry("getGrandparentName", lua_Parent_getGrandparentName)
end_lua_library(Parent)


static int lua_newChild(lua_State* L)
{
	Child* c = new Child();
	pushRegisteredClass(L, c);
	return 1;
}

static int lua_Child_getParentName(lua_State* L)
{
	Child* c = *static_cast<Child**>(lua_touserdata(L, -1));
	lua_pushstring(L, c->getParentName());
	return 1;
}

define_lua_class(Child, Child::super)
// should be able to be automagicked...
lua_named_entry("new", lua_newChild)
lua_named_entry("getParentName", lua_Child_getParentName)
end_lua_library(Child)
#endif//EXTENDED_BY_LUA
