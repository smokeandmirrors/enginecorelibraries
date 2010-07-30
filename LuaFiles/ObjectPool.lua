module("ObjectPool", package.seeall)
---------------------------------------------------------------------
--	ObjectPool.lua 
--	
--  	This class allows us to reduce the amount of memory allocations in lua for table instantiations that are only used locally
--	
-- @author Smoke and Mirrors Development
-- @email smokeandmirrorsdevelopment@gmail.com	
-- @copyright 2010 Smoke and Mirrors Development
--
OOP = require "ObjectOrientedParadigm"

local ObjectPoolTable = {}
ObjectPoolTable.Name = "ObjectPoolTable"
ObjectPoolTable.Protected = true

---------------------------------------------------------------------
-- define the class
-- this class creates and recycles of a single type
-- members include (but are all PRIVATE)
--	allObjects table
--	freeObjects table
-- 	numFreeObjects number
function ObjectPoolTable:Initialize() -- this would look like the vec3 pool object
	self.freeObjects = {} 
	self.numFreeObjects = 0
end

---------------------------------------------------------------------
-- creates more free objects if no free object remain PRIVATE
-- @param more how many more objects to create
function ObjectPoolTable:CreateMore_PRIVATE(classname, more)
	self.numFreeObjects = self.numFreeObjects + more
	
	for i = 1, more do
		table.insert(self.freeObjects, new(classname))
	end 
end

---------------------------------------------------------------------
-- used for gathering object creation stats, if needed
-- @return the number of free objects that this ObjectPoolTable has available
function ObjectPoolTable:GetNumFree()
	return self.freeObjects
end

---------------------------------------------------------------------
-- PRIVATE
-- @returns 1 object 
function ObjectPoolTable:GetObject_PRIVATE(classname)
	if self.numFreeObjects == 0 then
		return new(classname)
	else
		self.numFreeObjects = self.numFreeObjects - 1
		return table.remove(self.freeObjects)
	end
end

---------------------------------------------------------------------
-- PRIVATE
-- @returns a table of the objects of the type that this ObjectPoolTable manages
function ObjectPoolTable:GetObjects_PRIVATE(classname, num, objectTable)
	if self.numFreeObjects < num then
		self:CreateMore_PRIVATE(classname, num - self.numFreeObjects)
	end
	
	self.numFreeObjects = self.numFreeObjects - num
		
	for i = 1, num do
		table.insert(objectTable, table.remove(self.freeObjects))
	end
	
	return objectTable
end

---------------------------------------------------------------------
-- PRIVATE puts the object back in the free list
-- @param o the unneeded object
function ObjectPoolTable:Recycle_PRIVATE(o)
	self.numFreeObjects = self.numFreeObjects + 1
	table.insert(self.freeObjects, o) 
end

DeclareClass(ObjectPoolTable)

-- table of single type object tables
tables = {}

---------------------------------------------------------------------
-- PRIVATE creates an object pool of the object type if there is not one created all ready
-- @param classname the name of the object's class
function CreateObjectPool_PRIVATE(classname)
	tables[classname] = OOP.classes_PRIVATE["ObjectPoolTable"]:new()
	return tables[classname]
end

---------------------------------------------------------------------
-- Get a single object of the type classname
-- @param classname the name of the type of the object requested
-- @return a single instance of classname
function Get(classname)
	return tables[classname] and tables[classname]:GetObject_PRIVATE(classname) or CreateObjectPool_PRIVATE(classname):GetObject_PRIVATE(classname)
end

---------------------------------------------------------------------
-- Return an object to the pool for reuse
-- @param o the object that is not needed, and better not have 
-- ANY REFERENCES LEFT OUTSIDE THE POOL OR WE WILL BE SCREWED UNTO THE VERY LORD
function Recycle(...)
	local num = select('#', ...)
	local object
	for i=1,num do
		object = select(i, ...)
		if object then
			tables[object:GetClassName()]:Recycle_PRIVATE(object)
		end
	end
end

function GetOrRecycle(...)
	local num = select('#', ...)
	if num == 1 and type(...) == "string" then
		return Get(...)
	else
		Recycle(...)
	end
end

if not getmetatable(ObjectPool) then
	setmetatable(ObjectPool, {})
end

getmetatable(ObjectPool).__call = function(t, ...)
	return GetOrRecycle(...)
end


