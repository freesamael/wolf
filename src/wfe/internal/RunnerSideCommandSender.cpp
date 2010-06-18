/**
 * \file RunnerSideCommandSender.cpp
 * \date Jun 11, 2010
 * \author samael
 */

#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include "TLVUInt32.h"
#include "TLVReaderWriter.h"
#include "TLVCommand.h"
#include "HelperMacros.h"
#include "RunnerSideCommandSender.h"

using namespace std;
using namespace cml;

namespace wfe
{

void RunnerSideCommandSender::joinD2MCE(TCPSocket *sock, const string &appname)
{
#ifndef DISABLE_D2MCE
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
#endif /* DISABLE_D2MCE */
}

void RunnerSideCommandSender::hello(TCPSocket *sock)
{
	PINF_2("Sending HELLO_RUNNER.");
	TLVReaderWriter rw(sock);
	rw.write(TLVCommand(TLVCommand::HELLO_RUNNER));
}

void RunnerSideCommandSender::workerFinished(TCPSocket *sock, uint32_t wseq,
		AbstractWorkerActor *worker)
{
	PINF_2("Sending WORKER_FINISHED with id = " << wseq << ".");
	TLVReaderWriter rw(sock);
	TLVCommand cmd(TLVCommand::WORKER_FINISHED);
	TLVUInt32 u32(wseq);
	cmd.addParameter(&u32);
	cmd.addParameter(worker);
	rw.write(cmd);
}

void RunnerSideCommandSender::stealWorker(TCPSocket *sock)
{
	PINF_2("Sending WORKER_STEAL.");
	TLVReaderWriter rw(sock);
	rw.write(TLVCommand(TLVCommand::WORKER_STEAL));
}

void RunnerSideCommandSender::runWorker(TCPSocket *sock, uint32_t wseq,
		AbstractWorkerActor *worker)
{
	PINF_2("Sending WORKER_RUN with id = " << wseq << ".");
	TLVReaderWriter rw(sock);
	TLVCommand cmd(TLVCommand::WORKER_RUN);
	TLVUInt32 u32(wseq);
	cmd.addParameter(&u32);
	cmd.addParameter(worker);
	rw.write(cmd);
}

}
