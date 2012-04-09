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

/** \todo set ideal processor at job execution time */

#define unspecifiedPriority 0

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
	typedef uint SchedulePriority;
	

public: 
	class Input
	{
	public:
		Input(Executor& inExecutable, cpuID inPreferredCPU=noCPUpreference, SchedulePriority inPriority=unspecifiedPriority)
			: executable(&inExecutable)
			, preferredCPU(inPreferredCPU)
			, priority(inPriority)
		{ /* empty */ }

	private:
		friend class Dispatcher;
		Executor* executable;
		cpuID preferredCPU;
		SchedulePriority priority;
	}; // Dispatcher::Input

	typedef std::vector<Dispatcher::Input> InputQueue;
	typedef std::vector<Dispatcher::Input>::iterator InputQueueIterator;

	void enqueue(Dispatcher::Input& work);
	void enqueue(Dispatcher::InputQueue& work);
	void enqueueAndWait(Dispatcher::Input& work);
	void enqueueAndWait(Dispatcher::InputQueue& work);
	void enqueueAndWaitOnChildren(Dispatcher::Input& work);
	void enqueueAndWaitOnChildren(Dispatcher::InputQueue& work);
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
	void accountForWaitedOnThreadCompletion(Thread::Tree* children);
	bool getFreeIndex(cpuID& index);
	bool getFreeIndex(cpuID& available, cpuID idealCPU);
	void initializeAndTrackJob(Dispatcher::Input& work, Thread::Tree* children);
	void initializeNumberSystemThreads(void);
	bool isAnyIndexFree(void) const;	
	bool isAnyJobPending(void) const;
	bool isOriginalWaitingOnThread(threadID childID, threadID* originalID=NULL) const;
	void startJobs(void);
	const std::string toStringActiveJob(Job* job) const;
	const std::string toStringInactiveJob(void) const;
	
	std::map<threadID, threadID> m_originalByChildren;
	std::map<threadID, Thread::Tree* > m_childrenByOriginal;
	std::vector<Job*> m_activeJobs;
	uint m_maxThreads;
	uint m_numActiveJobs;
	uint m_numSystemThreads;
	signals::ReceiverMember	m_receiver;
	PendingJobQueue* m_pendingJobs;
	DECLARE_MUTEX(m_mutex);
}; // class Dispatcher
} // namespace concurrency
#endif//SCHEDULING_H