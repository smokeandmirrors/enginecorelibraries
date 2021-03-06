----------------------------------------------------------------------
-- ObjectOrientedParadigm.lua
--
-- This file defines a module which provides Object-Oriented 
-- characteristics useful in larger scale lua programs,
-- especially when used as an extension for a native classes.
-- 
--	\author Smoke and Mirrors Development
--	\email smokeandmirrorsdevelopment@gmail.com
--	\copyright 2010

-- begin module declaration
local modname = ...
local OOP = {}
_G[modname] = OOP
package.loaded[modname] = OOP
	
-- conditional halt functionality in error reporting
local assert = assert
local collectgarbage = collectgarbage
-- halt functionality in error reporting
local DEBUG_INTERPRETATION = DEBUG_INTERPRETATION
local error = error
local getmetatable = getmetatable
local next = next
local pairs = pairs
-- non-error message reporting
local print = print -- declareclasserror...runtimeerror, etc.
local rawequal = rawequal
local rawget = rawget
local rawset = rawset
local require = require
local setmetatable = setmetatable
local string = string
local table = table
local type = type
local Utilities = require'Utilities'
local _G = _G

_ENV = OOP
-- end module declaration


----------------------------------------------------------------------
----------------------------------------------------------------------
-- 'public'
----------------------------------------------------------------------
----------------------------------------------------------------------

---------------------------------------------------------------------
-- change the following values to change compilation, error handling,
-- error reporting, and informative messages



----------------------------------------------------------------------
-- Checks for implemetation of a specified interface on an instance
-- works only for declareClass() defined objects
-- @param instance the runtime object
-- @param interface the name of the interface the object must PLAY-THE-ROLE-OF 
function _G.ACTS_AS(instance, interface_name)
	return instance.getClass 
		and interfaces_PRIVATE[interface_name] 
		and implements_PRIVATE(instance:getClass(), interface_name)
end

----------------------------------------------------------------------
-- Checks for class type match on an object of a class declared with
-- this system, including iheritance
-- @param instance the runtime object
-- @param class_name the class type in question
function _G.IS_A(instance, class_name)
	local tupos = type(instance)
	return (tupos == 'table' or (tupos == 'userdata' and getmetatable(instance) and getmetatable(instance).__index)) 
		and instance.getClass 
		and classes_PRIVATE[class_name]
		and introspect_PRIVATE(instance:getClass(), classes_PRIVATE[class_name])
end

----------------------------------------------------------------------
-- Checks for class type match on an object of a class declared with
-- this system, returns true if most derived type of instance is class_name
-- @param instance the runtime object
-- @param class_name the class type in question
function _G.IS_EXACTLY_A(instance, class_name)
	local tupos = type(instance)
	return (tupos == 'table' or (tupos == 'userdata' and getmetatable(instance) and getmetatable(instance).__index)) 
		and instance.getClass
		and classes_PRIVATE[class_name]
		and rawequal(instance:getClass(), classes_PRIVATE[class_name])
end

----------------------------------------------------------------------
-- returns an iterator which progresses over all non-metatable classes
-- registered in the system.
function _G.classes()
	local k,v
	local iterator = function()
		k,v = next(classes_PRIVATE,k)
		while k and ('_mt' == string.sub(k, -3)) do
			k,v = next(classes_PRIVATE,k)
		end
		return k,v
	end
	return iterator, nil, nil
end

----------------------------------------------------------------------
-- Define an abstract class - cannot be instantiated, only extended!
-- @param definition a table with entries as follows:
-- name = (string) -- the class name
-- abstract = (table of functions) -- list of functions that must be found in concrete class that extend this one
function _G.declareAbstractClass(definition)
	declareAbstractClass_PRIVATE(definition)
	collectgarbage'collect'
end

----------------------------------------------------------------------
-- Define a class
-- @param definition a table with entries as follows:
-- name = (string) -- the class name
-- extends = (string) -- the base class name (optional)
-- implements = (table of interface names) -- the interfaces that this class implements
function _G.declareClass(definition)
	declareClass_PRIVATE(definition)
	collectgarbage'collect'
end

----------------------------------------------------------------------
-- Define an interface - cannot be instantiated, only implemented!
-- @param definition.name, otherwise functions the interface name
function _G.declareInterface(definition)
	declareInterface_PRIVATE(definition)
	collectgarbage'collect'
end

----------------------------------------------------------------------
-- nil out an object for garbage collection, and call any destruct methods
function _G.delete(object)
	destructHierarchy_PRIVATE(object)
end

----------------------------------------------------------------------
-- returns an iterator which progresses over all the functions available
-- in an instance of a class
function _G.functions(instance)
	local mt = getmetatable(instance)
	local index_table = mt.__index
	local k,v
	local iterator = function()
		k,v = next(index_table, k)
		while k and (type(v) ~= 'function') do
			k,v = next(index_table, k)
		end
		return k,v
	end
	return iterator, nil, nil
end

----------------------------------------------------------------------
-- Get the base class definition
function _G.getClass(class_name)
	return classes_PRIVATE[class_name]
end

----------------------------------------------------------------------
function _G.getClassFromObject(object, tupos)
	tupos = tupos or type(object)
	return ((tupos == 'table' or (tupos == 'userdata' and getmetatable(object))) and object.getClass)
		and object:getClass()
end

----------------------------------------------------------------------
-- Create a new instance of a class
if DEBUG_INTERPRETATION then
function _G.new(class_name, ...)
	local constructor = constructors_PRIVATE[class_name]
	assert(type(constructor) == 'function', 'No such class: '..class_name..' !')
	return constructor(...)
end
else
function _G.new(class_name, ...)
	return constructors_PRIVATE[class_name](...)
end
end

----------------------------------------------------------------------
-- this function makes it really easy to write to concatenation 
-- functions
function toStringConcat(lhs, rhs)
	return type(lhs) == 'string' and lhs..rhs:toString()
		or type(rhs) == 'string' and lhs:toString()..rhs
		or lhs:toString()..rhs:toString()
end

----------------------------------------------------------------------
-- validateObject an instance of specified classes/interfaces, etc...
function validateObject(instance, class_name, interface_names, nil_message, no_IS_A_message, class_message, interface_message)
	local good_instance = true
	local tupos = type(instance)
	if not (tupos == 'table' or (tupos == 'userdata' and getmetatable(instance))) then
		print(nil_message or 'The instance is the wrong type: '..type(instance))
		good_instance = false
	end
	if instance.IS_A == nil then
		print(no_IS_A_message or 'The instance isn\'t a valid class')
		good_instance = false
	end
	if class_name then
		if not instance:IS_A(class_name) then
			print(class_message or 'The instance is not or derived from: '..class_name)
			good_instance = false
		end
	end
	if interface_names then
		for each, interface in pairs(interface_names) do
			if not instance:ACTS_AS(interface) then
				print(interface_message or 'The instance does not implement the: '..interface..' interface')
				good_instance = false
			end
		end
	end
	local name = (type(instance) == 'table' and instance.name) and instance.name or 'no name'
	assert(good_instance, 'Invalid Instance: '..name..'.  See lua log.')
end

----------------------------------------------------------------------
----------------------------------------------------------------------
-- A set of functions common to all classes declared in this system. 
----------------------------------------------------------------------
----------------------------------------------------------------------

----------------------------------------------------------------------
-- @return the class definition
getClass = function(instance) 
	return instance.class
end

----------------------------------------------------------------------
-- @return the name of the class definition
getClassName = function(instance) 
	return instance.className
end

----------------------------------------------------------------------
-- @return get the name of the instance 
if DEBUG_INTERPRETATION then
getName = function(instance)
	local tupos = type(instance.name)
	if tupos == 'number' and instance:__isnewindexable() then 
		instance.name = instance:getClassName()..' '..instance.name
		instance.getName = getName2
	elseif tupos == 'nil' then
		return instance:getClassName()
	end	
	return instance.name
end
getName2 = function(instance)
	return instance.name
end
else
getName = function(instance)
	return instance:getClassName()
end
end --- DEBUG_INTERPRETATION

----------------------------------------------------------------------
-- @return the superclass definition
getSuperclass = function(instance) 
	return instance.super
end

----------------------------------------------------------------------
-- @return a string representation of this object.  Every class should 
-- have a version of this function
if DEBUG_INTERPRETATION then
toString = function(instance)
	return instance:getName()
end
else
toString = function(instance)
	return instance:getClassName()
end
end --- DEBUG_INTERPRETATION 

----------------------------------------------------------------------
----------------------------------------------------------------------
-- 'private'
----------------------------------------------------------------------
----------------------------------------------------------------------

-- hold the necessary composition of classes
--[[ these should all be able to be local --]]
classes_PRIVATE 		= {}
constructors_PRIVATE	= {}
destructors_PRIVATE		= {}
initializers_PRIVATE	= {}
interfaces_PRIVATE 		= {}
metatables_PRIVATE 		= {}
-- helper table
metamethods = {
	__add 			= true,
	__call 			= true,
	__concat 		= true,
	__div 			= true,
	__eq 			= true,
	__gc 			= true,
	__indexSupport 	= true,
	__le 			= true,
	__len 			= true,
	__lt 			= true,
	__metatable 	= true,
	__mod 			= true,
	__mode 			= true,
	__mul 			= true,
	__newindex 		= true,
	__newindexSupport = true,
	__pow 			= true,
	__sub 			= true,
	__tostring 		= true,
	__unm 			= true,
-- @note __index gets set automatically to base class
-- @note the use of __metatable will interfere with the ability
-- to refresh a class definition on instances at runtime
}

reservedWords = {
	'ACTS_AS',
	'class',
	'className',
	'getClass',
	'getClassName',
	'getSuperclass',
	'IS_A',
	'IS_EXACTLY_A',
	'super'
}
-- used to keep track if an inner/private class is being created
declarationInProgress		= false
-- hold on to an error message string in this module
errorMsg					= '' 
-- track missing interfaces
missingInterfaces			= {}
-- track missing functions
missingFunctions			= {}

if DEBUG_INTERPRETATION then
--	These values allow one to refresh instantiated 
--	objects	with new function tables if the class gets redefined 
classesNeedRefresh		= false
refreshInstances_PRIVATE	= setmetatable({}, {__mode = 'v'})
end -- if DEBUG_INTERPRETATION

----------------------------------------------------------------------
-- this replaces having a base class of 'object', saving an index 
-- lookup for every class read of these values
function addCommonClassProperties_PRIVATE(class, super, class_name)
	class.ACTS_AS		= _G.ACTS_AS
	class.class			= class
	class.className		= class_name
	class.getClass		= getClass
	class.getClassName	= getClassName
	class.getName		= class.getName or getName
	class.getSuperclass = getSuperclass
	class.IS_A			= _G.IS_A
	class.IS_EXACTLY_A	= _G.IS_EXACTLY_A
	class.__isnewindexable = class.__isnewindexable or _G.truef
	class.toString		= class.__tostring or class.toString or toString
	metatables_PRIVATE[class_name].__concat = metatables_PRIVATE[class_name].__concat or toStringConcat
	metatables_PRIVATE[class_name].__tostring = metatables_PRIVATE[class_name].__tostring or class.toString
	assert(type(class.toString) == 'function')
	class.super = super
	return true
end

if DEBUG_INTERPRETATION then
----------------------------------------------------------------------
function addInstanceToRefresh_PRIVATE(instance)
	table.insert(refreshInstances_PRIVATE, instance)
	return instance
end
end --- DEBUG_INTERPRETATION
 
----------------------------------------------------------------------
-- maintain a running compile problem message
function addToErrorMsg_PRIVATE(moreMessage) 
	errorMsg = (errorMsg .. moreMessage .. '\n')
end

----------------------------------------------------------------------
-- assign the metamethods to the metatable for this class
function assignMetaMethods_PRIVATE(name, def, super_class_name)
	local metatable = metatables_PRIVATE[name]
	for key, method in pairs(def) do
		if metamethods[key] then
			metatable[key] = method
		end
	end
	local super_mt = super_class_name and metatables_PRIVATE[super_class_name]
	if super_mt then
		for key, method in pairs(super_mt) do
			if not metatable[key] then
				metatable[key] = method
			end
		end
	end
end

----------------------------------------------------------------------
-- this verifies a table as definition and gives it the necessary Lua 
-- features to allow it to operate as a class
-- @param definition definition table in the same format as 
-- declareClass() and declareClass_PRIVATE()
if DEBUG_INTERPRETATION then
function beginClassDeclaration_PRIVATE(definition)
	-- hold failure reporting until the very end so that all problems with the class can be reported.
	local compiled = true
	local implements = definition.implements
	local name = definition.name
	local extends = definition.extends
	-- there should only be functions left in the definition
	local def = {}
	table.copyif(
		definition, 
		def, 
		function(key, value)
			return type(value) == 'function'
		end)
	-- validate the class name
	if findClassName_PRIVATE(name) then
		classesNeedRefresh = true
	end
	-- validate the baseclass name
	local base_class_name = findBaseClassName_PRIVATE(extends)
	compiled = (base_class_name ~= nil or extends == nil) and compiled
	if not compiled then
		local extendstring = extends and extends or ''
		addToErrorMsg_PRIVATE('super class '..extendstring..', extended by '..name..', does not exist!')
	end
	-- if we aren't good so far, future messages will be irrelevant
	assert(compiled, errorMsg)
	-- verify no use of ObjectOrientedParadigm keywords
	compiled = verifyKeywords_PRIVATE(def, name)
	-- assign basic properties
	local base_class
	if base_class_name then
		base_class = classes_PRIVATE[base_class_name]
	end
	local base_class = base_class_name and classes_PRIVATE[base_class_name]
	local class = createClassProperties_PRIVATE(name, base_class, def.__index)
	assignMetaMethods_PRIVATE(name, def, base_class_name)
	-- verify the interfaces_PRIVATE
	local interfacesGood = true
	local implemented, interfacesGood = findInterfaces_PRIVATE(implements)
	compiled = interfacesGood and compiled
	class.implements = implemented	
	-- add the defined functions in the file to the class declaration
	compiled = verifyFunctionTable_PRIVATE(class, def, base_class, name..'.', ' is not a function.  Create this object in the constructor() function.') and compiled
	-- add methods common to all classes in lieu of an Object base class
	compiled = addCommonClassProperties_PRIVATE(class, base_class, name) and compiled
	return class, compiled
end
else
function beginClassDeclaration_PRIVATE(definition)
	-- hold failure reporting until the very end so that all problems with the class can be reported.
	local compiled = true
	local implements = definition.implements
	local name = definition.name
	local extends = definition.extends
	-- there should only be functions left in the definition
	local def = {}
	table.copyif(
		definition, 
		def, 
		function(key, value)
			return type(value) == 'function'
		end)
	-- validate the class name
	if findClassName_PRIVATE(name) then
		-- warn(false, 'Class '..name..' already exists!')
		error('Class '..name..' already exists!')
	end
	-- validate the baseclass name
	local base_class_name = findBaseClassName_PRIVATE(extends)
	compiled = (base_class_name ~= nil or extends == nil) and compiled
	if not compiled then
		local extendstring = extends and extends or ''
		addToErrorMsg_PRIVATE('super class '..extendstring..', extended by '..name..', does not exist!')
	end
	-- if we aren't good so far, future messages will be irrelevant
	assert(compiled, errorMsg)
	-- verify no use of ObjectOrientedParadigm keywords
	compiled = verifyKeywords_PRIVATE(def, name)
	-- assign basic properties
	local base_class = base_class_name and classes_PRIVATE[base_class_name]
	local class = createClassProperties_PRIVATE(name, base_class, def.__index)
	assignMetaMethods_PRIVATE(name, def, base_class_name)
	-- verify the interfaces_PRIVATE
	local interfaces_good = true
	local implemented, interfaces_good = findInterfaces_PRIVATE(implements)
	compiled = interfaces_good and compiled
	class.implements = implemented	
	-- add the defined functions in the file to the class declaration
	compiled = verifyFunctionTable_PRIVATE(class, def, base_class, name..'.', ' is not a function.  Create this object in the constructor() function.') and compiled
	-- add methods common to all classes in lieu of an Object base class
	compiled = addCommonClassProperties_PRIVATE(class, base_class, name) and compiled
	return class, compiled
end
end -- if DEBUG_INTERPRETATION

function constructTable()
	return {}
end

----------------------------------------------------------------------
-- assign the basics, implement inheritance
if DEBUG_INTERPRETATION then
function createClassProperties_PRIVATE(name, superclass, custom__index)
	-- define the class
	local class = {className = name, nextInstanceId = 0}
	-- implement inheritance from super classes
	setmetatable(class, {__index = superclass}) 
	-- implement inheritance for instantiated objects
		metatables_PRIVATE[name] = {__index = custom__index or class} 
	-- return the class definition
	return class
end
else
function createClassProperties_PRIVATE(name, superclass, custom__index)
	-- define the class
	-- implement inheritance from super classes
	local class = setmetatable({className = name}, {__index = superclass}) 
	-- implement inheritance for instantiated objects
	metatables_PRIVATE[name] = {__index = custom__index or class} 
	-- return the class definition
	return class
end
end -- if DEBUG_INTERPRETATION

----------------------------------------------------------------------
-- create the creation function for the object
--
-- The C library registers first.  Then, the lua class gets (required and 
-- then both are) declared, adding functionality to the C library
if DEBUG_INTERPRETATION then
function createConstructor_PRIVATE(class, metatable)
	local allocator
	local setMetatable
	if type(class.__new) == 'function' then
		allocator = class.__new
	else
		allocator = constructTable
	end
	
	if type(class.__setmetatable) == 'function' then
		setMetatable = class.__setmetatable
	else
		setMetatable = setmetatable
	end
	-- an initializer for push() calls from native
	local initializer = function(instance, ...)
		class.nextInstanceId = class.nextInstanceId + 1
		addInstanceToRefresh_PRIVATE(constructHierarchy_PRIVATE(class, setMetatable(instance, metatable), ...))
		if (not instance.name) 
		and class.__isnewindexable() 
		then
			instance.name = class.nextInstanceId
		end
		return instance
	end
	-- a full constructor for new() calls from Lua
	local constructor = function(...)
		return initializer(allocator(...), ...)
	end			
	return constructor, initializer
end	
else
function createConstructor_PRIVATE(class, metatable)
	assert(class and metatable)
	local allocator
	local setMetatable
	
	if type(class.__new) == 'function' then
		allocator = class.__new
	else
		allocator = constructTable
	end
	
	if type(class.__setmetatable) == 'function' then
		setMetatable = class.__setmetatable
	else
		setMetatable = setmetatable
	end
	-- an initializer for push() calls from native
	local initializer = function(instance, ...)
		return constructHierarchy_PRIVATE(class, setMetatable(instance, metatable), ...)
	end
	-- a full constructor for new() calls from Lua
	local constructor = function(...)
		return initializer(allocator(...), ...)
	end			
	return constructor, initializer
end 	
end -- if DEBUG_INTERPRETATION

----------------------------------------------------------------------
-- calls initialize on the most base class first, then sequentially on
-- the derived classes_PRIVATE
function constructHierarchy_PRIVATE(class, instance, ...) 
	local super = class.super
	if super then
		constructHierarchy_PRIVATE(super, instance, ...)
	end
	local construct = rawget(class, 'construct')
	if construct then
		construct(instance, ...)
	end
	return instance
end

----------------------------------------------------------------------
function declareAbstractClass_PRIVATE(definition)
	definition.protected = nil -- can't be instantiated by the package or anything else
	local name = definition.name or 'unnamed abstract class'
	resetErrorMessage_PRIVATE('\nERROR:\nAbstract Class declaration for '..name..' is incorrect, see lua output or log.\n')
	local abstractFunctions = definition.abstract
	definition.abstract = nil
	local abstract_class, compiled = beginClassDeclaration_PRIVATE(definition)
	-- make the class abstract so it can't be directly instantiated
	abstract_class.abstract = true
	abstract_class.abstractFunctions = {}
	compiled = verifyFunctionTable_PRIVATE(abstract_class.abstractFunctions, abstractFunctions, definition, base_class, abstract_class:getClassName()..'.', ' is not a function.  Put this object in the Initialize() function.') and compiled
	assert(compiled, errorMsg)
	-- add to the list
	classes_PRIVATE[name] = abstract_class
	constructors_PRIVATE[name] = getAbstractConstructor(name)
	if classesNeedRefresh then
		refreshClasses_PRIVATE(name)
	end
end

----------------------------------------------------------------------
-- create a crashing message for abstract classes
function getAbstractConstructor(name)
	return function()
		assert(false, 'Cannot instantiate abstract class: '..name)
	end
end

----------------------------------------------------------------------
if DEBUG_INTERPRETATION then
function declareClass_PRIVATE(definition)
	local name = definition.name
	assert(type(name) == 'string', 'ERROR:\nClass declaration has no \'name\' field')
	local super_name = definition.extends
	resetErrorMessage_PRIVATE('\nERROR:\nClass declaration for '..name..' is incorrect, see lua output or log.\n')
	local class, compiled = beginClassDeclaration_PRIVATE(definition)
	-- if the class implements all interface methods and abstract methods, allow instantiation
	compiled = verifyAbstractImplementation_PRIVATE(class, class.super) and compiled
	compiled = verifyAllInterfacesImplementation_PRIVATE(class) and compiled
	local constructor
	local initializer
	constructor, initializer = createConstructor_PRIVATE(class, metatables_PRIVATE[name])
	if type(constructor) ~= 'function' then
		addToErrorMsg_PRIVATE("class: "..name.." didn't create a proper constructor")
		compiled = false
	end
	if type(initializer) ~= 'function' then
		addToErrorMsg_PRIVATE("class: "..name.." didn't create a proper initializer")
		compiled = false
	end
	-- if the class is well formed... 
	assert(compiled, errorMsg)
	-- ...add to the list...
	classes_PRIVATE[name] = class
	-- ...create the last function
	constructors_PRIVATE[name] = constructor
	initializers_PRIVATE[name] = initializer
	-- if the class is updated, refresh the instances
	if classesNeedRefresh then
		refreshClasses_PRIVATE(name)
	end
end
else
function declareClass_PRIVATE(definition)
	local public = true
	local name = definition.name or 'unnamed class'
	local super_name = definition.extends
	resetErrorMessage_PRIVATE('\nERROR:\nClass declaration for '..name..' is incorrect, see lua output or log.\n')
	local class, compiled = beginClassDeclaration_PRIVATE(definition)
	-- if the class implements all interface methods and abstract methods, allow instantiation
	compiled = verifyAbstractImplementation_PRIVATE(class, class.super) and compiled
	compiled = verifyAllInterfacesImplementation_PRIVATE(class) and compiled
	local constructor
	local initializer
	constructor, initializer = createConstructor_PRIVATE(class, metatables_PRIVATE[name])
	if type(constructor) ~= 'function' then
		addToErrorMsg_PRIVATE("class: "..name.." didn't create a proper constructor")
		compiled = false
	end
	if type(initializer) ~= 'function' then
		addToErrorMsg_PRIVATE("class: "..name.." didn't create a proper initializer")
		compiled = false
	end
	-- if the class is well formed...
	assert(compiled, errorMsg)
	-- ...add to the list...
	classes_PRIVATE[name] = class
	-- ...create the last function
	constructors_PRIVATE[name] = constructor
	initializers_PRIVATE[name] = initializer
end
end -- if DEBUG_INTERPRETATION

----------------------------------------------------------------------
function declareInterface_PRIVATE(definition)
	local name = definition.name or 'unnamed interface'
	resetErrorMessage_PRIVATE('\nERROR:\nInterface declaration for '..name..' is incorrect, see lua output or log.\n')
	definition.name = nil
	local funcs = definition
	local compiled = true
 	local interface -- for better error messages
	
	if interfaces_PRIVATE[name] then
		print('There is already an interface named: '..name)
	end
	
	interfaces_PRIVATE[name] = {}
	interface = interfaces_PRIVATE[name]
		
	compiled = verifyFunctionTable_PRIVATE(interface, funcs, definition, 'Everything in the interface, '..name..', function list must be a function.  ', ' is not.') and compiled 
	assert(compiled, addToErrorMsg_PRIVATE)
end

----------------------------------------------------------------------
function destructHierarchy_PRIVATE(instance)
	local class = instance:getClass()
	repeat
		local destruct = rawget(class, 'destruct')
		if destruct then
			destruct(instance)
		end
		class = class:getSuperclass()
	until class == nil
	rawNilKeys_PRIVATE(instance)	
end

----------------------------------------------------------------------
-- ensures that a base class exists
-- @param base_class_name the name of the base class
-- @return the baseclass name if it exists or 'Object' if not specified, else nil
function findBaseClassName_PRIVATE(base_class_name)
	if base_class_name and classes_PRIVATE[base_class_name] then
		return base_class_name		
	end
end

----------------------------------------------------------------------
-- checks for the existence of class by name
-- @returns true if it's defined, false if not
function findClassName_PRIVATE(name)
	return classes_PRIVATE[name] ~= nil
end

----------------------------------------------------------------------
-- looks for a specific function in a class, other types won't do!
-- @param funcName the name of the function
-- @param class the runtime class definition 
-- @see declareClass
function findConcreteFunction_PRIVATE(function_name, class)
	return class[function_name] and type(class[function_name]) == 'function'
end

----------------------------------------------------------------------
-- ensures that interfaces_PRIVATE exist 
-- @param table of interface names
-- @param table that will be loaded with actual interfaces_PRIVATE
-- @return true if success else false
function findInterfaces_PRIVATE(interface_names)		
	local success = true
	local interfaces 
	if interface_names then
		if type(interface_names) == 'string' then
			local swap = interface_names
			interface_names = {}
			table.insert(interface_names, swap)
		elseif type(interface_names) ~= 'table' then
			addToErrorMsg_PRIVATE('Implements entry of the definition must be a table of interfaces names!')
			success = false
		else 
			for _, s in pairs(interface_names) do
				if type(s) ~= 'string' then
					addToErrorMsg_PRIVATE('Non string value in the Interface table!')
					success = false
				end
			end	
		end
		if interface_names then
			interfaces = {}
			-- clear out any non-existent interfaces
			for _,value in pairs(interface_names) do
				if interfaces and interfaces_PRIVATE[value] then
					interfaces[value] = interfaces_PRIVATE[value]
				else
					addToErrorMsg_PRIVATE('There is no interface: '..value)
					success = false
				end
			end
		else
			interfaces = nil
		end
	end
	return interfaces, success
end

----------------------------------------------------------------------
function getMetatable(class_name)
	return metatables_PRIVATE[class_name]
end

----------------------------------------------------------------------
-- Checks for implementation of an interface on a class based on CreateClass()/Declare() calls
-- @param class the class of the created object
-- @param interface_name the name of the interface in question 
function implements_PRIVATE(class, interface_name)
	return 
	(class.implements and class.implements[interface_name] == interfaces_PRIVATE[interface_name])
	or 
	(class.super and implements_PRIVATE(class.super, interface_name))
end

----------------------------------------------------------------------
-- Checks for inheritance on a class based on CreateClass()/Declare() calls
-- @param instance_class the class of the created object
-- @param class the class in question
function introspect_PRIVATE(instance_class, class)
	return instance_class == class 
		or (instance_class 
			and instance_class.super 
			and introspect_PRIVATE(instance_class.super, class))
end
	
----------------------------------------------------------------------
function rawNilKeys_PRIVATE(t)
	if type(t) == 'table' then
		for key in pairs(t) do
			rawset(t, key, nil)
		end
		setmetatable(t, nil)
	end
end

----------------------------------------------------------------------
if DEBUG_INTERPRETATION then
function refreshClasses_PRIVATE(name)
    local direct_children = {}
    local refreshed_class = classes_PRIVATE[name]
    for _, class in pairs(classes_PRIVATE) do
		-- find the immediate child, and update the super class values
		local is_a = false
		local immediate_child = class
		local class = class:getSuperclass()
		while class do
			if class:getClassName() == name and (not direct_children[name]) then
				direct_children[class:getClassName()] = true
				is_a = true
				break
			end
			immediate_child = class
			class = class:getSuperclass()
		end
		
		if is_a then
			immediate_child.super = refreshed_class
			getmetatable(class).__index = refreshed_class
		end
	end
    for _, instance in pairs(refreshInstances_PRIVATE) do
		if instance.__isExtendableByProxy 
		and instance:__isExtendableByProxy() then
			local instance_mt = getmetatable(instance)
			local proxy = instance_mt.__index
			setmetatable(proxy, metatables_PRIVATE[instance:getClassName()])
		elseif type(instance) == 'table' then
			setmetatable(instance, metatables_PRIVATE[instance:getClassName()])
    	end
    end
	classesNeedRefresh = false
end
end -- if DEBUG_INTERPRETATION

----------------------------------------------------------------------
-- resets the error message
function resetErrorMessage_PRIVATE(start_message)
	errorMsg = start_message
	for key in pairs(missingInterfaces) do -- for key, _ in pairs(missingInterfaces) do
		missingInterfaces[key] = nil
	end
	for key in pairs(missingFunctions) do -- for key, _ in pairs(missingFunctions)
		missingFunctions[key] = nil
	end
end

----------------------------------------------------------------------
-- Checks to see if Class has implemented all of the abstract methods
-- of its parent
-- @param Class the class that derived from an abstract class
function verifyAbstractImplementation_PRIVATE(class, superclass)
	if not superclass then 
		return true
	elseif not superclass.abstract then
		return true
	elseif verifyFunctionImplementation_PRIVATE(class, superclass.abstractFunctions) then
		return true
	else
		addToErrorMsg_PRIVATE('Class '..class:getClassName()..' does not properly extend abstract class '..superclass:getClassName())
	end
end

----------------------------------------------------------------------
function verifyAllInterfacesImplementation_PRIVATE(class)
	local success = true
	if class.implements then
		local verifyClass = class
		repeat
			if verifyClass.implements then
				success = verifyInterfacesImplementation_PRIVATE(class, verifyClass.implements) and success
			end
			verifyClass = verifyClass.super
		until (not verifyClass) or not (verifyClass.abstract) 
	end
	return success
end
	
----------------------------------------------------------------------
-- Checks to see if Class has n implementation for every function
-- @param Class the class defined by declareClass()
-- @param functions a table of functions that must be found in declareClass()
-- @return true if successfull, else false
function verifyFunctionImplementation_PRIVATE(class, functions)
	local success = true
	for func_name, func in pairs(functions) do
		if not findConcreteFunction_PRIVATE(func_name, class) then
			if not missingFunctions[func_name] then
				missingFunctions[func_name] = true
				addToErrorMsg_PRIVATE('No implementation for function: '..func_name..'() found in class: '..class:getClassName())
			end
			success = false
		end
	end	
	return success
end

----------------------------------------------------------------------
-- checks to see if everything in functionTable is a function, if it is it 
-- adds it to Table.  If not, it prints the problem_message, + the !function name + messageCorrection
function verifyFunctionTable_PRIVATE(class, functions, base_class, problem_message, correction_message) 
	local success = true
	if functions then
		for name, func in pairs(functions) do
			if type(func) == 'function' then
				class[name] = func
			else
				addToErrorMsg_PRIVATE(problem_message..function_name..correction_message)
				success = false
			end
		end
	end
	return success
end
		
----------------------------------------------------------------------
-- Checks to see that Class implements all the interfaces it claims
-- to implement in declareClass()
-- @Class the class the must be verified
function verifyInterfacesImplementation_PRIVATE(class, interfaces)
	local success = true
	for key, interface in pairs(interfaces) do
		if not verifyFunctionImplementation_PRIVATE(class, interface) then
			if not missingInterfaces[key] then
				missingInterfaces[key] = true
				addToErrorMsg_PRIVATE(class:getClassName()..' implementation of the interface: '..tostring(key)..' is not correct!')
			end
			success = false
		end
	end
	return success
end

----------------------------------------------------------------------
-- makes sure the class definition use no keywords used by this 
-- system
function verifyKeywords_PRIVATE(class, name)
	local verified = true
	for _, reserved_word in pairs(reservedWords) do
		if class[reserved_word] then
			addToErrorMsg_PRIVATE(name..' has a member: '..reserved_word..' which will interfere with class declaration\n')
			verified = false
		end
	end
	return verified
end

return OOP