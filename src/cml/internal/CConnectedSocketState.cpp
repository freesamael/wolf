/**
 * \file CConnectedSocketState.cpp
 * \date Apr 5, 2010
 * \author samael
 */

#include <cstdio>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "CConnectedSocketState.h"
#include "CClosedSocketState.h"
#include "CTcpSocket.h"
#include "CSingletonAutoDestructor.h"

using namespace std;

namespace cml
{

SINGLETON_REGISTRATION(CConnectedSocketState);
SINGLETON_REGISTRATION_END();

bool CConnectedSocketState::close(ASocket *sock)
{
	PINF_3("Shutting down a socket.");
	if (shutdown(sock->sockfd(), SHUT_RDWR) != 0) {
		perror("Error: ConnectedSocketState::close(): shutdown");
		return false;
	}

	PINF_3("Closing a socket.");
	if (::close(sock->sockfd()) != 0) {
		perror("Error: ConnectedSocketState::close(): close");
		return false;
	}

	sock->changeState(CClosedSocketState::instance());
	return true;
}

ssize_t CConnectedSocketState::read(ASocket *sock, char *buf, size_t size)
{
	ssize_t result;
	if ((result = ::read(sock->sockfd(), buf, size)) < 0)
		perror("Error: ConnectedSocketState::read()");
	PINF_3(result << " bytes read.");
	return result;
}

ssize_t CConnectedSocketState::write(ASocket *sock, const char *buf,
		size_t size)
{
	ssize_t result;
	if ((result = ::write(sock->sockfd(), buf, size)) < 0)
		perror("Error: ConnectedSocketState::write()");
	PINF_3(result << " bytes written.");
	return result;

}

}
