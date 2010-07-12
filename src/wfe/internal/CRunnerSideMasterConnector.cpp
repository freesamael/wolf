/**
 * \file CRunnerSideMasterConnector.cpp
 * \date Jun 11, 2010
 * \author samael
 */

#include <iostream>
#include <sstream>
#include "HelperMacros.h"
#include "CUdpSocket.h"
#include "CTlvReaderWriter.h"
#include "CTlvCommand.h"
#include "CRunnerSideMasterConnector.h"

using namespace cml;

namespace wfe
{

CTcpSocket* CRunnerSideMasterConnector::connect(in_port_t mport, in_port_t rport)
{
	CTcpSocket *tsock = NULL;

	/*
	 * Wait for Master hello message.
	 */
	CHostAddress maddr;
	CUdpSocket passivesock;
	CTlvReaderWriter udpreader(&passivesock);
	CTlvCommand *inmsg;
	in_port_t tmpport;

	passivesock.passiveOpen(rport);
	if (!(inmsg = dynamic_cast<CTlvCommand *>(udpreader.recvfrom(&maddr, &tmpport)))) {
		PERR("Invalid incoming message.");
		return NULL;
	} else if (inmsg->command() != CTlvCommand::HELLO_MASTER) {
		PERR("Expected command " <<
				CTlvCommand::CommandString[CTlvCommand::HELLO_MASTER] <<
				" but got " << CTlvCommand::CommandString[inmsg->command()]);
		return NULL;
	}
	delete inmsg;
	PINF_2("Got master hello message.");

	/*
	 * Connect to Master.
	 */
	tsock = new CTcpSocket();
	tsock->activeOpen(maddr, mport);
	PINF_2("Connected to master.");

	// Check nonblocking flag and set to block if needed.
	// I noticed that the default value might be nonblocking on BSD/Mac.
	if (tsock->isNonblock())
		tsock->setNonblock(false);

	return tsock;
}

}
