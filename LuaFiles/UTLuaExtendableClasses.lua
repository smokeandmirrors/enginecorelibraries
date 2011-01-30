module(..., package.seeall)
local OOP = require'ObjectOrientedParadigm'
local UT = require'UnitTestingFramework'
require 'Utilities'

----------------------------------------------------------------------
UT.test('simple declaration',
	function()
		--[[
		pcall(function() require'Simple' end)
		s = new'Simple'
		UT.checkT(s.__tostring, 'function')
		UT.checkT(s:__tostring(), 'string')
		--]]
	end
)