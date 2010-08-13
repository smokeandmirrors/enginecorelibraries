module('UnitTestingFramework', package.seeall)
----------------------------------------------------------------------
-- UnitTestingFramework.lua
--
-- This file defines a module which provides a unit testing
-- framework in Lua
--
--	\author Smoke and Mirrors Development
--	\email smokeandmirrorsdevelopment@gmail.com
--	\copyright 2010
require'Utilities'

--[[
a unuique name isn't madatory, but 
will be easier for you

UT.test('name', 
	function()
	
	end
)
--]]

----------------------------------------------------------------------
-- PUBLIC
-- result checking functions

----------------------------------------------------------------------
-- checks that value of given the expression is true
check = function(value, fail_message)
	assert(value, 'check failed, '..tostring(value)..' is not true: '..(fail_message ~= nil and tostring(fail_message) or ''))
end

----------------------------------------------------------------------
-- checks the values for equality within the given tolerance
checkEqual = function(lhs, rhs, tolerance, fail_message)
	if type(tolerance) ~= 'number' then
		assert(lhs == rhs, 'checkEqual failed, '..tostring(lhs)..
			' is not equal to '..tostring(rhs)..': '..(fail_message ~= nil and tostring(fail_message) or ''))
	else
		checkNearEqual(tolerance)
	end
end

----------------------------------------------------------------------
-- checks the values for equality within the given tolerance
checkNearEqual = function(lhs, rhs, tolerance, fail_message)
	assert((math.abs((lhs - rhs)/rhs)) < tolerance, 
		'checkEqual failed, '..tostring(lhs)..
		' is not equal to '..tostring(rhs)..
		' within '..tostring(tolerance)..': '..(fail_message ~= nil and tostring(fail_message) or ''))
end

----------------------------------------------------------------------
-- checks that the given function called with the passed in 
-- arguments will throw an error 
checkError = function(test_function, fail_message, ...)
	--\ todo check test_function called with
	-- args and report true if it errors
	local result, output = pcall(test_function, ...)
	assert(not result, 'the function did not produce an error as expected: '..(fail_message ~= nil and tostring(fail_message) or ''))
end

----------------------------------------------------------------------
-- test writing functions

----------------------------------------------------------------------
-- creates a test out of the passed in function
-- the result is returned for manual testing, and will
-- get exicuted by runAll()
test = function(name, test_function)
	createTestFunction(name, test_function)
end

----------------------------------------------------------------------
-- runs all the unit test functions
-- \return the number of failures
runAll = function()
	for _, tester in pairs(unitTests) do
		tester();
	end
	-- \clean up after the framework
	-- \todo nil the loaded status of the unittesting framework
	-- \todo run a full garbage collect
	local num_failures, results = reportResults()
	unitTests = {}
	failedTests = {}	
	print(results)
	collectgarbage'collect'
	return num_failures, results
end

----------------------------------------------------------------------
-- PRIVATE
-- implementation

----------------------------------------------------------------------
createTestFunction = function(name, test_function)
	local tester = function()
		local success, error_message = pcall(test_function)
		if not success then
			reportFailure(name, error_message)
		end
	end
	
	table.insert(unitTests, tester)
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
	local results = '\n**************************************************'
	results = results..'\n************* Begin Lua Unit Testing *************\n'
	for _, failure in pairs(failedTests) do
		results = results..tostring(failure.test)..' FAILED!: '..failure.description..'\n' 
		i = i + 1
	end
	
	local end_time = os.clock()
	
	if i == 0 then
		results = results..'\nAll unit tests SUCCEEDED!\n'
	else
		results = results..'\n'..tostring(i)..' unit tests FAILED!!!!!!!!\n'
	end
	
	results = results..(tostring(table.countslow(unitTests))..' run in '..tostring(end_time - start_time)..' seconds\n')
	results = results..'\n************* Finish Lua Unit Testing ************\n'
	results = results..'**************************************************\n'
	return i, results
end

----------------------------------------------------------------------
-- PRIVATE
-- all the unit test descriptions and functions
unitTests = {}
-- the list of failed tests after a unit test run
failedTests = {}
