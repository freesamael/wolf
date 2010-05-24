/**
 * \file Runner.h
 * \date Apr 1, 2010
 * \author samael
 */

#ifndef RUNNER_H_
#define RUNNER_H_

#include <deque>
#include <string>
#include <HostAddress.h>
#include <TCPSocket.h>
#include <Mutex.h>
#include <WaitCondition.h>
#include "TLVMessage.h"
#include "AbstractWorkerActor.h"

namespace wfe
{

class Runner
{
public:
	/// Execute the runner with given ports and application name.
	void run(uint16_t runner_port, uint16_t master_port, const
			std::string &appname);
	void enqueue(AbstractWorkerActor *worker);
	AbstractWorkerActor* dequeue();

private:
	cml::HostAddress getMasterAddr(uint16_t runner_port);
	bool connectToMaster(cml::TCPSocket *sock, const cml::HostAddress &addr,
			uint16_t master_port);
	void joinGroup(cml::TCPSocket *sock, const std::string &appname);
	bool processCommand(TLVMessage *msg);
	void runnerLoop(cml::TCPSocket *sock);
	bool _endflag;
	std::deque<AbstractWorkerActor *> _wq;
	cml::Mutex _mutex;
	cml::WaitCondition _wcond;
};

}

#endif /* RUNNER_H_ */
