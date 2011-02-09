module(..., package.seeall)
----------------------------------------------------------------------
-- @file Vector3PureLua.lua
-- a 3D Vector for experimenting with extention from C
-- @author Smoke and Mirrors Development
-- copyright 2010
-- @date 02/24/2010
--
require "ObjectOrientedParadigm"

local vector3ToString = function(self)
        return string.format("(%8.2f, %8.2f, %8.2f)", self.x or -777, self.y or -777, self.z or -777)
end

----------------------------------------------------------------------
local Vector3PureLua = {}
----------------------------------------------------------------------
Vector3PureLua.name = "Vector3PureLua"
----------------------------------------------------------------------
-- the "==" compare by value operator
-- @return boolean
function Vector3PureLua.__eq(lhs, rhs)
	return rawequal(lhs, rhs) or (lhs.x == rhs.x and lhs.y == rhs.y and lhs.z == rhs.z)
end
----------------------------------------------------------------------
-- the "-" (unary minus) operator.  Negates the vector
-- @return self
function Vector3PureLua.__unm(rhs)
	rhs.x = -rhs.x
	rhs.y = -rhs.y
	rhs.z = -rhs.z
	return rhs
end
----------------------------------------------------------------------
-- adds a vector to self
-- @return self
function Vector3PureLua:add(x, y, z)
	local type_x = type(x)
	if type_x == 'number' then
		if type(y) == 'number' then
			self.x = self.x + x
			self.y = self.y + y
			self.z = self.z + z
		else
			self.x = self.x + x
			self.y = self.y + x
			self.z = self.z + x
		end
	elseif type_x ~= nil then 
		self.x = self.x + x.x
		self.y = self.y + x.y
		self.z = self.z + x.z
	end
end
----------------------------------------------------------------------
-- initalizes to passed in numbers.  Usage: v = new("Vector3PureLua", 1,2,3) or v = new("Vector3PureLua", otherVec)
function Vector3PureLua:construct(...)
	local a, b, c = ...
	if type(a) == 'table' then
		if a ~= self then
			self.x = a.x
			self.y = a.y
			self.z = a.z
		end
	elseif a then
		if b then
			self.x = a
			self.y = b
			self.z = c or 0
		else
			self.x = a
			self.y = a
			self.z = a
		end
	else
		self.x = 0
		self.y = 0
		self.z = 0
	end
end
----------------------------------------------------------------------
-- 3D vector cross product
-- @return self
function Vector3PureLua:cross(v,w)
	if w then
		self.x = v.y * w.z - v.z * w.y;
		self.y = v.z * w.x - v.x * w.z;
		self.z = v.x * w.y - v.y * w.x;
	else	
		local a, b, c
		a = self.y * v.z - self.z * v.y
		b = self.z * v.x - self.x * v.z
		c = self.x * v.y - self.y * v.x
		self.x = a
		self.y = b
		self.z = c
	end
	return self
end
----------------------------------------------------------------------
-- @return distance between to vectors
function Vector3PureLua:distance(v)
	local element = self.x - v.x
	local length = (element * element)
	element = self.y - v.y
	length = length + (element * element)
	element = self.z - v.z
	length = length + (element * element)
	return math.sqrt(length)
end
----------------------------------------------------------------------
-- @return squared distance
function Vector3PureLua:distanceSqr(v)
	local element = self.x - v.x
	local length = (element * element)
	element = self.y - v.y
	length = length + (element * element)
	element = self.z - v.z
	length = length + (element * element)
	return length
end
----------------------------------------------------------------------
-- @return distance in the xy plane only
function Vector3PureLua:distanceXY(v)
	local length = 0
	local element = self.x - v.x
	length = length + (element * element)
	element = self.y - v.y
	length = length + (element * element)
	return math.sqrt(length)
end
----------------------------------------------------------------------
-- @return squared xy distance
function Vector3PureLua:distanceXYSqr(v)
	local length = 0
	local element = self.x - v.x
	length = length + (element * element)
	element = self.y - v.y
	length = length + (element * element)
	return length
end
----------------------------------------------------------------------
-- 3D vector component division
-- @return self
function Vector3PureLua:divide(x, y, z)
	local type_x = type(x)
	if type_x == 'number' then
		if type(y) == 'number' then
			self.x = self.x / x
			self.y = self.y / y
			self.z = self.z / z
		else
			self.x = self.x / x
			self.y = self.y / x
			self.z = self.z / x
		end
	elseif type_x ~= nil then 
		self.x = self.x / x.x
		self.y = self.y / x.y
		self.z = self.z / x.z
	end
	return self
end
----------------------------------------------------------------------
-- @return vector dot product
function Vector3PureLua:dot(v)
    return self.x * v.x + self.y * v.y + self.z * v.z
end
----------------------------------------------------------------------
-- internal vector compare. use == to compare pointers
-- @return true if the vectors have the same 3D elements
function Vector3PureLua:equals(v)
    return (rawequal(self,v)) or (self.x == v.x and self.y == v.y and self.z == v.z)
end
----------------------------------------------------------------------
-- checks wither the vector is close enough to another
function Vector3PureLua:isFar(v, range)
    local element = self.x - v.x
	local length = (element * element)
	element = self.y - v.y
	length = length + (element * element)
	element = self.z - v.z
	length = length + (element * element)
	return length > (range * range)   
end
----------------------------------------------------------------------
-- checks wither the vector is close enough to another
function Vector3PureLua:isFarXY(v, range)
	local element = self.x - v.x
	local length = (element * element)
	element = self.y - v.y
	length = length + (element * element)
	return length > (range * range)   
end
----------------------------------------------------------------------
-- checks wither the vector is close enough to another
function Vector3PureLua:isNear(v, range)
	local element = self.x - v.x
	local length = (element * element)
	element = self.y - v.y
	length = length + (element * element)
	element = self.z - v.z
	length = length + (element * element)
	return length <= (range * range)
end
----------------------------------------------------------------------
-- checks wither the vector is close enough to another
function Vector3PureLua:isNearXY(v, range)
	local element = self.x - v.x
	local length = (element * element)
	element = self.y - v.y
	length = length + (element * element)
	return length <= (range * range)   
end
----------------------------------------------------------------------
function Vector3PureLua:isNormal()
	return self.x * self.x + self.y * self.y + self.z * self.z == 1
end
----------------------------------------------------------------------
function Vector3PureLua:isZero()
	return self.x == 0 and self.y == 0 and self.z == 0
end
----------------------------------------------------------------------
-- @return the magnitude of the vector
function Vector3PureLua:magnitude()
	return math.sqrt(self.x * self.x + self.y * self.y + self.z * self.z)
end
----------------------------------------------------------------------
-- @return the squared magnitude of the vector
function Vector3PureLua:magnitudeSqr()
    return self.x * self.x + self.y * self.y + self.z * self.z
end
----------------------------------------------------------------------
-- @return the magnitude of the vector on the xy plane only
function Vector3PureLua:magnitudeXY()
    return math.sqrt(self.x * self.x + self.y * self.y)
end
----------------------------------------------------------------------
-- @return the squared magnitude of the vector on the xy plane only
function Vector3PureLua:magnitudeXYSqr()
    return self.x * self.x + self.y * self.y
end
----------------------------------------------------------------------
-- equality
-- @return self
function Vector3PureLua:nearlyEquals(v, epsilon)
	epsilon = epsilon or 0.0001
	return math.abs(self.x - v.x) <= epsilon 
		and math.abs(self.y - v.y) <= epsilon 
		and math.abs(self.z - v.z) <= epsilon
end
----------------------------------------------------------------------
-- negates the vector
-- @return self
function Vector3PureLua:negate()
	self.x = -self.x
	self.y = -self.y
	self.z = -self.z
end
----------------------------------------------------------------------
-- normalized the vector, sets it to unit magnitude
-- @returns the original magnitude of the vector, for convenience
function Vector3PureLua:normalize()
    local magnitude = math.sqrt(self.x * self.x + self.y * self.y + self.z * self.z)
    local divisor = 1 / magnitude
    self.x = self.x * divisor
    self.y = self.y * divisor
    self.z = self.z * divisor
    return magnitude
end
----------------------------------------------------------------------
function Vector3PureLua:perpendicular()
	if self.x ~= 0 or self.y ~= 0 then
		self:cross(_G.WorldAxes.posZ)
	else 
		self:cross(_G.WorldAxes.posY)
	end
end
----------------------------------------------------------------------
-- 3D vector component multiply
-- @return self
function Vector3PureLua:scale(x, y, z)
    local type_x = type(x)
	if type_x == 'number' then
		if type(y) == 'number' then
			self.x = self.x * x
			self.y = self.y * y
			self.z = self.z * z
		else
			self.x = self.x * x
			self.y = self.y * x
			self.z = self.z * x
		end
	elseif type_x ~= nil then 
		self.x = self.x * x.x
		self.y = self.y * x.y
		self.z = self.z * x.z
	end
	return self
end
----------------------------------------------------------------------
-- sets the vector to the passed in values
-- @param ... either a table with x,y,z indices (another vector), or 3 numbers
Vector3PureLua.set = Vector3PureLua.construct
----------------------------------------------------------------------
-- subtract a vector to self
-- @return self
function Vector3PureLua:subtract(x, y, z)
	local type_x = type(x)
	if type_x == 'number' then
		if type(y) == 'number' then
			self.x = self.x - x
			self.y = self.y - y
			self.z = self.z - z
		else
			self.x = self.x - x
			self.y = self.y - x
			self.z = self.z - x
		end
	elseif type_x ~= nil then 
		self.x = self.x - x.x
		self.y = self.y - x.y
		self.z = self.z - x.z
	end
end
----------------------------------------------------------------------
function Vector3PureLua:zero()
	self.x = 0
	self.y = 0
	self.z = 0
end
----------------------------------------------------------------------
-- @return a string representation of the vector
Vector3PureLua.ToString = vector3ToString
----------------------------------------------------------------------
-- called when passed as an arguement to print().
-- @return a pretty, text version
Vector3PureLua.__tostring = vector3ToString

declareClass(Vector3PureLua)

-- to be used in internal calculations only
v3Scratch = new 'Vector3PureLua'
-- global scratch
_G.v3 = new 'Vector3PureLua'
-- world origin
_G.origin = new('Vector3PureLua', 0,0,0)
-- global cardinal axes
_G.WorldAxes =
{
	posZ =  new("Vector3PureLua", 0, 0, 1),
	negZ =  new("Vector3PureLua", 0, 0,-1),
	posX =  new("Vector3PureLua", 1, 0, 0),
	negX =  new("Vector3PureLua",-1, 0, 0),
	posY =  new("Vector3PureLua", 0, 1, 0),
	negY =  new("Vector3PureLua", 0,-1, 0),
}
