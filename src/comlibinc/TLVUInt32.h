/**
 * \file TLVUInt32.h
 * \date Mar 29, 2010
 * \author samael
 */

#ifndef TLVUINT32_H_
#define TLVUINT32_H_

#include "ITLVObject.h"

namespace cml
{

/**
 * 32bit unsigned integer with TLV supports.
 */
class TLVUInt32: public ITLVObject
{
public:
	static const unsigned short Size;

	TLVUInt32(unsigned int value = 0): _value(value) {}
	unsigned int value() const { return _value; }
	void setValue(unsigned int v) { _value = v; }
	StandardTLVBlock* toTLVBlock() const;

private:
	unsigned int _value;
};

}

#endif /* TLVUINT32_H_ */
