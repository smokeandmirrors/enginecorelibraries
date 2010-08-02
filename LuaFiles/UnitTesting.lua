module('UnitTesting', package.seeall)
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
	\todo testSuite function for multiple tests by the same name
--]]

--[[
	result checking functions
--]]

----------------------------------------------------------------------
-- checks that value of given the expression is true
check = function(value)
	assert(value, 'check failed: '..tostring(value)..'is not true')
end

----------------------------------------------------------------------
-- checks the values for equality within the given tolerance
checkEqual = function(lhs, rhs, tolerance)
	if type(tolerance) != 'number' then
		assert(lhs == rhs, 'checkEqual failed: '..tostring(lhs)..
			' is not equal to '..tostring(rhs))
	else
		checkNearEqual(tolerance)
	end
end

----------------------------------------------------------------------
-- checks the values for equality within the given tolerance
checkNearEqual = function(lhs, rhs, tolerance)
	assert((math.abs((lhs - rhs)/rhs)) < tolerance, 
		'checkEqual failed: '..tostring(lhs)..
		' is not equal to '..tostring(rhs)..
		' within '..tostring(tolerance))
end

----------------------------------------------------------------------
-- checks that the given function called with the passed in 
-- arguments will throw an error 
checkError = function(test_function, ...)
	--\ todo check test_function called with
	-- args and report true if it errors
	local result, output = pcall(test_function, ...)
	assert(not result, 'the function did not produce an error as expected')
end

--[[
	test writing functions
--]]

----------------------------------------------------------------------
-- creates a test out of the passed in function
-- the result is returned for manual testing, and will
-- get exicuted by UnitTesting.runAll()
test = function(name, test_function)
	createTestFunction(name, test_function))
end

--[[
	implementation
--]]

----------------------------------------------------------------------
createTestFunction = function(name, test_function)
	local tester = function()
		local success, error_message = pcall(test_function)
		if not success then
			reportFailure(name, error_message)
		end
	end
	table.insert(UnitTesting.unitTests, tester)
end

----------------------------------------------------------------------
reportFailure = function(name, error_message)
	table.insert(failedTests, {test = tostring(name), description = error_message})
end

----------------------------------------------------------------------
-- runs all the unit test functions
reportResults = function()
	local i = 0
	local start_time = os.clock()
	
	for _, failure in pairs(failedTests) do
		print('FAILED! '..tostring(failure.test)..':'..failure.description..'\n') 
		i = i + 1
	end
	
	local end_time = os.clock()
	
	if i == 0 then
		print'All unit tests SUCCEEDED!\n'
	else
		print(tostring(i)..' unit tests FAILED!!!!!!!!\n')
	end
	
	print(tostring(table.count(unitTest))..' run in '..tostring(end_time - start_time)..' seconds\n')
	return i
	-- \report status
	-- \report individual failures
end

----------------------------------------------------------------------
-- runs all the unit test functions
-- \return the number of failures
runAll = function()
	for _, tester in pairs(unitTests) do
		tester();
	end
	
	return reportResults()
end

unitTests = {}
failedTests = {}

