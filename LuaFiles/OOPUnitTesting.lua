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

----------------------------------------------------------------------
UT.test('OOP.interfaces',
	function()
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
----------------------------------------------------------------------
UT.test('OO.polymorphism',
    function()
		rerequire'ObjectOrientedParadigm'
        declareClass {
            name = 'grandparent',
            getNickName = function() return 'papa' end,
            isOld = function() return true end
			
        }

        declareClass {
            name = 'parent',
            extends = 'grandparent',
            getNickName = function() return 'daddy' end,
            isMiddleAged = function() return true end
        }

        declareClass {
            name = 'child',
            extends = 'parent',
            getNickName = function() return 'buggaboo' end,
            isYoung = function() return true end
        }        
        
        local gp = new'grandparent'
        UT.check(type(gp) == 'table')
        UT.check(IS_A(gp, 'grandparent'))
        UT.check(type(gp.IS_A) == 'function' and gp:IS_A'grandparent');
        UT.check(IS_EXACTLY_A(gp, 'grandparent'))
        UT.check(type(gp.IS_EXACTLY_A) == 'function' and gp:IS_EXACTLY_A'grandparent');
        UT.check(type(gp.getNickName) == 'function' and gp.getNickName() == 'papa')
        UT.check(type(gp.isOld) == 'function' and gp.isOld())        
        
        local p = new'parent'
        UT.check(type(p) == 'table')
        UT.check(IS_A(p, 'grandparent'))
        UT.check(not IS_EXACTLY_A(p, 'grandparent'))
        UT.check(IS_A(p, 'parent'))        
        UT.check(IS_EXACTLY_A(p, 'parent'))
        UT.check(type(p.IS_A) == 'function' and p:IS_A'grandparent')
        UT.check(type(p.IS_EXACTLY_A) == 'function' and (not p:IS_EXACTLY_A'grandparent'))
        UT.check(type(p.IS_A) == 'function' and p:IS_A'parent')
        UT.check(type(p.IS_EXACTLY_A) == 'function' and (p:IS_EXACTLY_A'parent'))
        UT.check(type(p.getNickName) == 'function' and p.getNickName() == 'daddy')
		UT.check(type(p.isMiddleAged) == 'function' and p.isMiddleAged())
        UT.check(type(p.isOld) == 'function' and p.isOld())        
        
        local c = new'child'
        UT.check(type(c) == 'table')
        UT.check(IS_A(c, 'grandparent'))
        UT.check(IS_A(c, 'parent'))
		UT.check(not IS_EXACTLY_A(c, 'grandparent'))
        UT.check(not IS_EXACTLY_A(c, 'parent'))
		UT.check(IS_A(c, 'child'))
		UT.check(IS_EXACTLY_A(c, 'child'))
		UT.check(type(c.IS_A) == 'function' and c:IS_A'grandparent')
        UT.check(type(c.IS_A) == 'function' and c:IS_A'parent')
        UT.check(type(c.IS_EXACTLY_A) == 'function' and not c:IS_EXACTLY_A'grandparent')
        UT.check(type(c.IS_EXACTLY_A) == 'function' and not c:IS_EXACTLY_A'parent')
        UT.check(type(c.IS_A) == 'function' and c:IS_A'child')
		UT.check(type(c.IS_EXACTLY_A) == 'function' and c:IS_EXACTLY_A'child')
		UT.check(type(c.getNickName) == 'function' and c.getNickName() == 'buggaboo')
		UT.check(type(c.isMiddleAged) == 'function' and c.isMiddleAged())
        UT.check(type(c.isOld) == 'function' and c.isOld())  
		UT.check(type(c.isYoung) == 'function' and c.isYoung())
	
		UT.testClassProperties('grandparent')
		UT.testClassProperties('parent', 'grandparent')
		UT.testClassProperties('child', 'parent')	      
    end
)

----------------------------------------------------------------------
UT.test('OO.construction and destruction',
	function()
		rerequire'ObjectOrientedParadigm'
		declareClass {
            name = 'grandparent',
            construct = function(self) 
				UT.check(self.one == nil)
				self.one = 1 
			end,
            destruct = function(self) 
				UT.check(self.one == 1)
				self.one = self.one - 1 
			end			
        }

        declareClass {
            name = 'parent',
            extends = 'grandparent',
            construct = function(self) 
				UT.check(self.one == 1)
				self.one = self.one + 1
				UT.check(self.two == nil)
				self.two = 1
			end,
            destruct = function(self) 
				UT.check(self.one == 2)
				self.one = self.one - 1
				UT.check(self.two == 1)
				self.two = self.two - 1 
			end			
        }

        declareClass {
			name = 'child',
            extends = 'parent',
             construct = function(self) 
				UT.check(self.one == 2)
				self.one = self.one + 1
				UT.check(self.two == 1)
				self.two = self.two + 1
				UT.check(self.three == nil)
				self.three = 1
			end,
            destruct = function(self) 
				UT.check(self.one == 3)
				self.one = self.one - 1
				UT.check(self.two == 2)
				self.two = self.two - 1
				UT.check(self.three == 1)
				self.three = 0
			end			
        }
		
		local gp = new'grandparent'
		local p = new'parent'
		local c = new'child'
		delete(gp)
		delete(p)
		delete(c)
		UT.check(next(gp) == nil)
		UT.check(next(p) == nil)
		UT.check(next(c) == nil)
		UT.testClassProperties('grandparent')
		UT.testClassProperties('parent', 'grandparent')
		UT.testClassProperties('child', 'parent')	      
	end
)

----------------------------------------------------------------------
UT.test('OOP.abstract classes',
	function()
		rerequire'ObjectOrientedParadigm'
		
		declareAbstractClass{
			name = 'AbstractNoFunctions'
		}
		
		declareAbstractClass{
			name = 'AbstractConcreteFunctions',
			concrete = function() return 1 end 
		}
		
		declareAbstractClass{
			name = 'AbstractMixedMethods',
			concrete = function() return 1 end,
			abstract = {
				overrideme = function() print'I am not implemented' end
			}
		}
			
		declareClass{
			name = 'Did override',
			extends = 'AbstractMixedMethods',
			overrideme = function() print'I AM implemented' end,
			concrete = function() return 2 end
		}
		
		declareClass{
			name = 'son of Did override',
			extends = 'Did override',
		}
		
		UT.checkError(
			function()
				declareClass{
					name = 'Didn\'t override',
					extends = 'AbstractMixedMethods',
					concrete = function() return 2 end
				}
			end
		)
		
		UT.checkError(
			function()
				local a = new'AbstractNoFunction'
			end
		)
		
		local d = new'Did override'
		UT.check(d:concrete() == 2)
		local e = new'son of Did override'
		UT.check(e:concrete() == 2)
		UT.check(e:IS_A'son of Did override')
		UT.check(e:IS_A'Did override')
		UT.check(not e:IS_EXACTLY_A'Did override')
		UT.check(e:IS_A'AbstractMixedMethods')	
		UT.check(not e:IS_EXACTLY_A'AbstractMixedMethods')	
	end
)

----------------------------------------------------------------------
UT.test('OOP.classes and functions',
	function()
		rerequire'ObjectOrientedParadigm'
		declareClass{name = 'one'}
		declareClass{name = 'two'}
		local i = 0
		for k, v in classes() do
			UT.check(type(v) == 'table')
			if i == 0 then
				UT.check(v:getClassName() == 'one')
			elseif i == 1 then
				UT.check(v:getClassName() == 'two')
			end
			i = i + 1
		end
		
		declareClass{name = 'three',
			one = function() return 1 end,
			two = function() return 2 end,
			three = function() return 3 end
		}
		
		local c = new'three'
		
		for k, v in functions(c) do
			UT.check(type(v) == 'function')
			if k == 'one' then
				UT.check(v(c) == 1)
			elseif k == 'two' then
				UT.check(v(c) == 2)
			elseif k == 'three' then
				UT.check(v(c) == 3)
			end			
		end
		UT.testClassProperties('one')
		UT.testClassProperties('two')
		UT.testClassProperties('three')	      
	end
)

----------------------------------------------------------------------
UT.test('OOP.common class properties',
function()
	rerequire'ObjectOrientedParadigm'
	declareClass{name = 'Basic'}
	declareClass{name ='Derived', extends = 'Basic'}
	
	local b = new'Basic'
	local bname = DEBUG_INTERPRETATION and 'Basic 1' or 'Basic'
	UT.check(type(b.class) == 'table')
	UT.check(b:getName() == bname)
	UT.check(b:toString() == bname)
	UT.check(b.class == getClass'Basic')
	UT.check(b:getClass() == getClass'Basic')
	UT.check(b.className == 'Basic')
	UT.check(b:getClassName() == 'Basic')
	UT.check(b.super == nil)
	UT.check(b:getSuperclass() == nil)
	
	local d = new'Derived'
	local dname = DEBUG_INTERPRETATION and 'Derived 1' or 'Derived'
	UT.check(type(d.class) == 'table')
	UT.check(d:toString() == dname)	
	UT.check(d:getName() == dname)
	UT.check(d.class == getClass'Derived')
	UT.check(d:getClass() == getClass'Derived')
	UT.check(d.className == 'Derived')
	UT.check(d:getClassName() == 'Derived')
	UT.check(d.super == getClass'Basic')
	UT.check(d:getSuperclass() == getClass'Basic')
	
	UT.testClassProperties('Basic')
	UT.testClassProperties('Derived', 'Basic')	     	
end)

----------------------------------------------------------------------
UT.test('OOP reserved words',
function()
	rerequire'ObjectOrientedParadigm'
	
	local declareBadClass = function(reservedWord)
		return function()
			local ErrorProne = {}
			ErrorProne.name = 'ErrorProne'
			ErrorProne[reservedWord] = function() print'I should not compile' end
			declareClass(ErrorProne)
		end	
	end
	
	UT.checkError(declareBadClass'ACTS_AS')
	UT.checkError(declareBadClass'class')
	UT.checkError(declareBadClass'className')
	UT.checkError(declareBadClass'getClass')
	UT.checkError(declareBadClass'getClassName')
	UT.checkError(declareBadClass'getSuperclass')
	UT.checkError(declareBadClass'IS_A')
	UT.checkError(declareBadClass'IS_EXACTLY_A')
	UT.checkError(declareBadClass'super')
end)



----------------------------------------------------------------------
UT.test('OOP.constuction and metatable methods',
function()
	UT = require'UnitTestingFramework'
	----------------------------------------------------------------------
	-- __new,		__setmetatable
	local Both = {
		name = 'Both',		
		construct = function(self, ...)
			self.value = 1
		end,		
		__new = function(...)
			return {...}
		end,		
		__setmetatable = function(table, mt)
			return setmetatable(table, mt)
		end,		
		only = function(self)
			return self.value + 1
		end
	}
	declareClass(Both)
	local BothChild = { 
		name = 'BothChild', 
		extends = 'Both' 
	}
	declareClass(BothChild)
	_G.instanceBoth = new'Both'
	_G.instanceBoth_child = new'BothChild'
	UT.testRefreshClassAbilities(Both, 'Both')
    UT.testRefreshClassAbilities(BothChild, 'BothChild', 'Both')
	UT.checkT(instanceBoth.only, 'function')
	UT.checkT(instanceBoth.value, 'number')
	UT.checkEqual(instanceBoth:only(), 2)
	UT.testInstanceProperties(instanceBoth, 'Both') 
	UT.checkT(instanceBoth_child.only, 'function')
	UT.checkT(instanceBoth_child.value, 'number')
	UT.checkEqual(instanceBoth_child:only(), 2)
	UT.testInstanceProperties(instanceBoth_child, 'BothChild', 'Both')
	
	----------------------------------------------------------------------
	-- OOP,			__setmetatable
	local SetMetatable = {
		name = 'SetMetatable',		
		construct = function(self, ...)
			self.value = 1
		end,		
		__setmetatable = function(table, mt)
			return setmetatable(table, mt)
		end,		
		only = function(self)
			return self.value + 1
		end
	}
	declareClass(SetMetatable)
	local SetMetatableChild = { 
		name = 'SetMetatableChild', 
		extends = 'SetMetatable' 
	}
	declareClass(SetMetatableChild)
	_G.instanceSetMetatable = new'SetMetatable'
	_G.instanceSetMetatable_child = new'SetMetatableChild'
	UT.testRefreshClassAbilities(SetMetatable, 'SetMetatable')
    UT.testRefreshClassAbilities(SetMetatableChild, 'SetMetatableChild', 'SetMetatable')
	UT.checkT(instanceSetMetatable.only, 'function')
	UT.checkT(instanceSetMetatable.value, 'number')
	UT.checkEqual(instanceSetMetatable:only(), 2)
	UT.testInstanceProperties(instanceSetMetatable, 'SetMetatable') 
	UT.checkT(instanceSetMetatable_child.only, 'function')
	UT.checkT(instanceSetMetatable_child.value, 'number')
	UT.checkEqual(instanceSetMetatable_child:only(), 2)
	UT.testInstanceProperties(instanceSetMetatable_child, 'SetMetatableChild', 'SetMetatable')
	
	----------------------------------------------------------------------
	-- __new,		OOP
	local NewOnly = {
		name = 'NewOnly',		
		construct = function(self, ...)
			self.value = 1
		end,		
		__new = function(...)
			return {...}
		end,		
		only = function(self)
			return self.value + 1
		end
	}
	declareClass(NewOnly)
	local NewOnlyChild = { 
		name = 'NewOnlyChild', 
		extends = 'NewOnly' 
	}
	declareClass(NewOnlyChild)
	_G.instanceNewOnly = new'NewOnly'
	_G.instanceNewOnly_child = new'NewOnlyChild'
	UT.testRefreshClassAbilities(NewOnly, 'NewOnly')
    UT.testRefreshClassAbilities(NewOnlyChild, 'NewOnlyChild', 'NewOnly')
	UT.checkT(instanceNewOnly.only, 'function')
	UT.checkT(instanceNewOnly.value, 'number')
	UT.checkEqual(instanceNewOnly:only(), 2)
	UT.testInstanceProperties(instanceNewOnly, 'NewOnly') 
	UT.checkT(instanceNewOnly_child.only, 'function')
	UT.checkT(instanceNewOnly_child.value, 'number')
	UT.checkEqual(instanceNewOnly_child:only(), 2)
	UT.testInstanceProperties(instanceNewOnly_child, 'NewOnlyChild', 'NewOnly')
	
	----------------------------------------------------------------------
	-- OOP,			OOP
	local Neither = {
		name = 'Neither',		
		construct = function(self, ...)
			self.value = 1
		end,		
		only = function(self)
			return self.value + 1
		end
	}
	declareClass(Neither)
	local NeitherChild = { 
		name = 'NeitherChild', 
		extends = 'Neither' 
	}
	declareClass(NeitherChild)
	_G.instanceNeither = new'Neither'
	_G.instanceNeither_child = new'NeitherChild'
	UT.testRefreshClassAbilities(Neither, 'Neither')
    UT.testRefreshClassAbilities(NeitherChild, 'NeitherChild', 'Neither')
	UT.checkT(instanceNeither.only, 'function')
	UT.checkT(instanceNeither.value, 'number')
	UT.checkEqual(instanceNeither:only(), 2)
	UT.testInstanceProperties(instanceNeither, 'Neither') 
	UT.checkT(instanceNeither_child.only, 'function')
	UT.checkT(instanceNeither_child.value, 'number')
	UT.checkEqual(instanceNeither_child:only(), 2)
	UT.testInstanceProperties(instanceNeither_child, 'NeitherChild', 'Neither')
end)

----------------------------------------------------------------------
UT.test('OOP.misc',
function()
	rerequire'ObjectOrientedParadigm'
	declareClass{
		name = 'Easy', 
		toString = function() return 'simple' end, 
		__tostring == toString,
		__concat = OOP.toStringConcat
	}
	
	declareInterface{
		name = 'Hard',
		never = function() end
	}
	
	declareClass {
		name = 'Mixed',
		implements = 'Hard',
		never = function() end
	}
	
	e = new'Easy'
	z = new'Easy'
	UT.check(e..z == 'simplesimple')
	UT.check(e..'hello' == 'simplehello')
	UT.check('goodbye'..z == 'goodbyesimple')
	
	local ctor = function()
		return {}
	end
	
	OOP.addClassConstructor('void', ctor)
	v = new'void'
	UT.check(v ~= nil)
	
	m = new'Mixed'
	OOP.validateObject(m, 'Mixed', {'Hard'})
	UT.checkError(
		function()
			OOP.validateObject(e, 'Easy', {'Hard'})
		end)
	UT.checkError(
		function()
			OOP.validateObject(z, 'Mixed')
		end)
end)

