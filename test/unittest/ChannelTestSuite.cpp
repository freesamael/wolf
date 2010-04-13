/**
 * \file ChannelTestSuite.cpp
 * \date Apr 13, 2010
 * \author samael
 */

#include "ChannelTestSuite.h"
#include "Channel.h"
#include "SinkPort.h"

CPPUNIT_TEST_SUITE_REGISTRATION(ChannelTestSuite);

using namespace wfe;

class CloneDrop: public IDrop
{
public:
	const IDrop *original;
	CloneDrop(const IDrop *orig): original(orig) {}
	IDrop* clone() const { return NULL; }
};

class FakeDrop: public IDrop
{
public:
	IDrop* clone() const { return new CloneDrop(this); }
};

void ChannelTestSuite::testAttachDetach()
{
	SinkPort p1(NULL), p2(NULL), p3(NULL);
	Channel ch;

	ch.attachReader(&p1);
	ch.attachReader(&p2);
	ch.attachReader(&p3);
	ch.attachReader(&p3);
	ch.attachReader(&p2);
	ch.attachReader(&p1);

	CPPUNIT_ASSERT_EQUAL(3, (int)ch.readers().size());
	CPPUNIT_ASSERT_EQUAL((void *)&p1, (void *)ch.readers()[0]);
	CPPUNIT_ASSERT_EQUAL((void *)&p2, (void *)ch.readers()[1]);
	CPPUNIT_ASSERT_EQUAL((void *)&p3, (void *)ch.readers()[2]);

	ch.detachReader(&p1);
	ch.detachReader(&p2);
	CPPUNIT_ASSERT_EQUAL(1, (int)ch.readers().size());
	CPPUNIT_ASSERT_EQUAL((void*)&p3, (void*)ch.readers()[0]);
}

void ChannelTestSuite::testWrite()
{
	SinkPort p1(NULL), p2(NULL);
	FakeDrop d1, d2, d3, d4;
	Channel ch;

	ch.attachReader(&p1);
	ch.attachReader(&p2);
	ch.write(&d1);
	ch.write(&d2);
	ch.write(&d3);
	ch.write(&d4);

	CloneDrop *d = (CloneDrop *)p1.readPort();
	CPPUNIT_ASSERT_EQUAL((void *)&d1, (void *)d->original);
	CPPUNIT_ASSERT_EQUAL((void *)&d1, (void *)p2.readPort());
	delete d;

	d = (CloneDrop *)p1.readPort();
	CPPUNIT_ASSERT_EQUAL((void *)&d2, (void *)d->original);
	CPPUNIT_ASSERT_EQUAL((void *)&d2, (void *)p2.readPort());
	delete d;

	d = (CloneDrop *)p1.readPort();
	CPPUNIT_ASSERT_EQUAL((void *)&d3, (void *)d->original);
	CPPUNIT_ASSERT_EQUAL((void *)&d3, (void *)p2.readPort());
	delete d;

	d = (CloneDrop *)p1.readPort();
	CPPUNIT_ASSERT_EQUAL((void *)&d4, (void *)d->original);
	CPPUNIT_ASSERT_EQUAL((void *)&d4, (void *)p2.readPort());
	delete d;
}
