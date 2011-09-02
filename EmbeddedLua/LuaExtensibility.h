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
	LUA_NAMED_ENTRY("Method", method)
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

\todo declare/define enums

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

#define CLOSE_LUA_LIB(NAME) \
		LUA_FINAL_ENTRY \
	};	/* end function list */ 
// #define CLOSE_LUA_LIB

#define CLOSE_LUA_NS(NAME) \
	}; // end namespace lua_library_##name
// #define CLOSE_LUA_NS

/**
\def DECLARE_LUA_CLASS
Declares a library around a POD class
\note compile-time directive
*/
#define DECLARE_LUA_CLASS(CLASS) \
	DECLARE_LUA_LIBRARY(CLASS) \
	DECLARE_LUA_PUSH_FUNCTION(CLASS) \
	DEFINE_TO_CLASS_FUNCTIONS(CLASS) 
// #define DECLARE_LUA_LUAEXTENDABLE

/**
\def DECLARE_LUA_CLASS_NS
Declares a library around a POD class
\note compile-time directive
*/
#define DECLARE_LUA_CLASS_NS(NAMESPACE, CLASS) \
	DECLARE_LUA_LIBRARY(CLASS)	\
	DECLARE_LUA_PUSH_FUNCTION_NS(NAMESPACE, CLASS) \
	DEFINE_TO_CLASS_FUNCTIONS(NAMESPACE##::##CLASS)
// #define DECLARE_LUA_CLASS_NS

/** 
\def DECLARE_LUA_LIBRARY
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
// #define begin_lua_library_declaration

/**
\def DECLARE_LUA_LUAEXTENDABLE
Declares a library around a class that implements
the LuaExtendable interface.
\note compile-time directive
*/
#define DECLARE_LUA_LUAEXTENDABLE(CLASS) \
	DECLARE_LUA_LIBRARY(CLASS) \
	DEFINE_TO_LUAEXTENDABLES(CLASS) 
// #define DECLARE_LUA_LUAEXTENDABLE

/**
\def DECLARE_LUA_LUAEXTENDABLE_NS
Declares a library around a class in a namespace that implements
the LuaExtendable interface.
\note compile-time directive
*/
#define DECLARE_LUA_LUAEXTENDABLE_NS(NAMESPACE, CLASS) \
	DECLARE_LUA_LIBRARY(CLASS)	\
	DEFINE_TO_LUAEXTENDABLES(NAMESPACE::CLASS)
// #define DECLARE_LUA_LUAEXTENDABLE_NS

#define DECLARE_LUA_PUSH_FUNCTION(CLASS) \
	namespace lua_extension \
	{ \
		sint push(lua_State* L, CLASS * value); \
	} 
// #define DECLARE_LUA_PUSH_FUNCTION

#define DECLARE_LUA_PUSH_FUNCTION_NS(NAMESPACE, CLASS) \
	namespace lua_extension \
	{ \
		sint push(lua_State* L, NAMESPACE##::##CLASS * value); \
	} 
// #define DECLARE_LUA_PUSH_FUNCTION_NS

#define DEFINE_DEFAULT_TOSTRING(CLASS) \
	virtual const schar* toString(void) \
	{ \
		return "This is a " #CLASS; \
	}
// #define DEFINE_DEFAULT_TOSTRING(CLASS) 

#define DEFINE_DEFAULT_GETCLASSNAME(CLASS) \
	virtual const schar* getClassName(void) const \
	{ \
		return #CLASS; \
	}
// #define DEFINE_DEFAULT_GETCLASSNAME(CLASS) 

#define DEFINE_CONDITIONAL__index_ENTRY(INDEX) \
	if (!strcmp(k, #INDEX )) return push(L, t.##INDEX##);	
// #define DEFINE_CONDITIONAL__index_ENTRY

#define DEFINE_CONDITIONAL__newindex_ENTRY(INDEX, TYPE) \
	if (!strcmp(k, #INDEX)) { t.##INDEX = to<##TYPE##>(L, -1); return 0; }	
// #define DEFINE_CONDITIONAL__index_ENTRY

#if DEBUG 
#define DEFINE_LUA_CLASS__newindex_ERROR(CLASS) \
	LUA_FUNC(__newindexError##CLASS) \
	{ \
		return luaL_error(L, "ERROR! Attempting to assign a value to a LuaExtendable %s that doesn't support new values.  " \
		"Use DEFINE_LUA_CLASS_BY_PROXY to expose this class to Lua if that is desired.", #CLASS); \
	}
// #define DEFINE_LUA_CLASS__newindex_ERROR
#else 
#define DEFINE_LUA_CLASS__newindex_ERROR(CLASS) \
	LUA_FUNC(__newindexError##CLASS) \
	{ \
		(void*)L; \
		return 0; \
	}
// #define DEFINE_LUA_CLASS__newindex_ERROR
#endif//DEBUG

/** \left off */
#define DEFINE_LUA_CLASS__tostring(CLASS) \
	LUA_FUNC(__tostring##CLASS##) \
	{ \
		lua_pushstring(L, "This is a " #CLASS); \
		return 1; \
	}	
// #define DEFINE_LUA_CLASS__tostring

/**
\def DEFINE_LUA_CLASS
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
// #define DEFINE_LUA_CLASS 

#define DEFINE_LUA_CLASS_AUTO_METAMETHODS(CLASS) \
	DEFINE_LUA_CLASS__newindex_ERROR(CLASS) \
	DEFINE_LUA_CLASS__tostring(CLASS) 
// #define DEFINE_LUA_CLASS_AUTO_METAMETHODS

/**
\def DEFINE_LUA_CLASS_BY_PROXY
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
// #define DEFINE_LUA_CLASS_BY_PROXY

#define DEFINE_LUA_NO_CLASS_NO_INDEX(TYPE, CLASS, SUPER_CLASS) \
	DEFINE_LUA_CLASS_LIB_NO_INDEX(TYPE, CLASS, SUPER_CLASS) \
		LUA_ENTRY_##TYPE##__gc_DESTRUCTOR(CLASS) \
		LUA_ENTRY_CLASS__isnewindexable_FALSE \
		LUA_ENTRY_CLASS__new_AUTO(CLASS) \
		LUA_ENTRY_CLASS__setmetatable_USERDATA \
		LUA_ENTRY_##TYPE##__tostring_AUTO(CLASS)  
// #define DEFINE_LUA_NO_CLASS_NO_INDEX

#define DEFINE_LUA_CLASS_LIB(TYPE, CLASS, SUPER_CLASS) \
	DEFINE_LUA_##TYPE##_PUSH_FUNCTION(CLASS) \
	OPEN_LUA_NS(CLASS) \
		DEFINE_LUA_##TYPE##_AUTO_METAMETHODS(CLASS) \
		OPEN_LUA_LIB(CLASS) 
// #define DEFINE_LUA_CLASS_LIB

#define DEFINE_LUA_CLASS_LIB_NO_INDEX(TYPE, CLASS, SUPER_CLASS) \
	DEFINE_LUA_##TYPE##_PUSH_FUNCTION(CLASS) \
	OPEN_LUA_NS(CLASS) \
		DEFINE_LUA_##TYPE##__tostring(CLASS) \
		OPEN_LUA_LIB(CLASS) 
// #define DEFINE_LUA_CLASS_LIB_NO_INDEX

#define DEFINE_LUA_CLASS_NO_CTOR(TYPE, CLASS, SUPER_CLASS) \
	DEFINE_LUA_CLASS_LIB(TYPE, CLASS, SUPER_CLASS) \
		LUA_ENTRY_##TYPE##__gc_DESTRUCTOR(CLASS) \
		LUA_ENTRY_CLASS__isnewindexable_FALSE \
		LUA_ENTRY_##TYPE##__newindex_ERROR_AUTO(CLASS) \
		LUA_ENTRY_CLASS__setmetatable_USERDATA \
		LUA_ENTRY_##TYPE##__tostring_AUTO(CLASS)  
// #define DEFINE_LUA_CLASS_NO_CTOR

/**
\def DEFINE_LUA_CLASS_NO_CTOR_NO_DTOR
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
\note when pushing an object into %Lua, it might not be because the 
object was created by a call to ObjectOrientedParadigm.new() in %Lua.  In this
case, if the class has a extra methods defined in %Lua, especially a 'construct'
method, that %Lua only properties of the object must be initialized the first
time the object is pushed into %Lua

\warning when called at this time (somewhere NOT from a new() call) NO ARGUMENTS WILL 
BE PASSED IN TO THE FUNCTION
*/
#define DEFINE_LUA_CLASS_PUSH_FUNCTION(CLASS) \
	sint lua_extension::push(lua_State* L, CLASS * value) \
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
		return 1; \
	} 
// #define DEFINE_LUA_PUSH_FUNCTION(CLASS) 

/**
empty for now, but makes things easier
*/
#define DEFINE_LUA_EXTENDABLE__tostring(CLASS)
// #define DEFINE_LUA_EXTENDABLE__tostring

/**
empty for now, but makes things easier
*/
#define DEFINE_LUA_EXTENDABLE_AUTO_METAMETHODS(CLASS) 
// #define DEFINE_LUA_EXTENDABLE_AUTO_METAMETHODS(CLASS) 

/**
empty for now, but makes things easier
*/
#define DEFINE_LUA_EXTENDABLE_PUSH_FUNCTION(CLASS) 
// #define DEFINE_LUA_EXTENDABLE_PUSH_FUNCTION(CLASS) 


#define DEFINE_LUA_FUNC__index_PUBLIC_MEMBERS(CLASS) \
	LUA_FUNC(##CLASS##__index) \
	{ \
		const schar* k = to<const schar*>(L, -1); \
		const AllPublic& t = to<const AllPublic&>(L, -2); 
// #define DEFINE_LUA_FUNC__index_PUBLIC_MEMBERS

#define DEFINE_LUA_FUNC__newindex_PUBLIC_MEMBERS(CLASS) \
	LUA_FUNC(##CLASS##__newindex) \
	{ \
	const schar* k = to<const schar*>(L, -2); \
	CLASS& t = to<CLASS&>(L, -3); 
// #define DEFINE_LUA_FUNC__newindex_PUBLIC_MEMBERS

/** 
\def DEFINE_LUA_LIBRARY
Begin a library definition for registration
This method is ideal for static classes or libraries.
\note compile-time directive
\note highly recommended to precede END_LUA_LIBRARY
\param name name of the library without string delimiters
*/
#define DEFINE_LUA_LIBRARY(NAME) \
	OPEN_LUA_NS(NAME) \
		OPEN_LUA_LIB(NAME)				
// #define DEFINE_LUA_LIBRARY

#define DEFINE_LUA_OPENER(NAME) \
	sint key(lua_State* L) \
	{ \
		luaL_register(L, #NAME, NAME##_library); \
		return 1; \
	} 

#define DEFINE_LUA_OPENER_CLASS(CLASS, SUPER_CLASS) \
	sint key(lua_State* L) \
	{ \
		luaL_register(L, #CLASS, CLASS##_library); \
		lua_extension::declareLuaClass(L, #CLASS, #SUPER_CLASS); \
		return 1; \
	} 

#define DEFINE_LUA_OPENER_EXTENSIBLE(NAME) \
	sint key(lua_State* L) \
	{ \
		luaL_register(L, #NAME, NAME##_library); \
		Lua::nilLoadedStatus(L, #NAME); \
		return 1; \
	} 

#define DEFINE_LUAEXTENDABLE_PROXY_DEFAULT_FUNCTIONS(CLASS) \
	DEFINE_DEFAULT_TOSTRING(CLASS) \
	DEFINE_DEFAULT_GETCLASSNAME(CLASS) \
	DEFINE_PROXY_SETMETATABLE(CLASS)
// #define DEFINE_LUAEXTENDABLE_USERDATA_DEFAULT_FUNCTIONS(CLASS) 


#define DEFINE_LUAEXTENDABLE_USERDATA_DEFAULT_FUNCTIONS(CLASS) \
	DEFINE_DEFAULT_TOSTRING(CLASS) \
	DEFINE_DEFAULT_GETCLASSNAME(CLASS) \
	DEFINE_USERDATA_SETMETATABLE(CLASS)
// #define DEFINE_PROXY_SETMETATABLE(CLASS) 

#define DEFINE_PROXY_SETMETATABLE(CLASS) \
	virtual sint setMetatable(lua_State* L) \
	{ \
		return setProxyMetatable(L); \
	}
// #define DEFINE_LUAEXTENDABLE_PROXY_DEFAULT_FUNCTIONS(CLASS) 

#if ARGUMENT_ERRORS
#define DEFINE_TO_CLASS_FUNCTIONS(CLASS) \
	namespace lua_extension \
	{ \
		template<> inline CLASS* to< CLASS* >(lua_State* L, int index) \
		{ \
			lua_assertIndexInStack(L, index); \
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
	}
// #define DEFINE_TO_CLASS_FUNCTIONS
#else
#define DEFINE_TO_CLASS_FUNCTIONS(CLASS) \
	namespace lua_extension \
	{ \
		template<> inline const CLASS* to< const CLASS* >(lua_State* L, int index) \
		{ \
			return *static_cast< CLASS** >(lua_touserdata(L, index)); \			
		} \
		template<> inline CLASS* to< CLASS* >(lua_State* L, int index) \
		{ \
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
	}
// #define DEFINE_TO_CLASS_FUNCTIONS
#endif//ARGUMENT_ERRORS

/**
defines functions that can be used to get specific class pointers
back out of %Lua.
\note compile-time directive
*/
#if ARGUMENT_ERRORS
#define DEFINE_TO_LUAEXTENDABLES(CLASS) \
	namespace lua_extension \
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
// #define DEFINE_TO_LUAEXTENDABLES
#else
#define DEFINE_TO_LUAEXTENDABLES(CLASS) \
	namespace lua_extension \
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
// #define DEFINE_TO_LUAEXTENDABLES
#endif//ARGUMENT_ERRORS

#define DEFINE_USERDATA_SETMETATABLE(CLASS) \
	virtual sint setMetatable(lua_State* L) \
	{ \
		return setUserdataMetatable(L); \
	}
// #define DEFINE_USERDATA_SETMETATABLE(CLASS) 

/**
\def END_LUA_CLASS
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
// #define END_LUA_CLASS(CLASS, SUPER_CLASS) 

#define END_LUA_FUNC__index_PUBLIC_MEMBERS(CLASS) \
		lua_getglobal(L, "getClass");	/*s: getClass */ \
		push(L, #CLASS);				/*s: getClass, "CLASS" */ \
		lua_call(L, 1, 1);				/*s: AllPublic */ \
		lua_getfield(L, -1, k);			/*s: AllPublic[k] */ \
		return 1; \
	} 
// #define END_LUA_FUNC__index_PUBLIC_MEMBERS	

#define END_LUA_FUNC__newindex_PUBLIC_MEMBERS(CLASS) \
		return luaL_error(L, "ERROR! nonassignable index %s for " #CLASS , k); \
	}
// #define END_LUA_FUNC__newindex_PUBLIC_MEMBERS	

/** 
\def END_LUA_LIBRARY
end a library definition for registration
\note compile-time directive
\note highly recommended to follow with DEFINE_LUA_LIBRARY
\param name name of the library without string delimiters
*/
#define END_LUA_LIBRARY(NAME) \
		CLOSE_LUA_LIB(NAME) \
		DEFINE_LUA_OPENER(NAME) \
	CLOSE_LUA_NS(NAME)
// #define END_LUA_LIBRARY

/** 
\def END_LUA_LIBRARY_EXTENSIBLE
end a library definition for registration,
adds shortcut to allow extending the library in %Lua with 
the require() function.
\note compile-time directive
\note highly recommended to follow define_lua_library_extensible
\param CLASS name of the library without string delimiters
*/
#define END_LUA_LIBRARY_EXTENSIBLE(CLASS) \
		CLOSE_LUA_LIB(CLASS) \
		DEFINE_LUA_OPENER_EXTENSIBLE(NAME) \
	CLOSE_LUA_NS(CLASS)
// #define END_LUA_LIBRARY_EXTENSIBLE

/** \todo name these all to LUA_ENTRY_CLASS<> */
#define LUA_ENTRY_CLASS__gc_DESTRUCTOR(CLASS) \
	LUA_NAMED_ENTRY("__gc", lua_extension::__gcmetamethod<##CLASS##>) 

#define LUA_ENTRY_CLASS__isExtendableByProxy \
	LUA_NAMED_ENTRY("__isExtendableByProxy", lua_extension::pushTrue) 

#define LUA_ENTRY_CLASS__isnewindexable_TRUE \
	LUA_NAMED_ENTRY("__isnewindexable", lua_extension::pushTrue) 

#define LUA_ENTRY_CLASS__isnewindexable_FALSE \
	LUA_NAMED_ENTRY("__isnewindexable", lua_extension::pushFalse) 

#define LUA_ENTRY_CLASS__new_AUTO(CLASS) \
	LUA_NAMED_ENTRY("__new", lua_extension::__new<##CLASS##>) 

#define LUA_ENTRY_CLASS__newindex_ERROR_AUTO(CLASS) \
	LUA_NAMED_ENTRY("__newindex", lua_library_##CLASS##::__newindexError##CLASS) 

#define LUA_ENTRY_CLASS__setmetatable_PROXY \
	LUA_NAMED_ENTRY("__setmetatable", lua_extension::setProxyMetatable) 

#define LUA_ENTRY_CLASS__setmetatable_USERDATA \
	LUA_NAMED_ENTRY("__setmetatable", lua_extension::setUserdataMetatable) 

#define LUA_ENTRY_CLASS__tostring_AUTO(CLASS) \
	LUA_NAMED_ENTRY("__tostring", __tostring##CLASS)

/** 
\def LUA_ENTRY
add a lua method to a definition by the same name 
\note compile-time directive
\param function a lua_function
*/
#define LUA_ENTRY(function) \
	{(#function), (function)}, 

// #define LUA_ENTRY
#define LUA_ENTRY_EXTENDABLE__gc_DESTRUCTOR(CLASS) \
	LUA_NAMED_ENTRY("__gc", LuaExtendable::__gcmetamethod)

#define LUA_ENTRY_EXTENDABLE__newindex_ERROR_AUTO(CLASS) \
	LUA_NAMED_ENTRY("__newindex", LuaExtendable::__newindexError) 

#define LUA_ENTRY_EXTENDABLE__tostring_AUTO(CLASS) \
	LUA_NAMED_ENTRY("__tostring", LuaExtendable::__tostring) 

/**
the sentinel entry in a lua library
*/
#define LUA_FINAL_ENTRY \
	{NULL, NULL}
// #define LUA_FINAL_ENTRY

/** 
\def LUA_FUNC
Declares a (static) lua function.  Declares a function that
takes a single lua_State argument, and returns an integer,
the number of arguments it has added to the stack.
\note compile-time directive
\param name name of the function that will be declared, without string delimiters
*/
#define LUA_FUNC(name) \
	sint name##(lua_State* L)
// #define LUA_FUNC

/**  
\def LUA_NAMED_ENTRY
add a lua method to a definition by a different name 
\note compile-time directive
\param name a string delimited name
\param function a lua_function
*/
#define LUA_NAMED_ENTRY(name, function)	\
	{(name), (function)}, 
// #define LUA_NAMED_ENTRY

#define OPEN_LUA_LIB(NAME) \
	static const luaL_reg NAME##_library[] = \
	{	/* begin function list */

#define OPEN_LUA_NS(NAME) \
	namespace lua_library_##NAME \
	{ 

/** 
\def REGISTER_LUA_LIBRARY
register a library with a lua state 
\warning registration MUST be done in dependency order, or the behavior
is undefined
\warning registration MUST be done in class hierarchical order, or the 
behavior is undefined
\note run-time directive
\param lua_object_ptr is class Lua, not struct lua_State 
\param module of the library without string delimiters
*/
#define REGISTER_LUA_LIBRARY(lua_object_ptr, module) \
	lua_object_ptr->openLibrary(lua_library_##module::key);		
// #define REGISTER_LUA_LIBRARY

/** @} */

namespace lua_extension 
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
	return pushRegisteredClass(L, new CLASS());
}

/**
experimental, trying to get the local proxy table on the top of the 
stack
*/
sint
	__getProxy(lua_State* L);

/**
__newindex method for the metatable of a class exposed to %Lua 
via the proxy method that will allow it to be assigned new fields
*/
sint 
	__newindexProxy(lua_State* L);

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
helps set a userdata metatable from script, this is a exact C version of the function in %Lua,
since you can't call setmetatable on a userdata value in %Lua.
\warning USE JUDICIOUSLY.  This violates some safety precedence in %Lua.
*/
sint
	setUserdataMetatable(lua_State* L);
} // namespace lua_extension 

/** @} */

/*
\todo if ever desired, finish looking into this:


struct AllPublic
{
sint 
one;
bool 
two;
sreal 
three;
}

DECLARE_LUA_CLASS(AllPublic);

LUA_FUNC(AllPublic__index)
{
const schar* k = to<const schar*>(L, -1);
const AllPublic& t = to<const AllPublic&>(L, -2);

if (!strcmp(k,"one")) return push(L, t.one);
if (!strcmp(k,"two")) return push(L, t.two);
if (!strcmp(k,"three")) return push(L, t.three);

lua_getglobal(L, "getClass");	//s: getClass
push(L, "AllPublic");			//s: getClass, "AllPublic"
lua_call(L, 1, 1);				//s: AllPublic
lua_getfield(L, -1, key);		//s: AllPublic[key]
return 1;
}

LUA_FUNC(AllPublic__newindex)
{
const schar* k = to<const schar*>(L, -2);
const AllPublic& t = to<const AllPublic&>(L, -3);

if (!strcmp(k,"one")) { t.one = to<sint>(L, -1); return 0; }
if (!strcmp(k,"two")) { t.two = to<bool>(L, -1); return 0; }
if (!strcmp(k,"three")) { t.three = to<sreal>(L, -1); return 0; }

return luaL_error(L, "ERROR! nonassignable index %s for AllPublic", k);
}

DEFINE_LUA_##TYPE##_PUSH_FUNCTION(CLASS) \
OPEN_LUA_NS(CLASS) \
DEFINE_LUA_##TYPE##_AUTO_METAMETHODS(CLASS) \
OPEN_LUA_LIB(CLASS)
LUA_ENTRY_##TYPE##__gc_DESTRUCTOR(CLASS) \
LUA_ENTRY_CLASS__isnewindexable_FALSE \
LUA_ENTRY_CLASS__new_AUTO(CLASS) \
LUA_ENTRY_##TYPE##__newindex_ERROR_AUTO(CLASS) \
LUA_ENTRY_CLASS__setmetatable_USERDATA \
LUA_ENTRY_##TYPE##__tostring_AUTO(CLASS)  
END_LUA_CLASS(AllPublic, AllPublic)


struct AllPublic
{
sint 
one;
bool 
two;
sreal 
three;
};

DECLARE_LUA_CLASS(AllPublic);

LUA_FUNC(AllPublic_getone)
{
return push(L, to<const AllPublic&>(L, -1).one);
}
LUA_FUNC(AllPublic_setone)
{
to<AllPublic&>(L, -2).one = to<sint>(L, -1);
return 0;
}

LUA_FUNC(AllPublic_gettwo)
{
return push(L, to<const AllPublic&>(L, -1).two);
}
LUA_FUNC(AllPublic_settwo)
{
to<AllPublic&>(L, -2).two = to<bool>(L, -1);
return 0;
}

LUA_FUNC(AllPublic_getthree)
{
return push(L, to<const AllPublic&>(L, -1).three);
}
LUA_FUNC(AllPublic_setthree)
{
to<AllPublic&>(L, -2).three = to<sreal>(L, -1);
return 0;
}

DEFINE_LUA_CLASS(CLASS, AllPublic, AllPublic)
LUA_NAMED_ENTRY("getOne", AllPublic_getone)
LUA_NAMED_ENTRY("setOne", AllPublic_setone)
END_LUA_CLASS(AllPublic, AllPublic)


*/


#endif//LUAEXTENSIBILITY_H

