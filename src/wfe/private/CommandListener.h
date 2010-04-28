/**
 * \file CommandListener.h
 * \date Apr 28, 2010
 * \author samael
 */

#ifndef COMMANDLISTENER_H_
#define COMMANDLISTENER_H_

#include <TCPSocket.h>
#include "TLVMessage.h"

namespace wfe
{

class CommandListener
{
public:
	CommandListener(cml::TCPSocket *sock): _done(false), _sock(sock) {}
	CommandListener(const CommandListener &o): _done(o._done), _sock(o._sock) {}
	CommandListener& operator=(const CommandListener &o)
		{ _done = o._done; _sock = o._sock; return *this; }
	void run();

private:
	bool processCommand(TLVMessage *cmd);
	bool _done;
	cml::TCPSocket *_sock;
};

}

#endif /* COMMANDLISTENER_H_ */
