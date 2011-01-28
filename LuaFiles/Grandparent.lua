module(..., package.seeall)
local OOP = require 'ObjectOrientedParadigm'

construct = function(self, ...)
	self.numberOfKids = 2
	self.numberOfGrandKids = 5
	self.favoriteFood = 'Pizza'
end

getNumberOfKids = function(self)
	return self.numberOfKids
end

getNumberOfGrandKids = function(self)
	return self.numberOfGrandKids
end

--[[
__eq = function(self, other)
	return self.favoriteFood == other.favoriteFood
end

favoriteMusic = function(self)
	return "The Beatles"
end

declareClass(Grandparent)
--]]
