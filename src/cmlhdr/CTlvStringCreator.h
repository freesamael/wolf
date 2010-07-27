/**
 * \file CTlvStringCreator.h
 * \date Mar 11, 2010
 * \author samael
 */

#ifndef CTLVSTRINGCREATOR_H_
#define CTLVSTRINGCREATOR_H_

#include "ITlvObjectCreator.h"
#include "CTlvString.h"

namespace wolf
{

/**
 * Creator for CTlvString.
 */
class CTlvStringCreator: public ITlvObjectCreator
{
public:
	inline ITlvObject* create() const { return new CTlvString(); }
	ITlvObject* create(const ITlvBlock &blk) const;
};

}

#endif /* CTLVSTRINGCREATOR_H_ */
