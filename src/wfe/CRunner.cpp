/**
 * \file Runner.cpp
 * \date Apr 1, 2010
 * \author samael
 */

#include <iostream>
#include <sstream>
#include <string>
#include <deque>
#include <cstdlib>
#include "CThread.h"
#include "CUdpSocket.h"
#include "HelperMacros.h"
#include "CRunner.h"
#include "CD2mce.h"
#include "internal/CRunnerSideMasterConnector.h"
#include "internal/CRunnerSideConnectionListener.h"
#include "internal/CRunnerSideCommandListener.h"
#include "internal/CRunnerSideCommandSender.h"
#include "internal/CRunnerSideWorkerExecutor.h"

using namespace std;
using namespace cml;

namespace wfe
{

struct PData
{
	PData(): pmsock(NULL), pmclis(NULL), pcnlis(NULL), rsocks(), rsocksmx(),
			rclis(), cmdsdr(), pwexe(NULL), wq(), wqmx() {}
	// Master related resources.
	CTcpSocket *pmsock;							// Master sock.
	CRunnerSideCommandListener *pmclis;			// Master cmd listener.

	// Runner related resources.
	CRunnerSideConnectionListener *pcnlis;		// Runner connection listener.
	vector<CTcpSocket *> rsocks;				// Runner socks.
	CMutex rsocksmx;							// Runner socks mutex.
	vector<CRunnerSideCommandListener *> rclis;	// Runner cmd listeners.

	// Others.
	CRunnerSideCommandSender cmdsdr;			// Command sender.
	CRunnerSideWorkerExecutor *pwexe;			// Worker executor.
	deque<pair<uint32_t, AWorkerActor *> > wq;	// Working queue.
	CMutex wqmx;								// Working queue mutex.

private:
	PData(const PData &UNUSED(o)): pmsock(NULL), pmclis(NULL), pcnlis(NULL),
	rsocks(), rsocksmx(), rclis(), cmdsdr(), pwexe(NULL), wq(), wqmx() {}
	PData& operator=(const PData &UNUSED(o)) { return *this; }
};

CRunner::CRunner(in_port_t master_port, in_port_t runner_port, IWorkerStealer *ws,
		const string &appname): _id(0), _state(NOT_READY), _statemx(),
		_statewcond(), _mport(master_port), _rport(runner_port), _stealer(ws),
		_appname(appname), _rserver(), _d(new PData())
{
#ifndef ENABLE_D2MCE /* Normal mode */
	if (ws)
		ws->setRunner(this);
#endif /* ENABLE_D2MCE */
	_rserver.setAutoclean(false);
}

CRunner::~CRunner()
{
	// Cleanup all workers.
	deque<pair<uint32_t, AWorkerActor *> >::iterator iter;
	for (iter = _d->wq.begin(); iter != _d->wq.end(); ++iter)
		delete iter->second;

	// Cleanup worker executor.
	delete _d->pwexe;

	// Cleanup master command listener and socket.
	delete _d->pmclis;
	delete _d->pmsock;

	// Cleanup runner connection listener.
	delete _d->pcnlis;

	// Cleanup runner command listeners and sockets.
	for (unsigned i = 0; i < _d->rsocks.size(); i++) {
		delete _d->rclis[i];
		delete _d->rsocks[i];
	}

	delete _d;
}

void CRunner::run()
{
	// Check state.
	_statemx.lock();
	if (_state != NOT_READY) {
		_statemx.unlock();
		PERR("Invalid operation.");
		return;
	}
	_statemx.unlock();

	// Connect to master and join D2MCE.
	CRunnerSideMasterConnector msconn;
	_d->pmsock = msconn.connect(_mport, _rport);
	_d->cmdsdr.joinD2MCE(_d->pmsock, _appname);

	// Start listening connections from other runners.
	_d->pcnlis = new CRunnerSideConnectionListener(this, &_rserver, _rport);
	_d->pcnlis->start();

	// Start listening master commands.
	_d->pmclis = new CRunnerSideCommandListener(this, _d->pmsock);
	_d->pmclis->start();

	// Create worker executor (but not to start yet).
	_d->pwexe = new CRunnerSideWorkerExecutor(this);

	// Send hello message to master.
	_d->cmdsdr.hello(_d->pmsock);

	// Set to ready and wait until ends.
	_statemx.lock();
	_state = READY;
	_statewcond.wait(&_statemx);
	_statemx.unlock();
	_d->pmclis->join();
}

/**
 * Get all runners.
 */
vector<CTcpSocket*> CRunner::runnerSocks()
{
	return _d->rsocks;
}

/**
 * Connect to a runner with given address.
 */
void CRunner::connectRunner(const CHostAddress &addr)
{
	_id++;
	CTcpSocket *sock = new CTcpSocket();
	sock->activeOpen(addr, _rport);
	runnerConnected(sock);
	_d->cmdsdr.hello(sock);
}

/**
 * Called when a runner connection got.
 */
void CRunner::runnerConnected(CTcpSocket *runnersock)
{
	CRunnerSideCommandListener *lis =
			new CRunnerSideCommandListener(this, runnersock);

	PINF_2("Starting runner command listener.");
	lis->start();

	_d->rsocksmx.lock();
	_d->rsocks.push_back(runnersock);
	_d->rclis.push_back(lis);
	_d->rsocksmx.unlock();
}

/**
 * Start accepting commands and stop listening for runner connections.
 */
void CRunner::startWorking()
{
	// Check state.
	_statemx.lock();
	if (_state != READY) {
		_statemx.unlock();
		PERR("Invalid operation.");
		return;
	}
	_statemx.unlock();

	// Stop connection listener and start worker executor.
	_d->pcnlis->stop();
	_d->pwexe->start();
	PINF_2("Totally " << _d->rsocks.size() << " runners connected.");
	PINF_2("Runner id = " << _id);

	// Change state.
	_statemx.lock();
	_state = WORKING;
	_statemx.unlock();
}

/**
 * Add a worker into the waiting queue for execution.
 */
void CRunner::putWorker(uint32_t wseq, AWorkerActor *worker,
		CTcpSocket *sender)
{
	_d->wqmx.lock();
	_d->wq.push_back(pair<uint32_t, AWorkerActor *>(wseq, worker));
	_d->wqmx.unlock();

#ifndef ENABLE_D2MCE /* Normal mode */
	if (_stealer)
		_stealer->workerArrived(sender);
#endif /* ENABLE_D2MCE */
}

/**
 * Take a worker from the waiting queue.
 */
pair<uint32_t, AWorkerActor *> CRunner::takeWorker()
{
	pair<uint32_t, AWorkerActor *> w(0, NULL);

	_d->wqmx.lock();
	if (_d->wq.size() > 0) {
		w = _d->wq.front();
		_d->wq.pop_front();
	}
	_d->wqmx.unlock();

#ifndef ENABLE_D2MCE /* Normal mode */
	if (!w.second && _stealer)
		_stealer->workerMissed();
#endif /* ENABLE_D2MCE */

	return w;
}

/**
 * Notify that the worker stealing failed.
 */
void CRunner::workerStealFailed(CTcpSocket *sender)
{
#ifndef ENABLE_D2MCE /* Normal mode */
	if (_stealer)
		_stealer->stealFailed(sender);
#endif /* ENABLE_D2MCE */
}

/**
 * Notify that a worker has been finished.
 */
void CRunner::sendWorkerFinished(uint32_t wseq, AWorkerActor *worker)
{
	_d->cmdsdr.workerFinished(_d->pmsock, wseq, worker);
	delete worker;
}

/**
 * Send n worker (if any) to given runner.
 */
void CRunner::sendWorker(CTcpSocket *sock, uint16_t nworkers)
{
#ifdef ENABLE_D2MCE /* DSM mode */
	_d->cmdsdr.stealFailed(sock); // Always fail in DSM mode.

#else					// Normal mode.
	vector<pair<uint32_t, AWorkerActor *> > wps;

	// Try to take n worker pairs.
	for (unsigned i = 0; i < nworkers; i++) {
		pair<uint32_t, AWorkerActor *> wp = takeWorker();
		if (!wp.second)
			break;
		wps.push_back(wp);
	}

	// Send workers to the runner or WORKER_STEAL_FAILED if no worker found.
	if (wps.empty()) {
		_d->cmdsdr.stealFailed(sock);
	} else {
		for (unsigned i = 0; i < wps.size(); i++)
			_d->cmdsdr.runWorker(sock, wps[i].first, wps[i].second);
	}
#endif /* ENABLE_D2MCE */
}

/**
 * Steal workers from givne runner.
 */
void CRunner::sendWorkerSteal(CTcpSocket *sock, uint16_t nworkers)
{
#ifndef ENABLE_D2MCE /* Normal mode */
	_d->cmdsdr.stealWorker(sock, nworkers);
#endif /* ENABLE_D2MCE */
}

/**
 * Stop the runner.
 */
void CRunner::shutdown()
{
	_statemx.lock();
	if (_state == READY) {
		_statemx.unlock();
		// Stop runner connection listener.
		_d->pcnlis->stop();
	} else if (_state == WORKING) {
		_statemx.unlock();
		// Stopping worker executor.
		_d->pwexe->setDone();
		_d->pwexe->join();
	} else {
		_statemx.unlock();
		PERR("Invalid operation.");
		return;
	}

	// Closing all runner sockets.
	for (unsigned i = 0; i < _d->rsocks.size(); i++)
		_d->rsocks[i]->close();

	// Stopping all runner command listeners.
	for (unsigned i = 0; i < _d->rclis.size(); i++) {
		_d->rclis[i]->setDone();
		_d->rclis[i]->join();
	}

	// Closing master socket.
	_d->pmsock->close();

	// Stopping master command listener.
	_d->pmclis->setDone();

	_statemx.lock();
	_state = END;
	_statewcond.wakeAll();
	_statemx.unlock();
}

}
