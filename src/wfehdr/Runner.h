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

class CommandListener;
class Runner
{
	friend class CommandListener;
public:
	Runner(uint16_t runner_port, const std::string &appname):
		_rport(runner_port), _mport(), _appname(appname), _maddr(),
		_msock(), _mhandle(NULL), _raddrs(), _rsocks(), _rhandles(),
		_endflag(false), _wq(), _mutex(), _wcond() {}
	~Runner();
	void run();
	void enqueue(AbstractWorkerActor *worker);
	AbstractWorkerActor* dequeue(unsigned timeout_us = 100000);

private:
	Runner(const Runner &UNUSED(o)): _rport(), _mport(), _appname(), _maddr(),
	_msock(), _mhandle(), _raddrs(), _rsocks(), _rhandles(), _endflag(false),
	_wq(), _mutex(), _wcond() {}
	Runner& operator=(const Runner &UNUSED(o)) { return *this; }
	bool waitMaster();
	bool connMaster();
	void joinD2MCE();
	void startWaitRunners();
	void stopWaitRunners();
	void listenMaster();
	void listenRunners();
//	cml::HostAddress getMasterAddr(uint16_t runner_port);
//	bool connectToMaster(cml::TCPSocket *sock, const cml::HostAddress &addr,
//			uint16_t master_port);
//	void joinGroup(cml::TCPSocket *sock, const std::string &appname);
//	bool processCommand(TLVMessage *msg);
//	void runnerLoop(cml::TCPSocket *sock);

private:
	uint16_t _rport, _mport;
	std::string _appname;
	cml::HostAddress _maddr;
	cml::TCPSocket _msock;
	CommandListener *_mhandle;
	std::vector<cml::HostAddress> _raddrs;
	std::vector<cml::TCPSocket> _rsocks;
	std::vector<CommandListener *> _rhandles;

	bool _endflag;
	std::deque<AbstractWorkerActor *> _wq;
	cml::Mutex _mutex;
	cml::WaitCondition _wcond;
};

}

#endif /* RUNNER_H_ */
