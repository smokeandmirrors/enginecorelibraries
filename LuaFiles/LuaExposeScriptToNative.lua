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

function callNotFound(nrets, nargs, hybrid, ntabs)
	if hybrid then
		return tabs[ntabs]..CW.templateAssignReturnValues(nrets)..'(*nativeFunction)('..CW.templateFunctionCallArguments(nrets, nargs)..');\n'
	else
		return ''
	end
end

function assignReturnValues(nrets, nargs, ntabs)
	tassert('number', nrets)
	local output = ''
	for i = 1, nrets do
		output = output..tabs[ntabs]..'ret'..i..' = to<RET_'..i..'>(L, -'..(nrets-i+1)..');\n' -- ret1 = to<RET_1>(L, -1);
	end
	return output
end

function pushArguments(nrets, nargs, ntabs)
	tassert('number', nargs)
	local output = ''
	for i = 1, nargs do
		output = output..tabs[ntabs]..'push(L, arg'..i..');\n'
	end
	return output
end

function hybridMember(nrets, nargs)
	tassert('number', nrets, nargs)
    return 'MemberReturn'..nrets..'Param'..nargs..'(lua_State* L, const char* scriptFunction, CLASS& object'..CW.templateCallSignature(nrets, nargs, ', ')..')\n'
end

function hybridConst(nrets, nargs)
	tassert('number', nrets, nargs)
    return 'ConstReturn'..nrets..'Param'..nargs..'(lua_State* L, const char* scriptFunction, const CLASS& object'..CW.templateCallSignature(nrets, nargs, ', ')..')\n'
end

function static(nrets, nargs)
	return 'StaticReturn'..nrets..'Param'..nargs..'(lua_State* L, const char* scriptFunction, '..CW.templateCallSignature(nrets, nargs)..', const char* module=\"_G\")\n'
end

function generateClassHybridCall(nrets, nargs, const)
	tassert('number', nrets, nargs)
    local name = 'hybrid'..(const and 'Const' or 'Member')..'Return'..nrets..'Param'..nargs
	local output = ''
	output = output..'/** '.. name..' */\n'
	output = output..'template<typename CLASS, '..CW.templateArguments(nrets, nargs)..', '..EN2S.endClassTemplateArgs(nrets, nargs, const, 'nativeFunction') 
	output = output..'inline ScriptToNativeCallResult\n'
	output = output..'hybrid'..(const and hybridConst(nrets, nargs) or hybridMember(nrets, nargs))
	output = output..'{\t/*s: */\n'
	output = output..tabs[1]..'push(L, object);\n'
	output = output..tabs[1]..'/*s: object */\n'
	output = output..tabs[1]..'lua_getfield(L, -1, scriptFunction);\n'
	output = output..tabs[1]..'/*s: object ? */\n'
	output = output..tabs[1]..'if (lua_isfunction(L, -1)) \n'
	output = output..tabs[1]..'{	/*s: object scriptFunction */ \n'
	output = output..tabs[2]..		'push(L, object);\n'
	output = output..tabs[2]..		'/*s: object scriptFunction object */ \n'
	output = output..				pushArguments(nrets, nargs, 2)
	output = output..tabs[2]..		'/*s: object scriptFunction object (arguments) */ \n'
	output = output..tabs[2]..		'lua_call(L, '..(nargs+1)..', '..nrets..'); \n'
	output = output..tabs[2]..		'/*s: object (return values) */ \n'
	output = output..				assignReturnValues(nrets, nargs, 2)
	output = output..tabs[2]..		'lua_pop(L, '..(nrets+1)..'); \n'
	output = output..tabs[2]..		'/*s: */ \n'
	output = output..tabs[2]..		'return embeddedLua::functionSuccess; \n'
	output = output..tabs[1]..'} \n'
	output = output..tabs[1]..'else \n'
	output = output..tabs[1]..'{\t/*s: module nil */ \n'
	output = output..tabs[2]..	'lua_pop(L, 2);\n'
	output = output..tabs[2]..	'/*s: */ \n'
	output = output..tabs[2]..	CW.templateAssignReturnValues(nrets)..'(object.*nativeFunction)('..CW.templateFunctionCallArguments(nrets, nargs)..');\n'
	output = output..tabs[2]..	'return embeddedLua::functionNotFound; \n'
	output = output..tabs[1]..'} \n'
	output = output..'} //'..name
	output = output..'\n\n'
	return output
end

function generateClassHybridPCall(nrets, nargs, const)
	tassert('number', nrets)
	tassert('number', nargs) 
	local name = 'phybrid'..(const and 'Const' or 'Member')..'Return'..nrets..'Param'..nargs
	local output = ''
	output = output..'/** '..name..' */\n'
	output = output..'template<typename CLASS, '..CW.templateArguments(nrets, nargs)..', '..EN2S.endClassTemplateArgs(nrets, nargs, const, 'nativeFunction') 
	output = output..'inline ScriptToNativeCallResult\n'
	output = output..'phybrid'..(const and hybridConst(nrets, nargs) or hybridMember(nrets, nargs))
	output = output..'{\t/*s: */\n'
	output = output..tabs[1]..'push(L, object);\n'
	output = output..tabs[1]..'/*s: object */\n'
	output = output..tabs[1]..'lua_getfield(L, -1, scriptFunction);\n'
	output = output..tabs[1]..'/*s: object ? */\n'
	output = output..tabs[1]..'if (lua_isfunction(L, -1)) \n'
	output = output..tabs[1]..'{	/*s: object scriptFunction */ \n'
	output = output..tabs[2]..		'push(L, object);\n'
	output = output..tabs[2]..		'/*s: object scriptFunction object */ \n'
	output = output..				pushArguments(nrets, nargs, 2)
	output = output..tabs[2]..		'/*s: object scriptFunction object (arguments) */ \n'
	output = output..tabs[2]..		'if (!Lua::callProtected(L, '..(nargs+1)..', '..nrets..'))\n'
	output = output..tabs[2]..		'{\t/*s: object (return values) */ \n'
	output = output..					assignReturnValues(nrets, nargs, 3)
	output = output..tabs[3]..			'lua_pop(L, '..(nrets+1)..'); \n'
	output = output..tabs[3]..			'/*s: */ \n'
	output = output..tabs[3]..			'return embeddedLua::functionSuccess; \n'
	output = output..tabs[2]..		'} \n'
	output = output..tabs[2]..		'else\n'
	output = output..tabs[2]..		'{\t/*s: object */\n'
	output = output..tabs[3]..			'lua_pop(L, 1);\n'
	output = output..tabs[3]..			'/*s: */\n'
	output = output..tabs[3]..			'return embeddedLua::functionError;\n'
	output = output..tabs[2]..		'} \n'
	output = output..tabs[1]..'}\n'
	output = output..tabs[1]..'else \n'
	output = output..tabs[1]..'{\t/*s: module nil */\n'
	output = output..tabs[2]..	'lua_pop(L, 2);\n'
	output = output..tabs[2]..	'/*s: */ \n'
	output = output..tabs[2]..	CW.templateAssignReturnValues(nrets)..'(object.*nativeFunction)('..CW.templateFunctionCallArguments(nrets, nargs)..');\n'
	output = output..tabs[2]..	'return embeddedLua::functionNotFound; \n'
	output = output..tabs[1]..'} \n'
	output = output..'} // '..name..'\n'
	output = output..'\n'
	return output
end

function generateStaticCall(nrets, nargs, hybrid)
	tassert('number', nrets, nargs)
    local name = (hybrid and 'hybrid' or 'call')..'StaticReturn'..nrets..'Param'..nargs
	local output = ''
	output = output..'/** '.. name..' */\n'
	if hybrid then
		output = output..'template<'..CW.templateArguments(nrets, nargs)..', '..EN2S.endStaticTemplateArgs(nrets, nargs, 'nativeFunction')
	else
		output = output..'template<'..CW.templateArguments(nrets, nargs)..'>'
	end
	output = output..'inline ScriptToNativeCallResult\n'
	output = output..(hybrid and 'hybrid' or 'call')..static(nrets, nargs)
	output = output..'{\t/*s: */\n'
	output = output..tabs[1]..'lua_getglobal(L, module);\n'
	output = output..tabs[1]..'/*s: ? */\n'
	output = output..tabs[1]..'if (lua_istable(L, -1))\n'
	output = output..tabs[1]..'{	/*s: module */\n'
	output = output..tabs[2]..		'lua_getfield(L, -1, scriptFunction);\n'
	output = output..tabs[2]..		'/*s: module ? */\n'
	output = output..tabs[2]..		'if (lua_isfunction(L, -1))\n'
	output = output..tabs[2]..		'{	/*s: module scriptFunction */\n'
	output = output..					pushArguments(nrets, nargs, 3)
	output = output..tabs[3]..			'/*s: module scriptFunction (arguments) */\n'
	output = output..tabs[3]..			'lua_call(L, '..nargs..', '..nrets..');\n'
	output = output..tabs[3]..			'/*s: module (return values) */\n'
	output = output..					assignReturnValues(nrets, nargs, 3)
	output = output..tabs[3]..			'lua_pop(L, '..(nrets+1)..');\n'
	output = output..tabs[3]..			'/*s: */\n'
	output = output..tabs[3]..			'return embeddedLua::functionSuccess;\n'
	output = output..tabs[2]..		'}\n'
	output = output..tabs[2]..		'else\n'
	output = output..tabs[2]..		'{\t/*s: module nil */\n'
	output = output..tabs[3]..			'lua_pop(L, 2);\n'
	output = output..tabs[3]..			'/*s: */\n'
	output = output..					callNotFound(nrets, nargs, hybrid, 3)
	output = output..tabs[3]..			'return embeddedLua::functionNotFound;\n'
	output = output..tabs[2]..		'}\n'
	output = output..tabs[1]..'}\n'
	output = output..tabs[1]..'else\n'
	output = output..tabs[1]..'{\t/*s: !table */ \n'
	output = output..tabs[2]..	'lua_pop(L, 1);\n'
	output = output..tabs[2]..	'/*s: */ \n'
	output = output..			callNotFound(nrets, nargs, hybrid, 2)
	output = output..tabs[2]..	'return embeddedLua::moduleNotFound; \n'
	output = output..tabs[1]..'} \n'
	output = output..'} // '..name..'\n\n'
	return output
end

function generateStaticPCall(nrets, nargs, hybrid)
	tassert('number', nrets)
	tassert('number', nargs) 
	local name = 'p'..(hybrid and 'hybrid' or 'call')..'StaticReturn'..nrets..'Param'..nargs
	local output = ''
	output = output..'/** '..name..' */\n'
	if hybrid then
		output = output..'template<'..CW.templateArguments(nrets, nargs)..', '..EN2S.endStaticTemplateArgs(nrets, nargs, 'nativeFunction')
	else
		output = output..'template<'..CW.templateArguments(nrets, nargs)..'>'
	end
	output = output..'inline ScriptToNativeCallResult\n'
	output = output..'p'..(hybrid and 'hybrid' or 'call')..static(nrets, nargs)
	output = output..'{\t/*s: */\n'
	output = output..tabs[1]..'lua_getglobal(L, module);\n'
	output = output..tabs[1]..'/*s: ? */\n'
	output = output..tabs[1]..'if (lua_istable(L, -1))\n'
	output = output..tabs[1]..'{	/*s: module */\n'
	output = output..tabs[2]..		'lua_getfield(L, -1, scriptFunction);\n'
	output = output..tabs[2]..		'/*s: module ? */\n'
	output = output..tabs[2]..		'if (lua_isfunction(L, -1))\n'
	output = output..tabs[2]..		'{	/*s: module scriptFunction */\n'
	output = output..					pushArguments(nrets, nargs, 3)
	output = output..tabs[3]..			'/*s: module scriptFunction (arguments) */\n'
	output = output..tabs[3]..			'if (!Lua::callProtected(L, '..nargs..', '..nrets..'))\n'
	output = output..tabs[3]..			'{\t/*s: module (return values) */ \n'
	output = output..						assignReturnValues(nrets, nargs, 4)
	output = output..tabs[4]..				'lua_pop(L, '..(nrets+1)..'); \n'
	output = output..tabs[4]..				'/*s: */ \n'
	output = output..tabs[4]..				'return embeddedLua::functionSuccess;\n'
	output = output..tabs[3]..			'} \n'
	output = output..tabs[3]..			'else\n'
	output = output..tabs[3]..			'{\t/*s: module */\n'
	output = output..tabs[4]..				'lua_pop(L, 1);\n'
	output = output..tabs[4]..				'/*s: */\n'
	output = output..tabs[4]..				'return embeddedLua::functionError;\n'
	output = output..tabs[3]..			'} \n'
	output = output..tabs[2]..		'}\n'
	output = output..tabs[2]..		'else\n'
	output = output..tabs[2]..		'{\t/*s: module nil */\n'
	output = output..tabs[3]..			'lua_pop(L, 2);\n'
	output = output..tabs[3]..			'/*s: */\n'
	output = output..					callNotFound(nrets, nargs, hybrid, 3)
	output = output..tabs[3]..			'return embeddedLua::functionNotFound;\n'
	output = output..tabs[2]..		'}\n'
	output = output..tabs[1]..'}\n'
	output = output..tabs[1]..'else\n'
	output = output..tabs[1]..'{\t/*s: !table */ \n'
	output = output..tabs[2]..	'lua_pop(L, 1);\n'
	output = output..tabs[2]..	'/*s: */ \n'
	output = output..			callNotFound(nrets, nargs, hybrid, 2)
	output = output..tabs[2]..	'return embeddedLua::moduleNotFound; \n'
	output = output..tabs[1]..'} \n'
	output = output..'} // '..name..'\n\n'
	return output
end

function generateHeader(file, nrets, nargs)
	tassert('userdata', file)
	tassert('number', nrets, nargs)
    local output = "namespace embeddedLua\n{\n" 
	output = output.."typedef enum ScriptToNativeCallResult\n"..
	"{\n"..
	"	functionSuccess=0,\n"..
	"	functionNotFound,\n"..
	"	functionError,\n"..
	"	moduleNotFound\n"..
	"}; // ScriptToNativeCallResult\n\n"
	file:write(output)
	
	output = "/** callStaticReturn0Param0 */\ninline ScriptToNativeCallResult \n"..
	"callStaticReturn0Param0(lua_State* L, const char* scriptFunction, const char* module=\"_G\")\n"..
	"{\n"..
	"	lua_getglobal(L, module);				/*s: ? */\n"..
	"	if (lua_istable(L, -1))					\n"..
	"	{\n"..
	"		lua_getfield(L, -1, scriptFunction);/*s: module ? */\n"..
	"		if (lua_isfunction(L, -1))\n"..
	"		{									/*s: module scriptFunction */\n"..
	"			lua_call(L, 0, 0);				/*s: module */\n"..
	"			lua_pop(L, 1);					/*s: */\n"..
	"			return embeddedLua::functionSuccess;\n"..
	"		}\n"..
	"		else\n"..
	"		{									/*s: module nil */\n"..
	"			lua_pop(L, 2);					/*s: */\n"..
	"			return embeddedLua::functionNotFound;\n"..
	"		}\n"..
	"	}\n"..
	"	else\n"..
	"	{										/*s: !table */\n"..
	"		lua_pop(L, 1);\n"..
	"		return embeddedLua::moduleNotFound;\n"..
	"	}\n"..
	"} // callStaticReturn0Param0\n\n"
	file:write(output)
	
	output = "/** hybridConstReturn0Param0 */\ntemplate<typename CLASS, void(CLASS::* nativeFunction)(void) const>\n"..
	"inline ScriptToNativeCallResult \n"..
	"hybridConstReturn0Param0(lua_State* L, const char* scriptFunction, const CLASS& object)\n"..
	"{\n"..
	"	push(L, object);					/*s: object */\n"..
	"	lua_getfield(L, -1, scriptFunction);/*s: object ? */\n"..
	"	if (lua_isfunction(L, -1))\n"..
	"	{									/*s: object scriptFunction */\n"..
	"		push(L, object);				/*s: object scriptFunction object */\n"..
	"		lua_call(L, 1, 0);				/*s: object */\n"..
	"		lua_pop(L, 1);					/*s: */\n"..
	"		return embeddedLua::functionSuccess;\n"..
	"	}\n"..
	"	else\n"..
	"	{									/*s: module nil */\n"..
	"		lua_pop(L, 2);					/*s: */\n"..
	"		(object.*nativeFunction)();\n"..
	"		return embeddedLua::functionNotFound;\n"..
	"	}\n"..
	"} // hybridConstReturn0Param0\n\n"
	file:write(output)
	
	output = "/** hybridMemberReturn0Param0 */\ntemplate<typename CLASS, void(CLASS::* nativeFunction)(void)>\n"..
	"inline ScriptToNativeCallResult \n"..
	"hybridMemberReturn0Param0(lua_State* L, const char* scriptFunction, CLASS& object)\n"..
	"{\n"..
	"	push(L, object);					/*s: object */\n"..
	"	lua_getfield(L, -1, scriptFunction);/*s: object ? */\n"..
	"	if (lua_isfunction(L, -1))\n"..
	"	{									/*s: object scriptFunction */\n"..
	"		push(L, object);				/*s: object scriptFunction object */\n"..
	"		lua_call(L, 1, 0);				/*s: object */\n"..
	"		lua_pop(L, 1);					/*s: */\n"..
	"		return embeddedLua::functionSuccess;\n"..
	"	}\n"..
	"	else\n"..
	"	{									/*s: module nil */\n"..
	"		lua_pop(L, 2);					/*s: */\n"..
	"		(object.*nativeFunction)();\n"..
	"		return embeddedLua::functionNotFound;\n"..
	"	}\n"..
	"} // hybridMemberReturn0Param0\n\n"
	file:write(output)
		
	output = "/** hybridStaticReturn0Param0 */\ntemplate<void(* nativeFunction)(void)>\n"..
	"inline ScriptToNativeCallResult \n"..
	"hybridStaticReturn0Param0(lua_State* L, const char* scriptFunction, const char* module=\"_G\")\n"..
	"{	\n"..
	"	lua_getglobal(L, module);				/*s: ? */\n"..
	"	if (lua_istable(L, -1))					\n"..
	"	{\n"..
	"		lua_getfield(L, -1, scriptFunction);/*s: module ? */\n"..
	"		if (lua_isfunction(L, -1))\n"..
	"		{									/*s: module scriptFunction */\n"..
	"			lua_call(L, 0, 0);				/*s: module */\n"..
	"			lua_pop(L, 1);					/*s: */\n"..
	"			return embeddedLua::functionSuccess;\n"..
	"		}\n"..
	"		else\n"..
	"		{									/*s: module nil */\n"..
	"			lua_pop(L, 2);					/*s: */\n"..
	"			(*nativeFunction)();\n"..
	"			return embeddedLua::functionNotFound;\n"..
	"		}\n"..
	"	}\n"..
	"	else\n"..
	"	{										/*s: !table */\n"..
	"		lua_pop(L, 1);\n"..
	"		(*nativeFunction)();\n"..
	"		return embeddedLua::moduleNotFound;\n"..
	"	}\n"..
	"} // hybridStaticReturn0Param0\n\n"
	file:write(output)
	
	output = "/** pcallStaticReturn0Param0 */\ninline ScriptToNativeCallResult \n"..
	"pcallStaticReturn0Param0(lua_State* L, const char* scriptFunction, const char* module=\"_G\")\n"..
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
	"				return embeddedLua::functionSuccess;\n"..
	"			}\n"..
	"			else\n"..
	"			{								/*s: module */\n"..
	"				lua_pop(L, 1);				/*s: */\n"..
	"				return embeddedLua::functionError;\n"..
	"			}\n"..
	"		}\n"..
	"		else\n"..
	"		{									/*s: module nil */\n"..
	"			lua_pop(L, 2);					/*s: */\n"..
	"			return embeddedLua::functionNotFound;\n"..
	"		}\n"..
	"	}\n"..
	"	else\n"..
	"	{										/*s: !table */\n"..
	"		lua_pop(L, 1);						/*s: */\n"..
	"		return embeddedLua::moduleNotFound;\n"..
	"	}						\n"..
	"} // pcallStaticReturn0Param0\n\n"
	file:write(output)
	
	output = "/** phybridConstReturn0Param0 */\ntemplate<typename CLASS, void(CLASS::* nativeFunction)(void) const>\n"..
	"inline ScriptToNativeCallResult \n"..
	"phybridConstReturn0Param0(lua_State* L, const char* scriptFunction, const CLASS& object)\n"..
	"{\n"..
	"	push(L, object);					/*s: object */\n"..
	"	lua_getfield(L, -1, scriptFunction);/*s: object ? */\n"..
	"	if (lua_isfunction(L, -1))\n"..
	"	{									/*s: object scriptFunction */\n"..
	"		push(L, object);				/*s: object scriptFunction object */\n"..
	"		if (!Lua::callProtected(L, 1, 0))\n"..
	"		{								/*s: object */\n"..
	"			lua_pop(L, 1);				/*s: */\n"..
	"			return embeddedLua::functionSuccess;\n"..
	"		}\n"..
	"		else\n"..
	"		{								/*s: object */\n"..
	"			lua_pop(L, 1);				/*s: */\n"..
	"			return embeddedLua::functionError;\n"..
	"		}				\n"..
	"	}\n"..
	"	else\n"..
	"	{									/*s: object nil */\n"..
	"		lua_pop(L, 2);					/*s: */\n"..
	"		(object.*nativeFunction)();\n"..
	"		return embeddedLua::functionNotFound;\n"..
	"	}\n"..
	"} // phybridConstReturn0Param0\n\n"
	file:write(output)
	
	output = "/** phybridMemberReturn0Param0 */\ntemplate<typename CLASS, void(CLASS::* nativeFunction)(void)>\n"..
	"inline ScriptToNativeCallResult \n"..
	"phybridMemberReturn0Param0(lua_State* L, const char* scriptFunction, CLASS& object)\n"..
	"{\n"..
	"	push(L, object);					/*s: object */\n"..
	"	lua_getfield(L, -1, scriptFunction);/*s: object ? */\n"..
	"	if (lua_isfunction(L, -1))\n"..
	"	{									/*s: object scriptFunction */\n"..
	"		push(L, object);				/*s: object scriptFunction object */\n"..
	"		if (!Lua::callProtected(L, 1, 0))\n"..
	"		{								/*s: object */\n"..
	"			lua_pop(L, 1);				/*s: */\n"..
	"			return embeddedLua::functionSuccess;\n"..
	"		}\n"..
	"		else\n"..
	"		{								/*s: object */\n"..
	"			lua_pop(L, 1);				/*s: */\n"..
	"			return embeddedLua::functionError;\n"..
	"		}				\n"..
	"	}\n"..
	"	else\n"..
	"	{									/*s: object nil */\n"..
	"		lua_pop(L, 2);					/*s: */\n"..
	"		(object.*nativeFunction)();\n"..
	"		return embeddedLua::functionNotFound;\n"..
	"	}\n"..
	"} // phybridMemberReturn0Param0\n\n"
	file:write(output)
	
	output = "/** phybridStaticReturn0Param0 */\ntemplate<void(* nativeFunction)(void)>\n"..
	"inline ScriptToNativeCallResult \n"..
	"phybridStaticReturn0Param0(lua_State* L, const char* scriptFunction, const char* module=\"_G\")\n"..
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
	"				return embeddedLua::functionSuccess;\n"..
	"			}\n"..
	"			else\n"..
	"			{								/*s: module */\n"..
	"				lua_pop(L, 1);				/*s: */\n"..
	"				return embeddedLua::functionError;\n"..
	"			}\n"..
	"		}\n"..
	"		else\n"..
	"		{									/*s: module nil */\n"..
	"			lua_pop(L, 2);					/*s: */\n"..
	"			(*nativeFunction)();\n"..
	"			return embeddedLua::functionNotFound;\n"..
	"		}\n"..
	"	}\n"..
	"	else\n"..
	"	{										/*s: !table */\n"..
	"		lua_pop(L, 1);\n"..
	"		(*nativeFunction)();\n"..
	"		return embeddedLua::moduleNotFound;\n"..
	"	}\n"..
	"} // phybridStaticReturn0Param0\n\n "
	file:write(output)
	
	for i = 0, nrets do
		for j = 0, nargs do
			if i ~= 0 or j ~= 0 then
				local output = ''
				-- callStatic
				output = output..generateStaticCall(i, j)
				-- hybridConst
				output = output..generateClassHybridCall(i, j, true)
				-- hybridMember
				output = output..generateClassHybridCall(i, j)
				-- hybridStatic
				output = output..generateStaticCall(i, j, true)
				-- pcallStatic
				output = output..generateStaticPCall(i, j)
				-- phybridConst
				output = output..generateClassHybridPCall(i, j, true)
				-- phybridMember
				output = output..generateClassHybridPCall(i, j)
				-- phybridStatic
				output = output..generateStaticPCall(i, j, true)
				-- write the current functions to file
				file:write(output)
			end
		end
	end
	
	file:write("} // namespace embeddedLua")
	file:flush()
end