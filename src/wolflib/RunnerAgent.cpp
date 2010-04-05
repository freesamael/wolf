/*
 * RunnerAgent.cpp
 *
 *  Created on: Apr 1, 2010
 *      Author: samael
 */

#include <cstdio>
#include <sys/time.h>
#include <unistd.h>
#include <UDPSocket.h>
#include <TLVReaderWriter.h>
#include <Thread.h>
#include "RunnerAgent.h"
#include "TLVMessage.h"

using namespace std;
using namespace cml;

namespace wfe
{

const char *RunnerAgent::StateString[] = { "Not Ready", "Ready" };
RunnerAgent *RunnerAgent::_instance = NULL;
pthread_mutex_t RunnerAgent::_mutex = PTHREAD_MUTEX_INITIALIZER;

class PrivateAcceptThread: public Thread
{
public:
	PrivateAcceptThread(): _stop(false), _server(NULL), _runners(NULL) {}
	void setparam(TCPServer *server, vector<TCPSocket *> *runners)
	{
		_server = server;
		_runners = runners;
	}
	void run()
	{
		while (!_stop) {
			TCPSocket *tsock;
			if ((tsock = _server->accept(true))) {
				TLVReaderWriter tcprw(tsock);
				TLVMessage *msg;
				if (!(msg = dynamic_cast<TLVMessage *>(tcprw.read()))) {
					fprintf(stderr, "RunnerAgent::setup(): Error: Invalid incoming message.\n");
				} else if (msg->command() != TLVMessage::HELLO_SLAVE) {
					fprintf(stderr, "RunnerAgent::setup(): Error: Expected command %s but got %s.\n",
							TLVMessage::CommandString[TLVMessage::HELLO_SLAVE],
							TLVMessage::CommandString[msg->command()]);
				} else {
					_runners->push_back(tsock);
				}
				delete msg;
			}
			usleep(20000);
		}
	}
	void stop() { _stop = true; }

private:
	bool _stop;
	TCPServer *_server;
	vector<TCPSocket *> *_runners;
};

RunnerAgent* RunnerAgent::instance()
{
	pthread_mutex_lock(&_mutex);
	if (!_instance)
		_instance = new RunnerAgent();
	pthread_mutex_unlock(&_mutex);
	return _instance;
}

void RunnerAgent::release()
{
	pthread_mutex_lock(&_mutex);
	delete _instance;
	_instance = NULL;
	pthread_mutex_unlock(&_mutex);
}

RunnerAgent::RunnerAgent(): _state(NOT_READY)
{

}

RunnerAgent::~RunnerAgent()
{
	for (int i = 0; i < (int)_runners.size(); i++)
		_runners[i]->shutdown();
}

/**
 * Setup runner agent.
 */
bool RunnerAgent::setup(unsigned short runner_port, unsigned short master_port,
		unsigned timeout)
{
	if (_state != NOT_READY)
		return false;

	// Listen and wait for join message.
	PrivateAcceptThread ath;
	_server.listen(master_port);
	ath.setparam(&_server, &_runners);
	ath.start();

	// Broadcast notification.
	UDPSocket usock;
	TLVReaderWriter udprw(&usock);
	usock.setBroadcast(true);
	usock.setTTL(1);
	udprw.sendto(TLVMessage(TLVMessage::HELLO_MASTER),
			HostAddress::BroadcastAddress, runner_port);

	// Wait until timed out.
	sleep(timeout);
	ath.stop();
	ath.join();

	if (_runners.size() == 0) {
		fprintf(stderr, "RunnerAgent::setup(): Error: No runner found.\n");
		return false;
	}

	_state = READY;
	return true;
}

/**
 * Send an worker actor to runners.
 *
 * \param[in] runner
 * Runner to send actor to, or NULL to all runners.
 */
bool RunnerAgent::sendActor(AbstractWorkerActor *actor, TCPSocket *runner)
{
	if (_state != READY)
		return false;

	TLVMessage msg;
	msg.setCommand(TLVMessage::RUN_ACTOR);
	msg.setParameter(actor);

	// Send to given runner.
	if (runner) {
		TLVReaderWriter rw(runner);
		return rw.write(msg);
	}

	// Send to all runners.
	bool success = true;
	for (int i = 0; i < (int)_runners.size(); i++) {
		TLVReaderWriter rw(_runners[i]);
		success &= rw.write(msg);
	}
	return success;
}

}
