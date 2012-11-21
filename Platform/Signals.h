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
private:
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
		virtual Receiver* getReceiver(void) const=0;
		virtual void transmit(void)=0;
		Connection* m_next;
	};
	/** 
	templated abstraction for receivers that registered non-const 
	member functions with this transmitter
	*/
	template<class RECEIVER>
	class volatile0 : public Connection
	{
	public:
		volatile0(void)
		: m_object(NULL)
		, m_function(NULL)
		{ /* empty */ }

		volatile0(RECEIVER* object, void (RECEIVER::* function)(void))
		: m_object(object)
		, m_function(function)
		{ /* empty */ }

		virtual Connection* clone(void)
		{
			return new volatile0<RECEIVER>(*this);
		}

		virtual Connection* duplicate(Receiver* receiver)
		{
			return new volatile0<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}

		virtual Receiver* getReceiver(void) const
		{
			return m_object;
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
	templated abstraction for receivers that registered const 
	member functions with this transmitter
	*/
	template<class RECEIVER>
	class const0 : public Connection
	{
	public:
		const0(void)
		: m_object(NULL)
		, m_function(NULL)
		{ /* empty */ }

		const0(RECEIVER* object, void (RECEIVER::* function)(void) const)
		: m_object(object)
		, m_function(function)
		{ /* empty */ }

		virtual Connection* clone(void)
		{
			return new const0<RECEIVER>(*this);
		}

		virtual Connection* duplicate(Receiver* receiver)
		{
			return new const0<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}

		virtual Receiver* getReceiver(void) const
		{
			return m_object;
		}

		virtual void transmit(void) 
		{
			(m_object->*m_function)();
		}

	private:
		RECEIVER*			m_object;
		void (RECEIVER::*	m_function)(void) const;
	};

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
		Connection* destinationIter = m_receivers;
		while (iter)
		{
			iter->getReceiver()->onConnect(this);
			
			destinationIter = iter->clone();
			
			if (previous)
			{	
				previous->m_next = destinationIter;
			}
			
			previous = destinationIter;
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
				if (iter->getReceiver() == static_cast<Receiver*>(receiver))
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
				if (iter->getReceiver() == static_cast<Receiver*>(receiver))
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

	/** disconnect all methods the receiver has registered */
	void disconnect(Receiver* receiver)
	{
		if (receiver)
		{
			SYNC(m_mutex);
			Connection* iter(m_receivers);
			Connection* previous(NULL);
			
			while (iter)
			{
				if (iter->getReceiver() == receiver)
				{	
					receiver->onDisconnect(this);
					
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
	/** called by the disconnection process, removes the receiver from the list */
	void onDisconnect(Receiver* receiver)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);
		Connection* previous(NULL);

		while (iter)
		{
			if (iter->getReceiver() == receiver)
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

	/** disconnects all receivers, but doesn't empty the list */
	void disconnectAll(void)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);
		
		while (iter)
		{
			iter->getReceiver()->onDisconnect(this);
			Connection* stale(iter);
			iter = iter->m_next;
			delete stale;
		}

		m_receivers = NULL;
	}
	
	/** helps with copy constructors */
	void replicate(const Receiver* receiver, Receiver* new_receiver)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);
		while (iter)
		{
			if (iter->getReceiver() == receiver)
			{
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
private:
	class Connection
	{
	public:
		Connection(void) : m_next(NULL) { /* empty */ };
		virtual ~Connection(void)=0 {};
		virtual Connection* clone(void)=0;
		virtual Connection* duplicate(Receiver* receiver)=0;
		virtual Receiver* getReceiver(void) const=0;
		virtual void transmit(ARG_1)=0;
		Connection* m_next;
	}; // class Connection
	template< class RECEIVER >
	class volatile1
		: public Connection
	{
	public:
		volatile1(void)
			: m_object(NULL)
			, m_function(NULL)
		{}
		volatile1(RECEIVER* object, void (RECEIVER::* function)(ARG_1))
			: m_object(object)
			, m_function(function)
		{}
		virtual Connection* clone(void)
		{
			return new volatile1<RECEIVER>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new volatile1<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual Receiver* getReceiver(void) const
		{
			return m_object;
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
		const1(void)
			: m_object(NULL)
			, m_function(NULL)
		{}
		const1(RECEIVER* object, void (RECEIVER::* function)(ARG_1) const)
			: m_object(object)
			, m_function(function)
		{}
		virtual Connection* clone(void)
		{
			return new const1<RECEIVER>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new const1<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual Receiver* getReceiver(void) const
		{
			return m_object;
		}
		virtual void transmit(ARG_1 arg1)
		{
			(m_object->*m_function)(arg1);
		}
	private:
		RECEIVER* m_object;
		void (RECEIVER::* m_function)(ARG_1) const;
	}; // class const1
public:
	Transmitter1(void)
		: m_receivers(NULL)
		, m_transmissionIter(NULL)
		, m_isRepeatTransmissionRequired(false)
		, m_isTransmitting(false)
	{ /* empty */}
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
		Connection* destinationIter = m_receivers;
		while (iter)
		{
			iter->getReceiver()->onConnect(this);
			destinationIter = iter->clone();

			if (previous)
			{
				previous->m_next = destinationIter;
			}

			previous = destinationIter
				iter = iter->m_next;
		}
	}
	virtual ~Transmitter1(void)
	{
		disconnectAll();
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
				if (iter->getReceiver() == static_cast<Receiver*>(receiver))
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
				if (iter->getReceiver() == static_cast<Receiver*>(receiver))
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
	void ceaseTransmission(void)
	{
		SYNC(m_mutex);
		disconnectAll();
		m_isTransmitting = false;
		m_transmissionIter = NULL;
		m_receivers = NULL;
	}
	void disconnect(Receiver* receiver)
	{
		if (receiver)
		{
			SYNC(m_mutex);
			Connection* iter(m_receivers);
			Connection* previous(NULL);

			while (iter)
			{
				if (iter->getReceiver() == receiver)				{
					receiver->onDisconnect(this);

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
	void onDisconnect(Receiver* receiver)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);
		Connection* previous(NULL);

		while (iter)
		{
			if (iter->getReceiver() == receiver)
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
	void disconnectAll(void)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);

		while (iter)
		{
			iter->getReceiver()->onDisconnect(this);
			Connection* stale(iter);
			iter = iter->m_next;
			delete stale;
		}

		m_receivers = NULL;	}
	void replicate(const Receiver* receiver, Receiver* new_receiver)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);

		while (iter)
		{
			if (iter->getReceiver() == receiver)
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
private:
	class Connection
	{
	public:
		Connection(void) : m_next(NULL) { /* empty */ };
		virtual ~Connection(void)=0 {};
		virtual Connection* clone(void)=0;
		virtual Connection* duplicate(Receiver* receiver)=0;
		virtual Receiver* getReceiver(void) const=0;
		virtual void transmit(ARG_1, ARG_2)=0;
		Connection* m_next;
	}; // class Connection
	template< class RECEIVER >
	class volatile2
		: public Connection
	{
	public:
		volatile2(void)
			: m_object(NULL)
			, m_function(NULL)
		{}
		volatile2(RECEIVER* object, void (RECEIVER::* function)(ARG_1, ARG_2))
			: m_object(object)
			, m_function(function)
		{}
		virtual Connection* clone(void)
		{
			return new volatile2<RECEIVER>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new volatile2<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual Receiver* getReceiver(void) const
		{
			return m_object;
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
		const2(void)
			: m_object(NULL)
			, m_function(NULL)
		{}
		const2(RECEIVER* object, void (RECEIVER::* function)(ARG_1, ARG_2) const)
			: m_object(object)
			, m_function(function)
		{}
		virtual Connection* clone(void)
		{
			return new const2<RECEIVER>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new const2<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual Receiver* getReceiver(void) const
		{
			return m_object;
		}
		virtual void transmit(ARG_1 arg1, ARG_2 arg2)
		{
			(m_object->*m_function)(arg1, arg2);
		}
	private:
		RECEIVER* m_object;
		void (RECEIVER::* m_function)(ARG_1, ARG_2) const;
	}; // class const2
public:
	Transmitter2(void)
		: m_receivers(NULL)
		, m_transmissionIter(NULL)
		, m_isRepeatTransmissionRequired(false)
		, m_isTransmitting(false)
	{ /* empty */}
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
		Connection* destinationIter = m_receivers;
		while (iter)
		{
			iter->getReceiver()->onConnect(this);
			destinationIter = iter->clone();

			if (previous)
			{
				previous->m_next = destinationIter;
			}

			previous = destinationIter
				iter = iter->m_next;
		}
	}
	virtual ~Transmitter2(void)
	{
		disconnectAll();
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
				if (iter->getReceiver() == static_cast<Receiver*>(receiver))
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
				if (iter->getReceiver() == static_cast<Receiver*>(receiver))
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
	void ceaseTransmission(void)
	{
		SYNC(m_mutex);
		disconnectAll();
		m_isTransmitting = false;
		m_transmissionIter = NULL;
		m_receivers = NULL;
	}
	void disconnect(Receiver* receiver)
	{
		if (receiver)
		{
			SYNC(m_mutex);
			Connection* iter(m_receivers);
			Connection* previous(NULL);

			while (iter)
			{
				if (iter->getReceiver() == receiver)				{
					receiver->onDisconnect(this);

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
	void onDisconnect(Receiver* receiver)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);
		Connection* previous(NULL);

		while (iter)
		{
			if (iter->getReceiver() == receiver)
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
	void disconnectAll(void)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);

		while (iter)
		{
			iter->getReceiver()->onDisconnect(this);
			Connection* stale(iter);
			iter = iter->m_next;
			delete stale;
		}

		m_receivers = NULL;	}
	void replicate(const Receiver* receiver, Receiver* new_receiver)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);

		while (iter)
		{
			if (iter->getReceiver() == receiver)
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
private:
	class Connection
	{
	public:
		Connection(void) : m_next(NULL) { /* empty */ };
		virtual ~Connection(void)=0 {};
		virtual Connection* clone(void)=0;
		virtual Connection* duplicate(Receiver* receiver)=0;
		virtual Receiver* getReceiver(void) const=0;
		virtual void transmit(ARG_1, ARG_2, ARG_3)=0;
		Connection* m_next;
	}; // class Connection
	template< class RECEIVER >
	class volatile3
		: public Connection
	{
	public:
		volatile3(void)
			: m_object(NULL)
			, m_function(NULL)
		{}
		volatile3(RECEIVER* object, void (RECEIVER::* function)(ARG_1, ARG_2, ARG_3))
			: m_object(object)
			, m_function(function)
		{}
		virtual Connection* clone(void)
		{
			return new volatile3<RECEIVER>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new volatile3<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual Receiver* getReceiver(void) const
		{
			return m_object;
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
		const3(void)
			: m_object(NULL)
			, m_function(NULL)
		{}
		const3(RECEIVER* object, void (RECEIVER::* function)(ARG_1, ARG_2, ARG_3) const)
			: m_object(object)
			, m_function(function)
		{}
		virtual Connection* clone(void)
		{
			return new const3<RECEIVER>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new const3<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual Receiver* getReceiver(void) const
		{
			return m_object;
		}
		virtual void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3)
		{
			(m_object->*m_function)(arg1, arg2, arg3);
		}
	private:
		RECEIVER* m_object;
		void (RECEIVER::* m_function)(ARG_1, ARG_2, ARG_3) const;
	}; // class const3
public:
	Transmitter3(void)
		: m_receivers(NULL)
		, m_transmissionIter(NULL)
		, m_isRepeatTransmissionRequired(false)
		, m_isTransmitting(false)
	{ /* empty */}
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
		Connection* destinationIter = m_receivers;
		while (iter)
		{
			iter->getReceiver()->onConnect(this);
			destinationIter = iter->clone();

			if (previous)
			{
				previous->m_next = destinationIter;
			}

			previous = destinationIter
				iter = iter->m_next;
		}
	}
	virtual ~Transmitter3(void)
	{
		disconnectAll();
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
				if (iter->getReceiver() == static_cast<Receiver*>(receiver))
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
				if (iter->getReceiver() == static_cast<Receiver*>(receiver))
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
	void ceaseTransmission(void)
	{
		SYNC(m_mutex);
		disconnectAll();
		m_isTransmitting = false;
		m_transmissionIter = NULL;
		m_receivers = NULL;
	}
	void disconnect(Receiver* receiver)
	{
		if (receiver)
		{
			SYNC(m_mutex);
			Connection* iter(m_receivers);
			Connection* previous(NULL);

			while (iter)
			{
				if (iter->getReceiver() == receiver)				{
					receiver->onDisconnect(this);

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
	void onDisconnect(Receiver* receiver)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);
		Connection* previous(NULL);

		while (iter)
		{
			if (iter->getReceiver() == receiver)
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
	void disconnectAll(void)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);

		while (iter)
		{
			iter->getReceiver()->onDisconnect(this);
			Connection* stale(iter);
			iter = iter->m_next;
			delete stale;
		}

		m_receivers = NULL;	}
	void replicate(const Receiver* receiver, Receiver* new_receiver)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);

		while (iter)
		{
			if (iter->getReceiver() == receiver)
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
private:
	class Connection
	{
	public:
		Connection(void) : m_next(NULL) { /* empty */ };
		virtual ~Connection(void)=0 {};
		virtual Connection* clone(void)=0;
		virtual Connection* duplicate(Receiver* receiver)=0;
		virtual Receiver* getReceiver(void) const=0;
		virtual void transmit(ARG_1, ARG_2, ARG_3, ARG_4)=0;
		Connection* m_next;
	}; // class Connection
	template< class RECEIVER >
	class volatile4
		: public Connection
	{
	public:
		volatile4(void)
			: m_object(NULL)
			, m_function(NULL)
		{}
		volatile4(RECEIVER* object, void (RECEIVER::* function)(ARG_1, ARG_2, ARG_3, ARG_4))
			: m_object(object)
			, m_function(function)
		{}
		virtual Connection* clone(void)
		{
			return new volatile4<RECEIVER>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new volatile4<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual Receiver* getReceiver(void) const
		{
			return m_object;
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
		const4(void)
			: m_object(NULL)
			, m_function(NULL)
		{}
		const4(RECEIVER* object, void (RECEIVER::* function)(ARG_1, ARG_2, ARG_3, ARG_4) const)
			: m_object(object)
			, m_function(function)
		{}
		virtual Connection* clone(void)
		{
			return new const4<RECEIVER>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new const4<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual Receiver* getReceiver(void) const
		{
			return m_object;
		}
		virtual void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4)
		{
			(m_object->*m_function)(arg1, arg2, arg3, arg4);
		}
	private:
		RECEIVER* m_object;
		void (RECEIVER::* m_function)(ARG_1, ARG_2, ARG_3, ARG_4) const;
	}; // class const4
public:
	Transmitter4(void)
		: m_receivers(NULL)
		, m_transmissionIter(NULL)
		, m_isRepeatTransmissionRequired(false)
		, m_isTransmitting(false)
	{ /* empty */}
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
		Connection* destinationIter = m_receivers;
		while (iter)
		{
			iter->getReceiver()->onConnect(this);
			destinationIter = iter->clone();

			if (previous)
			{
				previous->m_next = destinationIter;
			}

			previous = destinationIter
				iter = iter->m_next;
		}
	}
	virtual ~Transmitter4(void)
	{
		disconnectAll();
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
				if (iter->getReceiver() == static_cast<Receiver*>(receiver))
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
				if (iter->getReceiver() == static_cast<Receiver*>(receiver))
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
	void ceaseTransmission(void)
	{
		SYNC(m_mutex);
		disconnectAll();
		m_isTransmitting = false;
		m_transmissionIter = NULL;
		m_receivers = NULL;
	}
	void disconnect(Receiver* receiver)
	{
		if (receiver)
		{
			SYNC(m_mutex);
			Connection* iter(m_receivers);
			Connection* previous(NULL);

			while (iter)
			{
				if (iter->getReceiver() == receiver)				{
					receiver->onDisconnect(this);

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
	void onDisconnect(Receiver* receiver)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);
		Connection* previous(NULL);

		while (iter)
		{
			if (iter->getReceiver() == receiver)
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
	void disconnectAll(void)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);

		while (iter)
		{
			iter->getReceiver()->onDisconnect(this);
			Connection* stale(iter);
			iter = iter->m_next;
			delete stale;
		}

		m_receivers = NULL;	}
	void replicate(const Receiver* receiver, Receiver* new_receiver)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);

		while (iter)
		{
			if (iter->getReceiver() == receiver)
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
private:
	class Connection
	{
	public:
		Connection(void) : m_next(NULL) { /* empty */ };
		virtual ~Connection(void)=0 {};
		virtual Connection* clone(void)=0;
		virtual Connection* duplicate(Receiver* receiver)=0;
		virtual Receiver* getReceiver(void) const=0;
		virtual void transmit(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5)=0;
		Connection* m_next;
	}; // class Connection
	template< class RECEIVER >
	class volatile5
		: public Connection
	{
	public:
		volatile5(void)
			: m_object(NULL)
			, m_function(NULL)
		{}
		volatile5(RECEIVER* object, void (RECEIVER::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5))
			: m_object(object)
			, m_function(function)
		{}
		virtual Connection* clone(void)
		{
			return new volatile5<RECEIVER>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new volatile5<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual Receiver* getReceiver(void) const
		{
			return m_object;
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
		const5(void)
			: m_object(NULL)
			, m_function(NULL)
		{}
		const5(RECEIVER* object, void (RECEIVER::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) const)
			: m_object(object)
			, m_function(function)
		{}
		virtual Connection* clone(void)
		{
			return new const5<RECEIVER>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new const5<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual Receiver* getReceiver(void) const
		{
			return m_object;
		}
		virtual void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5)
		{
			(m_object->*m_function)(arg1, arg2, arg3, arg4, arg5);
		}
	private:
		RECEIVER* m_object;
		void (RECEIVER::* m_function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) const;
	}; // class const5
public:
	Transmitter5(void)
		: m_receivers(NULL)
		, m_transmissionIter(NULL)
		, m_isRepeatTransmissionRequired(false)
		, m_isTransmitting(false)
	{ /* empty */}
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
		Connection* destinationIter = m_receivers;
		while (iter)
		{
			iter->getReceiver()->onConnect(this);
			destinationIter = iter->clone();

			if (previous)
			{
				previous->m_next = destinationIter;
			}

			previous = destinationIter
				iter = iter->m_next;
		}
	}
	virtual ~Transmitter5(void)
	{
		disconnectAll();
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
				if (iter->getReceiver() == static_cast<Receiver*>(receiver))
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
				if (iter->getReceiver() == static_cast<Receiver*>(receiver))
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
	void ceaseTransmission(void)
	{
		SYNC(m_mutex);
		disconnectAll();
		m_isTransmitting = false;
		m_transmissionIter = NULL;
		m_receivers = NULL;
	}
	void disconnect(Receiver* receiver)
	{
		if (receiver)
		{
			SYNC(m_mutex);
			Connection* iter(m_receivers);
			Connection* previous(NULL);

			while (iter)
			{
				if (iter->getReceiver() == receiver)				{
					receiver->onDisconnect(this);

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
	void onDisconnect(Receiver* receiver)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);
		Connection* previous(NULL);

		while (iter)
		{
			if (iter->getReceiver() == receiver)
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
	void disconnectAll(void)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);

		while (iter)
		{
			iter->getReceiver()->onDisconnect(this);
			Connection* stale(iter);
			iter = iter->m_next;
			delete stale;
		}

		m_receivers = NULL;	}
	void replicate(const Receiver* receiver, Receiver* new_receiver)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);

		while (iter)
		{
			if (iter->getReceiver() == receiver)
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
private:
	class Connection
	{
	public:
		Connection(void) : m_next(NULL) { /* empty */ };
		virtual ~Connection(void)=0 {};
		virtual Connection* clone(void)=0;
		virtual Connection* duplicate(Receiver* receiver)=0;
		virtual Receiver* getReceiver(void) const=0;
		virtual void transmit(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6)=0;
		Connection* m_next;
	}; // class Connection
	template< class RECEIVER >
	class volatile6
		: public Connection
	{
	public:
		volatile6(void)
			: m_object(NULL)
			, m_function(NULL)
		{}
		volatile6(RECEIVER* object, void (RECEIVER::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6))
			: m_object(object)
			, m_function(function)
		{}
		virtual Connection* clone(void)
		{
			return new volatile6<RECEIVER>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new volatile6<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual Receiver* getReceiver(void) const
		{
			return m_object;
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
		const6(void)
			: m_object(NULL)
			, m_function(NULL)
		{}
		const6(RECEIVER* object, void (RECEIVER::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) const)
			: m_object(object)
			, m_function(function)
		{}
		virtual Connection* clone(void)
		{
			return new const6<RECEIVER>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new const6<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual Receiver* getReceiver(void) const
		{
			return m_object;
		}
		virtual void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6)
		{
			(m_object->*m_function)(arg1, arg2, arg3, arg4, arg5, arg6);
		}
	private:
		RECEIVER* m_object;
		void (RECEIVER::* m_function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) const;
	}; // class const6
public:
	Transmitter6(void)
		: m_receivers(NULL)
		, m_transmissionIter(NULL)
		, m_isRepeatTransmissionRequired(false)
		, m_isTransmitting(false)
	{ /* empty */}
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
		Connection* destinationIter = m_receivers;
		while (iter)
		{
			iter->getReceiver()->onConnect(this);
			destinationIter = iter->clone();

			if (previous)
			{
				previous->m_next = destinationIter;
			}

			previous = destinationIter
				iter = iter->m_next;
		}
	}
	virtual ~Transmitter6(void)
	{
		disconnectAll();
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
				if (iter->getReceiver() == static_cast<Receiver*>(receiver))
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
				if (iter->getReceiver() == static_cast<Receiver*>(receiver))
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
	void ceaseTransmission(void)
	{
		SYNC(m_mutex);
		disconnectAll();
		m_isTransmitting = false;
		m_transmissionIter = NULL;
		m_receivers = NULL;
	}
	void disconnect(Receiver* receiver)
	{
		if (receiver)
		{
			SYNC(m_mutex);
			Connection* iter(m_receivers);
			Connection* previous(NULL);

			while (iter)
			{
				if (iter->getReceiver() == receiver)				{
					receiver->onDisconnect(this);

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
	void onDisconnect(Receiver* receiver)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);
		Connection* previous(NULL);

		while (iter)
		{
			if (iter->getReceiver() == receiver)
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
	void disconnectAll(void)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);

		while (iter)
		{
			iter->getReceiver()->onDisconnect(this);
			Connection* stale(iter);
			iter = iter->m_next;
			delete stale;
		}

		m_receivers = NULL;	}
	void replicate(const Receiver* receiver, Receiver* new_receiver)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);

		while (iter)
		{
			if (iter->getReceiver() == receiver)
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
private:
	class Connection
	{
	public:
		Connection(void) : m_next(NULL) { /* empty */ };
		virtual ~Connection(void)=0 {};
		virtual Connection* clone(void)=0;
		virtual Connection* duplicate(Receiver* receiver)=0;
		virtual Receiver* getReceiver(void) const=0;
		virtual void transmit(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7)=0;
		Connection* m_next;
	}; // class Connection
	template< class RECEIVER >
	class volatile7
		: public Connection
	{
	public:
		volatile7(void)
			: m_object(NULL)
			, m_function(NULL)
		{}
		volatile7(RECEIVER* object, void (RECEIVER::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7))
			: m_object(object)
			, m_function(function)
		{}
		virtual Connection* clone(void)
		{
			return new volatile7<RECEIVER>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new volatile7<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual Receiver* getReceiver(void) const
		{
			return m_object;
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
		const7(void)
			: m_object(NULL)
			, m_function(NULL)
		{}
		const7(RECEIVER* object, void (RECEIVER::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) const)
			: m_object(object)
			, m_function(function)
		{}
		virtual Connection* clone(void)
		{
			return new const7<RECEIVER>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new const7<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual Receiver* getReceiver(void) const
		{
			return m_object;
		}
		virtual void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7)
		{
			(m_object->*m_function)(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		}
	private:
		RECEIVER* m_object;
		void (RECEIVER::* m_function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) const;
	}; // class const7
public:
	Transmitter7(void)
		: m_receivers(NULL)
		, m_transmissionIter(NULL)
		, m_isRepeatTransmissionRequired(false)
		, m_isTransmitting(false)
	{ /* empty */}
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
		Connection* destinationIter = m_receivers;
		while (iter)
		{
			iter->getReceiver()->onConnect(this);
			destinationIter = iter->clone();

			if (previous)
			{
				previous->m_next = destinationIter;
			}

			previous = destinationIter
				iter = iter->m_next;
		}
	}
	virtual ~Transmitter7(void)
	{
		disconnectAll();
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
				if (iter->getReceiver() == static_cast<Receiver*>(receiver))
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
				if (iter->getReceiver() == static_cast<Receiver*>(receiver))
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
	void ceaseTransmission(void)
	{
		SYNC(m_mutex);
		disconnectAll();
		m_isTransmitting = false;
		m_transmissionIter = NULL;
		m_receivers = NULL;
	}
	void disconnect(Receiver* receiver)
	{
		if (receiver)
		{
			SYNC(m_mutex);
			Connection* iter(m_receivers);
			Connection* previous(NULL);

			while (iter)
			{
				if (iter->getReceiver() == receiver)				{
					receiver->onDisconnect(this);

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
	void onDisconnect(Receiver* receiver)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);
		Connection* previous(NULL);

		while (iter)
		{
			if (iter->getReceiver() == receiver)
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
	void disconnectAll(void)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);

		while (iter)
		{
			iter->getReceiver()->onDisconnect(this);
			Connection* stale(iter);
			iter = iter->m_next;
			delete stale;
		}

		m_receivers = NULL;	}
	void replicate(const Receiver* receiver, Receiver* new_receiver)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);

		while (iter)
		{
			if (iter->getReceiver() == receiver)
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
private:
	class Connection
	{
	public:
		Connection(void) : m_next(NULL) { /* empty */ };
		virtual ~Connection(void)=0 {};
		virtual Connection* clone(void)=0;
		virtual Connection* duplicate(Receiver* receiver)=0;
		virtual Receiver* getReceiver(void) const=0;
		virtual void transmit(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8)=0;
		Connection* m_next;
	}; // class Connection
	template< class RECEIVER >
	class volatile8
		: public Connection
	{
	public:
		volatile8(void)
			: m_object(NULL)
			, m_function(NULL)
		{}
		volatile8(RECEIVER* object, void (RECEIVER::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8))
			: m_object(object)
			, m_function(function)
		{}
		virtual Connection* clone(void)
		{
			return new volatile8<RECEIVER>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new volatile8<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual Receiver* getReceiver(void) const
		{
			return m_object;
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
		const8(void)
			: m_object(NULL)
			, m_function(NULL)
		{}
		const8(RECEIVER* object, void (RECEIVER::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) const)
			: m_object(object)
			, m_function(function)
		{}
		virtual Connection* clone(void)
		{
			return new const8<RECEIVER>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new const8<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual Receiver* getReceiver(void) const
		{
			return m_object;
		}
		virtual void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8)
		{
			(m_object->*m_function)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		}
	private:
		RECEIVER* m_object;
		void (RECEIVER::* m_function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) const;
	}; // class const8
public:
	Transmitter8(void)
		: m_receivers(NULL)
		, m_transmissionIter(NULL)
		, m_isRepeatTransmissionRequired(false)
		, m_isTransmitting(false)
	{ /* empty */}
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
		Connection* destinationIter = m_receivers;
		while (iter)
		{
			iter->getReceiver()->onConnect(this);
			destinationIter = iter->clone();

			if (previous)
			{
				previous->m_next = destinationIter;
			}

			previous = destinationIter
				iter = iter->m_next;
		}
	}
	virtual ~Transmitter8(void)
	{
		disconnectAll();
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
				if (iter->getReceiver() == static_cast<Receiver*>(receiver))
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
				if (iter->getReceiver() == static_cast<Receiver*>(receiver))
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
	void ceaseTransmission(void)
	{
		SYNC(m_mutex);
		disconnectAll();
		m_isTransmitting = false;
		m_transmissionIter = NULL;
		m_receivers = NULL;
	}
	void disconnect(Receiver* receiver)
	{
		if (receiver)
		{
			SYNC(m_mutex);
			Connection* iter(m_receivers);
			Connection* previous(NULL);

			while (iter)
			{
				if (iter->getReceiver() == receiver)				{
					receiver->onDisconnect(this);

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
	void onDisconnect(Receiver* receiver)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);
		Connection* previous(NULL);

		while (iter)
		{
			if (iter->getReceiver() == receiver)
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
	void disconnectAll(void)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);

		while (iter)
		{
			iter->getReceiver()->onDisconnect(this);
			Connection* stale(iter);
			iter = iter->m_next;
			delete stale;
		}

		m_receivers = NULL;	}
	void replicate(const Receiver* receiver, Receiver* new_receiver)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);

		while (iter)
		{
			if (iter->getReceiver() == receiver)
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
private:
	class Connection
	{
	public:
		Connection(void) : m_next(NULL) { /* empty */ };
		virtual ~Connection(void)=0 {};
		virtual Connection* clone(void)=0;
		virtual Connection* duplicate(Receiver* receiver)=0;
		virtual Receiver* getReceiver(void) const=0;
		virtual void transmit(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9)=0;
		Connection* m_next;
	}; // class Connection
	template< class RECEIVER >
	class volatile9
		: public Connection
	{
	public:
		volatile9(void)
			: m_object(NULL)
			, m_function(NULL)
		{}
		volatile9(RECEIVER* object, void (RECEIVER::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9))
			: m_object(object)
			, m_function(function)
		{}
		virtual Connection* clone(void)
		{
			return new volatile9<RECEIVER>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new volatile9<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual Receiver* getReceiver(void) const
		{
			return m_object;
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
		const9(void)
			: m_object(NULL)
			, m_function(NULL)
		{}
		const9(RECEIVER* object, void (RECEIVER::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) const)
			: m_object(object)
			, m_function(function)
		{}
		virtual Connection* clone(void)
		{
			return new const9<RECEIVER>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new const9<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual Receiver* getReceiver(void) const
		{
			return m_object;
		}
		virtual void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9)
		{
			(m_object->*m_function)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		}
	private:
		RECEIVER* m_object;
		void (RECEIVER::* m_function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) const;
	}; // class const9
public:
	Transmitter9(void)
		: m_receivers(NULL)
		, m_transmissionIter(NULL)
		, m_isRepeatTransmissionRequired(false)
		, m_isTransmitting(false)
	{ /* empty */}
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
		Connection* destinationIter = m_receivers;
		while (iter)
		{
			iter->getReceiver()->onConnect(this);
			destinationIter = iter->clone();

			if (previous)
			{
				previous->m_next = destinationIter;
			}

			previous = destinationIter
				iter = iter->m_next;
		}
	}
	virtual ~Transmitter9(void)
	{
		disconnectAll();
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
				if (iter->getReceiver() == static_cast<Receiver*>(receiver))
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
				if (iter->getReceiver() == static_cast<Receiver*>(receiver))
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
	void ceaseTransmission(void)
	{
		SYNC(m_mutex);
		disconnectAll();
		m_isTransmitting = false;
		m_transmissionIter = NULL;
		m_receivers = NULL;
	}
	void disconnect(Receiver* receiver)
	{
		if (receiver)
		{
			SYNC(m_mutex);
			Connection* iter(m_receivers);
			Connection* previous(NULL);

			while (iter)
			{
				if (iter->getReceiver() == receiver)				{
					receiver->onDisconnect(this);

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
	void onDisconnect(Receiver* receiver)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);
		Connection* previous(NULL);

		while (iter)
		{
			if (iter->getReceiver() == receiver)
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
	void disconnectAll(void)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);

		while (iter)
		{
			iter->getReceiver()->onDisconnect(this);
			Connection* stale(iter);
			iter = iter->m_next;
			delete stale;
		}

		m_receivers = NULL;	}
	void replicate(const Receiver* receiver, Receiver* new_receiver)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);

		while (iter)
		{
			if (iter->getReceiver() == receiver)
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
private:
	class Connection
	{
	public:
		Connection(void) : m_next(NULL) { /* empty */ };
		virtual ~Connection(void)=0 {};
		virtual Connection* clone(void)=0;
		virtual Connection* duplicate(Receiver* receiver)=0;
		virtual Receiver* getReceiver(void) const=0;
		virtual void transmit(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10)=0;
		Connection* m_next;
	}; // class Connection
	template< class RECEIVER >
	class volatile10
		: public Connection
	{
	public:
		volatile10(void)
			: m_object(NULL)
			, m_function(NULL)
		{}
		volatile10(RECEIVER* object, void (RECEIVER::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10))
			: m_object(object)
			, m_function(function)
		{}
		virtual Connection* clone(void)
		{
			return new volatile10<RECEIVER>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new volatile10<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual Receiver* getReceiver(void) const
		{
			return m_object;
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
		const10(void)
			: m_object(NULL)
			, m_function(NULL)
		{}
		const10(RECEIVER* object, void (RECEIVER::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) const)
			: m_object(object)
			, m_function(function)
		{}
		virtual Connection* clone(void)
		{
			return new const10<RECEIVER>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new const10<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual Receiver* getReceiver(void) const
		{
			return m_object;
		}
		virtual void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, ARG_10 arg10)
		{
			(m_object->*m_function)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		}
	private:
		RECEIVER* m_object;
		void (RECEIVER::* m_function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) const;
	}; // class const10
public:
	Transmitter10(void)
		: m_receivers(NULL)
		, m_transmissionIter(NULL)
		, m_isRepeatTransmissionRequired(false)
		, m_isTransmitting(false)
	{ /* empty */}
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
		Connection* destinationIter = m_receivers;
		while (iter)
		{
			iter->getReceiver()->onConnect(this);
			destinationIter = iter->clone();

			if (previous)
			{
				previous->m_next = destinationIter;
			}

			previous = destinationIter
				iter = iter->m_next;
		}
	}
	virtual ~Transmitter10(void)
	{
		disconnectAll();
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
				if (iter->getReceiver() == static_cast<Receiver*>(receiver))
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
				if (iter->getReceiver() == static_cast<Receiver*>(receiver))
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
	void ceaseTransmission(void)
	{
		SYNC(m_mutex);
		disconnectAll();
		m_isTransmitting = false;
		m_transmissionIter = NULL;
		m_receivers = NULL;
	}
	void disconnect(Receiver* receiver)
	{
		if (receiver)
		{
			SYNC(m_mutex);
			Connection* iter(m_receivers);
			Connection* previous(NULL);

			while (iter)
			{
				if (iter->getReceiver() == receiver)				{
					receiver->onDisconnect(this);

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
	void onDisconnect(Receiver* receiver)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);
		Connection* previous(NULL);

		while (iter)
		{
			if (iter->getReceiver() == receiver)
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
	void disconnectAll(void)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);

		while (iter)
		{
			iter->getReceiver()->onDisconnect(this);
			Connection* stale(iter);
			iter = iter->m_next;
			delete stale;
		}

		m_receivers = NULL;	}
	void replicate(const Receiver* receiver, Receiver* new_receiver)
	{
		SYNC(m_mutex);
		Connection* iter(m_receivers);

		while (iter)
		{
			if (iter->getReceiver() == receiver)
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