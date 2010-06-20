/**
 * \file DUInt32Creator.h
 * \date Jun 20, 2010
 * \author samael
 */

#ifndef DUINT32CREATOR_H_
#define DUINT32CREATOR_H_

#include "TLVUInt32Creator.h"
#include "DUInt32.h"

namespace wfe
{

/**
 * Creator for DUInt32
 */
class DUInt32Creator: public cml::TLVUInt32Creator
{
public:
	cml::ITLVObject* create() const { return new DUInt32(); }
	cml::ITLVObject* create(const cml::ITLVBlock &blk) const;
};

}

#endif /* DUINT32CREATOR_H_ */
