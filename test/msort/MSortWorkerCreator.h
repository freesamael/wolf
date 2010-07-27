/**
 * \file MSortWorkerCreator.h
 * \date Jun 28, 2010
 * \author samael
 */

#ifndef MSORTWORKERCREATOR_H_
#define MSORTWORKERCREATOR_H_

#include <ITlvObjectCreator.h>
#include "MSortWorker.h"

class MSortWorkerCreator: public wolf::ITlvObjectCreator
{
public:
	MSortWorkerCreator();
	wolf::ITlvObject* create() const { return new MSortWorker(); }
	wolf::ITlvObject* create(const wolf::ITlvBlock &blk) const;
};

#endif /* MSORTWORKERCREATOR_H_ */
