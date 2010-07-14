/**
 * \file CTcpTlvWriter.cpp
 * \date Jul 14, 2010
 * \author samael
 */

#include <typeinfo>
#include "CTcpTlvWriter.h"
#include "CmlTLVTypes.h"

using namespace std;

namespace cml
{

/**
 * Write a TLV block to the socket.
 */
void CTcpTlvWriter::writeBlock(const ITlvBlock &blk) throw(XSocket, XThread)
{
	uint16_t offset = 0;
	_sock->lockwrite();
	try {
		// Loop until all data have been written.
		do {
			offset += _sock->write(blk.plainBuffer() + offset,
					blk.plainSize() - offset);
		} while (offset < blk.plainSize());
	} catch (const XSocket &x) {
		// Cleanup and rethrow.
		_sock->unlockwrite();
		throw x;
	}
	_sock->unlockwrite();
}

void CTcpTlvWriter::writeObject(const ITlvObject &obj)
		throw(XSocket, XThread, XTlvObject)
{
	ITlvBlock *blk;
	if (!(blk = obj.toTLVBlock())) {
		throw XTlvObject(__PRETTY_FUNCTION__, __LINE__,
				XTlvObject::NULL_BLOCK_GENERATED, TLV_TYPE_INVALID,
				typeid(obj).name());
	}

	try {
		writeBlock(*blk);
	} catch (const XSocket &x) {
		delete blk;
		throw x;
	} catch (const XThread &x) {
		delete blk;
		throw x;
	}
}

}
