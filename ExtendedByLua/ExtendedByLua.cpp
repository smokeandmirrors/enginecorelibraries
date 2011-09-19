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
	LUA_ENTRY_NAMED("method", (const_Return1Param0<AllPublicLE, sint, &AllPublicLE::method>))
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
	LUA_ENTRY_NAMED("childMethod", (const_Return1Param0<AllPublicChildLE, sint, &AllPublicChildLE::childMethod>))
END_LUA_CLASS(AllPublicChildLE, AllPublicLE)

//////////////////////////////////////////////////////////////////////////
DECLARE_LUA_CLASS(AllPublicGrandChildLE);

DEFINE_LUA_FUNC__index_PUBLIC_MEMBERS_PROXY(AllPublicGrandChildLE, AllPublicChildLE)
	__index_PROXY_MEMBER(six)
	__index_PROXY_MEMBER(seven)
END_LUA_FUNC__index_PUBLIC_MEMBERS_PROXY(AllPublicGrandChildLE, AllPublicChildLE)

DEFINE_LUA_FUNC__newindex_PUBLIC_MEMBERS_PROXY(AllPublicGrandChildLE, AllPublicChildLE)
	__newindex_PROXY_MEMBER(six, AllPublicChildLE*)
	__newindex_PROXY_MEMBER(seven, uint)
END_LUA_FUNC__newindex_PUBLIC_MEMBERS_PROXY(AllPublicGrandChildLE, AllPublicChildLE)

DEFINE_LUA_CLASS_BY_PROXY_PUBLIC_MEMBERS(EXTENDABLE, AllPublicGrandChildLE, AllPublicChildLE)
	LUA_ENTRY_NAMED("grandChildMethod", (const_Return1Param0<AllPublicGrandChildLE, sint, &AllPublicGrandChildLE::grandChildMethod>))
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
//  	LUA_ENTRY_NAMED("method", (const_Return1Param0<AllPublic, sint, &AllPublic::method>))
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
//  	LUA_ENTRY_NAMED("childMethod", (const_Return1Param0<AllPublicChild, sint, &AllPublicChild::childMethod>))
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
//  	LUA_ENTRY_NAMED("grandChildMethod", (const_Return1Param0<AllPublicGrandChild, sint, &AllPublicGrandChild::grandChildMethod>))
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

DEFINE_LUA_CLASS_PUBLIC_MEMBERS(CLASS, AllPublic, AllPublic)
	LUA_ENTRY_NAMED("method", (const_Return1Param0<AllPublic, sint, &AllPublic::method>))
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
	LUA_ENTRY_NAMED("childMethod", (const_Return1Param0<AllPublicChild, sint, &AllPublicChild::childMethod>))
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
	LUA_ENTRY_NAMED("grandChildMethod", (const_Return1Param0<AllPublicGrandChild, sint, &AllPublicGrandChild::grandChildMethod>))
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

template<typename ARG_1, typename ARG_2, typename RET_1, typename RET_2>
RET_1 nativeLuaCall(lua_State* L, const char* function, RET_2& ret_2, ARG_1 arg_1, ARG_2 arg_2, const char* module="_G")
{
	lua_getglobal(L, module);		//s: module
	lua_getfield(L, -1, function);	//s: module function
	assert(lua_isfunction(L, -1));	
	push(L, arg_1);					//s: module function arg_1
	push(L, arg_2);					//s: module function arg_1 arg_2
	lua_call(L, 2, 2);				//s: module ret_1, ret_2
	ret_2 = to<RET_2>(L, -1);
	RET_1 ret_1 = to<RET_1>(L, -2);
	lua_pop(L, 3);					//s: 
	return ret_1;
}

template<typename RET_1, typename ARG_1, typename ARG_2>
RET_1 nativeLuaCall(lua_State* L, const char* function, ARG_1 arg_1, ARG_2 arg_2, const char* module="_G")
{
	lua_getglobal(L, module);		//s: module
	lua_getfield(L, -1, function);	//s: module function
	assert(lua_isfunction(L, -1));	
	push(L, arg_1);					//s: module function arg_1
	push(L, arg_2);					//s: module function arg_1 arg_2
	lua_call(L, 2, 1);				//s: module ret_1
	RET_1 ret_1 = to<RET_1>(L, -1);
	lua_pop(L, 3);					//s: 
	return ret_1;
}

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
		REGISTER_LUA_LIBRARY((&lua), AllPublicGrandChild);
		REGISTER_LUA_LIBRARY((&lua), AllPublicLE);
		REGISTER_LUA_LIBRARY((&lua), AllPublicChildLE);
		REGISTER_LUA_LIBRARY((&lua), AllPublicGrandChildLE);
		REGISTER_LUA_LIBRARY((&lua), Vector2);
		REGISTER_LUA_LIBRARY((&lua), Vector3);
		
#if UNIT_TEST_VERIFICATION
		REGISTER_LUA_LIBRARY((&lua), Grandparent2);
		REGISTER_LUA_LIBRARY((&lua), Parent2);
		REGISTER_LUA_LIBRARY((&lua), Child2);
#endif // UNIT_TEST_VERIFICATION

		// get the user file for easier rapid iteration
		lua.require("User");
		sreal return2(4);
		bool return1(false);
		return2 = nativeLuaCall<sreal, bool, sreal, bool>(lua.getState(), "callable", return1, return2, return1);
		sreal ret1 = nativeLuaCall<sreal, sreal, sreal>(lua.getState(), "callable2", 3.0f, 4.0f);
		lua.runConsole();
	}
#endif//EXTENDED_BY_LUA
	
#if SANDBOX
	sandbox::play();// just plays with C/C++ compile/runtime functionality
#endif//SANDBOX	
	return 0;
}

