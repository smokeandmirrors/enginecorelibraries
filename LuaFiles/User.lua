module(..., package.seeall)

require'Utilities'
require'ObjectOrientedParadigm'
require'Vector3PureLua'
UT = require'UnitTestingFramework'

_G.u = function()
	rerequire'User'
end

_G.test = function()
	vpt(1000)
	vpt(10000)
	vpt(100000)
	vpt(1000000)
end

_G.vpt = function(iterations)
	print'\n\n\n\nStart Lua->Native!'
	collectgarbage'collect'
	local native_start = os.clock()
	vectorPerformance('Vector3', iterations)
	local native_end = os.clock()
	print'Finis Lua->Native!'
	collectgarbage'collect'
	print'Start Lua->Lua!'
	local script_start = os.clock()
	vectorPerformance('Vector3PureLua', iterations)
	local script_end = os.clock()
	print'Finis Lua->Lua!'
	collectgarbage'collect'
	print'Start Native->Native!'
	local all_native_start = os.clock()
	nativeVectorPerformance(iterations)
	local all_native_end = os.clock()
	print'Finis Native->Native!'
	-- nativeVectorPerformance
	
	local native = os.difftime(native_end, native_start)
	local script = os.difftime(script_end, script_start)
	local all_native = os.difftime(all_native_end, all_native_start)
	print'************************************************************************************************'
	printf('Native: %f. Script: %f. All Native: %f.  Native was %fx faster; Native native was %fx faster.', 
		native, script, all_native, script/native, script/all_native)
	print'************************************************************************************************'
	
end



vectorPerformance = function(class_name, iterations)
	iterations = iterations or 100
	for i=1,iterations do
	local instance = new(class_name)
	local v = new(class_name, 3,2,1)
	local w = new(class_name, 3,2,1)
	local x = new(class_name, 1,3,2)
	v:__eq(w)
	local is_true
	is_true = (v == w)
	v:add(x)
	v:subtract(x)
	v:construct(math.pi, math.pi/2, math.pi/3)
	v:construct(math.pi/4)
	v:construct(w)
	local z
	z = new(class_name)
	v:set(10,0,0)
	v:distance(z)
	v:distanceSqr(z)
	v:distanceXY(z)
	v:distanceXYSqr(z) 
	v:set(0,10,0)
	v:distance(z)
	v:distanceSqr(z)
	v:distanceXY(z) 
	v:distanceXYSqr(z)
	v:set(0,0,10)
	v:distance(z)
	v:distanceSqr(z) 
	v:distanceXY(z) 
	v:distanceXYSqr(z) 
	v:set(1,1,1)
	v:distance(z) 
	v:distanceSqr(z) 
	v:distanceXY(z) 
	v:distanceXYSqr(z) 
	v:normalize()
	v:distance(z) 
	v:distanceSqr(z) 
	v:set(0,1,1)
	v:distanceXY(z) 
	v:distanceXYSqr(z) 
	v:set(8,4,2)
	v:divide(2)
	v:set(8,4,2)
	v:divide(8,4,2)
	v:set(100,100,100)
	v:divide(50, 25, 10)
	v:set(1,2,3)
	z:set(-1,-2,-3)
	local v_dot_z = v:dot(z)
	local z_dot_v = z:dot(v)
	v:set(w)
	v:equals(w)
	w:equals(v)
	v:zero()
	z:set(0,0,10)
	v:isFar(z,5)
	is_true = not v:isFar(z,10)
	is_true = not v:isFarXY(z,0)
	is_true = not v:isFarXY(z,0)
	is_true = v:isNear(z,10)
	is_true = not v:isNear(z,9.99)
	is_true = v:isNearXY(z,0)
	v:set(10000000, 0, 0)
	v:normalize()
	v:isNormal()
	v:magnitude()
	v:set(0, 10000000, 0)
	v:normalize()
	v:isNormal()
	v:magnitude()
	v:set(0, 0, 10000000)
	v:normalize()
	is_true = v:isNormal()
	v:magnitude()
	is_true = not w:isNormal()
	is_true = not w:isZero()
	v:set(0)
	v:isZero()
	v:set(2,0,0)
	v:magnitude()
	v:magnitudeSqr()
	v:magnitudeXY()
	v:magnitudeXYSqr()
	v:set(0,2,0)
	v:magnitudeSqr()
	v:magnitude()
	v:magnitudeXY()
	v:magnitudeXYSqr()
	v:set(0,0,2)
	v:magnitude()
	v:magnitudeSqr()
	v:magnitudeXY()
	v:magnitudeXYSqr()
	z:set(0,0,2.00001)
	is_true = not v:equals(z)
	is_true = v ~= z
	v:nearlyEquals(z)
	v:set(2,3,4)
	v:negate()
	v:negate()
	v:scale(2)
	v:scale(1/4, 1/6, 1/8)
	v:scale(new(class_name, 2,3,4))
	v:zero()
	v:subtract(1,2,3)
	v:subtract(new(class_name, -1,-2,-3))
	is_true = v:isZero()
	v:subtract(9)
	local Xpos = new(class_name, 1, 0, 0)
	local Ypos = new(class_name, 0, 1, 0)
	local Zpos = new(class_name, 0, 0, 1)
	local Xneg = new(class_name,-1, 0, 0)
	local Yneg = new(class_name, 0,-1, 0)
	local Zneg = new(class_name, 0, 0,-1)
	-- x positive
	v:set(Xpos)
	v:cross(Zpos)
	v:set(Xpos)
	v:cross(Ypos)
	v:set(Xpos)
	v:cross(Zneg)
	v:set(Xpos)
	v:cross(Yneg)
	-- y positive
	v:set(Ypos)
	v:cross(Zpos)
	v:set(Ypos)
	v:cross(Xneg)
	v:set(Ypos)
	v:cross(Zneg)
	v:set(Ypos)
	v:cross(Xpos)
	-- z positive
	v:set(Zpos)
	v:cross(Yneg)
	v:set(Zpos)
	v:cross(Xpos)
	v:set(Zpos)
	v:cross(Ypos)
	v:set(Zpos)
	v:cross(Xneg)
	-- perpendicular
	v:set(2,3,4)
	w:set(v)
	v:perpendicular()
	v:dot(w)
	v:set(-4,-2,-3)
	w:set(v)
	v:perpendicular()
	end
end