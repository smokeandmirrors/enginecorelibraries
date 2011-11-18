#pragma once
#ifndef CONCURRENCY_H
#define CONCURRENCY_H

#include "Build.h"
#include "Time.h"

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
#if WIN32

#define ARGS_EXECUTABLE_FUNCTION(name) uint __stdcall name(void* args)
#define NOARGS_EXECUTABLE_FUNCTION(name) uint __stdcall name(void*)

typedef uint(__stdcall*		threadable)(void*);
typedef uint				threadID;
typedef void*				threadHandle;

#else
	PREVENT_COMPILE
#endif//WIN32

#define DECLARE_NOARGS_EXECUTABLE_FUNCTION(name) NOARGS_EXECUTABLE_FUNCTION(name);
#define DEFINE_NOARGS_EXECUTABLE_FUNCTION(name, code) NOARGS_EXECUTABLE_FUNCTION(name) \
	{ \
		code \
		return 0; \
	}

#define DECLARE_ARGS_EXECUTABLE_FUNCTION(name) ARGS_EXECUTABLE_FUNCTION(name);
#define DEFINE_ARGS_EXECUTABLE_FUNCTION(name, code) ARGS_EXECUTABLE_FUNCTION(name) \
	{ \
		code \
		return 0; \
	}

typedef sint cpuID;
typedef void(*	executableFunction)(void);

extern const cpuID noCPUpreference;
extern const threadID invalidThreadID;

void sleep(millisecond milliseconds);

class Executable 
{
public:
	virtual	
		~Executable(void)=0 
	{/* empty */}
	
	virtual void 
		execute(void)=0;

	virtual const std::string&
		toString(void) const=0;
}; // class Executable

class Executor
{
public:
	Executor(executableFunction executable, 
		const std::string& name="un-named")
		: m_name(name)
		, m_implementation(new FunctionImplementation(executable)) 
	{/* empty */}

	Executor(Executable* executable, 
		const std::string& name="un-named")
		: m_name(name)
		, m_implementation(new ObjectImplementation(executable)) 
	{/* empty */}

	~Executor(void) 
	{ 
		delete m_implementation; 
	}

	void 
		execute(void) 
	{ 
		m_implementation->execute(); 
	}

	const std::string&
		toString(void) const
	{
		return m_name;
	}

private:
	class ExecutorImplementation
	{
	public:
		virtual ~ExecutorImplementation() 
		{ /* empty */ }

		virtual void execute(void)=0;
	}; // ExecutorImplementation

	class ObjectImplementation : public ExecutorImplementation
	{
	public:
		ObjectImplementation(Executable* object) 
			: m_object(object) 
		{ /* empty */ }

		void 
			execute(void) 
		{ 
			m_object->execute(); 
		}					

	private:	
		Executable*	m_object;
	}; // class ExecutableExecutor : public Executor

	class FunctionImplementation : public ExecutorImplementation
	{
	public:		
		FunctionImplementation(executableFunction function) 
			: m_function(function) 
		{ /* empty */ }

		void 
			execute(void) 
		{ 
			(*m_function)(); 
		}		

	private:
		executableFunction m_function;
	}; // class FunctionExecutor : public Executor

	std::string
		m_name;

	ExecutorImplementation* 
		m_implementation;
}; // class Executor


}//namespace concurrency

#endif//CONCURRENCY_H