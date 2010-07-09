/**
 * \file CConnectedSocketState.h
 * \date Apr 5, 2010
 * \author samael
 */

#ifndef CCONNECTEDSOCKETSTATE_H_
#define CCONNECTEDSOCKETSTATE_H_

#include <iostream>
#include <sstream>
#include <vector>
#include "CMutex.h"
#include "ISocketState.h"
#include "HelperMacros.h"

namespace cml
{

/**
 * ConnectedSocketState implements connected state.
 *
 * \see ISocketState
 */
class CConnectedSocketState: public ISocketState
{
	SINGLETON(CConnectedSocketState);
public:
	inline const std::string& name() const { return _statestr; }
	inline CMutex& mutex() { return _mx; }

	bool close(ASocket *sock);
	ssize_t read(ASocket *sock, char *buf, size_t size);
	ssize_t write(ASocket *sock, const char *buf, size_t size);

	/// Unsupported operation with dummy implementation.
	inline bool open(ASocket *UNUSED(sock)) { return false; }
	/// Unsupported operation with dummy implementation.
	inline bool activeOpen(ASocket *UNUSED(sock),
			const CHostAddress &UNUSED(addr), uint16_t UNUSED(port))
			{ return false; }
	/// Unsupported operation with dummy implementation.
	inline bool passiveOpen(ASocket *UNUSED(sock), uint16_t UNUSED(port),
			int UNUSED(qlen)) { return false; }
	/// Unsupported operation with dummy implementation.
	inline CTcpSocket* accept(ASocket *UNUSED(sock)) { return NULL; }
	/// Unsupported operation with dummy implementation.
	inline ssize_t recvfrom(ASocket *UNUSED(sock), char *UNUSED(buf),
			size_t UNUSED(size), CHostAddress *UNUSED(addr),
			uint16_t *UNUSED(port)) { return -1; }
	/// Unsupported operation with dummy implementation.
	inline ssize_t sendto(ASocket *UNUSED(sock), const char *UNUSED(buf),
			size_t UNUSED(size), const CHostAddress &UNUSED(addr),
			uint16_t UNUSED(port)) { return -1; }

private:
	CConnectedSocketState(): SINGLETON_MEMBER_INITLST, _statestr("Connected"),
		_mx() {}
	std::string _statestr;
	CMutex _mx;
};

}

#endif /* CCONNECTEDSOCKETSTATE_H_ */
