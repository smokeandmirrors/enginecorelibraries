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

#include "Build.h"

#include "math.h"

typedef ulong cycle;
typedef dreal millicycle;
typedef dreal millisecond;
typedef dreal second;

namespace realTime
{
/** cycles per second */
extern const cycle	
	hertz; 
/** seconds per cycle */
extern const second	
	hertzInverse;
/** cycles per millisecond */
extern const millicycle 
	milliHz;
/** millisecond per cycle*/
extern const millisecond 
	milliHzInverse;
	
/** real time in cycles since program initialization */
cycle cycles(void);
/** real time in milliseconds since program initialization */
millisecond milliseconds(void);
/** real time in seconds since program initialization */
second seconds(void);

/** \todo split these up by constructor, if they are constructed with with a clock, all of the time is based on that clock calling tick(),
othwerwise, they will operate on the realTime calls directly. */
/** \todo minimize all of the arithmetic here, and remove the divides */
/** \todo make sure all of these values can handle slow motion, reversal of time */
// frame clock, game play/engine clock
class Clock 
{
public:
	virtual ~Clock(void)=0{/*empty*/}
	
	virtual dreal 
		getRate(void) const=0;
	
	/** return the last cycle when this object processed real time */
	virtual cycle
		getTick(void) const=0;

	virtual millisecond 
		milliseconds(void) const=0;
	
	virtual second 
		seconds(void) const=0;
	
	virtual void 
		setRate(dreal rate)=0;

	virtual void	
		tick(void)=0;
}; // Clock

class ClockReal : public Clock 
{
public:
	ClockReal(void)
	: m_currentMilliseconds(0)
	, m_currentSeconds(0)
	, m_rate(1.0)
	, m_tick(realTime::cycles())
	{ /* empty */ }
	
	ClockReal(cycle initialTime)
	: m_currentMilliseconds(0)
	, m_currentSeconds(0)
	, m_rate(1.0)
	, m_tick(initialTime)
	{ /* empty */ }
	
	ClockReal(const ClockReal& clone)
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
		cycle tick = realTime::cycles();
		dreal delta = m_rate * (tick - m_tick);
		m_currentMilliseconds += static_cast<millisecond>(delta * realTime::milliHzInverse); 
		m_currentSeconds += static_cast<second>(delta * realTime::hertzInverse);
		m_tick = tick;
	}

private:
	ClockReal operator=(const ClockReal &);

	millisecond	m_currentMilliseconds;
	second		m_currentSeconds;
	dreal		m_rate;
	cycle		m_tick;
}; // class ClockReal

class ClockRelative : public Clock 
{
public:
	ClockRelative(const Clock& parent)
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
		cycle tick = m_parent->getTick();
		millisecond delta = getRate() * (tick - m_tick);
		m_currentMilliseconds += static_cast<millisecond>(delta * realTime::milliHzInverse); 
		m_currentSeconds += static_cast<second>(delta * realTime::hertzInverse);
		m_tick = tick;
	}
	
protected:
	inline const Clock* getParent(void) const
	{
		return m_parent;
	}

private:
	ClockRelative operator=(const ClockRelative &);

	millisecond	m_currentMilliseconds;
	second		m_currentSeconds;
	dreal		m_rate;
	cycle		m_tick;
	const Clock* m_parent;
}; // class ClockRelative

class Stopwatch
{
public:
	Stopwatch(const Clock& reference)
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
			return static_cast<millisecond>(/* fabs (m_reference.getRate()) * */(m_reference.milliseconds() - m_start)); 
		else
			return static_cast<millisecond>(/* fabs (m_reference.getRate()) * */(m_stop - m_start));
	}

	second seconds(void) const
	{
		if (m_active)
			return static_cast<second>(0.001 * /* fabs (m_reference.getRate()) * */(m_reference.milliseconds() - m_start)); 
		else
			return static_cast<second>(0.001 * /* fabs (m_reference.getRate()) * */(m_stop - m_start));	
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
	
	const Clock& m_reference;
	millisecond m_start;
	millisecond m_stop;
	bool m_active;
}; // class Stopwatch

class Timer 
{
public:
	Timer(const Clock& reference, millisecond maxTime=0.0, millisecond minTime=-1.0, BoolEnum autoReset=BoolEnum_False)
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
		m_resetTime = m_maxTime; /** \todo randomize me */
	}

	second seconds(void) const
	{
		return milliseconds() * 0.001;
	}

	void set(second maxTime, second minTime=-1.0, BoolEnum autoReset=BoolEnum_Unset)
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

} // namespace realTime

#endif//TIME_H