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
a unique name isn't madatory, but 
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
	local start_time = os.clock()
	for _, tester in pairs(unitTests) do
		tester();
	end
	local end_time = os.clock()
	-- \todo nil the loaded status of the unittesting framework
	-- \todo run a full garbage collect
	local num_failures, results = reportResults(end_time - start_time)
	unitTests = {}
	failedTests = {}	
	print(results)
	collectgarbage'collect'
	if package then
		package.loaded['UnitTestingFramework'] = nil
	end
	_G.lastUnitTestRunSucceeded = num_failures == 0
	return num_failures, results
end

----------------------------------------------------------------------
-- PRIVATE
-- implementation

----------------------------------------------------------------------
createTestFunction = function(name, f)
	local tester = function()
		-- local success, error_message = pcall(f)
		local success, error_message = xpcall(f, errorHandler)
		if not success then
			reportFailure(name, error_message)
		end
	end
	
	table.insert(unitTests, tester)
end

----------------------------------------------------------------------
errorHandler = function(error_object)
	return debug.traceback(error_object,4)
end
----------------------------------------------------------------------
reportFailure = function(name, error_message)
	table.insert(failedTests, {test = tostring(name), description = error_message})
end

----------------------------------------------------------------------
-- runs all the unit test functions
reportResults = function(duration)
	local i = 0
	local results = '\n**************************************************'
	results = results..'\n************* Begin Lua Unit Testing *************\n'
	for _, failure in pairs(failedTests) do
		results = results..tostring(failure.test)..' FAILED!: '..failure.description..'\n' 
		i = i + 1
	end
	
	if i == 0 then
		results = results..'\nAll unit tests SUCCEEDED!\n'
	else
		results = results..'\n'..tostring(i)..' unit tests FAILED!!!!!!!!\n'
	end
	
	results = results..(tostring(table.countslow(unitTests))..' run in '..duration..' seconds\n')
	results = results..'\n************* Finish Lua Unit Testing ************\n'
	results = results..'**************************************************\n'
	return i, results
end

----------------------------------------------------------------------
-- PRIVATE
----------------------------------------------------------------------
--- the list of failed tests after a unit test run
failedTests = {}
--- the result of the last run of all tests
lastRunSucceeded = true
--- all the unit test descriptions and functions
unitTests = {}
