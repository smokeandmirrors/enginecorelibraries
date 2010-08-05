module(..., package.seeall)
require'Utilities'
require'ObjectOrientedParadigm'
local UT = require'UnitTesting'

_G.U = function()
	rerequire'User'
end

UnitTesting.test('succeed',
	function() 
		UnitTesting.check(true, 'sweet')
	end
)
UnitTesting.test('failure',
	function() 
		UnitTesting.check(false, 'awesome')
	end
)

UnitTesting.runAll()