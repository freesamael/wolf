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
TLVBlock::TLVBlock(unsigned short type, unsigned short length)
{
	_buf = new char[length + szHeader];
	_writetype(type);
	_writelength(length);
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
	_writetype(type);
}

/**
 * @brief Set length and allocate proper buffer.
 */
void TLVBlock::setLength(unsigned short len)
{
	unsigned short tp = type();
	delete _buf;
	_buf = new char[len + szHeader];

	_writetype(tp);
	_writelength(len);
}

/**
 * @brief Write type into buffer.
 */
void TLVBlock::_writetype(unsigned short type)
{
	unsigned short ntype = htons(type);
	memcpy(_buf, &ntype, szType);
}

/**
 * @brief Write length into buffer.
 */
void TLVBlock::_writelength(unsigned short length)
{
	unsigned short nlen = htons(length);
	memcpy(_buf + szType, &nlen, szLength);
}

/**
 * @brief Concatenate TLV blocks into one TLV block (nested TLV).
 * @note Type will be TLV_TYPE_INVALID, which should be modified afterward.
 */
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
