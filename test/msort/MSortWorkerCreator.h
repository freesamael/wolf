/**
 * \file MSortWorkerCreator.h
 * \date Jun 28, 2010
 * \author samael
 */

#ifndef MSORTWORKERCREATOR_H_
#define MSORTWORKERCREATOR_H_

#include <ITLVObjectCreator.h>
#include "MSortWorker.h"

class MSortWorkerCreator: public cml::ITLVObjectCreator
{
public:
	MSortWorkerCreator();
	cml::ITLVObject* create() const { return new MSortWorker(); }
	cml::ITLVObject* create(const cml::ITLVBlock &blk) const;
};

#endif /* MSORTWORKERCREATOR_H_ */
