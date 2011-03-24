#pragma once
#ifndef OBSERVATION_H
#define OBSERVATION_H
/**
\file Observation.h

This Observer pattern implementation is somewhat inspired by this article:
http://www.codeproject.com/KB/architecture/observer_with_templates.aspx

\warning WORK IN-PROGRESS! 
\note EXPERIMENTAL!  NOT INTENDED FOR USE!
\todo make it
*/

#include <assert.h>
#include <vector>

#include "Synchronization.h"

namespace design_patterns 
{

template<typename SUBJECT>
class Observable;

template<typename SUBJECT>
class ObservableBase;

template<typename SUBJECT>
class ObservableMember;

template<typename SUBJECT>
class Observer;

template<typename SUBJECT>
class ObserverBase;

template<typename SUBJECT>
class ObserverMember;

template<typename SUBJECT>
void begin(Observer<SUBJECT>* observer, SUBJECT* observable)
{
	observable->add(observer);
	observer->observe(observable);
}

template<typename SUBJECT>
void cease(Observer<SUBJECT>* observer, SUBJECT* observable)
{
	observable->remove(observer);
	observer->ignore(observable);
}

template<typename SUBJECT>
void ignore(Observer<SUBJECT>* observer, SUBJECT* observable)
{
	observer->ignore(observable);
}

template<typename SUBJECT>
void remove(SUBJECT* observable, Observer<SUBJECT>* observer)
{
	observable->remove(observer);
}

template<typename SUBJECT>
class Observable 
{
	friend void design_patterns::begin(Observer<SUBJECT>* observer, SUBJECT* observable);
	friend void design_patterns::cease(Observer<SUBJECT>* observer, SUBJECT* observable);
	friend void design_patterns::remove(SUBJECT* observable, Observer<SUBJECT>* observer);

public:
	virtual		~Observable(void)=0 {}
	virtual void notify(void)=0; 

protected:
	virtual void add(Observer<SUBJECT>* observer)=0;
	virtual void remove(Observer<SUBJECT>* observer)=0;
}; // class Observable

template<typename SUBJECT>
class Observer
{
	friend void design_patterns::begin(Observer<SUBJECT>* observer, SUBJECT* observable);
	friend void design_patterns::cease(Observer<SUBJECT>* observer, SUBJECT* observable);
	friend void design_patterns::ignore(Observer<SUBJECT>* observer, SUBJECT* observable);

public:
	virtual		~Observer(void)=0 {}
	virtual void notice(SUBJECT* observable)=0;

protected:
	virtual void ignore(SUBJECT* observable)=0;
	virtual void observe(SUBJECT* observable)=0;
}; // class Observer

template<typename SUBJECT>
class ObservableBase 
: Observable<SUBJECT>
{
	typedef std::vector<Observer<SUBJECT> *>	observer_list;
	typedef typename observer_list::iterator	observer_iter;

public:
	virtual ~ObservableBase() 
	{
		synchronize(m_mutex);
		observer_iter sentinel(m_observers.end());
		observer_iter iter(m_observers.begin());

		for (iter; iter != sentinel; iter++)
		{
			ignore(*iter, this);
		}
	}

	virtual void notify(void)
	{	// notification might cause the observer to remove itself from the observable
		synchronize(m_mutex);
		observer_list copy(m_observers);
		observer_iter iter(copy.begin());
		observer_iter sentinel(copy.end());

		for (iter; iter != sentinel; iter++)
		{
			(*iter)->notice(this);
		}
	}

protected:
	virtual void add(Observer<SUBJECT>* observer)
	{
		synchronize(m_mutex);
		observer_iter sentinel(m_observers.end());
		observer_iter iter(m_observers.begin());

		for (iter; iter != sentinel; iter++)
		{
			if (*iter == observer)
			{
				return;
			}
		}

		m_observers.push_back(observer);
	}

	virtual void remove(Observer<SUBJECT>* observer)
	{
		synchronize(m_mutex);
		observer_iter sentinel(m_observers.end());
		observer_iter iter(m_observers.begin());

		for (iter; iter != sentinel; iter++)
		{
			if (*iter == observer)
			{
				m_observers.erase(iter);
				return;
			}
		}
	}	

private:
	ObservableBase<SUBJECT>(const ObservableBase<SUBJECT>&);
	ObservableBase<SUBJECT> operator=(const ObservableBase<SUBJECT>&);

	multithreading::Mutex	m_mutex;
	observer_list			m_observers;
}; // ObservableBase

template<typename SUBJECT>
class ObservableMember 
: Observable<SUBJECT>
{
	typedef std::vector<Observer<SUBJECT> *>	observer_list;
	typedef typename observer_list::iterator	observer_iter;

public:
#if DEBUG
	ObservableMember(void)
		: m_observable(NULL)
	{
		/* empty */
	}
#endif//DEBUG

	virtual ~ObservableMember() 
	{
		synchronize(m_mutex);
		assert(m_observable);
		observer_iter iter(m_observers.begin());
		observer_iter sentinel(m_observers.end());
		
		for (iter; iter != sentinel; iter++)
		{
			design_patterns::ignore(*iter, m_observable);
		}
	}

	virtual void notify(void)
	{	// notification might cause the observer to remove itself from the observable
		synchronize(m_mutex);
		assert(m_observable);
		observer_list copy(m_observers);
		observer_iter iter(copy.begin());
		observer_iter sentinel(copy.end());

		for (iter; iter != sentinel; iter++)
		{
			(*iter)->notice(m_observable);
		}
	}

	void setObservable(SUBJECT* observable)
	{
		m_observable = observable;
	}

	virtual void add(Observer<SUBJECT>* observer)
	{
		synchronize(m_mutex);
		assert(m_observable);
		observer_iter iter(m_observers.begin());
		observer_iter sentinel(m_observers.end());

		for (iter; iter != sentinel; iter++)
		{
			if (*iter == observer)
			{
				return;
			}
		}

		m_observers.push_back(observer);
	}

	virtual void remove(Observer<SUBJECT>* observer)
	{
		synchronize(m_mutex);
		assert(m_observable);
		observer_iter iter(m_observers.begin());
		observer_iter sentinel(m_observers.end());

		for (iter; iter != sentinel; iter++)
		{
			if (*iter == observer)
			{
				m_observers.erase(iter);
				return;
			}
		}
	}	

private:
	ObservableMember<SUBJECT>(const ObservableMember<SUBJECT>&);
	ObservableMember<SUBJECT> operator=(const ObservableMember<SUBJECT>&);

	multithreading::Mutex	m_mutex;
	SUBJECT*				m_observable;
	observer_list			m_observers;
}; // ObservableMember

template<typename SUBJECT>
class ObserverBase
: Observer<SUBJECT>
{
	typedef std::vector<SUBJECT*>				observable_list;
	typedef typename observable_list::iterator	observable_iter;

public:
	virtual ~ObserverBase(void) 
	{
		synchronize(m_mutex);
		observable_list copy(m_observables);
		m_observables.clear();
		observable_iter iter(copy.begin());
		observable_iter sentinel(copy.end());

		for (iter; iter != sentinel; iter++)
		{
			remove(*iter, this);
		}
	}

protected:
	virtual void ignore(SUBJECT* observable)
	{
		synchronize(m_mutex);

		for (observable_iter iter(m_observables.begin()); iter != m_observables.end(); iter++)
		{
			if (*iter == observable)
			{
				m_observables.erase(iter);
				return;
			}
		}		
	}

	virtual void observe(SUBJECT* observable)
	{
		synchronize(m_mutex);

		for (observable_iter iter(m_observables.begin()); iter != m_observables.end(); iter++)
		{
			if (*iter == observable)
			{
				return;
			}
		}

		m_observables.push_back(observable);
	}

private:
	ObserverBase<SUBJECT>(const ObserverBase<SUBJECT>&);
	ObserverBase<SUBJECT> operator=(const ObserverBase<SUBJECT>&);

	multithreading::Mutex	m_mutex;
	observable_list			m_observables;
}; // ObserverBase

template<typename SUBJECT>
class ObserverMember
: Observer<SUBJECT>
{
	typedef std::vector<SUBJECT*>				observable_list;
	typedef typename observable_list::iterator	observable_iter;

public:
#if DEBUG
	ObserverMember(void)
	: m_observer(NULL)
	{
		/* empty */
	}
#endif//DEBUG

	virtual ~ObserverMember(void) 
	{
		synchronize(m_mutex);
		assert(m_observer);
		observable_list copy(m_observables);
		m_observables.clear();
		observable_iter iter(copy.begin());
		observable_iter sentinel(copy.end());

		for (iter; iter != sentinel; iter++)
		{
			remove(*iter, m_observer);
		}
	}

	virtual void notice(SUBJECT* observable)
	{
		assert(m_observer);
		m_observer->notice(observable);
	}

	void setObserver(Observer<SUBJECT>* observer)
	{
		m_observer = observer;
	}

	virtual void ignore(SUBJECT* observable)
	{
		synchronize(m_mutex);
		observable_iter iter(m_observables.begin());
		observable_iter sentinel(m_observables.end());

		for (iter; iter != sentinel; iter++)
		{
			if (*iter == observable)
			{
				m_observables.erase(iter);
				return;
			}
		}		
	}

	virtual void observe(SUBJECT* observable)
	{
		synchronize(m_mutex);
		observable_iter iter(m_observables.begin());
		observable_iter sentinel(m_observables.end());

		for (iter; iter != sentinel; iter++)
		{
			if (*iter == observable)
			{
				return;
			}
		}

		m_observables.push_back(observable);
	}
	
private:
	ObserverMember<SUBJECT>(const ObserverMember<SUBJECT>&);
	ObserverMember<SUBJECT> operator=(const ObserverMember<SUBJECT>&);

	multithreading::Mutex	m_mutex;
	observable_list			m_observables;
	Observer<SUBJECT>*		m_observer;
}; // ObserverMember

} // namespace design_patterns

#endif//OBSERVATION_H