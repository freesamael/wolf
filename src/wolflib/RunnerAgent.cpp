/**
 * \file RunnerAgent.cpp
 * \date Apr 1, 2010
 * \author samael
 */

#include <cstdio>
#include <sys/time.h>
#include <unistd.h>
#include <UDPSocket.h>
#include <TLVReaderWriter.h>
#include <Thread.h>
#include <SingletonAutoDestructor.h>
#include <HelperMacros.h>
#include "D2MCE.h"
#include "RunnerAgent.h"
#include "TLVMessage.h"

using namespace std;
using namespace cml;

namespace wfe
{

SINGLETON_REGISTRATION(RunnerAgent);

const char *RunnerAgent::StateString[] = { "Not Ready", "Ready" };
RunnerAgent *RunnerAgent::_instance = NULL;
pthread_mutex_t RunnerAgent::_mutex = PTHREAD_MUTEX_INITIALIZER;

/**
 * \internal
 * The internal private class used to accept connections from runners.
 */
class PrivateAcceptThread: public Thread
{
public:
	PrivateAcceptThread(): _stop(false), _msock(NULL), _ssocks(NULL) {}
	void setparam(TCPSocket *server, vector<TCPSocket *> *runners)
	{
		_msock = server;
		_ssocks = runners;
	}
	void run()
	{
		_msock->setNonblock(true);
		while (!_stop) {
			TCPSocket *tsock;
			if ((tsock = _msock->accept())) {
				TLVReaderWriter tcprw(tsock);
				TLVMessage *msg;
				if (!(msg = dynamic_cast<TLVMessage *>(tcprw.read()))) {
					PERR << "Invalid incoming message.\n";
				} else if (msg->command() != TLVMessage::HELLO_SLAVE) {
					PERR << "Expected command " <<
							TLVMessage::CommandString[TLVMessage::HELLO_SLAVE] <<
							"but got " <<
							TLVMessage::CommandString[msg->command()] << ".\n";
				} else {
					PINFO("Got one runner.");
					_ssocks->push_back(tsock);
				}
				delete msg;
			}
			usleep(tsock ? 0 : 50000);
		}
	}
	void stop() { _stop = true; }

private:
	bool _stop;
	TCPSocket *_msock;
	vector<TCPSocket *> *_ssocks;
};

/**
 * Get the instance of the agent.
 */
RunnerAgent* RunnerAgent::instance()
{
	pthread_mutex_lock(&_mutex);
	if (!_instance)
		_instance = new RunnerAgent();
	pthread_mutex_unlock(&_mutex);
	return _instance;
}

/**
 * Release the instance.
 */
void RunnerAgent::release()
{
	PINFO("Releasing RunnerAgent.");
	pthread_mutex_lock(&_mutex);
	delete _instance;
	_instance = NULL;
	pthread_mutex_unlock(&_mutex);
}

/**
 * Setup the agent. It must be called before other agent operations.
 */
bool RunnerAgent::setup(uint16_t runner_port, uint16_t master_port,
		const string &appname, unsigned int timeout)
{
	if (_state != NOT_READY)
		return false;

	// Listen and wait for join message.
	PrivateAcceptThread athread;
	_msock.passiveOpen(master_port);
	athread.setparam(&_msock, &_ssocks);
	athread.start();

#ifndef DISABLE_D2MCE
	// Join D2MCE computing group.
	D2MCE::instance()->join(appname);
//	printf("Info: %s: %d: %d nodes inside the group, node id = %d.\n",
//			__PRETTY_FUNCTION__, __LINE__,
//			D2MCE::instance()->getNumberOfNodes(),
//			D2MCE::instance()->nodeId());
#endif /* DISABLE_D2MCE */

	// Broadcast notification.
	UDPSocket usock;
	TLVReaderWriter udprw(&usock);
	usock.setBroadcast(true);
	usock.setTTL(1);
	udprw.sendto(TLVMessage(TLVMessage::HELLO_MASTER),
			HostAddress::BroadcastAddress, runner_port);

	// Wait until timed out.
	sleep(timeout);
	athread.stop();
	athread.join();

	if (_ssocks.size() == 0) {
		PERR << "No runner found.\n";
		return false;
	}


	_state = READY;
	return true;
}

/**
 * Send an worker actor to runners to execute.
 *
 * \param[in] actor
 * Actor to send.
 *
 * \param[in] rsock
 * Socket of runner to send actor to, or NULL for all runners.
 */
bool RunnerAgent::sendActor(AbstractWorkerActor *actor, TCPSocket *rsock)
{
	if (_state != READY)
		return false;

	TLVMessage msg;
	msg.setCommand(TLVMessage::RUN_ACTOR);
	msg.setParameter(actor);

	// Send to given runner.
	if (rsock) {
		TLVReaderWriter rw(rsock);
		return rw.write(msg);
	}

	// Send to all runners.
	bool success = true;
	for (int i = 0; i < (int)_ssocks.size(); i++) {
		TLVReaderWriter rw(_ssocks[i]);
		success &= rw.write(msg);
	}
	return success;
}

}
