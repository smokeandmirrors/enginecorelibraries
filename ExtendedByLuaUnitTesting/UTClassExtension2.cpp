#include "Build.h"

#if WITH_UNIT_TESTING
#include <cfixcc.h>
#include <string.h>

#include "UTTools.h"

#if EXTENDED_BY_LUA

#include "LuaExtensionInclusions.h"

using namespace embeddedLua;

class UTClassExtension2 : public cfixcc::TestFixture
{
public:
	void test_define_lua_class(void);
	void test_define_lua_class2(void); 
	void test_define_lua_class2_by_proxy(void);
};

class One2
{
public:
	typedef One2 super;
	sint getValue(void) const		{ return 1; }
	sint increment(sint i) const	{ return i + getValue(); }
}; // Basic

DECLARE_LUA_LIBRARY(One2)

LUA_FUNC(newOne2)
{
	pushRegisteredClass(L, new One2());		//s: ud
	lua_newtable(L);						//s: ud, ud_mt
	lua_getglobal(L, "One2");				//s: ud, ud_mt, Basic
	lua_setfield(L, -2, "__index");			//s: ud, ud_mt
	lua_setmetatable(L, -2);				//s: ud/mt
	return 1;
}

LUA_FUNC(getOne2)
{
	static One2* singleOne(NULL);

	if (!singleOne)
	{
		singleOne = new One2();
		pushRegisteredClass(L,singleOne);		//s: ud
		lua_newtable(L);						//s: ud, ud_mt
		lua_getglobal(L, "One2");				//s: ud, ud_mt, Basic
		lua_setfield(L, -2, "__index");			//s: ud, ud_mt
		lua_setmetatable(L, -2);				//s: ud/mt
	}
	else
	{
		pushRegisteredClass(L,singleOne);		//s: ud
	}

	return 1;
}

LUA_FUNC(getValueOne2)
{
	One2* one = static_cast<One2*>(lua_touserdata(L, -1));	//s: ud
	return push(L, one->getValue());						//s: ud, value
}

LUA_FUNC(incrementOne2)
{
	sint argument = to<sint>(L, -1);						//s: ud, arg
	lua_pop(L, 1);											//s: ud
	One2* one = static_cast<One2*>(lua_touserdata(L, -1));	//s: ud
	return push(L, one->increment(argument));				//s: ud, valuereturn 1;
}

DEFINE_LUA_LIBRARY(One2)
LUA_ENTRY_NAMED("new", newOne2)
LUA_ENTRY_NAMED("get", getOne2)
LUA_ENTRY_NAMED("getValue", getValueOne2)
LUA_ENTRY_NAMED("increment", incrementOne2)
END_LUA_LIBRARY(One2)

void UTClassExtension2::test_define_lua_class()
{
	embeddedLua::Lua lua; 
	lua.setPackagePath(UNIT_TESTING_LUA_PACKAGE_PATH);
	REGISTER_LUA_LIBRARY((&lua), One2);
	CFIX_ASSERT(lua.doString("_G.one = One2.new()"));
	lua_State* L = lua.getState();
	lua_getglobal(L, "one");
	//s: one
	CFIX_ASSERT(lua_isuserdata(L, -1));
	void* ud = lua_touserdata(L, -1);
	CFIX_ASSERT(ud);
	One2* one = static_cast<One2*>(lua_touserdata(L, -1));
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
	CFIX_ASSERT(lua.require("UTOne2"));
	CFIX_ASSERT(lua.doString("_G.one2 = One2.new()"));
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
	CFIX_ASSERT(zero == 0.0f);
	lua_pop(L, 2);
}

class Simple2
{
private:
	static bool everCreated;
	static uint numAllocated;

public:
	Simple2(void)
	{
		everCreated = true;
		numAllocated++;
	}

	virtual ~Simple2(void)
	{
		numAllocated--;
	}

	static uint getNumAllocated(void)	{ return numAllocated; }
	static bool wasEverCreated(void)	{ return everCreated; }

public:
	Simple2*			getOther(void) const		{ return m_other; }
	virtual uint	getValue(void) const		{ return 7; }
	bool			isSimple(void) const		{ return true; }
	Simple2*			reproduce() const			{ return new Simple2(); }

	void setOther(Simple2* other) 
	{ 
		m_other = other; 
	}

private:
	Simple2*			m_other;
};

uint Simple2::numAllocated = 0;
bool Simple2::everCreated = false;

DECLARE_LUA_CLASS(Simple2);

DEFINE_LUA_CLASS(CLASS, Simple2, Simple2)
	LUA_ENTRY_NAMED("__call",		(nativeConstReturn1Param0<Simple2, uint, &Simple2::getValue>))
	LUA_ENTRY_NAMED("getOther",		(nativeConstReturn1Param0<Simple2, Simple2*, &Simple2::getOther>))
	LUA_ENTRY_NAMED("getValue",		(nativeConstReturn1Param0<Simple2, uint, &Simple2::getValue>))
	LUA_ENTRY_NAMED("isSimple",		(nativeConstReturn1Param0<Simple2, bool, &Simple2::isSimple>))
	LUA_ENTRY_NAMED("reproduce",	(nativeConstReturn1Param0<Simple2, Simple2*, &Simple2::reproduce>))
	LUA_ENTRY_NAMED("setOther",		(nativeMemberReturn0Param1<Simple2, Simple2*, &Simple2::setOther>))
END_LUA_CLASS(Simple2, Simple2)


class Derived2
	: public Simple2
{
private:
	static bool everCreated;
	static uint numAllocated;

public:
	Derived2(void)
	{
		everCreated = true;
		numAllocated++;
	}

	virtual ~Derived2(void)
	{
		numAllocated--;
	}

	static uint getNumAllocated(void)		{ return numAllocated; }
	static bool wasEverCreated(void)		{ return everCreated; }

public:
	uint				getDerivation(void) const	{ return 21; }
	virtual uint		getValue(void) const		{ return 14; }
};

uint Derived2::numAllocated = 0;
bool Derived2::everCreated = false;

DECLARE_LUA_CLASS(Derived2);

DEFINE_LUA_CLASS(CLASS, Derived2, Simple2)
LUA_ENTRY_NAMED("getDerivation", (nativeConstReturn1Param0<Derived2, uint, &Derived2::getDerivation>))
END_LUA_CLASS(Derived2, Simple2)

void supporttest_define_lua_class()
{
	DECLARE_UNIT_TESTING_LUA_OBJECT
	REGISTER_LUA_LIBRARY((&lua), Simple2);
	REGISTER_LUA_LIBRARY((&lua), Derived2);
	unit_testing_tools::executeLuaUnitTest("UTLuaExtendableClasses2", &lua);
}

void UTClassExtension2::test_define_lua_class2()
{
	supporttest_define_lua_class();

	CFIX_ASSERT(Simple2::getNumAllocated() == 0);
	CFIX_ASSERT(Simple2::wasEverCreated());
	CFIX_ASSERT(Derived2::getNumAllocated() == 0);
	CFIX_ASSERT(Derived2::wasEverCreated());
}

// BEGIN PROXY
class Grandparent2 
{
private:
	static bool everCreated;
	static uint numAllocatedGrandparents;

public:
	typedef Grandparent2 super;

	static uint getNumAllocated(void)	{ return numAllocatedGrandparents; }
	static bool wasEverCreated(void)	{ return everCreated; }

	Grandparent2(void) 
	{
		everCreated = true;
		numAllocatedGrandparents++;
	}

	virtual ~Grandparent2(void) 
	{ 
		numAllocatedGrandparents--;
	}

	const schar* getFamilyName(void) const 
	{ 
		return "Curran"; 
	}

	virtual const schar* getTitle(void) const 
	{ 
		return "Grandparent2"; 
	}

	bool operator==(const Grandparent2& other) const
	{
		return this == &other; 
	}
}; // Grandparent2

uint Grandparent2::numAllocatedGrandparents = 0;
bool Grandparent2::everCreated = false;

DECLARE_LUA_CLASS(Grandparent2);

LUA_FUNC(__call2)
{
	return push(L, 7);
}

DEFINE_LUA_CLASS_BY_PROXY(CLASS, Grandparent2, Grandparent2)
LUA_ENTRY_NAMED("__call", __call2) 
LUA_ENTRY_NAMED("getFamilyName",	(nativeConstReturn1Param0<Grandparent2, const schar*, &Grandparent2::getFamilyName>))
LUA_ENTRY_NAMED("getTitle",			(nativeConstReturn1Param0<Grandparent2, const schar*, &Grandparent2::getTitle>))
LUA_ENTRY_NAMED("__eq",				(nativeConstReturn1Param1<Grandparent2, bool, const Grandparent2&, &Grandparent2::operator==>))
END_LUA_CLASS(Grandparent2, Grandparent2)

class Parent2 
	: public Grandparent2
{
public:
	typedef Grandparent2 super;
	Parent2(Grandparent2* gp=NULL) : m_grandParent(gp)		{  }
	Grandparent2*			getGrandparent(void) const		{ return m_grandParent; }
	const schar*				getGrandparentName(void) const	{ return "Robert Michael Curran, Sr."; }
	virtual const schar*		getTitle(void) const			{ return "Parent2"; }
	void					setGrandparent(Grandparent2* gp) { m_grandParent = gp; }

private:
	Grandparent2*			m_grandParent;			
}; // Parent2

DECLARE_LUA_CLASS(Parent2);

DEFINE_LUA_CLASS_BY_PROXY(CLASS, Parent2, Grandparent2)
LUA_ENTRY_NAMED("getGrandparent",		(nativeConstReturn1Param0<Parent2, Grandparent2*, &Parent2::getGrandparent>))
LUA_ENTRY_NAMED("getGrandparentName",	(nativeConstReturn1Param0<Parent2, const schar*, &Parent2::getGrandparentName>))
LUA_ENTRY_NAMED("setGrandparent",		(nativeMemberReturn0Param1<Parent2, Grandparent2*, &Parent2::setGrandparent>))
END_LUA_CLASS(Parent2, Grandparent2) 

class Child2 
	: public Parent2
{
public:
	typedef Parent2 super;

	static Child2*			get(void) 
	{ 
		static Child2* c(NULL); 
		if (!c)
			c = new Child2();
		return c; 
	}

	Parent2*					getParent(void) const		{ return m_parent; }
	const schar*				getParentName(void) const	{ return "Robert Michael Curran, Jr."; }
	virtual const schar*		getTitle(void) const		{ return "Child2"; }
	void					setParent(Parent2* gp)		{ m_parent = gp; }

private:
	Parent2*					m_parent;
}; // Child2

DECLARE_LUA_CLASS(Child2);

DEFINE_LUA_CLASS_BY_PROXY(CLASS, Child2, Parent2)
LUA_ENTRY_NAMED("get",				(nativeStaticReturn1Param0<Child2*, &Child2::get>))
LUA_ENTRY_NAMED("getParent",		(nativeConstReturn1Param0<Child2, Parent2*, &Child2::getParent>))
LUA_ENTRY_NAMED("getParentName",	(nativeConstReturn1Param0<Child2, const schar*, &Child2::getParentName>))
LUA_ENTRY_NAMED("setParent",		(nativeMemberReturn0Param1<Child2, Parent2*, &Child2::setParent>))
END_LUA_CLASS(Child2, Parent2)

// END PROXY

void supportProxyTesting2(void)
{
	DECLARE_UNIT_TESTING_LUA_OBJECT 
	REGISTER_LUA_LIBRARY((&lua), Grandparent2);
	REGISTER_LUA_LIBRARY((&lua), Parent2);
	REGISTER_LUA_LIBRARY((&lua), Child2);
	unit_testing_tools::executeLuaUnitTest("UTProxyClasses2", &lua);
}

void UTClassExtension2::test_define_lua_class2_by_proxy()
{
	supportProxyTesting2();
	CFIX_ASSERT(Grandparent2::getNumAllocated() == 0);
	CFIX_ASSERT(Grandparent2::wasEverCreated());
}

CFIXCC_BEGIN_CLASS(UTClassExtension2)
	CFIXCC_METHOD(test_define_lua_class)
	CFIXCC_METHOD(test_define_lua_class2)
	CFIXCC_METHOD(test_define_lua_class2_by_proxy)
CFIXCC_END_CLASS()

#endif//EXTENDED_BY_LUA
#endif//WITH_UNIT_TESTING