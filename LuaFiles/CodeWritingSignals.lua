require'Utilities'
require'CodeWriting'
local U = Utilities
local CW = CodeWriting

deprecatedNaughtyModule(...)

local tabs = function(number)
	local indent = ''
	number = number or 0
	for i = 1, number do
		indent = indent..'\t'
	end
	return indent
end

local more = function(output, numtabs, newString)
	if numtabs > 0 then
		output = output..tabs(1)..newString
	else
		output = output..newString
	end
end

function writeClassBasedOnNumberOfArguments(myFile, nargs)
	local output
	output = ''
	output = output..			'template<'..CW.templateArguments(0, nargs)..'>\n'
	output = output..			'class Transmitter'..nargs..' : public Transmitter\n'
	output = output..			'{\n'
	output = output..			'private:\n'
	output = output..tabs(1)..	'template<'..CW.templateArguments(0, nargs)..'>\n'
	output = output..tabs(1)..	'class Connection\n'
	output = output..tabs(1)..	'{\n'	
	output = output..tabs(1)..	'public:\n'
	output = output..tabs(2)..		'virtual ~Connection(void)=0 {};\n'
	output = output..tabs(2)..		'virtual Connection<'..CW.templateArgumentsSignature(0, nargs)..'>* clone(void)=0;\n'
	output = output..tabs(2)..		'virtual Connection<'..CW.templateArgumentsSignature(0, nargs)..'>* duplicate(Receiver* receiver)=0;\n'
	output = output..tabs(2)..		'virtual Receiver* getReceiver(void) const=0;\n'
	output = output..tabs(2)..		'virtual void transmit('..CW.templateArgumentsSignature(0, nargs)..') const=0;\n'
	output = output..tabs(1)..	'};\n'
	output = output..tabs(1)..	'template< class RECEIVER, '..CW.templateArguments(0, nargs)..'>\n'
	output = output..tabs(1)..	'class volatile'..nargs..'\n'
	output = output..tabs(1)..	'{\n'
	output = output..tabs(1)..	'public:\n'
	output = output..tabs(2)..		'volatile'..nargs..'(void)\n'
	output = output..tabs(2)..		': m_object(NULL)\n'
	output = output..tabs(2)..		', m_function(NULL)\n'
	output = output..tabs(2)..		'{}\n'
	output = output..tabs(2)..		'volatile'..nargs..'(RECEIVER* object, void (RECEIVER::* function)'..CW.templateArgumentsSignature(0, nargs)..'))\n'
	output = output..tabs(2)..		': m_object(object)\n'
	output = output..tabs(2)..		', m_function(function)\n'
	output = output..tabs(2)..		'{}\n'
	output = output..tabs(2)..		'virtual Connection* clone(void)\n'
	output = output..tabs(2)..		'{\n'
	output = output..tabs(3)..			'return new volatile'..nargs..'<RECEIVER, '..CW.templateArgumentsSignature(0, nargs)..'>(*this);\n'
	output = output..tabs(2)..		'}\n'
	output = output..tabs(2)..		'virtual Connection* duplicate(void)\n'
	output = output..tabs(2)..		'{\n'
	output = output..tabs(3)..			'return new volatile'..nargs..'<RECEIVER, '..CW.templateArgumentsSignature(0, nargs)..'>(static_cast<RECEIVER*>(receiver), m_function);\n'
	output = output..tabs(2)..		'}\n'
	output = output..tabs(2)..		'virtual Receiver* getReceiver(void) const\n'
	output = output..tabs(2)..		'{\n'
	output = output..tabs(3)..			'return m_object;\n'
	output = output..tabs(2)..		'}\n'
	output = output..tabs(2)..		'virtual void transmit('..CW.templateCallSignature(0, nargs)..') const\n'
	output = output..tabs(2)..		'{\n'
	output = output..tabs(3)..			'(m_object->*m_function)('..CW.templateFunctionCallArguments(0, nargs)..');\n'
	output = output..tabs(2)..		'}\n'
	output = output..tabs(1)..	'private:\n'
	output = output..tabs(2)..		'RECEIVER* m_object;\n'
	output = output..tabs(2)..		'void (RECEIVER::* m_function)('..CW.templateArgumentsSignature(0, nargs)..');\n'
	output = output..tabs(1)..	'}\n'
	output = output..tabs(1)..	'template<class RECEIVER, '..CW.templateArguments(0, nargs)..'>\n'
	output = output..tabs(1)..	'class const'..nargs..'\n'
	output = output..tabs(1)..	': public Connection<'..CW.templateArgumentsSignature(0, nargs)..'>\n'
	output = output..tabs(1)..	'{\n'
	output = output..tabs(1)..	'public:\n'
	output = output..tabs(2)..		'const'..nargs..'(void)\n'	
	output = output..tabs(2)..		': m_object(NULL)\n'
	output = output..tabs(2)..		', m_function(NULL)\n'
	output = output..tabs(2)..		'{}\n'
	output = output..tabs(2)..		''
	
--[[	
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
--]]
	myFile:write(output)
end
function writeToFile(myFile, nargs)
	for i=1,nargs do
		writeClassBasedOnNumberOfArguments(myFile, i)
		myFile:write('\n\n\n\n')
	end
	myFile:flush()
end