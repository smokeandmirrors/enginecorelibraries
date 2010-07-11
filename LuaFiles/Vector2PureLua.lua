module("Vector2PureLua", package.seeall)
----------------------------------------------------------------------
-- @file Vector2PureLua.lua
-- a 2D Vector for experimenting with extention from C
-- @author Smoke and Mirrors Development
-- copyright 2010
-- @date 02/24/2010
--
require "ObjectOrientedParadigm"

local vector2ToString = function(self)
	return string.format("(%8.2f, %8.2f)", self.x or -1, self.y or -1)
end

----------------------------------------------------------------------
-- Class V2
local Vector2PureLua = {}
----------------------------------------------------------------------
Vector2PureLua.name = "Vector2PureLua"
----------------------------------------------------------------------
-- adds a vector to self
-- @return self
function Vector2PureLua:Add(v)
	self.x = self.x + v.x
	self.y = self.y + v.y 
	return self
end
----------------------------------------------------------------------
-- initalizes to passed in numbers.  Usage: v = new("V2", 1,2)
function Vector2PureLua:ArgsConstructor(...)
	local a,b = ...
	self.x = a and a or self.x
	self.y = b and b or self.y
end
----------------------------------------------------------------------
-- @return distance between to vectors
function Vector2PureLua:Distance(v)
	v2Scratch:Set(self)
	v2Scratch:Subtract(v)
	return v2Scratch:Length()
end
----------------------------------------------------------------------
-- @return squared distance
function Vector2PureLua:DistanceSqr(v)
	v2Scratch:Set(self)
	v2Scratch:Subtract(v)
	return v2Scratch:LengthSqr()
end
----------------------------------------------------------------------
-- @return vector dot product
function Vector2PureLua:Dot(v)
	return self.x * v.x + self.y * v.y 
end
----------------------------------------------------------------------
-- unpack the elements of the class
-- @return 2 numbers
function Vector2PureLua:Elements()
	return self.x, self.y
end 
----------------------------------------------------------------------
-- internal vector compare. use == to compare pointers
-- @return true if the vectors have the same 2D elements
function Vector2PureLua:Equals(v)
	return self.x == v.x and self.y == v.y
end
----------------------------------------------------------------------
-- creates a table of 2 numbers, all zero
function Vector2PureLua:construct(...)
	local a,b = ...
	if a then
		if b then
			self.x = a 
			self.y = b 
		else
			self.x = a.x
			self.y = a.y
		end
	else
		self.x = 0
		self.y = 0
	end	
end
----------------------------------------------------------------------
-- checks each element for a valid number
function Vector2PureLua:IsValid()
	return math.isvalid(self.x) and math.isvalid(self.y)
end
----------------------------------------------------------------------
-- @return the magnitude of the vector
function Vector2PureLua:Length()
	return math.sqrt(self.x * self.x + self.y * self.y)
end
----------------------------------------------------------------------
-- @return the squared magnitude of the vector
function Vector2PureLua:LengthSqr()
	return self.x * self.x + self.y * self.y
end
----------------------------------------------------------------------
-- negates the vector
-- @return self
function Vector2PureLua:Negate()
	self.x = -self.x
	self.y = -self.y
	return self
end
----------------------------------------------------------------------
-- normalized the vector, sets it to unit length
-- @returns the original length of the vector, for convenience
function Vector2PureLua:Normalize()
	local length = self:Length()
	self.x = self.x / length
	self.y = self.y / length
	return length
end
----------------------------------------------------------------------
-- multiply each element of the vector by the passed in scalar
-- @param scalar multiple
-- @return self
function Vector2PureLua:Scale(scalar)
	self.x = self.x * scalar
	self.y = self.y * scalar
	return self
end
----------------------------------------------------------------------
-- sets the vector to the passed in values
-- @param ... either a Vector2PureLua, or 2 numbers
function Vector2PureLua:Set(...)
	local x,y = ...
	if y then
		self.x = x
		self.y = y
	elseif x then
		self.x = x.x
		self.y = x.y
	end
	return self
end
----------------------------------------------------------------------
-- subtracts a vector from self
-- @return self
function Vector2PureLua:Subtract(v)
	self.x = self.x - v.x
	self.y = self.y - v.y
	return self
end
----------------------------------------------------------------------
Vector2PureLua.ToString = vector2ToString
----------------------------------------------------------------------
-- the "+" operator.  Adds a vector to self
-- @return self
Vector2PureLua.__add = function(lhs, rhs)
	return new("Vector2PureLua", lhs.x + rhs.x, lhs.y + rhs.y)
end
----------------------------------------------------------------------
-- the ".." operator.  concats a string version
Vector2PureLua.__concat = ObjectOrientedParadigm.toStringConcat
----------------------------------------------------------------------
-- the "/" operator.  Devides each element of self by the divisor
-- @return self
Vector2PureLua.__div = function(lhs, rhs)
	return new("Vector2PureLua", lhs.x / rhs, lhs.y / rhs)
end
----------------------------------------------------------------------
-- the "*" operator. multiplies each element of self by the scalar
-- @return self
Vector2PureLua.__mul = function(lhs, rhs)
	return new("Vector2PureLua", lhs.x * rhs, lhs.y * rhs)
end
----------------------------------------------------------------------
-- the "-" (subtraction) operator.  Subtracts a vector from self
-- @return self
Vector2PureLua.__sub = function(lhs, rhs)
	return new("Vector2PureLua", lhs.x - rhs.x, lhs.y - rhs.y)
end
----------------------------------------------------------------------
-- called when passed as an arguement to print(). 
-- @return a pretty, text version
Vector2PureLua.__tostring = vector2ToString
----------------------------------------------------------------------
-- the "==" compare by value operator
-- @return boolean
Vector2PureLua.__eq = function(lhs, rhs)
	return rawequal(lhs, rhs) or lhs.x == rhs.x and lhs.y == rhs.y 
end

declareClass(Vector2PureLua)

-- to be used in internal calculations only
v2Scratch = new 'Vector2PureLua'
