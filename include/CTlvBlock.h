/**
 * \file CTlvBlock.h
 * \date Mar 10, 2010
 * \author samael
 */

#ifndef CTLVBLOCK_H_
#define CTLVBLOCK_H_

#include <cstddef>
#include <vector>
#include <arpa/inet.h>
#include "ITlvBlock.h"
#include "CmlTLVTypes.h"

namespace wolf
{

/**
 * A TLV block which manages it's own buffer. It automatically destroys the
 * buffer on destruction. In case that you need a TLV block sharing the buffer
 * with others and doesn't destory the buffer automatically, use SharedTLVBlock
 * instead.
 */
class CTlvBlock: public ITlvBlock
{
public:
	CTlvBlock(uint32_t type = TLV_TYPE_INVALID,
			uint32_t length = 0);
	CTlvBlock(const CTlvBlock &blk);
	~CTlvBlock();

	// Getters.
	inline uint32_t type() const {
		return ntohl(((uint32_t *)_buf)[0]); }
	inline uint32_t length() const {
		return ntohl(((uint32_t *)_buf)[1]); }
	inline uint32_t plainSize() const { return length() + szHeader; }

	// Setters.
	void setType(uint32_t type);
	void setLength(uint32_t len);

	// Buffer.
	inline char* plainBuffer() { return _buf; }
	inline const char* plainBuffer() const { return _buf; }
	inline char* value() {
		return (!length()) ? NULL : &_buf[szHeader]; }
	inline const char* value() const {
		return (!length()) ? NULL : &_buf[szHeader]; }

	CTlvBlock& operator=(const CTlvBlock &blk);

	// Static helpers.
	static CTlvBlock* concate(const std::vector<const ITlvBlock*> &blocks);

private:
	void _writetype(uint32_t type);
	void _writelength(uint32_t length);
	char *_buf;
};

/**
 * Used to construct a read-only CTLVBlock with given shared buffer. In this
 * case, this TLVBlock has no setters and won't delete the buffer automatically.
 * It's useful when you need to interpret/parse a TLV block buffer without
 * modifying it because CSharedTLVBlock takes care of net/host byte-order
 * conversion.
 */
class CSharedTlvBlock: public ITlvBlock
{
public:
	CSharedTlvBlock(const char *shared_buf): _buf(shared_buf) {}
	CSharedTlvBlock(const CSharedTlvBlock &blk): ITlvBlock(), _buf(blk._buf) {}
	CSharedTlvBlock(const CTlvBlock &blk): _buf(blk.plainBuffer()) {}
	inline uint32_t type() const {
		return ntohl(((uint32_t *)_buf)[0]); }
	inline uint32_t length() const {
		return ntohl(((uint32_t *)_buf)[1]); }
	inline uint32_t plainSize() const { return length() + szHeader; }
	inline const char* plainBuffer() const { return _buf; }
	inline const char* value() const {
		return (!length()) ? NULL : &_buf[szHeader]; }
	inline CSharedTlvBlock& operator=(const CSharedTlvBlock &blk)
		{ _buf = blk._buf; return *this; }

private:
	const char *_buf;
};

}

#endif /* CTLVBLOCK_H_ */
