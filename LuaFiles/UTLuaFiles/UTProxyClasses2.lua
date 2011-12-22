deprecatedNaughtyModule(..., package.seeall)
local OOP = require'ObjectOrientedParadigm'
local UT = require'UnitTestingFramework'
require 'Utilities'

----------------------------------------------------------------------
UT.test('inheritance',
	function()
		local g = new'Grandparent2'
		-- C++ functions
		UT.check(type(g.getFamilyName) == 'function')
		UT.checkEqual(g:getFamilyName(), 'Curran')
		UT.check(type(g.getTitle) == 'function')
		UT.checkEqual(g:getTitle(), 'Grandparent2')
		UT.checkT(g.__eq, 'function')
		UT.check(g == g)
		local g2 = new'Grandparent2'
		UT.check(g ~= g2 and g2 ~= g)
		UT.checkT(g.__tostring, 'function')
		UT.checkEqual(g.."", 'This is a Grandparent2') 
		UT.checkT(g.__gc, 'function')
		UT.checkT(g.__call, 'function')
		UT.check(g(), 7)
		-- Lua constructor results
		UT.checkEqual(g.numberOfKids, 2)
		UT.checkEqual(g.numberOfGrandKids, 5)
		UT.checkEqual(g.favoriteFood, 'Pizza')
		-- Lua functions
		UT.checkT(g.getNumberOfKids, 'function')
		UT.checkEqual(g:getNumberOfKids(), 2)
		UT.checkT(g.getNumberOfGrandKids, 'function')
		UT.checkEqual(g:getNumberOfGrandKids(), 5)
		g = new('Parent2')
		-- C++ functions
		UT.checkT(g.setGrandparent, 'function')
		g:setGrandparent(g2)
		UT.checkT(g.getGrandparent, 'function')
		UT.check(g2 == g:getGrandparent())
		UT.checkT(g.getGrandparentName, 'function')
		UT.checkEqual(g:getGrandparentName(), 'Robert Michael Curran, Sr.')
		UT.check(type(g.getFamilyName) == 'function')
		UT.checkEqual(g:getFamilyName(), 'Curran')
		UT.check(type(g.getTitle) == 'function')
		UT.checkEqual(g:getTitle(), 'Parent2')
		UT.checkT(g.__eq, 'function')
		UT.checkT(g.__call, 'function')
		UT.check(g(), 7)
		UT.check(g == g)
		UT.check(g ~= g2)
		local g2 = new('Parent2')
		UT.check(g ~= g2 and g2 ~= g)
		UT.checkT(g.__tostring, 'function')
		UT.checkEqual(g.."", 'This is a Parent2') 
		UT.checkT(g.__gc, 'function')
		-- Lua constructor results
		UT.checkEqual(g.numberOfParents, 3)
		UT.checkEqual(g.numberOfKids, 4)
		UT.checkEqual(g.numberOfGrandKids, 0)
		UT.checkEqual(g.favoriteFood, 'Pizza')
		UT.checkEqual(g.favoriteMovie, 'Star Wars')
		-- Lua functions
		UT.checkT(g.getNumberOfKids, 'function')
		UT.checkEqual(g:getNumberOfKids(), 4)
		UT.checkT(g.getNumberOfGrandKids, 'function')
		UT.checkEqual(g:getNumberOfGrandKids(), 0)
		UT.checkT(g.getNumberOfParents, 'function')
		UT.checkEqual(g:getNumberOfParents(), 3)		
		g = new'Child2'
		-- C++ functions
		UT.checkT(g.setGrandparent, 'function')
		g:setGrandparent(g2)
		UT.checkT(g.getGrandparent, 'function')
		UT.check(g2 == g:getGrandparent())
		UT.checkT(g.getGrandparentName, 'function')
		UT.checkEqual(g:getGrandparentName(), 'Robert Michael Curran, Sr.')
		UT.check(type(g.getFamilyName) == 'function')
		UT.checkEqual(g:getFamilyName(), 'Curran')
		UT.check(type(g.getTitle) == 'function')
		UT.checkEqual(g:getTitle(), 'Child2')
		UT.checkT(g.__eq, 'function')
		UT.check(g == g)
		UT.check(g ~= g2)
		local g2 = new'Child2'
		UT.check(g == g2 and g2 == g)
		g2.favoritePark = 'Lake Harriett'
		UT.check(g ~= g2 and g2 ~= g)
		UT.checkT(g.__tostring, 'function')
		UT.checkEqual(g.."", 'This is a Child2') 
		UT.checkT(g.__gc, 'function')
		UT.checkT(g.__call, 'function')
		UT.check(g(), 7)
		---[[
		local g3 = g2:get()
		UT.checkT(getmetatable(g3), 'table')
		-- Lua constructor results
		UT.checkEqual(g.numberOfKids, 0)
		UT.checkEqual(g.numberOfGrandKids, 0)
		UT.checkEqual(g.numberOfParents, 2)
		UT.checkEqual(g.numberOfGrandparents, 4)
		UT.checkEqual(g.favoritePark, 'Central Park')
		UT.checkEqual(g.favoriteFood, 'Pizza')
		UT.checkEqual(g.favoriteMovie, 'Star Wars')
		UT.checkT(g.mom, 'userdata')
		UT.check(g.mom:IS_A('Parent2'))
		UT.checkT(g.dad, 'userdata')
		UT.check(g.dad:IS_A('Parent2'))
		-- Lua functions
		UT.checkT(g.getNumberOfKids, 'function')
		UT.checkEqual(g:getNumberOfKids(), 0)
		UT.checkT(g.getNumberOfGrandKids, 'function')
		UT.checkEqual(g:getNumberOfGrandKids(), 0)
		UT.checkT(g.getNumberOfParents, 'function')
		UT.checkEqual(g:getNumberOfParents(), 2)		
		UT.checkT(g.getNumberOfGrandparents, 'function')
		UT.checkEqual(g:getNumberOfGrandparents(), 4)
		--]]
	end
)

---[[
----------------------------------------------------------------------
UT.test('proxy useage',
	function()
		local c = new'Child2'
		UT.checkT(c, 'userdata')
		UT.check(c.newThing == nil)
		c.newThing = 2;
		UT.checkEqual(c.newThing, 2)
	end
)

----------------------------------------------------------------------
UT.test('proxy OOP friendliness',
	function()
		UT.testClassProperties('Grandparent2')
		UT.testClassProperties('Parent2', 'Grandparent2')
		UT.testClassProperties('Child2', 'Parent2')
	end
)

----------------------------------------------------------------------
UT.test('proxy class redefinition',
	function()
		if DEBUG_INTERPRETATION then
			require'Child2'
			c = new'Child2'
			UT.testClassProperties('Parent2', 'Grandparent2')
			UT.testClassProperties('Child2', 'Parent2')
			Parent2.onRefresh = function() return 'refreshed' end
			declareClass(Parent2)
			UT.checkT(c.onRefresh, 'function')
			UT.checkEqual(c:onRefresh(), 'refreshed')
			UT.testInstanceProperties(c, 'Child2', 'Parent2')
			Child2.__add = function(lhs, rhs) return 2 end
			Child2.refreshed = function(self) return self() + 7 end
			declareClass(Child2)
			UT.checkEqual(c + new'Child2', 2)
			UT.checkT(c.refreshed, 'function')
			UT.checkEqual(c:refreshed(), 14)
			UT.testInstanceProperties(c, 'Child2', 'Parent2')
			UT.checkEqual((new'Child2'):refreshed(), 14)
			UT.testClassProperties('Parent2', 'Grandparent2')
			UT.testClassProperties('Child2', 'Parent2')
		end
	end
)
--]]