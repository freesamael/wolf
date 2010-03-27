/*
 * TLVBlock.h
 *
 *  Created on: Mar 10, 2010
 *      Author: samael
 */

#ifndef TLVBLOCK_H_
#define TLVBLOCK_H_

#include <cstddef>

#define TLV_TYPE_INVALID 	0
#define TLV_TYPE_STRING		1

namespace cml
{

class TLVBlock
{
public:
	TLVBlock(unsigned short type = TLV_TYPE_INVALID,
			unsigned short length = 0, char *value = NULL);
	~TLVBlock();
	inline size_t typeSize() const { return sizeof(_type); }
	inline size_t lengthSize() const { return sizeof(_length); }
	inline size_t headerSize() const { return sizeof(_type) + sizeof(_length); }
	inline unsigned short type() const { return _type; }
	inline unsigned short length() const { return _length; }
	inline char* value() const { return _value; }
	inline void setType(unsigned short type) { _type = type; }
	inline void setLength(unsigned short len) { _length = len; }
	inline void setValue(char *value) { _value = value; }
	void allocBuffer();

private:
	unsigned short _type;
	unsigned short _length;
	char *_value;
};

}

#endif /* TLVBLOCK_H_ */
