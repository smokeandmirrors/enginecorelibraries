#include <stdio.h>

#include "Platform.h"
#include "CompilerChecks.h"
#include "Synchronization.h"
#include "AuthorTimeRunTimeFactory.h"

using namespace concurrency;

// this macro just makes consistency a bit easier for your class
#define EXAMPLE_HAS_AUTHOR_TIME_STATE true

class Example
{
	// the Factory classes need access to construction and traits
	friend class Factory<Example>;
	friend class FactorySelector<EXAMPLE_HAS_AUTHOR_TIME_STATE>::Internal<Example>;

public:
	// this only has to be virtual if you will be doing this through polymorphic references
	virtual void recycle(void) { Factory<Example>::recycleRunTimeCopy(*this); }

	// not required, used as an example
	int getConfiguration(void) const { return m_configureValue; }

private:
	// or true, if there is differing state at author time (any constructor arguments)
	static const bool hasAuthorTimeState = EXAMPLE_HAS_AUTHOR_TIME_STATE;

	// return an exact copy, through whichever means you desire, a copy constructor isn't 
	// required for the factory system
	static Example* duplicate(const Example& source) { return new Example(source); }

	// not required, used as an example
	int m_configureValue;

	// not required, used as an example
	Example()
		: m_configureValue(-1)
	{
		// empty
	}

	// not required, used as an example
	Example(int configureValue)
		: m_configureValue(configureValue)
	{
		// empty
	}

	// doesn't have to be virtual, but the implementation would be the same
	virtual Example* getRunTimeCopy(void) const { return Factory<Example>::getRunTimeCopy(*this); }

	// or true, if there is run time state
	// this only has to be virtual if you will be doing this through polymorphic references
	virtual bool hasRunTimeState(void) const { return false; }

	// this is used to determine how many author time objects to keep "live"
	bool isEqualToAtAuthorTime(const Example& other) const { return getConfiguration() == other.getConfiguration(); } 

	// this will be called by the factory system you can make it do whatever you would like
	// this only has to be virtual if you will be doing this through polymorphic references
	virtual void recycleRunTimeCopy(void) 
	{
		delete this;
	}

	// if you do not forbid the copy assignment operator, you can subvert the factory system
	Example& operator=(const Example&);

}; // class Example

// To use the objects after they have been authored.

void testExample()
{
	// the template arguments to getAuthorCopy correspond to the constructor arguments for the 
	// object you are creating
	Example* argsAuthor = Factory<Example>::getAuthorCopy<int>(2);
	// returns the same object as argsAuthor
	Example* argsAuthor2 = Factory<Example>::getAuthorCopy<int>(2); 
	// executionVersion will only be a new object if Example::hasRunTimeState() returns true
	Example* executionVersion = Factory<Example>::getRunTimeCopy(*argsAuthor2);
	// returns -1
	executionVersion->getConfiguration(); 
	// deletes (or manages memory according to your implementation) executionVersion 
	// if Example::hasRunTimeState() returns true
	executionVersion->recycle();
	// destroys all the authorTimeFactoryObjects created by the Factory system
	// regardless of the template type.  Do this only when no more authoring
	// or run time use remains.
	FactoryDestroyer::destroyAllAuthorTimeAndStatelessObjects();
} // void testExample()


template<typename CLASS>
class TClass 
{
public:
	CLASS* instance; 
};

class EClass : public TClass<EClass>
{
public: 
	EClass() { instance = this; }
};


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

/*
class InnerClassCheck
{
public:
	class InnerA
	{
	public:
		void method(void) const { printf("I'm Inner A!\n"); }
	};

	class InnerB
	{
	public:
		void method(void) const { printf("I'm Inner B!\n"); }
	};

};

template<typename INNER_CLASS>
class OuterClass
{
public:
	InnerClassCheck::INNER_CLASS m_innerClass;

	void method(void) const { m_innerClass.method() };
};
*/


int globalAccess = 0;

namespace compilerChecks 
{
	void check(void)
	{
	
		testExample();
		// InnerClassCheck<InnerA> 
		
		Mutex<true> threadSafe;
		Mutex<false> threadUnsafe;
		Semaphore semaphore(2);

		{
			Synchronizer s(threadUnsafe);
			globalAccess++;
		}

		{
			Synchronizer s(threadSafe);
			globalAccess++;
		}

		{
			Synchronizer s(semaphore);
			globalAccess++;
		}


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