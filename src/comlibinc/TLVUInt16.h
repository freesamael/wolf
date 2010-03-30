/*
 * TLVUInt16.h
 *
 *  Created on: Mar 29, 2010
 *      Author: samael
 */

#ifndef TLVUINT16_H_
#define TLVUINT16_H_

#include "ITLVObject.h"

namespace cml
{

class TLVUInt16: public ITLVObject
{
public:
	TLVUInt16(unsigned short value = 0): _value(value) {}
	unsigned short value() const { return _value; }
	void setValue(unsigned short v) { _value = v; }
	TLVBlock* toTLVBlock() const;

private:
	unsigned short _value;
};

}

#endif /* TLVUINT16_H_ */
