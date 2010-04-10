/*
 * NumberSubstractorWorkerCreator.h
 *
 *  Created on: Apr 10, 2010
 *      Author: samael
 */

#ifndef NUMBERSUBSTRACTORWORKERCREATOR_H_
#define NUMBERSUBSTRACTORWORKERCREATOR_H_

#include <ITLVObjectCreator.h>

class NumberSubstractorWorkerCreator: public cml::ITLVObjectCreator
{
public:
	cml::ITLVObject* create() const;
	cml::ITLVObject* create(const cml::ITLVBlock &blk) const;
};

#endif /* NUMBERSUBSTRACTORWORKERCREATOR_H_ */
