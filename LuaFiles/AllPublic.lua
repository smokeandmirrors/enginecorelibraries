module(..., package.seeall)

require'Utilities'
require'ObjectOrientedParadigm'

function AllPublic:awesome()
	print('Awesome:', self.one)
end

function AllPublic:sweet()
	print('Sweet:', self.two)
end

--[[
function AllPublic:method2()
	-- dassert(self == nil)
	return 4
end
--]]

function AllPublic:method0()
	printf("script method0")
end

function AllPublic:method0C()
	printf("script method0C")
end
	