/**
 * \file CRunnerSideMasterConnector.h
 * \date Jun 11, 2010
 * \author samael
 */

#ifndef CRUNNERSIDEMASTERCONNECTOR_H_
#define CRUNNERSIDEMASTERCONNECTOR_H_

#include <stdint.h>
#include "CTcpSocket.h"

namespace wfe
{

/**
 * CRunnerSideMasterConnector connects to master once it got master hello
 * message.
 */
class CRunnerSideMasterConnector
{
public:
	cml::CTcpSocket* connect(uint16_t mport, uint16_t rport);
};

}

#endif /* CRUNNERSIDEMASTERCONNECTOR_H_ */
