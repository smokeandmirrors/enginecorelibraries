module(..., package.seeall)
----------------------------------------------------------------------
-- UnitTesting.lua
--
-- This file defines a module which provides a unit testing
-- framework in Lua
--
--	\author Smoke and Mirrors Development
--	\email smokeandmirrorsdevelopment@gmail.com
--	\copyright 2010
require'Utilities'

--[[
	result checking functions
--]]

----------------------------------------------------------------------
-- checks that value of given the expression is true
check = function(value)

end

----------------------------------------------------------------------
-- checks the values for equality within the given tolerance
checkEqual = function(lhs, rhs, tolerance)
	if (type(tolerance) != 'number')
		-- \todo check for equality, report the failure
		-- if not equal, error with information about what went wrong?
		unitTest.reportEqual((math.abs((lhs - rhs)/rhs)) < tolerance, 
			"checkEqual failed: "..tostring(lhs)..
			" is not equal to "..tostring(rhs)..
			" within "..tostring(tolerance))
	else
		checkNearEqual(tolerance)
	end
end

----------------------------------------------------------------------
-- checks the values for equality within the given tolerance
checkNearEqual = function(lhs, rhs, tolerance)
	-- \todo check for equality within the toleranc, report the failure
end

----------------------------------------------------------------------
-- checks that the given function called with the passed in 
-- arguments will throw an error 
checkError = function(test_function, ...)
	--\ todo check test_function called with
	-- args and report true if it errors
end

--[[
	test writing functions
--]]

----------------------------------------------------------------------
-- creates a test out of the passed in function
-- the result is returned for manual testing, and will
-- get exicuted by UnitTesting.runAll()
test = function(test_function)
	table.insert(unitTests, createTestFunction(test_function))
end

--[[
	implementation
--]]

----------------------------------------------------------------------
createTestFunction = function(test_function)
	
end

----------------------------------------------------------------------
-- runs all the unit test functions
report = function()
	-- \report status
	-- \report individual failures
end

----------------------------------------------------------------------
-- runs all the unit test functions
runAll = function()
	for _, test_function in pairs(unitTests) do
		test_function()
	end
	
	report()
end

unitTests = {}
failedTests = {}

