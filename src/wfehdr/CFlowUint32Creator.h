/**
 * \file CFlowUint32Creator.h
 * \date Jun 20, 2010
 * \author samael
 */

#ifndef CFLOWUINT32CREATOR_H_
#define CFLOWUINT32CREATOR_H_

#include "CTlvUint32Creator.h"
#include "CFlowUint32.h"

namespace wfe
{

/**
 * Creator for CFlowUint32
 */
class CFlowUint32Creator: public cml::CTlvUint32Creator
{
public:
	cml::ITlvObject* create() const { return new CFlowUint32(); }
	cml::ITlvObject* create(const cml::ITlvBlock &blk) const;
};

}

#endif /* CFLOWUINT32CREATOR_H_ */
