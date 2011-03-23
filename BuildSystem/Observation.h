#pragma once
#ifndef OBSERVATION_H
#define OBSERVATION_H
/**
\file Observation.h

This Observer pattern implementation is somewhat inspired by this article:
http://www.codeproject.com/KB/architecture/observer_with_templates.aspx

\warning WORK IN-PROGRESS! 
\note EXPERIMENTAL!  NOT INTENDED FOR USE!
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
class Observable
{	
public:
	virtual		~Observable(void) {}
	virtual void add(Observer<SUBJECT>* observer)=0;
	virtual void notify(void)=0; 
	virtual void remove(Observer<SUBJECT>* observer)=0;
}; // class Observable

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

		for (observer_iter iter(m_observers.begin()); iter != m_observers.end(); iter++)
		{
			(*iter)->ignore(this);
		}
	}

	virtual void add(Observer<SUBJECT>* observer)
	{
		synchronize(m_mutex);

		for (observer_iter iter(m_observers.begin()); iter != m_observers.end(); iter++)
		{
			if (*iter == observer)
			{
				return;
			}
		}

		m_observers.push_back(observer);
		observer->observe(this);
	}

	virtual void notify(void)
	{	// notification might cause the observer to remove itself from the observable
		synchronize(m_mutex);
		observer_list copy(m_observers);

		for (observer_iter iter(copy.begin()); iter != copy.end(); iter++)
		{
			(*iter)->notice(this);
		}
	}

	virtual void remove(Observer<SUBJECT>* observer)
	{
		synchronize(m_mutex);
		observer->ignore(this);

		for (observer_iter iter(m_observers.begin()); iter != m_observers.end(); iter++)
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
		
		for (observer_iter iter(m_observers.begin()); iter != m_observers.end(); iter++)
		{
			(*iter)->ignore(m_observable);
		}
	}
	
	virtual void add(Observer<SUBJECT>* observer)
	{
		synchronize(m_mutex);
		assert(m_observable);

		for (observer_iter iter(m_observers.begin()); iter != m_observers.end(); iter++)
		{
			if (*iter == observer)
			{
				return;
			}
		}

		m_observers.push_back(observer);
		observer->observe(m_observable);
	}
	
	virtual void notify(void)
	{	// notification might cause the observer to remove itself from the observable
		synchronize(m_mutex);
		assert(m_observable);
		observer_list copy(m_observers);

		for (observer_iter iter(copy.begin()); iter != copy.end(); iter++)
		{
			(*iter)->notice(m_observable);
		}
	}

	virtual void remove(Observer<SUBJECT>* observer)
	{
		synchronize(m_mutex);
		assert(m_observable);
		observer->ignore(m_observable);

		for (observer_iter iter(m_observers.begin()); iter != m_observers.end(); iter++)
		{
			if (*iter == observer)
			{
				m_observers.erase(iter);
				return;
			}
		}
	}	

	void setObservable(SUBJECT* observable)
	{
		m_observable = observable;
	}

private:
	ObservableMember<SUBJECT>(const ObservableMember<SUBJECT>&);
	ObservableMember<SUBJECT> operator=(const ObservableMember<SUBJECT>&);

	multithreading::Mutex	m_mutex;
	SUBJECT*				m_observable;
	observer_list			m_observers;
}; // ObservableMember

template<typename SUBJECT>
class Observer
{
public:
	virtual		~Observer(void) {}
	virtual void ignore(SUBJECT* observable)=0;
	virtual void notice(SUBJECT* observable)=0;
	virtual void observe(SUBJECT* observable)=0;
}; // class Observer

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

		for (observable_iter iter(copy.begin()); iter != copy.end(); iter++)
		{
			(*iter)->remove(this);
		}
	}

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

		for (observable_iter iter(copy.begin()); iter != copy.end(); iter++)
		{
			(*iter)->remove(m_observer);
		}
	}

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

	virtual void notice(SUBJECT* observable)
	{
		assert(m_observer);
		m_observer->notice(observable);
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

	void setObserver(Observer<SUBJECT>* observer)
	{
		m_observer = observer;
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