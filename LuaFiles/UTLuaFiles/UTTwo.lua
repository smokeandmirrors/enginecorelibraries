deprecatedNaughtyModule(..., package.seeall)

function memberReturn2Param2(self, one, two)
	UT.check(IS_A(self, 'Two'))
	UT.check(IS_A(one, 'One'))
	UT.check(IS_A(two, 'Two'))
	return one, two
end

function constReturn2Param2(self, one, two)
	UT.check(IS_A(self, 'Two'))
	UT.check(IS_A(one, 'One'))
	UT.check(IS_A(two, 'Two'))
	return one, two
end