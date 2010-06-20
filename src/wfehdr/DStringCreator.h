/**
 * \file DStringCreator.h
 * \date Jun 20, 2010
 * \author samael
 */

#ifndef DSTRINGCREATOR_H_
#define DSTRINGCREATOR_H_

#include "TLVStringCreator.h"
#include "DString.h"

namespace wfe
{

/**
 * Creator for DString.
 */
class DStringCreator: public cml::TLVStringCreator
{
public:
	cml::ITLVObject* create() const { return new DString(); }
	cml::ITLVObject* create(const cml::ITLVBlock &blk) const;
};

}

#endif /* DSTRINGCREATOR_H_ */
