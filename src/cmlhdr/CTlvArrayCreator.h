/**
 * \file CTlvArrayCreator.h
 * \date Apr 8, 2010
 * \author samael
 */

#ifndef CTLVARRAYCREATOR_H_
#define CTLVARRAYCREATOR_H_

#include "ITlvObjectCreator.h"
#include "CTlvArray.h"

namespace wolf
{

/**
 * The creator for CTlvArray.
 */
class CTlvArrayCreator: public ITlvObjectCreator
{
public:
	ITlvObject* create() const { return new CTlvArray(); }
	ITlvObject* create(const ITlvBlock &blk) const;
};

}

#endif /* CTLVARRAYCREATOR_H_ */
