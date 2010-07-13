/**
 * \file TCPSocketTestSuite.cpp
 * \date  Apr 6, 2010
 * \author samael
 */

#include <string>
#include <CThread.h>
#include <CTcpServer.h>
#include "TCPSocketTestSuite.h"

CPPUNIT_TEST_SUITE_REGISTRATION(TCPSocketTestSuite);

using namespace std;
using namespace cml;

struct Acceptor: public CThread
{
	CTcpServer *msock;
	CTcpSocket *ssock;
	Acceptor(CTcpServer *m): msock(m), ssock(NULL) {}
	void run() { ssock = msock->accept(); }
};

void TCPSocketTestSuite::testReadWrite()
{
	CTcpServer server;
	CTcpSocket client;
	Acceptor athread(&server);

	CPPUNIT_ASSERT_EQUAL((string)"Closed", server.state()->name());
	CPPUNIT_ASSERT_EQUAL((string)"Closed", client.state()->name());
	server.passiveOpen(6655);
	CPPUNIT_ASSERT_EQUAL((string)"Bound", server.state()->name());

	athread.start();
	client.activeOpen("127.0.0.1", 6655);
	CPPUNIT_ASSERT_EQUAL((string)"Connected", client.state()->name());
	athread.join();
	CPPUNIT_ASSERT_ASSERTION_FAIL(CPPUNIT_ASSERT_EQUAL((CTcpSocket *)NULL, athread.ssock));
	CPPUNIT_ASSERT_EQUAL((string)"Connected", athread.ssock->state()->name());

	const char *str = "Hello World";
	char sstr[20], cstr[20];
	CPPUNIT_ASSERT_EQUAL((ssize_t)12, client.write(str, 12));
	CPPUNIT_ASSERT_EQUAL((ssize_t)12, athread.ssock->read(sstr, 12));
	CPPUNIT_ASSERT_EQUAL((ssize_t)12, athread.ssock->write(sstr, 12));
	CPPUNIT_ASSERT_EQUAL((ssize_t)12, client.read(cstr, 12));
	CPPUNIT_ASSERT_EQUAL((string)str, (string)cstr);

	client.close();
	athread.ssock->close();
	server.close();
	CPPUNIT_ASSERT_EQUAL((string)"Closed", server.state()->name());
	CPPUNIT_ASSERT_EQUAL((string)"Closed", client.state()->name());
	CPPUNIT_ASSERT_EQUAL((string)"Closed", athread.ssock->state()->name());
}
