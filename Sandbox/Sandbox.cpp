#include <stdio.h>
#include <tchar.h>
#include <vector>

#include "Build.h"
#include "CompilerChecks.h"
#include "Sandbox.h"
#include "Threads.h"

bool newThreadIsSuspended(true);
sint crashOnMe(0);
uint delta = 100;
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
	while (true)
	{
		DWORD status = WaitForSingleObject(mutex, 20);
		if (status == WAIT_OBJECT_0)
		{
			sint before;
			getCrashOnMe(before);
			
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
			ReleaseMutex(mutex);
		}
		else
		{
			printf("runnable1 them up didn't get the mutex!\n");
		}
	}
	return 0;
}

uint __stdcall runnable2(void*)
{
	while (true)
	{
		DWORD status = WaitForSingleObject(mutex, 20);
		if (status == WAIT_OBJECT_0)
		{
			sint before;
			getCrashOnMe(before);

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
}

uint __stdcall screwThemUp(void*)
{
	while (true)
	{ 
		DWORD status = WaitForSingleObject(mutex, 20);
		if (status == WAIT_OBJECT_0)
		{
			static bool toggle(false);
			sint value = toggle ? -999999999 : 999999999;
			setCrashOnMe(value);
			toggle = false;
			printf("SCREWED UP!: value...... %d %d\n", value);
			ReleaseMutex(mutex);
		}
		else
		{
			printf("Screw them up didn't get the mutex!\n");
		}
	}
}



void Sandbox::play()
{
	printf("Playing in the sandbox!\n");
	CompilerChecks::sizeOfChecks();

	mutex = CreateMutex(NULL, false, NULL);
	assert(mutex);
	std::vector<HANDLE> threads;
	bool switcher(true);

	for (uint i = 0; i < 100; i++)
	{
		uint thread_id1;
		HANDLE thread = (HANDLE)(_beginthreadex(NULL,  CREATE_SUSPENDED, switcher ? runnable1 : runnable2, NULL, 0, &thread_id1));
		threads.push_back(thread);
		ResumeThread(thread);
		switcher = !switcher;
	}
	
	uint thread_id1;
	HANDLE thread = (HANDLE)(_beginthreadex(NULL,  CREATE_SUSPENDED, screwThemUp, NULL, 0, &thread_id1));
	ResumeThread(thread);
	
	while (newThreadIsSuspended) ;

	for (uint i = 0; i < 100; i++)
	{
		HANDLE thread = threads[i];
		SuspendThread(thread);
		CloseHandle(thread);
	}
}