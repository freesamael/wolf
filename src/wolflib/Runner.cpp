/*
 * Runner.cpp
 *
 *  Created on: Apr 1, 2010
 *      Author: samael
 */

#include <iostream>
#include <typeinfo>
#include <cstdio>
#include <UDPSocket.h>
#include <TCPSocket.h>
#include <TLVReaderWriter.h>
#include <D2MCE.h>
#include "Runner.h"
#include "TLVMessage.h"
#include "AbstractWorkerActor.h"

using namespace std;
using namespace cml;

namespace wfe
{

HostAddress wait_master(unsigned short runner_port);
bool connect_master(TCPSocket *tsock, const HostAddress &addr,
		unsigned short master_port);
bool join_group(const string &appname);
void runner_loop(TCPSocket *tsock);

void Runner::run(unsigned short runner_port, unsigned short master_port,
		const string &appname)
{
	HostAddress addr;
	if (!(addr = wait_master(runner_port)).isValid())
		return;

	TCPSocket tsock;
	if (!connect_master(&tsock, addr, master_port))
		return;

	if (!join_group(appname))
		return;

	runner_loop(&tsock);
}

/**
 * \internal
 * Listen and wait for master broadcasting a ADD_MASTER message.
 */
HostAddress wait_master(unsigned short runner_port)
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
bool connect_master(TCPSocket *tsock, const HostAddress &addr,
		unsigned short master_port)
{
	TLVReaderWriter tcprw(tsock);
	if (!tsock->activeOpen(addr, master_port)) {
		fprintf(stderr, "Runner::run(): Unable to connect to the master node.\n");
		return false;
	}

	TLVMessage outmsg(TLVMessage::HELLO_SLAVE);
	return tcprw.write(outmsg);
}

bool join_group(const string &appname)
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
 * Core loop of runner.
 */
void runner_loop(TCPSocket *tsock)
{
	TLVReaderWriter tcprw(tsock);
	ITLVObject *inobj;
	TLVMessage *inmsg = NULL;
	AbstractWorkerActor *actor = NULL;

	while ((inobj = tcprw.read())) {
		if (!(inmsg = dynamic_cast<TLVMessage *>(inobj))) {
			fprintf(stderr, "Runner::run(): Error: Invalid incoming message.\n");
			delete inobj;
		} else {
			if (inmsg->command() == TLVMessage::LOAD_ACTOR) {
				if (!(actor = dynamic_cast<AbstractWorkerActor *>(inmsg->parameter())))
					fprintf(stderr, "Runner::run(): Error: Invalid parameter.\n");
				else
					actor->prefire();
			} else if (inmsg->command() == TLVMessage::RUN_ACTOR) {
				if (!actor) {
					fprintf(stderr, "Runner::run(): Error: No actor loaded.\n");
				} else {
					while (actor->firecond())
						actor->fire();
					actor->postfire();
					delete actor;
					actor = NULL;
				}
			} else {
				fprintf(stderr, "Runner::run(): Error: Unexpected command %s.\n",
						TLVMessage::CommandString[inmsg->command()]);
				delete inmsg;
			}
		}
	}
}

}
