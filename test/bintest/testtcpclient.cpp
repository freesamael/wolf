/**
 * \file testtcpclient.cpp
 * \date Mar 30, 2010
 * \author samael
 */

#include <iostream>
#include <CTcpSocket.h>
#include <CHostAddress.h>
#include <CThread.h>

using namespace std;
using namespace cml;

#define SZ_BUF	8500
#define T_SEND	4

#include "testtcp.h"

int main(int argc, char *argv[])
{
	if (argc != 2)
		cerr << "Usage: " << argv[0] << " <addr>" << endl;

	char *c = new char[SZ_BUF];
	for (int i = 0; i < SZ_BUF; i++)
		c[i] = (char)0x55;

	CTcpSocket conn;
	conn.activeOpen(argv[1], 5566);

	ReadingThread reading(conn, (char)0xaa);
	reading.start();

	CTime st = CTime::now();
	unsigned bytecount = 0;
	while ((CTime::now() - st) < CTime(T_SEND, 0)) {
		bytecount += conn.write(c, SZ_BUF);
	}
	CTime sendtime = CTime::now() - st;
	cout << "Sent " << bytecount << " bytes." << endl;
	cout << "Sending rate = " << ((double)bytecount * 8 / 1048576 * 1000000 / sendtime.toMicroseconds()) << " Mbps" << endl;

	reading.setDone();
	reading.join();
	CTime recvtime = CTime::now() - reading.tstart();
	cout << "Received " << reading.bytecount() << " bytes." << endl;
	cout << "Receiving rate = " << ((double)reading.bytecount() * 8 / 1048576 * 1000000 / recvtime.toMicroseconds()) << " Mbps" << endl;

	delete [] c;
    return 0;
}
