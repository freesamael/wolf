/*
 * TLVReaderWriter.cpp
 *
 *  Created on: Mar 11, 2010
 *      Author: samael
 */

#include <cstdio>
#include <cstring>
#include "TLVReaderWriter.h"
#include "TLVBlock.h"
#include "ITLVObject.h"
#include "TLVObjectFactory.h"
#include "UDPSocket.h"
#include "SharedTLVBlock.h"

#define SZ_MAXBUF	65536	// Maximun 64KB.

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
 * @brief Read a TLV object from given socket.
 * @param socket Socket to read, or NULL to use the one given with constructor.
 * @return Object on success, NULL on failure.
 * @note User should delete the object manually.
 */
ITLVObject* TLVReaderWriter::read(AbstractSocket *socket)
{
	char *localbuf = NULL;
	int ret;
	SharedTLVBlock *tmpblk = NULL;
	TLVBlock blk;
	ITLVObject *obj = NULL;
	AbstractSocket *activesock = (socket == NULL) ? _socket : socket;

	if (!activesock) {
		fprintf(stderr, "TLVReaderWriter::read(): Error: No active socket found.\n");
		return NULL;
	}

	// Read buffer.
	localbuf = new char[SZ_MAXBUF];
	if ((ret = activesock->read(localbuf, SZ_MAXBUF)) == 0) { // End of file.
		delete localbuf;
		return NULL;
	} else if (ret < ITLVBlock::szHeader) {
		fprintf(stderr, "TLVReaderWriter::read(): Error: Data read is too small to be a TLV block.\n");
		delete localbuf;
		return NULL;
	}

	// Construct TLV block.
	tmpblk = new SharedTLVBlock(localbuf);
	blk.setType(tmpblk->type());
	blk.setLength(tmpblk->length());
	if (ret != blk.size()) {
		fprintf(stderr, "TLVReaderWriter::read(): Error: Expected %u bytes but %u bytes read.\n",
				blk.size(), ret);
		delete tmpblk;
		return NULL;
	} else {
		memcpy(blk.getValueBuffer(), tmpblk->getValueBuffer(), blk.length());
	}

	// Construct TLV object.
	obj = TLVObjectFactory::instance()->createTLVObject(blk);
	if (!obj)
		fprintf(stderr, "TLVReaderWriter::read(): Error: Unable to construct TLV object.\n");

	delete tmpblk;
	delete localbuf;

	return obj;
}

/**
 * @brief Read a TLV object from given UDP socket.
 */
ITLVObject* TLVReaderWriter::recvfrom(HostAddress *addr, unsigned short *port,
		UDPSocket *socket)
{
	char *localbuf = NULL;
	int ret;
	TLVBlock blk;
	SharedTLVBlock *tmpblk = NULL;
	ITLVObject *obj = NULL;
	UDPSocket *activesock = (socket == NULL) ?
			dynamic_cast<UDPSocket *>(_socket) : socket;

	if (!activesock) {
		fprintf(stderr, "TLVReaderWriter::recvfrom(): Error: No active UDP socket found.\n");
		return NULL;
	}

	// Read datagram.
	localbuf = new char[SZ_MAXBUF];
	if ((ret = activesock->recvfrom(localbuf, SZ_MAXBUF, addr, port)) == 0) {
		// End of file.
		delete localbuf;
		return NULL;
	} else if (ret < ITLVBlock::szHeader) {
		fprintf(stderr, "TLVReaderWriter::recvfrom(): Error: Data read is too small to be a TLV block.\n");
		delete localbuf;
		return NULL;
	}

	// Construct TLV block.
	tmpblk = new SharedTLVBlock(localbuf);
	blk.setType(tmpblk->type());
	blk.setLength(tmpblk->length());
	if (ret != blk.size()) {
		fprintf(stderr, "TLVReaderWriter::recvfrom(): Error: Expected %u bytes but %u bytes read.\n",
				blk.size(), ret);
		delete tmpblk;
		return NULL;
	} else {
		memcpy(blk.getValueBuffer(), tmpblk->getValueBuffer(), blk.length());
	}

	// Construct TLV object.
	obj = TLVObjectFactory::instance()->createTLVObject(blk);
	if (!obj)
		fprintf(stderr, "TLVReaderWriter::recvfrom(): Error: Unable to construct TLV object.\n");

	delete tmpblk;
	delete localbuf;

	return obj;
}

/**
 * @brief Write a TLV object.
 * @param socket Socket to write, or NULL to use the one from constructor.
 */
bool TLVReaderWriter::write(const ITLVObject &obj, AbstractSocket *socket)
{
	bool success = false;
	int ret;
	TLVBlock *blk = obj.toTLVBlock();
	AbstractSocket *activesock = (socket == NULL) ? _socket : socket;

	if (!activesock) {
		fprintf(stderr, "TLVReaderWriter::write(): Error: No active socket found.\n");
		return false;
	}

	if (blk) {
		ret = activesock->write(blk->getCompleteBuffer(), blk->size());
		if (!(success = (ret == (int)blk->size()))) {
			if (ret > 0) {
				fprintf(stderr, "TLVReaderWriter::write(): Error: Expected %u bytes but %u bytes written.",
						blk->size(), ret);
			} else {
				fprintf(stderr, "TLVReaderWriter::read(): Error: Fail to write.\n");
			}
		}
	} else {
		fprintf(stderr, "TLVReaderWriter::write(): Error: Unable to create TLV block from given object.\n");
	}

	delete blk;
	return success;
}

bool TLVReaderWriter::sendto(const ITLVObject &obj, const HostAddress &addr,
		unsigned short port, UDPSocket *socket)
{
	bool success = false;
	int ret;
	TLVBlock *blk = obj.toTLVBlock();
	UDPSocket *activesock = (socket == NULL) ?
			dynamic_cast<UDPSocket *>(_socket) : socket;

	if (!activesock) {
		fprintf(stderr, "TLVReaderWriter::sendto(): Error: No active UDP socket found.\n");
		return NULL;
	}

	if (blk) {
		ret = activesock->sendto(blk->getCompleteBuffer(), blk->size(),
				addr, port);
		if (!(success = (ret == (int)blk->size()))) {
			if (ret > 0) {
				fprintf(stderr, "TLVReaderWriter::sendto(): Error: Expected %u bytes but %u bytes written.",
						blk->size(), ret);
			} else {
				fprintf(stderr, "TLVReaderWriter::sendto(): Error: Fail to write.\n");
			}
		}
	} else {
		fprintf(stderr, "TLVReaderWriter::sendto(): Error: Unable to create TLV block from given object.\n");
	}

	delete blk;
	return success;
}

}
