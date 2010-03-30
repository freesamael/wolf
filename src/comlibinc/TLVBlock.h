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

#define TLV_TYPE_INVALID 	0

namespace cml
{

class TLVBlock
{
public:
	static const unsigned short szType, szLength, szHeader;
	TLVBlock(unsigned short type = TLV_TYPE_INVALID, unsigned short length = 0);
	~TLVBlock();
	inline unsigned short type() const { return _type; }
	inline unsigned short length() const { return _length; }
	inline unsigned short size() const { return _length + szHeader; }
	void setType(unsigned short type);
	void setLength(unsigned short len);
	inline char* getCompleteBuffer() { return _buf; }
	inline const char* getCompleteBuffer() const { return _buf; }
	inline char* getValueBuffer() {
		return (!_length) ? NULL : &_buf[szHeader]; }
	inline const char* getValueBuffer() const {
		return (!_length) ? NULL : &_buf[szHeader]; }

	static TLVBlock* concate(const std::vector<TLVBlock*> &blocks);

private:
	void _writetype();
	void _writelength();
	unsigned short _type;
	unsigned short _length;
	char *_buf;
};

}

#endif /* TLVBLOCK_H_ */
