#include "Platform.h"

#if WITH_UNIT_TESTING
#if EXTENDED_BY_LUA

#include <cfixcc.h>
#include "UTTools.h"
#include "LuaExtensionInclusions.h"

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
// END_LUA_PUBLIC_MEMBER_INDEXING(TC, TC)
} /* static void populate##CLASS##Supports(containers::Set< ClassMemberIndexer< CLASS > >& supports) */ 
	
class TCLuaIndexer 
{ 
public: 
	static const containers::Set< ClassMemberIndexer< TC > >& get(void) 
	{ 
		static TCLuaIndexer singleton; 
		return singleton.supports; 
	} 
private: 
	containers::Set< ClassMemberIndexer< TC > > supports; 
	TCLuaIndexer() 
	{ 
		populateTCSupports(supports); 
	} 
}; 
inline bool TCLuaIndex(const TC & t, const char* k, lua_State* L, const char* className) 
{ 
	const containers::Set< ClassMemberIndexer< TC > >& supports( TCLuaIndexer::get()); 
	if (supports.has(k)) 
	{ 
		const ClassMemberIndexer< TC >& support = supports.get(k); 
		(*support.pushFunction)(L, t, support.offset); 
		return true; 
	} 
	else if (String::compare(className, "TC" )) 
	{	/* here would be a recursive call that would be never called */ 
		return TCLuaIndex(t, k, L, "TC" );  
	} 
	else 
	{ 	/*  must tell the main calling function if something was pushed */ 
		return false; 
	} 
} 
inline bool TCLuaNewIndex(TC& t, const char* k, lua_State* L, const char* className) 
{ 
	const containers::Set< ClassMemberIndexer< TC > >& supports( TCLuaIndexer::get()); 
	if (supports.has(k)) 
	{ 
		const ClassMemberIndexer< TC >& support = supports.get(k); 
		(*support.assignFunction)(L, t, support.offset); 
		return true; 
	} 
	else if (String::compare(className, "TC" )) 
	{	/* here would be a recursive call that would be never called */  
		return TCLuaNewIndex(t, k, L, "TC" ); 
	} 
	else 
	{ 
		return false; /* must tell the main calling function if something was pushed */ 
	} 
} 

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


class UTPublicMembersExtensions : public cfixcc::TestFixture
{
public:
	static void SetUp()
	{
		designPatterns::createSingletons();
	}

	static void TearDown()
	{    
		designPatterns::destroySingletons();
	}

	void LuaPublicMemberTesting()
	{
		DECLARE_UNIT_TESTING_LUA_OBJECT
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
		unit_testing_tools::executeLuaUnitTest("UTPublicMembers", &lua);
	}
};

CFIXCC_BEGIN_CLASS(UTPublicMembersExtensions)
	CFIXCC_METHOD(LuaPublicMemberTesting)
CFIXCC_END_CLASS()

#endif//EXTENDED_BY_LUA
#endif//WITH_UNIT_TESTING