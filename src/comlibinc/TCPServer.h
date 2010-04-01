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

class TCPServer: public TCPSocket
{
public:
	TCPServer() {}
	TCPServer(int sock): TCPSocket(sock) {}
	~TCPServer();
	bool listen(unsigned short port, unsigned qlen);
	TCPSocket* accept(AbstractSocket::Blockable blk = AbstractSocket::BLOCK);

private:
	bool listen(unsigned qlen);
	std::vector<TCPSocket *> _socks;
};

}

#endif /* TCPSERVER_H_ */
