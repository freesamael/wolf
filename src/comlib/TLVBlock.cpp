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

/**
 * Construct a TLVblock with given value.
 *
 * \note
 * TLVBlock takes the ownership of it's own buffer, and deletes it on
 * destruction.
 */
StandardTLVBlock::StandardTLVBlock(unsigned short type, unsigned short length)
{
	_buf = new char[length + szHeader];
	_writetype(type);
	_writelength(length);
}

StandardTLVBlock::~StandardTLVBlock()
{
	delete [] _buf;
}

/**
 * Set TLV type.
 */
void StandardTLVBlock::setType(unsigned short type)
{
	_writetype(type);
}

/**
 * Set length and allocate proper buffer.
 */
void StandardTLVBlock::setLength(unsigned short len)
{
	unsigned short tp = type();
	delete [] _buf;
	_buf = new char[len + szHeader];

	_writetype(tp);
	_writelength(len);
}

/**
 * Write type into buffer.
 */
void StandardTLVBlock::_writetype(unsigned short type)
{
	unsigned short ntype = htons(type);
	memcpy(_buf, &ntype, szType);
}

/**
 * Write length into buffer.
 */
void StandardTLVBlock::_writelength(unsigned short length)
{
	unsigned short nlen = htons(length);
	memcpy(_buf + szType, &nlen, szLength);
}

/**
 * Concatenate TLV blocks into one TLV block (nested TLV).
 *
 * \note
 * Type will be set as TLV_TYPE_INVALID, which should be modified afterward.
 */
StandardTLVBlock* StandardTLVBlock::concate(const vector<const ITLVBlock*> &blocks)
{
	StandardTLVBlock *blk = new StandardTLVBlock();

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
