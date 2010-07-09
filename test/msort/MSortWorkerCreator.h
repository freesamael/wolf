/**
 * \file MSortWorkerCreator.h
 * \date Jun 28, 2010
 * \author samael
 */

#ifndef MSORTWORKERCREATOR_H_
#define MSORTWORKERCREATOR_H_

#include <ITlvObjectCreator.h>
#include "MSortWorker.h"

class MSortWorkerCreator: public cml::ITlvObjectCreator
{
public:
	MSortWorkerCreator();
	cml::ITlvObject* create() const { return new MSortWorker(); }
	cml::ITlvObject* create(const cml::ITlvBlock &blk) const;
};

#endif /* MSORTWORKERCREATOR_H_ */
