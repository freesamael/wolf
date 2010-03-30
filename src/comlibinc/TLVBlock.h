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
#include "TLVTypes.h"
#include "ITLVBlock.h"

namespace cml
{

class TLVBlock: public ITLVBlock
{
public:
	TLVBlock(unsigned short type = TLV_TYPE_INVALID, unsigned short length = 0);
	~TLVBlock();
	inline unsigned short type() const {
		return ntohs(((unsigned short *)_buf)[0]); }
	inline unsigned short length() const {
		return ntohs(((unsigned short *)_buf)[1]); }
	inline unsigned short size() const { return length() + szHeader; }
	void setType(unsigned short type);
	void setLength(unsigned short len);
	inline char* getCompleteBuffer() { return _buf; }
	inline const char* getCompleteBuffer() const { return _buf; }
	inline char* getValueBuffer() {
		return (!length()) ? NULL : &_buf[szHeader]; }
	inline const char* getValueBuffer() const {
		return (!length()) ? NULL : &_buf[szHeader]; }

	static TLVBlock* concate(const std::vector<const ITLVBlock*> &blocks);

private:
	void _writetype(unsigned short type);
	void _writelength(unsigned short length);
	char *_buf;
};


}

#endif /* TLVBLOCK_H_ */
