deprecatedNaughtyModule(..., package.seeall)

require 'ObjectOrientedParadigm'
UT = require'UnitTestingFramework'

_G.staticReturn2Param2 = function(one, two)
	UT.check(IS_A(one, 'One'))
	UT.check(IS_A(two, 'Two'))
	return one, two
end

local Two = getClass'Two'

function Two.error(...)
	return _G.error(...)
end

function Two:memberReturn2Param2Script(one, two)
	UT.check(IS_A(self, 'Two'))
	UT.check(IS_A(one, 'One'))
	UT.check(IS_A(two, 'Two'))
	return one, two
end

function Two:constReturn2Param2Script(one, two)
	UT.check(IS_A(self, 'Two'))
	UT.check(IS_A(one, 'One'))
	UT.check(IS_A(two, 'Two'))
	return one, two
end