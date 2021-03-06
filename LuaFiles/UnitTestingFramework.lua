_ENV = deprecatedNaughtyModule('UnitTestingFramework', package.seeall)
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

vectorTolerance = 0.0001

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
	tolerance = tolerance or vectorTolerance
	if rhs ~= 0 then
		assert(math.abs((lhs - rhs) / rhs) <= tolerance, 
			'checkEqual failed, '..tostring(lhs)..
			' is not equal to '..tostring(rhs)..
			' within '..tostring(tolerance)..': '..(fail_message ~= nil and tostring(fail_message) or ''))
	else
		assert(math.abs(lhs - rhs) <= tolerance, 
			'checkEqual failed, '..tostring(lhs)..
			' is not equal to '..tostring(rhs)..
			' within '..tostring(tolerance)..': '..(fail_message ~= nil and tostring(fail_message) or ''))
	end
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
checkVector = function(v, x, y, z, tolerance)
	tolerance = tolerance or vectorTolerance
	checkNearEqual(v.x, x, tolerance, 'x component not equal!')
	checkNearEqual(v.y, y, tolerance, 'y component not equal!')
	checkNearEqual(v.z, z, tolerance, 'z component not equal!')
end

----------------------------------------------------------------------
-- runs all the unit test functions
-- \return the number of failures
runAll = function(print_out)
	local start_time = os.clock()
	for test, tester in pairs(unitTests) do
		tester.func();
	end
	local end_time = os.clock()
	local num_failures, results = getResultsReport(end_time - start_time)
	unitTests = {}
	failedTests = {}	
	collectgarbage'collect'
	if package then
		package.loaded['UnitTestingFramework'] = nil
	end
	_G.lastUnitTestNumFailures = num_failures
	_G.lastUnitTestReport = results
	if print_out == nil or print_out then
		print(_G.lastUnitTestReport)
	end
	return num_failures == 0
end

----------------------------------------------------------------------
-- test writing functions

----------------------------------------------------------------------
-- creates a test out of the passed in function
-- the result is returned for manual testing, and will
-- get executed by runAll()
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

testAll = function(print_out)
	runAll(print_out)
end

runModule = function(name, print_out)
	require(name)
	runAll(print_out)
end

----------------------------------------------------------------------
-- PRIVATE
-- implementation

----------------------------------------------------------------------
createTestFunction = function(name, f)
	local tester = {
		name = name,
		func = function()
			-- local success, error_message = pcall(f)
			local success, error_message = xpcall(f, errorHandler)
			if not success then
				reportFailure(name, error_message)
			end
		end
	}
	
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
-- module specific testing functions
function testClassProperties(class_name, super_name, interfaces)
	local OOP = require'ObjectOrientedParadigm'
	
	if type(class_name) == 'string' then
		if not _G.getClass(class_name) then
			pcall(function() require(class_name) end)
			declareClass(_G[class_name])
			checkT(_G.getClass(class_name), 'table')
		end
	end
			
	local b = new(class_name)
	testInstanceProperties(b, class_name, super_name, interfaces)
end

function testRefreshClassAbilities(class_declaration, class_name, super_name, interfaces)
	if DEBUG_INTERPRETATION then
		local OOP = require'ObjectOrientedParadigm'
		testClassProperties(class_name, super_name, interfaces)
		local instance1 = new(class_name)
		class_declaration.unitTestingFunction1 = function(self)
			if not self.unitTestingValue1 then
				self.unitTestingValue1 = 'assignedvalue'
			end	
			return 7
		end
		declareClass(class_declaration)
		testInstanceProperties(instance1, class_name, super_name, interfaces)
		testClassProperties(class_name, super_name, interfaces)
		checkT(instance1.unitTestingFunction1, 'function')
		checkEqual(instance1:unitTestingFunction1(), 7)
		checkT(instance1.unitTestingValue1, 'string')
		checkEqual(instance1.unitTestingValue1, 'assignedvalue')		
	end
end

function testInstanceProperties(b, class_name, super_name, interfaces)
	local OOP = require'ObjectOrientedParadigm'
	
	checkEqual(b.ACTS_AS, _G.ACTS_AS)
	checkEqual(b.class, _G.getClass(class_name))
	checkEqual(b.className, class_name)
	checkEqual(b.getClass, OOP.getClass)
	checkEqual(b:getClass(), _G.getClass(class_name))
	checkEqual(b.getClassName, OOP.getClassName)
	checkEqual(b:getClassName(), class_name)
	checkT(b.getName, 'function')
	checkT(b:getName(), 'string')
	checkT(b.getSuperclass, 'function')
	checkEqual(b.getSuperclass, OOP.getSuperclass)
	checkEqual(b.IS_A, _G.IS_A)
	if class_name == 'Derived' then
		local tupos = type(b)
		check(tupos == 'table' or (tupos == 'userdata' and getmetatable(b) and getmetatable(b).__index)) 
		check(b.getClass ~= nil)
		check(OOP.classes_PRIVATE[class_name] ~= nil)
		check(OOP.introspect_PRIVATE(b:getClass(), OOP.classes_PRIVATE[class_name]))
	end
	check(b:IS_A(class_name))
	checkEqual(b.IS_EXACTLY_A, _G.IS_EXACTLY_A)
	check(b:IS_EXACTLY_A(class_name))
	checkT(getmetatable(b).__tostring, 'function')
	checkT(getmetatable(b).__tostring(b), 'string')
	checkT(b.toString, 'function')
	checkT(b:toString(), 'string')
	check(getmetatable(b) ~= nil and type(getmetatable(b).__concat) == 'function')
	local no_error = b..new(class_name)..'no error'
	local error_no = 'error on'..new(class_name)..b

	if super_name == nil then
		checkT(b.super, 'nil')
		checkT(b:getSuperclass(), 'nil')
	else
		local instance = b
		check(not b:IS_EXACTLY_A(super_name))
		checkEqual(b:getSuperclass(), getClass(super_name))
		checkEqual(b.super, getClass(super_name))
		check(b:IS_A(super_name))
	end
	
	if type(interfaces) == 'table' then
		for _, interface in pairs(interfaces) do
			check(b:ACTS_AS(interface))
		end
	end
end


----------------------------------------------------------------------
-- PRIVATE
----------------------------------------------------------------------
--- the list of failed tests after a unit test run
failedTests = {}
--- all the unit test descriptions and functions
unitTests = {}
