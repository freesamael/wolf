/*
 * SharedTLVBlock.h
 *
 *  Created on: Mar 30, 2010
 *      Author: samael
 */

#ifndef SHAREDTLVBLOCK_H_
#define SHAREDTLVBLOCK_H_

#include <arpa/inet.h>
#include "ITLVBlock.h"

namespace cml
{

/**
 * @detailed Construct a read-only TLVBlock with given shared buffer. In this
 * case, this TLVBlock has no setters and won't delete the buffer. It's useful
 * when you need to interpret a TLV block buffer without modifying it because
 * TLVBlock takes care of net/host byte-order conversion.
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

#endif /* SHAREDTLVBLOCK_H_ */
