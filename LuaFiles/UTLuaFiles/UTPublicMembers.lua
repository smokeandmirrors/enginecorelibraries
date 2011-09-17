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

UT.test('all',
	function()
	--[[
	REGISTER_LUA_LIBRARY((&lua), TC);
	REGISTER_LUA_LIBRARY((&lua), TCChild);
	REGISTER_LUA_LIBRARY((&lua), TCGrandChild);
	REGISTER_LUA_LIBRARY((&lua), ProxyTC);
	REGISTER_LUA_LIBRARY((&lua), ProxyTCChild);
	REGISTER_LUA_LIBRARY((&lua), ProxyTCGrandChild);
	REGISTER_LUA_LIBRARY((&lua), TCLE);
	REGISTER_LUA_LIBRARY((&lua), TCLEChild);
	REGISTER_LUA_LIBRARY((&lua), TCLEGrandChild);
	REGISTER_LUA_LIBRARY((&lua), ProxyTCLE);
	REGISTER_LUA_LIBRARY((&lua), ProxyTCLEChild);
	REGISTER_LUA_LIBRARY((&lua), ProxyTCLEGrandChild);
	--]]
	
	UT.testClassProperties('TC')
	UT.testClassProperties('TCChild', 'TC')
	UT.testClassProperties('TCGrandChild', 'TCChild')
	UT.testClassProperties('ProxyTC')
	UT.testClassProperties('ProxyTCChild', 'ProxyTC')
	UT.testClassProperties('ProxyTCGrandChild', 'ProxyTCChild')
	UT.testClassProperties('TCLE')
	UT.testClassProperties('TCLEChild', 'TCLE')
	UT.testClassProperties('TCLEGrandChild', 'TCLEChild')
	UT.testClassProperties('ProxyTCLE')
	UT.testClassProperties('ProxyTCLEChild', 'ProxyTCLE')
	UT.testClassProperties('ProxyTCLEGrandChild', 'ProxyTCLEChild')
	end
)