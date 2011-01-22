module('ObjectOrientedParadigm', package.seeall)
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
require'Utilities'

----------------------------------------------------------------------
----------------------------------------------------------------------
-- 'public'
----------------------------------------------------------------------
----------------------------------------------------------------------

-- @todo c++ metamethods && metamethods inheritance
-- @todo make the c++ wrapping do private/protected? FREAKING HARD (friend declaration + privacy placement?)
-- @todo make sure there are no functions/members by name
-- 		of the default class members, like IS_A, construct, super, etc.
-- @todo update documentation
-- \todo if __tostring or __concat are not supplied, supply the defaults

---------------------------------------------------------------------
-- change the following values to change compilation, error handling,
-- error reporting, and informative messages

-- for condition interpretation
-- recommended to be defined from C
-- local DEBUG_INTERPRETATION = true
-- non-error message reporting
local print = print -- declareclasserror...runtimeerror, etc.
-- halt functionality error reporting
local error = error
-- conditional halt functionality error reporting
local assert = assert

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
-- Checks for inheritance on an object created by declareClass() calls
-- or for inheritance on an object that is extended from native
-- @param instance the runtime object
-- @param class_name the class type in question
-- @todo finish is_subclass version
function _G.IS_A(instance, class_name)
	local tupos = type(instance)
	return (tupos == 'table' or (tupos == 'userdata' and getmetatable(instance) and getmetatable(instance).__index)) 
		and instance.getClass 
		and classes_PRIVATE[class_name]
		and introspect_PRIVATE(instance:getClass(), classes_PRIVATE[class_name])
end

----------------------------------------------------------------------
function _G.addClassConstructor(class_name, constructor)
	assert(not classes_PRIVATE[class_name], 'A class all ready is declared with that name')
	assert(not constructors_PRIVATE[class_name], 'A constructor all ready exists for that class.')
	classes_PRIVATE[class_name] = true
	constructors_PRIVATE[class_name] = constructor
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
-- Name = (string) -- the class name
-- AbstractFunctions = (table of functions) -- list of functions that must be found in concrete class that extend this one
-- functions = (table of functions) -- the concrete methods for this class
function _G.declareAbstractClass(definition)
	declareAbstractClass_PRIVATE(definition)
	collectgarbage('collect')
end

----------------------------------------------------------------------
-- Define a class
-- @param definition a table with entries as follows:
-- Name = (string) -- the class name
-- Extends = (string) -- the base class name (optional)
-- functions = (table of functions) -- the methods for this class
-- Implements = (table of interface names) -- the interfaces_PRIVATE this class implements
function _G.declareClass(definition)
	declareClass_PRIVATE(definition)
end

----------------------------------------------------------------------
-- Define an interface - cannot be instantiated, only implemented!
-- @param definition.name, otherwise functions the interface name
function _G.declareInterface(definition)
	declareInterface_PRIVATE(definition)
end

----------------------------------------------------------------------
-- nil out an object for garbage collection, and call any methods
-- it might have to clear out references to extension objects
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
function _G.new(class_name, ...)
	assert(classes_PRIVATE[class_name], 'No such class: '..class_name..'!')
	return constructors_PRIVATE[class_name](...)
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
-- @todo get this out of the constructor, or in debug mode only
if DEBUG_INTERPRETATION then
getName = function(instance)
	if type(instance.name) == 'number' then -- apparently, string concats in lua are harsh
		instance.name = instance:getClassName()..' '..instance.name
	end
	
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
classes_PRIVATE 		= {}
constructors_PRIVATE	= {}
destructors_PRIVATE		= {}
interfaces_PRIVATE 		= {}
metatables_PRIVATE 		= {}
-- helper table
metamethods = {
	__add 		= true,
	__call 		= true,
	__concat 	= true,
	__div 		= true,
	__eq 		= true,
	__gc 		= true,
	__le 		= true,
	__len 		= true,
	__lt 		= true,
	__metatable = true,
	__mod 		= true,
	__mode 		= true,
	__mul 		= true,
	__newindex 	= true,
	__pow 		= true,
	__sub 		= true,
	__tostring 	= true,
	__unm 		= true
-- @note __index gets set automatically to base class
-- @note the use of __metatable will interfere with the ability
-- to refresh a class definition on instances at runtime
}

-- @todo finish these and warn about them
reservedOOwords = {

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
classesNeedRefresh			= false
refreshInstances_PRIVATE	= setmetatable({}, {__mode = 'v'})
end --- DEBUG_INTERPRETATION

----------------------------------------------------------------------
-- this replaces having a base class of 'object', saving an index 
-- lookup for every class read of these values
function addCommonClassProperties_PRIVATE(class, super, class_name)
	class.ACTS_AS = ACTS_AS
	class.class = class
	class.className = class_name
	class.getClass = getClass
	class.getClassName = getClassName
	class.getName = class.getName or getName
	class.getSuperclass = getSuperclass
	class.IS_A = IS_A
	class.toString = class.toString or toString
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
-- @todo make this use inheritance
-- @and then pull them over from the library declaration
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
-- @param def definition table in the same format as 
-- declareClass() and declareClass_PRIVATE()
if DEBUG_INTERPRETATION then
function beginClassDeclaration_PRIVATE(def)
	-- hold failure reporting until the very end so that all problems with the class can be reported.
	local compiled = true
	local implements = def.implements
	local name = def.name
	local extends = def.extends
	-- there should only be functions left in the definition
	def.name = nil
	def.extends = nil
	def.implements = nil
	-- validate the class name
	if findClassName_PRIVATE(name) then
		classesNeedRefresh = true
		print('REDEFINING CLASS: '..name)
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
	-- assign basic properties
	local base_class
	if base_class_name then
		base_class = classes_PRIVATE[base_class_name]
	end
	local base_class = base_class_name and classes_PRIVATE[base_class_name]
	local class = createClassProperties_PRIVATE(name, base_class)
	assignMetaMethods_PRIVATE(name, def, base_class_name)
	-- verify the interfaces_PRIVATE
	local interfacesGood = true
	local implemented, interfacesGood = findInterfaces_PRIVATE(implements)
	compiled = interfacesGood and compiled
	class.implements = implemented	
	-- add the defined functions in the file to the class declaration
	compiled = verifyFunctionTable_PRIVATE(class, def, base_class, name..'.', ' is not a function.  Create this object in the constructor() function.') and compiled
	-- add methods common to all classes in lieu of an Object base class
	compiled = addCommonClassProperties_PRIVATE(class, base_class, name)
	return class, compiled
end
else
function beginClassDeclaration_PRIVATE(def)
	-- hold failure reporting until the very end so that all problems with the class can be reported.
	local compiled = true
	local implements = def.implements
	local name = def.name
	local extends = def.extends
	-- there should only be functions left in the definition
	def.name = nil
	def.extends = nil
	def.implements = nil
	-- validate the class name
	if findClassName_PRIVATE(name) then
		-- warn(false, 'Class '..name..' already exists!')
		assert(false, 'Class '..name..' already exists!')
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
	-- assign basic properties
	local base_class = base_class_name and classes_PRIVATE[base_class_name]
	local class = createClassProperties_PRIVATE(name, base_class)
	assignMetaMethods_PRIVATE(name, def, base_class_name)
	-- verify the interfaces_PRIVATE
	local interfaces_good = true
	local implemented, interfaces_good = findInterfaces_PRIVATE(implements)
	compiled = interfaces_good and compiled
	class.implements = implemented	
	-- add the defined functions in the file to the class declaration
	compiled = verifyFunctionTable_PRIVATE(class, def, base_class, name..'.', ' is not a function.  Create this object in the constructor() function.') and compiled
	-- add methods common to all classes in lieu of an Object base class
	compiled = addCommonClassProperties_PRIVATE(class, base_class, name)
	return class, compiled
end
end -- end if DEBUG_INTERPRETATION

----------------------------------------------------------------------
-- assign the basics, implement inheritance
-- @todo add the functions common to all classes
if DEBUG_INTERPRETATION then
function createClassProperties_PRIVATE(name, superclass)
	-- define the class
	local class = {className = name, nextInstanceId = 0}
	-- implement inheritance from super classes
	setmetatable(class, {__index = superclass}) 
	-- implement inheritance for instantiated objects
	metatables_PRIVATE[name] = {__index = class} 
	-- return the class definition
	return class
end
else
function createClassProperties_PRIVATE(name, superclass)
	-- define the class
	-- implement inheritance from super classes
	local class = setmetatable({className = name}, {__index = superclass}) 
	-- implement inheritance for instantiated objects
	metatables_PRIVATE[name] = {__index = class} 
	-- return the class definition
	return class
end
end -- end if DEBUG_INTERPRETATION

----------------------------------------------------------------------
-- create the creation function for the object
-- @todo in the old version, we included a check for function New() which
-- was used as a hook for classes in C to allow themselves to hook into
-- this system, this version will have to include that
--
-- Another question will have to be answered:
-- does the class get declared first, or does the C library register first?
-- Answer:  the C library registers first.  Then, the lua class gets declared,
-- adding functionality to the C library
--
if DEBUG_INTERPRETATION then
-- function createConstructor_PRIVATE(class, metatable, name, parentudata_metamethod_table_name)
-- function createConstructor_PRIVATE(class, metatable, name)
function createConstructor_PRIVATE(class, metatable)
	assert(class and metatable)
	if class.new then
		if class.setmetatable then
			return function(...)
				class.nextInstanceId = class.nextInstanceId + 1
				-- local instance = addInstanceToRefresh_PRIVATE(constructHierarchy_PRIVATE(class, class.setmetatable(class.new(...), metatable, name, parentudata_metamethod_table_name), ...)) 
				-- local instance = addInstanceToRefresh_PRIVATE(constructHierarchy_PRIVATE(class, class.setmetatable(class.new(...), metatable, name), ...)) 
				local instance = addInstanceToRefresh_PRIVATE(constructHierarchy_PRIVATE(class, class.setmetatable(class.new(...), metatable), ...)) 
				if not instance.name then
					instance.name = nextInstanceId
				end
				return instance
			end
		else
			return function(...)
				class.nextInstanceId = class.nextInstanceId + 1
				local instance = class.new(...)
				if not instance.name then
					instance.name = nextInstanceId
				end
				return addInstanceToRefresh_PRIVATE(constructHierarchy_PRIVATE(class, setmetatable(instance, metatable), ...)) 
			end	
		end
	elseif class.setmetatable then
		return function(...)
			class.nextInstanceId = class.nextInstanceId + 1
			constructHierarchy_PRIVATE(class, class.setmetatable({name = class.nextInstanceId, ...}, metatable), ...)
		end
	else
		return function(...)
			class.nextInstanceId = class.nextInstanceId + 1
			return addInstanceToRefresh_PRIVATE(constructHierarchy_PRIVATE(class, setmetatable({name = class.nextInstanceId, ...}, metatable), ...))
		end
	end
end	
else
-- function createConstructor_PRIVATE(class, metatable, name, parentudata_metamethod_table_name)
function createConstructor_PRIVATE(class, metatable)
	if class.new then
		if class.setmetatable then
			return function(...)
				-- return constructHierarchy_PRIVATE(class, class.setmetatable(class.new(...), metatable, name, parentudata_metamethod_table_name), ...)
				return constructHierarchy_PRIVATE(class, class.setmetatable(class.new(...), metatable), ...)
			end
		else
			return function(...)
				return constructHierarchy_PRIVATE(class, setmetatable(class.new(...), metatable), ...)
			end
		end	
	elseif class.setmetatable then
		return function(...)
			constructHierarchy_PRIVATE(class, class.setmetatable({...}, metatable), ...)
		end
	else
		return function(...)
			return constructHierarchy_PRIVATE(class, setmetatable({...}, metatable), ...)
		end
	end
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
	compiled = verifyFunctionTable_PRIVATE(abstract_class.abstractFunctions, abstractFunctions, base_class, abstract_class:getClassName()..'.', ' is not a function.  Put this object in the Initialize() function.') and compiled
	assert(compiled, errorMsg)
	-- add to the list
	classes_PRIVATE[name] = abstract_class
	constructors_PRIVATE[name] = getAbstractConstructor('Cannot instantiate abstract class: '..name)
end

----------------------------------------------------------------------
-- @todo, there doesn't really need to be a constructor
-- for every abstract classes, just an easy error message
function getAbstractConstructor(error_message)
	return function()
		assert(false, error_message)
	end
end

----------------------------------------------------------------------
if DEBUG_INTERPRETATION then
function declareClass_PRIVATE(definition)
	local public = true
	local name = definition.name or 'unnamed class'
	local super_name = definition.extends
	resetErrorMessage_PRIVATE('\nERROR:\nClass declaration for '..name..' is incorrect, see lua output or log.\n')
	local class, compiled = beginClassDeclaration_PRIVATE(definition)
	-- if the class implements all interface methods and abstract methods, allow instantiation
	compiled = verifyAbstractImplementation_PRIVATE(class, class.super) and compiled
	compiled = verifyAllInterfacesImplementation_PRIVATE(class) and compiled
	-- if the class is well formed... 
	assert(compiled, errorMsg)
	-- ...add to the list...
	classes_PRIVATE[name] = class
	-- ...create the last function
	-- local constructor_function = createConstructor_PRIVATE(class, metatables_PRIVATE[name], name, super_name)
	local constructor_function = createConstructor_PRIVATE(class, metatables_PRIVATE[name])
	if public then 
		constructors_PRIVATE[name] = constructor_function
	else
		-- @todo finish protected classes
	end
	if classesNeedRefresh then
		refreshClasses_PRIVATE()
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
	-- if the class is well formed...
	assert(compiled, errorMsg)
	-- ...add to the list...
	classes_PRIVATE[name] = class
	-- ...create the constructor
	-- local constructor_function = createConstructor_PRIVATE(class, metatables_PRIVATE[name], name, super_name)
	local constructor_function = createConstructor_PRIVATE(class, metatables_PRIVATE[name])
	if public then 
		constructors_PRIVATE[name] = constructor_function
	else
		-- @todo finish protected classes
	end
end
end -- end if DEBUG_INTERPRETATION

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
	-- @todo, make sure this next line is needed...I can't imagine why it would be
	interfaces_PRIVATE[name..'_mt'] = { __index = interfaces_PRIVATE[name] }
	interface = interfaces_PRIVATE[name]
		
	compiled = verifyFunctionTable_PRIVATE(interface, funcs, nil, 'Everything in the interface, '..name..', function list must be a function.  ', ' is not.') and compiled 
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
function refreshClasses_PRIVATE()
    for _, classdef in pairs(classes_PRIVATE) do
		if classdef:getSuperclass() then
			getmetatable(classdef).__index = classes_PRIVATE[classdef:getSuperclass():getClassName()]
		end
    end
    for _, instance in pairs(refreshInstances_PRIVATE) do
        setmetatable(instance, metatables_PRIVATE[instance.className])
    end
	classesNeedRefresh = false
end
end

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

function getEnvironment_PRIVATE(functions)
	for k, v in next, functions do
		if type(v) == 'function' then
			return getfenv(v)
		end
	end
	if functions.protected then
		for k, v in next, functions.protected do
			if type(v) == 'function' then
				return getfenv(v)
			end
		end
	end
	if functions.private then
		for k, v in next, functions.private do
			if type(v) == 'function' then
				return getfenv(v)
			end
		end
	end
end

----------------------------------------------------------------------
-- checks to see if everything in functionTable is a function, if it is it adds it to Table.  If not, it prints the problem_message, + the !function name + messageCorrection
function verifyFunctionTable_PRIVATE(t, functions, base_class, problem_message, correction_message) 
	
	local success = true
	if functions then
		
		local privateEnvironment
		local reference = getEnvironment_PRIVATE(functions) 
				
		if reference and (functions.protected or functions.protected) then
			privateEnvironment = { privateClass = t, super = function() return base_class end }
			setmetatable(privateEnvironment, {__index = reference})
		end					
		
		if functions.private then
			for name, func in pairs(functions.private) do
				if type(func) == 'function' then
					t[name] = function(self, ...)
						assert(getfenv(2) == t.privateEnvironment, 'function '..name..' is declared PRIVATE')
						return func(self, ...) 
					end
				else
					addToErrorMsg_PRIVATE(problem_message..name..correction_message)
					success = false
				end
			end
		end
		
		if functions.protected then
			for name, func in pairs(functions.protected) do
				if type(func) == 'function' then	
					t[name] = function(self, ...)
						assert(introspect_PRIVATE(self:getClass(), getfenv(2).privateClass), 'function' ..name.. ' is declared PROTECTED')
						return func(self, ...) 
					end
				else
					addToErrorMsg_PRIVATE(problem_message..name..correction_message)
					success = false
				end
			end
		end
		functions.protected = nil
		functions.private = nil
		
		for function_name, func in pairs(functions) do
			
			if type(func) == 'function' then
				if privateEnvironment then 
					setfenv(func, privateEnvironment)
				end
				
				t[function_name] = func
			elseif not ((type(func) == 'string' and (function_name == '_NAME' or function_name == '_PACKAGE')) 
			or (type(func) == 'table' and function_name == '_M')) -- and func == the module itself? to really check? 
			then				 
				
				addToErrorMsg_PRIVATE(problem_message..function_name..correction_message)
				success = false
			end
		end	
		t.privateEnvironment = privateEnvironment
	end
	
	return success
end
-- t._NAME with the given name, t._M with the module (t itself), and t._PACKAGE
		
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

