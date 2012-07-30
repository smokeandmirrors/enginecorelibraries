#pragma once
#ifndef SCHEDULING_H
#define SCHEDULING_H

#include <map>
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
class Dispatcher 
: public designPatterns::Singleton<Dispatcher>
{
	class Job;
	class PendingJobQueue;
	friend class designPatterns::Singleton<Dispatcher>;
	
public: 
	void enqueue(Thread::ExecutableQueue& work);
	void enqueueAndWait(Thread::ExecutableQueue& work);
	void enqueueAndWaitOnChildren(Thread::ExecutableQueue& work);
	uint getMaxThreads(void) const;
	uint getNumberActiveJobs(void) const;
	uint getNumberPendingJobs(void) const;
	uint getNumberSystemThreads(void) const;
	void printState(void) const;
	void setMaxThreads(uint max);
	const std::string toString(void) const;

protected:
	static Dispatcher* createSingleton(void) { return new Dispatcher; /* no dependencies */ } 

private:
	Dispatcher(void);
	~Dispatcher(void);
	Dispatcher(const Dispatcher&);
	Dispatcher operator=(const Dispatcher&);

	void accountForFinish(Job* finished);
	void accountForStartedJob(Job* started, cpuID index);
	void addAndStartJobs(Thread::ExecutableQueue& work);
	bool getFreeIndex(cpuID& index);
	bool getFreeIndex(cpuID& available, cpuID idealCPU);
	void initializeNumberSystemThreads(void);
	bool isAnyIndexFree(void) const;	
	bool isAnyJobPending(void) const;
	void startJobs(void);
	const std::string toStringActiveJob(Job* job) const;
	const std::string toStringInactiveJob(void) const;
	
	std::vector<Job*> m_activeJobs;
	signals::ReceiverMember	m_receiver;
	uint m_maxThreads;
	uint m_numActiveJobs;
	uint m_numSystemThreads;
	PendingJobQueue* m_pendingJobs;
	DECLARE_MUTEX(m_mutex);
}; // class Dispatcher
} // namespace concurrency

#endif//SCHEDULING_H