/**
 * \file CTlvUint16Creator.h
 * \date Mar 29, 2010
 * \author samael
 */

#ifndef CTLVUINT16CREATOR_H_
#define CTLVUINT16CREATOR_H_

#include "ITlvObjectCreator.h"
#include "CTlvUint16.h"

namespace cml
{

/**
 * Creator for CTlvUint16.
 */
class CTlvUint16Creator: public ITlvObjectCreator
{
public:
	inline ITlvObject* create() const { return new CTlvUint16(); }
	ITlvObject* create(const ITlvBlock &blk) const;
};

}

#endif /* CTLVUINT16CREATOR_H_ */
