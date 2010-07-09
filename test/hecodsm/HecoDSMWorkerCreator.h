/**
 * \file HecoDSMWorkerCreator.h
 * \date Apr 15, 2010
 * \author samael
 */

#ifndef HECODSMWORKERCREATOR_H_
#define HECODSMWORKERCREATOR_H_

#include <ITlvObjectCreator.h>
#include "HecoDSMWorker.h"

class HecoDSMWorkerCreator: public cml::ITlvObjectCreator
{
	inline cml::ITlvObject* create() const { return new HecoDSMWorker(); }
	cml::ITlvObject* create(const cml::ITlvBlock &blk) const;
};

#endif /* HECODSMWORKERCREATOR_H_ */
