/**
 * \file UDPSocketTestSuite.cpp
 * \date Apr 6, 2010
 * \author samael
 */

#include <cstring>
#include <string>
#include <CThread.h>
#include <CUdpSocket.h>
#include "UDPSocketTestSuite.h"

using namespace std;
using namespace wolf;

CPPUNIT_TEST_SUITE_REGISTRATION(UDPSocketTestSuite);

void UDPSocketTestSuite::testSendtoRecvfrom()
{
	CUdpSocket server, client;

	CPPUNIT_ASSERT_EQUAL((string)"Active", server.state()->name());
	CPPUNIT_ASSERT_EQUAL((string)"Active", client.state()->name());
	server.passiveOpen(5566);
	CPPUNIT_ASSERT_EQUAL((string)"Bound", server.state()->name());

	CHostAddress addr;
	unsigned short port;
	const char *ostr = "Hello World";
	char istr[20];
	CPPUNIT_ASSERT_EQUAL(12, (int)client.sendto(ostr, 12, "127.0.0.1", 5566));
	CPPUNIT_ASSERT_EQUAL(12, (int)server.recvfrom(istr, 20, &addr, &port));
	CPPUNIT_ASSERT_EQUAL((string)ostr, (string)istr);

	server.close();
	client.close();
	CPPUNIT_ASSERT_EQUAL((string)"Closed", server.state()->name());
	CPPUNIT_ASSERT_EQUAL((string)"Closed", client.state()->name());
}

void UDPSocketTestSuite::testReadWrite()
{
	CUdpSocket server, client;

	CPPUNIT_ASSERT_EQUAL((string)"Active", server.state()->name());
	CPPUNIT_ASSERT_EQUAL((string)"Active", client.state()->name());
	server.passiveOpen(7788);
	CPPUNIT_ASSERT_EQUAL((string)"Bound", server.state()->name());
	client.activeOpen("127.0.0.1", 7788);
	CPPUNIT_ASSERT_EQUAL((string)"Connected", client.state()->name());

	CHostAddress addr;
	unsigned short port;
	const char *str = "Hello World";
	char sstr[20], cstr[20];
	CPPUNIT_ASSERT_EQUAL(12, (int)client.write(str, 12));
	CPPUNIT_ASSERT_EQUAL(12, (int)server.recvfrom(sstr, 20, &addr, &port));
	CPPUNIT_ASSERT_EQUAL(12, (int)server.sendto(sstr, 12, addr, port));
	CPPUNIT_ASSERT_EQUAL(12, (int)client.read(cstr, 20));

	server.close();
	client.close();
	CPPUNIT_ASSERT_EQUAL((string)"Closed", server.state()->name());
	CPPUNIT_ASSERT_EQUAL((string)"Closed", client.state()->name());
}
