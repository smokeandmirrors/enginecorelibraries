#pragma once
#ifndef TIME_H
#define TIME_H
/**
\file Time.h

\todo investigate OS vs. C std library time functions.
*/
#include "Build.h"

typedef ulong clock_tick;
typedef ulong millisecond;
typedef float second;

namespace real_time
{

void			initialize(void);
millisecond		milliseconds(void);
second			seconds(void);
void			tick(void);

} // namespace time

#endif//TIME_H