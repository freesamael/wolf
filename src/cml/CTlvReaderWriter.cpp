/**
 * \file CTlvReaderWriter.cpp
 * \date Mar 11, 2010
 * \author samael
 */

#include <iostream>
#include <sstream>
#include <cstring>
#include "CTlvReaderWriter.h"
#include "CTlvBlock.h"
#include "ITlvObject.h"
#include "CTlvObjectFactory.h"
#include "HelperMacros.h"

#define SZ_MAXBUF	8192	///< Max buffer size used in recvfrom().

using namespace std;

namespace cml
{

/**
 * Read a TLV object from given TCP socket.
 *
 * \param[in] socket
 * Socket to use. Or NULL to use the default socket given in constructor.
 *
 * \return
 * Object on success, NULL on failure.
 *
 * \note
 * User should delete the returned object manually.
 */
ITlvObject* CTlvReaderWriter::read(CTcpSocket *socket)
{
	char *hdrbuf = new char[ITlvBlock::szHeader];
	int ret;
	CSharedTlvBlock *tmpblk = NULL;
	CTlvBlock blk;
	ITlvObject *obj = NULL;
	CTcpSocket *activesock = (socket == NULL) ?
			dynamic_cast<CTcpSocket *>(_socket) : socket;

	if (!activesock) {
		PERR("No active TCP socket found.");
		delete [] hdrbuf;
		return NULL;
	}

	PINF_3("Reading a TCP message from " <<
			activesock->peerAddress().toString());

	// Read header.
	activesock->lockread();
	if ((ret = activesock->read(hdrbuf, ITlvBlock::szHeader)) == 0) { // End of file.
		activesock->unlockread();
		delete [] hdrbuf;
		return NULL;
	} else if (ret < ITlvBlock::szHeader) {
		activesock->unlockread();
		PERR("Data read from " << activesock->peerAddress().toString() <<
				" is too small to be a TLV block.");
		delete [] hdrbuf;
		return NULL;
	}

	// Read value.
	tmpblk = new CSharedTlvBlock(hdrbuf);
	blk.setType(tmpblk->type());
	blk.setLength(tmpblk->length());
	if ((ret = activesock->read(blk.value(), blk.length())) !=
			blk.length()) {
		activesock->unlockread();
		PERR("Expected " << blk.plainSize() << " bytes but " << ret <<
				" bytes read from " << activesock->peerAddress().toString());
		delete [] hdrbuf;
		delete tmpblk;
		return NULL;
	}

	activesock->unlockread();

	// Construct TLV object.
	obj = CTlvObjectFactory::instance()->createTLVObject(blk);
	if (!obj)
		PERR("Unable to construct TLV object.");

	delete [] hdrbuf;
	delete tmpblk;
	return obj;
}

/**
 * Write a TLV object with given TCP Socket.
 *
 * \param[in] obj
 * Object to write.
 *
 * \param[in] socket
 * Socket to use. Or NULL to use the default socket given in constructor.
 *
 * \return
 * True on success, false otherwise.
 */
bool CTlvReaderWriter::write(const ITlvObject &obj, CTcpSocket *socket)
{
	bool success = false;
	int ret;
	CTlvBlock *blk = obj.toTLVBlock();
	CTcpSocket *activesock = (socket == NULL) ?
			dynamic_cast<CTcpSocket *>(_socket) : socket;

	if (!activesock) {
		PERR("No active TCP socket found.");
		return false;
	}

	if (blk) {
			PINF_3("Sending a TCP message to " <<
					activesock->peerAddress().toString());
			activesock->lockwrite();
			ret = activesock->write(blk->plainBuffer(), blk->plainSize());
			activesock->unlockwrite();
			if (!(success = (ret == (int)blk->plainSize()))) {
				if (ret > 0) {
					PERR("Expected " << blk->plainSize() << " bytes but " <<
							ret << " bytes written to " <<
							activesock->peerAddress().toString());
				} else {
					PERR("Fail to write to " <<
							activesock->peerAddress().toString());
				}
			}
	} else {
		PERR("Unable to create TLV block from given object.");
	}

	delete blk;
	return success;
}

/**
 * Read a TLV object from given UDP socket.
 *
 * \param[out] addr
 * Sender address of the incoming message.
 *
 * \param[out] port
 * Sender port of the incoming message.
 *
 * \param[in] socket
 * Socket to use. Or NULL to use the default socket given in constructor.
 *
 * \return
 * Object on success, NULL on failure.
 *
 * \note
 * User should delete the returned object manually.
 */
ITlvObject* CTlvReaderWriter::recvfrom(CHostAddress *addr, in_port_t *port,
		CUdpSocket *socket)
{
	char *localbuf = NULL;
	int ret;
	CTlvBlock blk;
	CSharedTlvBlock *tmpblk = NULL;
	ITlvObject *obj = NULL;
	CUdpSocket *activesock = (socket == NULL) ?
			dynamic_cast<CUdpSocket *>(_socket) : socket;

	if (!activesock) {
		PERR("No active UDP socket found.");
		return NULL;
	}

	PINF_3("Reading an UDP message.");

	// Read datagram.
	localbuf = new char[SZ_MAXBUF];
	activesock->lockread();
	if ((ret = activesock->recvfrom(localbuf, SZ_MAXBUF, addr, port)) == 0) {
		// End of file.
		activesock->unlockread();
		delete [] localbuf;
		return NULL;
	} else if (ret < ITlvBlock::szHeader) {
		activesock->unlockread();
		PERR("Data read from " << addr->toString() <<
				" is too small to be a TLV block.");
		delete [] localbuf;
		return NULL;
	}
	activesock->unlockread();

	// Construct TLV block.
	tmpblk = new CSharedTlvBlock(localbuf);
	blk.setType(tmpblk->type());
	blk.setLength(tmpblk->length());
	if (ret != blk.plainSize()) {
		PERR("Expected " << blk.plainSize() << " bytes but " << ret <<
				" bytes read from " << addr->toString());
		delete tmpblk;
		return NULL;
	} else {
		memcpy(blk.value(), tmpblk->value(), blk.length());
	}

	// Construct TLV object.
	obj = CTlvObjectFactory::instance()->createTLVObject(blk);
	if (!obj)
		PERR("Unable to construct TLV object.");

	delete tmpblk;
	delete [] localbuf;

	return obj;
}

/**
 * Send a message with given UDP Socket. If the object is too large to fit a
 * UDP packet, the receiver won't successfully construct it.
 *
 * \param[in] obj
 * Object to send.
 *
 * \param[in] addr
 * Address of target.
 *
 * \param[in] port
 * Port of target.
 *
 * \param[in] socket
 * Socket to use. Or NULL to use the default socket given in constructor.
 *
 * \return
 * True on success, false otherwise.
 */
bool CTlvReaderWriter::sendto(const ITlvObject &obj, const CHostAddress &addr,
		in_port_t port, CUdpSocket *socket)
{
	bool success = false;
	int ret;
	CTlvBlock *blk = obj.toTLVBlock();
	CUdpSocket *activesock = (socket == NULL) ?
			dynamic_cast<CUdpSocket *>(_socket) : socket;

	if (!activesock) {
		PERR("No active UDP socket found.");
		return false;
	}

	if (blk) {
		PINF_3("Sending an UDP message to " <<
				activesock->peerAddress().toString());
		activesock->lockwrite();
		ret = activesock->sendto(blk->plainBuffer(), blk->plainSize(),
				addr, port);
		activesock->unlockwrite();
		if (!(success = (ret == (int)blk->plainSize()))) {
			if (ret > 0) {
				PERR("Expected " << blk->plainSize() << " bytes but " <<
						ret << " bytes written to " <<
						activesock->peerAddress().toString());
			} else {
				PERR("Fail to write to " <<
						activesock->peerAddress().toString());
			}
		}
	} else {
		PERR("Unable to create TLV block from given object.");
	}

	delete blk;
	return success;
}

}
