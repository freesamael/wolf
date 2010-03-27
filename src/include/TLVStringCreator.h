/*
 * TLVStringCreator.h
 *
 *  Created on: Mar 11, 2010
 *      Author: samael
 */

#ifndef TLVSTRINGCREATOR_H_
#define TLVSTRINGCREATOR_H_

#include "ITLVObjectCreator.h"

namespace cml
{

class TLVStringCreator: public ITLVObjectCreator
{
public:
	ITLVObject* create();
	ITLVObject* create(const TLVBlock &blk);
};

}

#endif /* TLVSTRINGCREATOR_H_ */
