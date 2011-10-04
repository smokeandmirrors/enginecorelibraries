#pragma once
#ifndef LUAEXTENSIBILITY_H
#define LUAEXTENSIBILITY_H
/** 
\file 
\brief Defines macros to help registration of functions, 
libraries, and classes with lua.
\author Smoke and Mirrors Development
\htmlonly
<A HREF="smokeandmirrorsdevelopment@gmail.com">
smokeandmirrorsdevelopment@gmail.com</A>
<BR>
&copy;2009-2011 Smoke and Mirrors Development
<BR>
\endhtmlonly
\date 2/23/2010

example:
\code
// for the .h file
DECLARE_LUA_LIBRARY(example)
// would generate: 
struct lua_State;
namespace lua_library_example
{
	sint luaopen_example(lua_State* L);
}

// for the .cpp file 
DEFINE_LUA_LIBRARY(example)
	LUA_ENTRY_NAMED("Method", method)
	...
END_LUA_LIBRARY(example)
// would generate:

namespace lua_library_example 
{
	static const luaL_reg example_library[] = {
		{"Method", method}, 
		...,
		{NULL, NULL}
	};

	sint luaopen_example(lua_State* L)
	{
		luaL_register(L, "example", example_library);
		return 1;
	}
}

// to use the library
REGISTER_LUA_LIBRARY(Lua, example);
// would generate:
Lua->openLibrary(lua_library_example::luaopen_example);
\endcode

\warning REGISTRATION MUST BE DONE IN DEPENDENCY ORDER.
\warning THIS FUNCTIONALITY IS NOT THREAD SAFE.

<DEVELOPMENT STATUS>
Current Draft		:	1.0
Current Phase		:   FIELD TESTING
Purpose				:	DEPLOYMENT
Unit Tested			:	YES
Used in development	:	YES
Used in experiments :	YES
Tested in the field	:	YES

\todo investigate how much library sharing can happen
with LuaExtendable, probably a lot less memory in Lua
can be taken up that way.  There is obviously less
code bloat.

\todo document these in terms of the methods required by 
the ObjectOrientedParadigm

\todo replace __index/__newindex functionality with string -> offset map
*/

#include <typeinfo>
#include "LuaBuild.h"
/**
\defgroup LuaExtension Lua Extension
macros, classes and functions to 
aid embedding %Lua in an executable, and exposing libraries and classes
for use in %Lua.
@{
*/

#if !GOLDMASTER
#define ARGUMENT_ERRORS 1
#endif//!GOLDMASTER

/**
\defgroup luaCodeWriting  Lua C API Code Writing Help
\ingroup LuaExtension
macros to assist (mostly compile-time) protocol for exposing libraries
to %Lua.  These macros will also help ease integration of future changes
to %Lua and the %Lua C API.
@{
*/

/** 
used for an entry in a "getter" function 
for public members that can be pushed directly into %Lua
 
\*/
#define __index_MEMBER(INDEX) \
	if (!strcmp(k, #INDEX )) { push(L, t.##INDEX##); return true; }	

/**
*/
#define __index_PROXY_MEMBER(INDEX) \
	if (!strcmp(k, #INDEX )) { pushTrue(L); push(L, t.##INDEX##); return 2; }

/**
used for an entry in a "setter" function 
for public members that can be set directly from %Lua
*/
#define __newindex_MEMBER(INDEX, TYPE) \
	if (!strcmp(k, #INDEX)) { t.##INDEX = to<##TYPE##>(L, -1); return true; }	

/**
*/
#define __newindex_PROXY_MEMBER(INDEX, TYPE) \
	if (!strcmp(k, #INDEX)) { t.##INDEX = to<##TYPE##>(L, -1); pushTrue(L); return 1; }

/**
used to end a function list of functions to expose to %Lua
*/
#define CLOSE_LUA_LIB(NAME) \
		LUA_FINAL_ENTRY \
	};	/* end function list */ 

/** 
*/
#define CLOSE_LUA_NS(NAME) \
	}; // end namespace lua_library_##name

/**
Declares a library around a POD class
\note compile-time directive
*/
#define DECLARE_LUA_CLASS(CLASS) \
	DECLARE_LUA_LIBRARY(CLASS) \
	DECLARE_LUA_PUSH_FUNCTION(CLASS) \
	DEFINE_TO_CLASS_FUNCTIONS(CLASS) 

/**
Declares a library around a POD class
\note compile-time directive
*/
#define DECLARE_LUA_CLASS_NS(NAMESPACE, CLASS) \
	DECLARE_LUA_LIBRARY(CLASS)	\
	DECLARE_LUA_PUSH_FUNCTION_NS(NAMESPACE, CLASS) \
	DEFINE_TO_CLASS_FUNCTIONS(NAMESPACE##::##CLASS)

/** 
Declares a %Lua library for shared inclusion.  If used for a class,
instances of the class can be created or controlled in %Lua.  Using this 
method, the programmer is responsible for the whole system of usage of the 
class in %Lua, including memory management.  This method does not interact 
with the module ObjectOrientedParadigm.
\note compile-time directive
\param name name of the library without string delimiters
*/
#define DECLARE_LUA_LIBRARY(name) \
	struct lua_State; \
	namespace lua_library_##name \
	{ \
		sint key(lua_State* L); \
	}; // end namespace lua_library_##name

/**
Declares a library around a class that implements
the LuaExtendable interface.
\note compile-time directive
*/
#define DECLARE_LUA_LUAEXTENDABLE(CLASS) \
	DECLARE_LUA_LIBRARY(CLASS) \
	DEFINE_TO_LUAEXTENDABLES(CLASS) 

/**
Declares a library around a class in a namespace that implements
the LuaExtendable interface.
\note compile-time directive
*/
#define DECLARE_LUA_LUAEXTENDABLE_NS(NAMESPACE, CLASS) \
	DECLARE_LUA_LIBRARY(CLASS)	\
	DEFINE_TO_LUAEXTENDABLES(NAMESPACE::CLASS)

/** 
*/
#define DECLARE_LUA_PUSH_FUNCTION(CLASS) \
	namespace embeddedLua \
	{ \
		sint push(lua_State* L, CLASS * value); \
		sint push(lua_State* L, const CLASS * value); \
		sint push(lua_State* L, CLASS & value); \
		sint push(lua_State* L, const CLASS & value); \
	} 

/** 
*/
#define DECLARE_LUA_PUSH_FUNCTION_NS(NAMESPACE, CLASS) \
	namespace embeddedLua \
	{ \
		sint push(lua_State* L, NAMESPACE##::##CLASS * value); \
		sint push(lua_State* L, const NAMESPACE##::##CLASS * value); \
		sint push(lua_State* L, NAMESPACE##::##CLASS & value); \
		sint push(lua_State* L, const NAMESPACE##::##CLASS & value); \
	} 

/** 
*/
#define DEFINE_DEFAULT_GETCLASSNAME(CLASS) \
	virtual const schar* getClassName(void) const \
	{ \
		return #CLASS; \
	}

/** 
*/
#define DEFINE_DEFAULT_TOSTRING(CLASS) \
	virtual const schar* toString(void) \
	{ \
		return "This is a " #CLASS; \
	}

#if DEBUG 
/**
*/
#define DEFINE_LUA_CLASS__newindex_ERROR(CLASS) \
	LUA_FUNC(__newindexError##CLASS) \
	{ \
		return luaL_error(L, "ERROR! Attempting to assign a value to a LuaExtendable %s that doesn't support new values.  " \
		"Use DEFINE_LUA_CLASS_BY_PROXY to expose this class to Lua if that is desired.", #CLASS); \
	}
#else 
/**
*/
#define DEFINE_LUA_CLASS__newindex_ERROR(CLASS) \
	LUA_FUNC(__newindexError##CLASS) \
	{ \
		(void*)L; \
		return 0; \
	}
#endif//DEBUG

/** 
*/
#define DEFINE_LUA_CLASS__tostring(CLASS) \
	LUA_FUNC(__tostring##CLASS##) \
	{ \
		lua_pushstring(L, "This is a " #CLASS); \
		return 1; \
	}	

/**
Define a %Lua library around a class, so that instances of the 
class can be created or controlled in %Lua. This also exposes simple 
userdata pointers with all associated C++ and Lua methods, but it doesn't 
create any ability to added new %Lua fields.  But, this is often never needed.
This method would be preferable for objects like vectors.
\param CLASS the name of the CLASS being exposed, with no delimiters
\param SUPER_CLASS with no delimiters, the parent class of the LuaExtendable,
or the same if it has no parent class
\note compile-time directive
\note highly recommended to precede an END_LUA_CLASS
\note adds a __gc, calls the destructor on the LuaExtendable
\note adds a __isnewindexable, returns false
\note adds a __new, calls the no-args constructor
\note adds a __newindex, throws a %Lua error
\note adds a __setmetatable, calls setMetatable defined by the LuaExtendable
\note adds a __tostring, calls toString defined by the LuaExtendable
*/
#define DEFINE_LUA_CLASS(TYPE, CLASS, SUPER_CLASS) \
	DEFINE_LUA_CLASS_LIB(TYPE, CLASS, SUPER_CLASS) \
		LUA_ENTRY_##TYPE##__gc_DESTRUCTOR(CLASS) \
		LUA_ENTRY_CLASS__isnewindexable_FALSE \
		LUA_ENTRY_CLASS__new_AUTO(CLASS) \
		LUA_ENTRY_##TYPE##__newindex_ERROR_AUTO(CLASS) \
		LUA_ENTRY_CLASS__setmetatable_USERDATA \
		LUA_ENTRY_##TYPE##__tostring_AUTO(CLASS)  

/** 
*/
#define DEFINE_LUA_CLASS_AUTO_METAMETHODS(CLASS) \
	DEFINE_LUA_CLASS__newindex_ERROR(CLASS) \
	DEFINE_LUA_CLASS__tostring(CLASS) 

/**
begin a library definition for registration via a %Lua proxy table,
and use the default "__new", "__setmetatable", "__gc" & "__tostring" methods

The "by proxy" method is desirable because it allows a userdata type in lua
to be treated exactly like a table, an ObjectOrientedParadigm class instance, and 
a C++ class instance.  It is an arguably more expensive version of a %Lua
exposed class.  It requires each exposed object to have its own userdata
pointer, proxy table for new values, and metatable to reference the proxy 
table.  That's a lot of storage, and it comes with all the associated
extra table indexing and function calls.  But, it results in ZERO distinction
between all %Lua classes, and partly C++ classes when operating with them 
in %Lua.  The extra simplicity and power makes it worth it very valuable.
\param CLASS the name of the CLASS being exposed, with no delimiters
\param SuperClass with no delimiters, the parent class of the LuaExtendable,
or the same if it has no parent class
\note compile-time directive
\note highly recommended to precede an END_LUA_CLASS
\note adds a __gc, calls the destructor on the LuaExtendable
\note adds a __isExtendableByProxy, (used in %Lua) returns true
\note adds a __isnewindexable, returns false
\note adds a __new, calls the no-args constructor
\note adds a __setmetatable, calls setMetatable defined by the LuaExtendable
\note adds a __tostring, calls toString defined by the LuaExtendable
*/
#define DEFINE_LUA_CLASS_BY_PROXY(TYPE, CLASS, SUPER_CLASS) \
	DEFINE_LUA_CLASS_LIB(TYPE, CLASS, SUPER_CLASS) \
		LUA_ENTRY_##TYPE##__gc_DESTRUCTOR(CLASS) \
		LUA_ENTRY_CLASS__isExtendableByProxy \
		LUA_ENTRY_CLASS__isnewindexable_TRUE \
		LUA_ENTRY_CLASS__new_AUTO(CLASS) \
		LUA_ENTRY_CLASS__setmetatable_PROXY \
		LUA_ENTRY_##TYPE##__tostring_AUTO(CLASS) 

#define DEFINE_LUA_CLASS_BY_PROXY_PUBLIC_MEMBERS(TYPE, CLASS, SUPER_CLASS) \
	DEFINE_LUA_CLASS_LIB_PUBLIC_MEMBERS(TYPE, CLASS, SUPER_CLASS) \
		LUA_ENTRY_##TYPE##__gc_DESTRUCTOR(CLASS) \
		LUA_ENTRY_CLASS__isExtendableByProxy \
		LUA_ENTRY_CLASS__isnewindexable_TRUE \
		LUA_ENTRY_CLASS__new_AUTO(CLASS) \
		LUA_ENTRY_CLASS__setmetatable_PROXY_PUBLIC_MEMBERS \
		LUA_ENTRY_##TYPE##__tostring_AUTO(CLASS) \
		LUA_ENTRY__indexSupport(CLASS) \
		LUA_ENTRY__newindexSupport(CLASS)

/** 
*/
#define DEFINE_LUA_CLASS_LIB(TYPE, CLASS, SUPER_CLASS) \
	DEFINE_LUA_##TYPE##_PUSH_FUNCTION(CLASS) \
	OPEN_LUA_NS(CLASS) \
		DEFINE_LUA_##TYPE##_AUTO_METAMETHODS(CLASS) \
		OPEN_LUA_LIB(CLASS) 

/** 
*/
#define DEFINE_LUA_CLASS_LIB_PUBLIC_MEMBERS(TYPE, CLASS, SUPER_CLASS) \
	DEFINE_LUA_##TYPE##_PUSH_FUNCTION(CLASS) \
	OPEN_LUA_NS(CLASS) \
		DEFINE_LUA_##TYPE##__tostring(CLASS) \
		OPEN_LUA_LIB(CLASS) 

/** 
*/
#define DEFINE_LUA_CLASS_NO_CTOR(TYPE, CLASS, SUPER_CLASS) \
	DEFINE_LUA_CLASS_LIB(TYPE, CLASS, SUPER_CLASS) \
		LUA_ENTRY_##TYPE##__gc_DESTRUCTOR(CLASS) \
		LUA_ENTRY_CLASS__isnewindexable_FALSE \
		LUA_ENTRY_##TYPE##__newindex_ERROR_AUTO(CLASS) \
		LUA_ENTRY_CLASS__setmetatable_USERDATA \
		LUA_ENTRY_##TYPE##__tostring_AUTO(CLASS)  

/** 
\todo these need matching DEFINE LIB defines
*/
#define DEFINE_LUA_CLASS_NO_DTOR(TYPE, CLASS, SUPER_CLASS) \
	DEFINE_LUA_CLASS_LIB(TYPE, CLASS, SUPER_CLASS) \
		LUA_ENTRY_CLASS__new_AUTO(CLASS) \
		LUA_ENTRY_CLASS__isnewindexable_FALSE \
		LUA_ENTRY_##TYPE##__newindex_ERROR_AUTO(CLASS) \
		LUA_ENTRY_CLASS__setmetatable_USERDATA \
		LUA_ENTRY_##TYPE##__tostring_AUTO(CLASS)  

/**
Define a %Lua library around a class, so that instances of the 
controlled in %Lua. This also exposes simple userdata pointers with all 
associated C++ and Lua methods, but it doesn't create any ability to added 
new %Lua fields.  It also doesn't supply any constructor or destructor exposure
to %Lua This could be used for objects like singletons.
\param CLASS the name of the CLASS being exposed, with no delimiters
\param SuperClass with no delimiters, the parent class of the LuaExtendable,
or the same if it has no parent class
\note compile-time directive
\note highly recommended to precede an END_LUA_CLASS
\note adds a __isnewindexable, returns false
\note adds a __newindex, throws a %Lua error
\note adds a __setmetatable, calls setMetatable defined by the LuaExtendable
\note adds a __tostring, calls toString defined by the LuaExtendable
*/
#define DEFINE_LUA_CLASS_NO_CTOR_NO_DTOR(TYPE, CLASS, SUPER_CLASS) \
	DEFINE_LUA_CLASS_LIB(TYPE, CLASS, SUPER_CLASS) \
		LUA_ENTRY_CLASS__isnewindexable_FALSE \
		LUA_ENTRY_##TYPE##__newindex_ERROR_AUTO(CLASS) \
		LUA_ENTRY_CLASS__setmetatable_USERDATA \
		LUA_ENTRY_##TYPE##__tostring_AUTO(CLASS) 

/** 
*/
#define DEFINE_LUA_CLASS_PUBLIC_MEMBERS(TYPE, CLASS, SUPER_CLASS) \
	DEFINE_LUA_CLASS_LIB_PUBLIC_MEMBERS(TYPE, CLASS, SUPER_CLASS) \
		LUA_ENTRY_##TYPE##__gc_DESTRUCTOR(CLASS) \
		LUA_ENTRY_CLASS__isnewindexable_FALSE \
		LUA_ENTRY_CLASS__new_AUTO(CLASS) \
		LUA_ENTRY_CLASS__setmetatable_USERDATA \
		LUA_ENTRY_##TYPE##__tostring_AUTO(CLASS) \
		LUA_ENTRY__index(CLASS) \
		LUA_ENTRY__newindex(CLASS)

#define DEFINE_LUA_CLASS_PUBLIC_MEMBERS_NODTOR(TYPE, CLASS, SUPER_CLASS) \
	DEFINE_LUA_CLASS_LIB_PUBLIC_MEMBERS(TYPE, CLASS, SUPER_CLASS) \
		LUA_ENTRY_CLASS__isnewindexable_FALSE \
		LUA_ENTRY_CLASS__new_AUTO(CLASS) \
		LUA_ENTRY_CLASS__setmetatable_USERDATA \
		LUA_ENTRY_##TYPE##__tostring_AUTO(CLASS) \
		LUA_ENTRY__index(CLASS) \
		LUA_ENTRY__newindex(CLASS)


#define DEFINE_LUA_CLASS_PUBLIC_MEMBERS_NOCTOR_NODTOR(TYPE, CLASS, SUPER_CLASS) \
	DEFINE_LUA_CLASS_LIB_PUBLIC_MEMBERS(TYPE, CLASS, SUPER_CLASS) \
		LUA_ENTRY_CLASS__isnewindexable_FALSE \
		LUA_ENTRY_CLASS__setmetatable_USERDATA \
		LUA_ENTRY_##TYPE##__tostring_AUTO(CLASS) \
		LUA_ENTRY__index(CLASS) \
		LUA_ENTRY__newindex(CLASS)


/**
\note when pushing an object into %Lua, it might not be because the 
object was created by a call to ObjectOrientedParadigm.new() in %Lua.  In this
case, if the class has a extra methods defined in %Lua, especially a 'construct'
method, that %Lua only properties of the object must be initialized the first
time the object is pushed into %Lua

\warning when called at this time (somewhere NOT from a new() call) NO ARGUMENTS WILL 
BE PASSED IN TO THE FUNCTION
*/
#define DEFINE_LUA_CLASS_PUSH_FUNCTION(CLASS) \
	sint embeddedLua::push(lua_State* L, CLASS * value) \
	{ \
		if (value) \
		{ \
			pushRegisteredClass(L, value); \
			lua_getglobal(L, "getmetatable"); \
			lua_pushvalue(L, -2); \
			lua_call(L, 1, 1); \
			if (lua_istable(L, -1)) \
			{ \
				lua_pop(L, 1); \
			} \
			else \
			{ \
				lua_pop(L, 1); \
				lua_getglobal(L, "ObjectOrientedParadigm"); \
				lua_getfield(L, -1, "initializers_PRIVATE"); \
				lua_replace(L, -2); \
				lua_getfield(L, -1, #CLASS ); \
				lua_replace(L, -2); \
				lua_pushvalue(L, -2); \
				lua_call(L, 1, 0); \
			} \
		}\
		else \
		{ \
			lua_pushnil(L); \
		} \
		return 1; \
	} \
	sint embeddedLua::push(lua_State* L, CLASS & value) \
	{ \
		return push(L, &value); \
	} \
	sint embeddedLua::push(lua_State* L, const CLASS & value) \
	{ \
		return push(L, const_cast<CLASS &>(value)); \
	} \
	sint embeddedLua::push(lua_State* L, const CLASS * value) \
	{ \
		return push(L, const_cast<CLASS*>(value)); \
	}

/** 
*/
#define DEFINE_LUA_ENUM(ENUM_NAME) \
	DEFINE_TO_ENUM(ENUM_NAME) \
	namespace embeddedLua \
	{ \
		LUA_FUNC(register_##ENUM_NAME) \
		{ \
			lua_newtable(L);					/*s: {} */ 
		
/** 
*/
#define DEFINE_LUA_ENUM_BOUND(ENUM, MIN_VALUE, MAX_VALUE) \
	DEFINE_TO_ENUM_BOUND(ENUM, MIN_VALUE, MAX_VALUE) \
	namespace embeddedLua \
	{ \
		LUA_FUNC(register_##ENUM) \
		{ \
			lua_newtable(L);			/*s: {} */ \
			LUA_ENUM(MIN_VALUE)

/**
*/
#define DEFINE_LUA_ENUM_BOUND_NS(NAMESPACE, ENUM, MIN_VALUE, MAX_VALUE) \
	DEFINE_TO_ENUM_BOUND_NS(NAMESPACE, ENUM, MIN_VALUE, MAX_VALUE) \
	namespace embeddedLua \
	{ \
		inline sint register_##ENUM(struct lua_State* L) /* LUA_FUNC(register_##ENUM)*/ \
		{ \
			lua_newtable(L);			/*s: {} */ \
			LUA_ENUM_NS(NAMESPACE, MIN_VALUE)

/**
empty for now, but makes things easier
*/
#define DEFINE_LUA_EXTENDABLE__tostring(CLASS)

/**
empty for now, but makes things easier
*/
#define DEFINE_LUA_EXTENDABLE_AUTO_METAMETHODS(CLASS) 

/**
empty for now, but makes things easier
*/
#define DEFINE_LUA_EXTENDABLE_PUSH_FUNCTION(CLASS) 

/** 
*/
#define DEFINE_LUA_FUNC__index_PUBLIC_MEMBERS(CLASS, SUPER_CLASS) \
	inline bool CLASS##__indexSupport(const CLASS##& t, const char* k, lua_State* L, const char* className) \
	{

/*
*/
#define DEFINE_LUA_FUNC__index_PUBLIC_MEMBERS_PROXY(CLASS, SUPER_CLASS) \
	inline sint CLASS##__indexSupportImplementation(const CLASS##& t, const char* k, lua_State* L, const char* className) \
	{


/** 
 
*/
#define DEFINE_LUA_FUNC__newindex_PUBLIC_MEMBERS(CLASS, SUPER_CLASS) \
	inline bool CLASS##__newindexSupport(##CLASS##& t, const char* k, lua_State* L, const char* className) \
	{

/** 
 
*/
#define DEFINE_LUA_FUNC__newindex_PUBLIC_MEMBERS_PROXY(CLASS, SUPER_CLASS) \
	inline bool CLASS##__newindexImplementation(##CLASS##& t, const char* k, lua_State* L, const char* className) \
	{

/** 
Begin a library definition for registration
This method is ideal for static classes or libraries.
\note compile-time directive
\note highly recommended to precede END_LUA_LIBRARY
\param name name of the library without string delimiters
*/
#define DEFINE_LUA_LIBRARY(NAME) \
	OPEN_LUA_NS(NAME) \
		OPEN_LUA_LIB(NAME)				

/** 
*/
#define DEFINE_LUA_OPENER(NAME) \
	sint key(lua_State* L) \
	{ \
		luaL_register(L, #NAME, NAME##_library); \
		return 1; \
	} 

/** 
*/
#define DEFINE_LUA_OPENER_CLASS(CLASS, SUPER_CLASS) \
	sint key(lua_State* L) \
	{ \
		luaL_register(L, #CLASS, CLASS##_library); \
		embeddedLua::declareLuaClass(L, #CLASS, #SUPER_CLASS); \
		return 1; \
	} 

/** 
*/
#define DEFINE_LUA_OPENER_EXTENSIBLE(NAME) \
	sint key(lua_State* L) \
	{ \
		luaL_register(L, #NAME, NAME##_library); \
		Lua::nilLoadedStatus(L, #NAME); \
		return 1; \
	} 

/** 
*/
#define DEFINE_LUAEXTENDABLE_PROXY_PUBLIC_MEMBERS_DEFAULT_FUNCTIONS(CLASS) \
	DEFINE_DEFAULT_TOSTRING(CLASS) \
	DEFINE_DEFAULT_GETCLASSNAME(CLASS) \
	DEFINE_PROXY_SETMETATABLE_PUBLIC_MEMBERS(CLASS)

/** 
*/
#define DEFINE_LUAEXTENDABLE_PROXY_DEFAULT_FUNCTIONS(CLASS) \
	DEFINE_DEFAULT_TOSTRING(CLASS) \
	DEFINE_DEFAULT_GETCLASSNAME(CLASS) \
	DEFINE_PROXY_SETMETATABLE(CLASS)

/** 
*/
#define DEFINE_LUAEXTENDABLE_USERDATA_DEFAULT_FUNCTIONS(CLASS) \
	DEFINE_DEFAULT_TOSTRING(CLASS) \
	DEFINE_DEFAULT_GETCLASSNAME(CLASS) \
	DEFINE_USERDATA_SETMETATABLE(CLASS)

/** 
*/
#define DEFINE_PROXY_SETMETATABLE(CLASS) \
	virtual sint setMetatable(lua_State* L) \
	{ \
		return setProxyMetatable(L); \
	}

/** 
*/
#define DEFINE_PROXY_SETMETATABLE_PUBLIC_MEMBERS(CLASS) \
	virtual sint setMetatable(lua_State* L) \
	{ \
		return setProxyMetatablePublicMembers(L); \
	}

/** 
*/
#if ARGUMENT_ERRORS
	#define DEFINE_TO_CLASS_FUNCTIONS(CLASS) \
		namespace embeddedLua \
		{ \
			template<> inline CLASS* to< CLASS* >(lua_State* L, int index) \
			{ \
				lua_assertIndexInStack(L, index); \
				if (lua_isnil(L, index)) \
				{ \
					return NULL; \
				} \
				if (!lua_isuserdata(L, index)) \
				{ \
					const char* actual = luaL_typename(L, index); \
					luaL_error(L, "argument type error! argument at index %d expected: userdata actual: %s ", index, actual); \
				} \
				return *static_cast< CLASS** >(lua_touserdata(L, index)); \
			} \
			template<> inline const CLASS* to< const CLASS* >(lua_State* L, int index) \
			{ \
				lua_assertIndexInStack(L, index); \
				if (lua_isnil(L, index)) \
				{ \
					return NULL; \
				} \
				if (!lua_isuserdata(L, index)) \
				{ \
					const char* actual = luaL_typename(L, index); \
					luaL_error(L, "argument type error! argument at index %d expected: userdata actual: %s ", index, actual); \
				} \
				return *static_cast< CLASS** >(lua_touserdata(L, index)); \
			} \
			template<> inline CLASS& to< CLASS& >(lua_State* L, int index) \
			{ \
				lua_assertIndexInStack(L, index); \
				if (!lua_isuserdata(L, index)) \
				{ \
					const char* actual = luaL_typename(L, index); \
					luaL_error(L, "argument type error! argument at index %d expected: userdata actual: %s ", index, actual); \
				} \
				return **static_cast< CLASS** >(lua_touserdata(L, index)); \
			} \
			template<> inline const CLASS& to< const CLASS& >(lua_State* L, int index) \
			{ \
				lua_assertIndexInStack(L, index); \
				if (!lua_isuserdata(L, index)) \
				{ \
					const char* actual = luaL_typename(L, index); \
					luaL_error(L, "argument type error! argument at index %d expected: userdata actual: %s ", index, actual); \
				} \
				return **static_cast< CLASS** >(lua_touserdata(L, index)); \
			} \
		} // namespace embeddedLua 
#else // #if ARGUMENT_ERRORS
	#define DEFINE_TO_CLASS_FUNCTIONS(CLASS) \
		namespace embeddedLua \
		{ \
			template<> inline const CLASS* to< const CLASS* >(lua_State* L, int index) \
			{ \
				if (lua_isnil(L, index)) \
				{ \
					return NULL; \
				} \
				return *static_cast< CLASS** >(lua_touserdata(L, index)); \			
			} \
			template<> inline CLASS* to< CLASS* >(lua_State* L, int index) \
			{ \
				if (lua_isnil(L, index)) \
				{ \
					return NULL; \
				} \
				return *static_cast< CLASS** >(lua_touserdata(L, index)); \			
			} \
			template<> inline CLASS& to< CLASS& >(lua_State* L, int index) \
			{ \
				return **static_cast<CLASS**>(lua_touserdata(L, index)); \
			} \
			template<> inline const CLASS& to< const CLASS& >(lua_State* L, int index) \
			{ \
				return **static_cast<CLASS**>(lua_touserdata(L, index)); \
			} \
		} // namespace embeddedLua 
#endif

/** helps compilers with enums as paramenters in template wrapped functions */
#define DEFINE_TO_ENUM(ENUM) \
	template<> inline ENUM embeddedLua::to<##ENUM##>(lua_State* L, sint index) \
	{ \
		return static_cast<##ENUM##>(to<sint>(L, index)); \
	}


/** helps compilers with enums as paramenters in template wrapped functions */
#if ARGUMENT_ERRORS	
	#define DEFINE_TO_ENUM_BOUND(ENUM, MIN, MAX) \
		template<> inline ENUM embeddedLua::to< ##ENUM## >(lua_State* L, sint index) \
		{ \
			ENUM value = static_cast< ##ENUM## >(to<sint>(L, index)); \
			if (value > MAX || value < MIN) \
			{ \
				luaL_error(L, "argument type error! enum:" #ENUM " must be >= " #MIN ":%d and <= " #MAX ":%d but is %d", MIN, MAX, value); \
			} \
			return value; \
		}
#else
	#define DEFINE_TO_ENUM_BOUND(ENUM, MIN, MAX) \
		DEFINE_TO_ENUM(ENUM)		
#endif//ARGUMENT_ERRORS


/** helps compilers with enums as paramenters in template wrapped functions */
#if ARGUMENT_ERRORS
	#define DEFINE_TO_ENUM_BOUND_NS(NAMESPACE, ENUM, MIN, MAX) \
		template<> inline NAMESPACE##::##ENUM embeddedLua::to< NAMESPACE##::##ENUM >(lua_State* L, sint index) \
		{ \
			NAMESPACE##::##ENUM value = static_cast< NAMESPACE##::##ENUM >(to<sint>(L, index)); \
			if (value >NAMESPACE##::##MAX || value < NAMESPACE##::##MIN) \
			{ \
				luaL_error(L, "argument type error! enum:" #NAMESPACE "::" #ENUM " must be >= " #MIN ":%d and <= " #MAX ":%d but is %d",NAMESPACE##::##MIN, NAMESPACE##::##MAX, value); \
			} \
			return value; \
		}
#else
	#define DEFINE_TO_ENUM_BOUND_NS(NAMESPACE, ENUM, MIN, MAX) \
		DEFINE_TO_ENUM_NS(NAMESPACE, ENUM)
#endif//ARGUMENT_ERRORS


/** helps compilers with enums as paramenters in template wrapped functions */
#define DEFINE_TO_ENUM_NS(NAMESPACE, ENUM)\
	template<> inline NAMESPACE##::##ENUM embeddedLua::to< NAMESPACE##::##ENUM >(lua_State* L, sint index) \
	{ \
		return static_cast< NAMESPACE##::##ENUM >(to<sint>(L, index));\
	}


/**
defines functions that can be used to get specific class pointers
back out of %Lua.
\note compile-time directive
*/
#if ARGUMENT_ERRORS
#define DEFINE_TO_LUAEXTENDABLES(CLASS) \
	namespace embeddedLua \
	{ \
		template<> inline CLASS* to< CLASS* >(lua_State* L, sint index) \
		{ \
			LuaExtendable* le = to<LuaExtendable*>(L, index); \
			CLASS* object = dynamic_cast< CLASS* >(le); \
			if (object == static_cast< CLASS* >(le)) \
				return object; \
			luaL_error(L, "argument type error! argument at index %d: expected: %s actual: %s", index, #CLASS, typeid(object).name()); \
			return NULL; \
		} \
		template<> inline const CLASS* to< const CLASS* >(lua_State* L, sint index) \
		{ \
			return to< CLASS* >(L, index); \
		} \
		template<> inline CLASS& to< CLASS& >(lua_State* L, sint index) \
		{ \
			CLASS* object = to< CLASS* >(L, index); \
			return *object; \
		} \
		template<> inline const CLASS& to< const CLASS& >(lua_State* L, sint index) \
		{ \
			CLASS* object = to< CLASS* >(L, index); \
			return *object; \
		} \
	}
#else
#define DEFINE_TO_LUAEXTENDABLES(CLASS) \
	namespace embeddedLua \
	{ \
		template<> inline CLASS* to< CLASS* >(lua_State* L, sint index) \
		{ \
			return static_cast< CLASS* >(to<LuaExtendable*>(L, index)); \
		} \
		template<> inline const CLASS* to< const CLASS* >(lua_State* L, sint index) \
		{ \
			return to< CLASS* >(L, index); \
		} \
		template<> inline CLASS& to<CLASS&>(lua_State* L, sint index) \
		{ \
			return *to< CLASS* >(L, index); \
		} \
		template<> inline const CLASS& to< const CLASS& >(lua_State* L, sint index) \
		{ \
			return *to< CLASS* >(L, index); \
		} \
	}
#endif//ARGUMENT_ERRORS

/** 
*/
#define DEFINE_USERDATA_SETMETATABLE(CLASS) \
	virtual sint setMetatable(lua_State* L) \
	{ \
		return setUserdataMetatable(L); \
	}

/**
This closes out the luaL_reg and defines the library opener function, 
which will register the exposed function and declare a %Lua class
via ObjectOrientedParadgim.lua.
\param CLASS the name of the CLASS being exposed, with no delimiters
\param SuperClass with no delimiters, the parent class of the LuaExtendable,
or the same if it has no parent class

calls nilLoadedStatus() in declareLuaClass

\note compile-time directive
\note highly recommended to follow any form of DEFINE_LUA_LUAEXTENDABLE
*/
#define END_LUA_CLASS(CLASS, SUPER_CLASS) \
		CLOSE_LUA_LIB(CLASS) \
		DEFINE_LUA_OPENER_CLASS(CLASS, SUPER_CLASS) \
	CLOSE_LUA_NS(CLASS)

/** 
*/
#define END_LUA_ENUM(ENUM) \
			lua_newtable(L);						/*s: ReadOnly proxy */ \
			lua_newtable(L);						/*s: ReadOnly proxy mt */ \
			lua_pushvalue(L, -3);					/*s: ReadOnly proxy mt ReadOnly */ \
			lua_setfield(L, -2, "__index");			/*s: ReadOnly proxy mt */ \
			lua_pushcfunction(L, embeddedLua::__newindexEnum); /*s: ReadOnly proxy mt UpdateEnumError */ \
			lua_setfield(L, -2, "__newindex");		/*s: ReadOnly proxy mt */ \
			lua_setmetatable(L, -2);				/*s: ReadOnly proxy */ \
			lua_replace(L, -2);						/*s: proxy */ \
			lua_setglobal(L, #ENUM );				/*s: */ \
			return 0; \
		} \
	} // end namespace embeddedLua

/** 
*/
#define END_LUA_ENUM_BOUND(ENUM, MAX_ENUM_VALUE) \
		LUA_ENUM(MAX_ENUM_VALUE)	/*s: MAX_ENUM_VALUE */ \
	END_LUA_ENUM(ENUM)

/**
*/
#define END_LUA_ENUM_BOUND_NS(NAMESPACE, ENUM, MAX_ENUM_VALUE) \
		LUA_ENUM_NS(NAMESPACE, MAX_ENUM_VALUE)	/*s: MAX_ENUM_VALUE */ \
	END_LUA_ENUM_NS(NAMESPACE, ENUM)

/**
*/
#define END_LUA_ENUM_NS(NAMESPACE, ENUM) \
			lua_newtable(L);						/*s: ReadOnly proxy */ \
			lua_newtable(L);						/*s: ReadOnly proxy mt */ \
			lua_pushvalue(L, -3);					/*s: ReadOnly proxy mt ReadOnly */ \
			lua_setfield(L, -2, "__index");			/*s: ReadOnly proxy mt */ \
			lua_pushcfunction(L, embeddedLua::__newindexEnum); /*s: ReadOnly proxy mt UpdateEnumError */ \
			lua_setfield(L, -2, "__newindex");		/*s: ReadOnly proxy mt */ \
			lua_setmetatable(L, -2);				/*s: ReadOnly proxy */ \
			lua_replace(L, -2);						/*s: proxy */ \
			lua_setglobal(L, #ENUM );				/*s: */ \
			return 0; \
		} \
	} // end namespace embeddedLua

/** 
 
*/
#define END_LUA_FUNC__index_PUBLIC_MEMBERS(CLASS, SUPER_CLASS) \
		if (strcmp(className, #SUPER_CLASS)) \
		{	/* here would be a recursive call that would be never called */ \
			return SUPER_CLASS##__indexSupport(t, k, L, #SUPER_CLASS); \
		} \
		else \
		{ 	/*  must tell the main calling function if something was pushed */ \
			return false; \
		} \
	} \
	LUA_FUNC(CLASS##__index) \
	{ \
		const schar* k = to<const schar*>(L, -1); \
		const CLASS##& t = to<const CLASS##&>(L, -2); \
		if (!##CLASS##__indexSupport(t, k, L, #CLASS)) \
		{ \
			lua_getglobal(L, "getClass");	/*s: getClass */ \
			push(L, #CLASS);				/*s: getClass "CLASS" */ \
			lua_call(L, 1, 1);				/*s: CLASS */ \
			lua_getfield(L, -1, k);			/*s: CLASS[k] */ \
		} \
		return 1; \
	} 

/**
*/
#define END_LUA_FUNC__index_PUBLIC_MEMBERS_PROXY(CLASS, SUPER_CLASS) \
		if (strcmp(className, #SUPER_CLASS))\
		{	/* here would be a recursive call that would be never called */ \
			return SUPER_CLASS##__indexSupportImplementation(t, k, L, #SUPER_CLASS); \
		} \
		else \
		{ \
			pushFalse(L);\
			pushNil(L); \
			return 2; \
		} \
	} \
	LUA_FUNC(CLASS##__indexSupport) \
	{ \
		return CLASS##__indexSupportImplementation(to<const CLASS##&>(L, -2), to<const char*>(L, -1), L, #CLASS); \
	}

/** 
 
*/
#define END_LUA_FUNC__newindex_PUBLIC_MEMBERS(CLASS, SUPER_CLASS) \
	if (strcmp(className, #SUPER_CLASS)) \
	{	/* here would be a recursive call that would be never called */ \
		return SUPER_CLASS##__newindexSupport(t, k, L, #SUPER_CLASS); \
	} \
	else \
	{ \
		return false; /* must tell the main calling function if something was pushed */ \
	} \
} \
LUA_FUNC(##CLASS##__newindex) \
{ \
	const char* k = to<const schar*>(L, -2); \
	if (!##CLASS##__newindexSupport(to<CLASS&>(L, -3), k, L, #CLASS )) \
	{ \
		luaL_error(L, "ERROR! nonassignable index %s for " #CLASS , k); \
	} \
	return 0; \
} 

/**
*/
#define END_LUA_FUNC__newindex_PUBLIC_MEMBERS_PROXY(CLASS, SUPER_CLASS) \
		if (strcmp(className, #SUPER_CLASS)) \
		{	/* here would be a recursive call that would be never called */ \
			return SUPER_CLASS##__newindexImplementation(t, k, L, #SUPER_CLASS); \
		} \
		else \
		{ \
			pushFalse(L); \
			return 1; \
		} \
	} \
	LUA_FUNC(CLASS##__newindexSupport) \
	{ \
		return CLASS##__newindexImplementation(to<##CLASS##&>(L, -3), to<const schar*>(L, -2), L, #CLASS); \
	} 

/** 
end a library definition for registration
\note compile-time directive
\note highly recommended to follow with DEFINE_LUA_LIBRARY
\param name name of the library without string delimiters
*/
#define END_LUA_LIBRARY(NAME) \
		CLOSE_LUA_LIB(NAME) \
		DEFINE_LUA_OPENER(NAME) \
	CLOSE_LUA_NS(NAME)

/** 
end a library definition for registration,
adds shortcut to allow extending the library in %Lua with 
the require() function.
\note compile-time directive
\note highly recommended to follow define_lua_library_extensible
\param NAME name of the library without string delimiters
*/
#define END_LUA_LIBRARY_EXTENSIBLE(NAME) \
		CLOSE_LUA_LIB(NAME) \
		DEFINE_LUA_OPENER_EXTENSIBLE(NAME) \
	CLOSE_LUA_NS(NAME)

/** 
*/
#define LUA_ENTRY__index(CLASS) \
	LUA_ENTRY_NAMED("__index", CLASS##__index)

/** 
*/
#define LUA_ENTRY__indexSupport(CLASS) \
	LUA_ENTRY_NAMED("__indexSupport", CLASS##__indexSupport)

/** 
*/
#define LUA_ENTRY__newindex(CLASS) \
	LUA_ENTRY_NAMED("__newindex", CLASS##__newindex)

/** 
*/
#define LUA_ENTRY__newindexSupport(CLASS) \
	LUA_ENTRY_NAMED("__newindexSupport", CLASS##__newindexSupport)

/** 
*/
#define LUA_ENTRY_CLASS__gc_DESTRUCTOR(CLASS) \
	LUA_ENTRY_NAMED("__gc", embeddedLua::__gcmetamethod<##CLASS##>) 

/** 
*/
#define LUA_ENTRY_CLASS__isExtendableByProxy \
	LUA_ENTRY_NAMED("__isExtendableByProxy", embeddedLua::pushTrue) 

/** 
*/
#define LUA_ENTRY_CLASS__isnewindexable_TRUE \
	LUA_ENTRY_NAMED("__isnewindexable", embeddedLua::pushTrue) 

/** 
*/
#define LUA_ENTRY_CLASS__isnewindexable_FALSE \
	LUA_ENTRY_NAMED("__isnewindexable", embeddedLua::pushFalse) 

/** 
*/
#define LUA_ENTRY_CLASS__new_AUTO(CLASS) \
	LUA_ENTRY_NAMED("__new", embeddedLua::__new<##CLASS##>) 

/** 
*/
#define LUA_ENTRY_CLASS__newindex_ERROR_AUTO(CLASS) \
	LUA_ENTRY_NAMED("__newindex", lua_library_##CLASS##::__newindexError##CLASS) 

/** 
*/
#define LUA_ENTRY_CLASS__setmetatable_PROXY \
	LUA_ENTRY_NAMED("__setmetatable", embeddedLua::setProxyMetatable) 

/** 
*/
#define LUA_ENTRY_CLASS__setmetatable_PROXY_PUBLIC_MEMBERS \
	LUA_ENTRY_NAMED("__setmetatable", embeddedLua::setProxyMetatablePublicMembers) 

/** 
*/
#define LUA_ENTRY_CLASS__setmetatable_USERDATA \
	LUA_ENTRY_NAMED("__setmetatable", embeddedLua::setUserdataMetatable) 

/** 
*/
#define LUA_ENTRY_CLASS__tostring_AUTO(CLASS) \
	LUA_ENTRY_NAMED("__tostring", __tostring##CLASS)

/** 
add a lua method to a definition by the same name 
\note compile-time directive
\param function a lua_function
*/
#define LUA_ENTRY(function) \
	{(#function), (function)}, 

/** 
*/
#define LUA_ENTRY_EXTENDABLE__gc_DESTRUCTOR(CLASS) \
	LUA_ENTRY_NAMED("__gc", LuaExtendable::__gcmetamethod)

/** 
*/
#define LUA_ENTRY_EXTENDABLE__newindex_ERROR_AUTO(CLASS) \
	LUA_ENTRY_NAMED("__newindex", LuaExtendable::__newindexError) 

/** 
*/
#define LUA_ENTRY_EXTENDABLE__tostring_AUTO(CLASS) \
	LUA_ENTRY_NAMED("__tostring", LuaExtendable::__tostring) 

/** 
*/
#define LUA_ENUM(ENUMERATION) \
			push(L, ENUMERATION);				/*s: ENUM_NAME, ENUMERATION */ \
			lua_setfield(L, -2, #ENUMERATION );	/*s: ENUM_NAME */ 

/**
*/
#define LUA_ENUM_NS(NAMESPACE, ENUMERATION) \
			push(L, NAMESPACE##::##ENUMERATION);		/*s: ENUM_NAME, ENUMERATION */ \
			lua_setfield(L, -2, #ENUMERATION);			/*s: ENUM_NAME */ 

/**
the sentinel entry in a lua library
*/
#define LUA_FINAL_ENTRY \
	{NULL, NULL}
// #define LUA_FINAL_ENTRY

/** 
Declares a (static) lua function.  Declares a function that
takes a single lua_State argument, and returns an integer,
the number of arguments it has added to the stack.
\note compile-time directive
\param name name of the function that will be declared, without string delimiters
*/
#define LUA_FUNC(name) \
	sint name##(lua_State* L)

/**  
add a lua method to a definition by a different name 
\note compile-time directive
\param name a string delimited name
\param function a lua_function
*/
#define LUA_ENTRY_NAMED(name, function)	\
	{(name), (function)}, 

/** 
*/
#define OPEN_LUA_LIB(NAME) \
	static const luaL_reg NAME##_library[] = \
	{	/* begin function list */

/** 
*/
#define OPEN_LUA_NS(NAME) \
	namespace lua_library_##NAME \
	{ 

/** 
*/
#define REGISTER_LUA_ENUM(LUA_OBJECT_PTR, ENUM_NAME) \
	embeddedLua::register_##ENUM_NAME##(LUA_OBJECT_PTR->getState());

/** 
register a library with a lua state 
\warning registration MUST be done in dependency order, or the behavior
is undefined
\warning registration MUST be done in class hierarchical order, or the 
behavior is undefined
\note run-time directive
\param lua_object_ptr is class Lua, not struct lua_State 
\param module of the library without string delimiters
*/
#define REGISTER_LUA_LIBRARY(LUA_OBJECT_PTR, MODULE) \
	LUA_OBJECT_PTR->openLibrary(lua_library_##MODULE::key);		

/** @} */

namespace embeddedLua 
{

/**
\interface LuaExtendable
Implementing this interface, and defining the methods via the macros above
or having the virtual methods call the static versions below is probably the
easiest way to expose a class and all of it's methods to %Lua.
\warning The thread safety of this class is not guaranteed!
\ingroup LuaExtension
*/

class LuaExtendable 
{
public:
	/**
	__gc method for the metatable of a LuaExtendable exposed to %Lua.
	Using this will cause the C++ object get destroyed when all references to it
	in a lua_State are destroyed.
	*/
	static sint 
		__gcmetamethod(lua_State* L);
	
	/**
	\note __newindex methods:
	returns true if %Lua code like userdata[k] = v will operate correctly 
	(without errors, and with the expected results) on the userdata pointer
	
	\warning IT IS UP TO YOU TO MAKE SURE THIS IS CORRECT. If userdata[k] = v will 
	work, make sure that your userdata:__isnewindexable() returns true, otherwise
	make sure userdata:__isnewindexable() returns false in %Lua (and C/C++). This
	only needs to be true for if userdata[k] = v must work for any non-nil k, and 
	any v.  Vectors for example, which only allow userdata[x,y,z] = v, return
	userdata:__isnewindexable() returns false

	\note using the given LuaExtendable definitions will make this a lot easier.
	*/
	/**
	__newindex method for the metatable of a class exposed to %Lua that 
	should be configured to the desired error level for the build.
	e.g.: throw errors in a debug build, warn in a release build, etc.
	*/
	static sint				
		__newindexError(lua_State* L);
	
	/**
	__tostring method for the metatable of a class exposed to %Lua.
	*/
	static sint				
		__tostring(lua_State* L);	
			 
	/** empty dtor */
	virtual					
		~LuaExtendable(void)=0 {/* empty */};
	
	/** 
	a function that classes must implement to make them easier to make into well formed
	%Lua classes
	*/
	virtual const schar*		
		getClassName(void) const=0;
	
	/**
	objects of this type will have a metatable assigned to them when pushed into
	a lua_State.  %Lua doesn't allow setmetatable calls on userdata pointers
	from %Lua.  This function will be called via a legal %Lua function call.
	It is mostly easily implemented in terms of one of the static LuaExtendable
	functions.
	*/
	virtual sint			
		setMetatable(lua_State* L)=0;
	
	/**
	a to string function is almost always necessary, since so much of %Lua
	use is simply to make inspection of objects very easy, there is often
	a lot of information about them printed, logged, or rendered
	*/
	virtual const schar*		
		toString(void)=0;
}; // class LuaExtendable

/** 
metamethod for classes that do not implement
LuaExtendable
*/
template<typename CLASS> sint
__gcmetamethod(lua_State* L)
{
	CLASS* udata = to<CLASS*>(L, -1);
	delete udata;
	return 0;
}

template<typename CLASS> sint
__new(lua_State* L)
{
	return push(L, new CLASS());
}

/**
*/
sint 
	__newindexEnum(lua_State* L);

/**
__newindex method for the metatable of a class exposed to %Lua 
via the proxy method that will allow it to be assigned new fields
*/
sint 
	__newindexProxy(lua_State* L);

/**
__newindex method for the metatable of a class exposed to %Lua 
via the proxy method that will allow it to be assigned new fields
but also has exposed public members
*/
sint 
	__newindexProxyPublicMembers(lua_State* L);

/**
completes a %Lua class declaration in case no script accompanied
the class in %Lua.
\ingroup LuaExtension
*/
void 
	completeLuaClassDeclaration(lua_State* L, const schar* derived, const schar* super);

/**
makes sure that the class is declared declared in the lua OOP system.
\note run-time directive
*/
void				
	declareLuaClass(lua_State* L, const schar* derived, const schar* super);

/**
print the string to the %Lua output
\ingroup LuaExtension
*/
void 
	printToLua(lua_State* L, const schar* string);

/**
helper function for pushing a class to %Lua an preserving the ability
to compare userdata and use them as equivalent table keys
\see comments in the implementation of void Lua::initializeUserdataStorage(void)
\ingroup LuaExtension
*/
sint 
	pushRegisteredClass(lua_State* L, void* pushee);

/**
helper function for simply registering global native functions to %Lua
\ingroup LuaExtension
*/
void 
	registerGlobalLibrary(lua_State* L);

/**
helps set a userdata metatable from script
\warning USE JUDICIOUSLY.  This violates some safety precedence in %Lua. 
*/
sint				
	setProxyMetatable(lua_State* L);

/**
helps set a userdata metatable from script
\warning USE JUDICIOUSLY.  This violates some safety precedence in %Lua. 
*/
sint 
	setProxyMetatablePublicMembers(lua_State* L);

/**
helps set a userdata metatable from script, this is a exact C version of the function in %Lua,
since you can't call setmetatable on a userdata value in %Lua.
\warning USE JUDICIOUSLY.  This violates some safety precedence in %Lua.
*/
sint
	setUserdataMetatable(lua_State* L);
} // namespace embeddedLua 

/** @} */

#endif//LUAEXTENSIBILITY_H

