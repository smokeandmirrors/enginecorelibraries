module(..., package.seeall)

require'ObjectOrientedParadigm'
require'Utilities'

maxMilliseconds = 15000 -- milliseconds
frameClock = new'ClockFrame'
frame = 0
timer = new('Timer', frameClock)

function run()
	frameClock:tick()
	timer:set(maxMilliseconds, maxMilliseconds, BoolEnum.BoolEnum_False)
	timer:start()
	
	while timer:isTimeRemaining() do
		frameClock:tick()
		Sequence:run()
	end	
end