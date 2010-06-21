/**
 * \file AbstractActorTestSuite.cpp
 * \date Jun 21, 2010
 * \author samael
 */

#include "AbstractActorTestSuite.h"
#include "AbstractActor.h"

CPPUNIT_TEST_SUITE_REGISTRATION(AbstractActorTestSuite);

using namespace wfe;

class TestActor: public AbstractActor
{
public:
	void fire() {}
	State state() { return READY; }
};

void AbstractActorTestSuite::testAddRemovePort()
{
	TestActor t;

	IPort *p = t.addPort(IPort::SINK);
	CPPUNIT_ASSERT_EQUAL((size_t)1, t.sinkPorts().size());
	CPPUNIT_ASSERT_EQUAL(p, (IPort *)t.sinkPorts()[0]);

	p = t.addPort(IPort::SINK);
	CPPUNIT_ASSERT_EQUAL((size_t)2, t.sinkPorts().size());
	CPPUNIT_ASSERT_EQUAL(p, (IPort *)t.sinkPorts()[1]);

	p = t.addPort(IPort::SINK);
	CPPUNIT_ASSERT_EQUAL((size_t)3, t.sinkPorts().size());
	CPPUNIT_ASSERT_EQUAL(p, (IPort *)t.sinkPorts()[2]);

	p = t.addPort(IPort::SOURCE);
	CPPUNIT_ASSERT_EQUAL((size_t)1, t.sourcePorts().size());
	CPPUNIT_ASSERT_EQUAL(p, (IPort *)t.sourcePorts()[0]);

	p = t.addPort(IPort::SOURCE);
	CPPUNIT_ASSERT_EQUAL((size_t)2, t.sourcePorts().size());
	CPPUNIT_ASSERT_EQUAL(p, (IPort *)t.sourcePorts()[1]);

	p = t.addPort(IPort::SOURCE);
	CPPUNIT_ASSERT_EQUAL((size_t)3, t.sourcePorts().size());
	CPPUNIT_ASSERT_EQUAL(p, (IPort *)t.sourcePorts()[2]);

	t.removePort(t.sinkPorts()[0]);
	CPPUNIT_ASSERT_EQUAL((size_t)2, t.sinkPorts().size());

	t.removePort(t.sinkPorts()[0]);
	CPPUNIT_ASSERT_EQUAL((size_t)1, t.sinkPorts().size());

	t.removePort(t.sinkPorts()[0]);
	CPPUNIT_ASSERT_EQUAL((size_t)0, t.sinkPorts().size());

	t.removePort(t.sourcePorts()[0]);
	CPPUNIT_ASSERT_EQUAL((size_t)2, t.sourcePorts().size());

	t.removePort(t.sourcePorts()[0]);
	CPPUNIT_ASSERT_EQUAL((size_t)1, t.sourcePorts().size());

	t.removePort(t.sourcePorts()[0]);
	CPPUNIT_ASSERT_EQUAL((size_t)0, t.sourcePorts().size());
}
