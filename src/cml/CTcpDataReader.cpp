/**
 * \file CTcpDataReader.cpp
 * \date Jul 12, 2010
 * \author samael
 */

#include <errno.h>
#include <sys/select.h>
#include <sys/resource.h>
#include "CTcpDataReader.h"
#include "CTime.h"

using namespace std;

namespace cml
{

CTcpDataReader::CTcpDataReader():
		_done(false), _mx(), _socks()
{

}

CTcpDataReader::~CTcpDataReader()
{

}

/**
 * Add a socket to the watching list. If checks for duplicates.
 * If the running loop has already started, it takes effect in the next loop.
 */
void CTcpDataReader::addSocket(CTcpQueuedSocket *sock)
{
	if (sock) {
		_mx.lock();
		if (_socks.find(sock->sockfd()) == _socks.end()) {
			_socks[sock->sockfd()] = sock;
		}
		_mx.unlock();
	}
}

/**
 * Remove a socket from the watching list. Taking effect in the next loop if
 * it has started.
 */
void CTcpDataReader::removeSocket(CTcpQueuedSocket *sock)
{
	if (sock) {
		map<int, CTcpQueuedSocket *>::iterator iter;
		_mx.lock();
		if ((iter = _socks.find(sock->sockfd())) != _socks.end()) {
			_socks.erase(iter);
		}
		_mx.unlock();
	}
}

void CTcpDataReader::run()
{
	// Get limits.
	rlimit r;
	if (getrlimit(RLIMIT_NOFILE, &r) == -1) {
		throw XSocket(__PRETTY_FUNCTION__, __LINE__, errno);
	}
	int nfds = (int)r.rlim_cur;

	timeval timeout = CTime(10000).toTimeval();
	map<int, CTcpQueuedSocket *>::iterator iter;
	while (!isDone()) {
		// Initialize fdset.
		fd_set readfds;
		FD_ZERO(&readfds);
		_mx.lock();
		for (iter = _socks.begin(); iter != _socks.end(); iter++)
			FD_SET(iter->first, &readfds);
		_mx.unlock();

		if (select(nfds, &readfds, NULL, NULL, &timeout) == -1) {
			throw XSocket(__PRETTY_FUNCTION__, __LINE__, errno);
		} else {
			// Update all ready sockets.
			_mx.lock();
			for (iter = _socks.begin(); iter != _socks.end(); iter++) {
				if (FD_ISSET(iter->first, &readfds)) {
					iter->second->readSocket();
				}
			}
			_mx.unlock();
		}
	}
}

}
