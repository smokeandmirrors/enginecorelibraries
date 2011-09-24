module(..., package.seeall)

require'Utilities'
CW = require'CodeWriting'
EN2S = require'LuaExposeNativeToScript'

local U = require'Utilities'
local CW = require'CodeWriting'
local tabs = {}
table.insert(tabs, '\t')
table.insert(tabs, '\t\t')
table.insert(tabs, '\t\t\t')
table.insert(tabs, '\t\t\t\t')

function assignReturnValues(nrets, nargs, ntabs)
	tassert(nrets, 'number')
	local output = ''
	for i = 1, nrets do
		output = output..tabs[ntabs]..'ret'..i..' = to<RET_'..i..'>(L, -'..(nrets-i+1)..');\n' -- ret1 = to<RET_1>(L, -1);
	end
	return output
end

function pushArguments(nrets, nargs, ntabs)
	tassert(nargs, 'number')
	local output = ''
	for i = 1, nargs do
		output = output..tabs[ntabs]..'push(L, arg'..i..');\n'
	end
	return output
end

function hybridMember(nrets, nargs)
	tassert(nrets, 'number')
	tassert(nargs, 'number')
	return 'ConstReturn'..nrets..'Param'..nargs..'(lua_State* L, const char* scriptFunction, const CLASS& object'..CW.templateCallSignature(nrets, nargs, ', ')..')\n'
end

function hybridConst(nrets, nargs)
	tassert(nrets, 'number')
	tassert(nargs, 'number')
	return 'Member'..nrets..'Param'..nargs..'(lua_State* L, const char* scriptFunction, CLASS& object'..CW.templateCallSignature(nrets, nargs, ', ')..')\n'
end

function generateClassHybridCall(nrets, nargs, const)
	tassert(nrets, 'number')
	tassert(nargs, 'number')
	local name = 'hybrid'..(const and 'Const' or 'Member')..'Return'..nrets..'Param'..nargs
	local output = ''
	output = output..'/** '.. name..' */\n'
	output = output..'template<typename CLASS, '..CW.templateArguments(nrets, nargs)..', '..EN2S.endClassTemplateArgs(nrets, nargs, const) 
	output = output..'inline ScriptToNativeCallResult\n'
	output = output..'hybrid'..(const and hybridConst(nrets, nargs) or hybridMember(nrets, nargs))
	output = output..'{\t/*s: */\n'
	output = output..tabs[1]..'push(L, object);\n'
	output = output..tabs[1]..'/*s: object */\n'
	output = output..tabs[1]..'lua_getfield(L, -1, scriptFunction);\n'
	output = output..tabs[1]..'/*s: object ? */\n'
	output = output..tabs[1]..'if (lua_isfunction(L, -1)) \n'
	output = output..tabs[1]..'{	/*s: object scriptFunction */ \n'
	output = output..tabs[2]..		'lua_pushvalue(L, -2);\n'
	output = output..tabs[2]..		'/*s: object scriptFunction object */ \n'
	output = output..				pushArguments(nrets, nargs, 2)
	output = output..tabs[2]..		'/*s: object scriptFunction object (arguments) */ \n'
	output = output..tabs[2]..		'lua_call(L, '..(nargs+1)..'); \n'
	output = output..tabs[2]..		'/*s: object (return values) */ \n'
	output = output..				assignReturnValues(nrets, nargs, 2)
	output = output..tabs[2]..		'lua_pop(L, '..(nrets+1)..'); \n'
	output = output..tabs[2]..		'/*s: */ \n'
	output = output..tabs[2]..		'return lua_extension::functionSuccess; \n'
	output = output..tabs[1]..'} \n'
	output = output..tabs[1]..'else \n'
	output = output..tabs[1]..'{\t/*s: module nil */ \n'
	output = output..tabs[2]..	'lua_pop(L, 2);\n'
	output = output..tabs[2]..	'/*s: */ \n'
	output = output..tabs[2]..	CW.templateAssignReturnValues(nrets)..'(object.*nativeFunction)('..CW.templateFunctionCallArguments(nrets, nargs)..');\n'
	output = output..tabs[2]..	'return lua_extension::functionNotFound; \n'
	output = output..tabs[1]..'} \n'
	output = output..'}\n'
	output = output..'\n'
	return output
end

function generateClassHybridPCall(nrets, nargs, const)
	tassert(nrets, 'number')
	tassert(nargs, 'number') 
	local name = 'phybrid'..(const and 'Const' or 'Member')..'Return'..nrets..'Param'..nargs
	local output = ''
	output = output..'/** '..name..' */\n'
	output = output..'template<typename CLASS, '..CW.templateArguments(nrets, nargs)..', '..EN2S.endClassTemplateArgs(nrets, nargs, const) 
	output = output..'inline ScriptToNativeCallResult\n'
	output = output..'phybrid'..(const and hybridConst(nrets, nargs) or hybridMember(nrets, nargs))
	output = output..'{\t/*s: */\n'
	output = output..tabs[1]..'push(L, object);\n'
	output = output..tabs[1]..'/*s: object */\n'
	output = output..tabs[1]..'lua_getfield(L, -1, scriptFunction);\n'
	output = output..tabs[1]..'/*s: object ? */\n'
	output = output..tabs[1]..'if (lua_isfunction(L, -1)) \n'
	output = output..tabs[1]..'{	/*s: object scriptFunction */ \n'
	output = output..tabs[2]..		'lua_pushvalue(L, -2);\n'
	output = output..tabs[2]..		'/*s: object scriptFunction object */ \n'
	output = output..				pushArguments(nrets, nargs, 2)
	output = output..tabs[2]..		'/*s: object scriptFunction object (arguments) */ \n'
	output = output..tabs[2]..		'if (!Lua::callProtected((L, '..(nargs+1)..'))\n'
	output = output..tabs[2]..		'{\t/*s: object (return values) */ \n'
	output = output..					assignReturnValues(nrets, nargs, 3)
	output = output..tabs[3]..			'lua_pop(L, '..(nrets+1)..'); \n'
	output = output..tabs[3]..			'/*s: */ \n'
	output = output..tabs[3]..			'return lua_extension::functionSuccess; \n'
	output = output..tabs[2]..		'} \n'
	output = output..tabs[2]..		'else\n'
	output = output..tabs[2]..		'{\t/*s: object */\n'
	output = output..tabs[3]..			'lua_pop(L, 1);\n'
	output = output..tabs[3]..			'/*s: */\n'
	output = output..tabs[3]..			'return lua_extension::functionError;\n'
	output = output..tabs[2]..		'} \n'
	output = output..tabs[1]..'else \n'
	output = output..tabs[1]..'{\t/*s: module nil */\n'
	output = output..tabs[2]..	'lua_pop(L, 2);\n'
	output = output..tabs[2]..	'/*s: */ \n'
	output = output..tabs[2]..	CW.templateAssignReturnValues(nrets)..'(object.*nativeFunction)('..CW.templateFunctionCallArguments(nrets, nargs)..');\n'
	output = output..tabs[2]..	'return lua_extension::functionNotFound; \n'
	output = output..tabs[1]..'} \n'
	output = output..'} // '..name..'\n'
	output = output..'\n'
	return output
end

function generateHeader(file, nrets, nargs)
	tassert(file, 'userdata')
	tassert(nrets, 'number')
	tassert(nargs, 'number')
	local output 
	--[[
	output = "typedef enum ScriptToNativeCallResult\n"..
	"{\n"..
	"	functionSuccess=0,\n"..
	"	functionNotFound,\n"..
	"	functionError,\n"..
	"	moduleNotFound\n"..
	"}; // ScriptToNativeCallResult\n"
	file:write(output)
	output = "template<typename CLASS, void(CLASS::* nativeFunction)(void) const>\n"..
	"inline ScriptToNativeCallResult \n"..
	"	hybridConstReturn0Param0(lua_State* L, const char* scriptFunction, const CLASS& object)\n"..
	"{\n"..
	"	push(L, object);					/*s: object */\n"..
	"	lua_getfield(L, -1, scriptFunction);/*s: object ? */\n"..
	"	if (lua_isfunction(L, -1))\n"..
	"	{									/*s: object scriptFunction */\n"..
	"		lua_pushvalue(L, -2);			/*s: object scriptFunction object */\n"..
	"		lua_call(L, 1, 0);				/*s: object */\n"..
	"		lua_pop(L, 1);					/*s: */\n"..
	"		return lua_extension::functionSuccess;\n"..
	"	}\n"..
	"	else\n"..
	"	{									/*s: module nil */\n"..
	"		lua_pop(L, 2);					/*s: */\n"..
	"		(object.*nativeFunction)();\n"..
	"		return lua_extension::functionNotFound;\n"..
	"	}\n"..
	"}\n"
	file:write(output)
	output = "template<typename CLASS, void(CLASS::* nativeFunction)(void) const>\n"..
	"inline ScriptToNativeCallResult \n"..
	"	phybridConstReturn0Param0(lua_State* L, const char* scriptFunction, const CLASS& object)\n"..
	"{\n"..
	"	push(L, object);					/*s: object */\n"..
	"	lua_getfield(L, -1, scriptFunction);/*s: object ? */\n"..
	"	if (lua_isfunction(L, -1))\n"..
	"	{									/*s: object scriptFunction */\n"..
	"		lua_pushvalue(L, -2);			/*s: object scriptFunction object */\n"..
	"		if (!Lua::callProtected(L, 1, 0))\n"..
	"		{								/*s: object */\n"..
	"			lua_pop(L, 1);				/*s: */\n"..
	"			return lua_extension::functionSuccess;\n"..
	"		}\n"..
	"		else\n"..
	"		{								/*s: object */\n"..
	"			lua_pop(L, 1);				/*s: */\n"..
	"			return lua_extension::functionError;\n"..
	"		}				\n"..
	"	}\n"..
	"	else\n"..
	"	{									/*s: object nil */\n"..
	"		lua_pop(L, 2);					/*s: */\n"..
	"		(object.*nativeFunction)();\n"..
	"		return lua_extension::functionNotFound;\n"..
	"	}\n"..
	"}\n"..
	"\n"
	file:write(output)
	output = "template<typename CLASS, void(CLASS::* nativeFunction)(void)>\n"..
	"inline ScriptToNativeCallResult \n"..
	"	hybridMemberReturn0Param0(lua_State* L, const char* scriptFunction, CLASS& object)\n"..
	"{\n"..
	"	push(L, object);					/*s: object */\n"..
	"	lua_getfield(L, -1, scriptFunction);/*s: object ? */\n"..
	"	if (lua_isfunction(L, -1))\n"..
	"	{									/*s: object scriptFunction */\n"..
	"		lua_pushvalue(L, -2);			/*s: object scriptFunction object */\n"..
	"		lua_call(L, 1, 0);				/*s: object */\n"..
	"		lua_pop(L, 1);					/*s: */\n"..
	"		return lua_extension::functionSuccess;\n"..
	"	}\n"..
	"	else\n"..
	"	{									/*s: module nil */\n"..
	"		lua_pop(L, 2);					/*s: */\n"..
	"		(object.*nativeFunction)();\n"..
	"		return lua_extension::functionNotFound;\n"..
	"	}\n"..
	"}\n"
	file:write(output)
	output = "template<typename CLASS, void(CLASS::* nativeFunction)(void)>\n"..
	"inline ScriptToNativeCallResult \n"..
	"	phybridMemberReturn0Param0(lua_State* L, const char* scriptFunction, CLASS& object)\n"..
	"{\n"..
	"	push(L, object);					/*s: object */\n"..
	"	lua_getfield(L, -1, scriptFunction);/*s: object ? */\n"..
	"	if (lua_isfunction(L, -1))\n"..
	"	{									/*s: object scriptFunction */\n"..
	"		lua_pushvalue(L, -2);			/*s: object scriptFunction object */\n"..
	"		if (!Lua::callProtected(L, 1, 0))\n"..
	"		{								/*s: object */\n"..
	"			lua_pop(L, 1);				/*s: */\n"..
	"			return lua_extension::functionSuccess;\n"..
	"		}\n"..
	"		else\n"..
	"		{								/*s: object */\n"..
	"			lua_pop(L, 1);				/*s: */\n"..
	"			return lua_extension::functionError;\n"..
	"		}				\n"..
	"	}\n"..
	"	else\n"..
	"	{									/*s: object nil */\n"..
	"		lua_pop(L, 2);					/*s: */\n"..
	"		(object.*nativeFunction)();\n"..
	"		return lua_extension::functionNotFound;\n"..
	"	}\n"..
	"}\n"
	file:write(output)
	output = "inline ScriptToNativeCallResult \n"..
	"	callStaticReturn0Param0(lua_State* L, const char* scriptFunction, const char* module=\"_G\")\n"..
	"{\n"..
	"	lua_getglobal(L, module);				/*s: ? */\n"..
	"	if (lua_istable(L, -1))					\n"..
	"	{\n"..
	"		lua_getfield(L, -1, scriptFunction);/*s: module ? */\n"..
	"		if (lua_isfunction(L, -1))\n"..
	"		{									/*s: module scriptFunction */\n"..
	"			lua_call(L, 0, 0);				/*s: module */\n"..
	"			lua_pop(L, 1);					/*s: */\n"..
	"			return lua_extension::functionSuccess;\n"..
	"		}\n"..
	"		else\n"..
	"		{									/*s: module nil */\n"..
	"			lua_pop(L, 2);					/*s: */\n"..
	"			return lua_extension::functionNotFound;\n"..
	"		}\n"..
	"	}\n"..
	"	else\n"..
	"	{										/*s: !table */\n"..
	"		lua_pop(L, 1);\n"..
	"		return lua_extension::moduleNotFound;\n"..
	"	}\n"..
	"}\n"
	file:write(output)
	output = "template<void(* nativeFunction)(void)>\n"..
	"inline ScriptToNativeCallResult \n"..
	"	hybridStaticReturn0Param0(lua_State* L, const char* scriptFunction, const char* module=\"_G\")\n"..
	"{	\n"..
	"	lua_getglobal(L, module);				/*s: ? */\n"..
	"	if (lua_istable(L, -1))					\n"..
	"	{\n"..
	"		lua_getfield(L, -1, scriptFunction);/*s: module ? */\n"..
	"		if (lua_isfunction(L, -1))\n"..
	"		{									/*s: module scriptFunction */\n"..
	"			lua_call(L, 0, 0);				/*s: module */\n"..
	"			lua_pop(L, 1);					/*s: */\n"..
	"			return lua_extension::functionSuccess;\n"..
	"		}\n"..
	"		else\n"..
	"		{									/*s: module nil */\n"..
	"			lua_pop(L, 2);					/*s: */\n"..
	"			(*nativeFunction)();\n"..
	"			return lua_extension::functionNotFound;\n"..
	"		}\n"..
	"	}\n"..
	"	else\n"..
	"	{										/*s: !table */\n"..
	"		lua_pop(L, 1);\n"..
	"		(*nativeFunction)();\n"..
	"		return lua_extension::moduleNotFound;\n"..
	"	}\n"..
	"}\n"
	file:write(output)
	output = "inline ScriptToNativeCallResult \n"..
	"	pcallStaticReturn0Param0(lua_State* L, const char* scriptFunction, const char* module=\"_G\")\n"..
	"{\n"..
	"	lua_getglobal(L, module);				/*s: ? */\n"..
	"	if (lua_istable(L, -1))					\n"..
	"	{\n"..
	"		lua_getfield(L, -1, scriptFunction);/*s: module ? */\n"..
	"		if (lua_isfunction(L, -1))\n"..
	"		{									/*s: module scriptFunction */\n"..
	"			if (!Lua::callProtected(L, 0, 0))\n"..
	"			{								/*s: module */\n"..
	"				lua_pop(L, 1);				/*s: */\n"..
	"				return lua_extension::functionSuccess;\n"..
	"			}\n"..
	"			else\n"..
	"			{								/*s: module */\n"..
	"				lua_pop(L, 1);				/*s: */\n"..
	"				return lua_extension::functionError;\n"..
	"			}\n"..
	"		}\n"..
	"		else\n"..
	"		{									/*s: module nil */\n"..
	"			lua_pop(L, 2);					/*s: */\n"..
	"			return lua_extension::functionNotFound;\n"..
	"		}\n"..
	"	}\n"..
	"	else\n"..
	"	{										/*s: !table */\n"..
	"		lua_pop(L, 1);						/*s: */\n"..
	"		return lua_extension::moduleNotFound;\n"..
	"	}						\n"..
	"}\n"
	file:write(output)
	output = "template<void(* nativeFunction)(void)>\n"..
	"inline ScriptToNativeCallResult \n"..
	"	phybridStaticReturn0Param0(lua_State* L, const char* scriptFunction, const char* module=\"_G\")\n"..
	"{	\n"..
	"	lua_getglobal(L, module);				/*s: ? */\n"..
	"	if (lua_istable(L, -1))					\n"..
	"	{\n"..
	"		lua_getfield(L, -1, scriptFunction);/*s: module ? */\n"..
	"		if (lua_isfunction(L, -1))\n"..
	"		{									/*s: module scriptFunction */\n"..
	"			if (!Lua::callProtected(L, 0, 0))\n"..
	"			{								/*s: module */\n"..
	"				lua_pop(L, 1);				/*s: */\n"..
	"				return lua_extension::functionSuccess;\n"..
	"			}\n"..
	"			else\n"..
	"			{								/*s: module */\n"..
	"				lua_pop(L, 1);				/*s: */\n"..
	"				return lua_extension::functionError;\n"..
	"			}\n"..
	"		}\n"..
	"		else\n"..
	"		{									/*s: module nil */\n"..
	"			lua_pop(L, 2);					/*s: */\n"..
	"			(*nativeFunction)();\n"..
	"			return lua_extension::functionNotFound;\n"..
	"		}\n"..
	"	}\n"..
	"	else\n"..
	"	{										/*s: !table */\n"..
	"		lua_pop(L, 1);\n"..
	"		(*nativeFunction)();\n"..
	"		return lua_extension::moduleNotFound;\n"..
	"	}\n"..
	"}"
	file:write(output)
	--]]
	---[[
	for i = 0, nrets do
		for j = 0, nargs do
			if i ~= 0 or j ~= 0 then
				local output = ''
				-- generateClassHybridPCall
				output = output..generateClassHybridPCall(i, j)
				output = output..generateClassHybridPCall(i, j, true)
				-- generateClassHybridCall
				output = output..generateClassHybridCall(i, j)
				output = output..generateClassHybridCall(i, j, true)
				-- write the current functions to file
				file:write(output)
			end
		end
	end
	--]]
	-- save the file
	file:flush()
end