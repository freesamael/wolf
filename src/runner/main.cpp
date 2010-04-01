/*
 * main.cpp
 *
 *  Created on: Mar 31, 2010
 *      Author: samael
 */

#include <iostream>
#include <typeinfo>
#include <cstdio>
#include <cstdlib>
#include <UDPSocket.h>
#include <TCPSocket.h>
#include <TLVReaderWriter.h>
#include <TLVMessage.h>
#include <HostAddress.h>
#include <TLVObjectFactory.h>
#include <CustomTLVTypes.h>
#include <TLVMessageCreator.h>

#define SLAVE_PORT 5566
#define MASTER_PORT 7788

using namespace std;
using namespace cml;
using namespace wfe;

int main()
{
	TLVObjectFactory::instance()->registerType(typeid(TLVMessage).name(),
			TLV_TYPE_MESSAGE);
	TLVObjectFactory::instance()->registerCreator(typeid(TLVMessage).name(),
			new TLVMessageCreator());

	UDPSocket usock;
	TLVReaderWriter udprw(&usock);
	TLVMessage *inmsg;
	HostAddress inaddr;
	unsigned short inport;

	usock.bind(SLAVE_PORT);
	if (!(inmsg = dynamic_cast<TLVMessage *>(udprw.recvfrom(&inaddr, &inport)))) {
		fprintf(stderr, "Error: Invalid incoming message.\n");
		exit(EXIT_FAILURE);
	}

	cout << "Got message from " << inaddr.toString() << ": " << inport << endl;

	if (inmsg->command() != TLVMessage::ADD_MASTER) {
		fprintf(stderr, "Error: Expected command %s but got %s.\n",
				TLVMessage::CommandString[TLVMessage::ADD_MASTER],
				TLVMessage::CommandString[inmsg->command()]);
		exit(EXIT_FAILURE);
	}

	delete inmsg;

	TCPSocket tsock;
	TLVReaderWriter tcprw(&tsock);
	ITLVObject *inobj;

	cout << "Trying to connect to " << inaddr.toString() << ": " << MASTER_PORT << endl;
	if (!tsock.connect(inaddr, MASTER_PORT)) {
		fprintf(stderr, "Unable to connect to the master node.\n");
		exit(EXIT_FAILURE);
	}

	TLVMessage outmsg(TLVMessage::ADD_SLAVE);
	tcprw.write(outmsg);

	while ((inobj = tcprw.read())) {
		if (!(inmsg = dynamic_cast<TLVMessage *>(inobj))) {
			fprintf(stderr, "Error: Invalid incoming message.\n");
		} else {
			printf("Executing command: %s.\n",
					TLVMessage::CommandString[inmsg->command()]);
		}
		delete inobj;
	}

	TLVObjectFactory::releaseInstance();

	return 0;
}
