/**
 * \file WorkerCreator.h
 * \date Jun 20, 2010
 * \author samael
 */

#ifndef WORKERCREATOR_H_
#define WORKERCREATOR_H_

#include <ITLVObjectCreator.h>
#include "Worker.h"

class WorkerCreator: public cml::ITLVObjectCreator
{
public:
	cml::ITLVObject* create() const { return new Worker(); };
	cml::ITLVObject* create(const cml::ITLVBlock &blk) const;
};

#endif /* WORKERCREATOR_H_ */
