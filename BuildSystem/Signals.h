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
		virtual void disconnect(Receiver* receiver)=0;
		virtual void duplicate(const Receiver* old_receiver, Receiver* new_receiver)=0;
	};
	
	class Receiver 
	{
	private:
		typedef std::set<Transmitter*>			transmitter_set;
		typedef transmitter_set::const_iterator	const_iterator;

	public:
		Receiver(const Receiver& hs)
		{
			synchronize(m_mutex);
			const_iterator iter = hs.m_transmitters.begin();
			const_iterator sentinel = hs.m_transmitters.end();

			while (iter != sentinel)
			{
				(*iter)->duplicate(&hs, this);
				m_transmitters.insert(*iter);
				++iter;
			}
		} 

		virtual ~Receiver(void)
		{
			disconnectAll();
		}

		void connect(Transmitter* sender)
		{
			synchronize(m_mutex);
			m_transmitters.insert(sender);
		}

		void disconnect(Transmitter* sender)
		{
			synchronize(m_mutex);
			m_transmitters.erase(sender);
		}

		void disconnect(void)
		{
			synchronize(m_mutex);
			disconnectAll();
			m_transmitters.erase(m_transmitters.begin(), m_transmitters.end());
		}

	protected:
		inline void disconnectAll(void)
		{
			synchronize(m_mutex);
			const_iterator iter = m_transmitters.begin();
			const_iterator sentinel = m_transmitters.end();

			while (iter != sentinel)
			{
				(*iter)->disconnect(this);
				++iter;
			}
		}

	private:
		multithreading::Mutex	m_mutex;
		transmitter_set				m_transmitters;
	};

	class Transmitter0 : public Transmitter
	{
		class Connection0
		{
		public:
			virtual ~Connection0(void)=0 {}
			virtual Connection0*	clone()=0;
			virtual Connection0*	duplicate(Receiver* receiver)=0;
			virtual Receiver*		getReceiver() const=0;
			virtual void			send()=0;		
		};

		template<class RECEIVER>
		class Connection0Base : public Connection0
		{
		public:
			Connection0Base(void)
			: m_receiver(NULL)
			, m_function(NULL)
			{
				/* empty */
			}

			Connection0Base(RECEIVER* receiver, void (RECEIVER::*function)(void))
			: m_receiver(receiver)
			, m_function(function)
			{
				/* empty */
			}

			~Connection0Base(void)
			{
				printf("Connection is getting deleted!");
			}

			virtual Connection0* clone(void)
			{
				return new Connection0Base<RECEIVER>(*this);
			}

			virtual Connection0* duplicate(Receiver* receiver)
			{
				return new Connection0Base<RECEIVER>(static_cast<RECEIVER*>(receiver), m_function);
			}

			virtual Receiver* getReceiver(void) const
			{
				return m_receiver;
			}

			virtual void send(void)
			{
				(m_receiver->*m_function)();
			}

		private:
			RECEIVER* m_receiver;
			void (RECEIVER::* m_function)(void);
		};

		typedef std::list<Connection0 *>  connections_list;

	public:
		Transmitter0(const Transmitter0& s)
		: Transmitter(s)
		{
			synchronize(m_mutex);
			connections_list::const_iterator iter = s.m_receivers.begin();
			connections_list::const_iterator sentinel = s.m_receivers.end();

			while (iter != sentinel)
			{
				(*iter)->getReceiver()->connect(this);
				m_receivers.push_back((*iter)->clone());
				++iter;
			}
		}

		~Transmitter0(void)
		{
			disconnectAll();
		}

		template<class RECEIVER>
		void connect(RECEIVER* object, void (RECEIVER::*function)())
		{
			synchronize(m_mutex);
			connections_list::iterator iter = m_receivers.begin();
			connections_list::iterator sentinel = m_receivers.end();

			while (iter != sentinel)
			{
				if ((*iter)->getReceiver() == object)
				{
					return;
				}

				++iter;
			}

			m_receivers.push_back(new Connection0Base<RECEIVER>(object, function));
			object->connect(this);
		}

		void disconnect(void)
		{
			synchronize(m_mutex);
			disconnectAll()
			m_receivers.erase(m_receivers.begin(), m_receivers.end());
		}

		template<class RECEIVER>
		void disconnect(RECEIVER* object)
		{
			synchronize(m_mutex);
			connections_list::iterator iter = m_receivers.begin();
			connections_list::iterator sentinel = m_receivers.end();

			while (iter != sentinel)
			{
				Connection0* connection = *iter;
				
				if (connection->getReceiver() == object)
				{
					m_receivers.erase(iter);
					object->disconnect(this);
					delete connection;
					return;
				}

				++iter;
			}
		}

		void duplicate(const Receiver* old_receiver, Receiver* new_receiver)
		{
			synchronize(m_mutex);
			connections_list::iterator iter = m_receivers.begin();
			connections_list::iterator sentinel = m_receivers.end();

			while (iter != sentinel)
			{
				if ((*iter)->getReceiver() == old_receiver)
				{
					m_receivers.push_back((*iter)->duplicate(new_receiver));
				}

				++iter;
			}
		}

		inline void send(void)
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
				Connection0* connection = *iter;
				++iter;
				connection->getReceiver()->disconnect(this);
				delete connection;
			}
		}

	private:
		connections_list		m_receivers;   
		multithreading::Mutex	m_mutex;	
	};

} // Signals

#endif//SIGNALS_H