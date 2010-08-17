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
----------------------------------------------------------------------
UT.test('OO.polymorphism',
    function()
		-- convenience for (re)writing the test
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
        
        gp = new'grandparent'
        UT.check(type(gp) == 'table')
        UT.check(IS_A(gp, 'grandparent'))
        UT.check(type(gp.IS_A) == 'function' and gp:IS_A'grandparent');
        UT.check(type(gp.getNickName) == 'function' and gp.getNickName() == 'papa')
        UT.check(type(gp.isOld) == 'function' and gp.isOld())        
        
        p = new'parent'
        UT.check(type(p) == 'table')
        UT.check(IS_A(p, 'grandparent'))
        UT.check(IS_A(p, 'parent'))        
        UT.check(type(p.IS_A) == 'function' and p:IS_A'grandparent')
        UT.check(type(p.IS_A) == 'function' and p:IS_A'parent')
        UT.check(type(p.getNickName) == 'function' and p.getNickName() == 'daddy')
		UT.check(type(p.isMiddleAged) == 'function' and p.isMiddleAged())
        UT.check(type(p.isOld) == 'function' and p.isOld())        
        
        c = new'child'
        UT.check(type(c) == 'table')
        UT.check(IS_A(c, 'grandparent'))
        UT.check(IS_A(c, 'parent'))
		UT.check(IS_A(c, 'child'))
		UT.check(type(c.IS_A) == 'function' and c:IS_A'grandparent')
        UT.check(type(c.IS_A) == 'function' and c:IS_A'parent')
        UT.check(type(c.IS_A) == 'function' and c:IS_A'child')
		UT.check(type(c.getNickName) == 'function' and c.getNickName() == 'buggaboo')
		UT.check(type(c.isMiddleAged) == 'function' and c.isMiddleAged())
        UT.check(type(c.isOld) == 'function' and c.isOld())  
		UT.check(type(c.isYoung) == 'function' and c.isYoung())      
    end
)

----------------------------------------------------------------------
UT.test('OO.construction and destruction',
	function()
		-- convenience for (re)writing the test
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
		
		gp = new'grandparent'
		p = new'parent'
		c = new'child'
		delete(gp)
		delete(p)
		delete(c)
		UT.check(next(gp) == nil)
		UT.check(next(p) == nil)
		UT.check(next(c) == nil)
	end
)

----------------------------------------------------------------------
UT.test('OOP.abstract classes',
	function()
		-- convenience for (re)writing the test
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
				a = new'AbstractNoFunction'
			end
		)
		
		d = new'Did override'
		UT.check(d:concrete() == 2)
		e = new'son of Did override'
		UT.check(e:concrete() == 2)
		UT.check(e:IS_A'son of Did override')
		UT.check(e:IS_A'Did override')
		UT.check(e:IS_A'AbstractMixedMethods')		
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
		
		c = new'three'
		
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
	end
)

----------------------------------------------------------------------
UT.test('OOP.common class properties',
function()
	rerequire'ObjectOrientedParadigm'
	declareClass{name = 'Basic'}
	declareClass{name ='Derived', extends = 'Basic'}
	
	b = new'Basic'
	UT.check(type(b.class) == 'table')
	UT.check(b.class == getClass'Basic')
	UT.check(b:getClass() == getClass'Basic')
	UT.check(b.className == 'Basic')
	UT.check(b:getClassName() == 'Basic')
	UT.check(b:getName() == 'Basic')
	UT.check(b.super == nil)
	UT.check(b:getSuperclass() == nil)
	UT.check(b:toString() == 'Basic')
	
	d = new'Derived'
	sprint(d)
	UT.check(type(d.class) == 'table')
	UT.check(d.class == getClass'Derived')
	UT.check(d:getClass() == getClass'Derived')
	UT.check(d.className == 'Derived')
	UT.check(d:getClassName() == 'Derived')
	UT.check(d:getName() == 'Derived')
	UT.check(d.super == getClass'Basic')
	UT.check(d:getSuperclass() == getClass'Basic')
	UT.check(d:toString() == 'Derived')
	
	
end)

----------------------------------------------------------------------
UT.test('OOP.misc',
function()
	-- \todo validateObject
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

