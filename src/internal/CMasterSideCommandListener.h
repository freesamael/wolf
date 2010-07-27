/**
 * \file CMasterSideCommandListener.h
 * \date Jun 3, 2010
 * \author samael
 */

#ifndef CMASTERSIDECOMMANDLISTENER_H_
#define CMASTERSIDECOMMANDLISTENER_H_

#include "ACommandListener.h"
#include "CMaster.h"

namespace wolf
{

/**
 * Master side commands listener.
 */
class CMasterSideCommandListener: public ACommandListener
{
public:
	CMasterSideCommandListener(CMaster *master, wolf::CTcpSocket *sock):
		ACommandListener(sock), _master(master) {}
	CMasterSideCommandListener(const CMasterSideCommandListener &o):
		ACommandListener(o), _master(o._master) {}
	CMasterSideCommandListener& operator=(const CMasterSideCommandListener &o)
		{ ACommandListener::operator=(o); _master = o._master;
		return *this; }
	void process(CTlvCommand *cmd);

private:
	CMaster *_master;
};

}

#endif /* CMASTERSIDECOMMANDLISTENER_H_ */
