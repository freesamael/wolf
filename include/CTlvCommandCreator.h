/**
 * \file CTlvCommandCreator.h
 * \date Mar 29, 2010
 * \author samael
 */

#ifndef CTLVCOMMANDCREATOR_H_
#define CTLVCOMMANDCREATOR_H_

#include "ITlvObjectCreator.h"
#include "CTlvCommand.h"

namespace wolf
{

/**
 * Creator of CTlvCommand. When a command is created from a TLV block, user need
 * to take care of the deletion of parameters because CTlvCommand doesn't take
 * ownership of that, and parameters constructed here are always constructed
 * on heap.
 */
class CTlvCommandCreator: public ITlvObjectCreator
{
public:
	inline ITlvObject* create() const { return new CTlvCommand(); }
	ITlvObject* create(const ITlvBlock &blk) const;
};

}

#endif /* CTLVCOMMANDCREATOR_H_ */
