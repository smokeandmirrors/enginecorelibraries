#pragma once
#ifndef TIME_H
#define TIME_H
/**
\file Time.h

\todo investigate OS vs. C std library time functions.
*/
#include "Build.h"

typedef uint8 cycle;
typedef real8 millicycle;
typedef real8 millisecond;
typedef real8 second;

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

// frame clock, gameplay/engine clock
class Clock 
{
public:
	Clock(void)
	: m_currentMilliseconds(0)
	, m_currentSeconds(0)
	, m_rate(1.0)
	, m_tick(real_time::cycles())
	{
		/* empty */
	}

	Clock(cycle start)
	: m_currentMilliseconds(0)
	, m_currentSeconds(0)
	, m_rate(1.0)
	, m_tick(start)
	{
		/* empty */
	}

	Clock(const Clock& relative_parent)
	: m_currentMilliseconds(relative_parent.milliseconds())
	, m_currentSeconds(relative_parent.seconds())
	, m_rate(relative_parent.getRate())
	, m_tick(relative_parent.getTick())
	{
		/* empty */
	}
	
	inline real8 getRate(void) const 
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
	
	inline void setRate(real8 rate)
	{
		m_rate = rate;
	}

	inline void	tick(void)
	{
		cycle tick = real_time::cycles();
		real8 delta = m_rate * (tick - m_tick);
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
	real8		m_rate;
	cycle		m_tick;
}; // class Clock


class StopWatch 
{
public:
	StopWatch(real8 rate=1.0)
	: m_active(true)
	, m_start(real_time::cycles())
	, m_stop(m_start)
	, m_rate(rate)
	{
		/* empty */
	}

	StopWatch(const Clock& reference_frame)
	: m_active(true)
	, m_start(real_time::cycles())
	, m_stop(m_start)
	, m_rate(reference_frame.getRate())
	{
		/* empty */
	}

	inline real8 getRate(void) const 
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
	const real8	m_rate;
	cycle		m_start;
	cycle		m_stop;
}; // class StopWatch

} // namespace real_time

// namespace frame_time ? engine_time
// namespace game_time ?
// OR, time objects created by the real_time ns?

#endif//TIME_H