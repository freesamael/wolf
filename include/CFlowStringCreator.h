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
class CFlowStringCreator: public wolf::CTlvStringCreator
{
public:
	wolf::ITlvObject* create() const { return new CFlowString(); }
	wolf::ITlvObject* create(const wolf::ITlvBlock &blk) const;
};

}

#endif /* CFLOWSTRINGCREATOR_H_ */
