/**
 * \file CMasterSideConnectionListener.cpp
 * \date Apr 28, 2010
 * \author samael
 */

#include "CMasterSideConnectionListener.h"

using namespace cml;

namespace wfe
{

void CMasterSideConnectionListener::notify(CTcpSocket *sock)
{
	_master->runnerConnected(sock);
}

}
