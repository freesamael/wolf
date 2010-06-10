/**
 * \file MasterSideCommandListener.h
 * \date Jun 3, 2010
 * \author samael
 */

#ifndef MASTERSIDECOMMANDLISTENER_H_
#define MASTERSIDECOMMANDLISTENER_H_

#include "IRunnable.h"
#include "Master.h"
#include "TLVCommand.h"

namespace wfe
{

class MasterSideCommandListener: public cml::IRunnable
{
public:
	MasterSideCommandListener(Master *master, cml::TCPSocket *rsock):
		_done(false), _master(master), _rsock(rsock) {}
	MasterSideCommandListener(const MasterSideCommandListener &o):
		_done(o._done), _master(o._master), _rsock(o._rsock) {}
	MasterSideCommandListener& operator=(const MasterSideCommandListener &o)
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

#endif /* MASTERSIDECOMMANDLISTENER_H_ */
