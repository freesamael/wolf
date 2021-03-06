/**
 * \file CQueuedTcpSocket.cpp
 * \date Jul 13, 2010
 * \author samael
 */

#include "CQueuedTcpSocket.h"
#include <algorithm>
#define SZ_TRUNK	1500
#define SZ_QFULL	524288

using namespace std;

namespace wolf
{

/**
 * Read data from queue.
 * \return
 * Size read. Zero indicates connection ends (end-of-file).
 */
ssize_t CQueuedTcpSocket::read(char *buf, size_t size)
{
	size_t offset = 0;
	while (offset < size && state()->name() != ASocket::ClosedState) {
		_mx.lock();
		// Wait if no data and not disconnected yet.
		if (_q.empty() && state()->name() != ASocket::ClosedState)
			_cond.wait(&_mx);
		// Check again after waked up.
		if (!_q.empty()) {
			buf[offset++] = _q.front();
			_q.pop_front();
		}
		_mx.unlock();
	}

	// Return zero on connection ends.
	if (state()->name() == ASocket::ClosedState)
		return 0;
	return offset;
}

/**
 * Read raw socket and push data into the queue.
 */
void CQueuedTcpSocket::readSocket()
{
	if (_q.size() < SZ_QFULL) {
		// Read as much data as possible.
		ssize_t sz;
		char *data = new char[SZ_TRUNK];
		try {
			if ((sz = CTcpSocket::read(data, min(SZ_TRUNK, SZ_QFULL))) > 0) {
				_mx.lock();
				for (int i = 0; i < sz; i++)
					_q.push_back(data[i]);
				if (_q.size() == (unsigned)sz)
					_cond.wakeAll();
				_mx.unlock();
			}
		} catch (XSocket &x) {
			delete data;
			throw;
		}
		delete data;

		// Wake up all readers if end-of-file.
		if (sz == 0 && state()->name() == ASocket::ClosedState) {
			_mx.lock();
			_cond.wakeAll();
			_mx.unlock();
		}
	}
}

ssize_t CQueuedTcpSocket::write(const char *buf, size_t size)
{
	ssize_t sz = 0;
	do {
		sz += state()->write(this, buf + sz, size - sz);
	} while ((unsigned)sz < (unsigned)size);
	return sz;
}

void CQueuedTcpSocket::close()
{
	CTcpSocket::close();
	_mx.lock();
	_cond.wakeAll();
	_mx.unlock();
}

}
