/**
 * \file Runner.h
 * \date Apr 1, 2010
 * \author samael
 */

#ifndef RUNNER_H_
#define RUNNER_H_

#include <vector>
#include <deque>
#include <string>
#include "HostAddress.h"
#include "TCPSocket.h"
#include "Mutex.h"
#include "WaitCondition.h"
#include "TLVCommand.h"
#include "AbstractWorkerActor.h"

namespace wfe
{

struct PData;

/**
 * The runner which is responsible for worker executions.
 */
class Runner
{
	friend class RunnerSideCommandListener;
public:
	Runner(uint16_t master_port, uint16_t runner_port,
			const std::string &appname);
	~Runner();
	void run();
	void enqueue(AbstractWorkerActor *worker);
	AbstractWorkerActor* dequeue(unsigned timeout_us = 100000);

private:
	Runner(const Runner &UNUSED(o)) {}
	Runner& operator=(const Runner &UNUSED(o)) { return *this; }
	bool waitMaster();
	bool connMaster();
	void joinD2MCE();
	void startWaitRunners();
	void stopWaitRunners();
	void listenMaster();
	void listenRunners();

private:
	uint16_t _mport, _rport;
	std::string _appname;
	cml::TCPSocket *_msock;
	PData *_data;
};

}

#endif /* RUNNER_H_ */
