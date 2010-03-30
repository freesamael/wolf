/*
 * TLVMessageCreator.h
 *
 *  Created on: Mar 29, 2010
 *      Author: samael
 */

#ifndef TLVMESSAGECREATOR_H_
#define TLVMESSAGECREATOR_H_

#include "ITLVObjectCreator.h"
#include "TLVMessage.h"

namespace wfe
{

class TLVMessageCreator: public cml::ITLVObjectCreator
{
public:
	inline cml::ITLVObject* create() const { return new TLVMessage(); }
	cml::ITLVObject* create(const cml::ITLVBlock &blk) const;
};

}

#endif /* TLVMESSAGECREATOR_H_ */
