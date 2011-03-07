#pragma once
#ifndef SCHEDULING_H
#define SCHEDULING_H

#include "Build.h"

namespace multithreading
{

/** 
\todo accept only threadable functions and classes, or make separate job objects?
*/
class ThreadPool
{
public:
	static ThreadPool& single(void);

private:
	ThreadPool(void);
}; // class ThreadPool

} // multithreading

#endif//SCHEDULING_H