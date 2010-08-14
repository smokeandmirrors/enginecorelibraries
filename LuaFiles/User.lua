module(..., package.seeall)
require'Utilities'
require'ObjectOrientedParadigm'

_G.U = function()
	rerequire'User'
end

_G.test = function()
	local UTF = rerequire'UnitTestingFramework'
	rerequire'UnitTesting'
	rerequire'OOPUnitTesting'
	UTF.runAll()
end

