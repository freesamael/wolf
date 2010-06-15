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
	PData(): pcnlis(NULL), pmclis(NULL), rsocks(), rclis(), rclthreads(),
			cmdsdr() {}
	RunnerSideConnectionListener *pcnlis;
	RunnerSideCommandListener *pmclis;
	vector<TCPSocket *> rsocks;
	vector<RunnerSideCommandListener *> rclis;
	vector<Thread *> rclthreads;
	RunnerSideCommandSender cmdsdr;
private:
	PData(const PData &UNUSED(o)): pcnlis(NULL), pmclis(NULL), rsocks(),
		rclis(), rclthreads(), cmdsdr() {}
	PData& operator=(const PData &UNUSED(o)) { return *this; }
};

Runner::Runner(uint16_t master_port, uint16_t runner_port,
		const string &appname): _mport(master_port), _rport(runner_port),
		_appname(appname), _msock(NULL), _rsock(), _d(new PData())
{

}

Runner::~Runner()
{
	delete _d;
}

void Runner::run()
{
	// Connect to master and join D2MCE.
	RunnerSideMasterConnector msconn;
	if (!(_msock = msconn.connect(_mport, _rport))) {
		PERR("Runner fails. Exit.");
		return;
	}
	_d->cmdsdr.joinD2MCE(_appname);

	// Start listening connections from other runners.
	_d->pcnlis = new RunnerSideConnectionListener(this, &_rsock, _rport);
	_d->pcnlis->start();

	// Start listening master commands.
	_d->pmclis = new RunnerSideCommandListener(this, _msock);
	Thread cmdthread(_d->pmclis);
	cmdthread.start();

	// Send hello message to master.
	_d->cmdsdr.hello(_msock);

	// Block wait until command processing loop ends.
	cmdthread.join();
}

///**
// * Add an actor into the waiting queue for execution.
// */
//void Runner::enqueue(AbstractWorkerActor *worker)
//{
//	_mutex.lock();
//	_wq.push_back(worker);
//	if (_wq.size() == 1)
//		_wcond.wakeOne();
//	_mutex.unlock();
//}
//
///**
// * Take an actor from the waiting queue. If no actors are in the queue, the
// * caller will be blocked until available or return NULL if timed out.
// */
//AbstractWorkerActor* Runner::dequeue(unsigned timeout_us)
//{
//	AbstractWorkerActor *a;
//
//	_mutex.lock();
//	if (_wq.size() == 0)
//		_wcond.wait(&_mutex, timeout_us);
//	if (_wq.size() == 0)
//		return NULL;
//	a = _wq.front();
//	_wq.pop_front();
//	_mutex.unlock();
//
//	return a;
//}

/**
 * Called when a runner connection got.
 */
void Runner::runnerConnected(TCPSocket *runnersock)
{
	RunnerSideCommandListener *lis =
			new RunnerSideCommandListener(this, runnersock);
	Thread *listhread = new Thread(lis);
	listhread->start();

	_d->rsocks.push_back(runnersock);
	_d->rclis.push_back(lis);
	_d->rclthreads.push_back(listhread);
}

}
