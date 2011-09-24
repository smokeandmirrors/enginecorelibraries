module(..., package.seeall)

local U = require'Utilities'
local CW = require'CodeWriting'
local getTabs = U.getTabs

-- replaces EN2S_BEGIN_CLASS_TEMPLATE_ARGS
function beginClassTemplateArgs()

end

function callArguments(nrets, nargs, tabs)
	tassert(nrets, 'number')
	tassert(nargs, 'number')
	local output = ''
	if nrets < 2 and nargs == 0 then
		return output
	end
	if nrets > 1 then
		output = output..('ret2') 
	end
	for i = 3, nrets do
		output = output..(', ret'..i)
	end	
	if nargs > 0 then
		if nrets > 1 then
			output = output..(',\n'..getTabs(tabs)..'to<ARG_1>(L, -'..(nargs - 1 + 1)..')')
		else
			output = output..('to<ARG_1>(L, -'..(nargs - 1 + 1)..')')
		end
	end
	for i = 2, nargs do
		output = output..',\n'..getTabs(tabs)..'to<ARG_'..i..'>(L, -'..(nargs - i + 1)..')'
	end
	return output
end

-- replaces EN2S_GET_ARGS_N
function getArguments(nargs, tabs)
	tassert(nargs, 'number')
	local output = ''
	local tabs = getTabs(tabs)
	for i = 1, nargs do
		output = output..tabs..'ARG_'..i..' arg'..i..' = to<ARG_'..i..'>(L, -'..(nargs - i + 1)..');\n'
	end
	return output
end

-- replaces EN2S_GET_INSTANCE_ARGS_N
function getInstance(nargs)
	tassert(nargs, 'number')
	return 'to<CLASS*>(L, -'..(nargs + 1)..')'
end

-- replaces EN2S_PUSH_RETS_N
function pushRets(nrets, tabs)
	tassert(nrets, 'number', tabs)
	local output = ''
	local tabs = getTabs(tabs)
	if nrets > 0 then
		output = output..tabs..'sint pushed(push(L, ret1));\n'
	end	
	for i = 2, nrets do
		output = output..tabs..'pushed += push(L, ret'..i..');\n'
	end
	return output
end

-- replaces EN2S_END_STATIC_TEMPLATE_ARGS
-- end the static function template declaration
function endStaticTemplateArgs(nrets, nargs, fname)
	tassert(nrets, 'number')
	tassert(nargs, 'number')
	fname = fname or 'function'
	return CW.templateReturnSignature(nrets)..'(* '..fname..')('..CW.templateArgumentsSignature(nrets, nargs)..') >\n'
end

-- replaces EN2S_END_CLASS_TEMPLATE_ARGS(NUM_RETS, NUM_ARGS) 
function endClassTemplateArgs(nrets, nargs, const, fname)
	tassert(nrets, 'number')
	tassert(nargs, 'number')
	fname = fname or 'function'
	return CW.templateReturnSignature(nrets)..'(CLASS::* '..fname..')('..CW.templateArgumentsSignature(nrets, nargs)..') ' ..(const and 'const' or '')..'>\n'
end

-- replaces EN2S_GENERATE_CLASS_TEMPLATE and EN2S_GENERATE_CLASS_CONST_TEMPLATE
function generateMemberTemplate(nrets, nargs, const)
	tassert(nrets, 'number')
	tassert(nargs, 'number')
	local tabs1 = getTabs(1)
	local tabs2 = getTabs(2)
	local output = '/** native'..(const and 'Const' or 'Member')..'Return'..nrets..'Param'..nargs..' */\n'
	output = output..'template< typename CLASS, '..CW.templateArguments(nrets, nargs)..', '..endClassTemplateArgs(nrets, nargs, const)
	output = output..'inline LUA_FUNC(native'..(const and 'Const' or 'Member')..'Return'..nrets..'Param'..nargs..')\n'	
	output = output..'{\n'
	output = output..tabs1..'if (CLASS* object = '..getInstance(nargs)..')\n'
	output = output..tabs1..'{\n'
	output = output..			CW.templateDeclareReturnValues(nrets, 2)
	output = output..			CW.templateDeclareOneAssignReturnValues(nrets, 2)..'(object->*function)('..callArguments(nrets, nargs, 3)..');\n'
	output = output..pushRets(nrets, 2)
	if nrets > 0 then
		output = output..tabs2..'return pushed;\n'
	end
	output = output..tabs1..'}\n'
	output = output..tabs1..'return 0;\n'
	output = output..'} // native'..(const and 'Const' or 'Member')..'Return'..nrets..'Param'..nargs..'\n\n'
	return output
end

-- replaces EN2S_GENERATE_STATIC_TEMPLATE
function generateStaticTemplate(nrets, nargs)
	assert(type(file) ~= nil)
	tassert(nrets, 'number')
	tassert(nargs, 'number')
	local tabs = getTabs(1)
	local output = ''
	output = output..'/** nativeStaticReturn'..nrets..'Param'..nargs..' */\n'
	output = output..'template< '..CW.templateArguments(nrets, nargs)..', '..endStaticTemplateArgs(nrets, nargs)
	output = output..'inline LUA_FUNC(nativeStaticReturn'..nrets..'Param'..nargs..')\n'
	output = output..'{\n'
	output = output..CW.templateDeclareReturnValues(nrets, 1)
	output = output..CW.templateDeclareOneAssignReturnValues(nrets, 1)..'(*function)('..callArguments(nrets, nargs, 2)..');\n'
	output = output..pushRets(nrets, 1)
	if nrets > 0 then
		output = output..tabs..'return pushed;\n'
	else
		output = output..tabs..'return 0;\n'
	end
	output = output..'} // nativeStaticReturn'..nrets..'Param'..nargs..'\n\n'
	return output
end

function generateHeader(file, nrets, nargs)
	tassert(file, 'userdata')
	tassert(nrets, 'number')
	tassert(nargs, 'number')
	local output = "namespace lua_extension\n{\n" ..
	"/** nativeConstReturn0Param0 */\n"..
	"template<typename CLASS, void(CLASS::* function)(void) const>\n"..
	"inline sint nativeConstReturn0Param0(lua_State* L)\n"..
	"{"..
	"	if (CLASS* object = to<CLASS*>(L, -1))\n"..
	"	{\n"..
	"		(object->*function)();\n"..
	"	}\n"..
	"	return 0;\n"..
	"} // nativeConstReturn0Param0\n"..
	"\n"..
	"/** nativeMemberReturn0Param0 */\n"..
	"template<typename CLASS, void(CLASS::* function)(void)>\n"..
	"inline sint nativeMemberReturn0Param0(lua_State* L)\n"..
	"{\n"..
	"	if (CLASS* object = to<CLASS*>(L, -1))\n"..
	"	{\n"..
	"		(object->*function)();\n"..
	"	}\n"..
	"	return 0;\n"..	
	"} // nativeMemberReturn0Param0\n"..
	"\n"..
	"/** nativeStaticReturn0Param0 */\n"..
	"template<void(* function)(void)>\n"..
	"inline sint nativeStaticReturn0Param0(lua_State*)\n"..
	"{\n"..
	"	(*function)();\n"..
	"	return 0;\n"..
	"}// nativeStaticReturn0Param0\n\n"
	file:write(output)
	
	for i = 0, nrets do
		for j = 0, nargs do
			if i ~= 0 or j ~= 0 then
				local output = ''
				-- generateConstClassTemplate
				output = output..generateMemberTemplate(i, j, true)
				-- generateMemberClassTemplate
				output = output..generateMemberTemplate(i, j)
				-- generateStaticTemplate
				output = output..generateStaticTemplate(i, j)
				file:write(output)
			end
		end
	end
	file:write("} // namespace lua_extension")
	file:flush()
end