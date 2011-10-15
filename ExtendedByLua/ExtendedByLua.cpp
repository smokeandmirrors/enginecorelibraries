/**
ExtendedByLua.cpp 
Defines the entry point for the console application.
*/
#include <assert.h>
#include <stdio.h>
#include <tchar.h>

#include "LuaMathExtensions.h"

#if EXTENDED_BY_LUA
#pragma message("This executable is compiling with embedded lua.")
#include "LuaExtensionInclusions.h"
using namespace embeddedLua;
/** 
make sure all folders containing desired .lua files
relative to the working directory)
are included in the macro below
*/
#define LUA_PACKAGE_PATH_RUN_FROM_SOLUTION_DIR \
	"..\\LuaFiles\\?.lua;"  \
	"..\\LuaFiles\\UTLuaFiles\\?.lua;"
#endif//EXTENDED_BY_LUA

#if !GOLDMASTER
#define SANDBOX 1
#endif//!GOLDMASTER

#if SANDBOX
#include "Sandbox.h" 
#endif//SANDBOX

#include "Time.h"
#include "Vector.h"

#if WIN32
#include <process.h>
#include <windows.h>
#endif//WIN32

#define UNIT_TEST_VERIFICATION 0

#if UNIT_TEST_VERIFICATION

#endif//UNIT_TEST_VERIFICATION

class AllPublic
{
public:
	AllPublic(void) : one(1), two(true), three(3.0f) {}
	virtual ~AllPublic(void) {}
	sint 
		one;
	bool 
		two;
	sreal 
		three;

	void method0(void) { printf("native method0\n"); }
	void method0C(void) const { printf("const native method0\n"); }
	void method1(int value) { printf("native method1 %d\n", value); }
	void method1C(int value) const { printf("const native method1 %d\n", value); }
	sint methodr1(void) { return 4; }
	sint methodr1C(void) const { return 5; }
	sint method(void) const { return 17; }
	sint method2(void) const { return 3; }
};

class AllPublicChild : public AllPublic
{
public:
	AllPublicChild() : four(NULL), five(5) {}
	AllPublic* four;
	sint five;

	sint childMethod(void) const { return 1717; }
};

class AllPublicGrandChild : public AllPublicChild
{
public:
	AllPublicGrandChild() : six(NULL), seven(7) {}
	AllPublicChild* six;
	uint seven;

	sint grandChildMethod(void) const { return 171717; }
};


////////////////////////////////////////////////////////////////////////
class AllPublicLE : public LuaExtendable
{
	public:
	AllPublicLE(void) : one(1), two(true), three(3.0f) {}
	virtual ~AllPublicLE(void) {}
	sint 
		one;
	bool 
		two;
	sreal 
		three;

	DEFINE_LUAEXTENDABLE_PROXY_DEFAULT_FUNCTIONS(AllPublicLE)

	sint method(void) const { return 17; }
};

////////////////////////////////////////////////////////////////////////
class AllPublicChildLE : public AllPublicLE
{
public:
	AllPublicChildLE() : four(NULL), five(5) {}
	AllPublicLE* four;
	sint five;

	DEFINE_DEFAULT_TOSTRING(AllPublicChildLE)
	DEFINE_DEFAULT_GETCLASSNAME(AllPublicChildLE)

	sint childMethod(void) const { return 1717; }
};

////////////////////////////////////////////////////////////////////////
class AllPublicGrandChildLE : public AllPublicChildLE
{
public:
	AllPublicGrandChildLE() : six(NULL), seven(7) {}
	AllPublicChildLE* six;
	uint seven;

	sint grandChildMethod(void) const { return 171717; }
};

//////////////////////////////////////////////////////////////////////////
DECLARE_LUA_LUAEXTENDABLE(AllPublicLE)

DEFINE_LUA_FUNC__index_PUBLIC_MEMBERS_PROXY(AllPublicLE, AllPublicLE)
	__index_PROXY_MEMBER(one)
	__index_PROXY_MEMBER(two)
	__index_PROXY_MEMBER(three)
END_LUA_FUNC__index_PUBLIC_MEMBERS_PROXY(AllPublicLE, AllPublicLE)

DEFINE_LUA_FUNC__newindex_PUBLIC_MEMBERS_PROXY(AllPublicLE, AllPublicLE)
	__newindex_PROXY_MEMBER(one, sint)
	__newindex_PROXY_MEMBER(two, bool)
	__newindex_PROXY_MEMBER(three, sreal)
END_LUA_FUNC__newindex_PUBLIC_MEMBERS_PROXY(AllPublicLE, AllPublicLE)

DEFINE_LUA_CLASS_BY_PROXY_PUBLIC_MEMBERS(EXTENDABLE, AllPublicLE, AllPublicLE)
	LUA_ENTRY_NAMED("method", (nativeConstReturn1Param0<AllPublicLE, sint, &AllPublicLE::method>))
END_LUA_CLASS(AllPublicLE, AllPublicLE)


//////////////////////////////////////////////////////////////////////////
DECLARE_LUA_LUAEXTENDABLE(AllPublicChildLE)

DEFINE_LUA_FUNC__index_PUBLIC_MEMBERS_PROXY(AllPublicChildLE, AllPublicLE)
	__index_PROXY_MEMBER(four)
	__index_PROXY_MEMBER(five)
END_LUA_FUNC__index_PUBLIC_MEMBERS_PROXY(AllPublicChildLE, AllPublicLE)

DEFINE_LUA_FUNC__newindex_PUBLIC_MEMBERS_PROXY(AllPublicChildLE, AllPublicLE)
	__newindex_PROXY_MEMBER(four, AllPublicLE*)
	__newindex_PROXY_MEMBER(five, sint)
END_LUA_FUNC__newindex_PUBLIC_MEMBERS_PROXY(AllPublicChildLE, AllPublicLE)

DEFINE_LUA_CLASS_BY_PROXY_PUBLIC_MEMBERS(EXTENDABLE, AllPublicChildLE, AllPublicLE)
	LUA_ENTRY_NAMED("childMethod", (nativeConstReturn1Param0<AllPublicChildLE, sint, &AllPublicChildLE::childMethod>))
END_LUA_CLASS(AllPublicChildLE, AllPublicLE)

//////////////////////////////////////////////////////////////////////////
DECLARE_LUA_LUAEXTENDABLE(AllPublicGrandChildLE)

DEFINE_LUA_FUNC__index_PUBLIC_MEMBERS_PROXY(AllPublicGrandChildLE, AllPublicChildLE)
	__index_PROXY_MEMBER(six)
	__index_PROXY_MEMBER(seven)
END_LUA_FUNC__index_PUBLIC_MEMBERS_PROXY(AllPublicGrandChildLE, AllPublicChildLE)

DEFINE_LUA_FUNC__newindex_PUBLIC_MEMBERS_PROXY(AllPublicGrandChildLE, AllPublicChildLE)
	__newindex_PROXY_MEMBER(six, AllPublicChildLE*)
	__newindex_PROXY_MEMBER(seven, uint)
END_LUA_FUNC__newindex_PUBLIC_MEMBERS_PROXY(AllPublicGrandChildLE, AllPublicChildLE)

DEFINE_LUA_CLASS_BY_PROXY_PUBLIC_MEMBERS(EXTENDABLE, AllPublicGrandChildLE, AllPublicChildLE)
	LUA_ENTRY_NAMED("grandChildMethod", (nativeConstReturn1Param0<AllPublicGrandChildLE, sint, &AllPublicGrandChildLE::grandChildMethod>))
END_LUA_CLASS(AllPublicGrandChildLE, AllPublicChildLE)

// proxy versions
////////////////////////////////////////////////////////////////////////
//  DECLARE_LUA_CLASS(AllPublic);
//  
//  DEFINE_LUA_FUNC__index_PUBLIC_MEMBERS_PROXY(AllPublic, AllPublic)
//  	__index_PROXY_MEMBER(one)
//  	__index_PROXY_MEMBER(two)
//  	__index_PROXY_MEMBER(three)
//  END_LUA_FUNC__index_PUBLIC_MEMBERS_PROXY(AllPublic, AllPublic)
//  
//  DEFINE_LUA_FUNC__newindex_PUBLIC_MEMBERS_PROXY(AllPublic, AllPublic)
//  	__newindex_PROXY_MEMBER(one, sint)
//  	__newindex_PROXY_MEMBER(two, bool)
//  	__newindex_PROXY_MEMBER(three, sreal)
//  END_LUA_FUNC__newindex_PUBLIC_MEMBERS_PROXY(AllPublic, AllPublic)
//  
//  DEFINE_LUA_CLASS_BY_PROXY_PUBLIC_MEMBERS(CLASS, AllPublic, AllPublic)
//  	LUA_ENTRY_NAMED("method", (nativeConstReturn1Param0<AllPublic, sint, &AllPublic::method>))
//  	LUA_ENTRY__indexSupport(AllPublic)
//  	LUA_ENTRY__newindexSupport(AllPublic)
//  END_LUA_CLASS(AllPublic, AllPublic)
//  
//  
//  //////////////////////////////////////////////////////////////////////////
//  DECLARE_LUA_CLASS(AllPublicChild);
//  
//  DEFINE_LUA_FUNC__index_PUBLIC_MEMBERS_PROXY(AllPublicChild, AllPublic)
//  	__index_PROXY_MEMBER(four)
//  	__index_PROXY_MEMBER(five)
//  END_LUA_FUNC__index_PUBLIC_MEMBERS_PROXY(AllPublicChild, AllPublic)
//  
//  DEFINE_LUA_FUNC__newindex_PUBLIC_MEMBERS_PROXY(AllPublicChild, AllPublic)
//  	__newindex_PROXY_MEMBER(four, AllPublic*)
//  	__newindex_PROXY_MEMBER(five, sint)
//  END_LUA_FUNC__newindex_PUBLIC_MEMBERS_PROXY(AllPublicChild, AllPublic)
//  
//  DEFINE_LUA_CLASS_BY_PROXY_PUBLIC_MEMBERS(CLASS, AllPublicChild, AllPublic)
//  	LUA_ENTRY_NAMED("childMethod", (nativeConstReturn1Param0<AllPublicChild, sint, &AllPublicChild::childMethod>))
//  	LUA_ENTRY__indexSupport(AllPublicChild)
//  	LUA_ENTRY__newindexSupport(AllPublicChild)
//  END_LUA_CLASS(AllPublicChild, AllPublic)
//  
//  //////////////////////////////////////////////////////////////////////////
//  DECLARE_LUA_CLASS(AllPublicGrandChild);
//  
//  DEFINE_LUA_FUNC__index_PUBLIC_MEMBERS_PROXY(AllPublicGrandChild, AllPublicChild)
//  	__index_PROXY_MEMBER(six)
//  	__index_PROXY_MEMBER(seven)
//  END_LUA_FUNC__index_PUBLIC_MEMBERS_PROXY(AllPublicGrandChild, AllPublicChild)
//  
//  DEFINE_LUA_FUNC__newindex_PUBLIC_MEMBERS_PROXY(AllPublicGrandChild, AllPublicChild)
//  	__newindex_PROXY_MEMBER(six, AllPublicChild*)
//  	__newindex_PROXY_MEMBER(seven, uint)
//  END_LUA_FUNC__newindex_PUBLIC_MEMBERS_PROXY(AllPublicGrandChild, AllPublicChild)
//  
//  DEFINE_LUA_CLASS_BY_PROXY_PUBLIC_MEMBERS(CLASS, AllPublicGrandChild, AllPublicChild)
//  	LUA_ENTRY_NAMED("grandChildMethod", (nativeConstReturn1Param0<AllPublicGrandChild, sint, &AllPublicGrandChild::grandChildMethod>))
//  	LUA_ENTRY__indexSupport(AllPublicGrandChild)
//  	LUA_ENTRY__newindexSupport(AllPublicGrandChild)
//  END_LUA_CLASS(AllPublicGrandChild, AllPublicChild)


// non proxy versions
//////////////////////////////////////////////////////////////////////////
DECLARE_LUA_CLASS(AllPublic);

DEFINE_LUA_FUNC__index_PUBLIC_MEMBERS(AllPublic, AllPublic)
	__index_MEMBER(one)
	__index_MEMBER(two)
	__index_MEMBER(three)
END_LUA_FUNC__index_PUBLIC_MEMBERS(AllPublic, AllPublic)

DEFINE_LUA_FUNC__newindex_PUBLIC_MEMBERS(AllPublic, AllPublic)
	__newindex_MEMBER(one, sint)
	__newindex_MEMBER(two, bool)
	__newindex_MEMBER(three, sreal)
END_LUA_FUNC__newindex_PUBLIC_MEMBERS(AllPublic, AllPublic)

DEFINE_LUA_CLASS_PUBLIC_MEMBERS_NODTOR(CLASS, AllPublic, AllPublic)
	LUA_ENTRY_NAMED("method", (nativeConstReturn1Param0<AllPublic, sint, &AllPublic::method>))
END_LUA_CLASS(AllPublic, AllPublic)

//////////////////////////////////////////////////////////////////////////
DECLARE_LUA_CLASS(AllPublicChild);

DEFINE_LUA_FUNC__index_PUBLIC_MEMBERS(AllPublicChild, AllPublic)
	__index_MEMBER(four)
	__index_MEMBER(five)
END_LUA_FUNC__index_PUBLIC_MEMBERS(AllPublicChild, AllPublic)

DEFINE_LUA_FUNC__newindex_PUBLIC_MEMBERS(AllPublicChild, AllPublic)
__newindex_MEMBER(four, AllPublic*)
__newindex_MEMBER(five, sint)
END_LUA_FUNC__newindex_PUBLIC_MEMBERS(AllPublicChild, AllPublic)

DEFINE_LUA_CLASS_PUBLIC_MEMBERS(CLASS, AllPublicChild, AllPublic)
	LUA_ENTRY_NAMED("childMethod", (nativeConstReturn1Param0<AllPublicChild, sint, &AllPublicChild::childMethod>))
END_LUA_CLASS(AllPublicChild, AllPublic)

//////////////////////////////////////////////////////////////////////////
DECLARE_LUA_CLASS(AllPublicGrandChild);

DEFINE_LUA_FUNC__index_PUBLIC_MEMBERS(AllPublicGrandChild, AllPublicChild)
	__index_MEMBER(six)
	__index_MEMBER(seven)
END_LUA_FUNC__index_PUBLIC_MEMBERS(AllPublicGrandChild, AllPublicChild)

DEFINE_LUA_FUNC__newindex_PUBLIC_MEMBERS(AllPublicGrandChild, AllPublicChild)
	__newindex_MEMBER(six, AllPublicChild*)
	__newindex_MEMBER(seven, uint)
END_LUA_FUNC__newindex_PUBLIC_MEMBERS(AllPublicGrandChild, AllPublicChild)

DEFINE_LUA_CLASS_PUBLIC_MEMBERS(CLASS, AllPublicGrandChild, AllPublicChild)
	LUA_ENTRY_NAMED("grandChildMethod", (nativeConstReturn1Param0<AllPublicGrandChild, sint, &AllPublicGrandChild::grandChildMethod>))
END_LUA_CLASS(AllPublicGrandChild, AllPublicChild)

//////////////////////////////////////////////////////////////////////////
enum eNumbers
{
	One,
	Two,
	Three	
};

typedef enum eDirections
{
	Up,
	Down,
	Left,
	Right
};

enum ReadOnly
{
	ZeroRO,
	OneRO,
	TwoRO
};

//////////////////////////////////////////////////////////////////////////
DEFINE_LUA_ENUM(ReadOnly)
	LUA_ENUM(ZeroRO)
	LUA_ENUM(OneRO)
	LUA_ENUM(TwoRO)
END_LUA_ENUM(ReadOnly)

//////////////////////////////////////////////////////////////////////////
DEFINE_LUA_ENUM_BOUND(eDirections, Up, Right)
	LUA_ENUM(Down)
	LUA_ENUM(Left)
END_LUA_ENUM_BOUND(eDirections, Right)

//////////////////////////////////////////////////////////////////////////
DEFINE_LUA_ENUM(eNumbers)
	LUA_ENUM(One)
	LUA_ENUM(Two)
	LUA_ENUM(Three)
END_LUA_ENUM(eNumbers)

void returnZeroParamZero(void)
{
	printf("native zero zero\n");
}

void returnZeroParamOne(int value)
{
	printf("native zero one: %d\n", value);
}

sint returnOneParamZero(void)
{
	return 7;
}

using namespace realTime;

DEFINE_LUA_ENUM(BoolEnum)
	LUA_ENUM(BoolEnum_False)
	LUA_ENUM(BoolEnum_True)
	LUA_ENUM(BoolEnum_Unset)
END_LUA_ENUM(BoolEnum)

DECLARE_LUA_LIBRARY(realTime)
DEFINE_LUA_LIBRARY(realTime)
	LUA_ENTRY_NAMED("cycles", (nativeStaticReturn1Param0<cycle, &cycles>))
	LUA_ENTRY_NAMED("milliseconds", (nativeStaticReturn1Param0<millisecond, &milliseconds>))
	LUA_ENTRY_NAMED("seconds", (nativeStaticReturn1Param0<second, &seconds>))
END_LUA_LIBRARY(realTime)

DECLARE_LUA_CLASS(Clock)
DEFINE_LUA_CLASS_NO_CTOR(CLASS, Clock, Clock)
	LUA_ENTRY_NAMED("getRate", (nativeConstReturn1Param0<Clock, dreal, &Clock::getRate>))
	LUA_ENTRY_NAMED("getTick", (nativeConstReturn1Param0<Clock, cycle, &Clock::getTick>))
	LUA_ENTRY_NAMED("milliseconds", (nativeConstReturn1Param0<Clock, millisecond, &Clock::milliseconds>))
	LUA_ENTRY_NAMED("seconds", (nativeConstReturn1Param0<Clock, second, &Clock::seconds>))
	LUA_ENTRY_NAMED("setRate", (nativeMemberReturn0Param1<Clock, dreal, &Clock::setRate>))
	LUA_ENTRY_NAMED("tick", (nativeMemberReturn0Param0<Clock, &Clock::tick>))
END_LUA_CLASS(Clock, Clock)

DECLARE_LUA_CLASS(ClockReal)
DEFINE_LUA_CLASS(CLASS, ClockReal, Clock)
END_LUA_CLASS(ClockReal, Clock)

DECLARE_LUA_CLASS(ClockFrame)
DEFINE_LUA_CLASS(CLASS, ClockFrame, Clock)
END_LUA_CLASS(ClockFrame, Clock)

DECLARE_LUA_CLASS(ClockRelative)
LUA_FUNC(newClockRelative)
{
	return push(L, new ClockRelative(to<const Clock&>(L, -1)));
}
DEFINE_LUA_CLASS_NO_CTOR(CLASS, ClockRelative, Clock)
LUA_ENTRY_NAMED("__new", newClockRelative)
END_LUA_CLASS(ClockRelative, Clock)

DECLARE_LUA_CLASS(Stopwatch)
LUA_FUNC(newStopwatch)
{
	return push(L, new Stopwatch(to<const Clock&>(L, -1)));
}
DEFINE_LUA_CLASS_NO_CTOR(CLASS, Stopwatch, Stopwatch)
LUA_ENTRY_NAMED("__new", newStopwatch)
LUA_ENTRY_NAMED("start", (nativeMemberReturn0Param0<Stopwatch, &Stopwatch::start>))
LUA_ENTRY_NAMED("stop", (nativeMemberReturn0Param0<Stopwatch, &Stopwatch::stop>))
LUA_ENTRY_NAMED("reset", (nativeMemberReturn0Param0<Stopwatch, &Stopwatch::reset>))
LUA_ENTRY_NAMED("milliseconds", (nativeConstReturn1Param0<Stopwatch, millisecond, &Stopwatch::milliseconds>))
LUA_ENTRY_NAMED("seconds", (nativeConstReturn1Param0<Stopwatch, second, &Stopwatch::seconds>))
END_LUA_CLASS(Stopwatch, Stopwatch)

DECLARE_LUA_CLASS(Timer)
LUA_FUNC(newTimer)
{
	return push(L, new Timer(to<const Clock&>(L, -1)));
}
DEFINE_LUA_CLASS_NO_CTOR(CLASS, Timer, Timer)
LUA_ENTRY_NAMED("__new", newTimer)
LUA_ENTRY_NAMED("isTimeRemaining", (nativeMemberReturn1Param0<Timer, bool, &Timer::isTimeRemaining>))
LUA_ENTRY_NAMED("isTimeUp", (nativeMemberReturn1Param0<Timer, bool, &Timer::isTimeUp>))
LUA_ENTRY_NAMED("set", (nativeMemberReturn0Param3<Timer, second, second, BoolEnum, &Timer::set>))
LUA_ENTRY_NAMED("start", (nativeMemberReturn0Param0<Timer, &Timer::start>))
LUA_ENTRY_NAMED("stop", (nativeMemberReturn0Param0<Timer, &Timer::stop>))
LUA_ENTRY_NAMED("reset", (nativeMemberReturn0Param0<Timer, &Timer::reset>))
LUA_ENTRY_NAMED("milliseconds", (nativeConstReturn1Param0<Timer, millisecond, &Timer::milliseconds>))
LUA_ENTRY_NAMED("seconds", (nativeConstReturn1Param0<Timer, second, &Timer::seconds>))
END_LUA_CLASS(Timer, Timer)

sint _tmain(sint /* argc */, _TCHAR* /* argv[] */)
{
#if EXTENDED_BY_LUA 
	{
		embeddedLua::Lua lua;
		lua.setPackagePath(LUA_PACKAGE_PATH_RUN_FROM_SOLUTION_DIR);
		registerGlobalLibrary(lua.getState());
		lua.require("Utilities");
		lua.require("ObjectOrientedParadigm");
		REGISTER_LUA_ENUM((&lua), BoolEnum)
		REGISTER_LUA_ENUM((&lua), eDirections)
		REGISTER_LUA_ENUM((&lua), eNumbers)
		REGISTER_LUA_ENUM((&lua), ReadOnly)

		REGISTER_LUA_LIBRARY((&lua), AllPublic)
		REGISTER_LUA_LIBRARY((&lua), AllPublicChild)
		REGISTER_LUA_LIBRARY((&lua), AllPublicGrandChild)
		REGISTER_LUA_LIBRARY((&lua), AllPublicLE)
		REGISTER_LUA_LIBRARY((&lua), AllPublicChildLE)
		REGISTER_LUA_LIBRARY((&lua), AllPublicGrandChildLE)
		REGISTER_LUA_LIBRARY((&lua), Vector2)
		REGISTER_LUA_LIBRARY((&lua), Vector3)

		REGISTER_LUA_LIBRARY((&lua), realTime)
		REGISTER_LUA_LIBRARY((&lua), Clock)
		REGISTER_LUA_LIBRARY((&lua), ClockReal)
		REGISTER_LUA_LIBRARY((&lua), ClockRelative)
		REGISTER_LUA_LIBRARY((&lua), ClockFrame)
		REGISTER_LUA_LIBRARY((&lua), Timer) 
		REGISTER_LUA_LIBRARY((&lua), Stopwatch) 

#if UNIT_TEST_VERIFICATION
		REGISTER_LUA_LIBRARY((&lua), Grandparent2)
		REGISTER_LUA_LIBRARY((&lua), Parent2)
		REGISTER_LUA_LIBRARY((&lua), Child2)
#endif // UNIT_TEST_VERIFICATION

		// get the user file for easier rapid iteration
		lua.require("User");
		
#define POOR_MANS_TESTING 0
#if POOR_MANS_TESTING		
		
		lua_State* L = lua.getState();
		sreal return2(4);
		return2 = 4;
		bool return1(false);
		return1 = false;
		AllPublic ap;
				
		hybridMemberReturn0Param0<AllPublic, &AllPublic::method0>(L, "method0", ap);
		hybridConstReturn0Param0<AllPublic, &AllPublic::method0C>(L, "method0C", ap);
		phybridMemberReturn0Param0<AllPublic, &AllPublic::method0>(L, "method0", ap);
		phybridConstReturn0Param0<AllPublic, &AllPublic::method0C>(L, "method0C", ap);
		
		returnZeroParamZero();
		phybridStaticReturn0Param0<returnZeroParamZero>(L, "returnZeroParamZero");

		pcallStaticReturn0Param0(L, "returnZeroParamZero");
		pcallStaticReturn0Param0(L, "returnZeroParamZero1");
		pcallStaticReturn0Param0(L, "returnZeroParamZero", "moochy");
		pcallStaticReturn0Param0(L, "throwError");

		callStaticReturn0Param0(L, "returnZeroParamZero");
		callStaticReturn0Param0(L, "returnZeroParamZero1");
		callStaticReturn0Param0(L, "returnZeroParamZero", "moochy");
		// callStaticReturn0Param0(L, "throwError");
	
		printf("\n\nNEXT\n\n");

		int value(4);
		hybridMemberReturn0Param1<AllPublic, int, &AllPublic::method1>(L, "method1", ap, value);
		hybridConstReturn0Param1<AllPublic, int, &AllPublic::method1C>(L, "method1C", ap, value);
		phybridMemberReturn0Param1<AllPublic, int, &AllPublic::method1>(L, "method1", ap, value);
		phybridConstReturn0Param1<AllPublic, int, &AllPublic::method1C>(L, "method1C", ap, value);
		
		returnZeroParamOne(value);
				
		phybridStaticReturn0Param1<int, returnZeroParamOne>(L, "returnZeroParamOne", value);
		hybridStaticReturn0Param1<int, returnZeroParamOne>(L, "returnZeroParamOne", value);

		pcallStaticReturn0Param1<sint>(L, "returnZeroParamOne", value);
		pcallStaticReturn0Param1<sint>(L, "returnZeroParamOne1", value);
		pcallStaticReturn0Param1<sint>(L, "returnZeroParamOne", value, "moochy");
		pcallStaticReturn0Param1<sint>(L, "throwError", value);

		callStaticReturn0Param1<sint>(L, "returnZeroParamOne", value);
		callStaticReturn0Param1<sint>(L, "returnZeroParamOne1", value);
		callStaticReturn0Param1<sint>(L, "returnZeroParamOne", value, "moochy");
		// callStaticReturn0Param0(L, "throwError");
		
		printf("\n\nNEXT\n\n");
		value = -888;
		hybridMemberReturn1Param0<AllPublic, int, &AllPublic::methodr1>(L, "methodr1", ap, value);
		hybridConstReturn1Param0<AllPublic, int, &AllPublic::methodr1C>(L, "methodr1C", ap, value);
		phybridMemberReturn1Param0<AllPublic, int, &AllPublic::methodr1>(L, "methodr1", ap, value);
		phybridConstReturn1Param0<AllPublic, int, &AllPublic::methodr1C>(L, "methodr1C", ap, value);

		value = returnOneParamZero();

		phybridStaticReturn1Param0<int, returnOneParamZero>(L, "returnOneParamZero", value);
		hybridStaticReturn1Param0<int, returnOneParamZero>(L, "returnOneParamZero", value);

		pcallStaticReturn1Param0<sint>(L, "returnOneParamZero", value);
		pcallStaticReturn1Param0<sint>(L, "returnOneParamZero1", value);
		pcallStaticReturn1Param0<sint>(L, "returnOneParamZero", value, "moochy");
		pcallStaticReturn1Param0<sint>(L, "throwError", value);

		callStaticReturn1Param0<sint>(L, "returnOneParamZero", value);
		callStaticReturn1Param0<sint>(L, "returnOneParamZero1", value);
		callStaticReturn1Param0<sint>(L, "returnOneParamZero", value, "moochy");

		float value2 = 3.0f;
		callStaticReturn1Param0<float>(L, "returnOneParamZero", value2);
		 value2 = 3.14f;
		callStaticReturn0Param1<float>(L, "returnZeroParamOne", value2);
		
		// callStaticReturn0Param0(L, "throwError");
#endif//POOR_MANS_TESTING			

		lua.runConsole();
	}
#endif//EXTENDED_BY_LUA
	
#if SANDBOX
	sandbox::play();// just plays with C/C++ compile/runtime functionality
#endif//SANDBOX	
	return 0;
}

