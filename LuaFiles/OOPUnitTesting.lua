module('OOPUnitTesting', package.seeall)
----------------------------------------------------------------------
-- OOPUnitTesting.lua
--
-- This file defines lua unit tests for the ObjectOrientedParadigm
--
--	\author Smoke and Mirrors Development
--	\email smokeandmirrorsdevelopment@gmail.com
--	\copyright 2010
local OOP = require'ObjectOrientedParadigm'
local UT = require'UnitTestingFramework'
require'Utilities'

--[[
IS_A
addClassConstructor
classes
declareAbstractClass
declareClass
delete
functions
getClass
getClassFromObject
new
toStringConcat
validateObject
--]]

----------------------------------------------------------------------
-- ACTS_AS
-- declareInterface
-- classes declared as implemented an interface
UT.test('OOP.interfaces',
	function()
		-- convenience for (re)writing the test
		rerequire'ObjectOrientedParadigm'
		declareInterface{
			name = 'IACTS_AS_TEST',
			only = function() end
		};
		
		declareClass{
			name = 'CPASS_ACTS_AS_TEST',
			implements = 'IACTS_AS_TEST',
			only = function() print'I work' end 
		};
		
		declareClass{
			name = 'CFAIL_ACTS_AS_TEST',
			only = function() print'I work' end
		}
		
		UT.checkError( 
			function()
				declareClass{
					name = 'Should not compile',
					implements = 'IACTS_AS_TEST',
					fail = function() print'I fail' end
				};
			end, 'This class declaration should have failed')
		
		UT.checkError(
			function()
				local f = new'Should not compile' 
			end,
			'This class should not exists')
			
		local p = new'CPASS_ACTS_AS_TEST'
		UT.check(p:ACTS_AS'IACTS_AS_TEST')
		local f = new'CFAIL_ACTS_AS_TEST' 	
		UT.check(not f:ACTS_AS'CFAIL_ACTS_AS_TEST')
	end
)