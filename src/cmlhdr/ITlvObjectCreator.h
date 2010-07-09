/**
 * \file ITlvObjectCreator.h
 * \date Mar 10, 2010
 * \author samael
 */

#ifndef ITLVOBJECTCREATOR_H_
#define ITLVOBJECTCREATOR_H_

#include "ITlvObject.h"
#include "ITlvBlock.h"

namespace cml
{

/**
 * \interface ITlvObjectCreator
 *
 * All TLV objects (ITlvObject derives) should have a corresponding creator.
 * It must be registered to TLVObjectFactory.
 *
 * \see ITlvObject
 */
class ITlvObjectCreator
{
public:
	virtual ~ITlvObjectCreator() {}
	/// Create a TLV object corresponding to this creator.
	virtual ITlvObject* create() const = 0;
	/// Create a TLV object corresponding to this creator from TLV block.
	virtual ITlvObject* create(const ITlvBlock &blk) const = 0;
};

}

#endif /* ITLVOBJECTCREATOR_H_ */
