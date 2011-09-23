module(..., package.seeall)

U = require'Utilities'
CW = require'CodeWriting'

local getTabs = U.getTabs

-- replaces EN2S_GET_ARGS_N
function getArguments(nargs, tabs)
	tassert(nargs, 'number')
	local output = ''
	local tabs = getTabs(tabs)
	for i = 1, nargs do
		output = output..tabs..'ARG_'..i..' arg'..i..' = to<ARG_'..i..'>(L, -'..(nargs - i + 1)..');\n'
	end
	-- output: ARG_1 arg1 = to<ARG_1>(L, -n); ..., ARG_N argN = to<ARG_N>(L, -1);
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
	for i = 1, nrets do
		output = output..tabs..'pushed += push(L, ret'..i..');\n'
	end
	-- output: pushed += push(L, ret1); ..., pushed += push(L, retN);
	return output
end

-- replaces EN2S_END_STATIC_TEMPLATE_ARGS
-- end the static function template declaration
function endStaticTemplateArgs(nrets, nargs)
	tassert(nrets, 'number')
	tassert(nargs, 'number')
	return CW.templateReturnSignature(nargs)..'(* function)('..CW.templateArgumentsSignature(nrets, nargs)..') >\n'
end

-- replaces EN2S_GENERATE_STATIC_TEMPLATE
function generateStaticTemplate(nrets, nargs)
	tassert(nrets, 'number')
	tassert(nargs, 'number')
	local tabs = getTabs(1)
	local output = ''
	output = output..'template< '..CW.templateArguments(nrets, nargs)..', '..endStaticTemplateArgs(nrets, nargs)
	output = output..'inline LUA_FUNC(nativeStaticReturn'..nargs..'Param'..nrets..')\n'
	output = output..'{\n'
	output = output..tabs..'sint pushed(0);\n'
	output = output..CW.templateDeclareReturnValues(nrets, 1)
	output = output..getArguments(nargs, 1)
	output = output..CW.templateDeclareOneAssignReturnValues(nrets, 1)..'(*function)('..CW.templateFunctionCallArguments(nrets, nargs)..');\n'
	output = output..pushRets(nrets, 1)..'\n'
	output = output..tabs..'return pushed;\n'
	output = output..'} // nativeStaticReturn'..nrets..'Param'..nargs..'\n'
	
	return output
	--[[
	template<
		typename ARG_1, typename
	--]]
end

