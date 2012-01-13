template<typename ARG_1>
class Transmitter1 : public Transmitter
{
private:
	template<typename ARG_1>
	class Connection
	{
	public:
		virtual ~Connection(void)=0 {};
		virtual Connection<ARG_1>* clone(void)=0;
		virtual Connection<ARG_1>* duplicate(Receiver* receiver)=0;
		virtual Receiver* getReceiver(void) const=0;
		virtual void transmit(ARG_1) const=0;
	}; // class Connection
	template< class RECEIVER, typename ARG_1>
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
		virtual void transmit(ARG_1 arg1) const
		{
			(m_object->*m_function)(arg1);
		}
	private:
		RECEIVER* m_object;
		void (RECEIVER::* m_function)(ARG_1);
	}; // class volatile1
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
			return new const1<RECEIVER, ARG_1>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new const1<RECEIVER, ARG_1>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual Receiver* getReceiver(void) const
		{
			return m_object;
		}
		virtual void transmit(ARG_1 arg1) const
		{
			(m_object->*m_function)(arg1);
		}
	private:
		RECEIVER* m_object;
		void (RECEIVER::* m_function)(ARG_1) const;
	}; // class const1
public:
	typedef std::list< Connection<ARG_1> *> connections_list;
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
	void connect(RECEIVER* receiver, void (RECEIVER::* function)(ARG_1))
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
			m_receivers.push_back(new volatile1<RECEIVER, ARG_1>(receiver, function));
			receiver->onConnect(this);
		}
	}
	template<class RECEIVER>
	void connect(RECEIVER* receiver, void (RECEIVER::* function)(ARG_1) const)
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
			m_receivers.push_back(new const1<RECEIVER, ARG_1>(receiver, function));
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
	void transmit(ARG_1 arg1) const
	{
		SYNC(m_mutex);
		connections_list copy(m_receivers);
		connections_list::const_iterator iter = copy.begin();
		connections_list::const_iterator sentinel = copy.end();
		while (iter != sentinel)
		{
			(*iter)->transmit(arg1);
			++iter;
		}
	}
	inline void operator()(ARG_1 arg1) const
	{
		transmit(arg1);
	}
	protected:
	void onDisconnect(Receiver* receiver)
	{
		SYNC(m_mutex);
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
	connections_list m_receivers;
	DECLARE_MUTABLE_MUTEX(m_mutex)
}; // class Transmitter1

template<typename ARG_1, typename ARG_2>
class Transmitter2 : public Transmitter
{
private:
	template<typename ARG_1, typename ARG_2>
	class Connection
	{
	public:
		virtual ~Connection(void)=0 {};
		virtual Connection<ARG_1, ARG_2>* clone(void)=0;
		virtual Connection<ARG_1, ARG_2>* duplicate(Receiver* receiver)=0;
		virtual Receiver* getReceiver(void) const=0;
		virtual void transmit(ARG_1, ARG_2) const=0;
	}; // class Connection
	template< class RECEIVER, typename ARG_1, typename ARG_2>
	class volatile2
	: public Connection<ARG_1, ARG_2>
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
			return new volatile2<RECEIVER, ARG_1, ARG_2>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new volatile2<RECEIVER, ARG_1, ARG_2>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual Receiver* getReceiver(void) const
		{
			return m_object;
		}
		virtual void transmit(ARG_1 arg1, ARG_2 arg2) const
		{
			(m_object->*m_function)(arg1, arg2);
		}
	private:
		RECEIVER* m_object;
		void (RECEIVER::* m_function)(ARG_1, ARG_2);
	}; // class volatile2
	template<class RECEIVER, typename ARG_1, typename ARG_2>
	class const2
	: public Connection<ARG_1, ARG_2>
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
			return new const2<RECEIVER, ARG_1, ARG_2>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new const2<RECEIVER, ARG_1, ARG_2>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual Receiver* getReceiver(void) const
		{
			return m_object;
		}
		virtual void transmit(ARG_1 arg1, ARG_2 arg2) const
		{
			(m_object->*m_function)(arg1, arg2);
		}
	private:
		RECEIVER* m_object;
		void (RECEIVER::* m_function)(ARG_1, ARG_2) const;
	}; // class const2
public:
	typedef std::list< Connection<ARG_1, ARG_2> *> connections_list;
	Transmitter2(void)
	{}
	Transmitter2(const Transmitter2& s)
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
			m_receivers.push_back(new volatile2<RECEIVER, ARG_1, ARG_2>(receiver, function));
			receiver->onConnect(this);
		}
	}
	template<class RECEIVER>
	void connect(RECEIVER* receiver, void (RECEIVER::* function)(ARG_1, ARG_2) const)
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
			m_receivers.push_back(new const2<RECEIVER, ARG_1, ARG_2>(receiver, function));
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
			Connection<ARG_1, ARG_2>* connection = *iter;
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
	void transmit(ARG_1 arg1, ARG_2 arg2) const
	{
		SYNC(m_mutex);
		connections_list copy(m_receivers);
		connections_list::const_iterator iter = copy.begin();
		connections_list::const_iterator sentinel = copy.end();
		while (iter != sentinel)
		{
			(*iter)->transmit(arg1, arg2);
			++iter;
		}
	}
	inline void operator()(ARG_1 arg1, ARG_2 arg2) const
	{
		transmit(arg1, arg2);
	}
	protected:
	void onDisconnect(Receiver* receiver)
	{
		SYNC(m_mutex);
		connections_list::iterator iter = m_receivers.begin();
		connections_list::iterator sentinel = m_receivers.end();
		while (iter != sentinel)
		{
			Connection<ARG_1, ARG_2>* connection = *iter;
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
	connections_list m_receivers;
	DECLARE_MUTABLE_MUTEX(m_mutex)
}; // class Transmitter2

template<typename ARG_1, typename ARG_2, typename ARG_3>
class Transmitter3 : public Transmitter
{
private:
	template<typename ARG_1, typename ARG_2, typename ARG_3>
	class Connection
	{
	public:
		virtual ~Connection(void)=0 {};
		virtual Connection<ARG_1, ARG_2, ARG_3>* clone(void)=0;
		virtual Connection<ARG_1, ARG_2, ARG_3>* duplicate(Receiver* receiver)=0;
		virtual Receiver* getReceiver(void) const=0;
		virtual void transmit(ARG_1, ARG_2, ARG_3) const=0;
	}; // class Connection
	template< class RECEIVER, typename ARG_1, typename ARG_2, typename ARG_3>
	class volatile3
	: public Connection<ARG_1, ARG_2, ARG_3>
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
			return new volatile3<RECEIVER, ARG_1, ARG_2, ARG_3>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new volatile3<RECEIVER, ARG_1, ARG_2, ARG_3>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual Receiver* getReceiver(void) const
		{
			return m_object;
		}
		virtual void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3) const
		{
			(m_object->*m_function)(arg1, arg2, arg3);
		}
	private:
		RECEIVER* m_object;
		void (RECEIVER::* m_function)(ARG_1, ARG_2, ARG_3);
	}; // class volatile3
	template<class RECEIVER, typename ARG_1, typename ARG_2, typename ARG_3>
	class const3
	: public Connection<ARG_1, ARG_2, ARG_3>
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
			return new const3<RECEIVER, ARG_1, ARG_2, ARG_3>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new const3<RECEIVER, ARG_1, ARG_2, ARG_3>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual Receiver* getReceiver(void) const
		{
			return m_object;
		}
		virtual void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3) const
		{
			(m_object->*m_function)(arg1, arg2, arg3);
		}
	private:
		RECEIVER* m_object;
		void (RECEIVER::* m_function)(ARG_1, ARG_2, ARG_3) const;
	}; // class const3
public:
	typedef std::list< Connection<ARG_1, ARG_2, ARG_3> *> connections_list;
	Transmitter3(void)
	{}
	Transmitter3(const Transmitter3& s)
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
			m_receivers.push_back(new volatile3<RECEIVER, ARG_1, ARG_2, ARG_3>(receiver, function));
			receiver->onConnect(this);
		}
	}
	template<class RECEIVER>
	void connect(RECEIVER* receiver, void (RECEIVER::* function)(ARG_1, ARG_2, ARG_3) const)
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
			m_receivers.push_back(new const3<RECEIVER, ARG_1, ARG_2, ARG_3>(receiver, function));
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
			Connection<ARG_1, ARG_2, ARG_3>* connection = *iter;
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
	void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3) const
	{
		SYNC(m_mutex);
		connections_list copy(m_receivers);
		connections_list::const_iterator iter = copy.begin();
		connections_list::const_iterator sentinel = copy.end();
		while (iter != sentinel)
		{
			(*iter)->transmit(arg1, arg2, arg3);
			++iter;
		}
	}
	inline void operator()(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3) const
	{
		transmit(arg1, arg2, arg3);
	}
	protected:
	void onDisconnect(Receiver* receiver)
	{
		SYNC(m_mutex);
		connections_list::iterator iter = m_receivers.begin();
		connections_list::iterator sentinel = m_receivers.end();
		while (iter != sentinel)
		{
			Connection<ARG_1, ARG_2, ARG_3>* connection = *iter;
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
	connections_list m_receivers;
	DECLARE_MUTABLE_MUTEX(m_mutex)
}; // class Transmitter3

template<typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4>
class Transmitter4 : public Transmitter
{
private:
	template<typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4>
	class Connection
	{
	public:
		virtual ~Connection(void)=0 {};
		virtual Connection<ARG_1, ARG_2, ARG_3, ARG_4>* clone(void)=0;
		virtual Connection<ARG_1, ARG_2, ARG_3, ARG_4>* duplicate(Receiver* receiver)=0;
		virtual Receiver* getReceiver(void) const=0;
		virtual void transmit(ARG_1, ARG_2, ARG_3, ARG_4) const=0;
	}; // class Connection
	template< class RECEIVER, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4>
	class volatile4
	: public Connection<ARG_1, ARG_2, ARG_3, ARG_4>
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
			return new volatile4<RECEIVER, ARG_1, ARG_2, ARG_3, ARG_4>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new volatile4<RECEIVER, ARG_1, ARG_2, ARG_3, ARG_4>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual Receiver* getReceiver(void) const
		{
			return m_object;
		}
		virtual void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4) const
		{
			(m_object->*m_function)(arg1, arg2, arg3, arg4);
		}
	private:
		RECEIVER* m_object;
		void (RECEIVER::* m_function)(ARG_1, ARG_2, ARG_3, ARG_4);
	}; // class volatile4
	template<class RECEIVER, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4>
	class const4
	: public Connection<ARG_1, ARG_2, ARG_3, ARG_4>
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
			return new const4<RECEIVER, ARG_1, ARG_2, ARG_3, ARG_4>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new const4<RECEIVER, ARG_1, ARG_2, ARG_3, ARG_4>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual Receiver* getReceiver(void) const
		{
			return m_object;
		}
		virtual void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4) const
		{
			(m_object->*m_function)(arg1, arg2, arg3, arg4);
		}
	private:
		RECEIVER* m_object;
		void (RECEIVER::* m_function)(ARG_1, ARG_2, ARG_3, ARG_4) const;
	}; // class const4
public:
	typedef std::list< Connection<ARG_1, ARG_2, ARG_3, ARG_4> *> connections_list;
	Transmitter4(void)
	{}
	Transmitter4(const Transmitter4& s)
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
			m_receivers.push_back(new volatile4<RECEIVER, ARG_1, ARG_2, ARG_3, ARG_4>(receiver, function));
			receiver->onConnect(this);
		}
	}
	template<class RECEIVER>
	void connect(RECEIVER* receiver, void (RECEIVER::* function)(ARG_1, ARG_2, ARG_3, ARG_4) const)
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
			m_receivers.push_back(new const4<RECEIVER, ARG_1, ARG_2, ARG_3, ARG_4>(receiver, function));
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
			Connection<ARG_1, ARG_2, ARG_3, ARG_4>* connection = *iter;
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
	void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4) const
	{
		SYNC(m_mutex);
		connections_list copy(m_receivers);
		connections_list::const_iterator iter = copy.begin();
		connections_list::const_iterator sentinel = copy.end();
		while (iter != sentinel)
		{
			(*iter)->transmit(arg1, arg2, arg3, arg4);
			++iter;
		}
	}
	inline void operator()(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4) const
	{
		transmit(arg1, arg2, arg3, arg4);
	}
	protected:
	void onDisconnect(Receiver* receiver)
	{
		SYNC(m_mutex);
		connections_list::iterator iter = m_receivers.begin();
		connections_list::iterator sentinel = m_receivers.end();
		while (iter != sentinel)
		{
			Connection<ARG_1, ARG_2, ARG_3, ARG_4>* connection = *iter;
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
	connections_list m_receivers;
	DECLARE_MUTABLE_MUTEX(m_mutex)
}; // class Transmitter4

template<typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5>
class Transmitter5 : public Transmitter
{
private:
	template<typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5>
	class Connection
	{
	public:
		virtual ~Connection(void)=0 {};
		virtual Connection<ARG_1, ARG_2, ARG_3, ARG_4, ARG_5>* clone(void)=0;
		virtual Connection<ARG_1, ARG_2, ARG_3, ARG_4, ARG_5>* duplicate(Receiver* receiver)=0;
		virtual Receiver* getReceiver(void) const=0;
		virtual void transmit(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) const=0;
	}; // class Connection
	template< class RECEIVER, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5>
	class volatile5
	: public Connection<ARG_1, ARG_2, ARG_3, ARG_4, ARG_5>
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
			return new volatile5<RECEIVER, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new volatile5<RECEIVER, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual Receiver* getReceiver(void) const
		{
			return m_object;
		}
		virtual void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5) const
		{
			(m_object->*m_function)(arg1, arg2, arg3, arg4, arg5);
		}
	private:
		RECEIVER* m_object;
		void (RECEIVER::* m_function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5);
	}; // class volatile5
	template<class RECEIVER, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5>
	class const5
	: public Connection<ARG_1, ARG_2, ARG_3, ARG_4, ARG_5>
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
			return new const5<RECEIVER, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new const5<RECEIVER, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual Receiver* getReceiver(void) const
		{
			return m_object;
		}
		virtual void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5) const
		{
			(m_object->*m_function)(arg1, arg2, arg3, arg4, arg5);
		}
	private:
		RECEIVER* m_object;
		void (RECEIVER::* m_function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) const;
	}; // class const5
public:
	typedef std::list< Connection<ARG_1, ARG_2, ARG_3, ARG_4, ARG_5> *> connections_list;
	Transmitter5(void)
	{}
	Transmitter5(const Transmitter5& s)
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
			m_receivers.push_back(new volatile5<RECEIVER, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5>(receiver, function));
			receiver->onConnect(this);
		}
	}
	template<class RECEIVER>
	void connect(RECEIVER* receiver, void (RECEIVER::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5) const)
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
			m_receivers.push_back(new const5<RECEIVER, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5>(receiver, function));
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
			Connection<ARG_1, ARG_2, ARG_3, ARG_4, ARG_5>* connection = *iter;
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
	void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5) const
	{
		SYNC(m_mutex);
		connections_list copy(m_receivers);
		connections_list::const_iterator iter = copy.begin();
		connections_list::const_iterator sentinel = copy.end();
		while (iter != sentinel)
		{
			(*iter)->transmit(arg1, arg2, arg3, arg4, arg5);
			++iter;
		}
	}
	inline void operator()(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5) const
	{
		transmit(arg1, arg2, arg3, arg4, arg5);
	}
	protected:
	void onDisconnect(Receiver* receiver)
	{
		SYNC(m_mutex);
		connections_list::iterator iter = m_receivers.begin();
		connections_list::iterator sentinel = m_receivers.end();
		while (iter != sentinel)
		{
			Connection<ARG_1, ARG_2, ARG_3, ARG_4, ARG_5>* connection = *iter;
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
	connections_list m_receivers;
	DECLARE_MUTABLE_MUTEX(m_mutex)
}; // class Transmitter5

template<typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6>
class Transmitter6 : public Transmitter
{
private:
	template<typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6>
	class Connection
	{
	public:
		virtual ~Connection(void)=0 {};
		virtual Connection<ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6>* clone(void)=0;
		virtual Connection<ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6>* duplicate(Receiver* receiver)=0;
		virtual Receiver* getReceiver(void) const=0;
		virtual void transmit(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) const=0;
	}; // class Connection
	template< class RECEIVER, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6>
	class volatile6
	: public Connection<ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6>
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
			return new volatile6<RECEIVER, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new volatile6<RECEIVER, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual Receiver* getReceiver(void) const
		{
			return m_object;
		}
		virtual void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6) const
		{
			(m_object->*m_function)(arg1, arg2, arg3, arg4, arg5, arg6);
		}
	private:
		RECEIVER* m_object;
		void (RECEIVER::* m_function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6);
	}; // class volatile6
	template<class RECEIVER, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6>
	class const6
	: public Connection<ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6>
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
			return new const6<RECEIVER, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new const6<RECEIVER, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual Receiver* getReceiver(void) const
		{
			return m_object;
		}
		virtual void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6) const
		{
			(m_object->*m_function)(arg1, arg2, arg3, arg4, arg5, arg6);
		}
	private:
		RECEIVER* m_object;
		void (RECEIVER::* m_function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) const;
	}; // class const6
public:
	typedef std::list< Connection<ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6> *> connections_list;
	Transmitter6(void)
	{}
	Transmitter6(const Transmitter6& s)
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
			m_receivers.push_back(new volatile6<RECEIVER, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6>(receiver, function));
			receiver->onConnect(this);
		}
	}
	template<class RECEIVER>
	void connect(RECEIVER* receiver, void (RECEIVER::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6) const)
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
			m_receivers.push_back(new const6<RECEIVER, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6>(receiver, function));
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
			Connection<ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6>* connection = *iter;
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
	void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6) const
	{
		SYNC(m_mutex);
		connections_list copy(m_receivers);
		connections_list::const_iterator iter = copy.begin();
		connections_list::const_iterator sentinel = copy.end();
		while (iter != sentinel)
		{
			(*iter)->transmit(arg1, arg2, arg3, arg4, arg5, arg6);
			++iter;
		}
	}
	inline void operator()(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6) const
	{
		transmit(arg1, arg2, arg3, arg4, arg5, arg6);
	}
	protected:
	void onDisconnect(Receiver* receiver)
	{
		SYNC(m_mutex);
		connections_list::iterator iter = m_receivers.begin();
		connections_list::iterator sentinel = m_receivers.end();
		while (iter != sentinel)
		{
			Connection<ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6>* connection = *iter;
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
	connections_list m_receivers;
	DECLARE_MUTABLE_MUTEX(m_mutex)
}; // class Transmitter6

template<typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7>
class Transmitter7 : public Transmitter
{
private:
	template<typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7>
	class Connection
	{
	public:
		virtual ~Connection(void)=0 {};
		virtual Connection<ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7>* clone(void)=0;
		virtual Connection<ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7>* duplicate(Receiver* receiver)=0;
		virtual Receiver* getReceiver(void) const=0;
		virtual void transmit(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) const=0;
	}; // class Connection
	template< class RECEIVER, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7>
	class volatile7
	: public Connection<ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7>
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
			return new volatile7<RECEIVER, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new volatile7<RECEIVER, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual Receiver* getReceiver(void) const
		{
			return m_object;
		}
		virtual void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7) const
		{
			(m_object->*m_function)(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		}
	private:
		RECEIVER* m_object;
		void (RECEIVER::* m_function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7);
	}; // class volatile7
	template<class RECEIVER, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7>
	class const7
	: public Connection<ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7>
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
			return new const7<RECEIVER, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new const7<RECEIVER, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual Receiver* getReceiver(void) const
		{
			return m_object;
		}
		virtual void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7) const
		{
			(m_object->*m_function)(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
		}
	private:
		RECEIVER* m_object;
		void (RECEIVER::* m_function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) const;
	}; // class const7
public:
	typedef std::list< Connection<ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7> *> connections_list;
	Transmitter7(void)
	{}
	Transmitter7(const Transmitter7& s)
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
			m_receivers.push_back(new volatile7<RECEIVER, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7>(receiver, function));
			receiver->onConnect(this);
		}
	}
	template<class RECEIVER>
	void connect(RECEIVER* receiver, void (RECEIVER::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7) const)
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
			m_receivers.push_back(new const7<RECEIVER, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7>(receiver, function));
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
			Connection<ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7>* connection = *iter;
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
	void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7) const
	{
		SYNC(m_mutex);
		connections_list copy(m_receivers);
		connections_list::const_iterator iter = copy.begin();
		connections_list::const_iterator sentinel = copy.end();
		while (iter != sentinel)
		{
			(*iter)->transmit(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
			++iter;
		}
	}
	inline void operator()(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7) const
	{
		transmit(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
	}
	protected:
	void onDisconnect(Receiver* receiver)
	{
		SYNC(m_mutex);
		connections_list::iterator iter = m_receivers.begin();
		connections_list::iterator sentinel = m_receivers.end();
		while (iter != sentinel)
		{
			Connection<ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7>* connection = *iter;
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
	connections_list m_receivers;
	DECLARE_MUTABLE_MUTEX(m_mutex)
}; // class Transmitter7

template<typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8>
class Transmitter8 : public Transmitter
{
private:
	template<typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8>
	class Connection
	{
	public:
		virtual ~Connection(void)=0 {};
		virtual Connection<ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8>* clone(void)=0;
		virtual Connection<ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8>* duplicate(Receiver* receiver)=0;
		virtual Receiver* getReceiver(void) const=0;
		virtual void transmit(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) const=0;
	}; // class Connection
	template< class RECEIVER, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8>
	class volatile8
	: public Connection<ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8>
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
			return new volatile8<RECEIVER, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new volatile8<RECEIVER, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual Receiver* getReceiver(void) const
		{
			return m_object;
		}
		virtual void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8) const
		{
			(m_object->*m_function)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		}
	private:
		RECEIVER* m_object;
		void (RECEIVER::* m_function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8);
	}; // class volatile8
	template<class RECEIVER, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8>
	class const8
	: public Connection<ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8>
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
			return new const8<RECEIVER, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new const8<RECEIVER, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual Receiver* getReceiver(void) const
		{
			return m_object;
		}
		virtual void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8) const
		{
			(m_object->*m_function)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
		}
	private:
		RECEIVER* m_object;
		void (RECEIVER::* m_function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) const;
	}; // class const8
public:
	typedef std::list< Connection<ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8> *> connections_list;
	Transmitter8(void)
	{}
	Transmitter8(const Transmitter8& s)
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
			m_receivers.push_back(new volatile8<RECEIVER, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8>(receiver, function));
			receiver->onConnect(this);
		}
	}
	template<class RECEIVER>
	void connect(RECEIVER* receiver, void (RECEIVER::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8) const)
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
			m_receivers.push_back(new const8<RECEIVER, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8>(receiver, function));
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
			Connection<ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8>* connection = *iter;
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
	void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8) const
	{
		SYNC(m_mutex);
		connections_list copy(m_receivers);
		connections_list::const_iterator iter = copy.begin();
		connections_list::const_iterator sentinel = copy.end();
		while (iter != sentinel)
		{
			(*iter)->transmit(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
			++iter;
		}
	}
	inline void operator()(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8) const
	{
		transmit(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
	}
	protected:
	void onDisconnect(Receiver* receiver)
	{
		SYNC(m_mutex);
		connections_list::iterator iter = m_receivers.begin();
		connections_list::iterator sentinel = m_receivers.end();
		while (iter != sentinel)
		{
			Connection<ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8>* connection = *iter;
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
	connections_list m_receivers;
	DECLARE_MUTABLE_MUTEX(m_mutex)
}; // class Transmitter8

template<typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9>
class Transmitter9 : public Transmitter
{
private:
	template<typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9>
	class Connection
	{
	public:
		virtual ~Connection(void)=0 {};
		virtual Connection<ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9>* clone(void)=0;
		virtual Connection<ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9>* duplicate(Receiver* receiver)=0;
		virtual Receiver* getReceiver(void) const=0;
		virtual void transmit(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) const=0;
	}; // class Connection
	template< class RECEIVER, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9>
	class volatile9
	: public Connection<ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9>
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
			return new volatile9<RECEIVER, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new volatile9<RECEIVER, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual Receiver* getReceiver(void) const
		{
			return m_object;
		}
		virtual void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9) const
		{
			(m_object->*m_function)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		}
	private:
		RECEIVER* m_object;
		void (RECEIVER::* m_function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9);
	}; // class volatile9
	template<class RECEIVER, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9>
	class const9
	: public Connection<ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9>
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
			return new const9<RECEIVER, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new const9<RECEIVER, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual Receiver* getReceiver(void) const
		{
			return m_object;
		}
		virtual void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9) const
		{
			(m_object->*m_function)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
		}
	private:
		RECEIVER* m_object;
		void (RECEIVER::* m_function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) const;
	}; // class const9
public:
	typedef std::list< Connection<ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9> *> connections_list;
	Transmitter9(void)
	{}
	Transmitter9(const Transmitter9& s)
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
			m_receivers.push_back(new volatile9<RECEIVER, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9>(receiver, function));
			receiver->onConnect(this);
		}
	}
	template<class RECEIVER>
	void connect(RECEIVER* receiver, void (RECEIVER::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9) const)
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
			m_receivers.push_back(new const9<RECEIVER, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9>(receiver, function));
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
			Connection<ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9>* connection = *iter;
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
	void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9) const
	{
		SYNC(m_mutex);
		connections_list copy(m_receivers);
		connections_list::const_iterator iter = copy.begin();
		connections_list::const_iterator sentinel = copy.end();
		while (iter != sentinel)
		{
			(*iter)->transmit(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
			++iter;
		}
	}
	inline void operator()(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9) const
	{
		transmit(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
	}
	protected:
	void onDisconnect(Receiver* receiver)
	{
		SYNC(m_mutex);
		connections_list::iterator iter = m_receivers.begin();
		connections_list::iterator sentinel = m_receivers.end();
		while (iter != sentinel)
		{
			Connection<ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9>* connection = *iter;
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
	connections_list m_receivers;
	DECLARE_MUTABLE_MUTEX(m_mutex)
}; // class Transmitter9

template<typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10>
class Transmitter10 : public Transmitter
{
private:
	template<typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10>
	class Connection
	{
	public:
		virtual ~Connection(void)=0 {};
		virtual Connection<ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10>* clone(void)=0;
		virtual Connection<ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10>* duplicate(Receiver* receiver)=0;
		virtual Receiver* getReceiver(void) const=0;
		virtual void transmit(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) const=0;
	}; // class Connection
	template< class RECEIVER, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10>
	class volatile10
	: public Connection<ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10>
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
			return new volatile10<RECEIVER, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new volatile10<RECEIVER, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual Receiver* getReceiver(void) const
		{
			return m_object;
		}
		virtual void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, ARG_10 arg10) const
		{
			(m_object->*m_function)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		}
	private:
		RECEIVER* m_object;
		void (RECEIVER::* m_function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10);
	}; // class volatile10
	template<class RECEIVER, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10>
	class const10
	: public Connection<ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10>
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
			return new const10<RECEIVER, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10>(*this);
		}
		virtual Connection* duplicate(Receiver* receiver)
		{
			return new const10<RECEIVER, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10>(static_cast<RECEIVER*>(receiver), m_function);
		}
		virtual Receiver* getReceiver(void) const
		{
			return m_object;
		}
		virtual void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, ARG_10 arg10) const
		{
			(m_object->*m_function)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
		}
	private:
		RECEIVER* m_object;
		void (RECEIVER::* m_function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) const;
	}; // class const10
public:
	typedef std::list< Connection<ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10> *> connections_list;
	Transmitter10(void)
	{}
	Transmitter10(const Transmitter10& s)
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
			m_receivers.push_back(new volatile10<RECEIVER, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10>(receiver, function));
			receiver->onConnect(this);
		}
	}
	template<class RECEIVER>
	void connect(RECEIVER* receiver, void (RECEIVER::* function)(ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10) const)
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
			m_receivers.push_back(new const10<RECEIVER, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10>(receiver, function));
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
			Connection<ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10>* connection = *iter;
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
	void transmit(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, ARG_10 arg10) const
	{
		SYNC(m_mutex);
		connections_list copy(m_receivers);
		connections_list::const_iterator iter = copy.begin();
		connections_list::const_iterator sentinel = copy.end();
		while (iter != sentinel)
		{
			(*iter)->transmit(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
			++iter;
		}
	}
	inline void operator()(ARG_1 arg1, ARG_2 arg2, ARG_3 arg3, ARG_4 arg4, ARG_5 arg5, ARG_6 arg6, ARG_7 arg7, ARG_8 arg8, ARG_9 arg9, ARG_10 arg10) const
	{
		transmit(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
	}
	protected:
	void onDisconnect(Receiver* receiver)
	{
		SYNC(m_mutex);
		connections_list::iterator iter = m_receivers.begin();
		connections_list::iterator sentinel = m_receivers.end();
		while (iter != sentinel)
		{
			Connection<ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10>* connection = *iter;
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
	connections_list m_receivers;
	DECLARE_MUTABLE_MUTEX(m_mutex)
}; // class Transmitter10

