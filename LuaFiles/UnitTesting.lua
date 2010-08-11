module('UnitTesting', package.seeall)
----------------------------------------------------------------------
-- UnitTesting.lua
--
-- This file defines lua unit tests
--
--	\author Smoke and Mirrors Development
--	\email smokeandmirrorsdevelopment@gmail.com
--	\copyright 2010
require'Utilities'
local UT = require'UnitTestingFramework'

--[[ testing Utilities.lua ]]--

UT.test('dostring',
	function()
		local i = 1
		dostring('f = function() return 3 end')
		i = i + f()
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

--[[ call this last ]]--
_G.unitTestSuccessful = UT.runAll()