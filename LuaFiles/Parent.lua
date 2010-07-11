module(..., package.seeall)
require 'Grandparent'
require 'ObjectOrientedParadigm'

name = 'Parent'
extends = 'Grandparent'

construct = function(self, ...)
	self.numberOfKids = 4
	self.numberOfGrandKids = 0
	self.numberOfParents = 3
	self.favoriteMovie = 'Star Wars'
end

getNumberOfParents = function(self)
	return self.numberOfParents
end


declareClass(Parent)