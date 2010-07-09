/**
 * \file CTlvUint32Creator.h
 * \date Mar 29, 2010
 * \author samael
 */

#ifndef CTLVUINT32CREATOR_H_
#define CTLVUINT32CREATOR_H_

#include "ITlvObjectCreator.h"
#include "CTlvUint32.h"

namespace cml
{

/**
 * Creator for CTlvUint32.
 */
class CTlvUint32Creator: public ITlvObjectCreator
{
public:
	ITlvObject* create() const { return new CTlvUint32(); }
	ITlvObject* create(const ITlvBlock &blk) const;
};

}

#endif /* CTLVUINT32CREATOR_H_ */
