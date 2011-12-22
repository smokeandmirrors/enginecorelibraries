deprecatedNaughtyModule(..., package.seeall)

require'Utilities'
require'ObjectOrientedParadigm'

function AllPublicChild:awesome()
	print('Awesome Child:', self.three)
end

function AllPublicChild:bitchin()
	print('Bitchin Child:', self.four)
end

method = function(self)
	print('Awesome method: ', self.two)
end

childMethod = function(self)
	print('Awesome childMethod: ', self.one)
end