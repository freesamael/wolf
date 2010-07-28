/**
 * \file CTcpTlvReader.h
 * \date Jul 14, 2010
 * \author samael
 */

#ifndef CTCPTLVREADER_H_
#define CTCPTLVREADER_H_

#include "CTcpSocket.h"
#include "ITlvBlock.h"
#include "ITlvObject.h"
#include "XSocket.h"
#include "XThread.h"
#include "XTlvObject.h"

namespace wolf
{

/**
 * A TLV reader on TCP socket.
 */
class CTcpTlvReader
{
public:
	CTcpTlvReader(CTcpSocket *sock): _sock(sock) {}
	CTcpTlvReader(const CTcpTlvReader &o): _sock(o._sock) {}
	virtual ~CTcpTlvReader() {}
	inline CTcpTlvReader& operator=(const CTcpTlvReader &o)
			{ _sock = o._sock; return *this; }
	ITlvBlock* readBlock();
	ITlvObject* readObject();

private:
	CTcpSocket *_sock;
};

}

#endif /* CTCPTLVREADER_H_ */
