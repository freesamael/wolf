/**
 * \file testtcp.h
 * \date Jul 15, 2010
 * \author samael
 */

#ifndef TESTTCP_H_
#define TESTTCP_H_

#include <CTcpSocket.h>
#include <CTime.h>

class ReadingThread: public CThread
{
public:
	ReadingThread(cml::CTcpSocket &c, char d):
		_done(false), _conn(c), _bc(0), _data(d) {}
	unsigned bytecount() { return _bc; }
	CTime tstart() { return _tstart; }
	void setDone(bool d = true) { _done = d; }
	void run()
	{
		char *d = new char[SZ_BUF];
		int sz;
		int count = 0;
		while ((sz = _conn.read(d, SZ_BUF)) > 0) {
			if (count == 0)
				_tstart = cml::CTime::now();
			for (int i = 0; i < sz; i++)
				if (d[i] != _data)
					cerr << "Error: d = " << hex << (int)d[i] << endl;
			_bc += sz;
			count++;
		}
		delete [] d;
	}

private:
	bool _done;
	cml::CTcpSocket &_conn;
	unsigned _bc;
	char _data;
	CTime _tstart;
};

#endif /* TESTTCP_H_ */
