module(..., package.seeall)
local OOP = require'ObjectOrientedParadigm'
local UT = require'UnitTestingFramework'
require 'Utilities'

----------------------------------------------------------------------
UT.test('simple declaration',
	function()
		--[[
		pcall(function() require'Simple' end)
		pcall(function() require'Derived' end)
		local s = new'Simple'
		local s2a = new'Simple'
		s:setOther(s2a)
		
		local s2 = s:reproduce()
		UT.checkT(getmetatable(s2), 'table')
		UT.checkT(getmetatable(s2).__gc, 'function')
		
		local simple_func = function(simple)
			local s2b = simple:getOther();
			UT.checkT(getmetatable(s2b), 'table')
			UT.checkT(getmetatable(s2b).__gc, 'function')
		end
		
		simple_func(s)
		--]]
		
		--[[
		pcall(function() require'Simple' end)
		UT.testClassProperties('Simple')
		local s = new'Simple'
		UT.checkT(s.__tostring, 'function')
		UT.checkT(s:__tostring(), 'string')
		UT.checkEqual(s:__tostring(), 'Simple')
		UT.checkT(s.getValue, 'function')
		UT.checkEqual(s:getValue(), 7)
		UT.checkEqual(s(), 7)
		UT.checkT(s.isSimple, 'function')
		UT.check(s:isSimple(), true)
		UT.checkT(s:isSimple(), 'boolean')
		UT.checkEqual(s:isSimple(), true)
		UT.checkT(s.reproduce, 'function')
		UT.checkT(s:reproduce(), 'userdata') 
		
		pcall(function() require'Derived' end)
		UT.testClassProperties('Derived', 'Simple')
		local d = new'Derived'
		UT.checkT(d.__tostring, 'function')
		UT.checkT(d:__tostring(), 'string')
		UT.checkEqual(d:__tostring(), 'Derived')
		UT.checkT(d.getDerivation, 'function')
		UT.checkEqual(d:getDerivation(), 21)
		UT.checkT(d.getValue, 'function')
		UT.checkEqual(d:getValue(), 14)
		UT.checkEqual(d(), 14)
		UT.checkT(d.isSimple, 'function')
		UT.check(d:isSimple(), true)
		UT.checkT(d:isSimple(), 'boolean')
		UT.checkEqual(d:isSimple(), true)
		UT.checkT(d.reproduce, 'function')
		UT.checkT(d:reproduce(), 'userdata') 
		--]]
	end
)