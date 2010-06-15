/**
 * \file MasterSideCommandListener.h
 * \date Jun 3, 2010
 * \author samael
 */

#ifndef MASTERSIDECOMMANDLISTENER_H_
#define MASTERSIDECOMMANDLISTENER_H_

#include "AbstractCommandListener.h"
#include "Master.h"

namespace wfe
{

/**
 * Master side commands listener.
 */
class MasterSideCommandListener: public AbstractCommandListener
{
public:
	MasterSideCommandListener(Master *master, cml::TCPSocket *sock):
		AbstractCommandListener(sock), _master(master) {}
	MasterSideCommandListener(const MasterSideCommandListener &o):
		AbstractCommandListener(o), _master(o._master) {}
	MasterSideCommandListener& operator=(const MasterSideCommandListener &o)
		{ AbstractCommandListener::operator=(o); _master = o._master;
		return *this; }
	void process(TLVCommand *cmd);

private:
	Master *_master;
};

}

#endif /* MASTERSIDECOMMANDLISTENER_H_ */
