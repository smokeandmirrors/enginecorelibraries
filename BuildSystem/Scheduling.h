#pragma once
#ifndef SCHEDULING_H
#define SCHEDULING_H

#include <map>

#include "Build.h"
#include "Signals.h"
#include "Singleton.h"
#include "Synchronization.h"
#include "Concurrency.h"
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
/**
\todo Scheduler Todo List:
1 use events or some other thing to free up the creation of the threads ahead of time?
2 set ideal processor at job execution time
3 wait on completion of all jobs?
4 Write a scheduler, if not MT testing suite to allow for safe running and modification
of this file
*/


public:
	void 
	enqueue(Executor& executable, cpuID preferredCPU=noCPUpreference);

	void
	enqueueAndWait(Executor& executable, cpuID preferredCPU=noCPUpreference); // , bool waitOnChildren=false);

	void
	enqueueAndWaitOnChildren(Executor& executable, cpuID preferredCPU=noCPUpreference);
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

	std::map<threadID, std::vector<Thread*>* >
		m_childThreadsByOriginalID;

	std::map<threadID, std::vector<Job*>*>
		m_childJobsByOriginalID;

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