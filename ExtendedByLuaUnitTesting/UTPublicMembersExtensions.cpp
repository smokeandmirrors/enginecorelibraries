#include "Build.h"

#if WITH_UNIT_TESTING
#if EXTENDED_BY_LUA

#include <cfixcc.h>
#include "UTTools.h"
#include "LuaExtensionInclusions.h"

using namespace lua_extension;

class TC
{
public:
	TC(void) : one(1), two(true), three(3.0f) {}
	virtual ~TC(void) {}
	sint method(void) const { return 17; }
	sint one;
	bool two;
	sreal three;
};
DECLARE_LUA_CLASS(TC);
DEFINE_LUA_FUNC__index_PUBLIC_MEMBERS(TC, TC)
	__index_MEMBER(one)
	__index_MEMBER(two)
	__index_MEMBER(three)
END_LUA_FUNC__index_PUBLIC_MEMBERS(TC, TC)
DEFINE_LUA_FUNC__newindex_PUBLIC_MEMBERS(TC, TC)
	__newindex_MEMBER(one, sint)
	__newindex_MEMBER(two, bool)
	__newindex_MEMBER(three, sreal)
END_LUA_FUNC__newindex_PUBLIC_MEMBERS(TC, TC)
DEFINE_LUA_CLASS_PUBLIC_MEMBERS(CLASS, TC, TC)
	LUA_ENTRY_NAMED("method", (const_Return1Param0<TC, sint, &TC::method>))
END_LUA_CLASS(TC, TC)

class TCChild : public TC
{
public:
	TCChild() : four(NULL), five(5) {}
	sint childMethod(void) const { return 1717; }
	TC* four;
	sint five;
};
DECLARE_LUA_CLASS(TCChild);
DEFINE_LUA_FUNC__index_PUBLIC_MEMBERS(TCChild, TC)
	__index_MEMBER(four)
	__index_MEMBER(five)
END_LUA_FUNC__index_PUBLIC_MEMBERS(TCChild, TC)
DEFINE_LUA_FUNC__newindex_PUBLIC_MEMBERS(TCChild, TC)
	__newindex_MEMBER(four, TC*)
	__newindex_MEMBER(five, sint)
END_LUA_FUNC__newindex_PUBLIC_MEMBERS(TCChild, TC)
DEFINE_LUA_CLASS_PUBLIC_MEMBERS(CLASS, TCChild, TC)
	LUA_ENTRY_NAMED("childMethod", (const_Return1Param0<TCChild, sint, &TCChild::childMethod>))
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
DEFINE_LUA_FUNC__index_PUBLIC_MEMBERS(TCGrandChild, TCChild)
	__index_MEMBER(six)
	__index_MEMBER(seven)
END_LUA_FUNC__index_PUBLIC_MEMBERS(TCGrandChild, TCChild)
DEFINE_LUA_FUNC__newindex_PUBLIC_MEMBERS(TCGrandChild, TCChild)
	__newindex_MEMBER(six, TCChild*)
	__newindex_MEMBER(seven, uint)
END_LUA_FUNC__newindex_PUBLIC_MEMBERS(TCGrandChild, TCChild)
DEFINE_LUA_CLASS_PUBLIC_MEMBERS(CLASS, TCGrandChild, TCChild)
	LUA_ENTRY_NAMED("grandChildMethod", (const_Return1Param0<TCGrandChild, sint, &TCGrandChild::grandChildMethod>))
END_LUA_CLASS(TCGrandChild, TCChild)

class ProxyTC
{
public:
	ProxyTC(void) : one(1), two(true), three(3.0f) {}
	virtual ~ProxyTC(void) {}
	sint method(void) const { return 17; }
	sint one;
	bool two;
	sreal three;
};
DECLARE_LUA_CLASS(ProxyTC);
DEFINE_LUA_FUNC__index_PUBLIC_MEMBERS_PROXY(ProxyTC, ProxyTC)
	__index_PROXY_MEMBER(one)
	__index_PROXY_MEMBER(two)
	__index_PROXY_MEMBER(three)
END_LUA_FUNC__index_PUBLIC_MEMBERS_PROXY(ProxyTC, ProxyTC)
DEFINE_LUA_FUNC__newindex_PUBLIC_MEMBERS_PROXY(ProxyTC, ProxyTC)
	__newindex_PROXY_MEMBER(one, sint)
	__newindex_PROXY_MEMBER(two, bool)
	__newindex_PROXY_MEMBER(three, sreal)
END_LUA_FUNC__newindex_PUBLIC_MEMBERS_PROXY(ProxyTC, ProxyTC)
DEFINE_LUA_CLASS_BY_PROXY_PUBLIC_MEMBERS(CLASS, ProxyTC, ProxyTC)
	LUA_ENTRY_NAMED("method", (const_Return1Param0<ProxyTC, sint, &ProxyTC::method>))
	LUA_ENTRY__indexSupport(ProxyTC)
	LUA_ENTRY__newindexSupport(ProxyTC)
END_LUA_CLASS(ProxyTC, ProxyTC)

class ProxyTCChild : public ProxyTC
{
public:
	ProxyTCChild() : four(NULL), five(5) {}
	sint childMethod(void) const { return 1717; }
	ProxyTC* four;
	sint five;
};
DECLARE_LUA_CLASS(ProxyTCChild);
DEFINE_LUA_FUNC__index_PUBLIC_MEMBERS_PROXY(ProxyTCChild, ProxyTC)
__index_PROXY_MEMBER(four)
__index_PROXY_MEMBER(five)
END_LUA_FUNC__index_PUBLIC_MEMBERS_PROXY(ProxyTCChild, ProxyTC)
DEFINE_LUA_FUNC__newindex_PUBLIC_MEMBERS_PROXY(ProxyTCChild, ProxyTC)
__newindex_PROXY_MEMBER(four, ProxyTC*)
__newindex_PROXY_MEMBER(five, sint)
END_LUA_FUNC__newindex_PUBLIC_MEMBERS_PROXY(ProxyTCChild, ProxyTC)
DEFINE_LUA_CLASS_BY_PROXY_PUBLIC_MEMBERS(CLASS, ProxyTCChild, ProxyTC)
LUA_ENTRY_NAMED("childMethod", (const_Return1Param0<ProxyTCChild, sint, &ProxyTCChild::childMethod>))
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
DEFINE_LUA_FUNC__index_PUBLIC_MEMBERS_PROXY(ProxyTCGrandChild, ProxyTCChild)
__index_PROXY_MEMBER(six)
__index_PROXY_MEMBER(seven)
END_LUA_FUNC__index_PUBLIC_MEMBERS_PROXY(ProxyTCGrandChild, ProxyTCChild)
DEFINE_LUA_FUNC__newindex_PUBLIC_MEMBERS_PROXY(ProxyTCGrandChild, ProxyTCChild)
__newindex_PROXY_MEMBER(six, ProxyTCChild*)
__newindex_PROXY_MEMBER(seven, uint)
END_LUA_FUNC__newindex_PUBLIC_MEMBERS_PROXY(ProxyTCGrandChild, ProxyTCChild)
DEFINE_LUA_CLASS_BY_PROXY_PUBLIC_MEMBERS(CLASS, ProxyTCGrandChild, ProxyTCChild)
LUA_ENTRY_NAMED("grandChildMethod", (const_Return1Param0<ProxyTCGrandChild, sint, &ProxyTCGrandChild::grandChildMethod>))
LUA_ENTRY__indexSupport(ProxyTCGrandChild)
LUA_ENTRY__newindexSupport(ProxyTCGrandChild)
END_LUA_CLASS(ProxyTCGrandChild, ProxyTCChild)


class TCLE : public LuaExtendable
{
public:
	TCLE(void) : one(1), two(true), three(3.0f) {}
	virtual ~TCLE(void) {}
	sint method(void) const { return 17; }
	sint one;
	bool two;
	sreal three;

	DEFINE_LUAEXTENDABLE_USERDATA_DEFAULT_FUNCTIONS(TCLE)
};
DECLARE_LUA_CLASS(TCLE);
DEFINE_LUA_FUNC__index_PUBLIC_MEMBERS(TCLE, TCLE)
__index_MEMBER(one)
__index_MEMBER(two)
__index_MEMBER(three)
END_LUA_FUNC__index_PUBLIC_MEMBERS(TCLE, TCLE)
DEFINE_LUA_FUNC__newindex_PUBLIC_MEMBERS(TCLE, TCLE)
__newindex_MEMBER(one, sint)
__newindex_MEMBER(two, bool)
__newindex_MEMBER(three, sreal)
END_LUA_FUNC__newindex_PUBLIC_MEMBERS(TCLE, TCLE)
DEFINE_LUA_CLASS_PUBLIC_MEMBERS(EXTENDABLE, TCLE, TCLE)
LUA_ENTRY_NAMED("method", (const_Return1Param0<TCLE, sint, &TCLE::method>))
END_LUA_CLASS(TCLE, TCLE)


class TCLEChild : public TCLE
{
public:
	TCLEChild() : four(NULL), five(5) {}
	sint childMethod(void) const { return 1717; }
	TCLE* four;
	sint five;

	DEFINE_DEFAULT_TOSTRING(TCLEChild)
	DEFINE_DEFAULT_GETCLASSNAME(TCLEChild)
};
DECLARE_LUA_CLASS(TCLEChild);
DEFINE_LUA_FUNC__index_PUBLIC_MEMBERS(TCLEChild, TCLE)
__index_MEMBER(four)
__index_MEMBER(five)
END_LUA_FUNC__index_PUBLIC_MEMBERS(TCLEChild, TCLE)
DEFINE_LUA_FUNC__newindex_PUBLIC_MEMBERS(TCLEChild, TCLE)
__newindex_MEMBER(four, TCLE*)
__newindex_MEMBER(five, sint)
END_LUA_FUNC__newindex_PUBLIC_MEMBERS(TCLEChild, TCLE)
DEFINE_LUA_CLASS_PUBLIC_MEMBERS(EXTENDABLE, TCLEChild, TCLE)
LUA_ENTRY_NAMED("childMethod", (const_Return1Param0<TCLEChild, sint, &TCLEChild::childMethod>))
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
DECLARE_LUA_CLASS(TCLEGrandChild);
DEFINE_LUA_FUNC__index_PUBLIC_MEMBERS(TCLEGrandChild, TCLEChild)
__index_MEMBER(six)
__index_MEMBER(seven)
END_LUA_FUNC__index_PUBLIC_MEMBERS(TCLEGrandChild, TCLEChild)
DEFINE_LUA_FUNC__newindex_PUBLIC_MEMBERS(TCLEGrandChild, TCLEChild)
__newindex_MEMBER(six, TCLEChild*)
__newindex_MEMBER(seven, uint)
END_LUA_FUNC__newindex_PUBLIC_MEMBERS(TCLEGrandChild, TCLEChild)
DEFINE_LUA_CLASS_PUBLIC_MEMBERS(CLASS, TCLEGrandChild, TCLEChild)
LUA_ENTRY_NAMED("grandChildMethod", (const_Return1Param0<TCLEGrandChild, sint, &TCLEGrandChild::grandChildMethod>))
END_LUA_CLASS(TCLEGrandChild, TCLEChild)


class ProxyTCLE : public LuaExtendable
{
public:
	ProxyTCLE(void) : one(1), two(true), three(3.0f) {}
	virtual ~ProxyTCLE(void) {}
	sint method(void) const { return 17; }
	sint one;
	bool two;
	sreal three;

	DEFINE_LUAEXTENDABLE_PROXY_DEFAULT_FUNCTIONS(ProxyTCLE)
};
DECLARE_LUA_LUAEXTENDABLE(ProxyTCLE)
DEFINE_LUA_FUNC__index_PUBLIC_MEMBERS_PROXY(ProxyTCLE, ProxyTCLE)
__index_PROXY_MEMBER(one)
__index_PROXY_MEMBER(two)
__index_PROXY_MEMBER(three)
END_LUA_FUNC__index_PUBLIC_MEMBERS_PROXY(ProxyTCLE, ProxyTCLE)
DEFINE_LUA_FUNC__newindex_PUBLIC_MEMBERS_PROXY(ProxyTCLE, ProxyTCLE)
__newindex_PROXY_MEMBER(one, sint)
__newindex_PROXY_MEMBER(two, bool)
__newindex_PROXY_MEMBER(three, sreal)
END_LUA_FUNC__newindex_PUBLIC_MEMBERS_PROXY(ProxyTCLE, ProxyTCLE)
DEFINE_LUA_CLASS_BY_PROXY_PUBLIC_MEMBERS(EXTENDABLE, ProxyTCLE, ProxyTCLE)
LUA_ENTRY_NAMED("method", (const_Return1Param0<ProxyTCLE, sint, &ProxyTCLE::method>))
END_LUA_CLASS(ProxyTCLE, ProxyTCLE)

class ProxyTCLEChild : public ProxyTCLE
{
public:
	ProxyTCLEChild() : four(NULL), five(5) {}
	sint childMethod(void) const { return 1717; }
	ProxyTCLE* four;
	sint five;

	DEFINE_DEFAULT_TOSTRING(ProxyTCLEChild)
	DEFINE_DEFAULT_GETCLASSNAME(ProxyTCLEChild)
};
DECLARE_LUA_LUAEXTENDABLE(ProxyTCLEChild)
DEFINE_LUA_FUNC__index_PUBLIC_MEMBERS_PROXY(ProxyTCLEChild, ProxyTCLE)
__index_PROXY_MEMBER(four)
__index_PROXY_MEMBER(five)
END_LUA_FUNC__index_PUBLIC_MEMBERS_PROXY(ProxyTCLEChild, ProxyTCLE)
DEFINE_LUA_FUNC__newindex_PUBLIC_MEMBERS_PROXY(ProxyTCLEChild, ProxyTCLE)
__newindex_PROXY_MEMBER(four, ProxyTCLE*)
__newindex_PROXY_MEMBER(five, sint)
END_LUA_FUNC__newindex_PUBLIC_MEMBERS_PROXY(ProxyTCLEChild, ProxyTCLE)
DEFINE_LUA_CLASS_BY_PROXY_PUBLIC_MEMBERS(EXTENDABLE, ProxyTCLEChild, ProxyTCLE)
LUA_ENTRY_NAMED("childMethod", (const_Return1Param0<ProxyTCLEChild, sint, &ProxyTCLEChild::childMethod>))
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
DECLARE_LUA_CLASS(ProxyTCLEGrandChild);
DEFINE_LUA_FUNC__index_PUBLIC_MEMBERS_PROXY(ProxyTCLEGrandChild, ProxyTCLEChild)
__index_PROXY_MEMBER(six)
__index_PROXY_MEMBER(seven)
END_LUA_FUNC__index_PUBLIC_MEMBERS_PROXY(ProxyTCLEGrandChild, ProxyTCLEChild)
DEFINE_LUA_FUNC__newindex_PUBLIC_MEMBERS_PROXY(ProxyTCLEGrandChild, ProxyTCLEChild)
__newindex_PROXY_MEMBER(six, ProxyTCLEChild*)
__newindex_PROXY_MEMBER(seven, uint)
END_LUA_FUNC__newindex_PUBLIC_MEMBERS_PROXY(ProxyTCLEGrandChild, ProxyTCLEChild)
DEFINE_LUA_CLASS_BY_PROXY_PUBLIC_MEMBERS(EXTENDABLE, ProxyTCLEGrandChild, ProxyTCLEChild)
LUA_ENTRY_NAMED("grandChildMethod", (const_Return1Param0<ProxyTCLEGrandChild, sint, &ProxyTCLEGrandChild::grandChildMethod>))
END_LUA_CLASS(ProxyTCLEGrandChild, ProxyTCLEChild)


class UTPublicMembersExtensions : public cfixcc::TestFixture
{
private:

public:
	void LuaPublicMemberTesting()
	{
		DECLARE_UNIT_TESTING_LUA_OBJECT
		unit_testing_tools::executeLuaUnitTest("UTPublicMembers", &lua);
	}
};

CFIXCC_BEGIN_CLASS(UTPublicMembersExtensions)
	CFIXCC_METHOD(LuaPublicMemberTesting)
CFIXCC_END_CLASS()

#endif//EXTENDED_BY_LUA
#endif//WITH_UNIT_TESTING