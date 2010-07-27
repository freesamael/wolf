/**
 * \file CFlowUint16Creator.h
 * \date Jun 20, 2010
 * \author samael
 */

#ifndef CFLOWUINT16CREATOR_H_
#define CFLOWUINT16CREATOR_H_

#include "CTlvUint16Creator.h"
#include "CFlowUint16.h"

namespace wolf
{

/**
 * Creator for CFlowUint16.
 */
class CFlowUint16Creator: public CTlvUint16Creator
{
public:
	ITlvObject* create() const { return new CFlowUint16(); }
	ITlvObject* create(const ITlvBlock &blk) const;
};

}

#endif /* CFLOWUINT16CREATOR_H_ */
