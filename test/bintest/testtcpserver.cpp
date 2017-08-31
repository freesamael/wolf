/**
 * \file testtcpserver.cpp
 * \date Mar 30, 2010
 * \author samael
 */

#include <iostream>
#include <CTcpServer.h>
#include <CQueuedTcpDataReader.h>
#include <CTime.h>
#include <CThread.h>

using namespace std;
using namespace wolf;

#define SZ_BUF	1048576
#define T_SEND	8

#include "testtcp.h"

int main()
{
	CTcpServer server;
	server.passiveOpen(5566, 10, true);

	char *c = new char[SZ_BUF];
	for (int i = 0; i < SZ_BUF; i++)
		c[i] = (char)0xaa;

	CTcpSocket *conn = server.accept();

	ReadingThread reading(*conn, (char)0x55);
	reading.start();

	unsigned bytecount = 0;
	CTime st = CTime::now();
	while ((CTime::now() - st) < CTime(T_SEND, 0)) {
		bytecount += conn->write(c, SZ_BUF);
	}

	CTime sendtime = CTime::now() - st;
	reading.join(2000000);
	reading.cancel();
	CTime recvtime = reading.tend() - reading.tstart();

	cout << "Sent " << bytecount << " bytes in " << sendtime << "." << endl;
	cout << "Sending rate = " << ((double)bytecount * 8 / 1048576 * 1000000 / sendtime.toMicroseconds()) << " Mbps" << endl;
	cout << "Received " << reading.bytecount() << " bytes in " << recvtime << "." << endl;
	cout << "Receiving rate = " << ((double)reading.bytecount() * 8 / 1048576 * 1000000 / recvtime.toMicroseconds()) << " Mbps" << endl;

	conn->close();
	delete [] c;
	return 0;
}
