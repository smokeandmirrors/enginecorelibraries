#include <cfixcc.h>
#include <string.h>

#if EXTENDED_BY_LUA
#include "Lua.h"
#include "LuaInclusions.h"
#include "LuaLibraryDeclarations.h"
#include "LuaExtensibility.h"
#include "LuaStateInteraction.h"

using namespace LuaExtension;

/** 
\todo unit test __gc and garbage collection
*/

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
		sint one_value = to<sint>(L, -1);
		//s: one 1
		CFIX_ASSERT(one_value == 1);
		lua_pop(L, 1);
		//s: one
		lua_getfield(L, -1, "increment");
		//s: one increment
		CFIX_ASSERT(lua_iscfunction(L, -1));
		lua_pushvalue(L, -2);
		//s: one increment one
		CFIX_ASSERT(lua_isuserdata(L, -1));
		push(L, 2);
		//s: one increment one 2
		lua_call(L, 2, 1);
		//s: one 3
		sint three_value = to<sint>(L, -1);
		//s: one 1
		CFIX_ASSERT(three_value == 3);
		lua_pop(L, 2);
		lua.require("UTOne");
		CFIX_ASSERT(lua.doString("_G.one2 = One.new()"));
		CFIX_ASSERT(lua.doString("_G.there = type(one2.decrement) == 'function'"));
		lua_getglobal(L, "there");
		bool there = to<bool>(L, -1);
		//s: _G.there
		CFIX_ASSERT(there);
		CFIX_ASSERT(lua.doString("_G.zero = one2.decrement(one2:getValue())"));
		lua_getglobal(L, "zero");
		//s: _G.there _G.zero
		CFIX_ASSERT(lua_isnumber(L, -1));
		sint zero = to<sint>(L, -1);
		CFIX_ASSERT(zero == 0);
		lua_pop(L, 2);
	}
};

CFIXCC_BEGIN_CLASS(Classes)
	CFIXCC_METHOD(Test_declare_lua_library_withClasses)
CFIXCC_END_CLASS()

/**
@class
demonstrates full inheritance tree and proxy usesage
*/
class Grandparent 
: public LuaExtendable
{
public:
	Grandparent(const char* name=NULL) 
		: m_name(name) 
	{ /* empty */ }
	
	virtual ~Grandparent(void) 
	{ /* empty */ }
	
	const char* getFamilyName(void) const 
	{ 
		return "Curran"; 
	}
	
	virtual const char* getTitle(void) const 
	{ 
		return "Grandparent"; 
	}
	
	bool operator==(const Grandparent& other) const
	{
		return strcmp(getFamilyName(), other.getFamilyName()) == 0; 
	}

	sint setMetatable(lua_State* L)
	{
		return setProxyMetatable(L);
	}

	virtual const char*	toString(void)
	{ 
		return "This is a Grandparent"; 
	}
	
protected:
	const char*				m_name;
}; // Grandparent

declare_lua_LuaExtendable(Grandparent);

lua_func(__call)
{
	Grandparent& gp = to<Grandparent&>(L, -1);
	printToLua(L, gp.toString());
	return 0;
}
 
define_lua_LuaExtendable(Grandparent, Grandparent)
	lua_entry(__call) 
	lua_named_entry("getFamilyName",	(return1Param0const<Grandparent, const char*, &Grandparent::getFamilyName>))
	lua_named_entry("getTitle",			(return1Param0const<Grandparent, const char*, &Grandparent::getTitle>))
	lua_named_entry("__eq",				(return1Param1const<Grandparent, bool, const Grandparent&, &Grandparent::operator==>))
end_lua_LuaExtendable(Grandparent, Grandparent)

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

declare_lua_LuaExtendable(Parent);

static sint lua_newParent(lua_State* L)
{
	Parent* p = new Parent();
	pushRegisteredClass(L, p);
	return 1;
}

static sint lua_Parent_getGrandparentName(lua_State* L)
{
	Parent* p = *static_cast<Parent**>(lua_touserdata(L, -1));
	lua_pushstring(L, p->getGrandparentName());
	return 1;
}

define_lua_class(Parent, Parent::super)
	// should be able to be automagicked...
	lua_named_entry("new", lua_newParent)
	lua_named_entry("getGrandparentName", lua_Parent_getGrandparentName)
	// lua_named_entry("getGrandparent", (return1Param0const<Parent, Grandparent*, &Parent::getGrandparent>))
end_lua_library(Parent) 

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

declare_lua_LuaExtendable(Child);

static sint lua_newChild(lua_State* L)
{
	Child* c = new Child();
	pushRegisteredClass(L, c);
	return 1;
}

static sint lua_Child_getParentName(lua_State* L)
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

