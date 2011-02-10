#include <assert.h>
#include <string.h>

#include "Lua.h"
#include "LuaExtensibility.h"
#include "LuaInclusions.h"
#include "LuaStateInteraction.h"

namespace luaExtension
{

#define lua_setUserDataMetamethod(L, method)	/*s: userdata, lua_class_mt, proxy/mt, userdata_mt */\
	lua_getfield(L, -3, method);				/*s: userdata, lua_class_mt, proxy/mt, userdata_mt, ? */\
	lua_setfield(L, -2, method);				/*s: userdata, lua_class_mt, proxy/mt, userdata_mt	  */	

// uint testing = LUA_EXPOSURE_LIBRARY & LUA_EXPOSURE_CLASS & LUA_EXPOSURE_CREATE_GLOBAL_MT;

const char*	lua_metamethodNames[NUM_LUA_METAMETHODS] = {
	"__add",
	"__call",
	"__concat",
	"__div",
	"__eq",
	"__gc",
	"__index",
	"__le",
	"__len",
	"__lt",
	"__metatable",
	"__mod",
	"__mul",
	"__newindex",
	"__pow",
	"__sub",
	"__unm",
	"__tostring",
};

inline bool isInstanceBeingRefreshed(lua_State* L)
{	//s: userdata, lua_class_mt
	if (lua_getmetatable(L, -2))
	{
		lua_pop(L, 1);
		return true;
	}
	else
	{
		return false;
	}
}

sint LuaExtendable::__gcmetamethod(lua_State* L)
{
	LuaExtendable* udata = to<LuaExtendable*>(L, -1);
	delete udata;
	return 0;
}

sint LuaExtendable::__getProxy(lua_State* L)
{
	lua_pushvalue(L, lua_upvalueindex(1));	//s: proxy/nil
	return 1;
}

sint LuaExtendable::__newindexError(lua_State* L)
{											//: t, k, v
#if DEBUG
	LuaExtendable* udata = to<LuaExtendable*>(L, -3);
	// pop values off the stack?
	return luaL_error(L, "ERROR! Attempting to assign a value to a LuaExtendable %s that doesn't support new values.  "
		"Use define_lua_LuaExtendable_by_proxy to expose this class to Lua if that is desired.", udata->toString());
#else
	(void*)L;
	return 0;
#endif//DEBUG
}

sint LuaExtendable::__newindexProxy(lua_State* L) 
{											//s: ud, k, v 	
	lua_pushvalue(L, lua_upvalueindex(1));	//s: ud, k, v, proxy
	lua_replace(L, -4);						//s: proxy, k, v
	lua_rawset(L, -3);						//s: proxy
	lua_pop(L, 1);							//s: 
	return 0;
}

sint LuaExtendable::__tostring(lua_State* L)
{
	LuaExtendable* udata = to<LuaExtendable*>(L, -1);
	lua_pushstring(L, udata->toString());
	return 1;
}

sint LuaExtendable::callSetMetatable(lua_State* L)
{
	LuaExtendable* udata = to<LuaExtendable*>(L, -2);
	return udata->setMetatable(L);
}

void LuaExtendable::declareLuaClass(lua_State* L, const char* derived, const char* super)
{
	Lua::nilLoadedStatus(L, derived);
	Lua::require(L, "ObjectOrientedParadigm"); 
	Lua::require(L, derived); 
	completeLuaClassDeclaration(L, derived, super);
	
	lua_getglobal(L, "ObjectOrientedParadigm");
	if (!lua_istable(L, -1))
		return;
	//s: OOP
	lua_getfield(L, -1, "declareClass");
	assert(lua_isfunction(L, -1));
	//s: declareClass
	lua_getglobal(L, derived);
	assert(lua_istable(L, -1));
	//s: declareClass derived
#if DEBUG 
	bool success = Lua::callProtected(L, 1, 0) == 0;
	assert(success);
#else
	Lua::callProtected(L, 1, 0);
#endif//DEBUG
	//s: 
}

sint LuaExtendable::setProxyMetatable(lua_State* L)
{	/**
	-- will be called by lua constructor, as defined in ObjectOrientedParadigm.lua
	function(userdata, class_mt)
		local proxy = setmetatable({}, class_mt) -- class_mt is from ObjectOrientedParadigm
		local instance_mt = {
			__index = proxy,
			__newindex = function(t, k, v)
				proxy[k] = v
			end,
		}
		for name, method in pairs(metamethods) do
			if name ~= '__index' and name ~= '__newindex' do
				instance_mt[name] = method
			end
		end
		return setmetatable(userdata, instance_mt) -- can't be done from Lua
	end
	*/
												//s: userdata, lua_class_mt
	if (isInstanceBeingRefreshed(L)) 
	{	
		// the class is being redefined			//s: userdata, lua_class_mt
		lua_pushvalue(L, -1);					//s: userdata, lua_class_mt, lua_class_mt
		lua_getmetatable(L, -3);				//s: userdata, lua_class_mt, lua_class_mt, userdata_mt
		lua_getfield(L, -1, "__getProxy");		//s: userdata, lua_class_mt, lua_class_mt, userdata_mt, __getProxy
		lua_call(L, 0, 1);						//s: userdata, lua_class_mt, lua_class_mt, userdata_mt, proxy
		lua_replace(L, -2);						//s: userdata, lua_class_mt, lua_class_mt, proxy
		
		// initialize proxy
		lua_insert(L, -2);						//s: userdata, lua_class_mt, proxy, lua_class_mt
		lua_setmetatable(L, -2);				//s: userdata, lua_class_mt, proxy/mt
		lua_getmetatable(L, -3);				//s: userdata, lua_class_mt, proxy/mt, userdata_mt
	}
	else
	{	// the class is being defined			//s: userdata, lua_class_mt
		lua_pushvalue(L, -1);					//s: userdata, lua_class_mt, lua_class_mt
		lua_newtable(L);						//s: userdata, lua_class_mt, lua_class_mt, proxy
		
		// initialize proxy
		lua_insert(L, -2);						//s: userdata, lua_class_mt, proxy, lua_class_mt
		lua_setmetatable(L, -2);				//s: userdata, lua_class_mt, proxy/mt
		lua_newtable(L);						//s: userdata, lua_class_mt, proxy/mt, userdata_mt
	}
	
	lua_pushvalue(L, -2);						//s: userdata, lua_class_mt, proxy/mt, userdata_mt, proxy/mt
	lua_setfield(L, -2, "__index");				//s: userdata, lua_class_mt, proxy/mt, userdata_mt
	lua_pushvalue(L, -2);						//s: userdata, lua_class_mt, proxy/mt, userdata_mt, proxy/mt
	lua_pushcclosure(L, LuaExtendable::__newindexProxy, 1); 
												//s: userdata, lua_class_mt, proxy/mt, userdata_mt, __newindex
	lua_setfield(L, -2, "__newindex");			//s: userdata, lua_class_mt, proxy/mt, userdata_mt
	lua_pushvalue(L, -2);						//s: userdata, lua_class_mt, proxy/mt, userdata_mt, proxy/mt
	lua_pushcclosure(L, LuaExtendable::__getProxy, 1); 
												//s: userdata, lua_class_mt, proxy/mt, userdata_mt, __getProxy
	lua_setfield(L, -2, "__getProxy");			//s: userdata, lua_class_mt, proxy/mt, userdata_mt
	
	// define/redefine every other metamethod
	lua_setUserDataMetamethod(L, "__add");		//s: userdata, lua_class_mt, proxy/mt, userdata_mt
	lua_setUserDataMetamethod(L, "__call");		//s: userdata, lua_class_mt, proxy/mt, userdata_mt
	lua_setUserDataMetamethod(L, "__concat");	//s: userdata, lua_class_mt, proxy/mt, userdata_mt
	lua_setUserDataMetamethod(L, "__div");		//s: userdata, lua_class_mt, proxy/mt, userdata_mt
	lua_setUserDataMetamethod(L, "__eq");		//s: userdata, lua_class_mt, proxy/mt, userdata_mt
	lua_setUserDataMetamethod(L, "__gc");		//s: userdata, lua_class_mt, proxy/mt, userdata_mt
	lua_setUserDataMetamethod(L, "__le");		//s: userdata, lua_class_mt, proxy/mt, userdata_mt
	lua_setUserDataMetamethod(L, "__len");		//s: userdata, lua_class_mt, proxy/mt, userdata_mt
	lua_setUserDataMetamethod(L, "__lt");		//s: userdata, lua_class_mt, proxy/mt, userdata_mt
	lua_setUserDataMetamethod(L, "__metatable");//s: userdata, lua_class_mt, proxy/mt, userdata_mt
	lua_setUserDataMetamethod(L, "__mod");		//s: userdata, lua_class_mt, proxy/mt, userdata_mt
	lua_setUserDataMetamethod(L, "__mul");		//s: userdata, lua_class_mt, proxy/mt, userdata_mt
	lua_setUserDataMetamethod(L, "__pow");		//s: userdata, lua_class_mt, proxy/mt, userdata_mt
	lua_setUserDataMetamethod(L, "__sub");		//s: userdata, lua_class_mt, proxy/mt, userdata_mt
	lua_setUserDataMetamethod(L, "__unm");		//s: userdata, lua_class_mt, proxy/mt, userdata_mt
	lua_setUserDataMetamethod(L, "__tostring");	//s: userdata, lua_class_mt, proxy/mt, userdata_mt
	lua_setmetatable(L, -4);					//s: userdata/mt, lua_class_mt, proxy/mt
	lua_pop(L, 2);								//s: userdata/mt
	return 1;
}

sint LuaExtendable::setUserdataMetatable(lua_State* L)
{								//s: userdata, lua_class_mt
	lua_setmetatable(L, -2);	//s: userdata/mt
	return 1;
}

void completeLuaClassDeclaration(lua_State* L, const char* derived, const char* super)
{
	lua_getglobal(L, derived);
	//s: class_def
	assert(lua_istable(L, -1));
	/* ensure a proper 'name' field */
	lua_getfield(L, -1, "name");
	//s: class_def ?
	if (lua_isstring(L, -1))
	{	//s: class_def class_def.name
		assert(!strcmp(lua_tostring(L, -1), derived));
		lua_pop(L, 1);
		//s: class_def
	}
	else
	{	//s: class_def nil	
		assert(lua_isnil(L, -1));
		lua_pop(L, 1);
		//s: class_def
		push(L, derived);
		//s: class_def derived
		lua_setfield(L, -2, "name");
		//s: class_def

		lua_getfield(L, -1, "name");
		assert(lua_isstring(L, -1));
		//s: class_def class_def.name
		assert(!strcmp(lua_tostring(L, -1), derived));
		lua_pop(L, 1);
		//s: class_def 
	}
	//s: class_def
	/* ensure a proper 'extends' field */
	lua_getfield(L, -1, "extends");
	//s: class_def ?
	if (lua_isstring(L, -1))
	{	//s: class_def class_def.extends
		assert(!strcmp(lua_tostring(L, -1), super));
		lua_pop(L, 1);
		//s: class_def
	}
	else if (super && (strcmp(super, derived) != 0))
	{	//s: class_def nil	
		assert(lua_isnil(L, -1));
		lua_pop(L, 1);
		//s: class_def
		push(L, super);
		//s: class_def derived
		lua_setfield(L, -2, "extends");
		//s: class_def
	}
	//s: class_def
	lua_pop(L, 1);
	//s:
}

void printToLua(lua_State* L, const char* string)
{	
	lua_getglobal(L, "print");	//s: print
	lua_pushstring(L, string);	//s: print, string
	lua_call(L, 1, 0);			//s: 
}

sint pushRegisteredClass(lua_State* L, void* pushee)
{
	lua_getfield(L, LUA_REGISTRYINDEX, "pusheduserdata");	//s: pusheduserdatatable
	lua_pushlightuserdata(L, pushee);						//s: pusheduserdatatable, pushee* 
	lua_rawget(L, -2);										//s: pusheduserdatatable, pusheduserdatatable[pushee*]
	
	if (lua_isnil(L, -1))									//s: pusheduserdatatable, ?
	{														//s: pusheduserdatatable, nil
		lua_pop(L, 1);										//s: pusheduserdatatable
		void** userdata = static_cast<void**>(lua_newuserdata(L, sizeof(void*))); 
															//s: pusheduserdatatable, udata
		*userdata = pushee;									//s: pusheduserdatatable, udata
		lua_pushlightuserdata(L, pushee);					//s: pusheduserdatatable, udata, pushee*
		lua_pushvalue(L, -2);								//s: pusheduserdatatable, udata, pushee*, udata
		lua_rawset(L, -4);									//s: pusheduserdatatable, udata
	}

	lua_replace(L, -2);										//s: pusheduserdata
	return 1;
}

} // namespace luaExtension