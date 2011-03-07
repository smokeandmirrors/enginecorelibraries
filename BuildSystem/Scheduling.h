#pragma once
#ifndef SCHEDULING_H
#define SCHEDULING_H

#include "Build.h"
#include "Threads.h"

namespace multithreading
{

class Scheduler
{
public:
	static Scheduler& single(void);
	
	void enqueue(Executable* job, sint ideal_thread=-1);
	void enqueue(executableFunction job, sint ideal_thread=-1);
	void getNumberActiveJobs(void);
	void getNumberPendingJobs(void);
	uint getMaxThreads(void) const	{ return m_maxThreads; }
	uint getMinThreads(void) const	{ return m_minThreads; }
	void setMaxThreads(uint max)	{ m_maxThreads = max; }
	void setMinThreads(uint min)	{ m_minThreads = min; }
	
protected:
	uint getNumberSystemThreads(void) const;

private:
	typedef Scheduler& (*schedulerGetter)(void);
	static Scheduler& getInitializedScheduler(void);
	static Scheduler& getUninitializedScheduler(void);
	static Scheduler* singleton;
	static schedulerGetter getScheduler;

	Scheduler(void);
	Scheduler(const Scheduler&);
	Scheduler operator=(const Scheduler&);
	
	uint m_maxThreads;
	uint m_minThreads;
}; // class Scheduler

} // multithreading

#endif//SCHEDULING_H