/*
 * RunnerAgent.cpp
 *
 *  Created on: Apr 1, 2010
 *      Author: samael
 */

#include <cstdio>
#include <sys/time.h>
#include <TCPServer.h>
#include <UDPSocket.h>
#include <TLVReaderWriter.h>
#include "RunnerAgent.h"
#include "TLVMessage.h"

using namespace cml;

namespace wfe
{

const char *RunnerAgent::StateString[] = { "Not Ready", "Ready" };
RunnerAgent *RunnerAgent::_instance = NULL;
pthread_mutex_t RunnerAgent::_mutex = PTHREAD_MUTEX_INITIALIZER;

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
 * @brief Setup runner agent.
 */
bool RunnerAgent::setup(unsigned short runner_port, unsigned short master_port,
		unsigned timeout)
{
	if (_state != NOT_READY)
		return false;

	TCPServer server;
	server.listen(master_port);
	struct timeval now, abs_tout;
	struct timeval rel_tout = {timeout / 1000000, timeout % 1000000};

	// Set time.
	gettimeofday(&now, NULL);
	timeradd(&now, &rel_tout, &abs_tout);

	// Broadcast notification.
	UDPSocket usock;
	TLVReaderWriter udprw(&usock);
	usock.setBroadcast(true);
	usock.setTTL(1);
	udprw.sendto(TLVMessage(TLVMessage::ADD_MASTER),
			HostAddress::BroadcastAddress, runner_port);

	// Add runners.
	while (timercmp(&now, &abs_tout, <)) {
		TCPSocket *tsock;
		if ((tsock = server.accept(AbstractSocket::NONBLOCK))) {
			TLVReaderWriter tcprw(tsock);
			TLVMessage *msg;
			if (!(msg = dynamic_cast<TLVMessage *>(tcprw.read()))) {
				fprintf(stderr, "RunnerAgent::setup(): Error: Invalid incoming message.\n");
			} else if (msg->command() != TLVMessage::ADD_SLAVE) {
				fprintf(stderr, "RunnerAgent::setup(): Error: Expected command %s but got %s.\n",
						TLVMessage::CommandString[TLVMessage::ADD_SLAVE],
						TLVMessage::CommandString[msg->command()]);
			} else {
				_runners.push_back(tsock);
			}
		}
		gettimeofday(&now, NULL);
	}

	if (_runners.size() == 0) {
		fprintf(stderr, "RunnerAgent::setup(): Error: No runner found.\n");
		return false;
	}

	return true;
}

/**
 * @brief Send an worker actor to runners.
 * @param[in] runner Runner to send actor to, or NULL to all runners.
 */
bool RunnerAgent::sendActor(const AbstractWorkerActor &actor, TCPSocket *runner)
{
	if (_state != READY)
		return false;

	// Send to given runner.
	if (runner) {
		TLVReaderWriter rw(runner);
		return rw.write(actor);
	}

	// Send to all runners.
	bool success = true;
	for (int i = 0; i < (int)_runners.size(); i++) {
		TLVReaderWriter rw(_runners[i]);
		success &= rw.write(actor);
	}
	return success;
}

}
