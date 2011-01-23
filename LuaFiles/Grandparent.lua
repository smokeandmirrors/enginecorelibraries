module(..., package.seeall)
require 'ObjectOrientedParadigm'

name = 'Grandparent'

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

-- declareClass(Grandparent)