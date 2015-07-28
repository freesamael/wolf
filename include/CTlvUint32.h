/**
 * \file CTlvUint32.h
 * \date Mar 29, 2010
 * \author samael
 */

#ifndef CTLVUINT32_H_
#define CTLVUINT32_H_

#include <cstdint>
#include "ITlvObject.h"

namespace wolf
{

/**
 * 32bit unsigned integer with TLV supports.
 */
class CTlvUint32: public ITlvObject
{
public:
	static const uint32_t Size;

	CTlvUint32(uint32_t value = 0): _value(value) {}
	CTlvUint32(const CTlvUint32 &o): ITlvObject(), _value(o._value) {}
	uint32_t value() const { return _value; }
	void setValue(uint32_t v) { _value = v; }
	CTlvBlock* toTLVBlock() const;

private:
	uint32_t _value;
};

}

#endif /* CTLVUINT32_H_ */
