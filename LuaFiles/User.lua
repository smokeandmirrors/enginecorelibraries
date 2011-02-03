module(..., package.seeall)
_G.DEBUG_INTERPRETATION = true

require'Utilities'
require'ObjectOrientedParadigm'

_G.u = function()
	rerequire'User'
end

_G.test = function()
	
end

_G.testdprint = function()
	_G.a = { 6, 5, 4 }
	_G.b = { 9, a, 7 }
	_G.c = { a, 10, b }
	dprint(c)
end