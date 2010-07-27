/**
 * \file HecoDSMWorkerCreator.h
 * \date Apr 15, 2010
 * \author samael
 */

#ifndef HECODSMWORKERCREATOR_H_
#define HECODSMWORKERCREATOR_H_

#include <ITlvObjectCreator.h>
#include "HecoDSMWorker.h"

class HecoDSMWorkerCreator: public wolf::ITlvObjectCreator
{
	inline wolf::ITlvObject* create() const { return new HecoDSMWorker(); }
	wolf::ITlvObject* create(const wolf::ITlvBlock &blk) const;
};

#endif /* HECODSMWORKERCREATOR_H_ */
