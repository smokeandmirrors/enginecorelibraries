_ENV = deprecatedNaughtyModule(...)
require 'Grandparent'
require 'ObjectOrientedParadigm'

construct = function(self, ...)
	self.numberOfKids = 4
	self.numberOfGrandKids = 0
	self.numberOfParents = 3
	self.favoriteMovie = 'Star Wars'
end

getNumberOfParents = function(self)
	return self.numberOfParents
end
