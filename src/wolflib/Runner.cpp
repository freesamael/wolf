/**
 * \file Runner.cpp
 * \date Apr 1, 2010
 * \author samael
 */

#include <iostream>
#include <string>
#include <typeinfo>
#include <cstdio>
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

void Runner::run(unsigned short runner_port, unsigned short master_port,
		const string &appname)
{
	HostAddress addr;
	PINFO("Waiting for master notification.");
	if (!(addr = getMasterAddr(runner_port)).isValid()) {
		PERR << "Runner fails, exit now.\n";
		return;
	}

	TCPSocket sock;
	PINFO("Connection to the master node");
	if (!connectToMaster(&sock, addr, master_port)) {
		PERR << "Runner fails, exit now.\n";
		return;
	}
	PINFO(((string)"Connected with address = " + sock.currentAddress().toString()).c_str());

#ifdef ENABLE_D2MCE
	// Random back-off.
	srand((unsigned)sock.currentAddress().toInetAddr());
	usleep((rand() % 30) * 33000); // sleep 0 ~ 1s, granularity 33ms.
	// Join.
	if (!joinGroup(appname)) {
		PERR << "Runner fails, exit now.\n";
		return;
	}
#endif

	runnerLoop(&sock);
}

/**
 * \internal
 * Listen and wait for master broadcasting a ADD_MASTER message.
 */
HostAddress Runner::getMasterAddr(unsigned short runner_port)
{
	UDPSocket usock;
	TLVReaderWriter udprw(&usock);
	TLVMessage *inmsg;
	HostAddress inaddr;
	unsigned short inport;

	usock.passiveOpen(runner_port);
	if (!(inmsg = dynamic_cast<TLVMessage *>(udprw.recvfrom(&inaddr, &inport)))) {
		PERR << "Invalid incoming message.\n";
		return HostAddress();
	}

	if (inmsg->command() != TLVMessage::HELLO_MASTER) {
		PERR << "Expected command " <<
				TLVMessage::CommandString[TLVMessage::HELLO_MASTER] <<
				" but got " << TLVMessage::CommandString[inmsg->command()] <<
				".\n";
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
		unsigned short master_port)
{
	TLVReaderWriter tcprw(sock);
	if (!sock->activeOpen(addr, master_port)) {
		PERR << "Unable to connect to the master node.\n";
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
//	if (!D2MCE::instance()->join(appname)) {
//		fprintf(stderr, "Runner::run(): Unable to join group.\n");
//		return false;
//	}
	D2MCE::instance()->join(appname);
	printf("Info: %s: %d: %d nodes inside the group, node id = %d.\n",
			__PRETTY_FUNCTION__, __LINE__,
			D2MCE::instance()->getNumberOfNodes(),
			D2MCE::instance()->nodeId());

	return true;
}

/**
 * \internal
 * Process the command received.
 */
bool Runner::processCommand(TLVMessage *cmd)
{
	if (cmd->command() == TLVMessage::RUN_ACTOR) {
		AbstractWorkerActor *actor;
		if (!(actor = dynamic_cast<AbstractWorkerActor *>(cmd->parameter()))) {
			PERR << "Invalid parameter.\n";
			return false;
		}
		actor->setup();
		do {
			/// TODO: Add the power-aware load balancing feature.
			actor->prefire();
			actor->fire();
			actor->postfire();
		} while (actor->testfire());
		actor->wrapup();
		delete actor;
	} else {
		PERR << "Unexpected command \"" <<
				TLVMessage::CommandString[cmd->command()] << "\".\n";
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

	while ((inobj = tcprw.read())) {
		if (!(inmsg = dynamic_cast<TLVMessage *>(inobj))) {
			PERR << "Invalid incoming message.\n";
			delete inobj;
		} else {
			if (!processCommand(inmsg)) {
				PERR << "One command failed to execute.\n";
			}
			delete inmsg;
		}
	}
}

}
