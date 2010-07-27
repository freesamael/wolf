/**
 * \file CFLOWStringCreator.h
 * \date Jun 20, 2010
 * \author samael
 */

#ifndef CFLOWSTRINGCREATOR_H_
#define CFLOWSTRINGCREATOR_H_

#include "CTlvStringCreator.h"
#include "CFlowString.h"

namespace wolf
{

/**
 * Creator for CFlowString.
 */
class CFlowStringCreator: public CTlvStringCreator
{
public:
	ITlvObject* create() const { return new CFlowString(); }
	ITlvObject* create(const ITlvBlock &blk) const;
};

}

#endif /* CFLOWSTRINGCREATOR_H_ */
