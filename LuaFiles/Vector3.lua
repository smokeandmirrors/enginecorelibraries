module("Vector3", package.seeall)
----------------------------------------------------------------------
-- @file Vector3.lua
-- an extension of the native Vector3 libarary,
-- mainly used for args construction
--
-- @author Smoke and Mirrors Development
-- @copyright 2011
--
--[[
function Vector3:construct(...)
	local x,y,z = ...
	local x_type = type(x)
	if x_type == 'number' then
		if type(y) == 'number' and type(z) == 'number' then
			self:set(x, y, z)
		else
			self:set(x)
		end
	elseif x_type == 'userdata' then
		if IS_EXACTLY_A(x, 'Vector3') then
			self:set(x)
		end
	end
end
--]]