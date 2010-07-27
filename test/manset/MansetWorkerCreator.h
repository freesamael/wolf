/**
 * \file MansetWorkerCreator.h
 * \date Jul 17, 2010
 * \author samael
 */

#ifndef MANSETWORKERCREATOR_H_
#define MANSETWORKERCREATOR_H_

#include <ITlvObjectCreator.h>
#include "MansetWorker.h"

class MansetWorkerCreator: public wolf::ITlvObjectCreator
{
public:
	wolf::ITlvObject* create() const { return new MansetWorker(); }
	wolf::ITlvObject* create(const wolf::ITlvBlock &blk) const;
};

#endif /* MANSETWORKERCREATOR_H_ */
