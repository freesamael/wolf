/**
 * \file CMasterSideConnectionListener.cpp
 * \date Apr 28, 2010
 * \author samael
 */

#include "CMasterSideConnectionListener.h"

namespace wolf
{

void CMasterSideConnectionListener::notify(CTcpSocket *sock)
{
	_master->runnerConnected(sock);
}

}
