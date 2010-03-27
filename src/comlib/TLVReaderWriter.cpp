/*
 * TLVReaderWriter.cpp
 *
 *  Created on: Mar 11, 2010
 *      Author: samael
 */

#include "TLVReaderWriter.h"
#include "TLVBlock.h"
#include "ITLVObject.h"
#include "TLVObjectFactory.h"

using namespace std;

namespace cml
{

TLVReaderWriter::TLVReaderWriter(AbstractSocket *socket):
		_socket(socket)
{
	pthread_mutex_init(&_mutex, NULL);
}

TLVReaderWriter::~TLVReaderWriter()
{
	pthread_mutex_destroy(&_mutex);
}

/**
 * @brief Read a TLV object from given socket.
 * @param socket Socket to read, or NULL to use the one given with constructor.
 * @return Object on success, NULL on failure.
 * @note User should delete the object manually.
 */
ITLVObject* TLVReaderWriter::read(AbstractSocket *socket)
{
	bool success = false;
	int ret;
	unsigned int type, length;
	TLVBlock blk;
	ITLVObject *obj = NULL;
	AbstractSocket *activesock = (socket == NULL) ? _socket : socket;

	if (!activesock)
		return NULL;

	pthread_mutex_lock(&_mutex);
	// Read type.
	ret = activesock->read((char*)&type, blk.typeSize());
	if (ret == (int)blk.typeSize()) {
		type = ntohs(type);
		// Read length.
		ret = activesock->read((char*)&length, blk.lengthSize());
		if (ret == (int)blk.lengthSize()) {
			length = ntohs(length);
			blk.setType(type);
			blk.setLength(length);
			blk.allocBuffer();
			// Read value.
			ret = activesock->read(blk.value(), blk.length());
			if (ret == blk.length())
				success = true;
		}
	}
	pthread_mutex_unlock(&_mutex);

	if (success)
		obj = TLVObjectFactory::instance()->createTLVObject(blk);

	return obj;
}

/**
 * @brief Write a TLV object.
 * @param socket Socket to write, or NULL to use the one from constructor.
 */
bool TLVReaderWriter::write(const ITLVObject &obj, AbstractSocket *socket)
{
	bool success = false;
	int ret, wsize = 0;
	TLVBlock *blk = obj.toTLVBlock();
	AbstractSocket *activesock = (socket == NULL) ? _socket : socket;

	if (!activesock)
		return false;

	if (blk) {
		pthread_mutex_lock(&_mutex);
		unsigned short type = htons(blk->type()), length = htons(blk->length());
		// Write type.
		ret = activesock->write((char*)&type, blk->typeSize());
		wsize += ret;
		if (ret == (int)blk->typeSize()) {
			// Write length.
			ret = activesock->write((char*)&length, blk->lengthSize());
			wsize += ret;
			if (ret == (int)blk->lengthSize()) {
				// Write value.
				ret = activesock->write((char*)blk->value(), blk->length());
				wsize += ret;
			}
		}
		pthread_mutex_unlock(&_mutex);
		success = (wsize == (int)(blk->length() + blk->headerSize()));
	}

	delete blk;
	return success;
}

}
