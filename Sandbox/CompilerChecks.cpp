#include "Build.h"
#include "CompilerChecks.h"

namespace 
{
	struct PlainOldStruct {};
	class PlainOldClass {};
} // namespace

namespace compiler_checks 
{

void sizeOfChecks(void)
{
	size_t pos = sizeof(PlainOldStruct);	// 1
	size_t poc = sizeof(PlainOldClass);		// 1
	size_t pops = sizeof(PlainOldStruct*);	// 4
	size_t pocs = sizeof(PlainOldClass*);	// 4
	size_t total = pos + poc + pops + pocs;
	total = 0;

	bool* build_me(0);
	build_me = 0;
}

} // namespace compiler_checks 