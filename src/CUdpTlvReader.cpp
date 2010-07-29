/**
 * \file CUdpTlvReader.cpp
 * \date Jul 14, 2010
 * \author samael
 */

#include <cstring>
#include "CUdpTlvReader.h"
#include "HelperMacros.h"
#include "CTlvBlock.h"
#include "CTlvObjectFactory.h"

using namespace std;

namespace wolf
{

/**
 * Read a TLV block from the socket. Applicable to blockable sockets only.
 * \return Incoming block.
 */
ITlvBlock* CUdpTlvReader::recvBlockFrom(CHostAddress *addr, in_port_t *port)
		
{
	char *buf = new char[SZ_MSG_MAX];
	unsigned sz = 0;

	// Read a message.
	_sock->lockread();
	try {
		sz = _sock->recvfrom(buf, ITlvBlock::szHeader, addr, port);
	} catch (XSocket &x) {
		_sock->unlockread();
		delete [] buf;
		throw;
	}
	_sock->unlockread();

	// Check if message size is long enough for header.
	if (sz < ITlvBlock::szHeader)
		throw XTlvObject(XTlvObject::BLOCK_TOO_SHORT);

	// Check if message size is long enough for whole block.
	CSharedTlvBlock sblk(buf);
	if (sz < sblk.plainSize()) {
		delete [] buf;
		throw XTlvObject(XTlvObject::BLOCK_TOO_SHORT);
	}

	CTlvBlock *blk = new CTlvBlock(sblk.type(), sblk.length());
	memcpy(blk->value(), sblk.value(), sblk.length());

	delete [] buf;
	return blk;
}

/**
 * Read a TLV block from the socket. Applicable to blockable sockets only.
 * \return Incoming object.
 */
ITlvObject* CUdpTlvReader::recvObjectFrom(CHostAddress *addr, in_port_t *port)
		
{
	ITlvBlock *blk = recvBlockFrom(addr, port);
	ITlvObject *obj = NULL;
	try {
		obj = CTlvObjectFactory::instance()->createTLVObject(*blk);
	} catch (XTlvObject &x) {
		delete blk;
		throw;
	}
	delete blk;
	return obj;
}

}
