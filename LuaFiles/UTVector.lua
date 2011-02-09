module(..., package.seeall)
local OOP = require'ObjectOrientedParadigm'
local UT = require'UnitTestingFramework'
require 'Utilities'

function testVectorClass(class_name)
	local instance = new(class_name)
	UT.testInstanceProperties(instance, class_name)
	local v = new(class_name, 3,2,1)
	local w = new(class_name, 3,2,1)
	local x = new(class_name, 1,3,2)
	UT.checkT(v.x, 'number')
	UT.checkT(v.y, 'number')
	UT.checkT(v.z, 'number')
	UT.checkT(v.__eq, 'function')
	UT.checkT(v.add, 'function')
	UT.checkT(v.construct, 'function')
	UT.checkT(v.cross, 'function')
	UT.checkT(v.distance, 'function')
	UT.checkT(v.distanceSqr, 'function')
	UT.checkT(v.distanceXY, 'function')
	UT.checkT(v.distanceXYSqr, 'function')
	UT.checkT(v.divide, 'function')
	UT.checkT(v.dot, 'function')
	UT.checkT(v.equals, 'function')
	UT.checkT(v.isFar, 'function')
	UT.checkT(v.isFarXY, 'function')
	UT.checkT(v.isNear, 'function')
	UT.checkT(v.isNearXY, 'function')
	UT.checkT(v.isNormal, 'function')
	UT.checkT(v.isZero, 'function')
	UT.checkT(v.magnitude, 'function')
	UT.checkT(v.magnitudeSqr, 'function')
	UT.checkT(v.magnitudeXY, 'function')
	UT.checkT(v.magnitudeXYSqr, 'function')
	UT.checkT(v.nearlyEquals, 'function')
	UT.checkT(v.negate, 'function')
	UT.checkT(v.normalize, 'function')
	UT.checkT(v.perpendicular, 'function')
	UT.checkT(v.scale, 'function')
	UT.checkT(v.set, 'function')
	UT.checkT(v.subtract, 'function')
	UT.checkT(v.zero, 'function')
	UT.checkVector(v,3,2,1)
	UT.checkVector(x,1,3,2)
	UT.checkVector(w,3,2,1)
	UT.check(v:__eq(w))
	UT.check(v == w)
	UT.checkVector(v,3,2,1)
	UT.checkVector(w,3,2,1)
	v:negate()
	UT.checkVector(v,-3,-2,-1)
	v:negate()
	UT.checkVector(v,3,2,1)
	v:add(x)
	UT.checkVector(v,4,5,3)
	v:subtract(x)
	UT.checkVector(v,3,2,1)
	UT.checkVector(w,3,2,1)
	v:construct(math.pi, math.pi/2, math.pi/3)
	UT.checkVector(v,math.pi, math.pi/2, math.pi/3)
	v:construct(math.pi/4)
	UT.checkVector(v,math.pi/4, math.pi/4, math.pi/4)
	v:construct(w)
	UT.checkVector(v,3,2,1)
	UT.checkVector(w,3,2,1)
	z = new(class_name)
	UT.checkVector(z,0,0,0,0)
	v:set(10,0,0)
	UT.checkVector(v, 10, 0, 0, 0)
	UT.checkEqual(v:distance(z), 10)
	UT.checkVector(z,0,0,0,0)
	UT.checkEqual(v:distanceSqr(z), 100)
	UT.checkVector(z,0,0,0,0)
	UT.checkEqual(v:distanceXY(z), 10)
	UT.checkVector(z,0,0,0,0)
	UT.checkEqual(v:distanceXYSqr(z), 100)
	UT.checkVector(z,0,0,0,0)
	v:set(0,10,0)
	UT.checkVector(v, 0, 10, 0, 0)
	UT.checkEqual(v:distance(z), 10)
	UT.checkEqual(v:distanceSqr(z), 100)
	UT.checkEqual(v:distanceXY(z), 10)
	UT.checkEqual(v:distanceXYSqr(z), 100)
	v:set(0,0,10)
	UT.checkVector(v, 0, 0, 10, 0)
	UT.checkEqual(v:distance(z), 10)
	UT.checkEqual(v:distanceSqr(z), 100)
	UT.checkEqual(v:distanceXY(z), 0)
	UT.checkEqual(v:distanceXYSqr(z), 0)
	v:set(1,1,1)
	UT.checkVector(v, 1, 1, 1, 0)
	UT.checkNearEqual(v:distance(z), 1.73205)
	UT.checkEqual(v:distanceSqr(z), 3)
	UT.checkNearEqual(v:distanceXY(z), 1.414213)
	UT.checkEqual(v:distanceXYSqr(z), 2)
	v:normalize()
	UT.checkNearEqual(v:distance(z), 1)
	UT.checkNearEqual(v:distanceSqr(z), 1)
	v:set(0,1,1)
	UT.checkNearEqual(v:distanceXY(z), 1)
	UT.checkNearEqual(v:distanceXYSqr(z), 1)
	v:set(8,4,2)
	v:divide(2)
	UT.checkVector(v,4,2,1)
	v:set(8,4,2)
	UT.checkVector(v,8,4,2)
	v:divide(8,4,2)
	UT.checkVector(v, 1,1,1)
	v:set(100,100,100)
	v:divide(50, 25, 10)
	UT.checkVector(v,2,4,10)
	v:set(1,2,3)
	UT.checkVector(v,1,2,3,0)
	z:set(-1,-2,-3)
	UT.checkVector(z,-1,-2,-3,0)
	local v_dot_z = v:dot(z)
	local z_dot_v = z:dot(v)
	UT.checkEqual(v_dot_z, z_dot_v)
	UT.checkEqual(v_dot_z, -14)
	UT.checkEqual(z_dot_v, -14)
	UT.checkVector(z,-1,-2,-3,0)
	UT.checkVector(v,1,2,3,0)
	v:set(w)
	UT.check(v:equals(w))
	UT.check(w:equals(v))
	UT.check(not rawequal(v, w))
	UT.check(not rawequal(w, v))
	v:zero()
	UT.checkVector(v, 0,0,0)
	z:set(0,0,10)
	UT.checkVector(z,0,0,10)
	UT.check(v:isFar(z,5))
	UT.check(not v:isFar(z,10))
	UT.check(not v:isFarXY(z,0))
	UT.check(not v:isFarXY(z,0))
	UT.checkVector(z,0,0,10)
	UT.checkVector(v, 0,0,0)
	UT.check(v:isNear(z,10))
	UT.check(not v:isNear(z,9.99))
	UT.check(v:isNearXY(z,0))
	v:set(10000000, 0, 0)
	UT.checkEqual(v:normalize(), 10000000)
	UT.check(v:isNormal())
	UT.checkEqual(v:magnitude(), 1)
	UT.checkVector(v,1,0,0)
	v:set(0, 10000000, 0)
	UT.checkEqual(v:normalize(), 10000000)
	UT.check(v:isNormal())
	UT.checkEqual(v:magnitude(), 1)
	UT.checkVector(v,0,1,0)
	v:set(0, 0, 10000000)
	UT.checkEqual(v:normalize(), 10000000)
	UT.check(v:isNormal())
	UT.checkEqual(v:magnitude(), 1)
	UT.checkVector(v,0,0,1)
	UT.check(not w:isNormal())
	UT.check(not w:isZero())
	v:set(0)
	UT.checkVector(v,0,0,0,0)
	UT.check(v:isZero())
	v:set(2,0,0)
	UT.checkVector(v,2,0,0,0)
	UT.check(v:magnitude(), 2)
	UT.check(v:magnitudeSqr(), 4)
	UT.check(v:magnitudeXY(), 2)
	UT.check(v:magnitudeXYSqr(), 4)
	v:set(0,2,0)
	UT.checkVector(v,0,2,0,0)
	UT.check(v:magnitudeSqr(), 4)
	UT.check(v:magnitude(), 2)
	UT.check(v:magnitudeXY(), 2)
	UT.check(v:magnitudeXYSqr(), 4)
	v:set(0,0,2)
	UT.checkVector(v,0,0,2,0)
	UT.check(v:magnitude(), 2)
	UT.check(v:magnitudeSqr(), 4)
	UT.check(v:magnitudeXY(), 0)
	UT.check(v:magnitudeXYSqr(), 0)
	z:set(0,0,2.00001)
	UT.check(not v:equals(z))
	UT.check(v ~= z)
	UT.check(v:nearlyEquals(z))
	v:set(2,3,4)
	UT.checkVector(v,2,3,4,0)
	v:negate()
	UT.checkVector(v,-2,-3,-4,0)
	v:negate()
	UT.checkVector(v,2,3,4,0)
	v:scale(2)
	UT.checkVector(v,4,6,8,0)
	v:scale(1/4, 1/6, 1/8)
	UT.checkVector(v,1,1,1,0)
	v:scale(new(class_name, 2,3,4))
	UT.checkVector(v,2,3,4,0)
	v:zero()
	UT.checkVector(v,0,0,0,0)
	v:subtract(1,2,3)
	UT.checkVector(v,-1,-2,-3)
	v:subtract(new(class_name, -1,-2,-3))
	UT.check(v:isZero())
	UT.checkVector(v,0,0,0,0)
	v:subtract(9)
	UT.checkVector(v,-9,-9,-9,0)
	local Xpos = new(class_name, 1, 0, 0)
	local Ypos = new(class_name, 0, 1, 0)
	local Zpos = new(class_name, 0, 0, 1)
	local Xneg = new(class_name,-1, 0, 0)
	local Yneg = new(class_name, 0,-1, 0)
	local Zneg = new(class_name, 0, 0,-1)
	-- x positive
	v:set(Xpos)
	v:cross(Zpos)
	UT.checkEqual(v, Yneg)
	v:set(Xpos)
	v:cross(Ypos)
	UT.checkEqual(v, Zpos)
	v:set(Xpos)
	v:cross(Zneg)
	UT.checkEqual(v, Ypos)
	v:set(Xpos)
	v:cross(Yneg)
	UT.checkEqual(v, Zneg)
	-- y positive
	v:set(Ypos)
	v:cross(Zpos)
	UT.checkEqual(v, Xpos)
	v:set(Ypos)
	v:cross(Xneg)
	UT.checkEqual(v, Zpos)
	v:set(Ypos)
	v:cross(Zneg)
	UT.checkEqual(v, Xneg)
	v:set(Ypos)
	v:cross(Xpos)
	UT.checkEqual(v, Zneg)
	-- z positive
	v:set(Zpos)
	v:cross(Yneg)
	UT.checkEqual(v, Xpos)
	v:set(Zpos)
	v:cross(Xpos)
	UT.checkEqual(v, Ypos)
	v:set(Zpos)
	v:cross(Ypos)
	UT.checkEqual(v, Xneg)
	v:set(Zpos)
	v:cross(Xneg)
	UT.checkEqual(v, Yneg)
	-- perpendicular
	v:set(2,3,4)
	w:set(v)
	v:perpendicular()
	UT.checkEqual(v:dot(w), 0)
	v:set(-4,-2,-3)
	w:set(v)
	v:perpendicular()
	UT.checkEqual(v:dot(w), 0)
end

UT.test('Vector3 Lua',
	function()
		require'Vector3PureLua'
		testVectorClass('Vector3PureLua')
	end
)

UT.test('Vector3 native',
	function()
		testVectorClass('Vector3')
	end
)