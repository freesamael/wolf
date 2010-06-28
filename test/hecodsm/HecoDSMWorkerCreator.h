/**
 * \file HecoDSMWorkerCreator.h
 * \date Apr 15, 2010
 * \author samael
 */

#ifndef HECODSMWORKERCREATOR_H_
#define HECODSMWORKERCREATOR_H_

#include <ITLVObjectCreator.h>
#include "HecoDSMWorker.h"

class HecoDSMWorkerCreator: public cml::ITLVObjectCreator
{
	inline cml::ITLVObject* create() const { return new HecoDSMWorker(); }
	cml::ITLVObject* create(const cml::ITLVBlock &blk) const;
};

#endif /* HECODSMWORKERCREATOR_H_ */
