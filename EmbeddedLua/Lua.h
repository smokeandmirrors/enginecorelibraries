#pragma once
#ifndef LUA_H
#define LUA_H
/**
\file Lua.h
This file defines the class Lua
The Lua class encapsulates a lua_Struct.  It will allow for easier
creation of application and library code for %Lua.

\author Smoke and Mirrors Development
\copyright 2010 Smoke and Mirrors Development
\email smokeandmirrorsdevelopment@gmail.com
\date 2/18/2010

\todo expose some ability to modify the require path at runtime
\todo expose some ability to modify the require path at executions start up time
\todo expose some ability to modify the folders searched by the require function
*/

#include <stdlib.h>
#include "LuaExtensibility.h"

namespace LuaExtension 
{

/**
\class Lua
\brief The Lua class encapsulates a lua_Struct.  It will allow for easier
creation of application and library code for %Lua.
*/
class Lua 
{
public:
	/** 
	public [no-args] constructor.
	\param name a string identifier
	\param open_standard_libs if true, the base, package, string, table, and math %Lua libraries will be opened
	\param initialize_userdata_storage if true, the solution to userdata table indexing will be initialized
	*/
	Lua(const char* name="anonymous", bool open_standard_libs=true, bool initialize_userdata_storage=true);
	/** 
	destroys the lua_State and any memory allocated by this object
	*/
	~Lua(void);
	/**
	*/
	int					callProtected(int num_args=0, bool no_return_values=true);
	/**
	loads end executes the string as a lua chunk
	\return the status of the execution
	*/
	bool				doString(const char* chunk, const char* source="native code");
	/**
	\return the number of bytes allocated by the %Lua state
	*/
	size_t				getNumAllocatedBytes() const { return m_bytes; }	
	/**
	\return the string ID of this specific %Lua object
	*/
	const char*			getName(void) const		{ return m_name; }
	/**
	returns the lua_State encapsulated by this class
	*/
	lua_State*			getState(void) const	{ return L; }
	/** 
	sets package.loaded[module] = nil 
	allows for extending of C declared modules by %Lua files in packages
	by the same name
	\param module the name of the (loaded) module
	*/
	void				nilLoadedStatus(const char* module) const;
	/** 
	Opens %Lua library using the lua_function provided
	*/
	void				openLibrary(lua_function key) const;
	/** 
	require() shortcut 
	*/
	bool				require(const char* module) const;
	/** 
	quick, hack console for fast testing 
	*/
	void				runConsole(void) const;
	
protected:
	/**
	pushes a default implementation for __gc && __tostring for
	LuaExtendable classes.
	*/
	void				initializeDefaultProxyMetamethods(void) const;
	/** 
	initializes storage for global C defined classes and metatables
	*/
	void				initializeGlobalCSupport(void) const;
	/**
	initializes build configuration state that can be read from the lua_State
	*/
	void				initializeInterpretation(void) const;
	/**
	solves this problem: http://lua-users.org/lists/lua-l/2007-01/msg00126.html
	\see Lua.cpp
	*/
	void				initializeUserdataStorage(void) const;
	/**
	opens base, package, string, table, and math libraries in %Lua.  
	in DEBUG builds only, opens the debug library
	*/
	void				openStandardLibraries(void) const;
	/**
	reports output from the lua_State
	*/
	int					report(int status) const;
	
private:
	/** open standard libraries and such */
	void				initialize(const char* name);
	/** allocation method, see comments in Lua.cpp */
	static void*		luaAlloc(void* ud, void* ptr, size_t osize, size_t nsize);
	/** a function just to test stuff out */
	void				runSandbox(void) const;	
	/** The use of this could only be a terrible idea. */
	Lua& operator=(const Lua&);
	/** The use of this could only be a terrible idea. */
	Lua(const Lua&);
	/** 
	the %Lua state which this class encapsulates. 
	\note on readibility and coding standards this is
	one of the very few times I don't use m_ prefix 
	for a member variable.
	*/
	lua_State*			L; 
	/** current byte count of lua memory useage */
	size_t				m_bytes;
	/** simple identifier */
	char*				m_name;
};

} // namespace LuaExtension 

#endif//LUA_H