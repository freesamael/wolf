/**
 * \file CUdpTlvWriter.h
 * \date Jul 14, 2010
 * \author samael
 */

#ifndef CUDPTLVWRITER_H_
#define CUDPTLVWRITER_H_

#include "CUdpSocket.h"
#include "ITlvBlock.h"
#include "ITlvObject.h"
#include "XSocket.h"
#include "XThread.h"
#include "XTlvObject.h"

namespace wolf
{

/**
 * TLV writer on UDP socket.
 */
class CUdpTlvWriter
{
public:
	CUdpTlvWriter(CUdpSocket *sock): _sock(sock) {}
	CUdpTlvWriter(const CUdpTlvWriter &o): _sock(o._sock) {}
	virtual ~CUdpTlvWriter() {}
	inline CUdpTlvWriter& operator=(const CUdpTlvWriter &o)
			{ _sock = o._sock; return *this; }
	void sendBlockTo(const ITlvBlock &blk, const CHostAddress &addr,
			in_port_t port) ;
	void sendObjectTo(const ITlvObject &obj, const CHostAddress &addr,
			in_port_t port) ;

private:
	CUdpSocket *_sock;
};

}

#endif /* CUDPTLVWRITER_H_ */
