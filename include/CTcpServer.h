/**
 * \file CTcpServer.h
 * \date Jul 13, 2010
 * \author samael
 */

#ifndef CTCPSERVER_H_
#define CTCPSERVER_H_

#include <vector>
#include "CTcpSocket.h"

namespace wolf
{

/**
 * TCP server used to accept incoming connections. It manages the slave sockets
 * and will delete them on destruction unless autoclean is set to false.
 */
class CTcpServer: public CTcpSocket
{
public:
	typedef enum SlaveType {
		DIRECT,
		QUEUED
	} SlaveType;
	CTcpServer() : _ac(true), _ssocks() {}
	CTcpServer(int sock) : CTcpSocket(sock), _ac(true),
			_ssocks() {}
	~CTcpServer();
	inline void passiveOpen(in_port_t port, int qlen = 10, bool reuse = false)
			
			{ state()->passiveOpen(this, ISocketState::TCP, port, qlen, reuse); }
	CTcpSocket* accept(SlaveType type = DIRECT);
	inline void setAutoclean(bool ac)  { _ac = ac; }
	inline bool autoclean() const  { return _ac; }

private:
	bool _ac;
	std::vector<CTcpSocket *> _ssocks;
};

}

#endif /* CTCPSERVER_H_ */
