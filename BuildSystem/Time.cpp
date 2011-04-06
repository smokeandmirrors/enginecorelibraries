#include <ctime>
#include <time.h>

#if WIN32
#include <windows.h>
#endif//WIN32

#include "Time.h"
// static CLOCKS_PER_SEC
namespace 
{

bool		system_is_initialized(false);
cycle		systemCycleStart;
cycle		systemHertz;
millicycle	systemMillihertz;

inline cycle getCycles(void)
{
	assert(system_is_initialized);
#if WIN32
	LARGE_INTEGER perf_query;
#if DEBUG
	int success = QueryPerformanceCounter(&perf_query);
	assert(success);
#else
	QueryPerformanceCounter(&perf_query);
#endif//DEBUG
	return perf_query.QuadPart - systemCycleStart;
#else
	PREVENT_COMPILE
#endif//WIN32	
} // inline cycle getCycles(void)

} // namespace 

namespace real_time
{

cycle cycles(void)
{
	assert(system_is_initialized);
	return getCycles();
}

cycle hertz(void)
{
	assert(system_is_initialized);
	return systemHertz;
}

void initialize(void)
{
	if (system_is_initialized)
		return;
#if WIN32
	LARGE_INTEGER perf_query;
	int success = QueryPerformanceCounter(&perf_query);
	assert(success);
	systemCycleStart = perf_query.QuadPart;
	success = QueryPerformanceFrequency(&perf_query);
	assert(success);
	systemHertz = static_cast<cycle>(perf_query.QuadPart);
	systemMillihertz = static_cast<millicycle>(systemHertz) / static_cast<millicycle>(1000);
#else
	PREVENT_COMPILE
#endif//WIN32	
	system_is_initialized = true;
}

millicycle millihertz(void)
{
	assert(system_is_initialized);
	return systemMillihertz;
}

millisecond milliseconds(void)
{
	assert(system_is_initialized);
	return static_cast<millisecond>(getCycles()) / static_cast<millisecond>(systemMillihertz);	
}

second seconds(void)
{
	assert(system_is_initialized);
	return static_cast<second>(getCycles()) / static_cast<second>(systemHertz);
}

} // namespace time