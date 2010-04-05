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
void runner_loop(TCPSocket *tsock);

void Runner::run(unsigned short runner_port, unsigned short master_port)
{
	HostAddress addr;
	if (!(addr = wait_master(runner_port)).isValid())
		return;

	TCPSocket tsock;
	if (!connect_master(&tsock, addr, master_port))
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

	usock.bind(runner_port);
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
	if (!tsock->connect(addr, master_port)) {
		fprintf(stderr, "Runner::run(): Unable to connect to the master node.\n");
		return false;
	}

	TLVMessage outmsg(TLVMessage::HELLO_SLAVE);
	return tcprw.write(outmsg);
}

/**
 * \internal
 * Core loop of runner.
 */
void runner_loop(TCPSocket *tsock)
{
	TLVReaderWriter tcprw(tsock);
	ITLVObject *inobj;
	TLVMessage *inmsg;

	while ((inobj = tcprw.read())) {
		if (!(inmsg = dynamic_cast<TLVMessage *>(inobj))) {
			fprintf(stderr, "Runner::run(): Error: Invalid incoming message.\n");
		} else {
			if (inmsg->command() != TLVMessage::RUN_ACTOR) {
				fprintf(stderr, "Runner::run(): Error: Unexpected command %s.\n",
						TLVMessage::CommandString[inmsg->command()]);
			} else {
				AbstractWorkerActor *actor;
				if (!(actor = dynamic_cast<AbstractWorkerActor *>(inmsg->parameter()))) {
					fprintf(stderr, "Runner::run(): Error: Invalid parameter.\n");
				} else {
					actor->prefire();
					while (actor->firecond())
						actor->fire();
					actor->postfire();
				}
			}
		}
		delete inobj;
	}
}

}
