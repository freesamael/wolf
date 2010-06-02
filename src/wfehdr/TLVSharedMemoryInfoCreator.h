/**
 * \file TLVSharedMemoryInfoCreator.h
 * \date Apr 8, 2010
 * \author samael
 */

#ifndef TLVSHAREDMEMORYINFOCREATOR_H_
#define TLVSHAREDMEMORYINFOCREATOR_H_

#include "ITLVObjectCreator.h"
#include "TLVSharedMemoryInfo.h"

namespace wfe
{

class TLVSharedMemoryInfoCreator: public cml::ITLVObjectCreator
{
public:
	cml::ITLVObject* create() const { return new TLVSharedMemoryInfo(); }
	cml::ITLVObject* create(const cml::ITLVBlock &blk) const;
};

}

#endif /* TLVSHAREDMEMORYINFOCREATOR_H_ */
