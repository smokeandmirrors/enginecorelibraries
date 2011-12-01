#include "Platform.h"
#if WITH_UNIT_TESTING	
#include <cfixcc.h>
#include "Signals.h"

using namespace signals;

static const sint value1(1);
static const sint value2(2);

class TestReceiverBase 
: public ReceiverBase
{
public:
	TestReceiverBase(void)
	: m_0ReceptionCount(0)
	, m_0ConstReceptionCount(0)
	, m_1ReceptionCount(0)
	, m_1ConstReceptionCount(0)
	, m_2ReceptionCount(0)
	, m_2ConstReceptionCount(0)
	{

	}

	void increment0ReceptionCount(void)
	{
		++m_0ReceptionCount;
	}

	void increment0ConstReceptionCount(void)
	{
		++m_0ConstReceptionCount;
	}

	void increment1ReceptionCount(sint count1)
	{
		CFIXCC_ASSERT_EQUALS(value1, count1); 
		++m_1ReceptionCount;
	}

	void increment1ConstReceptionCount(sint count1)
	{
		CFIXCC_ASSERT_EQUALS(value1, count1); 
		++m_1ConstReceptionCount;
	}

	void increment2ReceptionCount(sint count1, sint count2)
	{
		CFIXCC_ASSERT_EQUALS(value1, count1); 
		CFIXCC_ASSERT_EQUALS(value2, count2); 
		++m_2ReceptionCount;
	}

	void increment2ConstReceptionCount(sint count1, sint count2)
	{
		CFIXCC_ASSERT_EQUALS(value1, count1); 
		CFIXCC_ASSERT_EQUALS(value2, count2); 
		++m_2ConstReceptionCount;
	}	
	
	sint get0ReceptionCount(void) const
	{
		return m_0ReceptionCount;
	}

	sint get0ConstReceptionCount(void) const
	{
		return m_0ConstReceptionCount;
	}

	sint get1ReceptionCount(void) const
	{
		return m_1ReceptionCount;
	}

	sint get1ConstReceptionCount(void) const
	{
		return m_1ConstReceptionCount;
	}

	sint get2ReceptionCount(void) const
	{
		return m_2ReceptionCount;
	}

	sint get2ConstReceptionCount(void) const
	{
		return m_2ConstReceptionCount;
	}

private:
	mutable sint m_0ReceptionCount;
	mutable sint m_0ConstReceptionCount;
	mutable sint m_1ReceptionCount;
	mutable sint m_1ConstReceptionCount;
	mutable sint m_2ReceptionCount;
	mutable sint m_2ConstReceptionCount;
};

class TestReceiverMember
: public Receiver
{
public:
	TestReceiverMember(void)
	: m_0ReceptionCount(0)
	, m_0ConstReceptionCount(0)
	, m_1ReceptionCount(0)
	, m_1ConstReceptionCount(0)
	, m_2ReceptionCount(0)
	, m_2ConstReceptionCount(0)
	{
		m_receiver.setReceiver(this);
	}

	void ceaseReception(void)
	{
		m_receiver.ceaseReception();
	}

	void increment0ReceptionCount(void)
	{
		++m_0ReceptionCount;
	}

	void increment0ConstReceptionCount(void)
	{
		++m_0ConstReceptionCount;
	}

	void increment1ReceptionCount(sint count1)
	{
		CFIXCC_ASSERT_EQUALS(value1, count1); 
		++m_1ReceptionCount;
	}

	void increment1ConstReceptionCount(sint count1)
	{
		CFIXCC_ASSERT_EQUALS(value1, count1); 
		++m_1ConstReceptionCount;
	}

	void increment2ReceptionCount(sint count1, sint count2)
	{
		CFIXCC_ASSERT_EQUALS(value1, count1); 
		CFIXCC_ASSERT_EQUALS(value2, count2); 
		++m_2ReceptionCount;
	}

	void increment2ConstReceptionCount(sint count1, sint count2)
	{
		CFIXCC_ASSERT_EQUALS(value1, count1); 
		CFIXCC_ASSERT_EQUALS(value2, count2); 
		++m_2ConstReceptionCount;
	}	
	
	sint get0ReceptionCount(void) const
	{
		return m_0ReceptionCount;
	}

	sint get0ConstReceptionCount(void) const
	{
		return m_0ConstReceptionCount;
	}

	sint get1ReceptionCount(void) const
	{
		return m_1ReceptionCount;
	}

	sint get1ConstReceptionCount(void) const
	{
		return m_1ConstReceptionCount;
	}

	sint get2ReceptionCount(void) const
	{
		return m_2ReceptionCount;
	}

	sint get2ConstReceptionCount(void) const
	{
		return m_2ConstReceptionCount;
	}
	
	void onConnect(signals::Transmitter* sender)
	{
		m_receiver.onConnect(sender);
	}

	void onDisconnect(signals::Transmitter* sender)
	{
		m_receiver.onDisconnect(sender);
	}

private:
	mutable sint m_0ReceptionCount;
	mutable sint m_0ConstReceptionCount;
	mutable sint m_1ReceptionCount;
	mutable sint m_1ConstReceptionCount;
	mutable sint m_2ReceptionCount;
	mutable sint m_2ConstReceptionCount;
	signals::ReceiverMember
		m_receiver;
};

class UTSignals : public cfixcc::TestFixture
{
private:

public:
	void SignalsTest1()
	{
		Transmitter0 t0;
		Transmitter1<sint> t1;
		Transmitter2<sint, sint> t2;
		
		TestReceiverBase trb;
		TestReceiverMember trm;
	
		t0.connect(&trb, &TestReceiverBase::increment0ReceptionCount);
		t1.connect(&trb, &TestReceiverBase::increment1ReceptionCount);
		t2.connect(&trb, &TestReceiverBase::increment2ReceptionCount);
		
		t0.transmit();
		t1.transmit(value1);
		t2.transmit(value1, value2);

		CFIXCC_ASSERT_EQUALS(trb.get0ConstReceptionCount(), 0);
		CFIXCC_ASSERT_EQUALS(trb.get0ReceptionCount(), 1);
		CFIXCC_ASSERT_EQUALS(trb.get1ConstReceptionCount(), 0);
		CFIXCC_ASSERT_EQUALS(trb.get1ReceptionCount(), 1);
		CFIXCC_ASSERT_EQUALS(trb.get2ConstReceptionCount(), 0);
		CFIXCC_ASSERT_EQUALS(trb.get2ReceptionCount(), 1);
		
		t0.disconnect(&trb);
		t1.disconnect(&trb);
		t2.disconnect(&trb);

		t0.connect(&trb, &TestReceiverBase::increment0ConstReceptionCount);
		t1.connect(&trb, &TestReceiverBase::increment1ConstReceptionCount);
		t2.connect(&trb, &TestReceiverBase::increment2ConstReceptionCount);

		t0.transmit();
		t1.transmit(value1);
		t2.transmit(value1, value2);

		CFIXCC_ASSERT_EQUALS(trb.get0ConstReceptionCount(), 1);
		CFIXCC_ASSERT_EQUALS(trb.get0ReceptionCount(), 1);
		CFIXCC_ASSERT_EQUALS(trb.get1ConstReceptionCount(), 1);
		CFIXCC_ASSERT_EQUALS(trb.get1ReceptionCount(), 1);
		CFIXCC_ASSERT_EQUALS(trb.get2ConstReceptionCount(), 1);
		CFIXCC_ASSERT_EQUALS(trb.get2ReceptionCount(), 1);
	}
};

CFIXCC_BEGIN_CLASS(UTSignals)
	CFIXCC_METHOD(SignalsTest1)
CFIXCC_END_CLASS()

#endif//WITH_UNIT_TESTING
