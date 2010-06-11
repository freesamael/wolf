/**
 * \file RunnerSideMasterConnector.cpp
 * \date Jun 11, 2010
 * \author samael
 */

#include "HelperMacros.h"
#include "UDPSocket.h"
#include "RunnerSideMasterConnector.h"

using namespace cml;

namespace wfe
{

TCPSocket* RunnerSideMasterConnector::connect(uint16_t mport, uint16_t rport)
{
	TCPSocket *tsock = NULL;

	/*
	 * Wait for Master hello message.
	 */
	HostAddress maddr;
	UDPSocket passivesock;
	TLVReaderWriter udpreader(&passivesock);
	TLVCommand *inmsg;
	uint32_t tmpport;

	passivesock.passiveOpen(rport);
	if (!(inmsg = dynamic_cast<TLVCommand *>(udpreader.recvfrom(&maddr, &tmpport)))) {
		PERR("Invalid incoming message.");
		return NULL;
	} else if (inmsg->command() != TLVCommand::HELLO_MASTER) {
		PERR("Expected command " <<
				TLVCommand::CommandString[TLVCommand::HELLO_MASTER] <<
				" but got " << TLVCommand::CommandString[inmsg->command()]);
		return NULL;
	}
	delete inmsg;

	/*
	 * Connect to Master.
	 */
	tsock = new TCPSocket();
	if (!tsock->activeOpen(maddr, mport)) {
		PERR("Unable to connect to master.");
		delete tsock;
		return NULL;
	}

	return tsock;
}

}
