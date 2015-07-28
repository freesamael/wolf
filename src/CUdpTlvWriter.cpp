/**
 * \file CUdpTlvWriter.cpp
 * \date Jul 14, 2010
 * \author samael
 */

#include "CUdpTlvWriter.h"

#include <typeinfo>
#include "CmlTLVTypes.h"
#include "HelperMacros.h"

using namespace std;

namespace wolf
{

/**
 * Send a TLV block out through the socket.
 */
void CUdpTlvWriter::sendBlockTo(const ITlvBlock &blk, const CHostAddress &addr,
		in_port_t port)
{
	_sock->lockwrite();
	try {
		_sock->sendto(blk.plainBuffer(), blk.plainSize(), addr, port);
	} catch (XSocket &x) {
		_sock->unlockwrite();
		throw;
	}
	_sock->unlockwrite();
}

/**
 * Send a TLV object out through the socket.
 */
void CUdpTlvWriter::sendObjectTo(const ITlvObject &obj, const CHostAddress &addr,
		in_port_t port)
{
	ITlvBlock *blk = NULL;
	if (!(blk = obj.toTLVBlock())) {
		throw XTlvObject(XTlvObject::NULL_BLOCK_GENERATED, TLV_TYPE_INVALID,
				TYPENAME(obj));
	}

	try {
		sendBlockTo(*blk, addr, port);
	} catch (XSocket &x) {
		delete blk;
		throw;
	} catch (XThread &x) {
		delete blk;
		throw;
	}
	delete blk;
}

}
