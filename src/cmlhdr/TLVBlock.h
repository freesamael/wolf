/**
 * \file TLVBlock.h
 * \date Mar 10, 2010
 * \author samael
 */

#ifndef TLVBLOCK_H_
#define TLVBLOCK_H_

#include <cstddef>
#include <vector>
#include <arpa/inet.h>
#include "ITLVBlock.h"
#include "CmlTLVTypes.h"

namespace cml
{

/**
 * A TLV block which manages it's own buffer. It automatically destroys the
 * buffer on destruction. In case that you need a TLV block sharing the buffer
 * with others and doesn't destory the buffer automatically, use SharedTLVBlock
 * instead.
 */
class StandardTLVBlock: public ITLVBlock
{
public:
	StandardTLVBlock(uint16_t type = TLV_TYPE_INVALID,
			uint16_t length = 0);
	StandardTLVBlock(const StandardTLVBlock &blk);
	~StandardTLVBlock();

	// Getters.
	inline uint16_t type() const {
		return ntohs(((uint16_t *)_buf)[0]); }
	inline uint16_t length() const {
		return ntohs(((uint16_t *)_buf)[1]); }
	inline uint16_t plainSize() const { return length() + szHeader; }

	// Setters.
	void setType(uint16_t type);
	void setLength(uint16_t len);

	// Buffer.
	inline char* plainBuffer() { return _buf; }
	inline const char* plainBuffer() const { return _buf; }
	inline char* value() {
		return (!length()) ? NULL : &_buf[szHeader]; }
	inline const char* value() const {
		return (!length()) ? NULL : &_buf[szHeader]; }

	StandardTLVBlock& operator=(const StandardTLVBlock &blk);

	// Static helpers.
	static StandardTLVBlock* concate(const std::vector<const ITLVBlock*> &blocks);

private:
	void _writetype(uint16_t type);
	void _writelength(uint16_t length);
	char *_buf;
};

/**
 * Used to construct a read-only TLVBlock with given shared buffer. In this
 * case, this TLVBlock has no setters and won't delete the buffer automatically.
 * It's useful when you need to interpret/parse a TLV block buffer without
 * modifying it because SharedTLVBlock takes care of net/host byte-order
 * conversion.
 */
class SharedTLVBlock: public ITLVBlock
{
public:
	SharedTLVBlock(const char *shared_buf): _buf(shared_buf) {}
	SharedTLVBlock(const SharedTLVBlock &blk): _buf(blk._buf) {}
	SharedTLVBlock(const StandardTLVBlock &blk): _buf(blk.plainBuffer()) {}
	inline uint16_t type() const {
		return ntohs(((uint16_t *)_buf)[0]); }
	inline uint16_t length() const {
		return ntohs(((uint16_t *)_buf)[1]); }
	inline uint16_t plainSize() const { return length() + szHeader; }
	inline const char* plainBuffer() const { return _buf; }
	inline const char* value() const {
		return (!length()) ? NULL : &_buf[szHeader]; }
	inline SharedTLVBlock& operator=(const SharedTLVBlock &blk)
		{ _buf = blk._buf; return *this; }

private:
	const char *_buf;
};

}

#endif /* TLVBLOCK_H_ */
