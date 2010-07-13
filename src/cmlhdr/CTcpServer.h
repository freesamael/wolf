/**
 * \file CTcpServer.h
 * \date Jul 13, 2010
 * \author samael
 */

#ifndef CTCPSERVER_H_
#define CTCPSERVER_H_

#include <vector>
#include "CTcpSocket.h"

namespace cml
{

class CTcpServer: public CTcpSocket
{
public:
	typedef enum SlaveType {
		DIRECT,
		QUEUED
	} SlaveType;
	CTcpServer() throw(XSocket, XThread): _ac(true), _ssocks() {}
	CTcpServer(int sock) throw(XSocket, XThread): CTcpSocket(sock), _ac(true),
			_ssocks() {}
	~CTcpServer() throw();
	inline void passiveOpen(in_port_t port, int qlen = 10, bool reuse = false)
			throw(XSocket)
			{ state()->passiveOpen(this, ISocketState::TCP, port, qlen, reuse); }
	CTcpSocket* accept(SlaveType type = DIRECT) throw(XSocket);
	inline void setAutoclean(bool ac) throw() { _ac = ac; }
	inline bool autoclean() const throw() { return _ac; }

private:
	bool _ac;
	std::vector<CTcpSocket *> _ssocks;
};

}

#endif /* CTCPSERVER_H_ */
