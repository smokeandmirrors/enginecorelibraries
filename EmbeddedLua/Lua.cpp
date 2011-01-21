#include "Lua.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include "LuaInclusions.h"

namespace LuaExtension 
{

#if !GOLDMASTER
// \note taken straight from lua.c
static sint traceback (lua_State* L)
{
  // if (!lua_isstring(L, 1))  /* 'message' not a string? */
  //  return 1;  /* keep it intact */
  lua_getfield(L, LUA_GLOBALSINDEX, "debug");
  if (!lua_istable(L, -1)) {
    lua_pop(L, 1);
    return 1;
  }
  lua_getfield(L, -1, "traceback");
  if (!lua_isfunction(L, -1)) {
    lua_pop(L, 2);
    return 1;
  }
  lua_pushvalue(L, 1);  /* pass error message */
  lua_pushinteger(L, 2);  /* skip this function and traceback */
  lua_call(L, 2, 1);  /* call debug.traceback */
  return 1;
}
#endif//!GOLDMASTER

Lua::Lua(const char *name, bool open_standard_libs, bool initialize_userdata_storage)
: m_bytes(0)
, m_name(NULL)
, L(NULL)
{
	initialize(name);
	
	if (open_standard_libs)
		openStandardLibraries();
	
	initializeInterpretation();
	initializeGlobalCSupport();

	if (initialize_userdata_storage)
		initializeUserdataStorage();

	initializeDefaultProxyMetamethods();

#if !GOLDMASTER
	lua_pushcfunction(L, traceback);
	lua_setglobal(L, "traceback");
	runSandbox();
#endif//!GOLDMASTER
}

Lua::~Lua(void)
{
	lua_close(L);
	L = NULL;
	delete m_name;
}

sint Lua::callProtected(sint num_args, sint num_return_values) const
{	
	sint errorfunc_index = lua_gettop(L) - num_args;	
	lua_getglobal(L, "traceback");			
	lua_insert(L, errorfunc_index);					
	sint error_code = lua_pcall(L, num_args, num_return_values, errorfunc_index);
	lua_remove(L, errorfunc_index);					
	
	if (error_code)
	{	// in case of error, fully collect %Lua garbarge  
		lua_gc(L, LUA_GCCOLLECT, 0); 
	}
	
	return report(error_code);
}

bool Lua::doString(const char* chunk, const char*)
{
	return !luaL_dostring(L, chunk);
}

void Lua::initialize(const char* name)
{
	size_t size = strlen(name) + 1;
	m_name = new char[size];
	strcpy_s(m_name, size, name);
	L = lua_newstate(luaAlloc, this);
}

void Lua::initializeDefaultProxyMetamethods(void) const
{
	lua_newtable(L);										//s: table
	lua_pushcfunction(L, __gcLuaExtendable);				//s: table, __gcLuaExtendable
	lua_setfield(L, -2, "__gc");							//s: table
	lua_pushcfunction(L, __tostringLuaExtendable);			//s: table, __tostringLuaExtendable
	lua_setfield(L, -2, "__tostring");						//s: table
	lua_setfield(L, LUA_REGISTRYINDEX, "proxymetamethods");	//s: 
}

void Lua::initializeGlobalCSupport(void) const
{
	lua_newtable(L);
	lua_setglobal(L, "C_metatables");
}

void Lua::initializeInterpretation(void) const
{
#if		DEBUG ///////////////////////////////// 
	lua_pushboolean(L, 1);
	lua_setglobal(L, "DEBUG_INTERPRETATION");
#endif//DEBUG /////////////////////////////////
}

void Lua::initializeUserdataStorage(void) const
{	/**
	solves this problem: http://lua-users.org/lists/lua-l/2007-01/msg00126.html
	@see also "Binding C/C++ Objects to Lua", Waldemar Celes, Luiz Henrique de Figueiredo, Roberto Ierusalimschy
	in "Game Programming Gems 6".

	basically, allows us to prevent duplication of exposed objects, and allows them to be
	used as equivalent table keys.  If it were not done, you would get this:
	
	a = getObject(3) -- a is userdata
	b = getObject(3) -- b is userdata (the same one as a)
	t = {}
	t[a] = 12

	print(a == b)  -- this prints "true"
	print(t[a])    -- this prints "12"
	print(t[b])    -- this prints "nil" !!!
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
		lua->m_bytes += nsize;
			
		if (osize)
		{
			lua->m_bytes -= osize;
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
		lua->m_bytes -= osize;
		return NULL;
	}
}

void Lua::nilLoadedStatus(const char* module) const
{
	if (module)
	{
		lua_getglobal(L, "package");
		lua_getfield(L, -1, "loaded");
		lua_pushnil(L);
		lua_setfield(L, -2, module);
		lua_pop(L, 1);
	}
}

void Lua::openLibrary(lua_function opener) const
{
	if (opener)
	{
		lua_pushcfunction(L, opener);
		callProtected();
		lua_pop(L, 1);
	}
}

void Lua::openStandardLibraries(void) const
{
	openLibrary(luaopen_base);
	openLibrary(luaopen_math);
	openLibrary(luaopen_package);
	openLibrary(luaopen_string);
	openLibrary(luaopen_table);
	openLibrary(luaopen_os);
#if	DEBUG /////
	openLibrary(luaopen_debug);
#endif // DEBUG 
}

// \note taken and modified from from lua.c 
sint Lua::report(sint error_code) const
{
	if (error_code && lua_isstring(L, -1)) 
	{
		const char *msg = lua_tostring(L, -1);
		if (msg == NULL) msg = "(error object is not a string)";
		// \todo log the error or the msg
		// l_message(progname, msg);
		lua_pop(L, 1);
	}
	
	return error_code;
}

bool Lua::require(const char* module) const
{
	lua_getglobal(L, "require");
	lua_pushstring(L, module);
	return !callProtected(1);
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
		
		if (strcmp(quit, "lua_quit"))
		{
			if (luaL_loadbuffer(L, buff, strlen(buff), "line") || callProtected())
			{
				fprintf(stderr, "%s\n", lua_tostring(L, -1));
				lua_pop(L, 1);
			}
		}
		else
		{
			break;
		}
	}	
}

void Lua::runSandbox(void) const
{
	
}

} // namespace LuaExtension