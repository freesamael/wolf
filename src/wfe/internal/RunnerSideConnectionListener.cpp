/**
 * \file RunnerSideConnectionListener.cpp
 * \date Jun 11, 2010
 * \author samael
 */

#include "RunnerSideConnectionListener.h"

using namespace cml;

namespace wfe
{

void wfe::RunnerSideConnectionListener::notify(cml::TCPSocket *sock)
{
	_runner->runnerConnected(sock);
}

}

