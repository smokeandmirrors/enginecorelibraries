module('UnitTesting', package.seeall)
----------------------------------------------------------------------
-- UnitTesting.lua
--
-- This file defines lua unit tests
--
--	\author Smoke and Mirrors Development
--	\email smokeandmirrorsdevelopment@gmail.com
--	\copyright 2010
require 'OOPUnitTesting'
local UT = require'UnitTestingFramework'
require'Utilities'

--[[ testing Utilities.lua ]]--
UT.test('dostring',
	function()
		local i = 1
		dostring('f = function() return 3 end')
		i = i + f()
		print('f(): '..f())
		print('i: ', i)
		UT.checkEqual(i,4)
	end
)

UT.test('falsef', 
	function()
		UT.check(not falsef())
	end
)

UT.test('truef',
	function()
		UT.check(truef())
	end
)

UT.test('togset',
	function()
		local toggle = true
		toggle = togset(toggle)
		UT.check(not toggle)
		toggle = togset(toggle)
		UT.check(toggle)
		toggle = togset(toggle, false)
		UT.check(not toggle)
		toggle = togset(toggle, true)
		UT.check(toggle)
	end
)
if table then
UT.test('table.countslow',
	function()
		local t = {}
		for i=100,1,-1 do
			table.insert(t, i)
		end	
		UT.checkEqual(table.countslow(t), #t) 
		UT.checkEqual(table.countslow(t), 100)
	end
)

UT.test('table.empty',
	function()
		local t = {a = 'sweet', b = 34, d = function() print'awesome' end}
		table.insert(t, 43)
		table.insert(t, 'execellent')
		t[75] = function() print'wierd' end
		table.insert(t, 95)
		table.empty(t)
		UT.checkEqual(nil, next(t))
	end
)

UT.test('table.emptyindexed',
	function()
		local t = {}
		for i=100,1,-1 do
			table.insert(t, i)
		end
		table.emptyindexed(t)
		UT.checkEqual(nil, next(t))
	end
)

UT.test('table.findindexslow',
	function()
		local t = {a = 'sweet', b = 34, d = function() print'awesome' end}
		table.insert(t, 43)
		table.insert(t, 'execellent')
		t[75] = function() print'wierd' end
		t[34] = 'bitchin'
		table.insert(t, 95)
		UT.checkEqual(table.findindexslow(t, 'bitchin'), 34)
	end
)

UT.test('table.removeindexslow',
	function()
		local t = {}
		for i=1,100 do
			table.insert(t, i)
		end
		local removed = table.removeindexslow(t, 34)
		
		UT.checkEqual(removed, 34)
		UT.checkEqual(table.countslow(t), 99)
	end
)

UT.test('table.shuffle',
	function()
		local t = {}
		local shuffled = {}
		local sum = 0
		
		for i=1,100 do
			table.insert(t, i)
			table.insert(shuffled, i)
			sum = sum + i			
		end
		
		table.shuffle(shuffled, 100)
		local control_sum = 0
		local shuffle_sum = 0
			
		for _, value in pairs(t) do
			control_sum = control_sum + value
		end
		
		for _, value in pairs(shuffled) do
			shuffle_sum = shuffle_sum + value
		end
		
		UT.checkEqual(shuffle_sum, control_sum)
		local is_different = false
		
		for i=1,100 do
			if shuffled[i] ~= t[i] then
				is_different = true
				break
			end		
		end
		
		UT.check(is_different)
	end
)

UT.test('dprint',
	function()
		local t = {a = 'sweet', b = 34, d = function() print'awesome' end}
		table.insert(t, 43)
		table.insert(t, 'execellent')
		t[75] = function() print'wierd' end
		t[34] = 'bitchin'
		table.insert(t, 95)
		dprint(t)
	end
)

UT.test('sprint',
	function()
		local t = {a = 'sweet', b = 34, d = function() print'awesome' end}
		table.insert(t, 43)
		table.insert(t, 'execellent')
		t[75] = function() print'wierd' end
		t[34] = 'bitchin'
		table.insert(t, 95)
		sprint(t)
	end
)
end -- if table

if string then
UT.testSuite
{
	name = 'string', 

	cprintf = function()
		-- mainly, don't throw an error
		print'L@@K: you should see \'awesome\' below'
		cprintf(true, 'awesome')
		cprintf(false, 'bitchin')
		print'L@@K: you should NOT see \'bitchin\' above'
	end,

	printf = function()
		-- mainly, don't throw an error
		printf('L@@K: The next character should be \'3\': %d', 3)
	end,

	sprintf = function()
		local results = sprintf('The next character should be \'3\': %d', 3)
		UT.checkEqual(results, 'The next character should be \'3\': 3')
	end,

	tprint = function()
		-- mainly, don't throw an error
		tprint(nil)
		tprint(function() print'hello' end)
		tprint{}
		tprint('string')
		tprint(9)
		tprint(true)
		tprint(coroutine.create(function() print'hello' end))
end
}
end -- if string