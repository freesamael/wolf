/*
 * UDPSocket.cpp
 *
 *  Created on: Mar 8, 2010
 *      Author: samael
 */

#include <cstdio>
#include <errno.h>
#include "UDPSocket.h"

namespace cml
{

UDPSocket::UDPSocket()
{
	if ((_sockfd = socket(AF_INET, type(), 0)) < 0)
		perror("UDPSocket::UDPSocket()");
}

}
