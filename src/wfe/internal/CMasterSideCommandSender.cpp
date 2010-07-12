/**
 * \file CMasterSideCommandSender.cpp
 * \date May 27, 2010
 * \author samael
 */

#include <iostream>
#include <sstream>
#include "CUdpSocket.h"
#include "CTlvReaderWriter.h"
#include "CMasterSideCommandSender.h"
#include "CTlvCommand.h"
#include "CTlvUint32.h"
#include "CD2mce.h"

using namespace std;
using namespace cml;

namespace wfe
{

uint32_t CMasterSideCommandSender::_wseq = 0;

void CMasterSideCommandSender::joinD2MCE(const string &appname)
{
#ifdef ENABLE_D2MCE /* DSM mode */
	// Join D2MCE computing group.
	D2MCE::instance()->join(appname);
	PINF_2("Currently " << D2MCE::instance()->getNumberOfNodes() <<
			" nodes inside the group, node id = " <<
			D2MCE::instance()->nodeId() << ".");
#endif /* ENABLE_D2MCE */
}

void CMasterSideCommandSender::hello(in_port_t rport, const CHostAddress &addr)
{
	PINF_2("Sending HELLO_MASTER.");
	CUdpSocket usock;
	CTlvReaderWriter udprw(&usock);
	usock.setBroadcast(true);
	udprw.sendto(CTlvCommand(CTlvCommand::HELLO_MASTER), addr, rport);
}

void CMasterSideCommandSender::addRunner(CTcpSocket *rsock, const vector<CHostAddress> &addrs)
{
	PINF_2("Sending RUNNER_ADD.");
	if (addrs.size() > 0) {
		CTlvCommand cmd(CTlvCommand::RUNNER_ADD);
		cmd.setAutoclean(true);
		for (unsigned i = 0; i < addrs.size(); i++) {
			cmd.addParameter(new CTlvUint32((uint32_t)addrs[i].toInetAddr()));
		}
		CTlvReaderWriter rw(rsock);
		rw.write(cmd);
	}
}

void CMasterSideCommandSender::startRunner(CTcpSocket *rsock)
{
	PINF_2("Sending RUNNER_START.");
	CTlvReaderWriter rw(rsock);
	rw.write(CTlvCommand(CTlvCommand::RUNNER_START));
}

void CMasterSideCommandSender::shutdown(CTcpSocket *rsock)
{
	PINF_2("Sending SHUTDOWN.");
	CTlvReaderWriter rw(rsock);
	rw.write(CTlvCommand(CTlvCommand::SHUTDOWN));
}

uint32_t CMasterSideCommandSender::runWorker(CTcpSocket *rsock, AWorkerActor *worker)
{
	if (++_wseq == UINT32_MAX)
		_wseq = 0;

	PINF_2("Sending WORKER_RUN with id = " << _wseq << ".");
	CTlvReaderWriter rw(rsock);
	CTlvCommand cmd(CTlvCommand::WORKER_RUN);
	CTlvUint32 u32(_wseq);
	cmd.addParameter(&u32);
	cmd.addParameter(worker);
	rw.write(cmd);

	return _wseq;
}

}
