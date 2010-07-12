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
 * CTcpSocket represents TCP sockets. If a CTcpSocket is created by accept(),
 * it's managed by the master socket who creates it, and the master socket will
 * destroy it on destruction of the master socket. You can use
 * setAutoclean(false) to explicitly avoid master socket deleting slaves
 * automatically.
 *
 * \see ASocket
 */
class CTcpSocket: public ASocket
{
public:
	CTcpSocket() throw(XSocket, XThread): _autoclean(true), _ssocks() {}
	CTcpSocket(int sock) throw(XSocket, XThread):
			ASocket(sock), _autoclean(true), _ssocks() {}
	~CTcpSocket() throw();
	CTcpSocket* accept() throw(XSocket);
	inline bool autoclean() const throw() { return _autoclean; }
	inline void setAutoclean(bool ac) throw() { _autoclean = ac; }
	inline const std::vector<CTcpSocket *>& slaveSockets() const throw()
			{ return _ssocks; }

private:
	bool _autoclean;
	std::vector<CTcpSocket *> _ssocks;
};

}

#endif /* CTCPSOCKET_H_ */
