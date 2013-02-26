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

class Second;
class Millisecond;

// class CustomNumber<T>;
// Second CustomNumber<second>, specialize some conversion

template<typename TYPE>
class Unit
{
public:


private:
	TYPE value;
}; // template<typename VALUE> class Value


/** \todo finish and use these! */
class Millisecond
{
	friend class Second;

public:
	inline Millisecond(const Second&);
	inline Millisecond(const millisecond&);
	
	inline Millisecond operator+(const Millisecond&) const;
	inline Millisecond operator++();
	inline Millisecond operator++(int);
	inline Millisecond& operator+=(const Millisecond&);

	inline Millisecond operator-(const Millisecond&) const;
	inline Millisecond operator--();
	inline Millisecond operator--(int);
	inline Millisecond& operator-=(const Millisecond&);

	inline Millisecond operator/(const Millisecond&) const;
	inline Millisecond& operator/=(const Millisecond&);

	inline Millisecond operator*(const Millisecond&) const;
	inline Millisecond& operator*=(const Millisecond&);

	inline Millisecond operator-(void);

	
private:
	millisecond value;
}; // class Millisecond

class Second
{
	friend class Millisecond;

public:
	inline Second(const Millisecond&);
	inline Second(const second&);

	inline Second operator+(const Second&) const;
	inline Second operator++();
	inline Second operator++(int);
	inline Second& operator+=(const Second&);

	inline Second operator-(void);

	inline Millisecond operator+(void);
	
private:
	second value;
}; // class Second

namespace xronos
{

	/** \todo why would I ever refer to these polymorphically? */
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
class SystemClock 
	: public designPatterns::Singleton<SystemClock>
{
	friend class designPatterns::Singleton<SystemClock>;

public:	
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
	millisecond milliseconds(void) const;
	void reset(void);
	second seconds(void) const;

protected:
	static SystemClock* createSingleton(void) { return new SystemClock(); }

private:
	cycle cycleZero;
	
	SystemClock(void);

	cycle getCurrentCycle(void) const;
}; // class SystemClock

class Clock
{
public:
	Clock(void)
	: m_currentMilliseconds(0)
	, m_currentSeconds(0)
	, m_rate(1.0)
	, m_tick(xronos::SystemClock::single().cycles())
	{ /* empty */ }
	
	Clock(cycle initialTime)
	: m_currentMilliseconds(0)
	, m_currentSeconds(0)
	, m_rate(1.0)
	, m_tick(initialTime)
	{ /* empty */ }
	
	Clock(const Clock& clone)
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
		cycle tick = xronos::SystemClock::single().cycles();
		cycle delta = tick - m_tick;
		m_currentMilliseconds += static_cast<millisecond>(m_rate * (delta * xronos::SystemClock::single().milliHzInverse)); 
		m_currentSeconds = m_currentMilliseconds * 0.001;
		m_tick = tick;
	}

private:
	Clock operator=(const Clock &);

	millisecond	m_currentMilliseconds;
	second		m_currentSeconds;
	dreal		m_rate;
	cycle		m_tick;
}; // class Clock

template<typename PARENT>
class RelativeClock
{
public:
	RelativeClock(const PARENT& parent)
		: m_currentMilliseconds(0)
		, m_currentSeconds(0)
		, m_rate(parent.getRate())
		, m_tick(parent.getTick())
		, m_parent(parent)
	{ /* empty */ }

	RelativeClock(const RelativeClock& clone)
		: m_currentMilliseconds(clone.milliseconds())
		, m_currentSeconds(clone.seconds())
		, m_rate(clone.getRate())
		, m_tick(clone.getTick())
		, m_parent(clone.getParent())
	{ /* empty */ }

	dreal getRate(void) const 
	{ 
		return m_parent.getRate() * m_rate; 
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
		cycle tick = m_parent.getTick();
		cycle delta = tick - m_tick;
		m_currentMilliseconds += static_cast<millisecond>(getRate() * (delta * xronos::SystemClock::single().milliHzInverse)); 
		m_currentSeconds = m_currentMilliseconds * 0.001;
		m_tick = tick;
	}
	
protected:
	inline const PARENT& getParent(void) const
	{
		return m_parent;
	}

private:
	RelativeClock operator=(const RelativeClock &);

	millisecond	m_currentMilliseconds;
	second		m_currentSeconds;
	dreal		m_rate;
	cycle		m_tick;
	const PARENT& m_parent;
}; // class RelativeClock

template<typename CLOCK>
class Stopwatch
{
public:
	Stopwatch(const CLOCK& reference)
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

	void reset(void)
	{
		m_start = m_reference.milliseconds();
		m_stop = m_start;
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
		
private:
	Stopwatch(void);
	Stopwatch(const Stopwatch&);
	Stopwatch operator=(const Stopwatch&);
	
	const CLOCK& m_reference;
	millisecond m_start;
	millisecond m_stop;
	bool m_active;
}; // class Stopwatch

template<typename CLOCK>
class Timer 
{
public:
	Timer(const CLOCK& reference, millisecond maxTime=0.0, millisecond minTime=-1.0, BoolEnum autoReset=BoolEnum_False)
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

			if (m_autoReset && !timeRemains)
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
			
			if (timeIsUp && m_autoReset)
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
	
	Stopwatch<CLOCK> m_stopwatch;
	bool		m_autoReset;
	millisecond	m_maxTime;
	millisecond	m_minTime;
	millisecond	m_resetTime;
}; // class Timer

class Throttler
{
public:
protected:
private:
}; // class Throttler

// \todo, remove these (currently needed for unit tests)
inline cycle cycles(void) { return SystemClock::single().cycles(); }
inline millisecond milliseconds(void) { return SystemClock::single().milliseconds(); }
inline second seconds(void) { return SystemClock::single().seconds(); }

} // namespace xronos


Second::Second(const second& source)
	: value(source)
{
	/* empty */
}

Second::Second(const Millisecond& source)
	: value(source.value * 0.001)
{
	/* empty */
}

Second Second::operator+(const Second& other) const
{
	return Second(value + other.value);
}

Second Second::operator++()
{
	++value;
	return value;
}

Second Second::operator++(int)
{
	Second suffix(value);
	++value;
	return Second(suffix);
}

Second& Second::operator+=(const Second& other)
{
	value += other.value;
	return *this;
}

Millisecond::Millisecond(const millisecond& source)
	: value(source)
{
	/* empty */
}

Millisecond::Millisecond(const Second& source)
	: value(source.value * 1000)
{
	/* empty */
}

Millisecond Millisecond::operator+(const Millisecond& other) const
{
	return Millisecond(value + other.value);
}

Millisecond Millisecond::operator++()
{
	++value;
	return value;
}

Millisecond Millisecond::operator++(int)
{
	millisecond suffix(value);
	++value;
	return Millisecond(suffix);
}

Millisecond& Millisecond::operator+=(const Millisecond& other)
{
	value += other.value;
	return *this;
}



#endif//TIME_H