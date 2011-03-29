#pragma once
#ifndef SIGNALS_H
#define SIGNALS_H

#include <set>
#include <vector>

#include "Synchronization.h"
#include "TemplateArguments.h"

/**
\todo fix the memory leak of the connection objects
\warning THERE IS A MEMORY LEAK HERE
*/

namespace signals
{
class Receiver;

class Transmitter
{
public:
	friend class Receiver;
	friend class ReceiverBase;
	friend class ReceiverMember;

protected:
	virtual void onDisconnect(Receiver* receiver)=0;
	virtual void replicate(const Receiver* receiver, Receiver* new_receiver)=0;
};

class Receiver
{
public:
	friend class Transmitter;
	friend class TransmitterGeneric;
	friend class Transmitter0;
	friend class Transmitter1;

	virtual ~Receiver(void)=0 {}
	virtual void disconnect(void)=0;

protected:
	typedef std::set<Transmitter *> sender_set;
	typedef sender_set::const_iterator const_iterator;

	virtual void onConnect(Transmitter* sender)=0;
	virtual void onDisconnect(Transmitter* sender)=0;
}; // 

class ReceiverBase
: public Receiver
{
	friend class Transmitter;
	friend class TransmitterGeneric;
	friend class Transmitter0;
	friend class Transmitter1;

public:
	ReceiverBase(void)
	{
		/* empty */
	}

	ReceiverBase(const ReceiverBase& receiver)
	{
		synchronize(m_mutex);
		const_iterator iter = receiver.m_senders.begin();
		const_iterator sentinel = receiver.m_senders.end();

		while (iter != sentinel)
		{
			(*iter)->replicate(&receiver, this);
			m_senders.insert(*iter);
			++iter;
		}
	} 
	
	virtual ~ReceiverBase(void)
	{
		disconnectAll();
	}

	void disconnect(void)
	{
		synchronize(m_mutex);
		disconnectAll();
		m_senders.erase(m_senders.begin(), m_senders.end());
	}

protected:
	void disconnectAll(void)
	{
		synchronize(m_mutex);
		const_iterator iter = m_senders.begin();
		const_iterator sentinel = m_senders.end();

		while (iter != sentinel)
		{
			(*iter)->onDisconnect(this);
			++iter;
		}
	}
	
	void onConnect(Transmitter* sender)
	{
		synchronize(m_mutex);
		m_senders.insert(sender);
	}

	void onDisconnect(Transmitter* sender)
	{
		synchronize(m_mutex);
		m_senders.erase(sender);
	}

private:
	multithreading::Mutex	m_mutex;
	sender_set				m_senders;
};


class ReceiverMember
	: public Receiver
{
	friend class Transmitter;
	friend class Transmitter0;

public:
	ReceiverMember(void)
	: m_receiver(NULL)
	{
		/* empty */
	}

	ReceiverMember(const ReceiverMember& receiver)
	: m_receiver(NULL)
	{
		synchronize(m_mutex);
		const_iterator iter = receiver.m_senders.begin();
		const_iterator sentinel = receiver.m_senders.end();

		while (iter != sentinel)
		{
			(*iter)->replicate(&receiver, this);
			m_senders.insert(*iter);
			++iter;
		}
	} 

	virtual ~ReceiverMember(void)
	{
		disconnectAll();
	}

	void disconnect(void)
	{
		synchronize(m_mutex);
		disconnectAll();
		m_senders.erase(m_senders.begin(), m_senders.end());
	}

	void onConnect(Transmitter* sender)
	{
		synchronize(m_mutex);
		m_senders.insert(sender);
	}

	void onDisconnect(Transmitter* sender)
	{
		synchronize(m_mutex);
		m_senders.erase(sender);
	}

	void setReceiver(Receiver* receiver)
	{
		m_receiver = receiver;
	}

protected:
	void disconnectAll(void)
	{
		synchronize(m_mutex);
		const_iterator iter = m_senders.begin();
		const_iterator sentinel = m_senders.end();

		while (iter != sentinel)
		{
			(*iter)->onDisconnect(m_receiver);
			++iter;
		}
	}

private:
	multithreading::Mutex	m_mutex;
	Receiver*				m_receiver;
	sender_set				m_senders;
};

class TransmitterGeneric : public Transmitter
{
private:
	class ConnectionGeneric
	{
	public:
		virtual ~ConnectionGeneric(void)=0 {};
		virtual ConnectionGeneric*	clone(void)=0;
		virtual ConnectionGeneric*	duplicate(Receiver* receiver)=0;
		virtual Receiver*		getReceiver(void) const=0;
		virtual void			send(void)=0;
	};

	template<class RECEIVER>
	class volatileGeneric : public ConnectionGeneric
	{
	public:
		volatileGeneric(void)
		: m_object(NULL)
		, m_function(NULL)
		{
			/* empty */
		}

		volatileGeneric(RECEIVER* object, void (RECEIVER::* function)(void))
		: m_object(object)
		, m_function(function)
		{
			/* empty */
		}

		virtual ConnectionGeneric* clone(void)
		{
			return new volatileGeneric<RECEIVER>(*this);
		}

		virtual ConnectionGeneric* duplicate(Receiver* receiver)
		{
			return new volatileGeneric<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}

		virtual Receiver* getReceiver(void) const
		{
			return m_object;
		}

		virtual void send(void)
		{
			(m_object->*m_function)();
		}

	private:
		RECEIVER*			m_object;
		void (RECEIVER::*	m_function)(void);
	};

	template<class RECEIVER>
	class constGeneric : public ConnectionGeneric
	{
	public:
		constGeneric(void)
		: m_object(NULL)
		, m_function(NULL)
		{
			/* empty */
		}

		constGeneric(RECEIVER* object, void (RECEIVER::* function)(void) const)
		: m_object(object)
		, m_function(function)
		{
			/* empty */
		}

		virtual ConnectionGeneric* clone(void)
		{
			return new constGeneric<RECEIVER>(*this);
		}

		virtual ConnectionGeneric* duplicate(Receiver* receiver)
		{
			return new constGeneric<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}

		virtual Receiver* getReceiver(void) const
		{
			return m_object;
		}

		virtual void send(void)
		{
			(m_object->*m_function)();
		}

	private:
		RECEIVER*			m_object;
		void (RECEIVER::*	m_function)(void) const;
	};

public:
	typedef std::list<ConnectionGeneric *>  connections_list;

	TransmitterGeneric(void)
	{
		/* empty */
	}

	TransmitterGeneric(const TransmitterGeneric& s)
	: Transmitter(s)
	{
		synchronize(m_mutex);
		connections_list::const_iterator iter = s.m_receivers.begin();
		connections_list::const_iterator sentinel = s.m_receivers.end();

		while (iter != sentinel)
		{
			(*iter)->getReceiver()->onConnect(this);
			m_receivers.push_back((*iter)->clone());

			++iter;
		}
	}

	~TransmitterGeneric(void)
	{
		disconnectAll();
	}

	template<class RECEIVER>
	void connect(RECEIVER* receiver, void (RECEIVER::* function)(void))
	{
		synchronize(m_mutex);
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

		m_receivers.push_back(new volatileGeneric<RECEIVER>(receiver, function));
		receiver->onConnect(this);
	}

	template<class RECEIVER>
	void connect(RECEIVER* receiver, void (RECEIVER::* function)(void) const)
	{
		synchronize(m_mutex);
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

		m_receivers.push_back(new constGeneric<RECEIVER>(receiver, function));
		receiver->onConnect(this);
	}

	void disconnect(void)
	{
		synchronize(m_mutex);
		disconnectAll();
		m_receivers.erase(m_receivers.begin(), m_receivers.end());
	}

	void disconnect(Receiver* receiver)
	{
		synchronize(m_mutex);
		connections_list::iterator iter = m_receivers.begin();
		connections_list::iterator sentinel = m_receivers.end();

		while (iter != sentinel)
		{
			ConnectionGeneric* connection = *iter;

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

	void replicate(const Receiver* receiver, Receiver* new_receiver)
	{
		synchronize(m_mutex);
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

	void send(void)
	{
		synchronize(m_mutex);
		connections_list copy(m_receivers);
		connections_list::const_iterator iter = copy.begin();
		connections_list::const_iterator sentinel = copy.end();

		while (iter != sentinel)
		{
			(*iter)->send();
			++iter;
		}
	}

	void operator()(void)
	{
		send();
	}

protected:
	void disconnectAll(void)
	{
		synchronize(m_mutex);
		connections_list::const_iterator iter = m_receivers.begin();
		connections_list::const_iterator sentinel = m_receivers.end();

		while (iter != sentinel)
		{
			(*iter)->getReceiver()->onDisconnect(this);
			delete *iter;
			++iter;
		}
	}

	void onDisconnect(Receiver* receiver)
	{
		synchronize(m_mutex);
		connections_list::iterator iter = m_receivers.begin();
		connections_list::iterator sentinel = m_receivers.end();

		while (iter != sentinel)
		{
			ConnectionGeneric* connection = *iter;

			if (connection->getReceiver() == receiver)
			{
				delete connection;
				m_receivers.erase(iter);
				return;
			}

			++iter;
		}
	}

private:
	connections_list		m_receivers;   
	multithreading::Mutex	m_mutex;
};

class Transmitter0 : public Transmitter
{
private:
	class Connection0
	{
	public:
		virtual ~Connection0(void)=0 {};
		virtual Connection0*	clone(void)=0;
		virtual Connection0*	duplicate(Receiver* receiver)=0;
		virtual Receiver*		getReceiver(void) const=0;
		virtual void			send(void)=0;
	};

	template<class RECEIVER>
	class volatile0 : public Connection0
	{
	public:
		volatile0(void)
			: m_object(NULL)
			, m_function(NULL)
		{
			/* empty */
		}

		volatile0(RECEIVER* object, void (RECEIVER::* function)(void))
			: m_object(object)
			, m_function(function)
		{
			/* empty */
		}

		virtual Connection0* clone(void)
		{
			return new volatile0<RECEIVER>(*this);
		}

		virtual Connection0* duplicate(Receiver* receiver)
		{
			return new volatile0<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}

		virtual Receiver* getReceiver(void) const
		{
			return m_object;
		}

		virtual void send(void)
		{
			(m_object->*m_function)();
		}

	private:
		RECEIVER*			m_object;
		void (RECEIVER::*	m_function)(void);
	};

	template<class RECEIVER>
	class const0 : public Connection0
	{
	public:
		const0(void)
			: m_object(NULL)
			, m_function(NULL)
		{
			/* empty */
		}

		const0(RECEIVER* object, void (RECEIVER::* function)(void) const)
			: m_object(object)
			, m_function(function)
		{
			/* empty */
		}

		virtual Connection0* clone(void)
		{
			return new const0<RECEIVER>(*this);
		}

		virtual Connection0* duplicate(Receiver* receiver)
		{
			return new const0<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}

		virtual Receiver* getReceiver(void) const
		{
			return m_object;
		}

		virtual void send(void)
		{
			(m_object->*m_function)();
		}

	private:
		RECEIVER*			m_object;
		void (RECEIVER::*	m_function)(void) const;
	};

public:
	typedef std::list<Connection0 *>  connections_list;

	Transmitter0(void)
	{
		/* empty */
	}

	Transmitter0(const Transmitter0& s)
		: Transmitter(s)
	{
		synchronize(m_mutex);
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

	template<class RECEIVER>
	void connect(RECEIVER* receiver, void (RECEIVER::* function)(void))
	{
		synchronize(m_mutex);
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

	template<class RECEIVER>
	void connect(RECEIVER* receiver, void (RECEIVER::* function)(void) const)
	{
		synchronize(m_mutex);
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

	void disconnect(void)
	{
		synchronize(m_mutex);
		disconnectAll();
		m_receivers.erase(m_receivers.begin(), m_receivers.end());
	}

	void disconnect(Receiver* receiver)
	{
		synchronize(m_mutex);
		connections_list::iterator iter = m_receivers.begin();
		connections_list::iterator sentinel = m_receivers.end();

		while (iter != sentinel)
		{
			Connection0* connection = *iter;

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

	void replicate(const Receiver* receiver, Receiver* new_receiver)
	{
		synchronize(m_mutex);
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

	void send(void)
	{
		synchronize(m_mutex);
		connections_list copy(m_receivers);
		connections_list::const_iterator iter = copy.begin();
		connections_list::const_iterator sentinel = copy.end();

		while (iter != sentinel)
		{
			(*iter)->send();
			++iter;
		}
	}

	void operator()(void)
	{
		send();
	}

protected:
	void disconnectAll(void)
	{
		synchronize(m_mutex);
		connections_list::const_iterator iter = m_receivers.begin();
		connections_list::const_iterator sentinel = m_receivers.end();

		while (iter != sentinel)
		{
			(*iter)->getReceiver()->onDisconnect(this);
			delete *iter;
			++iter;
		}
	}

	void onDisconnect(Receiver* receiver)
	{
		synchronize(m_mutex);
		connections_list::iterator iter = m_receivers.begin();
		connections_list::iterator sentinel = m_receivers.end();

		while (iter != sentinel)
		{
			Connection0* connection = *iter;

			if (connection->getReceiver() == receiver)
			{
				delete connection;
				m_receivers.erase(iter);
				return;
			}

			++iter;
		}
	}

private:
	connections_list		m_receivers;   
	multithreading::Mutex	m_mutex;
};

class Transmitter1 : public Transmitter
{
private:
	class Connection1
	{
	public:
		virtual ~Connection1(void)=0 {};
		virtual Connection1*	clone(void)=0;
		virtual Connection1*	duplicate(Receiver* receiver)=0;
		virtual Receiver*		getReceiver(void) const=0;
		virtual void			send(void)=0;
	};

	template<class RECEIVER>
	class volatile1 : public Connection1
	{
	public:
		volatile1(void)
			: m_object(NULL)
			, m_function(NULL)
		{
			/* empty */
		}

		volatile1(RECEIVER* object, void (RECEIVER::* function)(void))
			: m_object(object)
			, m_function(function)
		{
			/* empty */
		}

		virtual Connection1* clone(void)
		{
			return new volatile1<RECEIVER>(*this);
		}

		virtual Connection1* duplicate(Receiver* receiver)
		{
			return new volatile1<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}

		virtual Receiver* getReceiver(void) const
		{
			return m_object;
		}

		virtual void send(void)
		{
			(m_object->*m_function)();
		}

	private:
		RECEIVER*			m_object;
		void (RECEIVER::*	m_function)(void);
	};

	template<class RECEIVER>
	class const1 : public Connection1
	{
	public:
		const1(void)
			: m_object(NULL)
			, m_function(NULL)
		{
			/* empty */
		}

		const1(RECEIVER* object, void (RECEIVER::* function)(void) const)
			: m_object(object)
			, m_function(function)
		{
			/* empty */
		}

		virtual Connection1* clone(void)
		{
			return new const1<RECEIVER>(*this);
		}

		virtual Connection1* duplicate(Receiver* receiver)
		{
			return new const1<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
		}

		virtual Receiver* getReceiver(void) const
		{
			return m_object;
		}

		virtual void send(void)
		{
			(m_object->*m_function)();
		}

	private:
		RECEIVER*			m_object;
		void (RECEIVER::*	m_function)(void) const;
	};

public:
	typedef std::list<Connection1 *>  connections_list;

	Transmitter1(void)
	{
		/* empty */
	}

	Transmitter1(const Transmitter1& s)
		: Transmitter(s)
	{
		synchronize(m_mutex);
		connections_list::const_iterator iter = s.m_receivers.begin();
		connections_list::const_iterator sentinel = s.m_receivers.end();

		while (iter != sentinel)
		{
			(*iter)->getReceiver()->onConnect(this);
			m_receivers.push_back((*iter)->clone());

			++iter;
		}
	}

	~Transmitter1(void)
	{
		disconnectAll();
	}

	template<class RECEIVER>
	void connect(RECEIVER* receiver, void (RECEIVER::* function)(void))
	{
		synchronize(m_mutex);
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

		m_receivers.push_back(new volatile1<RECEIVER>(receiver, function));
		receiver->onConnect(this);
	}

	template<class RECEIVER>
	void connect(RECEIVER* receiver, void (RECEIVER::* function)(void) const)
	{
		synchronize(m_mutex);
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

		m_receivers.push_back(new const1<RECEIVER>(receiver, function));
		receiver->onConnect(this);
	}

	void disconnect(void)
	{
		synchronize(m_mutex);
		disconnectAll();
		m_receivers.erase(m_receivers.begin(), m_receivers.end());
	}

	void disconnect(Receiver* receiver)
	{
		synchronize(m_mutex);
		connections_list::iterator iter = m_receivers.begin();
		connections_list::iterator sentinel = m_receivers.end();

		while (iter != sentinel)
		{
			Connection1* connection = *iter;

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

	void replicate(const Receiver* receiver, Receiver* new_receiver)
	{
		synchronize(m_mutex);
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

	void send(void)
	{
		synchronize(m_mutex);
		connections_list copy(m_receivers);
		connections_list::const_iterator iter = copy.begin();
		connections_list::const_iterator sentinel = copy.end();

		while (iter != sentinel)
		{
			(*iter)->send();
			++iter;
		}
	}

	void operator()(void)
	{
		send();
	}

protected:
	void disconnectAll(void)
	{
		synchronize(m_mutex);
		connections_list::const_iterator iter = m_receivers.begin();
		connections_list::const_iterator sentinel = m_receivers.end();

		while (iter != sentinel)
		{
			(*iter)->getReceiver()->onDisconnect(this);
			delete *iter;
			++iter;
		}
	}

	void onDisconnect(Receiver* receiver)
	{
		synchronize(m_mutex);
		connections_list::iterator iter = m_receivers.begin();
		connections_list::iterator sentinel = m_receivers.end();

		while (iter != sentinel)
		{
			Connection1* connection = *iter;

			if (connection->getReceiver() == receiver)
			{
				delete connection;
				m_receivers.erase(iter);
				return;
			}

			++iter;
		}
	}

private:
	connections_list		m_receivers;   
	multithreading::Mutex	m_mutex;
};

}
#endif//SIGNALS_H