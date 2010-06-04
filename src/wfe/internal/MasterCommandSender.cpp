/**
 * \file MasterCommandSender.cpp
 * \date May 27, 2010
 * \author samael
 */

#include "UDPSocket.h"
#include "TLVReaderWriter.h"
#include "MasterCommandSender.h"
#include "TLVCommand.h"
#include "TLVUInt32.h"
#include "D2MCE.h"

using namespace std;
using namespace cml;

namespace wfe
{

void MasterCommandSender::joinD2MCE(const string &appname)
{
#ifndef DISABLE_D2MCE
	// Join D2MCE computing group.
	D2MCE::instance()->join(appname);
	PINFO(D2MCE::instance()->getNumberOfNodes() <<
			" nodes inside the group, node id = " <<
			D2MCE::instance()->nodeId() << ".");
#endif /* DISABLE_D2MCE */
}

void MasterCommandSender::hello(uint16_t runner_port)
{
	UDPSocket usock;
	TLVReaderWriter udprw(&usock);
	usock.setBroadcast(true);
	usock.setTTL(1);
	udprw.sendto(TLVCommand(TLVCommand::HELLO_MASTER),
	HostAddress::BroadcastAddress, runner_port);
}

void MasterCommandSender::start(TCPSocket *runner)
{
	TLVReaderWriter rw(runner);
	rw.write(TLVCommand(TLVCommand::RUNNER_START));
}

void MasterCommandSender::shutdown(TCPSocket *runner)
{
	TLVReaderWriter rw(runner);
	rw.write(TLVCommand(TLVCommand::SHUTDOWN));
}

void MasterCommandSender::runActor(TCPSocket *runner, AbstractWorkerActor *actor)
{
/// TODO:
}

void MasterCommandSender::addRunner(TCPSocket *runner, vector<HostAddress> addrs)
{
	if (addrs.size() > 0U) {
		TLVCommand cmd(TLVCommand::RUNNER_ADD);
		cmd.setAutoclean(true);
		for (unsigned i = 0; i < addrs.size(); i++) {
			cmd.addParameter(new TLVUInt32((uint32_t)addrs[i].toInetAddr()));
		}
		TLVReaderWriter rw(runner);
		rw.write(cmd);
	}
}

}
