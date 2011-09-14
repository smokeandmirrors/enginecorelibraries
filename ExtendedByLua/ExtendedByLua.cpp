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
DECLARE_LUA_LIBRARY(AllPublicLE)
namespace lua_extension 
{ 
	template<> inline AllPublicLE* to< AllPublicLE* >(lua_State* L, sint index) 
	{ 
		LuaExtendable* le = to<LuaExtendable*>(L, index); 
		AllPublicLE* object = dynamic_cast< AllPublicLE* >(le); 
		if (object == static_cast< AllPublicLE* >(le)) 
			return object; 
		luaL_error(L, "argument type error! argument at index %d: expected: %s actual: %s", index, "AllPublicLE", typeid(object).name()); 
		return NULL; 
	} 
	template<> inline const AllPublicLE* to< const AllPublicLE* >(lua_State* L, sint index) 
	{ 
		return to< AllPublicLE* >(L, index); 
	} 
	template<> inline AllPublicLE& to< AllPublicLE& >(lua_State* L, sint index) 
	{ 
		AllPublicLE* object = to< AllPublicLE* >(L, index); 
		return *object; 
	} 
	template<> inline const AllPublicLE& to< const AllPublicLE& >(lua_State* L, sint index) 
	{ 
		AllPublicLE* object = to< AllPublicLE* >(L, index); 
		return *object; 
	} 
}
// DEFINE_LUA_FUNC__index_PUBLIC_MEMBERS(AllPublicLE, AllPublicLE)
	inline bool AllPublicLE__indexSupport(const AllPublicLE& t, const char* k, lua_State* L, const char* className, const char* superClassName); 
	LUA_FUNC(AllPublicLE__index) 
	{ 
		const schar* k = to<const schar*>(L, -1); 
		const AllPublicLE& t = to<const AllPublicLE&>(L, -2); 
		if (AllPublicLE__indexSupport(t, k, L, "AllPublicLE", "AllPublicLE")) 
		{ 
			return 1; 
		} 
		else 
		{ 
			lua_getglobal(L, "getClass");	/*s: getClass */ 
			push(L, "AllPublicLE");			/*s: getClass, "CLASS" */ 
			lua_call(L, 1, 1);				/*s: CLASS */ 
			lua_getfield(L, -1, k);			/*s: CLASS[k] */ 
			return 1; 
		} 
	} 

	inline bool AllPublicLE__indexSupport(const AllPublicLE& t, const char* k, lua_State* L, const char* className, const char* superClassName) 
	{
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

DEFINE_LUA_FUNC__index_PUBLIC_MEMBERS(AllPublic, AllPublic)
	__index_FUNCTION_ENTRY(one)
	__index_FUNCTION_ENTRY(two)
	__index_FUNCTION_ENTRY(three)
END_LUA_FUNC__index_PUBLIC_MEMBERS(AllPublic, AllPublic)

DEFINE_LUA_FUNC__newindex_PUBLIC_MEMBERS(AllPublic, AllPublic)
	__newindex_FUNCTION_ENTRY(one, sint)
	__newindex_FUNCTION_ENTRY(two, bool)
	__newindex_FUNCTION_ENTRY(three, sreal)
END_LUA_FUNC__newindex_PUBLIC_MEMBERS(AllPublic, AllPublic)

DEFINE_LUA_CLASS_PUBLIC_MEMBERS(CLASS, AllPublic, AllPublic)
	LUA_ENTRY_NAMED("method", (const_Return1Param0<AllPublic, sint, &AllPublic::method>))
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

