/**
 * \file CUdpTlvWriter.cpp
 * \date Jul 14, 2010
 * \author samael
 */

#include <typeinfo>
#include "CUdpTlvWriter.h"
#include "CmlTLVTypes.h"

using namespace std;

namespace cml
{

/**
 * Send a TLV block out through the socket.
 */
void CUdpTlvWriter::sendBlockTo(const ITlvBlock &blk, const CHostAddress &addr,
		in_port_t port) throw(XSocket, XThread)
{
	_sock->lockwrite();
	try {
		_sock->sendto(blk.plainBuffer(), blk.plainSize(), addr, port);
	} catch (const XSocket &x) {
		_sock->unlockwrite();
		throw x;
	}
	_sock->unlockwrite();
}

/**
 * Send a TLV object out through the socket.
 */
void CUdpTlvWriter::sendObjectTo(const ITlvObject &obj, const CHostAddress &addr,
		in_port_t port) throw(XSocket, XThread, XTlvObject)
{
	ITlvBlock *blk = NULL;
	if (!(blk = obj.toTLVBlock())) {
		throw XTlvObject(__PRETTY_FUNCTION__, __LINE__,
				XTlvObject::NULL_BLOCK_GENERATED, TLV_TYPE_INVALID,
				typeid(obj).name());
	}

	try {
		sendBlockTo(*blk, addr, port);
	} catch (const XSocket &x) {
		delete blk;
		throw x;
	} catch (const XThread &x) {
		delete blk;
		throw x;
	}
}

}
