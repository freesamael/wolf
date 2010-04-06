/*
 * TCPSocket.h
 *
 *  Created on: Mar 8, 2010
 *      Author: samael
 */

#ifndef TCPSOCKET_H_
#define TCPSOCKET_H_

#include <vector>
#include "AbstractSocket.h"

namespace cml
{

class TCPSocket: public AbstractSocket
{
public:
	TCPSocket() {}
	TCPSocket(int sock): AbstractSocket(sock) {}
	~TCPSocket();
	TCPSocket* accept();

private:
	std::vector<TCPSocket *> _ssocks;
};

}

#endif /* TCPSOCKET_H_ */
