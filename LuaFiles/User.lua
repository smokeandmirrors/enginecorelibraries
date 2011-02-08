module(..., package.seeall)
_G.DEBUG_INTERPRETATION = true

require'Utilities'
require'ObjectOrientedParadigm'

_G.u = function()
	rerequire'User'
end

_G.test = function()
end

module(..., package.seeall)

require'Utilities'

_G.u = function()
	rerequire'User'
end

_G.test = function()
end

numberOfOnlys = 0

_G.Only = {
	construct = function(self)
		print'Constructed'
		numberOfOnlys = numberOfOnlys + 1
		self.number = numberOfOnlys
	end,
	public = function(self)
		return self.number
	end,
	protected = function(self)
		local fenv = getfenv(2)
		if fenv.class == _G.sOnly then
			print'Allowed call to protected'
		else
			print'DISALLOWED call to protected'
		end
		return self.number + 1 
	end,
	private = function(self)
		local fenv = getfenv(2)
		if fenv.class == _G.sOnly then
			print'Allowed call to private'
		else
			print'DISALLOWED call to private'
		end
		return self.number + 2
	end,
	callProtected = function(self)
		return self:protected()
	end,
	callPrivate = function(self)
		return self:private()
	end
}
Only.class = Only

_G.new = function()
	local instance = setmetatable({}, { __index = Only })
	instance:construct()
	return instance
end
_G.a = new()
a:public()
a:callProtected()
a:callPrivate()
a:protected()
a:private()
