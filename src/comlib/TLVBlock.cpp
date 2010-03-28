/*
 * TLVBlock.cpp
 *
 *  Created on: Mar 10, 2010
 *      Author: samael
 */

#include <cstring>
#include <arpa/inet.h>
#include "TLVBlock.h"

using namespace std;

namespace cml
{

const unsigned short TLVBlock::szType = sizeof(unsigned short);
const unsigned short TLVBlock::szLength = sizeof(unsigned short);
const unsigned short TLVBlock::szHeader = sizeof(unsigned short) * 2;

/**
 * @note TLVBlock takes the ownership of value buffer, and deletes it on
 * destruction.
 */
TLVBlock::TLVBlock(unsigned short type, unsigned short length):
		_type(type), _length(length)
{
	_buf = new char[length + szHeader];
}

TLVBlock::~TLVBlock()
{
	delete _buf;
}

/**
 * @brief Set TLV type.
 */
void TLVBlock::setType(unsigned short type)
{
	_type = type;

	unsigned short ntype = htons(type);
	memcpy(_buf, &ntype, szType);
}

/**
 * @brief Set length and allocate proper buffer.
 */
void TLVBlock::setLength(unsigned short len)
{
	_length = len;

	delete _buf;
	_buf = new char[len + szHeader];

	unsigned short nlen = htons(len);
	memcpy(&_buf[szType], &nlen, szLength);
}

TLVBlock* TLVBlock::concate(const vector<TLVBlock*> &blocks)
{
	TLVBlock *blk = new TLVBlock();

	unsigned short tlen = 0;
	for (int i = 0; i < (int)blocks.size(); i++)
		tlen += blocks[i]->size();

	blk->setLength(tlen);

	unsigned short offset = 0;
	for (int i = 0; i < (int)blocks.size(); i++) {
		memcpy(&blk->getValueBuffer()[offset], blocks[i]->getCompleteBuffer(),
				blocks[i]->size());
		offset += blocks[i]->size();
	}

	return blk;
}

}
