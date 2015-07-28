/**
 * \file ISocketState.h
 * \date Apr 5, 2010
 * \author: samael
 */

#ifndef ISOCKETSTATE_H_
#define ISOCKETSTATE_H_

#include <string>
#include <netinet/in.h>
#include "CHostAddress.h"
#include "XSocket.h"

namespace wolf
{

class ASocket;

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
	typedef enum SocketType {
		TCP,
		UDP
	} SocketType;

	virtual ~ISocketState() {}

	/// Simply open the socket.
	virtual void open(ASocket *sock, SocketType type)  = 0;

	/// Actively open the socket, which means to connect to a specific host.
	/// It can be called after open(), or called directly without open().
	virtual void activeOpen(ASocket *sock, SocketType type,
			const CHostAddress &addr, in_port_t port)  = 0;

	/// Passively open the socket, which means to bind or listen on specific
	/// port. It can be called after open(), or called directly without open().
	/// \param[in] sock Socket.
	/// \param[in] port Local port to bind to.
	/// \param[in] qlen The length of queue. Only applicable to TCP.
	/// \param[in] reuse If true, the socket will be bound to the port even if
	///            the port is in use.
	virtual void passiveOpen(ASocket *sock, SocketType type, in_port_t port,
			int qlen = 10, bool reuse = false)  = 0;

	/// Shutdown and close the socket.
	virtual void close(ASocket *sock)  = 0;

	/// Accept an incoming connection.
	/// \note Only applicable to TCP.
	/// \return Accepted socket descriptor, or -1 if the socket is non-blocking
	/// and no padding connection was found.
	virtual int accept(ASocket *sock)  = 0;

	/// Read a message from the socket.
	/// \return Size of bytes read. Zero indicates connection ends (end-of-file)
	/// or no padding data for non-blocking socket (check socket state to
	/// distinguish them).
	virtual ssize_t read(ASocket *sock, char *buf, size_t size)
		 = 0;

	/// Write a message to the socket.
	/// \return Size of bytes written. Zero indicates connection ends or the
	/// socket is non-blocking but the write operation needs to be delayed.
	virtual ssize_t write(ASocket *sock, const char *buf,
			size_t size)  = 0;

	/// Receive an incoming message. If the socket is non-blocking and there's
	/// no data to read, it simpley returns 0.
	/// \note Only applicable to UDP.
	/// \return Size of bytes received.
	virtual ssize_t recvfrom(ASocket *sock, char *buf, size_t size,
			CHostAddress *addr, in_port_t *port)  = 0;

	/// Send a message to given host.
	/// \note Only applicable to UDP.
	/// \return Size of bytes sent.
	virtual ssize_t sendto(ASocket *sock, const char *buf, size_t size,
			const CHostAddress &addr, in_port_t port)  = 0;

	/// Get the state name.
	virtual const std::string& name() const  = 0;
};

}

#endif /* ISOCKETSTATE_H_ */
