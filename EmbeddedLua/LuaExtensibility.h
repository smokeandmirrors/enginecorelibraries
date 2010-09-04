#pragma once
#ifndef LUAREGISTRATION_H
#define LUAREGISTRATION_H
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
	int luaopen_example(lua_State* L);
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

	int luaopen_example(lua_State* L)
	{
		luaL_register(L, "example", example_library);
		return 1;
	}
}

// to use the library
register_lua_library(Lua, example)
// would generate:
Lua->openLibrary(lua_library_example::luaopen_example);
@endcode

\note REGISTRATION MUST BE DONE IN DEPENDENCY ORDER.
*/


/**
@todo make namespaces
@todo make decisions about:
	when to call:
		createGlobalClassMetable(), immediately after registering non-extensibles?
	how to do inheritance? 
		through the declaration, or the registration?
	using flags to destinguish between what types exposition methods we would use
	and then using those flags in the namespace?
	typedef super?  how about the base class?
	
**/
struct lua_State;
struct lua_Debug;

typedef int (*lua_function)(lua_State* L);

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

extern unsigned int		testing; 
extern const char*		lua_metamethodNames[NUM_LUA_METAMETHODS];

/**
\def lua_require 
a macro fuction to call require from C, mostly for use in 
other macros
*/
#define lua_require(module) \
	lua_getglobal(L, "require"); \
	lua_pushstring(L, #module); \
	lua_pcall(L, 1, 0, 0); 
// end #define lua_require(module)

/**
\def lua_nilLoadedStatus
macro to help nil the loaded status of a module, mostly 
for use in allowing libraries registered with luaL_register
to be extended in %Lua with the use of the %Lua require function
*/
#define lua_nilLoadedStatus(module) \
	lua_getglobal(L, "package"); \
	lua_getfield(L, -1, "loaded"); \
	lua_pushnil(L); \
	lua_setfield(L, -2, module); \
	lua_pop(L, 1); \
// end #define lua_nilLoadedStatus(module)

/** 
\def lua_func
Declares a (static) lua function.  Declares a function that
takes a single lua_State argument, and returns an integer,
the number of arguments it has added to the stack.

\param name name of the function that will be declared, 
without string delimiters
*/
#define lua_func(name) \
	static int name##(lua_State* L)
// end #define lua_func

/** 
\def declare_lua_library
declare a library for shared inclusion 
\param name name of the library without string delimiters
*/
#define declare_lua_library(name) \
	struct lua_State; \
	namespace lua_library_##name \
	{ \
		int luaopen_##name(lua_State* L); \
	}; // end namespace lua_library_##name
// end #define begin_lua_library_declaration

/**
\def declare_lua_extendable
*/
#define declare_lua_extendable(class_name) \
	declare_lua_library(name) \
	namespace LuaExtension \
	{ \
		inline class_name* to(lua_State* L, int index, Differentiator<class_name>&) \
		{ \
			return static_cast<class_name*>(to<LuaExtendable*>(L, index)); \
		} \
	}
// end #define declare_lua_extendable

/** 
\def lua_entry
add a lua method to a definition by the same name 
\param function a lua_function
*/
#define lua_entry(function) \
			{(#function),	(function)}, \
// end #define add_nlua_function

/**  
\def lua_named_entry
add a lua method to a definition by a different name 
\param name a string delimited name
\param function a lua_function
*/
#define lua_named_entry(name, function)	\
			{(name),	(function)}, \
// end #define lua_named_entry

/** 
\def define_lua_library
begin a library definition for registration
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
\note highly recommended to follow with define_lua_library
\param name name of the library without string delimiters
*/
#define end_lua_library(name) \
			{NULL,		NULL} \
		};	/* end function list */ \
		int luaopen_##name(lua_State* L) \
		{ \
			luaL_register(L, #name, name##_library); \
			return 1; \
		} \
	}; // end namespace lua_library_##name
// end #define end_lua_library

/** 
\def define_lua_library_extensible
begin a library definition for registration, and allow
it to be extended in lua using the %Lua require function
\note highly recommended to precede end_lua_library_extensible
\param name name of the library without string delimiters
*/
#define define_lua_library_extensible(name) \
	namespace lua_library_##name \
	{ \
		static const luaL_reg name##_library[] = \
		{	/* begin function list */						
// end #define define_lua_library_extensible

/** 
\def end_lua_library_extensible
end a library definition for registration
\note highly recommended to follow with define_lua_library_extensible
\param name name of the library without string delimiters
*/
#define end_lua_library_extensible(name) \
			{NULL,		NULL} \
		};	/* end function list */ \
		int luaopen_##name(lua_State* L) \
		{ \
			luaL_register(L, #name, name##_library); \
			lua_nilLoadedStatus(#name); \
			return 1; \
		} \
	}; // end namespace lua_library_##name
// end #define end_lua_library_extensible

/**
\def define_lua_class
define a lua library around a class, so that instances of the 
class can be created or controlled in lua
\param derived_class the class to expose
\param super_class the parent class of the derived_class, if there is 
no parent class, simply supply the derived class again
*/
#define define_lua_class(derived_class, super_class) \
	define_lua_library(derived_class)
// end #define define_lua_class_defaults

/**
\def end_lua_class
*/
#define end_lua_class(derived_class, super_class) \
			{NULL,		NULL} \
		};	/* end function list */ \
		int luaopen_##derived_class(lua_State* L) \
		{ \
			luaL_register(L, #derived_class, derived_class##_library); \
			createGlobalClassMetatable(L, #derived_class, #super_class); \
			return 1; \
		} \
	}; // end namespace lua_library_##name
// end #define end_lua_class(derived_class, super_class) 

/**
\def define_lua_class_defaults
*/
#define define_lua_class_defaults(derived, super) \
	namespace lua_library_##derived \
	{ \
		int lua_new##derived(lua_State* L) \
		{ \
			pushRegisteredClass(L, new derived()); \
			return 1; \
		} \
		static const luaL_reg derived##_library[] = \
		{ \
			lua_named_entry("new", lua_new##derived) \
			lua_named_entry("__gc", __gcLuaExtendable) \
			lua_named_entry("__tostring", __tostringLuaExtendable)	
// end #define_lua_class_defaults

/**
\def end_lua_class_defaults
*/
#define end_lua_class_defaults(derived_class, super_class) \
			{NULL,		NULL} \
		};	/* end function list */ \
		int luaopen_##derived_class(lua_State* L) \
		{ \
			luaL_register(L, #derived_class, derived_class##_library); \
			createGlobalClassMetatable(L, #derived_class, #super_class); \
			lua_require(#derived_class) \
			lua_nilLoadedStatus(#derived_class) \
			return 1; \
		} \
	}; // end namespace lua_library_##name
// end #define end_lua_class_defaults(derived_class, super_class) 

/**
\def define_lua_class_by_proxy_defaults
begin a library definition for registration via lua proxy table,
and use the default "new", "setmetatable", "__gc" & "__tostring" methods
\note highly recommended to precede end_lua_library
*/
#define define_lua_class_by_proxy_defaults(derived_class, super_class) \
	define_lua_class_defaults(derived_class, super_class) \
		lua_named_entry("setmetatable", setmetatableLuaExtendable)
// end #define define_lua_class_by_proxy_defaults

#define end_lua_class_by_proxy_defaults(derived_class, super_class) \
			{NULL,		NULL} \
		};	/* end function list */ \
		int luaopen_##derived_class(lua_State* L) \
		{ \
			luaL_register(L, #derived_class, derived_class##_library); \
			lua_require(#derived_class) \
			lua_nilLoadedStatus(#derived_class) \
			return 1; \
		} \
	}; // end namespace lua_library_##name
// end #define end_lua_class_by_proxy_defaults
	

/** 
\def register_lua_library
register a library with a lua state 
\note registration MUST be done in dependency order, or the behavior
is undefined
\param lua_object is class @link Lua @endlink, not struct lua_State 
\param name of the library without string delimiters
*/
#define register_lua_library(lua_object, module) \
	lua_object->openLibrary(lua_library_##module::luaopen_##module);			
// end #define register_lua_library

/**
@interface LuaExtendable
Makes it easier to define metamethods on exposed C++ classes.
*/
class LuaExtendable 
{
public:
	/** defined pure virtual constructor */
	virtual					~LuaExtendable(void)=0 {} // pure virtual copy ctr(), op=()?
	virtual int				setMetatable(lua_State* L)=0;
	virtual const char*		toString(void)=0;
}; // class LuaExtendable

/**
__gc method for the metatable of a class exposed to %Lua by and extending a 
Lua class declared with this system
*/
int __gcLuaExtendable(lua_State* L);

/**
__newindex method for the metatable of a class exposed to %Lua by and extending a 
Lua class declared with this system
*/
int __newindexProxy(lua_State* L);

/**
__tostring method for the metatable of a class exposed to %Lua by and extending a 
Lua class declared with this system
*/
int __tostringLuaExtendable(lua_State* L);

/**
the timing of this is critical.  if executed before a %Lua extension file is loaded
it means that the metamethods redefined in %Lua will not be executed depending
on what method of exposure to %Lua used on the class
*/
void createGlobalClassMetatable(lua_State* L, const char* class_name, const char* super_class_name);

/**
*/
int createGlobalClassMetatable(lua_State* L);

/**
@todo follow up for direct wraps: int setmetatableFromGlobalClass(lua_State* L);
*/

/**
print the string to the %Lua output
*/
void printToLua(lua_State* L, const char* string);

/**
helper function for pushing a class to %Lua an preserving the ability
to compare userdata and use them as equivalent table keys
@see comments in the implementation of void Lua::initializeUserdataStorage(void)
*/
int pushRegisteredClass(lua_State* L, void* pushee);

/** 
helps set a LuaExtendable metatable from script
@warning USE JUDICIOUSLY.  This violates some safety precedence in %Lua. 
*/
int setmetatableLuaExtendable(lua_State* L);

/** 
helps set a userdata metatable from script
@warning USE JUDICIOUSLY.  This violates some safety precedence in %Lua. 
*/
int setDefaultMetatableProxy(lua_State* L);

} // namespace LuaExtension 

#endif//LUAREGISTRATION_H