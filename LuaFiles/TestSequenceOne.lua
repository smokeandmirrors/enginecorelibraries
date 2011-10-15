module(..., package.seeall)

require'ObjectOrientedParadigm'
require'Utilities'
require'Sequence'


function doTime(timeOne)
	assert(coroutine.running() ~= nil, 'Sequence code must be called from within a coroutine, use in a Sequence')
	local stopwatch = new('Stopwatch', Engine.frameClock)
	stopwatch:start()
	while stopwatch:seconds() < timeOne do
		Sequence.wait()
	end
	print(stopwatch:seconds())
end

-- sequence
function doLotsOfTime(timeOne, timeTwo, timeThree)
	
	doTime(timeOne)
	print('I finished time one after: '..timeOne)
	doTime(timeTwo)
	print('I finished time two: '..timeTwo)
	doTime(timeThree)
	print('I finished time three: '..timeThree)
end

function myTimeSequence()
	doLotsOfTime(1, 5, 10)
end

function myTimeSequence2()
	doLotsOfTime(2, 6.67, 8.333)
end

function woot(sequence)
	if sequence == myTimeSequence then
		print('woot! my first sequence finished!')
	elseif sequence == myTimeSequence2 then
		print('woot! my second sequence finished!')
	else
		error'There is trouble!'
	end
end

Sequence.create(myTimeSequence, woot)
Sequence.create(myTimeSequence2, woot)