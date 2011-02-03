module(..., package.seeall)
local OOP = require'ObjectOrientedParadigm'
local UT = require'UnitTestingFramework'
require 'Utilities'

----------------------------------------------------------------------
UT.test('simple declaration',
	function()
		pcall(function() require'Simple' end)
		UT.testClassProperties('Simple')
		local s = new'Simple'
		UT.checkT(s.__tostring, 'function')
		UT.checkT(s:__tostring(), 'string')
		UT.checkEqual(s:__tostring(), 'This is a Simple')
		UT.checkT(s.getValue, 'function')
		UT.checkEqual(s:getValue(), 7)
		UT.checkEqual(s(), 7)
		UT.checkT(s.isSimple, 'function')
		UT.check(s:isSimple(), true)
		UT.checkT(s:isSimple(), 'boolean')
		UT.checkEqual(s:isSimple(), true)
		UT.checkT(s.reproduce, 'function')
		UT.checkT(s:reproduce(), 'userdata') 
		local s2 = new'Simple'
		s:setOther(s2)
		local s3 = s:getOther()
		UT.checkEqual(s2, s3)
		UT.testInstanceProperties(s3, 'Simple')
		
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
		local d2 = new'Derived'
		s:setOther(d2)
		local d3 = s:getOther()
		UT.checkEqual(d2, d3)
		UT.testInstanceProperties(d3, 'Derived', 'Simple')
	end
)