deprecatedNaughtyModule(..., package.seeall)
require'Utilities'
local U = require'Utilities'
local tabs = {}
table.insert(tabs, '\t')
table.insert(tabs, '\t\t')
table.insert(tabs, '\t\t\t')
table.insert(tabs, '\t\t\t\t')

local Names = {}
table.insert(Names, 'One')
table.insert(Names, 'Two') 
table.insert(Names, 'Three')
table.insert(Names, 'Four')
table.insert(Names, 'Five')
table.insert(Names, 'Six')
table.insert(Names, 'Seven')
table.insert(Names, 'Eight')
table.insert(Names, 'Nine')
table.insert(Names, 'Ten')

local names = {}
table.insert(names, 'one')
table.insert(names, 'two') 
table.insert(names, 'three')
table.insert(names, 'four')
table.insert(names, 'five')
table.insert(names, 'six')
table.insert(names, 'seven')
table.insert(names, 'eight')
table.insert(names, 'nine')
table.insert(names, 'ten')

function writeClass(number)
	for rets = number, rets >= 0, -1 do
		for args = number, args >= 0, -1 do
			
		end	
	end
end

for i = 0, 10 do 
	writeClass(i)
end