#pragma once
#ifndef OBSERVATION_H
#define OBSERVATION_H
/**
\file Observation.h

This Observer pattern implementation is somewhat inspired by this article:
http://www.codeproject.com/KB/architecture/observer_with_templates.aspx

\todo make an observation manager which handles all the synchronization
problems

\warning THIS FUNCTIONALITY IS NOT THREAD SAFE!
*/

#include <hash_map>
#include <list>
#include <utility>
#include <vector>

#include "Singleton.h"

namespace design_patterns 
{

template<typename SUBJECT>
class IObserver
{
public:
	virtual		~IObserver(void) {}
	virtual void notice(SUBJECT* observable)=0;
}; // class IObserver

template<typename SUBJECT>
class IObservable
{	
public:
	virtual		~IObservable(void) {}
	virtual void notify(void)=0; // call notice() on all observers
}; // class IObservable

/**
The implicit interface of OBSERVER is void notice(OBSERVABLE* subject);

The implicit interface of OBSERVABLE is void notify(void);
\note which is most easily implemented as Observation<OBSERVABLE>::single.notify(this);
*/

template<typename OBSERVER, typename OBSERVABLE>
class Observation : public Singleton< Observation<OBSERVER, OBSERVABLE> >
{
	typedef std::list<OBSERVABLE*>							observable_list;
	typedef std::list<OBSERVER*>							observer_list;

	typedef typename std::list<OBSERVABLE*>::iterator		observable_list_iter;
	typedef typename std::list<OBSERVER*>::iterator			observer_list_iter;

	typedef std::pair<OBSERVER*, observable_list*>			observer_list_pair;
	typedef std::pair<OBSERVABLE*, observer_list*>			observable_list_pair;

	typedef stdext::hash_map<OBSERVER*, observable_list*>	observer_list_map;
	typedef stdext::hash_map<OBSERVABLE*, observer_list*>	observable_list_map;

public:
	void begin(OBSERVABLE& subject, OBSERVER& observer)
	{

	}

	void cease(OBSERVABLE& subject, OBSERVER& observer)
	{

	}

	void hide(OBSERVABLE& subject)
	{

	}

	void ignore(OBSERVER& observer)
	{

	}

	void notify(OBSERVABLE& subject)
	{

	}

protected:
	void notify(OBSERVABLE& subject, const observer_list& observers) const
	{
		observer_list temp = observers;
		
		for (observable_list_iter iter(temp.begin()); iter != temp.end(); iter++)
		{
			(*iter)->notify(&subject);	
		}		
	}

	bool isActive(void) const
	{
		
	}

private:
	

	observable_list_map m_observableListMap;
	observer_list_map	m_observerListMap;
	// container, observer -> observables
	// container, observable -> observers

}; // class Observation



















template<typename SUBJECT>
class Observer
{
public:
	virtual		~Observer(void) {}
	virtual void ignore(SUBJECT* observable)=0;
	virtual void notify(SUBJECT* observable)=0;
	virtual void notifyDestruction(SUBJECT* observable)=0;
	virtual void observe(SUBJECT* observable)=0;
}; // class Observer

template<typename SUBJECT>
class Observable
{	
public:
	virtual		~Observable(void) {}
	virtual void add(Observer<SUBJECT>* observer)=0;
	virtual void remove(Observer<SUBJECT>* observer)=0;
	virtual void update(void)=0; // call notify() on all observers
}; // class Observable

template<typename SUBJECT>
class ObservableHelper 
: Observable<SUBJECT>
{
public:
	explicit ObservableHelper(Observable<SUBJECT>& observable)
	: m_observable(observable)
	{
		/* empty */
	}
	
	virtual ~ObservableHelper() 
	{
		for (std::vector<Observer<SUBJECT> *>::iterator iter = m_observers.begin();
		iter != m_observers.end();
		iter++)
		{
			(*iter)->notifyDestruction(static_cast<SUBJECT*>(&m_observable));
		}
	}
	
	// when using the helper, only call OBSERVE, NEVER ADD
	virtual void add(Observer<SUBJECT>* observer)
	{
		for (std::vector<Observer<SUBJECT> *>::iterator iter = m_observers.begin();
		iter != m_observers.end();
		iter++)
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
		for (std::vector<Observer<SUBJECT> *>::iterator iter = m_observers.begin();
		iter != m_observers.end();
		iter++)
		{
			if (*iter == observer)
			{
				m_observers.erase(iter+0);
				return;
			}
		}
	}

	virtual void update(void)
	{
		for (std::vector<Observer<SUBJECT> *>::iterator iter = m_observers.begin();
		iter != m_observers.end();
		iter++)
		{
			(*iter)->notify(static_cast<SUBJECT*>(&m_observable));
		}
	}

private:
	ObservableHelper<SUBJECT>(void);
	ObservableHelper<SUBJECT>(const ObservableHelper<SUBJECT>&);
	ObservableHelper<SUBJECT> operator=(const ObservableHelper<SUBJECT>&);

	Observable<SUBJECT>&				m_observable;
	std::vector<Observer<SUBJECT> *>	m_observers;
}; // ObservableHelper

template<typename SUBJECT>
class ObserverHelper
: Observer<SUBJECT>
{
public:
	explicit ObserverHelper(Observer<SUBJECT>& observer)
	: m_observer(observer)
	{
		/* empty */
	}
	
	virtual ~ObserverHelper(void) 
	{
		for (std::vector<SUBJECT*>::iterator iter(m_observables.begin());
		iter != m_observables.end();
		iter++)
		{
			(*iter)->remove(this);
		}
	}
	
	virtual void ignore(SUBJECT* observable)
	{
		for (std::vector<SUBJECT*>::iterator iter(m_observables.begin());
		iter != m_observables.end();
		iter++)
		{
			if (*iter == observable)
			{
				// move to observation
				// observable->remove(this);
				m_observables.erase(iter);
				return;
			}
		}		
	}

	virtual void notify(SUBJECT* observable)
	{
		m_observer.notify(observable);
	}

	virtual void notifyDestruction(SUBJECT* observable)
	{
		for (std::vector<SUBJECT*>::iterator iter(m_observables.begin());
		iter != m_observables.end();
		iter++)
		{
			if (*iter == observable)
			{
				m_observer.notifyDestruction(observable);
				m_observables.erase(iter);
				return;
			}
		}
	}

	// when using the helper, only call OBSERVE, NEVER ADD
	virtual void observe(SUBJECT* observable)
	{
		for (std::vector<SUBJECT*>::iterator iter(m_observables.begin());
		iter != m_observables.end();
		iter++)
		{
			if (*iter == observable)
			{
				return;
			}
		}
		
		observable->add(this);
		m_observables.push_back(observable);
	}

private:
	ObserverHelper<SUBJECT>(void);
	ObserverHelper<SUBJECT>(const ObserverHelper<SUBJECT>&);
	ObserverHelper<SUBJECT> operator=(const ObserverHelper<SUBJECT>&);

	std::vector<SUBJECT*>	m_observables;
	Observer<SUBJECT>&		m_observer;
}; // ObserverHelper

} // namespace design_patterns

#endif//OBSERVATION_H