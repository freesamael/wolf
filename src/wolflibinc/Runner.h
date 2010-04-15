/**
 * \file Runner.h
 * \date Apr 1, 2010
 * \author samael
 */

#ifndef RUNNER_H_
#define RUNNER_H_

#include <string>
#include <HostAddress.h>
#include <TCPSocket.h>
#include "TLVMessage.h"

namespace wfe
{

class Runner
{
public:
	/// Execute the runner with given ports and application name.
	void run(unsigned short runner_port, unsigned short master_port, const
			std::string &appname);
private:
	cml::HostAddress getMasterAddr(unsigned short runner_port);
	bool connectToMaster(cml::TCPSocket *sock, const cml::HostAddress &addr,
			unsigned short master_port);
	bool joinGroup(const std::string &appname);
	bool processCommand(TLVMessage *msg);
	void runnerLoop(cml::TCPSocket *sock);
	bool _endf;
};

}

#endif /* RUNNER_H_ */
