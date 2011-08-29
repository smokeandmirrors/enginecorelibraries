module(..., package.seeall)
require 'Parent2'
require 'ObjectOrientedParadigm'

construct = function(self, ...)
	self.numberOfKids = 0
	self.numberOfGrandKids = 0
	self.numberOfParents = 2
	self.numberOfGrandparents = 4
	self.favoritePark = 'Central Park'
	self.mom = new'Parent2'
	self.dad = new'Parent2'
end

getNumberOfGrandparents = function(self)
	return self.numberOfGrandparents
end

__eq = function(self, other)
	return self.favoritePark == other.favoritePark
end
