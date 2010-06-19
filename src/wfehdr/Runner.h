/**
 * \file Runner.h
 * \date Apr 1, 2010
 * \author samael
 */

#ifndef RUNNER_H_
#define RUNNER_H_

#include <string>
#include <utility>
#include <stdint.h>
#include "TCPSocket.h"
#include "Mutex.h"
#include "WaitCondition.h"
#include "AbstractWorkerActor.h"

namespace wfe
{

struct PData;

/**
 * The runner which is responsible for worker executions.
 */
class Runner
{
public:
	typedef enum State {
		NOT_READY,
		READY,
		WORKING,
		END
	} State;

	Runner(uint16_t master_port, uint16_t runner_port,
			const std::string &appname = "default");
	~Runner();
	void run();

	// Used by internal classes and runner itself.
	void connectRunner(const cml::HostAddress &addr);
	void runnerConnected(cml::TCPSocket *runnersock);
	void startWorking();
	void putWorker(uint32_t wseq, AbstractWorkerActor *worker);
	std::pair<uint32_t, AbstractWorkerActor *> takeWorker();
	void workerFinished(uint32_t wseq, AbstractWorkerActor *worker);
	void workerMissed();
	void sendWorker(cml::TCPSocket *sock);
	void shutdown();

private:
	Runner(const Runner &UNUSED(o)): _state(NOT_READY), _statemx(),
	_statewcond(), _mport(0), _rport(0), _appname(), _rsock(), _d(NULL) {}
	Runner& operator=(const Runner &UNUSED(o)) { return *this; }

private:
	State _state;
	cml::Mutex _statemx;
	cml::WaitCondition _statewcond;
	uint16_t _mport, _rport;
	std::string _appname;
	cml::TCPSocket _rsock;
	PData *_d;
};

}

#endif /* RUNNER_H_ */
