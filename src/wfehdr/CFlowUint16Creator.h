/**
 * \file CFlowUint16Creator.h
 * \date Jun 20, 2010
 * \author samael
 */

#ifndef CFLOWUINT16CREATOR_H_
#define CFLOWUINT16CREATOR_H_

#include "CTlvUint16Creator.h"
#include "CFlowUint16.h"

namespace wfe
{

/**
 * Creator for CFlowUint16.
 */
class CFlowUint16Creator: public cml::CTlvUint16Creator
{
public:
	cml::ITlvObject* create() const { return new CFlowUint16(); }
	cml::ITlvObject* create(const cml::ITlvBlock &blk) const;
};

}

#endif /* CFLOWUINT16CREATOR_H_ */
