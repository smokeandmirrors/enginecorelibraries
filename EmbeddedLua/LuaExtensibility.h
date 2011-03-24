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
	sint4 luaopen_example(lua_State* L);
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

	sint4 luaopen_example(lua_State* L)
	{
		luaL_register(L, "example", example_library);
		return 1;
	}
}

// to use the library
register_lua_library(Lua, example);
// would generate:
Lua->openLibrary(lua_library_example::luaopen_example);
\endcode

\warning REGISTRATION MUST BE DONE IN DEPENDENCY ORDER.
\warning THIS FUNCTIONALITY IS NOT THREAD SAFE.

*/
#include "Build.h"

struct lua_State;
struct lua_Debug;

/**
\defgroup LuaExtension Lua Extension
macros, classes and functions to 
aid embedding %Lua in an executable, and exposing libraries and classes
for use in %Lua.
@{
*/

typedef sint4 (*lua_function)(lua_State* L);

namespace lua_extension 
{

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
\def LUA_FUNC
Declares a (static) lua function.  Declares a function that
takes a single lua_State argument, and returns an integer,
the number of arguments it has added to the stack.
\note compile-time directive
\param name name of the function that will be declared, without string delimiters
*/
#define LUA_FUNC(name) \
	static sint4 name##(lua_State* L)
// end #define LUA_FUNC

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
		sint4 key(lua_State* L); \
	}; // end namespace lua_library_##name
// end #define begin_lua_library_declaration

/** 
\def LUA_ENTRY
add a lua method to a definition by the same name 
\note compile-time directive
\param function a lua_function
*/
#define LUA_ENTRY(function) \
			{(#function),	(function)}, \
// end #define add_nlua_function

/**  
\def LUA_NAMED_ENTRY
add a lua method to a definition by a different name 
\note compile-time directive
\param name a string delimited name
\param function a lua_function
*/
#define LUA_NAMED_ENTRY(name, function)	\
			{(name),	(function)}, \
// end #define LUA_NAMED_ENTRY

#define LUA_FINAL_ENTRY {NULL, NULL}

/** 
\def DEFINE_LUA_LIBRARY
Begin a library definition for registration
This method is ideal for static classes or libraries.
\note compile-time directive
\note highly recommended to precede END_LUA_LIBRARY
\param name name of the library without string delimiters
*/
#define DEFINE_LUA_LIBRARY(name) \
	namespace lua_library_##name \
	{ \
		static const luaL_reg name##_library[] = \
		{	/* begin function list */						
// end #define DEFINE_LUA_LIBRARY

/** 
\def END_LUA_LIBRARY
end a library definition for registration
\note compile-time directive
\note highly recommended to follow with DEFINE_LUA_LIBRARY
\param name name of the library without string delimiters
*/
#define END_LUA_LIBRARY(name) \
			LUA_FINAL_ENTRY \
		};	/* end function list */ \
		sint4 key(lua_State* L) \
		{ \
			luaL_register(L, #name, name##_library); \
			return 1; \
		} \
	}; // end namespace lua_library_##name
// end #define END_LUA_LIBRARY

/** 
\def END_LUA_LIBRARY_EXTENSIBLE
end a library definition for registration,
addes shortcut to allow extending the library in %Lua with 
the require() function.
\note compile-time directive
\note highly recommended to follow define_lua_library_extensible
\param name name of the library without string delimiters
*/
#define END_LUA_LIBRARY_EXTENSIBLE(name) \
			LUA_FINAL_ENTRY \
		};	/* end function list */ \
		sint4 key(lua_State* L) \
		{ \
			luaL_register(L, #name, name##_library); \
			Lua::nilLoadedStatus(L, #name); \
			return 1; \
		} \
	}; // end namespace lua_library_##name
// end #define END_LUA_LIBRARY_EXTENSIBLE

/**
defines functions that can be used to get specific class pointers
back out of %Lua.
\note compile-time directive

*/
#if ARGUMENT_ERRORS
#define DEFINE_TO_LUAEXTENDABLES(Class) \
	namespace lua_extension \
	{ \
		template<> inline Class* to< Class* >(lua_State* L, sint4 index) \
		{ \
			Class* object = dynamic_cast< Class* >(to< LuaExtendable* >(L, index)); \
			if (object) \
				return object; \
			luaL_error(L, "argument type error! argument at index %d: expected: %s actual: unknown", index, #Class); \
			return NULL; \
		} \
		template<> inline const Class* to< const Class* >(lua_State* L, sint4 index) \
		{ \
			return to< Class* >(L, index); \
		} \
		template<> inline Class& to< Class& >(lua_State* L, sint4 index) \
		{ \
			Class* object = to< Class* >(L, index); \
			assert(object); \
			return *object; \
		} \
		template<> inline const Class& to< const Class& >(lua_State* L, sint4 index) \
		{ \
			Class* object = to< Class* >(L, index); \
			assert(object); \
			return *object; \
		} \
	}
// end #define DEFINE_TO_LUAEXTENDABLES
#else
#define DEFINE_TO_LUAEXTENDABLES(Class) \
	namespace lua_extension \
	{ \
		template<> inline Class* to< Class* >(lua_State* L, sint4 index) \
		{ \
			return static_cast< Class* >(to<LuaExtendable*>(L, index)); \
		} \
		template<> inline const Class* to< const Class* >(lua_State* L, sint4 index) \
		{ \
			return to< Class* >(L, index); \
		} \
		template<> inline Class& to<Class&>(lua_State* L, sint4 index) \
		{ \
			return *to< Class* >(L, index); \
		} \
		template<> inline const Class& to< const Class& >(lua_State* L, sint4 index) \
		{ \
			return *to< Class* >(L, index); \
		} \
	}
// end #define DEFINE_TO_LUAEXTENDABLES
#endif//ARGUMENT_ERRORS

/**
\def DECLARE_LUA_LUAEXTENDABLE
Declares a library around a class that implements
the LuaExtendable interface.
\note compile-time directive
*/
#define DECLARE_LUA_LUAEXTENDABLE(Class) \
	DECLARE_LUA_LIBRARY(Class) \
	DEFINE_TO_LUAEXTENDABLES(Class) 
// end #define DECLARE_LUA_LUAEXTENDABLE


/**
\def DECLARE_LUA_LUAEXTENDABLE_NS
Declares a library around a class in a namespace that implements
the LuaExtendable interface.
\note compile-time directive
*/
#define DECLARE_LUA_LUAEXTENDABLE_NS(ns, Class) \
	DECLARE_LUA_LIBRARY(Class)	\
	DEFINE_TO_LUAEXTENDABLES(ns::Class)

/**
\def DEFINE_LUA_LUAEXTENDABLE
Define a %Lua library around a class, so that instances of the 
class can be created or controlled in %Lua. This also exposes simple 
userdata pointers with all associated C++ and Lua methods, but it doesn't 
create any ability to added new %Lua fields.  But, this is often never needed.
This method would be preferable for objects like vectors.
\param Class the name of the Class being exposed, with no delimiters
\param SuperClass with no delimiters, the parent class of the LuaExtendable,
or the same if it has no parent class
\note compile-time directive
\note highly recommended to precede an END_LUA_LUAEXTENDABLE
\note adds a __gc, calls the destructor on the LuaExtendable
\note adds a __isnewindexable, returns false
\note adds a __new, calls the no-args constructor
\note adds a __newindex, throws a %Lua error
\note adds a __setmetatable, calls setMetatable defined by the LuaExtendable
\note adds a __tostring, calls toString defined by the LuaExtendable
*/
#define DEFINE_LUA_LUAEXTENDABLE(Class, SuperClass) \
	namespace lua_library_##Class \
	{ \
		sint4 lua_new##Class(lua_State* L) \
		{ \
			pushRegisteredClass(L, new Class()); \
			return 1; \
		} \
		static const luaL_reg Class##_library[] = \
		{ \
			LUA_NAMED_ENTRY("__gc", LuaExtendable::__gcmetamethod) \
			LUA_NAMED_ENTRY("__isnewindexable", lua_extension::pushFalse) \
			LUA_NAMED_ENTRY("__new", lua_new##Class) \
			LUA_NAMED_ENTRY("__newindex", LuaExtendable::__newindexError) \
			LUA_NAMED_ENTRY("__setmetatable", LuaExtendable::callSetMetatable) \
			LUA_NAMED_ENTRY("__tostring", LuaExtendable::__tostring) 
// end #DEFINE_LUA_LUAEXTENDABLE

/**
\def DEFINE_LUA_LUAEXTENDABLE_NOCTOR
Define a %Lua library around a class, so that instances of the 
controlled in %Lua. This also exposes simple userdata pointers with all 
associated C++ and Lua methods, but it doesn't create any ability to added 
new %Lua fields.  It also doesn't supply any constructor or destructor exposure
to %Lua This could be used for objects like singletons.
\param Class the name of the Class being exposed, with no delimiters
\param SuperClass with no delimiters, the parent class of the LuaExtendable,
or the same if it has no parent class
\note compile-time directive
\note highly recommended to precede an END_LUA_LUAEXTENDABLE
\note adds a __isnewindexable, returns false
\note adds a __newindex, throws a %Lua error
\note adds a __setmetatable, calls setMetatable defined by the LuaExtendable
\note adds a __tostring, calls toString defined by the LuaExtendable
*/
#define DEFINE_LUA_LUAEXTENDABLE_NOCTOR(Class, SuperClass) \
	namespace lua_library_##Class \
	{ \
		static const luaL_reg Class##_library[] = \
		{ \
			LUA_NAMED_ENTRY("__isnewindexable", lua_extension::pushFalse) \
			LUA_NAMED_ENTRY("__newindex", LuaExtendable::__newindexError) \
			LUA_NAMED_ENTRY("__setmetatable", LuaExtendable::callSetMetatable) \
			LUA_NAMED_ENTRY("__tostring", LuaExtendable::__tostring) 
// end #DEFINE_LUA_LUAEXTENDABLE

/**
\def DEFINE_LUA_LUAEXTENDABLE_BY_PROXY
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
\param Class the name of the Class being exposed, with no delimiters
\param SuperClass with no delimiters, the parent class of the LuaExtendable,
or the same if it has no parent class
\note compile-time directive
\note highly recommended to precede an END_LUA_LUAEXTENDABLE
\note adds a __gc, calls the destructor on the LuaExtendable
\note adds a __isExtendableByProxy, (used in %Lua) returns true
\note adds a __isnewindexable, returns false
\note adds a __new, calls the no-args constructor
\note adds a __setmetatable, calls setMetatable defined by the LuaExtendable
\note adds a __tostring, calls toString defined by the LuaExtendable
*/
#define DEFINE_LUA_LUAEXTENDABLE_BY_PROXY(Class, SuperClass) \
	namespace lua_library_##Class \
	{ \
		sint4 lua_new##Class(lua_State* L) \
		{ \
			pushRegisteredClass(L, new Class()); \
			return 1; \
		} \
		static const luaL_reg Class##_library[] = \
		{ \
			LUA_NAMED_ENTRY("__gc", LuaExtendable::__gcmetamethod) \
			LUA_NAMED_ENTRY("__isExtendableByProxy", lua_extension::pushTrue) \
			LUA_NAMED_ENTRY("__isnewindexable", lua_extension::pushTrue) \
			LUA_NAMED_ENTRY("__new", lua_new##Class) \
			LUA_NAMED_ENTRY("__setmetatable", LuaExtendable::callSetMetatable) \
			LUA_NAMED_ENTRY("__tostring", LuaExtendable::__tostring) 
// end #define DEFINE_LUA_LUAEXTENDABLE_BY_PROXY

/**
\def END_LUA_LUAEXTENDABLE
This closes out the luaL_reg and defines the library opener function, 
which will register the exposed function and declare a %Lua class
via ObjectOrientedParadgim.lua.
\param Class the name of the Class being exposed, with no delimiters
\param SuperClass with no delimiters, the parent class of the LuaExtendable,
or the same if it has no parent class
\note compile-time directive
\note highly recommended to follow any form of DEFINE_LUA_LUAEXTENDABLE
*/
#define END_LUA_LUAEXTENDABLE(Class, SuperClass) \
			LUA_FINAL_ENTRY \
		};	/* end function list */ \
		sint4 key(lua_State* L) \
		{ \
			luaL_register(L, #Class, Class##_library); \
			LuaExtendable::declareLuaClass(L, #Class, #SuperClass); \
			return 1; \
		} \
	}; // end namespace lua_library_##name
// end #define END_LUA_LUAEXTENDABLE(derived_class, super_class) 

/** 
\def register_lua_library
register a library with a lua state 
\warning registration MUST be done in dependency order, or the behavior
is undefined
\warning registration MUST be done in class hierarchical order, or the 
behavior is undefined
\note run-time directive
\param lua_object_ptr is class Lua, not struct lua_State 
\param module of the library without string delimiters
*/
#define register_lua_library(lua_object_ptr, module) \
	lua_object_ptr->openLibrary(lua_library_##module::key)		
// end #define register_lua_library

#define INLINE_DEFAULT_TOSTRING(Class) \
	virtual const sint1* toString(void) \
	{ \
		return "This is a " #Class; \
	}
// #define INLINE_DEFAULT_TOSTRING(Class) 

#define INLINE_DEFAULT_GETCLASSNAME(Class) \
	virtual const sint1* getClassName(void) const \
	{ \
		return #Class; \
	}
// #define INLINE_DEFAULT_GETCLASSNAME(Class) 

#define INLINE_PROXY_SETMETATABLE(Class) \
	virtual sint4 setMetatable(lua_State* L) \
	{ \
		return setProxyMetatable(L); \
	}
// #define INLINE_PROXY_SETMETATABLE(Class) 

#define INLINE_USERDATA_SETMETATABLE(Class) \
	virtual sint4 setMetatable(lua_State* L) \
	{ \
		return setUserdataMetatable(L); \
	}
// #define INLINE_USERDATA_SETMETATABLE(Class) 
	
#define INLINE_LUAEXTENDABLE_PROXY_DEFAULT_FUNCTIONS(Class) \
	INLINE_DEFAULT_TOSTRING(Class) \
	INLINE_DEFAULT_GETCLASSNAME(Class) \
	INLINE_PROXY_SETMETATABLE(Class) 
// #define INLINE_LUAEXTENDABLE_PROXY_DEFAULT_FUNCTIONS(Class) 

#define INLINE_LUAEXTENDABLE_USERDATA_DEFAULT_FUNCTIONS(Class) \
	INLINE_DEFAULT_TOSTRING(Class) \
	INLINE_DEFAULT_GETCLASSNAME(Class) \
	INLINE_USERDATA_SETMETATABLE(Class) 
// #define INLINE_LUAEXTENDABLE_USERDATA_DEFAULT_FUNCTIONS(Class) 

/** @} */

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
	__gc method for the metatable of a class exposed to %Lua.
	Using this will cause the C++ object get destroyed when all references to it
	in a lua_State are destroyed.
	*/
	static sint4				__gcmetamethod(lua_State* L);
	/**
	experimental, trying to get the local proxy table on the top of the 
	stack
	*/
	static sint4				__getProxy(lua_State* L);
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
	static sint4				__newindexError(lua_State* L);
	/**
	__newindex method for the metatable of a class exposed to %Lua that will
	allow it to be assigned new fields
	*/
	static sint4				__newindexProxy(lua_State* L);
	/**
	__tostring method for the metatable of a class exposed to %Lua.
	*/
	static sint4				__tostring(lua_State* L);	
	/** 
	helps set a LuaExtendable metatable from script
	\warning USE JUDICIOUSLY.  This violates some safety precedence in %Lua. 
	*/
	static sint4				callSetMetatable(lua_State* L);
	/**
	makes sure that the class is declared declared in the lua OOP system.
	*/
	static void				declareLuaClass(lua_State* L, const sint1* derived, const sint1* super);
	/**
	helps set a userdata metatable from script
	\warning USE JUDICIOUSLY.  This violates some safety precedence in %Lua. 
	*/
	static sint4				setProxyMetatable(lua_State* L);
	/**
	helps set a userdata metatable from script, this is a exact C version of the function in %Lua,
	since you can't call setmetatable on a userdata value in %Lua.
	\warning USE JUDICIOUSLY.  This violates some safety precedence in %Lua.
	*/
	static sint4				setUserdataMetatable(lua_State* L); 
	/** empty dtor */
	virtual					~LuaExtendable(void)=0 {/* empty */};
	/** 
	a function that classes must implement to make them easier to make into well formed
	%Lua classes
	*/
	virtual const sint1*		getClassName(void) const=0;
	/**
	objects of this type will have a metatable assigned to them when pushed into
	a lua_State.  %Lua doesn't allow setmetatable calls on userdata pointers
	from %Lua.  This function will be called via a legal %Lua function call.
	It is mostly easily implemented in terms of one of the static LuaExtendable
	functions.
	*/
	virtual sint4			setMetatable(lua_State* L)=0;
	/**
	a to string function is almost always necessary, since so much of %Lua
	use is simply to make inspection of objects very easy, there is often
	a lot of information about them printed, logged, or rendered
	*/
	virtual const sint1*		toString(void)=0;
}; // class LuaExtendable

/**
completes a %Lua class declaration in case no script accompanied
the class in %Lua.
\ingroup LuaExtension
*/
void completeLuaClassDeclaration(lua_State* L, const sint1* derived, const sint1* super);

/**
print the string to the %Lua output
\ingroup LuaExtension
*/
void printToLua(lua_State* L, const sint1* string);

/**
helper function for pushing a class to %Lua an preserving the ability
to compare userdata and use them as equivalent table keys
\see comments in the implementation of void Lua::initializeUserdataStorage(void)
\ingroup LuaExtension
*/
sint4 pushRegisteredClass(lua_State* L, void* pushee);

/**
helper function for simply registering global native functions to %Lua
\ingroup LuaExtension
*/
void registerGlobalLibrary(lua_State* L);

} // namespace lua_extension 

/** @} */

#endif//LUAEXTENSIBILITY_H