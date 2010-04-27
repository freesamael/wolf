/**
 * \file TLVBlock.cpp
 * \date Mar 10, 2010
 * \author samael
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
StandardTLVBlock::StandardTLVBlock(uint16_t type, uint16_t length)
{
	_buf = new char[length + szHeader];
	_writetype(type);
	_writelength(length);
}

StandardTLVBlock::StandardTLVBlock(const StandardTLVBlock &blk)
{
	_buf = new char[blk.plainSize()];
	memcpy(_buf, blk.plainBuffer(), blk.plainSize());
}

StandardTLVBlock::~StandardTLVBlock()
{
	delete [] _buf;
}

/**
 * Set TLV type.
 */
void StandardTLVBlock::setType(uint16_t type)
{
	_writetype(type);
}

/**
 * Set length and allocate proper buffer.
 */
void StandardTLVBlock::setLength(uint16_t len)
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
StandardTLVBlock& StandardTLVBlock::operator=(const StandardTLVBlock &blk)
{
	delete _buf;
	_buf = new char[blk.plainSize()];
	memcpy(_buf, blk.plainBuffer(), blk.plainSize());
	return *this;
}

/**
 * Write type into buffer.
 */
void StandardTLVBlock::_writetype(uint16_t type)
{
	uint16_t ntype = htons(type);
	memcpy(_buf, &ntype, szType);
}

/**
 * Write length into buffer.
 */
void StandardTLVBlock::_writelength(uint16_t length)
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
StandardTLVBlock* StandardTLVBlock::concate(const vector<const ITLVBlock*> &blocks)
{
	StandardTLVBlock *blk = new StandardTLVBlock();

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
