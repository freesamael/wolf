/**
 * \file CUdpTlvReader.h
 * \date Jul 14, 2010
 * \author samael
 */

#ifndef CUDPTLVREADER_H_
#define CUDPTLVREADER_H_

#include "CUdpSocket.h"
#include "ITlvObject.h"
#include "XSocket.h"

namespace cml
{

class CUdpTlvReader
{
public:
	CUdpTlvReader(CUdpSocket *sock): _sock(sock) {}
	CUdpTlvReader(const CUdpTlvReader &o): _sock(o._sock) {}
	virtual ~CUdpTlvReader();
	inline CUdpTlvReader& operator=(const CUdpTlvReader &o)
			{ _sock = o._sock; return *this; }
//	ITlvObject* recvfrom(CHostAddress *addr, in_port_t *port) throw(XSocket);

private:
	CUdpSocket *_sock;
};

}

#endif /* CUDPTLVREADER_H_ */
