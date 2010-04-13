/**
 * \file Runner.cpp
 * \date Apr 1, 2010
 * \author samael
 */

#include <iostream>
#include <typeinfo>
#include <cstdio>
#include <UDPSocket.h>
#include <TLVReaderWriter.h>
#include "Runner.h"
#include "D2MCE.h"
#include "IWorkerActor.h"

using namespace std;
using namespace cml;

namespace wfe
{

void Runner::run(unsigned short runner_port, unsigned short master_port,
		const string &appname)
{
	HostAddress addr;
	if (!(addr = getMasterAddr(runner_port)).isValid()) {
		fprintf(stderr, "Runner::run(): Error: Runner fails, exit now.\n");
		return;
	}

	TCPSocket sock;
	if (!connectToMaster(&sock, addr, master_port)) {
		fprintf(stderr, "Runner::run(): Error: Runner fails, exit now.\n");
		return;
	}

	if (!joinGroup(appname)) {
		fprintf(stderr, "Runner::run(): Error: Runner fails, exit now.\n");
		return;
	}

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
		fprintf(stderr, "Runner::run(): Error: Invalid incoming message.\n");
		return HostAddress();
	}

	if (inmsg->command() != TLVMessage::HELLO_MASTER) {
		fprintf(stderr, "Runner::run(): Error: Expected command %s but got %s.\n",
				TLVMessage::CommandString[TLVMessage::HELLO_MASTER],
				TLVMessage::CommandString[inmsg->command()]);
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
		fprintf(stderr, "Runner::run(): Unable to connect to the master node.\n");
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
	printf("%d nodes inside the group, node id = %d.\n",
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
		IWorkerActor *actor;
		if (!(actor = dynamic_cast<IWorkerActor *>(cmd->parameter()))) {
			fprintf(stderr, "Runner::run(): Error: Invalid parameter.\n");
			return false;
		}
		actor->setup();
		while (actor->testfire()) {
			/// TODO: Add the power-aware load balancing feature.
			actor->prefire();
			actor->fire();
			actor->postfire();
		}
		actor->wrapup();
		delete actor;
	} else {
		fprintf(stderr, "Runner::run(): Error: Unexpected command \"%s\".\n",
				TLVMessage::CommandString[cmd->command()]);
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
			fprintf(stderr, "Runner::run(): Error: Invalid incoming message.\n");
			delete inobj;
		} else {
			if (!processCommand(inmsg)) {
				fprintf(stderr, "Runner::run(): Error: One command failed to execute.\n");
			}
			delete inmsg;
		}
	}
}

}
