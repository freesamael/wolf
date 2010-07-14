/**
 * \file testtcpclient.cpp
 * \date Mar 30, 2010
 * \author samael
 */

#include <iostream>
#include <CTcpQueuedSocket.h>
#include <CTcpDataReader.h>
#include <CHostAddress.h>
#include <CThread.h>

using namespace std;
using namespace cml;

class ReadingThread: public CThread
{
public:
	ReadingThread(CTcpSocket &c): _done(false), _conn(c) {}
	void setDone(bool d = true) { _done = d; }
	void run()
	{
		char d[1500];
		while (!_done) {
			int sz;
			if ((sz = _conn.read(d, 1500)) > 0) {
				for (int i = 0; i < sz; i++)
					if (d[i] != (char)0xaa)
						cerr << "Error: d = " << hex << (int)d[i] << endl;
			}
		}
	}

private:
	bool _done;
	CTcpSocket &_conn;
};

int main(int argc, char *argv[])
{
	if (argc != 2)
		cerr << "Usage: " << argv[0] << " <addr>" << endl;

	char c[1500];
	for (int i = 0; i < 1500; i++)
		c[i] = 0x55;

	CQueuedTcpSocket conn;
	conn.activeOpen(argv[1], 5566);

	CQueuedTcpDataReader reader;
	reader.addSocket(&conn);
	CThread rdthread(&reader);
	rdthread.start();

	ReadingThread reading(conn);
	reading.start();

	CTime st = CTime::now();
	unsigned bytecount = 0;
	while ((CTime::now() - st) < CTime(10, 0))
		bytecount += conn.write(c, 1500);
	reader.setDone();
	rdthread.join();
	reading.setDone();
	reading.join(1000000);

	cout << "Bandwidth = " << ((double)bytecount * 8 / 10 / 1048576) << " Mbps" << endl;
    return 0;
}
