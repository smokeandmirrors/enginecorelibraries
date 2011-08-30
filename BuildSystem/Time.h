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
#include "Build.h"

typedef ulong cycle;
typedef dreal millicycle;
typedef dreal millisecond;
typedef dreal second;

namespace real_time
{
/** cycles since initialize() was called */
cycle			cycles(void);
void			initialize(void);
/** cycles per second */
cycle			hertz(void); 
/** cycles per millisecond */
millicycle		millihertz(void);
millisecond		milliseconds(void);
second			seconds(void);

/** \todo split these up by constructor, if they are constructed with with a clock, all of the time is based on that clock calling tick(),
othwerwise, they will operate on the real_time calls directly. */
/** \todo minimize all of the arithmetic here, and remove the divides */
/** \todo make sure all of these values can handle slomotion, reversal of time */

// frame clock, gameplay/engine clock
class Clock 
{
public:
	Clock(void)
	: m_currentMilliseconds(0)
	, m_currentSeconds(0)
	, m_rate(1.0)
	, m_tick(real_time::cycles())
	{ /* empty */ }
	
	Clock(cycle start)
	: m_currentMilliseconds(0)
	, m_currentSeconds(0)
	, m_rate(1.0)
	, m_tick(start)
	{ /* empty */ }
	
	Clock(const Clock& relative_parent)
	: m_currentMilliseconds(relative_parent.milliseconds())
	, m_currentSeconds(relative_parent.seconds())
	, m_rate(relative_parent.getRate())
	, m_tick(relative_parent.getTick())
	{ /* empty */ }
	
	inline dreal getRate(void) const 
	{ 
		return m_rate; 
	}

	inline millisecond milliseconds(void) const	
	{ 
		return m_currentMilliseconds; 
	}

	inline second seconds(void) const
	{
		return m_currentSeconds;
	}
	
	inline void setRate(dreal rate)
	{
		m_rate = rate;
	}

	inline void	tick(void)
	{
		cycle tick = real_time::cycles();
		dreal delta = m_rate * (tick - m_tick);
		m_currentMilliseconds += static_cast<millisecond>(delta / real_time::millihertz()); 
		m_currentSeconds += static_cast<second>(delta / real_time::hertz());
		m_tick = tick;
	}

protected:
	inline cycle getTick(void) const 
	{ 
		return m_tick; 
	}

private:
	Clock operator=(const Clock &);

	millisecond	m_currentMilliseconds;
	second		m_currentSeconds;
	dreal		m_rate;
	cycle		m_tick;
}; // class Clock

class StopWatch 
{
public:
	StopWatch(dreal rate=1.0)
	: m_active(true)
	, m_start(real_time::cycles())
	, m_stop(m_start)
	, m_rate(rate)
	{ /* empty */ }
	
	StopWatch(const Clock& reference_frame)
	: m_active(true)
	, m_start(real_time::cycles())
	, m_stop(m_start)
	, m_rate(reference_frame.getRate())
	{ /* empty */ }
	
	inline dreal getRate(void) const 
	{ 
		return m_rate; 
	}

	inline millisecond milliseconds(void) const	
	{ 
		if (m_active)
			return static_cast<millisecond>((m_rate * (real_time::cycles() - m_start)) / real_time::millihertz()); 
		else
			return static_cast<millisecond>((m_rate * (m_stop - m_start)) / real_time::millihertz());
	}

	inline second seconds(void) const
	{
		if (m_active)
			return static_cast<second>((m_rate * (real_time::cycles() - m_start)) / real_time::hertz());	
		else
			return static_cast<second>((m_rate * (m_stop - m_start)) / real_time::hertz());	
	}

	inline void start(void)
	{
		m_active = true;
	}

	inline void stop(void)
	{
		m_stop = real_time::cycles();
		m_active = false;
	}

	inline void reset(void)
	{
		m_start = real_time::cycles();
		m_stop = m_start;
	}
	
private:
	StopWatch(const StopWatch& relative_parent);
	StopWatch operator=(const StopWatch&);
	
	bool		m_active;
	const dreal	m_rate;
	cycle		m_start;
	cycle		m_stop;
}; // class StopWatch

class Timer 
{
public:
	Timer(const dreal rate=1.0, second max_time=0.0, second min_time=-1.0, bool auto_reset=false)
	: m_autoReset(auto_reset)
	, m_maxTime(max_time)
	, m_minTime(min_time == -1.0 ? max_time : min_time)
	, m_rate(rate)
	{
		reset();
	}

	inline void reset(void)
	{
		m_startTime = real_time::seconds();
		m_resetTime = m_maxTime; /** \todo: randomize me */
	}
	
	inline void set(second max_time, second min_time=-1.0, bool auto_reset=false)
	{
		m_maxTime = max_time;
		m_minTime = min_time == -1.0 ? max_time : min_time;
		m_autoReset = auto_reset;
	}
	
	inline bool timeIsUp(void) 
	{
		bool time_passed = getTimePassed() >= m_resetTime;
		
		if (m_autoReset)
		{
			reset();
		}
		
		return time_passed;
	}

	inline bool timeRemains(void)
	{
		bool time_passed = getTimePassed() < m_resetTime;
		
		if (m_autoReset)
		{
			reset();
		}
		
		return time_passed;
	}

protected:
	inline second getTimePassed(void) const
	{
		return m_rate * (real_time::seconds() - m_startTime); 
	}

private:
	Timer(const Timer& relative_parent);
	Timer operator=(const Timer&);

	bool		m_autoReset;
	second		m_maxTime;
	second		m_minTime;
	const dreal	m_rate;
	second		m_resetTime;
	second		m_startTime;
}; // class Timer

} // namespace real_time

// namespace frame_time ? engine_time
// namespace game_time ?
// OR, time objects created by the real_time ns?

#endif//TIME_H