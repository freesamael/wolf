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

class CTlvSharedMemoryInfoCreator: public wolf::ITlvObjectCreator
{
public:
	wolf::ITlvObject* create() const { return new CTlvSharedMemoryInfo(); }
	wolf::ITlvObject* create(const wolf::ITlvBlock &blk) const;
};

}

#endif /* CTLVSHAREDMEMORYINFOCREATOR_H_ */
