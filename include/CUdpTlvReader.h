/**
 * \file CUdpTlvReader.h
 * \date Jul 14, 2010
 * \author samael
 */

#ifndef CUDPTLVREADER_H_
#define CUDPTLVREADER_H_

#include "CUdpSocket.h"
#include "ITlvBlock.h"
#include "ITlvObject.h"
#include "XSocket.h"
#include "XThread.h"
#include "XTlvObject.h"

namespace wolf
{

/**
 * TLV reader on UDP socket.
 */
class CUdpTlvReader
{
public:
	CUdpTlvReader(CUdpSocket *sock): _sock(sock) {}
	CUdpTlvReader(const CUdpTlvReader &o): _sock(o._sock) {}
	virtual ~CUdpTlvReader() {}
	inline CUdpTlvReader& operator=(const CUdpTlvReader &o)
			{ _sock = o._sock; return *this; }
	ITlvBlock* recvBlockFrom(CHostAddress *addr, in_port_t *port)
			;
	ITlvObject* recvObjectFrom(CHostAddress *addr, in_port_t *port)
			;

private:
	CUdpSocket *_sock;
};

}

#endif /* CUDPTLVREADER_H_ */
