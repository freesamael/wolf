/**
 * \file TLVCommandCreator.h
 * \date Mar 29, 2010
 * \author samael
 */

#ifndef TLVCOMMANDCREATOR_H_
#define TLVCOMMANDCREATOR_H_

#include "ITLVObjectCreator.h"
#include "TLVCommand.h"

namespace wfe
{

/**
 * Creator of TLVCommand. When a command is created from a TLV block, user need
 * to take care of the deletion of parameters because TLVCommand doesn't take
 * ownership of that, and parameters constructed here are always constructed
 * on heap.
 */
class TLVCommandCreator: public cml::ITLVObjectCreator
{
public:
	inline cml::ITLVObject* create() const { return new TLVCommand(); }
	cml::ITLVObject* create(const cml::ITLVBlock &blk) const;
};

}

#endif /* TLVCOMMANDCREATOR_H_ */
