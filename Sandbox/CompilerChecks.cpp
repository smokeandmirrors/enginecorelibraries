#include <stdio.h>

#include "Build.h"
#include "CompilerChecks.h"

class Interface
{
public:
	virtual void poop(void) const=0;
};

class Interface2
{
public:
	virtual void poop2(void) const=0;
};

class Things2Implementer : public Interface
{
public:
	void poop(void) const { printf("poop!\n'"); }
	void poop2(void) const { printf("poop!\n'"); }

	int thingOne;
	int thingTwo;
};

class Things2 
{
public:
	void poop(void) const { printf("poop!\n'"); }

	int thingOne;
	int thingTwo;
};

class vThings2
{
public:
	virtual void poop(void) const { printf("poop!\n'"); }
	int thingOne;
	int thingTwo;
};

namespace compiler_checks 
{
	void check(void)
	{
		size_t sizeof2TI = sizeof(Things2Implementer);
		size_t sizeof2T = sizeof(Things2);
		size_t sizeofv2t = sizeof(vThings2);
		size_t sum = sizeof2TI + sizeof2T + sizeofv2t;
	}
} // namespace compiler_checks 