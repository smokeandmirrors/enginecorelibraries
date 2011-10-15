module(..., package.seeall)
----------------------------------------------------------------------
-- Sequence.lua
--	
-- A suite of functionality to frame-to-frame agnostic code
-- \todo execute on this with co-routines
--
-- @author Smoke and Mirrors Development
-- smokeandmirrorsdevelopment@gmail.com
-- copyright 2011
require'ObjectOrientedParadigm'
require'Utilities'

m_sequences = {}

function noOnComplete()
end

function create(f, onComplete)
	tassert('function', f)
	
	if not isCallable(onComplete) then
		onComplete = noOnComplete
	end
	
	local sequence = 
		{ 
			m_routine = coroutine.create(f), 
			m_function = f, 
			m_noticeComplete = onComplete 
		}
		
	table.insert(m_sequences, sequence)
end

function execute(sequence)
	coroutine.resume(sequence.m_routine)
	if coroutine.status(sequence.m_routine) == 'dead' then
		sequence.m_noticeComplete(sequence.m_function)
		return true
	end
end

function wait()
	coroutine.yield()
end

function run()
	for index, sequence in ipairs(m_sequences) do
		if execute(sequence) then
			table.remove(m_sequences, index)
		end
	end
end