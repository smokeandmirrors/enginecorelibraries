#include "Platform.h"
#if WITH_UNIT_TESTING && EXTENDED_BY_LUA
#include <cfixcc.h>

#include "LuaExtensionInclusions.h"
#include "Singleton.h"
#include "UTTools.h"

using namespace embeddedLua; 

class Zero
	: public designPatterns::Singleton<Zero>
{
public:
	const sint m_0;

	Zero(void) : m_0(0) {}
	
	static void staticReturn0Param0(void) 
	{
		CFIXCC_ASSERT_EQUALS(Zero::single().m_0, 0);
	}
	
	void constReturn0Param0(void) const 
	{ 
		return staticReturn0Param0();
	}

	void memberReturn0Param0(void) 
	{ 
		return staticReturn0Param0();
	}
}; // Zero
DECLARE_LUA_CLASS(Zero)
DEFINE_LUA_CLASS_NO_CTOR_NO_DTOR(CLASS, Zero, Zero)
	LUA_ENTRY_NAMED("staticReturn0Param0", (nativeStaticReturn0Param0<&Zero::staticReturn0Param0>))
	LUA_ENTRY_NAMED("constReturn0Param0", (nativeConstReturn0Param0<Zero, &Zero::constReturn0Param0>))
	LUA_ENTRY_NAMED("memberReturn0Param0", (nativeMemberReturn0Param0<Zero, &Zero::memberReturn0Param0>))
END_LUA_CLASS(Zero, Zero)

class One
: public designPatterns::Singleton<One>
{
public:
	static One* staticReturn1Param1(const One* param1) 
	{
		CFIXCC_ASSERT_EQUALS(param1->m_1, 1);
		return &One::single();
	}

	static One* staticReturn1Param0(void) 
	{
		return &One::single();
	}

	static void staticReturn0Param1(const One* param1)
	{
		CFIXCC_ASSERT_EQUALS(param1->m_1, 1);
	}

	const sint m_1;

	One(void) : m_1(1) {}
	
	One* constReturn1Param1(const One* param1) const 
	{ 
		return staticReturn1Param1(param1);
	}

	void constReturn0Param1(const One* param1) const
	{
		staticReturn0Param1(param1);
	}
	
	One* constReturn1Param0(void) const 
	{ 
		return staticReturn1Param0();
	}

	One* memberReturn1Param1(const One* param1)  
	{ 
		return staticReturn1Param1(param1);
	}

	void memberReturn0Param1(const One* param1) 
	{
		staticReturn0Param1(param1);
	}

	One* memberReturn1Param0(void) 
	{
		return staticReturn1Param0();
	}
}; // One

DECLARE_LUA_CLASS(One)
DEFINE_LUA_CLASS_NO_CTOR_NO_DTOR(CLASS, One, One)
	LUA_ENTRY_NAMED("staticReturn1Param1", (nativeStaticReturn1Param1<One*, const One*, &One::staticReturn1Param1>))
	LUA_ENTRY_NAMED("staticReturn1Param0", (nativeStaticReturn1Param0<One*, &One::staticReturn1Param0>))
	LUA_ENTRY_NAMED("staticReturn0Param1", (nativeStaticReturn0Param1<const One*, &One::staticReturn0Param1>))
	LUA_ENTRY_NAMED("constReturn1Param1", (nativeConstReturn1Param1<One, One*, const One*, &One::constReturn1Param1>))
	LUA_ENTRY_NAMED("constReturn1Param0", (nativeConstReturn1Param0<One, One*, &One::constReturn1Param0>))
	LUA_ENTRY_NAMED("constReturn0Param1", (nativeConstReturn0Param1<One, const One*, &One::constReturn0Param1>))
	LUA_ENTRY_NAMED("memberReturn1Param1", (nativeMemberReturn1Param1<One, One*, const One*, &One::memberReturn1Param1>))
	LUA_ENTRY_NAMED("memberReturn0Param1", (nativeMemberReturn0Param1<One, const One*, &One::memberReturn0Param1>))
	LUA_ENTRY_NAMED("memberReturn1Param0", (nativeMemberReturn1Param0<One, One*, &One::memberReturn1Param0>))
END_LUA_CLASS(One, One)

class Two 
	: public designPatterns::Singleton<Two>
{
public:	
	static One* staticReturn2Param2(Two*& return2, const One* param1, const Two* param2) 
	{
		CFIXCC_ASSERT_EQUALS(param1->m_1, 1);
		CFIXCC_ASSERT_EQUALS(param2->m_2, 2);
		return2 = &Two::single();
		return &One::single();
	}

	static One* staticReturn2Param1(Two*& return2, const One* param1) 
	{
		CFIXCC_ASSERT_EQUALS(param1->m_1, 1);
		return2 = &Two::single();
		return &One::single();
	}
	
	static One* staticReturn2Param0(Two*& return2) 
	{
		return2 = &Two::single();
		return &One::single();
	}

	static One* staticReturn1Param2(const One* param1, const Two* param2) 
	{
		CFIXCC_ASSERT_EQUALS(param1->m_1, 1);
		CFIXCC_ASSERT_EQUALS(param2->m_2, 2);
		return &One::single();
	}

	static void staticReturn0Param2(const One* param1, const Two* param2)
	{
		CFIXCC_ASSERT_EQUALS(param1->m_1, 1);
		CFIXCC_ASSERT_EQUALS(param2->m_2, 2);
	}

	const sint m_2;

	Two() : m_2(2) {}

	One* constReturn2Param2(Two*& return2, const One* param1, const Two* param2) const 
	{
		return staticReturn2Param2(return2, param1, param2);
	}

	One* constReturn2Param1(Two*& return2, const One* param1) const
	{
		return staticReturn2Param1(return2, param1);
	}

	One* constReturn2Param0(Two*& return2) const
	{
		return staticReturn2Param0(return2);
	}

	One* constReturn1Param2(const One* param1, const Two* param2) const
	{
		return staticReturn1Param2(param1, param2);
	}

	void constReturn0Param2(const One* param1, const Two* param2) const
	{
		staticReturn0Param2(param1, param2);
	}

	One* memberReturn2Param2(Two*& return2, const One* param1, const Two* param2)  
	{
		return staticReturn2Param2(return2, param1, param2);
	}

	One* memberReturn2Param1(Two*& return2, const One* param1) 
	{
		return staticReturn2Param1(return2, param1);
	}

	One* memberReturn2Param0(Two*& return2) 
	{
		return staticReturn2Param0(return2);
	}

	One* memberReturn1Param2(const One* param1, const Two* param2) 
	{
		return staticReturn1Param2(param1, param2);
	}

	void memberReturn0Param2(const One* param1, const Two* param2) 
	{
		staticReturn0Param2(param1, param2);
	}
}; // Two

DECLARE_LUA_CLASS(Two)
DEFINE_LUA_CLASS_NO_CTOR_NO_DTOR(CLASS, Two, Two)
END_LUA_CLASS(Two, Two)

class UTExposeNativeToScript : public cfixcc::TestFixture
{
private:

public:
	void Test()
	{
		DECLARE_UNIT_TESTING_LUA_OBJECT
		lua_State* L = lua.getState();
		REGISTER_LUA_LIBRARY((&lua), One);
		REGISTER_LUA_LIBRARY((&lua), Two);
		
		lua.require("UTExposeScriptToNative");

		One* param1 = &One::single();
		Two* param2 = &Two::single();
		One* return1;
		Two* return2;
		return1 = NULL;
		return2 = NULL;
		ScriptToNativeCallResult callResult;
		// call the script function
		return1 = NULL;
		return2 = NULL;
		callResult = phybridStaticReturn2Param2<One*, Two*, const One*, const Two*, &Two::staticReturn2Param2>(L, "staticReturn2Param2", return1, return2, param1, param2);
		CFIXCC_ASSERT_EQUALS(functionSuccess, callResult);	
		CFIXCC_ASSERT_EQUALS(&One::single(), return1);
		CFIXCC_ASSERT_EQUALS(&Two::single(), return2);
		// error the script function
		return1 = NULL;
		return2 = NULL;
		callResult = phybridStaticReturn2Param2<One*, Two*, const One*, const Two*, &Two::staticReturn2Param2>(L, "error", return1, return2, param1, param2);
		CFIXCC_ASSERT_EQUALS(functionError, callResult);	
		CFIX_ASSERT(!return1);
		CFIX_ASSERT(!return2);
		// don't find function
		return1 = NULL;
		return2 = NULL;
		callResult = phybridStaticReturn2Param2<One*, Two*, const One*, const Two*, &Two::staticReturn2Param2>(L, "UTNotFoundIdentifier", return1, return2, param1, param2);
		CFIXCC_ASSERT_EQUALS(functionNotFound, callResult);	
		CFIXCC_ASSERT_EQUALS(&One::single(), return1);
		CFIXCC_ASSERT_EQUALS(&Two::single(), return2);
		// don't find module 
		return1 = NULL;
		return2 = NULL;
		callResult = phybridStaticReturn2Param2<One*, Two*, const One*, const Two*, &Two::staticReturn2Param2>(L, "staticReturn2Param2", return1, return2, param1, param2, "UTNotFoundIdentifier");
		CFIXCC_ASSERT_EQUALS(moduleNotFound, callResult);	
		CFIXCC_ASSERT_EQUALS(&One::single(), return1);
		CFIXCC_ASSERT_EQUALS(&Two::single(), return2);	

		// call the script function
		return1 = NULL;
		return2 = NULL;
		callResult = phybridMemberReturn2Param2<Two, One*, Two*, const One*, const Two*, &Two::memberReturn2Param2>(L, "memberReturn2Param2Script", Two::single(), return1, return2, param1, param2);
		CFIXCC_ASSERT_EQUALS(functionSuccess, callResult);	
		CFIXCC_ASSERT_EQUALS(&One::single(), return1);
		CFIXCC_ASSERT_EQUALS(&Two::single(), return2);
		// error the script function
		return1 = NULL;
		return2 = NULL;
		callResult = phybridMemberReturn2Param2<Two, One*, Two*, const One*, const Two*, &Two::memberReturn2Param2>(L, "error", Two::single(), return1, return2, param1, param2);
		CFIXCC_ASSERT_EQUALS(functionError, callResult);	
		CFIX_ASSERT(!return1);
		CFIX_ASSERT(!return2);
		// don't find function
		return1 = NULL;
		return2 = NULL;
		callResult = phybridMemberReturn2Param2<Two, One*, Two*, const One*, const Two*, &Two::memberReturn2Param2>(L, "UTNotFoundIdentifier", Two::single(), return1, return2, param1, param2);
		CFIXCC_ASSERT_EQUALS(functionNotFound, callResult);	
		CFIXCC_ASSERT_EQUALS(&One::single(), return1);
		CFIXCC_ASSERT_EQUALS(&Two::single(), return2);
		
		// call the script function
		return1 = NULL;
		return2 = NULL;
		callResult = phybridConstReturn2Param2<Two, One*, Two*, const One*, const Two*, &Two::constReturn2Param2>(L, "constReturn2Param2Script", Two::single(), return1, return2, param1, param2);
		CFIXCC_ASSERT_EQUALS(functionSuccess, callResult);	
		CFIXCC_ASSERT_EQUALS(&One::single(), return1);
		CFIXCC_ASSERT_EQUALS(&Two::single(), return2);
		// error the script function
		return1 = NULL;
		return2 = NULL;
		callResult = phybridConstReturn2Param2<Two, One*, Two*, const One*, const Two*, &Two::constReturn2Param2>(L, "error", Two::single(), return1, return2, param1, param2);
		CFIXCC_ASSERT_EQUALS(functionError, callResult);	
		CFIX_ASSERT(!return1);
		CFIX_ASSERT(!return2);
		// don't find function
		return1 = NULL;
		return2 = NULL;
		callResult = phybridConstReturn2Param2<Two, One*, Two*, const One*, const Two*, &Two::constReturn2Param2>(L, "UTNotFoundIdentifier", Two::single(), return1, return2, param1, param2);
		CFIXCC_ASSERT_EQUALS(functionNotFound, callResult);	
		CFIXCC_ASSERT_EQUALS(&One::single(), return1);
		CFIXCC_ASSERT_EQUALS(&Two::single(), return2);
	}
};

CFIXCC_BEGIN_CLASS(UTExposeNativeToScript)
	CFIXCC_METHOD(Test)
CFIXCC_END_CLASS()
#endif//WITH_UNIT_TESTING