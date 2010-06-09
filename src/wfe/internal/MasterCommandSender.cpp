/**
 * \file MasterCommandSender.cpp
 * \date May 27, 2010
 * \author samael
 */

#define __STDC_LIMIT_MACROS // Needed for UINTx_MAX
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

uint32_t MasterCommandSender::_wseq = 0;

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

void MasterCommandSender::hello(uint16_t rport)
{
	UDPSocket usock;
	TLVReaderWriter udprw(&usock);
	usock.setBroadcast(true);
	usock.setTTL(1);
	udprw.sendto(TLVCommand(TLVCommand::HELLO_MASTER),
	HostAddress::BroadcastAddress, rport);
}

void MasterCommandSender::addRunner(TCPSocket *rsock, const vector<HostAddress> &addrs)
{
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

void MasterCommandSender::startRunner(TCPSocket *rsock)
{
	TLVReaderWriter rw(rsock);
	rw.write(TLVCommand(TLVCommand::RUNNER_START));
}

void MasterCommandSender::shutdown(TCPSocket *rsock)
{
	TLVReaderWriter rw(rsock);
	rw.write(TLVCommand(TLVCommand::SHUTDOWN));
}

uint32_t MasterCommandSender::runWorker(TCPSocket *rsock, AbstractWorkerActor *worker)
{
	if (++_wseq == UINT32_MAX)
		_wseq = 0;

	TLVReaderWriter rw(rsock);
	TLVCommand cmd(TLVCommand::WORKER_RUN);
	TLVUInt32 u32(_wseq);
	cmd.addParameter(&u32);
	cmd.addParameter(worker);
	rw.write(cmd);

	return _wseq;
}

}
