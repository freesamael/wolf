/**
 * \file CTlvSharedMemoryInfoCreator.h
 * \date Apr 8, 2010
 * \author samael
 */

#ifndef CTLVSHAREDMEMORYINFOCREATOR_H_
#define CTLVSHAREDMEMORYINFOCREATOR_H_

#include "ITlvObjectCreator.h"
#include "CTlvSharedMemoryInfo.h"

namespace wfe
{

class CTlvSharedMemoryInfoCreator: public cml::ITlvObjectCreator
{
public:
	cml::ITlvObject* create() const { return new CTlvSharedMemoryInfo(); }
	cml::ITlvObject* create(const cml::ITlvBlock &blk) const;
};

}

#endif /* CTLVSHAREDMEMORYINFOCREATOR_H_ */
