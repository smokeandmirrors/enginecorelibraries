#pragma once
#ifndef LUA_H
#define LUA_H
/**
\file Lua.h
\brief This file defines the class Lua.  

\author Smoke and Mirrors Development
\htmlonly
<A HREF="smokeandmirrorsdevelopment@gmail.com">
smokeandmirrorsdevelopment@gmail.com</A>
<BR>
&copy;2009-2011 Smoke and Mirrors Development
<BR>
\endhtmlonly
\date 2/18/2010

\warning THIS FUNCTIONALITY IS NOT THREAD SAFE.

<DEVELOPMENT STATUS>
Current Draft		:	1.0
Current Phase		:   FIELD TESTING
Purpose				:	DEPLOYMENT
Unit Tested			:	YES
Used in development	:	YES
Used in experiments :	YES
Tested in the field	:	YES

The Lua class encapsulates a lua_Struct.  It will allow for easier creation
of application and library code for %Lua.

*/
#include "LuaBuild.h"

namespace embeddedLua 
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
	calls lua_pcall() on the function at the top of the stack
	\param L the %Lua state to call the function
	\param num_args the number of arguments for the function call
	\param num_return_values the number of expected returned values, defaults
	to LUA_MULTIRET
	*/
	static sint	callProtected(lua_State* L, sint num_args=0, sint num_return_values=-1);
	/**
	reports output from the lua_State after a function call
	\param L the %Lua state in which the function was called
	\param status the error code from calling the function
	*/
	static void	report(lua_State* L, sint status);
	/**
	call require from C++
	*/
	static bool	require(lua_State* L, const schar* module, bool hideNotFoundError=false, bool hideSyntaxError=false);
	/** 
	public [no-args] constructor.
	\param name a string identifier
	\param open_standard_libs if true, the base, package, string, table, and math %Lua libraries will be opened
	\param initialize_userdata_storage if true, the solution to userdata table indexing will be initialized
	*/
	Lua(const schar* name="anonymous", bool open_standard_libs=true, bool initialize_userdata_storage=true);
	/** 
	destroys the lua_State and any memory allocated by this object
	*/
	virtual ~Lua(void);
	/**
	loads end executes the string as a lua chunk
	\return the status of the execution
	*/
	bool doString(const schar* chunk, const schar* source="native code");
	/**
	\return the number of bytes allocated by the %Lua state
	*/
	size_t getNumAllocatedBytes() const { return bytesInUse; }	
	/**
	\return the string ID of this specific %Lua object
	*/
	const schar* getName(void) const		{ return m_name; }
	/**
	returns the lua_State encapsulated by this class
	*/
	lua_State* getState(void) const	{ return L; }
	/** 
	Opens %Lua library using the lua_function provided
	\warning if you loaded a library and altered it, this will reload that library
	*/
	bool openLibrary(lua_function key) const;
	/**
	require() shortcut
	*/
	bool require(const schar* module, bool hideNotFoundError=false, bool hideSyntaxError=false);
	/** 
	quick, low functionality console for fast testing 
	*/
	void runConsole(void) const;
	/**
	sets the LUA_PATH value to the passed in string, loads the package library if not done yet
	*/
	void setPackagePath(const char* luaPath);
	
protected:
	/**
	*/
	bool conditionallyOpenStandardLibrary(lua_function key, const schar* name);
	/**
	pushes a default implementation for __gc && __tostring for
	LuaExtendable classes.
	*/
	void initializeDefaultProxyMetamethods(void) const;
	/**
	initializes build configuration state that can be read from the lua_State
	*/
	void initializeInterpretation(void) const;
	/**
	solves this problem: http://lua-users.org/lists/lua-l/2007-01/msg00126.html
	\see Lua.cpp
	*/
	void initializeUserdataStorage(void) const;
	/**
	opens base, package, string, table, and math libraries in %Lua.  
	in DEBUG builds only, opens the debug library
	*/
	void openStandardLibraries(void);	
	
private:
	/** open standard libraries and such */
	void initialize(const schar* name);
	/** allocation method, see comments in Lua.cpp */
	static void* luaAlloc(void* ud, void* ptr, size_t osize, size_t nsize);
	/** The use of this could only be a terrible idea. */
	Lua& operator=(const Lua&);
	/** The use of this could only be a terrible idea. */
	Lua(const Lua&);
	/** 
	the %Lua state which this class encapsulates. 
	\note on readability and coding standards this is
	one of the very few times I don't use m_ prefix 
	for a member variable.
	*/
	lua_State* L; 
	/** current byte count of %Lua memory use */
	size_t bytesInUse;
	/** simple identifier */
	char* m_name;
};

} // namespace embeddedLua 

#endif//LUA_H