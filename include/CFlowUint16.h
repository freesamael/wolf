/**
 * \file CFlowUint16.h
 * \date Jun 20, 2010
 * \author samael
 */

#ifndef CFLOWUINT16_H_
#define CFLOWUINT16_H_

#include "IDrop.h"
#include "CTlvUint16.h"

namespace wolf
{

/**
 * Specialized CTlvUint16 implementing IDrop.
 */
class CFlowUint16: public IDrop, public CTlvUint16
{
public:
	CFlowUint16(uint16_t value = 0): CTlvUint16(value) {}
	CFlowUint16(const CTlvUint16 &o): CTlvUint16(o) {}
	CTlvBlock* toTLVBlock() const;
	IDrop* clone() const;
};

}

#endif /* CFLOWUINT16_H_ */
