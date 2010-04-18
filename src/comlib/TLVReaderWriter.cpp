/**
 * \file TLVReaderWriter.cpp
 * \date Mar 11, 2010
 * \author samael
 */

#include <cstdio>
#include <cstring>
#include "TLVReaderWriter.h"
#include "TLVBlock.h"
#include "ITLVObject.h"
#include "TLVObjectFactory.h"
#include "HelperMacros.h"

#define SZ_MAXBUF	8192	///< Max buffer size used in recvfrom().

using namespace std;

namespace cml
{

TLVReaderWriter::TLVReaderWriter(AbstractSocket *socket):
		_socket(socket)
{
}

TLVReaderWriter::~TLVReaderWriter()
{
}

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
ITLVObject* TLVReaderWriter::read(TCPSocket *socket)
{
	char *hdrbuf = new char[ITLVBlock::szHeader];
	int ret;
	SharedTLVBlock *tmpblk = NULL;
	StandardTLVBlock blk;
	ITLVObject *obj = NULL;
	TCPSocket *activesock = (socket == NULL) ?
			dynamic_cast<TCPSocket *>(_socket) : socket;

	if (!activesock) {
		PERR << "No active TCP socket found.\n";
		return NULL;
	}

	PINFO("Reading a message from TCP socket.");

	// Read header.
	if ((ret = activesock->read(hdrbuf, ITLVBlock::szHeader)) == 0) { // End of file.
		delete [] hdrbuf;
		return NULL;
	} else if (ret < ITLVBlock::szHeader) {
		PERR << "Data read is too small to be a TLV block.\n";
		delete [] hdrbuf;
		return NULL;
	}

	// Read value.
	tmpblk = new SharedTLVBlock(hdrbuf);
	blk.setType(tmpblk->type());
	blk.setLength(tmpblk->length());
	if ((ret = activesock->read(blk.value(), blk.length())) !=
			blk.length()) {
		PERR << "Expected " << blk.plainSize() << " bytes but " << ret <<
				" bytes read.\n";
		delete [] hdrbuf;
		delete tmpblk;
		return NULL;
	}

	// Construct TLV object.
	obj = TLVObjectFactory::instance()->createTLVObject(blk);
	if (!obj)
		PERR << "Unable to construct TLV object.\n";

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
bool TLVReaderWriter::write(const ITLVObject &obj, TCPSocket *socket)
{
	bool success = false;
	int ret;
	StandardTLVBlock *blk = obj.toTLVBlock();
	TCPSocket *activesock = (socket == NULL) ?
			dynamic_cast<TCPSocket *>(_socket) : socket;

	if (!activesock) {
		PERR << "No active TCP socket found.\n";
		return false;
	}

	if (blk) {
		PINFO("Sending a message to TCP socket.");
		ret = activesock->write(blk->plainBuffer(), blk->plainSize());
		if (!(success = (ret == (int)blk->plainSize()))) {
			if (ret > 0) {
				PERR << "Expected " << blk->plainSize() << " bytes but " <<
						ret << " bytes written.\n";
			} else {
				PERR << "Fail to write.\n";
			}
		}
	} else {
		PERR << "Unable to create TLV block from given object.\n";
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
ITLVObject* TLVReaderWriter::recvfrom(HostAddress *addr, uint16_t *port,
		UDPSocket *socket)
{
	char *localbuf = NULL;
	int ret;
	StandardTLVBlock blk;
	SharedTLVBlock *tmpblk = NULL;
	ITLVObject *obj = NULL;
	UDPSocket *activesock = (socket == NULL) ?
			dynamic_cast<UDPSocket *>(_socket) : socket;

	if (!activesock) {
		PERR << "No active UDP socket found.\n";
		return NULL;
	}

	PINFO("Reading a message from UDP socket.");

	// Read datagram.
	localbuf = new char[SZ_MAXBUF];
	if ((ret = activesock->recvfrom(localbuf, SZ_MAXBUF, addr, port)) == 0) {
		// End of file.
		delete [] localbuf;
		return NULL;
	} else if (ret < ITLVBlock::szHeader) {
		PERR << "Data read is too small to be a TLV block.\n";
		delete [] localbuf;
		return NULL;
	}

	// Construct TLV block.
	tmpblk = new SharedTLVBlock(localbuf);
	blk.setType(tmpblk->type());
	blk.setLength(tmpblk->length());
	if (ret != blk.plainSize()) {
		PERR << "Expected " << blk.plainSize() << " bytes but " << ret <<
				" bytes read.\n";
		delete tmpblk;
		return NULL;
	} else {
		memcpy(blk.value(), tmpblk->value(), blk.length());
	}

	// Construct TLV object.
	obj = TLVObjectFactory::instance()->createTLVObject(blk);
	if (!obj)
		PERR << "Unable to construct TLV object.\n";

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
bool TLVReaderWriter::sendto(const ITLVObject &obj, const HostAddress &addr,
		uint16_t port, UDPSocket *socket)
{
	bool success = false;
	int ret;
	StandardTLVBlock *blk = obj.toTLVBlock();
	UDPSocket *activesock = (socket == NULL) ?
			dynamic_cast<UDPSocket *>(_socket) : socket;

	if (!activesock) {
		PERR << "No active UDP socket found.\n";
		return false;
	}

	if (blk) {
		PINFO("Sending a message to UDP socket.");
		ret = activesock->sendto(blk->plainBuffer(), blk->plainSize(),
				addr, port);
		if (!(success = (ret == (int)blk->plainSize()))) {
			if (ret > 0) {
				PERR << "Expected " << blk->plainSize() << " bytes but " <<
						ret << " bytes written.\n";
			} else {
				PERR<< "Fail to write.\n";
			}
		}
	} else {
		PERR << "Unable to create TLV block from given object.\n";
	}

	delete blk;
	return success;
}

}
