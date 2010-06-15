/**
 * \file MasterSideCommandSender.cpp
 * \date May 27, 2010
 * \author samael
 */

#define __STDC_LIMIT_MACROS // Needed to use UINTx_MAX macros in <stdint.h>
#include "UDPSocket.h"
#include "TLVReaderWriter.h"
#include "MasterSideCommandSender.h"
#include "TLVCommand.h"
#include "TLVUInt32.h"
#include "D2MCE.h"

using namespace std;
using namespace cml;

namespace wfe
{

uint32_t MasterSideCommandSender::_wseq = 0;

void MasterSideCommandSender::joinD2MCE(const string &appname)
{
#ifndef DISABLE_D2MCE
	// Join D2MCE computing group.
	D2MCE::instance()->join(appname);
	PINF_2(D2MCE::instance()->getNumberOfNodes() <<
			" nodes inside the group, node id = " <<
			D2MCE::instance()->nodeId() << ".");
#endif /* DISABLE_D2MCE */
}

void MasterSideCommandSender::hello(uint16_t rport)
{
	PINF_2("Sending HELLO_MASTER.");
	UDPSocket usock;
	TLVReaderWriter udprw(&usock);
	usock.setBroadcast(true);
	usock.setTTL(1);
	udprw.sendto(TLVCommand(TLVCommand::HELLO_MASTER),
	HostAddress::BroadcastAddress, rport);
}

void MasterSideCommandSender::addRunner(TCPSocket *rsock, const vector<HostAddress> &addrs)
{
	PINF_2("Sending RUNNER_ADD.");
	if (addrs.size() > 0) {
		TLVCommand cmd(TLVCommand::RUNNER_ADD);
		cmd.setAutoclean(true);
		for (unsigned i = 0; i < addrs.size(); i++) {
			cmd.addParameter(new TLVUInt32((uint32_t)addrs[i].toInetAddr()));
		}
		TLVReaderWriter rw(rsock);
		rw.write(cmd);
	}
}

void MasterSideCommandSender::startRunner(TCPSocket *rsock)
{
	PINF_2("Sending RUNNER_START.");
	TLVReaderWriter rw(rsock);
	rw.write(TLVCommand(TLVCommand::RUNNER_START));
}

void MasterSideCommandSender::shutdown(TCPSocket *rsock)
{
	PINF_2("Sending SHUTDOWN.");
	TLVReaderWriter rw(rsock);
	rw.write(TLVCommand(TLVCommand::SHUTDOWN));
}

uint32_t MasterSideCommandSender::runWorker(TCPSocket *rsock, AbstractWorkerActor *worker)
{
	if (++_wseq == UINT32_MAX)
		_wseq = 0;

	PINF_2("Sending WORKER_RUN with id = " << _wseq << ".");
	TLVReaderWriter rw(rsock);
	TLVCommand cmd(TLVCommand::WORKER_RUN);
	TLVUInt32 u32(_wseq);
	cmd.addParameter(&u32);
	cmd.addParameter(worker);
	rw.write(cmd);

	return _wseq;
}

}
