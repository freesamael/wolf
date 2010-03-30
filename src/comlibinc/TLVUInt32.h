/*
 * TLVUInt32.h
 *
 *  Created on: Mar 29, 2010
 *      Author: samael
 */

#ifndef TLVUINT32_H_
#define TLVUINT32_H_

#include "ITLVObject.h"

namespace cml
{

class TLVUInt32: public ITLVObject
{
public:
	TLVUInt32(unsigned int value = 0): _value(value) {}
	unsigned int value() const { return _value; }
	void setValue(unsigned int v) { _value = v; }
	TLVBlock* toTLVBlock() const;

private:
	unsigned int _value;
};

}

#endif /* TLVUINT32_H_ */
