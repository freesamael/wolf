/**
 * \file CFlowUint32Creator.h
 * \date Jun 20, 2010
 * \author samael
 */

#ifndef CFLOWUINT32CREATOR_H_
#define CFLOWUINT32CREATOR_H_

#include "CTlvUint32Creator.h"
#include "CFlowUint32.h"

namespace wolf
{

/**
 * Creator for CFlowUint32
 */
class CFlowUint32Creator: public CTlvUint32Creator
{
public:
	ITlvObject* create() const { return new CFlowUint32(); }
	ITlvObject* create(const ITlvBlock &blk) const;
};

}

#endif /* CFLOWUINT32CREATOR_H_ */
