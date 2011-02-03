module(..., package.seeall)
local OOP = require'ObjectOrientedParadigm'
local UT = require'UnitTestingFramework'
require 'Utilities'

----------------------------------------------------------------------
UT.test('inheritance',
	function()
		require'Grandparent'
		require'Parent'
		require'Child'
		
		local g = new'Grandparent'
		-- C++ functions
		UT.check(type(g.getFamilyName) == 'function')
		UT.checkEqual(g:getFamilyName(), 'Curran')
		UT.check(type(g.getTitle) == 'function')
		UT.checkEqual(g:getTitle(), 'Grandparent')
		UT.checkT(g.__eq, 'function')
		UT.check(g == g)
		local g2 = new'Grandparent'
		UT.check(g ~= g2 and g2 ~= g)
		UT.checkT(g.__tostring, 'function')
		UT.checkEqual(g.."", 'This is a Grandparent') 
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
				
		g = new('Parent')
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
		UT.checkEqual(g:getTitle(), 'Parent')
		UT.checkT(g.__eq, 'function')
		UT.checkT(g.__call, 'function')
		UT.check(g(), 7)
		UT.check(g == g)
		UT.check(g ~= g2)
		local g2 = new('Parent')
		UT.check(g ~= g2 and g2 ~= g)
		UT.checkT(g.__tostring, 'function')
		UT.checkEqual(g.."", 'This is a Grandparent') 
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
		
		g = new'Child'
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
		UT.checkEqual(g:getTitle(), 'Child')
		UT.checkT(g.__eq, 'function')
		UT.check(g == g)
		UT.check(g ~= g2)
		local g2 = new'Child'
		UT.check(g == g2 and g2 == g)
		g2.favoritePark = 'Lake Harriett'
		UT.check(g ~= g2 and g2 ~= g)
		UT.checkT(g.__tostring, 'function')
		UT.checkEqual(g.."", 'This is a Grandparent') 
		UT.checkT(g.__gc, 'function')
		UT.checkT(g.__call, 'function')
		UT.check(g(), 7)
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
		UT.check(g.mom:IS_A('Parent'))
		UT.checkT(g.dad, 'userdata')
		UT.check(g.dad:IS_A('Parent'))
		-- Lua functions
		UT.checkT(g.getNumberOfKids, 'function')
		UT.checkEqual(g:getNumberOfKids(), 0)
		UT.checkT(g.getNumberOfGrandKids, 'function')
		UT.checkEqual(g:getNumberOfGrandKids(), 0)
		UT.checkT(g.getNumberOfParents, 'function')
		UT.checkEqual(g:getNumberOfParents(), 2)		
		UT.checkT(g.getNumberOfGrandparents, 'function')
		UT.checkEqual(g:getNumberOfGrandparents(), 4)		
	end
)

----------------------------------------------------------------------
UT.test('proxy useage',
	function()
		require'Child'
		local c = new'Child'
		UT.checkT(c, 'userdata')
		UT.check(c.newThing == nil)
		c.newThing = 2;
		UT.checkEqual(c.newThing, 2)
	end
)

----------------------------------------------------------------------
UT.test('proxy OOP friendliness',
	function()
		UT.testClassProperties('Grandparent')
		UT.testClassProperties('Parent', 'Grandparent')
		UT.testClassProperties('Child', 'Parent')
	end
)

----------------------------------------------------------------------
UT.test('proxy class redefinition',
	function()
		require'Child'
		c = new'Child'
		Parent.onRefresh = function() return 'refreshed' end
		declareClass(Parent)
		UT.checkT(c.onRefresh, 'function')
		UT.checkEqual(c:onRefresh(), 'refreshed')
		Child.__add = function(lhs, rhs) return 2 end
		declareClass(Child)
		UT.checkEqual(c + new'Child', 2)
	end
)
