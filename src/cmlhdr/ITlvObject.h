/**
 * \file ITlvObject.h
 * \date Mar 10, 2010
 * \author samael
 */

#ifndef ITLVOBJECT_H_
#define ITLVOBJECT_H_

#include <cstddef>
#include "CTlvBlock.h"

namespace cml
{

class CTlvBlock;

/**
 * \interface ITlvObject
 *
 * All objects that can convert to/from TLV blocks should implement this
 * interface. Objects need to be registered to TLVObjectCreator (either manually
 * or by TLV_OBJECT_REGISTRATION(type, id, creator) helper macro) with the
 * corresponding TLV type id and creator.
 *
 * \see ITLVObjectCreator
 */
class ITlvObject
{
public:
	virtual ~ITlvObject() {}
	/// Convert to StandardTLVBlock.
	virtual CTlvBlock* toTLVBlock() const = 0;
};

}

#endif /* ITLVOBJECT_H_ */
