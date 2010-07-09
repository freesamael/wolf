/**
 * \file HecoWorkerCreator.h
 * \date Jun 20, 2010
 * \author samael
 */

#ifndef HECOWORKERCREATOR_H_
#define HECOWORKERCREATOR_H_

#include <ITlvObjectCreator.h>
#include "HecoWorker.h"

class HecoWorkerCreator: public cml::ITlvObjectCreator
{
public:
	cml::ITlvObject* create() const { return new HecoWorker(); };
	cml::ITlvObject* create(const cml::ITlvBlock &blk) const;
};

#endif /* HECOWORKERCREATOR_H_ */
