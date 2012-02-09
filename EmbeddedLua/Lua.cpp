#include "Lua.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include "LuaInclusions.h"
#include "LuaExtensibility.h"
#include "LuaStateInteraction.h"

namespace embeddedLua 
{
#if !GOLDMASTER
// \note taken straight from lua.c
static sint traceback (lua_State* L)
{
  lua_getglobal(L, "debug");
  if (!lua_istable(L, -1)) {
    lua_pop(L, 1);
    return 1;
  }
  lua_getfield(L, -1, "traceback");
  if (!lua_isfunction(L, -1)) {
    lua_pop(L, 2);
    return 1;
  }
  lua_pushvalue(L, 1);		/* pass error message */
  lua_pushinteger(L, 2);	/* skip this function and traceback */
  lua_call(L, 2, 1);		/* call debug.traceback */
  return 1;
}
#endif//!GOLDMASTER

Lua::Lua(const char *name, bool open_standard_libs, bool initialize_userdata_storage)
: bytesInUse(0)
, m_name(NULL)
, L(NULL)
{
	initialize(name);
	
	if (open_standard_libs)
		openStandardLibraries();
	
	initializeInterpretation();
	
	if (initialize_userdata_storage)
		initializeUserdataStorage();
	
	/** \todo use methods like this this to save memory on LuaExtendables */
	initializeDefaultProxyMetamethods();

#if !GOLDMASTER
	lua_pushcfunction(L, traceback);
	lua_setglobal(L, "traceback");
#endif//!GOLDMASTER
}

Lua::~Lua(void)
{
	lua_close(L);
	L = NULL;
	delete m_name;
}

sint Lua::callProtected(lua_State* L, sint num_args, sint num_return_values)
{	
	sint errorfunc_index = lua_gettop(L) - num_args;	
	lua_getglobal(L, "traceback");			
	lua_insert(L, errorfunc_index);					
	sint error_code = lua_pcall(L, num_args, num_return_values, errorfunc_index);
	lua_remove(L, errorfunc_index);					
	report(L, error_code);

	if (error_code)
	{	// in case of error, fully collect %Lua garbage  
		lua_gc(L, LUA_GCCOLLECT, 0); 
	}
	
	return error_code;
}

bool Lua::conditionallyOpenStandardLibrary(lua_function key, const schar* name)
{
	lua_getglobal(L, name); 
	if (lua_isnil(L, -1)) 
	{	// the final true stores the result into a global table 'name'
		luaL_requiref(L, name, key, true);
		return true;
	} 
	else 
	{ 
		lua_pop(L, 1); 
		return false;
	}
}

bool Lua::doString(const schar* chunk, const schar*)
{
	return !luaL_dostring(L, chunk);
}

void Lua::initialize(const schar* name)
{
	size_t size = strlen(name) + 1;
	m_name = new char[size];
	strcpy_s(m_name, size, name);
	L = lua_newstate(luaAlloc, this);
}

void Lua::initializeDefaultProxyMetamethods(void) const
{
	lua_newtable(L);										//s: table
	lua_pushcfunction(L, LuaExtendable::__gcmetamethod);	//s: table, __gcmetamethod
	lua_setfield(L, -2, "__gc");							//s: table
	lua_pushcfunction(L, LuaExtendable::__tostring);		//s: table, __tostring
	lua_setfield(L, -2, "__tostring");						//s: table
	lua_setfield(L, LUA_REGISTRYINDEX, "proxymetamethods");	//s: 
}

void Lua::initializeInterpretation(void) const
{
#if	DEBUG 
	lua_pushboolean(L, 1);
	lua_setglobal(L, "DEBUG_INTERPRETATION");
#endif//DEBUG 
}

void Lua::initializeUserdataStorage(void) const
{	/**
	solves this problem: http://lua-users.org/lists/lua-l/2007-01/msg00126.html
	\see also "Binding C/C++ Objects to Lua", Waldemar Celes, Luiz Henrique de Figueiredo, Roberto Ierusalimschy
	in "Game Programming Gems 6".

	basically, allows us to prevent duplication of exposed objects, and allows them to be
	used as equivalent table keys.  If it were not done, you would get this:
	
	a = getObject(3) -- a is userdata
	b = getObject(3) -- b is userdata (the same one as a)
	t = {}
	t[a] = 12

	print(a == b)	-- this prints "true"
	print(t[a])		-- this prints "12"
	print(t[b])		-- this prints "nil" !!!BAD!!!

	-- but, with the code below running
	print(t[b])		-- this prints "12" !!!GOOD!!!
	*/
	lua_newtable(L);										//s: table
	luaL_newmetatable(L, "pusheduserdata_mt");				//s: table, mt
	lua_pushstring(L, "v");									//s: table, mt, "v"
	lua_setfield(L, -2, "__mode");							//s: table, mt
	lua_setmetatable(L, -2);								//s: table&mt
	lua_setfield(L, LUA_REGISTRYINDEX, "pusheduserdata");	//s: 
}

/** 
implementation inspired by:
http://www.lua.org/manual/5.1/manual.html#lua_Alloc
*/ 
void* Lua::luaAlloc(void* ud, void* ptr, size_t osize, size_t nsize)
{
	Lua* lua = reinterpret_cast<Lua*>(ud);
		
	if (nsize)
	{
		lua->bytesInUse += nsize;
			
		if (osize)
		{
			lua->bytesInUse -= osize;
			return realloc(ptr, nsize);
		}
		else
		{	assert(!ptr);
			return malloc(nsize);
		}
	}
	else
	{	
		free(ptr);
		lua->bytesInUse -= osize;
		return NULL;
	}
}

bool Lua::openLibrary(lua_function opener) const
{
	if (opener)
	{
		
		lua_pushcfunction(L, opener);
		sint status = callProtected(L);
		lua_pop(L, 1);
		return status == 0;
	}
	else
	{
		return false;
	}
}

void Lua::openStandardLibraries(void) 
{
	conditionallyOpenStandardLibrary(luaopen_base, "base");
	conditionallyOpenStandardLibrary(luaopen_coroutine, "coroutine");
#if	DEBUG 
	conditionallyOpenStandardLibrary(luaopen_debug, "debug");
#endif // DEBUG 
	conditionallyOpenStandardLibrary(luaopen_io, "io");
	conditionallyOpenStandardLibrary(luaopen_math, "math");
	conditionallyOpenStandardLibrary(luaopen_os, "os");
	conditionallyOpenStandardLibrary(luaopen_package, "package");
	conditionallyOpenStandardLibrary(luaopen_string, "string");
	conditionallyOpenStandardLibrary(luaopen_table, "table");
}

// \note taken and modified from from lua.c 
void Lua::report(lua_State* L, sint error_code)
{
	if (error_code && lua_isstring(L, -1)) 
	{
		const char *msg = lua_tostring(L, -1);
		if (msg == NULL) 
			msg = "(error object is not a string)";
		// if (source) 
		//	fprintf(stderr, "Error source: %s\n", source);
		fprintf(stderr, "%s\n", msg);
		fflush(stderr);
		lua_pop(L, 1);
	}
}

bool Lua::require(lua_State* L, const schar* module, bool hideNotFoundError, bool hideSyntaxError)
{
	lua_getglobal(L, "require");
	push(L, module);
	push(L, hideNotFoundError);
	push(L, hideSyntaxError);
	return callProtected(L, 3, 1) == 0;
}

bool Lua::require(const schar* module, bool hideNotFoundError, bool hideSyntaxError)
{
	return require(L, module, hideNotFoundError, hideSyntaxError);
}

void Lua::runConsole(void) const
{
	char quit[9] = "quit_Lua";
	char buff[2048];
	
	while (fgets(buff, sizeof(buff), stdin))
	{
		char* d = &quit[0]; 
		char* s = &buff[0];

		for (sint i=0; i < 8; i++)
		{
			*d++ = *s++;
		}

		if (String::compare(quit, "lua_quit"))
		{
			if (luaL_loadbuffer(L, buff, strlen(buff), "line") || callProtected(L))
			{
				fprintf(stderr, "%s\n", lua_tostring(L, -1));
				lua_pop(L, 1);
			}
		}
		else
		{
			return;
		}
	}	
}

void Lua::setPackagePath(const char* luaPath)
{
	conditionallyOpenStandardLibrary(luaopen_package, "package");
	lua_getglobal(L, "package");	//s: package
	push(L, luaPath);				//s: package, LUA_PATH
	lua_setfield(L, -2, "path");	//s: package
	lua_pop(L, 1);					//s: 
}

} // namespace embeddedLua