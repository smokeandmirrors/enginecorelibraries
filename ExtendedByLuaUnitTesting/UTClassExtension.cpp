#include "Build.h"
#if BUILD_WITH_UNIT_TESTING
#include <cfixcc.h>
#include <string.h>

#include "UTTools.h"
#include "Vector.h"

#if EXTENDED_BY_LUA

#include "Lua.h"
#include "LuaInclusions.h"
#include "LuaExtensibility.h"
#include "LuaStateInteraction.h"

using namespace luaExtension;

class Classes : public cfixcc::TestFixture
{
public:
	void test_define_lua_class();
	void test_define_lua_LuaExtendable(); 
	void test_define_lua_LuaExtendable_by_proxy();
	void testVector3();
	void testLuaExtension(void);
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

define_lua_library(One)
	lua_named_entry("new", newOne)
	lua_named_entry("get", getOne)
	lua_named_entry("getValue", getValueOne)
	lua_named_entry("increment", incrementOne)
end_lua_library(One)

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

	createLuaExtendableUserdataDefaultFunctions(Simple)

private:
	Simple*			m_other;
};

uint Simple::numAllocated = 0;
bool Simple::everCreated = false;

declare_lua_LuaExtendable(Simple);

define_lua_LuaExtendable(Simple, Simple)
lua_named_entry("__call", (return1Param0const<Simple, uint, &Simple::getValue>))
lua_named_entry("getOther", (return1Param0const<Simple, Simple*, &Simple::getOther>))
lua_named_entry("getValue", (return1Param0const<Simple, uint, &Simple::getValue>))
lua_named_entry("isSimple", (return1Param0const<Simple, bool, &Simple::isSimple>))
lua_named_entry("reproduce", (return1Param0const<Simple, Simple*, &Simple::reproduce>))
lua_named_entry("setOther", (return0Param1<Simple, Simple*, &Simple::setOther>))
end_lua_LuaExtendable(Simple, Simple)


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

	createLuaExtendableUserdataDefaultFunctions(Derived)
};

uint Derived::numAllocated = 0;
bool Derived::everCreated = false;

declare_lua_LuaExtendable(Derived);

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

lua_func(getUnexposed)
{
	return push(L, Unexposed::getUnexposed());
}

define_lua_LuaExtendable(Derived, Simple)
lua_named_entry("getDerivation", (return1Param0const<Derived, uint, &Derived::getDerivation>))
lua_entry(getUnexposed)
end_lua_LuaExtendable(Derived, Simple)

void supporttest_define_lua_LuaExtendable()
{
	luaExtension::Lua lua; 
	register_lua_library((&lua), Simple);
	register_lua_library((&lua), Derived);
	unitTestingTools::executeLuaUnitTest("UTLuaExtendableClasses", &lua);
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

demonstrates full inheritance tree and proxy useage
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
	lua_getClassName(Parent)

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

	static Child*			get(void) 
	{ 
		static Child* c(NULL); 
		if (!c)
			c = new Child();
		return c; 
	}

	Parent*					getParent(void) const		{ return m_parent; }
	const char*				getParentName(void) const	{ return "Robert Michael Curran, Jr."; }
	virtual const char*		getTitle(void) const		{ return "Child"; }
	void					setParent(Parent* gp)		{ m_parent = gp; }
	lua_getClassName(Child)

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
	luaExtension::Lua lua; 
	register_lua_library((&lua), Grandparent);
	register_lua_library((&lua), Parent);
	register_lua_library((&lua), Child);
	unitTestingTools::executeLuaUnitTest("UTProxyClasses", &lua);
}

void Classes::test_define_lua_LuaExtendable_by_proxy()
{
	supportProxyTesting();
	CFIX_ASSERT(Grandparent::getNumAllocated() == 0.0f);
	CFIX_ASSERT(Grandparent::wasEverCreated());
}

#include "Numbers.h"
#include "UTTools.h"
#include "Vector.h"

/** 
	// \todo, move to it's own file
	CFIXCC_BEGIN_CLASS(UTVector)
	#if EXTENDED_BY_LUA
	CFIXCC_METHOD(testLuaExtension)
	#endif//EXTENDED_BY_LUA
	CFIXCC_METHOD(testVector3)
	CFIXCC_END_CLASS()
*/

using namespace unitTestingTools;
using namespace math;
void Classes::testLuaExtension(void)
{
	Lua lua;
	registerGlobalLibrary(lua.getState());
	lua.require("Utilities");
	lua.require("ObjectOrientedParadigm");
	register_lua_library((&lua), Vector3);
	unitTestingTools::executeLuaUnitTest("UTVector", &lua);	
}

void checkVector(const Vector3& v, vec_t x, vec_t y, vec_t z)
{
	CFIXCC_ASSERT_EQUALS(v.x, x);
	CFIXCC_ASSERT_EQUALS(v.y, y);
	CFIXCC_ASSERT_EQUALS(v.z, z);
}

void checkVector(const Vector3& v, vec_t x, vec_t y, vec_t z, vec_t tolerance)
{
	checkNearEqual(v.x, x, tolerance);
	checkNearEqual(v.y, y, tolerance);
	checkNearEqual(v.z, z, tolerance);
}

void checkVectorEqual(const Vector3& lhs, const Vector3& rhs)
{
	CFIXCC_ASSERT_EQUALS(lhs.x, rhs.x);
	CFIXCC_ASSERT_EQUALS(lhs.y, rhs.y);
	CFIXCC_ASSERT_EQUALS(lhs.z, rhs.z);
}



void Classes::testVector3(void)
{
	Vector3 v(3.0f,2.0f,1.0f);
	Vector3 w(3.0f,2.0f,1.0f);
	Vector3 x(1.0f,3.0f,2.0f);
	Vector3 z(0.0f);
	Vector3 scaleV(2,3,4);
	Vector3 subtractV( -1,-2,-3);
	Vector3 Xpos( 1, 0.0f, 0.0f);
	Vector3 Ypos( 0.0f, 1, 0.0f);
	Vector3 Zpos( 0.0f, 0.0f, 1);
	Vector3 Xneg(-1, 0.0f, 0.0f);
	Vector3 Yneg( 0.0f,-1, 0.0f);
	Vector3 Zneg( 0.0f, 0.0f,-1);

	CFIX_ASSERT(v == w);
	checkVector(v,3,2,1);
	checkVector(w,3,2,1);
	v.negate();
	checkVector(v,-3,-2,-1);
	v.negate();
	checkVector(v,3,2,1);
	v.add(x);
	checkVector(v,4,5,3);
	v.subtract(x);
	checkVector(v,3,2,1);
	checkVector(w,3,2,1);
	v.set(math::pi, math::pi/2, math::pi/3);
	checkVector(v,math::pi, math::pi/2, math::pi/3);
	v.set(math::pi/4);
	checkVector(v,math::pi/4, math::pi/4, math::pi/4);
	v.set(w);
	checkVector(v,3,2,1);
	checkVector(w,3,2,1);
	v.set(10.0f,0.0f,0.0f);
	checkVector(v, 10.0f, 0.0f, 0.0f);
	CFIXCC_ASSERT_EQUALS(v.distance(z), 10.0f);
	checkVector(z,0.0f,0.0f,0.0f);
	CFIXCC_ASSERT_EQUALS(v.distanceSqr(z), 100.0f);
	checkVector(z,0.0f,0.0f,0.0f,0.0f);
	CFIXCC_ASSERT_EQUALS(v.distanceXY(z), 10.0f);
	checkVector(z,0.0f,0.0f,0.0f,0.0f);
	CFIXCC_ASSERT_EQUALS(v.distanceXYSqr(z), 100.0f);
	checkVector(z,0.0f,0.0f,0.0f,0.0f);
	v.set(0.0f,10.0f,0.0f);
	checkVector(v, 0.0f, 10.0f, 0.0f, 0.0f);
	CFIXCC_ASSERT_EQUALS(v.distance(z), 10.0f);
	CFIXCC_ASSERT_EQUALS(v.distanceSqr(z), 100.0f);
	CFIXCC_ASSERT_EQUALS(v.distanceXY(z), 10.0f);
	CFIXCC_ASSERT_EQUALS(v.distanceXYSqr(z), 100.0f);
	v.set(0.0f,0.0f,10.0f);
	checkVector(v, 0.0f, 0.0f, 10.0f, 0.0f);
	CFIXCC_ASSERT_EQUALS(v.distance(z), 10.0f);
	CFIXCC_ASSERT_EQUALS(v.distanceSqr(z), 100.0f);
	CFIXCC_ASSERT_EQUALS(v.distanceXY(z), 0.0f);
	CFIXCC_ASSERT_EQUALS(v.distanceXYSqr(z), 0.0f);
	v.set(1,1,1);
	checkVector(v, 1, 1, 1, 0.0f);
	checkNearEqual(v.distance(z), 1.73205f);
	CFIXCC_ASSERT_EQUALS(v.distanceSqr(z), 3.0f);
	checkNearEqual(v.distanceXY(z), 1.414213f);
	CFIXCC_ASSERT_EQUALS(v.distanceXYSqr(z), 2.0f);
	v.normalize();
	checkNearEqual(v.distance(z), 1);
	checkNearEqual(v.distanceSqr(z), 1);
	v.set(0.0f,1,1);
	checkNearEqual(v.distanceXY(z), 1);
	checkNearEqual(v.distanceXYSqr(z), 1);
	v.set(8,4,2);
	v.divide(2);
	checkVector(v,4,2,1);
	v.set(8,4,2);
	checkVector(v,8,4,2);
	v.divide(8,4,2);
	checkVector(v, 1,1,1);
	v.set(100.0f,100.0f,100.0f);
	v.divide(50, 25, 10.0f);
	checkVector(v,2,4,10.0f);
	v.set(1,2,3);
	checkVector(v,1,2,3,0.0f);
	z.set(-1,-2,-3);
	checkVector(z,-1,-2,-3,0.0f);
	vec_t v_dot_z = v.dot(z);
	vec_t z_dot_v = z.dot(v);
	CFIXCC_ASSERT_EQUALS(v_dot_z, z_dot_v);
	CFIXCC_ASSERT_EQUALS(v_dot_z, -14.0f);
	CFIXCC_ASSERT_EQUALS(z_dot_v, -14.0f);
	checkVector(z,-1,-2,-3,0.0f);
	checkVector(v,1,2,3,0.0f);
	v.set(w);
	CFIX_ASSERT(! (v != w));
	CFIX_ASSERT(! (w != v));
	CFIX_ASSERT(w == v);
	CFIX_ASSERT(v == w);
	v.zero();
	checkVector(v, 0.0f,0.0f,0.0f);
	z.set(0.0f,0.0f,10.0f);
	checkVector(z,0.0f,0.0f,10.0f);
	CFIX_ASSERT(v.isFar(z,5));
	CFIX_ASSERT(!v.isFar(z,10.0f));
	CFIX_ASSERT(!v.isFarXY(z,0.0f));
	CFIX_ASSERT(!v.isFarXY(z,0.0f));
	checkVector(z,0.0f,0.0f,10.0f);
	checkVector(v, 0.0f,0.0f,0.0f);
	CFIX_ASSERT(v.isNear(z,10.0f));
	CFIX_ASSERT(!v.isNear(z,9.99f));
	CFIX_ASSERT(v.isNearXY(z,0.0f));
	v.set(10000000.0f, 0.0f, 0.0f);
	CFIXCC_ASSERT_EQUALS(v.normalize(), 10000000.0f);
	CFIX_ASSERT(v.isNormal());
	CFIXCC_ASSERT_EQUALS(v.magnitude(), 1.0f);
	checkVector(v,1,0.0f,0.0f);
	v.set(0.0f, 10000000.0f, 0.0f);
	CFIXCC_ASSERT_EQUALS(v.normalize(), 10000000.0f);
	CFIX_ASSERT(v.isNormal());
	CFIXCC_ASSERT_EQUALS(v.magnitude(), 1.0f);
	checkVector(v,0.0f,1.0f,0.0f);
	v.set(0.0f, 0.0f, 10000000.0f);
	CFIXCC_ASSERT_EQUALS(v.normalize(), 10000000.0f);
	CFIX_ASSERT(v.isNormal());
	CFIXCC_ASSERT_EQUALS(v.magnitude(), 1.0f);
	checkVector(v,0.0f,0.0f,1.0f);
	CFIX_ASSERT(!w.isNormal());
	CFIX_ASSERT(!w.isZero());
	v.set(0.0f);
	checkVector(v,0.0f,0.0f,0.0f,0.0f);
	CFIX_ASSERT(v.isZero());
	v.set(2,0.0f,0.0f);
	checkVector(v,2,0.0f,0.0f,0.0f);
	CFIXCC_ASSERT_EQUALS(v.magnitude(), 2.0f);
	CFIXCC_ASSERT_EQUALS(v.magnitudeSqr(), 4.0f);
	CFIXCC_ASSERT_EQUALS(v.magnitudeXY(), 2.0f);
	CFIXCC_ASSERT_EQUALS(v.magnitudeXYSqr(), 4.0f);
	v.set(0.0f,2.0f,0.0f);
	checkVector(v,0.0f,2.0f,0.0f,0.0f);
	CFIXCC_ASSERT_EQUALS(v.magnitudeSqr(), 4.0f);
	CFIXCC_ASSERT_EQUALS(v.magnitude(), 2.0f);
	CFIXCC_ASSERT_EQUALS(v.magnitudeXY(), 2.0f);
	CFIXCC_ASSERT_EQUALS(v.magnitudeXYSqr(), 4.0f);
	v.set(0.0f,0.0f,2.0f);
	checkVector(v,0.0f,0.0f,2.0f,0.0f);
	CFIXCC_ASSERT_EQUALS(v.magnitude(), 2.0f);
	CFIXCC_ASSERT_EQUALS(v.magnitudeSqr(), 4.0f);
	CFIXCC_ASSERT_EQUALS(v.magnitudeXY(), 0.0f);
	CFIXCC_ASSERT_EQUALS(v.magnitudeXYSqr(), 0.0f);
	z.set(0.0f,0.0f,2.00001f);
	CFIX_ASSERT(! (v == z));
	CFIX_ASSERT(v != z);
	CFIX_ASSERT(v.nearlyEquals(z));
	v.set(2,3,4);
	checkVector(v,2,3,4,0.0f);
	v.negate();
	checkVector(v,-2,-3,-4,0.0f);
	v.negate();
	checkVector(v,2,3,4,0.0f);
	v.scale(2);
	checkVector(v,4,6,8,0.0f);
	v.scale(1.0f/4.0f, 1.0f/6.0f, 1.0f/8.0f);
	checkVector(v,1.0f,1.0f,1.0f,0.0f);
	v.scale(scaleV);
	checkVector(v,2.0f,3.0f,4.0f,0.0f);
	v.zero();
	checkVector(v,0.0f,0.0f,0.0f,0.0f);
	v.subtract(1.0f,2.0f,3.0f);
	checkVector(v,-1.0f,-2.0f,-3.0f);
	v.subtract(subtractV);
	CFIX_ASSERT(v.isZero());
	checkVector(v,0.0f,0.0f,0.0f,0.0f);
	v.subtract(9.0f);
	checkVector(v,-9.0f,-9.0f,-9.0f,0.0f);
	// x positive
	v.set(Xpos);
	v.cross(Zpos);
	checkVectorEqual(v, Yneg);
	v.set(Xpos);
	v.cross(Ypos);
	checkVectorEqual(v, Zpos);
	v.set(Xpos);
	v.cross(Zneg);
	checkVectorEqual(v, Ypos);
	v.set(Xpos);
	v.cross(Yneg);
	checkVectorEqual(v, Zneg);
	// y positive
	v.set(Ypos);
	v.cross(Zpos);
	checkVectorEqual(v, Xpos);
	v.set(Ypos);
	v.cross(Xneg);
	checkVectorEqual(v, Zpos);
	v.set(Ypos);
	v.cross(Zneg);
	checkVectorEqual(v, Xneg);
	v.set(Ypos);
	v.cross(Xpos);
	checkVectorEqual(v, Zneg);
	// z positive
	v.set(Zpos);
	v.cross(Yneg);
	checkVectorEqual(v, Xpos);
	v.set(Zpos);
	v.cross(Xpos);
	checkVectorEqual(v, Ypos);
	v.set(Zpos);
	v.cross(Ypos);
	checkVectorEqual(v, Xneg);
	v.set(Zpos);
	v.cross(Xneg);
	checkVectorEqual(v, Yneg);
	// perpendicular
	v.set(2,3,4);
	w.set(v);
	v.perpendicular();
	CFIXCC_ASSERT_EQUALS(v.dot(w), 0.0f);
	v.set(-4,-2,-3);
	w.set(v);
	v.perpendicular();
	CFIXCC_ASSERT_EQUALS(v.dot(w), 0.0f);
}

CFIXCC_BEGIN_CLASS(Classes)
	CFIXCC_METHOD(test_define_lua_class)
	CFIXCC_METHOD(test_define_lua_LuaExtendable)
	CFIXCC_METHOD(test_define_lua_LuaExtendable_by_proxy)
	CFIXCC_METHOD(testVector3)
	CFIXCC_METHOD(testLuaExtension)
CFIXCC_END_CLASS()

#endif//EXTENDED_BY_LUA
#endif//BUILD_WITH_UNIT_TESTING
