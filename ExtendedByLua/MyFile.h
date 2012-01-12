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
	};
	template< class RECEIVER, typename ARG_1>
	class volatile1
	{
	public:
		volatile1(void)
		: m_object(NULL)
		, m_function(NULL)
		{}
		volatile1(RECEIVER* object, void (RECEIVER::* function)ARG_1))
		: m_object(object)
		, m_function(function)
		{}
		virtual Connection* clone(void)
		{
			return new volatile1<RECEIVER, ARG_1>(*this);
		}
		virtual Connection* duplicate(void)
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
	}
	template<class RECEIVER, typename ARG_1>
	class const1
	: public Connection<ARG_1>
	{
	public:
		const1(void)
		: m_object(NULL)
		, m_function(NULL)
		{}
		



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
	};
	template< class RECEIVER, typename ARG_1, typename ARG_2>
	class volatile2
	{
	public:
		volatile2(void)
		: m_object(NULL)
		, m_function(NULL)
		{}
		volatile2(RECEIVER* object, void (RECEIVER::* function)ARG_1, ARG_2))
		: m_object(object)
		, m_function(function)
		{}
		virtual Connection* clone(void)
		{
			return new volatile2<RECEIVER, ARG_1, ARG_2>(*this);
		}
		virtual Connection* duplicate(void)
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
	}
	template<class RECEIVER, typename ARG_1, typename ARG_2>
	class const2
	: public Connection<ARG_1, ARG_2>
	{
	public:
		const2(void)
		: m_object(NULL)
		, m_function(NULL)
		{}
		



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
	};
	template< class RECEIVER, typename ARG_1, typename ARG_2, typename ARG_3>
	class volatile3
	{
	public:
		volatile3(void)
		: m_object(NULL)
		, m_function(NULL)
		{}
		volatile3(RECEIVER* object, void (RECEIVER::* function)ARG_1, ARG_2, ARG_3))
		: m_object(object)
		, m_function(function)
		{}
		virtual Connection* clone(void)
		{
			return new volatile3<RECEIVER, ARG_1, ARG_2, ARG_3>(*this);
		}
		virtual Connection* duplicate(void)
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
	}
	template<class RECEIVER, typename ARG_1, typename ARG_2, typename ARG_3>
	class const3
	: public Connection<ARG_1, ARG_2, ARG_3>
	{
	public:
		const3(void)
		: m_object(NULL)
		, m_function(NULL)
		{}
		



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
	};
	template< class RECEIVER, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4>
	class volatile4
	{
	public:
		volatile4(void)
		: m_object(NULL)
		, m_function(NULL)
		{}
		volatile4(RECEIVER* object, void (RECEIVER::* function)ARG_1, ARG_2, ARG_3, ARG_4))
		: m_object(object)
		, m_function(function)
		{}
		virtual Connection* clone(void)
		{
			return new volatile4<RECEIVER, ARG_1, ARG_2, ARG_3, ARG_4>(*this);
		}
		virtual Connection* duplicate(void)
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
	}
	template<class RECEIVER, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4>
	class const4
	: public Connection<ARG_1, ARG_2, ARG_3, ARG_4>
	{
	public:
		const4(void)
		: m_object(NULL)
		, m_function(NULL)
		{}
		



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
	};
	template< class RECEIVER, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5>
	class volatile5
	{
	public:
		volatile5(void)
		: m_object(NULL)
		, m_function(NULL)
		{}
		volatile5(RECEIVER* object, void (RECEIVER::* function)ARG_1, ARG_2, ARG_3, ARG_4, ARG_5))
		: m_object(object)
		, m_function(function)
		{}
		virtual Connection* clone(void)
		{
			return new volatile5<RECEIVER, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5>(*this);
		}
		virtual Connection* duplicate(void)
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
	}
	template<class RECEIVER, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5>
	class const5
	: public Connection<ARG_1, ARG_2, ARG_3, ARG_4, ARG_5>
	{
	public:
		const5(void)
		: m_object(NULL)
		, m_function(NULL)
		{}
		



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
	};
	template< class RECEIVER, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6>
	class volatile6
	{
	public:
		volatile6(void)
		: m_object(NULL)
		, m_function(NULL)
		{}
		volatile6(RECEIVER* object, void (RECEIVER::* function)ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6))
		: m_object(object)
		, m_function(function)
		{}
		virtual Connection* clone(void)
		{
			return new volatile6<RECEIVER, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6>(*this);
		}
		virtual Connection* duplicate(void)
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
	}
	template<class RECEIVER, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6>
	class const6
	: public Connection<ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6>
	{
	public:
		const6(void)
		: m_object(NULL)
		, m_function(NULL)
		{}
		



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
	};
	template< class RECEIVER, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7>
	class volatile7
	{
	public:
		volatile7(void)
		: m_object(NULL)
		, m_function(NULL)
		{}
		volatile7(RECEIVER* object, void (RECEIVER::* function)ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7))
		: m_object(object)
		, m_function(function)
		{}
		virtual Connection* clone(void)
		{
			return new volatile7<RECEIVER, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7>(*this);
		}
		virtual Connection* duplicate(void)
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
	}
	template<class RECEIVER, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7>
	class const7
	: public Connection<ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7>
	{
	public:
		const7(void)
		: m_object(NULL)
		, m_function(NULL)
		{}
		



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
	};
	template< class RECEIVER, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8>
	class volatile8
	{
	public:
		volatile8(void)
		: m_object(NULL)
		, m_function(NULL)
		{}
		volatile8(RECEIVER* object, void (RECEIVER::* function)ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8))
		: m_object(object)
		, m_function(function)
		{}
		virtual Connection* clone(void)
		{
			return new volatile8<RECEIVER, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8>(*this);
		}
		virtual Connection* duplicate(void)
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
	}
	template<class RECEIVER, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8>
	class const8
	: public Connection<ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8>
	{
	public:
		const8(void)
		: m_object(NULL)
		, m_function(NULL)
		{}
		



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
	};
	template< class RECEIVER, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9>
	class volatile9
	{
	public:
		volatile9(void)
		: m_object(NULL)
		, m_function(NULL)
		{}
		volatile9(RECEIVER* object, void (RECEIVER::* function)ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9))
		: m_object(object)
		, m_function(function)
		{}
		virtual Connection* clone(void)
		{
			return new volatile9<RECEIVER, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9>(*this);
		}
		virtual Connection* duplicate(void)
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
	}
	template<class RECEIVER, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9>
	class const9
	: public Connection<ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9>
	{
	public:
		const9(void)
		: m_object(NULL)
		, m_function(NULL)
		{}
		



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
	};
	template< class RECEIVER, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10>
	class volatile10
	{
	public:
		volatile10(void)
		: m_object(NULL)
		, m_function(NULL)
		{}
		volatile10(RECEIVER* object, void (RECEIVER::* function)ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10))
		: m_object(object)
		, m_function(function)
		{}
		virtual Connection* clone(void)
		{
			return new volatile10<RECEIVER, ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10>(*this);
		}
		virtual Connection* duplicate(void)
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
	}
	template<class RECEIVER, typename ARG_1, typename ARG_2, typename ARG_3, typename ARG_4, typename ARG_5, typename ARG_6, typename ARG_7, typename ARG_8, typename ARG_9, typename ARG_10>
	class const10
	: public Connection<ARG_1, ARG_2, ARG_3, ARG_4, ARG_5, ARG_6, ARG_7, ARG_8, ARG_9, ARG_10>
	{
	public:
		const10(void)
		: m_object(NULL)
		, m_function(NULL)
		{}
		



