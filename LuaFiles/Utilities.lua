module("Utilities", package.seeall)
----------------------------------------------------------------------
--	Utilities.lua
--	
--	A set of extensions to lua libraries, and functions so useful that they are used
--	almost as much as basic lua syntax.
--	
--	@author Smoke and Mirrors Development
--	smokeandmirrorsdevelopment@gmail.com
--	copyright 2010

----------------------------------------------------------------------
-- executes the given string as code
function _G.dostring(s)
	local func = loadstring(s)
	if type(func) == 'function' then
		func()
	else
		print('do string failed')
	end
end

---------------------------------------------------------------------
function _G.falsef()
	return false
end

---------------------------------------------------------------------
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
function _G.rerequire(name)
	package.loaded[name] = nil
	return require(name)
end

local oldrequire = require

function _G.require(name)
	if package.loaded[name] then
		return package.loaded[name]
	else
		print("requiring:", name)
		return oldrequire(name)
	end
	
end
end -- package

--[[ table extensions]]--
if table then
---------------------------------------------------------------------
-- @todo test this
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

---------------------------------------------------------------------
table.findremoveslow = function(t, object)
	for index, value in pairs(t) do
		if rawequal(value, object) then
			table.remove(t,index)
			break
		end
	end
end

----------------------------------------------------------------------
-- Create a read-only version of the table
-- @param t modifiable table
-- @return a read-only version of t
function table.getreadonly(t)
	local proxy = {}
	local mt = {
		__index = t,
		__newindex = function(t, k, v)
			error("Cannot update read-only table!")
		end
	}
	setmetatable(proxy, mt)
	return proxy
end

----------------------------------------------------------------------
-- Take single set table and shuffle its members.  
-- @note THIS WILL ONLY WORK ON TABLES W/O NIL VALUES
-- @param t table to shuffle
function table.shuffle(t)
	local n = #t
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

----------------------------------------------------------------------
-- Recursive deep print 
-- @todo make correct version
function _G.dprint(object, indent) 

end

----------------------------------------------------------------------
-- sprint()
--
-- shallow print. essentially just lists the top-level contents (if the object is a table)
if table then
function _G.sprint(object)
	if (type(object) ~= "table" ) then
		print(tostring(object))
	else
		local list = {}
		for key,val in pairs(object) do	
			table.insert(list, tostring(key)..": "..tostring(val))
		end
		table.sort(list)
		for _,item in pairs(list) do 
			print (item)
		end
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