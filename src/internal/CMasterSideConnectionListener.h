/**
 * \file CMasterSideConnectionListener.h
 * \date Apr 28, 2010
 * \author samael
 */

#ifndef CMASTERSIDECONNECTIONLISTENER_H_
#define CMASTERSIDECONNECTIONLISTENER_H_

#include "AConnectionListener.h"
#include "CMaster.h"

namespace wolf
{

/**
 * Master side runner connections listener.
 */
class CMasterSideConnectionListener: public AConnectionListener
{
public:
	CMasterSideConnectionListener(CMaster *master, CTcpServer *server,
			in_port_t lport): AConnectionListener(server, lport),
			_master(master) {}
	void notify(CTcpSocket *sock);
private:
	CMasterSideConnectionListener(const CMasterSideConnectionListener &UNUSED(o)):
		AConnectionListener(NULL, 0), _master(NULL) {}
	CMasterSideConnectionListener& operator=(const CMasterSideConnectionListener
			&UNUSED(o))	{ return *this; }
	CMaster *_master;
};

}

#endif /* CMASTERSIDECONNECTIONLISTENER_H_ */
