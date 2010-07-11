/**
 * \file CTcpSocket.h
 * \date Mar 8, 2010
 * \author samael
 */

#ifndef CTCPSOCKET_H_
#define CTCPSOCKET_H_

#include <vector>
#include "ASocket.h"

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
class CTcpSocket: public ASocket
{
public:
	CTcpSocket(): _autoclean(true), _ssocks() {}
	CTcpSocket(int sock): ASocket(sock), _autoclean(true), _ssocks() {}
	~CTcpSocket() throw();
	CTcpSocket* accept();
	inline bool autoclean() const { return _autoclean; }
	inline void setAutoclean(bool ac) { _autoclean = ac; }
	inline const std::vector<CTcpSocket *>& slaveSockets() const
			{ return _ssocks; }

private:
	bool _autoclean;
	std::vector<CTcpSocket *> _ssocks;
};

}

#endif /* CTCPSOCKET_H_ */
