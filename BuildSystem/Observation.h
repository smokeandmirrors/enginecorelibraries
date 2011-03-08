#pragma once
#ifndef OBSERVATION_H
#define OBSERVATION_H
/**
\file Observation.h

This Observer pattern implementation is somewhat inspired by this article:
http://www.codeproject.com/KB/architecture/observer_with_templates.aspx

\warning THIS FUNCTIONALITY IS NOT THREAD SAFE!

*/

#include <algorithm>

namespace design_patterns 
{

template<typename SUBJECT, typename ASPECT=SUBJECT&>
class Observable;

template<typename SUBJECT, typename ASPECT=SUBJECT&>
class Observer
{
	/** 
	ignore and observer are to force the client to make sure that they do 
	not leave deleted Observers registered with some Observable 
	*/
public:
	virtual ~Observer(void) {}
	virtual void ignore(Observable<SUBJECT, ASPECT>* observable)=0;
	// this has to be notify(SUBJECT& observable, ASPECT aspect)
	virtual void notify(Observable<SUBJECT, ASPECT>* observable, ASPECT aspect)=0;
	virtual void notifyDestruction(Observable<SUBJECT, ASPECT>* observable)=0;
	virtual void observe(Observable<SUBJECT, ASPECT>* observable)=0;
}; // Observer

template<typename SUBJECT, typename ASPECT>
class Observable
{
public:
	virtual ~Observable(void) {}
	virtual void add(Observer<SUBJECT, ASPECT>* observer)=0;
	virtual void remove(Observer<SUBJECT, ASPECT>* observer)=0;
	virtual void update(ASPECT aspect)=0;
}; // class Observable

/**
These assist to implement observation (including hopefully in a multi-threaded environment, 
perhaps with a mutexes created on all operations that manipulate the data 
in the observable).

*/
template<typename SUBJECT, typename ASPECT=SUBJECT&>
class ObservableHelper 
: Observable<SUBJECT, ASPECT>
{
public:
	explicit ObservableHelper(Observable<SUBJECT, ASPECT>& observable)
	: m_observable(observable)
	{
		/* empty */
	}
	
	virtual ~ObservableHelper() 
	{
		for (std::vector<Observer<SUBJECT, ASPECT> *>::iterator iter = m_observers.begin();
		iter != m_observers.end();
		iter++)
		{
			(*iter)->notifyDestruction(&m_observable);
		}
	}
	
	virtual void add(Observer<SUBJECT, ASPECT>* observer)
	{
		for (std::vector<Observer<SUBJECT, ASPECT> *>::iterator iter = m_observers.begin();
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
	
	virtual void remove(Observer<SUBJECT, ASPECT>* observer)
	{
		for (std::vector<Observer<SUBJECT, ASPECT> *>::iterator iter = m_observers.begin();
		iter != m_observers.end();
		iter++)
		{
			if (*iter == observer)
			{
				m_observers.erase(iter);
				return;
			}
		}
	}

	virtual void update(ASPECT aspect)
	{
		for (std::vector<Observer<SUBJECT, ASPECT> *>::iterator iter = m_observers.begin();
			iter != m_observers.end();
			iter++)
		{
			(*iter)->notify(&m_observable, aspect);
		}
	}

private:
	ObservableHelper<SUBJECT, ASPECT>(void);
	ObservableHelper<SUBJECT, ASPECT>(const ObservableHelper<SUBJECT, ASPECT>&);
	ObservableHelper<SUBJECT, ASPECT> operator=(const ObservableHelper<SUBJECT, ASPECT>&);

	Observable<SUBJECT, ASPECT>&				m_observable;
	std::vector<Observer<SUBJECT, ASPECT> *>	m_observers;
}; // ObservableHelper

template<typename SUBJECT, typename ASPECT=SUBJECT&>
class ObserverHelper
: Observer<SUBJECT, ASPECT>
{
public:
	explicit ObserverHelper(Observer<SUBJECT, ASPECT>& observer)
	: m_observer(observer)
	{
		for (std::vector<Observable<SUBJECT, ASPECT> *>::iterator iter(m_observables.begin());
		iter != m_observables.end();
		iter++)
		{
			(*iter)->remove(this);
		}		
	}
	
	virtual ~ObserverHelper(void) 
	{
		for (std::vector<Observable<SUBJECT, ASPECT> *>::iterator iter(m_observables.begin());
		iter != m_observables.end();
		iter++)
		{
			(*iter)->remove(this);
		}
	}
	
	virtual void ignore(Observable<SUBJECT, ASPECT>* observable)
	{
		for (std::vector<Observable<SUBJECT, ASPECT> *>::iterator iter(m_observables.begin());
		iter != m_observables.end();
		iter++)
		{
			if (*iter == observable)
			{
				observable->remove(this);
				m_observables.erase(iter);
				return;
			}
		}		
	}

	virtual void notify(Observable<SUBJECT, ASPECT>* observable, ASPECT aspect)
	{
		m_observer.notify(observable, aspect);
	}

	virtual void notifyDestruction(Observable<SUBJECT, ASPECT>* observable)
	{
		for (std::vector<Observable<SUBJECT, ASPECT> *>::iterator iter(m_observables.begin());
		iter != m_observables.end();
		iter++)
		{
			if (*iter == observable)
			{
				m_observables.erase(iter);
				return;
			}
		}
	}

	virtual void observe(Observable<SUBJECT, ASPECT>* observable)
	{
		for (std::vector<Observable<SUBJECT, ASPECT> *>::iterator iter(m_observables.begin());
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
	ObserverHelper<SUBJECT, ASPECT>(void);
	ObserverHelper<SUBJECT, ASPECT>(const ObserverHelper<SUBJECT, ASPECT>&);
	ObserverHelper<SUBJECT, ASPECT> operator=(const ObserverHelper<SUBJECT, ASPECT>&);

	std::vector<Observable<SUBJECT, ASPECT> *>	m_observables;
	Observer<SUBJECT, ASPECT>&					m_observer;
}; // ObserverHelper

} // namespace design_patterns

#endif//OBSERVATION_H