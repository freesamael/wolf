/**
 * \file testtcpserver.cpp
 * \date Mar 30, 2010
 * \author samael
 */

#include <iostream>
#include <CTcpServer.h>
#include <CTcpDataReader.h>
#include <CTime.h>
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
					if (d[i] != (char)0x55)
						cerr << "Error: d = " << hex << (int)d[i] << endl;
			}
		}
	}

private:
	bool _done;
	CTcpSocket &_conn;
};


int main()
{
	CTcpServer server;
	server.passiveOpen(5566, 10, true);

	char c[1500];
	for (int i = 0; i < 1500; i++)
		c[i] = 0xaa;

	CTcpSocket *conn = server.accept(CTcpServer::QUEUED);

	CTcpDataReader reader;
	reader.addSocket(dynamic_cast<CTcpQueuedSocket *>(conn));
	CThread rdthread(&reader);
	rdthread.start();

	ReadingThread reading(*conn);
	reading.start();

	unsigned bytecount = 0;
	CTime st = CTime::now();
	while ((CTime::now() - st) < CTime(10, 0)) {
		bytecount += conn->write(c, 1500);
	}

	reader.setDone();
	rdthread.join();
	reading.setDone();
	reading.join(1000000);

	cout << "Bandwidth = " << ((double)bytecount * 8 / 10 / 1048576) << " Mbps" << endl;
    return 0;
}
