/**
 * \file DUInt32.h
 * \date Jun 20, 2010
 * \author samael
 */

#ifndef DUINT32_H_
#define DUINT32_H_

#include "IDrop.h"
#include "TLVUInt32.h"

namespace wfe
{

/**
 * Specialized TLVUInt32 implementing IDrop.
 */
class DUInt32: public IDrop, public cml::TLVUInt32
{
public:
	DUInt32(uint32_t value = 0): TLVUInt32(value) {}
	DUInt32(const TLVUInt32 &o): TLVUInt32(o) {}
	cml::StandardTLVBlock* toTLVBlock() const;
	IDrop* clone() const;
};

}

#endif /* DUINT32_H_ */
