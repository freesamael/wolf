/**
 * \file CRunnerSideMasterConnector.cpp
 * \date Jun 11, 2010
 * \author samael
 */

#include <string>
#include <typeinfo>
#include "CUdpSocket.h"
#include "CUdpTlvReader.h"
#include "CTlvCommand.h"
#include "CRunnerSideMasterConnector.h"
#include "XTlvCommand.h"
#include "HelperMacros.h"

using namespace std;

namespace wolf
{

CTcpSocket* CRunnerSideMasterConnector::connect(in_port_t mport, in_port_t rport)
{
	/*
	 * Wait for Master hello message.
	 */
	CHostAddress maddr;
	CUdpSocket passivesock;
	CUdpTlvReader ureader(&passivesock);
	in_port_t tmpport;

	passivesock.passiveOpen(rport);

	CTlvCommand *inmsg;
	ITlvObject *obj = ureader.recvObjectFrom(&maddr, &tmpport);
	if (!(inmsg = dynamic_cast<CTlvCommand *>(obj))) {
		string type = TYPENAME(obj);
		delete obj;
		throw XTlvCommand(XTlvCommand::INVALID_OBJECT, type);
	} else if (inmsg->command() != CTlvCommand::HELLO_MASTER) {
		XTlvCommand x(XTlvCommand::UNEXPECTED_COMMAND, *inmsg);
		delete inmsg;
		throw;
	}
	delete inmsg;

	/*
	 * Connect to Master.
	 */
	CTcpSocket *tsock = new CTcpSocket();
	tsock->activeOpen(maddr, mport);

	// Check nonblocking flag and set to block if needed.
	// The default value might be nonblocking on BSD/Mac.
	if (!tsock->blockable())
		tsock->setBlockable(true);

	return tsock;
}

}
