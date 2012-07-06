#pragma once
#ifndef TIME_H
#define TIME_H
/**
\file Time.h

<DEVELOPMENT STATUS>
Current Draft		:	0.0
Unit Tested			:	NO
Used in development	:	YES
Used in experiments :	YES
Tested in the field	:	NO

*/
#include <stdio.h>

#include "Platform.h"
#include "Singleton.h"

#include "math.h"

typedef ulong cycle;
typedef dreal millisecond;
typedef dreal second;

namespace xronos
{

/** frame clock, game play/engine clock */
class ClockInterface 
{
public:
	virtual ~ClockInterface(void)=0 {/*empty*/}
	virtual dreal getRate(void) const=0;
	/** return the last cycle when this object processed real time */
	virtual cycle getTick(void) const=0;
	virtual millisecond milliseconds(void) const=0;
	virtual second seconds(void) const=0;
	virtual void setRate(dreal rate)=0;
	virtual void tick(void)=0;
}; // ClockInterface

// the single, real time clock
class Clock 
	: public ClockInterface 
	, public designPatterns::Singleton<Clock>
{
public:
	static Clock* createSingleton(void) { return new Clock(); }

	/** cycles per second */
	const cycle hertz; 
	/** seconds per cycle */
	const second hertzInverse;
	/** cycles per millisecond */
	const cycle milliHz;
	/** millisecond per cycle*/
	const millisecond milliHzInverse;
	
	dreal getRate(void) const { return 1.0; }

	inline cycle cycles(void) const { return getCurrentCycle() - cycleZero; }

	cycle getTick(void) const { assert(false); return 0; /* never do this */ }

	millisecond milliseconds(void) const;

	void reset(void);

	second seconds(void) const;

	void setRate(dreal) { assert(false); /* not allowed on the real time clock */ }
	
	void tick(void) { assert(false); /* no need to tick this clock */ }

private:
	cycle cycleZero;
	
	Clock(void);

	cycle getCurrentCycle(void) const;
}; // class Clock

class ClockFrame : public ClockInterface 
{
public:
	ClockFrame(void)
	: m_currentMilliseconds(0)
	, m_currentSeconds(0)
	, m_rate(1.0)
	, m_tick(xronos::Clock::single().cycles())
	{ /* empty */ }
	
	ClockFrame(cycle initialTime)
	: m_currentMilliseconds(0)
	, m_currentSeconds(0)
	, m_rate(1.0)
	, m_tick(initialTime)
	{ /* empty */ }
	
	ClockFrame(const ClockFrame& clone)
	: m_currentMilliseconds(clone.milliseconds())
	, m_currentSeconds(clone.seconds())
	, m_rate(clone.getRate())
	, m_tick(clone.getTick())
	{ /* empty */ }
	
	dreal getRate(void) const 
	{ 
		return m_rate; 
	}

	cycle getTick(void) const 
	{ 
		return m_tick; 
	}

	millisecond milliseconds(void) const	
	{ 
		return m_currentMilliseconds; 
	}

	second seconds(void) const
	{
		return m_currentSeconds;
	}
	
	void setRate(dreal rate)
	{
		m_rate = rate;
	}

	void tick(void)
	{
		cycle tick = xronos::Clock::single().cycles();
		cycle delta = tick - m_tick;
		m_currentMilliseconds += static_cast<millisecond>(m_rate * (delta * xronos::Clock::single().milliHzInverse)); 
		m_currentSeconds += m_currentMilliseconds * 1000;
		m_tick = tick;
	}

private:
	ClockFrame operator=(const ClockFrame &);

	millisecond	m_currentMilliseconds;
	second		m_currentSeconds;
	dreal		m_rate;
	cycle		m_tick;
}; // class ClockFrame

class ClockRelative : public ClockFrame 
{
public:
	ClockRelative(const ClockInterface& parent)
		: m_currentMilliseconds(0)
		, m_currentSeconds(0)
		, m_rate(parent.getRate())
		, m_tick(parent.getTick())
		, m_parent(&parent)
	{ /* empty */ }

	ClockRelative(const ClockRelative& clone)
		: m_currentMilliseconds(clone.milliseconds())
		, m_currentSeconds(clone.seconds())
		, m_rate(clone.getRate())
		, m_tick(clone.getTick())
		, m_parent(clone.getParent())
	{ /* empty */ }

	dreal getRate(void) const 
	{ 
		return m_parent->getRate() * m_rate; 
	}

	void tick(void)
	{
		cycle tick = m_parent->getTick();
		cycle delta = tick - m_tick;
		m_currentMilliseconds += static_cast<millisecond>(getRate() * (delta * xronos::Clock::single().milliHzInverse)); 
		m_currentSeconds += m_currentMilliseconds * 1000;
		m_tick = tick;
	}
	
protected:
	inline const ClockInterface* getParent(void) const
	{
		return m_parent;
	}

private:
	ClockRelative operator=(const ClockRelative &);

	millisecond	m_currentMilliseconds;
	second		m_currentSeconds;
	dreal		m_rate;
	cycle		m_tick;
	const ClockInterface* m_parent;
}; // class ClockRelative

class Stopwatch
{
public:
	Stopwatch(const ClockInterface& reference)
	: m_reference(reference) 
	, m_start(0)
	, m_stop(0)
	, m_active(false)
	{ 
		/* empty */ 
	}
	
	bool isActive(void) const 
	{
		return m_active;
	}

	millisecond milliseconds(void) const	
	{ 
		if (m_active)
		{
			millisecond current = m_reference.milliseconds();
			return current - m_start;
		}
		else
		{
			return m_stop - m_start;
		}
	}

	second seconds(void) const
	{
		if (m_active)
			return static_cast<second>(0.001 * (m_reference.milliseconds() - m_start)); 
		else
			return static_cast<second>(0.001 * (m_stop - m_start));	
	}

	void start(void)
	{
		if (!m_active)
		{
			m_start = m_reference.milliseconds();
			m_active = true;
		}
	}

	void stop(void)
	{
		if (m_active)
		{
			m_stop = m_reference.milliseconds();
			m_active = false;
		}
	}

	void reset(void)
	{
		m_start = m_reference.milliseconds();
		m_stop = m_start;
	}
	
private:
	Stopwatch(void);
	Stopwatch(const Stopwatch&);
	Stopwatch operator=(const Stopwatch&);
	
	const ClockInterface& m_reference;
	millisecond m_start;
	millisecond m_stop;
	bool m_active;
}; // class Stopwatch

class Timer 
{
public:
	Timer(const ClockInterface& reference, millisecond maxTime=0.0, millisecond minTime=-1.0, BoolEnum autoReset=BoolEnum_False)
	: m_stopwatch(reference)
	, m_autoReset(autoReset == BoolEnum_Unset ? autoReset == BoolEnum_True : false)
	, m_maxTime(maxTime)
	, m_minTime(minTime == -1.0 ? maxTime : minTime)
	{
		reset();
	}

	bool isActive(void) const
	{	
		return m_stopwatch.isActive();
	}	

	bool isTimeRemaining(void)
	{
		if (isActive())
		{
			bool timeRemains = _getMillisecondsPassed() < m_resetTime;

			if (m_autoReset == BoolEnum_True)
			{
				reset();
			}

			return timeRemains;
		}
		
		return false;
	}

	bool isTimeUp(void) 
	{
		if (isActive())
		{
			bool timeIsUp = _getMillisecondsPassed() >= m_resetTime;
			
			if (m_autoReset)
			{
				reset();
			}
			
			return timeIsUp;
		}
		
		return false;
	}

	millisecond milliseconds(void) const
	{
		return m_resetTime - _getMillisecondsPassed();
	}

	void reset(void)
	{
		m_stopwatch.reset();
		m_resetTime = m_maxTime; // generateRandom(m_minTime, m_maxTime);
	}

	second seconds(void) const
	{
		return milliseconds() * 0.001;
	}

	void set(millisecond maxTime, millisecond minTime=-1.0, BoolEnum autoReset=BoolEnum_Unset)
	{
		m_maxTime = maxTime;
		m_minTime = minTime == -1.0 ? maxTime : minTime;
		reset();

		if (autoReset != BoolEnum_Unset)
			m_autoReset = autoReset == BoolEnum_True;
	}

	void start(void)
	{
		if (!isActive())
		{
			m_stopwatch.start();
		}
	}

	void stop(void)
	{
		if (isActive())
		{
			m_stopwatch.stop();
		}
	}

protected:
	inline millisecond _getMillisecondsPassed(void) const
	{
		return m_stopwatch.milliseconds(); 
	}

private:
	Timer(void);
	Timer(const Timer& relative_parent);
	Timer operator=(const Timer&);
	
	Stopwatch	m_stopwatch;
	bool		m_autoReset;
	millisecond	m_maxTime;
	millisecond	m_minTime;
	millisecond	m_resetTime;
}; // class Timer

// \todo, remove these (currently needed for unit tests)
inline cycle cycles(void) { return Clock::single().cycles(); }
inline millisecond milliseconds(void) { return Clock::single().milliseconds(); }
inline second seconds(void) { return Clock::single().seconds(); }

} // namespace xronos

#endif//TIME_H