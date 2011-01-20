#include <cfixcc.h>
#include <string.h>

#if EXTENDED_BY_LUA
#include "Lua.h"
#include "LuaInclusions.h"
#include "LuaLibraryDeclarations.h"
#include "LuaExtensibility.h"
#include "LuaStateInteraction.h"

using namespace LuaExtension;
/*
class Basic
: public LuaExtendable
{
public:
	typedef Basic super;
	
	int getValue(void) const 
	{ 
		return value; 
	}
	
	virtual int setMetatable(lua_State* L)
	{
		return setDefaultMetatableProxy(L);
	}

	virtual const char* toString(void)
	{
		return "This is a Basic.";
	}

	int setValue(int new_value) 
	{ 
		value = new_value; 
	}

private:
	int value;
}; // Basic

declare_lua_extendable(Basic)

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
		pushRegisteredClass(L,b);				//s: ud
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
	lua_named_entry("getValue", (return1Param0const<Basic, int, &Basic::getValue>))
end_lua_class(Basic, Basic)

 class Derived
 : public Basic
 {
 public:
 	typedef Basic super;
 	virtual int	setMetatable(lua_State* L)
	{
		return setDefaultMetatableProxy(L);
	}

 	virtual const char* toString(void)
	{
		return "This is a Derived";
	}
 }; // Derived
 
 declare_lua_library(Derived)
  
 define_lua_class_by_proxy_defaults(Derived, Basic)
 end_lua_class_by_proxy_defaults(Derived, Basic)
*/
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

class Classes : public cfixcc::TestFixture
{
private:

public:
	void TestBasicClassExposition()
	{
// 		Lua lua;
// 		register_lua_library((&lua), Basic);
// 		// CFIX_ASSERT(lua.doString("_G.b = new'Basic'"));
// 		lua.runConsole();
// 		lua_State* L = lua.getState();
// 		lua_getglobal(L, "b");
// 		//s: b
// 		CFIX_ASSERT(lua_isuserdata(L, -1));
// 		void* b = lua_touserdata(L, -1);
// 		CFIX_ASSERT(b);
// 		LuaExtendable* ble = to<LuaExtendable*>(L, -1);
// 		CFIX_ASSERT(ble);
// 		Basic* b_from_ble = dynamic_cast<Basic*>(ble);
// 		CFIX_ASSERT(b_from_ble);
// 		Basic* basic_from_lua = to<Basic*>(L, -1);
// 		CFIX_ASSERT(basic_from_lua);
	}
	/*
	void Test()
	{
		CFIX_INCONCLUSIVE(__TEXT("Not implemented"));
	}
	*/
};

CFIXCC_BEGIN_CLASS(Classes)
	CFIXCC_METHOD(TestBasicClassExposition)
CFIXCC_END_CLASS()

