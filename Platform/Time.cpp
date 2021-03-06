#include <ctime>
#include <time.h>

#if WIN32
#include <windows.h>
#include <intrin.h>
#pragma intrinsic(__rdtsc)
#endif//WIN32

#include "Time.h"

namespace 
{
#if WIN32
	inline cycle _getCycleCPU(void)
	{
		return __rdtsc();
	}

	inline cycle _getCycleOS(void)
	{
		LARGE_INTEGER perf_query;
		IF_DEBUG(sint success = ) QueryPerformanceCounter(&perf_query);
		assert(success);
		return perf_query.QuadPart;
	}

	inline cycle _initilializeFrequency(dreal* returnMinFactor=NULL)
	{
		cycle osFrequency(0);
		IF_DEBUG(cycle osFrequencyPrevious(0);)
		cycle cpuTicks1;
		cycle cpuTicks2;
		cycle osTicks1;
		cycle osTicks2;
		dreal minFactor = 1e20;

		for (uint i = 0; i < 100; i++)
		{
			cpuTicks1 = _getCycleCPU();
			osTicks1 = _getCycleOS();
			// spin
			volatile int x(1); for (int j(0); j < 50000; j++) x += x * x;
			--x;
			cpuTicks2 = _getCycleCPU();
			osTicks2 = _getCycleOS();

			IF_DEBUG(sint success =) QueryPerformanceFrequency((LARGE_INTEGER*)&osFrequency);
			IF_DEBUG
			( 
				assert(success);
				if (i == 0)
					osFrequencyPrevious = osFrequency;
				else
					assert(osFrequencyPrevious == osFrequency);
			)

			cycle cpuDelta(cpuTicks2 - cpuTicks1);
			cycle osDelta(osTicks2 - osTicks1);

			dreal factor(static_cast<dreal>(cpuDelta)/static_cast<dreal>(osDelta));

			if (factor < minFactor)
			{
				minFactor = factor;
			}
		}

		if (returnMinFactor)
		{
			*returnMinFactor = minFactor;
		}
		
		return static_cast<cycle>(static_cast<cycle>(osFrequency) * minFactor);
	} // inline cycle _initilializeFrequency(void)

#else
#error unsupported precision time platform
#endif//WIN32	
} // namespace 

xronos::SystemClock::SystemClock(void)
: hertz(_initilializeFrequency())
, hertzInverse(static_cast<const second>(static_cast<slong>(1)) / static_cast<const second>(static_cast<slong>((hertz))))
, milliHz(hertz / 1000)
, milliHzInverse(static_cast<const millisecond>(static_cast<slong>(1000)) / static_cast<const millisecond>(static_cast<slong>((hertz))))
, cycleZero(getCurrentCycle())
{
	/* empty */

	dreal factor1, factor2, factor3, factor4, factor5;
	cycle frequency1 = _initilializeFrequency(&factor1);
	cycle frequency2 = _initilializeFrequency(&factor2);
	cycle frequency3 = _initilializeFrequency(&factor3);
	cycle frequency4 = _initilializeFrequency(&factor4);
	cycle frequency5 = _initilializeFrequency(&factor5);
	// assert(frequency1 == frequency2 == frequency3 == frequency4 == frequency5);
}

cycle xronos::SystemClock::getCurrentCycle(void) const
{
	return _getCycleCPU();
} 

millisecond xronos::SystemClock::milliseconds(void) const
{
	return cycles() * milliHzInverse;
}

void xronos::SystemClock::reset(void)
{ 
	cycleZero = getCurrentCycle(); 
}

second xronos::SystemClock::seconds(void) const
{
	return milliseconds() * 1000;
}

DEFINE_SINGLETON_NS(SystemClock, xronos)
