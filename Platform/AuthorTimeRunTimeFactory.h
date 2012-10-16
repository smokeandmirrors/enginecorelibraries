#pragma once
#ifndef AUTHOR_TIME_RUN_TIME_FACTORY_H
#define AUTHOR_TIME_RUN_TIME_FACTORY_H

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
	virtual ~FactoryDestroyer(void) {};
	virtual void destroy(void) const=0;
	FactoryDestroyer* next;
}; // class FactoryDestroyer

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
}; // class CustomFactoryDestroyer

inline void destroyAllAuthorTimeFactoryObjects(void);

template<typename OBJECT>
OBJECT* FactorySelector<false>::Internal<OBJECT>::m_object;

template<typename OBJECT>
class Factory
{
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

private:
	static CustomFactoryDestroyer< Factory<OBJECT> >* m_objectDestroyer;
}; // Factory

template<typename OBJECT> CustomFactoryDestroyer< Factory<OBJECT> >* Factory<OBJECT>::m_objectDestroyer;

/*
template<OBJECT>
template<> Factory<OBJECT>* Singleton< Factory<OBJECT> >::singleton(NULL); \
	static CustomSingletonController< Factory<OBJECT> > BASE_CLASS##Initializer; \
	*/

void destroyAllAuthorTimeFactoryObjects(void)
{
	FactoryDestroyer* destroyer(factoryDestroyers);

	while (destroyer)
	{
		destroyer->destroy();
		destroyer = destroyer->next;
	}

	factoryDestroyers = NULL;
}

#endif//AUTHOR_TIME_RUN_TIME_FACTORY_H