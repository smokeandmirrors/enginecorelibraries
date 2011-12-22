deprecatedNaughtyModule(..., package.seeall)

require'ObjectOrientedParadigm'
require'Utilities'
require'Sequence'

-- latent function
function doTime(timeOne)
	Sequence.validate()
	local stopwatch = new('Stopwatch', Engine.frameClock)
	stopwatch:start()
	while stopwatch:seconds() < timeOne do
		Sequence.wait()
	end
end

-- sequence function that calls latent functions
function doLotsOfTime(timeOne, timeTwo, timeThree)	
	doTime(timeOne)
	print('I finished time one: '..timeOne)
	doTime(timeTwo)
	print('I finished time two: '..timeTwo)
	doTime(timeThree)
	print('I finished time three: '..timeThree)
end

function myTimeSequence()
	doLotsOfTime(1, 3, 5)
end

function myTimeSequence2()
	doLotsOfTime(2, 4, 6)
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

function test()
	Sequence.create(myTimeSequence, woot)
	Sequence.create(myTimeSequence2, woot)
end