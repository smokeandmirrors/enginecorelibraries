#include <assert.h>
#include <stdio.h>
#include <tchar.h>

#include "Constructors.h"
#include "Time.h"
#include "UnitTestVerification.h"
#include "Vector.h"
#if EXTENDED_BY_LUA
#include "LuaExtensionInclusions.h"
#include "LuaMathExtensions.h"

using namespace embeddedLua;

#define LUA_PACKAGE_PATH_RUN_FROM_SOLUTION_DIR \
	"..\\LuaFiles\\?.lua;"  \
	"..\\LuaFiles\\UTLuaFiles\\?.lua;"

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

DEFINE_LUA_PUBLIC_MEMBER_INDEXING(AllPublicLE, AllPublicLE)
LUA_PUBLIC_MEMBER_INDEX_ENTRY(AllPublicLE, sint, one)
LUA_PUBLIC_MEMBER_INDEX_ENTRY(AllPublicLE, bool, two)
LUA_PUBLIC_MEMBER_INDEX_ENTRY(AllPublicLE, sreal, three)
END_LUA_PUBLIC_MEMBER_INDEXING(AllPublicLE, AllPublicLE)

DEFINE_LUA_CLASS_BY_PROXY_PUBLIC_MEMBERS(EXTENDABLE, AllPublicLE, AllPublicLE)
LUA_ENTRY_NAMED("method", (nativeConstReturn1Param0<AllPublicLE, sint, &AllPublicLE::method>))
END_LUA_CLASS(AllPublicLE, AllPublicLE)


//////////////////////////////////////////////////////////////////////////
DECLARE_LUA_LUAEXTENDABLE(AllPublicChildLE)

DEFINE_LUA_PUBLIC_MEMBER_INDEXING(AllPublicChildLE, AllPublicLE)
LUA_PUBLIC_MEMBER_INDEX_ENTRY(AllPublicChildLE, AllPublicLE*, four)
LUA_PUBLIC_MEMBER_INDEX_ENTRY(AllPublicChildLE, sint, five)
END_LUA_PUBLIC_MEMBER_INDEXING(AllPublicChildLE, AllPublicLE)

DEFINE_LUA_CLASS_BY_PROXY_PUBLIC_MEMBERS(EXTENDABLE, AllPublicChildLE, AllPublicLE)
LUA_ENTRY_NAMED("childMethod", (nativeConstReturn1Param0<AllPublicChildLE, sint, &AllPublicChildLE::childMethod>))
END_LUA_CLASS(AllPublicChildLE, AllPublicLE)

//////////////////////////////////////////////////////////////////////////
DECLARE_LUA_LUAEXTENDABLE(AllPublicGrandChildLE)

DEFINE_LUA_PUBLIC_MEMBER_INDEXING(AllPublicGrandChildLE, AllPublicChildLE)
LUA_PUBLIC_MEMBER_INDEX_ENTRY(AllPublicGrandChildLE, AllPublicChildLE*, six)
LUA_PUBLIC_MEMBER_INDEX_ENTRY(AllPublicGrandChildLE, uint, seven)
END_LUA_PUBLIC_MEMBER_INDEXING(AllPublicGrandChildLE, AllPublicChildLE)

DEFINE_LUA_CLASS_BY_PROXY_PUBLIC_MEMBERS(EXTENDABLE, AllPublicGrandChildLE, AllPublicChildLE)
LUA_ENTRY_NAMED("grandChildMethod", (nativeConstReturn1Param0<AllPublicGrandChildLE, sint, &AllPublicGrandChildLE::grandChildMethod>))
END_LUA_CLASS(AllPublicGrandChildLE, AllPublicChildLE)

// proxy versions
////////////////////////////////////////////////////////////////////////
//  DECLARE_LUA_CLASS(AllPublic);
//  
//  DEFINE_LUA_PUBLIC_MEMBER_INDEXING(AllPublic, AllPublic)
//  	LUA_PUBLIC_MEMBER_INDEX_ENTRY(one, sint)
//  	LUA_PUBLIC_MEMBER_INDEX_ENTRY(two, bool)
//  	LUA_PUBLIC_MEMBER_INDEX_ENTRY(three, sreal)
//  END_LUA_PUBLIC_MEMBER_INDEXING(AllPublic, AllPublic)
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
//  DEFINE_LUA_PUBLIC_MEMBER_INDEXING(AllPublicChild, AllPublic)
//  	LUA_PUBLIC_MEMBER_INDEX_ENTRY(four, AllPublic*)
//  	LUA_PUBLIC_MEMBER_INDEX_ENTRY(five, sint)
//  END_LUA_PUBLIC_MEMBER_INDEXING(AllPublicChild, AllPublic)
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
//  DEFINE_LUA_PUBLIC_MEMBER_INDEXING(AllPublicGrandChild, AllPublicChild)
//  	LUA_PUBLIC_MEMBER_INDEX_ENTRY(six, AllPublicChild*)
//  	LUA_PUBLIC_MEMBER_INDEX_ENTRY(seven, uint)
//  END_LUA_PUBLIC_MEMBER_INDEXING(AllPublicGrandChild, AllPublicChild)
//  
//  DEFINE_LUA_CLASS_BY_PROXY_PUBLIC_MEMBERS(CLASS, AllPublicGrandChild, AllPublicChild)
//  	LUA_ENTRY_NAMED("grandChildMethod", (nativeConstReturn1Param0<AllPublicGrandChild, sint, &AllPublicGrandChild::grandChildMethod>))
//  	LUA_ENTRY__indexSupport(AllPublicGrandChild)
//  	LUA_ENTRY__newindexSupport(AllPublicGrandChild)
//  END_LUA_CLASS(AllPublicGrandChild, AllPublicChild)


// non proxy versions
//////////////////////////////////////////////////////////////////////////
DECLARE_LUA_CLASS(AllPublic);

DEFINE_LUA_PUBLIC_MEMBER_INDEXING(AllPublic, AllPublic)
LUA_PUBLIC_MEMBER_INDEX_ENTRY(AllPublic, sint, one)
LUA_PUBLIC_MEMBER_INDEX_ENTRY(AllPublic, bool, two)
LUA_PUBLIC_MEMBER_INDEX_ENTRY(AllPublic, sreal, three)
END_LUA_PUBLIC_MEMBER_INDEXING(AllPublic, AllPublic)

DEFINE_LUA_CLASS_PUBLIC_MEMBERS_NODTOR(CLASS, AllPublic, AllPublic)
LUA_ENTRY_NAMED("method", (nativeConstReturn1Param0<AllPublic, sint, &AllPublic::method>))
END_LUA_CLASS(AllPublic, AllPublic)

//////////////////////////////////////////////////////////////////////////
DECLARE_LUA_CLASS(AllPublicChild);

DEFINE_LUA_PUBLIC_MEMBER_INDEXING(AllPublicChild, AllPublic)
LUA_PUBLIC_MEMBER_INDEX_ENTRY(AllPublicChild, AllPublic*, four)
LUA_PUBLIC_MEMBER_INDEX_ENTRY(AllPublicChild, sint, five)
END_LUA_PUBLIC_MEMBER_INDEXING(AllPublicChild, AllPublic)

DEFINE_LUA_CLASS_PUBLIC_MEMBERS(CLASS, AllPublicChild, AllPublic)
LUA_ENTRY_NAMED("childMethod", (nativeConstReturn1Param0<AllPublicChild, sint, &AllPublicChild::childMethod>))
END_LUA_CLASS(AllPublicChild, AllPublic)

//////////////////////////////////////////////////////////////////////////
DECLARE_LUA_CLASS(AllPublicGrandChild);

DEFINE_LUA_PUBLIC_MEMBER_INDEXING(AllPublicGrandChild, AllPublicChild)
LUA_PUBLIC_MEMBER_INDEX_ENTRY(AllPublicGrandChild, AllPublicChild*, six)
LUA_PUBLIC_MEMBER_INDEX_ENTRY(AllPublicGrandChild, uint, seven)
END_LUA_PUBLIC_MEMBER_INDEXING(AllPublicGrandChild, AllPublicChild)

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

using namespace xronos;

DEFINE_LUA_ENUM(BoolEnum)
LUA_ENUM(BoolEnum_False)
LUA_ENUM(BoolEnum_True)
LUA_ENUM(BoolEnum_Unset)
END_LUA_ENUM(BoolEnum)

/*
DECLARE_LUA_LIBRARY(xronos)
DEFINE_LUA_LIBRARY(xronos)
LUA_ENTRY_NAMED("cycles", (nativeStaticReturn1Param0<cycle, &cycles>))
LUA_ENTRY_NAMED("milliseconds", (nativeStaticReturn1Param0<millisecond, &milliseconds>))
LUA_ENTRY_NAMED("seconds", (nativeStaticReturn1Param0<second, &seconds>))
END_LUA_LIBRARY(xronos)

DECLARE_LUA_CLASS(ClockInterface)
DEFINE_LUA_CLASS_NO_CTOR(CLASS, ClockInterface, ClockInterface)
LUA_ENTRY_NAMED("getRate", (nativeConstReturn1Param0<ClockInterface, dreal, &ClockInterface::getRate>))
LUA_ENTRY_NAMED("getTick", (nativeConstReturn1Param0<ClockInterface, cycle, &ClockInterface::getTick>))
LUA_ENTRY_NAMED("milliseconds", (nativeConstReturn1Param0<ClockInterface, millisecond, &ClockInterface::milliseconds>))
LUA_ENTRY_NAMED("seconds", (nativeConstReturn1Param0<ClockInterface, second, &ClockInterface::seconds>))
LUA_ENTRY_NAMED("setRate", (nativeMemberReturn0Param1<ClockInterface, dreal, &ClockInterface::setRate>))
LUA_ENTRY_NAMED("tick", (nativeMemberReturn0Param0<ClockInterface, &ClockInterface::tick>))
END_LUA_CLASS(ClockInterface, ClockInterface)

DECLARE_LUA_CLASS(Clock)
DEFINE_LUA_CLASS_NO_CTOR_NO_DTOR(CLASS, Clock, ClockInterface)
END_LUA_CLASS(Clock, ClockInterface)

DECLARE_LUA_CLASS(ClockFrame)
DEFINE_LUA_CLASS(CLASS, ClockFrame, ClockInterface)
END_LUA_CLASS(ClockFrame, ClockInterface)

DECLARE_LUA_CLASS(ClockRelative)
DEFINE_LUA_CLASS_NO_CTOR(CLASS, ClockRelative, ClockInterface)
LUA_ENTRY_NAMED("__new", (&__new<ClockRelative, const ClockInterface&>))
END_LUA_CLASS(ClockRelative, ClockInterface)

DECLARE_LUA_CLASS(Stopwatch)
DEFINE_LUA_CLASS_NO_CTOR(CLASS, Stopwatch, Stopwatch)
LUA_ENTRY_NAMED("__new", (&__new<Stopwatch, const ClockInterface&>))
LUA_ENTRY_NAMED("start", (nativeMemberReturn0Param0<Stopwatch, &Stopwatch::start>))
LUA_ENTRY_NAMED("stop", (nativeMemberReturn0Param0<Stopwatch, &Stopwatch::stop>))
LUA_ENTRY_NAMED("reset", (nativeMemberReturn0Param0<Stopwatch, &Stopwatch::reset>))
LUA_ENTRY_NAMED("milliseconds", (nativeConstReturn1Param0<Stopwatch, millisecond, &Stopwatch::milliseconds>))
LUA_ENTRY_NAMED("seconds", (nativeConstReturn1Param0<Stopwatch, second, &Stopwatch::seconds>))
END_LUA_CLASS(Stopwatch, Stopwatch)

DECLARE_LUA_CLASS(Timer)
DEFINE_LUA_CLASS_NO_CTOR(CLASS, Timer, Timer)
LUA_ENTRY_NAMED("__new", (&__new<Timer, const ClockInterface&>))
LUA_ENTRY_NAMED("isTimeRemaining", (nativeMemberReturn1Param0<Timer, bool, &Timer::isTimeRemaining>))
LUA_ENTRY_NAMED("isTimeUp", (nativeMemberReturn1Param0<Timer, bool, &Timer::isTimeUp>))
LUA_ENTRY_NAMED("set", (nativeMemberReturn0Param3<Timer, second, second, BoolEnum, &Timer::set>))
LUA_ENTRY_NAMED("start", (nativeMemberReturn0Param0<Timer, &Timer::start>))
LUA_ENTRY_NAMED("stop", (nativeMemberReturn0Param0<Timer, &Timer::stop>))
LUA_ENTRY_NAMED("reset", (nativeMemberReturn0Param0<Timer, &Timer::reset>))
LUA_ENTRY_NAMED("milliseconds", (nativeConstReturn1Param0<Timer, millisecond, &Timer::milliseconds>))
LUA_ENTRY_NAMED("seconds", (nativeConstReturn1Param0<Timer, second, &Timer::seconds>))
END_LUA_CLASS(Timer, Timer)
*/



using namespace embeddedLua;

class TC
{
public:
	TC(void) : one(1), two(true), three(3.5f) {}
	virtual ~TC(void) {}
	sint method(void) const { return 17; }
	sint one;
	bool two;
	sreal three;
};
DECLARE_LUA_CLASS(TC);

DEFINE_LUA_PUBLIC_MEMBER_INDEXING(TC, TC)
LUA_PUBLIC_MEMBER_INDEX_ENTRY(TC, sint, one)
LUA_PUBLIC_MEMBER_INDEX_ENTRY(TC, bool, two)
LUA_PUBLIC_MEMBER_INDEX_ENTRY(TC, sreal, three)
END_LUA_PUBLIC_MEMBER_INDEXING(TC, TC)
DEFINE_LUA_CLASS_PUBLIC_MEMBERS(CLASS, TC, TC)
LUA_ENTRY_NAMED("method", (nativeConstReturn1Param0<TC, sint, &TC::method>))
END_LUA_CLASS(TC, TC)

class TCChild : public TC
{
public:
	TCChild() : four(NULL), five(-5) {}
	sint childMethod(void) const { return 1717; }
	TC* four;
	sint five;
};
DECLARE_LUA_CLASS(TCChild);
DEFINE_LUA_PUBLIC_MEMBER_INDEXING(TCChild, TC)
LUA_PUBLIC_MEMBER_INDEX_ENTRY(TCChild, TC*, four)
LUA_PUBLIC_MEMBER_INDEX_ENTRY(TCChild, sint, five)
END_LUA_PUBLIC_MEMBER_INDEXING(TCChild, TC)
DEFINE_LUA_CLASS_PUBLIC_MEMBERS(CLASS, TCChild, TC)
LUA_ENTRY_NAMED("childMethod", (nativeConstReturn1Param0<TCChild, sint, &TCChild::childMethod>))
END_LUA_CLASS(TCChild, TC)

class TCGrandChild : public TCChild
{
public:
	TCGrandChild() : six(NULL), seven(7) {}
	sint grandChildMethod(void) const { return 171717; }
	TCChild* six;
	uint seven;
};
DECLARE_LUA_CLASS(TCGrandChild);
DEFINE_LUA_PUBLIC_MEMBER_INDEXING(TCGrandChild, TCChild)
LUA_PUBLIC_MEMBER_INDEX_ENTRY(TCGrandChild, TCChild*, six)
LUA_PUBLIC_MEMBER_INDEX_ENTRY(TCGrandChild, uint, seven)
END_LUA_PUBLIC_MEMBER_INDEXING(TCGrandChild, TCChild)
DEFINE_LUA_CLASS_PUBLIC_MEMBERS(CLASS, TCGrandChild, TCChild)
LUA_ENTRY_NAMED("grandChildMethod", (nativeConstReturn1Param0<TCGrandChild, sint, &TCGrandChild::grandChildMethod>))
END_LUA_CLASS(TCGrandChild, TCChild)

class ProxyTC
{
public:
	ProxyTC(void) : one(1), two(true), three(3.5f) {}
	virtual ~ProxyTC(void) {}
	sint method(void) const { return 17; }
	sint one;
	bool two;
	sreal three;
};
DECLARE_LUA_CLASS(ProxyTC);
DEFINE_LUA_PUBLIC_MEMBER_INDEXING(ProxyTC, ProxyTC)
LUA_PUBLIC_MEMBER_INDEX_ENTRY(ProxyTC, sint, one)
LUA_PUBLIC_MEMBER_INDEX_ENTRY(ProxyTC, bool, two)
LUA_PUBLIC_MEMBER_INDEX_ENTRY(ProxyTC, sreal, three)
END_LUA_PUBLIC_MEMBER_INDEXING(ProxyTC, ProxyTC)
DEFINE_LUA_CLASS_BY_PROXY_PUBLIC_MEMBERS(CLASS, ProxyTC, ProxyTC)
LUA_ENTRY_NAMED("method", (nativeConstReturn1Param0<ProxyTC, sint, &ProxyTC::method>))
LUA_ENTRY__indexSupport(ProxyTC)
LUA_ENTRY__newindexSupport(ProxyTC)
END_LUA_CLASS(ProxyTC, ProxyTC)

class ProxyTCChild : public ProxyTC
{
public:
	ProxyTCChild() : four(NULL), five(-5) {}
	sint childMethod(void) const { return 1717; }
	ProxyTC* four;
	sint five;
};
DECLARE_LUA_CLASS(ProxyTCChild);
DEFINE_LUA_PUBLIC_MEMBER_INDEXING(ProxyTCChild, ProxyTC)
LUA_PUBLIC_MEMBER_INDEX_ENTRY(ProxyTCChild, ProxyTC*, four)
LUA_PUBLIC_MEMBER_INDEX_ENTRY(ProxyTCChild, sint, five)
END_LUA_PUBLIC_MEMBER_INDEXING(ProxyTCChild, ProxyTC)
DEFINE_LUA_CLASS_BY_PROXY_PUBLIC_MEMBERS(CLASS, ProxyTCChild, ProxyTC)
LUA_ENTRY_NAMED("childMethod", (nativeConstReturn1Param0<ProxyTCChild, sint, &ProxyTCChild::childMethod>))
LUA_ENTRY__indexSupport(ProxyTCChild)
LUA_ENTRY__newindexSupport(ProxyTCChild)
END_LUA_CLASS(ProxyTCChild, ProxyTC)

class ProxyTCGrandChild : public ProxyTCChild
{
public:
	ProxyTCGrandChild() : six(NULL), seven(7) {}
	sint grandChildMethod(void) const { return 171717; }
	ProxyTCChild* six;
	uint seven;
};
//////////////////////////////////////////////////////////////////////////
DECLARE_LUA_CLASS(ProxyTCGrandChild);
DEFINE_LUA_PUBLIC_MEMBER_INDEXING(ProxyTCGrandChild, ProxyTCChild)
LUA_PUBLIC_MEMBER_INDEX_ENTRY(ProxyTCGrandChild, ProxyTCChild*, six)
LUA_PUBLIC_MEMBER_INDEX_ENTRY(ProxyTCGrandChild, uint, seven)
END_LUA_PUBLIC_MEMBER_INDEXING(ProxyTCGrandChild, ProxyTCChild)
DEFINE_LUA_CLASS_BY_PROXY_PUBLIC_MEMBERS(CLASS, ProxyTCGrandChild, ProxyTCChild)
LUA_ENTRY_NAMED("grandChildMethod", (nativeConstReturn1Param0<ProxyTCGrandChild, sint, &ProxyTCGrandChild::grandChildMethod>))
LUA_ENTRY__indexSupport(ProxyTCGrandChild)
LUA_ENTRY__newindexSupport(ProxyTCGrandChild)
END_LUA_CLASS(ProxyTCGrandChild, ProxyTCChild)


class TCLE : public LuaExtendable
{
public:
	TCLE(void) : one(1), two(true), three(3.5f) {}
	virtual ~TCLE(void) {}
	sint method(void) const { return 17; }
	sint one;
	bool two;
	sreal three;

	DEFINE_LUAEXTENDABLE_USERDATA_DEFAULT_FUNCTIONS(TCLE)
};
DECLARE_LUA_LUAEXTENDABLE(TCLE);
DEFINE_LUA_PUBLIC_MEMBER_INDEXING(TCLE, TCLE)
LUA_PUBLIC_MEMBER_INDEX_ENTRY(TCLE, sint, one)
LUA_PUBLIC_MEMBER_INDEX_ENTRY(TCLE, bool, two)
LUA_PUBLIC_MEMBER_INDEX_ENTRY(TCLE, sreal, three)
END_LUA_PUBLIC_MEMBER_INDEXING(TCLE, TCLE)
DEFINE_LUA_CLASS_PUBLIC_MEMBERS(EXTENDABLE, TCLE, TCLE)
LUA_ENTRY_NAMED("method", (nativeConstReturn1Param0<TCLE, sint, &TCLE::method>))
END_LUA_CLASS(TCLE, TCLE)


class TCLEChild : public TCLE
{
public:
	TCLEChild() : four(NULL), five(-5) {}
	sint childMethod(void) const { return 1717; }
	TCLE* four;
	sint five;

	DEFINE_DEFAULT_TOSTRING(TCLEChild)
		DEFINE_DEFAULT_GETCLASSNAME(TCLEChild)
};
DECLARE_LUA_LUAEXTENDABLE(TCLEChild);
DEFINE_LUA_PUBLIC_MEMBER_INDEXING(TCLEChild, TCLE)
LUA_PUBLIC_MEMBER_INDEX_ENTRY(TCLEChild, TCLE*, four)
LUA_PUBLIC_MEMBER_INDEX_ENTRY(TCLEChild, sint, five)
END_LUA_PUBLIC_MEMBER_INDEXING(TCLEChild, TCLE)
DEFINE_LUA_CLASS_PUBLIC_MEMBERS(EXTENDABLE, TCLEChild, TCLE)
LUA_ENTRY_NAMED("childMethod", (nativeConstReturn1Param0<TCLEChild, sint, &TCLEChild::childMethod>))
END_LUA_CLASS(TCLEChild, TCLE)


class TCLEGrandChild : public TCLEChild
{
public:
	TCLEGrandChild() : six(NULL), seven(7) {}
	sint grandChildMethod(void) const { return 171717; }
	TCLEChild* six;
	uint seven;

	DEFINE_DEFAULT_TOSTRING(TCLEGrandChild)
		DEFINE_DEFAULT_GETCLASSNAME(TCLEGrandChild)
};
DECLARE_LUA_LUAEXTENDABLE(TCLEGrandChild);
DEFINE_LUA_PUBLIC_MEMBER_INDEXING(TCLEGrandChild, TCLEChild)
LUA_PUBLIC_MEMBER_INDEX_ENTRY(TCLEGrandChild, TCLEChild*, six)
LUA_PUBLIC_MEMBER_INDEX_ENTRY(TCLEGrandChild, uint, seven)
END_LUA_PUBLIC_MEMBER_INDEXING(TCLEGrandChild, TCLEChild)
DEFINE_LUA_CLASS_PUBLIC_MEMBERS(EXTENDABLE, TCLEGrandChild, TCLEChild)
LUA_ENTRY_NAMED("grandChildMethod", (nativeConstReturn1Param0<TCLEGrandChild, sint, &TCLEGrandChild::grandChildMethod>))
END_LUA_CLASS(TCLEGrandChild, TCLEChild)


class ProxyTCLE : public LuaExtendable
{
public:
	ProxyTCLE(void) : one(1), two(true), three(3.5f) {}
	virtual ~ProxyTCLE(void) {}
	sint method(void) const { return 17; }
	sint one;
	bool two;
	sreal three;

	DEFINE_LUAEXTENDABLE_PROXY_DEFAULT_FUNCTIONS(ProxyTCLE)
};
DECLARE_LUA_LUAEXTENDABLE(ProxyTCLE)
DEFINE_LUA_PUBLIC_MEMBER_INDEXING(ProxyTCLE, ProxyTCLE)
LUA_PUBLIC_MEMBER_INDEX_ENTRY(ProxyTCLE, sint, one)
LUA_PUBLIC_MEMBER_INDEX_ENTRY(ProxyTCLE, bool, two)
LUA_PUBLIC_MEMBER_INDEX_ENTRY(ProxyTCLE, sreal, three)
END_LUA_PUBLIC_MEMBER_INDEXING(ProxyTCLE, ProxyTCLE)
DEFINE_LUA_CLASS_BY_PROXY_PUBLIC_MEMBERS(EXTENDABLE, ProxyTCLE, ProxyTCLE)
LUA_ENTRY_NAMED("method", (nativeConstReturn1Param0<ProxyTCLE, sint, &ProxyTCLE::method>))
END_LUA_CLASS(ProxyTCLE, ProxyTCLE)

class ProxyTCLEChild : public ProxyTCLE
{
public:
	ProxyTCLEChild() : four(NULL), five(-5) {}
	sint childMethod(void) const { return 1717; }
	ProxyTCLE* four;
	sint five;

	DEFINE_DEFAULT_TOSTRING(ProxyTCLEChild)
		DEFINE_DEFAULT_GETCLASSNAME(ProxyTCLEChild)
};
DECLARE_LUA_LUAEXTENDABLE(ProxyTCLEChild)
DEFINE_LUA_PUBLIC_MEMBER_INDEXING(ProxyTCLEChild, ProxyTCLE)
LUA_PUBLIC_MEMBER_INDEX_ENTRY(ProxyTCLEChild, ProxyTCLE*, four)
LUA_PUBLIC_MEMBER_INDEX_ENTRY(ProxyTCLEChild, sint, five)
END_LUA_PUBLIC_MEMBER_INDEXING(ProxyTCLEChild, ProxyTCLE)
DEFINE_LUA_CLASS_BY_PROXY_PUBLIC_MEMBERS(EXTENDABLE, ProxyTCLEChild, ProxyTCLE)
LUA_ENTRY_NAMED("childMethod", (nativeConstReturn1Param0<ProxyTCLEChild, sint, &ProxyTCLEChild::childMethod>))
END_LUA_CLASS(ProxyTCLEChild, ProxyTCLE)

class ProxyTCLEGrandChild : public ProxyTCLEChild
{
public:
	ProxyTCLEGrandChild() : six(NULL), seven(7) {}
	sint grandChildMethod(void) const { return 171717; }
	ProxyTCLEChild* six;
	uint seven;

	DEFINE_DEFAULT_TOSTRING(ProxyTCLEGrandChild)
		DEFINE_DEFAULT_GETCLASSNAME(ProxyTCLEGrandChild)
};
DECLARE_LUA_LUAEXTENDABLE(ProxyTCLEGrandChild);
DEFINE_LUA_PUBLIC_MEMBER_INDEXING(ProxyTCLEGrandChild, ProxyTCLEChild)
LUA_PUBLIC_MEMBER_INDEX_ENTRY(ProxyTCLEGrandChild, ProxyTCLEChild*, six)
LUA_PUBLIC_MEMBER_INDEX_ENTRY(ProxyTCLEGrandChild, uint, seven)
END_LUA_PUBLIC_MEMBER_INDEXING(ProxyTCLEGrandChild, ProxyTCLEChild)
DEFINE_LUA_CLASS_BY_PROXY_PUBLIC_MEMBERS(EXTENDABLE, ProxyTCLEGrandChild, ProxyTCLEChild)
LUA_ENTRY_NAMED("grandChildMethod", (nativeConstReturn1Param0<ProxyTCLEGrandChild, sint, &ProxyTCLEGrandChild::grandChildMethod>))
END_LUA_CLASS(ProxyTCLEGrandChild, ProxyTCLEChild)








void executeLuaUnitTest(char* module, Lua* lua)
{
	bool delete_lua(false);

	if (!lua)
	{
		lua = new Lua();
		lua->setPackagePath("C:\\Users\\carlos.curran\\Documents\\enginecorelibraries\\LuaFiles\\?.lua;" 
			"C:\\Users\\carlos.curran\\Documents\\enginecorelibraries\\LuaFiles\\UTLuaFiles\\?.lua;");
		lua->require("Utilities");
		delete_lua = true;
	}

	assert(lua->require("UnitTestingFramework"));
	if (!lua->require(module))
	{
		size_t origsize = strlen(module) + 1;
		size_t convertedChars = 0;
		wchar_t* wmodule = new wchar_t[origsize * 10];
		mbstowcs_s(&convertedChars, wmodule, origsize, module, _TRUNCATE);
		// CFIX_LOG(L"\nLua Unit Test Report: %s", wmodule);
		// CFIX_LOG(L"Test not found or written incorrectly: %s", wmodule);
		return;
	}
	lua_State* L = lua->getState();
	//s: ?
	lua_getglobal(L, "UnitTestingFramework");
	//s: UnitTestingFramework
	lua_getfield(L, -1, "testAll");
	//s: testAll
	lua_call(L, 0, 1);
	//s: bool
	lua_pop(L, 1);
	//s:
	lua_getglobal(L, "lastUnitTestNumFailures");
	//s: lastUnitTestNumFailures
	sint result = to<sint>(L, -1);
	lua_pop(L, 1);
	//s:
	lua_getglobal(L,  "lastUnitTestReport");
	//s: lastUnitTestReport
	const schar* report = to<const schar*>(L, -1);
	lua_pop(L, 1);
	//s:
	// Convert to a wchar_t*
	size_t origsize = strlen(report) + 1;
	size_t convertedChars = 0;
	wchar_t* wreport = new wchar_t[origsize * 10];
	mbstowcs_s(&convertedChars, wreport, origsize, report, _TRUNCATE);
	// CFIX_LOG(L"\nLua Unit Test Report: %s", wreport);

	assert(!result);

	delete[] wreport;
	if (delete_lua)
		delete lua;
}








void unitTestLua(void)
{
	embeddedLua::Lua lua;
	lua.setPackagePath(LUA_PACKAGE_PATH_RUN_FROM_SOLUTION_DIR);
	registerGlobalLibrary(lua.getState());
	lua.require("Utilities");
	lua.require("ObjectOrientedParadigm");
	lua.require("User");

	REGISTER_LUA_LIBRARY((&lua), TC);
	REGISTER_LUA_LIBRARY((&lua), TCChild);
	REGISTER_LUA_LIBRARY((&lua), TCGrandChild);
	REGISTER_LUA_LIBRARY((&lua), ProxyTC);
	REGISTER_LUA_LIBRARY((&lua), ProxyTCChild);
	REGISTER_LUA_LIBRARY((&lua), ProxyTCGrandChild);
	REGISTER_LUA_LIBRARY((&lua), TCLE);
	REGISTER_LUA_LIBRARY((&lua), TCLEChild);
	REGISTER_LUA_LIBRARY((&lua), TCLEGrandChild);
	REGISTER_LUA_LIBRARY((&lua), ProxyTCLE);
	REGISTER_LUA_LIBRARY((&lua), ProxyTCLEChild);
	REGISTER_LUA_LIBRARY((&lua), ProxyTCLEGrandChild);

	executeLuaUnitTest("UTPublicMembers", &lua);

	REGISTER_LUA_ENUM((&lua), BoolEnum)
	REGISTER_LUA_ENUM((&lua), eDirections)
	REGISTER_LUA_ENUM((&lua), eNumbers)
	REGISTER_LUA_ENUM((&lua), ReadOnly)

	REGISTER_LUA_LIBRARY((&lua), Vector2)
	REGISTER_LUA_LIBRARY((&lua), Vector3)
/*
	REGISTER_LUA_LIBRARY((&lua), xronos)
	REGISTER_LUA_LIBRARY((&lua), ClockInterface)
	REGISTER_LUA_LIBRARY((&lua), Clock)
	REGISTER_LUA_LIBRARY((&lua), ClockRelative)
	REGISTER_LUA_LIBRARY((&lua), ClockFrame)
	REGISTER_LUA_LIBRARY((&lua), Timer) 
	REGISTER_LUA_LIBRARY((&lua), Stopwatch) 

	REGISTER_LUA_LIBRARY((&lua), AllPublic)
	REGISTER_LUA_LIBRARY((&lua), AllPublicChild)
	REGISTER_LUA_LIBRARY((&lua), AllPublicGrandChild)
	REGISTER_LUA_LIBRARY((&lua), AllPublicLE)
	REGISTER_LUA_LIBRARY((&lua), AllPublicChildLE)
	REGISTER_LUA_LIBRARY((&lua), AllPublicGrandChildLE)
*/
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

	lua.runConsole();
}

#else
void unitTestLua(void)
{
	/* empty */
}

#endif//EXTENDED_BY_LUA

void sandbox::verifyUnitTests()
{
	unitTestLua();
};
