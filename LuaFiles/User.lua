module(..., package.seeall)
_G.DEBUG_INTERPRETATION = true

require'Utilities'
require'ObjectOrientedParadigm'

_G.u = function()
	rerequire'User'
end

_G.test = function()
	_G.v = new('Vector3', 3,4,5)
	_G.v2 = new('Vector3', v)
	_G.v3 = new('Vector3', math.pi)
end

