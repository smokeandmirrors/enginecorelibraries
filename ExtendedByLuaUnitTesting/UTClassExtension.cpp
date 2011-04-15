#include "Build.h"
#if WITH_UNIT_TESTING
#include <cfixcc.h>
#include <string.h>

#include "UTTools.h"
#include "Vector.h"
#include "NumericalFunctions.h"

#if EXTENDED_BY_LUA
#include "LuaExtensionInclusions.h"

using namespace lua_extension;

class Classes : public cfixcc::TestFixture
{
public:
	void test_define_lua_class(void);
	void test_define_lua_LuaExtendable(void); 
	void test_define_lua_LuaExtendable_by_proxy(void);
};

class One
{
public:
	typedef One super;
	sint4 getValue(void) const		{ return 1; }
	sint4 increment(sint4 i) const	{ return i + getValue(); }
}; // Basic

DECLARE_LUA_LIBRARY(One)

LUA_FUNC(newOne)
{
	pushRegisteredClass(L, new One());		//s: ud
	lua_newtable(L);						//s: ud, ud_mt
	lua_getglobal(L, "One");				//s: ud, ud_mt, Basic
	lua_setfield(L, -2, "__index");			//s: ud, ud_mt
	lua_setmetatable(L, -2);				//s: ud/mt
	return 1;
}

LUA_FUNC(getOne)
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

LUA_FUNC(getValueOne)
{
	One* one = static_cast<One*>(lua_touserdata(L, -1));	//s: ud
	return push(L, one->getValue());						//s: ud, value
}

LUA_FUNC(incrementOne)
{
	sint4 argument = to<sint4>(L, -1);						//s: ud, arg
	lua_pop(L, 1);											//s: ud
	One* one = static_cast<One*>(lua_touserdata(L, -1));	//s: ud
	return push(L, one->increment(argument));				//s: ud, valuereturn 1;
}

DEFINE_LUA_LIBRARY(One)
	LUA_NAMED_ENTRY("new", newOne)
	LUA_NAMED_ENTRY("get", getOne)
	LUA_NAMED_ENTRY("getValue", getValueOne)
	LUA_NAMED_ENTRY("increment", incrementOne)
END_LUA_LIBRARY(One)

void Classes::test_define_lua_class()
{
	Lua lua;
	REGISTER_LUA_LIBRARY((&lua), One);
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
	sint4 one_value = to<sint4>(L, -1);
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
	sint4 three_value = to<sint4>(L, -1);
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
	sint4 zero = to<sint4>(L, -1);
	CFIX_ASSERT(zero == 0.0f);
	lua_pop(L, 2);
}

class Simple
	: public LuaExtendable
{
private:
	static bool everCreated;
	static uint4 numAllocated;

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

	static uint4 getNumAllocated(void)	{ return numAllocated; }
	static bool wasEverCreated(void)	{ return everCreated; }

public:
	Simple*			getOther(void) const		{ return m_other; }
	virtual uint4	getValue(void) const		{ return 7; }
	bool			isSimple(void) const		{ return true; }
	Simple*			reproduce() const			{ return new Simple(); }

	void setOther(Simple* other) 
	{ 
		m_other = other; 
	}

	INLINE_LUAEXTENDABLE_USERDATA_DEFAULT_FUNCTIONS(Simple)

private:
	Simple*			m_other;
};

uint4 Simple::numAllocated = 0;
bool Simple::everCreated = false;

DECLARE_LUA_LUAEXTENDABLE(Simple);

DEFINE_LUA_LUAEXTENDABLE(Simple, Simple)
	LUA_NAMED_ENTRY("__call", (return1Param0const<Simple, uint4, &Simple::getValue>))
	LUA_NAMED_ENTRY("getOther", (return1Param0const<Simple, Simple*, &Simple::getOther>))
	LUA_NAMED_ENTRY("getValue", (return1Param0const<Simple, uint4, &Simple::getValue>))
	LUA_NAMED_ENTRY("isSimple", (return1Param0const<Simple, bool, &Simple::isSimple>))
	LUA_NAMED_ENTRY("reproduce", (return1Param0const<Simple, Simple*, &Simple::reproduce>))
	LUA_NAMED_ENTRY("setOther", (return0Param1<Simple, Simple*, &Simple::setOther>))
END_LUA_LUAEXTENDABLE(Simple, Simple)


class Derived
	: public Simple
{
private:
	static bool everCreated;
	static uint4 numAllocated;

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

	static uint4 getNumAllocated(void)		{ return numAllocated; }
	static bool wasEverCreated(void)		{ return everCreated; }

public:
	uint4				getDerivation(void) const	{ return 21; }
	virtual uint4		getValue(void) const		{ return 14; }

	INLINE_LUAEXTENDABLE_USERDATA_DEFAULT_FUNCTIONS(Derived)
};

uint4 Derived::numAllocated = 0;
bool Derived::everCreated = false;

DECLARE_LUA_LUAEXTENDABLE(Derived);

class Unexposed
	: public Derived
{
private:
	static bool everCreated;
	static uint4 numAllocated;

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
	static uint4 getNumAllocated(void)		{ return numAllocated; }
	static bool wasEverCreated(void)		{ return everCreated; }
};

uint4 Unexposed::numAllocated = 0;
bool Unexposed::everCreated = false;

LUA_FUNC(getUnexposed)
{
	return push(L, Unexposed::getUnexposed());
}

DEFINE_LUA_LUAEXTENDABLE(Derived, Simple)
LUA_NAMED_ENTRY("getDerivation", (return1Param0const<Derived, uint4, &Derived::getDerivation>))
LUA_ENTRY(getUnexposed)
END_LUA_LUAEXTENDABLE(Derived, Simple)

void supporttest_define_lua_LuaExtendable()
{
	lua_extension::Lua lua; 
	REGISTER_LUA_LIBRARY((&lua), Simple);
	REGISTER_LUA_LIBRARY((&lua), Derived);
	unit_testing_tools::executeLuaUnitTest("UTLuaExtendableClasses", &lua);
}

void Classes::test_define_lua_LuaExtendable()
{
	supporttest_define_lua_LuaExtendable();

	CFIX_ASSERT(Simple::getNumAllocated() == 0.0f);
	CFIX_ASSERT(Simple::wasEverCreated());
	CFIX_ASSERT(Derived::getNumAllocated() == 0.0f);
	CFIX_ASSERT(Derived::wasEverCreated());
	CFIX_ASSERT(Unexposed::getNumAllocated() == 0.0f);
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
	static uint4 numAllocatedGrandparents;
	
public:
	typedef Grandparent super;

	static uint4 getNumAllocated(void)	{ return numAllocatedGrandparents; }
	static bool wasEverCreated(void)	{ return everCreated; }

	Grandparent(const sint1* name=NULL) 
		: m_name(name) 
	{
		everCreated = true;
		numAllocatedGrandparents++;
	}

	virtual ~Grandparent(void) 
	{ 
		numAllocatedGrandparents--;
	}

	const sint1* getFamilyName(void) const 
	{ 
		return "Curran"; 
	}

	virtual const sint1* getTitle(void) const 
	{ 
		return "Grandparent"; 
	}

	bool operator==(const Grandparent& other) const
	{
		return this == &other; 
	}

	INLINE_LUAEXTENDABLE_PROXY_DEFAULT_FUNCTIONS(Grandparent)

protected:
	const sint1*				m_name;
}; // Grandparent

uint4 Grandparent::numAllocatedGrandparents = 0;
bool Grandparent::everCreated = false;

DECLARE_LUA_LUAEXTENDABLE(Grandparent);

LUA_FUNC(__call)
{
	return push(L, 7);
}

DEFINE_LUA_LUAEXTENDABLE_BY_PROXY(Grandparent, Grandparent)
LUA_ENTRY(__call) 
LUA_NAMED_ENTRY("getFamilyName",	(return1Param0const<Grandparent, const sint1*, &Grandparent::getFamilyName>))
LUA_NAMED_ENTRY("getTitle",			(return1Param0const<Grandparent, const sint1*, &Grandparent::getTitle>))
LUA_NAMED_ENTRY("__eq",				(return1Param1const<Grandparent, bool, const Grandparent&, &Grandparent::operator==>))
END_LUA_LUAEXTENDABLE(Grandparent, Grandparent)

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
	const sint1*				getGrandparentName(void) const	{ return "Robert Michael Curran, Sr."; }
	virtual const sint1*		getTitle(void) const			{ return "Parent"; }
	void					setGrandparent(Grandparent* gp) { m_grandParent = gp; }
	INLINE_DEFAULT_GETCLASSNAME(Parent)

private:
	Grandparent*			m_grandParent;			
}; // Parent

DECLARE_LUA_LUAEXTENDABLE(Parent);

DEFINE_LUA_LUAEXTENDABLE_BY_PROXY(Parent, Grandparent)
LUA_NAMED_ENTRY("getGrandparent",		(return1Param0const<Parent, Grandparent*, &Parent::getGrandparent>))
LUA_NAMED_ENTRY("getGrandparentName",	(return1Param0const<Parent, const sint1*, &Parent::getGrandparentName>))
LUA_NAMED_ENTRY("setGrandparent",		(return0Param1<Parent, Grandparent*, &Parent::setGrandparent>))
END_LUA_LUAEXTENDABLE(Parent, Grandparent) 

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
	const sint1*				getParentName(void) const	{ return "Robert Michael Curran, Jr."; }
	virtual const sint1*		getTitle(void) const		{ return "Child"; }
	void					setParent(Parent* gp)		{ m_parent = gp; }
	INLINE_DEFAULT_GETCLASSNAME(Child)

private:
	Parent*					m_parent;
}; // Child

DECLARE_LUA_LUAEXTENDABLE(Child);

DEFINE_LUA_LUAEXTENDABLE_BY_PROXY(Child, Parent)
LUA_NAMED_ENTRY("get",				(staticReturn1Param0<Child*, &Child::get>))
LUA_NAMED_ENTRY("getParent",		(return1Param0const<Child, Parent*, &Child::getParent>))
LUA_NAMED_ENTRY("getParentName",	(return1Param0const<Child, const sint1*, &Child::getParentName>))
LUA_NAMED_ENTRY("setParent",		(return0Param1<Child, Parent*, &Child::setParent>))
END_LUA_LUAEXTENDABLE(Child, Parent)

// END PROXY

void supportProxyTesting(void)
{
	lua_extension::Lua lua; 
	REGISTER_LUA_LIBRARY((&lua), Grandparent);
	REGISTER_LUA_LIBRARY((&lua), Parent);
	REGISTER_LUA_LIBRARY((&lua), Child);
	unit_testing_tools::executeLuaUnitTest("UTProxyClasses", &lua);
}

void Classes::test_define_lua_LuaExtendable_by_proxy()
{
	supportProxyTesting();
	CFIX_ASSERT(Grandparent::getNumAllocated() == 0.0f);
	CFIX_ASSERT(Grandparent::wasEverCreated());
}

CFIXCC_BEGIN_CLASS(Classes)
	CFIXCC_METHOD(test_define_lua_class)
	CFIXCC_METHOD(test_define_lua_LuaExtendable)
	CFIXCC_METHOD(test_define_lua_LuaExtendable_by_proxy)
CFIXCC_END_CLASS()

#endif//EXTENDED_BY_LUA
#endif//WITH_UNIT_TESTING
