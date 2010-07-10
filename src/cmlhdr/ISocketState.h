/**
 * \file ISocketState.h
 * \date Apr 5, 2010
 * \author: samael
 */

#ifndef ISOCKETSTATE_H_
#define ISOCKETSTATE_H_

#include <string>
#include <stdint.h>
#include "CHostAddress.h"
#include "XSocket.h"

namespace cml
{

class ASocket;
class CTcpSocket;

/**
 * \interface ISocketState
 *
 * It represents stateful socket status. There are 4 possible states - closed,
 * active, bound and connected, and the corresponding classes are
 * ClosedSocketState, SimpleActiveSocketState, BoundSocketState and
 * ConnectedSocketState, respectively.
 *
 * When a TCPSocket is initialized, it's in closed state. When it's opened
 * passively by passiveOpen(), it's active and then becomes in bound state
 * immediately. When it's opened actively by activeOpen(), it's active and then
 * becomes in connected state. A UDPSocket has similar behavior except that it
 * automatically calls open() on construction which turns it into active state.
 * For a UDPSocket, user can use recvfrom() and sendto() in active state without
 * passiveOpen() or activeOpen().
 */
class ISocketState
{
public:
	virtual ~ISocketState() {}

	/// Simply open the socket.
	/// \return True on success, false otherwise.
	virtual bool open(ASocket *sock) throw(XSocket) = 0;

	/// Actively open the socket, which means connect to a specific host.
	/// It can be called after open(), or called directly without open().
	/// \return True on success, false otherwise.
	virtual bool activeOpen(ASocket *sock, const CHostAddress &addr,
			uint16_t port) throw(XSocket) = 0;

	/// Passively open the socket, which means bind or listen on specific port.
	/// It can be called after open(), or called directly without open().
	/// \return True on success, false otherwise.
	virtual bool passiveOpen(ASocket *sock, uint16_t port,
			int qlen = 10) throw(XSocket) = 0;

	/// Shutdown and close the socket.
	/// \return True on success, false otherwise.
	virtual bool close(ASocket *sock) throw(XSocket) = 0;

	/// Accept an incoming connection.
	/// \return Accepted socket, or NULL for error or no padding connection if
	/// the socket is non-blocking.
	virtual CTcpSocket* accept(ASocket *sock) throw(XSocket) = 0;

	/// Read a message from the socket.
	/// \return Size of bytes read, or -1 for error.
	virtual ssize_t read(ASocket *sock, char *buf, size_t size)
		throw(XSocket) = 0;

	/// Write a message to the socket.
	/// \return Size of bytes written, or -1 for error.
	virtual ssize_t write(ASocket *sock, const char *buf,
			size_t size) throw(XSocket) = 0;

	/// Receive an incoming message.
	/// \return Size of bytes received, or -1 for error.
	virtual ssize_t recvfrom(ASocket *sock, char *buf, size_t size,
			CHostAddress *addr, uint16_t *port) throw(XSocket) = 0;

	/// Send a message to given host.
	/// \return Size of bytes sent, or -1 for error.
	virtual ssize_t sendto(ASocket *sock, const char *buf, size_t size,
			const CHostAddress &addr, uint16_t port) throw(XSocket) = 0;

	/// Get the state name.
	virtual const std::string& name() const throw() = 0;
};

}

#endif /* ISOCKETSTATE_H_ */
