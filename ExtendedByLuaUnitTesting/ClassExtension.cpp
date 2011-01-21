#include <cfixcc.h>
#include <string.h>

#if EXTENDED_BY_LUA
#include "Lua.h"
#include "LuaInclusions.h"
#include "LuaLibraryDeclarations.h"
#include "LuaExtensibility.h"
#include "LuaStateInteraction.h"

using namespace LuaExtension;

class One
{
public:
	typedef One super;
	sint getValue(void) const		{ return 1; }
	sint increment(sint i) const	{ return i + getValue(); }
}; // Basic

declare_lua_library(One)

lua_func(newOne)
{
	pushRegisteredClass(L, new One());		//s: ud
	lua_newtable(L);						//s: ud, ud_mt
	lua_getglobal(L, "One");				//s: ud, ud_mt, Basic
	lua_setfield(L, -2, "__index");			//s: ud, ud_mt
	lua_setmetatable(L, -2);				//s: ud/mt
	return 1;
}

lua_func(getOne)
{
	static One* singleOne(NULL);

	if (!singleOne)
	{
		singleOne = new One();
		pushRegisteredClass(L,singleOne);		//s: ud
		lua_newtable(L);						//s: ud, ud_mt
		lua_getglobal(L, "One");				//s: ud, ud_mt, Basic
		lua_setfield(L, -2, "__index");			//s: ud, ud_mt
		lua_setmetatable(L, -2);				//s: ud/mt
	}
	else
	{
		pushRegisteredClass(L,singleOne);		//s: ud
	}

	return 1;
}

lua_func(getValueOne)
{
	One* one = static_cast<One*>(lua_touserdata(L, -1));	//s: ud
	return push(L, one->getValue());						//s: ud, value
}

lua_func(incrementOne)
{
	sint argument = to<sint>(L, -1);						//s: ud, arg
	lua_pop(L, 1);											//s: ud
	One* one = static_cast<One*>(lua_touserdata(L, -1));	//s: ud
	return push(L, one->increment(argument));				//s: ud, valuereturn 1;
}

define_lua_class(One, One)
	lua_named_entry("new", newOne)
	lua_named_entry("get", getOne)
	lua_named_entry("getValue", getValueOne)
	lua_named_entry("increment", incrementOne)
end_lua_class(One, One)

class Two
{
public:
	typedef Two super;
	sint getValue(void) const		{ return 2; }
	sint increment(sint i) const	{ return i + getValue(); }
}; // Basic

declare_lua_library(Two)

lua_func(newTwo)
{
	pushRegisteredClass(L, new Two());		//s: ud
	lua_newtable(L);						//s: ud, ud_mt
	lua_getglobal(L, "Two");				//s: ud, ud_mt, Basic
	lua_setfield(L, -2, "__index");			//s: ud, ud_mt
	lua_setmetatable(L, -2);				//s: ud/mt
	return 1;
}

lua_func(getTwo)
{
	static Two* singleTwo(NULL);

	if (!singleTwo)
	{
		singleTwo = new Two();
		pushRegisteredClass(L,singleTwo);		//s: ud
		lua_newtable(L);						//s: ud, ud_mt
		lua_getglobal(L, "Two");				//s: ud, ud_mt, Basic
		lua_setfield(L, -2, "__index");			//s: ud, ud_mt
		lua_setmetatable(L, -2);				//s: ud/mt
	}
	else
	{
		pushRegisteredClass(L,singleTwo);	//s: ud
	}

	return 1;
}

lua_func(getValueTwo)
{
	Two* one = static_cast<Two*>(lua_touserdata(L, -1));	//s: ud
	return push(L, one->getValue());						//s: ud, value
}

lua_func(incrementTwo)
{
	sint argument = to<sint>(L, -1);						//s: ud, arg
	lua_pop(L, 1);											//s: ud
	Two* one = static_cast<Two*>(lua_touserdata(L, -1));	//s: ud
	return push(L, one->increment(argument));				//s: ud, valuereturn 1;
}

define_lua_class(Two, Two)
lua_named_entry("new", newTwo)
lua_named_entry("get", getTwo)
lua_named_entry("getValue", getValueTwo)
lua_named_entry("increment", incrementTwo)
end_lua_class(Two, Two)

class Classes : public cfixcc::TestFixture
{
public:
	void Test_declare_lua_library_withClasses()
	{
		Lua lua;
		register_lua_library((&lua), One);
		CFIX_ASSERT(lua.doString("_G.one = One.new()"));
		lua_State* L = lua.getState();
		lua_getglobal(L, "one");
		//s: one
		CFIX_ASSERT(lua_isuserdata(L, -1));
		void* ud = lua_touserdata(L, -1);
		CFIX_ASSERT(ud);
		One* one = static_cast<One*>(lua_touserdata(L, -1));
		CFIX_ASSERT(one);
		lua_getfield(L, -1, "getValue");
		//s: one getValue
		CFIX_ASSERT(lua_iscfunction(L, -1));
		lua_pushvalue(L, -2);
		//s: one getValue one
		CFIX_ASSERT(lua_isuserdata(L, -1));
		lua_call(L, 1, 1);
		//s: one 1
		CFIX_ASSERT(lua_isnumber(L, -1));

		register_lua_library((&lua), Two);
	}
};

CFIXCC_BEGIN_CLASS(Classes)
	CFIXCC_METHOD(Test_declare_lua_library_withClasses)
CFIXCC_END_CLASS()

//  declare_lua_library(Derived)
//   
//  define_lua_class_by_proxy_defaults(Derived, Basic)
//  end_lua_class_by_proxy_defaults(Derived, Basic)

/**
@class

demonstrates full inheritance tree and proxy usesage
*/
class Grandparent 
: public LuaExtendable
{
public:
	Grandparent(const char* name=NULL) : m_name(name)		{ /* empty */ }
	virtual ~Grandparent(void)								{ /* empty */ }
	const char*				getFamilyName(void) const		{ return "Curran"; }
	virtual const char*		getTitle(void) const			{ return "Grandparent"; }
	virtual const char*		toString(void);
	bool					operator==(const Grandparent& other) const;
	int						setMetatable(lua_State* L);

protected:
	const char*				m_name;

}; // Grandparent

/**
@class

demonstrates full inheritance tree and proxy usesage
*/
class Parent 
: public Grandparent
{
public:
	typedef Grandparent super;
	Parent(Grandparent* gp=NULL) : m_grandParent(gp)		{ /* empty */ }
	Grandparent*			getGrandparent(void) const		{ return m_grandParent; }
	const char*				getGrandparentName(void) const	{ return "Robert Michael Curran, Sr."; }
	virtual const char*		getTitle(void) const			{ return "Parent"; }

private:
	Grandparent*			m_grandParent;			
}; // Parent

/**
@class

demonstrates full inheritance tree and proxy usesage
*/
class Child 
: public Parent
{
public:
	typedef Parent super;
	const char*				getParentName(void) const	{ return "Robert Michael Curran, Jr."; }
	virtual const char*		getTitle(void) const		{ return "Child"; }
}; // Child

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


 
 declare_lua_extendable(Grandparent);
 declare_lua_extendable(Parent);
 declare_lua_extendable(Child);
 
 define_lua_class(Grandparent, Grandparent)
 	lua_entry(__call) 
 	lua_entry(getFamilyName)
 	lua_entry(getTitle)
 end_lua_class(Grandparent, Grandparent)
 
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
 lua_named_entry("getGrandparent", (return1Param0const<Parent, Grandparent*, &Parent::getGrandparent>))
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

