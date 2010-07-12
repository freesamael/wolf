/**
 * \file ISocketState.h
 * \date Apr 5, 2010
 * \author: samael
 */

#ifndef ISOCKETSTATE_H_
#define ISOCKETSTATE_H_

#include <string>
#include <inttypes.h>
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
 * CClosedSocketState, CSimpleActiveSocketState, CBoundSocketState and
 * CConnectedSocketState, respectively.
 *
 * When a CTcpSocket is initialized, it's in closed state. Function
 * passiveOpen() makes it be in bound state, and activeOpen() makes it be in
 * connected state. A CUdpSocket has similar behavior except that it
 * automatically calls open() on construction which turns it into active state.
 * For a CUdpSocket, user can use recvfrom() and sendto() in active state
 * without passiveOpen() or activeOpen().
 */
class ISocketState
{
public:
	virtual ~ISocketState() {}

	/// Simply open the socket.
	virtual void open(ASocket *sock) throw(XSocket) = 0;

	/// Actively open the socket, which means to connect to a specific host.
	/// It can be called after open(), or called directly without open().
	virtual void activeOpen(ASocket *sock, const CHostAddress &addr,
			in_port_t port) throw(XSocket) = 0;

	/// Passively open the socket, which means to bind or listen on specific
	/// port. It can be called after open(), or called directly without open().
	/// \param[in] sock Socket.
	/// \param[in] port Local port to bind to.
	/// \param[in] qlen The length of queue. Only applicable to CTcpSocket.
	/// \param[in] reuse If true, the socket will be bound to the port even if
	///            the port is in use.
	virtual void passiveOpen(ASocket *sock, in_port_t port, int qlen = 10,
			bool reuse = false) throw(XSocket) = 0;

	/// Shutdown and close the socket.
	virtual void close(ASocket *sock) throw(XSocket) = 0;

	/// Accept an incoming connection.
	/// \return Accepted socket, or NULL if no padding connection and the socket
	/// is non-blocking.
	virtual CTcpSocket* accept(ASocket *sock) throw(XSocket) = 0;

	/// Read a message from the socket.
	/// \return Size of bytes read.
	virtual ssize_t read(ASocket *sock, char *buf, size_t size)
		throw(XSocket) = 0;

	/// Write a message to the socket.
	/// \return Size of bytes written.
	virtual ssize_t write(ASocket *sock, const char *buf,
			size_t size) throw(XSocket) = 0;

	/// Receive an incoming message. If the socket is non-blocking and no data
	/// to read, it simpley returns 0.
	/// \return Size of bytes received.
	virtual ssize_t recvfrom(ASocket *sock, char *buf, size_t size,
			CHostAddress *addr, in_port_t *port) throw(XSocket) = 0;

	/// Send a message to given host.
	/// \return Size of bytes sent, or -1 for error.
	virtual ssize_t sendto(ASocket *sock, const char *buf, size_t size,
			const CHostAddress &addr, in_port_t port) throw(XSocket) = 0;

	/// Get the state name.
	virtual const std::string& name() const throw() = 0;
};

}

#endif /* ISOCKETSTATE_H_ */
