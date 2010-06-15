/**
 * \file MasterSideConnectionListener.h
 * \date Apr 28, 2010
 * \author samael
 */

#ifndef MASTERSIDECONNECTIONLISTENER_H_
#define MASTERSIDECONNECTIONLISTENER_H_

#include "AbstractConnectionListener.h"
#include "Master.h"

namespace wfe
{

/**
 * Master side runner connections listener.
 */
class MasterSideConnectionListener: public AbstractConnectionListener
{
public:
	MasterSideConnectionListener(Master *master, cml::TCPSocket *lsock,
			uint16_t lport): AbstractConnectionListener(lsock, lport),
			_master(master) {}
	void notify(cml::TCPSocket *sock);
private:
	MasterSideConnectionListener(const MasterSideConnectionListener &UNUSED(o)):
		AbstractConnectionListener(NULL, 0), _master(NULL) {}
	MasterSideConnectionListener& operator=(const MasterSideConnectionListener
			&UNUSED(o))	{ return *this; }
	Master *_master;
};

}

#endif /* MASTERSIDECONNECTIONLISTENER_H_ */
