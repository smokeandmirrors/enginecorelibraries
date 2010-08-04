module(..., package.seeall)
require'Utilities'
require'ObjectOrientedParadigm'
local UT = require'UnitTesting'
print(tostring(UT)..' I broke require!')
_G.U = function()
	rerequire'User'
end

print('finished requiring user 1')

-- debug.sethook(function(str, line) print(str..tostring(line)..'\n') end, 'crl')

UnitTesting.test('succeed',
	function() 
		UnitTesting.check(true, 'sweet')
	end
)

print('finished requiring user 2')


UnitTesting.test('failure',
	function() 
		UnitTesting.check(false, 'awesome')
	end
)

print('finished requiring user 3')

UnitTesting.runAll()