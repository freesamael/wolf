/*
 * testmaster.cpp
 *
 *  Created on: Mar 31, 2010
 *      Author: samael
 */

#include <iostream>
#include <typeinfo>
#include <cstdio>
#include <cstdlib>
#include <Thread.h>
#include <TCPServer.h>
#include <TCPSocket.h>
#include <TLVReaderWriter.h>
#include <TLVMessage.h>
#include <UDPSocket.h>
#include <TLVObjectFactory.h>
#include <CustomTLVTypes.h>
#include <TLVMessageCreator.h>

#define SLAVE_PORT 5566
#define MASTER_PORT 7788

using namespace std;
using namespace cml;
using namespace wfe;

class FakeCommandGenerator: public Thread
{
	void run()
	{
		cout << "Start command generator thread." << endl;

		TCPServer server;
		server.listen(MASTER_PORT, 10);

		TCPSocket *sock = server.accept();
		TLVReaderWriter rw(sock);
		TLVMessage *inmsg;

		if (!(inmsg = dynamic_cast<TLVMessage *>(rw.read()))) {
			fprintf(stderr, "Error: Invalid incoming message.\n");
			return;
		}

		if (inmsg->command() != TLVMessage::ADD_SLAVE) {
			fprintf(stderr, "Error: Expected command %s but got %s.\n",
					TLVMessage::CommandString[TLVMessage::ADD_SLAVE],
					TLVMessage::CommandString[inmsg->command()]);
		}

		delete inmsg;

		for (int i = 0; i < 20; i++) {
			TLVMessage outmsg(TLVMessage::RUN_ACTOR);
			rw.write(outmsg);
			sleep(1);
		}

		sock->shutdown();
	}
};

int main()
{
	TLVObjectFactory::instance()->registerType(typeid(TLVMessage).name(),
			TLV_TYPE_MESSAGE);
	TLVObjectFactory::instance()->registerCreator(typeid(TLVMessage).name(),
			new TLVMessageCreator());

	FakeCommandGenerator fake;
	fake.start();

	UDPSocket sock;
	TLVReaderWriter rw(&sock);
	TLVMessage outmsg(TLVMessage::ADD_MASTER);

	sock.setBroadcast(true);
	sock.setTTL(1);
	rw.sendto(outmsg, "255.255.255.255", SLAVE_PORT);

	fake.join();

	TLVObjectFactory::instance()->releaseInstance();

	return 0;
}
