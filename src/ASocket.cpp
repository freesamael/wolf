/**
 * \file ASocket.cpp
 * \date Mar 8, 2010
 * \author samael
 */

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "ASocket.h"
#include "internal/CClosedSocketState.h"
#include "internal/CSimpleActiveSocketState.h"
#include "internal/CBoundSocketState.h"
#include "internal/CConnectedSocketState.h"
#include "HelperMacros.h"

using namespace std;

namespace wolf
{

const string &ASocket::ClosedState = CClosedSocketState::instance()->name();
const string &ASocket::ActiveState = CSimpleActiveSocketState::instance()->name();
const string &ASocket::BoundState = CBoundSocketState::instance()->name();
const string &ASocket::ConnectedState = CConnectedSocketState::instance()->name();

ASocket::ASocket() :
		_sockfd(0), _wmx(), _rmx(), _mx(), _state(CClosedSocketState::instance())
{
}

ASocket::ASocket(const ASocket &sock) :
		_sockfd(sock._sockfd), _wmx(), _rmx(), _mx(), _state(sock._state)
{
}

ASocket::ASocket(int sockfd) :
		_sockfd(sockfd), _wmx(), _rmx(), _mx(),
		_state(CSimpleActiveSocketState::instance())
{
}

ASocket::~ASocket() 
{
	try {
		_state->close(this);
	} catch (const XSocket &x) {
		if (!(x.xtype() == XSocket::INVALID_SOCKET_STATE &&
				_state->name() == ClosedState))
			PERR(x.toString());
	}
}

ASocket& ASocket::operator=(const ASocket &sock) 
{
	_sockfd = sock._sockfd;
	_state = sock._state;
	return *this;
}

void ASocket::setBlockable(bool blk) 
{
	int arg;

	// Get arg.
	if ((arg = fcntl(_sockfd, F_GETFL, NULL)) == -1)
		throw XSocket(errno);

	// Change arg.
	if (!blk)
		arg |= O_NONBLOCK;
	else
		arg &= (~O_NONBLOCK);

	// Set arg.
	if ((fcntl(_sockfd, F_SETFL, arg)) == -1) {
		throw XSocket(errno);
	}
}

bool ASocket::blockable() const 
{
	int arg;

	// Get arg.
	if ((arg = fcntl(_sockfd, F_GETFL, NULL)) == -1)
		throw XSocket(errno);

	return !(arg & O_NONBLOCK);
}

CHostAddress ASocket::currentAddress() const 
{
	sockaddr_in inaddr;
	socklen_t len = sizeof(inaddr);
	if (getsockname(_sockfd, (sockaddr *)&inaddr, &len) != 0)
		throw XSocket(errno);
	return CHostAddress(inaddr.sin_addr.s_addr);
}

CHostAddress ASocket::peerAddress() const 
{
	sockaddr_in inaddr;
	socklen_t len = sizeof(inaddr);
	if (getpeername(_sockfd, (sockaddr *)&inaddr, &len) != 0)
		throw XSocket(errno);
	return CHostAddress(inaddr.sin_addr.s_addr);
}

/**
 * Register a release() function of a singleton object to all singleton socket
 * objects. It's used by SINGLETON_DEPENDS_SOCKET() macro, and is not supposed
 * to be called manually by users.
 */
void ASocket::registerSocketDependant(void (*rls)())
{
	CClosedSocketState::instance()->registerDependant(rls);
	CSimpleActiveSocketState::instance()->registerDependant(rls);
	CBoundSocketState::instance()->registerDependant(rls);
	CConnectedSocketState::instance()->registerDependant(rls);
}

}
