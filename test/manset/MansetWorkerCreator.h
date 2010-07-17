/**
 * \file MansetWorkerCreator.h
 * \date Jul 17, 2010
 * \author samael
 */

#ifndef MANSETWORKERCREATOR_H_
#define MANSETWORKERCREATOR_H_

#include <ITlvObjectCreator.h>
#include "MansetWorker.h"

class MansetWorkerCreator: public cml::ITlvObjectCreator
{
public:
	cml::ITlvObject* create() const { return new MansetWorker(); }
	cml::ITlvObject* create(const cml::ITlvBlock &blk) const;
};

#endif /* MANSETWORKERCREATOR_H_ */
