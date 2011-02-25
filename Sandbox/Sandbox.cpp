#include <stdio.h>
#include <tchar.h>
#include <vector>

#include "Build.h"
#include "CompilerChecks.h"
#include "Sandbox.h"
#include "Threads.h"


#if WIN32
#include <process.h>
#include <windows.h>
#endif

bool newThreadIsSuspended(true);
bool childThreadsAreActive(true);
sint crashOnMe(0);
uint delta = 100;
static uint iterations(10000);
HANDLE closedthreadmutex;
uint closedthreads(0);
HANDLE mutex;

void getCrashOnMe(sint& out)
{
	out = crashOnMe;
}

void setCrashOnMe(sint value)
{
	crashOnMe = value;
}

uint __stdcall runnable1(void*)
{
	_endthreadex(0);
	while (childThreadsAreActive)
	{
		DWORD status = WaitForSingleObject(mutex, 20);
		if (status == WAIT_OBJECT_0)
		{
			sint before;
			getCrashOnMe(before);
			iterations++;
			if (iterations > 100)
				childThreadsAreActive = false;
			for (uint i = 0; i < delta; i++)
			{
				int during;
				getCrashOnMe(during); 
				setCrashOnMe(during - 1);
			}
			
			sint after;
			getCrashOnMe(after);
			sint value = before - delta;

			if (value == after)
			{
				printf("DECREMENTOR: equal...... %d %d\n", value, after);
			}
			else
			{
				printf("DECREMENTOR: NOT EQUAL!! %d %d\n", value, after);
			}
			
		}
		else
		{
			printf("runnable1 them up didn't get the mutex!\n");
		}
	}
	while (true)
	{
		DWORD status = WaitForSingleObject(closedthreadmutex, INFINITE);
		if (status == WAIT_OBJECT_0)
		{
			closedthreads++;
			ReleaseMutex(mutex);
			_endthreadex(0);
		}
	}
	
	return 0;
}

uint __stdcall runnable2(void*)
{
	_endthreadex(0);
	while (childThreadsAreActive)
	{
		DWORD status = WaitForSingleObject(mutex, 20);
		if (status == WAIT_OBJECT_0)
		{
			sint before;
			getCrashOnMe(before);
			iterations++;
			if (iterations > 100)
				childThreadsAreActive = false;
			for (uint i = 0; i < delta; i++)
			{
				int during;
				getCrashOnMe(during); 
				setCrashOnMe(during + 1);
			}

			sint after;
			getCrashOnMe(after);
			sint value = before + delta;

			if (value == after)
			{
				printf("INCREMENTOR: equal...... %d %d\n", value, after);
			}
			else
			{
				printf("INCREMENTOR: NOT EQUAL!! %d %d\n", value, after);
			}
			ReleaseMutex(mutex);
		}
		else
		{
			printf("runnable2 them up didn't get the mutex!\n");
		}
	}
	while (true)
	{
		DWORD status = WaitForSingleObject(closedthreadmutex, INFINITE);
		if (status == WAIT_OBJECT_0)
		{
			closedthreads++;
			ReleaseMutex(mutex);
			_endthreadex(0);
		}
	}
	return 0;
}

uint __stdcall screwThemUp(void*)
{
	_endthreadex(0);
	while (childThreadsAreActive)
	{ 
		DWORD status = WaitForSingleObject(mutex, INFINITE);
		if (status == WAIT_OBJECT_0)
		{
			
			static bool toggle(false);
			sint value = toggle ? -999999999 : 999999999;
			setCrashOnMe(value);
			toggle = false;
			printf("SCREWED UP!: value...... %d %d\n", value);
			iterations++;
			if (iterations > 100)
				childThreadsAreActive = false;
			ReleaseMutex(mutex);
		}
		else
		{
			printf("Screw them up didn't get the mutex!\n");
		}
	}
	while (true)
	{
		DWORD status = WaitForSingleObject(closedthreadmutex, INFINITE);
		if (status == WAIT_OBJECT_0)
		{
			closedthreads++;
			ReleaseMutex(mutex);
			_endthreadex(0);
		}
	}
	return 0;
}

void threadsChecking()
{
	mutex = CreateMutex(NULL, false, NULL);
	assert(mutex);
	std::vector<HANDLE> threads;
	bool switcher(true);

	
	for (uint i = 0; i < 100; i++)
	{
		uint thread_id1;
		HANDLE thread = (HANDLE)(_beginthreadex(NULL, 0, switcher ? runnable1 : runnable2, NULL, CREATE_SUSPENDED, &thread_id1));
		threads.push_back(thread);
		ResumeThread(thread);
		switcher = !switcher;
	}

	uint thread_id1;
	HANDLE s_thread = (HANDLE)(_beginthreadex(NULL, 0, screwThemUp, NULL, CREATE_SUSPENDED, &thread_id1));
	ResumeThread(s_thread);

	// while (closedthreads != 101) ;

	for (uint i = 0; i < 100; i++)
	{
		HANDLE thread = threads[i];
		CloseHandle(thread);
	}

	CloseHandle(s_thread);
}

void Sandbox::play()
{
	printf("Playing in the sandbox!\n");
	CompilerChecks::sizeOfChecks();
	threadsChecking();
}