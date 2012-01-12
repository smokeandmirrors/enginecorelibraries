#pragma once
#ifndef SIGNALS_H
#define SIGNALS_H

/**
\file Signals.h
This files implements a typesafe Signal/Slot delegate system.  It owes all of its
inspiration, and much (if not most) of its implementaion to Sarah Thompson
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

The receiver methods should't be considered public at all, they should
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

#include <list>
#include <set>

#include "Synchronization.h"
#include "TemplateArguments.h"

namespace signals
{
class Receiver;

/**
interface for classes to hide the template nature of the all
the different Transmitter classes.  This allows for typesafe useage
for clients, but more generic implementation here.

\todo check this for functions that are uneccessarily virtual

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
	typedef std::set<Transmitter *> sender_set;
	typedef sender_set::const_iterator const_iterator;

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
	{ /* empty */ }

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
	sender_set				m_transmitters;
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
	{ /* empty */ }

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
	sender_set				m_transmitters;
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
		virtual ~Connection(void)=0 {};
		virtual Connection*	clone(void)=0;
		virtual Connection*	duplicate(Receiver* receiver)=0;
		virtual Receiver*	getReceiver(void) const=0;
		virtual void		transmit(void) const=0;
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

		virtual void transmit(void) const
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

		virtual void transmit(void) const
		{
			(m_object->*m_function)();
		}

	private:
		RECEIVER*			m_object;
		void (RECEIVER::*	m_function)(void) const;
	};

public:
	typedef std::list<Connection *>  connections_list;

	Transmitter0(void)
	{ /* empty */ }

	Transmitter0(const Transmitter0& s)
	: Transmitter(s)
	{
		SYNC(m_mutex);
		connections_list::const_iterator iter = s.m_receivers.begin();
		connections_list::const_iterator sentinel = s.m_receivers.end();

		while (iter != sentinel)
		{
			(*iter)->getReceiver()->onConnect(this);
			m_receivers.push_back((*iter)->clone());

			++iter;
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
		m_receivers.erase(m_receivers.begin(), m_receivers.end());
	}

	/** connect to a receiver via a non-const method*/
	template<class RECEIVER>
	void connect(RECEIVER* receiver, void (RECEIVER::* function)(void))
	{
		if (receiver && function)
		{
			SYNC(m_mutex);
			connections_list::const_iterator iter = m_receivers.begin();
			connections_list::const_iterator sentinel = m_receivers.end();

			while (iter != sentinel)
			{
				if ((*iter)->getReceiver() == static_cast<Receiver*>(receiver))
				{
					return;
				}

				++iter;
			}

			m_receivers.push_back(new volatile0<RECEIVER>(receiver, function));
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
			connections_list::const_iterator iter = m_receivers.begin();
			connections_list::const_iterator sentinel = m_receivers.end();

			while (iter != sentinel)
			{
				if ((*iter)->getReceiver() == static_cast<Receiver*>(receiver))
				{
					return;
				}

				++iter;
			}

			m_receivers.push_back(new const0<RECEIVER>(receiver, function));
			receiver->onConnect(this);
		}
	}

	/** disconnect all methods the receiver has registered */
	void disconnect(Receiver* receiver)
	{
		if (receiver)
		{
			SYNC(m_mutex);
			connections_list::iterator iter = m_receivers.begin();
			connections_list::iterator sentinel = m_receivers.end();

			while (iter != sentinel)
			{
				Connection* connection = *iter;

				if (connection->getReceiver() == receiver)
				{
					receiver->onDisconnect(this);
					delete connection;
					m_receivers.erase(iter);
					return;
				}

				++iter;
			}
		}
	}

	/** call each method registered by all receivers */
	void transmit(void) const
	{
		SYNC(m_mutex);
		connections_list copy(m_receivers);
		connections_list::const_iterator iter = copy.begin();
		connections_list::const_iterator sentinel = copy.end();

		while (iter != sentinel)
		{
			(*iter)->transmit();
			++iter;
		}
	}

	/** call each method registered by all receivers */
	inline void operator()(void) const
	{
		transmit();
	}

protected:
	/** called by the disconnection process, removes the receiver from the list */
	void onDisconnect(Receiver* receiver)
	{
		SYNC(m_mutex);
		connections_list::iterator iter = m_receivers.begin();
		connections_list::iterator sentinel = m_receivers.end();

		while (iter != sentinel)
		{
			Connection* connection = *iter;

			if (connection->getReceiver() == receiver)
			{
				delete connection;
				m_receivers.erase(iter);
				return;
			}

			++iter;
		}
	}

	/** disconnects all receivers, but doesn't empty the list */
	void disconnectAll(void)
	{
		SYNC(m_mutex);
		connections_list::const_iterator iter = m_receivers.begin();
		connections_list::const_iterator sentinel = m_receivers.end();

		while (iter != sentinel)
		{
			(*iter)->getReceiver()->onDisconnect(this);
			delete *iter;
			++iter;
		}
	}
	
	/** helps with copy constructors */
	void replicate(const Receiver* receiver, Receiver* new_receiver)
	{
		SYNC(m_mutex);
		connections_list::iterator iter = m_receivers.begin();
		connections_list::iterator sentinel = m_receivers.end();

		while (iter != sentinel)
		{
			if ((*iter)->getReceiver() == receiver)
			{
				m_receivers.push_back((*iter)->duplicate(new_receiver));
				return;
			}

			++iter;
		}
	}

private:
	connections_list				m_receivers;   
	mutable concurrency::Mutex	m_mutex;
};

#define SIGNALS_DECLARE_TRANSMITTER(NUM_ARGS) \
	template < CW_TEMPLATE_ARGS_RETS_0_ARGS_##NUM_ARGS > \
	class Transmitter##NUM_ARGS : public Transmitter \
	{ \
	private: \
		template< CW_TEMPLATE_ARGS_RETS_0_ARGS_##NUM_ARGS > \
		class Connection \
		{ \
		public: \
			virtual ~Connection(void)=0 {}; \
			virtual Connection < CW_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_##NUM_ARGS >* clone(void)=0; \
			virtual Connection< CW_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_##NUM_ARGS >* duplicate(Receiver* receiver)=0; \
			virtual Receiver* getReceiver(void) const=0; \
			virtual void transmit( CW_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_##NUM_ARGS ) const=0; \
		}; \
		template< class RECEIVER, CW_TEMPLATE_ARGS_RETS_0_ARGS_##NUM_ARGS > \
		class volatile##NUM_ARGS \
		: public Connection< CW_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_##NUM_ARGS > \
		{ \
		public: \
			volatile##NUM_ARGS(void) \
			: m_object(NULL) \
			, m_function(NULL) \
			{} \
			volatile##NUM_ARGS(RECEIVER* object, void (RECEIVER::* function)(CW_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_##NUM_ARGS)) \
			: m_object(object) \
			, m_function(function) \
			{} \
			virtual Connection* clone(void) \
			{ \
				return new volatile##NUM_ARGS<RECEIVER, CW_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_##NUM_ARGS>(*this); \
			} \
			virtual Connection* duplicate(Receiver* receiver) \
			{ \
				return new volatile##NUM_ARGS<RECEIVER, CW_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_##NUM_ARGS>(static_cast<RECEIVER*>(receiver), m_function); \
			} \
			virtual Receiver* getReceiver(void) const \
			{ \
				return m_object; \
			} \
			virtual void transmit(CW_DECLARE_FUNCTION_RETS_0_ARGS_##NUM_ARGS) const \
			{ \
				(m_object->*m_function)(CW_CALL_RETS_0_ARGS_##NUM_ARGS); \
			} \
		private: \
			RECEIVER*			m_object; \
			void (RECEIVER::*	m_function)(CW_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_##NUM_ARGS); \
		}; \
		template<class RECEIVER, CW_TEMPLATE_ARGS_RETS_0_ARGS_##NUM_ARGS> \
		class const##NUM_ARGS \
		: public Connection<CW_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_##NUM_ARGS> \
		{ \
		public: \
			const##NUM_ARGS(void) \
			: m_object(NULL) \
			, m_function(NULL) \
			{} \
			const##NUM_ARGS(RECEIVER* object, void (RECEIVER::* function)(CW_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_##NUM_ARGS) const) \
			: m_object(object) \
			, m_function(function) \
			{} \
			virtual Connection* clone(void) \
			{ \
				return new const##NUM_ARGS<RECEIVER, CW_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_##NUM_ARGS>(*this); \
			} \
			virtual Connection* duplicate(Receiver* receiver) \
			{ \
				return new const##NUM_ARGS<RECEIVER, CW_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_##NUM_ARGS>(static_cast<RECEIVER*>(receiver), m_function); \
			} \
			virtual Receiver* getReceiver(void) const \
			{ \
				return m_object; \
			} \
			virtual void transmit(CW_DECLARE_FUNCTION_RETS_0_ARGS_##NUM_ARGS) const \
			{ \
				(m_object->*m_function)(CW_CALL_RETS_0_ARGS_##NUM_ARGS); \
			} \
		private: \
			RECEIVER*			m_object; \
			void (RECEIVER::*	m_function)(CW_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_##NUM_ARGS) const; \
		}; \
	public: \
		typedef std::list<Connection<CW_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_##NUM_ARGS> *> connections_list; \
		Transmitter##NUM_ARGS(void) \
		{} \
		Transmitter##NUM_ARGS(const Transmitter##NUM_ARGS& s) \
		: Transmitter(s) \
		{ \
			SYNC(m_mutex); \
			connections_list::const_iterator iter = s.m_receivers.begin(); \
			connections_list::const_iterator sentinel = s.m_receivers.end(); \
			while (iter != sentinel) \
			{ \
				(*iter)->getReceiver()->onConnect(this); \
				m_receivers.push_back((*iter)->clone()); \
				++iter; \
			} \
		} \
		virtual ~Transmitter##NUM_ARGS(void) \
		{ \
			disconnectAll(); \
		} \
		template<class RECEIVER> \
		void connect(RECEIVER* receiver, void (RECEIVER::* function)(CW_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_##NUM_ARGS)) \
		{ \
			if (receiver && function) \
			{ \
				SYNC(m_mutex); \
				connections_list::const_iterator iter = m_receivers.begin(); \
				connections_list::const_iterator sentinel = m_receivers.end(); \
				while (iter != sentinel) \
				{ \
					if ((*iter)->getReceiver() == static_cast<Receiver*>(receiver)) \
					{ \
						return; \
					} \
					++iter; \
				} \
				m_receivers.push_back(new volatile##NUM_ARGS<RECEIVER, CW_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_##NUM_ARGS>(receiver, function)); \
				receiver->onConnect(this); \
			} \
		} \
		template<class RECEIVER> \
		void connect(RECEIVER* receiver, void (RECEIVER::* function)(CW_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_##NUM_ARGS) const) \
		{ \
			if (receiver && function) \
			{ \
				SYNC(m_mutex); \
				connections_list::const_iterator iter = m_receivers.begin(); \
				connections_list::const_iterator sentinel = m_receivers.end(); \
				while (iter != sentinel) \
				{ \
					if ((*iter)->getReceiver() == static_cast<Receiver*>(receiver)) \
					{ \
						return; \
					} \
					++iter; \
				} \
				m_receivers.push_back(new const1<RECEIVER, CW_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_##NUM_ARGS>(receiver, function)); \
				receiver->onConnect(this); \
			} \
		} \
		void ceaseTransmission(void) \
		{ \
			SYNC(m_mutex); \
			disconnectAll(); \
			m_receivers.erase(m_receivers.begin(), m_receivers.end()); \
		} \
		void disconnect(Receiver* receiver) \
		{ \
			SYNC(m_mutex); \
			connections_list::iterator iter = m_receivers.begin(); \
			connections_list::iterator sentinel = m_receivers.end(); \
			while (iter != sentinel) \
			{ \
				Connection<CW_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_##NUM_ARGS>* connection = *iter; \
				if (connection->getReceiver() == receiver) \
				{ \
					receiver->onDisconnect(this); \
					delete connection; \
					m_receivers.erase(iter); \
					return; \
				} \
				++iter; \
			} \
		} \
		void transmit(CW_DECLARE_FUNCTION_RETS_0_ARGS_##NUM_ARGS) const \
		{ \
			SYNC(m_mutex); \
			connections_list copy(m_receivers); \
			connections_list::const_iterator iter = copy.begin(); \
			connections_list::const_iterator sentinel = copy.end(); \
			while (iter != sentinel) \
			{ \
				(*iter)->transmit(CW_CALL_RETS_0_ARGS_##NUM_ARGS); \
				++iter; \
			} \
		} \
		inline void operator()(CW_DECLARE_FUNCTION_RETS_0_ARGS_##NUM_ARGS) const \
		{ \
			transmit(CW_CALL_RETS_0_ARGS_##NUM_ARGS); \
		} \
	protected: \
		void onDisconnect(Receiver* receiver) \
		{ \
			SYNC(m_mutex); \
			connections_list::iterator iter = m_receivers.begin(); \
			connections_list::iterator sentinel = m_receivers.end(); \
			while (iter != sentinel) \
			{ \
				Connection<CW_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_##NUM_ARGS>* connection = *iter; \
				if (connection->getReceiver() == receiver) \
				{ \
					delete connection; \
					m_receivers.erase(iter); \
					return; \
				} \
				++iter; \
			} \
		} \
		void disconnectAll(void) \
		{ \
			SYNC(m_mutex); \
			connections_list::const_iterator iter = m_receivers.begin(); \
			connections_list::const_iterator sentinel = m_receivers.end(); \
			while (iter != sentinel) \
			{ \
				(*iter)->getReceiver()->onDisconnect(this); \
				delete *iter; \
				++iter; \
			} \
		} \
		void replicate(const Receiver* receiver, Receiver* new_receiver) \
		{ \
			SYNC(m_mutex); \
			connections_list::iterator iter = m_receivers.begin(); \
			connections_list::iterator sentinel = m_receivers.end(); \
			while (iter != sentinel) \
			{ \
				if ((*iter)->getReceiver() == receiver) \
				{ \
					m_receivers.push_back((*iter)->duplicate(new_receiver)); \
					return; \
				} \
				++iter; \
			} \
		} \
	private: \
		connections_list				m_receivers; \
		DECLARE_MUTABLE_MUTEX(m_mutex) \
	};

template < CW_TEMPLATE_ARGS_RETS_0_ARGS_1 > 
class Transmitter1 : public Transmitter 
{ 
private: 
	template< CW_TEMPLATE_ARGS_RETS_0_ARGS_1 > 
	class Connection 
	{ 
	public: 
		virtual ~Connection(void)=0 {}; 
		virtual Connection < CW_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_1 >* clone(void)=0; 
		virtual Connection< CW_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_1 >* duplicate(Receiver* receiver)=0; 
		virtual Receiver* getReceiver(void) const=0; 
		virtual void transmit( CW_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_1 ) const=0; 
	}; 
	template< class RECEIVER, CW_TEMPLATE_ARGS_RETS_0_ARGS_1 > 
	class volatile1 
		: public Connection< CW_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_1 > 
	{ 
	public: 
		volatile1(void) 
			: m_object(NULL) 
			, m_function(NULL) 
		{} 
		volatile1(RECEIVER* object, void (RECEIVER::* function)(CW_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_1)) 
			: m_object(object) 
			, m_function(function) 
		{} 
		virtual Connection* clone(void) 
		{ 
			return new volatile1<RECEIVER, CW_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_1>(*this); 
		} 
		virtual Connection* duplicate(Receiver* receiver) 
		{ 
			return new volatile1<RECEIVER, CW_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_1>(static_cast<RECEIVER*>(receiver), m_function); 
		} 
		virtual Receiver* getReceiver(void) const 
		{ 
			return m_object; 
		} 
		virtual void transmit(CW_DECLARE_FUNCTION_RETS_0_ARGS_1) const 
		{ 
			(m_object->*m_function)(CW_CALL_RETS_0_ARGS_1); 
		} 
	private: 
		RECEIVER*			m_object; 
		void (RECEIVER::*	m_function)(CW_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_1); 
	}; 
	template<class RECEIVER, CW_TEMPLATE_ARGS_RETS_0_ARGS_1> 
	class const1 
		: public Connection<CW_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_1> 
	{ 
	public: 
		const1(void) 
			: m_object(NULL) 
			, m_function(NULL) 
		{} 
		const1(RECEIVER* object, void (RECEIVER::* function)(CW_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_1) const) 
			: m_object(object) 
			, m_function(function) 
		{} 
		virtual Connection* clone(void) 
		{ 
			return new const1<RECEIVER, CW_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_1>(*this); 
		} 
		virtual Connection* duplicate(Receiver* receiver) 
		{ 
			return new const1<RECEIVER, CW_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_1>(static_cast<RECEIVER*>(receiver), m_function); 
		} 
		virtual Receiver* getReceiver(void) const 
		{ 
			return m_object; 
		} 
		virtual void transmit(CW_DECLARE_FUNCTION_RETS_0_ARGS_1) const 
		{ 
			(m_object->*m_function)(CW_CALL_RETS_0_ARGS_1); 
		} 
	private: 
		RECEIVER*			m_object; 
		void (RECEIVER::*	m_function)(CW_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_1) const; 
	}; 
public: 
	typedef std::list<Connection<CW_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_1> *> connections_list; 
	Transmitter1(void) 
	{} 
	Transmitter1(const Transmitter1& s) 
		: Transmitter(s) 
	{ 
		SYNC(m_mutex); 
		connections_list::const_iterator iter = s.m_receivers.begin(); 
		connections_list::const_iterator sentinel = s.m_receivers.end(); 
		while (iter != sentinel) 
		{ 
			(*iter)->getReceiver()->onConnect(this); 
			m_receivers.push_back((*iter)->clone()); 
			++iter; 
		} 
	} 
	virtual ~Transmitter1(void) 
	{ 
		disconnectAll(); 
	} 
	template<class RECEIVER> 
	void connect(RECEIVER* receiver, void (RECEIVER::* function)(CW_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_1)) 
	{ 
		if (receiver && function) 
		{ 
			SYNC(m_mutex); 
			connections_list::const_iterator iter = m_receivers.begin(); 
			connections_list::const_iterator sentinel = m_receivers.end(); 
			while (iter != sentinel) 
			{ 
				if ((*iter)->getReceiver() == static_cast<Receiver*>(receiver)) 
				{ 
					return; 
				} 
				++iter; 
			} 
			m_receivers.push_back(new volatile1<RECEIVER, CW_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_1>(receiver, function)); 
			receiver->onConnect(this); 
		} 
	} 
	template<class RECEIVER> 
	void connect(RECEIVER* receiver, void (RECEIVER::* function)(CW_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_1) const) 
	{ 
		if (receiver && function) 
		{ 
			SYNC(m_mutex); 
			connections_list::const_iterator iter = m_receivers.begin(); 
			connections_list::const_iterator sentinel = m_receivers.end(); 
			while (iter != sentinel) 
			{ 
				if ((*iter)->getReceiver() == static_cast<Receiver*>(receiver)) 
				{ 
					return; 
				} 
				++iter; 
			} 
			m_receivers.push_back(new const1<RECEIVER, CW_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_1>(receiver, function)); 
			receiver->onConnect(this); 
		} 
	} 
	void ceaseTransmission(void) 
	{ 
		SYNC(m_mutex); 
		disconnectAll(); 
		m_receivers.erase(m_receivers.begin(), m_receivers.end()); 
	} 
	void disconnect(Receiver* receiver) 
	{ 
		SYNC(m_mutex); 
		connections_list::iterator iter = m_receivers.begin(); 
		connections_list::iterator sentinel = m_receivers.end(); 
		while (iter != sentinel) 
		{ 
			Connection<CW_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_1>* connection = *iter; 
			if (connection->getReceiver() == receiver) 
			{ 
				receiver->onDisconnect(this); 
				delete connection; 
				m_receivers.erase(iter); 
				return; 
			} 
			++iter; 
		} 
	} 
	void transmit(CW_DECLARE_FUNCTION_RETS_0_ARGS_1) const 
	{ 
		SYNC(m_mutex); 
		connections_list copy(m_receivers); 
		connections_list::const_iterator iter = copy.begin(); 
		connections_list::const_iterator sentinel = copy.end(); 
		while (iter != sentinel) 
		{ 
			(*iter)->transmit(CW_CALL_RETS_0_ARGS_1); 
			++iter; 
		} 
	} 
	inline void operator()(CW_DECLARE_FUNCTION_RETS_0_ARGS_1) const 
	{ 
		transmit(CW_CALL_RETS_0_ARGS_1); 
	} 
protected: 
	void onDisconnect(Receiver* receiver) 
	{ 
		SYNC(m_mutex); 
		connections_list::iterator iter = m_receivers.begin(); 
		connections_list::iterator sentinel = m_receivers.end(); 
		while (iter != sentinel) 
		{ 
			Connection<CW_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_1>* connection = *iter; 
			if (connection->getReceiver() == receiver) 
			{ 
				delete connection; 
				m_receivers.erase(iter); 
				return; 
			} 
			++iter; 
		} 
	} 
	void disconnectAll(void) 
	{ 
		SYNC(m_mutex); 
		connections_list::const_iterator iter = m_receivers.begin(); 
		connections_list::const_iterator sentinel = m_receivers.end(); 
		while (iter != sentinel) 
		{ 
			(*iter)->getReceiver()->onDisconnect(this); 
			delete *iter; 
			++iter; 
		} 
	} 
	void replicate(const Receiver* receiver, Receiver* new_receiver) 
	{ 
		SYNC(m_mutex); 
		connections_list::iterator iter = m_receivers.begin(); 
		connections_list::iterator sentinel = m_receivers.end(); 
		while (iter != sentinel) 
		{ 
			if ((*iter)->getReceiver() == receiver) 
			{ 
				m_receivers.push_back((*iter)->duplicate(new_receiver)); 
				return; 
			} 
			++iter; 
		} 
	} 
private: 
	connections_list				m_receivers; 
	DECLARE_MUTABLE_MUTEX(m_mutex) 
};


// SIGNALS_DECLARE_TRANSMITTER(1);
SIGNALS_DECLARE_TRANSMITTER(2);
SIGNALS_DECLARE_TRANSMITTER(3);
SIGNALS_DECLARE_TRANSMITTER(4);
SIGNALS_DECLARE_TRANSMITTER(5);

}

#endif//SIGNALS_H