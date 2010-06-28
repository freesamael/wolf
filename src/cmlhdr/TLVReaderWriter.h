/**
 * \file TLVReaderWriter.h
 * \date Mar 11, 2010
 * \author samael
 */

#ifndef TLVREADERWRITER_H_
#define TLVREADERWRITER_H_

#include "AbstractSocket.h"
#include "UDPSocket.h"
#include "TCPSocket.h"

namespace cml
{

/**
 * A reader/writer to send TLV objects to a remote host or receive TLV objects
 * from a remote host.
 */
class TLVReaderWriter
{
public:
	TLVReaderWriter(AbstractSocket *socket = NULL, unsigned retrylimit = 10):
		_socket(socket), _retrylimit(retrylimit) {}
	TLVReaderWriter(const TLVReaderWriter &o):
		_socket(o._socket), _retrylimit(o._retrylimit) {}
	TLVReaderWriter& operator=(const TLVReaderWriter &o)
		{ _socket = o._socket; _retrylimit = o._retrylimit; return *this; }

	// TCP read/write.
	ITLVObject* read(TCPSocket *socket = NULL);
	bool write(const ITLVObject &obj, TCPSocket *socket = NULL);

	// UDP read/write.
	ITLVObject* recvfrom(HostAddress *addr, uint16_t *port,
			UDPSocket *socket = NULL);
	bool sendto(const ITLVObject &obj, const HostAddress &addr,
			uint16_t port, UDPSocket *socket = NULL);

private:
	AbstractSocket *_socket;
	unsigned _retrylimit;
};

}

#endif /* TLVREADERWRITER_H_ */
