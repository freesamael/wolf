/**
 * \file DUInt16.h
 * \date Jun 20, 2010
 * \author samael
 */

#ifndef DUINT16_H_
#define DUINT16_H_

#include "IDrop.h"
#include "TLVUInt16.h"

namespace wfe
{

/**
 * Specialized TLVUInt16 implementing IDrop.
 */
class DUInt16: public IDrop, public cml::TLVUInt16
{
public:
	DUInt16(uint16_t value = 0): TLVUInt16(value) {}
	DUInt16(const TLVUInt16 &o): TLVUInt16(o) {}
	cml::StandardTLVBlock* toTLVBlock() const;
	IDrop* clone() const;
};

}

#endif /* DUINT16_H_ */
