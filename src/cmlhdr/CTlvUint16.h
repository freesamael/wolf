/**
 * \file CTlvUInt16.h
 * \date Mar 29, 2010
 * \author samael
 */

#ifndef CTLVUINT16_H_
#define CTLVUINT16_H_

#include <stdint.h>
#include "ITlvObject.h"

namespace cml
{

/**
 * 16 bit unsigned integer with TLV supports.
 */
class CTlvUint16: public ITlvObject
{
public:
	static const uint16_t Size;

	CTlvUint16(uint16_t value = 0): _value(value) {}
	CTlvUint16(const CTlvUint16 &o): ITlvObject(), _value(o._value) {}
	uint16_t value() const { return _value; }
	void setValue(uint16_t v) { _value = v; }
	CTlvBlock* toTLVBlock() const;

private:
	uint16_t _value;
};

}

#endif /* CTLVUINT16_H_ */
