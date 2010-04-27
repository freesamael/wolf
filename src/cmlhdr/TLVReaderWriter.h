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
	TLVReaderWriter(AbstractSocket *socket = NULL): _socket(socket) {}
	TLVReaderWriter(const TLVReaderWriter &rw): _socket(rw._socket) {}
	TLVReaderWriter& operator=(const TLVReaderWriter &rw)
		{ _socket = rw._socket; return *this; }

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
};

}

#endif /* TLVREADERWRITER_H_ */
