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

--[[ testing Utililties.lua ]]--
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

--[[ call this last ]]--
UT.runAll()