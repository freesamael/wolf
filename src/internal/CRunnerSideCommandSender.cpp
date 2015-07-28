/**
 * \file CRunnerSideCommandSender.cpp
 * \date Jun 11, 2010
 * \author samael
 */

#include "CRunnerSideCommandSender.h"

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <unistd.h>
#include "CD2mce.h"
#include "CTlvUint32.h"
#include "CTlvUint16.h"
#include "CTlvCommand.h"
#include "HelperMacros.h"
#include "CTcpTlvWriter.h"

using namespace std;

namespace wolf
{

void CRunnerSideCommandSender::joinD2MCE(UNUSED(CTcpSocket *sock), UNUSED(const string &appname))
{
#ifdef __D2MCE__ /* DSM mode */
	// Random delay.
	srand((unsigned)sock->currentAddress().toInetAddr());
	unsigned delay = rand() % 60 * 33000; // 0 ~ 2s, step 33ms
	PINF_2("Delaying " << delay << " microseconds.");
	usleep(delay);
	// Join D2MCE computing group.
	D2MCE::instance()->join(appname);
	PINF_2("Currently " << D2MCE::instance()->getNumberOfNodes() <<
			" nodes inside the group, node id = " <<
			D2MCE::instance()->nodeId() << ".");
#endif /* __D2MCE__ */
}

void CRunnerSideCommandSender::hello(CTcpSocket *sock)
{
	CTcpTlvWriter writer(sock);
	writer.writeObject(CTlvCommand(CTlvCommand::HELLO_RUNNER));
}

void CRunnerSideCommandSender::workerFinished(CTcpSocket *sock, uint32_t wseq,
		AWorkerActor *worker)
{
	CTcpTlvWriter writer(sock);
	CTlvCommand cmd(CTlvCommand::WORKER_FINISHED);
	CTlvUint32 u32(wseq);
	cmd.addParameter(&u32);
	cmd.addParameter(worker);
	writer.writeObject(cmd);
}

void CRunnerSideCommandSender::stealWorker(CTcpSocket *sock, uint32_t n)
{
	CTcpTlvWriter writer(sock);
	CTlvCommand cmd(CTlvCommand::WORKER_STEAL);
	CTlvUint32 u32(n);
	cmd.addParameter(&u32);
	writer.writeObject(cmd);
}

void CRunnerSideCommandSender::stealFailed(CTcpSocket *sock)
{
	CTcpTlvWriter writer(sock);
	writer.writeObject(CTlvCommand(CTlvCommand::WORKER_STEAL_FAILED));
}

void CRunnerSideCommandSender::runWorker(CTcpSocket *sock, uint32_t wseq,
		AWorkerActor *worker)
{
	CTcpTlvWriter writer(sock);
	CTlvCommand cmd(CTlvCommand::WORKER_RUN);
	CTlvUint32 u32(wseq);
	cmd.addParameter(&u32);
	cmd.addParameter(worker);
	writer.writeObject(cmd);
}

}
