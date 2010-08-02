module(..., package.seeall)
require'Utilities'
require'ObjectOrientedParadigm'
local UT = require'UnitTesting'

_G.U = function()
	rerequire'User'
end

print('finished requiring user')


UT.test('succeed',
	function() 
		UT.check(true, 'sweet')
	end
)

print('finished requiring user')


UT.test('failure',
	function() 
		UT.check(false, 'awesome')
	end
)

print('finished requiring user')
