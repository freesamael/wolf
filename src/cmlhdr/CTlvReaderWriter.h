/**
 * \file CTlvReaderWriter.h
 * \date Mar 11, 2010
 * \author samael
 */

#ifndef CTlvREADERWRITER_H_
#define CTlvREADERWRITER_H_

#include "ASocket.h"
#include "CUdpSocket.h"
#include "CTcpSocket.h"
#include "ITlvObject.h"

namespace cml
{

/**
 * A reader/writer to send TLV objects to a remote host or receive TLV objects
 * from a remote host.
 */
class CTlvReaderWriter
{
public:
	CTlvReaderWriter(ASocket *socket = NULL, unsigned retrylimit = 10):
		_socket(socket), _retrylimit(retrylimit) {}
	CTlvReaderWriter(const CTlvReaderWriter &o):
		_socket(o._socket), _retrylimit(o._retrylimit) {}
	CTlvReaderWriter& operator=(const CTlvReaderWriter &o)
		{ _socket = o._socket; _retrylimit = o._retrylimit; return *this; }

	// TCP read/write.
	ITlvObject* read(CTcpSocket *socket = NULL);
	bool write(const ITlvObject &obj, CTcpSocket *socket = NULL);

	// UDP read/write.
	ITlvObject* recvfrom(CHostAddress *addr, in_port_t *port,
			CUdpSocket *socket = NULL);
	bool sendto(const ITlvObject &obj, const CHostAddress &addr,
			in_port_t port, CUdpSocket *socket = NULL);

private:
	ASocket *_socket;
	unsigned _retrylimit;
};

}

#endif /* CTLVREADERWRITER_H_ */
