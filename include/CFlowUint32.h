/**
 * \file CFlowUint32.h
 * \date Jun 20, 2010
 * \author samael
 */

#ifndef CFLOWUINT32_H_
#define CFLOWUINT32_H_

#include "IDrop.h"
#include "CTlvUint32.h"

namespace wolf
{

/**
 * Specialized CTlvUint32 implementing IDrop.
 */
class CFlowUint32: public IDrop, public CTlvUint32
{
public:
	CFlowUint32(uint32_t value = 0): CTlvUint32(value) {}
	CFlowUint32(const CTlvUint32 &o): CTlvUint32(o) {}
	CTlvBlock* toTLVBlock() const;
	IDrop* clone() const;
};

}

#endif /* CFLOWUINT32_H_ */
