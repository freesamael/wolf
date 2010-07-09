/**
 * \file CFLOWStringCreator.h
 * \date Jun 20, 2010
 * \author samael
 */

#ifndef CFLOWSTRINGCREATOR_H_
#define CFLOWSTRINGCREATOR_H_

#include "CTlvStringCreator.h"
#include "CFlowString.h"

namespace wfe
{

/**
 * Creator for CFlowString.
 */
class CFlowStringCreator: public cml::CTlvStringCreator
{
public:
	cml::ITlvObject* create() const { return new CFlowString(); }
	cml::ITlvObject* create(const cml::ITlvBlock &blk) const;
};

}

#endif /* CFLOWSTRINGCREATOR_H_ */
