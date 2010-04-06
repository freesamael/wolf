/*
 * ISocketState.h
 *
 *  Created on: Apr 5, 2010
 *      Author: samael
 */

#ifndef ISOCKETSTATE_H_
#define ISOCKETSTATE_H_

#include <string>
#include "HostAddress.h"

namespace cml
{

class AbstractSocket;
class TCPSocket;
class ISocketState
{
public:
	/// Actively open the socket, which means connect to a specific host.
	/// \return True on success, false otherwise.
	virtual bool activeOpen(AbstractSocket *sock, const HostAddress &addr,
			unsigned short port) = 0;

	/// Passively open the socket, which means bind or listen on specific port.
	/// \return True on success, false otherwise.
	virtual bool passiveOpen(AbstractSocket *sock, unsigned short port,
			int qlen = 10) = 0;

	/// Shutdown and close the socket.
	/// \return True on success, false otherwise.
	virtual bool close(AbstractSocket *sock) = 0;

	/// Accept an incoming connection.
	/// \return Accepted socket, or NULL for error or no padding connection if
	/// the socket is non-blocking.
	virtual TCPSocket* accept(AbstractSocket *sock) = 0;

	/// Read a message from the socket.
	/// \return Size of bytes read, or -1 for error.
	virtual ssize_t read(AbstractSocket *sock, char *buf, size_t size) = 0;

	/// Write a message to the socket.
	/// \return Size of bytes written, or -1 for error.
	virtual ssize_t write(AbstractSocket *sock, const char *buf,
			size_t size) = 0;

	/// Receive an incoming message.
	/// \return Size of bytes received, or -1 for error.
	virtual ssize_t recvfrom(AbstractSocket *sock, char *buf, size_t size,
			HostAddress *addr, unsigned short *port) = 0;

	/// Send a message to given host.
	/// \return Size of bytes sent, or -1 for error.
	virtual ssize_t sendto(AbstractSocket *sock, const char *buf, size_t size,
			const HostAddress &addr, unsigned short port) = 0;

	/// Get the state string.
	virtual const std::string& toString() const = 0;
};

}

#endif /* ISOCKETSTATE_H_ */
