module(..., package.seeall)
require 'Parent'
require 'ObjectOrientedParadigm'

construct = function(self, ...)
	self.numberOfKids = 0
	self.numberOfGrandKids = 0
	self.numberOfParents = 2
	self.numberOfGrandparents = 4
	self.favoritePark = 'Central Park, NYC'
end

getNumberOfGrandparents = function(self)
	return numberOfGrandparents
end
