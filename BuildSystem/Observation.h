#pragma once
#ifndef OBSERVATION_H
#define OBSERVATION_H
/**
\file Observation.h

This Observer pattern implementation is somewhat inspired by this article:
http://www.codeproject.com/KB/architecture/observer_with_templates.aspx

\warning THIS FUNCTIONALITY IS NOT THREAD SAFE!

*/

#include <vector>

namespace design_patterns 
{

template<typename SUBJECT, typename ASPECT=SUBJECT>
class Observer
{
public:
	virtual ~Observer(void) {}

	virtual void ignore(SUBJECT* observable, ASPECT* aspect=NULL)=0;
	virtual void observe(SUBJECT* observable, ASPECT* aspect=NULL)=0;
	virtual void notify(SUBJECT* observable, ASPECT* aspect=NULL)=0;
	virtual void notifyDestruction(SUBJECT* observable, ASPECT* aspect=NULL)=0;
}; // class Observer

template<typename SUBJECT, typename ASPECT=SUBJECT>
class Observable
{	
public:
	virtual ~Observable(void) {}
	virtual void add(Observer<SUBJECT, ASPECT>* observer)=0;
	virtual void remove(Observer<SUBJECT, ASPECT>* observer)=0;

protected:	
	// call notify() on all observers
	virtual void update(ASPECT* aspect)=0;
}; // class Observable

template<typename SUBJECT, typename ASPECT=SUBJECT>
class ObservableHelper 
: Observable<SUBJECT, ASPECT>
{
public:
	explicit ObservableHelper(Observable<SUBJECT, ASPECT>& observable)
	: m_observable(observable)
	{
		// empty
	}
	
	virtual ~ObservableHelper() 
	{
		for (std::vector<Observer<SUBJECT, ASPECT> *>::iterator iter = m_observers.begin();
		iter != m_observers.end();
		iter++)
		{
			(*iter)->notifyDestruction(static_cast<SUBJECT*>(&m_observable));
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

	virtual void update(ASPECT* aspect)
	{
		for (std::vector<Observer<SUBJECT, ASPECT> *>::iterator iter = m_observers.begin();
		iter != m_observers.end();
		iter++)
		{
			(*iter)->notify(static_cast<SUBJECT*>(&m_observable), aspect);
		}
	}

private:
	ObservableHelper<SUBJECT, ASPECT>(void);
	ObservableHelper<SUBJECT, ASPECT>(const ObservableHelper<SUBJECT, ASPECT>&);
	ObservableHelper<SUBJECT, ASPECT> operator=(const ObservableHelper<SUBJECT, ASPECT>&);

	Observable<SUBJECT, ASPECT>&				m_observable;
	std::vector<Observer<SUBJECT, ASPECT> *>	m_observers;
}; // ObservableHelper

template<typename SUBJECT, typename ASPECT=SUBJECT>
class ObserverHelper
: Observer<SUBJECT, ASPECT>
{
public:
	explicit ObserverHelper(Observer<SUBJECT, ASPECT>& observer)
	: m_observer(observer)
	{
		for (std::vector<SUBJECT*>::iterator iter(m_observables.begin());
		iter != m_observables.end();
		iter++)
		{
			(*iter)->remove(this);
		}		
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
	
	virtual void ignore(SUBJECT* observable, ASPECT* aspect=NULL)
	{
		for (std::vector<SUBJECT*>::iterator iter(m_observables.begin());
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

	virtual void notify(SUBJECT* observable, ASPECT* aspect=NULL)
	{
		m_observer.notify(observable, aspect);
	}

	virtual void notifyDestruction(SUBJECT* observable, ASPECT* aspect=NULL)
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

	virtual void observe(SUBJECT* observable, ASPECT* aspect=NULL)
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
	ObserverHelper<SUBJECT, ASPECT>(void);
	ObserverHelper<SUBJECT, ASPECT>(const ObserverHelper<SUBJECT, ASPECT>&);
	ObserverHelper<SUBJECT, ASPECT> operator=(const ObserverHelper<SUBJECT, ASPECT>&);

	std::vector<SUBJECT*>		m_observables;
	Observer<SUBJECT, ASPECT>&	m_observer;
}; // ObserverHelper

} // namespace design_patterns

#endif//OBSERVATION_H