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
using namespace lua_extension;
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

	sint method(void) const { return 17; }
};

class AllPublicChild : public AllPublic
{
public:
	AllPublicChild() : four(NULL), five(5) {}
	AllPublic* four;
	sint five;

	sint childMethod(void) const { return 1717; }
};


//////////////////////////////////////////////////////////////////////////
class AllPublicLE 
	: public LuaExtendable
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
DECLARE_LUA_LUAEXTENDABLE(AllPublicLE)

DEFINE_LUA_FUNC__index_PUBLIC_MEMBERS(AllPublicLE, AllPublicLE)
		__index_FUNCTION_ENTRY(one)
		__index_FUNCTION_ENTRY(two)
		__index_FUNCTION_ENTRY(three)
END_LUA_FUNC__index_PUBLIC_MEMBERS(AllPublicLE, AllPublicLE)

DEFINE_LUA_FUNC__newindex_PUBLIC_MEMBERS(AllPublicLE, AllPublicLE)
	__newindex_FUNCTION_ENTRY(one, sint)
	__newindex_FUNCTION_ENTRY(two, bool)
	__newindex_FUNCTION_ENTRY(three, sreal)
END_LUA_FUNC__newindex_PUBLIC_MEMBERS(AllPublicLE, AllPublicLE)

DEFINE_LUA_CLASS_BY_PROXY(EXTENDABLE, AllPublicLE, AllPublicLE)
	LUA_ENTRY__index(AllPublicLE)
	LUA_ENTRY__newindex(AllPublicLE)
END_LUA_CLASS(AllPublicLE, AllPublicLE)


//////////////////////////////////////////////////////////////////////////
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
DECLARE_LUA_LUAEXTENDABLE(AllPublicChildLE)

DEFINE_LUA_FUNC__index_PUBLIC_MEMBERS(AllPublicChildLE, AllPublicLE)
	__index_FUNCTION_ENTRY(four)
	__index_FUNCTION_ENTRY(five)
END_LUA_FUNC__index_PUBLIC_MEMBERS(AllPublicChildLE, AllPublicLE)

DEFINE_LUA_FUNC__newindex_PUBLIC_MEMBERS(AllPublicChildLE, AllPublicLE)
	__newindex_FUNCTION_ENTRY(four, AllPublicLE*)
	__newindex_FUNCTION_ENTRY(five, sint)
END_LUA_FUNC__newindex_PUBLIC_MEMBERS(AllPublicChildLE, AllPublicLE)

DEFINE_LUA_CLASS_BY_PROXY(EXTENDABLE, AllPublicChildLE, AllPublicLE)
	LUA_ENTRY__index(AllPublicChildLE)
	LUA_ENTRY__newindex(AllPublicChildLE)
END_LUA_CLASS(AllPublicChildLE, AllPublicLE)


//////////////////////////////////////////////////////////////////////////
DECLARE_LUA_CLASS(AllPublic);
// 
// DEFINE_LUA_FUNC__index_PUBLIC_MEMBERS(AllPublic, AllPublic)
// 	__index_FUNCTION_ENTRY(one)
// 	__index_FUNCTION_ENTRY(two)
// 	__index_FUNCTION_ENTRY(three)
// END_LUA_FUNC__index_PUBLIC_MEMBERS(AllPublic, AllPublic)

inline sint AllPublic__indexSupport(const AllPublic& t, const char* k, lua_State* L, const char* className, const char* superClassName)
{
	if (!strcmp(k, "one" )) { pushTrue(L); push(L, t.one); return 2; }	
	if (!strcmp(k, "two" )) { pushTrue(L); push(L, t.two); return 2; }	
	if (!strcmp(k, "three" )) { pushTrue(L); push(L, t.three); return 2; }	

	if (strcmp(className, superClassName)) 
	{	/* here would be a recursive call that would be never called */ 
		return AllPublic__indexSupport(t, k, L, "AllPublic", "AllPublic"); 
	} 
	else 
	{ 
		pushFalse(L);
		pushNil(L);
		return 2;
	} 
}
LUA_FUNC(AllPublic__indexSupportExposed)
{
	return AllPublic__indexSupport(to<const AllPublic&>(L, -2), to<const char*>(L, -1), L, "AllPublic", "AllPublic");
}

DEFINE_LUA_FUNC__newindex_PUBLIC_MEMBERS(AllPublic, AllPublic)
	__newindex_FUNCTION_ENTRY(one, sint)
	__newindex_FUNCTION_ENTRY(two, bool)
	__newindex_FUNCTION_ENTRY(three, sreal)
END_LUA_FUNC__newindex_PUBLIC_MEMBERS(AllPublic, AllPublic)



DEFINE_LUA_CLASS_BY_PROXY_PUBLIC_MEMBERS(CLASS, AllPublic, AllPublic)
	LUA_ENTRY_NAMED("method", (const_Return1Param0<AllPublic, sint, &AllPublic::method>))
	LUA_ENTRY_NAMED("__indexSupport", AllPublic__indexSupportExposed)
END_LUA_CLASS(AllPublic, AllPublic)


//////////////////////////////////////////////////////////////////////////
DECLARE_LUA_CLASS(AllPublicChild);

DEFINE_LUA_FUNC__index_PUBLIC_MEMBERS(AllPublicChild, AllPublic)
	__index_FUNCTION_ENTRY(four)
	__index_FUNCTION_ENTRY(five)
END_LUA_FUNC__index_PUBLIC_MEMBERS(AllPublicChild, AllPublic)

DEFINE_LUA_FUNC__newindex_PUBLIC_MEMBERS(AllPublicChild, AllPublic)
	__newindex_FUNCTION_ENTRY(four, AllPublic*)
	__newindex_FUNCTION_ENTRY(five, sint)
END_LUA_FUNC__newindex_PUBLIC_MEMBERS(AllPublicChild, AllPublic)

DEFINE_LUA_CLASS_PUBLIC_MEMBERS(CLASS, AllPublicChild, AllPublic)
	LUA_ENTRY_NAMED("childMethod", (const_Return1Param0<AllPublicChild, sint, &AllPublicChild::childMethod>))
END_LUA_CLASS(AllPublicChild, AllPublic)

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

sint _tmain(sint /* argc */, _TCHAR* /* argv[] */)
{
	real_time::initialize();

#if EXTENDED_BY_LUA 
	{
		lua_extension::Lua lua;
		lua.setPackagePath(LUA_PACKAGE_PATH_RUN_FROM_SOLUTION_DIR);
		registerGlobalLibrary(lua.getState());
		lua.require("Utilities");
		lua.require("ObjectOrientedParadigm");
		REGISTER_LUA_ENUM((&lua), eDirections)
		REGISTER_LUA_ENUM((&lua), eNumbers)
		REGISTER_LUA_ENUM((&lua), ReadOnly)

		REGISTER_LUA_LIBRARY((&lua), AllPublic);
		REGISTER_LUA_LIBRARY((&lua), AllPublicChild);
		REGISTER_LUA_LIBRARY((&lua), AllPublicLE);
		REGISTER_LUA_LIBRARY((&lua), AllPublicChildLE);
		REGISTER_LUA_LIBRARY((&lua), Vector2);
		REGISTER_LUA_LIBRARY((&lua), Vector3);
		
#if UNIT_TEST_VERIFICATION
		REGISTER_LUA_LIBRARY((&lua), Grandparent2);
		REGISTER_LUA_LIBRARY((&lua), Parent2);
		REGISTER_LUA_LIBRARY((&lua), Child2);
#endif // UNIT_TEST_VERIFICATION

		// get the user file for easier rapid iteration
		lua.require("User");
		lua.runConsole();
	}
#endif//EXTENDED_BY_LUA
	
#if SANDBOX
	sandbox::play();// just plays with C/C++ compile/runtime functionality
#endif//SANDBOX	
	return 0;
}

