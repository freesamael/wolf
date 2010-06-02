/**
 * \file Runner.cpp
 * \date Apr 1, 2010
 * \author samael
 */

#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <sys/time.h>
#include "Thread.h"
#include "UDPSocket.h"
#include "TLVReaderWriter.h"
#include "HelperMacros.h"
#include "Runner.h"
#include "D2MCE.h"
#include "internal/CommandListener.h"
#include "internal/ActorExecutor.h"

using namespace std;
using namespace cml;

namespace wfe
{

Runner::~Runner()
{
	delete _mhandle;
	for (unsigned i = 0; i < _rhandles.size(); i++) {
		delete _rhandles[i];
	}
}

void Runner::run()
{
	// Preparation
	if (!waitMaster()) return;
	if (!connMaster()) return;
	joinD2MCE();

	// Start processing commands.
	CommandListener cmdhandle(this, &_msock);
	ActorExecutor actorhandle(this);
	Thread cmdthread(&cmdhandle);
	Thread actorthread(&actorhandle);
	cmdthread.start();
	actorthread.start();
	cmdthread.join();
	actorthread.join();
}

/**
 * Wait for master hello message.
 */
bool Runner::waitMaster()
{
	UDPSocket usock;
	TLVReaderWriter udprw(&usock);
	TLVCommand *inmsg;

	usock.passiveOpen(_rport);
	if (!(inmsg = dynamic_cast<TLVCommand *>(udprw.recvfrom(&_maddr, &_mport)))) {
		PERR("Invalid incoming message.");
		return false;
	}

	if (inmsg->command() != TLVCommand::HELLO_MASTER) {
		PERR("Expected command " <<
				TLVCommand::CommandString[TLVCommand::HELLO_MASTER] <<
				" but got " << TLVCommand::CommandString[inmsg->command()]);
		return false;
	}

	delete inmsg;
	return true;
}

/**
 * Connect to master node.
 */
bool Runner::connMaster()
{
	TLVReaderWriter tcprw(&_msock);
	if (!_msock.activeOpen(_maddr, _mport)) {
		PERR("Unable to connect to the master node.");
		return false;
	}

	TLVCommand outmsg(TLVCommand::HELLO_RUNNER);
	return tcprw.write(outmsg);
}

/**
 * Join the computing group.
 */
void Runner::joinD2MCE()
{
#ifndef DISABLE_D2MCE
	// Random back-off. It's just a workaround for the problem that multiple
	// nodes joining at the same time might cause failure.
	srand((unsigned)_msock.currentAddress().toInetAddr());
	usleep((rand() % 30) * 33000); // sleep 0 ~ 1s, granularity 33ms.

	// Join
	D2MCE::instance()->join(_appname);
	PINFO(D2MCE::instance()->getNumberOfNodes() <<
			"nodes inside the group, node id = " << D2MCE::instance()->nodeId()
			<< ".");
#endif /* DISABLE_D2MCE */
}

/**
 * Add an actor into the waiting queue for execution.
 */
void Runner::enqueue(AbstractWorkerActor *worker)
{
	_mutex.lock();
	_wq.push_back(worker);
	if (_wq.size() == 1)
		_wcond.wakeOne();
	_mutex.unlock();
}

/**
 * Take an actor from the waiting queue. If no actors are in the queue, the
 * caller will be blocked until available or return NULL if timed out.
 */
AbstractWorkerActor* Runner::dequeue(unsigned timeout_us)
{
	AbstractWorkerActor *a;

	_mutex.lock();
	if (_wq.size() == 0)
		_wcond.wait(&_mutex, timeout_us);
	if (_wq.size() == 0)
		return NULL;
	a = _wq.front();
	_wq.pop_front();
	_mutex.unlock();

	return a;
}

}
