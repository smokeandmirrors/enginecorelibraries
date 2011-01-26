module(..., package.seeall)
local OOP = require'ObjectOrientedParadigm'
local UT = require'UnitTestingFramework'
require 'Utilities'
--[[
require'Grandparent'
require'Parent'
require'Child'
--]]
----------------------------------------------------------------------
UT.test('simple declaration',
	function()
		UT.checkT(OOP.classes_PRIVATE['Grandparent'], 'table')
		UT.check(getClass('Grandparent'))
		local g = new('Grandparent')
		-- C++ functions
		UT.check(type(g.getFamilyName) == 'function')
		UT.checkEqual(g:getFamilyName(), 'Curran')
		UT.check(type(g.getTitle) == 'function')
		UT.checkEqual(g:getTitle(), 'Grandparent')
		UT.checkT(g.__eq, 'function')
		UT.check(g == g)
		local g2 = new('Grandparent')
		UT.check(g ~= g2 and g2 ~= g)
		UT.checkT(g.__tostring, 'function')
		UT.checkEqual(g.."", 'This is a Grandparent') 
		UT.checkT(g.__gc, 'function')
		-- Lua constructor results
		UT.checkEqual(g.numberOfKids, 2)
		UT.checkEqual(g.numberOfGrandKids, 5)
		UT.checkEqual(g.favoriteFood, 'Pizza')
		-- Lua functions
		UT.checkT(g.getNumberOfKids, 'function')
		UT.checkEqual(g:getNumberOfKids(), 2)
		UT.checkT(g.getNumberOfGrandKids, 'function')
		UT.checkEqual(g:getNumberOfGrandKids(), 5)		
	end
)