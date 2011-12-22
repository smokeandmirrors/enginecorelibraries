#include "Platform.h"
#if WITH_UNIT_TESTING
#include <cfixcc.h>
#include <string.h>

#include "UTTools.h"

#if EXTENDED_BY_LUA
#include "LuaExtensionInclusions.h"

using namespace embeddedLua;

class Classes : public cfixcc::TestFixture
{
public:
	void test_define_lua_class(void);
	void test_define_lua_LuaExtendable(void); 
	void test_define_lua_LuaExtendable_by_proxy(void);
};


// BEGIN SINGLE
class Single
{
public:
	typedef Single super;
	sint getValue(void) const		{ return 1; }
	sint increment(sint i) const	{ return i + getValue(); }
}; // Basic

DECLARE_LUA_LIBRARY(Single)

LUA_FUNC(newSingle)
{
	pushRegisteredClass(L, new Single());		//s: ud
	lua_newtable(L);						//s: ud, ud_mt
	lua_getglobal(L, "Single");				//s: ud, ud_mt, Basic
	lua_setfield(L, -2, "__index");			//s: ud, ud_mt
	lua_setmetatable(L, -2);				//s: ud/mt
	return 1;
}

LUA_FUNC(getSingle)
{
	static Single* singleSingle(NULL);

	if (!singleSingle)
	{
		singleSingle = new Single();
		pushRegisteredClass(L,singleSingle);		//s: ud
		lua_newtable(L);						//s: ud, ud_mt
		lua_getglobal(L, "Single");				//s: ud, ud_mt, Basic
		lua_setfield(L, -2, "__index");			//s: ud, ud_mt
		lua_setmetatable(L, -2);				//s: ud/mt
	}
	else
	{
		pushRegisteredClass(L,singleSingle);		//s: ud
	}

	return 1;
}

LUA_FUNC(getValueSingle)
{
	Single* single = static_cast<Single*>(lua_touserdata(L, -1));	//s: ud
	return push(L, single->getValue());						//s: ud, value
}

LUA_FUNC(incrementSingle)
{
	sint argument = to<sint>(L, -1);						//s: ud, arg
	lua_pop(L, 1);											//s: ud
	Single* single = static_cast<Single*>(lua_touserdata(L, -1));	//s: ud
	return push(L, single->increment(argument));				//s: ud, valuereturn 1;
}

DEFINE_LUA_LIBRARY(Single)
	LUA_ENTRY_NAMED("new", newSingle)
	LUA_ENTRY_NAMED("get", getSingle)
	LUA_ENTRY_NAMED("getValue", getValueSingle)
	LUA_ENTRY_NAMED("increment", incrementSingle)
END_LUA_LIBRARY(Single)
// END SINGLE


void Classes::test_define_lua_class()
{
	DECLARE_UNIT_TESTING_LUA_OBJECT
	REGISTER_LUA_LIBRARY((&lua), Single);
	CFIX_ASSERT(lua.doString("_G.single = Single.new()"));
	lua_State* L = lua.getState();
	lua_getglobal(L, "single");
	//s: single
	CFIX_ASSERT(lua_isuserdata(L, -1));
	void* ud = lua_touserdata(L, -1);
	CFIX_ASSERT(ud);
	Single* single = static_cast<Single*>(lua_touserdata(L, -1));
	CFIX_ASSERT(single);
	lua_getfield(L, -1, "getValue");
	//s: single getValue
	CFIX_ASSERT(lua_iscfunction(L, -1));
	lua_pushvalue(L, -2);
	//s: single getValue single
	CFIX_ASSERT(lua_isuserdata(L, -1));
	lua_call(L, 1, 1);
	//s: single 1
	CFIX_ASSERT(lua_isnumber(L, -1));
	sint single_value = to<sint>(L, -1);
	//s: single 1
	CFIX_ASSERT(single_value == 1);
	lua_pop(L, 1);
	//s: single
	lua_getfield(L, -1, "increment");
	//s: single increment
	CFIX_ASSERT(lua_iscfunction(L, -1));
	lua_pushvalue(L, -2);
	//s: single increment single
	CFIX_ASSERT(lua_isuserdata(L, -1));
	push(L, 2);
	//s: single increment single 2
	lua_call(L, 2, 1);
	//s: single 3
	sint three_value = to<sint>(L, -1);
	//s: single 1
	CFIX_ASSERT(three_value == 3);
	lua_pop(L, 2);
	CFIX_ASSERT(lua.require("UTSingle"));
	CFIX_ASSERT(lua.doString("_G.single2 = Single.new()"));
	CFIX_ASSERT(lua.doString("_G.there = type(single2.decrement) == 'function'"));
	lua_getglobal(L, "there");
	bool there = to<bool>(L, -1);
	//s: _G.there
	CFIX_ASSERT(there);
	CFIX_ASSERT(lua.doString("_G.zero = single2.decrement(single2:getValue())"));
	lua_getglobal(L, "zero");
	//s: _G.there _G.zero
	CFIX_ASSERT(lua_isnumber(L, -1));
	sint zero = to<sint>(L, -1);
	CFIX_ASSERT(zero == 0.0f);
	lua_pop(L, 2);
}

class Simple
	: public LuaExtendable
{
private:
	static bool everCreated;
	static uint numAllocated;

public:
	Simple(void)
	{
		everCreated = true;
		numAllocated++;
	}

	virtual ~Simple(void)
	{
		numAllocated--;
	}

	static uint getNumAllocated(void)	{ return numAllocated; }
	static bool wasEverCreated(void)	{ return everCreated; }

public:
	Simple*			getOther(void) const		{ return m_other; }
	virtual uint	getValue(void) const		{ return 7; }
	bool			isSimple(void) const		{ return true; }
	Simple*			reproduce() const			{ return new Simple(); }

	void setOther(Simple* other) 
	{ 
		m_other = other; 
	}

	DEFINE_LUAEXTENDABLE_USERDATA_DEFAULT_FUNCTIONS(Simple)

private:
	Simple*			m_other;
};

uint Simple::numAllocated = 0;
bool Simple::everCreated = false;

DECLARE_LUA_LUAEXTENDABLE(Simple);

DEFINE_LUA_CLASS(EXTENDABLE, Simple, Simple)
	LUA_ENTRY_NAMED("__call", (nativeConstReturn1Param0<Simple, uint, &Simple::getValue>))
	LUA_ENTRY_NAMED("getOther", (nativeConstReturn1Param0<Simple, Simple*, &Simple::getOther>))
	LUA_ENTRY_NAMED("getValue", (nativeConstReturn1Param0<Simple, uint, &Simple::getValue>))
	LUA_ENTRY_NAMED("isSimple", (nativeConstReturn1Param0<Simple, bool, &Simple::isSimple>))
	LUA_ENTRY_NAMED("reproduce", (nativeConstReturn1Param0<Simple, Simple*, &Simple::reproduce>))
	LUA_ENTRY_NAMED("setOther", (nativeMemberReturn0Param1<Simple, Simple*, &Simple::setOther>))
END_LUA_CLASS(Simple, Simple)


class Derived
	: public Simple
{
private:
	static bool everCreated;
	static uint numAllocated;

public:
	Derived(void)
	{
		everCreated = true;
		numAllocated++;
	}

	virtual ~Derived(void)
	{
		numAllocated--;
	}

	static uint getNumAllocated(void)		{ return numAllocated; }
	static bool wasEverCreated(void)		{ return everCreated; }

public:
	uint				getDerivation(void) const	{ return 21; }
	virtual uint		getValue(void) const		{ return 14; }

	DEFINE_LUAEXTENDABLE_USERDATA_DEFAULT_FUNCTIONS(Derived)
};

uint Derived::numAllocated = 0;
bool Derived::everCreated = false;

DECLARE_LUA_LUAEXTENDABLE(Derived);

class Unexposed
	: public Derived
{
private:
	static bool everCreated;
	static uint numAllocated;

public:
	Unexposed(void)
	{
		everCreated = true;
		numAllocated++;
	}

	virtual ~Unexposed(void)
	{
		numAllocated--;
	}

	static Unexposed* getUnexposed(void)	
	{ 
		static Unexposed* singleton(NULL); 
		if (!singleton) singleton = new Unexposed();
		return singleton;
	}
	static uint getNumAllocated(void)		{ return numAllocated; }
	static bool wasEverCreated(void)		{ return everCreated; }
};

uint Unexposed::numAllocated = 0;
bool Unexposed::everCreated = false;

LUA_FUNC(getUnexposed)
{
	return push(L, Unexposed::getUnexposed());
}

DEFINE_LUA_CLASS(EXTENDABLE, Derived, Simple)
	LUA_ENTRY_NAMED("getDerivation", (nativeConstReturn1Param0<Derived, uint, &Derived::getDerivation>))
	LUA_ENTRY(getUnexposed)
END_LUA_CLASS(Derived, Simple)

void supporttest_define_lua_LuaExtendable()
{
	DECLARE_UNIT_TESTING_LUA_OBJECT
	REGISTER_LUA_LIBRARY((&lua), Simple);
	REGISTER_LUA_LIBRARY((&lua), Derived);
	unit_testing_tools::executeLuaUnitTest("UTLuaExtendableClasses", &lua);
}

void Classes::test_define_lua_LuaExtendable()
{
	supporttest_define_lua_LuaExtendable();

	CFIX_ASSERT(Simple::getNumAllocated() == 0);
	CFIX_ASSERT(Simple::wasEverCreated());
	CFIX_ASSERT(Derived::getNumAllocated() == 0);
	CFIX_ASSERT(Derived::wasEverCreated());
	CFIX_ASSERT(Unexposed::getNumAllocated() == 0);
	CFIX_ASSERT(Unexposed::wasEverCreated());
}

// BEGIN PROXY
/**
\class
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

	Grandparent(void) 
	{
		everCreated = true;
		numAllocatedGrandparents++;
	}

	virtual ~Grandparent(void) 
	{ 
		numAllocatedGrandparents--;
	}

	const schar* getFamilyName(void) const 
	{ 
		return "Curran"; 
	}

	virtual const schar* getTitle(void) const 
	{ 
		return "Grandparent"; 
	}

	bool operator==(const Grandparent& other) const
	{
		return this == &other; 
	}

	DEFINE_LUAEXTENDABLE_PROXY_DEFAULT_FUNCTIONS(Grandparent)
}; // Grandparent

uint Grandparent::numAllocatedGrandparents = 0;
bool Grandparent::everCreated = false;

DECLARE_LUA_LUAEXTENDABLE(Grandparent);

LUA_FUNC(__call)
{
	return push(L, 7);
}

DEFINE_LUA_CLASS_BY_PROXY(EXTENDABLE, Grandparent, Grandparent)
	LUA_ENTRY(__call) 
	LUA_ENTRY_NAMED("getFamilyName",	(nativeConstReturn1Param0<Grandparent, const schar*, &Grandparent::getFamilyName>))
	LUA_ENTRY_NAMED("getTitle",			(nativeConstReturn1Param0<Grandparent, const schar*, &Grandparent::getTitle>))
	LUA_ENTRY_NAMED("__eq",				(nativeConstReturn1Param1<Grandparent, bool, const Grandparent&, &Grandparent::operator==>))
END_LUA_CLASS(Grandparent, Grandparent)

/**
\class

demonstrates full inheritance tree and proxy useage
*/
class Parent 
	: public Grandparent
{
public:
	typedef Grandparent super;
	Parent(Grandparent* gp=NULL) : m_grandParent(gp)		{ /* empty */ }
	Grandparent*			getGrandparent(void) const		{ return m_grandParent; }
	const schar*				getGrandparentName(void) const	{ return "Robert Michael Curran, Sr."; }
	virtual const schar*		getTitle(void) const			{ return "Parent"; }
	void					setGrandparent(Grandparent* gp) { m_grandParent = gp; }
	DEFINE_DEFAULT_GETCLASSNAME(Parent)

private:
	Grandparent*			m_grandParent;			
}; // Parent

DECLARE_LUA_LUAEXTENDABLE(Parent);

DEFINE_LUA_CLASS_BY_PROXY(EXTENDABLE, Parent, Grandparent)
LUA_ENTRY_NAMED("getGrandparent",		(nativeConstReturn1Param0<Parent, Grandparent*, &Parent::getGrandparent>))
LUA_ENTRY_NAMED("getGrandparentName",	(nativeConstReturn1Param0<Parent, const schar*, &Parent::getGrandparentName>))
LUA_ENTRY_NAMED("setGrandparent",		(nativeMemberReturn0Param1<Parent, Grandparent*, &Parent::setGrandparent>))
END_LUA_CLASS(Parent, Grandparent) 

/**
\class

demonstrates full inheritance tree and proxy usesage
*/
class Child 
	: public Parent
{
public:
	typedef Parent super;

	static Child*			get(void) 
	{ 
		static Child* c(NULL); 
		if (!c)
			c = new Child();
		return c; 
	}

	Parent*					getParent(void) const		{ return m_parent; }
	const schar*				getParentName(void) const	{ return "Robert Michael Curran, Jr."; }
	virtual const schar*		getTitle(void) const		{ return "Child"; }
	void					setParent(Parent* gp)		{ m_parent = gp; }
	DEFINE_DEFAULT_GETCLASSNAME(Child)

private:
	Parent*					m_parent;
}; // Child

DECLARE_LUA_LUAEXTENDABLE(Child);

DEFINE_LUA_CLASS_BY_PROXY(EXTENDABLE, Child, Parent)
	LUA_ENTRY_NAMED("get",				(nativeStaticReturn1Param0<Child*, &Child::get>))
	LUA_ENTRY_NAMED("getParent",		(nativeConstReturn1Param0<Child, Parent*, &Child::getParent>))
	LUA_ENTRY_NAMED("getParentName",	(nativeConstReturn1Param0<Child, const schar*, &Child::getParentName>))
	LUA_ENTRY_NAMED("setParent",		(nativeMemberReturn0Param1<Child, Parent*, &Child::setParent>))
END_LUA_CLASS(Child, Parent)

// END PROXY

void supportProxyTesting(void)
{
	DECLARE_UNIT_TESTING_LUA_OBJECT 
	REGISTER_LUA_LIBRARY((&lua), Grandparent);
	REGISTER_LUA_LIBRARY((&lua), Parent);
	REGISTER_LUA_LIBRARY((&lua), Child);
	unit_testing_tools::executeLuaUnitTest("UTProxyClasses", &lua);
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
#endif//WITH_UNIT_TESTING
