#include <ctime>
#include <time.h>

#include "Time.h"
// static CLOCKS_PER_SEC
namespace real_time
{
const real8 cyclesToSeconds			(static_cast<real8>(1.0) / static_cast<real8>(CLOCKS_PER_SEC));
const real8 cyclesToMilliseconds		(static_cast<real8>(1000.0) / static_cast<real8>(CLOCKS_PER_SEC));

time_t			appCalendarStart;
millisecond		appMillisecondsCurrent	(0);
second			appSecondsCurrent		(0);

inline clock_tick clockTicks(void)
{
	return clock();
} // clock_tick clockTicks(void)

void initialize(void)
{
	time(&appCalendarStart);
}

millisecond milliseconds(void)
{
	return appMillisecondsCurrent;
}

second seconds(void)
{
	return appSecondsCurrent;
}

void tick(void)
{
	/* time_t method
	time_t current;
	time(&current);
	real8 delta = difftime(current, appCalendarStart);
	appMillisecondsCurrent = static_cast<millisecond>(delta * 1000.0f);
	appSecondsCurrent = static_cast<second>(delta);
	*/
	// clock() method
	clock_tick cycles = clockTicks();
	appMillisecondsCurrent = static_cast<millisecond>(cycles * cyclesToMilliseconds);
	appSecondsCurrent = static_cast<second>(cycles * cyclesToSeconds);
}

} // namespace time