module(..., package.seeall)
_G.DEBUG_INTERPRETATION = true

require'Utilities'
require'ObjectOrientedParadigm'

_G.u = function()
	rerequire'User'
end

_G.test = function()
	
end


function createGlobalClassMetatable(derived, super)
	local class = _G[derived]
	if class then
		local class_mt = ObjectOrientedParadigm.getMetatable[class_name]
		if not class_mt then
			class_mt = {}
			_G.C_metatables[class_name] = class_mt
		end
		for metamethodname, _ in pairs(metamethods) do
			if class[metamethodname] then
				class_mt[metamethodname] = class[metamethodname]
			end
		end
	end
end
