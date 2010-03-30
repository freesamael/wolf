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

#define TLV_TYPE_MESSAGE	10

namespace wfe
{

class TLVMessageCreator: public cml::ITLVObjectCreator
{
public:
	inline cml::ITLVObject* create() const { return new TLVMessage(); }
	cml::ITLVObject* create(const cml::TLVBlock &blk) const;
};

}

#endif /* TLVMESSAGECREATOR_H_ */
