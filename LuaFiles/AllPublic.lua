deprecatedNaughtyModule(..., package.seeall)

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
function AllPublic:method1(value)
	printf("script method1 "..value)
end

function AllPublic:method1C(value)
	printf("script method1C "..value)
end
--[[		
function AllPublic:methodr1()
	return 18
end

function AllPublic:methodr1C()
	return 36
end
--]]