/**
 * \file TLVUInt16.h
 * \date Mar 29, 2010
 * \author samael
 */

#ifndef TLVUINT16_H_
#define TLVUINT16_H_

#include <stdint.h>
#include "ITLVObject.h"

namespace cml
{

/**
 * 16 bit unsigned integer with TLV supports.
 */
class TLVUInt16: public ITLVObject
{
public:
	static const uint16_t Size;

	TLVUInt16(uint16_t value = 0): _value(value) {}
	TLVUInt16(const TLVUInt16 &o): ITLVOBject(), _value(o._value) {}
	uint16_t value() const { return _value; }
	void setValue(uint16_t v) { _value = v; }
	StandardTLVBlock* toTLVBlock() const;

private:
	uint16_t _value;
};

}

#endif /* TLVUINT16_H_ */
