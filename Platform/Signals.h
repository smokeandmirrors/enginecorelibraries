#pragma once
#ifndef SIGNALS_H
#define SIGNALS_H
/**
\file Signals.h
This files implements a type safe Signal/Slot delegate system.  It owes all of its
inspiration, and much (if not most) of its implementation to Sarah Thompson
and her work here: http://sigslot.sourceforge.net/

usage:
The signal::Transmitter* classes can be used to broadcast, that is call functions
on objects that have connected to it.  The signal::Receiver defines the interfaces
for receiving the signal from the Transmitter* classes.  

implementation:
Transmitter0 is implemented explicitly below.  Transmitter1 through Transmitter5
are implemented via the use of the SIGNALS_DECLARE_TRANSMITTER macro, and the
macros defined in TemplateArguments.h.  If you need more than 5 arguments 
to be passed into the receivers functions, it would be easiest to add the 
necessary macros to TemplateArguments, and simply add entries to the SIGNALS_DECLARE_TRANSMITTER 
uses below.

What should be considered the real public interface of the Transmitter class is
as follows:
connect() - register a member function, and an object with the transmitter
disconnect() - unregister all functions registered with an object with the transmitter
all other Transmitter functions should be considered protected, only to be called
by the owner of the Transmitter.    

The receiver methods shouldn't be considered public at all, they should
only be called by the Trasmitters with which it has registered.

\author Smoke and Mirrors Development
\htmlonly
<A HREF="smokeandmirrorsdevelopment@gmail.com">smokeandmirrorsdevelopment@gmail.com</A>
<BR>
&copy;2009-2011 Smoke and Mirrors Development
<BR>
\endhtmlonly
\date 4/5/2011

<DEVELOPMENT STATUS>
Current Draft		:	0.0
Current Phase		:   DEVELOPMENT
Purpose				:	DEPLOYMENT
Unit Tested			:	PARTIALLY
Used in development	:	NO
Used in experiments :	YES
Tested in the field	:	NO
*/

#include <set>
// #include <functional> this might just replace all the mess below
#include "Synchronization.h"

namespace signals
{
class Receiver;

/**
interface for classes to hide the template nature of the all
the different Transmitter classes.  This allows for type safe usage
for clients, but more generic implementation here.
*/
class Transmitter
{
public:
	friend class Receiver;
	friend class ReceiverBase;
	friend class ReceiverMember;

	virtual ~Transmitter(void)=0 {}

protected:
	/** called by the disconnection process, do not call directly */
	virtual void onDisconnect(Receiver* receiver)=0;
	/** called by the copy constructor process */
	virtual void replicate(const Receiver* receiver, Receiver* new_receiver)=0;
};

/**
interface for classes that can connect to Transmitters
and receiver a signal (allow member functions to be called when connected)
*/
class Receiver
{
public:
	typedef std::set<Transmitter*> transmitter_set;
	typedef transmitter_set::const_iterator const_iterator;

	virtual ~Receiver(void)=0 {}
	/** manually terminates all connections with all Transmitters */
	virtual void ceaseReception(void)=0;
	/** called by the connection process, do not call directly */
	virtual void onConnect(Transmitter* transmitter)=0;
	/** called by the disconnection process, do not call directly */
	virtual void onDisconnect(Transmitter* transmitter)=0;
}; // 

/**
class that makes it easy to make a new concrete class
that derives from Receiver
*/
class ReceiverBase
: public Receiver
{
public:
	ReceiverBase(void)
	{ 
		SET_THREAD_SPIN_COUNT(m_mutex, 12);
	}

	ReceiverBase(const ReceiverBase& receiver)
	{
		SYNC(m_mutex);
		const_iterator iter = receiver.m_transmitters.begin();
		const_iterator sentinel = receiver.m_transmitters.end();

		while (iter != sentinel)
		{
			(*iter)->replicate(&receiver, this);
			m_transmitters.insert(*iter);
			++iter;
		}
	} 
	
	/** 
	disconnects from all Transmitters, so the children
	of this class don't leave any deleted pointers registered
	with Transmitters
	*/
	virtual ~ReceiverBase(void)
	{
		disconnectAll();
	}

	/**
	manually disconnect from all Transmitters,
	and clear the list
	*/
	void ceaseReception(void)
	{
		SYNC(m_mutex);
		disconnectAll();
		m_transmitters.erase(m_transmitters.begin(), m_transmitters.end());
	}

	/**
	called by the connection process, adds the transmitter
	to the list
	*/
	void onConnect(Transmitter* transmitter)
	{
		SYNC(m_mutex);
		m_transmitters.insert(transmitter);
	}

	/**
	called by the disconnection process, removes the transmitter
	from the list
	*/
	void onDisconnect(Transmitter* transmitter)
	{
		SYNC(m_mutex);
		m_transmitters.erase(transmitter);
	}
protected:
	/**
	disconnect from all Transmitters, tell them that this receiver has 
	disconnected, but don't clear the list
	*/
	void disconnectAll(void)
	{
		SYNC(m_mutex);
		const_iterator iter = m_transmitters.begin();
		const_iterator sentinel = m_transmitters.end();

		while (iter != sentinel)
		{
			(*iter)->onDisconnect(this);
			++iter;
		}
	}
	
private:
	/** thread synchonizer */
	DECLARE_MUTEX(m_mutex);
	/** a list of all transmitters this object is registered with */
	transmitter_set				m_transmitters;
};

/**
if you prefer a HAS-A relationship to receiver,
add one of these to your class, and implement the methods:

void ceaseReception(void);
void onConnect(signals::Transmitter* sender);
void onDisconnect(signals::Transmitter* sender);

by simply calling the same methods on your class' instance
of ReceiverMember.
*/
class ReceiverMember
: public Receiver
{
public:
	ReceiverMember(void)
	: m_receiver(NULL)
	{ 
		SET_THREAD_SPIN_COUNT(m_mutex, 12);
	}

	ReceiverMember(const ReceiverMember& receiver)
	: m_receiver(NULL)
	{
		SYNC(m_mutex);
		const_iterator iter = receiver.m_transmitters.begin();
		const_iterator sentinel = receiver.m_transmitters.end();

		while (iter != sentinel)
		{
			(*iter)->replicate(&receiver, this);
			m_transmitters.insert(*iter);
			++iter;
		}
	} 

	virtual ~ReceiverMember(void)
	{
		disconnectAll();
	}

	/**
	manually disconnect from all Transmitters,
	and clear the list
	*/
	void ceaseReception(void)
	{
		SYNC(m_mutex);
		disconnectAll();
		m_transmitters.erase(m_transmitters.begin(), m_transmitters.end());
	}
	
	/**
	called by the connection process, adds the transmitter
	to the list
	*/
	void onConnect(Transmitter* transmitter)
	{
		SYNC(m_mutex);
		m_transmitters.insert(transmitter);
	}

	/**
	called by the disconnection process, removes the transmitter
	from the list
	*/
	void onDisconnect(Transmitter* transmitter)
	{
		SYNC(m_mutex);
		m_transmitters.erase(transmitter);
	}

	/**
	set the actual owner, the object that
	will actually receive the signals
	*/
	void setReceiver(Receiver* receiver)
	{
		m_receiver = receiver;
	}

protected:
	/**
	disconnect from all Transmitters, tell them that this receiver has 
	disconnected, but don't clear the list
	*/
	void disconnectAll(void)
	{
		SYNC(m_mutex);
		const_iterator iter = m_transmitters.begin();
		const_iterator sentinel = m_transmitters.end();

		while (iter != sentinel)
		{
			(*iter)->onDisconnect(m_receiver);
			++iter;
		}
	}
	
private:
	/** thread synchonizer */
	DECLARE_MUTEX(m_mutex);
	/** the actual owner, the object that will actually receive the signals */
	Receiver*				m_receiver;
	/** a list of all transmitters this object is registered with */
	transmitter_set				m_transmitters;
};

/** Transmits signals with no arguments */
class Transmitter0 
: public Transmitter
{
	typedef void StaticFunction(void);
		
	/** abstraction for all of the receivers that have registered with this transmitter */
	class Connection
	{
	public:
		Connection(void)
		: m_next(NULL)
		{
			/* empty */
		}

		virtual ~Connection(void)=0 {};
		virtual Connection*	clone(void)=0;
		virtual Connection*	duplicate(Receiver* receiver)=0;
		virtual bool isFunction(StaticFunction*) const=0;
		virtual bool isReceiver(const Receiver*) const=0;
		virtual void onConnect(Transmitter&)=0;
		virtual void onDisconnect(Transmitter&)=0;
		virtual void transmit(void)=0;
		Connection* m_next;
	};
	/** 
	template abstraction for receivers that registered non-const 
	member functions with this transmitter
	*/
	template<class RECEIVER>
	class volatile0 : public Connection
	{
	public:
		volatile0(RECEIVER* object, void (RECEIVER::* function)(void))
		: m_object(object)
		, m_function(function)
		{ /* empty */ }

		virtual Connection* clone(void)
		{
			return new volatile0<RECEIVER>(static_cast<RECEIVER*>(m_object), m_function);
		}

		virtual Connection* duplicate(Receiver* receiver)
		{
			return new volatile0<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}

		virtual bool isFunction(StaticFunction*) const
		{
			return false;
		}

		virtual bool isReceiver(const Receiver* receiver) const
		{
			return m_object == static_cast<const RECEIVER*>(receiver);
		}

		virtual void onConnect(Transmitter& transmitter)
		{
			m_object->onConnect(&transmitter);
		}

		virtual void onDisconnect(Transmitter& transmitter)
		{
			m_object->onDisconnect(&transmitter);
		}

		virtual void transmit(void) 
		{
			(m_object->*m_function)();
		}

	private:
		RECEIVER*			m_object;
		void (RECEIVER::*	m_function)(void);
	};

	/** 
	template abstraction for receivers that registered const 
	member functions with this transmitter
	*/
	template<class RECEIVER>
	class const0 : public Connection
	{
	public:
		const0(RECEIVER* object, void (RECEIVER::* function)(void) const)
		: m_object(object)
		, m_function(function)
		{ /* empty */ }

		virtual Connection* clone(void)
		{
			return new const0<RECEIVER>(static_cast<RECEIVER*>(m_object), m_function);
		}

		virtual Connection* duplicate(Receiver* receiver)
		{
			return new const0<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}

		virtual bool isFunction(StaticFunction*) const
		{
			return false;
		}

		virtual bool isReceiver(const Receiver* receiver) const
		{
			return m_object == static_cast<RECEIVER*>(receiver);
		}

		virtual void onConnect(Transmitter& transmitter)
		{
			m_object->onConnect(&transmitter);
		}

		virtual void onDisconnect(Transmitter& transmitter)
		{
			m_object->onDisconnect(&transmitter);
		}
		
		virtual void transmit(void) 
		{
			(m_object->*m_function)();
		}

	private:
		RECEIVER*			m_object;
		void (RECEIVER::*	m_function)(void) const;
	};

	class static0 : public Connection
	{
	public:
		static0(StaticFunction& function)
			: m_function(function)
		{ /* empty */ }

		virtual Connection* clone(void)
		{
			return new static0(m_function);
		}

		virtual Connection* duplicate(Receiver*)
		{
			return clone();
		}

		virtual bool isFunction(StaticFunction* function) const
		{
			return function == &m_function;
		}

		virtual bool isReceiver(const Receiver*) const
		{
			return false;
		}

		virtual void onConnect(Transmitter&)
		{
			/* empty */
		}

		virtual void onDisconnect(Transmitter&)
		{
			/* empty */
		}

		virtual void transmit(void)
		{
			m_function();
		}

	private:
		StaticFunction& m_function;
	}; // 

public:
	Transmitter0(void)
		: m_receivers(NULL)
		, m_transmissionIter(NULL)
		, m_isRepeatTransmissionRequired(false)
		, m_isTransmitting(false)
	{ /* empty */ }

	Transmitter0(const Transmitter0& s)
	: Transmitter(s)
	, m_receivers(NULL)
	, m_transmissionIter(NULL)
	, m_isRepeatTransmissionRequired(false)
	, m_isTransmitting(false)
	{
		SYNC(m_mutex);
		Connection* iter(s.m_receivers);
		Connection* previous(NULL);
		Connection** destinationIter = &m_receivers;
		while (iter)
		{
			iter->onConnect(*this);
			*destinationIter = iter->clone();
			
			if (previous)
			{	
				previous->m_next = *destinationIter;
			}
			
			previous = *destinationIter;
			iter = iter->m_next;
		}
	}

	~Transmitter0(void)
	{
		disconnectAll();
	}
	
	/** manually disconnect from all receivers, and clear the list */
	void ceaseTransmission(void)
	{
		SYNC(m_mutex);
		disconnectAll();
		m_isTransmitting = false;
		m_transmissionIter = NULL;
		m_receivers = NULL;
	}

	/** \todo connect unchecked! */

	/** connect to a receiver via a non-const method*/
	template<class RECEIVER>
	void connect(RECEIVER* receiver, void (RECEIVER::* function)(void))
	{
		if (receiver && function)
		{
			SYNC(m_mutex);
			Connection* iter(m_receivers);

			while (iter)
			{
				if (iter->isReceiver(receiver))
				{
					return;
				}

				iter = iter->m_next;
			}

			Connection* connection(new volatile0<RECEIVER>(receiver, function));
			connection->m_next = m_receivers;
			m_receivers = connection;
			receiver->onConnect(this);
		}
	}

	/** connect to a receiver via a const method*/
	template<class RECEIVER>
	void connect(RECEIVER* receiver, void (RECEIVER::* function)(void) const)
	{
		if (receiver && function)
		{
			SYNC(m_mutex);
			Connection* iter(m_receivers);

			while (iter)
			{
				if (iter->isReceiver(receiver))
				{
					return;
				}

				iter = iter->m_next;
			}

			Connection* connection(new const0<RECEIVER>(receiver, function));
			connection->m_next = m_receivers;
			m_receivers = connection;
			receiver->onConnect(this);
		}
	}

	/** connect a raw function */
	void connect(StaticFunction& function)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);

		while (iter)
		{
			if (iter->isFunction(&function))
			{
				return;
			}

			iter = iter->m_next;
		}

		Connection* connection(new static0(function));
		connection->m_next = m_receivers;
		m_receivers = connection;
	}

	void disconnect(Receiver* receiver)
	{
		disconnect(receiver, NULL);
	}

	void disconnect(StaticFunction& function)
	{
		disconnect(NULL, function);
	}

	/** call each method registered by all receivers */
	void transmit(void) 
	{
		SYNC(m_mutex);
		if (m_isTransmitting)
		{
			m_isRepeatTransmissionRequired = true;
		}
		else
		{
			m_isTransmitting = true;
			m_transmissionIter = m_receivers;
			// the size of the receiver list can change during transmission
			while (m_transmissionIter) 
			{	
				m_transmissionIter->transmit();
				// calling transmit() might have triggered the removal of the receiver
				if (m_transmissionIter)
					m_transmissionIter = m_transmissionIter->m_next;
				else
					m_transmissionIter = m_receivers;
			}
					
			m_isTransmitting = false;
			
			if (m_isRepeatTransmissionRequired)
			{
				m_isRepeatTransmissionRequired = false;
				transmit();
			}
		}
	}

	/** call each method registered by all receivers */
	inline void operator()(void) 
	{
		transmit();
	}

protected:
	
	void disconnect(Receiver* receiver, StaticFunction* function)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);
		Connection* previous(NULL);

		while (iter)
		{
			bool isFound;

			if (iter->isReceiver(receiver))
			{
				receiver->onDisconnect(this);
				isFound = true;	
			}
			else
			{
				isFound = iter->isFunction(function);
			}

			if (isFound)
			{	
				if (previous)
				{	
					previous->m_next = iter->m_next;
				}
				else 
				{
					m_receivers = iter->m_next;
				}

				// if transmitting...	
				if (m_isTransmitting)
				{	// ... and we just removed the transmission iter ...
					if (m_transmissionIter == iter)
					{	// .. set the iterator back one to preserve the transmission iteration
						m_transmissionIter = previous;
					}
				}

				delete iter;
				break;
			}

			previous = iter;
			iter = iter->m_next;
		}
	}

	/** disconnects all receivers, but doesn't empty the list */
	void disconnectAll(void)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);
		
		while (iter)
		{
			iter->onDisconnect(*this);
			Connection* stale(iter);
			iter = iter->m_next;
			delete stale;
		}

		m_receivers = NULL;
	}
	
	/** called by the be receivers that are disconnecting of their own accord */
	void onDisconnect(Receiver* receiver)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);
		Connection* previous(NULL);

		while (iter)
		{
			if (iter->isReceiver(receiver))
			{
				if (previous)
				{
					previous->m_next = iter->m_next;
				}
				else
				{
					m_receivers = iter->m_next;
				}

				delete iter;
				break;
			}

			previous = iter;
			iter = iter->m_next;
		}
	}

	/** helps with copy constructors of receivers */
	void replicate(const Receiver* receiver, Receiver* new_receiver)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);
		while (iter)
		{
			if (iter->isReceiver(receiver))
			{	/** the new reiver will be registered with all transmitters of receiver*/
				Connection* connection = iter->duplicate(new_receiver);
				connection->m_next = m_receivers;
				m_receivers = connection;
				break;
			}
		}
	}

private:
	Connection* m_receivers;   
	Connection* m_transmissionIter;
	DECLARE_MUTABLE_MUTEX(m_mutex);
	bool m_isRepeatTransmissionRequired;
	bool m_isTransmitting;
}; // Transmitter0

/* begin auto generated code */
template<typename ARG_1>
class Transmitter1 : public Transmitter
{
	typedef void StaticFunction1(ARG_1);

	class Connection
	{
	public:
		Connection(void) : m_next(NULL) { /* empty */ };
		virtual ~Connection(void)=0 { /* empty */ };
		virtual Connection* clone(void)=0;
		virtual Connection* duplicate(Receiver* receiver)=0;
		virtual bool isFunction(StaticFunction1*) const=0;
		virtual bool isReceiver(const Receiver*) const=0;
		virtual void onConnect(Transmitter&)=0;
		virtual void onDisconnect(Transmitter&)=0;
		virtual void transmit(ARG_1)=0;
		Connection* m_next;
	}; // class Connection
	template< class RECEIVER >
	class volatile1
		: public Connection
	{
	public:
		volatile1(RECEIVER* object, void (RECEIVER::* function)(ARG_1))
			: m_object(object)
			, m_function(function)
		{ /* empty */ }
		virtual Connection* clone(void)
		{
			return new volatile1<RECEIVER>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new volatile1<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual bool isFunction(StaticFunction1*) const
		{
			return false;
		}
		virtual bool isReceiver(const Receiver* receiver) const
		{
			return m_object == static_cast<const RECEIVER*>(receiver);
		}
		virtual void onConnect(Transmitter& transmitter)
		{
			m_object->onConnect(&transmitter);
		}
		virtual void onDisconnect(Transmitter& transmitter)
		{
			m_object->onDisconnect(&transmitter);
		}
		virtual void transmit(ARG_1 arg1)
		{
			(m_object->*m_function)(arg1);
		}
	private:
		RECEIVER* m_object;
		void (RECEIVER::* m_function)(ARG_1);
	}; // class volatile1
	template<class RECEIVER >
	class const1
		: public Connection
	{
	public:
		const1(RECEIVER* object, void (RECEIVER::* function)(ARG_1) const)
			: m_object(object)
			, m_function(function)
		{ /* empty */ }
		virtual Connection* clone(void)
		{
			return new const1<RECEIVER>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new const1<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual bool isFunction(StaticFunction1*) const
		{
			return false;
		}
		virtual bool isReceiver(const Receiver* receiver) const
		{
			return m_object == static_cast<const RECEIVER*>(receiver);
		}
		virtual void onConnect(Transmitter& transmitter)
		{
			m_object->onConnect(&transmitter);
		}
		virtual void onDisconnect(Transmitter& transmitter)
		{
			m_object->onDisconnect(&transmitter);
		}
		virtual void transmit(ARG_1 arg1)
		{
			(m_object->*m_function)(arg1);
		}
	private:
		RECEIVER* m_object;
		void (RECEIVER::* m_function)(ARG_1) const;
	}; // class const1
	class static1
		: public Connection
	{
	public:
		static1(StaticFunction1& function)
			: m_function(function)
		{ /* empty */ }
		virtual Connection* clone(void)
		{
			return new const1<RECEIVER>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new const1<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual bool isFunction(StaticFunction1* function) const
		{
			return &m_function == function;
		}
		virtual bool isReceiver(const Receiver*) const
		{
			return false;
		}
		virtual void onConnect(Transmitter& transmitter)
		{
			/* empty */;
		}
		virtual void onDisconnect(Transmitter& transmitter)
		{
			/* empty */;
		}
		virtual void transmit(ARG_1 arg1)
		{
			m_function(arg1);
		}
	private:
		StaticFunction1& m_function;
	}; // class static1
public:
	Transmitter1(void)
		: m_receivers(NULL)
		, m_transmissionIter(NULL)
		, m_isRepeatTransmissionRequired(false)
		, m_isTransmitting(false)
	{ /* empty */ }
	Transmitter1(const Transmitter1& source)
		: Transmitter(source)
		, m_receivers(NULL)
		, m_transmissionIter(NULL)
		, m_isRepeatTransmissionRequired(false)
		, m_isTransmitting(false)
	{
		SYNC(m_mutex);
		Connection* iter(source.m_receivers);
		Connection* previous(NULL);
		Connection** destinationIter = &m_receivers;
		while (iter)
		{
			iter->onConnect(*this);
			*destinationIter = iter->clone();

			if (previous)
			{
				previous->m_next = *destinationIter;
			}

			previous = *destinationIter
				iter = iter->m_next;
		}
	}
	virtual ~Transmitter1(void)
	{
		disconnectAll();
	}
	void ceaseTransmission(void)
	{
		SYNC(m_mutex);
		disconnectAll();
		m_isTransmitting = false;
		m_transmissionIter = NULL;
		m_receivers = NULL;
	}
	template<class RECEIVER>
	void connect(RECEIVER* receiver, void (RECEIVER::* function)(ARG_1))
	{
		if (receiver && function)
		{
			SYNC(m_mutex);
			Connection* iter(m_receivers);

			while (iter)
			{
				if (iter->isReceiver(receiver))
				{
					return;
				}

				iter = iter->m_next;
			}

			Connection* connection(new volatile1<RECEIVER>(receiver, function));
			connection->m_next = m_receivers;
			m_receivers = connection;
			receiver->onConnect(this);
		}
	}
	template<class RECEIVER>
	void connect(RECEIVER* receiver, void (RECEIVER::* function)(ARG_1) const)
	{
		if (receiver && function)
		{
			SYNC(m_mutex);
			Connection* iter(m_receivers);

			while (iter)
			{
				if (iter->isReceiver(receiver))
				{
					return;
				}

				iter = iter->m_next;
			}

			Connection* connection(new const1<RECEIVER>(receiver, function));
			connection->m_next = m_receivers;
			m_receivers = connection;
			receiver->onConnect(this);
		}
	}
	void connect(StaticFunction1& function)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);

		while (iter)
		{
			if (iter->isFunction(&function))
			{
				return;
			}

			iter = iter->m_next;
		}

		Connection* connection(new static1(function));
		connection->m_next = m_receivers;
		m_receivers = connection;
	}
	void disconnect(Receiver* receiver)
	{
		disconnect(receiver, NULL);
	}
	void disconnect(StaticFunction1& function)
	{
		disconnect(NULL, function);
	}
	void transmit(ARG_1 arg1)
	{
		SYNC(m_mutex);
		if (m_isTransmitting)
		{
			m_isRepeatTransmissionRequired = true;
		}
		else
		{
			m_isTransmitting = true;
			m_transmissionIter = m_receivers;
			// the receiver list can change be modified transmission
			while (m_transmissionIter)
			{
				m_transmissionIter->transmit(arg1);
				// calling transmit() might have triggered the removal of the receiver
				if (m_transmissionIter)
					m_transmissionIter = m_transmissionIter->m_next;
				else
					m_transmissionIter = m_receivers;
			}

			m_isTransmitting = false;

			if (m_isRepeatTransmissionRequired)
			{
				m_isRepeatTransmissionRequired = false;
				transmit(arg1);
			}
		}
	}
	inline void operator()(ARG_1 arg1)
	{
		transmit(arg1);
	}
protected:
	void disconnect(Receiver* receiver, StaticFunction1* function)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);
		Connection* previous(NULL);

		while (iter)
		{
			bool isFound;

			if (iter->isReceiver(receiver))
			{
				receiver->onDisconnect(this);
				isFound = true;
			}
			else
			{
				isFound = iter->isFunction(function);
			}

			if (isFound)
			{
				if (previous)
				{
					previous->m_next = iter->m_next;
				}
				else 
				{
					m_receivers = iter->m_next;
				}

				// if transmitting...	
				if (m_isTransmitting)
				{	// ... and we just removed the transmission iter ...
					if (m_transmissionIter == iter)
					{	// .. set the iterator back one to preserve the transmission iteration
						m_transmissionIter = previous;
					}
				}

				delete iter;
				break;
			}				
			previous = iter;
			iter = iter->m_next;
		}
	}
	void disconnectAll(void)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);

		while (iter)
		{
			iter->onDisconnect(*this);
			Connection* stale(iter);
			iter = iter->m_next;
			delete stale;
		}

		m_receivers = NULL;
	}
	void onDisconnect(Receiver* receiver)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);
		Connection* previous(NULL);

		while (iter)
		{
			if (iter->isReceiver(receiver))
			{
				if (previous)
				{
					previous->m_next = iter->m_next;
				}
				else
				{
					m_receivers = iter->m_next;
				}

				delete iter;
				break;
			}

			previous = iter;
			iter = iter->m_next;
		}
	}
	void replicate(const Receiver* receiver, Receiver* new_receiver)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);

		while (iter)
		{
			if (iter->isReceiver(receiver))
			{
				Connection* connection = iter->duplicate(new_receiver);
				connection->m_next = m_receivers;
				m_receivers = connection;
				break;
			}
		}
	}
private:
	DECLARE_MUTABLE_MUTEX(m_mutex)
	Connection* m_receivers;
	Connection* m_transmissionIter;
	bool m_isRepeatTransmissionRequired;
	bool m_isTransmitting;
}; // class Transmitter1

template<typename ARG_1, typename ARG_2>
class Transmitter2 : public Transmitter
{
	typedef void StaticFunction2(ARG_1, ARG_2);

	class Connection
	{
	public:
		Connection(void) : m_next(NULL) { /* empty */ };
		virtual ~Connection(void)=0 { /* empty */ };
		virtual Connection* clone(void)=0;
		virtual Connection* duplicate(Receiver* receiver)=0;
		virtual bool isFunction(StaticFunction2*) const=0;
		virtual bool isReceiver(const Receiver*) const=0;
		virtual void onConnect(Transmitter&)=0;
		virtual void onDisconnect(Transmitter&)=0;
		virtual void transmit(ARG_1, ARG_2)=0;
		Connection* m_next;
	}; // class Connection
	template< class RECEIVER >
	class volatile2
		: public Connection
	{
	public:
		volatile2(RECEIVER* object, void (RECEIVER::* function)(ARG_1, ARG_2))
			: m_object(object)
			, m_function(function)
		{ /* empty */ }
		virtual Connection* clone(void)
		{
			return new volatile2<RECEIVER>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new volatile2<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual bool isFunction(StaticFunction2*) const
		{
			return false;
		}
		virtual bool isReceiver(const Receiver* receiver) const
		{
			return m_object == static_cast<const RECEIVER*>(receiver);
		}
		virtual void onConnect(Transmitter& transmitter)
		{
			m_object->onConnect(&transmitter);
		}
		virtual void onDisconnect(Transmitter& transmitter)
		{
			m_object->onDisconnect(&transmitter);
		}
		virtual void transmit(ARG_1 arg1, ARG_2 arg2)
		{
			(m_object->*m_function)(arg1, arg2);
		}
	private:
		RECEIVER* m_object;
		void (RECEIVER::* m_function)(ARG_1, ARG_2);
	}; // class volatile2
	template<class RECEIVER >
	class const2
		: public Connection
	{
	public:
		const2(RECEIVER* object, void (RECEIVER::* function)(ARG_1, ARG_2) const)
			: m_object(object)
			, m_function(function)
		{ /* empty */ }
		virtual Connection* clone(void)
		{
			return new const2<RECEIVER>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new const2<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual bool isFunction(StaticFunction2*) const
		{
			return false;
		}
		virtual bool isReceiver(const Receiver* receiver) const
		{
			return m_object == static_cast<const RECEIVER*>(receiver);
		}
		virtual void onConnect(Transmitter& transmitter)
		{
			m_object->onConnect(&transmitter);
		}
		virtual void onDisconnect(Transmitter& transmitter)
		{
			m_object->onDisconnect(&transmitter);
		}
		virtual void transmit(ARG_1 arg1, ARG_2 arg2)
		{
			(m_object->*m_function)(arg1, arg2);
		}
	private:
		RECEIVER* m_object;
		void (RECEIVER::* m_function)(ARG_1, ARG_2) const;
	}; // class const2
	class static2
		: public Connection
	{
	public:
		static2(StaticFunction2& function)
			: m_function(function)
		{ /* empty */ }
		virtual Connection* clone(void)
		{
			return new const2<RECEIVER>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new const2<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual bool isFunction(StaticFunction2* function) const
		{
			return &m_function == function;
		}
		virtual bool isReceiver(const Receiver*) const
		{
			return false;
		}
		virtual void onConnect(Transmitter& transmitter)
		{
			/* empty */;
		}
		virtual void onDisconnect(Transmitter& transmitter)
		{
			/* empty */;
		}
		virtual void transmit(ARG_1 arg1, ARG_2 arg2)
		{
			m_function(arg1, arg2);
		}
	private:
		StaticFunction2& m_function;
	}; // class static2
public:
	Transmitter2(void)
		: m_receivers(NULL)
		, m_transmissionIter(NULL)
		, m_isRepeatTransmissionRequired(false)
		, m_isTransmitting(false)
	{ /* empty */ }
	Transmitter2(const Transmitter2& source)
		: Transmitter(source)
		, m_receivers(NULL)
		, m_transmissionIter(NULL)
		, m_isRepeatTransmissionRequired(false)
		, m_isTransmitting(false)
	{
		SYNC(m_mutex);
		Connection* iter(source.m_receivers);
		Connection* previous(NULL);
		Connection** destinationIter = &m_receivers;
		while (iter)
		{
			iter->onConnect(*this);
			*destinationIter = iter->clone();

			if (previous)
			{
				previous->m_next = *destinationIter;
			}

			previous = *destinationIter
				iter = iter->m_next;
		}
	}
	virtual ~Transmitter2(void)
	{
		disconnectAll();
	}
	void ceaseTransmission(void)
	{
		SYNC(m_mutex);
		disconnectAll();
		m_isTransmitting = false;
		m_transmissionIter = NULL;
		m_receivers = NULL;
	}
	template<class RECEIVER>
	void connect(RECEIVER* receiver, void (RECEIVER::* function)(ARG_1, ARG_2))
	{
		if (receiver && function)
		{
			SYNC(m_mutex);
			Connection* iter(m_receivers);

			while (iter)
			{
				if (iter->isReceiver(receiver))
				{
					return;
				}

				iter = iter->m_next;
			}

			Connection* connection(new volatile2<RECEIVER>(receiver, function));
			connection->m_next = m_receivers;
			m_receivers = connection;
			receiver->onConnect(this);
		}
	}
	template<class RECEIVER>
	void connect(RECEIVER* receiver, void (RECEIVER::* function)(ARG_1, ARG_2) const)
	{
		if (receiver && function)
		{
			SYNC(m_mutex);
			Connection* iter(m_receivers);

			while (iter)
			{
				if (iter->isReceiver(receiver))
				{
					return;
				}

				iter = iter->m_next;
			}

			Connection* connection(new const2<RECEIVER>(receiver, function));
			connection->m_next = m_receivers;
			m_receivers = connection;
			receiver->onConnect(this);
		}
	}
	void connect(StaticFunction2& function)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);

		while (iter)
		{
			if (iter->isFunction(&function))
			{
				return;
			}

			iter = iter->m_next;
		}

		Connection* connection(new static2(function));
		connection->m_next = m_receivers;
		m_receivers = connection;
	}
	void disconnect(Receiver* receiver)
	{
		disconnect(receiver, NULL);
	}
	void disconnect(StaticFunction2& function)
	{
		disconnect(NULL, function);
	}
	void transmit(ARG_1 arg1, ARG_2 arg2)
	{
		SYNC(m_mutex);
		if (m_isTransmitting)
		{
			m_isRepeatTransmissionRequired = true;
		}
		else
		{
			m_isTransmitting = true;
			m_transmissionIter = m_receivers;
			// the receiver list can change be modified transmission
			while (m_transmissionIter)
			{
				m_transmissionIter->transmit(arg1, arg2);
				// calling transmit() might have triggered the removal of the receiver
				if (m_transmissionIter)
					m_transmissionIter = m_transmissionIter->m_next;
				else
					m_transmissionIter = m_receivers;
			}

			m_isTransmitting = false;

			if (m_isRepeatTransmissionRequired)
			{
				m_isRepeatTransmissionRequired = false;
				transmit(arg1, arg2);
			}
		}
	}
	inline void operator()(ARG_1 arg1, ARG_2 arg2)
	{
		transmit(arg1, arg2);
	}
protected:
	void disconnect(Receiver* receiver, StaticFunction2* function)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);
		Connection* previous(NULL);

		while (iter)
		{
			bool isFound;

			if (iter->isReceiver(receiver))
			{
				receiver->onDisconnect(this);
				isFound = true;
			}
			else
			{
				isFound = iter->isFunction(function);
			}

			if (isFound)
			{
				if (previous)
				{
					previous->m_next = iter->m_next;
				}
				else 
				{
					m_receivers = iter->m_next;
				}

				// if transmitting...	
				if (m_isTransmitting)
				{	// ... and we just removed the transmission iter ...
					if (m_transmissionIter == iter)
					{	// .. set the iterator back one to preserve the transmission iteration
						m_transmissionIter = previous;
					}
				}

				delete iter;
				break;
			}				
			previous = iter;
			iter = iter->m_next;
		}
	}
	void disconnectAll(void)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);

		while (iter)
		{
			iter->onDisconnect(*this);
			Connection* stale(iter);
			iter = iter->m_next;
			delete stale;
		}

		m_receivers = NULL;
	}
	void onDisconnect(Receiver* receiver)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);
		Connection* previous(NULL);

		while (iter)
		{
			if (iter->isReceiver(receiver))
			{
				if (previous)
				{
					previous->m_next = iter->m_next;
				}
				else
				{
					m_receivers = iter->m_next;
				}

				delete iter;
				break;
			}

			previous = iter;
			iter = iter->m_next;
		}
	}
	void replicate(const Receiver* receiver, Receiver* new_receiver)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);

		while (iter)
		{
			if (iter->isReceiver(receiver))
			{
				Connection* connection = iter->duplicate(new_receiver);
				connection->m_next = m_receivers;
				m_receivers = connection;
				break;
			}
		}
	}
private:
	DECLARE_MUTABLE_MUTEX(m_mutex)
	Connection* m_receivers;
	Connection* m_transmissionIter;
	bool m_isRepeatTransmissionRequired;
	bool m_isTransmitting;
}; // class Transmitter2

template<typename ARG_1, typename ARG_2, typename ARG_3>
class Transmitter3 : public Transmitter
{
	typedef void StaticFunction3(ARG_1, ARG_2, ARG_3);

	class Connection
	{
	public:
		Connection(void) : m_next(NULL) { /* empty */ };
		virtual ~Connection(void)=0 { /* empty */ };
		virtual Connection* clone(void)=0;
		virtual Connection* duplicate(Receiver* receiver)=0;
		virtual bool isFunction(StaticFunction3*) const=0;
		virtual bool isReceiver(const Receiver*) const=0;
		virtual void onConnect(Transmitter&)=0;
		virtual void onDisconnect(Transmitter&)=0;
		virtual void transmit(ARG_1, ARG_2, ARG_3)=0;
		Connection* m_next;
	}; // class Connection
	template< class RECEIVER >
	class volatile3
		: public Connection
	{
	public:
		volatile3(RECEIVER* object, void (RECEIVER::* function)(ARG_1, ARG_2, ARG_3))
			: m_object(object)
			, m_function(function)
		{ /* empty */ }
		virtual Connection* clone(void)
		{
			return new volatile3<RECEIVER>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new volatile3<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual bool isFunction(StaticFunction3*) const
		{
			return false;
		}
		virtual bool isReceiver(const Receiver* receiver) const
		{
			return m_object == static_cast<const RECEIVER*>(receiver);
		}
		virtual void onConnect(Transmitter& transmitter)
		{
			m_object->onConnect(&transmitter);
		}
		virtual void onDisconnect(Transmitter& transmitter)
		{
			m_object->onDisconnect(&transmitter);
		}
		virtual void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3)
		{
			(m_object->*m_function)(arg1, arg2, arg3);
		}
	private:
		RECEIVER* m_object;
		void (RECEIVER::* m_function)(ARG_1, ARG_2, ARG_3);
	}; // class volatile3
	template<class RECEIVER >
	class const3
		: public Connection
	{
	public:
		const3(RECEIVER* object, void (RECEIVER::* function)(ARG_1, ARG_2, ARG_3) const)
			: m_object(object)
			, m_function(function)
		{ /* empty */ }
		virtual Connection* clone(void)
		{
			return new const3<RECEIVER>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new const3<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual bool isFunction(StaticFunction3*) const
		{
			return false;
		}
		virtual bool isReceiver(const Receiver* receiver) const
		{
			return m_object == static_cast<const RECEIVER*>(receiver);
		}
		virtual void onConnect(Transmitter& transmitter)
		{
			m_object->onConnect(&transmitter);
		}
		virtual void onDisconnect(Transmitter& transmitter)
		{
			m_object->onDisconnect(&transmitter);
		}
		virtual void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3)
		{
			(m_object->*m_function)(arg1, arg2, arg3);
		}
	private:
		RECEIVER* m_object;
		void (RECEIVER::* m_function)(ARG_1, ARG_2, ARG_3) const;
	}; // class const3
	class static3
		: public Connection
	{
	public:
		static3(StaticFunction3& function)
			: m_function(function)
		{ /* empty */ }
		virtual Connection* clone(void)
		{
			return new const3<RECEIVER>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new const3<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual bool isFunction(StaticFunction3* function) const
		{
			return &m_function == function;
		}
		virtual bool isReceiver(const Receiver*) const
		{
			return false;
		}
		virtual void onConnect(Transmitter& transmitter)
		{
			/* empty */;
		}
		virtual void onDisconnect(Transmitter& transmitter)
		{
			/* empty */;
		}
		virtual void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3)
		{
			m_function(arg1, arg2, arg3);
		}
	private:
		StaticFunction3& m_function;
	}; // class static3
public:
	Transmitter3(void)
		: m_receivers(NULL)
		, m_transmissionIter(NULL)
		, m_isRepeatTransmissionRequired(false)
		, m_isTransmitting(false)
	{ /* empty */ }
	Transmitter3(const Transmitter3& source)
		: Transmitter(source)
		, m_receivers(NULL)
		, m_transmissionIter(NULL)
		, m_isRepeatTransmissionRequired(false)
		, m_isTransmitting(false)
	{
		SYNC(m_mutex);
		Connection* iter(source.m_receivers);
		Connection* previous(NULL);
		Connection** destinationIter = &m_receivers;
		while (iter)
		{
			iter->onConnect(*this);
			*destinationIter = iter->clone();

			if (previous)
			{
				previous->m_next = *destinationIter;
			}

			previous = *destinationIter
				iter = iter->m_next;
		}
	}
	virtual ~Transmitter3(void)
	{
		disconnectAll();
	}
	void ceaseTransmission(void)
	{
		SYNC(m_mutex);
		disconnectAll();
		m_isTransmitting = false;
		m_transmissionIter = NULL;
		m_receivers = NULL;
	}
	template<class RECEIVER>
	void connect(RECEIVER* receiver, void (RECEIVER::* function)(ARG_1, ARG_2, ARG_3))
	{
		if (receiver && function)
		{
			SYNC(m_mutex);
			Connection* iter(m_receivers);

			while (iter)
			{
				if (iter->isReceiver(receiver))
				{
					return;
				}

				iter = iter->m_next;
			}

			Connection* connection(new volatile3<RECEIVER>(receiver, function));
			connection->m_next = m_receivers;
			m_receivers = connection;
			receiver->onConnect(this);
		}
	}
	template<class RECEIVER>
	void connect(RECEIVER* receiver, void (RECEIVER::* function)(ARG_1, ARG_2, ARG_3) const)
	{
		if (receiver && function)
		{
			SYNC(m_mutex);
			Connection* iter(m_receivers);

			while (iter)
			{
				if (iter->isReceiver(receiver))
				{
					return;
				}

				iter = iter->m_next;
			}

			Connection* connection(new const3<RECEIVER>(receiver, function));
			connection->m_next = m_receivers;
			m_receivers = connection;
			receiver->onConnect(this);
		}
	}
	void connect(StaticFunction3& function)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);

		while (iter)
		{
			if (iter->isFunction(&function))
			{
				return;
			}

			iter = iter->m_next;
		}

		Connection* connection(new static3(function));
		connection->m_next = m_receivers;
		m_receivers = connection;
	}
	void disconnect(Receiver* receiver)
	{
		disconnect(receiver, NULL);
	}
	void disconnect(StaticFunction3& function)
	{
		disconnect(NULL, function);
	}
	void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3)
	{
		SYNC(m_mutex);
		if (m_isTransmitting)
		{
			m_isRepeatTransmissionRequired = true;
		}
		else
		{
			m_isTransmitting = true;
			m_transmissionIter = m_receivers;
			// the receiver list can change be modified transmission
			while (m_transmissionIter)
			{
				m_transmissionIter->transmit(arg1, arg2, arg3);
				// calling transmit() might have triggered the removal of the receiver
				if (m_transmissionIter)
					m_transmissionIter = m_transmissionIter->m_next;
				else
					m_transmissionIter = m_receivers;
			}

			m_isTransmitting = false;

			if (m_isRepeatTransmissionRequired)
			{
				m_isRepeatTransmissionRequired = false;
				transmit(arg1, arg2, arg3);
			}
		}
	}
	inline void operator()(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3)
	{
		transmit(arg1, arg2, arg3);
	}
protected:
	void disconnect(Receiver* receiver, StaticFunction3* function)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);
		Connection* previous(NULL);

		while (iter)
		{
			bool isFound;

			if (iter->isReceiver(receiver))
			{
				receiver->onDisconnect(this);
				isFound = true;
			}
			else
			{
				isFound = iter->isFunction(function);
			}

			if (isFound)
			{
				if (previous)
				{
					previous->m_next = iter->m_next;
				}
				else 
				{
					m_receivers = iter->m_next;
				}

				// if transmitting...	
				if (m_isTransmitting)
				{	// ... and we just removed the transmission iter ...
					if (m_transmissionIter == iter)
					{	// .. set the iterator back one to preserve the transmission iteration
						m_transmissionIter = previous;
					}
				}

				delete iter;
				break;
			}				
			previous = iter;
			iter = iter->m_next;
		}
	}
	void disconnectAll(void)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);

		while (iter)
		{
			iter->onDisconnect(*this);
			Connection* stale(iter);
			iter = iter->m_next;
			delete stale;
		}

		m_receivers = NULL;
	}
	void onDisconnect(Receiver* receiver)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);
		Connection* previous(NULL);

		while (iter)
		{
			if (iter->isReceiver(receiver))
			{
				if (previous)
				{
					previous->m_next = iter->m_next;
				}
				else
				{
					m_receivers = iter->m_next;
				}

				delete iter;
				break;
			}

			previous = iter;
			iter = iter->m_next;
		}
	}
	void replicate(const Receiver* receiver, Receiver* new_receiver)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);

		while (iter)
		{
			if (iter->isReceiver(receiver))
			{
				Connection* connection = iter->duplicate(new_receiver);
				connection->m_next = m_receivers;
				m_receivers = connection;
				break;
			}
		}
	}
private:
	DECLARE_MUTABLE_MUTEX(m_mutex)
	Connection* m_receivers;
	Connection* m_transmissionIter;
	bool m_isRepeatTransmissionRequired;
	bool m_isTransmitting;
}; // class Transmitter3

template<typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4>
class Transmitter4 : public Transmitter
{
	typedef void StaticFunction4(ARG_1, ARG_2, ARG_3, ARG_4);

	class Connection
	{
	public:
		Connection(void) : m_next(NULL) { /* empty */ };
		virtual ~Connection(void)=0 { /* empty */ };
		virtual Connection* clone(void)=0;
		virtual Connection* duplicate(Receiver* receiver)=0;
		virtual bool isFunction(StaticFunction4*) const=0;
		virtual bool isReceiver(const Receiver*) const=0;
		virtual void onConnect(Transmitter&)=0;
		virtual void onDisconnect(Transmitter&)=0;
		virtual void transmit(ARG_1, ARG_2, ARG_3, ARG_4)=0;
		Connection* m_next;
	}; // class Connection
	template< class RECEIVER >
	class volatile4
		: public Connection
	{
	public:
		volatile4(RECEIVER* object, void (RECEIVER::* function)(ARG_1, ARG_2, ARG_3, ARG_4))
			: m_object(object)
			, m_function(function)
		{ /* empty */ }
		virtual Connection* clone(void)
		{
			return new volatile4<RECEIVER>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new volatile4<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual bool isFunction(StaticFunction4*) const
		{
			return false;
		}
		virtual bool isReceiver(const Receiver* receiver) const
		{
			return m_object == static_cast<const RECEIVER*>(receiver);
		}
		virtual void onConnect(Transmitter& transmitter)
		{
			m_object->onConnect(&transmitter);
		}
		virtual void onDisconnect(Transmitter& transmitter)
		{
			m_object->onDisconnect(&transmitter);
		}
		virtual void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4)
		{
			(m_object->*m_function)(arg1, arg2, arg3, arg4);
		}
	private:
		RECEIVER* m_object;
		void (RECEIVER::* m_function)(ARG_1, ARG_2, ARG_3, ARG_4);
	}; // class volatile4
	template<class RECEIVER >
	class const4
		: public Connection
	{
	public:
		const4(RECEIVER* object, void (RECEIVER::* function)(ARG_1, ARG_2, ARG_3, ARG_4) const)
			: m_object(object)
			, m_function(function)
		{ /* empty */ }
		virtual Connection* clone(void)
		{
			return new const4<RECEIVER>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new const4<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual bool isFunction(StaticFunction4*) const
		{
			return false;
		}
		virtual bool isReceiver(const Receiver* receiver) const
		{
			return m_object == static_cast<const RECEIVER*>(receiver);
		}
		virtual void onConnect(Transmitter& transmitter)
		{
			m_object->onConnect(&transmitter);
		}
		virtual void onDisconnect(Transmitter& transmitter)
		{
			m_object->onDisconnect(&transmitter);
		}
		virtual void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4)
		{
			(m_object->*m_function)(arg1, arg2, arg3, arg4);
		}
	private:
		RECEIVER* m_object;
		void (RECEIVER::* m_function)(ARG_1, ARG_2, ARG_3, ARG_4) const;
	}; // class const4
	class static4
		: public Connection
	{
	public:
		static4(StaticFunction4& function)
			: m_function(function)
		{ /* empty */ }
		virtual Connection* clone(void)
		{
			return new const4<RECEIVER>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new const4<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual bool isFunction(StaticFunction4* function) const
		{
			return &m_function == function;
		}
		virtual bool isReceiver(const Receiver*) const
		{
			return false;
		}
		virtual void onConnect(Transmitter& transmitter)
		{
			/* empty */;
		}
		virtual void onDisconnect(Transmitter& transmitter)
		{
			/* empty */;
		}
		virtual void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4)
		{
			m_function(arg1, arg2, arg3, arg4);
		}
	private:
		StaticFunction4& m_function;
	}; // class static4
public:
	Transmitter4(void)
		: m_receivers(NULL)
		, m_transmissionIter(NULL)
		, m_isRepeatTransmissionRequired(false)
		, m_isTransmitting(false)
	{ /* empty */ }
	Transmitter4(const Transmitter4& source)
		: Transmitter(source)
		, m_receivers(NULL)
		, m_transmissionIter(NULL)
		, m_isRepeatTransmissionRequired(false)
		, m_isTransmitting(false)
	{
		SYNC(m_mutex);
		Connection* iter(source.m_receivers);
		Connection* previous(NULL);
		Connection** destinationIter = &m_receivers;
		while (iter)
		{
			iter->onConnect(*this);
			*destinationIter = iter->clone();

			if (previous)
			{
				previous->m_next = *destinationIter;
			}

			previous = *destinationIter
				iter = iter->m_next;
		}
	}
	virtual ~Transmitter4(void)
	{
		disconnectAll();
	}
	void ceaseTransmission(void)
	{
		SYNC(m_mutex);
		disconnectAll();
		m_isTransmitting = false;
		m_transmissionIter = NULL;
		m_receivers = NULL;
	}
	template<class RECEIVER>
	void connect(RECEIVER* receiver, void (RECEIVER::* function)(ARG_1, ARG_2, ARG_3, ARG_4))
	{
		if (receiver && function)
		{
			SYNC(m_mutex);
			Connection* iter(m_receivers);

			while (iter)
			{
				if (iter->isReceiver(receiver))
				{
					return;
				}

				iter = iter->m_next;
			}

			Connection* connection(new volatile4<RECEIVER>(receiver, function));
			connection->m_next = m_receivers;
			m_receivers = connection;
			receiver->onConnect(this);
		}
	}
	template<class RECEIVER>
	void connect(RECEIVER* receiver, void (RECEIVER::* function)(ARG_1, ARG_2, ARG_3, ARG_4) const)
	{
		if (receiver && function)
		{
			SYNC(m_mutex);
			Connection* iter(m_receivers);

			while (iter)
			{
				if (iter->isReceiver(receiver))
				{
					return;
				}

				iter = iter->m_next;
			}

			Connection* connection(new const4<RECEIVER>(receiver, function));
			connection->m_next = m_receivers;
			m_receivers = connection;
			receiver->onConnect(this);
		}
	}
	void connect(StaticFunction4& function)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);

		while (iter)
		{
			if (iter->isFunction(&function))
			{
				return;
			}

			iter = iter->m_next;
		}

		Connection* connection(new static4(function));
		connection->m_next = m_receivers;
		m_receivers = connection;
	}
	void disconnect(Receiver* receiver)
	{
		disconnect(receiver, NULL);
	}
	void disconnect(StaticFunction4& function)
	{
		disconnect(NULL, function);
	}
	void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4)
	{
		SYNC(m_mutex);
		if (m_isTransmitting)
		{
			m_isRepeatTransmissionRequired = true;
		}
		else
		{
			m_isTransmitting = true;
			m_transmissionIter = m_receivers;
			// the receiver list can change be modified transmission
			while (m_transmissionIter)
			{
				m_transmissionIter->transmit(arg1, arg2, arg3, arg4);
				// calling transmit() might have triggered the removal of the receiver
				if (m_transmissionIter)
					m_transmissionIter = m_transmissionIter->m_next;
				else
					m_transmissionIter = m_receivers;
			}

			m_isTransmitting = false;

			if (m_isRepeatTransmissionRequired)
			{
				m_isRepeatTransmissionRequired = false;
				transmit(arg1, arg2, arg3, arg4);
			}
		}
	}
	inline void operator()(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4)
	{
		transmit(arg1, arg2, arg3, arg4);
	}
protected:
	void disconnect(Receiver* receiver, StaticFunction4* function)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);
		Connection* previous(NULL);

		while (iter)
		{
			bool isFound;

			if (iter->isReceiver(receiver))
			{
				receiver->onDisconnect(this);
				isFound = true;
			}
			else
			{
				isFound = iter->isFunction(function);
			}

			if (isFound)
			{
				if (previous)
				{
					previous->m_next = iter->m_next;
				}
				else 
				{
					m_receivers = iter->m_next;
				}

				// if transmitting...	
				if (m_isTransmitting)
				{	// ... and we just removed the transmission iter ...
					if (m_transmissionIter == iter)
					{	// .. set the iterator back one to preserve the transmission iteration
						m_transmissionIter = previous;
					}
				}

				delete iter;
				break;
			}				
			previous = iter;
			iter = iter->m_next;
		}
	}
	void disconnectAll(void)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);

		while (iter)
		{
			iter->onDisconnect(*this);
			Connection* stale(iter);
			iter = iter->m_next;
			delete stale;
		}

		m_receivers = NULL;
	}
	void onDisconnect(Receiver* receiver)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);
		Connection* previous(NULL);

		while (iter)
		{
			if (iter->isReceiver(receiver))
			{
				if (previous)
				{
					previous->m_next = iter->m_next;
				}
				else
				{
					m_receivers = iter->m_next;
				}

				delete iter;
				break;
			}

			previous = iter;
			iter = iter->m_next;
		}
	}
	void replicate(const Receiver* receiver, Receiver* new_receiver)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);

		while (iter)
		{
			if (iter->isReceiver(receiver))
			{
				Connection* connection = iter->duplicate(new_receiver);
				connection->m_next = m_receivers;
				m_receivers = connection;
				break;
			}
		}
	}
private:
	DECLARE_MUTABLE_MUTEX(m_mutex)
	Connection* m_receivers;
	Connection* m_transmissionIter;
	bool m_isRepeatTransmissionRequired;
	bool m_isTransmitting;
}; // class Transmitter4

template<typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5>
class Transmitter5 : public Transmitter
{
	typedef void StaticFunction5(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5);

	class Connection
	{
	public:
		Connection(void) : m_next(NULL) { /* empty */ };
		virtual ~Connection(void)=0 { /* empty */ };
		virtual Connection* clone(void)=0;
		virtual Connection* duplicate(Receiver* receiver)=0;
		virtual bool isFunction(StaticFunction5*) const=0;
		virtual bool isReceiver(const Receiver*) const=0;
		virtual void onConnect(Transmitter&)=0;
		virtual void onDisconnect(Transmitter&)=0;
		virtual void transmit(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5)=0;
		Connection* m_next;
	}; // class Connection
	template< class RECEIVER >
	class volatile5
		: public Connection
	{
	public:
		volatile5(RECEIVER* object, void (RECEIVER::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5))
			: m_object(object)
			, m_function(function)
		{ /* empty */ }
		virtual Connection* clone(void)
		{
			return new volatile5<RECEIVER>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new volatile5<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual bool isFunction(StaticFunction5*) const
		{
			return false;
		}
		virtual bool isReceiver(const Receiver* receiver) const
		{
			return m_object == static_cast<const RECEIVER*>(receiver);
		}
		virtual void onConnect(Transmitter& transmitter)
		{
			m_object->onConnect(&transmitter);
		}
		virtual void onDisconnect(Transmitter& transmitter)
		{
			m_object->onDisconnect(&transmitter);
		}
		virtual void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5)
		{
			(m_object->*m_function)(arg1, arg2, arg3, arg4, arg5);
		}
	private:
		RECEIVER* m_object;
		void (RECEIVER::* m_function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5);
	}; // class volatile5
	template<class RECEIVER >
	class const5
		: public Connection
	{
	public:
		const5(RECEIVER* object, void (RECEIVER::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) const)
			: m_object(object)
			, m_function(function)
		{ /* empty */ }
		virtual Connection* clone(void)
		{
			return new const5<RECEIVER>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new const5<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual bool isFunction(StaticFunction5*) const
		{
			return false;
		}
		virtual bool isReceiver(const Receiver* receiver) const
		{
			return m_object == static_cast<const RECEIVER*>(receiver);
		}
		virtual void onConnect(Transmitter& transmitter)
		{
			m_object->onConnect(&transmitter);
		}
		virtual void onDisconnect(Transmitter& transmitter)
		{
			m_object->onDisconnect(&transmitter);
		}
		virtual void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5)
		{
			(m_object->*m_function)(arg1, arg2, arg3, arg4, arg5);
		}
	private:
		RECEIVER* m_object;
		void (RECEIVER::* m_function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) const;
	}; // class const5
	class static5
		: public Connection
	{
	public:
		static5(StaticFunction5& function)
			: m_function(function)
		{ /* empty */ }
		virtual Connection* clone(void)
		{
			return new const5<RECEIVER>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new const5<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual bool isFunction(StaticFunction5* function) const
		{
			return &m_function == function;
		}
		virtual bool isReceiver(const Receiver*) const
		{
			return false;
		}
		virtual void onConnect(Transmitter& transmitter)
		{
			/* empty */;
		}
		virtual void onDisconnect(Transmitter& transmitter)
		{
			/* empty */;
		}
		virtual void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5)
		{
			m_function(arg1, arg2, arg3, arg4, arg5);
		}
	private:
		StaticFunction5& m_function;
	}; // class static5
public:
	Transmitter5(void)
		: m_receivers(NULL)
		, m_transmissionIter(NULL)
		, m_isRepeatTransmissionRequired(false)
		, m_isTransmitting(false)
	{ /* empty */ }
	Transmitter5(const Transmitter5& source)
		: Transmitter(source)
		, m_receivers(NULL)
		, m_transmissionIter(NULL)
		, m_isRepeatTransmissionRequired(false)
		, m_isTransmitting(false)
	{
		SYNC(m_mutex);
		Connection* iter(source.m_receivers);
		Connection* previous(NULL);
		Connection** destinationIter = &m_receivers;
		while (iter)
		{
			iter->onConnect(*this);
			*destinationIter = iter->clone();

			if (previous)
			{
				previous->m_next = *destinationIter;
			}

			previous = *destinationIter
				iter = iter->m_next;
		}
	}
	virtual ~Transmitter5(void)
	{
		disconnectAll();
	}
	void ceaseTransmission(void)
	{
		SYNC(m_mutex);
		disconnectAll();
		m_isTransmitting = false;
		m_transmissionIter = NULL;
		m_receivers = NULL;
	}
	template<class RECEIVER>
	void connect(RECEIVER* receiver, void (RECEIVER::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5))
	{
		if (receiver && function)
		{
			SYNC(m_mutex);
			Connection* iter(m_receivers);

			while (iter)
			{
				if (iter->isReceiver(receiver))
				{
					return;
				}

				iter = iter->m_next;
			}

			Connection* connection(new volatile5<RECEIVER>(receiver, function));
			connection->m_next = m_receivers;
			m_receivers = connection;
			receiver->onConnect(this);
		}
	}
	template<class RECEIVER>
	void connect(RECEIVER* receiver, void (RECEIVER::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) const)
	{
		if (receiver && function)
		{
			SYNC(m_mutex);
			Connection* iter(m_receivers);

			while (iter)
			{
				if (iter->isReceiver(receiver))
				{
					return;
				}

				iter = iter->m_next;
			}

			Connection* connection(new const5<RECEIVER>(receiver, function));
			connection->m_next = m_receivers;
			m_receivers = connection;
			receiver->onConnect(this);
		}
	}
	void connect(StaticFunction5& function)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);

		while (iter)
		{
			if (iter->isFunction(&function))
			{
				return;
			}

			iter = iter->m_next;
		}

		Connection* connection(new static5(function));
		connection->m_next = m_receivers;
		m_receivers = connection;
	}
	void disconnect(Receiver* receiver)
	{
		disconnect(receiver, NULL);
	}
	void disconnect(StaticFunction5& function)
	{
		disconnect(NULL, function);
	}
	void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5)
	{
		SYNC(m_mutex);
		if (m_isTransmitting)
		{
			m_isRepeatTransmissionRequired = true;
		}
		else
		{
			m_isTransmitting = true;
			m_transmissionIter = m_receivers;
			// the receiver list can change be modified transmission
			while (m_transmissionIter)
			{
				m_transmissionIter->transmit(arg1, arg2, arg3, arg4, arg5);
				// calling transmit() might have triggered the removal of the receiver
				if (m_transmissionIter)
					m_transmissionIter = m_transmissionIter->m_next;
				else
					m_transmissionIter = m_receivers;
			}

			m_isTransmitting = false;

			if (m_isRepeatTransmissionRequired)
			{
				m_isRepeatTransmissionRequired = false;
				transmit(arg1, arg2, arg3, arg4, arg5);
			}
		}
	}
	inline void operator()(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5)
	{
		transmit(arg1, arg2, arg3, arg4, arg5);
	}
protected:
	void disconnect(Receiver* receiver, StaticFunction5* function)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);
		Connection* previous(NULL);

		while (iter)
		{
			bool isFound;

			if (iter->isReceiver(receiver))
			{
				receiver->onDisconnect(this);
				isFound = true;
			}
			else
			{
				isFound = iter->isFunction(function);
			}

			if (isFound)
			{
				if (previous)
				{
					previous->m_next = iter->m_next;
				}
				else 
				{
					m_receivers = iter->m_next;
				}

				// if transmitting...	
				if (m_isTransmitting)
				{	// ... and we just removed the transmission iter ...
					if (m_transmissionIter == iter)
					{	// .. set the iterator back one to preserve the transmission iteration
						m_transmissionIter = previous;
					}
				}

				delete iter;
				break;
			}				
			previous = iter;
			iter = iter->m_next;
		}
	}
	void disconnectAll(void)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);

		while (iter)
		{
			iter->onDisconnect(*this);
			Connection* stale(iter);
			iter = iter->m_next;
			delete stale;
		}

		m_receivers = NULL;
	}
	void onDisconnect(Receiver* receiver)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);
		Connection* previous(NULL);

		while (iter)
		{
			if (iter->isReceiver(receiver))
			{
				if (previous)
				{
					previous->m_next = iter->m_next;
				}
				else
				{
					m_receivers = iter->m_next;
				}

				delete iter;
				break;
			}

			previous = iter;
			iter = iter->m_next;
		}
	}
	void replicate(const Receiver* receiver, Receiver* new_receiver)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);

		while (iter)
		{
			if (iter->isReceiver(receiver))
			{
				Connection* connection = iter->duplicate(new_receiver);
				connection->m_next = m_receivers;
				m_receivers = connection;
				break;
			}
		}
	}
private:
	DECLARE_MUTABLE_MUTEX(m_mutex)
	Connection* m_receivers;
	Connection* m_transmissionIter;
	bool m_isRepeatTransmissionRequired;
	bool m_isTransmitting;
}; // class Transmitter5

template<typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6>
class Transmitter6 : public Transmitter
{
	typedef void StaticFunction6(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6);

	class Connection
	{
	public:
		Connection(void) : m_next(NULL) { /* empty */ };
		virtual ~Connection(void)=0 { /* empty */ };
		virtual Connection* clone(void)=0;
		virtual Connection* duplicate(Receiver* receiver)=0;
		virtual bool isFunction(StaticFunction6*) const=0;
		virtual bool isReceiver(const Receiver*) const=0;
		virtual void onConnect(Transmitter&)=0;
		virtual void onDisconnect(Transmitter&)=0;
		virtual void transmit(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6)=0;
		Connection* m_next;
	}; // class Connection
	template< class RECEIVER >
	class volatile6
		: public Connection
	{
	public:
		volatile6(RECEIVER* object, void (RECEIVER::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6))
			: m_object(object)
			, m_function(function)
		{ /* empty */ }
		virtual Connection* clone(void)
		{
			return new volatile6<RECEIVER>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new volatile6<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual bool isFunction(StaticFunction6*) const
		{
			return false;
		}
		virtual bool isReceiver(const Receiver* receiver) const
		{
			return m_object == static_cast<const RECEIVER*>(receiver);
		}
		virtual void onConnect(Transmitter& transmitter)
		{
			m_object->onConnect(&transmitter);
		}
		virtual void onDisconnect(Transmitter& transmitter)
		{
			m_object->onDisconnect(&transmitter);
		}
		virtual void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6)
		{
			(m_object->*m_function)(arg1, arg2, arg3, arg4, arg5, arg6);
		}
	private:
		RECEIVER* m_object;
		void (RECEIVER::* m_function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6);
	}; // class volatile6
	template<class RECEIVER >
	class const6
		: public Connection
	{
	public:
		const6(RECEIVER* object, void (RECEIVER::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) const)
			: m_object(object)
			, m_function(function)
		{ /* empty */ }
		virtual Connection* clone(void)
		{
			return new const6<RECEIVER>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new const6<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual bool isFunction(StaticFunction6*) const
		{
			return false;
		}
		virtual bool isReceiver(const Receiver* receiver) const
		{
			return m_object == static_cast<const RECEIVER*>(receiver);
		}
		virtual void onConnect(Transmitter& transmitter)
		{
			m_object->onConnect(&transmitter);
		}
		virtual void onDisconnect(Transmitter& transmitter)
		{
			m_object->onDisconnect(&transmitter);
		}
		virtual void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6)
		{
			(m_object->*m_function)(arg1, arg2, arg3, arg4, arg5, arg6);
		}
	private:
		RECEIVER* m_object;
		void (RECEIVER::* m_function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) const;
	}; // class const6
	class static6
		: public Connection
	{
	public:
		static6(StaticFunction6& function)
			: m_function(function)
		{ /* empty */ }
		virtual Connection* clone(void)
		{
			return new const6<RECEIVER>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new const6<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual bool isFunction(StaticFunction6* function) const
		{
			return &m_function == function;
		}
		virtual bool isReceiver(const Receiver*) const
		{
			return false;
		}
		virtual void onConnect(Transmitter& transmitter)
		{
			/* empty */;
		}
		virtual void onDisconnect(Transmitter& transmitter)
		{
			/* empty */;
		}
		virtual void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6)
		{
			m_function(arg1, arg2, arg3, arg4, arg5, arg6);
		}
	private:
		StaticFunction6& m_function;
	}; // class static6
public:
	Transmitter6(void)
		: m_receivers(NULL)
		, m_transmissionIter(NULL)
		, m_isRepeatTransmissionRequired(false)
		, m_isTransmitting(false)
	{ /* empty */ }
	Transmitter6(const Transmitter6& source)
		: Transmitter(source)
		, m_receivers(NULL)
		, m_transmissionIter(NULL)
		, m_isRepeatTransmissionRequired(false)
		, m_isTransmitting(false)
	{
		SYNC(m_mutex);
		Connection* iter(source.m_receivers);
		Connection* previous(NULL);
		Connection** destinationIter = &m_receivers;
		while (iter)
		{
			iter->onConnect(*this);
			*destinationIter = iter->clone();

			if (previous)
			{
				previous->m_next = *destinationIter;
			}

			previous = *destinationIter
				iter = iter->m_next;
		}
	}
	virtual ~Transmitter6(void)
	{
		disconnectAll();
	}
	void ceaseTransmission(void)
	{
		SYNC(m_mutex);
		disconnectAll();
		m_isTransmitting = false;
		m_transmissionIter = NULL;
		m_receivers = NULL;
	}
	template<class RECEIVER>
	void connect(RECEIVER* receiver, void (RECEIVER::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6))
	{
		if (receiver && function)
		{
			SYNC(m_mutex);
			Connection* iter(m_receivers);

			while (iter)
			{
				if (iter->isReceiver(receiver))
				{
					return;
				}

				iter = iter->m_next;
			}

			Connection* connection(new volatile6<RECEIVER>(receiver, function));
			connection->m_next = m_receivers;
			m_receivers = connection;
			receiver->onConnect(this);
		}
	}
	template<class RECEIVER>
	void connect(RECEIVER* receiver, void (RECEIVER::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) const)
	{
		if (receiver && function)
		{
			SYNC(m_mutex);
			Connection* iter(m_receivers);

			while (iter)
			{
				if (iter->isReceiver(receiver))
				{
					return;
				}

				iter = iter->m_next;
			}

			Connection* connection(new const6<RECEIVER>(receiver, function));
			connection->m_next = m_receivers;
			m_receivers = connection;
			receiver->onConnect(this);
		}
	}
	void connect(StaticFunction6& function)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);

		while (iter)
		{
			if (iter->isFunction(&function))
			{
				return;
			}

			iter = iter->m_next;
		}

		Connection* connection(new static6(function));
		connection->m_next = m_receivers;
		m_receivers = connection;
	}
	void disconnect(Receiver* receiver)
	{
		disconnect(receiver, NULL);
	}
	void disconnect(StaticFunction6& function)
	{
		disconnect(NULL, function);
	}
	void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6)
	{
		SYNC(m_mutex);
		if (m_isTransmitting)
		{
			m_isRepeatTransmissionRequired = true;
		}
		else
		{
			m_isTransmitting = true;
			m_transmissionIter = m_receivers;
			// the receiver list can change be modified transmission
			while (m_transmissionIter)
			{
				m_transmissionIter->transmit(arg1, arg2, arg3, arg4, arg5, arg6);
				// calling transmit() might have triggered the removal of the receiver
				if (m_transmissionIter)
					m_transmissionIter = m_transmissionIter->m_next;
				else
					m_transmissionIter = m_receivers;
			}

			m_isTransmitting = false;

			if (m_isRepeatTransmissionRequired)
			{
				m_isRepeatTransmissionRequired = false;
				transmit(arg1, arg2, arg3, arg4, arg5, arg6);
			}
		}
	}
	inline void operator()(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6)
	{
		transmit(arg1, arg2, arg3, arg4, arg5, arg6);
	}
protected:
	void disconnect(Receiver* receiver, StaticFunction6* function)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);
		Connection* previous(NULL);

		while (iter)
		{
			bool isFound;

			if (iter->isReceiver(receiver))
			{
				receiver->onDisconnect(this);
				isFound = true;
			}
			else
			{
				isFound = iter->isFunction(function);
			}

			if (isFound)
			{
				if (previous)
				{
					previous->m_next = iter->m_next;
				}
				else 
				{
					m_receivers = iter->m_next;
				}

				// if transmitting...	
				if (m_isTransmitting)
				{	// ... and we just removed the transmission iter ...
					if (m_transmissionIter == iter)
					{	// .. set the iterator back one to preserve the transmission iteration
						m_transmissionIter = previous;
					}
				}

				delete iter;
				break;
			}				
			previous = iter;
			iter = iter->m_next;
		}
	}
	void disconnectAll(void)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);

		while (iter)
		{
			iter->onDisconnect(*this);
			Connection* stale(iter);
			iter = iter->m_next;
			delete stale;
		}

		m_receivers = NULL;
	}
	void onDisconnect(Receiver* receiver)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);
		Connection* previous(NULL);

		while (iter)
		{
			if (iter->isReceiver(receiver))
			{
				if (previous)
				{
					previous->m_next = iter->m_next;
				}
				else
				{
					m_receivers = iter->m_next;
				}

				delete iter;
				break;
			}

			previous = iter;
			iter = iter->m_next;
		}
	}
	void replicate(const Receiver* receiver, Receiver* new_receiver)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);

		while (iter)
		{
			if (iter->isReceiver(receiver))
			{
				Connection* connection = iter->duplicate(new_receiver);
				connection->m_next = m_receivers;
				m_receivers = connection;
				break;
			}
		}
	}
private:
	DECLARE_MUTABLE_MUTEX(m_mutex)
	Connection* m_receivers;
	Connection* m_transmissionIter;
	bool m_isRepeatTransmissionRequired;
	bool m_isTransmitting;
}; // class Transmitter6

template<typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7>
class Transmitter7 : public Transmitter
{
	typedef void StaticFunction7(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7);

	class Connection
	{
	public:
		Connection(void) : m_next(NULL) { /* empty */ };
		virtual ~Connection(void)=0 { /* empty */ };
		virtual Connection* clone(void)=0;
		virtual Connection* duplicate(Receiver* receiver)=0;
		virtual bool isFunction(StaticFunction7*) const=0;
		virtual bool isReceiver(const Receiver*) const=0;
		virtual void onConnect(Transmitter&)=0;
		virtual void onDisconnect(Transmitter&)=0;
		virtual void transmit(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7)=0;
		Connection* m_next;
	}; // class Connection
	template< class RECEIVER >
	class volatile7
		: public Connection
	{
	public:
		volatile7(RECEIVER* object, void (RECEIVER::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7))
			: m_object(object)
			, m_function(function)
		{ /* empty */ }
		virtual Connection* clone(void)
		{
			return new volatile7<RECEIVER>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new volatile7<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual bool isFunction(StaticFunction7*) const
		{
			return false;
		}
		virtual bool isReceiver(const Receiver* receiver) const
		{
			return m_object == static_cast<const RECEIVER*>(receiver);
		}
		virtual void onConnect(Transmitter& transmitter)
		{
			m_object->onConnect(&transmitter);
		}
		virtual void onDisconnect(Transmitter& transmitter)
		{
			m_object->onDisconnect(&transmitter);
		}
		virtual void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7)
		{
			(m_object->*m_function)(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		}
	private:
		RECEIVER* m_object;
		void (RECEIVER::* m_function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7);
	}; // class volatile7
	template<class RECEIVER >
	class const7
		: public Connection
	{
	public:
		const7(RECEIVER* object, void (RECEIVER::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) const)
			: m_object(object)
			, m_function(function)
		{ /* empty */ }
		virtual Connection* clone(void)
		{
			return new const7<RECEIVER>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new const7<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual bool isFunction(StaticFunction7*) const
		{
			return false;
		}
		virtual bool isReceiver(const Receiver* receiver) const
		{
			return m_object == static_cast<const RECEIVER*>(receiver);
		}
		virtual void onConnect(Transmitter& transmitter)
		{
			m_object->onConnect(&transmitter);
		}
		virtual void onDisconnect(Transmitter& transmitter)
		{
			m_object->onDisconnect(&transmitter);
		}
		virtual void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7)
		{
			(m_object->*m_function)(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		}
	private:
		RECEIVER* m_object;
		void (RECEIVER::* m_function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) const;
	}; // class const7
	class static7
		: public Connection
	{
	public:
		static7(StaticFunction7& function)
			: m_function(function)
		{ /* empty */ }
		virtual Connection* clone(void)
		{
			return new const7<RECEIVER>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new const7<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual bool isFunction(StaticFunction7* function) const
		{
			return &m_function == function;
		}
		virtual bool isReceiver(const Receiver*) const
		{
			return false;
		}
		virtual void onConnect(Transmitter& transmitter)
		{
			/* empty */;
		}
		virtual void onDisconnect(Transmitter& transmitter)
		{
			/* empty */;
		}
		virtual void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7)
		{
			m_function(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		}
	private:
		StaticFunction7& m_function;
	}; // class static7
public:
	Transmitter7(void)
		: m_receivers(NULL)
		, m_transmissionIter(NULL)
		, m_isRepeatTransmissionRequired(false)
		, m_isTransmitting(false)
	{ /* empty */ }
	Transmitter7(const Transmitter7& source)
		: Transmitter(source)
		, m_receivers(NULL)
		, m_transmissionIter(NULL)
		, m_isRepeatTransmissionRequired(false)
		, m_isTransmitting(false)
	{
		SYNC(m_mutex);
		Connection* iter(source.m_receivers);
		Connection* previous(NULL);
		Connection** destinationIter = &m_receivers;
		while (iter)
		{
			iter->onConnect(*this);
			*destinationIter = iter->clone();

			if (previous)
			{
				previous->m_next = *destinationIter;
			}

			previous = *destinationIter
				iter = iter->m_next;
		}
	}
	virtual ~Transmitter7(void)
	{
		disconnectAll();
	}
	void ceaseTransmission(void)
	{
		SYNC(m_mutex);
		disconnectAll();
		m_isTransmitting = false;
		m_transmissionIter = NULL;
		m_receivers = NULL;
	}
	template<class RECEIVER>
	void connect(RECEIVER* receiver, void (RECEIVER::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7))
	{
		if (receiver && function)
		{
			SYNC(m_mutex);
			Connection* iter(m_receivers);

			while (iter)
			{
				if (iter->isReceiver(receiver))
				{
					return;
				}

				iter = iter->m_next;
			}

			Connection* connection(new volatile7<RECEIVER>(receiver, function));
			connection->m_next = m_receivers;
			m_receivers = connection;
			receiver->onConnect(this);
		}
	}
	template<class RECEIVER>
	void connect(RECEIVER* receiver, void (RECEIVER::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) const)
	{
		if (receiver && function)
		{
			SYNC(m_mutex);
			Connection* iter(m_receivers);

			while (iter)
			{
				if (iter->isReceiver(receiver))
				{
					return;
				}

				iter = iter->m_next;
			}

			Connection* connection(new const7<RECEIVER>(receiver, function));
			connection->m_next = m_receivers;
			m_receivers = connection;
			receiver->onConnect(this);
		}
	}
	void connect(StaticFunction7& function)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);

		while (iter)
		{
			if (iter->isFunction(&function))
			{
				return;
			}

			iter = iter->m_next;
		}

		Connection* connection(new static7(function));
		connection->m_next = m_receivers;
		m_receivers = connection;
	}
	void disconnect(Receiver* receiver)
	{
		disconnect(receiver, NULL);
	}
	void disconnect(StaticFunction7& function)
	{
		disconnect(NULL, function);
	}
	void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7)
	{
		SYNC(m_mutex);
		if (m_isTransmitting)
		{
			m_isRepeatTransmissionRequired = true;
		}
		else
		{
			m_isTransmitting = true;
			m_transmissionIter = m_receivers;
			// the receiver list can change be modified transmission
			while (m_transmissionIter)
			{
				m_transmissionIter->transmit(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
				// calling transmit() might have triggered the removal of the receiver
				if (m_transmissionIter)
					m_transmissionIter = m_transmissionIter->m_next;
				else
					m_transmissionIter = m_receivers;
			}

			m_isTransmitting = false;

			if (m_isRepeatTransmissionRequired)
			{
				m_isRepeatTransmissionRequired = false;
				transmit(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
			}
		}
	}
	inline void operator()(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7)
	{
		transmit(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
	}
protected:
	void disconnect(Receiver* receiver, StaticFunction7* function)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);
		Connection* previous(NULL);

		while (iter)
		{
			bool isFound;

			if (iter->isReceiver(receiver))
			{
				receiver->onDisconnect(this);
				isFound = true;
			}
			else
			{
				isFound = iter->isFunction(function);
			}

			if (isFound)
			{
				if (previous)
				{
					previous->m_next = iter->m_next;
				}
				else 
				{
					m_receivers = iter->m_next;
				}

				// if transmitting...	
				if (m_isTransmitting)
				{	// ... and we just removed the transmission iter ...
					if (m_transmissionIter == iter)
					{	// .. set the iterator back one to preserve the transmission iteration
						m_transmissionIter = previous;
					}
				}

				delete iter;
				break;
			}				
			previous = iter;
			iter = iter->m_next;
		}
	}
	void disconnectAll(void)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);

		while (iter)
		{
			iter->onDisconnect(*this);
			Connection* stale(iter);
			iter = iter->m_next;
			delete stale;
		}

		m_receivers = NULL;
	}
	void onDisconnect(Receiver* receiver)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);
		Connection* previous(NULL);

		while (iter)
		{
			if (iter->isReceiver(receiver))
			{
				if (previous)
				{
					previous->m_next = iter->m_next;
				}
				else
				{
					m_receivers = iter->m_next;
				}

				delete iter;
				break;
			}

			previous = iter;
			iter = iter->m_next;
		}
	}
	void replicate(const Receiver* receiver, Receiver* new_receiver)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);

		while (iter)
		{
			if (iter->isReceiver(receiver))
			{
				Connection* connection = iter->duplicate(new_receiver);
				connection->m_next = m_receivers;
				m_receivers = connection;
				break;
			}
		}
	}
private:
	DECLARE_MUTABLE_MUTEX(m_mutex)
	Connection* m_receivers;
	Connection* m_transmissionIter;
	bool m_isRepeatTransmissionRequired;
	bool m_isTransmitting;
}; // class Transmitter7

template<typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8>
class Transmitter8 : public Transmitter
{
	typedef void StaticFunction8(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8);

	class Connection
	{
	public:
		Connection(void) : m_next(NULL) { /* empty */ };
		virtual ~Connection(void)=0 { /* empty */ };
		virtual Connection* clone(void)=0;
		virtual Connection* duplicate(Receiver* receiver)=0;
		virtual bool isFunction(StaticFunction8*) const=0;
		virtual bool isReceiver(const Receiver*) const=0;
		virtual void onConnect(Transmitter&)=0;
		virtual void onDisconnect(Transmitter&)=0;
		virtual void transmit(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8)=0;
		Connection* m_next;
	}; // class Connection
	template< class RECEIVER >
	class volatile8
		: public Connection
	{
	public:
		volatile8(RECEIVER* object, void (RECEIVER::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8))
			: m_object(object)
			, m_function(function)
		{ /* empty */ }
		virtual Connection* clone(void)
		{
			return new volatile8<RECEIVER>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new volatile8<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual bool isFunction(StaticFunction8*) const
		{
			return false;
		}
		virtual bool isReceiver(const Receiver* receiver) const
		{
			return m_object == static_cast<const RECEIVER*>(receiver);
		}
		virtual void onConnect(Transmitter& transmitter)
		{
			m_object->onConnect(&transmitter);
		}
		virtual void onDisconnect(Transmitter& transmitter)
		{
			m_object->onDisconnect(&transmitter);
		}
		virtual void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8)
		{
			(m_object->*m_function)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		}
	private:
		RECEIVER* m_object;
		void (RECEIVER::* m_function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8);
	}; // class volatile8
	template<class RECEIVER >
	class const8
		: public Connection
	{
	public:
		const8(RECEIVER* object, void (RECEIVER::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) const)
			: m_object(object)
			, m_function(function)
		{ /* empty */ }
		virtual Connection* clone(void)
		{
			return new const8<RECEIVER>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new const8<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual bool isFunction(StaticFunction8*) const
		{
			return false;
		}
		virtual bool isReceiver(const Receiver* receiver) const
		{
			return m_object == static_cast<const RECEIVER*>(receiver);
		}
		virtual void onConnect(Transmitter& transmitter)
		{
			m_object->onConnect(&transmitter);
		}
		virtual void onDisconnect(Transmitter& transmitter)
		{
			m_object->onDisconnect(&transmitter);
		}
		virtual void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8)
		{
			(m_object->*m_function)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		}
	private:
		RECEIVER* m_object;
		void (RECEIVER::* m_function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) const;
	}; // class const8
	class static8
		: public Connection
	{
	public:
		static8(StaticFunction8& function)
			: m_function(function)
		{ /* empty */ }
		virtual Connection* clone(void)
		{
			return new const8<RECEIVER>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new const8<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual bool isFunction(StaticFunction8* function) const
		{
			return &m_function == function;
		}
		virtual bool isReceiver(const Receiver*) const
		{
			return false;
		}
		virtual void onConnect(Transmitter& transmitter)
		{
			/* empty */;
		}
		virtual void onDisconnect(Transmitter& transmitter)
		{
			/* empty */;
		}
		virtual void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8)
		{
			m_function(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		}
	private:
		StaticFunction8& m_function;
	}; // class static8
public:
	Transmitter8(void)
		: m_receivers(NULL)
		, m_transmissionIter(NULL)
		, m_isRepeatTransmissionRequired(false)
		, m_isTransmitting(false)
	{ /* empty */ }
	Transmitter8(const Transmitter8& source)
		: Transmitter(source)
		, m_receivers(NULL)
		, m_transmissionIter(NULL)
		, m_isRepeatTransmissionRequired(false)
		, m_isTransmitting(false)
	{
		SYNC(m_mutex);
		Connection* iter(source.m_receivers);
		Connection* previous(NULL);
		Connection** destinationIter = &m_receivers;
		while (iter)
		{
			iter->onConnect(*this);
			*destinationIter = iter->clone();

			if (previous)
			{
				previous->m_next = *destinationIter;
			}

			previous = *destinationIter
				iter = iter->m_next;
		}
	}
	virtual ~Transmitter8(void)
	{
		disconnectAll();
	}
	void ceaseTransmission(void)
	{
		SYNC(m_mutex);
		disconnectAll();
		m_isTransmitting = false;
		m_transmissionIter = NULL;
		m_receivers = NULL;
	}
	template<class RECEIVER>
	void connect(RECEIVER* receiver, void (RECEIVER::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8))
	{
		if (receiver && function)
		{
			SYNC(m_mutex);
			Connection* iter(m_receivers);

			while (iter)
			{
				if (iter->isReceiver(receiver))
				{
					return;
				}

				iter = iter->m_next;
			}

			Connection* connection(new volatile8<RECEIVER>(receiver, function));
			connection->m_next = m_receivers;
			m_receivers = connection;
			receiver->onConnect(this);
		}
	}
	template<class RECEIVER>
	void connect(RECEIVER* receiver, void (RECEIVER::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) const)
	{
		if (receiver && function)
		{
			SYNC(m_mutex);
			Connection* iter(m_receivers);

			while (iter)
			{
				if (iter->isReceiver(receiver))
				{
					return;
				}

				iter = iter->m_next;
			}

			Connection* connection(new const8<RECEIVER>(receiver, function));
			connection->m_next = m_receivers;
			m_receivers = connection;
			receiver->onConnect(this);
		}
	}
	void connect(StaticFunction8& function)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);

		while (iter)
		{
			if (iter->isFunction(&function))
			{
				return;
			}

			iter = iter->m_next;
		}

		Connection* connection(new static8(function));
		connection->m_next = m_receivers;
		m_receivers = connection;
	}
	void disconnect(Receiver* receiver)
	{
		disconnect(receiver, NULL);
	}
	void disconnect(StaticFunction8& function)
	{
		disconnect(NULL, function);
	}
	void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8)
	{
		SYNC(m_mutex);
		if (m_isTransmitting)
		{
			m_isRepeatTransmissionRequired = true;
		}
		else
		{
			m_isTransmitting = true;
			m_transmissionIter = m_receivers;
			// the receiver list can change be modified transmission
			while (m_transmissionIter)
			{
				m_transmissionIter->transmit(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
				// calling transmit() might have triggered the removal of the receiver
				if (m_transmissionIter)
					m_transmissionIter = m_transmissionIter->m_next;
				else
					m_transmissionIter = m_receivers;
			}

			m_isTransmitting = false;

			if (m_isRepeatTransmissionRequired)
			{
				m_isRepeatTransmissionRequired = false;
				transmit(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
			}
		}
	}
	inline void operator()(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8)
	{
		transmit(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
	}
protected:
	void disconnect(Receiver* receiver, StaticFunction8* function)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);
		Connection* previous(NULL);

		while (iter)
		{
			bool isFound;

			if (iter->isReceiver(receiver))
			{
				receiver->onDisconnect(this);
				isFound = true;
			}
			else
			{
				isFound = iter->isFunction(function);
			}

			if (isFound)
			{
				if (previous)
				{
					previous->m_next = iter->m_next;
				}
				else 
				{
					m_receivers = iter->m_next;
				}

				// if transmitting...	
				if (m_isTransmitting)
				{	// ... and we just removed the transmission iter ...
					if (m_transmissionIter == iter)
					{	// .. set the iterator back one to preserve the transmission iteration
						m_transmissionIter = previous;
					}
				}

				delete iter;
				break;
			}				
			previous = iter;
			iter = iter->m_next;
		}
	}
	void disconnectAll(void)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);

		while (iter)
		{
			iter->onDisconnect(*this);
			Connection* stale(iter);
			iter = iter->m_next;
			delete stale;
		}

		m_receivers = NULL;
	}
	void onDisconnect(Receiver* receiver)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);
		Connection* previous(NULL);

		while (iter)
		{
			if (iter->isReceiver(receiver))
			{
				if (previous)
				{
					previous->m_next = iter->m_next;
				}
				else
				{
					m_receivers = iter->m_next;
				}

				delete iter;
				break;
			}

			previous = iter;
			iter = iter->m_next;
		}
	}
	void replicate(const Receiver* receiver, Receiver* new_receiver)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);

		while (iter)
		{
			if (iter->isReceiver(receiver))
			{
				Connection* connection = iter->duplicate(new_receiver);
				connection->m_next = m_receivers;
				m_receivers = connection;
				break;
			}
		}
	}
private:
	DECLARE_MUTABLE_MUTEX(m_mutex)
	Connection* m_receivers;
	Connection* m_transmissionIter;
	bool m_isRepeatTransmissionRequired;
	bool m_isTransmitting;
}; // class Transmitter8

template<typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9>
class Transmitter9 : public Transmitter
{
	typedef void StaticFunction9(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9);

	class Connection
	{
	public:
		Connection(void) : m_next(NULL) { /* empty */ };
		virtual ~Connection(void)=0 { /* empty */ };
		virtual Connection* clone(void)=0;
		virtual Connection* duplicate(Receiver* receiver)=0;
		virtual bool isFunction(StaticFunction9*) const=0;
		virtual bool isReceiver(const Receiver*) const=0;
		virtual void onConnect(Transmitter&)=0;
		virtual void onDisconnect(Transmitter&)=0;
		virtual void transmit(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9)=0;
		Connection* m_next;
	}; // class Connection
	template< class RECEIVER >
	class volatile9
		: public Connection
	{
	public:
		volatile9(RECEIVER* object, void (RECEIVER::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9))
			: m_object(object)
			, m_function(function)
		{ /* empty */ }
		virtual Connection* clone(void)
		{
			return new volatile9<RECEIVER>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new volatile9<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual bool isFunction(StaticFunction9*) const
		{
			return false;
		}
		virtual bool isReceiver(const Receiver* receiver) const
		{
			return m_object == static_cast<const RECEIVER*>(receiver);
		}
		virtual void onConnect(Transmitter& transmitter)
		{
			m_object->onConnect(&transmitter);
		}
		virtual void onDisconnect(Transmitter& transmitter)
		{
			m_object->onDisconnect(&transmitter);
		}
		virtual void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9)
		{
			(m_object->*m_function)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		}
	private:
		RECEIVER* m_object;
		void (RECEIVER::* m_function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9);
	}; // class volatile9
	template<class RECEIVER >
	class const9
		: public Connection
	{
	public:
		const9(RECEIVER* object, void (RECEIVER::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) const)
			: m_object(object)
			, m_function(function)
		{ /* empty */ }
		virtual Connection* clone(void)
		{
			return new const9<RECEIVER>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new const9<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual bool isFunction(StaticFunction9*) const
		{
			return false;
		}
		virtual bool isReceiver(const Receiver* receiver) const
		{
			return m_object == static_cast<const RECEIVER*>(receiver);
		}
		virtual void onConnect(Transmitter& transmitter)
		{
			m_object->onConnect(&transmitter);
		}
		virtual void onDisconnect(Transmitter& transmitter)
		{
			m_object->onDisconnect(&transmitter);
		}
		virtual void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9)
		{
			(m_object->*m_function)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		}
	private:
		RECEIVER* m_object;
		void (RECEIVER::* m_function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) const;
	}; // class const9
	class static9
		: public Connection
	{
	public:
		static9(StaticFunction9& function)
			: m_function(function)
		{ /* empty */ }
		virtual Connection* clone(void)
		{
			return new const9<RECEIVER>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new const9<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual bool isFunction(StaticFunction9* function) const
		{
			return &m_function == function;
		}
		virtual bool isReceiver(const Receiver*) const
		{
			return false;
		}
		virtual void onConnect(Transmitter& transmitter)
		{
			/* empty */;
		}
		virtual void onDisconnect(Transmitter& transmitter)
		{
			/* empty */;
		}
		virtual void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9)
		{
			m_function(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		}
	private:
		StaticFunction9& m_function;
	}; // class static9
public:
	Transmitter9(void)
		: m_receivers(NULL)
		, m_transmissionIter(NULL)
		, m_isRepeatTransmissionRequired(false)
		, m_isTransmitting(false)
	{ /* empty */ }
	Transmitter9(const Transmitter9& source)
		: Transmitter(source)
		, m_receivers(NULL)
		, m_transmissionIter(NULL)
		, m_isRepeatTransmissionRequired(false)
		, m_isTransmitting(false)
	{
		SYNC(m_mutex);
		Connection* iter(source.m_receivers);
		Connection* previous(NULL);
		Connection** destinationIter = &m_receivers;
		while (iter)
		{
			iter->onConnect(*this);
			*destinationIter = iter->clone();

			if (previous)
			{
				previous->m_next = *destinationIter;
			}

			previous = *destinationIter
				iter = iter->m_next;
		}
	}
	virtual ~Transmitter9(void)
	{
		disconnectAll();
	}
	void ceaseTransmission(void)
	{
		SYNC(m_mutex);
		disconnectAll();
		m_isTransmitting = false;
		m_transmissionIter = NULL;
		m_receivers = NULL;
	}
	template<class RECEIVER>
	void connect(RECEIVER* receiver, void (RECEIVER::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9))
	{
		if (receiver && function)
		{
			SYNC(m_mutex);
			Connection* iter(m_receivers);

			while (iter)
			{
				if (iter->isReceiver(receiver))
				{
					return;
				}

				iter = iter->m_next;
			}

			Connection* connection(new volatile9<RECEIVER>(receiver, function));
			connection->m_next = m_receivers;
			m_receivers = connection;
			receiver->onConnect(this);
		}
	}
	template<class RECEIVER>
	void connect(RECEIVER* receiver, void (RECEIVER::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) const)
	{
		if (receiver && function)
		{
			SYNC(m_mutex);
			Connection* iter(m_receivers);

			while (iter)
			{
				if (iter->isReceiver(receiver))
				{
					return;
				}

				iter = iter->m_next;
			}

			Connection* connection(new const9<RECEIVER>(receiver, function));
			connection->m_next = m_receivers;
			m_receivers = connection;
			receiver->onConnect(this);
		}
	}
	void connect(StaticFunction9& function)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);

		while (iter)
		{
			if (iter->isFunction(&function))
			{
				return;
			}

			iter = iter->m_next;
		}

		Connection* connection(new static9(function));
		connection->m_next = m_receivers;
		m_receivers = connection;
	}
	void disconnect(Receiver* receiver)
	{
		disconnect(receiver, NULL);
	}
	void disconnect(StaticFunction9& function)
	{
		disconnect(NULL, function);
	}
	void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9)
	{
		SYNC(m_mutex);
		if (m_isTransmitting)
		{
			m_isRepeatTransmissionRequired = true;
		}
		else
		{
			m_isTransmitting = true;
			m_transmissionIter = m_receivers;
			// the receiver list can change be modified transmission
			while (m_transmissionIter)
			{
				m_transmissionIter->transmit(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
				// calling transmit() might have triggered the removal of the receiver
				if (m_transmissionIter)
					m_transmissionIter = m_transmissionIter->m_next;
				else
					m_transmissionIter = m_receivers;
			}

			m_isTransmitting = false;

			if (m_isRepeatTransmissionRequired)
			{
				m_isRepeatTransmissionRequired = false;
				transmit(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
			}
		}
	}
	inline void operator()(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9)
	{
		transmit(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
	}
protected:
	void disconnect(Receiver* receiver, StaticFunction9* function)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);
		Connection* previous(NULL);

		while (iter)
		{
			bool isFound;

			if (iter->isReceiver(receiver))
			{
				receiver->onDisconnect(this);
				isFound = true;
			}
			else
			{
				isFound = iter->isFunction(function);
			}

			if (isFound)
			{
				if (previous)
				{
					previous->m_next = iter->m_next;
				}
				else 
				{
					m_receivers = iter->m_next;
				}

				// if transmitting...	
				if (m_isTransmitting)
				{	// ... and we just removed the transmission iter ...
					if (m_transmissionIter == iter)
					{	// .. set the iterator back one to preserve the transmission iteration
						m_transmissionIter = previous;
					}
				}

				delete iter;
				break;
			}				
			previous = iter;
			iter = iter->m_next;
		}
	}
	void disconnectAll(void)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);

		while (iter)
		{
			iter->onDisconnect(*this);
			Connection* stale(iter);
			iter = iter->m_next;
			delete stale;
		}

		m_receivers = NULL;
	}
	void onDisconnect(Receiver* receiver)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);
		Connection* previous(NULL);

		while (iter)
		{
			if (iter->isReceiver(receiver))
			{
				if (previous)
				{
					previous->m_next = iter->m_next;
				}
				else
				{
					m_receivers = iter->m_next;
				}

				delete iter;
				break;
			}

			previous = iter;
			iter = iter->m_next;
		}
	}
	void replicate(const Receiver* receiver, Receiver* new_receiver)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);

		while (iter)
		{
			if (iter->isReceiver(receiver))
			{
				Connection* connection = iter->duplicate(new_receiver);
				connection->m_next = m_receivers;
				m_receivers = connection;
				break;
			}
		}
	}
private:
	DECLARE_MUTABLE_MUTEX(m_mutex)
	Connection* m_receivers;
	Connection* m_transmissionIter;
	bool m_isRepeatTransmissionRequired;
	bool m_isTransmitting;
}; // class Transmitter9

template<typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10>
class Transmitter10 : public Transmitter
{
	typedef void StaticFunction10(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10);

	class Connection
	{
	public:
		Connection(void) : m_next(NULL) { /* empty */ };
		virtual ~Connection(void)=0 { /* empty */ };
		virtual Connection* clone(void)=0;
		virtual Connection* duplicate(Receiver* receiver)=0;
		virtual bool isFunction(StaticFunction10*) const=0;
		virtual bool isReceiver(const Receiver*) const=0;
		virtual void onConnect(Transmitter&)=0;
		virtual void onDisconnect(Transmitter&)=0;
		virtual void transmit(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10)=0;
		Connection* m_next;
	}; // class Connection
	template< class RECEIVER >
	class volatile10
		: public Connection
	{
	public:
		volatile10(RECEIVER* object, void (RECEIVER::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10))
			: m_object(object)
			, m_function(function)
		{ /* empty */ }
		virtual Connection* clone(void)
		{
			return new volatile10<RECEIVER>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new volatile10<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual bool isFunction(StaticFunction10*) const
		{
			return false;
		}
		virtual bool isReceiver(const Receiver* receiver) const
		{
			return m_object == static_cast<const RECEIVER*>(receiver);
		}
		virtual void onConnect(Transmitter& transmitter)
		{
			m_object->onConnect(&transmitter);
		}
		virtual void onDisconnect(Transmitter& transmitter)
		{
			m_object->onDisconnect(&transmitter);
		}
		virtual void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, ARG_10 arg10)
		{
			(m_object->*m_function)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		}
	private:
		RECEIVER* m_object;
		void (RECEIVER::* m_function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10);
	}; // class volatile10
	template<class RECEIVER >
	class const10
		: public Connection
	{
	public:
		const10(RECEIVER* object, void (RECEIVER::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) const)
			: m_object(object)
			, m_function(function)
		{ /* empty */ }
		virtual Connection* clone(void)
		{
			return new const10<RECEIVER>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new const10<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual bool isFunction(StaticFunction10*) const
		{
			return false;
		}
		virtual bool isReceiver(const Receiver* receiver) const
		{
			return m_object == static_cast<const RECEIVER*>(receiver);
		}
		virtual void onConnect(Transmitter& transmitter)
		{
			m_object->onConnect(&transmitter);
		}
		virtual void onDisconnect(Transmitter& transmitter)
		{
			m_object->onDisconnect(&transmitter);
		}
		virtual void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, ARG_10 arg10)
		{
			(m_object->*m_function)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		}
	private:
		RECEIVER* m_object;
		void (RECEIVER::* m_function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) const;
	}; // class const10
	class static10
		: public Connection
	{
	public:
		static10(StaticFunction10& function)
			: m_function(function)
		{ /* empty */ }
		virtual Connection* clone(void)
		{
			return new const10<RECEIVER>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new const10<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual bool isFunction(StaticFunction10* function) const
		{
			return &m_function == function;
		}
		virtual bool isReceiver(const Receiver*) const
		{
			return false;
		}
		virtual void onConnect(Transmitter& transmitter)
		{
			/* empty */;
		}
		virtual void onDisconnect(Transmitter& transmitter)
		{
			/* empty */;
		}
		virtual void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, ARG_10 arg10)
		{
			m_function(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		}
	private:
		StaticFunction10& m_function;
	}; // class static10
public:
	Transmitter10(void)
		: m_receivers(NULL)
		, m_transmissionIter(NULL)
		, m_isRepeatTransmissionRequired(false)
		, m_isTransmitting(false)
	{ /* empty */ }
	Transmitter10(const Transmitter10& source)
		: Transmitter(source)
		, m_receivers(NULL)
		, m_transmissionIter(NULL)
		, m_isRepeatTransmissionRequired(false)
		, m_isTransmitting(false)
	{
		SYNC(m_mutex);
		Connection* iter(source.m_receivers);
		Connection* previous(NULL);
		Connection** destinationIter = &m_receivers;
		while (iter)
		{
			iter->onConnect(*this);
			*destinationIter = iter->clone();

			if (previous)
			{
				previous->m_next = *destinationIter;
			}

			previous = *destinationIter
				iter = iter->m_next;
		}
	}
	virtual ~Transmitter10(void)
	{
		disconnectAll();
	}
	void ceaseTransmission(void)
	{
		SYNC(m_mutex);
		disconnectAll();
		m_isTransmitting = false;
		m_transmissionIter = NULL;
		m_receivers = NULL;
	}
	template<class RECEIVER>
	void connect(RECEIVER* receiver, void (RECEIVER::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10))
	{
		if (receiver && function)
		{
			SYNC(m_mutex);
			Connection* iter(m_receivers);

			while (iter)
			{
				if (iter->isReceiver(receiver))
				{
					return;
				}

				iter = iter->m_next;
			}

			Connection* connection(new volatile10<RECEIVER>(receiver, function));
			connection->m_next = m_receivers;
			m_receivers = connection;
			receiver->onConnect(this);
		}
	}
	template<class RECEIVER>
	void connect(RECEIVER* receiver, void (RECEIVER::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) const)
	{
		if (receiver && function)
		{
			SYNC(m_mutex);
			Connection* iter(m_receivers);

			while (iter)
			{
				if (iter->isReceiver(receiver))
				{
					return;
				}

				iter = iter->m_next;
			}

			Connection* connection(new const10<RECEIVER>(receiver, function));
			connection->m_next = m_receivers;
			m_receivers = connection;
			receiver->onConnect(this);
		}
	}
	void connect(StaticFunction10& function)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);

		while (iter)
		{
			if (iter->isFunction(&function))
			{
				return;
			}

			iter = iter->m_next;
		}

		Connection* connection(new static10(function));
		connection->m_next = m_receivers;
		m_receivers = connection;
	}
	void disconnect(Receiver* receiver)
	{
		disconnect(receiver, NULL);
	}
	void disconnect(StaticFunction10& function)
	{
		disconnect(NULL, function);
	}
	void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, ARG_10 arg10)
	{
		SYNC(m_mutex);
		if (m_isTransmitting)
		{
			m_isRepeatTransmissionRequired = true;
		}
		else
		{
			m_isTransmitting = true;
			m_transmissionIter = m_receivers;
			// the receiver list can change be modified transmission
			while (m_transmissionIter)
			{
				m_transmissionIter->transmit(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
				// calling transmit() might have triggered the removal of the receiver
				if (m_transmissionIter)
					m_transmissionIter = m_transmissionIter->m_next;
				else
					m_transmissionIter = m_receivers;
			}

			m_isTransmitting = false;

			if (m_isRepeatTransmissionRequired)
			{
				m_isRepeatTransmissionRequired = false;
				transmit(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
			}
		}
	}
	inline void operator()(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, ARG_10 arg10)
	{
		transmit(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
	}
protected:
	void disconnect(Receiver* receiver, StaticFunction10* function)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);
		Connection* previous(NULL);

		while (iter)
		{
			bool isFound;

			if (iter->isReceiver(receiver))
			{
				receiver->onDisconnect(this);
				isFound = true;
			}
			else
			{
				isFound = iter->isFunction(function);
			}

			if (isFound)
			{
				if (previous)
				{
					previous->m_next = iter->m_next;
				}
				else 
				{
					m_receivers = iter->m_next;
				}

				// if transmitting...	
				if (m_isTransmitting)
				{	// ... and we just removed the transmission iter ...
					if (m_transmissionIter == iter)
					{	// .. set the iterator back one to preserve the transmission iteration
						m_transmissionIter = previous;
					}
				}

				delete iter;
				break;
			}				
			previous = iter;
			iter = iter->m_next;
		}
	}
	void disconnectAll(void)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);

		while (iter)
		{
			iter->onDisconnect(*this);
			Connection* stale(iter);
			iter = iter->m_next;
			delete stale;
		}

		m_receivers = NULL;
	}
	void onDisconnect(Receiver* receiver)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);
		Connection* previous(NULL);

		while (iter)
		{
			if (iter->isReceiver(receiver))
			{
				if (previous)
				{
					previous->m_next = iter->m_next;
				}
				else
				{
					m_receivers = iter->m_next;
				}

				delete iter;
				break;
			}

			previous = iter;
			iter = iter->m_next;
		}
	}
	void replicate(const Receiver* receiver, Receiver* new_receiver)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);

		while (iter)
		{
			if (iter->isReceiver(receiver))
			{
				Connection* connection = iter->duplicate(new_receiver);
				connection->m_next = m_receivers;
				m_receivers = connection;
				break;
			}
		}
	}
private:
	DECLARE_MUTABLE_MUTEX(m_mutex)
	Connection* m_receivers;
	Connection* m_transmissionIter;
	bool m_isRepeatTransmissionRequired;
	bool m_isTransmitting;
}; // class Transmitter10

} // namespace signals
#endif//SIGNALS_H