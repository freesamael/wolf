/**
 * \file CRunnerSideConnectionListener.cpp
 * \date Jun 11, 2010
 * \author samael
 */

#include "CRunnerSideConnectionListener.h"

namespace wolf
{

void wolf::CRunnerSideConnectionListener::notify(wolf::CTcpSocket *sock)
{
	_runner->runnerConnected(sock);
}

}

