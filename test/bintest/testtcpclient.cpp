/**
 * \file testtcpclient.cpp
 * \date Mar 30, 2010
 * \author samael
 */

#include <iostream>
#include <CQueuedTcpSocket.h>
#include <CQueuedTcpDataReader.h>
#include <CHostAddress.h>
#include <CThread.h>

using namespace std;
using namespace cml;

class ReadingThread: public CThread
{
public:
	ReadingThread(CTcpSocket &c): _done(false), _conn(c), _bc(0) {}
	unsigned bytecount() { return _bc; }
	void setDone(bool d = true) { _done = d; }
	void run()
	{
		char d[1500];
		int sz;
		while ((sz = _conn.read(d, 1500)) > 0) {
			for (int i = 0; i < sz; i++)
				if (d[i] != (char)0xaa)
					cerr << "Error: d = " << hex << (int)d[i] << endl;
			_bc += sz;
		}
	}

private:
	bool _done;
	CTcpSocket &_conn;
	unsigned _bc;
};

int main(int argc, char *argv[])
{
	if (argc != 2)
		cerr << "Usage: " << argv[0] << " <addr>" << endl;

	char c[1500];
	for (int i = 0; i < 1500; i++)
		c[i] = 0x55;

	CTcpSocket conn;
	conn.activeOpen(argv[1], 5566);

//	CQueuedTcpDataReader reader;
//	reader.addSocket(&conn);
//	CThread rdthread(&reader);
//	rdthread.start();

	ReadingThread reading(conn);
	reading.start();

	CTime st = CTime::now();
	unsigned bytecount = 0;
	while ((CTime::now() - st) < CTime(4, 0)) {
		bytecount += conn.write(c, 1500);
	}
//	conn.close();

	cout << "Sent " << bytecount << " bytes." << endl;
	cout << "Sending rate = " << ((double)bytecount * 8 / 4 / 1048576) << " Mbps" << endl;

//	reader.setDone();
//	rdthread.join();
	reading.setDone();
	reading.join();

	cout << "Received " << reading.bytecount() << " bytes." << endl;
	cout << "Receiving rate = " << ((double)reading.bytecount() * 8 / 4 / 1048576) << " Mbps" << endl;
    return 0;
}
