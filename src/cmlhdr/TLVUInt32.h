/**
 * \file TLVUInt32.h
 * \date Mar 29, 2010
 * \author samael
 */

#ifndef TLVUINT32_H_
#define TLVUINT32_H_

#include <stdint.h>
#include "ITLVObject.h"

namespace cml
{

/**
 * 32bit unsigned integer with TLV supports.
 */
class TLVUInt32: public ITLVObject
{
public:
	static const uint16_t Size;

	TLVUInt32(uint32_t value = 0): _value(value) {}
	TLVUInt32(const TLVUInt32 &o): _value(o._value) {}
	uint32_t value() const { return _value; }
	void setValue(uint32_t v) { _value = v; }
	StandardTLVBlock* toTLVBlock() const;

private:
	uint32_t _value;
};

}

#endif /* TLVUINT32_H_ */
