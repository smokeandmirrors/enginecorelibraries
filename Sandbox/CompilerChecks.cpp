#include <stdio.h>

#include "Platform.h"
#include "CompilerChecks.h"

namespace compilerChecks 
{
	void check(void)
	{
		// neat!
		// int int_version = Math<int>::ZERO_TOLERANCE;
		// float float_version = Math<float>::ZERO_TOLERANCE;

		uint high = 2;
		uint low = 1;
		uint m = (high + low) / 2;
		printf("M = %d", m);

	}
} // namespace compilerChecks 