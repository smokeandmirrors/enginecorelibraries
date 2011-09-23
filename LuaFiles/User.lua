module(..., package.seeall)

require'Utilities'
require'ObjectOrientedParadigm'
require'Vector3PureLua'
UT = require'UnitTestingFramework'

_G.u = function()
	rerequire'User'
end

function _G.testFile()
	local CW = rerequire'CodeWriting'
	local EN2S = rerequire'LuaExposeNativeToScript'
	local myFile = io.open('MyFile.h', 'w+')
	EN2S.generateHeader(myFile, 10, 10)
end

function _G.cwtest()
	u()
	testFile()
end

---[[
function _G.returnOneParamZero()
	return 17
end	
--]]

---[[
function _G.returnZeroParamZero()
	printf'script zero zero'
end
--]]

---[[
function _G.returnZeroParamOne(value)
	printf('script zero one '..value)
end
--]]



function _G.throwError()
	error'FAIL!'
end

_G.loader = function(modulename)
	local errmsg = ""
	-- Find source
	local modulepath = string.gsub(modulename, "%.", "/")
	for path in string.gmatch(package.path, "([^;]+)") do
		local filename = string.gsub(path, "%?", modulepath)
		print(filename)
		--[[
		local file = io.open(filename, "rb")
		if file then
			-- Compile and return the module
			return assert(loadstring(assert(file:read("*a")), filename))
		end
		--]]
		errmsg = errmsg.."\n\tno file '"..filename.."' (checked with custom loader)"
	end
	return errmsg
end

_G.callable = function(aNumber, aBoolean)
	aNumber = aNumber + 1
	aBoolean = not aBoolean
	return aNumber, aBoolean
end

_G.callable2 = function(aNumber, anotherNumber)
	return aNumber + anotherNumber
end

_G.test = function()
	indices = {"one", "two","three", "four", "five", "six", "seven" }
	agp = new'AllPublicGrandChild'
	for k, v in pairs(indices) do 
		print(v, agp[v])
	end
--[[	
	local v = new'Value_sint4'
	v:setValue(7)
	assert(v:getValue() == 7)
	print(v:getValue())


	vpt(1000)
	vpt(10000)
	vpt(100000)
	vpt(1000000)
--]]
end

_G.vpt = function(iterations)
	print'\n\n\n\nStart Lua->Lua!'
	local script_start = os.clock()
	vectorPerformance('Vector3PureLua', iterations)
	local script_end = os.clock()
	print'Finis Lua->Lua!'
	print'Start Lua->Native!'
	local native_start = os.clock()
	vectorPerformance('Vector3', iterations)
	local native_end = os.clock()
	print'Finis Lua->Native!'
	print'Start Native->Native!'
	local all_native_start = os.clock()
	nativeVectorPerformance(iterations)
	local all_native_end = os.clock()
	print'Finis Native->Native!'
	local native = os.difftime(native_end, native_start)
	local script = os.difftime(script_end, script_start)
	local all_native = os.difftime(all_native_end, all_native_start)
	print'************************************'
	print('Iterations: '..tostring(iterations))
	printf('Script: %f\nNative: %f\nAll Native: %f\nNative was %fx faster than script\nAll native was %fx faster than script.', 
		script, native, all_native, script/native, script/all_native)
	print'************************************'
	
end



vectorPerformance = function(class_name, iterations)
	iterations = iterations or 100
	local instance = new(class_name)
	local v = new(class_name, 3,2,1)
	local w = new(class_name, 3,2,1)
	local x = new(class_name, 1,3,2)
	local z = new(class_name)
	local Xpos = new(class_name, 1, 0, 0)
	local Ypos = new(class_name, 0, 1, 0)
	local Zpos = new(class_name, 0, 0, 1)
	local Xneg = new(class_name,-1, 0, 0)
	local Yneg = new(class_name, 0,-1, 0)
	local Zneg = new(class_name, 0, 0,-1)
	local neg123 = new(class_name, -1,-2,-3)
	local pos234 = new(class_name, 2,3,4)
		
	collectgarbage'collect'
	
	for i=1,iterations do
		v:__eq(w)
		local is_true
		is_true = (v == w)
		v:add(x)
		v:subtract(x)
		v:construct(math.pi, math.pi/2, math.pi/3)
		v:construct(math.pi/4)
		v:construct(w)
		v:setEach(10,0,0)
		v:distance(z)
		v:distanceSqr(z)
		v:distanceXY(z)
		v:distanceXYSqr(z) 
		v:setEach(0,10,0)
		v:distance(z)
		v:distanceSqr(z)
		v:distanceXY(z) 
		v:distanceXYSqr(z)
		v:setEach(0,0,10)
		v:distance(z)
		v:distanceSqr(z) 
		v:distanceXY(z) 
		v:distanceXYSqr(z) 
		v:setEach(1,1,1)
		v:distance(z) 
		v:distanceSqr(z) 
		v:distanceXY(z) 
		v:distanceXYSqr(z) 
		v:normalize()
		v:distance(z) 
		v:distanceSqr(z) 
		v:setEach(0,1,1)
		v:distanceXY(z) 
		v:distanceXYSqr(z) 
		v:setEach(8,4,2)
		v:divide(2)
		v:setEach(8,4,2)
		v:divide(8,4,2)
		v:setEach(100,100,100)
		v:divide(50, 25, 10)
		v:setEach(1,2,3)
		z:setEach(-1,-2,-3)
		local v_dot_z = v:dot(z)
		local z_dot_v = z:dot(v)
		v:setEqual(w)
		v:equals(w)
		w:equals(v)
		v:zero()
		z:setEach(0,0,10)
		v:isFar(z,5)
		is_true = not v:isFar(z,10)
		is_true = not v:isFarXY(z,0)
		is_true = not v:isFarXY(z,0)
		is_true = v:isNear(z,10)
		is_true = not v:isNear(z,9.99)
		is_true = v:isNearXY(z,0)
		v:setEach(10000000, 0, 0)
		v:normalize()
		v:isNormal()
		v:magnitude()
		v:setEach(0, 10000000, 0)
		v:normalize()
		v:isNormal()
		v:magnitude()
		v:setEach(0, 0, 10000000)
		v:normalize()
		is_true = v:isNormal()
		v:magnitude()
		is_true = not w:isNormal()
		is_true = not w:isZero()
		v:setAll(0)
		v:isZero()
		v:setEach(2,0,0)
		v:magnitude()
		v:magnitudeSqr()
		v:magnitudeXY()
		v:magnitudeXYSqr()
		v:setEach(0,2,0)
		v:magnitudeSqr()
		v:magnitude()
		v:magnitudeXY()
		v:magnitudeXYSqr()
		v:setEach(0,0,2)
		v:magnitude()
		v:magnitudeSqr()
		v:magnitudeXY()
		v:magnitudeXYSqr()
		z:setEach(0,0,2.00001)
		is_true = not v:equals(z)
		is_true = v ~= z
		v:nearlyEquals(z)
		v:setEach(2,3,4)
		v:negate()
		v:negate()
		v:scale(2)
		v:scale(1/4, 1/6, 1/8)
		v:scale(pos234)
		v:zero()
		v:subtract(1,2,3)
		v:subtract(neg123)
		is_true = v:isZero()
		v:subtract(9)
		-- x positive
		v:setEqual(Xpos)
		v:cross(Zpos)
		v:setEqual(Xpos)
		v:cross(Ypos)
		v:setEqual(Xpos)
		v:cross(Zneg)
		v:setEqual(Xpos)
		v:cross(Yneg)
		-- y positive
		v:setEqual(Ypos)
		v:cross(Zpos)
		v:setEqual(Ypos)
		v:cross(Xneg)
		v:setEqual(Ypos)
		v:cross(Zneg)
		v:setEqual(Ypos)
		v:cross(Xpos)
		-- z positive
		v:setEqual(Zpos)
		v:cross(Yneg)
		v:setEqual(Zpos)
		v:cross(Xpos)
		v:setEqual(Zpos)
		v:cross(Ypos)
		v:setEqual(Zpos)
		v:cross(Xneg)
		-- perpendicular
		v:setEach(2,3,4)
		w:setEqual(v)
		v:perpendicular()
		v:dot(w)
		v:setEach(-4,-2,-3)
		w:setEqual(v)
		v:perpendicular()
	end
end