/*
 * TCPSocket.cpp
 *
 *  Created on: Mar 8, 2010
 *      Author: samael
 */

#include <cstdio>
#include <errno.h>
#include "TCPSocket.h"

namespace cml
{

TCPSocket::TCPSocket()
{
	if ((_sockfd = socket(AF_INET, type(), 0)) < 0)
		perror("TCPSocket::TCPSocket()");
}

}
