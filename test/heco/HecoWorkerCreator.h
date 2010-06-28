/**
 * \file HecoWorkerCreator.h
 * \date Jun 20, 2010
 * \author samael
 */

#ifndef HECOWORKERCREATOR_H_
#define HECOWORKERCREATOR_H_

#include <ITLVObjectCreator.h>
#include "HecoWorker.h"

class HecoWorkerCreator: public cml::ITLVObjectCreator
{
public:
	cml::ITLVObject* create() const { return new HecoWorker(); };
	cml::ITLVObject* create(const cml::ITLVBlock &blk) const;
};

#endif /* HECOWORKERCREATOR_H_ */
