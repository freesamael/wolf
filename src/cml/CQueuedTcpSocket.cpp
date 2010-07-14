/**
 * \file CTcpQueuedSocket.cpp
 * \date Jul 13, 2010
 * \author samael
 */

#include "CTcpQueuedSocket.h"

#define SZ_TRUNK	1500

namespace cml
{

/**
 * Read data from queue.
 * \return
 * Size read. Zero indicates connection ends (end-of-file).
 */
ssize_t CQueuedTcpSocket::read(char *buf, size_t size) throw(XSocket)
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
void CQueuedTcpSocket::readSocket() throw(XSocket)
{
	// Set non-blocking if needed.
	bool b = blockable();
	if (b)
		setBlockable(false);

	// Read as much data as possible.
	ssize_t sz;
	char *data = new char[SZ_TRUNK];
	try {
		if ((sz = CTcpSocket::read(data, SZ_TRUNK)) > 0) {
			_mx.lock();
			for (int i = 0; i < sz; i++)
				_q.push_back(data[i]);
			if (_q.size() == (unsigned)sz)
				_cond.wakeAll();
			_mx.unlock();
		}
	} catch (const XSocket &x) {
		delete data;
		throw x;
	}
	delete data;

	// Wake up all readers if end-of-file.
	if (sz == 0 && state()->name() == ASocket::ClosedState) {
		_mx.lock();
		_cond.wakeAll();
		_mx.unlock();
	}

	// Restore blockable state.
	if (b)
		setBlockable(true);
}

void CQueuedTcpSocket::close() throw(XSocket)
{
	CTcpSocket::close();
	_mx.lock();
	_cond.wakeAll();
	_mx.unlock();
}

}
