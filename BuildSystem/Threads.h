#pragma once
#ifndef THREADS_H
#define THREADS_H

#include "Build.h"

namespace threading
{
class Runnable 
{
public:
	virtual	~Runnable(void) {/* empty */}
	virtual void	run(void)=0;
}; // class Runnable

/** ? */
class ThreadPool
{
public:
	static ThreadPool& single(void);

private:
	ThreadPool(void);
}; // class ThreadPool

} // threading

#endif//THREADS_H