/**
 * \file MasterSideRunnerCommandListener.h
 * \date Jun 3, 2010
 * \author samael
 */

#ifndef MASTERSIDERUNNERCOMMANDLISTENER_H_
#define MASTERSIDERUNNERCOMMANDLISTENER_H_

#include "IRunnable.h"
#include "Master.h"
#include "TLVCommand.h"

namespace wfe
{

class MasterSideRunnerCommandListener: public cml::IRunnable
{
public:
	MasterSideRunnerCommandListener(Master *master, cml::TCPSocket *rsock):
		_done(false), _master(master), _rsock(rsock) {}
	MasterSideRunnerCommandListener(const MasterSideRunnerCommandListener &o):
		_done(o._done), _master(o._master), _rsock(o._rsock) {}
	MasterSideRunnerCommandListener& operator=(const MasterSideRunnerCommandListener &o)
		{ _done = o._done; _master = o._master; _rsock = o._rsock; return *this;}
	inline void setDone() { _done = true; }
	void run();
	void process(TLVCommand *cmd);

private:
	bool _done;
	Master *_master;
	cml::TCPSocket *_rsock;
};

}

#endif /* MASTERSIDERUNNERCOMMANDLISTENER_H_ */
