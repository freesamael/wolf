/**
 * \file CMasterSideCommandSender.cpp
 * \date May 27, 2010
 * \author samael
 */

#include <iostream>
#include <sstream>
#include "CUdpSocket.h"
#include "CMasterSideCommandSender.h"
#include "CTlvCommand.h"
#include "CTlvUint32.h"
#include "CD2mce.h"
#include "CTcpTlvWriter.h"
#include "CUdpTlvWriter.h"

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
	CUdpSocket usock;
	CUdpTlvWriter uwriter(&usock);
	usock.setBroadcast(true);
	uwriter.sendObjectTo(CTlvCommand(CTlvCommand::HELLO_MASTER), addr, rport);
}

void CMasterSideCommandSender::addRunner(CTcpSocket *rsock, const vector<CHostAddress> &addrs)
{
	if (addrs.size() > 0) {
		CTlvCommand cmd(CTlvCommand::RUNNER_ADD);
		cmd.setAutoclean(true);
		for (unsigned i = 0; i < addrs.size(); i++) {
			cmd.addParameter(new CTlvUint32((uint32_t)addrs[i].toInetAddr()));
		}
		CTcpTlvWriter writer(rsock);
		writer.writeObject(cmd);
	}
}

void CMasterSideCommandSender::startRunner(CTcpSocket *rsock)
{
	CTcpTlvWriter writer(rsock);
	writer.writeObject(CTlvCommand(CTlvCommand::RUNNER_START));
}

void CMasterSideCommandSender::shutdown(CTcpSocket *rsock)
{
	CTcpTlvWriter writer(rsock);
	writer.writeObject(CTlvCommand(CTlvCommand::SHUTDOWN));
}

uint32_t CMasterSideCommandSender::runWorker(CTcpSocket *rsock, AWorkerActor *worker)
{
	if (++_wseq == UINT32_MAX)
		_wseq = 0;

	CTcpTlvWriter writer(rsock);
	CTlvCommand cmd(CTlvCommand::WORKER_RUN);
	CTlvUint32 u32(_wseq);
	cmd.addParameter(&u32);
	cmd.addParameter(worker);
	writer.writeObject(cmd);

	return _wseq;
}

}
