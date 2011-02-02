#include <cfixcc.h>
#include <string.h>

#include "UnitTestingTools.h"
#include "Vector.h"

#if EXTENDED_BY_LUA

#include "Lua.h"
#include "LuaInclusions.h"
#include "LuaExtensibility.h"
#include "LuaStateInteraction.h"

using namespace LuaExtension;

class Classes : public cfixcc::TestFixture
{
public:
	void test_define_lua_class();
	void test_define_lua_LuaExtendable(); // \todo expose and test the vector class
	void test_define_lua_LuaExtendable_by_proxy();
};

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

void Classes::test_define_lua_class()
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


void supporttest_define_lua_LuaExtendable()
{
	LuaExtension::Lua lua; 
	// register_lua_library((&lua), Simple);
	// register_lua_library((&lua), Derived);
	UnitTestingTools::executeLuaUnitTest("UTLuaExtendableClasses", &lua);
}

void Classes::test_define_lua_LuaExtendable()
{
	/*
	supporttest_define_lua_LuaExtendable();
	CFIX_ASSERT(Simple::getNumAllocated() == 0);
	CFIX_ASSERT(Simple::wasEverCreated());
	CFIX_ASSERT(Derived::getNumAllocated() == 0);
	CFIX_ASSERT(Derived::wasEverCreated());
	*/
}

// BEGIN PROXY
/**
@class
demonstrates full inheritance tree and proxy useage
*/
class Grandparent 
	: public LuaExtendable
{
private:
	static bool everCreated;
	static uint numAllocatedGrandparents;
	
public:
	typedef Grandparent super;

	static uint getNumAllocated(void)	{ return numAllocatedGrandparents; }
	static bool wasEverCreated(void)	{ return everCreated; }

	Grandparent(const char* name=NULL) 
		: m_name(name) 
	{
		everCreated = true;
		numAllocatedGrandparents++;
	}

	virtual ~Grandparent(void) 
	{ 
		numAllocatedGrandparents--;
	}

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
		return this == &other; 
	}

	createLuaExtendableProxyDefaultFunctions(Grandparent)

protected:
	const char*				m_name;
}; // Grandparent

uint Grandparent::numAllocatedGrandparents = 0;
bool Grandparent::everCreated = false;

declare_lua_LuaExtendable(Grandparent);

lua_func(__call)
{
	return push(L, 7);
}

define_lua_LuaExtendable_by_proxy(Grandparent, Grandparent)
lua_entry(__call) 
lua_named_entry("getFamilyName",	(return1Param0const<Grandparent, const char*, &Grandparent::getFamilyName>))
lua_named_entry("getTitle",			(return1Param0const<Grandparent, const char*, &Grandparent::getTitle>))
lua_named_entry("__eq",				(return1Param1const<Grandparent, bool, const Grandparent&, &Grandparent::operator==>))
end_lua_LuaExtendable_by_proxy(Grandparent, Grandparent)

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
	virtual ~Parent(void)									{ /* empty */ }
	Grandparent*			getGrandparent(void) const		{ return m_grandParent; }
	const char*				getGrandparentName(void) const	{ return "Robert Michael Curran, Sr."; }
	virtual const char*		getTitle(void) const			{ return "Parent"; }
	void					setGrandparent(Grandparent* gp) { m_grandParent = gp; }

private:
	Grandparent*			m_grandParent;			
}; // Parent

declare_lua_LuaExtendable(Parent);

define_lua_LuaExtendable_by_proxy(Parent, Grandparent)
lua_named_entry("getGrandparent",		(return1Param0const<Parent, Grandparent*, &Parent::getGrandparent>))
lua_named_entry("getGrandparentName",	(return1Param0const<Parent, const char*, &Parent::getGrandparentName>))
lua_named_entry("setGrandparent",		(return0Param1<Parent, Grandparent*, &Parent::setGrandparent>))
end_lua_LuaExtendable_by_proxy(Parent, Grandparent) 

/**
@class

demonstrates full inheritance tree and proxy usesage
*/
class Child 
	: public Parent
{
public:
	typedef Parent super;

	static Child*			get(void)					{ static Child c; return &c; }

	Parent*					getParent(void) const		{ return m_parent; }
	const char*				getParentName(void) const	{ return "Robert Michael Curran, Jr."; }
	virtual const char*		getTitle(void) const		{ return "Child"; }
	void					setParent(Parent* gp)		{ m_parent = gp; }

private:
	Parent*					m_parent;
}; // Child

declare_lua_LuaExtendable(Child);

define_lua_LuaExtendable_by_proxy(Child, Parent)
lua_named_entry("get",				(staticReturn1Param0<Child*, &Child::get>))
lua_named_entry("getParent",		(return1Param0const<Child, Parent*, &Child::getParent>))
lua_named_entry("getParentName",	(return1Param0const<Child, const char*, &Child::getParentName>))
lua_named_entry("setParent",		(return0Param1<Child, Parent*, &Child::setParent>))
end_lua_LuaExtendable_by_proxy(Child, Parent)

// END PROXY

void supportProxyTesting(void)
{
	LuaExtension::Lua lua; 
	register_lua_library((&lua), Grandparent);
	register_lua_library((&lua), Parent);
	register_lua_library((&lua), Child);
	UnitTestingTools::executeLuaUnitTest("UTProxyClasses", &lua);
}

void Classes::test_define_lua_LuaExtendable_by_proxy()
{
	supportProxyTesting();
	CFIX_ASSERT(Grandparent::getNumAllocated() == 0);
	CFIX_ASSERT(Grandparent::wasEverCreated());
}

CFIXCC_BEGIN_CLASS(Classes)
	CFIXCC_METHOD(test_define_lua_class)
	CFIXCC_METHOD(test_define_lua_LuaExtendable)
	CFIXCC_METHOD(test_define_lua_LuaExtendable_by_proxy)
CFIXCC_END_CLASS()


#endif//EXTENDED_BY_LUA

