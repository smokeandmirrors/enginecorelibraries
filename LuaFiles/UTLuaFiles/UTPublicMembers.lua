module(..., package.seeall)
----------------------------------------------------------------------
-- UTPublicMembers.lua
--
-- This file defines lua unit tests for exposure of public member 
-- variables from C++ to Lua
--
--	\author Smoke and Mirrors Development
--	\email smokeandmirrorsdevelopment@gmail.com
--	\copyright 2010
local OOP = require'ObjectOrientedParadigm'
local UT = require'UnitTestingFramework'
require'Utilities'

function class(object, prefix, suffix) 
	if not object then
		object = new((prefix or '')..'TC'..(suffix or ''))
	end
	
	UT.checkEqual(object.one, 1)
	object.one = 2
	UT.checkEqual(object.one, 2)
	if prefix ~= 'Proxy' then
		UT.checkError(function() object.one = {} end)
	else
		object.onexxx = { sweet = 7 }
		UT.checkT(object.onexxx, 'table')
		UT.checkEqual(object.onexxx.sweet, 7)
	end
	
	UT.checkEqual(object.two, true)
	object.two = false
	UT.checkEqual(object.two, false)
	if prefix ~= 'Proxy' then
		UT.checkError(function() object.two = {} end)
	end
	
	UT.checkEqual(object.three, 3.5)
	object.three = 4.7
	UT.checkNearEqual(object.three, 4.7)
	if prefix ~= 'Proxy' then
		UT.checkError(function() object.three = {} end)
	end	
	
	UT.checkT(object.method, 'function')
	UT.checkEqual(object:method(), 17)
end

function childClass(object, prefix, suffix) 
	if not object then
		object = new((prefix or '')..'TC'..(suffix or '')..'Child')
	end
	
	UT.checkEqual(object.four, nil)
	local four = new((prefix or '')..'TC'..(suffix or ''))
	object.four = four
	UT.checkEqual(object.four, four)
	if prefix ~= 'Proxy' then
		UT.checkError(function() object.four = {} end)
	else
		object.fourxxx = { sweet = 7 }
		UT.checkT(object.fourxxx, 'table')
		UT.checkEqual(object.fourxxx.sweet, 7)
	end
	
	UT.checkEqual(object.five, -5)
	object.five = -7
	UT.checkEqual(object.five, -7)
	if prefix ~= 'Proxy' then
		UT.checkError(function() object.five = {} end)
	end
	
	UT.checkT(object.childMethod, 'function')
	UT.checkEqual(object:childMethod(), 1717)	
		
	class(object, prefix, suffix)
end

function grandChildClass(object, prefix, suffix) 
	if not object then
		object = new((prefix or '')..'TC'..(suffix or '')..'GrandChild')
	end
	
	UT.checkEqual(object.six, nil)
	local six = new((prefix or '')..'TC'..(suffix or '')..'Child')
	object.six = six
	UT.checkEqual(object.six, six)
	if prefix ~= 'Proxy' then
		UT.checkError(function() object.six = {} end)
	else
		object.sixxxx = { sweet = 7 }
		UT.checkT(object.sixxxx, 'table')
		UT.checkEqual(object.sixxxx.sweet, 7)
	end
		
	UT.checkEqual(object.seven, 7)
	object.seven = 5
	UT.checkEqual(object.seven, 5)
	if prefix ~= 'Proxy' then
		UT.checkError(function() object.seven = {} end)
	end
		
	UT.checkT(object.grandChildMethod, 'function')
	UT.checkEqual(object:grandChildMethod(), 171717)	
		
	childClass(object, prefix, suffix)
end

function testAll(prefix, suffix)
	class(nil, prefix, suffix)
	childClass(nil, prefix, suffix)
	grandChildClass(nil, prefix, suffix)
end

UT.test('all',
	function()
		UT.testClassProperties('TC')
		UT.testClassProperties('TCChild', 'TC')
		UT.testClassProperties('TCGrandChild', 'TCChild')
		UT.testClassProperties('TCLE')
		UT.testClassProperties('TCLEChild', 'TCLE')
		UT.testClassProperties('TCLEGrandChild', 'TCLEChild')
		
		UT.testClassProperties('ProxyTC')
		UT.testClassProperties('ProxyTCChild', 'ProxyTC')
		UT.testClassProperties('ProxyTCGrandChild', 'ProxyTCChild')
		UT.testClassProperties('ProxyTCLE')
		UT.testClassProperties('ProxyTCLEChild', 'ProxyTCLE')
		UT.testClassProperties('ProxyTCLEGrandChild', 'ProxyTCLEChild')
		
		testAll(nil, nil) -- 'TC'
		testAll(nil, 'LE') -- 'TCLE'
		testAll('Proxy', nil) -- 'ProxyTC'
		testAll('Proxy', 'LE') -- 'ProxyTCLE'
	end
)