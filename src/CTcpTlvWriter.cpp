/**
 * \file CTcpTlvWriter.cpp
 * \date Jul 14, 2010
 * \author samael
 */

#include <typeinfo>
#include <string>
#include "CTcpTlvWriter.h"
#include "CmlTLVTypes.h"
#include "HelperMacros.h"

using namespace std;

namespace wolf
{

/**
 * Write a TLV block to the socket.
 */
void CTcpTlvWriter::writeBlock(const ITlvBlock &blk) 
{
	uint16_t offset = 0;
	_sock->lockwrite();
	try {
		// Loop until all data have been written.
		do {
			offset += _sock->write(blk.plainBuffer() + offset,
					blk.plainSize() - offset);
		} while (offset < blk.plainSize());
	} catch (XSocket &x) {
		// Cleanup and rethrow.
		_sock->unlockwrite();
		throw;
	}
	_sock->unlockwrite();
}

/**
 * Write a TLV object to the socket.
 */
void CTcpTlvWriter::writeObject(const ITlvObject &obj)
		
{
	ITlvBlock *blk;
	if (!(blk = obj.toTLVBlock())) {
		throw XTlvObject(XTlvObject::NULL_BLOCK_GENERATED, TLV_TYPE_INVALID,
				TYPENAME(obj));
	}

	try {
		writeBlock(*blk);
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
