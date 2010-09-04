#include <stdio.h>

#include "CompilerChecks.h"
#include "Sandbox.h"

void Sandbox::play()
{
	printf("Playing in the sandbox!\n");
	CompilerChecks::sizeOfChecks();
}