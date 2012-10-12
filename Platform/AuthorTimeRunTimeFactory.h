#pragma once
#ifndef AUTHOR_TIME_RUN_TIME_FACTORY_H
#define AUTHOR_TIME_RUN_TIME_FACTORY_H

template<bool HAS_AUTHOR_TIME_STATE>
class Factory
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
}; // Factory

template<bool HAS_AUTHOR_TIME_STATE>
template<typename OBJECT>
std::vector<OBJECT*> Factory<HAS_AUTHOR_TIME_STATE>::Internal<OBJECT>::m_objects;

template<> /* template specialization for no author time state */
class Factory<false>
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

template<typename OBJECT>
OBJECT* Factory<false>::Internal<OBJECT>::m_object;

template<typename OBJECT, typename ARGS>
OBJECT* NewAuthorCopy(const ARGS& args)
{
	return Factory< OBJECT::hasAuthorTimeState >::Internal<OBJECT>::getAuthorCopy<ARGS>(args);
};

template<typename OBJECT>
OBJECT* NewAuthorCopy(void)
{
	return Factory< OBJECT::hasAuthorTimeState >::Internal<OBJECT>::getAuthorCopy();
}

template<typename OBJECT>
OBJECT* NewRunTimeCopy(const OBJECT& object)
{
	return Factory< OBJECT::hasAuthorTimeState >::Internal<OBJECT>::getRunTimeCopy(object);
}

template<typename OBJECT>
void RecycleRunTimeCopy(OBJECT& object)
{
	Factory< OBJECT::hasAuthorTimeState >::Internal<OBJECT>::recycle(object);
}

template<typename OBJECT>
void DestroyAuthorCopies(void)
{
	Factory< OBJECT::hasAuthorTimeState >::Internal<OBJECT>::destroyObjects();
}

#endif//AUTHOR_TIME_RUN_TIME_FACTORY_H