module("Vector3PureLua", package.seeall)
----------------------------------------------------------------------
-- @file Vector3PureLua.lua
-- a 3D Vector for experimenting with extention from C
-- @author Smoke and Mirrors Development
-- copyright 2010
-- @date 02/24/2010
--
require "ObjectOrientedParadigm"
require "Vector2PureLua"

local vector3ToString = function(self)
        return string.format("(%8.2f, %8.2f, %8.2f)", self.x or -777, self.y or -777, self.z or -777)
end

----------------------------------------------------------------------
local Vector3PureLua = {}

----------------------------------------------------------------------
Vector3PureLua.name = "Vector3PureLua"
Vector3PureLua.extends = "Vector2PureLua"
----------------------------------------------------------------------
-- adds a vector to self
-- @return self
function Vector3PureLua:Add(v)
        self.x = self.x + v.x
        self.y = self.y + v.y
        self.z = self.z + v.z
        return self
end

----------------------------------------------------------------------
-- adds a vector to self
-- @return self
function Vector3PureLua:AddComponent(x, y, z)
        self.x = self.x + x
        self.y = self.y + y
        self.z = self.z + z
        return self
end
----------------------------------------------------------------------
-- initalizes to passed in numbers.  Usage: v = new("Vector3PureLua", 1,2,3) or v = new("Vector3PureLua", otherVec)
function Vector3PureLua:construct(...)
        if ... then
                self:Set(...)
        end
end

----------------------------------------------------------------------
-- 3D vector component multiply
-- @return self
function Vector3PureLua:ComponentMul(v)
        self.x = self.x * v.x
        self.y = self.y * v.y
        self.z = self.z * v.z
        return self
end

----------------------------------------------------------------------
-- 3D vector component division
-- @return self
function Vector3PureLua:ComponentDiv(v)
        self.x = self.x / v.x
        self.y = self.y / v.y
        self.z = self.z / v.z
        return self
end

----------------------------------------------------------------------
-- 3D vector cross product
-- @return self
function Vector3PureLua:Cross(v)
        local a, b, c
        a = self.y * v.z - self.z * v.y
        b = self.z * v.x - self.x * v.z
        c = self.x * v.y - self.y * v.x
        self.x = a
        self.y = b
        self.z = c
        return self
end
----------------------------------------------------------------------
-- @return distance between to vectors
function Vector3PureLua:Distance(v)
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
function Vector3PureLua:DistanceSqr(v)
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
function Vector3PureLua:DistanceXY(v)
        local length = 0
        local element = self.x - v.x
        length = length + (element * element)
        element = self.y - v.y
        length = length + (element * element)
        return math.sqrt(length)
end
----------------------------------------------------------------------
-- @return squared xy distance
function Vector3PureLua:DistanceXYSqr(v)
        local length = 0
        local element = self.x - v.x
        length = length + (element * element)
        element = self.y - v.y
        length = length + (element * element)
        return length
end
----------------------------------------------------------------------
-- @return vector dot product
function Vector3PureLua:Dot(v)
        return self.x * v.x + self.y * v.y + self.z * v.z
end
----------------------------------------------------------------------
-- unpack the elements of the class
-- @return 3 numbers
function Vector3PureLua:Elements()
        return self.x, self.y, self.z
end
----------------------------------------------------------------------
-- internal vector compare. use == to compare pointers
-- @return true if the vectors have the same 3D elements
function Vector3PureLua:Equals(v)
        return (rawequal(self,v)) or (self.x == v.x and self.y == v.y and self.z == v.z)
end
----------------------------------------------------------------------
-- creates a table of 3 numbers, all zero
function Vector3PureLua:construct(...)
        local a, b, c = ...
        if a then
                if b then
                        self.x = a
                        self.y = b
                        self.z = c or 0
                else
                        self.x = a.x
                        self.y = a.y
                        self.z = a.z
                end
        else
                self.x = 0
                self.y = 0
                self.z = 0
        end
end
----------------------------------------------------------------------
-- checks wither the vector is close enough to another
function Vector3PureLua:IsFar(pos, range)
        return self:DistanceSqr(pos) >= (range * range)
end
----------------------------------------------------------------------
-- checks wither the vector is close enough to another
function Vector3PureLua:IsFarXY(pos, range)
        return self:DistanceXYSqr(pos) >= (range * range)
end
----------------------------------------------------------------------
-- checks wither the vector is close enough to another
function Vector3PureLua:IsNear(pos, range)
        return self:DistanceSqr(pos) <= (range * range)
end
----------------------------------------------------------------------
-- checks wither the vector is close enough to another
function Vector3PureLua:IsNearXY(pos, range)
        return self:DistanceXYSqr(pos) <= (range * range)
end
----------------------------------------------------------------------
-- checks each element for a valid number
function Vector3PureLua:IsValid()
        return math.isvalid(self.x) and math.isvalid(self.y) and math.isvalid(self.z)
end
----------------------------------------------------------------------
-- @return the magnitude of the vector
function Vector3PureLua:Length()
        return math.sqrt(self.x * self.x + self.y * self.y + self.z * self.z)
end
----------------------------------------------------------------------
-- @return the squared magnitude of the vector
function Vector3PureLua:LengthSqr()
        return self.x * self.x + self.y * self.y + self.z * self.z
end
----------------------------------------------------------------------
-- @return the magnitude of the vector on the xy plane only
function Vector3PureLua:LengthXY()
        return math.sqrt(self.x * self.x + self.y * self.y)
end
----------------------------------------------------------------------
-- @return the squared magnitude of the vector on the xy plane only
function Vector3PureLua:LengthXYSqr()
        return self.x * self.x + self.y * self.y
end
----------------------------------------------------------------------
-- negates the vector
-- @return self
function Vector3PureLua:Negate()
        self.x = -self.x
        self.y = -self.y
        self.z = -self.z
        return self
end
----------------------------------------------------------------------
-- normalized the vector, sets it to unit length
-- @returns the original length of the vector, for convenience
function Vector3PureLua:Normalize()
        local length = math.sqrt(self.x * self.x + self.y * self.y + self.z * self.z)
        self.x = self.x / length
        self.y = self.y / length
        self.z = self.z / length
        return length
end

function Vector3PureLua:Rotate(m)
        self:Set(self.x * m[1][1] + self.y * m[2][1] + self.z * m[3][1],
                self.x * m[1][2] + self.y * m[2][2] + self.z * m[3][2],
                self.x * m[1][3] + self.y * m[2][3] + self.z * m[3][3])
        return self
end

----------------------------------------------------------------------
-- multiply each element of the vector by the passed in scalar
-- @param scalar multiple
-- @return self
function Vector3PureLua:Scale(scalar)
        self.x = self.x * scalar
        self.y = self.y * scalar
        self.z = self.z * scalar
        return self
end
----------------------------------------------------------------------
-- sets the vector to the passed in values
-- @param ... either a table with x,y,z indices (another vector), or 3 numbers
function Vector3PureLua:SetNoAssert(...)
        local x, y, z = ...
        if y then
                self.x = x
                self.y = y
                self.z = z
        elseif x then
                self.x = x.x
                self.y = x.y
                self.z = x.z
        end
        return self
end

function Vector3PureLua:SetWithAssert(...)
        local x, y, z = ...
        if y then
                assert(x and y and z, "bad data in Vector3PureLua")
                self.x = x
                self.y = y
                self.z = z
        elseif x then
                assert(x.x and x.y and x.z, "bad data in Vector3PureLua")
                self.x = x.x
                self.y = x.y
                self.z = x.z
        else
                error("bad data in Vector3PureLua")
        end
        return self
end

if DEBUG_INTERPRETATION then
        Vector3PureLua.Set = Vector3PureLua.SetWithAssert
else
        Vector3PureLua.Set = Vector3PureLua.SetNoAssert
end
----------------------------------------------------------------------
-- subtracts a vector from self
-- @return self
function Vector3PureLua:Subtract(v)
        self.x = self.x - v.x
        self.y = self.y - v.y
        self.z = self.z - v.z
        return self
end

function Vector3PureLua:Transform(m)
        self:Set(self.x * m[1][1] + self.y * m[2][1] + self.z * m[3][1] + m[4][1],
                self.x * m[1][2] + self.y * m[2][2] + self.z * m[3][2] + m[4][2],
                self.x * m[1][3] + self.y * m[2][3] + self.z * m[3][3] + m[4][3])
        return self
end

function Vector3PureLua:WithinBounds(v1, v2)
        return self.x >= v1.x and self.x <= v2.x and self.y >= v1.y and self.y <= v2.y and self.z >= v1.z and self.z <= v2.z
end

----------------------------------------------------------------------
-- @return the magnitude of the vector
function Vector3PureLua:Distance(v)
        return math.sqrt((self.x - v.x) * (self.x - v.x) + (self.y - v.y) * (self.y - v.y) + (self.z - v.z) * (self.z - v.z))
end
----------------------------------------------------------------------
-- @return the squared magnitude of the vector
function Vector3PureLua:DistanceSqr(v)
        return (self.x - v.x) * (self.x - v.x) + (self.y - v.y) * (self.y - v.y) + (self.z - v.z) * (self.z - v.z)
end
----------------------------------------------------------------------
-- @return a string representation of the vector
Vector3PureLua.ToString = vector3ToString
----------------------------------------------------------------------
-- the "+" operator.  Adds a vector to self
-- @return self
function Vector3PureLua.__add(lhs, rhs)
        return new("Vector3PureLua", lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z)
end
----------------------------------------------------------------------
-- the ".." operator.  concats a string version
Vector3PureLua.__concat = ObjectOrientedParadigm.toStringConcat
----------------------------------------------------------------------
-- the "/" operator.  Devides each element of self by the divisor
-- @return self
function Vector3PureLua.__div(lhs, rhs)
        return new("Vector3PureLua", lhs.x / rhs, lhs.y / rhs, lhs.z / rhs)
end
----------------------------------------------------------------------
-- the "*" operator. multiplies each element of self by the scalar
-- @return self
function Vector3PureLua.__mul(lhs, rhs)
        return new("Vector3PureLua", lhs.x * rhs, lhs.y * rhs, lhs.z * rhs)
end
----------------------------------------------------------------------
-- the "-" (subtraction) operator.  Subtracts a vector from self
-- @return self
function Vector3PureLua.__sub(lhs, rhs)
        return new("Vector3PureLua", lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z)
end
----------------------------------------------------------------------
-- called when passed as an arguement to print().
-- @return a pretty, text version
-- Vector3PureLua.__tostring = vector3ToString
----------------------------------------------------------------------
-- the "-" (unary minus) operator.  Negates the vector
-- @return self
function Vector3PureLua.__unm(rhs)
        return new("Vector3PureLua", -rhs.x, -rhs.y, -rhs.z)
end
----------------------------------------------------------------------
-- the "==" compare by value operator
-- @return boolean
function Vector3PureLua.__eq(lhs, rhs)
        return rawequal(lhs, rhs) or (lhs.x == rhs.x and lhs.y == rhs.y and lhs.z == rhs.z)
end

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
