/*
 * TLVBlock.h
 *
 *  Created on: Mar 10, 2010
 *      Author: samael
 */

#ifndef TLVBLOCK_H_
#define TLVBLOCK_H_

#include <cstddef>
#include <vector>
#include <arpa/inet.h>
#include "ITLVBlock.h"
#include "TLVTypes.h"

namespace cml
{

class StandardTLVBlock: public ITLVBlock
{
public:
	StandardTLVBlock(unsigned short type = TLV_TYPE_INVALID,
			unsigned short length = 0);
	~StandardTLVBlock();

	// Getters.
	inline unsigned short type() const {
		return ntohs(((unsigned short *)_buf)[0]); }
	inline unsigned short length() const {
		return ntohs(((unsigned short *)_buf)[1]); }
	inline unsigned short size() const { return length() + szHeader; }

	// Setters.
	void setType(unsigned short type);
	void setLength(unsigned short len);

	// Buffer.
	inline char* getCompleteBuffer() { return _buf; }
	inline const char* getCompleteBuffer() const { return _buf; }
	inline char* getValueBuffer() {
		return (!length()) ? NULL : &_buf[szHeader]; }
	inline const char* getValueBuffer() const {
		return (!length()) ? NULL : &_buf[szHeader]; }

	// Static helpers.
	static StandardTLVBlock* concate(const std::vector<const ITLVBlock*> &blocks);

private:
	void _writetype(unsigned short type);
	void _writelength(unsigned short length);
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
	inline unsigned short type() const {
		return ntohs(((unsigned short *)_buf)[0]); }
	inline unsigned short length() const {
		return ntohs(((unsigned short *)_buf)[1]); }
	inline unsigned short size() const { return length() + szHeader; }
	inline const char* getCompleteBuffer() const { return _buf; }
	inline const char* getValueBuffer() const {
		return (!length()) ? NULL : &_buf[szHeader]; }

private:
	const char *_buf;
};

}

#endif /* TLVBLOCK_H_ */
