#pragma once
#ifndef AUTHOR_TIME_RUN_TIME_FACTORY_H
#define AUTHOR_TIME_RUN_TIME_FACTORY_H

/**
\file AuthorTimeRunTimeFactory.h
\author Smoke and Mirrors Development
\htmlonly
<A HREF="smokeandmirrorsdevelopment@gmail.com">
smokeandmirrorsdevelopment@gmail.com</A>
<BR>
&copy;2009-2012 Smoke and Mirrors Development
<BR>
\endhtmlonly

This is a system to help classes control creation
on the basis of 1) author time state, and 2) run time state.
1) author time state means the configuration of objects when 
they are created.  Only one instance of each configuration 
will be created.  2) run time state means that the objects
have state that can be modified when the object is actually
getting used by whatever client requested use of it.

The motivation for the systems has been the fact that I
have repeatedly run into situations where I have 
a small set of recipes (constructor arguments) on a 
set of objects.  This what I consider "author time"
situation.  Additionally, I have needed access to some
of these objects, but only occasionally to some 
of them need differentiating state when executed, "run
time state".  This factory system makes it much easier
control the unecessary creation of objects with any 
combination of author-time and run-time state.

"Author time" copies are entirely distinguished from
each other in their constructors. 

"Run time" copies are created by calling getRunTimeCopy()
and passing in an author copy as an argument.

Calling destroyAllAuthorTimeFactoryObjects() will destroy
all of the "author time" copies, which, would include any
"run time" copies that have no run time state.  Be careful
to call recycle() on any run time copies, it will do nothing
to run-time-stateless objects but will help maintain memory
management if the code changes at a later time.  Make sure
to never use any of the objects after 
destroyAllAuthorTimeFactoryObjects() has been called.  All
such objects should have been deleted.  To use more,
simply call the factory create methods again.

A primary example of this (and original motivation) is the HFSM system. An ActionState
could have no author time state (that is, no variable arguments 
in its constructor).  Only one of these objects will ever
be created to author different state machines.  If it did
have author time state, say a string name, only one author 
time copy will get created for each different string.

To allow your class to be controlled by the Factory
system, you will have to have the following 
member variables and methods (unless marked not required):

\code
// this macro just makes consistency a bit easier for your class
#define EXAMPLE_HAS_AUTHOR_TIME_STATE false

class Example
{
// the Factory classes need access to construction and traits
friend class Factory<Example>;
friend class FactorSelector<EXAMPLE_HAS_AUTHOR_TIME_STATE>::Internal<Example>;

public:
// this only has to be virtual if you will be doing this through polymorphic references
virtual void recycle(void) { Factory<Example>::recycleRunTimeCopy(*this); }

private:
// or true, if there is differing state at author time (any constructor arguments)
static const bool hasAuthorTimeState = EXAMPLE_HAS_AUTHOR_TIME_STATE;

// return an exact copy, through whichever means you desire, a copy constructor isn't 
// required for the factory system
static Example* duplicate(const Example& source) { return new Example(source); }

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

// not required, used as an example
int getConfiguration(void) const { return m_configureValue; }

// doesn't have to be virtual, but the implementation would be the same
virtual Example* getRunTimeCopy(void) const { return Factory<Example>::getRunTimeCopy(*this); }

// or true, if there is run time state
// this only has to be virtual if you will be doing this through polymorphic references
virtual bool hasRunTimeState(void) const { return false; }

// this is used to determine how many author time objects to keep "live"
bool isEqualToAtAuthorTime(const Example& other) const { return getConfiguration() == other.getConfiguration(); } 

// if you do not forbid the copy assignment operator, you can subvert the factory system
Example& operator=(cost Example&);
\endcode

To use the objects after they have been authored.

\code
// the template arguments to getAuthorCopy correspond to the constructor arguments for the 
// object you are creating
Example* noArgsAuthor = Factory<Example>::getAuthorCopy();
Example* argsAuthor = Factory<Example>::getAuthorCopy<int>(2);
// returns the same object as argsAuthor
Example* argsAuthor2 = Factory<Example>::getAuthorCopy<int>(2); 
// executionVersion will only be a new object if Example::hasRunTimeState() returns true
Example* executionVersion = Factory<Example>::getRunTimeCopy(*noArgsAuthor);
// returns -1
executionVersion->getConfiguration(); 
// deletes (or manages memory according to your implementation) executionVersion 
// if Example::hasRunTimeState() returns true
executionVersion->recycle();
// destroys all the authorTimeFactoryObjects created by the Factory system
// regardless of the template type.  Do this only when no more authoring
// or run time use remains.
FactoryDestroyer::destroyAllAuthorTimeAndStatelessObjects();
\endcode

\note This functionality is intentionally not thread-safe.  As long
as the author-time objects are created from a single thread, run time execution
should be perfectly fine.   If specific optimizations of run-time copies
are desired, changes would have to be made to the recycle() methods here 
and on client classes.

<DEVELOPMENT STATUS>
Current Draft		:	1.0
Current Phase		:   FIELD TESTING
Purpose				:	DEPLOYMENT
Unit Tested			:	NO
Used in development	:	YES
Used in experiments :	YES
Tested in the field	:	NO
*/

/** support macro for the declaration of author/run time factory classes */
#define HAS_RUN_TIME_STATE_GENERIC(VALUE) \
	virtual bool hasRunTimeState(void) const { return VALUE; } 

/** support macro for the declaration of author/run time factory classes */
#define HAS_AUTHOR_TIME_STATE_false(CLASS_NAME) \
	bool isEqualToAtAuthorTime(const CLASS_NAME##&) const { return true; } \
	static const bool hasAuthorTimeState = false;

/** support macro for the declaration of author/run time factory classes */
#define HAS_AUTHOR_TIME_STATE_true(CLASS_NAME) \
	bool isEqualToAtAuthorTime(const CLASS_NAME##& other) const; \
	static const bool hasAuthorTimeState = true;

/** support macro for the declaration of author/run time factory classes */
#define RUN_AND_AUTHOR_TIME_FACTORY_IMPLEMENTATION(CLASS_NAME, BASE_CLASS, AUTHOR_TIME, RUN_TIME) \
	public: \
	virtual void recycle(void) { Factory< CLASS_NAME >::recycleRunTimeCopy(*this); } \
	HAS_AUTHOR_TIME_STATE_##AUTHOR_TIME ( CLASS_NAME ) \
	HAS_RUN_TIME_STATE_GENERIC ( RUN_TIME ) \
	private: \
	friend class Factory< CLASS_NAME >; \
	friend class FactorySelector< AUTHOR_TIME >::Internal< CLASS_NAME >; \
	static CLASS_NAME * duplicate(const CLASS_NAME & source) { return new CLASS_NAME (source);  } \
	virtual BASE_CLASS* getRunTimeCopy(void) const { return Factory< CLASS_NAME >::getRunTimeCopy(*this); } \
	CLASS_NAME & operator=(const CLASS_NAME &); 

#define PURE_FACTORY_OBJECT(CLASS_NAME, BASE_CLASS_NAME) RUN_AND_AUTHOR_TIME_FACTORY_IMPLEMENTATION(CLASS_NAME, BASE_CLASS, false, false)
#define AUTHOR_TIME_FACTORY_OBJECT(CLASS_NAME, BASE_CLASS_NAME) RUN_AND_AUTHOR_TIME_FACTORY_IMPLEMENTATION(CLASS_NAME, BASE_CLASS, true, false)
#define AUTHOR_AND_RUN_TIME_FACTORY_OBJECT(CLASS_NAME, BASE_CLASS_NAME) RUN_AND_AUTHOR_TIME_FACTORY_IMPLEMENTATION(CLASS_NAME, BASE_CLASS, true, true)
#define RUN_TIME_FACTORY_OBJECT(CLASS_NAME, BASE_CLASS_NAME) RUN_AND_AUTHOR_TIME_FACTORY_IMPLEMENTATION(CLASS_NAME, BASE_CLASS, false, true)

template<bool HAS_AUTHOR_TIME_STATE>
class FactorySelector
{
public:
	template<typename OBJECT>
	class Internal
	{
	public:
		static void destroyAuthorCopies(void)
		{
			for (std::vector<OBJECT*>::iterator i(m_objects.begin()), sentinel(m_objects.end())
				; i != sentinel
				; ++i)
			{
				delete *i;
			}

			m_objects.resize(0);
		}

		template<typename LHS_ARGS, typename RHS_ARGS>
		static OBJECT* getAuthorCopy(LHS_ARGS lhsArgs, RHS_ARGS rhsArgs)
		{
			OBJECT candidate(lhsArgs, rhsArgs);
			int objectIndex(0);

			if (!has(candidate, objectIndex))
			{
				objectIndex = m_objects.size();
				m_objects.push_back(new OBJECT(lhsArgs, rhsArgs));
			}

			return m_objects[objectIndex];
		}

		template<typename ARGS>
		static OBJECT* getAuthorCopy(ARGS args)
		{
			OBJECT candidate(args);
			int objectIndex(0);

			if (!has(candidate, objectIndex))
			{
				objectIndex = m_objects.size();
				m_objects.push_back(new OBJECT(args));
			}

			return m_objects[objectIndex];
		}
		
		static OBJECT* getRunTimeCopy(const OBJECT& object)
		{
			if (object.hasRunTimeState())
			{
				return OBJECT::duplicate(object);
			}
			else
			{
				return const_cast<OBJECT*>(&object);
			}
		}

		static void recycle(OBJECT& object)
		{
			if (object.hasRunTimeState())
			{
				object.recycleRunTimeCopy();
			}
		}

	protected:
		static int has(const OBJECT& object, int& objectIndex)
		{
			objectIndex = -1;

			for (int i(0), sentinel(m_objects.size()); i < sentinel; ++i)
			{
				if (m_objects[i]->isEqualToAtAuthorTime(object))
				{
					objectIndex = i;
					return true;
				}
			}

			return false;
		}

	private:
		static std::vector<OBJECT*> m_objects;
	}; // Internal
}; // FactorySelector

template<bool HAS_AUTHOR_TIME_STATE>
template<typename OBJECT>
std::vector<OBJECT*> FactorySelector<HAS_AUTHOR_TIME_STATE>::Internal<OBJECT>::m_objects;

template<> /* template specialization for no author time state */
class FactorySelector<false>
{
public:
	template<typename OBJECT>
	class Internal
	{
	public:
		static void destroyAuthorCopies(void)
		{
			delete m_object;
			m_object = NULL;
		}

		/* IF NOT AUTHOR TIME STATE THAN THERE MUST ONLY BE A NO-ARGS CONSTRUCTOR */
		static OBJECT* getAuthorCopy(void)
		{	
			printf("has NOT author time version with no args!\n");
			if (m_object == NULL)
			{
				m_object = new OBJECT;
			}

			return m_object;
		}
		
		static OBJECT* getRunTimeCopy(const OBJECT& object)
		{
			if (object.hasRunTimeState())
			{
				return OBJECT::duplicate(object);
			}
			else
			{
				return const_cast<OBJECT*>(&object);
			}
		}

		static void recycle(OBJECT& object)
		{	// this must be handled at run time since 
			// run-time objects might get recycled through 
			// a virtual object
			if (object.hasRunTimeState())
			{
				object.recycleRunTimeCopy();
			}
		}

	private:
		static OBJECT* m_object;
	}; 
};

extern class FactoryDestroyer* factoryDestroyers;

class FactoryDestroyer
{
public:
	static void destroyAllAuthorTimeAndStatelessObjects(void)
	{
		FactoryDestroyer* destroyer(factoryDestroyers);

		while (destroyer)
		{
			destroyer->destroy();
			FactoryDestroyer* oldDestroyer(destroyer);
			destroyer = destroyer->next;
			oldDestroyer->clearDestroyer();
			delete oldDestroyer;
		}

		factoryDestroyers = NULL;
	}

protected:
	virtual ~FactoryDestroyer(void) {};
	virtual void destroy(void) const=0;
	virtual void clearDestroyer(void)=0;
	FactoryDestroyer* next;
}; // class FactoryDestroyer

template<typename OBJECT>
class Factory;

template<typename T>
class CustomFactoryDestroyer : public FactoryDestroyer
{
public:
	CustomFactoryDestroyer()
	{
		next = factoryDestroyers;
		factoryDestroyers = this;
	}
	
	virtual void destroy(void) const
	{
		T::destroyAuthorCopies();
	}

	virtual void clearDestroyer(void)
	{
		Factory<T>::clearDestroyer();
	}
}; // class CustomFactoryDestroyer

template<typename OBJECT>
OBJECT* FactorySelector<false>::Internal<OBJECT>::m_object;

template<typename OBJECT>
class Factory
{
	friend class CustomFactoryDestroyer<OBJECT>;

public:
	// temporary until we get the variadic templates in C++11
	template<typename LHS_ARGS, typename RHS_ARGS>
	static OBJECT* getAuthorCopy(LHS_ARGS lhsArgs, RHS_ARGS rhsArgs)
	{
		initializeDestroyer();
		return FactorySelector< OBJECT::hasAuthorTimeState >::Internal<OBJECT>::getAuthorCopy<LHS_ARGS, RHS_ARGS>(lhsArgs, rhsArgs);
	}; 
	
	template<typename ARGS>
	static OBJECT* getAuthorCopy(ARGS args)
	{
		initializeDestroyer();
		return FactorySelector< OBJECT::hasAuthorTimeState >::Internal<OBJECT>::getAuthorCopy<ARGS>(args);
	}; 

	static OBJECT* getAuthorCopy(void)
	{
		initializeDestroyer();
		return FactorySelector< OBJECT::hasAuthorTimeState >::Internal<OBJECT>::getAuthorCopy();
	}

	static OBJECT* getRunTimeCopy(const OBJECT& object)
	{
		return FactorySelector< OBJECT::hasAuthorTimeState >::Internal<OBJECT>::getRunTimeCopy(object);
	}

	static void recycleRunTimeCopy(OBJECT& object)
	{
		FactorySelector< OBJECT::hasAuthorTimeState >::Internal<OBJECT>::recycle(object);
	}

	static void destroyAuthorCopies(void)
	{
		FactorySelector< OBJECT::hasAuthorTimeState >::Internal<OBJECT>::destroyAuthorCopies();
	}

protected:
	static inline void initializeDestroyer(void)
	{
		if (!m_objectDestroyer)
		{
			m_objectDestroyer = new CustomFactoryDestroyer< Factory<OBJECT> >;
		}
	}
	
	static inline void clearDestroyer(void)
	{
		m_objectDestroyer = NULL;
	}

private:
	static CustomFactoryDestroyer< Factory<OBJECT> >* m_objectDestroyer;
}; // Factory

template<typename OBJECT> CustomFactoryDestroyer< Factory<OBJECT> >* Factory<OBJECT>::m_objectDestroyer;



#endif//AUTHOR_TIME_RUN_TIME_FACTORY_H