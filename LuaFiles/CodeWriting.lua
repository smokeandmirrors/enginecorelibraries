module(..., package.seeall)

require'Utilities'

-- replaces CW_DECLARE_FUNCTION_REF
function templateCallSignature(nrets, nargs, prefixIfAny)
	tassert('number', nrets, nargs)
	if nrets == 0 and nargs == 0 then
		return ''
	end
	prefixIfAny = prefixIfAny or ''
	local output = prefixIfAny
	if nrets > 0 then
		output = output..'RET_1& ret1'
	end
	for i = 2, nrets do
		output = output..', RET_'..i..'& ret'..i
	end
	if nargs > 0 then
		if nrets > 0 then
			output = output..', ARG_1 arg1'
		else
			output = output..'ARG_1 arg1'
		end		
	end
	for i = 2, nargs do
		output = output..', ARG_'..i..' arg'..i
	end
	return output
end

-- replaces CW_TEMPLATE_ARGS_RETS_N_ARGS_N
function templateArguments(nrets, nargs)
	tassert('number', nrets, nargs)
	assert(nrets > 0 or nargs > 0, 'nrets ==0 , nargs == 0 is handled manually (for now)\n'..
							'current: nrets == '..nrets..', nargs == '..nargs)
	local output = ''
	
	if nrets > 0 then
		output = output..'typename RET_1'
		-- output: 'typename RET_1'
	end
	
	for i = 2, nrets do
		output = output..(', typename RET_'..i)
		-- output: 'typename RET_2, ..., typename RET_N'
	end	
	
	if nrets > 0 and nargs > 0 then
		output = output..(', ')
	end
	
	if nargs > 0 then
		output = output..('typename ARG_1') 
		-- output: 'typename ARG_1'
	end
	
	for i = 2, nargs do
		output = output..(', typename ARG_'..i)
		-- output: 'typename ARG_2, ..., typename ARG_N'
	end
	
	return output
end

-- replaces CW_TEMPLATE_RETURN_SIGNATURE_RETS_N
-- end the static function template declaration
function templateReturnSignature(nrets)
	tassert('number', nrets)
	local output = ''
	output = output..(nrets == 0 and 'void ' or 'RET_1 ') 
	return output
end

-- replaces CW_TEMPLATE_ARGS_SIGNATURE_RETS_N_ARGS_N
function templateArgumentsSignature(nrets, nargs)
	tassert('number', nrets, nargs)
	assert(nrets > 0 or nargs > 0, '0, 0 is handled manually (for now)')
	local output = ''
	
	if nrets == 0 and nargs == 1 then
		output = output..('ARG_1')
		return output
	end
	
	if nrets == 1 and nargs == 0 then
		output = output..('void')
		return output
	end
	
	if nrets > 1 then
		output = output..('RET_2&') 
	end
	
	for i = 3, nrets do
		output = output..(', RET_'..i..'&')
	end	
	-- output: 'RET_2&, ... , RET_N&'
	
	if nrets > 1 and nargs > 0 then
		output = output..(', ')
	end
	
	if nargs > 0 then
		output = output..('ARG_1') 
	end
	
	for i = 2, nargs do
		output = output..(', ARG_'..i)
	end
	-- output: 'ARG_1, ..., ARG_N'
	return output
end

-- replaces CW_DECLARE_FUNCTION_RETS_N_ARGS_N
function templateDeclareFunctionSignature(nrets, nargs)
	tassert('number', nrets, nargs)
	local output = ''
	if nrets < 2 and nargs == 0 then
		output = output..('void')
		return output
	end
	
	if nrets > 1 then
		output = output..('RET_2& ret2') 
	end
	
	for i = 3, nrets do
		output = output..(', RET_'..i..'& ret'..i)
	end	
	-- output: 'RET_2& ret2, ... , RET_N& retN'
	
	if nrets > 1 and nargs > 0 then
		output = output..(', ')
	end
	
	if nargs > 0 then
		output = output..('ARG_1 arg1') 
	end
	
	for i = 2, nargs do
		output = output..(', ARG_'..i..' arg1')
	end
	-- output: 'ARG_1, ..., ARG_N'
	return output
end

-- replaces CW_DECLARE_RETS_N
function templateDeclareReturnValues(nrets, tabs)
	tassert('number', nrets)
	tabs = Utilities.getTabs(tabs)
	local output = ''
	
	if nrets < 2 then
		return output
	end
	
	for i = 2, nrets do
		output = output..tabs..'RET_'..i..' ret'..i..';\n'
	end
	
	return output
end

-- replaces CW_DECLARE_1_ASSIGN_RETS_N
function templateDeclareOneAssignReturnValues(nrets, tabs)
	tassert('number', nrets)
	tabs = Utilities.getTabs(tabs)
	local output = ''
	
	if nrets > 0 then
		output = output..tabs..('RET_1 ret1 = ')
	else
		output = tabs
	end
	
	return output
end

-- replaces CW_ASSIGN_RETS_N
function templateAssignReturnValues(nrets)
	tassert('number', nrets)
	local output = ''
	
	if nrets > 0 then
		output = output..('ret1 = ')
	end
	
	return output
end

-- replaces CW_CALL_RETS_N_ARGS_N
function templateFunctionCallArguments(nrets, nargs)
	tassert('number', nrets, nargs)
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
	
	if nrets > 1 and nargs > 0 then
		output = output..(', ')
	end
	
	if nargs > 0 then
		output = output..('arg1') 
	end
	
	for i = 2, nargs do
		output = output..(', arg'..i)
	end
	return output
end



