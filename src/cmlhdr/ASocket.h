/**
 * \file ASocket.h
 * \date Mar 8, 2010
 * \author samael
 */

#ifndef ASOCKET_H_
#define ASOCKET_H_

#include <string>
#include "CHostAddress.h"
#include "ISocketState.h"
#include "CMutex.h"

namespace cml
{

/**
 * The abstract socket used for TCP/UDP sockets.
 */
class ASocket
{
public:
	static const std::string &ClosedState;
	static const std::string &ActiveState;
	static const std::string &BoundState;
	static const std::string &ConnectedState;

	ASocket() throw(XSocket, XThread);
	ASocket(const ASocket &sock) throw(XSocket, XThread);
	ASocket(int sockfd) throw(XSocket, XThread);
	/// Destruct ASocket. It automatically closes the socket on destruction.
	virtual ~ASocket() throw();
	/// Assignment.
	ASocket& operator=(const ASocket &sock) throw();

	/// Open the socket without binding or connection.
	virtual void open() throw(XSocket) = 0;
	/// Actively open the socket, which means to connect to a specific host.
	/// It can be called after open(), or called directly without open().
	virtual void activeOpen(const CHostAddress &addr, in_port_t port)
			throw(XSocket) = 0;
	/// Passively open the socket, which means to bind or listen on specific
	/// port. It can be called after open(), or called directly without open().
	/// \param[in] sock Socket.
	/// \param[in] port Local port to bind to.
	/// \param[in] qlen The length of queue. Only applicable to TCP.
	/// \param[in] reuse If true, the socket will be bound to the port even if
	///            the port is in use.
	virtual void passiveOpen(in_port_t port, int qlen = 10, bool reuse = false)
			throw(XSocket) = 0;
	/// Close (and shutdown) the socket.
	inline virtual void close() throw(XSocket) { _state->close(this); }
	/// Read a message. It's not thread-safe unless you use lockread() and
	/// unlockread() in your program.
	/// \return Size of bytes read. Zero indicates connection ends (end-of-file)
	/// or no padding data for non-blocking socket (check socket state to
	/// distinguish them).
	inline virtual ssize_t read(char *buf, size_t size) throw(XSocket)
			{ return _state->read(this, buf, size); }
	/// Write a message. It's not thread-safe unless you use lockwrite() and
	/// unlockwrite().
	/// \return Size of bytes written. Zero indicates connection ends or the
	/// socket is non-blocking but the write operation needs to be delayed.
	inline virtual ssize_t write(const char *buf, size_t size) throw(XSocket)
			{ return _state->write(this, buf, size); }

	/// Lock read operation.
	inline void lockread() throw(XThread) { _rmx.lock(); }
	/// Unlock read operation.
	inline void unlockread() throw(XThread) { _rmx.unlock(); }
	/// Lock write operation.
	inline void lockwrite() throw(XThread) { _wmx.lock(); }
	/// Unlock write operation.
	inline void unlockwrite() throw(XThread) { _wmx.unlock(); }

	/// Set if the socket should be blockable.
	void setBlockable(bool nonblk) throw(XSocket);
	/// Check if the socket is blockable.
	bool blockable() const throw(XSocket);
	/// Get the address currently bound.
	CHostAddress currentAddress() const throw(XSocket);
	/// Get the address of connected peer.
	CHostAddress peerAddress() const throw(XSocket);

	/// Change the socket state.
	inline void changeState(ISocketState *state) throw()
			{ _mx.lock(); _state = state; _mx.unlock(); }
	/// Get current socket state.
	inline ISocketState* state() throw()
			{ _mx.lock(); ISocketState *s = _state; _mx.unlock(); return s; }
	/// Set the socket descriptor.
	inline void setSockfd(int sockfd) throw()
			{ _mx.lock(); _sockfd = sockfd; _mx.unlock(); }
	/// Get the socket descriptor.
	inline int sockfd() throw()
			{ _mx.lock(); int s = _sockfd; _mx.unlock(); return s; }

	static void registerSocketDependant(void (*rls)());

protected:
	int _sockfd;
	CMutex _wmx, _rmx, _mx;
	ISocketState *_state;
};

}

#endif /* ASOCKET_H_ */
