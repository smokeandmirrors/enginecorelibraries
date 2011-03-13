#pragma once
#ifndef TIME_H
#define TIME_H
/**
\file Time.h

\todo investigate OS vs. C std library time functions.
*/
#include "Build.h"

typedef uint8 clock_tick;
typedef uint8 millisecond;
typedef real4 second;

namespace real_time
{

void			initialize(void);
millisecond		milliseconds(void);
second			seconds(void);
void			tick(void);

} // namespace time

#endif//TIME_H