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
#include "internal/RunnerSideMasterConnector.h"
#include "internal/RunnerSideConnectionListener.h"
#include "internal/RunnerSideCommandListener.h"
#include "internal/RunnerSideCommandSender.h"
#include "internal/RunnerSideWorkerExecutor.h"

using namespace std;
using namespace cml;

namespace wfe
{

struct PData
{
};

Runner::Runner(uint16_t master_port, uint16_t runner_port,
		const string &appname): _mport(master_port), _rport(runner_port),
		_appname(appname), _msock(NULL), _data(new PData())
{

}

Runner::~Runner()
{
	delete _data;
}

void Runner::run()
{
	// Connect to master.
	RunnerSideMasterConnector msconn;
	if (!(_msock = msconn.connect(_mport, _rport))) {
		PERR("Runner fails. Exit.");
		return;
	}

	// Start listening connections from other runners.

	// Start listening master commands.
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
	PINFO_2(D2MCE::instance()->getNumberOfNodes() <<
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
