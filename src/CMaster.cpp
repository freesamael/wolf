/**
 * \file CMaster.cpp
 * \date Apr 1, 2010
 * \author samael
 */

#include <sys/time.h>
#include <unistd.h>
#include <cstdlib>
#include "CMutex.h"
#include "CUdpSocket.h"
#include "CThread.h"
#include "CSingletonAutoDestructor.h"
#include "CTlvUint32.h"
#include "CMaster.h"
#include "CTlvCommand.h"
#include "IManagerActor.h"
#include "internal/CMasterSideConnectionListener.h"
#include "internal/CMasterSideCommandListener.h"
#include "internal/CMasterSideCommandSender.h"
#include "internal/CMasterSideFinishedWorkerProcessor.h"

using namespace std;

namespace wolf
{

struct PData
{
	PData(): rsocks(), rsocksmx(), cmdsdr(), clis(), pfwpsr(NULL), mgrq(),
			mgrqmx(), fwq(), fwqmx(), nfinwrks(0),
			bcastaddr(CHostAddress::BroadcastAddress), stime(), exetime() {}

	// Runner related resources.
	vector<CTcpSocket *> rsocks;				// Runner sockets.
	CMutex rsocksmx;							// Runner sockets mutex.
	CMasterSideCommandSender cmdsdr;			// Command sender.
	vector<CMasterSideCommandListener *> clis;	// Command listeners.
	CMasterSideFinishedWorkerProcessor *pfwpsr;	// Finished worker processor.

	// Others.
	map<uint32_t, IManagerActor *> mgrq;		// Manager queue.
	CMutex mgrqmx;								// Manager queue mutex.
	deque<pair<uint32_t, AWorkerActor *> > fwq; // Finished worker queue.
	CMutex fwqmx;								// Finished worker queue mutex.
	unsigned nfinwrks;							// # finished workers.
	CHostAddress bcastaddr;						// Broadcast address.
	wolf::CTime stime;							// Time when started.
	wolf::CTime exetime;							// Execution time.

private:
	PData(const PData &UNUSED(o)): rsocks(), rsocksmx(), cmdsdr(), clis(),
			pfwpsr(NULL), mgrq(), mgrqmx(), fwq(), fwqmx(), nfinwrks(0),
			bcastaddr(CHostAddress::BroadcastAddress), stime(),	exetime() {}
	PData& operator=(const PData &UNUSED(o)) { return *this; }
};

SINGLETON_REGISTRATION(CMaster);
SINGLETON_DEPENDS_SOCKET(CMaster);
SINGLETON_REGISTRATION_END();

const string CMaster::StateString[] = { "Not Ready", "Ready", "End" };

CMaster::CMaster():
		SINGLETON_MEMBER_INITLST,	_state(NOT_READY), _mserver(), _defdisp(),
		_activedisp(&_defdisp), _d(new PData)
{
}

CMaster::~CMaster()
{
	for (unsigned i = 0; i < _d->clis.size(); i++)
		delete _d->clis[i];
	delete _d->pfwpsr;
	delete _d;
}

/**
 * Initial master with program parameters.
 */
void CMaster::init(int argc, char *argv[])
{
	int opt;
	while ((opt = getopt(argc, argv, "b:h")) != -1) {
		switch (opt) {
		case 'b':
			_d->bcastaddr = CHostAddress(optarg);
			break;
		case 'h':
			cerr << "Usage: " << argv[0] <<
			" [-b broadcast_address]" << endl;
			exit(EXIT_FAILURE);
		}
	}
}

/**
 * Setup the master. It must be called before other operations.
 */
bool CMaster::setup(in_port_t master_port, in_port_t runner_port,
		const string &appname, unsigned int timeout)
{
	if (_state != NOT_READY)
		return false;

	// Start waiting runner connections.
	CMasterSideConnectionListener listener(this, &_mserver, master_port);
	listener.start();

	// Join D2MCE group and broadcast hello message.
	_d->cmdsdr.joinD2MCE(appname);
	_d->cmdsdr.hello(runner_port, _d->bcastaddr);

	// Check the runners.
	sleep(timeout);
	listener.stop();
	if (_d->rsocks.size() == 0) {
		PERR("No runner found.");
		return false;
	}
	PINF_1("Totally " << _d->rsocks.size() << " runners connected.");

	// Start finished worker processor.
	_d->pfwpsr = new CMasterSideFinishedWorkerProcessor(this);
	_d->pfwpsr->start();

	// Bind command listeners to each runner, and start all runners.
	for (unsigned i = 0; i < _d->rsocks.size(); i++) {
		CMasterSideCommandListener *cl =
				new CMasterSideCommandListener(this, _d->rsocks[i]);
		cl->start();
		_d->clis.push_back(cl);
		_d->cmdsdr.startRunner(_d->rsocks[i]);
	}

	_state = READY;
	_d->stime = CTime::now();
	return true;
}

/**
 * Send a worker out to run.
 */
void CMaster::runWorker(AWorkerActor *worker, IManagerActor *mgr)
{
	if (!worker || !mgr)
		return;

#ifdef __D2MCE__ /* DSM mode */
	_d->mgrqmx.lock();
	for (unsigned i = 0; i < _d->rsocks.size(); i++) {
		uint32_t seq = _d->cmdsdr.runWorker(_d->rsocks[i], worker);
		_d->mgrq[seq] = mgr;
	}
	_d->mgrqmx.unlock();
#else /* Normal mode */
	_d->rsocksmx.lock();
	CTcpSocket *runner = dispatcher()->choose(_d->rsocks);
	_d->rsocksmx.unlock();
	if (runner) {
		_d->mgrqmx.lock();
		uint32_t seq = _d->cmdsdr.runWorker(runner, worker);
		_d->mgrq[seq] = mgr;
		PINF_2("Worker " << seq << " has been sent to runner " <<
				runner->peerAddress().toString());
		_d->mgrqmx.unlock();
	}
#endif /* __D2MCE__ */
}

/**
 * Tell the runners to shutdown. It should be perform before program exits.
 */
void CMaster::shutdown()
{
	_d->exetime = CTime::now() - _d->stime;
	PINF_1("Execution time = " << _d->exetime);
	PINF_1(_d->nfinwrks << " runners finished.");

	// Stop finished worker processor.
	_d->pfwpsr->setDone();
	_d->pfwpsr->join();

	// Shutdown all runners and stop all command listeners.
	for (unsigned i = 0; i < _d->rsocks.size(); i++) {
		_d->clis[i]->setDone();
		_d->cmdsdr.shutdown(_d->rsocks[i]);
	}
	for (unsigned i = 0; i < _d->rsocks.size(); i++)
		_d->clis[i]->join();

	_state = END;
}

/**
 * Used by RunnerCommandListener to notify that a runner is got.
 */
void CMaster::runnerConnected(wolf::CTcpSocket *runnersock)
{
	vector<CHostAddress> addrs;
	_d->rsocksmx.lock();
	for (unsigned i = 0; i < _d->rsocks.size(); i++) {
		addrs.push_back(_d->rsocks[i]->peerAddress());
	}
	_d->cmdsdr.addRunner(runnersock, addrs);
	_d->rsocks.push_back(runnersock);
	_d->rsocksmx.unlock();
}

/**
 * Put a finished worker into waiting to for processing.
 */
void CMaster::putFinishWorker(uint32_t wseq, AWorkerActor *worker)
{
	_d->fwqmx.lock();
	_d->nfinwrks++;
	_d->fwq.push_back(pair<uint32_t, AWorkerActor *>(wseq, worker));
	_d->fwqmx.unlock();
}

/**
 * Process a finished worker from queue. It's called by a different thread from
 * who put workers to queue.
 */
void CMaster::processFinishedWorker()
{
	uint32_t wseq;
	AWorkerActor *worker = NULL;

	// Take a finished worker.
	_d->fwqmx.lock();
	if (!_d->fwq.empty()) {
		pair<uint32_t, AWorkerActor *> p = _d->fwq.front();
		wseq = p.first;
		worker = p.second;
		_d->fwq.pop_front();
	}
	_d->fwqmx.unlock();

	if (!worker) {
		usleep(10000);
	} else {
		// Find the belonging manager.
		map<uint32_t, IManagerActor *>::iterator iter;
		_d->mgrqmx.lock();
		if ((iter = _d->mgrq.find(wseq)) == _d->mgrq.end()) {
			PERR("No manager found owning worker with sequence = " << wseq);
			delete worker;
			return;
		}

		// Take the value and remove the manager from the queue.
		IManagerActor *mgr = iter->second;
		_d->mgrq.erase(iter);
		_d->mgrqmx.unlock();

#ifdef __D2MCE__ /* DSM mode */
		// Check if it's the last worker owned by that manager.
		map<uint32_t, IManagerActor *>::iterator tmpiter;
		bool lastone = true;
		_d->mgrqmx.lock();
		for (tmpiter = _d->mgrq.begin();
				tmpiter != _d->mgrq.end(); ++tmpiter) {
			if (tmpiter->second == mgr) {
				lastone = false;
				break;
			}
		}
		_d->mgrqmx.unlock();

		// Notify manager only if it's the last worker.
		if (lastone) {
			mgr->processFinishedWorker(worker);
		}
#else /* Normal mode */
		mgr->workerFinished(worker);
#endif /* DISABLE_D2MCE */
		delete worker;
	}
}

/**
 * Get the number of runners.
 */
unsigned CMaster::numberOfRunners()
{
	_d->rsocksmx.lock();
	unsigned n = _d->rsocks.size();
	_d->rsocksmx.unlock();
	return n;
}

CTime CMaster::executionTime() const
{
	return _d->exetime;
}

}
