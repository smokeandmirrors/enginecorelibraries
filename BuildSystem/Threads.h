#pragma once
#ifndef THREADS_H
#define THREADS_H

#include "Build.h"

namespace threading
{
// #if WIN32
// /** 
// todo, these themselves might have to be hidden behind even smaller classes for
// better cross-platform use
// */
// typedef uint			threadID;
// typedef uint __stdcall (*thread_function)(void*);
// typedef HANDLE			thread_resource;
// #endif//WIN32
// 
// class Runnable 
// {
// public:
// 	virtual			~Runnable(void) {/* empty */}
// 	virtual void	run(void)=0;
// }; // class Runnable
// 
// /** 
// should be an observer or something, there needs to be a way
// of notifying the thread of the Runnable's destruction 
// */
// class Thread
// {
// public:
// 	Thread(Runnable* runnable);
// 	Thread(void(*runnable)(void));
// 	~Thread(void);
// 	bool			start();
// 	// below are deprecated in Java, but remain in C++
// 	// void	stop();
// 	// void	resume();
// 
// protected:
// 	void			destroyResource();
// 	void			runFunction();
// 
// private:
// 	/** one inner class for the Runnable*, one for the void(*)(void); */
// 	void(*			m_function)(void);
// 	threadID		m_id;
// 	Runnable*		m_object;
// 	slong			m_suspensionCount;
// 	thread_resource	m_thread;
// }; // class Thread
// 
// /** ? */
// class ThreadPool
// {
// 
// }; // class ThreadPool

} // threading

#endif//THREADS_H