#ifdef EXTENDED_BY_LUA
#include <assert.h>

#include "LuaRegistration.h"
#include "LuaInclusions.h"

#define setUserdataMetamethod(L, method)		/*s: userdata, lua_class_mt, proxy/mt				  */\
	lua_getfield(L, -3, method);				/*s: userdata, lua_class_mt, proxy/mt, userdata_mt, ? */\
	lua_setfield(L, -2, method);				/*s: userdata, lua_class_mt, proxy/mt, userdata_mt	  */	

unsigned int testing = eLUA_EXPOSURE_LIBRARY & eLUA_EXPOSURE_CLASS & eLUA_EXPOSURE_CREATE_GLOBAL_MT;

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

int __gcLuaExtendable(lua_State* L)
{
	LuaExtendable* udata = *static_cast<LuaExtendable**>(lua_touserdata(L, -1));
	delete udata;
	return 0;
}

int __newindexProxy(lua_State* L) 
{											//s: table,	k, v 	
	lua_pushvalue(L, lua_upvalueindex(1));	//s: table, k, v, proxy
	lua_replace(L, -4);						//s: proxy, k, v
	lua_rawset(L, -3);						//s: proxy
	lua_pop(L, 1);							//s: 
	return 0;
}

int __tostringLuaExtendable(lua_State* L)
{
	LuaExtendable* udata = *static_cast<LuaExtendable**>(lua_touserdata(L, -1));
	lua_pushstring(L, udata->toString());
	return 1;
}

/** \todo support the super_class name */
void createGlobalClassMetatable(lua_State* L, const char* class_name, const char* super_class_name)
{
	lua_pushstring(L, class_name);
	createGlobalClassMetatable(L);
}

int createGlobalClassMetatable(lua_State* L)
{	/*
	function createGlobalClassMetatable(class_name, metatable_name)
		local class = _G[class_name]
		if class then
			local class_mt = _G.C_metatables[class_name]
			if not class_mt then
				class_mt = {}
				_G.C_metatables[class_name] = class_mt
			end
			for metamethodname, _ in pairs(metamethods) do
				if class[metamethodname] then
					class_mt[metamethodname] = class[metamethodname]
				end
			end
		end
	end
	*/
															//s: class_name
	const char* class_name = lua_tostring(L, -1);			//s: class_name
	lua_pop(L, 1);											//s:
	lua_getglobal(L, class_name);							//s: class
	lua_getglobal(L, "C_metatables");						//s: class, C_metatables
	lua_getfield(L, -1, class_name);						//s: class, C_metatables, ?
	/** 
	@todo under what situations would this be called 2x?  
	when would this be non nil (for the same class)? 
	*/
	if (lua_isnil(L, -1))
	{														//s: class, C_metatables, nil
		lua_pop(L, 1);										//s: class, C_metatables
		lua_newtable(L);									//s: class, C_metatables, class_mt
		lua_pushvalue(L, -1);								//s: class, C_metatables, class_mt, class_mt
		lua_setfield(L, -3, class_name);					//s: class, C_metatables, class_mt
	}
															//s: class, C_metatables, class_mt
	lua_replace(L, -2);										//s: class, class_mt
	
	int index = NUM_LUA_METAMETHODS;
	do 
	{
		--index;
		const char* method_name = lua_metamethodNames[index];
		lua_getfield(L, -2, method_name);					//s: class, class_mt, ?
		if (lua_isnil(L, -1))
		{													//s: class, class_mt, nil
			lua_pop(L, 1);									//s: class, class_mt
		}
		else
		{													//s: class, class_mt, metamethod
			lua_setfield(L, -1, method_name);				//s: class, class_mt
		}
	} 
	while (index);
															//s: class, class_mt
	lua_getfield(L, -1, "__index");							//s: class, class_mt, ?
	
	if (lua_isnil(L, -1))
	{														//s: class, class_mt, nil
		lua_pop(L, 1);										//s: class, class_mt
		lua_pushvalue(L, -2);								//s: class, class_mt, class
		lua_setfield(L, -2, "__index");						//s: class, class_mt
		lua_pop(L, 2);										//s: 
	}
	else
	{														//s: class, class_mt, __index
		lua_pop(L, 3);										//s: 
	}
															//s:
	return 0;
}

void printToLua(lua_State* L, const char* string)
{	
	lua_getglobal(L, "print");	//s: print
	lua_pushstring(L, string);	//s: print, string
	lua_call(L, 1, 0);			//s: 
}

void pushRegisteredClass(lua_State* L, void* pushee)
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
}

int setmetatableLuaExtendable(lua_State* L)
{
	LuaExtendable* udata = *static_cast<LuaExtendable**>(lua_touserdata(L, -2));
	return udata->setMetatable(L);
}

int setDefaultMetatableProxy(lua_State* L)
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
	lua_pushvalue(L, -1);						//s: userdata, lua_class_mt, lua_class_mt
	lua_newtable(L);							//s: userdata, lua_class_mt, lua_class_mt, proxy
	lua_insert(L, -2);							//s: userdata, lua_class_mt, proxy, lua_class_mt
	lua_setmetatable(L, -2);					//s: userdata, lua_class_mt, proxy/mt
	lua_newtable(L);							//s: userdata, lua_class_mt, proxy/mt, userdata_mt
	lua_pushvalue(L, -2);						//s: userdata, lua_class_mt, proxy/mt, userdata_mt, proxy/mt
	lua_setfield(L, -2, "__index");				//s: userdata, lua_class_mt, proxy/mt, userdata_mt
	lua_pushvalue(L, -2);						//s: userdata, lua_class_mt, proxy/mt, userdata_mt, proxy/mt
	lua_pushcclosure(L, __newindexProxy, 1);	//s: userdata, lua_class_mt, proxy/mt, userdata_mt, __newindexProxy
	lua_setfield(L, -2, "__newindex");			//s: userdata, lua_class_mt, proxy/mt, userdata_mt
	setUserdataMetamethod(L, "__add")
	setUserdataMetamethod(L, "__call")
	setUserdataMetamethod(L, "__concat")
	setUserdataMetamethod(L, "__div")
	setUserdataMetamethod(L, "__eq")
	setUserdataMetamethod(L, "__gc")
	setUserdataMetamethod(L, "__le")
	setUserdataMetamethod(L, "__len")
	setUserdataMetamethod(L, "__lt")
	setUserdataMetamethod(L, "__metatable")
	setUserdataMetamethod(L, "__mod")
	setUserdataMetamethod(L, "__mul")
	setUserdataMetamethod(L, "__pow")
	setUserdataMetamethod(L, "__sub")
	setUserdataMetamethod(L, "__unm")
	setUserdataMetamethod(L, "__tostring")
	lua_setmetatable(L, -4);					//s: userdata, lua_class_mt, proxy/mt
	lua_pop(L, 2);								//s: userdata/mt
	return 1;
}
#endif//EXTENDED_BY_LUA
