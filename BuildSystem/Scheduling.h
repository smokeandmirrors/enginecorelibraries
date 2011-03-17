#pragma once
#ifndef SCHEDULING_H
#define SCHEDULING_H

#include "Build.h"
#include "Observation.h"
#include "Singleton.h"
#include "Threads.h"
/**
\warning WORK IN-PROGRESS! 
\note EXPERIMENTAL!  NOT INTENDED FOR USE!
*/
namespace multithreading
{

class PendingJobQueue;

class Scheduler 
: public design_patterns::Singleton<Scheduler>
, public design_patterns::Observer<Thread>
{
	friend class design_patterns::Singleton<Scheduler>;

public:
	/** 
	\todo expose an optional direct callback mechanism for when the job
	is finished 
	*/
	void			enqueue(Executable* job, 
						sint4 ideal_thread=noThreadPreference,
						const sint1* name="un-named");

	/** 
	\todo expose an optional direct callback mechanism for when the job
	is finished 
	*/
	void			enqueue(executableFunction job, 
						sint4 ideal_thread=noThreadPreference,
						const sint1* name="un-named");

	uint4 getMaxThreads(void) const 
	{ 
		return m_maxThreads; 
	}
	
	uint4 getNumberActiveJobs(void) const
	{
		return m_numActiveJobs;
	}
	
	uint4			getNumberPendingJobs(void) const;
	
	uint4 getNumberSystemThreads(void) const	
	{ 
		return m_numSystemThreads; 
	}
	
	bool hasAnyWork(void) const
	{
		return getNumberActiveJobs() || getNumberPendingJobs();
	}

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
	
	void printState(void) const
	{
		std::string output = this->toString();
		printf(output.c_str());
	}

	void			setMaxThreads(uint4 max)			{ m_maxThreads = max; }
	const std::string toString(void) const;
	
protected:
	Scheduler(void);
	~Scheduler(void);
	
	inline void accountForFinish(Thread* job)
	{
		sint4 thread_index = -1;

		for (uint4 i = 0; i < m_numSystemThreads; i++)
		{
			if (m_activeJobs[i] == job)
			{
				thread_index = static_cast<sint4>(i);
				break;
			}
		}

		assert(thread_index != -1);
		m_activeJobs[thread_index] = NULL;
		m_numActiveJobs--;
		printState();
	}

	inline void accountForNewJob(Thread* job, sint4 index)
	{
		m_activeJobs[index] = job;
		m_numActiveJobs++;
		printState();
	}
	
	inline bool getFreeIndex(sint4& index)
	{
		for (uint4 i = 0; i < m_numSystemThreads; i++)
		{
			if (!m_activeJobs[i])
			{
				index = static_cast<sint4>(i);
				return true;
			}
		}

		return false;
	}

	inline bool getOpenThread(sint4& index, sint4 ideal_thread)
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

	void			initializeNumberSystemThreads(void);
	void			startNextJob(void);
	const std::string toStringActiveJob(Thread* job) const;
	const std::string toStringInactiveJob(void) const;
	
private:
	Scheduler(const Scheduler&);
	Scheduler operator=(const Scheduler&);
	
	Thread**				m_activeJobs;
	uint4					m_maxThreads;
	uint4					m_numActiveJobs;
	uint4					m_numSystemThreads;
	design_patterns::ObserverHelper<Thread>* 
							m_observer;
	PendingJobQueue*		m_pendingJobs;
}; // class Scheduler

} // multithreading

#endif//SCHEDULING_H