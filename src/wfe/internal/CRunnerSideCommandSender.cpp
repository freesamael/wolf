/**
 * \file CRunnerSideCommandSender.cpp
 * \date Jun 11, 2010
 * \author samael
 */

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <unistd.h>
#include "CD2mce.h"
#include "CTlvUint32.h"
#include "CTlvUint16.h"
#include "CTlvReaderWriter.h"
#include "CTlvCommand.h"
#include "HelperMacros.h"
#include "CRunnerSideCommandSender.h"

using namespace std;
using namespace cml;

namespace wfe
{

void CRunnerSideCommandSender::joinD2MCE(CTcpSocket *sock, const string &appname)
{
#ifdef ENABLE_D2MCE /* DSM mode */
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
#endif /* ENABLE_D2MCE */
}

void CRunnerSideCommandSender::hello(CTcpSocket *sock)
{
	PINF_2("Sending HELLO_RUNNER.");
	CTlvReaderWriter rw(sock);
	rw.write(CTlvCommand(CTlvCommand::HELLO_RUNNER));
}

void CRunnerSideCommandSender::workerFinished(CTcpSocket *sock, uint32_t wseq,
		AWorkerActor *worker)
{
	PINF_2("Sending WORKER_FINISHED with id = " << wseq << ".");
	CTlvReaderWriter rw(sock);
	CTlvCommand cmd(CTlvCommand::WORKER_FINISHED);
	CTlvUint32 u32(wseq);
	cmd.addParameter(&u32);
	cmd.addParameter(worker);
	rw.write(cmd);
}

void CRunnerSideCommandSender::stealWorker(CTcpSocket *sock, uint16_t n)
{
	PINF_2("Sending WORKER_STEAL to steal " << n << " workers.");
	CTlvReaderWriter rw(sock);
	CTlvCommand cmd(CTlvCommand::WORKER_STEAL);
	CTlvUint16 u16(n);
	cmd.addParameter(&u16);
	rw.write(cmd);
}

void CRunnerSideCommandSender::stealFailed(CTcpSocket *sock)
{
	PINF_2("Sending WORKER_STEAL_FAILED.");
	CTlvReaderWriter rw(sock);
	rw.write(CTlvCommand(CTlvCommand::WORKER_STEAL_FAILED));
}

void CRunnerSideCommandSender::runWorker(CTcpSocket *sock, uint32_t wseq,
		AWorkerActor *worker)
{
	PINF_2("Sending WORKER_RUN with id = " << wseq << ".");
	CTlvReaderWriter rw(sock);
	CTlvCommand cmd(CTlvCommand::WORKER_RUN);
	CTlvUint32 u32(wseq);
	cmd.addParameter(&u32);
	cmd.addParameter(worker);
	rw.write(cmd);
}

}
