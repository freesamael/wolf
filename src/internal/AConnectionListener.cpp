/**
 * \file AConnectionListener.cpp
 * \date Jun 14, 2010
 * \author samael
 */

#include "AConnectionListener.h"

#include <string>
#include <typeinfo>
#include "CTcpTlvReader.h"
#include "CTlvCommand.h"
#include "XTlvCommand.h"
#include "HelperMacros.h"

using namespace std;

namespace wolf
{

AConnectionListener::AConnectionListener(CTcpServer *server,
		in_port_t lport): _server(server), _listener(_server),
		_listhread(&_listener)
{
	_server->passiveOpen(lport, 10, true);
	_listener.attach(this);
}

/**
 * Start listener.
 */
void AConnectionListener::start()
{
	_listhread.start();
}

/**
 * Set the end condition of listener and wait until it ends.
 */
void AConnectionListener::stop()
{
	_listener.setDone();
	_listhread.join();
}

void AConnectionListener::update(AObservable *o)
{
	// Check observable.
	CTcpConnectionListener *ca;
	if ((ca = dynamic_cast<CTcpConnectionListener*>(o))) {
		// Check socket.
		CTcpSocket *sock;
		if ((sock = ca->lastAcceptedSocket())) {
			// Check message.
			CTcpTlvReader reader(sock);
			ITlvObject *obj;
			if ((obj = reader.readObject())) {
				CTlvCommand *msg;
				if (!(msg = dynamic_cast<CTlvCommand *>(obj))) {
					string type = TYPENAME(obj);
					delete obj;
					throw XTlvCommand(XTlvCommand::INVALID_OBJECT, type);
				} else if (msg->command() != CTlvCommand::HELLO_RUNNER) {
					XTlvCommand x(XTlvCommand::UNEXPECTED_COMMAND, *msg);
					delete msg;
					throw;
				} else {
					// Check nonblocking flag and set to block if needed.
					// The default value might be nonblocking on BSD/Mac.
					if (!sock->blockable())
						sock->setBlockable(true);
					notify(sock);
				}
				delete msg;
			}
		}
	}
}

}
