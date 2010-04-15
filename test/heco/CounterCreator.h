/**
 * \file CounterCreator.h
 * \date Apr 15, 2010
 * \author samael
 */

#ifndef COUNTERCREATOR_H_
#define COUNTERCREATOR_H_

#include <ITLVObjectCreator.h>
#include "Counter.h"

class CounterCreator: public cml::ITLVObjectCreator
{
	inline cml::ITLVObject* create() const { return new Counter(); }
	cml::ITLVObject* create(const cml::ITLVBlock &blk) const;
};

#endif /* COUNTERCREATOR_H_ */
