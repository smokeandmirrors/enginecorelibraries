#pragma once
#ifndef SCHEDULING_H
#define SCHEDULING_H

#include "Build.h"
#include "Observation.h"
#include "Singleton.h"
#include "Threads.h"

namespace multithreading
{

class PendingJobQueue;

class Scheduler 
: public design_patterns::Singleton<Scheduler>
, public design_patterns::Observer<Thread>
{
	friend class design_patterns::Singleton<Scheduler>;

public:
	void enqueue(Executable* job, sint ideal_thread=noThreadPreference);
	void enqueue(executableFunction job, sint ideal_thread=noThreadPreference);
	uint getMaxThreads(void) const			{ return m_maxThreads; }
	uint getMinThreads(void) const			{ return m_minThreads; }
	void getNumberActiveJobs(void);
	void getNumberPendingJobs(void);
	uint getNumberSystemThreads(void) const { return m_numSystemThreads; }
	void ignore(Thread* observable)
	{
		m_observer->ignore(observable);
	}
	void notice(Thread* observable)
	{
		accountForFinish(observable);
		startNextJob();
	}
	void observe(Thread* observable)
	{
		m_observer->observe(observable);
	}
	void setMaxThreads(uint max)			{ m_maxThreads = max; }
	void setMinThreads(uint min)			{ m_minThreads = min; }
	
protected:
	Scheduler(void);
	~Scheduler(void);
	
	inline void accountForFinish(Thread* job)
	{
		sint thread_index = -1;

		for (uint i = 0; i < m_numSystemThreads; i++)
		{
			if (m_activeJobs[i] == job)
			{
				thread_index = static_cast<sint>(i);
				break;
			}
		}

		assert(thread_index != -1);
		m_activeJobs[thread_index] = NULL;
		m_numActiveJobs--;
	}

	inline void accountForNewJob(Thread* job, sint index)
	{
		m_activeJobs[index] = job;
		m_numActiveJobs++;
	}
	
	inline bool getFreeIndex(sint& index)
	{
		for (uint i = 0; i < m_numSystemThreads; i++)
		{
			if (!m_activeJobs[i])
			{
				index = static_cast<sint>(i);
				return true;
			}
		}

		return false;
	}

	inline bool getOpenThread(sint& index, sint ideal_thread)
	{
		if (ideal_thread != noThreadPreference && !m_activeJobs[ideal_thread])
		{
			index = ideal_thread;
			return true;
		}
		else
		{
			return getFreeIndex(index);
		}	
	}

	void initializeNumberSystemThreads(void);
	void startNextJob(void);
	
private:
							Scheduler(const Scheduler&);
							Scheduler operator=(const Scheduler&);
	
	Thread**				m_activeJobs;
	uint					m_maxThreads;
	uint					m_minThreads;
	uint					m_numActiveJobs;
	uint					m_numSystemThreads;
	design_patterns::ObserverHelper<Thread>* m_observer;
	PendingJobQueue*		m_pendingJobs;
}; // class Scheduler

} // multithreading

#endif//SCHEDULING_H