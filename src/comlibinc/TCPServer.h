/*
 * TCPServer.h
 *
 *  Created on: Mar 8, 2010
 *      Author: samael
 */

#ifndef TCPSERVER_H_
#define TCPSERVER_H_

#include <vector>
#include "TCPSocket.h"

namespace cml
{

/**
 * TCP server used to accept incoming connections.
 */
class TCPServer: public TCPSocket
{
public:
	TCPServer() {}
	TCPServer(int sock): TCPSocket(sock) {}
	~TCPServer();
	bool listen(unsigned short port, unsigned qlen = 10);
	TCPSocket* accept(bool nonblk = false);

private:
	bool _listen(unsigned qlen);
	std::vector<TCPSocket *> _socks;
};

}

#endif /* TCPSERVER_H_ */
