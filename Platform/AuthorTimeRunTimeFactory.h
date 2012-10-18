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

A primary example of this is HFSM systems.  An ActionState
could have no author time state (that is, no variable arguments 
in its constructor).  Only one of these objects will ever
be created to author different state machines.  If it did
have author time state, say a string name, only one author 
time copy will get created for each different string.

"Run time" copies are created by calling getRunTimeCopy()
and passing in an author copy as an argument.  They are
destroyed by calling recycle() on the run time copy,
and the Author copies are destroyed 
by calling destroyAllAuthorTimeFactoryObjects();

To allow your class to be controlled by the Factory
system, you will have to have the folling 
member variables and methods:

\code
// this macro just makes consistency a bit easier for your class
#define EXAMPLE_HAS_AUTHOR_TIME_STATE false

class Example
{
public:
// or true, if there is differing state at author time (any constructor arguments)
static const bool hasAuthorTimeState = EXAMPLE_HAS_AUTHOR_TIME_STATE;

Example()
: m_configureValue(-1)
{
	// empty
}

Example(int configureValue)
: m_configureValue(configureValue)
{
	// empty
}

int getConfiguration(void) const
{
	return m_configureValue;
}

// this only has to be virtual if you will be doing this through polymorphic references
virtual void recycle(void) { Factory<Example>::recycleRunTimeCopy(*this); }

// or true, if there is run time state
// this only has to be virtual if you will be doing this through polymorphic references
virtual bool hasRunTimeState(void) const { return false; }

private:
friend class Factory<Example>;
friend class FactorSelector<EXAMPLE_HAS_AUTHOR_TIME_STATE>::Internal<Example>;

// return an exact copy, through whichever means you desire, a copy constructor isn't 
// required for this function
static Example* duplicate(const Example& source) { return new Example(source); }

// doesn't have to be virtual, but the implementation would be the same
virtual Example* getRunTimeCopy(void) const { return Factory<Example>::getRunTimeCopy(*this); }

// if you do not forbid the copy assignment operator, you can subvert the factory system
Example& operator=(cost Example&);
};
\endcode

To use the objects:
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


<DEVELOPMENT STATUS>
Current Draft		:	1.0
Current Phase		:   FIELD TESTING
Purpose				:	DEPLOYMENT
Unit Tested			:	NO
Used in development	:	YES
Used in experiments :	YES
Tested in the field	:	NO
*/

template<bool HAS_AUTHOR_TIME_STATE>
class FactorySelector
{
	/**
	does the state have run-time state?
		return a new copy, every time.

	does the state have author-time state?
		return a single copy on a per author-time basis.

	else
		return a single copy.

	run time state status must be available at run-time
	for objects that might be deleted through a 
	virtual interface
	*/			
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

		template<typename ARGS>
		static OBJECT* getAuthorCopy(const ARGS& args)
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

		static OBJECT* getAuthorCopy(void)
		{
			OBJECT candidate;
			int objectIndex(0);

			if (!has(candidate, objectIndex))
			{
				objectIndex = m_objects.size();
				m_objects.push_back(new OBJECT);
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
	template<typename ARGS>
	static OBJECT* getAuthorCopy(const ARGS& args)
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