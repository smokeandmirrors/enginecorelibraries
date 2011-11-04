#pragma once
#ifndef SCHEDULING_H
#define SCHEDULING_H

#include "Build.h"
#include "Signals.h"
#include "Singleton.h"
#include "Synchronization.h"
#include "Multithreading.h"
/**
<DEVELOPMENT STATUS>
Current Draft		:	0.0
Current Phase		:   DEVELOPMENT
Purpose				:	DEPLOYMENT
Unit Tested			:	NO
Used in development	:	NO
Used in experiments :	YES
Tested in the field	:	NO
*/

namespace multithreading
{

class Thread;

/** 
a class that handles processing concurrent execution
of threads 
 */
class Scheduler 
: public designPatterns::Singleton<Scheduler>
{
	class Job;
	class PendingJobQueue;
	friend class designPatterns::Singleton<Scheduler>;

public:
	void 
		enqueue(Executor& executable, cpuID preferredCPU=noCPUpreference);

	void
		enqueueAndWait(Executor& executable, cpuID preferredCPU=noCPUpreference);
/*
	void 
		enqueue(std::vector<Job*>& job);

	void 
		enqueueAndWait(std::vector<Job*>& job);
*/
	uint 
		getMaxThreads(void) const;
	
	uint 
		getNumberActiveJobs(void) const;
	
	uint 
		getNumberPendingJobs(void) const;
	
	uint 
		getNumberSystemThreads(void) const;
	
	bool 
		hasAnyWork(void) const;
			
	void 
		printState(void) const;
	
	void 
		setMaxThreads(uint max);
	
	const std::string 
		toString(void) const;
	
protected:
	Scheduler(void);
	~Scheduler(void);
	
	void 
		accountForFinish(Job* finished);

	void 
		accountForStartedJob(Job* started, cpuID index);
	
	bool 
		getFreeIndex(cpuID& index);
	
	bool 
		getFreeIndex(cpuID& available, cpuID idealCPU);

	void
		initializeNumberSystemThreads(void);

	bool 
		isAnyIndexFree(void) const;
	
	bool
		isAnyJobPending(void) const;
	
	void
		startJobs(void);
	
	const std::string 
		toStringActiveJob(Job* job) const;
	
	const std::string 
		toStringInactiveJob(void) const;
	
private:
	Scheduler(const Scheduler&);
	Scheduler operator=(const Scheduler&);
	
	/** \todo

	std::vector<HardwareThreads> m_threads;

	class HardwareThread
	{
		Thread* m_softwareThread;
		DECLARE_MUTEX(m_mutex);
	}
	*/


	std::vector<Job*>		
		m_activeJobs;
	
	uint 
		m_maxThreads;
	
	uint 
		m_numActiveJobs;
	
	uint
		m_numSystemThreads;
	
	signals::ReceiverMember	
		m_receiver;
	
	PendingJobQueue*		
		m_pendingJobs;
	
	DECLARE_MUTEX(m_mutex);
}; // class Scheduler

} // multithreading

#endif//SCHEDULING_H