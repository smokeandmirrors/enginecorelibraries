#pragma once
#ifndef SCHEDULING_H
#define SCHEDULING_H

#include <map>
#include <queue>
#include <vector>

#include "Concurrency.h"
#include "Platform.h"
#include "Signals.h"
#include "Singleton.h"
#include "Synchronization.h"
#include "Thread.h"

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

namespace concurrency
{

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
/**
\todo Scheduler Todo List:
1 use events or some other thing to free up the creation of the threads ahead of time?
2 set ideal processor at job execution time
*/


public:
	void 
	enqueue(Executor& executable, cpuID preferredCPU=noCPUpreference);

	void 
	enqueue(std::queue<Executor*>& work);
	
	void
	enqueueAndWait(Executor& executable, cpuID preferredCPU=noCPUpreference); // , bool waitOnChildren=false);

	void 
	enqueueAndWait(std::queue<Executor*>& work);
	
	void
	enqueueAndWaitOnChildren(Executor& executable, cpuID preferredCPU=noCPUpreference);
	
	void 
	enqueueAndWaitOnChildren(std::queue<Executor*>& work);

	uint 
	getMaxThreads(void) const;
	
	uint 
	getNumberActiveJobs(void) const;
	
	uint 
	getNumberPendingJobs(void) const;
	
	uint 
	getNumberSystemThreads(void) const;
			
	void 
	printState(void) const;
	
	void 
	setMaxThreads(uint max);
	
	const std::string 
	toString(void) const;
	
private:
	Scheduler(void);
	~Scheduler(void);
	Scheduler(const Scheduler&);
	Scheduler operator=(const Scheduler&);

	void 
		accountForFinish(Job* finished);

	void 
		accountForStartedJob(Job* started, cpuID index);
	
	void
		accountForWaitedOnThreadCompletion(Thread::Tree* children);

	bool 
		getFreeIndex(cpuID& index);
	
	bool 
		getFreeIndex(cpuID& available, cpuID idealCPU);


	void 
		initializeAndTrackJob(
			Executor& executable,
			cpuID preferredCPU,
			Thread::Tree* children);
	
	void
		initializeNumberSystemThreads(void);

	bool 
		isAnyIndexFree(void) const;
	
	bool
		isAnyJobPending(void) const;
	
	bool 
		isOriginalWaitingOnThread(threadID childID, threadID* originalID=NULL) const;

	void
		startJobs(void);
	
	const std::string 
		toStringActiveJob(Job* job) const;
	
	const std::string 
		toStringInactiveJob(void) const;
	
	std::map<threadID, threadID>
		m_originalByChildren;

	std::map<threadID, Thread::Tree* >
		m_childrenByOriginal;

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
} // concurrency

#endif//SCHEDULING_H