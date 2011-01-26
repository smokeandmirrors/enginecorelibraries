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
available functions:
check(value, fail_message)
checkError(test_function, fail_message, ...)
checkEqual(lhs, rhs, fail_message)
checkNearEqual(lhs, rhs, tolerance, fail_message)
checkT(value, tupos)
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
checkEqual = function(lhs, rhs, fail_message)
	assert(lhs == rhs, 'checkEqual failed, '..tostring(lhs)..
		' is not equal to '..tostring(rhs)..': '..(fail_message ~= nil and tostring(fail_message) or ''))
	
end

----------------------------------------------------------------------
-- checks that the given function called with the passed in 
-- arguments will throw an error 
checkError = function(test_function, fail_message, ...)
	local result, output = pcall(test_function, ...)
	assert(not result, 'the function did not produce an error as expected: '..(fail_message ~= nil and tostring(fail_message) or ''))
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
-- checks that the values is of the appropriate type
checkT = function(value, tupos)
	assert(tupos == 'function'
		or tupos == 'userdata'
		or tupos == 'number'
		or tupos == 'boolean'
		or tupos == 'string'
		or tupos == 'nil'
		or tupos == 'thread'
		or tupos == 'table', 
		'checkT called with invalid type parameter: '..tupos)
	assert(tupos == type(value), 
		'checkT failed, expected type: '..tupos..' actual type: '..type(value))
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
	local num_failures, results = getResultsReport(end_time - start_time)
	unitTests = {}
	failedTests = {}	
	collectgarbage'collect'
	
	if package then
		package.loaded['UnitTestingFramework'] = nil
	end
	
	_G.lastUnitTestNumFailures = num_failures
	_G.lastUnitTestReport = results
	
	return num_failures == 0
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

testSuite = function(args)
	local suite_name = args.name
	if type(suite_name) ~= 'string' then
		suite_name = 'poorly named suite'	
	end
	for func_name, test_func in pairs(args) do
		if test_func ~= suite_name then
			createTestFunction(suite_name..'.'..tostring(func_name), test_func)
		end
	end
end

_G.testAll = function(print_out)
	-- require all the unit test modules here
	rerequire'UnitTesting'
	rerequire'OOPUnitTesting'
	runAll()
	if print_out then
		print(_G.lastUnitTestReport)
	end
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
-- runs all the unit test functions
getResultsReport = function(duration)
	local i = 0
	local results = '\n**************************************************'
	results = results..'\n************* Begin Lua Unit Testing *************\n'
	for _, failure in pairs(failedTests) do
		local desc = failure.description
		if desc == nil then
			desc = 'no description'
		end
		results = results..'function: '..tostring(failure.test)..' FAILED!: '..desc..'\n' 
		i = i + 1
	end
	
	if i == 0 then
		results = results..'\nAll unit tests SUCCEEDED!\n'
	else
		results = results..'\n'..tostring(i)..' unit tests FAILED!!!!!!!!\n'
	end
	
	results = results..(tostring(table.countslow(unitTests))..' run in '..sprintf('%4.2f', duration)..' seconds\n')
	results = results..'\n************* Finish Lua Unit Testing ************\n'
	results = results..'**************************************************\n'
	return i, results
end

----------------------------------------------------------------------
reportFailure = function(name, error_message)
	table.insert(failedTests, {test = tostring(name), description = error_message})
end

----------------------------------------------------------------------
-- PRIVATE
----------------------------------------------------------------------
--- the list of failed tests after a unit test run
failedTests = {}
--- all the unit test descriptions and functions
unitTests = {}
