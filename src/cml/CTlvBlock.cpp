/**
 * \file CTlvBlock.cpp
 * \date Mar 10, 2010
 * \author samael
 */

#include <cstring>
#include <arpa/inet.h>
#include "CTlvBlock.h"

using namespace std;

namespace wolf
{

/**
 * Construction with given value.
 *
 * \note
 * TLVBlock takes the ownership of it's own buffer, and deletes it on
 * destruction.
 */
CTlvBlock::CTlvBlock(uint16_t type, uint16_t length):
		_buf(NULL)
{
	_buf = new char[length + szHeader];
	_writetype(type);
	_writelength(length);
}

CTlvBlock::CTlvBlock(const CTlvBlock &blk):
		ITlvBlock(), _buf(NULL)
{
	_buf = new char[blk.plainSize()];
	memcpy(_buf, blk.plainBuffer(), blk.plainSize());
}

CTlvBlock::~CTlvBlock()
{
	delete [] _buf;
}

/**
 * Set TLV type.
 */
void CTlvBlock::setType(uint16_t type)
{
	_writetype(type);
}

/**
 * Set length and allocate proper buffer.
 */
void CTlvBlock::setLength(uint16_t len)
{
	uint16_t tp = type();
	delete [] _buf;
	_buf = new char[len + szHeader];

	_writetype(tp);
	_writelength(len);
}

/**
 * Operator =
 */
CTlvBlock& CTlvBlock::operator=(const CTlvBlock &blk)
{
	if (&blk != this) {
		delete _buf;
		_buf = new char[blk.plainSize()];
		memcpy(_buf, blk.plainBuffer(), blk.plainSize());
	}
	return *this;
}

/**
 * Write type into buffer.
 */
void CTlvBlock::_writetype(uint16_t type)
{
	uint16_t ntype = htons(type);
	memcpy(_buf, &ntype, szType);
}

/**
 * Write length into buffer.
 */
void CTlvBlock::_writelength(uint16_t length)
{
	uint16_t nlen = htons(length);
	memcpy(_buf + szType, &nlen, szLength);
}

/**
 * Concatenate TLV blocks into one TLV block (nested TLV).
 *
 * \note
 * Type will be set as TLV_TYPE_INVALID, which should be modified afterward.
 */
CTlvBlock* CTlvBlock::concate(const vector<const ITlvBlock*> &blocks)
{
	CTlvBlock *blk = new CTlvBlock();

	uint16_t tlen = 0;
	for (unsigned i = 0; i < blocks.size(); i++)
		tlen += blocks[i]->plainSize();

	blk->setLength(tlen);

	uint16_t offset = 0;
	for (unsigned i = 0; i < blocks.size(); i++) {
		memcpy(&blk->value()[offset], blocks[i]->plainBuffer(),
				blocks[i]->plainSize());
		offset += blocks[i]->plainSize();
	}

	return blk;
}

}
