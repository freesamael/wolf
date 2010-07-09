/**
 * \file CRunnerSideConnectionListener.cpp
 * \date Jun 11, 2010
 * \author samael
 */

#include "CRunnerSideConnectionListener.h"

using namespace cml;

namespace wfe
{

void wfe::CRunnerSideConnectionListener::notify(cml::CTcpSocket *sock)
{
	_runner->runnerConnected(sock);
}

}

