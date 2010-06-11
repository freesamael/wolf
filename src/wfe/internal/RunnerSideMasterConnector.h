/**
 * \file RunnerSideMasterConnector.h
 * \date Jun 11, 2010
 * \author samael
 */

#ifndef RUNNERSIDEMASTERCONNECTOR_H_
#define RUNNERSIDEMASTERCONNECTOR_H_

#include <stdint.h>
#include "TCPSocket.h"

namespace wfe
{

class RunnerSideMasterConnector
{
public:
	cml::TCPSocket* connect(uint16_t mport, uint16_t rport);
};

}

#endif /* RUNNERSIDEMASTERCONNECTOR_H_ */
