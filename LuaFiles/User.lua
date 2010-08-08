module(..., package.seeall)
require'Utilities'
require'ObjectOrientedParadigm'
local UT = require'UnitTesting'

_G.U = function()
	rerequire'User'
end

UT.test('succeed',
	function() 
		UT.check(true, 'sweet')
	end
)
UT.test('failure',
	function() 
		UT.check(false, 'awesome')
	end
)

UT.runAll()