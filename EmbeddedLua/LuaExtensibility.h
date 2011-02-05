#pragma once
#ifndef LUAEXTENSIBILITY_H
#define LUAEXTENSIBILITY_H
/** 
@brief Defines macros to help registration of functions, 
libraries, and classes with lua.

@file 
copyright 2010 Smoke and Mirrors Development
@author Smoke and Mirrors Development
smokeandmirrorsdevelopment@gmail.com
@date 2/23/2010

example:
@code
// for the .h file
declare_lua_library(example)
// would generate: 
struct lua_State;
namespace lua_library_example
{
	sint luaopen_example(lua_State* L);
}

// for the .cpp file 
define_lua_library(example)
	lua_named_entry("Method", method)
	...
end_lua_library(example)
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
register_lua_library(Lua, example);
// would generate:
Lua->openLibrary(lua_library_example::luaopen_example);
@endcode

\note REGISTRATION MUST BE DONE IN DEPENDENCY ORDER.
*/
#include "Build.h"

struct lua_State;
struct lua_Debug;

typedef sint (*lua_function)(lua_State* L);

namespace LuaExtension 
{

enum LUA_EXPOSURE
{
	LUA_EXPOSURE_CLASS				= 1 << 0,
	LUA_EXPOSURE_CREATE_GLOBAL_MT	= 1 << 1,
	LUA_EXPOSURE_DERIVED			= 1 << 2,
	LUA_EXPOSURE_EXTENSIBLE			= 1 << 3,
	LUA_EXPOSURE_LIBRARY			= 1 << 4,
}; // end LUA_EXPOSURE

#define NUM_LUA_METAMETHODS (18)

#if !GOLDMASTER
#define ARGUMENT_ERRORS 1
#endif//!GOLDMASTER

/** 
\def lua_func 

Declares a (static) lua function.  Declares a function that
takes a single lua_State argument, and returns an integer,
the number of arguments it has added to the stack.

\note compile-time directive

\param name name of the function that will be declared, 
without string delimiters
*/
#define lua_func(name) \
	static sint name##(lua_State* L)
// end #define lua_func

/** 
\def declare_lua_library

Declares a %Lua library for shared inclusion.  If used for a class,
instances of the class can be created or controlled in %Lua.  Using this 
method, the programmer is responsible for the whole system of usage of the 
class in %Lua, including memory management.  This method does not interact 
with the module ObjectOrientedParadigm.

\note compile-time directive

\param name name of the library without string delimiters
*/
#define declare_lua_library(name) \
	struct lua_State; \
	namespace lua_library_##name \
	{ \
		sint key(lua_State* L); \
	}; // end namespace lua_library_##name
// end #define begin_lua_library_declaration

/** 
\def lua_entry
add a lua method to a definition by the same name 
\note compile-time directive
\param function a lua_function
*/
#define lua_entry(function) \
			{(#function),	(function)}, \
// end #define add_nlua_function

/**  
\def lua_named_entry
add a lua method to a definition by a different name 
\note compile-time directive
\param name a string delimited name
\param function a lua_function
*/
#define lua_named_entry(name, function)	\
			{(name),	(function)}, \
// end #define lua_named_entry

#define lua_final_entry {NULL, NULL}

/** 
\def define_lua_library

Begin a library definition for registration
This method is ideal for static classes or libraries.

\note compile-time directive
\note highly recommended to precede end_lua_library
\param name name of the library without string delimiters
*/
#define define_lua_library(name) \
	namespace lua_library_##name \
	{ \
		static const luaL_reg name##_library[] = \
		{	/* begin function list */						
// end #define define_lua_library

/** 
\def end_lua_library

end a library definition for registration

\note compile-time directive
\note highly recommended to follow with define_lua_library
\param name name of the library without string delimiters
*/
#define end_lua_library(name) \
			lua_final_entry \
		};	/* end function list */ \
		sint key(lua_State* L) \
		{ \
			luaL_register(L, #name, name##_library); \
			return 1; \
		} \
	}; // end namespace lua_library_##name
// end #define end_lua_library

/** 
\def end_lua_library_extensible

end a library definition for registration,
addes shortcut to allow extending the library in %Lua with 
the require() function.

\note compile-time directive
\note highly recommended to follow define_lua_library_extensible
\param name name of the library without string delimiters
*/
#define end_lua_library_extensible(name) \
			lua_final_entry \
		};	/* end function list */ \
		sint key(lua_State* L) \
		{ \
			luaL_register(L, #name, name##_library); \
			Lua::nilLoadedStatus(L, #name); \
			return 1; \
		} \
	}; // end namespace lua_library_##name
// end #define end_lua_library_extensible

/**
\def declare_lua_LuaExtendable

Declares a library around a class that implements
the LuaExtendable interface.

\note compile-time directive
*/
#if ARGUMENT_ERRORS
#define declare_lua_LuaExtendable(class_name) \
	declare_lua_library(class_name) \
	namespace LuaExtension \
	{ \
		template<> inline class_name* to<class_name*>(lua_State* L, sint index) \
		{ \
			LuaExtendable* ud = to<LuaExtendable*>(L, index); \
			class_name* object = dynamic_cast<class_name*>(ud); \
			if (object) \
				return object; \
			luaL_error(L, "argument type error! #: %d expected: %s actual: unknown", #class_name); \
			return NULL; \
		} \
		template<> inline const class_name* to<const class_name*>(lua_State* L, sint index) \
		{ \
			return to<class_name*>(L, index); \
		} \
		template<> inline class_name& to<class_name&>(lua_State* L, sint index) \
		{ \
			class_name* object = to<class_name*>(L, index); \
			assert(object); \
			return *object; \
		} \
		template<> inline const class_name& to<const class_name&>(lua_State* L, sint index) \
		{ \
			class_name* object = to<class_name*>(L, index); \
			assert(object); \
			return *object; \
		} \
	}
// end #define declare_lua_LuaExtendable
#else
#define declare_lua_LuaExtendable(class_name) \
	declare_lua_library(class_name) \
	namespace LuaExtension \
	{ \
		template<> inline class_name* to<class_name*>(lua_State* L, sint index) \
		{ \
			return static_cast<class_name*>(to<LuaExtendable*>(L, index)); \
		} \
		template<> inline const class_name* to<const class_name*>(lua_State* L, sint index) \
		{ \
			return to<class_name*>(L, index); \
		} \
		template<> inline class_name& to<class_name&>(lua_State* L, sint index) \
		{ \
			return *to<class_name*>(L, index); \
		} \
		template<> inline const class_name& to<const class_name&>(lua_State* L, sint index) \
		{ \
			return *to<class_name*>(L, index); \
		} \
	}
// end #define declare_lua_LuaExtendable
#endif//ARGUMENT_ERRORS

/**
\def define_lua_LuaExtendable

Define a %Lua library around a class, so that instances of the 
class can be created or controlled in %Lua. This also exposes simple 
userdata pointers with all associated C++ and Lua methods, but it doesn't 
create any ability to added new %Lua fields.  But, this is often never needed.
This method would be preferable for objects like vectors.

\note compile-time directive
*/
#define define_lua_LuaExtendable(derived, super) \
	namespace lua_library_##derived \
	{ \
		sint lua_new##derived(lua_State* L) \
		{ \
			pushRegisteredClass(L, new derived()); \
			return 1; \
		} \
		static const luaL_reg derived##_library[] = \
		{ \
			lua_named_entry("__gc", LuaExtendable::__gcmetamethod) \
			lua_named_entry("__new", lua_new##derived) \
			lua_named_entry("__setmetatable", LuaExtendable::callSetMetatable) \
			lua_named_entry("__tostring", LuaExtendable::__tostring) 
// end #define_lua_LuaExtendable

/**
\def end_lua_LuaExtendable
\note compile-time directive
*/
#define end_lua_LuaExtendable(derived_class, super_class) \
			lua_named_entry("__newindex", LuaExtendable::__newindexError) \
			lua_named_entry("__newindexable", LuaExtension::pushFalse) \
			lua_final_entry \
		};	/* end function list */ \
		sint key(lua_State* L) \
		{ \
			luaL_register(L, #derived_class, derived_class##_library); \
			LuaExtendable::declareLuaClass(L, #derived_class, #super_class); \
			return 1; \
		} \
	}; // end namespace lua_library_##name
// end #define end_lua_LuaExtendable(derived_class, super_class) 

/**
\def define_lua_LuaExtendable_by_proxy
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

\note compile-time directive
\note highly recommended to precede end_lua_LuaExtendable_by_proxy
*/
#define define_lua_LuaExtendable_by_proxy(derived_class, super_class) \
	define_lua_LuaExtendable(derived_class, super_class) 
// end #define define_lua_LuaExtendable_by_proxy

/**
\note compile-time directive
*/
#define end_lua_LuaExtendable_by_proxy(derived, super) \
			lua_named_entry("__newindexable", LuaExtension::pushTrue) \
			lua_named_entry("__isExtendableByProxy", LuaExtension::pushTrue) \
			lua_final_entry \
		};	/* end function list */ \
		sint key(lua_State* L) \
		{ \
			luaL_register(L, #derived, derived##_library); \
			LuaExtendable::declareLuaClass(L, #derived, #super); \
			return 1; \
		} \
	}; // end namespace lua_library_##name
// end #define end_lua_LuaExtendable_by_proxy	

/** 
\def register_lua_library
register a library with a lua state 
\note registration MUST be done in dependency order, or the behavior
is undefined
run-time directive
\param lua_object is class @link Lua @endlink, not struct lua_State 
\param name of the library without string delimiters
*/
#define register_lua_library(lua_object_ptr, module) \
	lua_object_ptr->openLibrary(lua_library_##module::key)		
// end #define register_lua_library

#define lua_defaultToString(Class) \
	virtual const char* toString(void) \
	{ \
		return "This is a " #Class; \
	}

#define lua_getClassName(Class) \
	virtual const char* getClassName(void) const \
	{ \
		return #Class; \
	}

#define lua_proxySetMetatableFunction(Class) \
	virtual sint setMetatable(lua_State* L) \
	{ \
		return setProxyMetatable(L); \
	}

#define lua_userdataSetMetatableFunction(Class) \
	virtual sint setMetatable(lua_State* L) \
	{ \
		return setUserdataMetatable(L); \
	}

#define createLuaExtendableUserdataDefaultFunctions(Class) \
	lua_defaultToString(Class) \
	lua_getClassName(Class) \
	lua_userdataSetMetatableFunction(Class) \
	
#define createLuaExtendableProxyDefaultFunctions(Class) \
	lua_defaultToString(Class) \
	lua_getClassName(Class) \
	lua_proxySetMetatableFunction(Class) \
	
/**
@interface LuaExtendable
Makes it easier to define metamethods on exposed C++ classes.
*/
class LuaExtendable 
{
public:
	/**
	__gc method for the metatable of a class exposed to %Lua.
	Using this will cause the C++ object get destroyed when all references to it
	in a lua_State are destroyed.
	*/
	static sint				__gcmetamethod(lua_State* L);
	/**
	experimental, trying to get the local proxy table on the top of the 
	stack
	*/
	static sint				__getProxy(lua_State* L);
	/**
	\note __newindex methods:
	returns true if %Lua code like userdata[k] = v will operate correctly 
	(without errors, and with the expected results) on the userdata pointer
	
	\warning IT IS UP TO YOU TO MAKE SURE THIS IS CORRECT. If userdata[k] = v will 
	work, make sure that your userdata:__newindexable() returns true, otherwise
	make sure userdata:__newindexable() returns false in %Lua (and C/C++). This
	only needs to be true for if userdata[k] = v must work for any non-nil k, and 
	any v.  Vectors for example, which only allow userdata[x,y,z] = v, return
	userdata:__newindexable() returns false

	\note using the given LuaExtendable definitions will make this a lot easier.
	*/
	/**
	__newindex method for the metatable of a class exposed to %Lua that 
	should be configured to the desired error level for the build.
	e.g.: throw errors in a debug build, warn in a release build, etc.
	*/
	static sint				__newindexError(lua_State* L);
	/**
	__newindex method for the metatable of a class exposed to %Lua that will
	allow it to be assigned new fields
	*/
	static sint				__newindexProxy(lua_State* L);
	/**
	__tostring method for the metatable of a class exposed to %Lua.
	*/
	static sint				__tostring(lua_State* L);
	
	/** 
	helps set a LuaExtendable metatable from script
	@warning USE JUDICIOUSLY.  This violates some safety precedence in %Lua. 
	*/
	static sint				callSetMetatable(lua_State* L);
	/**
	makes sure that the class is declared declared in the lua OOP system.
	*/
	static void				declareLuaClass(lua_State* L, const char* derived, const char* super);
	/**
	helps set a userdata metatable from script
	\warning USE JUDICIOUSLY.  This violates some safety precedence in %Lua. 
	*/
	static sint				setProxyMetatable(lua_State* L);
	/**
	helps set a userdata metatable from script, this is a exact C version of the function in %Lua,
	since you can't call setmetatable on a userdata value in %Lua.
	\warning USE JUDICIOUSLY.  This violates some safety precedence in %Lua.
	*/
	static sint				setUserdataMetatable(lua_State* L); 
	/** defined pure virtual constructor */
	virtual					~LuaExtendable(void)=0 {} // pure virtual copy ctr(), op=()?
	virtual const char*		getClassName(void) const=0;
	virtual sint			setMetatable(lua_State* L)=0;
	virtual const char*		toString(void)=0;
}; // class LuaExtendable

/**
completes a %Lua class declaration in case no script accompanied
the class in %Lua.
*/
void completeLuaClassDeclaration(lua_State* L, const char* derived, const char* super);

/**
print the string to the %Lua output
*/
void printToLua(lua_State* L, const char* string);

/**
helper function for pushing a class to %Lua an preserving the ability
to compare userdata and use them as equivalent table keys
@see comments in the implementation of void Lua::initializeUserdataStorage(void)
*/
sint pushRegisteredClass(lua_State* L, void* pushee);

} // namespace LuaExtension 

#endif//LUAEXTENSIBILITY_H