/**
 * \file ITLVObjectCreator.h
 * \date Mar 10, 2010
 * \author samael
 */

#ifndef ITLVOBJECTCREATOR_H_
#define ITLVOBJECTCREATOR_H_

#include "ITLVObject.h"
#include "ITLVBlock.h"

namespace cml
{

/**
 * \interface ITLVObjectCreator
 *
 * All TLV objects (ITLVObject derives) should have a corresponding creator.
 * It must be registered to TLVObjectFactory.
 *
 * \see ITLVObject
 */
class ITLVObjectCreator
{
public:
	virtual ~ITLVObjectCreator() {}
	/// Create a TLV object corresponding to this creator.
	virtual ITLVObject* create() const = 0;
	/// Create a TLV object corresponding to this creator from TLV block.
	virtual ITLVObject* create(const ITLVBlock &blk) const = 0;
};

}

#endif /* ITLVOBJECTCREATOR_H_ */
