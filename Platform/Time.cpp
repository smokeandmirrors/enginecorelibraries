#include <ctime>
#include <time.h>

#if WIN32
#include <windows.h>
#endif//WIN32

#include "Time.h"
// static CLOCKS_PER_SEC
namespace 
{
inline cycle _getCurrentCycle(void)
{
#if WIN32
	LARGE_INTEGER perf_query;
	IF_DEBUG(sint success = ) QueryPerformanceCounter(&perf_query);
	assert(success);
	return perf_query.QuadPart;
#else
	PREVENT_COMPILE
#endif//WIN32	
} // inline cycle _getCurrentCycle(void)

cycle cycleZero(_getCurrentCycle());

inline cycle _getCycles(void)
{
	return _getCurrentCycle() - cycleZero;
} // inline cycle _getCycles(void)

inline cycle _getSystemHertz(void)
{
#if WIN32
	LARGE_INTEGER perf_query;
	IF_DEBUG(sint success =) QueryPerformanceFrequency(&perf_query);
	assert(success);
	return static_cast<cycle>(perf_query.QuadPart);
#else
	PREVENT_COMPILE
#endif//WIN32	
} // inline cycle _getSystemHertz(void)
} // namespace 

namespace realTime
{
const cycle hertz(_getSystemHertz()); 
const second hertzInverse(1.0 / _getSystemHertz());
const millicycle milliHz(_getSystemHertz() / 1000.0);
const millisecond milliHzInverse(1.0 / (_getSystemHertz() / 1000.0));

void initalizeInternal(cycle& hz, second& inverseHz, millicycle& milliHertz, millisecond& inverseMillihz);

cycle cycles(void)
{
	return _getCycles();
}

millisecond milliseconds(void)
{
	return static_cast<millisecond>(_getCycles()) * milliHzInverse;	
}

second seconds(void)
{
	return static_cast<second>(_getCycles()) * hertzInverse;
}

} // namespace time