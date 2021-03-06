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
	ReadingThread(wolf::CTcpSocket &c, char d):
		_conn(c), _bc(0), _data(d), _tstart(wolf::CTime::now()) {}
	unsigned bytecount() { return _bc; }
	CTime tstart() { return _tstart; }
	CTime tend() { return _tend; }
	void run()
	{
		char *d = new char[SZ_BUF];
		int sz;
		int count = 0;
		while ((sz = _conn.read(d, SZ_BUF)) > 0) {
			_tend = wolf::CTime::now();
			if (count == 0)
				_tstart = wolf::CTime::now();
			for (int i = 0; i < sz; i++)
				if (d[i] != _data)
					cerr << "Error: d = " << hex << (int)d[i] << endl;
			_bc += sz;
			count++;
		}
		delete [] d;
	}

private:
	wolf::CTcpSocket &_conn;
	unsigned _bc;
	char _data;
	CTime _tstart;
	CTime _tend;
};

#endif /* TESTTCP_H_ */
