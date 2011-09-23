module(..., package.seeall)

local U = require'Utilities'
local CW = require'CodeWriting'
local getTabs = U.getTabs

function callArguments(nrets, nargs)
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
			output = output..(', '..'to<ARG_1>(L, -'..(nargs - 1 + 1)..')')
		else
			output = output..('to<ARG_1>(L, -'..(nargs - 1 + 1)..')')
		end
	end
	for i = 2, nargs do
		output = output..', to<ARG_'..i..'>(L, -'..(nargs - i + 1)..')'
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
function endStaticTemplateArgs(nrets, nargs)
	tassert(nrets, 'number')
	tassert(nargs, 'number')
	return CW.templateReturnSignature(nrets)..'(* function)('..CW.templateArgumentsSignature(nrets, nargs)..') >\n'
end

-- replaces EN2S_GENERATE_STATIC_TEMPLATE
function generateStaticTemplate(nrets, nargs)
	tassert(nrets, 'number')
	tassert(nargs, 'number')
	local tabs = getTabs(1)
	local output = ''
	output = output..'template< '..CW.templateArguments(nrets, nargs)..', '..endStaticTemplateArgs(nrets, nargs)
	output = output..'inline LUA_FUNC(nativeStaticReturn'..nrets..'Param'..nargs..')\n'
	output = output..'{\n'
	output = output..CW.templateDeclareReturnValues(nrets, 1)
	--[[ begin slightly more debuggable ]]--
	-- output = output..getArguments(nargs, 1)
	-- output = output..CW.templateDeclareOneAssignReturnValues(nrets, 1)..'(*function)('..CW.templateFunctionCallArguments(nrets, nargs)..');\n'
	--[[ end slightly more debuggable ]]--
	--[[ begin slightly less debuggable ]]--
	output = output..CW.templateDeclareOneAssignReturnValues(nrets, 1)..'(*function)('..callArguments(nrets, nargs)..');\n'
	--[[ end slightly less debuggable ]]--
	output = output..pushRets(nrets, 1)
	if nrets > 0 then
		output = output..tabs..'return pushed;\n'
	else
		output = output..tabs..'return 0;\n'
	end
	output = output..'} // nativeStaticReturn'..nrets..'Param'..nargs..'\n'
	return output
end