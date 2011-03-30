#pragma once
#ifndef SIGNALS_H
#define SIGNALS_H

#include <set>
#include <vector>

#include "Synchronization.h"
#include "TemplateArguments.h"

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

#define DECLARE_TRANSMITTER_FRIEND(NUM_ARGS) \
	template < CW_TEMPLATE_ARGS_RETS_0_ARGS_##NUM_ARGS > friend class Transmitter##NUM_ARGS;

#define DECLARE_TRANSMITTER_FRIENDS \
	DECLARE_TRANSMITTER_FRIEND(1) \
	DECLARE_TRANSMITTER_FRIEND(2) \
	DECLARE_TRANSMITTER_FRIEND(3) \
	DECLARE_TRANSMITTER_FRIEND(4) \
	DECLARE_TRANSMITTER_FRIEND(5) \

class Receiver
{
public:
	friend class Transmitter;
	friend class Transmitter0;
	DECLARE_TRANSMITTER_FRIENDS 

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
	friend class Transmitter0;
	DECLARE_TRANSMITTER_FRIENDS 

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
	template<typename ARG_1> friend class Transmitter1;

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

class Transmitter0 
: public Transmitter
{
private:
	class Connection
	{
	public:
		virtual ~Connection(void)=0 {};
		virtual Connection*	clone(void)=0;
		virtual Connection*	duplicate(Receiver* receiver)=0;
		virtual Receiver*	getReceiver(void) const=0;
		virtual void		send(void) const=0;
	};
	
	template<class RECEIVER>
	class volatile0 : public Connection
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

		virtual void send(void) const
		{
			(m_object->*m_function)();
		}

	private:
		RECEIVER*			m_object;
		void (RECEIVER::*	m_function)(void);
	};

	template<class RECEIVER>
	class const0 : public Connection
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

		virtual void send(void) const
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

	void send(void) const
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

	inline void operator()(void) const
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

private:
	connections_list				m_receivers;   
	mutable multithreading::Mutex	m_mutex;
};

/*
template<typename ARG_1>
class Transmitter1 
: public Transmitter
{
private:
	template<typename ARG_1>
	class Connection
	{
	public:
		virtual ~Connection(void)=0 {};
		virtual Connection<ARG_1>*	clone(void)=0;
		virtual Connection<ARG_1>*	duplicate(Receiver* receiver)=0;
		virtual Receiver*			getReceiver(void) const=0;
		virtual void				send(ARG_1) const=0;
	};	
	
	template<class RECEIVER, typename ARG_1>
	class volatile1 
	: public Connection<ARG_1>
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
			return new volatile1<RECEIVER, ARG_1>(*this);
		}

		virtual Connection* duplicate(Receiver* receiver)
		{
			return new volatile1<RECEIVER, ARG_1>(static_cast<RECEIVER*>(receiver), m_function);
		}

		virtual Receiver* getReceiver(void) const
		{
			return m_object;
		}

		virtual void send(ARG_1 arg1) const
		{
			(m_object->*m_function)(arg1);
		}

	private:
		RECEIVER*			m_object;
		void (RECEIVER::*	m_function)(ARG_1);
	};

	template<class RECEIVER, typename ARG_1>
	class const1 
	: public Connection<ARG_1>
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
			return new volatile1<RECEIVER, ARG_1>(*this);
		}

		virtual Connection* duplicate(Receiver* receiver)
		{
			return new volatile1<RECEIVER, ARG_1>(static_cast<RECEIVER*>(receiver), m_function);
		}

		virtual Receiver* getReceiver(void) const
		{
			return m_object;
		}

		virtual void send(ARG_1 arg1) const
		{
			(m_object->*m_function)(arg1);
		}

	private:
		RECEIVER*			m_object;
		void (RECEIVER::*	m_function)(ARG_1) const;
	};

public:
	typedef std::list<Connection<ARG_1> *>  connections_list;

	Transmitter1(void)
	{}

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
	void connect(RECEIVER* receiver, void (RECEIVER::* function)(ARG_1))
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

		m_receivers.push_back(new volatile1<RECEIVER, ARG_1>(receiver, function));
		receiver->onConnect(this);
	}

	template<class RECEIVER>
	void connect(RECEIVER* receiver, void (RECEIVER::* function)(ARG_1) const)
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

		m_receivers.push_back(new const1<RECEIVER, ARG_1>(receiver, function));
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
			Connection<ARG_1>* connection = *iter;

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

	void send(ARG_1 arg1) const
	{
		synchronize(m_mutex);
		connections_list copy(m_receivers);
		connections_list::const_iterator iter = copy.begin();
		connections_list::const_iterator sentinel = copy.end();

		while (iter != sentinel)
		{
			(*iter)->send(arg1);
			++iter;
		}
	}

	inline void operator()(ARG_1 arg1) const
	{
		send(arg1);
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
			Connection<ARG_1>* connection = *iter;

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
	connections_list				m_receivers;   
	mutable multithreading::Mutex	m_mutex;
};
*/

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
			virtual void send( CW_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_##NUM_ARGS ) const=0; \
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
			virtual void send(CW_DECLARE_FUNCTION_ARGS_##NUM_ARGS) const \
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
			virtual void send(CW_DECLARE_FUNCTION_ARGS_##NUM_ARGS) const \
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
			synchronize(m_mutex); \
			connections_list::const_iterator iter = s.m_receivers.begin(); \
			connections_list::const_iterator sentinel = s.m_receivers.end(); \
			while (iter != sentinel) \
			{ \
				(*iter)->getReceiver()->onConnect(this); \
				m_receivers.push_back((*iter)->clone()); \
				++iter; \
			} \
		} \
		~Transmitter##NUM_ARGS(void) \
		{ \
			disconnectAll(); \
		} \
		template<class RECEIVER> \
		void connect(RECEIVER* receiver, void (RECEIVER::* function)(CW_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_##NUM_ARGS)) \
		{ \
			synchronize(m_mutex); \
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
		template<class RECEIVER> \
		void connect(RECEIVER* receiver, void (RECEIVER::* function)(CW_TEMPLATE_ARGS_SIGNATURE_RETS_0_ARGS_##NUM_ARGS) const) \
		{ \
			synchronize(m_mutex); \
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
		void disconnect(void) \
		{ \
			synchronize(m_mutex); \
			disconnectAll(); \
			m_receivers.erase(m_receivers.begin(), m_receivers.end()); \
		} \
		void disconnect(Receiver* receiver) \
		{ \
			synchronize(m_mutex); \
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
		void replicate(const Receiver* receiver, Receiver* new_receiver) \
		{ \
			synchronize(m_mutex); \
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
		void send(CW_DECLARE_FUNCTION_ARGS_##NUM_ARGS) const \
		{ \
			synchronize(m_mutex); \
			connections_list copy(m_receivers); \
			connections_list::const_iterator iter = copy.begin(); \
			connections_list::const_iterator sentinel = copy.end(); \
			while (iter != sentinel) \
			{ \
				(*iter)->send(CW_CALL_RETS_0_ARGS_##NUM_ARGS); \
				++iter; \
			} \
		} \
		inline void operator()(CW_DECLARE_FUNCTION_ARGS_##NUM_ARGS) const \
		{ \
			send(CW_CALL_RETS_0_ARGS_##NUM_ARGS); \
		} \
	protected: \
		void disconnectAll(void) \
		{ \
			synchronize(m_mutex); \
			connections_list::const_iterator iter = m_receivers.begin(); \
			connections_list::const_iterator sentinel = m_receivers.end(); \
			while (iter != sentinel) \
			{ \
				(*iter)->getReceiver()->onDisconnect(this); \
				delete *iter; \
				++iter; \
			} \
		} \
		void onDisconnect(Receiver* receiver) \
		{ \
			synchronize(m_mutex); \
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
	private: \
		connections_list				m_receivers; \
		mutable multithreading::Mutex	m_mutex; \
	};

SIGNALS_DECLARE_TRANSMITTER(1);
SIGNALS_DECLARE_TRANSMITTER(2);
SIGNALS_DECLARE_TRANSMITTER(3);
SIGNALS_DECLARE_TRANSMITTER(4);
SIGNALS_DECLARE_TRANSMITTER(5);

}

#endif//SIGNALS_H