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

#include <vector>

#include "Singleton.h"
#include "Synchronization.h"

namespace design_patterns 
{

template<typename SUBJECT>
class Observer;

template<typename SUBJECT>
class Observable
{	
public:
	virtual		~Observable(void) {}
	virtual void add(Observer<SUBJECT>* observer)=0;
	virtual void notify(void)=0; // call notice() on all observers
	virtual void remove(Observer<SUBJECT>* observer)=0;
}; // class Observable

template<typename SUBJECT>
class ObservableHelper 
: Observable<SUBJECT>
{
	typedef std::vector<Observer<SUBJECT> *>	observer_list;
	typedef typename observer_list::iterator	observer_iter;
	
public:
	explicit ObservableHelper(SUBJECT& observable)
	: m_observable(observable)
	{
		/* empty */
	}
	
	virtual ~ObservableHelper() 
	{
		synchronize(m_mutex)

		for (observer_iter iter(m_observers.begin()); iter != m_observers.end(); iter++)
		{
			(*iter)->ignore(&m_observable);
		}
	}
	
	virtual void add(Observer<SUBJECT>* observer)
	{
		synchronize(m_mutex)

		for (observer_iter iter(m_observers.begin()); iter != m_observers.end(); iter++)
		{
			if (*iter == observer)
			{
				return;
			}
		}

		m_observers.push_back(observer);
		observer->observe(&m_observable);
	}
	
	virtual void remove(Observer<SUBJECT>* observer)
	{
		synchronize(m_mutex)
		observer->ignore(&m_observable);

		for (observer_iter iter(m_observers.begin()); iter != m_observers.end(); iter++)
		{
			if (*iter == observer)
			{
				m_observers.erase(iter);
				return;
			}
		}
	}

	virtual void notify(void)
	{	// notification might cause the observer to remove itself from the observable
		synchronize(m_mutex)
		observer_list copy(m_observers);

		for (observer_iter iter(copy.begin()); iter != copy.end(); iter++)
		{
			(*iter)->notice(&m_observable);
		}
	}

private:
	ObservableHelper<SUBJECT>(void);
	ObservableHelper<SUBJECT>(const ObservableHelper<SUBJECT>&);
	ObservableHelper<SUBJECT> operator=(const ObservableHelper<SUBJECT>&);

	multithreading::Mutex	m_mutex;
	SUBJECT&				m_observable;
	observer_list			m_observers;
}; // ObservableHelper

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
class ObserverHelper
: Observer<SUBJECT>
{
	typedef std::vector<SUBJECT*>				observable_list;
	typedef typename observable_list::iterator	observable_iter;

public:
	explicit ObserverHelper(Observer<SUBJECT>& observer)
	: m_observer(observer)
	{
		/* empty */
	}
	
	virtual ~ObserverHelper(void) 
	{
		synchronize(m_mutex)
		observable_list copy(m_observables);
		m_observables.clear();

		for (observable_iter iter(copy.begin()); iter != copy.end(); iter++)
		{
			(*iter)->remove(&m_observer);
		}
	}
	
	virtual void ignore(SUBJECT* observable)
	{
		synchronize(m_mutex)
			
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
		m_observer.notice(observable);
	}

	virtual void observe(SUBJECT* observable)
	{
		synchronize(m_mutex)
		
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
	ObserverHelper<SUBJECT>(void);
	ObserverHelper<SUBJECT>(const ObserverHelper<SUBJECT>&);
	ObserverHelper<SUBJECT> operator=(const ObserverHelper<SUBJECT>&);
	
	multithreading::Mutex	m_mutex;
	observable_list			m_observables;
	Observer<SUBJECT>&		m_observer;
}; // ObserverHelper

} // namespace design_patterns

#endif//OBSERVATION_H