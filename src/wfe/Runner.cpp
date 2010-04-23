/**
 * \file Runner.cpp
 * \date Apr 1, 2010
 * \author samael
 */

#include <iostream>
#include <string>
#include <typeinfo>
#include <cstdlib>
#include <unistd.h>
#include <sys/time.h>
#include <UDPSocket.h>
#include <TLVReaderWriter.h>
#include <HelperMacros.h>
#include "Runner.h"
#include "D2MCE.h"
#include "AbstractWorkerActor.h"

using namespace std;
using namespace cml;

namespace wfe
{

void Runner::run(uint16_t runner_port, uint16_t master_port,
		const string &appname)
{
	HostAddress addr;
	PINFO("Waiting for master notification.");
	if (!(addr = getMasterAddr(runner_port)).isValid()) {
		PERR("Runner fails, exit now.");
		return;
	}

	TCPSocket sock;
	PINFO("Connection to the master node");
	if (!connectToMaster(&sock, addr, master_port)) {
		PERR("Runner fails, exit now.");
		return;
	}
	PINFO("Connected with address = " << sock.currentAddress().toString());

#ifndef DISABLE_D2MCE
	// Random back-off. It's just a workaround for the problem that multiple
	// nodes joining at the same time might cause failure.
	srand((unsigned)sock.currentAddress().toInetAddr());
	usleep((rand() % 30) * 33000); // sleep 0 ~ 1s, granularity 33ms.
	// Join.
	if (!joinGroup(appname)) {
		PERR("Runner fails, exit now.");
		return;
	}
#endif /* DISABLE_D2MCE */

	_endflag = false;
	runnerLoop(&sock);
}

/**
 * \internal
 * Listen and wait for master broadcasting a ADD_MASTER message.
 */
HostAddress Runner::getMasterAddr(uint16_t runner_port)
{
	UDPSocket usock;
	TLVReaderWriter udprw(&usock);
	TLVMessage *inmsg;
	HostAddress inaddr;
	uint16_t inport;

	usock.passiveOpen(runner_port);
	if (!(inmsg = dynamic_cast<TLVMessage *>(udprw.recvfrom(&inaddr, &inport)))) {
		PERR("Invalid incoming message.");
		return HostAddress();
	}

	if (inmsg->command() != TLVMessage::HELLO_MASTER) {
		PERR("Expected command " <<
				TLVMessage::CommandString[TLVMessage::HELLO_MASTER] <<
				" but got " << TLVMessage::CommandString[inmsg->command()]);
		return HostAddress();
	}

	delete inmsg;

	return inaddr;
}

/**
 * \internal
 * Connect to the master node.
 */
bool Runner::connectToMaster(TCPSocket *sock, const HostAddress &addr,
		uint16_t master_port)
{
	TLVReaderWriter tcprw(sock);
	if (!sock->activeOpen(addr, master_port)) {
		PERR("Unable to connect to the master node.");
		return false;
	}

	TLVMessage outmsg(TLVMessage::HELLO_SLAVE);
	return tcprw.write(outmsg);
}

/**
 * \internal
 * Join the computing group.
 */
bool Runner::joinGroup(const string &appname)
{
#ifndef DISABLE_D2MCE
	D2MCE::instance()->join(appname);
	PINFO(D2MCE::instance()->getNumberOfNodes() <<
			"nodes inside the group, node id = " << D2MCE::instance()->nodeId()
			<< ".");
#endif /* DISABLE_D2MCE */
	return true;
}

/**
 * \internal
 * Process the command received.
 */
bool Runner::processCommand(TLVMessage *cmd)
{
	PINFO("Processing a command.");
	if (cmd->command() == TLVMessage::RUN_ACTOR) {
		AbstractWorkerActor *actor;
		if (!(actor = dynamic_cast<AbstractWorkerActor *>(cmd->parameter()))) {
			PERR("Invalid parameter.");
			return false;
		}
		actor->setup();
		do {
			actor->prefire();
			actor->fire();
			actor->postfire();
		} while (actor->testfire());
		actor->wrapup();
		delete actor;
	} else if (cmd->command() == TLVMessage::SHUTDOWN) {
		PINFO("Ending runner.");
		_endflag = true;
	} else {
		PERR("Unexpected command \"" <<
				TLVMessage::CommandString[cmd->command()] << "\".");
		return false;
	}
	return true;
}

/**
 * \internal
 * Core loop of runner.
 */
void Runner::runnerLoop(TCPSocket *sock)
{
	TLVReaderWriter tcprw(sock);
	ITLVObject *inobj;
	TLVMessage *inmsg = NULL;

	while (!_endflag) {
		if (!(inobj = tcprw.read()))
			break; // End of file.
		if (!(inmsg = dynamic_cast<TLVMessage *>(inobj))) {
			PERR("Invalid incoming message.");
			delete inobj;
		} else {
			if (!processCommand(inmsg)) {
				PERR("One command failed to execute.");
			}
			delete inmsg;
		}
	}
	PINFO("Runner loop ends.");
}

}
