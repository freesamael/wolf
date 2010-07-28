/**
 * \file CTcpTlvWriter.h
 * \date Jul 14, 2010
 * \author samael
 */

#ifndef CTCPTLVWRITER_H_
#define CTCPTLVWRITER_H_

#include "CTcpSocket.h"
#include "ITlvBlock.h"
#include "ITlvObject.h"
#include "XSocket.h"
#include "XThread.h"
#include "XTlvObject.h"

namespace wolf
{

/**
 * A TLV writer on TCP socket.
 */
class CTcpTlvWriter
{
public:
	CTcpTlvWriter(CTcpSocket *sock): _sock(sock) {}
	CTcpTlvWriter(const CTcpTlvWriter &o): _sock(o._sock) {}
	virtual ~CTcpTlvWriter() {}
	inline CTcpTlvWriter& operator=(const CTcpTlvWriter &o)
			{ _sock = o._sock; return *this; }
	void writeBlock(const ITlvBlock &blk);
	void writeObject(const ITlvObject &obj);

private:
	CTcpSocket *_sock;
};

}

#endif /* CTCPTLVWRITER_H_ */
