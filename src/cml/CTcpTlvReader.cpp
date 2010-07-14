/**
 * \file CTcpTlvReader.cpp
 * \date Jul 14, 2010
 * \author samael
 */

#include "CTcpTlvReader.h"
#include "CTlvBlock.h"
#include "CTlvObjectFactory.h"

namespace cml
{

/**
 * Read a TLV block from the socket. Applicable to blockable sockets only.
 * \return The incoming block or NULL if connection ends (end-of-file).
 */
ITlvBlock* CTcpTlvReader::readBlock() throw(XSocket, XThread)
{
	int ret;
	char *hdrbuf = new char[ITlvBlock::szHeader];
	CTlvBlock *blk = NULL;

	try {
	_sock->lockread();
		if ((ret = _sock->read(hdrbuf, ITlvBlock::szHeader)) ==
				ITlvBlock::szHeader) {
			// Construct block.
			CSharedTlvBlock sblk(hdrbuf);
			blk = new CTlvBlock(sblk.type(), sblk.length());

			// Read value.
			uint16_t offset = 0;
			do {
				_sock->read(blk->value() + offset, blk->length() - offset);
			} while (offset < blk->length());

			// Cleanup and return.
			_sock->unlockread();
			delete [] hdrbuf;
			return blk;
		} else if (ret == 0) {	// End-of-file.
			// Cleanup and return.
			_sock->unlockread();
			delete [] hdrbuf;
			return NULL;
		}
	} catch (const XSocket &x) {
		// Cleanup and throw.
		_sock->unlockread();
		delete [] hdrbuf;
		delete blk;
		throw x;
	}

	// Unexpected result.
	_sock->unlockread();
	throw XSocket(__PRETTY_FUNCTION__, __LINE__, XSocket::UNKNOWN_ERR);
}

/**
 * Read a TLV object from the socket. Applicable to blockable sockets only.
 * \return The incoming block or NULL if connection ends (end-of-file).
 */
ITlvObject* CTcpTlvReader::readObject() throw(XSocket, XThread, XTlvObject)
{
	ITlvBlock *blk = NULL;
	try {
		if ((blk = readBlock())) {
			// Construct TLV object.
			ITlvObject *obj = CTlvObjectFactory::instance()->
					createTLVObject(*blk);
			delete blk;
			return obj;
		}
	} catch (const XTlvObject &x) {
		// Cleanup and rethrow.
		delete blk;
		throw x;
	}

	// End-of-file.
	return NULL;
}

}
