module(..., package.seeall)
----------------------------------------------------------------------
--	Utilities.lua
--	
--	A set of extensions to lua libraries, and functions so useful that they are used
--	almost as much as basic lua syntax.
--	
--	@author Smoke and Mirrors Development
--	smokeandmirrorsdevelopment@gmail.com
--	copyright 2010

--[[ global (Lua) utilities ]]--
----------------------------------------------------------------------
-- executes the given string as code
function _G.dostring(s)
	local func = loadstring(s)
	if type(func) == 'function' then
		func()
	else
		print('dostring() argument wasn\'t a fuction after running through '..
			'loadstring')
		print('argument: '..tostring(s))
		print('result type: '..type(func))
	end
end

---------------------------------------------------------------------
-- defines a single, global function that returns false, comes in
-- handy all over the place
function _G.falsef()
	return false
end

---------------------------------------------------------------------
-- defines a single, global function that returns true, comes in
-- handy all over the place
function _G.truef()
	return true
end	

---------------------------------------------------------------------
-- set the provided toggle to the boolean, or it toggle it if the boolean is nil
function _G.togset(toggle, bool) 
	if bool == nil then
		return not toggle
	else
		return bool
	end		
end

---------------------------------------------------------------------
-- shorcut for assert(type(object) == 'sometype')
function _G.tassert(object, type_name)
	assert(type(object) == type_name, 'type: '..type_name..' expected, but '..type(object)..' found instead!')
end


--[[ debug extensions ]]--
if debug then
---------------------------------------------------------------------
function debug.functionline(event, line)
	local line = line or debug.getinfo(2, 'l').currentline
	local function_name = debug.getinfo(2, 'n').name
	if	function_name ~= 'rawget' and
		function_name ~= 'insert' and
		function_name ~= 'assert' and
		function_name ~= 'setmetatable' and
		function_name ~= 'module' and
		function_name ~= 'require' and
		function_name ~= 'pairs' and
		function_name ~= '(for generator)' and
		function_name ~= 'print' and
		function_name ~= 'type' and
		function_name ~= 'setfenv' and
		function_name ~= 'print'
	then
		print('debug function:', function_name, 'event:', event, 'line:', line)
	end
end
end

--[[ package extensions ]]--
if package then
---------------------------------------------------------------------
-- reloads a module
function _G.rerequire(name, hideNotFoundError, hideSyntaxError)
	package.loaded[name] = nil
	return require(name, hideNotFoundError, hideSyntaxError)
end

if not oldrequire then
	oldrequire = require
end

function _G.require(name, hideNotFoundError, hideSyntaxError)
	if package.loaded[name] then
		return package.loaded[name]
	else
		local status, pack = xpcall(
			function() 
				return oldrequire(name) 
			end, 
			function(err)
				local isMissing = string.match(err, 'module \''..name..'\' not found:')
				if ((not hideNotFoundError) and isMissing)
				or ((not hideSyntaxError) and (not isMissing)) then
					print(err)
				end
			end)		
		if status then
			return pack
		end
	end
end

end -- package

--[[ table extensions]]--
if table then
---------------------------------------------------------------------
table.copy = function(original, copy)
	for k, v in pairs(original) do
		copy[k] = v
	end
end

---------------------------------------------------------------------
-- \param predicate_book_key_value is a function that takes a key, 
-- and a value from the original table and returns a boolean expression
table.copyif = function(original, copy, predicate)
	for key, val in pairs(original) do
		if predicate(key, val) then
			copy[key] = val
		end
	end
end

---------------------------------------------------------------------
isValueFunction = function(key, value)
	return type(value) == 'function'
end

---------------------------------------------------------------------
table.countslow = function(t)
	local n = 0
	for _ in pairs(t) do
		n = n + 1
	end
	return n
end

---------------------------------------------------------------------
table.empty = function(t)
	for each, value in pairs(t) do
		t[each] = nil
	end
end

---------------------------------------------------------------------
table.emptyindexed = function(t)
	while table.remove(t) ~= nil do
		-- empty
	end
end

---------------------------------------------------------------------
table.findindexslow = function(t, object)
	for index, value in pairs(t) do
		if rawequal(value, object) then
			return index
		end
	end
end

----------------------------------------------------------------------
local readOnlySupport = function(t, k, v)
	error("Cannot update read-only table!")
end

----------------------------------------------------------------------
-- Create a read-only version of the table
-- \warning this table can't be used in pairs()/ipairs()
-- @param t modifiable table
-- @return a read-only version of t
function table.getreadonly(t)
	local proxy = {}
	local mt = {
		__index = t,
		__newindex = readOnlySupport
	}
	setmetatable(proxy, mt)
	return proxy
end

---------------------------------------------------------------------
table.removeindexslow = function(t, object)
	for index, value in pairs(t) do
		if rawequal(value, object) then
			return table.remove(t, index)
		end
	end
end

----------------------------------------------------------------------
-- Take single set table and shuffle its members.  
-- @param t table to shuffle
-- \param elements a number that MUST be <= the number of elements in the table
function table.shuffle(t, elements)
	local n = type(elements) == 'number' and elements or table.countslow(t)
	-- only shuffle more than 1
	if n > 1 then
		local k = 0
		repeat
			k = math.random(n) 
			t[n], t[k] = t[k], t[n]
			n = n - 1
		until n == 1
	end
 end
 end -- if table

 --[[ printing functions (string shortcuts) ]]--
 if string then
----------------------------------------------------------------------
--- conditionally prints a formated version of formatME with the args
function _G.cprintf(condition, format_me, ...)
	if condition and (type(condition) ~= "function" or condition()) then 
		print(string.format(format_me, ...)) 
	end
end

----------------------------------------------------------------------
-- prints a formated version of formatME with the args
function _G.printf(format_me, ...)
	print(string.format(format_me, ...))
end

----------------------------------------------------------------------
-- returns a formated version of formatME with the args
function _G.sprintf(format_me, ...)
	return string.format(format_me, ...)
end

if table then
function getTabs(number)
	local indent = ''
	number = number or 0
	for i = 1, number do
		indent = indent..'\t'
	end
	return indent
end

function printTableEntries(object, indent, previous, tabs)
	for key, value in pairs(object) do
		if type(value) == 'table' then
			-- print(..tostring(value))
			dprint(value, indent, previous, tabs..tostring(key)..' -> ')
		else
			print(tabs..tostring(key)..' -> '..tostring(value))
		end
	end
end

----------------------------------------------------------------------
-- Recursive deep print 
function _G.dprint(object, indent, previous, prefix) 
	indent = indent or 0
	local tabs = getTabs(indent)	
	if type(object) == 'table' then
		if not previous then
			previous = {}
			previous[object] = true
			if prefix then
				print(prefix..tostring(object)..' : o')
			else
				print(tabs..tostring(object)..' : o')
			end
			printTableEntries(object, indent + 1, previous, tabs)
		elseif not previous[object] then
			previous[object] = true
			if prefix then
				print(prefix..tostring(object)..' : o')
			else
				print(tabs..tostring(object)..' : o')
			end
			printTableEntries(object, indent, previous, tabs)
		else
			if prefix then
				print(prefix..tostring(object)..' : x')
			else
				print(tabs..tostring(object)..' : x')
			end
		end
	else
		print(tabs..tostring(object))
	end
end

----------------------------------------------------------------------
-- sprint()
-- shallow print. essentially just lists the top-level contents (if the object is a table)
function _G.sprint(object)
	if type(object) == 'table' then
		local list = {}
		for key, val in pairs(object) do	
			table.insert(list, tostring(key)..': '..tostring(val))
		end
		table.sort(list)
		for _,item in pairs(list) do 
			print(item)
		end
	else
		print(tostring(object))
	end
end
end -- if table
----------------------------------------------------------------------
-- tprint()
--
-- shortcut to printing the type of the object
function _G.tprint(object)
	print(type(object))
end
end -- if string