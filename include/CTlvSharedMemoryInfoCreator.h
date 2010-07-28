/**
 * \file CTlvSharedMemoryInfoCreator.h
 * \date Apr 8, 2010
 * \author samael
 */

#ifndef CTLVSHAREDMEMORYINFOCREATOR_H_
#define CTLVSHAREDMEMORYINFOCREATOR_H_

#include "ITlvObjectCreator.h"
#include "CTlvSharedMemoryInfo.h"

namespace wolf
{

/**
 * Creator for CTlvSharedMemoryInfo.
 */
class CTlvSharedMemoryInfoCreator: public ITlvObjectCreator
{
public:
	ITlvObject* create() const { return new CTlvSharedMemoryInfo(); }
	ITlvObject* create(const ITlvBlock &blk) const;
};

}

#endif /* CTLVSHAREDMEMORYINFOCREATOR_H_ */
