/**
 * \file TCPSocket.h
 * \date Mar 8, 2010
 * \author samael
 */

#ifndef TCPSOCKET_H_
#define TCPSOCKET_H_

#include <vector>
#include "AbstractSocket.h"

namespace cml
{

/**
 * TCP sockets representation. If a TCPSocket is created by accept(), it's
 * managed by the master socket who creates it, and the master socket will
 * destroy it on destruction of the master socket. You can use
 * setAutoclean(false) to explicitly avoid master socket deleting slaves
 * automatically.
 *
 * \see AbstractSocket
 */
class TCPSocket: public AbstractSocket
{
public:
	TCPSocket(): _autoclean(true), _ssocks() {}
	TCPSocket(int sock): AbstractSocket(sock), _autoclean(true), _ssocks() {}
	~TCPSocket();
	TCPSocket* accept();
	inline bool autoclean() const { return _autoclean; }
	inline void setAutoclean(bool ac) { _autoclean = ac; }
	inline const std::vector<TCPSocket *>& slaveSockets() const
			{ return _ssocks; }

private:
	bool _autoclean;
	std::vector<TCPSocket *> _ssocks;
};

}

#endif /* TCPSOCKET_H_ */
