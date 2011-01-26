module(..., package.seeall)
require 'Parent'
require 'ObjectOrientedParadigm'

construct = function(self, ...)
	self.numberOfKids = 0
	self.numberOfGrandKids = 0
	self.numberOfParents = 2
	self.numberOfGrandparents = 4
	self.favoritePark = 'Central Park, NYC'
	self.mom = new'Parent'
	self.dad = new'Parent'
end

getNumberOfGrandparents = function(self)
	return numberOfGrandparents
end

__eq = function(self, other)
	return self.favoritePark == other.favoritePark
end

--[[
onRefresh = function(self)
	return 'Wes knows awesome when he sees it'
end

onRefresh2 = function(self, sweet)
	self.favoritePark = sweet
	return self.favoritePark
end

declareClass(Child)
--]]