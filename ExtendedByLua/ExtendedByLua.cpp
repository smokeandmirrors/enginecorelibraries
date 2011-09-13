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
	sint 
		one;
	bool 
		two;
	sreal 
		three;

	sint method(void) const { return 17; }
};

class AllPublicChild
{
public:
	AllPublicChild() : four(NULL) {}
	AllPublic* four;
	sint five;
};

//////////////////////////////////////////////////////////////////////////
DECLARE_LUA_CLASS(AllPublic);

// DEFINE_LUA_FUNC__index_PUBLIC_MEMBERS(AllPublic)
LUA_FUNC(AllPublic__index) 
{ 
	const schar* k = to<const schar*>(L, -1); 
	const AllPublic& t = to<const AllPublic&>(L, -2); 
	if (!strcmp(k, "one" )) { pushTrue(L); push(L, t.one); return 2; }// __index_FUNCTION_ENTRY(one)
	if (!strcmp(k, "two" )) { pushTrue(L);  push(L, t.two); return 2; }// __index_FUNCTION_ENTRY(two)
	if (!strcmp(k, "three" )) { pushTrue(L);  push(L, t.three); return 2; } // __index_FUNCTION_ENTRY(three)
	pushFalse(L); return 1; 
} 
// END_LUA_FUNC__index_PUBLIC_MEMBERS(AllPublic)

DEFINE_LUA_FUNC__newindex_PUBLIC_MEMBERS(AllPublic)
	__newindex_FUNCTION_ENTRY(one, sint)
	__newindex_FUNCTION_ENTRY(two, bool)
	__newindex_FUNCTION_ENTRY(three, sreal)
END_LUA_FUNC__newindex_PUBLIC_MEMBERS(AllPublic)

DEFINE_LUA_CLASS_PUBLIC_MEMBERS(CLASS, AllPublic, AllPublic)
	LUA_NAMED_ENTRY("method", (const_Return1Param0<AllPublic, sint, &AllPublic::method>))
END_LUA_CLASS(AllPublic, AllPublic)

//////////////////////////////////////////////////////////////////////////
DECLARE_LUA_CLASS(AllPublicChild);
/*
DEFINE_LUA_FUNC__index_PUBLIC_MEMBERS(AllPublicChild)
	__index_FUNCTION_ENTRY(four)
	__index_FUNCTION_ENTRY(five)
END_LUA_FUNC__index_PUBLIC_MEMBERS(AllPublic)
*/
LUA_FUNC(AllPublicChild__index) 
{ 
	const schar* k = to<const schar*>(L, -1); 
	const AllPublicChild& t = to<const AllPublicChild&>(L, -2); 
	if (!strcmp(k, "four" )) { pushTrue(L); push(L, t.four); return 2; }// __index_FUNCTION_ENTRY(one)
	if (!strcmp(k, "five" )) { pushTrue(L);  push(L, t.five); return 2; }// __index_FUNCTION_ENTRY(two)
	pushFalse(L); return 1; 
} 

DEFINE_LUA_FUNC__newindex_PUBLIC_MEMBERS(AllPublicChild)
	__newindex_FUNCTION_ENTRY(four, AllPublic*)
	__newindex_FUNCTION_ENTRY(five, sint)
END_LUA_FUNC__newindex_PUBLIC_MEMBERS(AllPublicChild)

DEFINE_LUA_CLASS_PUBLIC_MEMBERS(CLASS, AllPublicChild, AllPublic)
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

DEFINE_LUA_ENUM(ReadOnly)
	LUA_ENUM(ZeroRO)
	LUA_ENUM(OneRO)
	LUA_ENUM(TwoRO)
END_LUA_ENUM(ReadOnly)

DEFINE_LUA_ENUM_BOUND(eDirections, Up, Right)
	LUA_ENUM(Down)
	LUA_ENUM(Left)
END_LUA_ENUM_BOUND(eDirections, Right)

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
		REGISTER_LUA_LIBRARY((&lua), Vector2);
		REGISTER_LUA_LIBRARY((&lua), Vector3);
		REGISTER_LUA_LIBRARY((&lua), AllPublic);
		REGISTER_LUA_LIBRARY((&lua), AllPublicChild);
		REGISTER_LUA_ENUM((&lua), eNumbers)
		REGISTER_LUA_ENUM((&lua), eDirections)
		REGISTER_LUA_ENUM((&lua), ReadOnly)

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

