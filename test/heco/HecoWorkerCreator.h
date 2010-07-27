/**
 * \file HecoWorkerCreator.h
 * \date Jun 20, 2010
 * \author samael
 */

#ifndef HECOWORKERCREATOR_H_
#define HECOWORKERCREATOR_H_

#include <ITlvObjectCreator.h>
#include "HecoWorker.h"

class HecoWorkerCreator: public wolf::ITlvObjectCreator
{
public:
	wolf::ITlvObject* create() const { return new HecoWorker(); };
	wolf::ITlvObject* create(const wolf::ITlvBlock &blk) const;
};

#endif /* HECOWORKERCREATOR_H_ */
