/**
 * \file HelloWorkerCreator.h
 * \date Apr 14, 2010
 * \author samael
 */

#ifndef HELLOWORKERCREATOR_H_
#define HELLOWORKERCREATOR_H_

#include <ITLVObjectCreator.h>
#include "HelloWorker.h"

class HelloWorkerCreator: public cml::ITLVObjectCreator
{
public:
	inline cml::ITLVObject* create() const { return new HelloWorker(); }
	inline cml::ITLVObject* create(const cml::ITLVBlock &blk) const
			{ return create(); }
};

#endif /* HELLOWORKERCREATOR_H_ */
