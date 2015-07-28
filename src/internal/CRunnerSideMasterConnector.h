/**
 * \file CRunnerSideMasterConnector.h
 * \date Jun 11, 2010
 * \author samael
 */

#ifndef CRUNNERSIDEMASTERCONNECTOR_H_
#define CRUNNERSIDEMASTERCONNECTOR_H_

#include <netinet/in.h>
#include "CTcpSocket.h"

namespace wolf
{

/**
 * CRunnerSideMasterConnector connects to master once it got master hello
 * message.
 */
class CRunnerSideMasterConnector
{
public:
	CTcpSocket* connect(in_port_t mport, in_port_t rport);
};

}

#endif /* CRUNNERSIDEMASTERCONNECTOR_H_ */
