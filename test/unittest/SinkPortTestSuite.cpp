/**
 * \file SinkPortTestSuite.cpp
 * \date Apr 13, 2010
 * \author samael
 */

#include "SinkPortTestSuite.h"
#include "SinkPort.h"

CPPUNIT_TEST_SUITE_REGISTRATION(SinkPortTestSuite);

using namespace wfe;

class FakeDrop: public IDrop
{
public:
	IDrop* clone() const { return NULL; }
};

void SinkPortTestSuite::testWriteReadPort()
{
	SinkPort port(NULL);
	FakeDrop a, b, c;
	CPPUNIT_ASSERT_EQUAL((void *)NULL, (void *)port.readPort());

	port.writePort(&a);
	CPPUNIT_ASSERT_EQUAL((void *)&a, (void *)port.readPort());
	CPPUNIT_ASSERT_EQUAL((void *)NULL, (void *)port.readPort());

	port.writePort(&a);
	port.writePort(&b);
	port.writePort(&c);
	CPPUNIT_ASSERT_EQUAL((void *)&a, (void *)port.readPort());
	CPPUNIT_ASSERT_EQUAL((void *)&b, (void *)port.readPort());
	CPPUNIT_ASSERT_EQUAL((void *)&c, (void *)port.readPort());
	CPPUNIT_ASSERT_EQUAL((void *)NULL, (void *)port.readPort());
}
