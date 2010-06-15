/**
 * \file MasterSideConnectionListener.cpp
 * \date Apr 28, 2010
 * \author samael
 */

#include "MasterSideConnectionListener.h"

using namespace cml;

namespace wfe
{

void MasterSideConnectionListener::notify(TCPSocket *sock)
{
	_master->runnerConnected(sock);
}

}
