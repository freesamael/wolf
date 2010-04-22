/**
 * \file ITLVObject.h
 * \date Mar 10, 2010
 * \author samael
 */

#ifndef ITLVOBJECT_H_
#define ITLVOBJECT_H_

#include <cstddef>
#include "TLVBlock.h"

namespace cml
{

class StandardTLVBlock;

/**
 * \interface ITLVObject
 *
 * All objects that can convert to/from TLV blocks should implement this
 * interface. Objects need to be registered to TLVObjectCreator (either manually
 * or by TLV_OBJECT_REGISTRATION(type, id, creator) helper macro) with the
 * corresponding TLV type id and creator.
 *
 * \see ITLVObjectCreator
 */
class ITLVObject
{
public:
	virtual ~ITLVObject() {}
	virtual StandardTLVBlock* toTLVBlock() const = 0;
};

}

#endif /* ITLVOBJECT_H_ */
