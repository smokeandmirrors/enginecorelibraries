#pragma once
#ifndef AUTHOR_TIME_RUN_TIME_FACTORY_H
#define AUTHOR_TIME_RUN_TIME_FACTORY_H

/*
 \todo make these singletons so that all of their 
 destroy functions can get called at once
*/

template<bool HAS_AUTHOR_TIME_STATE>
class FactorySelector
{
public:
	template<typename OBJECT>
	class Internal
	{
	public:
		static void destroyObjects(void)
		{
			for (std::vector<OBJECT*>::iterator i(m_objects.begin()), sentinel(m_objects.end())
				; i != sentinel
				; ++i)
			{
				delete *i;
			}
		}

		template<typename ARGS>
		static OBJECT* getAuthorCopy(const ARGS& args)
		{
			printf("has author time version with args!\n");
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
			printf("has author time version without args!\n");
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
			/**
			does the state have run-time state?
				return a new copy, every time.

			does the state have author-time state?
				return a single copy on a per author-time basis.

			else
				return a single copy.
			*/
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
				delete &object;
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
		static void destroyObjects(void)
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
			/**
			does the state have run-time state?
				return a new copy, every time.

			does the state have author-time state?
				return a single copy on a per author-time basis.

			else
				return a single copy.
			*/
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
				delete &object;
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
		T::destroyObjects();
	}
}; // class CustomFactoryDestroyer

inline void destroyFactoryObjects(void);

template<typename OBJECT>
OBJECT* FactorySelector<false>::Internal<OBJECT>::m_object;

template<typename OBJECT>
class Factory
{
public:
	template<typename ARGS>
	static OBJECT* NewAuthorCopy(const ARGS& args)
	{
		initializeDestroyer();
		return FactorySelector< OBJECT::hasAuthorTimeState >::Internal<OBJECT>::getAuthorCopy<ARGS>(args);
	}; 

	static OBJECT* NewAuthorCopy(void)
	{
		initializeDestroyer();
		return FactorySelector< OBJECT::hasAuthorTimeState >::Internal<OBJECT>::getAuthorCopy();
	}

	static OBJECT* NewRunTimeCopy(const OBJECT& object)
	{
		return FactorySelector< OBJECT::hasAuthorTimeState >::Internal<OBJECT>::getRunTimeCopy(object);
	}

	static void RecycleRunTimeCopy(OBJECT& object)
	{
		FactorySelector< OBJECT::hasAuthorTimeState >::Internal<OBJECT>::recycle(object);
	}

	static void destroyObjects(void)
	{
		FactorySelector< OBJECT::hasAuthorTimeState >::Internal<OBJECT>::destroyObjects();
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

void destroyFactoryObjects(void)
{
	FactoryDestroyer* destroyer(factoryDestroyers);

	while (destroyer)
	{
		destroyer->destroy();
		destroyer = destroyer->next;
	}
}

#endif//AUTHOR_TIME_RUN_TIME_FACTORY_H