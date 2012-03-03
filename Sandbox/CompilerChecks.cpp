#include <stdio.h>

#include "Platform.h"
#include "CompilerChecks.h"



template<typename ELEMENT, typename IS_EQUAL=isEqual<ELEMENT>, typename IS_GREATER=isGreater<ELEMENT>, typename IS_LESS=isLess<ELEMENT>>
class CompileMe
{
public:
	void doSomething(void) { printf("Hello, world."); }

	ELEMENT m_element;
	IS_EQUAL m_isEqual;
	IS_GREATER m_isGreater;
	IS_LESS m_isLess;
};

class A
{
	virtual void hello(void) { printf("Hello, I'm A"); }
};

class B : public A
{
	virtual void hello(void) { printf("Hello, I'm B"); }
};

class C 
{
	virtual void hello(void) { printf("Hello, I'm C"); }
};


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

		// CompileMe<sint, isEqual<sint>, isGreater<sint>, isLess<sint> > compileMe;
		CompileMe<sint> compileMe;

		A a;
		B b;
		C c;

		A* pba = &b;
		B* pbb = dynamic_cast<B*>(pba);

		if (pbb)
		{
			printf("hmmm");
		}

		compileMe.doSomething();
	}
} // namespace compilerChecks 